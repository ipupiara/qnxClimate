//
// Module Name:	StateClass.hpp
//
// Description:	class for statechart engine.  This class represents
//				any class that would actually contain and use the engine.
//


#if !defined(CCtateClassHeader)
#define CCtateClassHeader

#include <sys/time.h>
#include <sys/types.h>

#include "stdtype.h"

//#include "RelaisController.h"
#include "HygrosenseIF.h"
#include "GrowBoxDefines.h"
//#include "DBInterface.h"
#include "GrowBoxDefines.h"
#include "Timer.h"

//class CGrowBoxDlg;
class CGrowBoxController;

#include "GrowBoxSoapServer.h"
//#include "CoolingController.h"



enum eEventTypes
{
	eReset,
	eValueAssignement,
	eVentilationStartTimer,
	eVentilationStopTimer,
	eVentilationButtonPressed,
	eVentilationStopButtonPressed
};


// class to held event data for the statechart
class CGrowBoxEvent {
public:
	CGrowBoxEvent();
	virtual ~CGrowBoxEvent();
	int evType;
	double temperature;
	double humidity;
	
	const CGrowBoxEvent& operator=(const CGrowBoxEvent& src);
};

// statechart implementation, see RationalRoseDescription.pdf
// and codeproject.com/samples/statechart.asp
class CHumidityStateClass:  public MutexedClass
{
	public:
		void nCatHumidifyerStateString(char* dest,int enn);
		CHumidityStateClass();
//		CStateClass();
		~CHumidityStateClass();

		void setOwner(CGrowBoxController* own);
		void start();

		bool	processEvent(CGrowBoxEvent& ev);


		// State transition/handling methods
//		void	defEntryStateGrowBoxKeepingHumidity();

		void	entryStateGrowBoxKeepingHumidity();
		void	entryStateHumidifying();
		void	entryStateIdle();
		void	entryStateNonVentilating();
		void	entryStateVentilating();
		void	entryStateDrying();

		void	exitStateGrowBoxKeepingHumidity();
		void	exitStateHumidifying();
		void	exitStateIdle();
		void	exitStateNonVentilating();
		void	exitStateVentilating();
		void	exitStateDrying();

		uint32  evStateGrowBoxKeepingHumidity();
		uint32  evStateHumidifying();
		uint32  evStateIdle();
		uint32  evStateNonVentilating();
		uint32  evStateVentilating();
		uint32  evStateDrying();


	private:
		static  pthread_mutex_t humidEngineMutex;
		bool	inState(const uint32 u32State);
		void	*engine;
		CGrowBoxEvent event;
		CGrowBoxController* owner;


};




// statechart implementation for temperature Control
// 
class CTemperatureStateClass:  public MutexedClass
{
	public:
		void nCatHeaterStateString(char* dest,int enn);
		CTemperatureStateClass();
//		CStateClass();
		~CTemperatureStateClass();

		void setOwner(CGrowBoxController* own);
		void start();

		bool	processEvent(CGrowBoxEvent& ev);

		// State transition/handling methods

		void	entryStateGrowBoxTemperature();
		void	entryStateHeating();
		void    entryStateCooling();
		void	entryStateTemperatureIdle();

		void	exitStateGrowBoxTemperature();
		void	exitStateHeating();
		void    exitStateCooling();
		void	exitStateTemperatureIdle();

		uint32  evStateGrowBoxTemperature();
		uint32  evStateHeating();
		uint32  evStateCooling();
		uint32  evStateTemperatureIdle();

	private:
		static  pthread_mutex_t tempEngineMutex;	  
		bool	inState(const uint32 u32State);
		void	*engine;
		CGrowBoxEvent event;
		CGrowBoxController* owner;
};



#endif
