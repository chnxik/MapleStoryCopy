#pragma once
#include "CActor.h"

class CSpawner;
class CPlayer;
class CMobState;
class CSound;

class CMob :
    public CActor
{
private:
    CSpawner* m_pSpawner;
    CPlayer* m_pTarget;
    tStatus m_tStatus;
    CMobState* m_pState;
    CSound*  m_pHitSound;
    CSound*  m_pDeadSound;
    bool     m_bInvincible;

public:
    virtual void init() = 0;// 몬스터 초기 정보 셋팅
    virtual void SetAnimator() = 0;
    virtual void tick();

    CSpawner* GetSpawner() { return m_pSpawner; }

    virtual void SetTarget(CPlayer* pTarget) { m_pTarget = pTarget; }
    virtual CPlayer* GetTarget() { return m_pTarget; }

    virtual void ChangeState(CMobState* _newState);
    virtual void CreateState();

    void SetInvincible(bool _b) { m_bInvincible = _b; }
    const bool IsInvincible() { return m_bInvincible; }

    void SetHitSound(CSound* _Sound) { m_pHitSound = _Sound; }
    void SetDeadSound(CSound* _Sound) { m_pDeadSound = _Sound; }

    CSound* GetHitSound() { return m_pHitSound; }
    CSound* GetDeadSound() { return m_pDeadSound; }

    void SetStatus(tStatus _Status) { m_tStatus = _Status; }
    tStatus& GetStatus() { return m_tStatus; }
    void HPtick(int _amount);
    void MPtick(int _amount);

    virtual void randState();
    virtual void Idle() {}
    virtual void Walk() {}
    virtual float Dead();
    virtual void Alert() {}
    virtual void Spawn(UINT _Optical) {}
    virtual float Damaged() { return 0; }

    CMob(CSpawner* _pSpawner);
    ~CMob();
};