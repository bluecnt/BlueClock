// [SGLEE:20210203WED_214300] 최초 작성

#include "pch.h"
#include "ComponentManager.h"

CComponentManager::CComponentManager()
{
    //
}
CComponentManager::~CComponentManager()
{
    //
}

int CComponentManager::Add(shared_ptr<CComponent> componentSp)
{
    mVector.push_back(componentSp);

    return 0;
}

int CComponentManager::Load()
{
    CComponent::CInitParams init_params;

    auto comp_date_sp = make_shared<CComponent_Date>();
    //
    init_params.mName           =_T("Date");
    //
    init_params.mWidth          = comp_date_sp->GetWidth();
    init_params.mHeight         = comp_date_sp->GetHeight();
    init_params.mMargin         = CComponent::DefaultMargin;
    init_params.mItemMargin     = CComponent::DefaultItemMargin;
    //
    init_params.mBkgndColor     = RGB(0xde, 0xeb, 0xf6);
    init_params.mTextColor      = RGB(0x1e, 0x4e, 0x79);
    init_params.mBkgndColor2    = RGB(0xbd, 0xd7, 0xee);
    init_params.mBkgndColor3    = RGB(0x9c, 0xc3, 0xe5);
    init_params.mTextColor2     = RGB(0x2e, 0x75, 0xb5);
    //
    init_params.mFontName       = CComponent::DefaultFontName;
    init_params.mFontName2      = CComponent::DefaultFontName2;
    init_params.mFontSize       = CComponent::DefaultFontSize;
    init_params.mFontSize2      = CComponent::DefaultFontSize2;
    //
    comp_date_sp->Init(init_params);

    auto comp_time_sp = make_shared<CComponent_Time>();
    //
    init_params.mName           = _T("Time");
    //
    init_params.mWidth          = comp_date_sp->GetWidth();
    init_params.mHeight         = comp_date_sp->GetHeight();
    init_params.mMargin         = CComponent::DefaultMargin;
    init_params.mItemMargin     = CComponent::DefaultItemMargin;
    //
    init_params.mBkgndColor     = RGB(0xc6, 0xd9, 0xf0);
    init_params.mTextColor      = RGB(0x0f, 0x24, 0x3e);
    init_params.mBkgndColor2    = RGB(0x8d, 0xb3, 0xe2);
    init_params.mBkgndColor3    = RGB(0x54, 0x8d, 0xd4);
    init_params.mTextColor2     = RGB(0x17, 0x36, 0x5d);
    //
    init_params.mFontName       = CComponent::DefaultFontName;
    init_params.mFontName2      = CComponent::DefaultFontName2;
    init_params.mFontSize       = 24; //CComponent::DefaultFontSize;
    init_params.mFontSize2      = CComponent::DefaultFontSize2;
    //
    comp_time_sp->Init(init_params);

    Add(comp_date_sp);
    Add(comp_time_sp);

    return 0;
}

int CComponentManager::SetScale(double value)
{
    for (const auto& i : mVector)
        i->SetScale(value);

    return 0;
}

int CComponentManager::GetWidth() const
{
    int max_w = 0;
    for (const auto& i : mVector)
    {
        int w = (int)(i->GetWidth() * i->GetScale() + 0.5);
        if (w > max_w)
            max_w = w;
    }

    return max_w + (BorderSize * 2);
}
int CComponentManager::GetHeight() const
{
    int sum_h = 0;
    for (const auto& i : mVector)
    {
        int h = (int)(i->GetHeight() * i->GetScale() + 0.5);
        sum_h += h;
    }

    return sum_h + (BorderSize * 2);
}

int CComponentManager::Create()
{
    if ((int)mVector.size() == 0)
    {
        bl_printf(_T("There is no component to create! <ERROR>"));

        return -10;
    }

    for (const auto& i : mVector)
    {
        int ret = i->Create();
        if (ret < 0)
            return -10;
    }

    return 0;
}
void CComponentManager::Destroy()
{
    for (const auto& i : mVector)
    {
        i->Destroy();
    }
}

void CComponentManager::Update()
{
    for (const auto& i : mVector)
        i->Update();
}
void CComponentManager::Display(blue::mfc::CCanvas* canvasPtr)
{
    int y = 1;
    int x = 1;
    for (const auto& i : mVector)
    {
        canvasPtr->DrawCanvas(i->GetCanvasPtr(), x, y);
        y += i->GetHeight();
    }

    canvasPtr->FrameRect(nullptr, RGB(0, 0, 0255));
}