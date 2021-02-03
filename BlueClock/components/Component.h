// [SGLEE:20210203WED_213100] 최초 작성

#pragma once

#include "blue/inc/mfc/BlueCanvas.h"

class CComponent
{
public:
    static const int DefaultWidth   = 240;
    static const int DefaultHeight  = 100;
    static const int DefaultMargin  = 10;

    class CInitParams
    {
    public:
        CString         mName           = _T("");
        int             mWidth          = DefaultWidth;
        int             mHeight         = DefaultHeight;
        int             mMargin         = DefaultMargin;
        COLORREF        mBkgndColor     = RGB(255, 255, 255);
        COLORREF        mTextColor      = RGB(0, 0, 0);
        COLORREF        mBkgndColor2    = (COLORREF)-1;
        COLORREF        mBkgndColor3    = (COLORREF)-1;
        COLORREF        mTextColor2     = RGB(0, 0, 0);
    };

public:
    CComponent();
    virtual ~CComponent();

public:
    int Init(const CInitParams& params);

    virtual int Create();
    virtual void Destroy();
    virtual void Update();
    
    blue::mfc::CCanvas* GetCanvasPtr();
    CString GetName() const;
    int GetWidth(bool margin = false) const;
    int GetHeight(bool margin = false) const;
    int GetMargin() const;
    COLORREF GetBkgndColor() const;
    COLORREF GetTextColor() const;
    COLORREF GetBkgndColor2() const;
    COLORREF GetBkgndColor3() const;
    COLORREF GetTextColor2() const;

    CRect GetViewRect(bool margin = false);

private:
    blue::mfc::CCanvas      mCanvas;
    CInitParams             mInitParams;
};