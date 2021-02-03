// [SGLEE:20210203WED_213900] 최초 작성

#include "Component.h"

class CComponent_Date : public CComponent
{
public:
    CComponent_Date();
    virtual ~CComponent_Date();

public:
    virtual int Create() override;
    virtual void Destroy() override;
    virtual void Update() override;
};