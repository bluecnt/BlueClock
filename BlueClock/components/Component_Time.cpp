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

    const int ProgresssBarHeight = 14;

    SYSTEMTIME st = { 0 };
    GetLocalTime(&st);

#if 1
    int day_of_week = st.wDayOfWeek;
    int hour = st.wHour;
    int minute = st.wMinute;
#else
    int day_of_week = 4;
    int hour = 6;
    int minute = 15;
#endif

    CRect view_rc = GetViewRect();
    CRect view_rc2 = GetViewRect(true);

    GetCanvasPtr()->FillRect(&view_rc, GetBkgndColor());
#if 0
    GetCanvasPtr()->FillRect(&view_rc2, RGB(255, 255, 255));
#endif

    // 시간

    GetCanvasPtr()->SetFont(_T("맑은 고딕"), 24);
    blue::mfc::CCanvas::CDrawStringParams ds_params;
    ds_params.mForeColor = GetTextColor();
    ds_params.mFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
    ds_params.mY = GetMargin();
    ds_params.mHeight = GetHeight(true) / 2;
#if 1
    GetCanvasPtr()->DrawStringParams(ds_params, _T("%02d:%02d:%02d"), hour, minute, st.wSecond);
#else
    GetCanvasPtr()->DrawStringParams(ds_params, _T("%02d:%02d:%02d.%03d"),
        hour, minute, st.wSecond, st.wMilliseconds);
#endif

    // 프로그레스 바

    CRect rc;
    rc.left     = GetMargin();
    rc.top      = GetMargin();
    rc.right    = rc.left + (int)((hour + 1) * view_rc2.Width() / 24.0 + 0.5);
    rc.bottom   = rc.top + ProgresssBarHeight;
    rc.OffsetRect(0, view_rc2.Height() - ProgresssBarHeight);
    GetCanvasPtr()->FillRect(&rc, GetBkgndColor2());

#if 0
    rc.left     = GetMargin() + (int)(hour * view_rc2.Width() / 24.0 + 0.5);
    rc.right    = rc.left + (int)(minute * (view_rc2.Width() / 24.0) / 60.0 + 0.5);
#else
    rc.left     = GetMargin();
    rc.right    = rc.left + (int)(hour * view_rc2.Width() / 24.0 + 0.5) +
                    (int)((minute+1) * (view_rc2.Width() / 24.0 + 0.5) / 60.0 + 0.5);
#endif
    //GetCanvasPtr()->FillRect(&rc, GetBkgndColor3());
    rc.top += 4;
    GetCanvasPtr()->FillRect(&rc, GetTextColor2());

    rc.top -= 4;
    int hours[] = { 0, 2, 6, 9, 12, 18, 21 };
    GetCanvasPtr()->SetFont(_T("바탕체"), 8);
    for (int i = 0; i < 24; i++)
    {
        rc.left     = GetMargin() + (int)(i * view_rc2.Width() / 24.0 + 0.5);
        rc.right    = rc.left + 1;
        rc.bottom   = rc.top + 2;
        
        for (int j = 0; j < sizeof(hours) / sizeof(int); j++)
        {
            int v = hours[j];
            if (i == v)
            {
                GetCanvasPtr()->DrawString(rc.left, rc.top - ProgresssBarHeight, GetTextColor2(), _T("%02d"), i);
                rc.bottom = rc.top + ProgresssBarHeight;
            }
        }

        GetCanvasPtr()->FillRect(&rc, GetTextColor2());
    }
}