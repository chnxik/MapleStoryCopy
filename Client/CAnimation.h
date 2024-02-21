#pragma once
#include "CEntity.h"

class CAnimator;
class CTexture;
class CSound;

class CAnimation :
    public CEntity
{
private:
    CAnimator*          m_pAnimator;    // �����ų �ִϸ�����
    vector<tAnimFrm>    m_vecFrm;       // ������ ����
    CTexture*           m_pAtlas;       // ��Ʋ��
    UINT                m_iCurFrm;      // ���� ������
    float               m_fAccTime;     // ������ ����ӵ��� ���� �����ð�
    bool                m_bFinish;      // �ִϸ��̼� ��� �Ϸ�
    bool                m_bFlashing;    // ����ȿ��
    CSound*             m_pSound;       // �����ų ����
    float               m_fOpacity;     // ����
    float               m_fScale;       // ���� ���
    float               m_iOpacityLimit; // ���� ���Ѽ�
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

