#include "pch.h"
#include "CPlayerSkillBrick1.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CSound.h"

#include "CPlayerState.h"
#include "CPlayer.h"
#include "Skillbrick1.h"

void CPlayerSkillBrick1::KeyInput(CPlayer* player)
{
}

void CPlayerSkillBrick1::Update(CPlayer* player)
{
	_facc += DT;

	if (_facc >= _fDelay)
		player->ChangeState(CHANGESTATE(CPlayerState)::brick2);
}

void CPlayerSkillBrick1::Enter(CPlayer* player)
{
	_facc = 0;
	CSkill* brick = new Skillbrick1(player);	// 스킬생성
	_fDelay = brick->GetNextActTime();
	brick->Active();
	Instantiate(brick, LAYER::SKILL);

	player->GetRigidbody()->SetGravityAccel(0);
	player->GetRigidbody()->SetVelocity(Vec2(0, 0));

	player->SetInvincible();
}

void CPlayerSkillBrick1::Exit(CPlayer* player)
{
}