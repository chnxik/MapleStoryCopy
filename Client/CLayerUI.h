#pragma once
#include "CUI.h"

class CLayerUI :
    public CUI
{
public:
    virtual void tick();
    virtual void render(HDC _dc);
    
public:
    CLONE_DEACTIVATE(CLayerUI);

public:
    CLayerUI();
    ~CLayerUI();
};

