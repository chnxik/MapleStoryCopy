#include "pch.h"
#include "CPlayerWalkLeft.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CRigidbody.h"
#include "CCollider.h"

#include "CPlayerState.h"
#include "CPlayer.h"

void CPlayerWalkLeft::KeyInput(CPlayer* player)
{
	player->attack();
	player->Jump();

	if (ISTAP(KEY::RIGHT))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::walkright);
	}
	if (ISHOLD(KEY::LEFT))
	{
		player->GetRigidbody()->AddForce(Vec2(-3000.f, 0.f));
	}
	if (ISHOLD(KEY::DOWN))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::proneleft);
	}
	if (ISAWAY(KEY::LEFT))
	{
		player->Idle();
	}
}

void CPlayerWalkLeft::Update(CPlayer* player)
{
	_acctime += 1 * DT;
	
	if (0.1f <= _acctime)
	{
		if (player->GetRigidbody()->IsGrnd() == false)
			player->ChangeState(CHANGESTATE(CPlayerState)::jumpleft);
	}
	
	if (player->GetRigidbody()->IsGrnd())
		_acctime = 0.f;
}

void CPlayerWalkLeft::Enter(CPlayer* player)
{
	_acctime = 0.f;
	player->SetDir(eDir::LEFT);
	if (player->IsInvincible())
		player->GetAnimator()->Play(L"walk_l", true, FLASHGVALUE, true);
	else
		player->GetAnimator()->Play(L"walk_l", true);
}

void CPlayerWalkLeft::Exit(CPlayer* player)
{
}