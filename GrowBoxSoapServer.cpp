// GrowBoxSoapServer.cpp: implementation of the GrowBoxSoapServer class.
//
//////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <string.h>



#include "GrowBoxSoapServer.h"
#include "GrowBoxController.h"

#include "soapH.h"
#include "states.nsmap"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

enum eActions {
	noneAct = 0,
	stopAct,
	ventilateAct,
	stopVentilateAct
};

GrowBoxSoapServer*  GrowBoxSoapServer::GBSoapServer = NULL;


GrowBoxSoapServer::GrowBoxSoapServer()
{
	int rc;
	TemperatureValue = 0.0f;
	HygroCntValue  = 0;
	HumidityValue = 0.0f;
	stopCondSet = 0;
	rc = pthread_cond_init(&stopCond, NULL);  // initializes to PTHREAD_COND_INITIALIZER (= all values 0) 
												// according to ibm - manual  pn, 23.oct 12
	rc = pthread_mutex_init(&stopCondMutex, NULL);  // sets mutex equal to PTHREAD_MUTEX_INITIALIZER;
	memset(StateValue,0,sizeof(StateValue));
}

int GrowBoxSoapServer::waitForApplicationStopCondSet()
{  
	int rc;
	rc = pthread_mutex_lock(&stopCondMutex);
	if (rc != 0)  {
		info_printf("stopCondMutex not locked rc %i\n",rc);
	}
	rc = pthread_cond_wait(&stopCond, &stopCondMutex);
	info_printf("after wait for stopCond, now stopCond is set\n");
	rc = pthread_mutex_unlock(&stopCondMutex);
	if (rc != 0)  {
		info_printf("stopCondMutex not unlocked rc %i\n",rc);
	}
	return rc;
}

int  GrowBoxSoapServer::isApplicationStopCondSet()
{
	int rc;
	int res;
	rc = pthread_mutex_lock(&stopCondMutex);
	if (rc != 0)  {
		info_printf("isStopCondSet not locked rc %i\n",rc);
	}
	res = stopCondSet;
	rc = pthread_mutex_unlock(&stopCondMutex);
	return res;
}

void GrowBoxSoapServer::setApplicationStopCond()
{
	int rc;
	rc = pthread_mutex_lock(&stopCondMutex);
	stopCondSet = 1;
	rc = pthread_cond_broadcast(&stopCond);
	rc = pthread_mutex_unlock(&stopCondMutex);
}

GrowBoxSoapServer::~GrowBoxSoapServer()
{
	pthread_cond_destroy(&stopCond);
	pthread_mutex_destroy(&stopCondMutex);
	
}

soap::soap()     //pn 29. sept defined destructor und constructor of soap to avoid linker problem
{				// but strange bug anyhow. let's hope that code will work at all ??????????
}

soap::~soap()
{
}


void * GrowBoxSoapServer::serverMethod(void* pParam)
{
	int res;
	info_printf("GrowBoxSoapServer::serverMethod start\n");

  soap soapStru; 

   int ms, ss; // master and slave sockets 

   while (!GBSoapServer->isApplicationStopCondSet()) {
	   soap_init(&soapStru);
	//   ms = soap_bind(&soapStru, "127.0.0.1", 18083, 100);
	   ms = soap_bind(&soapStru, WorkstationIPAddresss, 18083, 100);
	   if (ms < 0) {
			info_printf("Soap bind error, retry .... \n");
		  soap_print_fault(&soapStru, stderr);
		  sleep(10);
	   }
	   else
	   {
		  info_printf("SOAP Socket connection successful: master socket = %d\n", ms);
		  soapStru.accept_timeout = 5;  // seconds
		  while (!GBSoapServer->isApplicationStopCondSet()) {

	//    	  printf("waiting for soap call\n");
			  ss= -1;
			 while ((ss<0) && (!GBSoapServer->isApplicationStopCondSet())) {
				 ss = soap_accept(&soapStru);
				 if (ss < 0)
				 {
					// printf("timeout soap_accept %i\n",ss);
				 }
			 }
	//        printf("%d: accepted connection from IP=%d.%d.%d.%d socket=%d\n", i,
	//            (soapStru.ip >> 24)&0xFF, (soapStru.ip >> 16)&0xFF, (soapStru.ip >> 8)&0xFF, soapStru.ip&0xFF, s);

			 if (!GBSoapServer->isApplicationStopCondSet()) {
				 if ((res= soap_serve(&soapStru)) != SOAP_OK)  {
					soap_print_fault(&soapStru, stderr);
					info_printf("soap serve error in soap serve method res %i \n ",res);
				 }
		//         printf( "soap request served res %i\n",res);
			 }
			 soap_destroy(&soapStru);
			 soap_end(&soapStru);
		  }
	   }
	   soap_done(&soapStru);
   }
   
  // pn 23. oct 12, during testing it obviousely bee seen, that
   // soap-destroy-end-done sequence does not give up the socket bindings
   // it needs to wait approx. two minutes before applicatin can be restarted without error
   // todo: check later why and what can be done

	info_printf("SOAP ServerTHREAD::server Thread Returning\n");
	return 0;
}



void GrowBoxSoapServer::startServerThread()
{
	pthread_attr_t        attr;
	size_t stacksize, newstacksize;
	int rc;
	info_printf("\nstart GrowBoxSoapServer server\n");
	
	if( pthread_attr_init(&attr) != 0) info_printf("GrowBoxSoapServer::startServerThread attr init problem\n");
	
	if (pthread_attr_getstacksize(&attr,&stacksize) != 0) info_printf("GrowBoxSoapServer::startServerThread get stack size  problem\n");
	newstacksize =  (stacksize/ 4) * 3;
	info_printf("GrowBoxSoapServer::startServerThread default stack size: %i *** currently NOT try set to %i\n", stacksize, newstacksize);
/*	if ((rc = pthread_attr_setstacksize(&attr, newstacksize)) != 0) {
		info_printf("GrowBoxSoapServer::startServerThread set stack size  problem %i\n",rc);
	}
//	pn 5. dec 12: extending the stack size was not possible when trying to double the space
//       it seems that 	by default system max value is used.
*/	
	pthread_create( &serverThread, &attr,&serverMethod, this);
	
	if( pthread_attr_destroy(&attr) != 0) info_printf("GrowBoxSoapServer::startServerThread attr destroy problem\n");
}



/*
int GrowBoxSoapServer::setValues(DWORD &cnt, float &tmp, float &hum, char* state)
{
	Mutex m (&mcMutex);

	HygroCntValue = cnt;
	TemperatureValue = tmp;
	HumidityValue = hum;
	strncpy(StateValue,state,sizeof(StateValue));
	return 0;
}
*/
void GrowBoxSoapServer::startServer(CGrowBoxController* ownr)
{
	owner = ownr;
	GrowBoxSoapServer::GBSoapServer = this;
    startServerThread();
}
void GrowBoxSoapServer::stopServer()
{
	// wait until the server thread has stopped, while the 
	// stop signal was sent before
	info_printf("GrowBoxSoapServer::~GrowBoxSoapServer waiting for serverThread return\n");
	pthread_join(serverThread,NULL); 
	info_printf("end waiting for soap serverThread\n");
}

void GrowBoxSoapServer::onVentilationCommand()
{
	owner->onVentilationButtonPressed();
}

void GrowBoxSoapServer::onStopVentilationCommand()
{
	owner->onStopVentilationButtonPressed();
}


#define BuffSize 512
char BufferForServerThread [BuffSize];

SOAP_FMAC5 int SOAP_FMAC6 ns__getGrowBoxInfo(struct soap*, GrowBoxInfo *Result)
{
	GrowBoxSoapServer::Mutex m(&GrowBoxSoapServer::mcMutex);

	if (Result->HygroCnt == 1)  {
		//  send VentilateRequiredEvent to statechart...
	}
	if (Result->HygroCnt == 2)  {
		//  send ApplicationStop ...
	}
	
	Result->HygroCnt=GrowBoxSoapServer::GBSoapServer->HygroCntValue;
	Result->Temperature = GrowBoxSoapServer::GBSoapServer->TemperatureValue;
	Result->Humidity= GrowBoxSoapServer::GBSoapServer->HumidityValue;
	
	memset(BufferForServerThread,0,sizeof(BufferForServerThread));
	strncpy(BufferForServerThread,GrowBoxSoapServer::GBSoapServer->StateValue, BuffSize -1);

	Result->State = BufferForServerThread;
//	printf("ns__getGrowBoxInfo temp %f hum %f  state %s\n",Result->Humidity,Result->Temperature, Result->State);
   return SOAP_OK; 
}


SOAP_FMAC5 int SOAP_FMAC6 ns__performAction(struct soap*, long actionCode, long &return_Code)
{
//	printf("action_Code received %i\n",actionCode);
	if (actionCode == stopAct) {
		info_printf("received stopAction command\n");
		GrowBoxSoapServer::GBSoapServer->setApplicationStopCond();
	}
	if (actionCode == ventilateAct){
		info_printf("received ventilateActionCommand\n");
		GrowBoxSoapServer::GBSoapServer->onVentilationCommand();
	}
	if (actionCode == stopVentilateAct) {
		info_printf("received stopVentilateActionCommand\n");
		GrowBoxSoapServer::GBSoapServer->onStopVentilationCommand();
	}
	return_Code = 1;
	return SOAP_OK; 
}


void GrowBoxSoapServer::publishValues(DWORD cnt, float &tmp, float &hum, char* stat)
{
	Mutex m (&mcMutex);

	HumidityValue = hum;
	TemperatureValue  = tmp;
	HygroCntValue = cnt;
	strncpy(StateValue,stat,sizeof(StateValue));
//	printf("GrowBoxSoapServer::publishValues  temp %f hum %f  state %s\n",HumidityValue,TemperatureValue, StateValue);
}
