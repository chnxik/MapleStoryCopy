#pragma once
#include "CMob.h"


class Mob_BlueSnail :
    public CMob
{
private:
    float       m_fAcc;
    int         m_iMoveDist;

public:
    virtual void init(); // 몬스터 초기 정보 셋팅
    virtual void SetAnimator();

    virtual void render(HDC _dc);

public:
    virtual void Idle();
    virtual void Walk();
    virtual float Dead();
    virtual void Alert();
    virtual void Spawn(UINT _Optical);
    virtual float Damaged();

    CLONE_DEACTIVATE(Mob_BlueSnail);

public:
    Mob_BlueSnail(CSpawner* _pSpawner);
    ~Mob_BlueSnail();
};

