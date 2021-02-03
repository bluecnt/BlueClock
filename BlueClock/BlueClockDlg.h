
// BlueClockDlg.h : header file
//

#pragma once


// CBlueClockDlg dialog
class CBlueClockDlg : public CDialogEx
{
// Construction
public:
	CBlueClockDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLUECLOCK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
	enum class ESide
	{
		Left			= 0x0001,
		Center			= 0x0002,
		Right			= 0x0004,
		Top				= 0x0010,
		Middle			= 0x0020,
		Bottom			= 0x0040,
		//
		LeftTop			= Left | Top,
		LeftMiddle		= Left | Middle,
		LeftBottom		= Left | Bottom,
		CenterTop		= Center | Top,
		CenterMIddle	= Center | Middle,
		CenterBottom	= Center | Bottom,
		RightTop		= Right | Top,
		RightMiddle		= Right | Middle,
		RightBottom		= Right | Bottom,

		//
		Count,
		None = -1,
	};

private:
	void move_window(ESide side, LPWINDOWPOS lpwndpos = nullptr);
	void size_window(int width, int height);
};

int bl_printf(LPCTSTR format, ...);