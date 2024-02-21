#pragma once
#include "CUI.h"

class CEditorLevel;
class CTexture;
class CSound;

typedef void(*TestFuncType)(void);          // 기본 void 함수포인터
typedef void(CEntity::* DELEGATE)(void);    // CEntity를 상속받은 모든 클래스의 함수를 호출할 수 있는 함수포인터.

class CBtnUI :
    public CUI
{
private:
    CTexture*       m_pOverTex;         // Mouse Over Texture
    CTexture*       m_pPressTex;        // Mouse Press Texture
    CTexture*       m_pDisAble;         // DisAbleBtn
    Vec2            m_vOffset;          // render Offset

    CSound*         m_pBtOverSound;     // Mouse Over Sound;
    bool            m_bBtOnCheck;
    bool            m_bActive;          // 활성화

    bool            _DebugBtn;

    // Call Back
    TestFuncType    m_pFunc;

    // Delegate
    CEntity*        m_pInst;
    DELEGATE        m_pDelegateFunc;

public:
    void SetCallBack(TestFuncType _pCallBack) { m_pFunc = _pCallBack; }
    void SetDelegate(CEntity* _pInst, DELEGATE _Func)
    {
        m_pInst = _pInst;
        m_pDelegateFunc = _Func;
    }

public:
    void SetMsOverTex(CTexture* _pTex) { m_pOverTex = _pTex; }
    void SetMsPressTex(CTexture* _pTex) { m_pPressTex = _pTex; }
    void SetDisAbleTex(CTexture* _pTex) { m_pDisAble = _pTex; }
    void SetOffset(Vec2 _vOffset) { m_vOffset = _vOffset; }
    void SetMsOverSound(CSound* _pSound) { m_pBtOverSound = _pSound; }

    void SetDebugBtn() { _DebugBtn = true; }
    void SetActive(bool _b) { m_bActive = _b; }

    virtual void render(HDC _dc);


private:
    virtual void MouseLbtnDown() override;
    virtual void MouseLbtnClicked() override;
    virtual void MouseOn() override;

public:
    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

