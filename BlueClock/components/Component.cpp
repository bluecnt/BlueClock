// [SGLEE:20210203WED_213100] √÷√  ¿€º∫

#include "pch.h"
#include "Component.h"

const CString    CComponent::DefaultFontName      = _T("πŸ≈¡√º");
const CString    CComponent::DefaultFontName2     = _T("πŸ≈¡√º");

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

    mCanvas.SetFont(_T("πŸ≈¡√º"), 16);
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
int CComponent::GetItemMargin() const
{
    return mInitParams.mItemMargin;
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

CString CComponent::GetFontName() const
{
    return mInitParams.mFontName;
}
CString CComponent::GetFontName2() const
{
    return mInitParams.mFontName2;
}
int CComponent::GetFontSize() const
{
    return mInitParams.mFontSize;
}
int CComponent::GetFontSize2() const
{
    return mInitParams.mFontSize2;
}

CRect CComponent::GetViewRect(bool margin /*= false*/)
{
    CRect rc = { 0, 0, GetWidth(), GetHeight() };
    if (margin)
        rc.DeflateRect(GetMargin(), GetMargin());

    return rc;
}

int CComponent::printf(LPCTSTR format, ...)
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

    _stprintf_s(buf2, _T("[%s] %s\n"), time, buf);
    OutputDebugString(buf2);

    return lstrlen(buf2);
}