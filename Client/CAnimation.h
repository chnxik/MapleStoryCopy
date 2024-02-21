#pragma once
#include "CEntity.h"

class CAnimator;
class CTexture;
class CSound;

class CAnimation :
    public CEntity
{
private:
    CAnimator*          m_pAnimator;    // 재생시킬 애니메이터
    vector<tAnimFrm>    m_vecFrm;       // 프레임 정보
    CTexture*           m_pAtlas;       // 아틀라스
    UINT                m_iCurFrm;      // 현재 프레임
    float               m_fAccTime;     // 프레임 재생속도를 위한 누적시간
    bool                m_bFinish;      // 애니메이션 재생 완료
    bool                m_bFlashing;    // 점멸효과
    CSound*             m_pSound;       // 재생시킬 사운드
    float               m_fOpacity;     // 투명도
    float               m_fScale;       // 투명도 계수
    float               m_iOpacityLimit; // 투명도 하한선
    bool                m_bStop;        // stop

private:
    void init(const tAnimInfo* _tAnimInfo);

public:
    void tick();
    void render(HDC _dc);

public:
    bool IsFinish() { return m_bFinish; }
    void SetStop(bool _b) { m_bStop = _b; }
    bool IsStop() { return m_bStop; }
    void Reset()
    {
        m_bFinish = false;
        m_iCurFrm = 0;
        m_fAccTime = 0.f;
    }

    void SetOpacity(UINT _iOpacity)
    { 
        _iOpacity = max(0, min(100, _iOpacity));
        m_fOpacity = (float)_iOpacity * 0.01f;
    };

    void SetFlashing(bool _b) { m_bFlashing = _b; }
    void SetOpacityLimit(UINT _iOpacity)
    {
        _iOpacity = max(0, min(100, _iOpacity));
        m_iOpacityLimit = (float)_iOpacity * 0.01f;
    };

public:
    CLONE(CAnimation);

public:
    CAnimation(CAnimator* _pAnimator);
    ~CAnimation();

    friend class CAnimator;
};

