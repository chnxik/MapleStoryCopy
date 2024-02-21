#include "pch.h"
#include "CToolLevel.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEngine.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CCollisionMgr.h"

#include "CTexture.h"

#include "CBackgrnd.h"
#include "CMap.h"

#include "CUI.h"
#include "CPNUI.h"
#include "CToolCell.h"
#include "CToolInven.h"
#include "CDummy.h"

#include "CLine.h"
#include "CPlatform.h"
#include "CWall.h"
#include "CRope.h"
#include "CLadder.h"
#include "CSpawner.h"
#include "CPortal.h"


void CToolLevel::UpdateCurTool(TOOL_TYPE _Tool, CToolCell* _Cell)
{
	m_eCurTool = _Tool;
	m_pCurCell = _Cell;
	if (m_pCurLine)
	{
		m_pCurLine->SetDead();
		m_pCurLine = nullptr;
	}
}

void CToolLevel::DrawLine(TOOL_TYPE _Tool)
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	if (0.f < vMousePos.x && 0.f < vMousePos.y &&
		vMousePos.x < vResolution.x && vMousePos.y < vResolution.y)
	{

		if (!m_pCurLine)
		{
			if (ISTAP(KEY::RBTN))
			{
				CLine*	pLine = nullptr;
				LAYER	_layer = LAYER::END;

				switch (_Tool)
				{
				case TOOL_TYPE::DRAWPLATFORM:
				{
					pLine = new CPlatform;
					_layer = LAYER::PLATFORM;
					dynamic_cast<CPlatform*>(pLine)->SetEarth(false);
				}
					break;
				case TOOL_TYPE::DRAWEARTH:
				{
					pLine = new CPlatform;
					_layer = LAYER::PLATFORM;
					dynamic_cast<CPlatform*>(pLine)->SetEarth(true);
				}
					break;
				case TOOL_TYPE::DRAWWALL_LEFT:
				{
					pLine = new CWall;
					_layer = LAYER::MAP;
					dynamic_cast<CWall*>(pLine)->SetWallDir(eDir::LEFT);
					dynamic_cast<CWall*>(pLine)->SetOnlyMob(false);
				}
					break;
				case TOOL_TYPE::DRAWWALL_RIGHT:
				{
					pLine = new CWall;
					_layer = LAYER::MAP;
					dynamic_cast<CWall*>(pLine)->SetWallDir(eDir::RIGHT);
					dynamic_cast<CWall*>(pLine)->SetOnlyMob(false);
				}
					break;
				case TOOL_TYPE::DRAWMOBWALL_LEFT:
				{
					pLine = new CWall;
					_layer = LAYER::MAP;
					dynamic_cast<CWall*>(pLine)->SetWallDir(eDir::LEFT);
					dynamic_cast<CWall*>(pLine)->SetOnlyMob(true);
				}
					break;
				case TOOL_TYPE::DRAWMOBWALL_RIGHT:
				{
					pLine = new CWall;
					_layer = LAYER::MAP;
					dynamic_cast<CWall*>(pLine)->SetWallDir(eDir::RIGHT);
					dynamic_cast<CWall*>(pLine)->SetOnlyMob(true);
				}
					break;
				case TOOL_TYPE::DRAWROPE:
				{
					pLine = new CRope;
					_layer = LAYER::MAP;
				}
					break;
				case TOOL_TYPE::DRAWLADDER:
				{
					pLine = new CLadder;
					_layer = LAYER::MAP;
				}
					break;
				}

				if (pLine != nullptr)
				{
					vMousePos = CCamera::GetInst()->GetRealPos(vMousePos); // 마우스 좌표가 가리키는 실제 포지션으로 변환
					m_pCurLine = pLine;
					Instantiate(m_pCurLine, Vec2(0, 0), _layer);
					pLine->SetLdot(vMousePos);
					pLine->SetRdot(vMousePos);
				}
			}
		}

		else
		{
			Vec2 LastDot = CCamera::GetInst()->GetRealPos(vMousePos);
			LAYER _layer = LAYER::END;

				switch (_Tool)
				{
				case TOOL_TYPE::DRAWPLATFORM:
				case TOOL_TYPE::DRAWEARTH:
				{
					_layer = LAYER::PLATFORM;
					m_pCurLine->SetRdot(LastDot);
					if (ISHOLD(KEY::LSHIFT))
					{
						LastDot = Vec2(LastDot.x, m_pCurLine->GetLdot().y);
						m_pCurLine->SetRdot(LastDot);
					}
				}
				break;
				case TOOL_TYPE::DRAWWALL_LEFT:
				case TOOL_TYPE::DRAWWALL_RIGHT:
				case TOOL_TYPE::DRAWMOBWALL_LEFT:
				case TOOL_TYPE::DRAWMOBWALL_RIGHT:
				case TOOL_TYPE::DRAWROPE:
				case TOOL_TYPE::DRAWLADDER:
				{
					_layer = LAYER::MAP;
					LastDot = Vec2(m_pCurLine->GetLdot().x, LastDot.y);
					m_pCurLine->SetRdot(LastDot);
				}
				break;
				}


			if (ISTAP(KEY::RBTN))
			{
				m_pCurLine->SetLine(m_pCurLine->GetLdot(), m_pCurLine->GetRdot());
				CDummy* pDummy = new CDummy;
				pDummy->SetLineDummy(m_pCurLine, _Tool, _layer);
				Instantiate(pDummy, LAYER::PLAYERUI);
				m_mapData.insert(make_pair(pDummy->GetKey(), pDummy));								// 작업 더미에 추가.
				m_pCurLine = nullptr;
			}

			if (ISTAP(KEY::ESC))
			{
				m_pCurLine->SetDead();
				m_pCurLine = nullptr;
			}

		}
	}
}

void CToolLevel::CreateMapObj(TOOL_TYPE _Tool)
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

	CActor* pMapObj = nullptr;
	LAYER	_layer = LAYER::END;

	if (ISTAP(KEY::RBTN))
	{
		switch (_Tool)
		{
		case TOOL_TYPE::CREATEMOB:
		{
			pMapObj = new CSpawner;
			_layer = LAYER::MOB;
			((CSpawner*)pMapObj)->SetSpawner(m_pCurCell->GetMobKey()); // 스포너에 몹 이름 전달 및 정보세팅
			((CSpawner*)pMapObj)->SetMob(m_pCurCell->GetCellNumb()); // 셀enum class 전달
			Instantiate(pMapObj, vMousePos, _layer);
		}
		break;
		case TOOL_TYPE::CREATENPC:
			break;
		case TOOL_TYPE::CREATEPORTAL:
		{
			pMapObj = CPortal::CreatePortal();
			
			if (pMapObj == nullptr)
				return;

			_layer = LAYER::MAPOBJ;
			AddPortal((CPortal*)pMapObj, ((CPortal*)pMapObj)->GetPortalNo());
			Instantiate(pMapObj, vMousePos, _layer);
		}
			break;
		case TOOL_TYPE::NONE:
			break;
		default:
			break;
		}

		CDummy* pDummy = new CDummy;
		pDummy->SetObjDummy(pMapObj, _Tool, _layer);
		Instantiate(pDummy, LAYER::PLAYERUI);
		m_mapData.insert(make_pair(pDummy->GetKey(), pDummy));								// 작업 더미에 추가.
	}
}

void CToolLevel::DeleteDummy(UINT _id)
{
	map<UINT, CDummy*>::iterator iter = m_mapData.find(_id);
	
	if (iter == m_mapData.end())
	{
		wstring errMsg = _id + L" 번 더미를 찾을 수 없습니다.\n 더미 삭제에 실패했습니다.";
		ShowCursor(true);
		MessageBox(nullptr, errMsg.c_str(), L"더미 삭제 실패", MB_OK);
		ShowCursor(false);
		return;
	}
	iter->second->GetActor()->SetDead();	// 더미에 연결된 객체 삭제
	iter->second->SetDead();				// 더미 삭제
	m_mapData.erase(iter);					// 더미를 저장했던 map 공간 삭제
}

void CToolLevel::DeleteAllDummy()
{
	map<UINT, CDummy*>::iterator iter = m_mapData.begin();

	if (iter == m_mapData.end())
		return;

	while(iter != m_mapData.end())
	{
		map<UINT, CDummy*>::iterator Deleteiter = iter++;

		Deleteiter->second->GetActor()->SetDead();
		Deleteiter->second->SetDead();
		m_mapData.erase(Deleteiter);
	}
}
