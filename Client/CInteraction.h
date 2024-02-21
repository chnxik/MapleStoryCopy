#pragma once
#include "CActor.h"

class CPlayer;
class CSound;

class CInteraction :
    public CActor
{
private:
    CPlayer* m_pPlayer;
    CSound* m_pSound;
    float m_fAcc;
    float m_fTime;
    float m_fNextActTime;

public:
    virtual void tick();

    virtual void Active() {}
    CPlayer* GetPlayer() { return m_pPlayer; }
    
    void SetSound(CSound* _sound) { m_pSound = _sound; }
    CSound* GetSound() { return m_pSound; }
    
    void SetTime(float _Time) { m_fTime = _Time; m_fNextActTime = _Time; }
    void SetNextActTime(float _Time) { m_fNextActTime = _Time; }
    float GetTime() { return m_fTime; }
    float GetNextActTime() { return m_fNextActTime; }

public:
    virtual void BeginOverlap(CCollider* _pOther) {}
    virtual void OnOverlap(CCollider* _pOther) {}
    virtual void EndOverlap(CCollider* _pOther) {}

    CLONE_DEACTIVATE(CInteraction);

public:
    CInteraction(CPlayer* _pPlayer);
    ~CInteraction();
};

