#include "pch.h"
#include "Tomb.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CSound.h"

#include "CAnimator.h"
#include "CRigidbody.h"

#include "CPlayer.h"
#include "CPlayerDeadMessage.h"

Tomb::Tomb(CPlayer* pPlayer)
	: CInteraction(pPlayer)
	, m_fAcc(0.f)
	, m_TombPos(0)
{
	SetScale(pPlayer->GetScale());

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"tomb");

	SetSound(CResMgr::GetInst()->LoadSound(L"tomb", L"sound\\etc\\Tombstone.wav"));
	GetSound()->SetPosition(0.f);

	CActor::SetCmrAfctd(true);
}

Tomb::~Tomb()
{
}

void Tomb::tick()
{
	
	if (m_fAcc < 1.3f)
	{
		Vec2 vPos = m_TombPos;
		m_fAcc += DT;
		vPos.y = GetPlayer()->GetPos().y * m_fAcc / 1.3f;
		SetPos(vPos);
	}
	
	CActor::tick();
}

void Tomb::render(HDC _dc)
{
	CActor::render(_dc);
}

void Tomb::Active()
{
	Vec2 vPos = Vec2(GetPlayer()->GetPos());
	vPos.y -= CEngine::GetInst()->GetResolution().y;
	m_TombPos = vPos;
	SetPos(vPos);

	GetAnimator()->Play(L"tomb", false);
	GetSound()->SetPosition(0.f);
	GetSound()->Play(false);
}