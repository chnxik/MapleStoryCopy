#include "pch.h"
#include "CPlayerProneRight.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayerState.h"
#include "CPlayer.h"

void CPlayerProneRight::KeyInput(CPlayer* player)
{

	if (ISAWAY(KEY::DOWN))
	{
		player->Idle();
	}
	if (ISTAP(KEY::LEFT))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::proneleft);
	}
	if (ISTAP(KEY::SPACE))
	{
		if (player->IsEarth())
		{
			player->Jump();
			player->ChangeState(CHANGESTATE(CPlayerState)::jumpright);
		}
		else
		{
			player->DownJump();
			player->ChangeState(CHANGESTATE(CPlayerState)::jumpright);
		}
	}
}

void CPlayerProneRight::Update(CPlayer* player)
{
	if (player->GetRigidbody()->IsGrnd() == false)
		player->ChangeState(CHANGESTATE(CPlayerState)::jumpright);
}

void CPlayerProneRight::Enter(CPlayer* player)
{
	player->SetDir(eDir::RIGHT);
	if (player->IsInvincible())
		player->GetAnimator()->Play(L"prone_r", true, FLASHGVALUE, true);
	else
		player->GetAnimator()->Play(L"prone_r", true);
}

void CPlayerProneRight::Exit(CPlayer* player)
{
}