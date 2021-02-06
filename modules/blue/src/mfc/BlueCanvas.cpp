// [SGLEE:20210203WED_160000] 최초 작성

#include "pch.h"
#include "../../inc/mfc/BlueCanvas.h"

ns_begin_blue_mfc

CCanvas::CCanvas()
{
}
CCanvas::~CCanvas()
{
    Destroy();
}

int CCanvas::Create(int width, int height)
{
    Destroy();

    mWidth = width;
    mHeight = height;

    mDCPtr = new CDC();
    mBmpPtr = new CBitmap();
    mFntPtr = new CFont();

    CDC* desktop_dc_ptr = CWnd::GetDesktopWindow()->GetWindowDC();

    mDCPtr->CreateCompatibleDC(desktop_dc_ptr);
    mBmpPtr->CreateCompatibleBitmap(desktop_dc_ptr, mWidth, mHeight);

    CWnd::GetDesktopWindow()->ReleaseDC(desktop_dc_ptr);

    mOldBmpPtr = mDCPtr->SelectObject(mBmpPtr);

    return 0;
}
void CCanvas::Destroy()
{
    if (mDCPtr)
    {
        mDCPtr->SelectObject(mOldBmpPtr);

        delete mFntPtr;
        delete mBmpPtr;
        delete mDCPtr;

        mFntPtr = nullptr;
        mBmpPtr = nullptr;
        mDCPtr = nullptr;
    }
}

CDC* CCanvas::GetDC()
{
    return mDCPtr;
}
int CCanvas::GetWidth() const
{
    if (!mDCPtr)
        return -10;

    return mWidth;
}
int CCanvas::GetHeight() const
{
    if (!mDCPtr)
        return -10;

    return mHeight;
}
CSize CCanvas::GetSize() const
{
    return CSize(GetWidth(), GetHeight());
}
CRect CCanvas::GetRect() const
{
    return CRect(0, 0, GetWidth(), GetHeight());
}

int CCanvas::FrameRect(CRect* rcPtr, COLORREF color)
{
    if (!mDCPtr)
        return -10;

    if (!rcPtr)
    {
        CRect rc = { 0, 0, GetWidth(), GetHeight() };
        rcPtr = &rc;
    }

    CBrush br(color);
    mDCPtr->FrameRect(rcPtr, &br);

    return 0;
}
int CCanvas::FillRect(CRect* rcPtr, COLORREF color)
{
    if (!mDCPtr)
        return -10;

    if (!rcPtr)
    {
        CRect rc = { 0, 0, GetWidth(), GetHeight() };
        rcPtr = &rc;
    }

    CBrush br(color);
    mDCPtr->FillRect(rcPtr, &br);

    return 0;
}
int CCanvas::FillRects(const vector<CRect>& items, COLORREF color,
    int activeIdx /*= -1*/, COLORREF activeColor /*= (COLORREF)-1*/,
    int offsetX /*= 0*/, int offsetY /*= 0*/)
{
    if (!mDCPtr)
        return -10;

    int idx = 0;
    for (auto& i : items)
    {
        if (color == (COLORREF)-1 && idx != activeIdx)
        {
            idx++;

            continue;
        }

        CRect rc = i;
        rc.OffsetRect(offsetX, offsetY);
        FillRect(&rc, idx++ == activeIdx ? activeColor : color);
    }

    return 0;
}
int CCanvas::SetFont(LPCTSTR name, int size)
{
    if (!mDCPtr)
        return -10;

    if (mOldFntPtr)
        mDCPtr->SelectObject(mOldFntPtr);

    CFont fnt;
    fnt.CreatePointFont(size * 10, name);
    mOldFntPtr = mDCPtr->SelectObject(&fnt);

    return 0;
}
int CCanvas::DrawStringParams(const CDrawStringParams& params, LPCTSTR format, ...)
{
    if (!mDCPtr)
        return -10;

    TCHAR buf[1024] = { 0 };
    va_list ap;

    va_start(ap, format);
    _vstprintf_s(buf, format, ap);
    va_end(ap);

    mDCPtr->SetTextColor(params.mForeColor);
    mDCPtr->SetBkMode(params.mBackColor == (COLORREF)-1 ? TRANSPARENT : OPAQUE);
    if (params.mBackColor != (COLORREF)-1)
        mDCPtr->SetBkColor(params.mBackColor);

    CRect rc = { params.mX, params.mY,
        params.mWidth == -1 ? params.mX + GetWidth() : params.mX + params.mWidth,
        params.mHeight == -1 ? params.mY + GetHeight() : params.mY + params.mHeight };
    mDCPtr->DrawText(buf, &rc, params.mFormat);

    return 0;
}
int CCanvas::DrawString(int x, int y, COLORREF color, LPCTSTR format, ...)
{
    if (!mDCPtr)
        return -10;

    TCHAR buf[1024] = { 0 };
    va_list ap;

    va_start(ap, format);
    _vstprintf_s(buf, format, ap);
    va_end(ap);

    CDrawStringParams params;

    if (x == Center)
        params.mFormat |= DT_CENTER;
    else if (x == Right)
        params.mFormat |= DT_RIGHT;
    else
        params.mX = x;

    if (y == Middle)
        params.mFormat |= DT_VCENTER | DT_SINGLELINE;
    else if (x == Bottom)
        params.mFormat |= DT_BOTTOM;
    else
        params.mY = y;

    params.mForeColor = color;

    DrawStringParams(params, buf);

    return 0;
}

int CCanvas::DrawStringCenterMiddle(const CRect& rc, COLORREF color, LPCTSTR format, ...)
{
    if (!mDCPtr)
        return -10;

    TCHAR buf[1024] = { 0 };
    va_list ap;

    va_start(ap, format);
    _vstprintf_s(buf, format, ap);
    va_end(ap);

    CDrawStringParams params;
    //
    params.mX           = rc.left;
    params.mY           = rc.top;
    params.mWidth       = rc.Width();
    params.mHeight      = rc.Height();
    params.mForeColor   = color;
    //params.mBackColor;
    params.mFormat      = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
    //
    return DrawStringParams(params, buf);
}

int CCanvas::DrawCanvas(CCanvas* canvasPtr, int x /*= 0*/, int y /*= 0*/)
{
    if (!mDCPtr)
        return -10;

    mDCPtr->BitBlt(x, y, canvasPtr->GetWidth(), canvasPtr->GetHeight(), canvasPtr->GetDC(), 0, 0, SRCCOPY);

    return 0;
}

int CCanvas::Display(CDC* dcPtr)
{
    if (!mDCPtr)
        return -10;

    dcPtr->BitBlt(0, 0, GetWidth(), GetHeight(), mDCPtr, 0, 0, SRCCOPY);

    return 0;
}

vector<CRect> CCanvas::CalcRects(int width, int height, int cols, int rows)
{
    vector<CRect> vt;

    int cell_w = width / cols;
    int cell_h = height / rows;
    int mod_w = width % cols;
    int mod_w1 = mod_w;
    int mod_h = height % rows;
    int delta_x = 0;
    int delta_y = 0;

    for (int j = 0; j < rows; j++)
    {
        delta_x = 0;
        mod_w = mod_w1;
        for (int i = 0; i < cols; i++)
        {
            CRect rc;
            int x = i * cell_w + delta_x;
            int y = j * cell_h + delta_y;
            int r = x + cell_w + (mod_w > 0 ? 1 : 0);            
            int b = y + cell_h + (mod_h > 0 ? 1 : 0);
            rc.SetRect(x, y, r, b);
            vt.push_back(rc);

            if (mod_w-- > 0) delta_x++;
            if (mod_h-- > 0) delta_y++;
        }
    }

    return vt;
}

ns_end_blue_mfc