#pragma once
#include "CLevel.h"
class CStage03 :
    public CLevel
{
public:
    virtual void init() override;
    virtual void Enter(UINT _iPortalNo) override;
    virtual void Exit() override;

    virtual void CreateUI() override;

public:
    CStage03();
    ~CStage03();
};

