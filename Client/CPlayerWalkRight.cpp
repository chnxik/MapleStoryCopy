#include "pch.h"
#include "CPlayerWalkRight.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayerState.h"
#include "CPlayer.h"

void CPlayerWalkRight::KeyInput(CPlayer* player)
{
	player->attack();
	player->Jump();

	if (ISHOLD(KEY::RIGHT))
	{
		player->GetRigidbody()->AddForce(Vec2(3000.f, 0.f));
	}
	if (ISTAP(KEY::LEFT))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::walkleft);
	}
	if (ISHOLD(KEY::DOWN))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::proneright);
	}
	if (ISAWAY(KEY::RIGHT))
	{
		player->Idle();
	}
}

void CPlayerWalkRight::Update(CPlayer* player)
{
	_acctime += 1 * DT;

	if (0.1f <= _acctime)
	{
		if (player->GetRigidbody()->IsGrnd() == false)
			player->ChangeState(CHANGESTATE(CPlayerState)::jumpright);
	}

	if (player->GetRigidbody()->IsGrnd())
		_acctime = 0.f;
}

void CPlayerWalkRight::Enter(CPlayer* player)
{
	_acctime = 0.f;
	player->SetDir(eDir::RIGHT);
	if (player->IsInvincible())
		player->GetAnimator()->Play(L"walk_r", true, FLASHGVALUE, true);
	else
		player->GetAnimator()->Play(L"walk_r", true);
}

void CPlayerWalkRight::Exit(CPlayer* player)
{
}