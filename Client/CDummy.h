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
    const UINT  m_DummyKey;     // Map 검색용으로 사용될 본인의 Key, 0 = Bg, 1 = map, 2 = BGM, 3 ~
    
    TOOL_TYPE   m_UseTOOL;      // 생성하는 툴 종류
    LAYER       m_LayerInfo;    // 생성할 레이어 정보
    Vec2        m_VecInfo1;     // Tool별 사용하는 위치 정보
    Vec2        m_VecInfo2;     // Tool별 사용하는 위치 정보
    bool        m_binfo;        // 세부정보 bool값
    UINT        m_eInfo;        // 세부정보 UINT값
    wstring     m_MgrKey;       // 각 객체별 매니저에서 호출할 키
    
    CActor*     m_pActor;       // 연결된 본체 객체
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

