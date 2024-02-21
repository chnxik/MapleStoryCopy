#pragma once
#include "CActor.h"

class CLevel;
class CSound;

class CPortal :
    public CActor
{
private:
    static UINT g_iPortalNo;
    UINT    m_iPortalNo;
    UINT    m_iConnectPortalNo;
    LEVEL_TYPE m_pConnectLevel;
    CSound* m_pPortalSound;

public:
    virtual void tick();
    virtual void render(HDC _dc);

    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void EndOverlap(CCollider* _pOther);

public:
    void SetPortalInfo(LEVEL_TYPE _pConnectLevel, UINT _iConnectPortalNo)
    {
        m_pConnectLevel = _pConnectLevel;
        m_iConnectPortalNo = _iConnectPortalNo;
    }
    void ConnectLevel(LEVEL_TYPE _pLevel) { m_pConnectLevel = _pLevel; }
    UINT GetPortalNo() { return m_iPortalNo; }
    Vec2 GetSpawnPos() 
    { 
        Vec2 vPos = GetPos();
        vPos.y -= 200.f;
        return vPos;
    }
    virtual void SetDead();

    static CPortal* CreatePortal();  // Æ÷Å»°´Ã¼ »ý¼º ÇÔ¼ö
    static void SetZeroPortal() { g_iPortalNo = 1; }

public:
    CLONE(CPortal);

private:
    CPortal();
    ~CPortal();
};