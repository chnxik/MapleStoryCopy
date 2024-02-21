#include "pch.h"
#include "CBtnUI.h"

#include "CLevelMgr.h"
#include "CToolLevel.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "CSound.h"


CBtnUI::CBtnUI()
	: m_pFunc(nullptr)
	, m_pOverTex(nullptr)
	, m_pPressTex(nullptr)
	, m_pDisAble(nullptr)
	, m_pInst(nullptr)
	, m_pDelegateFunc(nullptr)
	, m_pBtOverSound(nullptr)
	, m_bBtOnCheck(false)
	, m_bActive(true)
	, _DebugBtn(false)
{
	m_pBtOverSound = CResMgr::GetInst()->LoadSound(L"MsOverSound", L"sound\\etc\\BtMouseOver.wav");
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::render(HDC _dc)
{
	if (_DebugBtn && !CDebug::GetInst()->IsDebugOn())
		return;

	CTexture* pTargetTex = GetIdleTex();
	
	if (m_bActive)
	{

		if (IsLbtnDown())
		{
			if (m_pPressTex)
				pTargetTex = m_pPressTex;
		}
		else if (IsMouseOn())
		{
			if (m_pOverTex)
				pTargetTex = m_pOverTex;
		}
		else
		{
			m_bBtOnCheck = false;
		}
	}
	else
	{
		pTargetTex = m_pDisAble;
	}

	if (!pTargetTex)
	{
		CUI::render(_dc);
		return;
	}

	Vec2 vPos = GetFinalPos();
	vPos += m_vOffset;
	
	OpRender(_dc, pTargetTex, vPos, 100);

	render_childUI(_dc);
}

void CBtnUI::MouseLbtnDown()
{
	if (!m_bActive || _DebugBtn && !CDebug::GetInst()->IsDebugOn())
		return;

	CUI::MouseLbtnDown();
}

void CBtnUI::MouseLbtnClicked()
{
	if (!m_bActive || _DebugBtn && !CDebug::GetInst()->IsDebugOn())
		return;

	if (nullptr != m_pFunc)
		m_pFunc();

	if (m_pInst && m_pDelegateFunc)
	{
		(m_pInst->*m_pDelegateFunc)();
	}

	CUI::MouseLbtnClicked();
}

void CBtnUI::MouseOn()
{
	if (!m_bActive || _DebugBtn && !CDebug::GetInst()->IsDebugOn())
		return;

	if (!m_bBtOnCheck)
	{
		m_bBtOnCheck = true;
		if (nullptr != m_pBtOverSound)
			m_pBtOverSound->Play(false);
	}
}
