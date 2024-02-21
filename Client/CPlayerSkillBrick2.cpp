#include "pch.h"
#include "CPlayerSkillBrick2.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CSound.h"

#include "CPlayerState.h"
#include "CPlayer.h"
#include "Skillbrick2.h"

void CPlayerSkillBrick2::KeyInput(CPlayer* player)
{
}

void CPlayerSkillBrick2::Update(CPlayer* player)
{
	_facc += DT;

	if (_facc >= _fDelay)
		player->ChangeState(CHANGESTATE(CPlayerState)::brick3);
}

void CPlayerSkillBrick2::Enter(CPlayer* player)
{
	_facc = 0;
	CSkill* brick = new Skillbrick2(player);	// 스킬생성
	_fDelay = brick->GetNextActTime();
	brick->Active();
	Instantiate(brick, LAYER::SKILL);
}

void CPlayerSkillBrick2::Exit(CPlayer* player)
{
}