#include "pch.h"
#include "CTab.h"

#include "CEngine.h"
#include "CResMgr.h"
#include "CKeyMgr.h"

#include "CToolInven.h"

#include "CTexture.h"
#include "CSound.h"

CTab::CTab()
	: m_eThisType(TOOL_TAP::END)
	, m_pSelectedTex(nullptr)
	, m_pTabSound(nullptr)
{
	m_pTabSound = CResMgr::GetInst()->LoadSound(L"Tab", L"sound\\etc\\Tab.wav");
	
}

CTab::~CTab()
{
	
}

void CTab::render(HDC _dc)
{
	linerender(_dc);

	CTexture* pCurTex;

	if (dynamic_cast<CToolInven*>(GetParentUI())->GetCurMode() == m_eThisType)
		pCurTex = m_pSelectedTex;
	else
		pCurTex = GetIdleTex();
	
	if (nullptr == pCurTex)	// Idle Texture를 얻어와서 nullptr일경우 return시킨다.
		return;

	OpRender(_dc, pCurTex, GetFinalPos(), 100);

	render_childUI(_dc);
}

void CTab::MouseLbtnDown()
{
	CUI::MouseLbtnDown();

	CToolInven* ParentUI = dynamic_cast<CToolInven*>(GetParentUI());
	
	assert(ParentUI);
	ParentUI->SetCurMode(m_eThisType);

	m_pTabSound->Play(false);
}

void CTab::MouseLbtnClicked()
{
}

void CTab::MouseOn()
{
	SetCsrState(CSRSTATE::IDLE_On);
}
