// BRD2007Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "inputnumber.h"
#define DIGITS 4
#define CURRENCY 4

// CBRD2007Dlg dialog
class CBRD2007Dlg : public CDialog
{
// Construction
public:
	CBRD2007Dlg(CWnd* pParent = NULL);	// standard constructor
	void UpdateComPort();
	void ReadConfig();
	void ReadValues(void);
	void SaveValues(void);
// Dialog Data
	enum { IDD = IDD_BRD2007_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
public:
	int portNumber, intensity;
	int oldPort, oldIntensity;

protected:
	CString inFile;		// numele fisierului de unde se incarca datele despre panouri
	CString outFile;	// numele fisierului unde se salveaza datele din panouri
	//CFont font_com;
	CEdit m_row1;
	CEdit m_row2;
	CFont font, title_font, font_valute, font_valute_l;
	CFont *oldFont;
	unsigned char panel_data[2048];

// Implementation
protected:
	HICON m_hIcon;
	void OnTimer(UINT nIDEvent) ;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CInputNumber m_val11;
	CInputNumber m_val12;
	CInputNumber m_val13;
	CInputNumber m_val14;
	CInputNumber m_val21;
	CInputNumber m_val22;
	CInputNumber m_val23;
	CInputNumber m_val24;
	CInputNumber m_comision;

	CEdit m_time;
	CEdit m_date;
	afx_msg void OnBnClickedSettingsCom();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedTrimite();
	afx_msg void OnBnClickedSyncClock();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSave();
	CInputNumber m_val15;
	CInputNumber m_val25;
};
