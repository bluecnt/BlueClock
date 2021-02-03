// [SGLEE:20210203WED_152900] 최초 작성

#pragma once

#ifndef ns_begin_blue_mfc
# define ns_begin_blue_mfc           namespace blue { namespace mfc {
# define ns_end_blue_mfc             }}
#endif

ns_begin_blue_mfc

#define BL_MFC_WND_SIDE_NONE        blue::mfc::CWndUtils::ESide::None
#define BL_MFC_WND_SIDE_LEFT        blue::mfc::CWndUtils::ESide::Left
#define BL_MFC_WND_SIDE_CENTER      blue::mfc::CWndUtils::ESide::Center
#define BL_MFC_WND_SIDE_RIGHT       blue::mfc::CWndUtils::ESide::Right
#define BL_MFC_WND_SIDE_TOP         blue::mfc::CWndUtils::ESide::Topt
#define BL_MFC_WND_SIDE_MIDDLE      blue::mfc::CWndUtils::ESide::Middle
#define BL_MFC_WND_SIDE_BOTTOM      blue::mfc::CWndUtils::ESide::Bottom

#define BL_MFC_WND_SIDE_LEFT_TOP            blue::mfc::CWndUtils::ESide::LeftTop
#define BL_MFC_WND_SIDE_LEFT_MIDDLE         blue::mfc::CWndUtils::ESide::LeftMiddle
#define BL_MFC_WND_SIDE_LEFT_BOTTOM         blue::mfc::CWndUtils::ESide::LeftBottom
#define BL_MFC_WND_SIDE_CENTER_TOP          blue::mfc::CWndUtils::ESide::CenterTop
#define BL_MFC_WND_SIDE_CENTER_MIDDLE       blue::mfc::CWndUtils::ESide::CenterMiddle
#define BL_MFC_WND_SIDE_CENTER_BOTTOM       blue::mfc::CWndUtils::ESide::CenterBottom
#define BL_MFC_WND_SIDE_RIGHT_TOP           blue::mfc::CWndUtils::ESide::RightTop
#define BL_MFC_WND_SIDE_RIGHT_MIDDLE        blue::mfc::CWndUtils::ESide::RightMiddle
#define BL_MFC_WND_SIDE_RIGHT_BOTTOM        blue::mfc::CWndUtils::ESide::RightBottom

#define bl_printf(...)              blue::mfc::CWndUtils::printf(__VA_ARGS__)

class CWndUtils
{
public:
    enum class ESide
    {
        Left            = 0x0001,
        Center          = 0x0002,
        Right           = 0x0004,
        Top             = 0x0010,
        Middle          = 0x0020,
        Bottom          = 0x0040,
        //
        LeftTop         = Left | Top,
        LeftMiddle      = Left | Middle,
        LeftBottom      = Left | Bottom,
        CenterTop       = Center | Top,
        CenterMiddle    = Center | Middle,
        CenterBottom    = Center | Bottom,
        RightTop        = Right | Top,
        RightMiddle     = Right | Middle,
        RightBottom     = Right | Bottom,

        //
        Count,
        None = -1,
    };

public:
    CWndUtils(CWnd* wndPtr);
    virtual ~CWndUtils();

public:
    void SetWndPtr(CWnd* wndPtr);

    int Move(ESide side, LPWINDOWPOS lpwndpos = nullptr);
    int Size(int width, int height);
    int SetTopmost(bool flag);
    int ToggleTopmost();

    bool IsTopmost() const;


public:
    static int printf(LPCTSTR format, ...);

private:
    CWnd*           mWndPtr     = nullptr;
    bool            mTopmost    = false;
};

ns_end_blue_mfc