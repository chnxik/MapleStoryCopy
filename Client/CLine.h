#pragma once
#include "CActor.h"

class CTester;

class CLine :
    public CActor
{
private:
    TOOL_TYPE  m_Tool;
    __LINE     m_Line;

public:
    virtual void tick();
    virtual void render(HDC _dc) {};

public:
    virtual void SetLine(Vec2 _vLdot, Vec2 _vRdot)
    {
        m_Line.Ldx = (short)_vLdot.x;
        m_Line.Ldy = (short)_vLdot.y;
        m_Line.Rdx = (short)_vRdot.x;
        m_Line.Rdy = (short)_vRdot.y;

        DrawCmplt();
    };


    virtual void SetLdot(Vec2 _vPos) { m_Line.Ldx = (short)_vPos.x; m_Line.Ldy = (short)_vPos.y; }
    virtual void SetRdot(Vec2 _vPos) { m_Line.Rdx = (short)_vPos.x; m_Line.Rdy = (short)_vPos.y; }
    virtual void SetToolType(TOOL_TYPE _Tool) { m_Tool = _Tool; }
    virtual void DrawCmplt();


    virtual TOOL_TYPE GetToolType() { return m_Tool; }
    virtual __LINE& GetLine() { return m_Line; }
    virtual Vec2 GetLdot() { return Vec2(m_Line.Ldx, m_Line.Ldy); }
    virtual Vec2 GetRdot() { return Vec2(m_Line.Rdx, m_Line.Rdy); }
    virtual float GetCenterx() { return GetPos().x + GetScale().x / 2; }

    virtual void SetLineInfo();

    Vec2 GetGradient()
    {
        Vec2 vGradient = { m_Line.Rdx - m_Line.Ldx , m_Line.Rdy - m_Line.Ldy };
        vGradient.Normalize();
        return vGradient;
    }

    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void EndOverlap(CCollider* _pOther);

public:
    CLONE(CLine);

public:
    CLine();
    ~CLine();

    friend class CUI;
};
