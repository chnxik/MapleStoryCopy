#include "pch.h"
#include "CPlayerSkillBrick3.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CSound.h"

#include "CPlayerState.h"
#include "CPlayer.h"
#include "Skillbrick3.h"

void CPlayerSkillBrick3::KeyInput(CPlayer* player)
{
}

void CPlayerSkillBrick3::Update(CPlayer* player)
{
	_facc += DT;

	if (_facc >= _fDelay)
		player->ChangeState(CHANGESTATE(CPlayerState)::brick4);
}

void CPlayerSkillBrick3::Enter(CPlayer* player)
{
	_facc = 0;
	CSkill* brick = new Skillbrick3(player);	// 스킬생성
	_fDelay = brick->GetNextActTime();
	brick->Active();
	Instantiate(brick, LAYER::SKILL);

	player->GetRigidbody()->SetGrnd(false);
	player->GetRigidbody()->SetVelocityLimit(500.f);
	player->GetRigidbody()->SetGravityAccel(2500.f);

	switch (player->GetDir())
	{
	case eDir::LEFT:
	{
		player->GetRigidbody()->SetVelocity(Vec2(-500.f, -500.f));
	}
	break;
	case eDir::RIGHT:
	{
		player->GetRigidbody()->SetVelocity(Vec2(500.f, -500.f));
	}
	break;
	}
}

void CPlayerSkillBrick3::Exit(CPlayer* player)
{
	player->GetRigidbody()->SetVelocityLimit(300.f);
}