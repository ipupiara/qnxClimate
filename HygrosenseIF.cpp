#include <unistd.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/time.h>
#include  <string.h>
#include "HygrosenseIF.h"
#include "GrowBoxDefines.h"


#define timerDelay 1000
#define dbTimerDelay 120000


enum eTimers {
	checkValuesTimer = 50,
	dbUpdateTimer,
	ventilationStartTimer,
	ventilationStopTimer
};



int CHygrosenseIF::hygroStopCond = 0;

double CHygrosenseIF::temperature;
double CHygrosenseIF::humidity;
DWORD CHygrosenseIF::measureCount;


//  PN 8. Nov 2005
//
//  standard way of method access synchronisation
//
//  let the constructor/destructor access the semaphore in the
//   frame of a method
//
//  do not remove the method local Mutex m variables, even they seem 
//  not explicitely be used.
//


CHygrosenseIF::CHygrosenseIF() 
{
	info_printf("constuctor CHygrosenseIF  \n");
	hygroStopCond = 0;
}


CHygrosenseIF::~CHygrosenseIF()
{
	info_printf("destructor CHygrosenseIF\n");
}


int CHygrosenseIF::start()
{
	/*
	 * pn 19. sept 12, leave this evaluation for later , and continue with default attributes right now.
	 * but finally priority of the serial thread should be somewhat higher than the application thread's prio
	 * and system preemptive threads should be used for this purpose.
	 * 
	pthread_attr_t thAttr;
	int scope;
	int ret;
	
	ret = pthread_attr_init(&thAttr);
	ret = pthread_attr_getscope(&thAttr,&scope);
	printf("pthread getScope returned %i, scopeval %i (proc/syst %i/%i ) \n",ret,scope,
			PTHREAD_SCOPE_PROCESS,PTHREAD_SCOPE_SYSTEM);
	*/		
	
	info_printf("\nstart CHygrosenseIF\n");
	commPort.Open_port();

	pthread_create( &hygroThread, NULL,&hygroThreadMethod, this);
	
	return 1;
}

void CHygrosenseIF::setStopCond()
{
	Mutex m (&mcMutex);
	hygroStopCond = 1;	 
}

void CHygrosenseIF::stop()
{
//	DWORD tmOut;
	info_printf("\nstop CHygrosenseIF\n");
	
	setStopCond();
 
	commPort.Close_port();

	/*
	tmOut = GBSerialReadTotalTimeoutConstant  \
			+ GBReadIntervalTimeout  \
			+ 2000;  //  max calculation time
	*/

	pthread_join(hygroThread,NULL);    // pn 22. sept 12,
										// timeout would be desirable, but not possible via join (timedjoin), seems not be supported 
										// in the library, according to pthread.h. Could be implemented by slowly polling for 
										// a thread-terminated-variable with max counter condition. Or with a call to 
										// pthread_cond_timedwait when waiting for a thread terminated condition
										// currently left this point open for later implementation
	
	info_printf("hygtoIF threadMethod stopped\n");
}

// the safest way to terminate an other thread
int CHygrosenseIF::isStopCondSet()
{
	Mutex m (&mcMutex);

	int res = hygroStopCond;
 
	return (res);   
}

void* CHygrosenseIF::hygroThreadMethod(void* parm)
{
	int step = 0;

	CHygrosenseIF* HSIF = (CHygrosenseIF*) parm;
	
    info_printf("\nHYGROTHREAD::hygro Thread Started\n");
    
    while (!HSIF->   isStopCondSet()) {
		++ step;
//		printf("HYGROTHREAD::hygro Thread step %i\n",step);

		if (! HSIF->getSensorValues()) {
			info_printf("\nHYGROTHREAD::hygro Thread error getting values");
		}
	}
	info_printf("\nHYGROTHREAD::hygro Thread Returning\n");
	
	return 0;
}


DWORD CHygrosenseIF::incMeasure(double hum, double temp)
{
	Mutex m (&mcMutex);
	DWORD res;

	res = (measureCount ++);
	temperature = temp;
	humidity = hum;
	deviceRunning = TRUE;
	if ((measureCount % 150) == 0) {
//		info_printf("CHygrosenseIF::incMeasure temp %f hum %f  count %i\n",temperature,humidity,measureCount);
	}
	return res;
}

void CHygrosenseIF::getMeasure(double& hum, double& temp, DWORD& cnt)
{
	Mutex m (&mcMutex);

	cnt = measureCount;
	temp = temperature;
	hum = humidity;
//	printf("CHygrosenseIF::getMeasure temp %f hum %f  count %i\n",temperature,humidity,measureCount);

}

BOOL CHygrosenseIF::getSensorValues()
{
	char buffer [300];
	DWORD amtRcv = 0;

	memset(&buffer, 0, sizeof(buffer));

	delay (200); // wait 0.2 sec for the case, if second to last Read_port started during
	                 // receiption of a message. In this case, let the last message (which will then
					//	let return the read-call after having recieved amtRecv charachters) terminate,
					// before next read. This is done to avoid that the next read will be partial once more.
					// (see also timeout and vmin behaviour of unix serial comms methods, which
					// lacks oridnary wait-for-message-timeout and inter-character-timeout
					// pn 15. sept 12
	
	commPort.Read_port(&buffer, sizeof(buffer), &amtRcv);
	
//	sleep(10);   // pn 19. sept 12 set temporarely to test threading without uart beeing used

	if (amtRcv == 68) {

		char* tempS;
		char* hydS;
		DWORD mCnt;

		tempS = strstr(buffer,"V01")+3;
		hydS = strstr(buffer,"V02")+3;
		*(hydS+4) = 0;
		*(tempS+4) = 0;

		long tempI = strtoul(tempS ,NULL,0x10);
		long hydI = strtoul (hydS, NULL, 0x10);

/*		long teI, hyI;
		int res;
		res = sscanf(tempS,"%X",&teI);
		res = sscanf(hydS,"%X",&hyI);
*/
		double temp = tempI / 100;
		double hyd = hydI / 200;

		mCnt = incMeasure(hyd,temp); // sets deviceRunning true
//		info_printf("Step %i temp V01: %s %f / hyd V02: %s %f\n",mCnt,tempS, temp,hydS, hyd);
	} else
	{
		setDeviceRunning(FALSE);
		info_printf("CHygro IF wrong amount of bytes: %i\n",(int)amtRcv);
	}
	return  TRUE;
}

BOOL CHygrosenseIF::isDeviceRunning()
{
	Mutex m (&mcMutex);
	return deviceRunning;
}

void CHygrosenseIF::setDeviceRunning(BOOL runOK)
{
	Mutex m (&mcMutex);
	deviceRunning = runOK;
}
