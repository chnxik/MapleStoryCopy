#pragma once
#include "CLine.h"
class CWall :
    public CLine
{
private:
    bool m_bOnlyMob;
    eDir m_eWallDir;


public:
    virtual void tick();
    virtual void render(HDC _dc);
    

    virtual void SetLineInfo() override;
    void SetWallDir(eDir _LorR) { m_eWallDir = _LorR; }
    void SetOnlyMob(bool _b) { m_bOnlyMob = (bool)_b; }

    bool GetOnlyMob() { return m_bOnlyMob;}
    eDir GetWallDir() { return m_eWallDir;}

public:
    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void EndOverlap(CCollider* _pOther);
    
    bool CheckCollisionWall(Vec2 _OtherPos);


public:
    CLONE(CWall);

public:
    CWall();
    ~CWall();

    friend class CUI;
};

