// [SGLEE:20210203WED_214300] 최초 작성

#pragma once

#include <memory>
#include <vector>
#include "Component.h"
#include "Component_Date.h"
#include "Component_Time.h"

using namespace std;

class CComponentManager
{
public:
    CComponentManager();
    virtual ~CComponentManager();

public:
    int Add(shared_ptr<CComponent> componentSp);

    int Load();

    int GetWidth() const;
    int GetHeight() const;

    int Create();
    void Destroy();
    void Update();
    void Display(blue::mfc::CCanvas* canvasPtr);

private:
    vector<shared_ptr<CComponent>>      mVector;
};