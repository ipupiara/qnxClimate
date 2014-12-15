#ifndef RelaisController_h
#define RelaisController_h

#include "GrowBoxDefines.h"
//#include "PrintPort32.h"
//#include "USBDLL.H"


// PN 7. Nov 2005
//
// RelaisController implements a baseclass for the USB and Parallel Relais Controller
//
//
// The Parallel controller keeps its relais states at the Parallel Port. Data is written 
// to the Port, whenever they change and read from the port, whenever needed. It does not
// use the timer.
//
// The USB Port keeps its state in a variable because the relais state can not be queried
// from the device.
// It writes out the variable, whenever
// the value changes and on each timerEvent (each second), because of the watchdog
// mechanism on the device
//
//
//




#ifdef port32Bit

typedef long PortType;
#define AllBitsSet   0xFFFFFFFF

#else
typedef  BYTE  PortType;
#define AllBitsSet  0xFF
#endif


class RelaisController
{
public:

	// methods for UI to get relais states
	BOOL isRelaisSet( int pos);
	virtual BOOL isRelaisControllerRunning();

	// action methods used by the statecharts
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

	// methods for os to communicate timer event each second
	virtual void onSecondTimer();
	virtual void testMethod();

public:

	RelaisController();	// standard constructor
	virtual ~RelaisController();

protected:
	void setOffAllRelais();
	PortType allRelaisValue();
	
private:
	void setRelais(BOOL on, int pos);
	void setOffRelaisPos(int pos);
	void setOnRelaisPos(int pos);

	PortType bitMaskOnAt(int pos );
	PortType bitMaskOffAt(int pos);

private:
	virtual PortType getRelaisValue();
	virtual void setRelaisValue(PortType bits);
};


//#warning: tobe changed into an gpio class

#define mapLen 0x1000   // 4096   one memory page
//#define mapBase 0x80840000		// GPIO
//#define DDRregOfs 0x10		//PADDR
//#define DRregOfs  0x00		//PADR

//#define DDRregOfs 0x14		//PBDDR    // DIO ???
//#define DRregOfs  0x04		//PBDR

#define mapBase    0x600ff000      // DIO
#define DRregOfs  0x84				// DOut0  - DOut5
#define DDRregOfs 0xFFFF			// no DDR register


class GPIORelaisController:    public RelaisController
{
public:
	GPIORelaisController();	// standard constructor
	virtual ~GPIORelaisController();

	virtual BOOL isRelaisControllerRunning();
	virtual void testMethod();
private:
	PortType allRelaisBits;   // cache this often used value (set in constructor), doesnt change during runtime
//	int memfd;
	char *gpioregs;
	virtual PortType getRelaisValue();
	virtual void setRelaisValue(PortType bits);
	void setMultipleRelaisOn(int amt);
	void setupPort();
#ifndef oldMMap
	int openMap();
	int closeMap();
#endif	
};


class USBRelaisController:    public RelaisController
{

public:
	USBRelaisController();	// standard constructor
	virtual ~USBRelaisController();

	virtual void onSecondTimer();

	virtual BOOL isRelaisControllerRunning();
private:
	PortType m_bits;
	virtual PortType getRelaisValue();
	virtual void setRelaisValue(PortType bits);
	void writeValue();
//	USBBoardIF USBBoard;
};

#endif

