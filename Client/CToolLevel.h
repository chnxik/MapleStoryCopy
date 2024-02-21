#pragma once
#include "CLevel.h"

class CMap;
class CBackgrnd;
class CSound;

class CLine;
class CDummy;

class CToolCell;

class CToolLevel :
    public CLevel
{
private:
    wstring   m_BgstrKey;
    wstring   m_BgstrRelativePath;
    wstring   m_MapstrKey;
    wstring   m_MapstrRelativePath;
    wstring   m_BGMstrKey;
    wstring   m_BGMstrRelativePath;

    TOOL_TYPE       m_eCurTool;
    CToolCell*      m_pCurCell;

    map<UINT, CDummy*> m_mapData;

    CLine* m_pCurLine;

public:
    virtual void init() override;
    virtual void tick() override;
    virtual void Enter(UINT _iPortalNo) override;
    virtual void Exit() override;

private:
    void CreateUI();

public:
    void DeleteDummy(UINT _id);
    void DeleteAllDummy();
    map<UINT, CDummy*>& GetDummyMap() { return m_mapData; };

public:
    void SaveMap();
    void LoadMap();
    void LoadMapData(wifstream& _ifs) override;
    void CreateMap();
    void CreateBackgrnd();
    void CreateBgm();

public:
    void UpdateCurTool(TOOL_TYPE _Tool,CToolCell* _Cell);

    void DrawLine(TOOL_TYPE _Tool);
    void CreateMapObj(TOOL_TYPE _Tool);


public:
    CToolLevel();
    ~CToolLevel();
};