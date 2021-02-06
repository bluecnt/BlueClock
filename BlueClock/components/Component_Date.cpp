// [SGLEE:20210203WED_213900] 최초 작성

#include "pch.h"
#include "Component_Date.h"

CComponent_Date::CComponent_Date()
{
    //
}
CComponent_Date::~CComponent_Date()
{
    //
}

int CComponent_Date::Create()
{
    CComponent::Create();

    return 0;
}
void CComponent_Date::Destroy()
{
    CComponent::Destroy();

    //
}

void CComponent_Date::Update()
{
#if 0
    CComponent::Update();

    return;
#endif

//#define __WHITE_ITEM_BKGND

    LPCTSTR WeekNames[] =
    {
        _T("Sunday"), _T("Monday"), _T("Tuesday"), _T("Wednesday"), _T("Thursday"), _T("Friday"), _T("Satrueday")
    };
    LPCTSTR WeekNames2[] =
    {
        _T("SUN"), _T("MON"), _T("TUE"), _T("WED"), _T("THU"), _T("FRI"), _T("SAT")
    };

    SYSTEMTIME st = { 0 };
    GetLocalTime(&st);

#if 0
    int day_of_week = st.wDayOfWeek;
    int hour = st.wHour;
#else
    int day_of_week = 3;
    int hour = 7;
#endif

    CRect view_rc = GetViewRect();
    CRect view_rc2 = GetViewRect(true);

    GetCanvasPtr()->FillRect(&view_rc, GetBkgndColor());
#if 0
    GetCanvasPtr()->FillRect(&view_rc2, RGB(255, 255, 255));
#endif

    int date_y  = GetMargin();
    int date_b  = date_y + GetTextHeight();

    int day_bar_y  = GetItemMargin() + date_b;
    int day_bar_b  = day_bar_y + GetProgressBarHeight();

    CRect rc;

    // Date

    rc = view_rc2;
    rc.top      = date_y;
    rc.bottom   = date_b;
#ifdef __WHITE_ITEM_BKGND
    GetCanvasPtr()->FillRect(&rc, RGB(255,255,255));
#endif

    GetCanvasPtr()->SetFont(GetFontName(), GetFontSize());
    GetCanvasPtr()->DrawStringCenterMiddle(&rc, GetTextColor(), _T("%04d.%02d.%02d.%s"),
        st.wYear, st.wMonth, st.wDay, WeekNames2[day_of_week]);

    // Day bar

    rc.top      = day_bar_y;
    rc.bottom   = day_bar_b;
#ifdef __WHITE_ITEM_BKGND
    GetCanvasPtr()->FillRect(&rc, RGB(255,255,255));
#endif

    auto items = blue::mfc::CCanvas::CalcRects(rc.Width(), rc.Height(), 7, 1);
    CRect rc2 = rc;

    rc2.right = rc.left + items[day_of_week].right;
    GetCanvasPtr()->FillRect(&rc2, GetBkgndColor2());

    GetCanvasPtr()->SetFont(GetFontName2(), GetFontSize2());

    int idx = 0;
    for (auto& i : items)
    {
        rc2 = i;
        rc2.OffsetRect(rc.left, rc.top);

#if 1
        if (idx == day_of_week)
            GetCanvasPtr()->FillRect(&rc2, GetBkgndColor3());
#endif

        COLORREF fc = GetTextColor2();
        if (idx == 0)
            fc = RGB(255, 0, 0);
        else if (idx == 6)
            fc = RGB(0, 0, 255);

        GetCanvasPtr()->DrawStringCenterMiddle(&rc2, fc, WeekNames2[idx++]);
    }
}

int CComponent_Date::GetWidth(bool margin /*= false*/) const
{
    return CComponent::GetWidth(margin);
}
int CComponent_Date::GetHeight(bool margin /*= false*/) const
{
    int h =
        (!margin ? GetMargin() : 0) +
        // Date
        GetTextHeight() +
        //
        GetItemMargin() +
        // Day bar
        GetProgressBarHeight() +
        //
        (!margin ? GetMargin() : 0);
    //
    return h;
}

int CComponent_Date::GetTextHeight() const
{
    int h = (int)(GetFontSize() * 2.0 + 0.5);
    //
    return h;
}
int CComponent_Date::GetProgressBarHeight() const
{
    return 20;
}
