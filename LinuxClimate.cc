
//============================================================================
// Name        : LinuxClimate.cpp
// Author      : Peter's project
// Version     :
// Copyright   : Peter's project
// Description : Hello World in C++, Ansi-style
//============================================================================

// further Todo:
// - regularely check relais-state while in a state
//   and correct if needed

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include "GrowBoxDefines.h"
#include "GrowBoxController.h"

//using namespace std;

CGrowBoxController growBoxController;

int main() {
	int i1;
	printf("LinuxClimate before using info_print\n");

	info_printf("Growbox Controller Climux starting up...\n");
//	growBoxController.start();
	info_printf("Climux started\n");
//	growBoxController.timerTest();
	growBoxController.relaisTestMethod();
#ifdef useGrowBoxSoapServer
	GrowBoxSoapServer::GBSoapServer->waitForApplicationStopCondSet();
#else
	for (i1=0; i1 < 3; ++ i1) {
//		info_printf("debugging mode: SoapServer not used %i\n",i1);
//		sleep(30);
	}
#endif
	info_printf("Climux stopping..... \n");
//	growBoxController.stop();
	info_printf("Climux stopped\n");

	return 0;
}
