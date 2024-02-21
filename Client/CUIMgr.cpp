#include "pch.h"
#include "CUIMgr.h"

#include "CLevelMgr.h"
#include "CCsrMgr.h"
#include "CLevel.h"
#include "CUI.h"

#include "CToolLevel.h"

#include "CKeyMgr.h"
#include "CCursor.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
	, m_pPriorityUI(nullptr)
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::tick()
{
	bool bLbtnTAP = ISTAP(KEY::LBTN);
	bool bLbtnAWAY = ISAWAY(KEY::LBTN);

	// 현재 레벨 접근
	// UI Layer 가져오기

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	const vector<CActor*>& vecUI = pCurLevel->GetLayer(LAYER::PLAYERUI);

	for (int i = (int)vecUI.size() - 1; 0 <= i; --i)
	{
		m_pPriorityUI = GetPriorityUI((CUI*)vecUI[i]);	// 현재 UI에 우선순위 UI가 있는지 확인한다.

		if (nullptr == m_pPriorityUI)	// 우선순위 UI가 없는경우 다음 UI 검사를 진행한다.
			continue;

		// 마우스온 이벤트 호출
		m_pPriorityUI->MouseOn();

		// 이번에 LBTN이 눌렸다
		if (bLbtnTAP)
		{
			// LbtnDown 이벤트 호출
			m_pPriorityUI->MouseLbtnDown();

			// 부모 UI를 FocusedUI 로 설정, 가장 나중에 렌더되도록한다.
			m_pFocusedUI = (CUI*)vecUI[i];
			pCurLevel->SetFocusedUI(m_pFocusedUI);
			break;
		}

		// 이번에 LBTN이 떼졌다
		else if (bLbtnAWAY)
		{
			// 이전에 눌린적이 있다.
			if (m_pPriorityUI->m_bLbtnDown)
			{
				// 클릭 이벤트 호출
				m_pPriorityUI->MouseLbtnClicked();
				m_pPriorityUI->m_bLbtnDown = false;
			}
		}
	}
}

CUI* CUIMgr::GetPriorityUI(CUI* _pParentUI)
{

	bool bLbtnReleased = ISAWAY(KEY::LBTN);

	CUI* pPriorityUI = nullptr;

	static queue<CUI*> _queue;
	_queue.push(_pParentUI);

	while (!_queue.empty())
	{
		CUI* pUI = _queue.front();
		_queue.pop();

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			_queue.push(vecChild[i]);
		}

		// UI 의 상태 확인
		if (pUI->IsMouseOn())
		{
			// 우선순위 UI 로 지정됐지만, 더 높은 우선순위를 가진 다른 UI 가 나온 경우.
			// 기존 UI 의 LBTNDown 상태를 갱신한다.
			if (bLbtnReleased && nullptr != pPriorityUI && pPriorityUI->IsLbtnDown())
			{
				pPriorityUI->m_bLbtnDown = false;
			}

			// 우선순위 UI 로 지정
			pPriorityUI = pUI;
		}

		// 우선순위 UI 로 지정 안된 UI 는 마우스 해제조건이 발생하면 LBtnDown 을 해제해놓는다.
		else if (bLbtnReleased)
		{
			pUI->m_bLbtnDown = false;
		}
	}


	// 모든 검사가 끝나면 현재 확인된 우선순위 UI를 반환한다.
	return pPriorityUI;
}

void CUIMgr::CloseUI(CUI* _pParentUI)
{
	static queue<CUI*> _Closequeue;
	_Closequeue.push(_pParentUI);

	while (!_Closequeue.empty())
	{
		CUI* pUI = _Closequeue.front();
		_Closequeue.pop();

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			_Closequeue.push(vecChild[i]);
		}

		// UI 의 상태 확인
		if (pUI->IsMouseOn())
			CCsrMgr::GetInst()->SubCsrOnCnt();
	}
}

void CUIMgr::OpenUI(CUI* _pParentUI)
{
	static queue<CUI*> _Openqueue;
	_Openqueue.push(_pParentUI);

	while (!_Openqueue.empty())
	{
		CUI* pUI = _Openqueue.front();
		_Openqueue.pop();

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			_Openqueue.push(vecChild[i]);
		}

		// UI 의 상태 확인
		if (pUI->IsMouseOn())
			CCsrMgr::GetInst()->AddCsrOnCnt();
	}
}
