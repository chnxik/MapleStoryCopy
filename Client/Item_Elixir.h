#pragma once
#include "CItem.h"

class Item_Elixir :
    public CItem
{
    CLONE_DEACTIVATE(Item_Elixir);

public:
    virtual void UseItem(CPlayer* pPlayer);

public:
    Item_Elixir();
    ~Item_Elixir();
};

