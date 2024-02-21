#include "pch.h"
#include "CUI.h"

#include "CResMgr.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CCsrMgr.h"

#include "CTexture.h"
#include "CSound.h"

CUI::CUI()
	: m_pParentUI(nullptr)
	, m_pIdleTex(nullptr)
	, m_bLbtnDown(false)
	, m_bMouseOn(false)
	, m_bOpen(true)
	, m_pOCSound(nullptr)
{
	m_pOCSound = CResMgr::GetInst()->LoadSound(L"click", L"sound\\etc\\BtMouseClick.wav");
}

CUI::CUI(const CUI& _other)
	: CActor(_other)
	, m_pParentUI(nullptr)
	, m_pIdleTex(_other.m_pIdleTex)
	, m_bLbtnDown(false)
	, m_bMouseOn(false)
	, m_bOpen(_other.m_bOpen)
	, m_pOCSound(_other.m_pOCSound)
{
	for (size_t i = 0; i < _other.m_vecChildUI.size(); ++i)
	{
		AddChildUI(_other.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	if (m_bMouseOn)
		CCsrMgr::GetInst()->SubCsrOnCnt();

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		delete m_vecChildUI[i];
	}
}

void CUI::tick()
{
	// 위치 계산
	m_vFinalPos = GetPos();

	if (m_pParentUI)
	{
		m_vFinalPos += m_pParentUI->GetFinalPos();
	}

	// 마우스 체크
	MouseOnCheck();

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->tick();
	}

	CActor::tick();
}

void CUI::render(HDC _dc)
{
	render_childUI(_dc);
}

void CUI::linerender(HDC _dc)
{
	if (CDebug::GetInst()->IsDebugOn())
	{
		Vec2 vPos = GetFinalPos();
		Vec2 vScale = GetScale();

		HPEN hPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
		HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

		HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);
		HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

		Rectangle(_dc,
			(int)vPos.x,
			(int)vPos.y,
			(int)(vPos.x + vScale.x),
			(int)(vPos.y + vScale.y));

		SelectObject(_dc, hOriginPen);
		SelectObject(_dc, hOriginBrush);
	}
}

void CUI::render_childUI(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::SetIdleTex(CTexture* _pTex)
{
	m_pIdleTex = _pTex;

	if (nullptr != m_pIdleTex)
	{
		Vec2 vScale = Vec2((float)m_pIdleTex->Width(), (float)m_pIdleTex->Height());
		SetScale(vScale);
	}
}

void CUI::UIOpen()
{
	m_bOpen = true;
	m_pOCSound->SetPosition(0);
	m_pOCSound->Play(false);
	
}

void CUI::UIClose()
{
	m_bOpen = false;
	m_pOCSound->SetPosition(0);
	m_pOCSound->Play(false);
}

void CUI::SetCsrState(CSRSTATE _CsrState)
{
	CCsrMgr::GetInst()->SetCsrState(_CsrState);
}

void CUI::MouseOnCheck()
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	Vec2 vMousePos = MOUSE_POS;

	if (IsCmrAfctd())
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x
		&& vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)
	{
		if(!m_bMouseOn)
			CCsrMgr::GetInst()->AddCsrOnCnt();
		
		m_bMouseOn = true;
	}
	else
	{
		if (m_bMouseOn)
			CCsrMgr::GetInst()->SubCsrOnCnt();

		m_bMouseOn = false;
	}
}

void UIClose()
{
}
