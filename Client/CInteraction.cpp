#include "pch.h"
#include "CInteraction.h"

#include "CTimeMgr.h"

CInteraction::CInteraction(CPlayer* _pPlayer)
	: m_pPlayer(_pPlayer)
	, m_pSound(nullptr)
	, m_fAcc(0.f)
	, m_fTime(1.f)
	, m_fNextActTime(1.f)
{
}

CInteraction::~CInteraction()
{
}

void CInteraction::tick()
{
	m_fAcc += DT;

	if (m_fAcc >= m_fTime)
		SetDead();

	CActor::tick();
}