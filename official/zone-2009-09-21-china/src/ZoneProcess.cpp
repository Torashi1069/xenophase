#include "AgitDB.h"
#include "CAgitMapRes.hpp"
#include "CAuctionCtrl.hpp"
#include "CBuffInfoMgr.hpp"
#include "CCashItemShopDB.hpp"
#include "CCashItemShopScript.hpp"
#include "CharacterMgr.h"
#include "CCharInfoDB.hpp"
#include "CCharMTInfo.hpp"
#include "CCheckUseItemList.hpp"
#include "CompositionLog.h"
#include "CCoupleInfoDB.hpp"
#include "CreatePackageScript.h"
#include "DBScriptInfo.h"
#include "ErrorLog.h"
#include "CExpParameter.hpp"
#include "CFamilyInfoDB.hpp"
#include "FSMMgr.h"
#include "CGlobalVarDB.hpp"
#include "GuildDB.h"
#include "CGVar.hpp"
#include "HomunLog.h"
#include "HSvrIO.h"
#include "HSvrIOPacketHandler.h"
#include "ImportantItem.h"
#include "CItemList.hpp"
#include "ItemLog.h"
#include "ItemPackageScript.h"
#include "ISvrIO.h"
#include "ISvrIOPacketHandler.h"
#include "ItemReuseLimit.h"
#include "CITPMgr.hpp"
#include "CJobCodeForItem.hpp"
#include "LogRecorder.h"
#include "CLottoDB.hpp"
#include "CMakerRankDB.hpp"
#include "MakingLog.h"
#include "MapInfo.h"
#include "MapResMgr.h"
#include "MapTypePropertyMgr.h"
#include "CMaxHpSp.hpp"
#include "CMercenaryConfiguration.hpp"
#include "CMercenaryDBV2.hpp"
#include "MercenaryLog.h"
#include "CMercenarySkillMgr.hpp"
#include "CMerceDB.hpp"
#include "MonParameterMgr.h"
#include "MyMiniDumpUnhandledExceptionHandler.h"
#include "CMEventDB.hpp"
#include "CMVPInfo.hpp"
#include "NpcServer/NpcSvr.h"
#include "CNPCAddSkillInfo.hpp"
#include "Path.h"
#include "PetDefaultValue.h"
#include "CPetDB.hpp"
#include "PetLog.h"
#include "PresentLog.h"
#include "CPCSkillDB.hpp"
#include "CPEventDB.hpp"
#include "CPKInfoMgr.hpp"
#include "CProcessTimeChecker.hpp"
#include "CPvPScoreDB.hpp"
#include "QuestEventMgr.h"
#include "RefiningLog.h"
#include "RoomMgr.h"
#include "ScriptCompiler.h"
#include "ScriptEventMgr.h"
#include "ServerInfo.h"
#include "SkillLog.h"
#include "CSkillTypeInfoMgr.hpp"
#include "CSpecialItemMgr.hpp"
#include "CStatpointPerLevel.hpp"
#include "CStatusPlusInfoByJLV.hpp"
#include "StatusLog.h"
#include "StorePasswordDB.h"
#include "CSummonMonsterTable.hpp"
#include "TestButton.h"
#include "CUIDGenerator.hpp"
#include "ZoneProcess.h"
#include "ZoneScript.h"
#include "ZGuildMgr.h"
#include "ZSAcceptHandler.h"
#include "N2System/N2SystemMgr.h"
#include "AsyncDBWork/NAsyncDBMgr.h"
#include "AsyncDBWork/NSystemMgr.h"
#include "FontShop/CFontShopMgr.h"
#include "Instant Map/InstantMapMgr.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "NetLib/Acceptor.h"
#include "shared.h"
#include "enum.hpp"
#include "globals.hpp"
#include <process.h>


hook_func<int (__cdecl *)(HINSTANCE hInstance, int nCmdShow)> _InitInstance(SERVER, "InitInstance");
int __cdecl InitInstance(HINSTANCE hInstance, int nCmdShow) // line 551
{
	return (_InitInstance)(hInstance, nCmdShow);

	g_hInst = hInstance;

	WNDCLASSEXA wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_CLASSDC|CS_DBLCLKS;
	wc.lpfnWndProc = &WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandleA(NULL);
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Ragnarok";
	wc.hIconSm = NULL;
	RegisterClassExA(&wc);

	char buf[256];
	mystd::string windowName = "RO - GROBAL_VERSION";
	sprintf(buf, "(VC9)%s ( %s )", windowName.c_str(), "Sep 21 2009 18:00:27");

	g_hWnd = CreateWindowExA(0, "Ragnarok", buf, WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_GROUP|WS_TABSTOP, 100, 100, 700, 600, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	if( g_hWnd == NULL )
	{
		MessageBoxA(NULL, "failed window", "error", MB_OK);
		return 0;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);
	return 1;
}


hook_func<LRESULT (CALLBACK *)(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)> _WndProc(SERVER, "WndProc");
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // line 616
{
	return (_WndProc)(hWnd, msg, wParam, lParam);

	switch( msg )
	{
	case WM_CREATE:
	{
		CREATESTRUCT* pCS = (CREATESTRUCT*)lParam;
		ToggleButtonCriticalLog->CTestButton::OnCreate(hWnd, pCS->hInstance, (short)GetDialogBaseUnits() + 400, GetDialogBaseUnits() >> 16, 80, 21, "critical log");
		ToggleButtonTraceLog->CTestButton::OnCreate(hWnd, pCS->hInstance, (short)GetDialogBaseUnits() + 400, (GetDialogBaseUnits() >> 16) + 22, 80, 21, "trace log");
	}
	break;

	case WM_DESTROY:
		g_errorLogs->CErrorLog::CriticalErrorLog("WM_DESTROY", 1317, ".\\ZoneProcess.cpp");
		ExitProcess(EXIT_FAILURE);
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		RECT rect;
		BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		FillRect(ps.hdc, &rect, (HBRUSH)GetStockObject(0));

		char buf[256];
		int pos = 0;

		sprintf(buf, "no");
		if( g_isCriticalLog != 0 )
			sprintf(buf, "yes");
		TextOutA(ps.hdc, ToggleButtonCriticalLog->CTestButton::GetWidth() + ToggleButtonCriticalLog->CTestButton::GetX() + 5, ToggleButtonCriticalLog->CTestButton::GetY(), buf, strlen(buf));

		sprintf(buf, "no");
		if( Trace == TraceF )
			sprintf(buf, "yes");
		TextOutA(ps.hdc, ToggleButtonTraceLog->CTestButton::GetWidth() + ToggleButtonTraceLog->CTestButton::GetX() + 5, ToggleButtonTraceLog->CTestButton::GetY(), buf, strlen(buf));

		sprintf(buf, "EPISODE_VER %d.0", 99999);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		if( !g_zsAcceptHandler->CZSAcceptHandler::GetAcceptable() )
		{
			SetTextColor(ps.hdc, 0xFFu);
			pos += 16;
			TextOutA(ps.hdc, 0, pos, "Client Accept FALSE ! ! !", 25);
			SetTextColor(ps.hdc, GetTextColor(ps.hdc));
		}

		if( g_IsNpcSvrOn )
		{
			pos += 16;
			TextOutA(ps.hdc, 0, pos, "NPCSvr : ON", 11);
		}
		else
		{
			SetTextColor(ps.hdc, 0xFFu);
			pos += 16;
			TextOutA(ps.hdc, 0, pos, "NPCSvr : OFF", 12);
			SetTextColor(ps.hdc, GetTextColor(ps.hdc));
		}

		if( g_bPremium_Service == 1 )
		{
			sprintf(buf, "Premium_Service");
			pos += 16;
			TextOutA(ps.hdc, 0, pos, buf, strlen(buf));
		}

		if( g_isMobileEventOn != 0 )
		{
			char mobile[128];
			memset(mobile, 0, sizeof(mobile));
			sprintf(mobile, "MOBILE_EVENT TYPE = %d", g_isMobileEventOn);
			pos += 16;
			TextOutA(ps.hdc, 0, pos, mobile, strlen(mobile));
		}

		sprintf(buf, "ITEM_VERSIONINFO %d", 4);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		if( g_isGameGuardOn == 1 )
			sprintf(buf, "GAMEGUARD : ON");
		else
			sprintf(buf, "GAMEGUARD : OFF");
		pos =+ 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		if( g_gameGuardSwitch == 1 )
		{
			sprintf(buf, "GAME GUARD (ON / OFF) SYSTEM");
			pos += 16;
			TextOutA(ps.hdc, 0, pos, buf, strlen(buf));
		}

		pos += 16;
		if( g_isKillerSystem != 0 )
			TextOutA(ps.hdc, 0, pos, "KILLER_SYSTEM : ON", 18);
		else
			TextOutA(ps.hdc, 0, pos, "KILLER_SYSTEM : OFF", 19);

		sprintf(buf, "KILLER_SYSTEM VERSION : 2");
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "MAIL AUCTION SYSYTEM");
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		if( g_isGuildDelete == 0 )
		{
			SetTextColor(ps.hdc, 0xFFu);
			pos += 16;
			TextOutA(ps.hdc, 0, pos, "Guild Disorganization Not Use!!!", 32);
			SetTextColor(ps.hdc, GetTextColor(ps.hdc));
		}

		if( g_isGuildEmergencyCall == 0 )
		{
			SetTextColor(ps.hdc, 0xFFu);
			pos += 16;
			TextOutA(ps.hdc, 0, pos, "Guild Emergency Call Not Use!!!", 31);
			SetTextColor(ps.hdc, GetTextColor(ps.hdc));
		}

		sprintf(buf, "ForeignCode : %d", g_ForeignCode);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		if( g_Free_Server == 1 )
		{
			pos += 16;
			TextOutA(ps.hdc, 0, pos, "TAIWAN FREE SERVER", 18);
		}

		sprintf(buf, "CASH_POINT_ITEM_SHOP V2, MailSize =  %d", 40);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		if( g_SimpleCashShop == 1 )
		{
			sprintf(buf, "_SIMPLE_CASH_SHOP");
			pos += 16;
			TextOutA(ps.hdc, 0, pos, buf, strlen(buf));
		}

		sprintf(buf, "__MEMORIAL_DUNGEON");
		if( CInstantMapMgr::GetObj() != NULL )
		{
			char temp[260];
			_snprintf(temp, sizeof(temp), "Ctrl(%d)", CInstantMapMgr::GetObj()->CInstantMapMgr::GetCtrlCount());
			memcpy(buf, temp, strlen(temp) + 1);
		}
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "__ASYNC_DB_WORK(%d)", CGVar::GetObj()->m_AsyncDBThreadNum);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "__PARTY_INVITE");
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "__QUEST_EVENT_SYSTEM_  Version = %d", 2);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		if( CAgitMapRes::IsSiegeTime_ByMapType(MAPTYPE_AGIT) )
		{
			sprintf(buf, "SIEGE V1.0 : Siege Mode");
		}
		else
		{
			time_t t2 = CAgitMapRes::GetNextSigeTime();
			tm* t = _localtime32(&t2);
			sprintf(buf, "SIEGE V1.0 : Next Siege Time %d / %d  %d", t->tm_mon + 1, t->tm_mday, t->tm_hour);
		}
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		if( g_siegeV15On == 0 )
		{
			SetTextColor(ps.hdc, 0xFF);
			TextOutA(ps.hdc, 300, pos, "SIEGE Version 1.5 : OFF", 23);
			SetTextColor(ps.hdc, GetTextColor(ps.hdc));
		}
		else
		if( CAgitMapRes::IsSiegeTime_ByMapType(18) )
		{
			sprintf(buf, "SIEGE V1.5 : Siege Mode");
			TextOutA(ps.hdc, 300, pos, buf, strlen(buf));
		}
		else
		{
			time_t t2 = CAgitMapRes::GetNextSigeTime_v15();
			tm* t = _localtime32(&t2);
			sprintf(buf, "SIEGE V1.5 : Next Siege Time %d / %d  %d", t->tm_mon + 1, t->tm_mday, t->tm_hour);
			TextOutA(ps.hdc, 300, pos, buf, strlen(buf));
		}

		sprintf(buf, "AGIT_EMPLIUM_HP_SETTING  %d", g_empelium_hp);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "MAX_STORE_SIZE %d, StoreMaxItemSize  %d", 600, g_StoreMaxItemSize);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "MAPPROPERTY_EXTEND");
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "_ZENY_CHECKSUM = %d", g_ZenyChecksum);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "NPC Count:%d\t  Used Memory : %dByte", g_characterMgr->CCharacterMgr::GetMonsterCount(), g_npcMemorySize * g_characterMgr->CCharacterMgr::GetMonsterCount());
		pos += 30;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "User Count:%d, Valid User Count:%d, Disconnect User Conut:%d", g_characterMgr->CCharacterMgr::GetCurPlayChar(), g_characterMgr->CCharacterMgr::GetCurValidPlayChar(), g_characterMgr->CCharacterMgr::GetCurDisconnectCountPlayChar());
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "section Count:%d", g_mapResMgr->CMapResMgr::GetTotalSectionSize());
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "Guild Count:%d Free Size:%d  OffSet : %d", g_ZGuildMgr->CGuildMgr::GetGuildSize(), g_ZGuildMgr->CZGuildMgr::GetFreeSize(), g_ZGuildMgr->CZGuildMgr::GetOffset());
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "Skill Count:%d/%d  ", g_characterMgr->CCharacterMgr::GetSkillSize(), g_maxSkill);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "Zone Login - Inter Login : %d , Zone-Inter Login Error : %d ", g_ZoneInterLoginValue, g_ZoneInterLoginError);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		sprintf(buf, "Zone ProcessTime / Max ProcessTime  : %d / %d ", (int)g_ProcessTime, (int)g_MaxProcessTime);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		pos += 16;
		for( int i = 0; i < 8; ++i )
		{
			sprintf(buf, "%d[%d]", i, (int)g_ProcessTimeList[i]);
			TextOutA(ps.hdc, 60 * i, pos, buf, strlen(buf));
		}
		sprintf(buf, "Body[%d] Store[%d] ", g_BodyItemLoadProcssTime->CProcessTimeChecker::GetMax(), g_StoreItemLoadProcssTime->CProcessTimeChecker::GetMax());
		TextOutA(ps.hdc, 480, pos, buf, strlen(buf));

		sprintf(buf, "NPC Event Max [Real / Max] ProcessTime  [%d / %d]", (int)g_NpcProcessTimeList[0], (int)g_NpcProcessTimeList[1]);
		pos += 16;
		TextOutA(ps.hdc, 0, pos, buf, strlen(buf));

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_COMMAND:
		if( wParam == 20 )
		{
			g_isCriticalLog = 1 - g_isCriticalLog;
		}
		else
		if( wParam == 21 )
		{
			Trace = ( Trace != TraceN ) ? TraceN : TraceF;
		}
		else
			break;

		InvalidateRect(hWnd, NULL, FALSE);
	break;

	case WM_TIMER:
		InvalidateRect(hWnd, NULL, FALSE);
	break;

	case WM_RBUTTONDOWN:
		if( g_IsNpcSvrOn )
			InvalidateRect(hWnd, NULL, TRUE);
	break;

	default:
	break;
	}

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}


hook_func<bool (__cdecl *)(void)> _InitFromRoInf(SERVER, "InitFromRoInf");
bool __cdecl InitFromRoInf(void) // line 1393
{
	return (_InitFromRoInf)();

	//TODO
}


static hook_func<int (__cdecl *)(int nMin, int nMax)> _GetServerRandom(SERVER, "GetServerRandom");
static hook_val<int> bRandFirst(SERVER, "bRandFirst");
static hook_val<int> gStartTime(SERVER, "gStartTime");
static hook_val<int> gPid(SERVER, "gPid");
int GetServerRandom(int nMin, int nMax) // line 3068
{
	return (_GetServerRandom)(nMin, nMax);

	if( nMax == nMin )
		return nMin;

	if( bRandFirst == 0 )
	{
		gStartTime = timeGetTime();
		gPid = _getpid();
		srand(gStartTime + gPid);
		bRandFirst = 1;
	}

	LARGE_INTEGER PerformanceCount;
	QueryPerformanceCounter(&PerformanceCount);
	return min(nMin, nMax) + (rand() + PerformanceCount.LowPart) % (unsigned int)(nMax - nMin + 1); //FIXME: incorrect result if nMax < nMin, also allows division-by-zero
}


hook_func<bool (__cdecl *)(void)> _ScriptCompile(SERVER, "ScriptCompile");
bool __cdecl ScriptCompile(void) // line 3174
{
	return (_ScriptCompile)();

	CScriptCompiler compiler;
	g_itpMgr->CITPMgr::Save(GetScriptFileName(DEF_ITEM));
	g_monParameter->CMonsterParameterTable::SaveToFileMobName(GetScriptFileName(DEF_MOBNAME));
	g_monParameter->CMonsterParameterTable::SaveToFileNpcSpr(GetScriptFileName(DEF_NPCSPR));
	g_skillTypeInfoMgr->CSkillTypeBaseInfo::SaveToFile(GetScriptFileName(DEF_SKILL));

	if( !compiler.CScriptCompiler::Init() )
	{
		MessageBoxA(0, "SCRIPT COMPILE FAIL !!", "ERROR", 0);
		return false;
	}

	return true;
}


hook_func<int (__stdcall *)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)> _WinMain(SERVER, "WinMain");
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) // line 1740
{
	return (_WinMain)(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	if( !CMyMiniDumpUnhandledExceptionHandler::CreateInstance() )
		return 0;

	SYSTEMTIME st;
	GetLocalTime(&st);
	_snprintf(g_szCriticalLogFileName, 260, "criticalError(%04d%02d%02d).txt", st.wYear, st.wMonth, st.wDay);
	_snprintf(g_szTraceLogFileName, 260, "TraceLog(%04d%02d%02d).txt", st.wYear, st.wMonth, st.wDay);

	HANDLE v5 = CreateMutexA(0, 0, "Global\\Ragnarok Zone Server");
	if( WaitForSingleObject(v5, 0) )
	{
		MessageBoxA(0, "Another Zone Server is Still Executing", 0, 0);
		return 0;
	}
	if( !CGVar::CreateInstance() )
	{
		MessageBoxA(0, "CGvar Init faile", "zoneserver error", 0);
		return 0;
	}
	if( !InitInstance(hInstance, nCmdShow) )
	{
		MessageBoxA(0, "failed init window", 0, 0);
		return 0;
	}

	unsigned int wTimerRes = 0;
	timecaps_tag tc;
	if( !timeGetDevCaps(&tc, 8u) )
	{
		unsigned int v6 = tc.wPeriodMin;
		unsigned int v7 = tc.wPeriodMin;

		if( tc.wPeriodMin <= 1u )
			v7 = 1;
		if( v7 >= tc.wPeriodMax )
		{
			v6 = tc.wPeriodMax;
			wTimerRes = tc.wPeriodMax;
		}
		else
		{
			if( tc.wPeriodMin <= 1u )
			{
				v6 = 1;
				wTimerRes = 1;
			}
			else
			{
				wTimerRes = tc.wPeriodMin;
			}
		}
		timeBeginPeriod(v6);
	}

	g_curTime = _time32(NULL);

	if( !InitFromRoInf() )
	{
		MessageBoxA(0, "InitFromRoInf failed", "zoneserver error", 48);
		return 0;
	}

	WSAData wsaData;
	if( WSAStartup(MAKEWORD(2,2), &wsaData) == -1 )
	{
		MessageBoxA(0, "Check OS TCP/IP setting.", 0, 0);
		return 0;
	}

	g_pathData->CPathData::SetFileName("DBInfo.scp");
	if( !g_dbScriptInfo->CDBScriptInfo::Load(g_pathData) )
	{
		MessageBoxA(0, "Check DBInfo.scp file exist.", 0, 0);
		return 0;
	}

	const char* v11 = g_dbScriptInfo->CDBScriptInfo::Search("globalinfo");
	const char* v14 = g_dbScriptInfo->CDBScriptInfo::Search("character");
	const char* v12 = g_dbScriptInfo->CDBScriptInfo::Search("script");
	const char* IPInfo = g_dbScriptInfo->CDBScriptInfo::Search("ipinfo");
	const char* v10 = g_dbScriptInfo->CDBScriptInfo::Search("log");
	if( !v11 || !v14 || !v12 || !IPInfo || !v10 )
	{
		MessageBoxA(0, "check DBInfo.scp invalid", 0, 0);
		return 0;
	}

	Trace("AddDSN begin\n");
	if( !AddDSN() )
	{
		MessageBoxA(0, "AddDSN failed", "zone server error", 48);
		return 0;
	}
	Trace("AddDSN end\n");

	if( !CCheckUseItemList::CreateInstance() )
	{
		MessageBoxA(0, "Error", "CCheckUseItemList::CreateInstance", 0);
		return 0;
	}

	Trace("g_statpointPerLevel\tINIT START\n");
	g_statpointPerLevel->CStatpointPerLevel::Init();
	g_statpointPerLevel->CStatpointPerLevel::LoadStatpointPerLevel();

	Trace("FSM INIT START\n");
	g_fsmMgr->CFSMMgr::Init();

	Trace("ITPMGR INIT START\n");
	g_itpMgr->CITPMgr::Init(v12);

	Trace("g_metalItemList load START\n");
	g_metalItemList->CItemList::LoadFromFile(g_pathData->CPathData::SetFileName("metalitemlist.scp"), 20020627);
	g_weaponItemList->CItemList::LoadFromFile(g_pathData->CPathData::SetFileName("weaponitemList.scp"), 20020627);
	g_potionItemList->CItemList::LoadFromFile(g_pathData->CPathData::SetFileName("potionitemList.scp"), 20030515);

	Trace("g_monParameter INIT START\n");
	g_monParameter->CMonParameterMgr::Init(v12);

	Trace("g_expParameter\tINIT START\n");
	g_expParameter->CExpParameter::Init(v12);

	Trace("g_maxHpSp INIT START\n");
	g_maxHpSp->CMaxHpSp::Init();
	g_maxHpSp->CMaxHpSp::LoadHp();
	g_maxHpSp->CMaxHpSp::LoadSp();
	g_maxHpSp->CMaxHpSp::LoadMaxHPSP();

	Trace("g_AgitDB\tINIT START\n");
	g_AgitDB->CODBC::Init(v14, "character", g_dbPWD, v14, 0);

	Trace("g_mvpInfo\tINIT START\n");
	g_mvpInfo->CMVPInfo::Init(v12, "script", g_GlobaldbPWD, v12, 0);

	Trace("g_charMTInfo\tINIT START\n");
	g_charMTInfo->CCharMTInfo::Init();

	Trace("g_serverInfo.Init\n");
	g_serverInfo->CServerInfo::Init("globalinfo", g_GlobaldbPWD, v11, 3);

	if( g_characterServerPort != 0 )
		g_serverInfo->CServerInfo::SetServerPort(g_serverInfo->CServerInfo::GetDestinationSID(1), g_characterServerPort);

	g_ZGuildDB->CGuildDB::Init(v14, "character", g_dbPWD, v14, 0);

	int v22 = GetPrivateProfileIntA("ETC", "MAXGUILD", 0, g_infFile);
	g_ZGuildMgr->CZGuildMgr::Init(v22);
	Trace("g_ZGuildMgr after\n");

	if( !CCreatePackageScript::GetObj()->CCreatePackageScript::Init() )
		return 0;

	Trace("_CASH_POINT_ITEM_SHOP1\n");
	char CashPointItemShop_DBname[32] = "";
	GetPrivateProfileStringA("DSN", "CASHPOINTITEMSHOP_DB", "", CashPointItemShop_DBname, sizeof(CashPointItemShop_DBname), g_infFile);
	const char* v24 = g_dbScriptInfo->CDBScriptInfo::Search("cash_point_item_shop");
	if ( !v24 )
	{
		MessageBoxA(0, "cash item shop DSN/DB name not found", "check DBInfo.scp/Ro.ini invalid", 0);
		return 0;
	}

	Trace("_CASH_POINT_ITEM_SHOP2\n");
	char Buffer[80];
	char DBPWD[256];
	strncpy(Buffer, "unknown", sizeof(Buffer));
	strncpy(DBPWD, "unknown", sizeof(DBPWD));
	GetPrivateProfileStringA("ETC", "DBPWD_CASHITEMSHOP", "unknown", Buffer, sizeof(Buffer), g_infFile);
	Decrypt(Buffer, DBPWD);

	Trace("_CASH_POINT_ITEM_SHOP3\n");
	CCashItemShopDB::GetObj()->CODBCV2::Init(v24, "cashitemshop", DBPWD, CashPointItemShop_DBname, CODBCV2Connector::DSN_CONNECT_TYPE, false);

	Trace("_CASH_POINT_ITEM_SHOP4\n");
	if( !CCashItemShopScript::GetObj()->CCashItemShopScript::Init() )
	{
		MessageBoxA(0, "CashItemShopScript.txt loading error", "CashItemShopScript.txt", 0);
		return 0;
	}
	if( !CItemPackageScript::GetObj()->CItemPackageScript::Init() )
	{
		MessageBoxA(0, "item package script error", "critical", 0);
		return 0;
	}

	Trace("ENABLE_ITEMLOG1\n");
	if ( !CUIDGenerator::GetObj()->CUIDGenerator::Init() )
	{
		MessageBoxA(0, "unique identity number generator init error found", "UID Generator", 0);
		return 0;
	}

	Trace("ENABLE_ITEMLOG2\n");
	g_importantItem->CImportantItem::LoadImportantItem();

	Trace("ENABLE_ITEMLOG3\n");
	g_itemLog->CItemLog::ConnectToDatabase(v10);

	Trace("ENABLE_ITEMLOG4\n");
	g_logRecorder->CLogRecorder::Add(&g_itemLog);
	Trace("End ENABLE_ITEMLOG5\n");

	g_makingLog->CMakingLog::ConnectToDatabase(v10);
	g_logRecorder->CLogRecorder::Add(&g_makingLog);
	Trace("End ENABLE_MAKINGLOG\n");

	g_refiningLog->CRefiningLog::ConnectToDatabase(v10);
	g_logRecorder->CLogRecorder::Add(&g_refiningLog);
	Trace("End ENABLE_REFININGLOG\n");

	g_skillLog->CSkillLog::ConnectToDatabase(v10);
	g_logRecorder->CLogRecorder::Add(&g_skillLog);
	Trace("End ENABLE_SKILLLOG\n");

	g_statusLog->CStatusLog::ConnectToDatabase(v10);
	g_logRecorder->CLogRecorder::Add(&g_statusLog);
	Trace("End ENABLE_STATUSLOG\n");

	g_compositionLog->CCompositionLog::ConnectToDatabase(v10);
	g_logRecorder->CLogRecorder::Add(&g_compositionLog);
	Trace("End ENABLE_COMPOSITIONLOG\n");

	g_presentLog->CPresentLog::ConnectToDatabase(v10);
	g_logRecorder->CLogRecorder::Add(&g_presentLog);
	Trace("End ENABLE_PRESENTLOG\n");

	g_homunLog->CHomunLog::ConnectToDatabase(v10);
	g_logRecorder->CLogRecorder::Add(&g_homunLog);
	Trace("End ENABLE_HOMUNLOG\n");

	g_MercenaryLog->CMercenaryLog::ConnectToDatabase(v10);
	g_logRecorder->CLogRecorder::Add(&g_MercenaryLog);
	Trace("End ENABLE_MERCENARYLOG\n");

	g_petLog->CPetLog::ConnectToDatabase(v10);
	g_logRecorder->CLogRecorder::Add(&g_petLog);
	Trace("End PET_LOG\n");

	g_mapInfo->CODBC::Init(IPInfo, "ipinfo", g_dbPWD, IPInfo, 0);
	g_pvpScoreDB->CODBC::Init(v14, "character", g_dbPWD, v14, 0);
	g_charInfoDB->CODBC::Init(v14, "character", g_dbPWD, v14, 0);
	g_petDB->CODBC::Init(v14, "character", g_dbPWD, v14, 0);
	g_merceDB->CODBC::Init(v14, "character", g_dbPWD, v14, 0);

	g_mapInfo->CMapInfo::GetMapInfo();
	Trace("g_mapInfo.GetMapInfo\n");

	g_skillTypeInfoMgr->CSkillTypeInfoMgr::Init();

	g_pcSkillDB->CODBC::Init(v14, "character", g_dbPWD, v14, 0);
	g_coupleInfoDB->CODBC::Init(v14, "character", g_dbPWD, v14, 0);
	g_familyInfoDB->CODBC::Init(v14, "character", g_dbPWD, v14, 0);
	g_makerRankDB->CODBC::Init(v14, "character", g_dbPWD, v14, 0);
	if( IsSetting(SETTING_KILLER_SYSTEM) )
		g_PKInfoMgr->CODBC::Init(v14, "character", g_dbPWD, v14, 0);

	g_StatusPlusnfoByJLV->CStatusPlusInfoByJLV::Init();

	if( !g_buffInfoMgr->CBuffInfoMgr::Create() )
	{
		MessageBoxA(0, "Initialize error\n g_buffInfoMgr.Create()", "g_buffInfoMgr", 0);
		return 0;
	}

	if( !CMapTypePropertyMgr::CreateInstance() )
	{
		MessageBoxA(0, "Initialize error\n CMapTypePropertyMgr::CreateInstance()", "MapTypePropertyMgr", 0);
		return 0;
	}

	if( !g_mapResMgr->CMapResMgr::Init(g_serverInfo->GetLocalServerID()) )
	{
		MessageBoxA(0, "Map FILE Open Error", "error", 0);
		return 0;
	}
	Trace("MapResMgr init finished\n");

	g_characterMgr->CCharacterMgr::Init(1500);
	g_roomMgr->CRoomMgr::Init(5000);
	g_summonItemTable.CMatchTable::LoadFromFile(g_pathData->CPathData::SetFileName("ItemSummonList.txt"));
	g_summonMonsterTable->CSummonMonsterTable::LoadFromFile(g_pathData->CPathData::SetFileName("MonsterSummonList.txt"));
	g_summonMobBySkillTable.CMatchTable::LoadFromFile(g_pathData->CPathData::SetFileName("ClassChange.txt"));
	g_zoneScript->CZoneScript::Init();

	if( !g_petDefaultValue->CPetDefaultValue::Load(g_pathData->CPathData::SetFileName("PetTable.txt")) )
	{
		MessageBoxA(0, "Check... PetTable.txt", "error", 0);
		return 0;
	}

	g_pathData->CPathData::SetFileName("NpcAddSkillInfo.txt");
	if( !g_npcAddSkillInfo->CNPCAddSkillInfo::Load(g_pathData) )
	{
		MessageBoxA(0, "Check NpcAddSkillInfo.txt", "error", 0);
		return 0;
	}

	if( !ScriptCompile() )
		return 0;

	if ( !g_specialItmMgr->CSpecialItemMgr::Init() )
	{
		MessageBoxA(0, "Item Server Init Fail", "error", 0);
		return 0;
	}

	::InvalidateRect(g_hWnd, 0, false);
	Trace("Item Server Init Success.\n");

	if( g_isMobileEventOn != 0 )
	{
		if( !g_MEventDB->CODBCV2::Init(v11, "globalinfo", g_GlobaldbPWD, v11, CODBCV2Connector::DSN_CONNECT_TYPE, true) )
		{
			MessageBoxA(0, "mobile event database init or connect error", "mobile event", 0);
			return 0;
		}
	}

	g_PEventDB->CODBC::Init(v11, "globalinfo", g_GlobaldbPWD, v11, 0);
	g_globalVarDB->CODBC::Init(v14, "character", g_dbPWD, v14, 0);

	if( g_jobCodeForItem->CJobCodeForItem::Init() )
		Trace("g_jobCodeForItem.Init success\n");
	else
		MessageBoxA(0, "JobCodeForItem.scp error", "script error", 0);

	if( g_isGameGuardOn == 1 )
	{
		unsigned int v40 = InitGameguardAuth(".", 50);
		if( v40 )
		{
			sprintf(Buffer, "GameGuard ggauth.dll Load error : %d", v40);
			MessageBoxA(0, Buffer, "error", 0);
			return 0;
		}
	}

	if( (g_storePasswordCheck == 1 || g_cashShopPasswordCheck == 1) && !g_storePasswordDB->CODBC::Init(v11, "globalinfo", g_GlobaldbPWD, v11, 0) )
	{
		MessageBoxA(0, "g_storePasswordDB.Init error", "error", 0);
		return 0;
	}

	if( g_lottoCheck == 1 && !g_lottoDB->CODBC::Init(v11, "globalinfo", g_GlobaldbPWD, v11, 0) )
	{
		MessageBoxA(0, "g_lottoDB.Init error", "error", 0);
		return 0;
	}

	Trace("Before Auction Initial\n");
	g_AuctionCtrl->CAuctionCtrl::Init(g_serverInfo->GetLocalServerID(), v14, "character", g_dbPWD, v14, 0);
	Trace("Auction Over\n");

	mystd::pair<bool,mystd::string> ret;
	ret = startup();

	if( !ret.first )
	{
		MessageBoxA(0, ret.second.c_str(), "error", 0);
		return 0;
	}

	if( g_isNpcSkip == 0 && !g_npcSvr->CNpcSvr::Start() )
	{
		MessageBoxA(0, "Npc Server Start Fail 2", "error", 0);
		return 0;
	}

	if( !g_buffInfoMgr->CBuffInfoMgr::InitBuffScript() )
	{
		MessageBoxA(0, "Initialize error\n g_buffInfoMgr.InitBuffScript()", "g_buffInfoMgr", 0);
		return 0;
	}

	if( !g_skillTypeInfoMgr->CSkillTypeInfoMgr::InitSkillScript() || !g_itemReuseLimit->CItemReuseLimit::Init() )
	{
		return 0;
	}

	if( !CMercenaryDBV2::CreateInstance(v14, "character", g_dbPWD, v14, CODBCV2Connector::DSN_CONNECT_TYPE) )
	{
		MessageBoxA(0, "Initialize error", "MercenaryDBV2", 0);
		return 0;
	}

	if( !CMercenarySkillMgr::CreateInstance() )
	{
		MessageBoxA(0, "Initialize error", "CMercenarySkillMgr", 0);
		return 0;
	}

	if( !CMercenaryConfiguration::CreateInstance() )
	{
		MessageBoxA(0, "Initialize error", "CMercenaryConfiguration", 0);
		return 0;
	}

	if( !NSystemMgr::CreateInstance() )
	{
		MessageBoxA(0, "Initialize error\nNSystemMgr::CreateInstance()", "NSystemMgr", 0);
		return 0;
	}

	mystd::string characterDBconnectionStr;
	characterDBconnectionStr += "DSN=";
	characterDBconnectionStr += v14;
	characterDBconnectionStr += ";";
	characterDBconnectionStr += "UID=";
	characterDBconnectionStr += "character";
	characterDBconnectionStr += ";";
	characterDBconnectionStr += "PWD=";
	characterDBconnectionStr += mystd::string(g_dbPWD);
	characterDBconnectionStr += ";";
	if( !NAsyncDBMgr::CreateInstance(characterDBconnectionStr) )
	{
		MessageBoxA(0, "Initialize error \n NAsyncDBMgr::CreateInstance()", "NAsyncDBMgr", 0);
		return 0;
	}

	if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::Start() )
	{
		MessageBoxA(0, "start error \n NAsyncDBMgr::GetObj()->Start()", "NAsyncDBMgr", 0);
		return 0;
	}

	if( !N2SystemMgr::CreateInstance() )
	{
		MessageBoxA(0, "Initialize error\nN2SystemMgr::CreateInstance()", "N2SystemMgr", 0);
		return 0;
	}

	if( !CInstantMapMgr::CreateInstance() )
	{
		MessageBoxA(0, "Initialize error \n CInstantMapMgr::CreateInstance()", "CInstantMapMgr", 0);
		return 0;
	}

	if( !CMemorialDungeonMgr::CreateInstance() )
	{
		MessageBoxA(0, "Initialize error \n CMemorialDungeon::CreateInstance()", "CMemorialDunbeonMgr", 0);
		return 0;
	}

	if( !CInstantMapMgr::GetObj()->CInstantMapMgr::Start() )
	{
		MessageBoxA(0, "Initialize error \n CInstantMapMgr::Start()", "CInstantMapMgr", 0);
		return 0;
	}

	if( !CFontShopMgr::CreateInstance() )
	{
		MessageBoxA(0, "Initialize error", "CFontShopMgr", 0);
		return 0;
	}

	g_logRecorder->CLogRecorder::BeginSaveToDatabase();
	Trace("End g_logRecorder.BeginSaveToDatabase()\n");

	Trace("Network Init begin\n");
	g_zsAcceptHandler->CZSAcceptHandler::Init(1500);
	Trace("after g_zsAcceptHandler.Init\n");

	StartCompletionProactor();
	Trace("StartCompletionProactor\n");

	unsigned int v62; // esi@109
	v62 = g_serverInfo->CServerInfo::GetServerPrivateIPAddr(g_serverInfo->CServerInfo::GetDestinationSID(1));
	if( !v62 )
		v62 = g_serverInfo->CServerInfo::GetServerIPAddr(g_serverInfo->CServerInfo::GetDestinationSID(1));

	__int16 v65; // di@111
	v65 = g_serverInfo->CServerInfo::GetServerPrivatePort(g_serverInfo->CServerInfo::GetDestinationSID(1));
	if ( !v65 )
		v65 = g_serverInfo->CServerInfo::GetServerPort(g_serverInfo->CServerInfo::GetDestinationSID(1));

	g_hSvrIO->CSvrIO::Init(v62, v65, new CHSvrIOPacketHandler());

	unsigned int v70; // esi@116
	v70 = g_serverInfo->CServerInfo::GetServerPrivateIPAddr(g_serverInfo->CServerInfo::GetDestinationSID(2));
	if ( !v70 )
		v70 = g_serverInfo->CServerInfo::GetServerIPAddr(g_serverInfo->CServerInfo::GetDestinationSID(2));

	__int16 v73; // di@118
	v73 = g_serverInfo->CServerInfo::GetServerPrivatePort(g_serverInfo->CServerInfo::GetDestinationSID(2));
	if ( !v73 )
		v73 = g_serverInfo->CServerInfo::GetServerPort(g_serverInfo->CServerInfo::GetDestinationSID(2));

	g_iSvrIO->CSvrIO::Init(v70, v73, new CISvrIOPacketHandler());

	_ACCEPT_PARM ap;
	ap.ip = g_serverInfo->CServerInfo::GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS);
	ap.port = g_serverInfo->GetLocalPort();
	ap.backlog = 20;
	ap.ipLog = GetPrivateProfileIntA("ETC", "IPLOG", 0, g_infFile);
	ap.handler = (CAcceptHandler *)&g_zsAcceptHandler;

	void *v78;
	unsigned int ThreadID;
	v78 = (void *)_beginthreadex(NULL, 0, AcceptThread, &ap, 0, &ThreadID);
	if ( !v78 )
		return 0;
	CloseHandle(v78);
	Trace("Network Init end\n");

	while( !g_npcSvr->ClearFirstEvent() )
		g_npcSvr->CNpcSvr::Process();

	if( g_characterMgr->CCharacterMgr::CheckChashTraderNpc() == 1 && !CCashItemShopDB::GetObj()->CODBCV2::SyncConnect() )
	{
		MessageBoxA(0, "cash item shop database connect error", "cash item shop", 0);
		return 0;
	}

	g_NpcProcessTimeList[0] = 0.0;
	g_NpcProcessTimeList[1] = 0.0;
	g_ProcessTimeList[0] = 0.0;
	g_ProcessTimeList[1] = 0.0;
	g_ProcessTimeList[2] = 0.0;
	g_ProcessTimeList[3] = 0.0;
	g_ProcessTimeList[4] = 0.0;
	g_ProcessTimeList[5] = 0.0;
	g_ProcessTimeList[6] = 0.0;
	g_ProcessTimeList[7] = 0.0;
	g_ProcessTimeList[8] = 0.0;
	g_ProcessTimeList[9] = 0.0;

	tagMSG msg;
	msg.hwnd = 0;
	msg.message = 0;
	msg.wParam = 0;
	msg.lParam = 0;
	msg.time = 0;
	msg.pt.x = 0;
	msg.pt.y = 0;

	while( !g_npcSvr->ClearFirstEvent() )
	{
		if( PeekMessageA(&msg, 0, 0, 0, 1u) )
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else
		{
			g_npcSvr->CNpcSvr::Process();
		}
	}

	g_IsNpcSvrOn = true;
	::InvalidateRect(g_hWnd, 0, false);

	if( !g_questEventMgr->CQuestEventMgr::Initialize() )
	{
		MessageBoxA(0, "Quest Start Fail", "ERROR", 0);
		return 0;
	}

	g_NpcProcessTimeList[0] = 0.0;
	g_NpcProcessTimeList[1] = 0.0;

	timeGetTime();
	g_errorLogs->CErrorLog::CriticalErrorLog("Zone Process Loop Start", 2710, ".\\ZoneProcess.cpp");

	// core loop start
	while( msg.message != 18 )
	{
		if( PeekMessageA(&msg, 0, 0, 0, 1u) )
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else
		{
			DWORD v82 = timeGetTime(); // start time
			g_curTime = _time32(NULL);

			g_mapResMgr->CMapResMgr::Process();
			g_ProcessTimeList[0] = max(g_ProcessTimeList[0], timeGetTime() - v82);

			g_npcSvr->CNpcSvr::Process();
			g_ProcessTimeList[1] = max(g_ProcessTimeList[1], timeGetTime() - v82);

			g_scriptEventMgr->CScriptEventMgr::Process();
			g_ProcessTimeList[2] = max(g_ProcessTimeList[2], timeGetTime() - v82);

			g_characterMgr->CCharacterMgr::ProcessAllCharacter();
			g_ProcessTimeList[3] = max(g_ProcessTimeList[3], timeGetTime() - v82);

			g_iSvrIO->CISvrIO::OnProcess();
			g_ProcessTimeList[4] = max(g_ProcessTimeList[4], timeGetTime() - v82);

			g_hSvrIO->CSvrIO::OnProcess();
			g_ProcessTimeList[5] = max(g_ProcessTimeList[5], timeGetTime() - v82);

			g_AuctionCtrl->CAuctionCtrl::Process();
			g_ProcessTimeList[6] = max(g_ProcessTimeList[6], timeGetTime() - v82);

			NAsyncDBMgr::GetObj()->NAsyncDBMgr::Process();

			CInstantMapMgr::GetObj()->CInstantMapMgr::Process();

			unsigned int v89 = timeGetTime() - v82;
			OutputStat(v89);

			unsigned int v88 = max(1, v89);
			g_loopCountPerSec = 1000 / v88;

			if( v89 < 20 )
				Sleep(20 - v89);

			g_MaxProcessTime = max(g_MaxProcessTime, v89);
			g_ProcessTime = v89;
		}
	}
	// core loop end

	NAsyncDBMgr::GetObj()->NAsyncDBMgr::Stop();
	NAsyncDBMgr::DestoryInstance();
	NSystemMgr::DestroyInstance();
	CInstantMapMgr::GetObj()->CInstantMapMgr::Stop();
	CMemorialDungeonMgr::DestroyInstance();
	CMapTypePropertyMgr::DestroyInstance();
	CInstantMapMgr::DestroyInstance();
	N2SystemMgr::DestroyInstance();
	CFontShopMgr::DestroyInstance();
	CMercenaryDBV2::DestroyInstance();
	CMercenarySkillMgr::DestroyInstance();
	CMercenaryConfiguration::DestroyInstance();
	g_questEventMgr->CQuestEventMgr::Finalize();
	cleanup();
	if( g_isGameGuardOn == 1 )
		CleanupGameguardAuth();
	if( wTimerRes )
		timeEndPeriod(wTimerRes);
	CCheckUseItemList::DestroyInstance();
	CGVar::DestroyInstance();
	CMyMiniDumpUnhandledExceptionHandler::DestroyInstance();

	return 0;
};
