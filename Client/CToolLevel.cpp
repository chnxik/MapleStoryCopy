#include "pch.h"
#include "CToolLevel.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEngine.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CCamera.h"

#include "CTexture.h"
#include "CSound.h"

#include "CBackgrnd.h"
#include "CMap.h"

#include "CUI.h"
#include "CToolCell.h"
#include "CPNUI.h"
#include "CDummy.h"

#include "CPlatform.h"
#include "Client.h"

CToolLevel::CToolLevel()
	: m_pCurLine(nullptr)
	, m_pCurCell(nullptr)
	, m_eCurTool(TOOL_TYPE::NONE)
{
}

CToolLevel::~CToolLevel()
{
	// map 메모리 해제
	map<UINT, CDummy*>::iterator iter = m_mapData.begin();
	for (; iter != m_mapData.end();)
	{
		iter = m_mapData.erase(iter);
	}

	for (UINT j = 0; j < m_arrLayer[(UINT)LAYER::PLAYERUI].size(); ++j)
	{
		if (m_arrLayer[(UINT)LAYER::PLAYERUI][j]->IsDead())
			continue;

		DEL(m_arrLayer[(UINT)LAYER::PLAYERUI][j]);
	}

	// 동적할당 해제시킨 주소값들을 벡터내에서 비워내기
	m_arrLayer[(UINT)LAYER::PLAYERUI].clear();
}

void CToolLevel::tick()
{
	switch (m_eCurTool)
	{
	case TOOL_TYPE::DRAWPLATFORM:
	case TOOL_TYPE::DRAWEARTH:
	case TOOL_TYPE::DRAWWALL_LEFT:
	case TOOL_TYPE::DRAWWALL_RIGHT:
	case TOOL_TYPE::DRAWMOBWALL_LEFT:
	case TOOL_TYPE::DRAWMOBWALL_RIGHT:
	case TOOL_TYPE::DRAWROPE:
	case TOOL_TYPE::DRAWLADDER:
	{
		DrawLine(m_eCurTool);
	}

		break;
	case TOOL_TYPE::CREATEMOB:
	case TOOL_TYPE::CREATEPORTAL:
	{
		CreateMapObj(m_eCurTool);
	}
		break;
	case TOOL_TYPE::NONE:
		break;
	}

	CLevel::tick();
}

void CToolLevel::Enter(UINT _iPortalNo)
{
	init();
}

void CToolLevel::Exit()
{
}
