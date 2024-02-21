#pragma once
#include "CLevel.h"
class CStage06 :
    public CLevel
{
public:
    virtual void init() override;
    virtual void Enter(UINT _iPortalNo) override;
    virtual void Exit() override;

    virtual void CreateUI() override;

public:
    CStage06();
    ~CStage06();
};

