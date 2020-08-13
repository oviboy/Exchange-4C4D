// Settings.cpp : implementation file
//

#include "stdafx.h"
#include "BRD2007.h"
#include ".\Settings.h"

// CSettings dialog

IMPLEMENT_DYNAMIC(CSettings, CDialog)
CSettings::CSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CSettings::IDD, pParent)
{
}

CSettings::~CSettings()
{
}

void CSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, comports);
	DDX_Control(pDX, IDC_SLIDER1, intensity);
}

BEGIN_MESSAGE_MAP(CSettings, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDCANCEL, &CSettings::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CSettings::OnBnClickedOk)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

BOOL CSettings::OnInitDialog()
{
	CDialog::OnInitDialog();

	for(int i = 1; i < 10; i++)
	{
		CString s;
		s.Format(_T("COM%d"), i);
		comports.AddString(s);
	}
	intensity.SetRange(5, 235, TRUE);
	intensity.SetTic(5);
	intensity.SetTicFreq(5);
	SetCom();
	int x = comports.GetCurSel();
	comports.GetLBText(x, selectedItem);

	return FALSE;
}

// CSettings message handlers
void CSettings::OnCbnSelchangeCombo1()
{
	int x = comports.GetCurSel();
	comports.GetLBText(x, selectedItem);
}

void CSettings::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)  
{  
    CSliderCtrl* pSlider = reinterpret_cast<CSliderCtrl*>(pScrollBar);  
	//CStatic *m_test = (CStatic*)GetDlgItem(IDC_STATIC_TEST2);
    switch(nSBCode)
    {
    case TB_LINEUP:
		//m_test->SetWindowTextA("TB_LINEUP");
		selected_intensity = pSlider->GetPos();
        break;
    case TB_LINEDOWN:
		selected_intensity = pSlider->GetPos();
		//m_test->SetWindowTextA("TB_LINEDOWN");
        break;
    case TB_PAGEUP:
		selected_intensity = pSlider->GetPos();
		//m_test->SetWindowTextA("TB_PAGEUP");
        break;
    case TB_PAGEDOWN:
		selected_intensity = pSlider->GetPos();
		//m_test->SetWindowTextA("TB_PAGEDOWN");
        break;
    case TB_THUMBPOSITION:
		//m_test->SetWindowTextA("TB_THUMBPOSITION");
		selected_intensity = pSlider->GetPos();
        break;
    case TB_TOP:
		selected_intensity = pSlider->GetPos();
		//m_test->SetWindowTextA("TB_TOP");
        break;
    case TB_BOTTOM:
		selected_intensity = pSlider->GetPos();
		//m_test->SetWindowTextA("TB_BOTTOM");
        break;  
    case TB_THUMBTRACK:  //start
		selected_intensity = pSlider->GetPos();
		//m_test->SetWindowTextA("TB_THUMBTRACK");
        break;  
    case TB_ENDTRACK:   //end
		/*if(start_drag == 1) {
			slider_pos = pSlider->GetPos();
			SendIntesity();
			start_drag = 0;
		}*/
		//m_test->SetWindowTextA("TB_ENDTRACK");
        break;  
    default:  
        break;  
    }
}

void CSettings::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CSettings::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
