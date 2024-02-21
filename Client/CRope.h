#pragma once
#include "CLine.h"

class CTester;

class CRope :
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
    CLONE(CRope);

public:
    CRope();
    ~CRope();

    friend class CUI;
};

