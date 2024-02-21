#pragma once
#include "CInteraction.h"

class CPlayer;
class CSound;
class CMob;

class CSkill :
    public CInteraction
{
private:
    float       m_fSkillDmg;
    vector<CMob*> m_vecTarget;
    CSound*     m_pHitSound;
    UINT        m_iMaxTarget;
    UINT        m_iTarget;
    UINT        m_iMaxHitCnt;
    UINT        m_iHitCnt;

    UINT        m_iSkillLv;

    float       m_fHitDelay;
    float       m_fHitAcc;

public:
    virtual void tick();
    virtual void render(HDC _dc);

    void SetHitSound(CSound* _pSound) { m_pHitSound = _pSound; }
    CSound* GetHitSound() { return m_pHitSound; }

    void SetSkillDmg(SKILL _skill, float _DefaultDmg, float _LvScale);
    float GetSkillDmg() { return m_fSkillDmg; }
    UINT GetSkillLv() { return m_iSkillLv; }

    void SetMaxTarget(UINT _MaxCnt) { m_iMaxTarget = _MaxCnt; }
    void SetHitDelay(float _hitdelay) { m_fHitDelay = _hitdelay; }
    inline UINT GetMaxTarget() { return m_iMaxTarget; }
    inline UINT GetTargetCnt() { return m_iTarget; }
    void AddTarget(CMob* _Mob);

    void SetMaxHitCnt(UINT _MaxCnt) { m_iMaxHitCnt = _MaxCnt; }

    vector<CMob*>& GetTarget() { return m_vecTarget; }


    virtual void Active() {}

public:
    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void EndOverlap(CCollider* _pOther) {}

    
    CLONE_DEACTIVATE(CSkill);

public:
    CSkill(CPlayer* _pPlayer);
    ~CSkill();
};