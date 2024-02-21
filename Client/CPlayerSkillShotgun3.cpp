#include "pch.h"
#include "CPlayerSkillShotgun3.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CSound.h"

#include "CPlayerState.h"
#include "CPlayer.h"
#include "Skillshotgun3.h"

void CPlayerSkillShotgun3::KeyInput(CPlayer* player)
{
}

void CPlayerSkillShotgun3::Update(CPlayer* player)
{
	_facc += DT;

	if (_facc >= _fDelay)
		player->Idle();
}

void CPlayerSkillShotgun3::Enter(CPlayer* player)
{
	_facc = 0;
	CSkill* shotgun = new Skillshotgun3(player);	// 스킬생성
	_fDelay = shotgun->GetNextActTime();
	shotgun->Active();
	Instantiate(shotgun, LAYER::SKILL);
	player->ReleaseInvincible();
	player->SetAlert();
	player->GetRigidbody()->SetVelocityLimit(500.f);
	player->GetRigidbody()->SetGrnd(false);

	switch (player->GetDir())
	{
	case eDir::LEFT:
		player->GetRigidbody()->SetVelocity(Vec2(500.f, -500.f));
	break;
	case eDir::RIGHT:
		player->GetRigidbody()->SetVelocity(Vec2(-500.f, -500.f));
	break;
	}
}

void CPlayerSkillShotgun3::Exit(CPlayer* player)
{
	player->GetRigidbody()->SetVelocityLimit(300.f);
}