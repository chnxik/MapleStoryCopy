#pragma once
#include "CItem.h"
class Item_RedPotion :
    public CItem
{
    CLONE_DEACTIVATE(Item_RedPotion);

public:
    virtual void UseItem(CPlayer* pPlayer);

public:
    Item_RedPotion();
    ~Item_RedPotion();
};

