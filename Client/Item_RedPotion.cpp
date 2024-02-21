#include "pch.h"
#include "Item_RedPotion.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CSound.h"

#include "CPlayer.h"


Item_RedPotion::Item_RedPotion()
{
	SetItemType(ITEM_TYPE::REDPOTION);
	SetItemTex(CResMgr::GetInst()->LoadTexture(L"redpt", L"texture\\item\\redpt.png"));
	SetItemSound(CResMgr::GetInst()->LoadSound(L"potion", L"sound\\item\\potion.wav"));
}

Item_RedPotion::~Item_RedPotion()
{
}

void Item_RedPotion::UseItem(CPlayer* pPlayer)
{
	GetUseSound()->SetPosition(0);
	GetUseSound()->Play(false);
	pPlayer->HPtick(50);
}