#pragma once

class CTexture;
class CSound;

class CResMgr
{
	SINGLE(CResMgr);
private:
	map<wstring, CTexture*>	m_mapTex;
	map<wstring, CSound*>	m_mapSounds;

public:
	CTexture* FindTexture(const wstring& _strKey);
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight);

	CSound* FindSound(const wstring& _strKey);
	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
};

