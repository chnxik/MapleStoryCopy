#include "pch.h"
#include "Item_BluePotion.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CSound.h"

#include "CPlayer.h"


Item_BluePotion::Item_BluePotion()
{
	SetItemType(ITEM_TYPE::BLUEPOTION);
	SetItemTex(CResMgr::GetInst()->LoadTexture(L"bluept", L"texture\\item\\bluept.png"));
	SetItemSound(CResMgr::GetInst()->LoadSound(L"potion", L"sound\\item\\potion.wav"));
}

Item_BluePotion::~Item_BluePotion()
{
}

void Item_BluePotion::UseItem(CPlayer* pPlayer)
{
	GetUseSound()->SetPosition(0);
	GetUseSound()->Play(false);
	pPlayer->MPtick(50);
}