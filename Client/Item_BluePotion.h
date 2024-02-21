#pragma once
#include "CItem.h"
class Item_BluePotion :
    public CItem
{
    CLONE_DEACTIVATE(Item_BluePotion);

public:
    virtual void UseItem(CPlayer* pPlayer);

public:
    Item_BluePotion();
    ~Item_BluePotion();
};

