// [SGLEE:20210203WED_213100] 최초 작성

#pragma once

#include "blue/inc/mfc/BlueCanvas.h"

#ifndef bl_printf
# define bl_printf   CComponent::printf
#endif

class CComponent
{
public:
    static const int        DefaultWidth        = 240;
    static const int        DefaultHeight       = 100;
    static const int        DefaultMargin       = 10;
    static const int        DefaultItemMargin   = 4;
    //
    static const CString    DefaultFontName;
    static const CString    DefaultFontName2;
    static const int        DefaultFontSize     = 18;
    static const int        DefaultFontSize2    = 8;

    class CInitParams
    {
    public:
        CString         mName           = _T("");
        //
        int             mWidth          = DefaultWidth;
        int             mHeight         = DefaultHeight;
        int             mMargin         = DefaultMargin;
        int             mItemMargin     = DefaultItemMargin;
        //
        COLORREF        mBkgndColor     = RGB(255, 255, 255);
        COLORREF        mTextColor      = RGB(0, 0, 0);
        COLORREF        mBkgndColor2    = (COLORREF)-1;
        COLORREF        mBkgndColor3    = (COLORREF)-1;
        COLORREF        mTextColor2     = RGB(0, 0, 0);
        //
        CString         mFontName       = DefaultFontName;
        CString         mFontName2      = DefaultFontName2;
        int             mFontSize       = DefaultFontSize;
        int             mFontSize2      = DefaultFontSize2;
    };

public:
    CComponent();
    virtual ~CComponent();

public:
    int Init(const CInitParams& params);

    virtual int Create();
    virtual void Destroy();
    virtual void Update();

    int SetScale(double scale);
    
    blue::mfc::CCanvas* GetCanvasPtr();
    CInitParams GetCreateParams() const;

    CString GetName() const;

    virtual int GetWidth(bool margin = false) const;
    virtual int GetHeight(bool margin = false) const;
    int GetMargin() const;
    int GetItemMargin() const;

    COLORREF GetBkgndColor() const;
    COLORREF GetTextColor() const;
    COLORREF GetBkgndColor2() const;
    COLORREF GetBkgndColor3() const;
    COLORREF GetTextColor2() const;

    CString GetFontName() const;
    CString GetFontName2() const;
    int GetFontSize() const;
    int GetFontSize2() const;

    CRect GetViewRect(bool margin = false);

    double GetScale() const;

public:
    static int printf(LPCTSTR format, ...);

private:
    blue::mfc::CCanvas      mCanvas;
    CInitParams             mInitParams;

#if 1
    double                  mScale  = 1.0;
#else
    double                  mScale  = 2.0;
#endif
};