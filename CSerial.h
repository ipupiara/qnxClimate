#include "GrowBoxDefines.h"
#include <iostream>


//  PN 8. Nov 2005
//
//  code to access the serial port, copied from a MSDN sample
//
//

// pn 17. sept 12, commtimeouts copied from windows, linux struct to be found later

typedef struct _COMMTIMEOUTS {
    DWORD ReadIntervalTimeout;          /* Maximum time between read chars. */
    DWORD ReadTotalTimeoutMultiplier;   /* Multiplier of characters.        */
    DWORD ReadTotalTimeoutConstant;     /* Constant in milliseconds.        */
    DWORD WriteTotalTimeoutMultiplier;  /* Multiplier of characters.        */
    DWORD WriteTotalTimeoutConstant;    /* Constant in milliseconds.        */
} COMMTIMEOUTS,*LPCOMMTIMEOUTS;



class CSerial
{
public:
 CSerial();
 virtual ~CSerial();

 BOOL Open_port(void);
 BOOL Write_port(char* buffer, DWORD len,DWORD* dwBytesTransferred);
 BOOL Read_port( void* lpBuffer, DWORD len,DWORD* dwBytesTransferred);
 BOOL Close_port(void);
 
 BOOL isConnected();

private:

 int hComm;
// DCB      m_dcb;
 COMMTIMEOUTS m_CommTimeouts;
 BOOL     m_bPortReady;
 BOOL     bWriteRC;
 BOOL     bReadRC;
 DWORD iBytesWritten;
 DWORD iBytesRead;
 DWORD dwBytesRead;

 BOOL Configure_port(void);
} ;

