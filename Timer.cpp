#include <iostream>

#include <signal.h>
#include <time.h>

#include <stdio.h>
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
#include <string.h>

#include "GrowBoxController.h"
#include "Timer.h"



/*
 * Timer Linux implementation methods
 * 
 */

/*


PosixTimer::PosixTimer()
{
	memset(posixTimers,0,sizeof(posixTimers));
}

PosixTimer::~PosixTimer()
{
}

void PosixTimer::timer_signal_handler(int signo) {
    printf("receiving sig %d\n", signo);
}


int PosixTimer::create_timer(int signo) 
{
    int res = 0;
   
    struct sigevent se;
    se.sigev_notify=SIGEV_SIGNAL;
    se.sigev_signo = signo;
    if (timer_create(CLOCK_REALTIME, &se, &posixTimers[signo]) == -1) {
        printf("Failed to create timer\n");
        res = 0;;
    } else res = 1;
   
    return res;
}

void PosixTimer::install_sighandler(int signo, void(*handler)(int)) 
{
	
    sigset_t set;
    struct sigaction act;

   
    act.sa_handler = handler;
    act.sa_flags = SA_RESTART;
    sigaction(signo, &act, 0);

   
    sigemptyset(&set);
    sigaddset(&set, signo);
    sigprocmask(SIG_UNBLOCK, &set, NULL);

    return;
}

int PosixTimer::set_timer(int timerid, int seconds) 
{
	int res = 0;
    struct itimerspec timervals;
    timervals.it_value.tv_sec = seconds;
    timervals.it_value.tv_nsec = 0;
    timervals.it_interval.tv_sec = seconds;
    timervals.it_interval.tv_nsec = 0;

    if (timer_settime(posixTimers[timerid], 0, &timervals, NULL) == -1) {
        printf("Failed to start timer\n");
        res = 0;
    } else res = 1;
    
    return res;
}

int PosixTimer::SetTimer(int timerID , int seconds)
{
	
	create_timer(timerID);
	install_sighandler(timerID, timer_signal_handler);
	set_timer(timerID, seconds);
	
	return 1;
}

int PosixTimer::KillTimer(int timerID)
{
//	timer_delete(posixTimers[timerID]);
	return 1;
}


*/


NonPosixTimer::NonPosixTimer()
{
	info_printf("NonPosixTimer creator\n");
	stopCond = 0;
	step = 0;
	memset(timerCnt,0,sizeof(timerCnt));
}

NonPosixTimer::~NonPosixTimer()
{
}


int NonPosixTimer::SetTimer(int timerID , int seconds)
{
	Mutex m (&mcMutex);
	timerCnt[timerID] = seconds;   // no range check done
	return 1;
}

int NonPosixTimer::KillTimer(int timerID)
{
	Mutex m (&mcMutex);
	timerCnt[timerID] = 0;       
	return 1;
}

BOOL   NonPosixTimer::isTimerTodo (int timerID)
{
	Mutex m (&mcMutex);
	int res = 0;
	if (timerCnt[timerID] > 0) --timerCnt[timerID];
	if (timerCnt[timerID]== 0) {
		res = 1;
											    // restart some timers automatically.
		if (timerID == checkValuesTimer) {     // hardcoded, since the whole class is just a work around a problem in the TS-7350 library
			timerCnt[timerID] = timerDelay; // and will later be replace by posix timers anyhow, just after application once runs.
											 // as this would be done under ("Time To Market" :-) conditions
			
		}
		if (timerID == dbUpdateTimer) {    
					timerCnt[timerID] = dbTimerDelay;
				}
	}

	return (res);
}

void   NonPosixTimer::onTimer(int timerID)
{
	if (timerID == ventilationStartTimer)  {
		owner->OnVentilationStartTimer();
	}

	if (timerID == ventilationStopTimer)  {
		owner->OnVentilationStopTimer();
	}

	if (timerID == checkValuesTimer)
	{
		owner->OnCheckValuesTimer();
	}
	if (timerID == dbUpdateTimer)
	{
		owner->OnDBUpdateTimer();
	} 
}

/*
void   NonPosixTimer::onTimer(int timerID)  // used for testing
{
	if (timerID == ventilationStartTimer)  {
		printf("ventilationStartTimer\n");
	}

	if (timerID == ventilationStopTimer)  {
		printf("ventilationStopTimer\n");
	}

	if (timerID == checkValuesTimer)
	{
		printf("*VAL*\n");
	}
	if (timerID == dbUpdateTimer)
	{
		printf(".\n");
	} 
}
*/


void * NonPosixTimer::nonPosixTimerThreadMethod(void * parm)
{
	int cnt;

	NonPosixTimer* lpTimer = (NonPosixTimer*) parm;
	lpTimer->step = 0;
	
    info_printf("\nNonPosixTimer::nonPosixTimerThreadMethod Started\n");
    
    while (!lpTimer->isStopCondSet()) {
		++ lpTimer->step;
		for (cnt = 0; cnt < maxTimers; ++ cnt){
			if (lpTimer->isTimerTodo(cnt)){
				lpTimer->onTimer(cnt);
			}
		}
		sleep(1);
	}
	info_printf("\nNonPosixTimer::nonPosixTimerThreadMethod Returning\n");
	
	return 0;
}

void NonPosixTimer::setStopCond()
{  
	Mutex m (&mcMutex);
	stopCond = 1;
}

BOOL NonPosixTimer::isStopCondSet()
{
	Mutex m (&mcMutex);
	return (stopCond == 1);
}

void NonPosixTimer::start(CGrowBoxController* ownr)
{
	info_printf("\nstart NonPosixTimer\n");
	owner= ownr;
	pthread_create( &nptThread, NULL,&nonPosixTimerThreadMethod, this);	
}

void NonPosixTimer::stop()
{
	//	DWORD tmOut;
		info_printf("\nstop NonPosixTimer\n");
		
		setStopCond();

		/*
		tmOut = 
		*/

		pthread_join(nptThread,NULL);    // pn 22. sept 12,
											// timeout would be desirable, but not possible via join (timedjoin), seems not be supported 
											// in the library, according to pthread.h. Could be implemented by slowly polling for 
											// a thread-terminated-variable with max counter condition. Or with a call to 
											// pthread_cond_timedwait when waiting for a thread terminated condition
											// currently left this point open for later implementation
		
		info_printf("NonPosixTimer threadMethod stopped\n");
}

/*
void NonPosixTimer::testTimer()
{
	printf("TestTimer: No timer running at %i\n",step);
	sleep(20);
	printf("starting checkvaluesTimer at %i\n",step);
	SetTimer(checkValuesTimer,1);
	sleep(10);
	printf("starting ventilationStartTimer to 1 minute at %i\n",step);
	SetTimer(ventilationStartTimer,60);
	sleep(30);
	printf("starting db upd Timer at %i\n",step);
	SetTimer(dbUpdateTimer,12);
	sleep(10);
	printf("stopping check V Timer at %i\n",step);
	KillTimer(checkValuesTimer);
	sleep(13);
	printf("stopping db upd timer at %i\n",step);
	KillTimer(dbUpdateTimer);
	sleep(20);
	printf("starting Vent stop timer 30 secs at %i\n",step);
	SetTimer(ventilationStopTimer,30);
	sleep(10);
	printf("restarting dbUpdTimer and check V Timer at %i\n",step);
	SetTimer(dbUpdateTimer,12);
	SetTimer(checkValuesTimer,1);
	sleep(30);
	printf("stopping dbUpdTimer and checkV Timer at %i\n",step);
	KillTimer(dbUpdateTimer);
	KillTimer(checkValuesTimer);
	sleep(30);
	printf("test Finished at %i\n",step);
	printf("values of timerCnt: ");
	printf("[%i,%i,%i,%i]\n",timerCnt[1],timerCnt[2],timerCnt[3],timerCnt[4]);
}
*/

/*
 * 
 * END Timer  Linux implementation  methods
 * 
 */



