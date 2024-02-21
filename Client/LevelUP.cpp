#include "pch.h"
#include "LevelUP.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CRigidbody.h"

#include "CPlayer.h"

LevelUP::LevelUP(CPlayer* pPlayer)
	: CInteraction(pPlayer)
{
	SetScale(pPlayer->GetScale());

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"LevelUP");
	
	SetSound(CResMgr::GetInst()->LoadSound(L"LevelUP", L"sound\\etc\\LevelUP.wav"));
	GetSound()->SetPosition(0.f);
	SetTime(2.1f);

	CActor::SetCmrAfctd(true);
}

LevelUP::~LevelUP()
{
}

void LevelUP::tick()
{
	Vec2 vPos = GetPlayer()->GetPos();
	SetPos(vPos);
	CInteraction::tick();
}

void LevelUP::render(HDC _dc)
{
	CActor::render(_dc);
}

void LevelUP::Active()
{
	GetAnimator()->Play(L"LevelUP", false);
	GetSound()->SetPosition(0.f);
	GetSound()->Play(false);
}