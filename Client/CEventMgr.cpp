#include "pch.h"
#include "CEventMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CActor.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::tick()
{
	// �������� ������Ʈ ����
	for (size_t i = 0; i < m_vecGarbage.size(); ++i)
	{
		delete m_vecGarbage[i];
	}
	m_vecGarbage.clear();


	// �̺�Ʈ ó��
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		switch (m_vecEvent[i].eType)
		{
		case EVENT_TYPE::CREATE_ACTOR: // wParam : Object Adress, lParam : Layer
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

			CActor* pNewAct = (CActor*)m_vecEvent[i].wParam;
			LAYER eLayer = (LAYER)m_vecEvent[i].lParam;

			pCurLevel->AddActor(pNewAct, eLayer);
		}
		break;
		case EVENT_TYPE::DELETE_ACTOR:
		{
			// �������� ������Ʈ�� Dead ���·� �ΰ� Garbage �� �ִ´�.
			CActor* pNewAct = (CActor*)m_vecEvent[i].wParam;

			// ���� Ȯ���� ���� tick ���� ���ÿ� ���� ������Ʈ�� ������û �� ��츦 ���
			if (false == pNewAct->m_bDead)
			{
				m_vecGarbage.push_back(pNewAct);
				pNewAct->m_bDead = true;
			}
		}
		break;


		case EVENT_TYPE::LEVEL_CHANGE:
		{
			// wParam : Next Level Type
			LEVEL_TYPE eNextLevel = (LEVEL_TYPE)m_vecEvent[i].wParam;
			UINT iPortalNo = (UINT)m_vecEvent[i].lParam;
			CLevelMgr::GetInst()->ChangeLevel(eNextLevel, iPortalNo);
		}
		break;
		}
	}

	m_vecEvent.clear();
}
