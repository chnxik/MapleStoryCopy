#pragma once
#include "CUI.h"

class KeySlot;
class CTexture;
class CPlayer;
class CItem;

class CQuickSlotUI :
    public CUI
{
private:
    CPlayer*        m_pPlayer;
    KEYSLOT_TYPE    m_eCurSlotType;

    SKILL           m_eCurSkill;
    CItem*          m_pCurItem;
    KeySlot*        m_pCurSlot;
    CTexture*       m_pSelectedTex;

    KeySlot* m_pKeySlot[16];
    KeySlot* m_pPrvSkillSlot[(UINT)SKILL::END];
    KeySlot* m_pPrvItemSlot[(UINT)ITEM_TYPE::END];

public:
    void init();
    void initKey();

public:
    void SetSlotType(KEYSLOT_TYPE _type) { m_eCurSlotType = _type; }
    void SetItemSlot(CItem* _ItemSlot) { m_pCurItem = _ItemSlot; }
    void SelectSkill(SKILL _skill) { m_eCurSkill = _skill; }
    void SelectKeySlot(KeySlot* _key) { m_pCurSlot = _key; }
    void SelectTex(CTexture* _pTex) { m_pSelectedTex = _pTex; }

    KeySlot* GetPrevSlot(SKILL _pSKill) { return m_pPrvSkillSlot[(UINT)_pSKill]; }
    KeySlot* GetPrevSlot(ITEM_TYPE _pITemType) { return m_pPrvItemSlot[(UINT)_pITemType]; }
    void SetPrevSlot(SKILL _pSKill, KeySlot* _pSlot) { m_pPrvSkillSlot[(UINT)_pSKill] = _pSlot; }
    void SetPrevSlot(ITEM_TYPE _pITemType, KeySlot* _pSlot) { m_pPrvItemSlot[(UINT)_pITemType] = _pSlot; }


public:
    void ResetSlot();

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CQuickSlotUI(CPlayer* _pPlayer);
    ~CQuickSlotUI();
};