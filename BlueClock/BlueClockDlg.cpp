
// BlueClockDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "BlueClock.h"
#include "BlueClockDlg.h"
#include "afxdialogex.h"

#include "components/Component_Title.h"
#include "components/Component_Date.h"
#include "components/Component_Time.h"

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

	CComponent::CInitParams init_params;

	auto comp_title_sp	= make_shared<CComponent_Title>();
	auto comp_date_sp	= make_shared<CComponent_Date>();
	auto comp_time_sp	= make_shared<CComponent_Time>();

#if 0
	init_params.mName			= _T("BlueClock v0.1");
	init_params.mHeight			= 60;
	init_params.mBkgndColor		= RGB(0xeb, 0xf1, 0xdd);
	init_params.mTextColor		= RGB(0x4f, 0x61, 0x28);
	init_params.mBkgndColor2	= RGB(0xd7, 0xe3, 0xbc);
	init_params.mBkgndColor3	= RGB(0xc3, 0xd6, 0x9b);
	init_params.mTextColor2		= RGB(0x76, 0x92, 0x3c);
	comp_title_sp->Init(init_params);
	mComponentMngr.Add(comp_title_sp);
#endif

	init_params.mName			= _T("Date");
	init_params.mHeight			= 80;
	init_params.mBkgndColor		= RGB(0xdb, 0xee, 0xf3);
	init_params.mTextColor		= RGB(0x20, 0x58, 0x67);
	init_params.mBkgndColor2	= RGB(0xb7, 0xdd, 0xe8);
	init_params.mBkgndColor3	= RGB(0x92, 0xcd, 0xdc);
	init_params.mTextColor2		= RGB(0x31, 0x85, 0x9b);
	comp_date_sp->Init(init_params);
	mComponentMngr.Add(comp_date_sp);

	init_params.mName			= _T("Time");
	init_params.mHeight			= 100;
	init_params.mBkgndColor		= RGB(0xc6, 0xd9, 0xf0);
	init_params.mTextColor		= RGB(0x0f, 0x24, 0x3e);
	init_params.mBkgndColor2	= RGB(0x8d, 0xb3, 0xe2);
	init_params.mBkgndColor3	= RGB(0x54, 0x8d, 0xd4);
	init_params.mTextColor2		= RGB(0x17, 0x36, 0x5d);
	comp_time_sp->Init(init_params);
	mComponentMngr.Add(comp_time_sp);

	mComponentMngr.Create();

	mWndUtils.SetWndPtr(this);
	mWndUtils.Size(mComponentMngr.GetWidth(), mComponentMngr.GetHeight());
	mWndUtils.Move(BL_MFC_WND_SIDE_RIGHT_TOP);
	mWndUtils.SetTopmost(true);

	CRect rc;
	GetClientRect(&rc);
	mBackBuffer.Create(rc.Width(), rc.Height());

	SetTimer(1, 100, NULL);

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