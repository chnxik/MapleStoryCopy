#include "pch.h"
#include "DoubleJump.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayer.h"

DoubleJump::DoubleJump(CPlayer* pPlayer)
	: CSkill(pPlayer)
{
	SetScale(pPlayer->GetScale());

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"dbjump_l");
	GetAnimator()->CreateAnimation(L"dbjump_r");

	SetSound(CResMgr::GetInst()->LoadSound(L"shift", L"sound\\skill\\shift.wav"));
	GetSound()->SetVolume(SKILLVOLUME);
	GetSound()->SetPosition(0.f);
	SetTime(0.4f);

	CActor::SetCmrAfctd(true);
}

DoubleJump::~DoubleJump()
{
}

void DoubleJump::tick()
{
	CSkill::tick();
}

void DoubleJump::render(HDC _dc)
{
	CActor::render(_dc);
}

void DoubleJump::Active()
{
	Vec2 vPos = GetPlayer()->GetPos();
	SetPos(vPos);

	if (GetPlayer()->GetDir() == eDir::LEFT)
	{
		GetPlayer()->GetAnimator()->Play(L"jump_l", false);
		GetAnimator()->Play(L"dbjump_l", false);
		GetSound()->Play(false);
		GetPlayer()->GetRigidbody()->SetVelocityLimit(800.f);
		GetPlayer()->GetRigidbody()->SetVelocity(Vec2(-800.f, -500.f));
	}
	else
	{
		GetPlayer()->GetAnimator()->Play(L"jump_r", false);
		GetAnimator()->Play(L"dbjump_r", false);
		GetSound()->Play(false);
		GetPlayer()->GetRigidbody()->SetVelocityLimit(800.f);
		GetPlayer()->GetRigidbody()->SetVelocity(Vec2(800.f, -500.f));
	}
}