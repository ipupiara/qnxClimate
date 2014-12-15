//
// Module Name:	StateClass.cpp
//
// Description:	Test class for statechart engine.  This class exemplifies
//				any class that would actually contain and use the engine.
//
// Copyright (c) 1994-2005 Grant D. Schultz.	All rights reserved.
//


#include <iostream>

#include <signal.h>
#include <time.h>

#include <stdio.h>
#include <unistd.h>
//#include <syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sched.h>
#include <setjmp.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


#ifdef useStateCharts
#include "TStatechart.h"
#include "StateClass.h"
#endif

//#include "GrowBoxDlg.h"
#include "GrowBoxDefines.h"
#include "GrowBoxController.h"





CGrowBoxController::~CGrowBoxController(void)
{
	info_printf("CGrowBoxController::~CGrowBoxController()\n");
	delete relais;
	DB_IF.exitDBInterface() ;
}


CGrowBoxController::CGrowBoxController()
{
	info_printf("CGrowBoxController::CGrowBoxController()\n");
	if (CGrowBoxDefines::useUSBBoard())  {
		relais = new USBRelaisController();
	} else {
		relais = new GPIORelaisController();
	}
	

//	relais = new RelaisController();  // pn 5. jan 13, just for debugging

#ifdef useStateCharts	
	growBoxHumidityChart.setOwner(this);
	growBoxTemperatureChart.setOwner(this);
#endif
	DB_IF.initDBInterface();

}


void CGrowBoxController::getMeasure(double& hum, double& temp, DWORD& cnt)
{
#ifdef useHygrosenseIF	
	HygroIF.getMeasure(hum, temp, cnt);
#else
	hum = 99.9;
	temp =99.9;
	cnt = 99999;
#endif
}

void CGrowBoxController::relaisTestMethod()
{
	info_printf("CGrowBoxController::relaisTestMethod()\n");
	relais->testMethod();
}



void CGrowBoxController::OnVentilationStartTimer()
{
#ifdef useStateCharts		
	CGrowBoxEvent ev;
	ev.evType = eVentilationStartTimer;
	growBoxHumidityChart.processEvent(ev);
#endif	
}

void CGrowBoxController::OnVentilationStopTimer()
{
#ifdef useStateCharts		
	CGrowBoxEvent ev;
	ev.evType = eVentilationStopTimer;
	growBoxHumidityChart.processEvent(ev);
#endif	
}

void CGrowBoxController::OnCheckValuesTimer()
{
	double temp;
	double humid;
	DWORD cnt;
	char state [123];
	getMeasure(humid,temp,cnt);
//	printf("CGrowBoxController::OnCheckValuesTimer cnt %i\n", cnt);

	if (cnt > 0) {
#ifdef useStateCharts			
		CGrowBoxEvent ev;
		ev.evType = eValueAssignement;
		ev.humidity = humid;
		ev.temperature = temp;	
		growBoxHumidityChart.processEvent(ev);
		growBoxTemperatureChart.processEvent(ev);
#endif		

		float tf = (float) temp;
		float hf = (float) humid;
		memset(state,0,sizeof(state));
		strcat(state,"t: ");
		nCatHeaterStateString(state,40);
		strcat(state," h: ");
		nCatHumidifyerStateString(state,40);
#ifdef useHygrosenseIF		
		if (!HygroIF.isDeviceRunning()){
			strcat(state," | sensor problem");
		}
#endif
#ifdef useGrowBoxSoapServer		
		soapServer.publishValues(cnt,tf,hf,state);	
#endif		
	}
	
	relais->onSecondTimer();
	
}

void CGrowBoxController::onEntryIdleNotVentilating()
{

//	owner->onEntryIdleNotVentilating();
}

void CGrowBoxController::onExitIdleNotVentilating()
{
//	owner->onExitIdleNotVentilating();
}

void CGrowBoxController::onEntryIdleVentilating()
{

//	owner->onEntryIdleVentilating();
}

void CGrowBoxController::onExitIdleVentilating()
{
//	owner->onExitIdleVentilating();
}



BOOL CGrowBoxController::isRelaisSet( int pos)
{
	return relais->isRelaisSet(pos);
	return 0;
}


void CGrowBoxController::startHeating()
{
	relais->startHeating();
}

void CGrowBoxController::stopHeating()
{
	relais->stopHeating();
}

void CGrowBoxController::startHumidifying()
{
	relais->startHumidifying();
}

void CGrowBoxController::stopHumidifying()
{
	relais->stopHumidifying();
}

void CGrowBoxController::startVentilating()
{
	relais->startVentilating();
}

void CGrowBoxController::stopVentilating()
{
	relais->stopVentilating();
}


void CGrowBoxController::Reset()
{
#ifdef useStateCharts	
	CGrowBoxEvent ev;
	ev.evType = eReset;
	growBoxHumidityChart.processEvent(ev);
	growBoxTemperatureChart.processEvent(ev);
#endif	
}

void CGrowBoxController::stop()
{
	//  pn 17. sept 12 todo:
	//	KillTimer( checkValuesTimer);
	//	KillTimer( dbUpdateTimer);

	info_printf("CGrowBoxController::stop()\n");
#ifdef useTimer	
	psxTimer.KillTimer( checkValuesTimer);
	psxTimer.KillTimer( dbUpdateTimer);
	psxTimer.stop();
#endif	
#ifdef useHygrosenseIF	
	HygroIF.stop();
#endif
#ifdef useGrowBoxSoapServer	
	soapServer.stopServer();
#endif

}

void CGrowBoxController::start()
{
	info_printf("CGrowBoxController::start()\n");
#ifdef useStateCharts	
	growBoxHumidityChart.start();
	growBoxTemperatureChart.start();
#endif	
#ifdef useGrowBoxSoapServer	
	soapServer.startServer(this);
#endif	
#ifdef useHygrosenseIF	
	if (! HygroIF.start())  {
		info_printf("error on HygroIF start\n");
	}
#endif
#ifdef useTimer
	psxTimer.start(this);
	psxTimer.SetTimer( checkValuesTimer, timerDelay);
	psxTimer.SetTimer( dbUpdateTimer, dbTimerDelay);
#endif
}

/*
void CGrowBoxController::timerTest()
{
	psxTimer.testTimer();
}
*/

void CGrowBoxController::setOwner(CGrowBoxDlg* own)
{
//	owner = own;
}

void CGrowBoxController::startVentilatingStopTimer(double minutes)
{
	// Todo: test this convertion of double to int, maybe it works
	// pn, 9. oct 12, same on method below
#ifdef useTimer	
	psxTimer.SetTimer(ventilationStopTimer , (minutes * 60 ));
#endif
}

void CGrowBoxController::stopVentilatingStopTimer()
{
#ifdef useTimer	
		psxTimer.KillTimer(ventilationStopTimer);
#endif
}

void CGrowBoxController::startVentilatingStartTimer(double minutes)
{
	// Todo: pls. see remarks above
#ifdef useTimer	
	psxTimer.SetTimer( ventilationStartTimer, (minutes * 60 ));
#endif
}

void CGrowBoxController::stopVentilatingStartTimer()
{
#ifdef useTimer	
	psxTimer.KillTimer(ventilationStartTimer);
#endif
}

void CGrowBoxController::nCatHeaterStateString(char* dest,int enn)
{
#ifdef useStateCharts	
	growBoxTemperatureChart.nCatHeaterStateString(dest,enn);
#endif	
}

void CGrowBoxController::nCatHumidifyerStateString(char* dest,int enn)
{
#ifdef useStateCharts	
	growBoxHumidityChart.nCatHumidifyerStateString(dest, enn);
#endif	
}


void CGrowBoxController::startDrying()
{
	relais->startDrying();
}

void CGrowBoxController::stopDrying()
{
	relais->stopDrying();
}

void CGrowBoxController::startCooling()
{
	relais->startCooling();
}

void CGrowBoxController::stopCooling()
{
	relais->stopCooling();
}

BOOL CGrowBoxController::isHygrosensSensorRunning()
{
#ifdef useHygrosenseIF	
	return HygroIF.isDeviceRunning();
#else
	return 0;
#endif	
}

BOOL CGrowBoxController::isRelaisControllerRunning()
{
	return relais->isRelaisControllerRunning();
	return 0;
}

void CGrowBoxController::OnDBUpdateTimer()
{
//	printf("CGrowBoxController::OnDBUpdateTimer\n");
	// pn 22.oct 12, db interface currently not used
	double temp;
	double humid;
	DWORD cnt;
#ifdef useHygrosenseIF
	HygroIF.getMeasure(humid,temp,cnt);
#endif
	if (cnt > 0) {
		DB_IF.logValues(temp,humid);	
	}

}

bool CGrowBoxController::isDBInterfaceOn()
{
	return DB_IF.isInterfaceOn();
	return 0;
}

void CGrowBoxController::onVentilationButtonPressed()
{
#ifdef useStateCharts	
	CGrowBoxEvent ev;
	ev.evType = eVentilationButtonPressed;
	growBoxHumidityChart.processEvent(ev);
#endif	
}

void CGrowBoxController::onStopVentilationButtonPressed()
{
#ifdef useStateCharts		
	CGrowBoxEvent ev;
	ev.evType = eVentilationStopButtonPressed;	
	growBoxHumidityChart.processEvent(ev);
#endif	
}
