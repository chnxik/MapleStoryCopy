#include "pch.h"
#include "CPlayerSkillBrick4.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CSound.h"

#include "CPlayerState.h"
#include "CPlayer.h"
#include "Skillbrick4.h"

void CPlayerSkillBrick4::KeyInput(CPlayer* player)
{
}

void CPlayerSkillBrick4::Update(CPlayer* player)
{
	_facc += DT;

	if (_facc >= _fDelay)
		player->Idle();
}

void CPlayerSkillBrick4::Enter(CPlayer* player)
{
	_facc = 0;
	CSkill* brick = new Skillbrick4(player);	// 스킬생성
	_fDelay = brick->GetNextActTime();
	brick->Active();
	Instantiate(brick, LAYER::SKILL);

	CCamera::GetInst()->Shake(1.f);
	
	player->ReleaseInvincible();
	player->SetAlert();
}

void CPlayerSkillBrick4::Exit(CPlayer* player)
{
	player->GetRigidbody()->SetVelocityLimit(300.f);
	player->GetRigidbody()->SetGravityAccel(2500.f);
}