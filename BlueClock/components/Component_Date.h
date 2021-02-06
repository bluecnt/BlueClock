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

    virtual int GetWidth(bool margin = false) const override;
    virtual int GetHeight(bool margin = false) const override;

private:
    int GetTextHeight() const;
    int GetProgressBarHeight() const;
};