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
#include <unistd.h>
//#include <syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sched.h>
#include <signal.h>
#include <setjmp.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>




#include "TStatechart.h"
#include "StateClass.h"
//#include "GrowBoxDlg.h"
#include "GrowBoxDefines.h"
#include "GrowBoxController.h"



// This defines and names the states the class has.
enum eStates
{
	eStateGrowBoxKeepingHumidity,
	eStartState = eStateGrowBoxKeepingHumidity,
	eStateHumidifying,
	eStateIdle,
	eStateNonVentilating,
	eStateVentilating,
	eStateDrying,
	eNumberOfStates
};

pthread_mutex_t CTemperatureStateClass::tempEngineMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t CHumidityStateClass::humidEngineMutex = PTHREAD_MUTEX_INITIALIZER;


TStatechart<CHumidityStateClass>::xStateType xaStates[eNumberOfStates] = {
/* name						*/	{eStateGrowBoxKeepingHumidity,
/* parent					*/	-1,
/* default_substate			*/	eStateIdle,
/* event-checking func		*/	&CHumidityStateClass::evStateGrowBoxKeepingHumidity,
/* default state entry func	*/	NULL,  //CHumidityStateClass::defEntryStateGrowBoxKeepingHumidity,
/* entering state func		*/	&CHumidityStateClass::entryStateGrowBoxKeepingHumidity,
/* exiting state func		*/	&CHumidityStateClass::exitStateGrowBoxKeepingHumidity},

/* name						*/	{eStateHumidifying,
/* parent					*/	eStateGrowBoxKeepingHumidity,
/* default_substate			*/	-1,
/* event-checking func		*/	&CHumidityStateClass::evStateHumidifying,
/* default state entry func	*/	NULL,
/* entering state func		*/	&CHumidityStateClass::entryStateHumidifying,
/* exiting state func		*/	&CHumidityStateClass::exitStateHumidifying},

/* name						*/	{eStateIdle,
/* parent					*/	eStateGrowBoxKeepingHumidity,
/* default_substate			*/	eStateNonVentilating,
/* event-checking func		*/	&CHumidityStateClass::evStateIdle,
/* default state entry func	*/	NULL,
/* entering state func		*/	&CHumidityStateClass::entryStateIdle,
/* exiting state func		*/	&CHumidityStateClass::exitStateIdle},

/* name						*/	{eStateNonVentilating,
/* parent					*/	eStateIdle,
/* default_substate			*/	-1,
/* event-checking func		*/	&CHumidityStateClass::evStateNonVentilating,
/* default state entry func	*/	NULL,
/* entering state func		*/	&CHumidityStateClass::entryStateNonVentilating,
/* exiting state func		*/	&CHumidityStateClass::exitStateNonVentilating},

/* name						*/	{eStateVentilating,
/* parent					*/	eStateIdle,
/* default_substate			*/	-1,
/* event-checking func		*/	&CHumidityStateClass::evStateVentilating,
/* default state entry func	*/	NULL,
/* entering state func		*/	&CHumidityStateClass::entryStateVentilating,
/* exiting state func		*/	&CHumidityStateClass::exitStateVentilating},

/* name						*/	{eStateDrying,
/* parent					*/	eStateGrowBoxKeepingHumidity,
/* default_substate			*/	-1,
/* event-checking func		*/	&CHumidityStateClass::evStateDrying,
/* default state entry func	*/	NULL,
/* entering state func		*/	&CHumidityStateClass::entryStateDrying,
/* exiting state func		*/	&CHumidityStateClass::exitStateDrying}
};


/*
CHumidityStateClass::CHumidityStateClass(void)
{
	clearFlags();

	CREATE_ENGINE(CHumidityStateClass, engine, xaStates, eNumberOfStates, eStartState);

	// Test initial state entry and defaulting.
	assertInitial();
}
*/

CHumidityStateClass::~CHumidityStateClass(void)
{
	if (engine != NULL ) {
		DESTROY_ENGINE(CHumidityStateClass, engine);
	}
}


CHumidityStateClass::CHumidityStateClass()
{
	engine = NULL;
}

void CHumidityStateClass::setOwner(CGrowBoxController* own)
{
	owner = own;
}

void CHumidityStateClass::start()
{
	if (engine == NULL) {
		CREATE_ENGINE(CHumidityStateClass, engine, xaStates, eNumberOfStates, eStartState);
	} else
	{
		info_printf("error: engine already exists, CHumidityStateClass::start() ");
	}
}


bool CHumidityStateClass::processEvent(CGrowBoxEvent& ev)
{
	Mutex m(&humidEngineMutex);
	bool res;
	event = ev;
	res = (PROCESS_EVENT(CHumidityStateClass, engine));
	return res;
}


bool CHumidityStateClass::inState(const uint32 u32State)
{
	Mutex m(&humidEngineMutex);
	bool res;
	res = (IN_STATE(CHumidityStateClass, engine, u32State));
	return res;
}


uint32 CHumidityStateClass::evStateGrowBoxKeepingHumidity(void)
{
//	printf("check for event in State evStateGrowBoxKeepingHumidity\n");
	if (event.evType == eReset)
	{
		BEGIN_EVENT_HANDLER(CHumidityStateClass, engine, eStateGrowBoxKeepingHumidity );
			// No event action.
		END_EVENT_HANDLER(CHumidityStateClass, engine);
		
/*  left this as an original example for history states
 
		BEGIN_EVENT_HANDLER(CHumidityStateClass, engine, eStateGrowBoxKeepingHumidity | u32WithHistory);
			// No event action.
		END_EVENT_HANDLER(CHumidityStateClass, engine);
*/
		return (u32HandlingDone);
	}
	return (u32NoMatch);
}


uint32 CHumidityStateClass::evStateHumidifying(void)
{
//	printf("check for event in State evStateHumidifying\n");
	if ((event.evType == eValueAssignement) && (CGrowBoxDefines::GetHumidifyingUpperLimit() < event.humidity))
	{
		BEGIN_EVENT_HANDLER(CHumidityStateClass, engine, eStateIdle);
			// No event action.
		END_EVENT_HANDLER(CHumidityStateClass, engine);
		return (u32HandlingDone);
	}
	return (u32NoMatch);
}


uint32 CHumidityStateClass::evStateIdle(void)
{
//	printf("check for event in State evStateIdle\n");

	if (event.evType == eValueAssignement) 
	{	if (CGrowBoxDefines::GetHumidifyingLowerLimit() > event.humidity)
		{
			BEGIN_EVENT_HANDLER(CHumidityStateClass, engine, eStateHumidifying);
				// No event action.
			END_EVENT_HANDLER(CHumidityStateClass, engine);
			return (u32HandlingDone);
		}
		if (CGrowBoxDefines::GetDryingUpperLimit() < event.humidity)
		{
			BEGIN_EVENT_HANDLER(CHumidityStateClass, engine, eStateDrying);
				// No event action.
			END_EVENT_HANDLER(CHumidityStateClass, engine);
			return (u32HandlingDone);
		}
	}
	return (u32NoMatch);
}


uint32 CHumidityStateClass::evStateNonVentilating(void)
{
//	printf("check for event in State evStateNonVentilating\n");

	if ((event.evType == eVentilationStartTimer) || (event.evType ==  eVentilationButtonPressed))
	{
		BEGIN_EVENT_HANDLER(CHumidityStateClass, engine, eStateVentilating);
			// No event action.
		END_EVENT_HANDLER(CHumidityStateClass, engine);
		return (u32HandlingDone);
	
	}
	return (u32NoMatch);
}


uint32 CHumidityStateClass::evStateVentilating(void)
{
//	printf("check for event in State evStateVentilating\n");

	if ((event.evType == eVentilationStopTimer)  || (event.evType ==  eVentilationStopButtonPressed))
	{
		BEGIN_EVENT_HANDLER(CHumidityStateClass, engine, eStateNonVentilating);
			// No event action.
		END_EVENT_HANDLER(CHumidityStateClass, engine);
		return (u32HandlingDone);
	
	}
	return (u32NoMatch);
}

uint32 CHumidityStateClass::evStateDrying(void)
{
//	printf("check for event in State evStateDrying\n");
	if ((event.evType == eValueAssignement) && (CGrowBoxDefines::GetDryingLowerLimit() > event.humidity))
	{
		BEGIN_EVENT_HANDLER(CHumidityStateClass, engine, eStateIdle);
			// No event action.
		END_EVENT_HANDLER(CHumidityStateClass, engine);
		return (u32HandlingDone);
	}
	return (u32NoMatch);
}

/*
// State transition/handling methods
// left as an example of this defEntry method

void CHumidityStateClass::defEntryStateGrowBoxKeepingHumidity(void)
{

//	printf("CHumidityStateClass::defEntryStateGrowBoxKeepingHumidity\n");
}
*/



void CHumidityStateClass::entryStateGrowBoxKeepingHumidity(void)
{
	info_printf("CHumidityStateClass::entryStateGrowBoxKeepingHumidity\n");
}


void CHumidityStateClass::entryStateHumidifying(void)
{
	info_printf("CHumidityStateClass::entryStateHumidifying\n");
	owner->startHumidifying();
}


void CHumidityStateClass::entryStateIdle(void)
{
	info_printf("CHumidityStateClass::entryStateIdle\n");
}


void CHumidityStateClass::entryStateNonVentilating(void)
{
	info_printf("CHumidityStateClass::entryStateNonVentilating\n");
	owner->startVentilatingStartTimer(CGrowBoxDefines::GetIdleVentilationDelayMinutes());
	owner->onEntryIdleNotVentilating();
}


void CHumidityStateClass::entryStateVentilating(void)
{
	info_printf("CHumidityStateClass::entryStateVentilating\n");
	owner->startVentilating();
	owner->startVentilatingStopTimer(CGrowBoxDefines::GetIdleVentilationMinutes());
	owner->onEntryIdleVentilating();
}

void CHumidityStateClass::entryStateDrying(void)
{
	info_printf("CHumidityStateClass::entryStateDrying\n");
	owner->startDrying();
}

void CHumidityStateClass::exitStateGrowBoxKeepingHumidity(void)
{
	//  printf("CHumidityStateClass::exitStateGrowBoxKeepingHumidity\n");
}


void CHumidityStateClass::exitStateHumidifying(void)
{
	//  printf("CHumidityStateClass::exitStateHumidifying\n");
	owner->stopHumidifying();
}


void CHumidityStateClass::exitStateIdle(void)
{
	//  printf("CHumidityStateClass::exitStateIdle\n");
}


void CHumidityStateClass::exitStateNonVentilating(void)
{
	//  printf("CHumidityStateClass::exitStateNonVentilating\n");
	owner->stopVentilatingStartTimer();
	owner->onExitIdleNotVentilating();
}


void CHumidityStateClass::exitStateVentilating(void)
{
	//  printf("CHumidityStateClass::exitStateVentilating\n");
	owner->stopVentilating();
	owner->stopVentilatingStopTimer();
	owner->onExitIdleVentilating();
}


void CHumidityStateClass::exitStateDrying(void)
{
	//  printf("CHumidityStateClass::exitStateDrying\n");
	owner->stopDrying();
}




/***   Temperature  ********/

// This defines and names the states the class has.
enum eTemperatureStates
{
	eStateGrowBoxTemperature,
	eTemperatureStartState = eStateGrowBoxTemperature,
	eStateTemperatureIdle,
	eStateHeating,
	eStateCooling,
	eNumberOfTemperatureStates
};


TStatechart<CTemperatureStateClass>::xStateType xTemperatureStates[eNumberOfTemperatureStates] = {
/* name						*/	{eStateGrowBoxTemperature,
/* parent					*/	-1,
/* default_substate			*/	eStateTemperatureIdle,
/* event-checking func		*/	&CTemperatureStateClass::evStateGrowBoxTemperature,
/* default state entry func	*/	NULL,
/* entering state func		*/	&CTemperatureStateClass::entryStateGrowBoxTemperature,
/* exiting state func		*/	&CTemperatureStateClass::exitStateGrowBoxTemperature},

/* name						*/	{eStateTemperatureIdle,
/* parent					*/	eStateGrowBoxTemperature,
/* default_substate			*/	-1,
/* event-checking func		*/	&CTemperatureStateClass::evStateTemperatureIdle,
/* default state entry func	*/	NULL,
/* entering state func		*/	&CTemperatureStateClass::entryStateTemperatureIdle,
/* exiting state func		*/	&CTemperatureStateClass::exitStateTemperatureIdle},

/* name						*/	{eStateHeating,
/* parent					*/	eStateGrowBoxTemperature,
/* default_substate			*/	-1,
/* event-checking func		*/	&CTemperatureStateClass::evStateHeating,
/* default state entry func	*/	NULL,
/* entering state func		*/	&CTemperatureStateClass::entryStateHeating,
/* exiting state func		*/	&CTemperatureStateClass::exitStateHeating},

/* name						*/	{eStateCooling,
/* parent					*/	eStateGrowBoxTemperature,
/* default_substate			*/	-1,
/* event-checking func		*/	&CTemperatureStateClass::evStateCooling,
/* default state entry func	*/	NULL,
/* entering state func		*/	&CTemperatureStateClass::entryStateCooling,
/* exiting state func		*/	&CTemperatureStateClass::exitStateCooling},

};


/*
CTemperatureStateClass::CTemperatureStateClass(void)
{
	clearFlags();

	CREATE_ENGINE(CHumidityStateClass, engine, xaStates, eNumberOfStates, eStartState);

	// Test initial state entry and defaulting.
	assertInitial();
}
*/

CTemperatureStateClass::~CTemperatureStateClass(void)
{
	if (engine != NULL ) {
		DESTROY_ENGINE(CTemperatureStateClass, engine);
	}
}


CTemperatureStateClass::CTemperatureStateClass()
{
	engine = NULL;
}
	

void CTemperatureStateClass::setOwner(CGrowBoxController* own)
{
	owner = own;
}

void CTemperatureStateClass::start()
{
	if (engine == NULL ){
		CREATE_ENGINE(CTemperatureStateClass, engine, xTemperatureStates, eNumberOfTemperatureStates, eTemperatureStartState);
	} else
	{
		info_printf("error: engine already exists, CTemperatureStateClass::start() ");
	}

}


bool CTemperatureStateClass::processEvent(CGrowBoxEvent& ev)
{
	Mutex m(&tempEngineMutex);
	bool res;
	event = ev;
	res = (PROCESS_EVENT(CTemperatureStateClass, engine));
	return res;
}


bool CTemperatureStateClass::inState(const uint32 u32State)
{
	Mutex m(&tempEngineMutex);
	bool res;
	res = (IN_STATE(CTemperatureStateClass, engine, u32State));
	return res;
}


uint32 CTemperatureStateClass::evStateGrowBoxTemperature(void)
{
//	printf("check for event in State evStateGrowBoxKeepingHumidity\n");
	if (event.evType == eReset)
	{
		BEGIN_EVENT_HANDLER(CTemperatureStateClass, engine, eStateGrowBoxTemperature );
			// No event action.
		END_EVENT_HANDLER(CTemperatureStateClass, engine);
		
/*  left this as an original example for history states
 
		BEGIN_EVENT_HANDLER(CTemperatureStateClass, engine, eStateGrowBoxKeepingHumidity | u32WithHistory);
			// No event action.
		END_EVENT_HANDLER(CTemperatureStateClass, engine);
*/
		return (u32HandlingDone);
	}
	return (u32NoMatch);
}


uint32 CTemperatureStateClass::evStateTemperatureIdle(void)
{
//	printf("check for event in State evStateHumidifying\n");
	if ((event.evType == eValueAssignement) && (CGrowBoxDefines::GetHeatingLowerLimit() > event.temperature))
	{
		BEGIN_EVENT_HANDLER(CTemperatureStateClass, engine, eStateHeating);
			// No event action.
		END_EVENT_HANDLER(CTemperatureStateClass, engine);
		return (u32HandlingDone);
	}
	if ((event.evType == eValueAssignement) && (CGrowBoxDefines::GetCoolingUpperLimit() < event.temperature))
	{
		BEGIN_EVENT_HANDLER(CTemperatureStateClass, engine, eStateCooling);
			// No event action.
		END_EVENT_HANDLER(CTemperatureStateClass, engine);
		return (u32HandlingDone);
	}
	return (u32NoMatch);
}


uint32 CTemperatureStateClass::evStateHeating(void)
{
//	printf("check for event in State evStateIdle\n");

	if (event.evType == eValueAssignement) 
	{	if (CGrowBoxDefines::GetHeatingUpperLimit() < event.temperature)
		{
			BEGIN_EVENT_HANDLER(CTemperatureStateClass, engine, eStateTemperatureIdle);
				// No event action.
			END_EVENT_HANDLER(CTemperatureStateClass, engine);
			return (u32HandlingDone);
		}
	}
	return (u32NoMatch);
}

uint32 CTemperatureStateClass::evStateCooling(void)
{
//	printf("check for event in State evStateIdle\n");

	if (event.evType == eValueAssignement) 
	{	if (CGrowBoxDefines::GetCoolingLowerLimit() > event.temperature)
		{
			BEGIN_EVENT_HANDLER(CTemperatureStateClass, engine, eStateTemperatureIdle);
				// No event action.
			END_EVENT_HANDLER(CTemperatureStateClass, engine);
			return (u32HandlingDone);
		}
	}
	return (u32NoMatch);
}


void CTemperatureStateClass::entryStateGrowBoxTemperature(void)
{
	// printf("CHumidityStateClass::entryStateGrowTemperature\n");
}


void CTemperatureStateClass::entryStateTemperatureIdle(void)
{
	// printf("CHumidityStateClass::entryStateTemperatureIdle\n");
}


void CTemperatureStateClass::entryStateHeating(void)
{
	// printf("CHumidityStateClass::entryStateHeating\n");
	owner->startHeating();
}

void CTemperatureStateClass::entryStateCooling(void)
{
	// printf("CHumidityStateClass::entryStateCooling\n");
	owner->startCooling();
}


void CTemperatureStateClass::exitStateGrowBoxTemperature(void)
{
	// printf("CHumidityStateClass::exitStateGrowBoxTemperature\n");
}


void CTemperatureStateClass::exitStateTemperatureIdle(void)
{
	// printf("CHumidityStateClass::exitStateTemperatureIdle\n");
}


void CTemperatureStateClass::exitStateHeating(void)
{
	// printf("CHumidityStateClass::exitStateHeating\n");
	owner->stopHeating();
}

void CTemperatureStateClass::exitStateCooling(void)
{
	// printf("CHumidityStateClass::exitStateCooling\n");
	owner->stopCooling();
}


/**** end Temperature *****/


const CGrowBoxEvent& CGrowBoxEvent::operator =( const CGrowBoxEvent& src )
{
	evType = src.evType;
	temperature = src.temperature;
	humidity = src.humidity;

	return *this;
}

CGrowBoxEvent::CGrowBoxEvent()
{
}

CGrowBoxEvent::~CGrowBoxEvent()
{
}

// see comment for method CHumidityStateClass::nCatHumidifyerStateString
// pn 19 oct 12
void CTemperatureStateClass::nCatHeaterStateString(char* dest,int enn)
{
	if (inState(eStateTemperatureIdle)) {
		strncat(dest,"TemperatrueIdle",enn);
		return;
	}
	if (inState(eStateHeating)) {
		strncat(dest,"Heating",enn);
		return;
	}
	if (inState(eStateCooling)) {
		strncat(dest,"Cooling",enn);
		return;
	}
	strncat(dest,"temp application error",enn);
}


// pn 19. oct 12,
// this method does not provide transaction wide locking, because
// between any two inState method calls a processEvent might happen
// so that it is possible that no valid state is returned, but that
// "application error" is returned. Anyhow, this method serves just for UI
// display and one upon a time an invalid value does not hurt much.
void CHumidityStateClass::nCatHumidifyerStateString(char* dest,int enn)
{
	if (inState(eStateHumidifying)) {
		strncat(dest,"Humidifying ",enn);
		return;
	}
	if (inState(eStateNonVentilating)) {
		strncat(dest,"Idle / Not Ventilating ",enn);
		return;
	}
	if (inState(eStateVentilating)) {
		strncat(dest,"Idle / Ventilating",enn);
		return;
	}
	if (inState(eStateDrying)) {
		strncat(dest,"eStateDrying",enn);
		return;
	}
	strncat(dest,"humid application error", enn);
}
