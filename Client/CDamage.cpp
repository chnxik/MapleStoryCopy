#include "pch.h"
#include "CDamage.h"

#include "CTimeMgr.h"

#include "CResMgr.h"
#include "CTexture.h"

CDamage::CDamage(int _num,DMG_TYPE type)
	: m_pTex(nullptr)
	, m_iNumb(_num)
	, m_fRatio(100.f)
{
	switch (type)
	{
	case PLAYER:
	{
		switch ((NUMB)m_iNumb)
		{
		case NUMB::_0:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"PDMGSKIN_0", L"texture\\Dmg\\Player\\0.png");
			break;
		case NUMB::_1:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"PDMGSKIN_1", L"texture\\Dmg\\Player\\1.png");
			break;
		case NUMB::_2:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"PDMGSKIN_2", L"texture\\Dmg\\Player\\2.png");
			break;
		case NUMB::_3:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"PDMGSKIN_3", L"texture\\Dmg\\Player\\3.png");
			break;
		case NUMB::_4:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"PDMGSKIN_4", L"texture\\Dmg\\Player\\4.png");
			break;
		case NUMB::_5:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"PDMGSKIN_5", L"texture\\Dmg\\Player\\5.png");
			break;
		case NUMB::_6:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"PDMGSKIN_6", L"texture\\Dmg\\Player\\6.png");
			break;
		case NUMB::_7:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"PDMGSKIN_7", L"texture\\Dmg\\Player\\7.png");
			break;
		case NUMB::_8:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"PDMGSKIN_8", L"texture\\Dmg\\Player\\8.png");
			break;
		case NUMB::_9:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"PDMGSKIN_9", L"texture\\Dmg\\Player\\9.png");
			break;
		}
	}
		break;
	case MOB:
	{
		switch ((NUMB)m_iNumb)
		{
		case NUMB::_0:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"MDMGSKIN_0", L"texture\\Dmg\\Mob\\0.png");
			break;
		case NUMB::_1:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"MDMGSKIN_1", L"texture\\Dmg\\Mob\\1.png");
			break;
		case NUMB::_2:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"MDMGSKIN_2", L"texture\\Dmg\\Mob\\2.png");
			break;
		case NUMB::_3:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"MDMGSKIN_3", L"texture\\Dmg\\Mob\\3.png");
			break;
		case NUMB::_4:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"MDMGSKIN_4", L"texture\\Dmg\\Mob\\4.png");
			break;
		case NUMB::_5:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"MDMGSKIN_5", L"texture\\Dmg\\Mob\\5.png");
			break;
		case NUMB::_6:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"MDMGSKIN_6", L"texture\\Dmg\\Mob\\6.png");
			break;
		case NUMB::_7:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"MDMGSKIN_7", L"texture\\Dmg\\Mob\\7.png");
			break;
		case NUMB::_8:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"MDMGSKIN_8", L"texture\\Dmg\\Mob\\8.png");
			break;
		case NUMB::_9:
			m_pTex = CResMgr::GetInst()->LoadTexture(L"MDMGSKIN_9", L"texture\\Dmg\\Mob\\9.png");
			break;
		}
	}
		break;
	}

	
}

CDamage::~CDamage()
{
	m_pTex = nullptr;
	delete m_pTex;
}

void CDamage::tick()
{
	m_fRatio -= 100 * DT;

	if (m_fRatio <= 0.f)
	{
		SetDead();
		return;
	}

	Vec2 vPos = GetPos();
	vPos.y -= 50 * DT;

	SetPos(vPos);
}

void CDamage::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	OpRender(_dc, m_pTex, vPos, (UINT)m_fRatio);
}
