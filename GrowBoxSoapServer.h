// GrowBoxSoapServer.h: interface for the GrowBoxSoapServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GROWBOXSOAPSERVER_H__4E85D5CD_28F2_40F5_9736_80151B6D0042__INCLUDED_)
#define AFX_GROWBOXSOAPSERVER_H__4E85D5CD_28F2_40F5_9736_80151B6D0042__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GrowBoxDefines.h"

#define WorkstationIPAddresss  "192.168.1.106"

class CGrowBoxController;

class GrowBoxSoapServer : public MutexedClass 
{
public:
	void startServer(CGrowBoxController* ownr);
	void stopServer();
//	int setValues(DWORD& cnt, float& tmp, float& hum, char* state);
	GrowBoxSoapServer();
	virtual ~GrowBoxSoapServer();

	static GrowBoxSoapServer* GBSoapServer;
	int waitForApplicationStopCondSet();
	int isApplicationStopCondSet();
	void setApplicationStopCond();
	void onVentilationCommand();
	void onStopVentilationCommand();

private:

	pthread_t serverThread;  
//	static void * GrowBoxSoapServer::serverMethod(void* pParam);

	static void * serverMethod(void* pParam);

	void startServerThread();
	
	pthread_cond_t  stopCond;
	pthread_mutex_t     stopCondMutex;
	int stopCondSet;
	CGrowBoxController* owner;
public:
	void publishValues(DWORD cnt, float& tmp, float& hum, char* stat);
	char StateValue[128];
	DWORD   HygroCntValue;
	float	TemperatureValue;
	float   HumidityValue;
};

#endif // !defined(AFX_GROWBOXSOAPSERVER_H__4E85D5CD_28F2_40F5_9736_80151B6D0042__INCLUDED_)
