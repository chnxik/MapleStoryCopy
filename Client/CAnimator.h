#pragma once
#include "CComponent.h"


class CAnimation;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>       m_mapAnim;
    CAnimation*                     m_pCurAnim;
    bool                            m_bRepeat;

public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;


public:
    void Play(const wstring& _strName, bool _bRepeat);
    void Play(const wstring& _strName, bool _bRepeat, UINT _iOpacity);
    void Play(const wstring& _strName, bool _bRepeat, UINT _iOpacity, bool _bFlashing);
    void Stop();        
    void RePlay();      
    void EraseCurAnim() { m_pCurAnim = nullptr; }

    void CreateAnimation(const wstring& _strName);
    CAnimation* FindAnimation(const wstring& _strName);
    CAnimation* GetCurAnimation() { return m_pCurAnim; }

public:
    CLONE(CAnimator);

public:
    CAnimator(CActor* _pOwner);
    CAnimator(const CAnimator& _other);
    ~CAnimator();
};