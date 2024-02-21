#pragma once
#include "CActor.h"

class CTexture;
class CSound;
class CPlayer;

class CItem :
    public CActor
{
private:
    ITEM_TYPE m_eItemtype;  // ������ ����
    CTexture* m_pItemTex;   // ������ �ؽ���
    CSound*   m_pUseSound;  // ������ ��� ����
    UINT      m_iQuantity;

public:
    virtual void tick();

protected:
    virtual void SetItemType(ITEM_TYPE _type) { m_eItemtype = _type; }
    virtual void SetItemTex(CTexture* _pTex) { m_pItemTex = _pTex; }
    virtual void SetItemSound(CSound* _pSound) { m_pUseSound = _pSound; }

public:
    virtual ITEM_TYPE   GetItemType() { return m_eItemtype; }
    virtual CTexture*   GetItemTex() { return m_pItemTex; }
    virtual CSound*     GetUseSound() { return m_pUseSound; }

    UINT AddItemCnt() { if (m_iQuantity < 99) ++m_iQuantity; return m_iQuantity; }
    UINT SubItemCnt() { if (m_iQuantity > 0) --m_iQuantity; return m_iQuantity; }
    UINT GetItemCnt() { return m_iQuantity; }

public:
    virtual void UseItem(CPlayer* pPlayer) {}

public:
    CItem();
    ~CItem();
};

