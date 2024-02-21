#pragma once
#include "CActor.h"

class CMob;

class CSpawner :
    public CActor
{
private:
    wstring     m_MobKey;       // �ҷ��� �� �̸�
    MOB_TYPE    m_eMob;          // �� enum��
    bool        m_bSpawn;       // bool�� ���� ����
    float       m_fZen;         // ���� �ð�
    float       m_fZenAcc;      // ���� ���� �ð�
    CTexture*   m_pTexture;     // ToolLevel Ȯ�ο� Texture

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

