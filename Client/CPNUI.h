#pragma once
#include "CUI.h"
class CPNUI :
    public CUI
{
private:
    Vec2 m_vPressPos;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void MouseLbtnDown() override;
    virtual void MouseLbtnClicked() override;
    virtual void MouseOn() override;


public:
    CPNUI();
    ~CPNUI();
};