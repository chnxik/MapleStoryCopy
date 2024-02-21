#pragma once
#include "CActor.h"

class CPlayerState;
class CPlatform;
class CLine;
class CSound;
class CItem;
class CFiledItem;
class Tomb;
class CPlayerDeadMessage;

class CPlayer :
    public CActor
{
private:
    CPlayerState*   m_pState;           // 상태값
    CPlatform*      m_pPlatform;
    CLine*          m_pLiftObj;
    CSound*         m_pSound[(UINT)SOUND_ETC::END];
    float           m_fAlertAcc;
    bool            m_bAlert;
    float           m_fInvincibleAcc;
    bool            m_bInvincible;
    bool            m_bPlayerDead;

    CFiledItem*     m_pTargetItem;

    tSkillInfo      m_arrtSkill[(UINT)SKILL::END];
    
    Tomb*           m_pTomb;
    CPlayerDeadMessage* m_pDeadMessage;

    UINT            m_iJumpCnt;

    tStatus         m_tStatus;
   
private:
    void SetInterface();
    void SetAnimation();
    void SetSkillInfo();
    void SetStatus();
    void SoundInit();
    CSound* GetSound(SOUND_ETC _sound) { return m_pSound[(UINT)_sound]; }

public: // 지형
    void SetPlatform(CPlatform* _pPlatform) { m_pPlatform = _pPlatform; }
    void SetLiftObj(CLine* _pLine) { m_pLiftObj = _pLine; }

    CLine* GetLiftObj() { return m_pLiftObj; }
    CPlatform* GetPlatform() { return m_pPlatform; }
    
    bool IsEarth();

public: // 스탯
    const tStatus& GetStatus() { return m_tStatus; }
    UINT HPtick(int _amount);
    UINT MPtick(int _amount);
    void AddExp(int _Exp);
    
    void HPUP();
    void MPUP();
    void ATKUP();
    void DEFUP();

public: // 스킬
    void CoolTime();
    tSkillInfo GetSkill(SKILL _skill) { return m_arrtSkill[(UINT)_skill]; }
    void SkillUP() { --m_tStatus.SkillPoint; }


public: // Key
    void DeleteSkillKey(SKILL _skill);
    void SetKey(SKILL _skill, UINT _key) { m_arrtSkill[(UINT)_skill].Key = _key; }
    void Keyinit();
    
    void PlayerLvUP();

public:
    virtual void tick();
    virtual void render(HDC _dc);

public: // 상태
    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void EndOverlap(CCollider* _pOther);

    virtual void SetDir(eDir _dir);

    void ChangeState(CPlayerState* _newState);
    void CreateState();

    void SetAlert() { m_fAlertAcc = 0.f; m_bAlert = true; }
    const bool IsAlert() { return m_bAlert; }
    void SetInvincible() { m_fInvincibleAcc = 0.f; m_bInvincible = true; }
    void ReleaseInvincible() { m_bInvincible = false; }
    const bool IsInvincible() { return m_bInvincible; }

    
public: // 상태 조작
    void Idle();
    void attack();
    void Jump();
    void DownJump();
    void Damaged(eDir _Dir);
    void LiftJump(Vec2 _vVelocity);
    void PlayerDead();
    void Resurrection();

    void ZeroJumpCnt() { m_iJumpCnt = 0; }


public:
    CLONE(CPlayer);

public:
    CPlayer();
    ~CPlayer();

    friend class CPlayerState;
};

