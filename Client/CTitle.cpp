#include "pch.h"
#include "CTitle.h"

#include "CLevelMgr.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CBackgrnd.h"
#include "CBtnUI.h"

#include "CSound.h"

#include "CAnimator.h"

CTitle::CTitle()
	: m_fAcc(0.f)
	, m_bPlay(false)
	, m_pSound(nullptr)
{
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"logo");
	m_pSound = CResMgr::GetInst()->LoadSound(L"logosound", L"sound\\title\\WzLogo.wav");
}

CTitle::~CTitle()
{
}

void CTitle::tick()
{
	m_fAcc += DT;

	if (2.0f <= m_fAcc && !m_bPlay)
	{
		m_bPlay = true;
		GetAnimator()->Play(L"logo", false);
		m_pSound->Play(false);
	}
	
	CActor::tick();

	if (8.f <= m_fAcc)
		CLevelMgr::GetInst()->ChangeLevel(LEVEL_TYPE::LOGIN, 0);

}

void CTitle::render(HDC _dc)
{
	if (6.0f >= m_fAcc)
		CActor::render(_dc);
}

