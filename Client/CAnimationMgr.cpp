#include "pch.h"
#include "CAnimationMgr.h"
#include "CPathMgr.h"

CAnimationMgr::CAnimationMgr()
{

}


CAnimationMgr::~CAnimationMgr()
{
	// map 메모리 해제
	map<wstring, tAnimInfo>::iterator iter = m_mapAniInfo.begin();
	for (; iter != m_mapAniInfo.end();)
	{
		iter->second.vecFrm.clear();
		iter = m_mapAniInfo.erase(iter);
	}
}

void CAnimationMgr::init()
{
	// csv 파일을 읽어와 AniInfo map 생성
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"data\\AnimInfo.csv";
	wifstream fs;

	fs.open(strFilePath.c_str());		// 파일 열기

	if (!fs.is_open())					// 파일 열람 검사
	{
		wstring errMsg = L"해당 파일이 없거나 파일 경로가 올바르지 않습니다. \n 찾는 파일 경로 : \n";
		errMsg += strFilePath;
		MessageBox(nullptr, errMsg.c_str(), L"csv 파일 불러오기 실패", MB_OK);
		return;
	}

	wstring szbuff;

	bool FrmRepeat = false;

	std::getline(fs, szbuff);	// 첫줄 셀항목 부분 버리기

	while (!fs.eof())					// 파일의 끝이면 반복중단
	{
		tAnimInfo Temp;

		std::getline(fs, szbuff, L','); // 애니메이션 표기 이름 받아와 버리기.
		if (fs.eof())
			break;

		std::getline(fs, szbuff, L',');
		wstringstream(szbuff) >> Temp.strAnimName;
		
		std::getline(fs, szbuff, L',');
		wstringstream(szbuff) >> Temp.strAtlasKey;
		
		std::getline(fs, szbuff, L',');
		wstringstream(szbuff) >> Temp.strAtlasPath;
		
		std::getline(fs, szbuff, L',');
		wstringstream(szbuff) >> Temp.strSoundKey;
		
		std::getline(fs, szbuff, L',');
		wstringstream(szbuff) >> Temp.strSoundPath;
		
		std::getline(fs, szbuff, L',');
		wstringstream(szbuff) >> Temp.bUseSound;
		
		std::getline(fs, szbuff, L',');
		wstringstream(szbuff) >> Temp.iFrmCnt;

		std::getline(fs, szbuff, L',');
		wstringstream(szbuff) >> FrmRepeat;

		if (FrmRepeat)
		{
			tAnimFrm tFrm = {};

			std::getline(fs, szbuff, L',');
			wstringstream(szbuff) >> tFrm.vLeftTop.x;

			std::getline(fs, szbuff, L',');
			wstringstream(szbuff) >> tFrm.vLeftTop.y;

			std::getline(fs, szbuff, L',');
			wstringstream(szbuff) >> tFrm.vSize.x;

			std::getline(fs, szbuff, L',');
			wstringstream(szbuff) >> tFrm.vSize.y;

			std::getline(fs, szbuff, L',');
			wstringstream(szbuff) >> tFrm.vOffset.x;

			std::getline(fs, szbuff, L',');
			wstringstream(szbuff) >> tFrm.vOffset.y;
			
			std::getline(fs, szbuff, L'\n');
			wstringstream(szbuff) >> tFrm.fDuration;
			
			Temp.vecFrm.push_back(tFrm);

			for (UINT i = 1; i < Temp.iFrmCnt; ++i)
			{
				tFrm.vLeftTop.x += tFrm.vSize.x;
				Temp.vecFrm.push_back(tFrm);
			}
		}
		else
		{
			for (UINT i = 0; i < Temp.iFrmCnt; ++i)
			{
				tAnimFrm tFrm = {};
			
				std::getline(fs, szbuff, L',');
				wstringstream(szbuff) >> tFrm.vLeftTop.x;
			
				std::getline(fs, szbuff, L',');
				wstringstream(szbuff) >> tFrm.vLeftTop.y;
			
				std::getline(fs, szbuff, L',');
				wstringstream(szbuff) >> tFrm.vSize.x;
			
				std::getline(fs, szbuff, L',');
				wstringstream(szbuff) >> tFrm.vSize.y;
			
				std::getline(fs, szbuff, L',');
				wstringstream(szbuff) >> tFrm.vOffset.x;
			
				std::getline(fs, szbuff, L',');
				wstringstream(szbuff) >> tFrm.vOffset.y;
			
				if (i + 1 == Temp.iFrmCnt)
				{
					std::getline(fs, szbuff, L'\n');
					wstringstream(szbuff) >> tFrm.fDuration;
				}
				else
				{
					std::getline(fs, szbuff, L',');
					wstringstream(szbuff) >> tFrm.fDuration;
				}

				Temp.vecFrm.push_back(tFrm);
			}
		}
		
		m_mapAniInfo.insert(make_pair(Temp.strAnimName, Temp));
		
	}

	fs.close();				// 파일 닫기
}

const tAnimInfo* CAnimationMgr::GetAniInfo(const wstring& _strName)
{
	map<wstring,tAnimInfo>::iterator iter = m_mapAniInfo.find(_strName);
	
	if (iter == m_mapAniInfo.end())
	{
		MessageBox(nullptr, L"해당 Animation 정보 없음", L"Animation 정보 불러오기 실패", MB_OK);
		return nullptr;
	}

	return &(iter->second);
}
