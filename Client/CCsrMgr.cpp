#include "pch.h"
#include "CCsrMgr.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CAnimationMgr.h"

#include "CActor.h"
#include "CCursor.h"

CCsrMgr::CCsrMgr()
	: m_pCursor(nullptr)
	, m_eCsrState(CSRSTATE::IDLE)
	, m_iCsrOnCnt(0)
{
}

CCsrMgr::~CCsrMgr()
{
	DEL(m_pCursor);
}

void CCsrMgr::init()
{
	m_pCursor = new CCursor;
	m_pCursor->SetPos(CKeyMgr::GetInst()->GetMousePos());
	ShowCursor(false);
}

void CCsrMgr::tick()
{
	if (0 == m_iCsrOnCnt)
		m_eCsrState = CSRSTATE::IDLE;

	m_pCursor->tick();
	m_pCursor->final_tick();
}

void CCsrMgr::render(HDC _dc)
{
	m_pCursor->render(_dc);
}

void CCsrMgr::SetItemCsr(CTexture* _pTex,Vec2 _Offset)
{
	m_pCursor->m_ItemCsr = _pTex;
	m_pCursor->m_vItemCsrOffset = _Offset;
}