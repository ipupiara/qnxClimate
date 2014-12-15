// ClimatUIDlg.h : header file
//
#ifndef climatuidlg_h
#define climatuidlg_h


#pragma once



// CClimatUIDlg dialog
class CClimatUIDlg : public CDialog
{
// Construction
public:
	CClimatUIDlg(CWnd* pParent = NULL);	// standard constructor
	~CClimatUIDlg();

// Dialog Data
	enum { IDD = IDD_CLIMATUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	int timerCnt;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdittemp();
	CString temperature;
	CString humidity;
	CString state;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString counter;
	CString connectionState;
	afx_msg void OnBnClickedButtonventilate();
	afx_msg void OnBnClickedButtonstop();
	afx_msg void OnBnClickedButtonstopventilate();
};


#endif