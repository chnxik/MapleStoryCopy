#pragma once
#include "CEntity.h"

#include "CCamera.h"

class CAnimator;
class CRigidbody;
class CCollider;
class CLevel;

class CActor :
    public CEntity
{

private:
    Vec2    m_vPos;
    Vec2    m_vScale;

    CCollider* m_pCollider;
    CAnimator* m_pAnimator;
    CRigidbody* m_pRigidbody;

    eDir        m_eDir;

    bool    m_bDead;
    bool    m_bCmrAfctd;

public:
    void SetPos(Vec2 _v) { m_vPos = _v; }
    void SetScale(Vec2 _v) { m_vScale = _v; }

    inline Vec2 GetPos() { return m_vPos; }
    inline Vec2 GetScale() { return m_vScale; }

    virtual void SetDir(eDir _dir) { m_eDir = _dir; }
    const eDir GetDir() { return m_eDir; }

    void CreateCollider();
    void CreateAnimator();
    void CreateRigidbody();

    CCollider* GetCollider() { return m_pCollider; }
    CAnimator* GetAnimator() { return m_pAnimator; }
    CRigidbody* GetRigidbody() { return m_pRigidbody; }

public:
    virtual void tick();
    virtual void final_tick() final;
    virtual void render(HDC _dc);

    virtual void BeginOverlap(CCollider* _pOther) {}
    virtual void OnOverlap(CCollider* _pOther) {}
    virtual void EndOverlap(CCollider* _pOther) {}

public:
    bool IsDead() { return m_bDead; }
    virtual void SetDead();
    bool IsCmrAfctd() { return m_bCmrAfctd; }
    void SetCmrAfctd(bool _Set) { m_bCmrAfctd = _Set; }
    
    virtual CActor* Clone() = 0;

public:
    CActor();
    CActor(const CActor& _other);
    virtual ~CActor();

    friend class CEventMgr;
};

