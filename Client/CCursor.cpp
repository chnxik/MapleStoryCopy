#include "pch.h"
#include "CCursor.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCsrMgr.h"
#include "CResMgr.h"

#include "CAnimator.h"
#include "CKeyMgr.h"
#include "CSound.h"
#include "CTexture.h"


CCursor::CCursor()
	: m_vItemCsrOffset{}
	, m_eApplyCsrState (CSRSTATE::IDLE)
	, m_ePrevCsrState (CSRSTATE::IDLE)

	, m_ItemCsr(nullptr)
{
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"idlecsr");
	GetAnimator()->CreateAnimation(L"clickcsr");
	GetAnimator()->CreateAnimation(L"grabcsr");
	GetAnimator()->CreateAnimation(L"onclickcsr");
	GetAnimator()->CreateAnimation(L"ongripcsr");
	
	m_CsrSound[(UINT)CSRSTATE::IDLE] = CResMgr::GetInst()->LoadSound(L"click",L"sound\\etc\\BtMouseClick.wav");
	m_CsrSound[(UINT)CSRSTATE::GRIP] = CResMgr::GetInst()->LoadSound(L"click",L"sound\\etc\\BtMouseClick.wav");
	
	GetAnimator()->Play(L"idlecsr", false);
}

CCursor::~CCursor()
{
}

void CCursor::tick()
{
	CActor::tick();
	SetPos(CKeyMgr::GetInst()->GetMousePos());

	if (!(ISHOLD(KEY::LBTN)))
	{
		if (0 == CCsrMgr::GetInst()->GetCsrOnCnt()) CCsrMgr::GetInst()->SetCsrState(CSRSTATE::IDLE);
		if (m_eApplyCsrState != CCsrMgr::GetInst()->GetCsrState())
		{
			m_eApplyCsrState = CCsrMgr::GetInst()->GetCsrState();
			// 바뀐 스테이트에 맞게 재생
			switch (m_eApplyCsrState)
			{
			case CSRSTATE::IDLE:
				GetAnimator()->Play(L"idlecsr", false);
				break;
			case CSRSTATE::IDLE_On:
				GetAnimator()->Play(L"onclickcsr", true);
				break;
			case CSRSTATE::GRIP:
				GetAnimator()->Play(L"ongripcsr", true);
				break;
			}
		}
	}
	

	switch (m_eApplyCsrState)
	{
	case CSRSTATE::IDLE:
	{
		if (ISTAP(KEY::LBTN))
		{
			GetAnimator()->Play(L"clickcsr", false);
			m_CsrSound[(UINT)CSRSTATE::IDLE]->Play(false);
		}
		if (ISAWAY(KEY::LBTN))
		{
			GetAnimator()->Play(L"idlecsr", false);
		}
	}
	break;
	case CSRSTATE::IDLE_On:
	{
		if (ISTAP(KEY::LBTN))
		{
			GetAnimator()->Play(L"clickcsr", false);
			m_CsrSound[(UINT)CSRSTATE::IDLE]->Play(false);
		}
		if (ISAWAY(KEY::LBTN))
		{
			GetAnimator()->Play(L"onclickcsr", true);
		}
	}
	break;
	case CSRSTATE::GRIP:
	{
		if (ISTAP(KEY::LBTN))
		{
			GetAnimator()->Play(L"grabcsr", false);
			m_CsrSound[(UINT)CSRSTATE::IDLE]->Play(false);
		}
		if (ISAWAY(KEY::LBTN))
		{
			GetAnimator()->Play(L"ongripcsr", true);
		}
	}
	break;
	}
	
		
}

void CCursor::render(HDC _dc)
{

	Vec2 vPos = GetPos();
	
	if (CDebug::GetInst()->IsDebugOn())
	{
		RECT rt = { (LONG)(vPos.x),
					(LONG)(vPos.y - 10),
					(LONG)(vPos.x + 30),
					(LONG)(vPos.y + 20) };	// 문자가 써질 사각형

		wchar_t szBuff[256] = {};
		swprintf_s(szBuff, L"%d", CCsrMgr::GetInst()->GetCsrOnCnt());

		SetBkMode(_dc, TRANSPARENT);				// 문자 배경 투명 설정
		DrawText(_dc, szBuff, -1, &rt, DT_RIGHT);	// 문자 출력
	}

	if (m_ItemCsr)
	{
		OpRender(_dc, m_ItemCsr, vPos, m_vItemCsrOffset, 70);
	
		if(CDebug::GetInst()->IsDebugOn())
		{
			HPEN hPen = nullptr;

			hPen = CEngine::GetInst()->GetPen(PEN_TYPE::BOLD_GREEN);

			// DC 의 기존 펜과 브러시를 새로 가져온 것들로 대체한다
			HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);

			// DC 의 GDI 오브젝트들을 기존의 펜과 브러시로 되돌린다.
			SelectObject(_dc, hOriginPen);
			
			MoveToEx(_dc, (int)vPos.x - m_ItemCsr->Width()/2, (int)(vPos.y + m_ItemCsr->Height() + m_vItemCsrOffset.y), NULL);
			LineTo(_dc, (int)vPos.x + m_ItemCsr->Width()/2, (int)(vPos.y + m_ItemCsr->Height() + m_vItemCsrOffset.y));
		}
	}

		
	CActor::render(_dc);
}