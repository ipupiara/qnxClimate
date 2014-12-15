#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "GrowBoxDefines.h"
#include "minIni.h"


double  CGrowBoxDefines::IdleVentilationDelayMinutes = DefaultIdleVentilationDelayMinutes;    
double  CGrowBoxDefines::IdleVentilationMinutes = DefaultIdleVentilationMinutes;    

double  CGrowBoxDefines::HumidifyingLowerLimit = DefaultHumidifyingLowerLimit;   
double  CGrowBoxDefines::HumidifyingUpperLimit = DefaultHumidifyingUpperLimit ;  
double  CGrowBoxDefines::DryingUpperLimit = DefaultDryingUpperLimit ;	
double  CGrowBoxDefines::DryingLowerLimit = DefaultDryingLowerLimit;	


double  CGrowBoxDefines::HeatingLowerLimit = DefaultHeatingLowerLimit;	
double  CGrowBoxDefines::HeatingUpperLimit = DefaultHeatingUpperLimit;	
double  CGrowBoxDefines::CoolingLowerLimit = DefaultCoolingLowerLimit;	
double  CGrowBoxDefines::CoolingUpperLimit = DefaultCoolingUpperLimit;	

int CGrowBoxDefines::UseUSBBoard = DefaultRelaisBoard;

int CGrowBoxDefines::VentilatingRelais = DefaultVentilatingRelais;
int CGrowBoxDefines::HumidifyingRelais = DefaultHumidifyingRelais;
int CGrowBoxDefines::DryingRelais= DefaultDryingRelais;
int CGrowBoxDefines::HeatingRelais = DefaultHeatingRelais;
int CGrowBoxDefines::CoolingRelais = DefaultCoolingRelais;


BOOL CGrowBoxDefines::initialized = FALSE;

char CGrowBoxDefines::iniFilePath [256];


void  CGrowBoxDefines::checkInitialization()
{
	
	if (initialized) return;
	setIniFilePath();

	IdleVentilationDelayMinutes = GetIniValue("IdleVentilationDelayMinutes",IdleVentilationDelayMinutes);
	IdleVentilationMinutes = GetIniValue("IdleVentilationMinutes",IdleVentilationMinutes);

	HumidifyingLowerLimit = GetIniValue("HumidifyingLowerLimit",HumidifyingLowerLimit);
	HumidifyingUpperLimit = GetIniValue("HumidifyingUpperLimit",HumidifyingUpperLimit);
	DryingLowerLimit = GetIniValue("DryingLowerLimit",DryingLowerLimit);
	DryingUpperLimit = GetIniValue("DryingUpperLimit",DryingUpperLimit);

	HeatingLowerLimit = GetIniValue("HeatingLowerLimit",HeatingLowerLimit);
	HeatingUpperLimit = GetIniValue("HeatingUpperLimit",HeatingUpperLimit);
	CoolingLowerLimit = GetIniValue("CoolingLowerLimit",CoolingLowerLimit);
	CoolingUpperLimit = GetIniValue("CoolingUpperLimit",CoolingUpperLimit);

	UseUSBBoard = GetIniInt("UseUSBBoard",1);

	VentilatingRelais = GetIniInt("VentilatingRelais",DefaultVentilatingRelais);
	HumidifyingRelais = GetIniInt("HumidifyingRelais",DefaultHumidifyingRelais);
	DryingRelais = GetIniInt("DryingRelais", DefaultDryingRelais);
	HeatingRelais = GetIniInt("HeatingRelais",DefaultHeatingRelais);
	CoolingRelais = GetIniInt("CoolingRelais",DefaultCoolingRelais);
	
	initialized = TRUE;
	
}


double  CGrowBoxDefines::GetIdleVentilationDelayMinutes()
{
	checkInitialization();
	return IdleVentilationDelayMinutes;
}

double  CGrowBoxDefines::GetIdleVentilationMinutes()   
{
	checkInitialization();
	return IdleVentilationMinutes;
}

double  CGrowBoxDefines::GetHumidifyingLowerLimit()  
{
	checkInitialization();
	return HumidifyingLowerLimit;
}

double  CGrowBoxDefines::GetHumidifyingUpperLimit() 
{
	checkInitialization();
	return HumidifyingUpperLimit;
}

double  CGrowBoxDefines::GetDryingUpperLimit()
{
	checkInitialization();
	return DryingUpperLimit;
}
double  CGrowBoxDefines::GetDryingLowerLimit()	
{
	checkInitialization();
	return DryingLowerLimit;
}

double  CGrowBoxDefines::GetHeatingLowerLimit()
{
	checkInitialization();
	return HeatingLowerLimit;
}

double  CGrowBoxDefines::GetHeatingUpperLimit()
{
	checkInitialization();
	return HeatingUpperLimit;
}

double  CGrowBoxDefines::GetCoolingLowerLimit()
{
	checkInitialization();
	return CoolingLowerLimit;
}

double  CGrowBoxDefines::GetCoolingUpperLimit()
{
	checkInitialization();
	return CoolingUpperLimit;
}

BOOL CGrowBoxDefines::useUSBBoard()
{
	checkInitialization();
	return UseUSBBoard;
}

int CGrowBoxDefines::GetVentilatingRelais()
{	checkInitialization();
	return VentilatingRelais;
}

int CGrowBoxDefines::GetHumidifyingRelais()
{	checkInitialization();
	return HumidifyingRelais;
}

int CGrowBoxDefines::GetDryingRelais()
{	checkInitialization();
	return DryingRelais;
}

int CGrowBoxDefines::GetHeatingRelais()
{	checkInitialization();
	return HeatingRelais;
}

int CGrowBoxDefines::GetCoolingRelais()
{	checkInitialization();
	return CoolingRelais;
}


double CGrowBoxDefines::GetIniValue(char* id, double defaultVal)
{
	char buffer [50];
	memset(buffer,0,sizeof(buffer));
//	GetPrivateProfileString("Behaviour",id, "", buffer, sizeof(buffer), iniFilePath);
	ini_gets("Behaviour",id, "", buffer, sizeof(buffer), iniFilePath);
//	printf("\n 1. %s %s\n",id,buffer);
	if (strlen(buffer) == 0)  {
		sprintf(buffer,"%.2f",defaultVal);
//		WritePrivateProfileString("Behaviour",id, buffer, iniFilePath); 
		ini_puts("Behaviour",id, buffer, iniFilePath); 
//		printf("\ndefValString %s\n",buffer);
	}
	return atof(buffer);
//	return 0;
}

int CGrowBoxDefines::GetIniInt(char* id, int defaultVal)
{

	int res = ini_getl("Behaviour",id, 0xFF,  iniFilePath);
//	printf("\n 1. %s %i\n",id,res);
	if (res == 0xFF)  {
		char buffer [50];
		sprintf(buffer,"%i",defaultVal);
		res = defaultVal;
		ini_puts("Behaviour",id, buffer, iniFilePath); 
//		printf("\ndefValString %s\n",buffer);
	}
	return res;
//		return 0;
}


void CGrowBoxDefines::setIniFilePath()
{
	char cwd [256];
//	MessageBox(NULL,"must be specified","error",MB_OK);

	memset(&iniFilePath,0,sizeof(iniFilePath));
	if (getcwd(cwd,sizeof(cwd))) {
		strncpy(iniFilePath,cwd,strlen(cwd));
		strcat(iniFilePath,"/LinuxClimate.ini");
//		printf("\nini File path %s\n",iniFilePath);
	} else {
		info_printf("setIniFilePath getcwd returned null\n");
		strcat(iniFilePath,"/home/Growbox.ini");
	}
		
}

pthread_mutex_t MutexedClass::mcMutex = PTHREAD_MUTEX_INITIALIZER;

MutexedClass::MutexedClass()
{
	info_printf("MutexedClass::MutexedClass() \n");
}

MutexedClass::~MutexedClass()
{
}

MutexedClass::Mutex::Mutex(pthread_mutex_t* lpMutex)
{
	pMutex =  lpMutex;
	pthread_mutex_lock( pMutex );

}

MutexedClass::Mutex::~Mutex()
{
	pthread_mutex_unlock( pMutex );
}


pthread_mutex_t printMutex = PTHREAD_MUTEX_INITIALIZER;



void info_printf( char *msg, ...)
{
	va_list ap;

	pthread_mutex_lock( &printMutex );	
	
	va_start(ap, msg);
	

	vfprintf(stdout,msg,ap);
	
//	printf(emsg);
	
	

	va_end(ap);
	pthread_mutex_unlock( &printMutex );


}



int printMutex_lock()
{
	pthread_mutex_lock( &printMutex );
	return 0;
}

int printMutex_unlock()
{
	pthread_mutex_unlock( &printMutex );
	return 0;
}




/*  PN 2. mar. 13
 *
 *  Strange workaround - around a strange compiler (who looses references )
 *
 */

/*
void info_printf(char* msg,...)
{
	va_list ap;



	va_start(ap, msg);

//	info_printf(msg,ap);

	va_end(ap);
}

*/
