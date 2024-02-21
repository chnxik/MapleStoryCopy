#pragma once
#include "CComponent.h"

class CPlatform;

class CCollider :
    public CComponent
{
private:
    Vec2    m_vOffsetPos;
    Vec2    m_vFinalPos;
    Vec2    m_vScale;

    Vec2    m_vGrndPos;

    int     m_iOverlapCount;
    int     m_iPlatformCnt;

public:
    void SetOffsetPos(Vec2 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

    Vec2 GetOffsetPos() { return m_vOffsetPos; }
    Vec2 GetScale() { return m_vScale; }
    Vec2 GetGrndPt() { return m_vGrndPos; }
    int GetOverlapCount() { return m_iOverlapCount; }

    Vec2 GetFinalPos() { return m_vFinalPos; }

    void AddPlfCnt() { ++m_iPlatformCnt; }
    void SubPlfCnt() { --m_iPlatformCnt; }
    bool IsZeroPlfCnt() { return m_iPlatformCnt == 0; }

public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc);

public:
    void BeginOverlap(CCollider* _pOther);
    void OnOverlap(CCollider* _pOther);
    void EndOverlap(CCollider* _pOther);

public:
    CLONE(CCollider);

public:
    CCollider(CActor* _pOwner);
    CCollider(const CCollider& _other);
    ~CCollider();
};

