#pragma once
#include "CUI.h"
class CBackGrndUI :
    public CUI
{
public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CLONE_DEACTIVATE(CBackGrndUI);

public:
    CBackGrndUI();
    ~CBackGrndUI();
};

