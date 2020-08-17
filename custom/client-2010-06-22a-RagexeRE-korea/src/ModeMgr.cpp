#include "Enum.h" // ServiceType
#include "GameMode.h"
#include "Globals.h" // g_hMainWnd, g_sysQuit
#include "LoginMode.h"
#include "ModeMgr.h"
#include <Shellapi.h>


CModeMgr::CModeMgr()
{
	m_loopCond = TRUE;
}


BOOL CModeMgr::GetLoopCond()
{
	return m_loopCond;
}


CMode* CModeMgr::GetCurMode()
{
	return m_curMode;
}


CLoginMode* CModeMgr::GetLoginMode()
{
	return ( m_curModeType == MT_LOGIN ) ? (CLoginMode*)m_curMode : NULL;
}


CGameMode* CModeMgr::GetGameMode()
{
	return ( m_curModeType == MT_GAME ) ? (CGameMode*)m_curMode : NULL;
}


void CModeMgr::Run(int modeType, const char* worldName)
{
	m_curModeType = modeType;
	m_nextModeType = modeType;
	strcpy(m_curModeName, worldName);
	strcpy(m_nextModeName, worldName);

	while( m_loopCond )
	{
		if( g_sysQuit )
			break;

		m_curModeType = m_nextModeType;
		strcpy(m_curModeName, m_nextModeName);

		if( m_curModeType == MT_LOGIN )
			m_curMode = new CLoginMode();
		else
		if( m_curModeType == MT_GAME )
			m_curMode = new CGameMode();

		m_curMode->OnInit(m_curModeName);
		m_curMode->OnRun();
		m_curMode->OnExit();

		delete m_curMode;
		m_curMode = NULL;
	}
}


void CModeMgr::Switch(int modeType, const char* modeName)
{
	m_curMode->CMode::PostQuitMsg();
	strcpy(m_nextModeName, modeName);
	m_nextModeType = modeType;
}


void CModeMgr::Quit()
{
	m_curMode->CMode::PostQuitMsg();
	if( g_serviceType == ServiceIndia )
		ShellExecuteA(g_hMainWnd, "open", "http://www.ragnarok.co.in/index.php", NULL, NULL, SW_SHOWNORMAL);
	m_loopCond = FALSE;
}
