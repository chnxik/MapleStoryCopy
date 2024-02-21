#include "pch.h"
#include "CPlayerSkillShotgun2.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CSound.h"

#include "CPlayerState.h"
#include "CPlayer.h"
#include "Skillshotgun2.h"

void CPlayerSkillShotgun2::KeyInput(CPlayer* player)
{
}

void CPlayerSkillShotgun2::Update(CPlayer* player)
{
	_facc += DT;

	if (_facc >= _fDelay)
		player->ChangeState(CHANGESTATE(CPlayerState)::shotgun3);
}

void CPlayerSkillShotgun2::Enter(CPlayer* player)
{
	_facc = 0;
	CSkill* shotgun = new Skillshotgun2(player);	// 스킬생성
	_fDelay = shotgun->GetNextActTime();
	shotgun->Active();
	Instantiate(shotgun, LAYER::SKILL);
}

void CPlayerSkillShotgun2::Exit(CPlayer* player)
{
	player->GetRigidbody()->SetGravityAccel(2500.f);
}