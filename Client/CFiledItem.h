#pragma once
#include "CActor.h"

class CItem;
class CTexture;

class CFiledItem :
    public CActor
{
private:
    CItem* m_pItem;
    CTexture* m_pTex;
    float m_fAcc;
    float m_fMaxFiledTime;

    float   m_fDir;
    float   m_fOffset;
    float   m_fMaxOffset;
    bool    m_bGetable;

    float   m_fRatio;

    bool    m_bGet;

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    void SetItemInfo();
    void DropItem();
    CItem* GetItem();

public:
    bool IsGetable() { return m_bGetable; }
    CItem* GetTargetItem() { return m_pItem; }

public:
    CLONE_DEACTIVATE(CFiledItem);

public:
    CFiledItem(CItem* pItem);
    ~CFiledItem();
};

