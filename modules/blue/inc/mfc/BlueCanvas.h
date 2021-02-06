// [SGLEE:20210203WED_160000] 최초 작성

#pragma once

#include <vector>

using namespace std;

#ifndef ns_begin_blue_mfc
# define ns_begin_blue_mfc           namespace blue { namespace mfc {
# define ns_end_blue_mfc             }}
#endif

ns_begin_blue_mfc

#define BL_MFC_CANVAS_CENTER        blue::mfc::CCanvas::Center
#define BL_MFC_CANVAS_RIGHT         blue::mfc::CCanvas::Right
#define BL_MFC_CANVAS_MIDDLE        blue::mfc::CCanvas::Middle
#define BL_MFC_CANVAS_BOTTOM        blue::mfc::CCanvas::Bottom

class CCanvas
{
public:
    static const int    Center      = 1000000;
    static const int    Right       = 1000001;
    static const int    Middle      = 1000002;
    static const int    Bottom      = 1000003;

    class CDrawStringParams
    {
    public:
        int             mX          = 0;
        int             mY          = 0;
        int             mWidth      = -1;
        int             mHeight     = -1;
        COLORREF        mForeColor  = RGB(0, 0, 0);
        COLORREF        mBackColor  = (COLORREF)-1;
        UINT            mFormat     = DT_LEFT | DT_TOP;
    };

public:
    CCanvas();
    virtual ~CCanvas();

public:
    int Create(int width, int height);
    void Destroy();

    CDC* GetDC();
    int GetWidth() const;
    int GetHeight() const;
    CSize GetSize() const;
    CRect GetRect() const;

    int FrameRect(CRect* rcPtr, COLORREF color);
    int FillRect(CRect* rcPtr, COLORREF color);
    int FillRects(const vector<CRect>& items, COLORREF color,
        int activeIdx = -1, COLORREF activeColor = (COLORREF)-1,
        int offsetX = 0, int offsetY = 0);
    int SetFont(LPCTSTR name, int size);
    int DrawStringParams(const CDrawStringParams& params, LPCTSTR format, ...);
    int DrawString(int x, int y, COLORREF color, LPCTSTR format, ...);
    int DrawStringCenterMiddle(const CRect& rc, COLORREF color, LPCTSTR format, ...);

    int DrawCanvas(CCanvas* canvasPtr, int x = 0, int y = 0);

    int Display(CDC* dcPtr);

    static vector<CRect> CalcRects(int width, int height, int cols, int rows);

private:
    CDC*                mDCPtr      = nullptr;
    CBitmap*            mBmpPtr     = nullptr;
    int                 mWidth      = 0;
    int                 mHeight     = 0;
    CFont*              mFntPtr     = nullptr;
    CBitmap*            mOldBmpPtr  = nullptr;
    CFont*              mOldFntPtr  = nullptr;
};

ns_end_blue_mfc