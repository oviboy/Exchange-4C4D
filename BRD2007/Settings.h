#pragma once
#include "afxcmn.h"

// CSettings dialog

class CSettings : public CDialog
{
	DECLARE_DYNAMIC(CSettings)

public:
	CSettings(CWnd* pParent = NULL);   // standard constructor
	CSettings(int comNumber, int intensity) : CDialog(IDD, NULL)
	{
		com = comNumber;
		selected_intensity = intensity;
	}
	virtual ~CSettings();
	
	void GetSelection(CString &comp, int &intensity)
	{
		comp = selectedItem;
		intensity = selected_intensity;
	}

	void SetCom()
	{
		CString s;
		if(selected_intensity >= 5 && selected_intensity <= 235) {
			intensity.SetPos(selected_intensity);
		}
		else {
			AfxMessageBox(_T("Setare de intensitate gresita in\r\nfisierul de configurare !"));
			comports.SetCurSel(0);
		}
		if((com < 10) && (com > 0))	{
			for(int i = 0; i < comports.GetCount(); i++) {
				comports.GetLBText(i, s);
				char chArray[10];
				memcpy(chArray, s.GetBuffer(0), 4);
				char xCh = chArray[3];
				if(com == (int)(xCh - 0x30)) {
					comports.SetCurSel(com - 1);
					return;
				}
			}
			comports.SetCurSel(0);
		}
		else {
			AfxMessageBox(_T("Setare de port gresita in\r\nfisierul de configurare !"));
			comports.SetCurSel(0);
		}
	}

// Dialog Data
	enum { IDD = IDD_SETARI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CComboBox comports;
	int com, selected_intensity;
	CString selectedItem;
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl intensity;
};
