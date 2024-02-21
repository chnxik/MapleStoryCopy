#include "pch.h"
#include "CPlayerSkillShotgun1.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CSound.h"

#include "CPlayerState.h"
#include "CPlayer.h"
#include "Skillshotgun1.h"

void CPlayerSkillShotgun1::KeyInput(CPlayer* player)
{
}

void CPlayerSkillShotgun1::Update(CPlayer* player)
{
	_facc += DT;
	if (_facc >= _fDelay)
		player->ChangeState(CHANGESTATE(CPlayerState)::shotgun2);
}

void CPlayerSkillShotgun1::Enter(CPlayer* player)
{
	_facc = 0;
	CSkill* shotgun = new Skillshotgun1(player);	// 스킬생성
	_fDelay = shotgun->GetNextActTime();
	shotgun->Active();
	Instantiate(shotgun, LAYER::SKILL);

	player->GetRigidbody()->SetGravityAccel(0);
	player->GetRigidbody()->SetVelocity(Vec2(0, 0));

	player->SetInvincible();
	player->SetAlert();
}

void CPlayerSkillShotgun1::Exit(CPlayer* player)
{
	
}