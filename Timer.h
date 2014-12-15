#ifndef Timer_h
#define Timer_h

#include <sys/time.h>
#include <sys/types.h>
#include "stdtype.h"

#include "GrowBoxDefines.h"


#define maxTimers 4

#define timerDelay 1
#define dbTimerDelay 12

enum eTimers {
	checkValuesTimer = 0,
	dbUpdateTimer,
	ventilationStartTimer,
	ventilationStopTimer
};

class CGrowBoxController;

/*
 * 
 * pn 26. sept 12, posix timers could not be linked within all the many library files
 * found on the arm-unknown-linux-gnu lib directories. I tried many combination of different
 * .a files to link statically to the executable, I tried to find with nm command-line tool, ....
 * but eg. pthread_atfork could nowhere be found. 
 * 
 * For right now, I then decided to implement the timers with a non - posix timer class 
 * using simple pthread methods together with the "sleep(1)" method in a while-loop, since
 * the timers used by this application are rather trivial without any hard realtime requirements, they 
 * operate just on a "plus-minus one second" exactness.
 * 
 * When all the rest of the project is done, I will come back on this link problem, but probable it will
 * be best to compile and link all the libraries on my own, but right now I want to continue with the 
 * application as also would be done under real "time-to-market" enivironment.
 * 
 * pn 21. nov 12: pthread_atfork is not linkable, means not in the pthread library as it schould
 * --->>> incompatible pthread libraray, should be built again
 * 
 */

/*
class PosixTimer
{public:
	PosixTimer();
	virtual ~PosixTimer();
	int SetTimer(int timerID , int seconds);
	int KillTimer(int timerID);
protected:
	timer_t posixTimers [4];
	
	static void timer_signal_handler(int signo);

	int create_timer(int signo);
	int set_timer(int timerid, int seconds) ;
	void install_sighandler(int signo, void(*handler)(int)) ;
	

};
*/

class NonPosixTimer: public MutexedClass
{public:
	NonPosixTimer();
	virtual ~NonPosixTimer();
	int SetTimer(int timerID , int seconds);
	int KillTimer(int timerID);
	void start(CGrowBoxController* ownr);
	void stop();
//	void testTimer();
protected:
	pthread_t nptThread;  // Thread reading values from Sensor
	DWORD  timerCnt  [maxTimers];
	int stopCond;
	DWORD step;
	BOOL   isTimerTodo (int timerID);
	void   onTimer(int timerID);
	void setStopCond();
	static void * nonPosixTimerThreadMethod(void * parm); 
	
	BOOL isStopCondSet();
	CGrowBoxController* owner;
};

#endif
