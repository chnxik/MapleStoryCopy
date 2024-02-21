#pragma once
#include "CUI.h"

class CPlayer;
class CItem;
class CNum;

class CItemSlot :
    public CUI
{
private:
    UINT        m_iSlotNo;
    CPlayer*    m_pPlayer;
    CItem*      m_pItem;
    CNum*       m_pCNum[2];

    float       m_fAcc;
    bool        m_bDbClick;

public:
    virtual void tick();
    virtual void render(HDC _dc);

    void SetItem(CItem* _type) { m_pItem = _type;}
    void SetSlotNo(UINT _No) { m_iSlotNo = _No; }

    void NumInit();

public:
    UINT GetSlotNo() { return m_iSlotNo; }
    CItem* GetItem() { return m_pItem; }

    
    void UseItem();

public:
    virtual void MouseLbtnClicked();
    virtual void MouseLbtnDown();
    virtual void MouseOn();

public:
    CLONE_DEACTIVATE(CItemSlot);

public:
    CItemSlot(CPlayer* pPlayer, UINT _i);
    ~CItemSlot();
};

