#include "pch.h"
#include "CToolCell.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CAnimationMgr.h"
#include "CResMgr.h"
#include "CCsrMgr.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CToolInven.h"

CToolCell::CToolCell(CToolInven* pToolInven, int m_CellNumb)
	: m_pToolInven(pToolInven)
	, m_CellNumb(m_CellNumb)
	, m_pMobTex(nullptr)
	, m_bSelected(false)
	, m_thisTool{ TOOL_TYPE::NONE,TOOL_TYPE::CREATEMOB }
{
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"selectcell");
}

CToolCell::~CToolCell()
{
}

void CToolCell::tick()
{
	CUI::tick();
}

void CToolCell::render(HDC _dc)
{
	linerender(_dc);

	switch (m_pToolInven->GetCurMode())
	{
	case TOOL_TAP::OBJ:
	{
		if (GetIdleTex())	// Idle Texture를 얻어와서 nullptr일경우 return시킨다.
			OpRender(_dc, GetIdleTex(), GetFinalPos(), 100);

	}
		break;
	case TOOL_TAP::MOB:
	{
		if (m_pMobTex)	// Idle Texture를 얻어와서 nullptr일경우 return시킨다.
			OpRender(_dc, m_pMobTex, GetFinalPos(), 100);
	}
		break;
	}


	CActor::render(_dc);
	render_childUI(_dc);
}

void CToolCell::MouseLbtnDown()
{
	CUI::MouseLbtnDown();
}

void CToolCell::MouseLbtnClicked()
{
	m_pToolInven->SelectCell(this);
	
	

	CUI::MouseLbtnClicked();
}

void CToolCell::MouseOn()
{
	SetCsrState(CSRSTATE::IDLE_On);
}

void CToolCell::SetSelect(bool _b)
{
	m_bSelected = _b;
	if (_b)
	{
		GetAnimator()->Play(L"selectcell", true);

		if (m_pToolInven->GetCurMode() == TOOL_TAP::MOB && m_pMobTex != nullptr)
		{
			wstring MobTexKey = m_strMobKey + L"_spawner";
			wstring MobTexPath = L"texture\\mob\\spawner\\" + m_strMobKey + L".png";
			CCsrMgr::GetInst()->SetItemCsr(CResMgr::GetInst()->LoadTexture(MobTexKey, MobTexPath),Vec2(0,0));
		}
		else if (m_pToolInven->GetCurMode() == TOOL_TAP::OBJ && m_thisTool[(UINT)TOOL_TAP::OBJ] == TOOL_TYPE::CREATEPORTAL)
		{
			CCsrMgr::GetInst()->SetItemCsr(CResMgr::GetInst()->LoadTexture(L"portal_tool", L"texture\\map\\mapobj\\portal_tool.png"),Vec2(-45,-215));
		}
		else
		{
			CCsrMgr::GetInst()->SetItemCsr(nullptr,Vec2(0,0));
		}
	}
	else
		GetAnimator()->EraseCurAnim();
}
