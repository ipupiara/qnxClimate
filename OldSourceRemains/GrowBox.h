// GrowBox.h : main header file for the GROWBOX application
//

#if !defined(AFX_GROWBOX_H__F2FD9AA5_3A6F_11DA_BB67_00001B483E74__INCLUDED_)
#define AFX_GROWBOX_H__F2FD9AA5_3A6F_11DA_BB67_00001B483E74__INCLUDED_

/*
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
*/

#include "resource.h"		// main symbols
#include "GrowBoxDefines.h"

/////////////////////////////////////////////////////////////////////////////
// CGrowBoxApp:
// See GrowBox.cpp for the implementation of this class
//

class CGrowBoxApp        // : public CWinApp
{
public:
	CGrowBoxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrowBoxApp)
	public:
	virtual BOOL runInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGrowBoxApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
//private:
//	HANDLE hMutexOneInstance; // will be release by OS after Process termination
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROWBOX_H__F2FD9AA5_3A6F_11DA_BB67_00001B483E74__INCLUDED_)
