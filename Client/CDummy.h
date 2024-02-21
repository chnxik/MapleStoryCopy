#pragma once
#include "CUI.h"

class CLine;
class CActor;

class CDummy :
    public CUI
{
private:
    static UINT	g_iNextDummyKey;

private:
    const UINT  m_DummyKey;     // Map �˻������� ���� ������ Key, 0 = Bg, 1 = map, 2 = BGM, 3 ~
    
    TOOL_TYPE   m_UseTOOL;      // �����ϴ� �� ����
    LAYER       m_LayerInfo;    // ������ ���̾� ����
    Vec2        m_VecInfo1;     // Tool�� ����ϴ� ��ġ ����
    Vec2        m_VecInfo2;     // Tool�� ����ϴ� ��ġ ����
    bool        m_binfo;        // �������� bool��
    UINT        m_eInfo;        // �������� UINT��
    wstring     m_MgrKey;       // �� ��ü�� �Ŵ������� ȣ���� Ű
    
    CActor*     m_pActor;       // ����� ��ü ��ü
public:
    virtual void tick() override;

public:
    void SetLineDummy(CLine* _Line, TOOL_TYPE _Tool, LAYER _LAYER);
    void SetObjDummy(CActor* _Act, TOOL_TYPE _Tool, LAYER _LAYER);
    void CreateDeleteBtn();

    CActor* GetActor() { return m_pActor; }

    void SelfDelete();

    const UINT GetToolType() { return (UINT)m_UseTOOL; }
    const UINT GetLAYER() { return (UINT)m_LayerInfo; }
    const Vec2 GetVecInfo1() { return m_VecInfo1; }
    const Vec2 GetVecInfo2() { return m_VecInfo2; }
    const UINT Getboolifno() { return m_binfo; }
    const UINT GeteInfo() { return m_eInfo; }
    const wstring GetMgrKey() { return m_MgrKey; }
    const UINT GetKey() { return m_DummyKey; }
    void SetInitKey() { g_iNextDummyKey = 0; }

private:
    virtual void MouseLbtnDown() override;
    virtual void MouseLbtnClicked() override;
    virtual void MouseOn() override;

public:
    CLONE(CDummy);

public:
    CDummy();
    ~CDummy();
};

