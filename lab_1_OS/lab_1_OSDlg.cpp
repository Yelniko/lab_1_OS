
// lab_1_OSDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "lab_1_OS.h"
#include "lab_1_OSDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


struct ThreadParams
{
	Clab1OSDlg* pDlg;
	int id;
};


HANDLE hThread1 = NULL;
HANDLE hThread2 = NULL;
HANDLE hThread3 = NULL;

DWORD g_dwThreadId1, g_dwThreadId2, g_dwThreadId3;

FILETIME creationTime1, exitTime1, kernelTime1, userTime1;
FILETIME creationTime2, exitTime2, kernelTime2, userTime2;
FILETIME creationTime3, exitTime3, kernelTime3, userTime3;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Clab1OSDlg dialog



Clab1OSDlg::Clab1OSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LAB_1_OS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clab1OSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, progres_1);
	DDX_Control(pDX, IDC_PROGRESS2, progres_2);
	DDX_Control(pDX, IDC_PROGRESS3, progres_3);
	DDX_Control(pDX, IDC_LIST4, m_CONTEX_WORK);
	DDX_Control(pDX, IDC_LIST5, b_Time1);
	DDX_Control(pDX, IDC_LIST6, b_Time2);
	DDX_Control(pDX, IDC_LIST7, b_Time3);
	DDX_Control(pDX, IDC_COMBO1, Drop_List);
	DDX_Control(pDX, IDC_RADIO1, b_RADIO_1);
}

BEGIN_MESSAGE_MAP(Clab1OSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS3, &Clab1OSDlg::OnNMCustomdrawProgress3)
	
	ON_LBN_SELCHANGE(IDC_LIST4, &Clab1OSDlg::OnLbnSelchangeList4)
	
	ON_BN_CLICKED(Create, &Clab1OSDlg::OnBnClickedCreate)
	ON_BN_CLICKED(ID_Button_START_THREAD, &Clab1OSDlg::OnBnClickedButtonStartThread)
	
	
	ON_MESSAGE(WM_UPDATE_PROGRESS, &Clab1OSDlg::OnUpdateProgress)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &Clab1OSDlg::OnNMCustomdrawProgress1)
	

	ON_CBN_SELCHANGE(IDC_COMBOBOXEX3, &Clab1OSDlg::OnCbnSelchangeComboboxex3)
	ON_BN_CLICKED(IDC_BUTTON_STOP_THEARD, &Clab1OSDlg::OnBnClickedButtonStopTheard)

	ON_BN_CLICKED(IDC_BUTTON_TERMINATE_THREAD, &Clab1OSDlg::OnBnClickedButtonTerminateThread)
	ON_BN_CLICKED(IDC_BUTTON11, &Clab1OSDlg::OnBnClickedButton11)

	ON_LBN_SELCHANGE(IDC_LIST5, &Clab1OSDlg::OnLbnSelchangeList5)
	ON_LBN_SELCHANGE(IDC_LIST6, &Clab1OSDlg::OnLbnSelchangeList6)
	ON_LBN_SELCHANGE(IDC_LIST13, &Clab1OSDlg::OnLbnSelchangeList13)

	ON_CBN_SELCHANGE(IDC_COMBO1, &Clab1OSDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON6, &Clab1OSDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &Clab1OSDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_RADIO1, &Clab1OSDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &Clab1OSDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &Clab1OSDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_BUTTON8, &Clab1OSDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// Clab1OSDlg message handlers

BOOL Clab1OSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	


	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	progres_1.SetRange(0, 100);

	CheckDlgButton(IDC_RADIO1, BST_CHECKED);

	Drop_List.AddString(_T("High priority"));
	Drop_List.AddString(_T("Normal priority"));
	Drop_List.AddString(_T("Low priority"));
	Drop_List.SetCurSel(1);

	m_selectedThread = 0; 
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Clab1OSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Clab1OSDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Clab1OSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


DWORD WINAPI Threads(LPVOID pParam)
{
	ThreadParams* params = (ThreadParams*)pParam;
	Clab1OSDlg* pDlg = params->pDlg;
	int id = params->id;

	int n = 0;
	for (int i = 0; 1 <= 100; i++)
	{
		n += i;
		Sleep(100); // Imitation work
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_PROGRESS, (WPARAM)id, (LPARAM)i);
	}

	delete params;
	return 0;
}

void Clab1OSDlg::OnNMCustomdrawProgress3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
}

void Clab1OSDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void Clab1OSDlg::OnLbnSelchangeList4()
{
	// TODO: Add your control notification handler code here
}

void Clab1OSDlg::OnBnClickedCreate()
{
	SYSTEMTIME stUTC, stLocal;
	CString str;

	progres_1.SetRange(0, 100);
	progres_2.SetRange(0, 100);
	progres_3.SetRange(0, 100);

	b_Time1.DeleteString(0);
	b_Time2.DeleteString(0);
	b_Time3.DeleteString(0);

	ThreadParams* p1 = new ThreadParams{ this, 1 };
	hThread1 = CreateThread(0, 0, Threads, p1, CREATE_SUSPENDED, &g_dwThreadId1);

	ThreadParams* p2 = new ThreadParams{ this, 2 };
	hThread2 = CreateThread(0, 0, Threads, p2, CREATE_SUSPENDED, &g_dwThreadId2);

	ThreadParams* p3 = new ThreadParams{ this, 3 };
	hThread3 = CreateThread(0, 0, Threads, p3, CREATE_SUSPENDED, &g_dwThreadId3);

	GetThreadTimes(hThread1, &creationTime1, &exitTime1, &kernelTime1, &userTime1);
	GetThreadTimes(hThread2, &creationTime2, &exitTime2, &kernelTime2, &userTime2);
	GetThreadTimes(hThread3, &creationTime3, &exitTime3, &kernelTime3, &userTime3);

	FileTimeToSystemTime(&creationTime1, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

	str.Format(_T("Creation Time: %02d.%02d.%04d %02d:%02d:%02d\n"),
		stLocal.wDay, stLocal.wMonth, stLocal.wYear,
		stLocal.wHour, stLocal.wMinute, stLocal.wSecond);

	b_Time1.AddString(str);

	FileTimeToSystemTime(&creationTime2, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

	str.Format(_T("Creation Time: %02d.%02d.%04d %02d:%02d:%02d\n"),
		stLocal.wDay, stLocal.wMonth, stLocal.wYear,
		stLocal.wHour, stLocal.wMinute, stLocal.wSecond);

	b_Time2.AddString(str);

	FileTimeToSystemTime(&creationTime3, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

	str.Format(_T("Creation Time: %02d.%02d.%04d %02d:%02d:%02d\n"),
		stLocal.wDay, stLocal.wMonth, stLocal.wYear,
		stLocal.wHour, stLocal.wMinute, stLocal.wSecond);

	b_Time3.AddString(str);



}


void Clab1OSDlg::OnCbnSelchangeComboboxex3()
{
	
}

LRESULT Clab1OSDlg::OnUpdateProgress(WPARAM wParam, LPARAM lParam)
{
	int threadId = (int)wParam;
	int value = (int)lParam;  

	switch (threadId)
	{
		case 1: progres_1.SetPos(value); break;
		case 2: progres_2.SetPos(value); break;
		case 3: progres_3.SetPos(value); break;
	}
	return 0;
}

void Clab1OSDlg::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
}

void Clab1OSDlg::OnBnClickedButtonStartThread()
{
	ResumeThread(hThread1);
	ResumeThread(hThread2);
	ResumeThread(hThread3);
}

void Clab1OSDlg::OnBnClickedButtonStopTheard()
{
	CString cpuStr;
	ULARGE_INTEGER kTime, uTime;

	SuspendThread(hThread1);
	SuspendThread(hThread2);
	SuspendThread(hThread3);

	b_Time1.DeleteString(1);
	b_Time2.DeleteString(1);
	b_Time3.DeleteString(1);

	kTime.LowPart = kernelTime1.dwLowDateTime;
	kTime.HighPart = kernelTime1.dwHighDateTime;
	uTime.LowPart = userTime1.dwLowDateTime;
	uTime.HighPart = userTime1.dwHighDateTime;

	cpuStr.Format(_T("Kernel Time: %I64u ms\nUser Time: %I64u ms"),
		kTime.QuadPart / 10000,
		uTime.QuadPart / 10000);

	b_Time1.AddString(cpuStr);

	kTime.LowPart = kernelTime1.dwLowDateTime;
	kTime.HighPart = kernelTime1.dwHighDateTime;
	uTime.LowPart = userTime1.dwLowDateTime;
	uTime.HighPart = userTime1.dwHighDateTime;

	cpuStr.Format(_T("Kernel Time: %I64u ms\nUser Time: %I64u ms"),
		kTime.QuadPart / 10000,
		uTime.QuadPart / 10000);
	
	b_Time2.AddString(cpuStr);

	kTime.LowPart = kernelTime1.dwLowDateTime;
	kTime.HighPart = kernelTime1.dwHighDateTime;
	uTime.LowPart = userTime1.dwLowDateTime;
	uTime.HighPart = userTime1.dwHighDateTime;

	cpuStr.Format(_T("Kernel Time: %I64u ms\nUser Time: %I64u ms"),
		kTime.QuadPart / 10000,
		uTime.QuadPart / 10000);

	b_Time3.AddString(cpuStr);
}

void Clab1OSDlg::OnBnClickedButtonTerminateThread()
{
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	CloseHandle(hThread3);

	progres_1.SetPos(0);
	progres_2.SetPos(0);
	progres_3.SetPos(0);

	for (int i = 0; i <= 1; i++)
	{
		b_Time1.DeleteString(0);
		b_Time2.DeleteString(0);
		b_Time3.DeleteString(0);
	}
}

void Clab1OSDlg::OnNMCustomdrawProgress8(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void Clab1OSDlg::OnBnClickedButton11()
{
	CONTEXT ctx;
	ctx.ContextFlags = CONTEXT_FULL;
	GetThreadContext(hThread1, &ctx);
	int priority_s = GetThreadPriority(hThread1);

	CString str;

	for (int i = 0; i < 45; i++)
	{
		m_CONTEX_WORK.DeleteString(0);
	}

	m_CONTEX_WORK.AddString(_T("--------Thread-1--------"));

	str.Format(_T("Priority = %i\n"), priority_s);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("ContextFlags = 0x%08X\n"), ctx.ContextFlags);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("EFlags = 0x%08X\n"), ctx.EFlags);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegGs = 0x%08X\n"), ctx.SegGs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegFs = 0x%08X\n"), ctx.SegFs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegEs = 0x%08X\n"), ctx.SegEs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegDs = 0x%08X\n"), ctx.SegDs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegSs = 0x%08X\n"), ctx.SegSs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR0 = 0x%08X\n"), ctx.Dr0);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("nDR1 = 0x%08X\n"), ctx.Dr1);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR2 = 0x%08X\n"), ctx.Dr1);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR3 = 0x%08X\n"), ctx.Dr3);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR6 = 0x%08X\n"), ctx.Dr6);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR7 = 0x%08X\n"), ctx.Dr7);
	m_CONTEX_WORK.AddString(str);

	m_CONTEX_WORK.AddString(_T("--------Thread-2--------"));
	
	priority_s = GetThreadPriority(hThread2);
	GetThreadContext(hThread2, &ctx);

	str.Format(_T("Priority = %i\n"), priority_s);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("ContextFlags = 0x%08X\n"), ctx.ContextFlags);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("EFlags = 0x%08X\n"), ctx.EFlags);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegGs = 0x%08X\n"), ctx.SegGs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegFs = 0x%08X\n"), ctx.SegFs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegEs = 0x%08X\n"), ctx.SegEs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegDs = 0x%08X\n"), ctx.SegDs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegSs = 0x%08X\n"), ctx.SegSs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR0 = 0x%08X\n"), ctx.Dr0);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("nDR1 = 0x%08X\n"), ctx.Dr1);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR2 = 0x%08X\n"), ctx.Dr1);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR3 = 0x%08X\n"), ctx.Dr3);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR6 = 0x%08X\n"), ctx.Dr6);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR7 = 0x%08X\n"), ctx.Dr7);
	m_CONTEX_WORK.AddString(str);

	m_CONTEX_WORK.AddString(_T("--------Thread-3--------"));

	priority_s = GetThreadPriority(hThread3);
	GetThreadContext(hThread3, &ctx);
	str.Format(_T("Priority = %i\n"), priority_s);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("ContextFlags = 0x%08X\n"), ctx.ContextFlags);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("EFlags = 0x%08X\n"), ctx.EFlags);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegGs = 0x%08X\n"), ctx.SegGs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegFs = 0x%08X\n"), ctx.SegFs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegEs = 0x%08X\n"), ctx.SegEs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegDs = 0x%08X\n"), ctx.SegDs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("SegSs = 0x%08X\n"), ctx.SegSs);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR0 = 0x%08X\n"), ctx.Dr0);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("nDR1 = 0x%08X\n"), ctx.Dr1);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR2 = 0x%08X\n"), ctx.Dr1);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR3 = 0x%08X\n"), ctx.Dr3);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR6 = 0x%08X\n"), ctx.Dr6);
	m_CONTEX_WORK.AddString(str);
	str.Format(_T("DR7 = 0x%08X\n"), ctx.Dr7);
	m_CONTEX_WORK.AddString(str);

}

void Clab1OSDlg::OnLbnSelchangeList5()
{
	// TODO: Add your control notification handler code here
}



void Clab1OSDlg::OnLbnSelchangeList6()
{
	// TODO: Add your control notification handler code here
}

void Clab1OSDlg::OnLbnSelchangeList13()
{
	// TODO: Add your control notification handler code here
}

void Clab1OSDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}

void Clab1OSDlg::OnBnClickedButton6()
{
	UpdateData(TRUE);
	int sel = Drop_List.GetCurSel();
	int priority = THREAD_PRIORITY_NORMAL;

	if (sel == 0) priority = THREAD_PRIORITY_HIGHEST;
	else if (sel == 2) priority = THREAD_PRIORITY_LOWEST;

	switch (m_selectedThread)
	{
	case 0: SetThreadPriority(hThread1, priority); break;
	case 1: SetThreadPriority(hThread2, priority); break;
	case 2: SetThreadPriority(hThread3, priority); break;
	}
}

void Clab1OSDlg::OnBnClickedButton7()
{
	// It's start
	switch (m_selectedThread)
	{
	case 0: ResumeThread(hThread1); break;
	case 1: ResumeThread(hThread2); break;
	case 2: ResumeThread(hThread3); break;
	}
}

void Clab1OSDlg::OnBnClickedRadio1()
{
	m_selectedThread = 0;
}

void Clab1OSDlg::OnBnClickedRadio2()
{
	m_selectedThread = 1;
}

void Clab1OSDlg::OnBnClickedRadio3()
{
	m_selectedThread = 2;
}

void Clab1OSDlg::OnBnClickedButton8()
{
	// Ti's stap
	switch (m_selectedThread)
	{
	case 0: SuspendThread(hThread1); break;
	case 1: SuspendThread(hThread2); break;
	case 2: SuspendThread(hThread3); break;
	}
}
