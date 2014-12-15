// GrowBoxDlg.cpp : implementation file
//

#include "GrowBox.h"
#include "GrowBoxDlg.h"
#include "Timer.h"
//#include <conio.h>




/////////////////////////////////////////////////////////////////////////////
// CGrowBoxDlg dialog

CGrowBoxDlg::CGrowBoxDlg()   //(CWnd* pParent /*=NULL*/)
//	: CDialog(CGrowBoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrowBoxDlg)
	m_TimerCount = 0;
	m_Humidity = 0.0;
	m_HygroCnt = 0;
	m_Temperature = 0.0;
	m_DryingLowerLimit = 0.0;
	m_DryingUpperLimit = 0.0;
	m_HeatingLowerLimit = 0.0;
	m_HeatingUpperLimit = 0.0;
	m_HumidifyingLowerLimit = 0.0;
	m_HumidifyingUpperLimit = 0.0;
	m_IdleVentilationDelayMinutes = 0.0;
	m_IdleVentilationMinutes = 0.0;
	m_CoolingLowerLimit = 0.0;
	m_CoolingUpperLimit = 0.0;
	m_RelaisCool = FALSE;
	m_RelaisDry = FALSE;
	m_RelaisHeat = FALSE;
	m_RelaisHumidify = FALSE;
	m_RelaisVentilate = FALSE;
/*
	m_RelaisHumidifyCaption = _T("");
	m_CoolingRelaisCaption = _T("");
	m_DryingRelaisCaption = _T("");
	m_HeatingRelaisCaption = _T("");
	m_VentilatingRelaisCaption = _T("");
	m_DBStateOK = FALSE;
	m_HeaterCoolerStates = _T("");

/*
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	growBoxController.setOwner(this);

}

void CGrowBoxDlg::DoDataExchange()   //(CDataExchange* pDX)
{
	/*
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrowBoxDlg)
	DDX_Control(pDX, IDC_EDITStateText, m_EditStateText);
	DDX_Control(pDX, IDC_EDITTitle, m_EditTitle);
	DDX_Text(pDX, IDC_EDITTimerCount, m_TimerCount);
	DDX_Text(pDX, IDC_EDIThumidity, m_Humidity);
	DDX_Text(pDX, IDC_EDIThygroCnt, m_HygroCnt);
	DDX_Text(pDX, IDC_EDITTemperature, m_Temperature);
	DDX_Text(pDX, IDC_EDITDryingLowerLimit, m_DryingLowerLimit);
	DDX_Text(pDX, IDC_EDITDryingUpperLimit, m_DryingUpperLimit);
	DDX_Text(pDX, IDC_EDITHeatingLowerLimit, m_HeatingLowerLimit);
	DDX_Text(pDX, IDC_EDITHeatingUpperLimit, m_HeatingUpperLimit);
	DDX_Text(pDX, IDC_EDITHumidifyingLowerLimit, m_HumidifyingLowerLimit);
	DDX_Text(pDX, IDC_EDITHumidifyingUpperLimit, m_HumidifyingUpperLimit);
	DDX_Text(pDX, IDC_EDITIdleVentilationDelayMinutes, m_IdleVentilationDelayMinutes);
	DDX_Text(pDX, IDC_EDITIdleVentilationMinutes, m_IdleVentilationMinutes);
	DDX_Text(pDX, IDC_EDITCoolingLowerLImit, m_CoolingLowerLimit);
	DDX_Text(pDX, IDC_EDITCoolingUpperLimit, m_CoolingUpperLimit);
	DDX_Check(pDX, IDC_CHECKRelaisCool, m_RelaisCool);
	DDX_Check(pDX, IDC_CHECKRelaisDry, m_RelaisDry);
	DDX_Check(pDX, IDC_CHECKRelaisHeat, m_RelaisHeat);
	DDX_Check(pDX, IDC_CHECKRelaisHumidify, m_RelaisHumidify);
	DDX_Check(pDX, IDC_CHECKRelaisVentilate, m_RelaisVentilate);
	DDX_Text(pDX, IDC_EDITRelaisHumidify, m_RelaisHumidifyCaption);
	DDX_Text(pDX, IDC_EDITCoolingRelais, m_CoolingRelaisCaption);
	DDX_Text(pDX, IDC_EDITDryingRelais, m_DryingRelaisCaption);
	DDX_Text(pDX, IDC_EDITHeatingRelais, m_HeatingRelaisCaption);
	DDX_Text(pDX, IDC_EDITVentilatingRelais, m_VentilatingRelaisCaption);
	DDX_Check(pDX, IDC_CHECKDBState, m_DBStateOK);
	DDX_Text(pDX, IDC_EDITHeaterCoolerStates, m_HeaterCoolerStates);
	//}}AFX_DATA_MAP
*/

}

/*
BEGIN_MESSAGE_MAP(CGrowBoxDlg, CDialog)
	//{{AFX_MSG_MAP(CGrowBoxDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONMinimize, OnBUTTONMinimize)
	ON_BN_CLICKED(IDC_BUTTONVentilation, OnBUTTONVentilation)
	ON_BN_CLICKED(IDC_BUTTONStopVentilation, OnBUTTONStopVentilation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
// CGrowBoxDlg message handlers

BOOL CGrowBoxDlg::OnInitDialog()
{
//	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
/*
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	setBoldText(m_EditTitle,CString("HUMIDITY TEMPERATURE CONTROLLER"));
*/
	growBoxController.start();

	
//  pn 17. sept 12 todo:
//	SetTimer( checkValuesTimer, timerDelay, NULL);
//	SetTimer( dbUpdateTimer, dbTimerDelay, NULL);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

//void CGrowBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
//{
	/*
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
	*/
//}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGrowBoxDlg::OnPaint() 
{
	/*
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
	*/
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
/*
HCURSOR CGrowBoxDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
*/


CGrowBoxDlg::~CGrowBoxDlg()
{
//	CDialog::~CDialog();
}


// pn 22. oct 12, CGrowBoxDlg::OnTimer is no more called
// since we dont have a UI within the application and mmoved the 
// timer from the dlg class (MFC-style) to it's own Timer class
void CGrowBoxDlg::OnTimer(unsigned int nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
//	CDialog::OnTimer(nIDEvent);


	if (nIDEvent == ventilationStartTimer)  {
		growBoxController.OnVentilationStartTimer();
	}

	if (nIDEvent == ventilationStopTimer)  {
		growBoxController.OnVentilationStopTimer();
	}

	if (nIDEvent == checkValuesTimer)
	{
		m_TimerCount ++;

		growBoxController.OnCheckValuesTimer();
//		growBoxController.getMeasure(m_Humidity,m_Temperature,m_HygroCnt);
//      pn 22 oct 12, commented some methods out and left them as prototype 
//		for tuture UI integration, as they were used under windows
//		GetRelaisValues();
//		GetBehaviourValues();

//		setStateText();
//		UpdateData( FALSE );
	}
	if (nIDEvent == dbUpdateTimer)
	{
		growBoxController.OnDBUpdateTimer();
	}
}


// todo: this must be transferred to the statechart part of the methods because it defines 
// behaviour of the statechart and not behaviour of the UI  pn 17. sept 12

void CGrowBoxDlg::startVentilatingStopTimer(double minutes)
{
//	SetTimer(ventilationStopTimer , (minutes * 60 * 1000), NULL);
}

void CGrowBoxDlg::stopVentilatingStopTimer()
{
//	KillTimer(ventilationStopTimer);
}

void CGrowBoxDlg::startVentilatingStartTimer(double minutes)
{
//	SetTimer( ventilationStartTimer, (minutes * 60 * 1000), NULL);
}

void CGrowBoxDlg::stopVentilatingStartTimer()
{
//	KillTimer(ventilationStartTimer);
}



void CGrowBoxDlg::GetBehaviourValues()
{

	m_HeatingLowerLimit = CGrowBoxDefines::GetHeatingLowerLimit();
	m_HeatingUpperLimit = CGrowBoxDefines::GetHeatingUpperLimit();
	m_CoolingLowerLimit = CGrowBoxDefines::GetCoolingLowerLimit();
	m_CoolingUpperLimit = CGrowBoxDefines::GetCoolingUpperLimit();

	m_HumidifyingLowerLimit = CGrowBoxDefines::GetHumidifyingLowerLimit();
	m_HumidifyingUpperLimit = CGrowBoxDefines::GetHumidifyingUpperLimit();
	m_DryingLowerLimit = CGrowBoxDefines::GetDryingLowerLimit();
	m_DryingUpperLimit = CGrowBoxDefines::GetDryingUpperLimit();
	
	m_IdleVentilationDelayMinutes = CGrowBoxDefines::GetIdleVentilationDelayMinutes();
	m_IdleVentilationMinutes = CGrowBoxDefines::GetIdleVentilationMinutes();
}

void CGrowBoxDlg::GetRelaisValues()
{
	/*
	m_RelaisCool = growBoxController.isRelaisSet(CGrowBoxDefines::GetCoolingRelais());
	m_RelaisDry = growBoxController.isRelaisSet(CGrowBoxDefines::GetDryingRelais());
	m_RelaisHeat = growBoxController.isRelaisSet(CGrowBoxDefines::GetHeatingRelais());
	m_RelaisHumidify = growBoxController.isRelaisSet(CGrowBoxDefines::GetHumidifyingRelais());
	m_RelaisVentilate = growBoxController.isRelaisSet(CGrowBoxDefines::GetVentilatingRelais());

	m_RelaisHumidifyCaption.Format("Relais %i",CGrowBoxDefines::GetHumidifyingRelais() );
	m_CoolingRelaisCaption.Format("Relais %i",CGrowBoxDefines::GetCoolingRelais() );
	m_DryingRelaisCaption.Format("Relais %i",CGrowBoxDefines::GetDryingRelais() );
	m_HeatingRelaisCaption.Format("Relais %i",CGrowBoxDefines::GetHeatingRelais() );
	m_VentilatingRelaisCaption.Format("Relais %i",CGrowBoxDefines::GetVentilatingRelais());				

	m_HeaterCoolerStates = CString("t: ")+ growBoxController.HeaterStateString()+ CString(" h: ")+  \
						growBoxController.HumidifyerStateString();
	m_DBStateOK = growBoxController.isDBInterfaceOn();
*/
}

void CGrowBoxDlg::OnOK() 
{
	// TODO: Add extra validation here
	growBoxController.stop();
//	CDialog::OnOK();
}


void CGrowBoxDlg::setStateText()
{
	/*
	CString txt = CString("");

	if (! growBoxController.isHygrosensSensorRunning()) txt += "/  Sensor error  ";
	if (! growBoxController.isRelaisControllerRunning()) txt += "/  Relais error  ";
	
	setBoldText(m_EditStateText,txt);
	
	m_EditStateText.SetWindowText(txt);
	*/
}

void CGrowBoxDlg::setBoldText()    //(CEdit &edt, CString &txt)
{
/*
	//
	//  PN 8. Nov 2005 copied this code from an MSDN Sample
	//		lets hope it works under all possible windows font intallations....
	//
/*
	edt.SetWindowText(txt);
	CFont font;
	font.CreateFont(
	   16,                        // nHeight
	   0,                         // nWidth
	   0,                         // nEscapement
	   0,                         // nOrientation
	   FW_NORMAL,                 // nWeight
	   FALSE,                     // bItalic
	   FALSE,                     // bUnderline
	   0,                         // cStrikeOut
	   ANSI_CHARSET,              // nCharSet
	   OUT_DEFAULT_PRECIS,        // nOutPrecision
	   CLIP_DEFAULT_PRECIS,       // nClipPrecision
	   DEFAULT_QUALITY,           // nQuality
	   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	   NULL);                 // lpszFacename
	edt.SetFont(&font);
	font.DeleteObject(); 
*/
}

void CGrowBoxDlg::OnBUTTONMinimize() 
{
	// TODO: Add your control notification handler code here

/*
	WINDOWPLACEMENT  wp;
	if (GetWindowPlacement(&wp)) {
			
		wp.showCmd = SW_SHOWMINIMIZED   ;


		SetWindowPlacement(&wp);
	}
*/
	// CWnd. SetWindowPlacement....
}

void CGrowBoxDlg::OnBUTTONVentilation() 
{
	// TODO: Add your control notification handler code here
	growBoxController.onVentilationButtonPressed();
}

void CGrowBoxDlg::onEntryIdleNotVentilating()
{
	//GetDlgItem(IDC_BUTTONVentilation)->EnableWindow(TRUE);
}

void CGrowBoxDlg::onExitIdleNotVentilating()
{
//	GetDlgItem(IDC_BUTTONVentilation)->EnableWindow(FALSE);
}

void CGrowBoxDlg::onEntryIdleVentilating()
{
//	GetDlgItem(IDC_BUTTONStopVentilation)->EnableWindow(TRUE);
}

void CGrowBoxDlg::onExitIdleVentilating()
{
//	GetDlgItem(IDC_BUTTONStopVentilation)->EnableWindow(FALSE);
}

void CGrowBoxDlg::OnBUTTONStopVentilation() 
{
	// TODO: Add your control notification handler code here
	growBoxController.onStopVentilationButtonPressed();
	
}
