
// BlueClockDlg.h : header file
//

#pragma once

#include "blue/inc/mfc/BlueWndUtils.h"
#include "components/ComponentManager.h"


#if 0
#define COMPONENT_WIDTH		160
#define COMPONENT_HEIGHT	80
#define COMPONENT_COUNT		4
#define COMPONENT_MARGIN	10

#define VIEW_BORDER			1
#define VIEW_WIDTH			(COMPONENT_WIDTH + VIEW_BORDER * 2)
#define VIEW_HEIGHT			(COMPONENT_HEIGHT * COMPONENT_COUNT + VIEW_BORDER * 2)
#endif

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

	blue::mfc::CWndUtils	mWndUtils;
	blue::mfc::CCanvas		mBackBuffer;

#if 0
	blue::mfc::CCanvas		mDateCanvas;
	blue::mfc::CCanvas		mTimeCanvas;
	blue::mfc::CCanvas		mWeekCanvas;
	blue::mfc::CCanvas		mDayCanvas;
#endif

	CComponentManager		mComponentMngr;

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
	afx_msg void OnClose();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnNcHitTest(CPoint point);

#if 0
	void create_components();
	void destroy_components();
	void update_components();
	void display_components();

	void update_date_component();
	void update_time_component();
	void update_week_component();
	void update_day_component();
#endif
};