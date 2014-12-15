

#if !defined(GrowBoxControllerHeader)
#define GrowBoxControllerHeader

#include <sys/time.h>
#include <sys/types.h>

//#include "stdtype.h"

#include "RelaisController.h"

#include "GrowBoxDefines.h"
#include "DBInterface.h"

#ifdef useTimer
#include "Timer.h"
#endif

#ifdef useStateCharts
#include "StateClass.h"
#endif

class CGrowBoxDlg;

#ifdef useGrowBoxSoapServer
#include "GrowBoxSoapServer.h"
#endif

#ifdef useHygrosenseIF
#include "HygrosenseIF.h"
#endif

#include "CoolingController.h"


// class to aggregate all the different helper objects
// needed to implement the growbox control
class CGrowBoxController
{
public:
	void onVentilationButtonPressed();
	void onStopVentilationButtonPressed();
	void onExitIdleNotVentilating();
	void onEntryIdleNotVentilating();
	void onExitIdleVentilating();
	void onEntryIdleVentilating();
	bool isDBInterfaceOn();
	void OnDBUpdateTimer();
	// creation, intialization and stop/start methods
	CGrowBoxController();
	~CGrowBoxController();
	void setOwner(CGrowBoxDlg* own);
	void stop();
	void start();
//	void timerTest();
	void relaisTestMethod();

	// interface for Dialog to get values
	void getMeasure(double& hum, double& temp, DWORD& cnt);
	BOOL isRelaisSet( int pos);
	void nCatHumidifyerStateString(char* dest,int enn);  // currently not used
    void nCatHeaterStateString(char* dest,int enn);      // currently not used
	BOOL isRelaisControllerRunning();
	BOOL isHygrosensSensorRunning();

	// interface for OS to notify timer events
	void OnVentilationStartTimer();
	void OnVentilationStopTimer();
	void OnCheckValuesTimer();
	void Reset(); // resets state charts, needs to be done, when behaviour values
					// should be changeable during application run

	//  interface for the statechart to request Timers and Relais Actions
	void stopVentilatingStopTimer();
	void startVentilatingStopTimer(double minutes);
	void stopVentilatingStartTimer();
	void startVentilatingStartTimer(double minutes);
	void stopVentilating();
	void startVentilating();
	void stopHumidifying();
	void startHumidifying();
	void stopHeating();
	void startHeating();
	void stopCooling();
	void startCooling();
	void stopDrying();
	void startDrying();

private:
	RelaisController* relais;
#ifdef useHygrosenseIF	
	CHygrosenseIF HygroIF;
#endif	
#ifdef useStateCharts	
	CHumidityStateClass growBoxHumidityChart;
	CTemperatureStateClass growBoxTemperatureChart;
#endif	
//	CGrowBoxDlg* owner;
#ifdef useGrowBoxSoapServer	
	GrowBoxSoapServer soapServer;
#endif	
	DBInterface DB_IF;
	CoolingController cooler;
#ifdef useTimer	
	NonPosixTimer psxTimer;
//	PosixTimer PSXTimer;
#endif	
};


#endif

