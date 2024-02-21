#pragma once
#include "CActor.h"

class CColliderBox :
    public CActor
{
private:
    CActor* m_pOwnerAct;
    bool m_bActivate;


public:
    virtual void tick();
    virtual void render(HDC _dc);

    CLONE_DEACTIVATE(CColliderBox);

public:
    CColliderBox(CActor* _pAct);
    ~CColliderBox();
};

