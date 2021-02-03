// [SGLEE:20210204THU_011400] 최초 작성

#include "pch.h"
#include "Component_Title.h"

CComponent_Title::CComponent_Title()
{
    //
}
CComponent_Title::~CComponent_Title()
{
    //
}

int CComponent_Title::Create()
{
    CComponent::Create();

    return 0;
}
void CComponent_Title::Destroy()
{
    CComponent::Destroy();

    //
}

void CComponent_Title::Update()
{
#if 1
    CComponent::Update();

    return;
#endif

    const int ProgresssBarHeight = 12;

    SYSTEMTIME st = { 0 };
    GetLocalTime(&st);

    CRect view_rc = GetViewRect();
    CRect view_rc2 = GetViewRect(true);

    GetCanvasPtr()->FillRect(&view_rc, GetBkgndColor());
#if 1
    GetCanvasPtr()->FillRect(&view_rc2, RGB(255, 255, 255));
#endif

    //

}