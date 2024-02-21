#include "pch.h"
#include "CItemMgr.h"

#include "CItem.h"
#include "CFiledItem.h"
#include "CActor.h"

#include "Item_RedPotion.h"
#include "Item_BluePotion.h"
#include "Item_Elixir.h"

CItemMgr::CItemMgr()
{
}

CItemMgr::~CItemMgr()
{
}

void CItemMgr::CreateItem(ITEM_TYPE _type, CActor* pAct)
{
	CFiledItem* newItem = nullptr;
	
	switch (_type)
	{
	case ITEM_TYPE::REDPOTION:
		newItem = new CFiledItem(new Item_RedPotion);
		break;
	case ITEM_TYPE::BLUEPOTION:
		newItem = new CFiledItem(new Item_BluePotion);
		break;
	case ITEM_TYPE::ELIXIR:
		newItem = new CFiledItem(new Item_Elixir);
		break;
	case ITEM_TYPE::END:
		break;
	}
	if (newItem == nullptr)
		return;
	
	newItem->SetItemInfo();
	Instantiate(newItem, LAYER::ITEM);
	Vec2 vPos = pAct->GetPos();
	vPos.y -= pAct->GetScale().y;
	newItem->SetPos(vPos);
	newItem->DropItem();
}
