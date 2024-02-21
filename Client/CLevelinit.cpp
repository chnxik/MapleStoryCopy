#include "pch.h"
#include "CLevel.h"

#include "CEngine.h"
#include "CPathMgr.h"
#include "CLevelMgr.h"
#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CCollisionMgr.h"
#include "CCamera.h"
#include "CPlayerMgr.h"

#include "CTexture.h"
#include "CSound.h"

#include "CBackgrnd.h"
#include "CMap.h"

#include "CUI.h"

#include "CLine.h"
#include "CPlatform.h"
#include "CWall.h"
#include "CRope.h"
#include "CLadder.h"
#include "CSpawner.h"
#include "CPortal.h"
#include "CPlayer.h"

// UI
#include "CStatusBarUI.h"
#include "CExpBarUI.h"
#include "CQuickSlotUI.h"
#include "CPlayerStatWin.h"
#include "CPlayerSkillWin.h"

void CLevel::PortalInit(PORTAL _CurMapPortal, PORTAL _NextMapPortal, LEVEL_TYPE _NextLevelType)
{
	m_pPortal[(UINT)_CurMapPortal]->SetPortalInfo(_NextLevelType, (UINT)_NextMapPortal);
}

void CLevel::CreatePlayer(UINT _iPortalNo)
{
	Vec2 vPos = m_pPortal[_iPortalNo]->GetSpawnPos();
	
	CPlayer* pPlayer = CPlayerMgr::GetInst()->GetPlayer();
	Instantiate(pPlayer, vPos, LAYER::PLAYER);
	CCamera::GetInst()->SetTarget(pPlayer);
	CCamera::GetInst()->SetLook(vPos);

	Instantiate(CPlayerMgr::GetInst()->GetStatusBar(), LAYER::PLAYERUI);
	Instantiate(CPlayerMgr::GetInst()->GetExpBar(), LAYER::PLAYERUI);
	Instantiate(CPlayerMgr::GetInst()->GetQuickSlot(), LAYER::PLAYERUI);
}

void CLevel::CreatePlayer(Vec2 _vPos)
{
	CPlayer* pPlayer = CPlayerMgr::GetInst()->GetPlayer();
	Instantiate(pPlayer, _vPos, LAYER::PLAYER);
	CCamera::GetInst()->SetTarget(pPlayer);
	CCamera::GetInst()->SetLook(_vPos);

	Instantiate(CPlayerMgr::GetInst()->GetStatusBar(), LAYER::PLAYERUI);
	Instantiate(CPlayerMgr::GetInst()->GetExpBar(), LAYER::PLAYERUI);
	Instantiate(CPlayerMgr::GetInst()->GetQuickSlot(), LAYER::PLAYERUI);
}

void CLevel::ChangeBgm()
{
	CSoundMgr::GetInst()->RegisterToBGM(m_pCurBgm);
	m_pCurBgm->PlayToBGM(true);
	m_pCurBgm->SetVolume(20);
}

void CLevel::MapFileLoad(wstring _mapFileName)
{
	// 제작한 맵 파일을 불러와서 배경, 맵, 음악, 오브젝트 세팅들을 해준다.
	wstring strMapFilrPath = CPathMgr::GetInst()->GetContentPath();
	strMapFilrPath += L"data\\map\\" + _mapFileName + L".map";

	wifstream ifs;

	ifs.open(strMapFilrPath, std::ios::binary);

	if (!ifs.is_open())					// 파일 열람 검사
	{
		wstring errMsg = L"해당 파일이 없거나 파일 경로가 올바르지 않습니다. \n 찾는 파일 경로 : \n";
		errMsg += strMapFilrPath;
		MessageBox(nullptr, errMsg.c_str(), L"csv 파일 불러오기 실패", MB_OK);
		return;
	}

	wstring strKey;
	wstring strPath;

	// 배경이미지 , 맵, 배경음악 설정

		// 배경이미지 설정
	std::getline(ifs, strKey, L',');	// 리소스 키
	std::getline(ifs, strPath, L'\n');	// 리소스 패스

	if (wcscmp(L"", strKey.c_str()) != 0)
	{
		if (nullptr == m_pCurBackgrnd)
		{
			m_pCurBackgrnd = new CBackgrnd;
			Instantiate(m_pCurBackgrnd, Vec2(0, 0), LAYER::BACKGROUND);
		}
		m_pCurBackgrnd->SetBackGrnd(strKey, strPath);
	}
	else if (m_pCurBackgrnd != nullptr)
	{
		m_pCurBackgrnd = nullptr;
	}

	// Map 설정
	std::getline(ifs, strKey, L',');	// 리소스 키
	std::getline(ifs, strPath, L'\n');	// 리소스 패스

	if (wcscmp(L"", strKey.c_str()) != 0)
	{
		if (nullptr == m_pCurMap)
		{
			m_pCurMap = new CMap;
			Instantiate(m_pCurMap, LAYER::MAP);
		}
		m_pCurMap->SetMap(strKey, strPath);
	}
	else if (m_pCurMap != nullptr)
		m_pCurMap = nullptr;

	// BGM 설정
	std::getline(ifs, strKey, L',');	// 리소스 키
	std::getline(ifs, strPath, L'\n');	// 리소스 패스

	if (wcscmp(L"", strKey.c_str()) != 0)
	{
		m_pCurBgm = CResMgr::GetInst()->LoadSound(strKey, strPath);

		CSoundMgr::GetInst()->RegisterToBGM(m_pCurBgm);
		m_pCurBgm->PlayToBGM(true);
		m_pCurBgm->SetVolume(20);
	}
	else if (m_pCurBgm != nullptr)
		m_pCurBgm = nullptr;

	while (!ifs.eof())
	{
		LoadMapData(ifs);
	}

	ifs.close();
}
void CLevel::LoadMapData(wifstream& _ifs)
{
	wchar_t szbuff[256] = {};

	UINT _TOOLTYPE = {};
	_ifs.getline(szbuff,256, L',');

	if (_ifs.eof())
		return;

	_TOOLTYPE = _wtoi(szbuff);


	UINT _LAYER = {};
	_ifs.getline(szbuff, 256, L',');
	_LAYER = _wtoi(szbuff);

	Vec2 _VecInfo1 = {};
	_ifs.getline(szbuff, 256, L',');
	_VecInfo1.x = (float)_wtof(szbuff);
	_ifs.getline(szbuff, 256, L',');
	_VecInfo1.y = (float)_wtof(szbuff);

	Vec2 _VecInfo2 = {};
	_ifs.getline(szbuff, 256, L',');
	_VecInfo2.x = (float)_wtof(szbuff);
	_ifs.getline(szbuff, 256, L',');
	_VecInfo2.y = (float)_wtof(szbuff);


	bool _bInfo = {};
	_ifs.getline(szbuff, 256, L',');
	_bInfo = _wtoi(szbuff);

	UINT _eInfo = {};
	_ifs.getline(szbuff, 256, L',');
	_eInfo = _wtoi(szbuff);

	wstring _strMgrKey = {};
	_ifs.getline(szbuff, 256, L'\n');
	_strMgrKey = szbuff;


	CActor* pAct = nullptr;	// 생성할 객체

	switch ((TOOL_TYPE)_TOOLTYPE)
	{
	case TOOL_TYPE::DRAWPLATFORM:
	case TOOL_TYPE::DRAWEARTH:
	{
		pAct = new CPlatform;
		Instantiate(pAct, (LAYER)_LAYER);
		((CPlatform*)pAct)->SetLine(_VecInfo1, _VecInfo2);
		((CPlatform*)pAct)->SetLineInfo();
		((CPlatform*)pAct)->SetEarth((bool)_bInfo);
	}
	break;
	case TOOL_TYPE::DRAWWALL_LEFT:
	case TOOL_TYPE::DRAWWALL_RIGHT:
	case TOOL_TYPE::DRAWMOBWALL_LEFT:
	case TOOL_TYPE::DRAWMOBWALL_RIGHT:
	{
		pAct = new CWall;
		Instantiate(pAct, (LAYER)_LAYER);
		((CWall*)pAct)->SetLine(_VecInfo1, _VecInfo2);
		((CWall*)pAct)->SetLineInfo();
		((CWall*)pAct)->SetOnlyMob(_bInfo);
		((CWall*)pAct)->SetWallDir((eDir)_eInfo);
	}
	break;
	case TOOL_TYPE::DRAWROPE:
	{
		pAct = new CRope;
		Instantiate(pAct, (LAYER)_LAYER);
		((CRope*)pAct)->SetLine(_VecInfo1, _VecInfo2);
		((CRope*)pAct)->SetLineInfo();
	}
	break;
	case TOOL_TYPE::DRAWLADDER:
	{
		pAct = new CLadder;
		Instantiate(pAct, (LAYER)_LAYER);
		((CLadder*)pAct)->SetLine(_VecInfo1, _VecInfo2);
		((CLadder*)pAct)->SetLineInfo();
	}
	break;
	case TOOL_TYPE::CREATEMOB:
	{
		pAct = new CSpawner;
		Instantiate(pAct, Vec2(_VecInfo1.x, _VecInfo1.y), (LAYER)_LAYER);
		((CSpawner*)pAct)->SetSpawner(_strMgrKey); // 스포너에 몹 이름 전달 및 정보세팅
		((CSpawner*)pAct)->SetMob(_eInfo);	// 몹 enum 값 전달
	}
	break;
	case TOOL_TYPE::CREATENPC:
	case TOOL_TYPE::CREATEPORTAL:
	{
		pAct = CPortal::CreatePortal();
		if (pAct == nullptr)
			return;

		Instantiate(pAct, Vec2(_VecInfo1.x, _VecInfo1.y), (LAYER)_LAYER); // 위치 , 사이즈 생성.
		AddPortal((CPortal*)pAct, ((CPortal*)pAct)->GetPortalNo());
	}
	break;
	}
};