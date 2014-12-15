// GrowBox.cpp : Defines the class behaviors for the application.
//

#include "GrowBox.h"
#include "GrowBoxDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CGrowBoxApp
/*
BEGIN_MESSAGE_MAP(CGrowBoxApp, CWinApp)
	//{{AFX_MSG_MAP(CGrowBoxApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
// CGrowBoxApp construction

CGrowBoxApp::CGrowBoxApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGrowBoxApp object

//CGrowBoxApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGrowBoxApp initialization

BOOL CGrowBoxApp::runInstance()
{
	// PN 7. Nov 2005 copyied mutex code from an MSDN sample.
	// let the os cleanup the mutex after program termination.
	// It is a resource concurrency problem that
	// made this test necessary (Relais started wildly flickering).
	//
	// application and os were hanging, -> red button !
	//

/*
 * 	
	
	BOOL bFound = FALSE;
    hMutexOneInstance = 
    CreateMutex(NULL,TRUE,_T("PreventSecondGrowBoxInstance"));
    if(GetLastError() == ERROR_ALREADY_EXISTS)
        bFound = TRUE;
    if(hMutexOneInstance) 
        ReleaseMutex(hMutexOneInstance);
    if (bFound) {
		MessageBox(NULL,"you can only use one instance of GrowBox Application","error",MB_OK);
		return FALSE;
	}

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

*
 * 
 * - init application data
 * - evtl start timers
 * - wait for termination semaphore
 * 
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CGrowBoxDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
	*/
	return 0;
}



