#pragma once
#include "CLine.h"

class CPlatform :
    public CLine
{
private:
    bool _bEarth;

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void EndOverlap(CCollider* _pOther);

    virtual void SetLineInfo() override;

    void SetEarth(bool _b) { _bEarth = _b; }
    bool IsEarth() { return _bEarth; }

public:
    CLONE(CPlatform);

public:
    CPlatform();
    ~CPlatform();

    friend class CUI;
};

