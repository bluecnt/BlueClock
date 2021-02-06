
// BlueClockDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "BlueClock.h"
#include "BlueClockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#if 0
# include <mmsystem.h>
# pragma comment(lib, "winmm.lib")
#endif

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
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CBlueClockDlg dialog



CBlueClockDlg::CBlueClockDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BLUECLOCK_DIALOG, pParent), mWndUtils(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBlueClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBlueClockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_WM_KEYDOWN()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CBlueClockDlg message handlers


int64_t bl_get_curr_usec(bool utc = false)
{
	int64_t usec = 0;

#ifdef _WIN32

	FILETIME ft = { 0 };
	int64_t t = 0;

	// 1601.01.01.MON 기준으로 100ns(1/10,000,000)
	GetSystemTimeAsFileTime(&ft);

	if (!utc)
		FileTimeToLocalFileTime(&ft, &ft);

#if 0
	SYSTEMTIME st = { 0 };
	FileTimeToSystemTime(&ft, &st);
#endif

	t = (int64_t)ft.dwHighDateTime << 32 | ft.dwLowDateTime;
	// 1970.01.01.THU 기준으로 변환
	usec = t / 10 - 11644473600000000; /* Jan 1, 1601 */

#elif __linux__

	timeval tv = { 0 };

	gettimeofday(&tv, NULL);
	usec = (int64_t)tv.tv_sec * MicroSecond + tv.tv_usec;

	if (!utc)
	{
		tm* tm = localtime(&tv.tv_sec);
		usec += tm->tm_gmtoff * MicroSecond;
	}

#endif

	return usec;
}


BOOL CBlueClockDlg::OnInitDialog()
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

	// TODO: Add extra initialization here

	SetWindowText(_T("BLUECNT BlueClock v0.1"));
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW | WS_EX_TOPMOST);

	mComponentMngr.Load();
	mComponentMngr.Create();

	mWndUtils.SetWndPtr(this);
	mWndUtils.Size(mComponentMngr.GetWidth(), mComponentMngr.GetHeight());
	mWndUtils.Move(BL_MFC_WND_SIDE_RIGHT_TOP);
	mWndUtils.SetTopmost(true);

	CRect rc;
	GetClientRect(&rc);
	mBackBuffer.Create(rc.Width(), rc.Height());

	SetTimer(1, 100, NULL);


#if 0
	timeBeginPeriod(1);

	vector<double> vt;
    for (int i = 0; i < 10; i++)
    {
        int64_t start = bl_get_curr_usec();

        Sleep(10);

        double delta = (bl_get_curr_usec() - start) / 1000000.0;

		vt.push_back(delta);
    }

	int a = 0;
#endif

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CBlueClockDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			PostMessage(WM_CLOSE);

			return TRUE;
		}
		else if (pMsg->wParam == VK_RETURN)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CBlueClockDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBlueClockDlg::OnPaint()
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

		CClientDC dc(this);

		mComponentMngr.Update();
		mComponentMngr.Display(&mBackBuffer);

		mBackBuffer.Display(&dc);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBlueClockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBlueClockDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanging(lpwndpos);

	mWndUtils.Move(BL_MFC_WND_SIDE_NONE, lpwndpos);
}

void CBlueClockDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);

	if (nIDEvent == 1)
	{
		Invalidate();
	}
}
BOOL CBlueClockDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CDialogEx::OnEraseBkgnd(pDC);
	return TRUE;
}

void CBlueClockDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CString s = _T("Exit?");

	int ret = AfxMessageBox(s, MB_ICONQUESTION | MB_YESNO);
	if (ret == IDYES)
	{
		CDialogEx::OnClose();

		KillTimer(1);
		mComponentMngr.Destroy();
		mBackBuffer.Destroy();
	}
}


void CBlueClockDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);

	switch (nChar)
	{
		case VK_NUMPAD7: mWndUtils.Move(BL_MFC_WND_SIDE_LEFT_TOP); break;
		case VK_NUMPAD8: mWndUtils.Move(BL_MFC_WND_SIDE_CENTER_TOP); break;
		case VK_NUMPAD9: mWndUtils.Move(BL_MFC_WND_SIDE_RIGHT_TOP); break;
		case VK_NUMPAD4: mWndUtils.Move(BL_MFC_WND_SIDE_LEFT_MIDDLE); break;
		case VK_NUMPAD5: mWndUtils.Move(BL_MFC_WND_SIDE_CENTER_MIDDLE); break;
		case VK_NUMPAD6: mWndUtils.Move(BL_MFC_WND_SIDE_RIGHT_MIDDLE); break;
		case VK_NUMPAD1: mWndUtils.Move(BL_MFC_WND_SIDE_LEFT_BOTTOM); break;
		case VK_NUMPAD2: mWndUtils.Move(BL_MFC_WND_SIDE_CENTER_BOTTOM); break;
		case VK_NUMPAD3: mWndUtils.Move(BL_MFC_WND_SIDE_RIGHT_BOTTOM); break;
	}
}


LRESULT CBlueClockDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//return CDialogEx::OnNcHitTest(point);
	return HTCAPTION;
}