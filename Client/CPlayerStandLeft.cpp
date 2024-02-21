#include "pch.h"
#include "CPlayerStandLeft.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayerState.h"
#include "CPlayer.h"

void CPlayerStandLeft::KeyInput(CPlayer* player)
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
		player->ChangeState(CHANGESTATE(CPlayerState)::proneleft);
	}
}

void CPlayerStandLeft::Update(CPlayer* player)
{
	if (player->GetRigidbody()->IsGrnd() == false)
		player->ChangeState(CHANGESTATE(CPlayerState)::jumpleft);
}

void CPlayerStandLeft::Enter(CPlayer* player)
{
	player->SetDir(eDir::LEFT);
	player->GetAnimator()->Play(L"stand_l", true);
}

void CPlayerStandLeft::Exit(CPlayer* player)
{
}
