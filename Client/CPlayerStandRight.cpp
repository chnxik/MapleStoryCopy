#include "pch.h"
#include "CPlayerStandRight.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayerState.h"
#include "CPlayer.h"

void CPlayerStandRight::KeyInput(CPlayer* player)
{
	player->attack();
	player->Jump();

	if (ISHOLD(KEY::LEFT) && ISHOLD(KEY::RIGHT))
		return;

	if (ISHOLD(KEY::RIGHT))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::walkright);
	}
	if (ISHOLD(KEY::LEFT))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::walkleft);
	}
	if (ISHOLD(KEY::DOWN))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::proneright);
	}
}

void CPlayerStandRight::Update(CPlayer* player)
{
	if (player->GetRigidbody()->IsGrnd() == false)
		player->ChangeState(CHANGESTATE(CPlayerState)::jumpright);
}

void CPlayerStandRight::Enter(CPlayer* player)
{
	player->SetDir(eDir::RIGHT);
	player->GetAnimator()->Play(L"stand_r", true);
}

void CPlayerStandRight::Exit(CPlayer* player)
{
}
