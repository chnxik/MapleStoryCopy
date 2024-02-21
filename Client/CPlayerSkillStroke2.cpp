#include "pch.h"
#include "CPlayerSkillStroke2.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CSound.h"

#include "CPlayerState.h"
#include "CPlayer.h"
#include "SkillStroke2.h"

void CPlayerSkillStroke2::KeyInput(CPlayer* player)
{
}

void CPlayerSkillStroke2::Update(CPlayer* player)
{
	_facc += DT;

	if (_facc >= _fDelay)
		player->Idle();
}

void CPlayerSkillStroke2::Enter(CPlayer* player)
{
	_facc = 0;
	CSkill* stroke = new SkillStroke2(player);	// 스킬생성
	_fDelay = stroke->GetNextActTime();
	stroke->Active();
	Instantiate(stroke, LAYER::SKILL);
	player->SetAlert();
}

void CPlayerSkillStroke2::Exit(CPlayer* player)
{
}