#pragma once
#include "CEntity.h"

class CMap;
class CBackgrnd;
class CSound;
class CActor;
class CPortal;

class CLevel :
    public CEntity
{
private:
    vector<CActor*>   m_arrLayer[(UINT)LAYER::END];
    CMap*             m_pCurMap;
    CBackgrnd*        m_pCurBackgrnd;
    CSound*           m_pCurBgm;
    
    CPortal*          m_pPortal[(UINT)PORTAL::END];

    bool              m_bInitcomplet;

public:
    virtual void init() = 0;
    virtual void tick();
    virtual void final_tick();
    virtual void render(HDC _dc);

    virtual void Enter(UINT _iPortalNo) = 0;   // 레벨에 진입할 때 호출 됨
    virtual void Exit() = 0;    // 레벨을 벗어날 때 호출 됨

public:
    void AddActor(CActor* _pObj, LAYER _Layer) { m_arrLayer[(UINT)_Layer].push_back(_pObj); }
    const vector<CActor*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer]; }
    void DeleteAllActor();
    void DeleteActor(LAYER _eLayer);

    bool IsInitComplet() { return m_bInitcomplet; }
    void SetInitComplet() { m_bInitcomplet = true; }

    void SetFocusedUI(CActor* _pUI);
    void CloseUI(CActor* _pUI);
    void OpenUI(CActor* _pUI);

public:
    virtual void CreateUI() = 0;

public:
    CMap* GetCurMap() { return m_pCurMap; }
    void  SetCurMap(CMap* _pMap) { m_pCurMap = _pMap; }

public:
    void AddPortal(CPortal* _pPortal, UINT _PORTALNO) { m_pPortal[_PORTALNO] = _pPortal; }
    CPortal* GetPortal(PORTAL _portalNo) { return m_pPortal[(UINT)_portalNo]; }
    void PortalInit(PORTAL _CurMapPortal, PORTAL _NextMapPortal, LEVEL_TYPE _NextLevelType);
    
    void CreatePlayer(UINT _iPortalNo);
    void CreatePlayer(Vec2 _vPos);
    void ChangeBgm();

protected:
    void MapFileLoad(wstring _mapFileName);
    virtual void LoadMapData(wifstream& _ifs);

public:
    CLONE_DEACTIVATE(CLevel);

public:
    CLevel();
    virtual ~CLevel();

    friend class CToolLevel;
};
