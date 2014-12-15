// ClimatUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClimatUI.h"
#include "ClimatUIDlg.h"

#include "soapH.h" // include all interfaces (library and generated)
#include "states.nsmap" // import the generated namespace mapping table



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define timerDelay 3000
#define dbTimerDelay 120000


enum eTimers {
	checkValuesTimer = 50,
	dbUpdateTimer,
	ventilationStartTimer,
	ventilationStopTimer
};

enum eActions {
	noneAct = 0,
	stopAct,
	ventilateAct,
	stopVentilateAct
};

// CClimatUIDlg dialog





struct soap soap;

CClimatUIDlg::CClimatUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClimatUIDlg::IDD, pParent)
	, temperature(_T(""))
	, humidity(_T(""))
	, state(_T(""))
	, counter(_T(""))
	, connectionState(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


CClimatUIDlg::~CClimatUIDlg()
{
	soap_destroy(&soap); // delete deserialized class instances (for C++)
	soap_end(&soap); // remove deserialized data and clean up
	soap_done(&soap); // detach the gSOAP context

}

void CClimatUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITTemp, temperature);
	DDX_Text(pDX, IDC_EDITHum, humidity);
	DDX_Text(pDX, IDC_EDITState, state);
	DDX_Text(pDX, IDC_EDITCounter, counter);
	DDX_Text(pDX, IDC_EDITConnection, connectionState);
}

BEGIN_MESSAGE_MAP(CClimatUIDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONVentilate, &CClimatUIDlg::OnBnClickedButtonventilate)
	ON_BN_CLICKED(IDC_BUTTONStop, &CClimatUIDlg::OnBnClickedButtonstop)
	ON_BN_CLICKED(IDC_BUTTONStopVentilate, &CClimatUIDlg::OnBnClickedButtonstopventilate)
END_MESSAGE_MAP()


// CClimatUIDlg message handlers

BOOL CClimatUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	timerCnt = 0;

	SetTimer( checkValuesTimer, timerDelay, NULL);
	soap_init(&soap);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClimatUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClimatUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CClimatUIDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CClimatUIDlg::OnEnChangeEdittemp()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CClimatUIDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	GrowBoxInfo  growBoxInfo;
	CDialog::OnTimer(nIDEvent);
	int res;

//soap_call_ns__getGrowBoxInfo(struct soap *soap, const char *soap_endpoint, const char *soap_action, GrowBoxInfo *Result);


	++timerCnt;
	if (nIDEvent == checkValuesTimer)
	{

		if( (res = soap_call_ns__getGrowBoxInfo(&soap, "192.168.1.50:18083", NULL, &growBoxInfo))== SOAP_OK) {
			state = growBoxInfo.State;
			humidity.Format("%6.2f",growBoxInfo.Humidity);
			temperature.Format("%6.2f",growBoxInfo.Temperature);
			counter.Format("%i",growBoxInfo.HygroCnt);
			connectionState.Format("connected at %i",timerCnt);
			
			if (state.Find(_T("Not Ventilating")) >  -1) {
				GetDlgItem(IDC_BUTTONVentilate)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTONStopVentilate)->EnableWindow(FALSE);
			} else { if (state.Find(_T("Ventilating")) >  -1) {
				GetDlgItem(IDC_BUTTONVentilate)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTONStopVentilate)->EnableWindow(TRUE);
			} else {
				GetDlgItem(IDC_BUTTONVentilate)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTONStopVentilate)->EnableWindow(FALSE);
			}}		  
			
		} else {
			connectionState.Format("err: %i at: %i %s",res,timerCnt,*soap_faultstring(&soap));
			//MessageBeep(0);
			//MessageBox("error gsoap getGrowBoxInfo","error gsoap getGrowBoxInfo",MB_OK);
		}
		UpdateData( FALSE );
//		MessageBeep(0);
/*
		growBoxController.OnCheckValuesTimer();
		growBoxController.getMeasure(m_Humidity,m_Temperature,m_HygroCnt);

		GetRelaisValues();
		GetBehaviourValues();

		setStateText();
		UpdateData( FALSE );
*/
	}
	if (nIDEvent == dbUpdateTimer)
	{
//		growBoxController.OnDBUpdateTimer();
	}

}

void CClimatUIDlg::OnBnClickedButtonventilate()
{
	// TODO: Add your control notification handler code here
	long res;
	long retVal;
	if ((retVal = soap_call_ns__performAction(&soap, "192.168.1.50:18083", NULL, ventilateAct, res))== SOAP_OK) {
	} else {
		MessageBox("error","soap",MB_OK);
	}

}

void CClimatUIDlg::OnBnClickedButtonstop()
{
	// TODO: Add your control notification handler code here
	long res;
	long retVal;
	if ((retVal = soap_call_ns__performAction(&soap, "192.168.1.50:18083", NULL, stopAct, res))== SOAP_OK) {
	} else {
		MessageBox("error","soap",MB_OK);
	}
}

void CClimatUIDlg::OnBnClickedButtonstopventilate()
{
	// TODO: Add your control notification handler code here
	long res;
	long retVal;
	if ((retVal = soap_call_ns__performAction(&soap, "192.168.1.50:18083", NULL, stopVentilateAct, res))== SOAP_OK) {
	} else {
		MessageBox("error","soap",MB_OK);
	}
}
