#pragma once

class CActor;

class CItemMgr
{
	SINGLE(CItemMgr);
public:
	void CreateItem(ITEM_TYPE _type, CActor* pAct);
};

