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

int CComponentManager::GetWidth() const
{
    int max_w = 0;
    for (const auto& i : mVector)
    {
        if (i->GetWidth() > max_w)
            max_w = i->GetWidth();
    }

    return max_w + 1 * 2;
}
int CComponentManager::GetHeight() const
{
    int sum_h = 0;
    for (const auto& i : mVector)
        sum_h += i->GetHeight();

    return sum_h + 1 * 2;
}


int CComponentManager::Create()
{
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