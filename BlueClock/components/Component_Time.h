// [SGLEE:20210204THU_000300] 최초 작성

#include "Component.h"

class CComponent_Time: public CComponent
{
public:
    CComponent_Time();
    virtual ~CComponent_Time();

public:
    virtual int Create() override;
    virtual void Destroy() override;
    virtual void Update() override;

    virtual int GetWidth(bool margin = false) const override;
    virtual int GetHeight(bool margin = false) const override;

private:
    int GetTextHeight() const;
    int GetProgressBarTextHeight() const;
    int GetProgressBarHeight() const;
};