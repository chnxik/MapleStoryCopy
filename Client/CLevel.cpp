#include "pch.h"
#include "CLevel.h"

#include "CLevelMgr.h"
#include "CUIMgr.h"

#include "CActor.h"

#include "CEngine.h"
#include "CCamera.h"
#include "CToolLevel.h"
#include "CUI.h"

CLevel::CLevel()
	: m_pCurMap(nullptr)
	, m_pCurBackgrnd(nullptr)
	, m_pCurBgm(nullptr)
	, m_pPortal{}
	, m_bInitcomplet(false)
{
}

CLevel::~CLevel()
{
	// 오브젝트 삭제
	DeleteAllActor();
}

void CLevel::tick()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		if (CLevelMgr::GetInst()->IsWaiting() && (i == (UINT)LAYER::PLAYER))
			continue;

		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			m_arrLayer[i][j]->tick();
		}
	}
}

void CLevel::final_tick()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			m_arrLayer[i][j]->final_tick();
		}
	}
}

void CLevel::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		vector<CActor*>::iterator iter = m_arrLayer[i].begin();

		for (; iter != m_arrLayer[i].end();)
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrLayer[i].erase(iter);
			}
			else
			{
				(*iter)->render(_dc);
				++iter; 
			}
		}
	}
}


void CLevel::DeleteAllActor()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		if (i == (UINT)LAYER::PLAYER || i == (UINT)LAYER::PLAYERUI)
			continue;

		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			if (m_arrLayer[i][j]->IsDead())
				continue;

			DEL(m_arrLayer[i][j]);
		}

		// 동적할당 해제시킨 주소값들을 벡터내에서 비워내기
		m_arrLayer[i].clear();
	}
}

void CLevel::DeleteActor(LAYER _eLayer)
{
	vector<CActor*>::iterator iter = m_arrLayer[(UINT)_eLayer].begin();

	for(; iter != m_arrLayer[(UINT)_eLayer].end();)
	{
		iter = m_arrLayer[(UINT)_eLayer].erase(iter);
	}
}

void CLevel::SetFocusedUI(CActor* _pUI)
{
	vector<CActor*>& vecUI = m_arrLayer[(UINT)LAYER::PLAYERUI];	// UILayer를 가져온다.

	if (vecUI.back() == _pUI)	// UILayer의 제일 위에있는 UI가 인자UI와 같다면 return.
		return;

	vector<CActor*>::iterator iter = vecUI.begin();	// UILayer의 iterator를 가져온다.

	for (; iter != vecUI.end(); ++iter)
	{
		if ((*iter) == _pUI)	// Focusing 할 UI를 찾으면 vector에서 뺀다음 다시 제일 마지막으로 넣는다.
		{
			vecUI.erase(iter);
			vecUI.push_back(_pUI);
			return;
		}
	}

	// Focued UI 가 잡히지 않는경우 예외처리
	assert(nullptr);
}

void CLevel::CloseUI(CActor* _pUI)
{
	vector<CActor*>& vecUI = m_arrLayer[(UINT)LAYER::PLAYERUI];	// UILayer를 가져온다.

	vector<CActor*>::iterator iter = vecUI.begin();	// UILayer의 iterator를 가져온다.

	for (; iter != vecUI.end(); ++iter)
	{
		if ((*iter) == _pUI)	// Focusing 할 UI를 찾으면 vector에서 뺀다음 다시 제일 마지막으로 넣는다.
		{
			vecUI.erase(iter);
			CUIMgr::GetInst()->CloseUI((CUI*)_pUI);
			break;
		}
	}
}

void CLevel::OpenUI(CActor* _pUI)
{
	vector<CActor*>& vecUI = m_arrLayer[(UINT)LAYER::PLAYERUI];	// UILayer를 가져온다.

	vector<CActor*>::iterator iter = vecUI.begin();	// UILayer의 iterator를 가져온다.

	for (; iter != vecUI.end(); ++iter)
	{
		if ((*iter) == _pUI)	// Focusing 할 UI를 찾으면 vector에서 뺀다음 다시 제일 마지막으로 넣는다.
			return;
	}

	Instantiate(_pUI, LAYER::PLAYERUI);
	CUIMgr::GetInst()->OpenUI((CUI*)_pUI);
}
