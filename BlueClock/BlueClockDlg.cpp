
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
	: CDialogEx(IDD_BLUECLOCK_DIALOG, pParent)
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
END_MESSAGE_MAP()


// CBlueClockDlg message handlers

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
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	SetWindowText(_T("BLUECNT BlueClock v0.1"));
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	
	size_window(200, 240);
	//move_window(ESide::LeftTop);
	move_window(ESide::RightTop);
	//move_window(ESide::LeftBottom);
	//move_window(ESide::RightBottom);

	SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CBlueClockDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
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
		CRect rc;
		CDC mem_dc;
		CBitmap mem_bmp;
		CBitmap* old_bmp_ptr = nullptr;

		GetClientRect(&rc);
		mem_dc.CreateCompatibleDC(&dc);
		mem_bmp.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
		old_bmp_ptr = mem_dc.SelectObject(&mem_bmp);

		CBrush br;
		CFont fnt;
		CFont* old_fnt_ptr = nullptr;

		br.CreateSolidBrush(RGB(0x99, 0xcc, 0xff));
		mem_dc.FillRect(&rc, &br);

		fnt.CreatePointFont(28 * 10, _T("¸¼Àº °íµñ"));
		old_fnt_ptr = mem_dc.SelectObject(&fnt);

		CString s;
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
#if 0
		s.Format(_T("%02d:%02d:%02d.%03d"), st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#else
		s.Format(_T("%02d:%02d:%02d"), st.wHour, st.wMinute, st.wSecond);
#endif
		mem_dc.SetBkMode(TRANSPARENT);
		mem_dc.SetTextColor(RGB(0x00, 0x00, 0xff));
		mem_dc.DrawText(s, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		dc.BitBlt(0, 0, rc.Width(), rc.Height(), &mem_dc, 0, 0, SRCCOPY);

		mem_dc.SelectObject(old_fnt_ptr);
		mem_dc.SelectObject(old_bmp_ptr);
		mem_dc.DeleteDC();
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

	move_window(ESide::None, lpwndpos);
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

int bl_printf(LPCTSTR format, ...)
{
	TCHAR buf[1024] = { 0 };
	va_list ap;

	va_start(ap, format);
	_vstprintf_s(buf, format, ap);
	va_end(ap);

	::OutputDebugString(buf);

	return lstrlen(buf);
}

void CBlueClockDlg::move_window(ESide side, LPWINDOWPOS lpwndpos /*= nullptr*/)
{
#if 0
	if (lpwndpos)
		bl_printf(_T("[%4d:%s()] wx: %4d, wy: %4d <INFORMATION> \n"), __LINE__, _T(__FUNCTION__),
			lpwndpos->x, lpwndpos->y);
#endif

	CRect desktop_rc;
	CRect wnd_rc;

	SystemParametersInfo(SPI_GETWORKAREA, 0, &desktop_rc, 0);
	GetWindowRect(&wnd_rc);

	const int InvisibleBorderSize = 8;
	desktop_rc.InflateRect(InvisibleBorderSize, 0);
	desktop_rc.bottom += InvisibleBorderSize;

	int x = 0;
	int y = 0;

	if (side != ESide::None)
	{
		if ((int)side & (int)ESide::Left)
			x = desktop_rc.left;
		else if ((int)side & (int)ESide::Center)
			x = (desktop_rc.right - wnd_rc.right) / 2;
		else if ((int)side & (int)ESide::Right)
			x = desktop_rc.right - wnd_rc.right;

		if ((int)side & (int)ESide::Top)
			y = desktop_rc.top;
		else if ((int)side & (int)ESide::Middle)
			y = (desktop_rc.bottom - wnd_rc.bottom) / 2;
		else if ((int)side & (int)ESide::Bottom)
			y = desktop_rc.bottom - wnd_rc.bottom;

		SetWindowPos(&CWnd::wndNoTopMost, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}
	else if (lpwndpos)
	{
		const int MagneticDistance = 10;
		int wx = lpwndpos ? lpwndpos->x : 0;
		int wy = lpwndpos ? lpwndpos->y : 0;
		int wr = lpwndpos ? wx + lpwndpos->cx : 0;
		int wb = lpwndpos ? wy + lpwndpos->cy : 0;

		if (wx <= MagneticDistance && wx >= -MagneticDistance)
			x = desktop_rc.left;
		else if (wr <= desktop_rc.right + MagneticDistance && wr >= desktop_rc.right - MagneticDistance)
			x = desktop_rc.right - wnd_rc.Width();
		else
			x = lpwndpos->x;

		if ((side != ESide::None && (int)side & (int)ESide::Top) ||
			(lpwndpos && wy <= MagneticDistance && wy >= -MagneticDistance))
			y = desktop_rc.top;
		else if (wb <= desktop_rc.bottom + MagneticDistance && wb >= desktop_rc.bottom - MagneticDistance)
			y = desktop_rc.bottom - wnd_rc.Height();
		else
			y = lpwndpos->y;

		lpwndpos->x = x;
		lpwndpos->y = y;
	}

#if 0
	bl_printf(_T("[%4d:%s()] nx: %4d, ny: %4d \n"), __LINE__, _T(__FUNCTION__), x, y);
#endif
}

void CBlueClockDlg::size_window(int width, int height)
{
	CRect wnd_rc = { 0 };
	GetWindowRect(&wnd_rc);

	int w = width > 0 ? width : wnd_rc.Width();
	int h = height > 0 ? height : wnd_rc.Height();

	SetWindowPos(&CWnd::wndNoTopMost, 0, 0, w, h, SWP_NOZORDER | SWP_NOMOVE);
}