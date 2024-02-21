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

	// ���� ���� ����
	// UI Layer ��������

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	const vector<CActor*>& vecUI = pCurLevel->GetLayer(LAYER::PLAYERUI);

	for (int i = (int)vecUI.size() - 1; 0 <= i; --i)
	{
		m_pPriorityUI = GetPriorityUI((CUI*)vecUI[i]);	// ���� UI�� �켱���� UI�� �ִ��� Ȯ���Ѵ�.

		if (nullptr == m_pPriorityUI)	// �켱���� UI�� ���°�� ���� UI �˻縦 �����Ѵ�.
			continue;

		// ���콺�� �̺�Ʈ ȣ��
		m_pPriorityUI->MouseOn();

		// �̹��� LBTN�� ���ȴ�
		if (bLbtnTAP)
		{
			// LbtnDown �̺�Ʈ ȣ��
			m_pPriorityUI->MouseLbtnDown();

			// �θ� UI�� FocusedUI �� ����, ���� ���߿� �����ǵ����Ѵ�.
			m_pFocusedUI = (CUI*)vecUI[i];
			pCurLevel->SetFocusedUI(m_pFocusedUI);
			break;
		}

		// �̹��� LBTN�� ������
		else if (bLbtnAWAY)
		{
			// ������ �������� �ִ�.
			if (m_pPriorityUI->m_bLbtnDown)
			{
				// Ŭ�� �̺�Ʈ ȣ��
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

		// UI �� ���� Ȯ��
		if (pUI->IsMouseOn())
		{
			// �켱���� UI �� ����������, �� ���� �켱������ ���� �ٸ� UI �� ���� ���.
			// ���� UI �� LBTNDown ���¸� �����Ѵ�.
			if (bLbtnReleased && nullptr != pPriorityUI && pPriorityUI->IsLbtnDown())
			{
				pPriorityUI->m_bLbtnDown = false;
			}

			// �켱���� UI �� ����
			pPriorityUI = pUI;
		}

		// �켱���� UI �� ���� �ȵ� UI �� ���콺 ���������� �߻��ϸ� LBtnDown �� �����س��´�.
		else if (bLbtnReleased)
		{
			pUI->m_bLbtnDown = false;
		}
	}


	// ��� �˻簡 ������ ���� Ȯ�ε� �켱���� UI�� ��ȯ�Ѵ�.
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

		// UI �� ���� Ȯ��
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

		// UI �� ���� Ȯ��
		if (pUI->IsMouseOn())
			CCsrMgr::GetInst()->AddCsrOnCnt();
	}
}
