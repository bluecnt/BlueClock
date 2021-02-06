// [SGLEE:20210204THU_000300] 최초 작성

#include "pch.h"
#include "Component_Time.h"

CComponent_Time::CComponent_Time()
{
    //
}
CComponent_Time::~CComponent_Time()
{
    //
}

int CComponent_Time::Create()
{
    CComponent::Create();

    return 0;
}
void CComponent_Time::Destroy()
{
    CComponent::Destroy();

    //
}

void CComponent_Time::Update()
{
#if 0
    CComponent::Update();

    return;
#endif

//#define __WHITE_ITEM_BKGND

    SYSTEMTIME st = { 0 };
    GetLocalTime(&st);

#if 1
    int day_of_week = st.wDayOfWeek;
    int hour        = st.wHour;
    int minute      = st.wMinute;
    int second      = st.wSecond;
#else
    int day_of_week = 3;
    int hour        = 12;
    int minute      = 30;
    int second      = 30;
#endif

    CRect view_rc = GetViewRect();
    CRect view_rc2 = GetViewRect(true);

    GetCanvasPtr()->FillRect(&view_rc, GetBkgndColor());
#if 0
    GetCanvasPtr()->FillRect(&view_rc2, RGB(255, 255, 255));
#endif

    int time_y          = GetMargin();
    int time_b          = time_y + GetTextHeight();

    int hour_prog_bar_y = time_b + GetItemMargin();
    int hour_prog_bar_b = hour_prog_bar_y + GetProgressBarTextHeight() + GetProgressBarHeight();

    int min_prog_bar_y  = hour_prog_bar_b + GetItemMargin();
    int min_prog_bar_b  = min_prog_bar_y + GetProgressBarTextHeight() + GetProgressBarHeight();

    //int min_prog_y      = 0;

    CRect rc;

    // Time

    rc = view_rc2;
    rc.top      = time_y;
    rc.bottom   = time_b;
#ifdef __WHITE_ITEM_BKGND
    GetCanvasPtr()->FillRect(&rc, RGB(255,255,255));
#endif

    GetCanvasPtr()->SetFont(GetFontName(), GetFontSize());
#if 1
    GetCanvasPtr()->DrawStringCenterMiddle(&rc, GetTextColor(), _T("%02d:%02d:%02d"),
        hour, minute, st.wSecond);
#else
    GetCanvasPtr()->DrawStringCenterMiddle(&rc, GetTextColor(), _T("%02d:%02d:%02d.%03d"),
        hour, minute, st.wSecond, st.wMilliseconds);
#endif

    // Hour progress bar

    rc = view_rc2;
    rc.top      = hour_prog_bar_y;
    rc.bottom   = hour_prog_bar_b;
#ifdef __WHITE_ITEM_BKGND
    GetCanvasPtr()->FillRect(&rc, RGB(255,255,255));
#else
    {
        CRect rc2 = rc;
        rc2.top += GetProgressBarTextHeight();
        GetCanvasPtr()->FillRect(&rc2, GetBkgndColor2());
    }
#endif

    auto items = blue::mfc::CCanvas::CalcRects(rc.Width(), rc.Height(), 24, 1);

#if 0
    int hours[] = { 0, 3, 6, 9, 12, 15, 18, 21 };
#else
    int hours[] = { 0, 2, 6, 9, 12, 18, 21 };
#endif
    int idx = 0;
    GetCanvasPtr()->SetFont(GetFontName2(), GetFontSize2());
    for (const auto& i : items)
    {
        CRect rc2 = i;
        rc2.OffsetRect(rc.left, rc.top);

        bool hour_set = false;
        for (auto j : hours)
        {
            if (j == idx)
            {
                GetCanvasPtr()->DrawString(rc2.left, rc2.top, GetTextColor2(), _T("%02d"), j);
                hour_set = true;

                break;
            }
        }

        if (idx < hour)
        {
            CRect rc3 = rc2;
            rc3.top += GetProgressBarTextHeight();
            GetCanvasPtr()->FillRect(&rc3, GetBkgndColor3());
        }

        if (idx == hour)
        {
            CRect rc3 = rc2;
            rc3.top     += GetProgressBarTextHeight();
            rc3.right   = rc2.left + (int)((minute * (double)rc2.Width() / 60) + 0.5);
            GetCanvasPtr()->FillRect(&rc3, GetBkgndColor3());
        }

        CRect rc3 = rc2;
        rc3.top     += GetProgressBarTextHeight();
        rc3.right   = rc3.left + 1;
        if (!hour_set)
            rc3.bottom  = rc3.top + 4;
        GetCanvasPtr()->FrameRect(&rc3, GetTextColor2());

        idx++;
    }

    // Minute progress bar

    rc = view_rc2;
    rc.top      = min_prog_bar_y;
    rc.bottom   = min_prog_bar_b;
#ifdef __WHITE_ITEM_BKGND
    GetCanvasPtr()->FillRect(&rc, RGB(255,255,255));
#else
    {
        CRect rc2 = rc;
        rc2.top += GetProgressBarTextHeight();
        GetCanvasPtr()->FillRect(&rc2, GetBkgndColor2());
    }
#endif

    items = blue::mfc::CCanvas::CalcRects(rc.Width(), rc.Height(), 60, 1);

#if 1
    int minutes[] = { 0, 15, 30, 45 };
#else
int minutes[] = { 0, 10, 20, 30, 40, 50 };
#endif
    idx = 0;
    GetCanvasPtr()->SetFont(GetFontName2(), GetFontSize2());
    for (const auto& i : items)
    {
        CRect rc2 = i;
        rc2.OffsetRect(rc.left, rc.top);

        bool min_set = false;
        for (auto j : minutes)
        {
            if (j == idx)
            {
                GetCanvasPtr()->DrawString(rc2.left, rc2.top, GetTextColor2(), _T("%02d"), j);
                min_set = true;

                break;
            }
        }

        if (idx < minute)
        {
            CRect rc3 = rc2;
            rc3.top += GetProgressBarTextHeight();
            GetCanvasPtr()->FillRect(&rc3, GetBkgndColor3());
        }

        if (idx == minute)
        {
            CRect rc3 = rc2;
            rc3.top     += GetProgressBarTextHeight();
            rc3.right   = rc2.left + (int)((second * ((double)rc2.Width()) / 60) + 0.5);
            GetCanvasPtr()->FillRect(&rc3, GetBkgndColor3());
        }

        CRect rc3 = rc2;
        rc3.top     += GetProgressBarTextHeight();
        rc3.right   = rc3.left + 1;
        if (!min_set)
            rc3.bottom  = rc3.top + 4;
        GetCanvasPtr()->FrameRect(&rc3, GetTextColor2());

        idx++;
    }
}

int CComponent_Time::GetWidth(bool margin) const
{
    return CComponent::GetWidth(margin);
}
int CComponent_Time::GetHeight(bool margin) const
{
    int h =
        (!margin ? GetMargin() : 0) +
        // Time
        GetTextHeight() +
        //
        GetItemMargin() +
        // Hour progress bar
        GetProgressBarTextHeight() +
        GetProgressBarHeight() +
        //
        GetItemMargin() +
        // Minute progress bar
        GetProgressBarTextHeight() +
        GetProgressBarHeight() +
        //
        (!margin ? GetMargin() : 0);
    //
    return h;
}

int CComponent_Time::GetTextHeight() const
{
    int h = (int)(GetFontSize() * 2.0 + 0.5);
    //
    return h;
}
int CComponent_Time::GetProgressBarTextHeight() const
{
    return 14;
}
int CComponent_Time::GetProgressBarHeight() const
{
    return 14;
}
