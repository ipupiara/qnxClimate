#ifndef HygrosesseIF_h
#define HygrosesseIF_h


#include <pthread.h>
#include "CSerial.h"



class CHygrosenseIF:  public MutexedClass{          // singleton object class
public:

	BOOL isDeviceRunning();

	CHygrosenseIF();
	virtual ~CHygrosenseIF();
	int start();
	void stop();
	void getMeasure(double& hum, double& temp, DWORD& cnt);
	int isStopCondSet();

private:
	BOOL deviceRunning;
	void setDeviceRunning(BOOL runOK);

	pthread_t hygroThread;  // Thread reading values from Sensor
	DWORD incMeasure(double hum, double temp);
	BOOL getSensorValues();
	void setStopCond();
	static int hygroStopCond;  // event variable to communicate to the hygrothread that it shall stop
								// used an int because pThread_cond_wait and pThread_cond_timedwait could  not be linked ???
								// and what libraries are actually linked together in this IDE   ?????????????
	static double temperature;
	static double humidity;
	static DWORD measureCount;
	CSerial commPort;
	
	static void * hygroThreadMethod(void * parm); 
};


#endif
