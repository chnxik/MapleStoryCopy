#include "pch.h"
#include "CAnimationMgr.h"
#include "CPathMgr.h"

CAnimationMgr::CAnimationMgr()
{

}


CAnimationMgr::~CAnimationMgr()
{
	// map �޸� ����
	map<wstring, tAnimInfo>::iterator iter = m_mapAniInfo.begin();
	for (; iter != m_mapAniInfo.end();)
	{
		iter->second.vecFrm.clear();
		iter = m_mapAniInfo.erase(iter);
	}
}

void CAnimationMgr::init()
{
	// csv ������ �о�� AniInfo map ����
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"data\\AnimInfo.csv";
	wifstream fs;

	fs.open(strFilePath.c_str());		// ���� ����

	if (!fs.is_open())					// ���� ���� �˻�
	{
		wstring errMsg = L"�ش� ������ ���ų� ���� ��ΰ� �ùٸ��� �ʽ��ϴ�. \n ã�� ���� ��� : \n";
		errMsg += strFilePath;
		MessageBox(nullptr, errMsg.c_str(), L"csv ���� �ҷ����� ����", MB_OK);
		return;
	}

	wstring szbuff;

	bool FrmRepeat = false;

	std::getline(fs, szbuff);	// ù�� ���׸� �κ� ������

	while (!fs.eof())					// ������ ���̸� �ݺ��ߴ�
	{
		tAnimInfo Temp;

		std::getline(fs, szbuff, L','); // �ִϸ��̼� ǥ�� �̸� �޾ƿ� ������.
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

	fs.close();				// ���� �ݱ�
}

const tAnimInfo* CAnimationMgr::GetAniInfo(const wstring& _strName)
{
	map<wstring,tAnimInfo>::iterator iter = m_mapAniInfo.find(_strName);
	
	if (iter == m_mapAniInfo.end())
	{
		MessageBox(nullptr, L"�ش� Animation ���� ����", L"Animation ���� �ҷ����� ����", MB_OK);
		return nullptr;
	}

	return &(iter->second);
}
