#pragma once
#include "CUI.h"

class CTexture;
class CPlayer;
class CItem;
class CNum;

class KeySlot :
    public CUI
{
private:
    CPlayer* m_pPlayer;
    const UINT m_iSlotNum;
    KEYSLOT_TYPE m_eSlotType;
    UINT m_eKey;
    
    SKILL       m_eCurSkill;
    CItem*      m_pCurItem;

    CNum* m_pCNum[2];
    
    CTexture* m_pSlotTex;
    CTexture* m_pCoolTex;

    float m_fCoolRatio;

public:
    void NumInit();

public:
    virtual void tick();
    virtual void render(HDC _dc);
    void SetSlot(KEYSLOT_TYPE _NewSlotType, SKILL _newSkill, CTexture* _pTex);
    void SetSlot(KEYSLOT_TYPE _NewSlotType, CItem* _newItem);
    void ResetSlot();
    SKILL GetCurSkill() { return m_eCurSkill; }
    UINT GetKey() { return m_eKey; }

public:
    CLONE_DEACTIVATE(KeySlot);

public:
    KeySlot(CPlayer* _pPlayer, UINT _SlotNum, UINT _key, CTexture* _KeyTex);
    ~KeySlot();
};

