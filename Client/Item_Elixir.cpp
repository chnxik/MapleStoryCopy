#include "pch.h"
#include "Item_Elixir.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CSound.h"

#include "CPlayer.h"


Item_Elixir::Item_Elixir()
{
	SetItemType(ITEM_TYPE::ELIXIR);
	SetItemTex(CResMgr::GetInst()->LoadTexture(L"elixir", L"texture\\item\\elixir.png"));
	SetItemSound(CResMgr::GetInst()->LoadSound(L"potion", L"sound\\item\\potion.wav"));
}

Item_Elixir::~Item_Elixir()
{
}

void Item_Elixir::UseItem(CPlayer* pPlayer)
{
	GetUseSound()->SetPosition(0);
	GetUseSound()->Play(false);
	tStatus Status = pPlayer->GetStatus();

	pPlayer->HPtick((int)((float)Status.MaxHP * 0.5f));
	pPlayer->MPtick((int)((float)Status.MaxMP * 0.5f));
}