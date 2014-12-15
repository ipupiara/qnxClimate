#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>  /* UNIX standard function definitions */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "RelaisController.h"
//#include "USBDLL.h"


// set bit at pos to 1, all other bits to 0
//
PortType RelaisController::bitMaskOnAt(int pos )
{
	PortType v = 1;
	v = v << pos;
	return v;
}

// set the bit at pos to 0, all other to 1
//
PortType RelaisController::bitMaskOffAt(int pos)
{
	return (bitMaskOnAt(pos) ^ AllBitsSet );
}


RelaisController::~RelaisController()
{
	info_printf("desstructur RelaisController\n");
}


RelaisController::RelaisController()
{
//	TRACE0("\nconstructur RelaisController");
	setOffAllRelais();
}

BOOL RelaisController::isRelaisSet( int pos)
{
	BOOL res = 0;
	if (pos > -1) {
		PortType cmp = 0;
		PortType bits = getRelaisValue();
		cmp = bits & bitMaskOnAt(pos);
		res = (cmp != 0);
	}
	return res;
}


void RelaisController::startHeating()
{
	setOnRelaisPos(CGrowBoxDefines::GetHeatingRelais());
}

void RelaisController::stopHeating()
{
	setOffRelaisPos(CGrowBoxDefines::GetHeatingRelais());
}




void RelaisController::startHumidifying()
{
	setOnRelaisPos(CGrowBoxDefines::GetHumidifyingRelais());
}

void RelaisController::stopHumidifying()
{
	setOffRelaisPos(CGrowBoxDefines::GetHumidifyingRelais());
}

void RelaisController::startVentilating()
{
	setOnRelaisPos(CGrowBoxDefines::GetVentilatingRelais());
}

void RelaisController::stopVentilating()
{
	setOffRelaisPos(CGrowBoxDefines::GetVentilatingRelais());
}


void RelaisController::startCooling()
{
	setOnRelaisPos(CGrowBoxDefines::GetCoolingRelais());
}

void RelaisController::stopCooling()
{
	setOffRelaisPos(CGrowBoxDefines::GetCoolingRelais());
}


void RelaisController::startDrying()
{
	setOnRelaisPos(CGrowBoxDefines::GetDryingRelais());
}

void RelaisController::stopDrying()
{
	setOffRelaisPos(CGrowBoxDefines::GetDryingRelais());
}


void RelaisController::setOnRelaisPos(int pos)
{
	if (pos > -1) {
		PortType bits = getRelaisValue();
		bits = bits | bitMaskOnAt(pos) ;	
		setRelaisValue(bits);
	}
}

void RelaisController::setOffRelaisPos(int pos)
{
	if (pos > -1) {
		PortType bits = getRelaisValue();
		bits = bits & bitMaskOffAt(pos)   ;	
		setRelaisValue(bits);
	}
}

PortType RelaisController::allRelaisValue()
{
	PortType res = 0;
	res = ( (1 << CGrowBoxDefines::GetHeatingRelais()) | (1 << CGrowBoxDefines::GetHumidifyingRelais())
					| (1 << CGrowBoxDefines::GetVentilatingRelais()) | (1 << CGrowBoxDefines::GetCoolingRelais())
					| (1 << CGrowBoxDefines::GetDryingRelais()) );
	return res;
}

void RelaisController::setOffAllRelais()
{
	PortType bits = 0 ;
	setRelaisValue(bits);
}

void RelaisController::setRelais(BOOL on, int pos)
{
	if (on) {
		setOnRelaisPos(pos);
	} else
	{
		setOffRelaisPos(pos);
	}
}


PortType RelaisController::getRelaisValue()
{
	return 0;
}

void RelaisController::setRelaisValue(PortType bits)
{
}

void RelaisController::onSecondTimer()
{
}

BOOL RelaisController::isRelaisControllerRunning()
{
	return FALSE;
}


GPIORelaisController::~GPIORelaisController()
{
	info_printf("~GPIORelaisController\n");
	setOffAllRelais();
	closeMap();
}

GPIORelaisController::GPIORelaisController()
{
	info_printf("constructur GPIORelaisController\n");
	allRelaisBits = allRelaisValue();
	if (openMap()) {
		setOffAllRelais();
	}
}

#define PIO_PUDR   0x0060
#define PIO_PER    0x0000
#define PIO_OER    0x0010
#define PIO_MDDR   0x0054
#define PIO_IFDR   0x0024
#define PIO_IDR    0x0044

#define PIO_PDSR   0x003C
#define PIO_SODR   0x0030
#define PIO_CODR   0x0034
#define PIO_OWER   0x00A0
#define PIO_ODSR   0x0038
#define PIO_OWDR   0x00A4

void GPIORelaisController::setupPort()
{

	//  PN  11. Mar 13, for a very first test on at91sam9m10 setup will be hardcoded

	// set PIO_PUDR   pullup disable

	*((long *) (&gpioregs[PIO_PUDR])) = allRelaisBits;

	//	set PIO_PER 1 for all relais bits, enable PIO

	//  set PIO_OER as 1 for all relais , enable Output on PIO

	//  set PIO_MDDR  multi drive (open drain) disable

	//  set PIO_IFDR  input filter disable since we do not need input filtering

	//  set PIO_IDR   interrupt disable for allRelaisBis


}

PortType GPIORelaisController::getRelaisValue()
{
//  read PIO_PDSR   pin data status
//  and return PIO_PDSR & allRelaisBits  (only the values that represent relais

	PortType res;

	res = *((long *) &gpioregs[PIO_PDSR]);

	res &= allRelaisBits;


	return res;
}

void GPIORelaisController::setRelaisValue(PortType bits)
{
//write out values
// set PIO_SODR for  allRelaisBits set in bits
// set PIO_CODR  for allRelaisBits not set in bits
// or:
// set PIO_OWER  output write enable
// set PIO_ODSR  (output data status) to bits & allRelaisBits (-> synchronous write)

// ATTENTION: if multiple threads should be accessing the port concurrently, synchronization
// of their methods would be urgently needed (mutex or so..) !

	*((long *) (&gpioregs[PIO_OWER])) = allRelaisBits;
	*((long *) (&gpioregs[PIO_OWDR])) = ~allRelaisBits;
	*((long *) (&gpioregs[PIO_ODSR])) = (bits & allRelaisBits);
}


#define   gpioPortBase   0xFFFFF400
#define   gpioPortLen    0x0200

int GPIORelaisController::openMap()
{
	int res = 1;
	info_printf("GPIORelaisController::openMap\n");

	gpioregs = (char *) mmap_device_memory( 0, gpioPortLen, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, gpioPortBase );
	if ( gpioregs == MAP_FAILED ) {
		info_printf( "mmap_device_memory for physical address %X  and length %X failed\n", gpioPortBase, gpioPortLen );
		res = 0;
	}
		
/*	memfd = open("/dev/mem", O_RDWR|O_SYNC);
	if( memfd == NULL ) {
		info_printf("Error while opening the mem file.\n");
		gpioregs = MAP_FAILED;
		res = 0;
	}
	if (res  == 0 ) { 
		gpioregs = (char *)mmap(0, mapLen, PROT_READ|PROT_WRITE, MAP_SHARED, memfd, mapBase);
		if (gpioregs == MAP_FAILED)  {
			info_printf("Error while mmap.\n");
			res = 0;
		}
//		info_printf("gpioregs mapped\n");
	}
//	usleep(500000);

 */
	return res;
}

int GPIORelaisController::closeMap()
{
	int res = 0;
	info_printf("GPIORelaisController::closeMap()\n");

//	if (munmap_device_memory( gpioPortBase, gpioPortLen ) == -1 )  {  ???
	if (munmap_device_memory( gpioregs, gpioPortLen ) == -1 )  {
		info_printf("GPIORelaisController::closeMap:   munmap_device_memory failed \n");
	}

/*	if ( munmap(gpioregs, mapLen) < 0) {
		printf("munmap() error");
		res = 1;
	}
//	printf("gioregs unmapped\n");
	close(memfd);
	*/

	return res;
}


BOOL GPIORelaisController::isRelaisControllerRunning()
{
	return (gpioregs != MAP_FAILED);
}


void GPIORelaisController::testMethod()
{	int cnt1;
	info_printf("GPIORelaisController::testMethod()\n");
	
	for (cnt1 = 0; cnt1 < 100; ++ cnt1) {
//		printf("step %i\n",cnt1);
		setMultipleRelaisOn(5);
		sleep(4);
		setMultipleRelaisOn(0);
		sleep(1);
		
		setMultipleRelaisOn(5);
		sleep(1);
		setMultipleRelaisOn(0);
		sleep(1);		
		
		setMultipleRelaisOn(4);
		sleep(1);
		setMultipleRelaisOn(0);
		sleep(1);	

		setMultipleRelaisOn(3);
		sleep(1);
		setMultipleRelaisOn(0);
		sleep(1);		
		
		setMultipleRelaisOn(2);
		sleep(1);
		setMultipleRelaisOn(0);
		sleep(1);		
		
		setMultipleRelaisOn(1);
		sleep(1);
		setMultipleRelaisOn(0);
		sleep(1);		
		
		setMultipleRelaisOn(0);
		sleep(3);	
	}
	info_printf("END GPIORelaisController::testMethod()\n");
}

void GPIORelaisController::setMultipleRelaisOn(int amt)
{
	setOffAllRelais();
	if (amt > 0)  startVentilating();
	if (amt > 1)  startHumidifying();
	if (amt > 2)  startHeating();
	if (amt > 3)  startCooling();
	if (amt > 4)  startDrying();
}


void RelaisController::testMethod()
{
	info_printf("RelaisController::testMethod()\n");
}




USBRelaisController::~USBRelaisController()
{
	setOffAllRelais();
//	TRACE0("\ndestructur USBRelaisController\n");
}


USBRelaisController::USBRelaisController() 
{
	m_bits = 0;
	writeValue();
//	TRACE0("\nconstructur USBRelaisController\n");
}

PortType USBRelaisController::getRelaisValue()
{
	return m_bits;
}

void USBRelaisController::setRelaisValue(PortType bits)
{
	m_bits = bits;
	writeValue();
}

void USBRelaisController::onSecondTimer()
{
	writeValue();
}

void USBRelaisController::writeValue()
{
	/*
	int devErr;
	if ( (devErr = USBBoard.GetDeviceError()) != Err_No)  {
		TRACE1(" USBRelaisController::onSecondTimer GetDeviceError %X\n",devErr);
		USBBoard.closeDevice();
		USBBoard.openDevice();
	}
	if ( (devErr = USBBoard.GetDeviceError()) == Err_No)  {
		USBBoard.readValue(m_bits);
	}
	*/
}



BOOL USBRelaisController::isRelaisControllerRunning()
{
	return 0; // (USBBoard.GetDeviceError() == Err_No);
}

