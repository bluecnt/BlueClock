// [SGLEE:20210203WED_213100] 최초 작성

#include "pch.h"
#include "Component.h"

CComponent::CComponent()
{
    //
}
CComponent::~CComponent()
{
    //
}

int CComponent::Init(const CInitParams& params)
{
    mInitParams = params;

    return 0;
}

int CComponent::Create()
{
    Destroy();

    mCanvas.Create(GetWidth(), GetHeight());

    return 0;
}
void CComponent::Destroy()
{
    //
}
void CComponent::Update()
{
    CRect rc = GetViewRect();
    mCanvas.FillRect(&rc, GetBkgndColor());

    rc = GetViewRect(true);
    mCanvas.FillRect(&rc, GetBkgndColor2());

    mCanvas.SetFont(_T("바탕체"), 16);
    mCanvas.DrawString(BL_MFC_CANVAS_CENTER, BL_MFC_CANVAS_MIDDLE, GetTextColor(), GetName());
}

blue::mfc::CCanvas* CComponent::GetCanvasPtr()
{
    return &mCanvas;
}
CString CComponent::GetName() const
{
    return mInitParams.mName;
}
int CComponent::GetWidth(bool margin /*= false*/) const
{
    return margin ? mInitParams.mWidth - GetMargin() : mInitParams.mWidth;
}
int CComponent::GetHeight(bool margin /*= false*/) const
{
    return margin ? mInitParams.mHeight - GetMargin() : mInitParams.mHeight;
}
int CComponent::GetMargin() const
{
    return DefaultMargin;
}
COLORREF CComponent::GetBkgndColor() const
{
    return mInitParams.mBkgndColor;
}
COLORREF CComponent::GetTextColor() const
{
    return mInitParams.mTextColor;
}
COLORREF CComponent::GetBkgndColor2() const
{
    return mInitParams.mBkgndColor2;
}
COLORREF CComponent::GetBkgndColor3() const
{
    return mInitParams.mBkgndColor3;
}
COLORREF CComponent::GetTextColor2() const
{
    return mInitParams.mTextColor2;
}

CRect CComponent::GetViewRect(bool margin /*= false*/)
{
    CRect rc = { 0, 0, GetWidth(), GetHeight() };
    if (margin)
        rc.DeflateRect(GetMargin(), GetMargin());

    return rc;
}