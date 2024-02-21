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
#include "CSound.h"

#include "CBackgrnd.h"
#include "CMap.h"

#include "CUI.h"
#include "CPNUI.h"
#include "CToolInven.h"
#include "CDummy.h"

#include "CPlayer.h"

#include "CLine.h"
#include "CPlatform.h"
#include "CWall.h"
#include "CRope.h"
#include "CLadder.h"
#include "CSpawner.h"
#include "CPortal.h"


void CToolLevel::init()
{
	// ī�޶� ����
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

//	CPlayer* pPlayer = new CPlayer;
//	pPlayer->SetScale(Vec2(46, 73));
//	pPlayer->SetCmrAfctd(true);
//	Instantiate(pPlayer, vResolution / 2, LAYER::PLAYER);
//	
//	CCamera::GetInst()->SetTarget(pPlayer);

	CreateUI();

	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MAP);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MAPOBJ);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MOB, LAYER::MAP);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MOB, LAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MOB);

}

void CToolLevel::CreateUI()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	// UI Textrue Load
	CTexture* pToolIvPn1 = CResMgr::GetInst()->LoadTexture(L"ToolInvenPn1", L"texture\\Tool\\ToolInvenpn1.png");

	CPNUI* pToolPNUI = new CPNUI;
	pToolPNUI->SetName(L"ToolPNUI");
	pToolPNUI->SetIdleTex(pToolIvPn1);

	CToolInven* pToolInvenUI = new CToolInven(this);
	pToolInvenUI->SetName(L"ToolInvenPNUI");
	pToolInvenUI->SetPos(Vec2(6, 21));
	pToolPNUI->AddChildUI(pToolInvenUI);
	pToolInvenUI->CreateBtn();
	pToolInvenUI->CreateCell();

	Instantiate(pToolPNUI, Vec2(vResolution.x * (5.f / 7.f), vResolution.y * (1.f / 10.f)), LAYER::PLAYERUI);
}

void CToolLevel::CreateBackgrnd()
{
	ShowCursor(true);
	// open a file name
	OPENFILENAME ofn = {};

	wstring strBgImgFolderPath = CPathMgr::GetInst()->GetContentPath();
	int iPathLen = (int)wcslen(strBgImgFolderPath.c_str());
	strBgImgFolderPath += L"texture\\map\\backgrnd\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"png\0*.png\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strBgImgFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
	{
		ShowCursor(false);
		return;
	}
	ShowCursor(false);

	size_t iLen = wcslen(strBgImgFolderPath.c_str());
	size_t istrCnt = wcslen(szFilePath);


	wstring strFilePath = szFilePath;
	wstring strRelativePath = strFilePath.substr(iPathLen, istrCnt - iPathLen);
	wstring strKey = strFilePath.substr(iLen, istrCnt - iLen - 4);


	if (nullptr == m_pCurBackgrnd)
	{
		m_pCurBackgrnd = new CBackgrnd;
		Instantiate(m_pCurBackgrnd, LAYER::BACKGROUND);
	}

	m_BgstrKey = strKey;
	m_BgstrRelativePath = strRelativePath;

	m_pCurBackgrnd->SetBackGrnd(m_BgstrKey, m_BgstrRelativePath);
}

void CToolLevel::CreateMap()
{
	ShowCursor(true);
	// open a file name
	OPENFILENAME ofn = {};

	wstring strMapImgFolderPath = CPathMgr::GetInst()->GetContentPath();
	int iPathLen = (int)wcslen(strMapImgFolderPath.c_str());
	strMapImgFolderPath += L"texture\\map\\map\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"png\0*.png\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strMapImgFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
	{
		ShowCursor(false);
		return;
	}
	ShowCursor(false);


	size_t iLen = wcslen(strMapImgFolderPath.c_str());
	size_t istrCnt = wcslen(szFilePath);

	wstring strFilePath = szFilePath;
	wstring strRelativePath = strFilePath.substr(iPathLen, istrCnt - iPathLen);
	wstring strKey = strFilePath.substr(iLen, istrCnt - iLen - 4);

	if (nullptr == m_pCurMap)
	{
		m_pCurMap = new CMap;
		Instantiate(m_pCurMap, LAYER::MAP);
		SetCurMap(m_pCurMap);
	}

	m_MapstrKey = strKey;
	m_MapstrRelativePath = strRelativePath;

	m_pCurMap->SetMap(m_MapstrKey, m_MapstrRelativePath);
}

void CToolLevel::CreateBgm()
{
	ShowCursor(true);
	// open a file name
	OPENFILENAME ofn = {};

	wstring strBgmFolderPath = CPathMgr::GetInst()->GetContentPath();
	int iPathLen = (int)wcslen(strBgmFolderPath.c_str());
	strBgmFolderPath += L"sound\\bgm\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"wav\0*.wav\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strBgmFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
	{
		ShowCursor(false);
		return;
	}
	ShowCursor(false);


	size_t iLen = wcslen(strBgmFolderPath.c_str());
	size_t istrCnt = wcslen(szFilePath);

	wstring strFilePath = szFilePath;
	wstring strRelativePath = strFilePath.substr(iPathLen, istrCnt - iPathLen);
	wstring strKey = strFilePath.substr(iLen, istrCnt - iLen - 4);
	
	m_BGMstrKey = strKey;
	m_BGMstrRelativePath = strRelativePath;

	m_pCurBgm = CResMgr::GetInst()->LoadSound(m_BGMstrKey, m_BGMstrRelativePath);

	CSoundMgr::GetInst()->RegisterToBGM(m_pCurBgm);
	m_pCurBgm->PlayToBGM(true);
}


void CToolLevel::SaveMap()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"data\\map\\";


	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"map\0*.map\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	ShowCursor(true);
	if (false == GetSaveFileName(&ofn))
	{
		ShowCursor(false);
		return;
	}
	ShowCursor(false);

	wofstream ofs;

	ofs.open(szFilePath, std::ios::binary);

	wstring szbuff;

	// ���, ��, ������� ����
	szbuff = m_BgstrKey + L',' + m_BgstrRelativePath + L'\n';
	ofs.write(szbuff.c_str(), szbuff.size());
	szbuff = m_MapstrKey + L',' + m_MapstrRelativePath + L'\n';
	ofs.write(szbuff.c_str(), szbuff.size());
	szbuff = m_BGMstrKey + L',' + m_BGMstrRelativePath + L'\n';
	ofs.write(szbuff.c_str(), szbuff.size());

	// mapData ����
	map<UINT, CDummy*>::iterator iter = m_mapData.begin();

	while (iter != m_mapData.end())
	{
		wstring szbuff = {}; // ���� ������ ���� stream

		// 1. ���� TOOL_TYPE ��������
		szbuff = std::to_wstring(iter->second->GetToolType()) + L',';

		// 2. ������ ���̾� ����
		szbuff += std::to_wstring(iter->second->GetLAYER()) + L',';

		// 3. ��ġ �� ũ��, �о���� TOOLŸ�Կ� ���߾� �д´�.
		szbuff += std::to_wstring(iter->second->GetVecInfo1().x) + L',';
		szbuff += std::to_wstring(iter->second->GetVecInfo1().y) + L',';
		szbuff += std::to_wstring(iter->second->GetVecInfo2().x) + L',';
		szbuff += std::to_wstring(iter->second->GetVecInfo2().y) + L',';

		// 4. ���� ���� 1 , bool ��
		szbuff += std::to_wstring(iter->second->Getboolifno()) + L',';

		// 5. ���� ���� 2 , short ��
		szbuff += std::to_wstring(iter->second->GeteInfo()) + L',';

		// 6. �Ŵ������� �ҷ��� �̸� Ű�� (Mob, NPC, Portal)
		szbuff += iter->second->GetMgrKey() + L'\n';
		ofs.write(szbuff.c_str(), szbuff.size());

		++iter;
	}
	ofs.close();
}

void CToolLevel::LoadMap()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"data\\map\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"map\0*.map\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	ShowCursor(true);
	if (false == GetSaveFileName(&ofn))
	{
		ShowCursor(false);
		return;
	}
	ShowCursor(false);

	wifstream ifs;

	ifs.open(szFilePath, std::ios::binary);

	if (!ifs.is_open())					// ���� ���� �˻�
	{
		wstring errMsg = L"�ش� ������ ���ų� ���� ��ΰ� �ùٸ��� �ʽ��ϴ�. \n ã�� ���� ��� : \n";
		errMsg += szFilePath;
		MessageBox(nullptr, errMsg.c_str(), L"csv ���� �ҷ����� ����", MB_OK);
		return;
	}

	wstring strKey;
	wstring strPath;

	// ����̹��� , ��, ������� ����
	{
		// ����̹��� ����
		std::getline(ifs, strKey, L',');	// ���ҽ� Ű
		std::getline(ifs, strPath, L'\n');	// ���ҽ� �н�

		m_BgstrKey = strKey;
		m_BgstrRelativePath = strPath;
		if (wcscmp(L"", strKey.c_str()) != 0)
		{
			if (nullptr == m_pCurBackgrnd)
			{
				m_pCurBackgrnd = new CBackgrnd;
				Instantiate(m_pCurBackgrnd, Vec2(0, 0), LAYER::BACKGROUND);
			}
			m_pCurBackgrnd->SetBackGrnd(m_BgstrKey, m_BgstrRelativePath);
		}
		else if (m_pCurBackgrnd != nullptr)
		{
			m_pCurBackgrnd->SetDead();
			m_pCurBackgrnd = nullptr;
		}
		
		// Map ����
		std::getline(ifs, strKey, L',');	// ���ҽ� Ű
		std::getline(ifs, strPath, L'\n');	// ���ҽ� �н�

		m_MapstrKey = strKey;
		m_MapstrRelativePath = strPath;

		if (wcscmp(L"", strKey.c_str()) != 0)
		{
			if (nullptr == m_pCurMap)
			{
				m_pCurMap = new CMap;
				Instantiate(m_pCurMap, LAYER::MAP);
			}
			m_pCurMap->SetMap(m_MapstrKey, m_MapstrRelativePath);
		}
		else if (m_pCurMap != nullptr)
		{
			m_pCurMap->SetDead();
			m_pCurMap = nullptr;
		}
		
		// BGM ����
		std::getline(ifs, strKey, L',');	// ���ҽ� Ű
		std::getline(ifs, strPath, L'\n');	// ���ҽ� �н�

		m_BGMstrKey = strKey;
		m_BGMstrRelativePath = strPath;
		if (wcscmp(L"", strKey.c_str()) != 0)
		{
			m_pCurBgm = CResMgr::GetInst()->LoadSound(m_BGMstrKey, m_BGMstrRelativePath);

			CSoundMgr::GetInst()->RegisterToBGM(m_pCurBgm);
			m_pCurBgm->PlayToBGM(true);
			m_pCurBgm->SetVolume(20);
		}
		else if(m_pCurBgm != nullptr)
		{
			m_pCurBgm->Stop();
			m_pCurBgm = nullptr;
		}
	}

	vector<CActor*> MobLayer = GetLayer(LAYER::MOB);
	vector<CActor*>::iterator iter = MobLayer.begin();
	while (iter != MobLayer.end())
	{
		CSpawner* Spawner = dynamic_cast<CSpawner*>(*iter);

		if (Spawner == nullptr)
		{
			DEL((*iter));
			iter = MobLayer.erase(iter);
		}
		else
			++iter;
	}

	DeleteAllDummy();

	while(!ifs.eof())
	{
		LoadMapData(ifs);
	}

	ifs.close();
}

void CToolLevel::LoadMapData(wifstream& _ifs)
{

	wstring szbuff;

	UINT _TOOLTYPE = {};				
	std::getline(_ifs, szbuff, L',');	// ��Ÿ��
	wstringstream(szbuff) >> _TOOLTYPE;

	if (_ifs.eof())
		return;
	
	UINT _LAYER = {};					
	std::getline(_ifs, szbuff, L',');	// ���̾� ����
	wstringstream(szbuff) >> _LAYER;

	Vec2 _VecInfo1 = {};
	std::getline(_ifs, szbuff, L',');	// ����, ��ġ, ũ�� ����
	wstringstream(szbuff) >> _VecInfo1.x;
	std::getline(_ifs, szbuff, L',');	// ����, ��ġ, ũ�� ����
	wstringstream(szbuff) >> _VecInfo1.y;
	
	Vec2 _VecInfo2 = {};
	std::getline(_ifs, szbuff, L',');	// ����, ��ġ, ũ�� ����
	wstringstream(szbuff) >> _VecInfo2.x;
	std::getline(_ifs, szbuff, L',');	// ����, ��ġ, ũ�� ����
	wstringstream(szbuff) >> _VecInfo2.y;

	bool _bInfo = {};
	std::getline(_ifs, szbuff, L',');	// bool ��
	wstringstream(szbuff) >> _bInfo;

	UINT _eInfo= {};
	std::getline(_ifs, szbuff, L',');	// short ��
	wstringstream(szbuff) >> _eInfo;

	wstring _strMgrKey = {};
	std::getline(_ifs, szbuff, L'\n');	// �Ŵ��� Ű��
	wstringstream(szbuff) >> _strMgrKey;
	
	

	CActor* pAct = nullptr;	// ������ ��ü

	switch ((TOOL_TYPE)_TOOLTYPE)
	{
	case TOOL_TYPE::DRAWPLATFORM:
	case TOOL_TYPE::DRAWEARTH:
	{
		pAct = new CPlatform;
		Instantiate(pAct, (LAYER)_LAYER);
		((CPlatform*)pAct)->SetLine(_VecInfo1,_VecInfo2);
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
		((CSpawner*)pAct)->SetSpawner(_strMgrKey); // �����ʿ� �� �̸� ���� �� ��������
		((CSpawner*)pAct)->SetMob(_eInfo);	// �� enum �� ����
	}
	break;
	case TOOL_TYPE::CREATENPC:
	case TOOL_TYPE::CREATEPORTAL:
	{
		pAct = CPortal::CreatePortal();
		if (pAct == nullptr)
			return;

		Instantiate(pAct, Vec2(_VecInfo1.x, _VecInfo1.y), (LAYER)_LAYER); // ��ġ , ������ ����.
	}
		break;
	}

	// ToolLevel �� ���� ����

	CToolLevel* pToolLevel = dynamic_cast<CToolLevel*>(CLevelMgr::GetInst()->GetCurLevel());
	if (pToolLevel)
	{
		switch ((TOOL_TYPE)_TOOLTYPE)
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
			CDummy* pDummy = new CDummy;
			Instantiate(pDummy,  LAYER::PLAYERUI);
			pDummy->SetLineDummy((CLine*)pAct, (TOOL_TYPE)_TOOLTYPE,(LAYER)_LAYER);
			m_mapData.insert(make_pair(pDummy->GetKey(), pDummy));
		}
			break;
		case TOOL_TYPE::CREATEMOB:
		case TOOL_TYPE::CREATENPC:
		case TOOL_TYPE::CREATEPORTAL:
		{
			CDummy* pDummy = new CDummy;
			Instantiate(pDummy, LAYER::PLAYERUI);
			pDummy->SetObjDummy((CSpawner*)pAct, (TOOL_TYPE)_TOOLTYPE, (LAYER)_LAYER);
			m_mapData.insert(make_pair(pDummy->GetKey(), pDummy));
		}
			break;
		case TOOL_TYPE::NONE:
			break;
		default:
			break;
		}
	}
}