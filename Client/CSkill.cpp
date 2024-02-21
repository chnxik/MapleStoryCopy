#include "pch.h"
#include "CSkill.h"

#include "CPlayerMgr.h"
#include "CCollisionMgr.h"
#include "CTimeMgr.h"
#include "CBattleMgr.h"
#include "CPlayerMgr.h"

#include "CPlayer.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CSound.h"

#include "CMob.h"


CSkill::CSkill(CPlayer* _pPlayer)
	: CInteraction(_pPlayer)
	, m_pHitSound(nullptr)
	, m_iMaxTarget(1)
	, m_iTarget(0)
	, m_fSkillDmg(1.f)
	, m_iMaxHitCnt(1)
	, m_iHitCnt(0)
	, m_iSkillLv(0)
	, m_fHitDelay(0.1f)
	, m_fHitAcc(0.f)
{
}

CSkill::~CSkill()
{
}

void CSkill::tick()
{
	m_fHitAcc += DT;

	if (m_fHitDelay <= m_fHitAcc)
	{
		if (m_iHitCnt < m_iMaxHitCnt)
		{
			for (UINT i = 0; i < (UINT)m_vecTarget.size(); ++i)
			{
				if (m_vecTarget[i] != nullptr)
					CBattleMgr::GetInst()->Battle(this, m_vecTarget[i], i, m_iHitCnt);
			}
			++m_iHitCnt;
		}
		m_fHitAcc = 0.f;
	}

	CInteraction::tick();
}

void CSkill::render(HDC _dc)
{
	CActor::render(_dc);
}

void CSkill::SetSkillDmg(SKILL _skill, float _DefaultDmg, float _LvScale)
{
	m_iSkillLv = CPlayerMgr::GetInst()->GetSkillLv(_skill);
	m_fSkillDmg = _DefaultDmg + ((float)m_iSkillLv * _LvScale);
}


void CSkill::AddTarget(CMob* _Mob)
{
	if (m_iTarget < m_iMaxTarget)
	{
		++m_iTarget;
		m_vecTarget.push_back(_Mob);
	}
}

void CSkill::BeginOverlap(CCollider* _pOther)
{
	CMob* pMob = dynamic_cast<CMob*>(_pOther->GetOwner());
	if (pMob)
		AddTarget(pMob);
}

void CSkill::OnOverlap(CCollider* _pOther)
{
}
