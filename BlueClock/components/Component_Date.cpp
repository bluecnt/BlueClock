// [SGLEE:20210203WED_213900] ���� �ۼ�

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

    LPCTSTR WeekNames[] =
    {
        _T("Sunday"), _T("Monday"), _T("Tuesday"), _T("Wednesday"), _T("Thursday"), _T("Friday"), _T("Satrueday")
    };
    LPCTSTR WeekNames2[] =
    {
        _T("S"), _T("M"), _T("T"), _T("W"), _T("T"), _T("F"), _T("S")
    };
    const int ProgresssBarHeight = 12;

    SYSTEMTIME st = { 0 };
    GetLocalTime(&st);

#if 1
    int day_of_week = st.wDayOfWeek;
    int hour = st.wHour;
#else
    int day_of_week = 4;
    int hour = 9;
#endif

    CRect view_rc = GetViewRect();
    CRect view_rc2 = GetViewRect(true);

    GetCanvasPtr()->FillRect(&view_rc, GetBkgndColor());
#if 0
    GetCanvasPtr()->FillRect(&view_rc2, RGB(255, 255, 255));
#endif

    // ��¥

    GetCanvasPtr()->SetFont(_T("����ü"), 14);
    blue::mfc::CCanvas::CDrawStringParams ds_params;
    ds_params.mForeColor = GetTextColor();
    ds_params.mFormat = DT_CENTER;
    ds_params.mY = GetMargin();
    ds_params.mHeight = GetHeight(true) / 3;
    GetCanvasPtr()->DrawStringParams(ds_params, _T("%04d.%02d.%02d"), st.wYear, st.wMonth, st.wDay);

    // ����

    ds_params.mY = GetMargin() + GetHeight(true) / 3;
    ds_params.mHeight = GetHeight(true) / 3;
    GetCanvasPtr()->DrawStringParams(ds_params, _T("%s"), WeekNames[day_of_week]);

    // ���α׷��� ��

    auto items = blue::mfc::CCanvas::CalcRects(view_rc2.Width(), ProgresssBarHeight, 7, 1);

    CRect rc;
    rc.left     = GetMargin();
    rc.top      = view_rc2.bottom - ProgresssBarHeight;
    rc.right    = rc.left + items[day_of_week].right;
    rc.bottom   = rc.top + ProgresssBarHeight;
    GetCanvasPtr()->FillRect(&rc, GetBkgndColor2());

    rc = items[day_of_week];
    rc.OffsetRect(GetMargin(), GetMargin() + view_rc2.Height() - ProgresssBarHeight);
    rc.right = rc.left + ((hour + 1) * rc.Width() / 24);
    GetCanvasPtr()->FillRect(&rc, GetBkgndColor3());

    GetCanvasPtr()->SetFont(_T("����ü"), 8);

    int idx = 0;
    for (auto& i : items)
    {
        blue::mfc::CCanvas::CDrawStringParams params;
        params.mX			= GetMargin() + i.left;
        params.mY			= view_rc2.bottom - ProgresssBarHeight;
        params.mWidth		= i.Width();
        params.mHeight		= i.Height();
        params.mFormat		= DT_CENTER | DT_VCENTER | DT_SINGLELINE;
        params.mForeColor	= GetTextColor2();

        if (idx == 0)
            params.mForeColor = RGB(255, 0, 0);
        else if (idx == 6)
            params.mForeColor = RGB(0, 0, 255);

        GetCanvasPtr()->DrawStringParams(params, WeekNames2[idx++]);
    }
}