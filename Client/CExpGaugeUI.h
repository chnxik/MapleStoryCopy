#pragma once
#include "CUI.h"

class CNum;

class CExpGaugeUI :
    public CUI
{
private:
    float m_fMaxValue;
    float m_fPrevValue;
    float m_fCurValue;
    float m_fUpdateValue;
    float m_fRatio;
    CNum* m_arrVal[3];

public:
    void SetMaxValue(UINT _iMaxValue) { m_fMaxValue = (float)_iMaxValue; }
    void SetValue(UINT _iValue) { m_fCurValue = (float)_iValue; m_fUpdateValue = (float)_iValue; }
    void UpdateValue(UINT _iUpdateValue)
    {
        if ((UINT)m_fUpdateValue == _iUpdateValue)
            return;

        float fValue = (float)_iUpdateValue;
        if (fValue < 0)
            fValue = 0;
        else if (fValue > m_fMaxValue)
            fValue = m_fMaxValue;

        m_fPrevValue = m_fCurValue;
        m_fUpdateValue = fValue;
    }

public:
    void Numinit();
    void SetValueNum();
    

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CLONE_DEACTIVATE(CExpGaugeUI);

public:
    CExpGaugeUI();
    ~CExpGaugeUI();
};

