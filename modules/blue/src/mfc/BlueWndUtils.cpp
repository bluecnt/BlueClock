// [SGLEE:20210203WED_152900] 최초 작성

#include "pch.h"
#include "../../inc/mfc/BlueWndUtils.h"

ns_begin_blue_mfc

CWndUtils::CWndUtils(CWnd* wndPtr)
{
    mWndPtr = wndPtr;
}
CWndUtils::~CWndUtils()
{
}

void CWndUtils::SetWndPtr(CWnd* wndPtr)
{
    mWndPtr = wndPtr;
}

int CWndUtils::Move(ESide side, LPWINDOWPOS lpwndpos /*= nullptr*/)
{
    if (!mWndPtr)
        return -10;

#if 0
    if (lpwndpos)
        bl_printf(_T("[%4d:%s()] wx: %4d, wy: %4d <INFORMATION> \n"), __LINE__, _T(__FUNCTION__),
            lpwndpos->x, lpwndpos->y);
#endif

    CRect desktop_rc;
    CRect wnd_rc;

    SystemParametersInfo(SPI_GETWORKAREA, 0, &desktop_rc, 0);
    mWndPtr->GetWindowRect(&wnd_rc);

    if (mWndPtr->GetStyle() & WS_BORDER)
    {
        const int InvisibleBorderSize = 8;
        desktop_rc.InflateRect(InvisibleBorderSize, 0);
        desktop_rc.bottom += InvisibleBorderSize;
    }

#if 0
    bl_printf(_T("desktop_rc = { %4d, %4d, %4d, %4d }, wnd_rc = { %4d, %4d, %4d, %4d } \n"),
        desktop_rc.left, desktop_rc.top, desktop_rc.right, desktop_rc.bottom,
        wnd_rc.left, wnd_rc.top, wnd_rc.right, wnd_rc.bottom);
#endif

    int x = 0;
    int y = 0;

    if (side != ESide::None)
    {
        if ((int)side & (int)ESide::Left)
            x = desktop_rc.left;
        else if ((int)side & (int)ESide::Center)
            x = (desktop_rc.Width() - wnd_rc.Width()) / 2;
        else if ((int)side & (int)ESide::Right)
            x = desktop_rc.right - wnd_rc.Width();

        if ((int)side & (int)ESide::Top)
            y = desktop_rc.top;
        else if ((int)side & (int)ESide::Middle)
            y = (desktop_rc.Height() - wnd_rc.Height()) / 2;
        else if ((int)side & (int)ESide::Bottom)
            y = desktop_rc.bottom - wnd_rc.Height();

        mWndPtr->SetWindowPos(&CWnd::wndNoTopMost, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
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


    return 0;
}
int CWndUtils::Size(int width, int height)
{
    if (!mWndPtr)
        return -10;

    CRect wnd_rc = { 0 };
    mWndPtr->GetWindowRect(&wnd_rc);

    int w = width > 0 ? width : wnd_rc.Width();
    int h = height > 0 ? height : wnd_rc.Height();

    mWndPtr->SetWindowPos(&CWnd::wndNoTopMost, 0, 0, w, h, SWP_NOZORDER | SWP_NOMOVE);

    return 0;
}
int CWndUtils::SetTopmost(bool flag)
{
    if (!mWndPtr)
        return -10;

    mTopmost = flag;

    mWndPtr->SetWindowPos(mTopmost ? &CWnd::wndTopMost : &CWnd::wndNoTopMost, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE);

    return 0;
}
int CWndUtils::ToggleTopmost()
{
    return SetTopmost(!IsTopmost());
}

bool CWndUtils::IsTopmost() const
{
    return mTopmost;
}

int CWndUtils::printf(LPCTSTR format, ...)
{
    TCHAR buf[1024] = { 0 };
    TCHAR buf2[1024] = { 0 };
    TCHAR time[32] = { 0 };
    SYSTEMTIME st = { 0 };
    va_list ap;

    va_start(ap, format);
    _vstprintf_s(buf, format, ap);
    va_end(ap);

    GetLocalTime(&st);
    _stprintf_s(time, _T("%02d:%02d:%02d.%03d"),
        st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    _stprintf_s(buf2, _T("[%s] %s"), time, buf);

    ::OutputDebugString(buf2);

    return lstrlen(buf);
}

ns_end_blue_mfc