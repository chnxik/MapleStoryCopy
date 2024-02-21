#include "pch.h"
#include "CPlayerProneLeft.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayerState.h"
#include "CPlayer.h"

void CPlayerProneLeft::KeyInput(CPlayer* player)
{
	if (ISAWAY(KEY::DOWN))
	{
		player->Idle();
	}
	if (ISTAP(KEY::RIGHT))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::proneright);
	}
	if (ISTAP(KEY::SPACE))
	{
		if (player->IsEarth())
		{
			player->Jump();
			player->ChangeState(CHANGESTATE(CPlayerState)::jumpleft);
		}
		else
		{
			player->DownJump();
			player->ChangeState(CHANGESTATE(CPlayerState)::jumpleft);
		}
	}
}

void CPlayerProneLeft::Update(CPlayer* player)
{
	if (player->GetRigidbody()->IsGrnd() == false)
		player->ChangeState(CHANGESTATE(CPlayerState)::jumpleft);
}

void CPlayerProneLeft::Enter(CPlayer* player)
{
	player->SetDir(eDir::LEFT);
	if (player->IsInvincible())
		player->GetAnimator()->Play(L"prone_l", true, FLASHGVALUE, true);
	else
		player->GetAnimator()->Play(L"prone_l", true);
}

void CPlayerProneLeft::Exit(CPlayer* player)
{
}