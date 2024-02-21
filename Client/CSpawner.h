#pragma once
#include "CActor.h"

class CMob;

class CSpawner :
    public CActor
{
private:
    wstring     m_MobKey;       // 불러올 몹 이름
    MOB_TYPE    m_eMob;          // 몹 enum값
    bool        m_bSpawn;       // bool값 생성 여부
    float       m_fZen;         // 리젠 시간
    float       m_fZenAcc;      // 누적 리젠 시간
    CTexture*   m_pTexture;     // ToolLevel 확인용 Texture

public:
    virtual void tick();
    virtual void render(HDC _dc);

    void SetSpawner(wstring _strMobKey);
    void SetMob(UINT _CellNum) { m_eMob = (MOB_TYPE)_CellNum; }
    const UINT GeteMob() { return (UINT)m_eMob; }
    const wstring GetMobKey() { return m_MobKey; }

    void CreateMob();
    void DeadMob() { m_bSpawn = false; }

public:
    CLONE(CSpawner);

public:
    CSpawner();
    ~CSpawner();
};

