#pragma once
#include "CLevel.h"

class CSound;
class CBtnUI;

class CLoginLevel :
    public CLevel
{
private:
    CSound* m_pSound;
    CBtnUI* m_pLoginBtn;


public:
    void GameStart();

public:
    virtual void init() override;
    virtual void Enter(UINT _iPortalNo) override;
    virtual void Exit() override;

    virtual void CreateUI() override;

public:
    CLoginLevel();
    ~CLoginLevel();
};

