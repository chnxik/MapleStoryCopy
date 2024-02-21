#pragma once
#include "CLine.h"

class CTester;

class CLadder :
    public CLine
{
private:

public:
    virtual void tick();
    virtual void render(HDC _dc);

    virtual void SetLineInfo() override;

public:
    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void EndOverlap(CCollider* _pOther);


public:
    CLONE(CLadder);

public:
    CLadder();
    ~CLadder();

    friend class CUI;
};

