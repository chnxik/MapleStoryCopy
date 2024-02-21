#include "pch.h"
#include "CSpawner.h"

#include "CLevelMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CCamera.h"

#include "CMob.h"

#include "CLevel.h"
#include "CToolLevel.h"
#include "CTexture.h"

#include "Mob_Snail.h"
#include "Mob_BlueSnail.h"
#include "Mob_Mushmom.h"
#include "Mob_Priestmem.h"

CSpawner::CSpawner()
	: m_eMob(MOB_TYPE::END)
	, m_bSpawn(false)
	, m_fZen(3.f)
	, m_fZenAcc(3.f)
	, m_pTexture(nullptr)
{
}

CSpawner::~CSpawner()
{
}

void CSpawner::tick()
{
	CActor::tick();

	if (m_bSpawn)
		return;

	m_fZenAcc += DT;
	if(m_fZenAcc >= m_fZen)
		CreateMob();
}

void CSpawner::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	
	if (nullptr != m_pTexture)
	{
		if (dynamic_cast<CToolLevel*>(CLevelMgr::GetInst()->GetCurLevel()))
		{
			OpRender(_dc, m_pTexture, vPos, 100);
				CActor::render(_dc);
		}

		if (CDebug::GetInst()->IsDebugOn())
		{

			if (CDebug::GetInst()->IsDebugTextOn())
			{
				RECT rt = { (LONG)(vPos.x - 50),
							(LONG)(vPos.y - 50),
							(LONG)(vPos.x + 50),
							(LONG)(vPos.y) };	// 문자가 써질 사각형

				wchar_t szBuff[256] = {};
				swprintf_s(szBuff, L"Mob\n%s", m_MobKey.c_str());

				SetBkMode(_dc, OPAQUE);				// 문자 배경 투명 설정
				DrawText(_dc, szBuff, -1, &rt, DT_CENTER);	// 문자 출력
			}
		}
	}
}

void CSpawner::SetSpawner(wstring _strMobKey)
{
	m_MobKey = _strMobKey;

	if (dynamic_cast<CToolLevel*>(CLevelMgr::GetInst()->GetCurLevel()))
	{
		if (m_pTexture == nullptr)
		{
			wstring MobTexKey = m_MobKey + L"_spawner";
			wstring MobTexPath = L"texture\\mob\\spawner\\" + m_MobKey + L".png";
			m_pTexture = CResMgr::GetInst()->LoadTexture(MobTexKey, MobTexPath);
		}

		SetScale(Vec2(m_pTexture->Width(), m_pTexture->Height()));
	}
}

void CSpawner::CreateMob()
{
	m_fZenAcc = 0.f;
	m_bSpawn = true;
	
	CMob* pNewMob;
	switch (m_eMob)
	{
	case MOB_TYPE::SNAIL:
	{
		pNewMob = new Mob_Snail(this);
		Instantiate(pNewMob, GetPos(), LAYER::MOB);
	}
	break;
	case MOB_TYPE::BLUESNAIL:
	{
		pNewMob = new Mob_BlueSnail(this);
		Instantiate(pNewMob, GetPos(), LAYER::MOB);
	}
	break;
	case MOB_TYPE::MUSHMOM:
	{
		pNewMob = new Mob_Mushmom(this);
		Instantiate(pNewMob, GetPos(), LAYER::MOB);
	}
	break;
	case MOB_TYPE::PRIESTOFMEM:
	{
		pNewMob = new Mob_Priestmem(this);
		Instantiate(pNewMob, GetPos(), LAYER::MOB);
	}
	case MOB_TYPE::END:
		break;
	default:
		break;
	}
}
