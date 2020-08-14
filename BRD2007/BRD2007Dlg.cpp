// BRD2007Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "BRD2007.h"
#include "BRD2007Dlg.h"
#include "Settings.h"
#include "Serial.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
int bcd(int dec)
{
	return ((dec/10)<<4)+(dec%10);
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBRD2007Dlg dialog




CBRD2007Dlg::CBRD2007Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBRD2007Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	intensity = 100;
}

void CBRD2007Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VAL11, m_val11);
	DDX_Control(pDX, IDC_VAL12, m_val12);
	DDX_Control(pDX, IDC_VAL13, m_val13);
	DDX_Control(pDX, IDC_VAL14, m_val14);
	DDX_Control(pDX, IDC_VAL21, m_val21);
	DDX_Control(pDX, IDC_VAL22, m_val22);
	DDX_Control(pDX, IDC_VAL23, m_val23);
	DDX_Control(pDX, IDC_VAL24, m_val24);
}

BEGIN_MESSAGE_MAP(CBRD2007Dlg, CDialog)
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SETTINGS_COM, &CBRD2007Dlg::OnBnClickedSettingsCom)
	ON_BN_CLICKED(IDC_EXIT, &CBRD2007Dlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_TRIMITE, &CBRD2007Dlg::OnBnClickedTrimite)
	ON_BN_CLICKED(IDC_SYNC_CLOCK, &CBRD2007Dlg::OnBnClickedSyncClock)
	ON_BN_CLICKED(IDC_OPEN, &CBRD2007Dlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_SAVE, &CBRD2007Dlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CBRD2007Dlg message handlers

BOOL CBRD2007Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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
	ReadConfig();
	// TODO: Add extra initialization here
	oldFont = m_val11.GetFont();	//este la fel pentru toate celelalte controale
	font.CreateFont(16,                        
		0,                        
		0,                        
		0,                        
		FW_BOLD,                 
		FALSE,                   
		FALSE,                   
		0,                       
		DEFAULT_CHARSET,            
		OUT_DEFAULT_PRECIS,      
		CLIP_DEFAULT_PRECIS,     
		DEFAULT_QUALITY,         
		DEFAULT_PITCH | FF_SWISS, 
		_T("Arial"));
	title_font.CreateFont(21,                        
		0,                        
		0,                        
		0,                        
		FW_BOLD,                 
		FALSE,                   
		FALSE,                   
		0,                       
		DEFAULT_CHARSET,            
		OUT_DEFAULT_PRECIS,      
		CLIP_DEFAULT_PRECIS,     
		ANTIALIASED_QUALITY,         
		DEFAULT_PITCH | FF_SWISS, 
		_T("Tahoma"));
	font_valute.CreateFont(15,                        
		0,                        
		0,                        
		0,                        
		FW_BOLD,                 
		FALSE,                   
		FALSE,                   
		0,                       
		DEFAULT_CHARSET,            
		OUT_DEFAULT_PRECIS,      
		CLIP_DEFAULT_PRECIS,     
		ANTIALIASED_QUALITY,         
		DEFAULT_PITCH | FF_SWISS, 
		_T("Tahoma"));
	font_valute_l.CreateFont(13,                        
		0,                        
		0,                        
		0,                        
		FW_BOLD,                 
		FALSE,                   
		FALSE,                   
		0,                       
		DEFAULT_CHARSET,            
		OUT_DEFAULT_PRECIS,      
		CLIP_DEFAULT_PRECIS,     
		ANTIALIASED_QUALITY,         
		DEFAULT_PITCH | FF_SWISS, 
		_T("Tahoma"));

	m_val11.SetFont(&font);
	m_val11.SetMaxLen(DIGITS);
	m_val12.SetFont(&font);
	m_val12.SetMaxLen(DIGITS);
	m_val13.SetFont(&font);
	m_val13.SetMaxLen(DIGITS);
	m_val14.SetFont(&font);
	m_val14.SetMaxLen(DIGITS);

	m_val21.SetFont(&font);
	m_val21.SetMaxLen(DIGITS);
	m_val22.SetFont(&font);
	m_val22.SetMaxLen(DIGITS);
	m_val23.SetFont(&font);
	m_val23.SetMaxLen(DIGITS);
	m_val24.SetFont(&font);
	m_val24.SetMaxLen(DIGITS);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBRD2007Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBRD2007Dlg::OnPaint()
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
HCURSOR CBRD2007Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBRD2007Dlg::UpdateComPort()
{
	CStdioFile cfgFile;
	char *path1, *path2, *path3;
	path1 = new char[1024];
	path2 = new char[1024];
	path3 = new char[1024];
	unsigned len = 0, last;
	CString line;

	//aflam aici calea executabilului
	memset(path1, 0x00, 1024);
	GetModuleFileName(NULL, (LPTSTR)path1, 1024);
	//curatam path2
	memset(path2, 0x00, 1024);
	while(len <= strlen(path1)) {
		if(path1[len] == '\\')
			last = len;
		len++;
	}
	memcpy(path2, path1, last);
	memset(path3, 0x00, 1024);
	memcpy(path3, path1, last);
	strncat(path2, "\\panou.cfg", strlen("\\panou.cfg"));
	strncat(path3, "\\panounew.cfg", strlen("\\panounew.cfg"));

	CString strLine;
	CString bigString;
	cfgFile.Open(CString(path2), CFile::modeRead);

	delete path1;

	while(cfgFile.ReadString(strLine))
	{
		bigString += strLine.TrimLeft(_T("\r\n"));
		bigString += CString(_T("\n"));
	}

	cfgFile.Close();

	CString repl1, repl2, tmp;
	tmp.Format("ComPort=%d\r\nIntensity=%d", portNumber, intensity);
	
	CStdioFile newCfg;
	newCfg.Open((LPCTSTR)path3, CFile::modeCreate | CFile::modeWrite);
	newCfg.WriteString(tmp);
	newCfg.Close();
	
	try {
		CFile::Remove((LPCTSTR)path2);

	}
	catch (CFileException* pEx) {
		AfxMessageBox(_T("Nu pot salva noua configuratie (Error 1) !"));
		delete path2;
		delete path3;
		pEx->Delete();
		return;
	}

	try {
		CFile::Rename((LPCTSTR)path3, (LPCTSTR)path2);
	}
	catch(CFileException* pEx ) {
		AfxMessageBox(_T("Nu pot salva noua configuratie (Error 2) !"));
		pEx->Delete();
	}

	delete path2;
	delete path3;
}

void CBRD2007Dlg::ReadValues(void)
{
	FILE *iniFile;
	char *path1, *path2;
	char buffer[255];
	path1 = new char[256];
	path2 = new char[256];
	unsigned len = 0, last = 0;
	CString line;

	//aflam aici calea executabilului
	memset(path1, 0x00, 256);
	GetModuleFileName(NULL, path1, 255);
	//curatam path2
	memset(path2, 0x00, 256);
	while(len <= strlen(path1)) {
		if(path1[len] == '\\')
			last = len;
		len++;
	}
	memcpy_s(path2, 255, path1, last);
	strcat(path2, "\\pv.cfg");
	if((iniFile = fopen(path2, "rb")) == NULL) {
		delete []path1;
		delete []path2;
		return;
	}
	delete []path1;
	delete []path2;

	do {
		fgets(buffer, 255, iniFile);
		line = CString(buffer);
		line.Trim();
		if(line.GetAt(0) != ';') {
			int n;
			char *pdest = NULL;
			pdest = strstr((char*)(LPCTSTR)line, "=");
			n = (int)(pdest - (char*)(LPCTSTR)line + 1);
			if(pdest != NULL) {
				CString leftText = line.Left(n-1);
				CString rightText = line.Right(line.GetLength() - n);
				if(leftText.CompareNoCase(_T("val11")) == 0) {
					m_val11.SetWindowTextA(rightText);
				}
				if(leftText.CompareNoCase(_T("val12")) == 0) {
					m_val21.SetWindowTextA(rightText);
				}
				if(leftText.CompareNoCase(_T("val21")) == 0) {
					m_val12.SetWindowTextA(rightText);
				}
				if(leftText.CompareNoCase(_T("val22")) == 0) {
					m_val22.SetWindowTextA(rightText);
				}
				if(leftText.CompareNoCase(_T("val31")) == 0) {
					m_val13.SetWindowTextA(rightText);
				}
				if(leftText.CompareNoCase(_T("val32")) == 0) {
					m_val23.SetWindowTextA(rightText);
				}
				if(leftText.CompareNoCase(_T("val41")) == 0) {
					m_val14.SetWindowTextA(rightText);
				}
				if(leftText.CompareNoCase(_T("val42")) == 0) {
					m_val24.SetWindowTextA(rightText);
				}
			}
		}
		if(feof(iniFile))
			break;
	}while(TRUE);

	fclose(iniFile);
}

void CBRD2007Dlg::SaveValues(void)
{
	CStdioFile cfgFile;
	char *path1, *path2;
	path1 = new char[1024];
	path2 = new char[1024];
	unsigned len = 0, last;
	CString line;

	//aflam aici calea executabilului
	memset(path1, 0x00, 1024);
	GetModuleFileName(NULL, (LPTSTR)path1, 1024);
	//curatam path2
	memset(path2, 0x00, 1024);
	while(len <= strlen(path1)) {
		if(path1[len] == '\\')
			last = len;
		len++;
	}
	memcpy(path2, path1, last);
	strncat(path2, "\\pv.cfg", strlen("\\pv.cfg"));	
	delete path1;

	CString val11, val12, val21, val22, val31, val32, val41, val42, tmp;
	m_val11.GetWindowTextA(val11);
	m_val21.GetWindowTextA(val12);
	m_val12.GetWindowTextA(val21);
	m_val22.GetWindowTextA(val22);
	m_val13.GetWindowTextA(val31);
	m_val23.GetWindowTextA(val32);
	m_val14.GetWindowTextA(val41);
	m_val24.GetWindowTextA(val42);

	tmp.Format("val11=%s\r\nval12=%s\r\nval21=%s\r\nval22=%s\r\nval31=%s\r\nval32=%s\r\nval41=%s\r\nval42=%s", val11, val12, val21, val22, val31, val32, val41, val42);
	
	CStdioFile newCfg;
	newCfg.Open((LPCTSTR)path2, CFile::modeCreate | CFile::modeWrite);
	newCfg.WriteString(tmp);
	newCfg.Close();

	delete path2;
}

void CBRD2007Dlg::ReadConfig(void)
{
	FILE *iniFile;
	char *path1, *path2;
	char buffer[255];
	path1 = new char[256];
	path2 = new char[256];
	unsigned len = 0, last = 0;
	CString line;

	//aflam aici calea executabilului
	memset(path1, 0x00, 256);
	GetModuleFileName(NULL, path1, 255);
	//curatam path2
	memset(path2, 0x00, 256);
	while(len <= strlen(path1)) {
		if(path1[len] == '\\')
			last = len;
		len++;
	}
	memcpy_s(path2, 255, path1, last);
	strcat(path2, "\\panou.cfg");
	if((iniFile = fopen(path2, "rb")) == NULL) {
		AfxMessageBox(_T("Nu pot deschide fisierul de configurare \"panou.cfg\" ! \r\nAplicatia nu poate rula fara fisier de configurare !"));
		delete []path1;
		delete []path2;
		SendMessage(WM_CLOSE, NULL, NULL);
	}
	delete []path1;
	delete []path2;

	do {
		fgets(buffer, 255, iniFile);
		line = CString(buffer);
		line.Trim();
		if(line.GetAt(0) != ';') {
			int n;
			char *pdest = NULL;
			pdest = strstr((char*)(LPCTSTR)line, "=");
			n = (int)(pdest - (char*)(LPCTSTR)line + 1);
			if(pdest != NULL) {
				CString leftText = line.Left(n-1);
				CString rightText = line.Right(line.GetLength() - n);
				if(leftText.CompareNoCase(_T("ComPort")) == 0) {
					portNumber = atoi((char*)(LPCTSTR)rightText);
				}
				if(leftText.CompareNoCase(_T("Intensity")) == 0) {
					intensity = atoi((char*)(LPCTSTR)rightText);
					oldIntensity = intensity;
				}
			}
		}
		if(feof(iniFile))
			break;
	}while(TRUE);

	ReadValues();

	fclose(iniFile);
}

void CBRD2007Dlg::OnBnClickedSettingsCom()
{
	//Setari de com
	CSettings setting(portNumber, intensity);
	INT_PTR nRet = setting.DoModal();
	if(nRet == IDOK) {
		CString com;
		oldIntensity = intensity;
		setting.GetSelection(com, intensity);
		char xArray[10];
		memcpy(xArray, (LPCTSTR)com, 4);
		if(portNumber != (int)(xArray[3] - 0x30) || oldIntensity != intensity) {
			oldPort = portNumber;
			portNumber = (int)(xArray[3] - 0x30);
			
			UpdateComPort();
		}
	}
}

void CBRD2007Dlg::OnBnClickedExit()
{
	m_val11.SetFont(oldFont);
	m_val12.SetFont(oldFont);
	m_val13.SetFont(oldFont);
	m_val14.SetFont(oldFont);

	m_val21.SetFont(oldFont);
	m_val22.SetFont(oldFont);
	m_val23.SetFont(oldFont);
	m_val24.SetFont(oldFont);
	SaveValues();
	font.DeleteObject();
	EndDialog(0);
}


void CBRD2007Dlg::OnOK()
{
	OnBnClickedExit();
}

void CBRD2007Dlg::OnCancel()
{
	OnBnClickedExit();
}

void CBRD2007Dlg::OnTimer(UINT nIDEvent) 
{
	
   CDialog::OnTimer(nIDEvent);
}

void CBRD2007Dlg::OnBnClickedTrimite()
{
	char tmp[10];
	CString text;
	size_t len = 0;

	memset(tmp, 0x00, 10);

	memset(panel_data, 0x00, 2048);
	panel_data[len] = START;			//start
	len++;
	panel_data[len] = 240-(unsigned char)intensity;
	len++;

	char no_number[DIGITS];
	memset(no_number, 0x00, DIGITS);
	for (int i = 0; i < DIGITS; i++)
		no_number[i] = '-';


	memset(tmp, 0x00, 10);
	m_val11.GetWindowText(text);
	if(!text.IsEmpty()) {
		if(text.Find('.') == -1)
			sprintf_s(tmp, 10, "% 4s", (char*)(LPCSTR)text);
		else
			sprintf_s(tmp, 10, "% 5s", (char*)(LPCSTR)text);
	}
	else
		sprintf_s(tmp, 10, "%s", no_number);
	memcpy_s(panel_data + len, 10, (unsigned char*)tmp, strlen(tmp));
	len += strlen(tmp);

	memset(tmp, 0x00, 10);
	m_val21.GetWindowText(text);
	if(!text.IsEmpty()) {
		if(text.Find('.') == -1)
			sprintf_s(tmp, 10, "% 4s", (char*)(LPCSTR)text);
		else
			sprintf_s(tmp, 10, "% 5s", (char*)(LPCSTR)text);
	}
	else
		sprintf_s(tmp, 10, "%s", no_number);
	memcpy_s(panel_data + len, 10, (unsigned char*)tmp, strlen(tmp));
	len += strlen(tmp);

	memset(tmp, 0x00, 10);
	m_val12.GetWindowText(text);
	if(!text.IsEmpty()) {
		if(text.Find('.') == -1)
			sprintf_s(tmp, 10, "% 4s", (char*)(LPCSTR)text);
		else
			sprintf_s(tmp, 10, "% 5s", (char*)(LPCSTR)text);
	}
	else
		sprintf_s(tmp, 10, "%s", no_number);
	memcpy_s(panel_data + len, 10, (unsigned char*)tmp, strlen(tmp));
	len += strlen(tmp);

	memset(tmp, 0x00, 10);
	m_val22.GetWindowText(text);
	if(!text.IsEmpty()) {
		if(text.Find('.') == -1)
			sprintf_s(tmp, 10, "% 4s", (char*)(LPCSTR)text);
		else
			sprintf_s(tmp, 10, "% 5s", (char*)(LPCSTR)text);
	}
	else
		sprintf_s(tmp, 10, "%s", no_number);
	memcpy_s(panel_data + len, 10, (unsigned char*)tmp, strlen(tmp));
	len += strlen(tmp);

	memset(tmp, 0x00, 10);
	m_val13.GetWindowText(text);
	if(!text.IsEmpty()) {
		if(text.Find('.') == -1)
			sprintf_s(tmp, 10, "% 4s", (char*)(LPCSTR)text);
		else
			sprintf_s(tmp, 10, "% 5s", (char*)(LPCSTR)text);
	}
	else
		sprintf_s(tmp, 10, "%s", no_number);
	memcpy_s(panel_data + len, 10, (unsigned char*)tmp, strlen(tmp));
	len += strlen(tmp);

	memset(tmp, 0x00, 10);
	m_val23.GetWindowText(text);
	if(!text.IsEmpty()) {
		if(text.Find('.') == -1)
			sprintf_s(tmp, 10, "% 4s", (char*)(LPCSTR)text);
		else
			sprintf_s(tmp, 10, "% 5s", (char*)(LPCSTR)text);
	}
	else
		sprintf_s(tmp, 10, "%s", no_number);
	memcpy_s(panel_data + len, 10, (unsigned char*)tmp, strlen(tmp));
	len += strlen(tmp);

	memset(tmp, 0x00, 10);
	m_val14.GetWindowText(text);
	if(!text.IsEmpty()) {
		if(text.Find('.') == -1)
			sprintf_s(tmp, 10, "% 4s", (char*)(LPCSTR)text);
		else
			sprintf_s(tmp, 10, "% 5s", (char*)(LPCSTR)text);
	}
	else
		sprintf_s(tmp, 10, "%s", no_number);
	memcpy_s(panel_data + len, 10, (unsigned char*)tmp, strlen(tmp));
	len += strlen(tmp);

	memset(tmp, 0x00, 10);
	m_val24.GetWindowText(text);
	if(!text.IsEmpty()) {
		if(text.Find('.') == -1)
			sprintf_s(tmp, 10, "% 4s", (char*)(LPCSTR)text);
		else
			sprintf_s(tmp, 10, "% 5s", (char*)(LPCSTR)text);
	}
	else
		sprintf_s(tmp, 10, "%s", no_number);
	memcpy_s(panel_data + len, 10, (unsigned char*)tmp, strlen(tmp));
	len += strlen(tmp);

	panel_data[len] = STOP;
	len++;

	CWaitCursor w;
	CSerial s;
	char com[10];
	sprintf_s(com, 9, "COM%d", portNumber);
	s.Open(com);
	s.Send(panel_data, (DWORD)len);
	s.Close();
	w.Restore();
}

void CBRD2007Dlg::OnBnClickedSyncClock()
{
	char tmp[10];
	CString text;
	size_t len = 0;
	CTime t = CTime::GetCurrentTime();

	memset(tmp, 0x00, 10);

	memset(panel_data, 0x00, 2048);
	panel_data[len] = START;			//start
	len++;
	panel_data[len] = 0x31;
	len++;
	panel_data[len] = (unsigned char)bcd(t.GetSecond());
	len++;
	panel_data[len] = (unsigned char)bcd(t.GetMinute());
	len++;
	panel_data[len] = (unsigned char)bcd(t.GetHour());
	len++;
	panel_data[len] = (unsigned char)bcd(t.GetDay());
	len++;
	panel_data[len] = (unsigned char)bcd(t.GetDayOfWeek());
	len++;
	panel_data[len] = (unsigned char)bcd(t.GetMonth());
	len++;
	panel_data[len] = (unsigned char)bcd((t.GetYear() - 2000));
	len++;
	panel_data[len] = STOP;
	len++;

	CWaitCursor w;
	CSerial s;
	char com[10];
	sprintf_s(com, 9, "COM%d", portNumber);
	s.Open(com);
	s.Send(panel_data, (DWORD)len);
	s.Close();
	w.Restore();
}

void CBRD2007Dlg::OnBnClickedOpen()
{
	char tipuri[] = "Fisiere v44 (*.v44)|*.v44|Toate fisierele (*.*)|*.*||";
	CFileDialog fileDlg(TRUE, "V44", "*.v44", OFN_FILEMUSTEXIST, tipuri, this);
	CStdioFile stdf;
	CString strLine, strLine1, line1, line2, timp;
	unsigned char tmp[256];
	int index = 0, idx = 0;
	BOOL num;
	
	num = FALSE;
	if(fileDlg.DoModal() == IDOK) {
		inFile = fileDlg.GetPathName();
		if(!stdf.Open(inFile, CFile::modeRead | CFile::typeText))
			AfxMessageBox("Fisierul introdus nu se poate deschide !");
		int i = 0;
		while(stdf.GetPosition() != stdf.GetLength()) {
			stdf.ReadString(strLine);
			if(i != 0)
				idx++;
			if(i == 0) {
				memset(tmp, 0x00, 255);
				if(strLine.GetLength() >= 255)
					memcpy_s(tmp, 255, (LPCSTR)strLine, 255);//citeste max 255 din linie. oricum nu ne intereseaza
				else								  //deoarece sigur nu avem asa o linie in fisier (intr-un fisier valid, ma refer)
					memcpy_s(tmp, 255, (LPCSTR)strLine, strLine.GetLength());
				i++;
				if(tmp[0] != START) {	//verific daca fisierul selectat este unul corespunzator
					AfxMessageBox("Fisierul selectat este invalid !");
					break;
				}
			}
			else {
				int number_of_decimal_points = 0;
				if(idx == 1) {//dob ron
					m_val11.SetWindowText(strLine);
				    if (strLine.Find('.') != -1) {
						number_of_decimal_points = 1;
					}
					m_val11.setCheckPoint((bool)number_of_decimal_points);
				}
				else if(idx == 2) {
					m_val21.SetWindowText(strLine);
				    if (strLine.Find('.') != -1) {
						number_of_decimal_points = 1;
					}
					m_val21.setCheckPoint((bool)number_of_decimal_points);
				}
				else if(idx == 3) {
					m_val12.SetWindowText(strLine);
				    if (strLine.Find('.') != -1) {
						number_of_decimal_points = 1;
					}
					m_val12.setCheckPoint((bool)number_of_decimal_points);
				}
				else if(idx == 4) {
					m_val22.SetWindowText(strLine);
				    if (strLine.Find('.') != -1) {
						number_of_decimal_points = 1;
					}
					m_val22.setCheckPoint((bool)number_of_decimal_points);
				}
				else if(idx == 5) {
					m_val13.SetWindowText(strLine);
				    if (strLine.Find('.') != -1) {
						number_of_decimal_points = 1;
					}
					m_val13.setCheckPoint((bool)number_of_decimal_points);
				}
				else if(idx == 6) {
					m_val23.SetWindowText(strLine);
				    if (strLine.Find('.') != -1) {
						number_of_decimal_points = 1;
					}
					m_val23.setCheckPoint((bool)number_of_decimal_points);
				}
				else if(idx == 7) {
					m_val14.SetWindowText(strLine);
				    if (strLine.Find('.') != -1) {
						number_of_decimal_points = 1;
					}
					m_val14.setCheckPoint((bool)number_of_decimal_points);
				}
				else if(idx == 8) {
					m_val24.SetWindowText(strLine);
				    if (strLine.Find('.') != -1) {
						number_of_decimal_points = 1;
					}
					m_val24.setCheckPoint((bool)number_of_decimal_points);
				}
			}
		}
		stdf.Close();
	}
}

void CBRD2007Dlg::OnBnClickedSave()
{
	CString numbers;
	CString line1, line2, val;
	int timp = 0;
	
	//obtin valorile numerice
	numbers = _T("");
	m_val11.GetWindowText(val);
	numbers.Append(val);
	numbers.Append(_T("\r\n"));
	m_val21.GetWindowText(val);
	numbers.Append(val);
	numbers.Append(_T("\r\n"));
	m_val12.GetWindowText(val);
	numbers.Append(val);
	numbers.Append(_T("\r\n"));
	m_val22.GetWindowText(val);
	numbers.Append(val);
	numbers.Append(_T("\r\n"));
	m_val13.GetWindowText(val);
	numbers.Append(val);
	numbers.Append(_T("\r\n"));

	m_val23.GetWindowText(val);
	numbers.Append(val);
	numbers.Append(_T("\r\n"));
	m_val14.GetWindowText(val);
	numbers.Append(val);
	numbers.Append(_T("\r\n"));
	m_val24.GetWindowText(val);
	numbers.Append(val);
	numbers.Append(_T("\r\n"));

	char tipuri[] = "Fisiere V54 (*.v44)|*.v44|Toate fisierele (*.*)|*.*||";
	char enter[2] = {0x0d, 0x0a};
	CFileDialog fileDlg(FALSE, "V44", NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, tipuri, this);

	if(fileDlg.DoModal() == IDOK)
	{
		outFile = fileDlg.GetPathName();
		if(outFile.IsEmpty())
			AfxMessageBox("Trebuie sa introduceti un nume de fisier mai intai !");
		else
		{
			//incep sa salvez datele din panou
			CFile out((LPCTSTR)outFile, CFile::modeCreate | CFile::modeWrite);
			CString time, field1, field2;
			int txIndex = 0;
			unsigned char *buff;
			buff = (unsigned char*)malloc(10);
			
			memset(buff, 0x00, 10);
			buff[0] = START;
			out.Write(buff, 1);	//se incepe cu caracterul de start
			out.Write(enter, 2);
			out.Write((LPCSTR)numbers, numbers.GetLength());
			memset(buff, 0x00, 10);
			buff[0] = STOP;
			out.Write(buff, 1);	//se mai adauga si un caracter de stop
			out.Write(enter, 2);
			out.Close();
			free(buff);
		}
	}
}
