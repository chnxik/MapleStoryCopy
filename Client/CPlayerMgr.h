#pragma once

class CPlayer;
class CStatusBarUI;
class CExpBarUI;
class CQuickSlotUI;
class CPlayerStatWin;
class CPlayerSkillWin;
class CPlayerInvenWin;
class CItem;

class CPlayerMgr
{
private:
	SINGLE(CPlayerMgr)
private:
	CPlayer* m_pPlayer;
	CStatusBarUI* m_pStatusBar;
	CExpBarUI* m_pExpBar;
	CQuickSlotUI* m_pQuickSlot;
	CPlayerStatWin* m_pPlayerStatWin;
	CPlayerSkillWin* m_pPlayerSkillWin;
	CPlayerInvenWin* m_pPlayerInvenWin;

private:
	UINT m_iSkillLv[(UINT)SKILL::END];

public:
	void tick();

public:
	void init();
	void ToggleStatWin();
	void ToggleSkillWin();
	void ToggleInvenWin();

	CPlayer* GetPlayer() { return m_pPlayer; }
	CStatusBarUI* GetStatusBar() { return m_pStatusBar; }
	CExpBarUI* GetExpBar() { return m_pExpBar; }
	CQuickSlotUI* GetQuickSlot() { return m_pQuickSlot; }
	CPlayerStatWin* GetStatWin() { return m_pPlayerStatWin;	}
	CPlayerSkillWin* GetSkillWin() { return m_pPlayerSkillWin; }
	CPlayerInvenWin* GetInvenWin() { return m_pPlayerInvenWin; }

public:

public:
	void AddSkillLv(SKILL _skill);
	UINT GetSkillLv(SKILL _skill) { return m_iSkillLv[(UINT)_skill]; }
};

