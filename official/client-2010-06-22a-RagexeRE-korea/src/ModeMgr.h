#pragma once
class CMode;
class CLoginMode;
class CGameMode;


enum MODETYPE
{
	MT_LOGIN = 0,
	MT_GAME  = 1,
};


class CModeMgr
{
public:
	CModeMgr();
	void Run(int modeType, const char* worldName);
	void Switch(int modeType, const char* modeName);
	void Quit();

public:
	BOOL GetLoopCond();
	CMode* GetCurMode();
	CGameMode* GetGameMode();
	CLoginMode* GetLoginMode();

private:
	/* this+ 0 */ BOOL m_loopCond;
	/* this+ 4 */ CMode* m_curMode;
	/* this+ 8 */ char m_curModeName[40];
	/* this+48 */ char m_nextModeName[40];
	/* this+88 */ int m_curModeType; //enum MODETYPE
	/* this+92 */ int m_nextModeType; //enum MODETYPE
};
