#pragma once
#include "CEntity.h"

class CActor;

class CComponent :
    public CEntity
{
private:
    CActor* m_pOwner;

public:
    virtual void tick() = 0;
    virtual void final_tick() {};
    virtual void render(HDC _dc) = 0;

public:
    CActor* GetOwner() { return m_pOwner; }

private:
    void SetOwner(CActor* _pOwner) { m_pOwner = _pOwner; }

public:
    CComponent(CActor* _pOwner);
    ~CComponent();

    friend class CActor;
};

