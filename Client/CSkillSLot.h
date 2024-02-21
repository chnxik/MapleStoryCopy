#pragma once
#include "CUI.h"

class CBtnUI;
class CPlayer;
class CTexture;

class CSkillSLot :
    public CUI
{
private:
    const wchar_t*    m_strSkillName;
    CTexture*        m_pDisTex;
    SKILL            m_eSkill;
    UINT             m_iSkillLv;
    RECT             m_rtSkillName;
    RECT             m_rtSkillLv;
    CBtnUI*          m_btnSkillPoint;
    bool             m_bActive;

public:
    virtual void tick();
    virtual void render(HDC _dc);

    void init();
    void SetDisTex(CTexture* _pTex) { m_pDisTex = _pTex; }

    inline void UpdateSkillLv(UINT _i) { m_iSkillLv = _i; }
    CBtnUI* GetSkillPointBtn() { return m_btnSkillPoint; }

    void SkillPointUp();

public:
    virtual void MouseLbtnDown();

public:
    CLONE_DEACTIVATE(CSkillSLot);

public:
    CSkillSLot(const wchar_t* _skillName, SKILL _skill);
    ~CSkillSLot();
};

