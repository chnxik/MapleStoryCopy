#pragma once

class CLevel;
class CLevelState;

class CLevelMgr
{
	SINGLE(CLevelMgr);
private:
	CLevel* m_arrLevel[(UINT)LEVEL_TYPE::END];
	CLevel* m_pCurLevel;
	CLevelState* m_pState;

	LEVEL_TYPE	m_eNextLevel;
	UINT		m_iNextPortalNo;
	bool		m_bWaiting;	// 조작 대기


public:
	void init();
	void tick();
	void render(HDC _dc);

public:
	void ChangeLevel(LEVEL_TYPE _eNext, UINT _iPortalNo);
	void ChangeState(CLevelState* _newState);

public:
	bool IsWaiting() { return m_bWaiting; }
	void SetWaiting(bool _b) { m_bWaiting = _b; }
	void SetChangeInfo(LEVEL_TYPE _eNext, UINT _iPortalNo)
	{
		m_eNextLevel = _eNext;
		m_iNextPortalNo = _iPortalNo;
	}

public:
	CLevel* GetCurLevel() { return m_pCurLevel; }

	friend class CEventMgr;
	friend class CLevelChange;
};