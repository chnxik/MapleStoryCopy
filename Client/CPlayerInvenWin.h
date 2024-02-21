#pragma once
#include "CUI.h"

class CPlayer;
class CPNUI;
class CItemSlot;
class CItem;

class CPlayerInvenWin :
    public CUI
{
private:
    CPNUI* m_pPNUI;
    CPlayer* m_pPlayer;

    vector<CItemSlot*> m_arrItemSlot;
    UINT m_iItemCnt;

    CItemSlot* m_pSourceSlot;
    CItemSlot* m_pDestSlot;

public:
    void init();
    void SetItemSlot();
    void SwapSlot();

    void AddSourceSlot(CItemSlot* pSlot) { m_pSourceSlot = pSlot; }
    void AddDestSlot(CItemSlot* pSlot) { m_pDestSlot = pSlot; }

public:
    UINT GetItemCnt() { return m_iItemCnt; }
    CItemSlot* GetSourceSlot() { return m_pSourceSlot; }
    bool AddItem(CItem* pItem);

    CLONE_DEACTIVATE(CPlayerInvenWin);

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CPlayerInvenWin(CPlayer* pPlayer);
    ~CPlayerInvenWin();
};

