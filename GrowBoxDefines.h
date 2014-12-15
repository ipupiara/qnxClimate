#ifndef GrowBoxDefinesHeader
#define GrowBoxDefinesHeader

#include <pthread.h>

typedef int BOOL;
typedef char BYTE;
typedef long int DWORD;
typedef void *HANDLE;
#define TRUE 1
#define FALSE 0

//#define useGrowBoxSoapServer    // commenting it out is used only for debugging purpose
//#define useTimer               // for debugging purpose
//#define useHygrosenseIF
//#define useStateCharts

// values defining behaviour of statechart

#define DefaultIdleVentilationDelayMinutes     30
#define DefaultIdleVentilationMinutes     2

#define DefaultHumidifyingLowerLimit   90.0    
#define DefaultHumidifyingUpperLimit   92.0 
#define DefaultDryingUpperLimit	94.0
#define DefaultDryingLowerLimit	93.0


#define DefaultHeatingLowerLimit	22.0
#define DefaultHeatingUpperLimit	24.0

#define DefaultCoolingLowerLimit	27.0
#define DefaultCoolingUpperLimit	28.0

// values in rH, Centigrade





/* SERIAL INTERFACE  */

// change these Values, if period of incoming messages on serial 
// input device should change

#define GBSerialReadTotalTimeoutConstant  8000  
// must be bigger maximum possible delay between incoming messages

 
#define GBReadIntervalTimeout  500
// must be bigger than the maximum possible inter character delay
// 500 ms should be enough, need probable never a change

// for configuring Baud, parity and so, please refer to CSerial::Configure_port


// all times in ms  !!!



// Paralle Port setting

//#define lptPortNumber 0x0378

#define lptPortNumber 0x03BC

//com2 had been intentionally not tested   ;-)


// Relais Numbers (0 based)

#define DefaultRelaisBoard    0     // 1 = usb,  0 = gpio

//#define DefaultVentilatingRelais 0
//#define DefaultHumidifyingRelais 1
//#define DefaultDryingRelais      2
//#define DefaultHeatingRelais	  3
//#define DefaultCoolingRelais     4


#define DefaultVentilatingRelais 11
#define DefaultHumidifyingRelais 9
#define DefaultDryingRelais      27
#define DefaultHeatingRelais	  25
#define DefaultCoolingRelais     23


class CGrowBoxDefines
{
public:

	static double  GetIdleVentilationDelayMinutes();    
	static double  GetIdleVentilationMinutes();    

	static double  GetHumidifyingLowerLimit();   
	static double  GetHumidifyingUpperLimit();  
	static double  GetDryingUpperLimit();	
	static double  GetDryingLowerLimit();	


	static double  GetHeatingLowerLimit();	
	static double  GetHeatingUpperLimit();
	static double  GetCoolingLowerLimit();	
	static double  GetCoolingUpperLimit();


	static BOOL useUSBBoard();

	static int GetVentilatingRelais();
	static int GetHumidifyingRelais();
	static int GetDryingRelais();
	static int GetHeatingRelais();
	static int GetCoolingRelais();
	
	

private:
	static void checkInitialization();
	static void setIniFilePath();
	static int GetIniInt(char* id, int defaultVal);
	static double GetIniValue(char* id,double defaultVal);

	static double  IdleVentilationDelayMinutes;    
	static double  IdleVentilationMinutes;    

	static double  HumidifyingLowerLimit;   
	static double  HumidifyingUpperLimit;  
	static double  DryingUpperLimit;	
	static double  DryingLowerLimit;	


	static double  HeatingLowerLimit;	
	static double  HeatingUpperLimit;
	static double  CoolingLowerLimit;	
	static double  CoolingUpperLimit;

	static int UseUSBBoard;

	static int VentilatingRelais;
	static int HumidifyingRelais;
	static int DryingRelais;
	static int HeatingRelais;
	static int CoolingRelais;

	static BOOL initialized;
	
	static char iniFilePath [256];

};

/*
 * 
 * The MutexedClass should only be used for short and simple shared variable
 * access, not for methods calling complex, deeply stacked methods, because the single mutex that all
 * these classes access, causes potential deadlock risks if called on top of
 * deep stacks.. `!
 * 
 * if a class needs an own mutex because deep stacks will get called,
 * an additional mutex has to be created on this class for usage by the
 * Mutex(pthread_mutex_t* lpMutex) creator, see also for example 
 * CHumidityStateClass and CTemperatureStateClass and their methods
 * inState(..) and processEvent(..)
 */
class MutexedClass  {
public:
	MutexedClass();
	~MutexedClass();
	
	static pthread_mutex_t mcMutex;	
	class Mutex{
	public:
		Mutex(pthread_mutex_t* lpMutex);
		~Mutex();
		pthread_mutex_t* pMutex;
	};	
	
};

int printMutex_lock();
int printMutex_unlock();

void info_printf(char* msg,...);

#endif

