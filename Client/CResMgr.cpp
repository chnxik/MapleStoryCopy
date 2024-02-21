#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CSound.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
    for (; iter != m_mapTex.end(); ++iter)
    {
        delete iter->second;
    }

    map<wstring, CSound*>::iterator iter_sound = m_mapSounds.begin();
    for (; iter_sound != m_mapSounds.end(); ++iter_sound)
    {
        delete iter_sound->second;
    }
}


CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);
    if (iter == m_mapTex.end())
    {
        return nullptr;
    }

    return iter->second;
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    CRes* pTexture = FindTexture(_strKey);

    if (nullptr != pTexture)
        return (CTexture*)pTexture;

    // PathMgr 를 이용해서 최종 Texture의 경로를 만든다.
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    // 텍스쳐 생성 및 로딩
    pTexture = new CTexture;
    pTexture->Load(strFilePath);
    pTexture->SetKey(_strKey);
    pTexture->SetRelativePath(_strRelativePath);

    // Map 에 저장
    m_mapTex.insert(make_pair(_strKey, (CTexture*)pTexture));

    return (CTexture*)pTexture;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
    CTexture* pTexture = FindTexture(_strKey);

    if (nullptr != pTexture)
        return (CTexture*)pTexture;

    // 텍스쳐 생성 및 로딩
    pTexture = new CTexture;
    pTexture->Create(_iWidth, _iHeight);
    pTexture->SetKey(_strKey);

    // Map 에 저장
    m_mapTex.insert(make_pair(_strKey, pTexture));

    return pTexture;
}

CSound* CResMgr::FindSound(const wstring& _strKey)
{
    map<wstring, CSound*>::iterator iter = m_mapSounds.find(_strKey);
    if (iter == m_mapSounds.end())
    {
        return nullptr;
    }

    return iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
    CRes* pSound = FindSound(_strKey);

    if (nullptr != pSound)
        return (CSound*)pSound;

    // PathMgr 를 이용해서 최종 Texture의 경로를 만든다.
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    // 텍스쳐 생성 및 로딩
    pSound = new CSound;
    pSound->Load(strFilePath);
    pSound->SetKey(_strKey);
    pSound->SetRelativePath(_strRelativePath);

    // Map 에 저장
    m_mapSounds.insert(make_pair(_strKey, (CSound*)pSound));

    return (CSound*)pSound;
}
