#pragma once


class CAnimationMgr
{
	SINGLE(CAnimationMgr);
private:
	map<wstring, tAnimInfo> m_mapAniInfo;

public:
	void init();
	
public:
	const tAnimInfo* GetAniInfo(const wstring& _strName);
};

