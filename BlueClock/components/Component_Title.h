// [SGLEE:20210204THU_011400] ���� �ۼ�

#include "Component.h"

class CComponent_Title: public CComponent
{
public:
    CComponent_Title();
    virtual ~CComponent_Title();

public:
    virtual int Create() override;
    virtual void Destroy() override;
    virtual void Update() override;
};