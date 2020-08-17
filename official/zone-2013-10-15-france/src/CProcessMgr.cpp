#include "CAuctionCtrl.h"
#include "CFontShopMgr.h"
#include "CharacterMgr.h"
#include "CProcessMgr.h"
#include "CStaticNPCAIDGenerator.h"
#include "CThreadAffinityMgr.h"
#include "GVar.h"
#include "MapResMgr.h"
#include "MapTypePropertyMgr.h"
#include "MercenaryDBV2.h"
#include "NNetworkMgr.h"
#include "NpcMobRecycleMgr.h"
#include "Path.h"
#include "QuestArlimi.h"
#include "QuestEventMgr.h"
#include "ScriptEventMgr.h"
#include "SSIMgr.h"
#include "ZGuildInfoDB.h"
#include "ZGuildMgr.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "ZSAcceptHandler.h"
#include "ZSAcceptThread.h"
#include "AsyncDBWork/NAsyncDBMgr.h"
#include "Client/C2ClientMgr.h"
#include "Instant map/InstantMapMgr.h"
#include "LuaMonsterAI/NLuaMonsterAIMgr.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "NpcServer/NpcSvr.h"
#include "shared/CMapInfoMgr.h"
#include "shared/NSystem/NIPAddr.h"
#include "shared/N2System/N2SystemMgr.h"
#include "shared/N3System/N3MessageMgr.h"
#include "shared/NOutputTextMgr.h"
#include "shared/ServerInfo.h"
#include "shared/shared.h"


/// singleton instance
CProcessMgr*& CProcessMgr::m_cpSelf = VTOR<CProcessMgr*>(DetourFindFunction(EXEPATH(), "CProcessMgr::m_cpSelf"));


/// globals
CNpcSvr& g_npcSvr = VTOR<CNpcSvr>(DetourFindFunction(EXEPATH(), "g_npcSvr"));
CNewLogRecoder& g_logRecorder = VTOR<CNewLogRecoder>(DetourFindFunction(EXEPATH(), "g_logRecorder"));
CSpecialItemMgr& g_specialItmMgr = VTOR<CSpecialItemMgr>(DetourFindFunction(EXEPATH(), "g_specialItmMgr"));
CCharMTInfo& g_charMTInfo = VTOR<CCharMTInfo>(DetourFindFunction(EXEPATH(), "g_charMTInfo"));
CSkillTypeInfoMgr& g_skillTypeInfoMgr = VTOR<CSkillTypeInfoMgr>(DetourFindFunction(EXEPATH(), "g_skillTypeInfoMgr"));
CUserBlockMgr& g_UserBlockMgr = VTOR<CUserBlockMgr>(DetourFindFunction(EXEPATH(), "g_UserBlockMgr"));
CMakingLog& g_makingLog = VTOR<CMakingLog>(DetourFindFunction(EXEPATH(), "g_makingLog"));
CRefiningLog& g_refiningLog = VTOR<CRefiningLog>(DetourFindFunction(EXEPATH(), "g_refiningLog"));
CSkillLog& g_skillLog = VTOR<CSkillLog>(DetourFindFunction(EXEPATH(), "g_skillLog"));
CStatusLog& g_statusLog = VTOR<CStatusLog>(DetourFindFunction(EXEPATH(), "g_statusLog"));
CCompositionLog& g_compositionLog = VTOR<CCompositionLog>(DetourFindFunction(EXEPATH(), "g_compositionLog"));
CPresentLog& g_presentLog = VTOR<CPresentLog>(DetourFindFunction(EXEPATH(), "g_presentLog"));
CHomunLog& g_homunLog = VTOR<CHomunLog>(DetourFindFunction(EXEPATH(), "g_homunLog"));
CGMWhisperLog& g_gmWhisperLog = VTOR<CGMWhisperLog>(DetourFindFunction(EXEPATH(), "g_gmWhisperLog"));
double& g_ProcessTime = VTOR<double>(DetourFindFunction(EXEPATH(), "g_ProcessTime"));
double& g_MaxProcessTime = VTOR<double>(DetourFindFunction(EXEPATH(), "g_MaxProcessTime"));


CProcessMgr::CProcessMgr()
: N3Thread("ProcessMgr"), N3Inter(), N3Object(),
  m_bReqExit(false), m_MessageQueue(), m_bOK(false)
{
	N3MessageMgr::GetObj()->N3MessageMgr::Insert(this->N3Object::GetMyID(), this);
	m_bOK = true;
}


CProcessMgr::~CProcessMgr()
{
	N3MessageMgr::GetObj()->N3MessageMgr::Remove(this->N3Object::GetMyID(), this);
}


namespace {
////////////////////////////////////////


std::tr1::tuple<bool,std::string,std::string> ZsvrStartup6st()
{
	if( !g_questEventMgr.CQuestEventMgr::Initialize() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Initialize()", "g_questEventMgr");
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("g_questEventMgr.Initialize()...ok");

	if( !g_questArlimi.CQuestArlimi::Initialize() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Initialize()", "g_questArlimi");
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("g_questArlimi.Initialize()...ok");

	return std::tr1::tuple<bool,std::string,std::string>(true, "", "");
}


void ZsvrCleanup6st()
{
	g_questArlimi.CQuestArlimi::Filnalize();
	g_questEventMgr.CQuestEventMgr::Filnalize();
}


std::tr1::tuple<bool,std::string,std::string> ZsvrStartupLastFirst()
{
	if( !CZSAcceptThread::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CZSAcceptThread");

	std::pair<bool,std::string> ret = CZSAcceptThread::GetObj()->CZSAcceptThread::Start(g_serverInfo.CServerInfo::GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS), g_serverInfo.CServerInfo::GetLocalPort(), &g_zsAcceptHandler);
	if( !ret.first )
		return std::tr1::tuple<bool,std::string,std::string>(false, ret.second.c_str(), "CZSAcceptThread");

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("client accept thread start (%s:%d)", NIPAddapter(NIPAddr(g_serverInfo.CServerInfo::GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS))), g_serverInfo.CServerInfo::GetLocalPort());
	return std::tr1::tuple<bool,std::string,std::string>(true, "", "");
}


void ZsvrCleanupLastFirst()
{
	if( CZSAcceptThread::GetObj() != NULL )
	{
		CZSAcceptThread::GetObj()->CZSAcceptThread::Stop();
		CZSAcceptThread::DestroyInstance();
	}
}


std::tr1::tuple<bool,std::string,std::string> StartupNpcFirstEvent()
{
	DWORD RunScriptFirstEventStatTM = timeGetTime();
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("run script first event...start");

	while( !g_npcSvr.CNpcSvr::ClearFirstEvent() )
	{
		Sleep(1);
		g_npcSvr.CNpcSvr::Process();
	}

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("run script first event...end");
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("run script first event %.2f second", (timeGetTime() - RunScriptFirstEventStatTM) / 1000.0);

	return std::tr1::tuple<bool,std::string,std::string>(true, "", "");
}


std::tr1::tuple<bool,std::string,std::string> ZsvrStartup5st()
{
	DWORD RunScriptFirstEventStatTM = timeGetTime();
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("run script first event for cashtradenpc...start");

	while( !g_npcSvr.CNpcSvr::ClearFirstEvent() )
	{
		Sleep(1);
		g_npcSvr.CNpcSvr::Process();
	}

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("run script first event for cashtradenpc...end");
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("run script first event for cashtradenpc %.2f second", (timeGetTime() - RunScriptFirstEventStatTM) / 1000.0);

	return std::tr1::tuple<bool,std::string,std::string>(true, "", "");
}


std::tr1::tuple<bool,std::string,std::string> ZsvrStartup4st()
{
	if( !N2SystemMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "N2SystemMgr");

	if( !CInstantMapMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CInstantMapMgr");

	if( !CMemorialDungeonMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CMemorialDungeonMgr");

	if( !CInstantMapMgr::GetObj()->CInstantMapMgr::Start() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Start()", "InstanceCInstantMapMgr");

	if( !CFontShopMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CFontShopMgr");

	int MaxCharacterCount = CGVar::GetObj()->CGVar::GetMaxCharacterCount();
	g_zsAcceptHandler.CZSAcceptHandler::Init(MaxCharacterCount);

	if( !NNetworkMgr::GetObj()->NNetworkMgr::Start() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Start()", "InstanceNNetworkMgr");

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("network manager start");

	if( !C2ClientMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CClientMgr");

	return std::tr1::tuple<bool,std::string,std::string>(true, "", "");
}


void ZsvrCleanup4st()
{
	C2ClientMgr::DestroyInstance();
	NNetworkMgr::GetObj()->NNetworkMgr::Stop();
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("network manager stop");
	CFontShopMgr::DestroyInstance();
	CInstantMapMgr::GetObj()->CInstantMapMgr::Stop();
	CMemorialDungeonMgr::DestroyInstance();
	CInstantMapMgr::DestoryInstance();
	N2SystemMgr::DestoryInstance();
}


hook_func<std::tr1::tuple<bool,std::string,std::string>* (__cdecl *)()> _ZsvrStartup3st(EXEPATH(), "`anonymous namespace'::ZsvrStartup3st");
std::tr1::tuple<bool,std::string,std::string> ZsvrStartup3st()
{
	std::tr1::tuple<bool,std::string,std::string> result;
	void* hookptr = _ZsvrStartup3st;
	__asm lea ecx, result
	__asm call hookptr
	return result; //TODO
/*
	if( !g_BuyingStoreItemList.CBuyingStoreItemList::OpenFileBuyingStoreItemList() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "OpenFileBuyingStoreItemList()", "g_BuyingStoreItemList()");

	if( !g_skillTypeInfoMgr.CSkillTypeInfoMgr::InitSkillScript() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "InitSkillScript()", "g_skillTypeInfoMgr");

	if( !g_itemReuseLimit.CItemReuseLimit::Init() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Init()", "g_itemReuseLimit");

	const char* PASS = GetCharDBPwd();

	if( !CMercenaryDBV2::CreateInstance(CHARACTER_DSN_FILE, PASS, CODBCV2Connector::FILE_DSN_CONNECT_TYPE) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CMercenaryDBV2");

	if( !CMercenarySkillMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CMercenarySkillMgr");

	if( !CMercenaryConfiguration::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CMercenaryConfiguration");

	if( !NSystemMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "NSystemMgr");

	std::string characterDBconnectionStr = std::string() + "FILEDSN=.\\" + CHARACTER_DSN_FILE + ";PWD=" + PASS + ";";

	if( !NAsyncDBMgr::CreateInstance(characterDBconnectionStr) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "NAsyncDBMgr");

	if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::Start() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Start()", "InstanceNAsyncDBMgr");

	return std::tr1::tuple<bool,std::string,std::string>(true, "", "");
*/
}


hook_func<void (__cdecl *)()> _ZsvrCleanup3st(EXEPATH(), "`anonymous namespace'::ZsvrCleanup3st");
void ZsvrCleanup3st()
{
	return _ZsvrCleanup3st(); //TODO
/*
	NAsyncDBMgr::GetObj()->NAsyncDBMgr::Stop();
	NAsyncDBMgr::DestoryInstance();
	NSystemMgr::DestoryInstance();
	CMercenaryConfiguration::DestroyInstance();
	CMercenarySkillMgr::DestoryInstance();
	CMercenaryDBV2::DestoryInstance();
*/
}


hook_func<std::tr1::tuple<bool,std::string,std::string>* (__cdecl *)()> _ZsvrStartup2st(EXEPATH(), "`anonymous namespace'::ZsvrStartup2st");
std::tr1::tuple<bool,std::string,std::string> ZsvrStartup2st()
{
	std::tr1::tuple<bool,std::string,std::string> result;
	void* hookptr = _ZsvrStartup2st;
	__asm lea edi, result
	__asm call hookptr
	return result; //TODO
/*
	if( !CStaticNPCAIDGenerator::CreateInstance(NPC_MINIMUM_AID, NPC_MAXIMUM_AID) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CStaticNPCAIDGenerator");

	CNpcEventLog::CreateInstance();

	if( !CDisconnectLog::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CDisconnectLog");

	if( !CZoneUniqueIDGenerator::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CZoneUniqueIDGenerator");

	if( !CZoneSkillGroupUniqueIDGenerator::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CZoneSkillGroupUniqueIDGenerator");

	if( !NEO_PACKAGEITEM::CNeoPackageItem::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "NEO_PACKAGEITEM::CNeoPackageItem");

	if( !NEO_PACKAGEITEM::CNeoPackageItem::IsExistLuaFile("PackageItem.lua") )
	{
		if( !CCreatePackageScript::CreateInstance() )
			return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CCreatePackageScript");

		if( !CCreatePackageScript::GetObj()->CCreatePackageScript::Init() )
			return std::tr1::tuple<bool,std::string,std::string>(false, "Init()", "CCreatePackageScript");

		if( !CItemPackageScript::CreateInstance() )
			return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CItemPackageScript");

		if( !CItemPackageScript::GetObj()->CItemPackageScript::Init() )
			return std::tr1::tuple<bool,std::string,std::string>(false, "Init()", "CItemPackageScript");

		if( !CCreatePackageScript::GetObj()->CCreatePackageScript::Convert_NeoPakcageItem() )
			return std::tr1::tuple<bool,std::string,std::string>(false, "Convert_NeoPakcageItem()", "InstanceCCreatePackageScript");

		if( !CItemPackageScript::GetObj()->CItemPackageScript::Convert_NeoPakcageItem() )
			return std::tr1::tuple<bool,std::string,std::string>(false, "Convert_NeoPakcageItem()", "InstanceCItemPackageScript");

		if( !NEO_PACKAGEITEM::CNeoPackageItem::GetObj()->NEO_PACKAGEITEM::CNeoPackageItem::MakeLuaFile2() )
			return std::tr1::tuple<bool,std::string,std::string>(false, "MakeLuaFile()", "InstanceCNeoPackageItem");

		NEO_PACKAGEITEM::CNeoPackageItem::GetObj()->NEO_PACKAGEITEM::CNeoPackageItem::PackageListClear();
		CCreatePackageScript::DestroyInstance();
		CItemPackageScript::DestroyInstance();
	}

	NEO_PACKAGEITEM::RESULT_VALUES initNeoPackageItemRet = NEO_PACKAGEITEM::CNeoPackageItem::GetObj()->NEO_PACKAGEITEM::CNeoPackageItem::Init();
	if( initNeoPackageItemRet != NEO_PACKAGEITEM::REULST_SUCCESS )
	{
		if( initNeoPackageItemRet == NEO_PACKAGEITEM::RESULT_NULL_PTR )
			return std::tr1::tuple<bool,std::string,std::string>(false, "Init()  Null_Pointer Error!!", "NEO_PACKAGEITEM::InstanceCNeoPackageItem()");
		if( initNeoPackageItemRet == NEO_PACKAGEITEM::RESULT_LUAFILE_LOADING_FAILED )
			return std::tr1::tuple<bool,std::string,std::string>(false, "Init()  Check ! Lua File(packageitem.lua) loading error", "NEO_PACKAGEITEM::InstanceCNeoPackageItem()");
		if( initNeoPackageItemRet == NEO_PACKAGEITEM::RESULT_RANDOM_INT_MAX_OVER )
			return std::tr1::tuple<bool,std::string,std::string>(false, "Init()  Check ! Lua File(packageitem.lua) total random values > MAX_INT ] , error package info -> CriticalError.txt", "NEO_PACKAGEITEM::InstanceCNeoPackageItem()");
	}

	if( !CLevelPenaltyMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance", "CLevelPenaltyMgr");

	if( !CFixedSKCastingApplyObjMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CFixedSKCastingApplyObjMgr");

	if( !CUseItemBlockWhenSitdownMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CUseItemBlockWhenSitdownMgr");

	if( !CNpcMobRecycleMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CNpcMobRecycleMgr");

	if( !g_isNpcSkip && !g_npcSvr.CNpcSvr::Start() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Error Npc Server Start Fail 2", "g_npcSvr.Start()");

	if( !NLuaMonsterAIMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "NLuaMonsterAIMgr");

	std::pair<bool,std::string> initRet = NLuaMonsterAIMgr::GetObj()->NLuaMonsterAIMgr::Init();
	if( !initRet.first )
		return std::tr1::tuple<bool,std::string,std::string>(false, initRet.second, "InstanceNLuaMonsterAIMgr()->Init()");

	if( !CChangeMaterialMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CChangeMaterialMgr");

	if( !CGenetic3rd2SkillDataMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CGenetic3rd2SkillDataMgr");

	if( !CObjectRecycleMgr<CNpcElemental>::CreateInstance(50) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CObjectRecycleMgr<CNpcElemental>");

	int LogonPermitObjectMaxCnt = GetPrivateProfileIntA("ASYNC DATABASE WORK", "max num of logonpermit object recycle mgr", 100, g_infFile);
	if( LogonPermitObjectMaxCnt < 100 )
		LogonPermitObjectMaxCnt = 100;

	if( !CObjectRecycleMgr<CLogonPermitADBWork>::CreateInstance(LogonPermitObjectMaxCnt) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CObjectRecycleMgr<CLogonPermitADBWork>");

	int SaveAllObjectMaxCnt = GetPrivateProfileIntA("ASYNC DATABASE WORK", "max num of saveall object recycle mgr", 200, g_infFile);
	if( SaveAllObjectMaxCnt < 200 )
		SaveAllObjectMaxCnt = 200;

	if( !CObjectRecycleMgr<CSaveAllADBWork>::CreateInstance(SaveAllObjectMaxCnt) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CObjectRecycleMgr<CSaveAllADBWork>");

	int SaveQuestEventObjectMaxCnt = GetPrivateProfileIntA("ASYNC DATABASE WORK", "max num of savequestevent object recycle mgr", 100, g_infFile);
	if( SaveQuestEventObjectMaxCnt < 100 )
		SaveQuestEventObjectMaxCnt = 100;

	if( !CObjectRecycleMgr<CSaveQuestEventDBWork>::CreateInstance(SaveQuestEventObjectMaxCnt) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CObjectRecycleMgr<CSaveQuestEventDBWork>");

	int LoadStoreObjectMaxCnt = GetPrivateProfileIntA("ASYNC DATABASE WORK", "max num of loadstore object recycle mgr", 100, g_infFile);
	if( LoadStoreObjectMaxCnt < 100 )
		LoadStoreObjectMaxCnt = 100;

	if( !CObjectRecycleMgr<CLoadStoreADBWork>::CreateInstance(LoadStoreObjectMaxCnt) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CObjectRecycleMgr<CLoadStoreADBWork>");

	int SaveStoreObjectMaxCnt = GetPrivateProfileIntA("ASYNC DATABASE WORK", "max num of savestore object recycle mgr", 100, g_infFile);
	if( SaveStoreObjectMaxCnt < 100 )
		SaveStoreObjectMaxCnt = 100;

	if( !CObjectRecycleMgr<CSaveStoreADBWork>::CreateInstance(SaveStoreObjectMaxCnt) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CObjectRecycleMgr<CSaveStoreADBWork>");

	int LoadCartObjectMaxCnt = GetPrivateProfileIntA("ASYNC DATABASE WORK", "max num of loadcart object recycle mgr", 100, g_infFile);
	if( LoadCartObjectMaxCnt < 100 )
		LoadCartObjectMaxCnt = 100;

	if( !CObjectRecycleMgr<CLoadCartADBWork>::CreateInstance(LoadCartObjectMaxCnt) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CObjectRecycleMgr<CLoadCartADBWork>");

	int SaveCartObjectMaxCnt = GetPrivateProfileIntA("ASYNC DATABASE WORK", "max num of savecart object recycle mgr", 100, g_infFile);
	if( SaveCartObjectMaxCnt < 100 )
		SaveCartObjectMaxCnt = 100;

	if( !CObjectRecycleMgr<CSaveCartADBWork>::CreateInstance(SaveCartObjectMaxCnt) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CObjectRecycleMgr<CSaveCartADBWork>");

	int SaveBodyItemObjectMaxCnt = GetPrivateProfileIntA("ASYNC DATABASE WORK", "max num of savebodyitem object recycle mgr", 100, g_infFile);
	if( SaveBodyItemObjectMaxCnt < 100 )
		SaveBodyItemObjectMaxCnt = 100;

	if( !CObjectRecycleMgr<CSaveBodyItemADBWork>::CreateInstance(SaveBodyItemObjectMaxCnt) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CObjectRecycleMgr<CSaveBodyItemADBWork>");

	if( !CGeneticSlingItemMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CGeneticSlingItemMgr");

	if( !CBroadCastingSpecialItemListMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CBroadCastingSpecialItemListMgr");

	if( !CSSIMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CSSIMgr");

	if( !CScriptMobTombInfo::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CScriptMobTombInfo");

	if( !CScriptMobTombInfo::GetObj()->CScriptMobTombInfo::LoadLuaFIle() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "LoadLuaFIle()", "InstanceCScriptMobTombInfo");

	if( !CMonsterTransformMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CMonsterTransformMgr");

	if( !CMonsterTransformMgr::GetObj()->CMonsterTransformMgr::LoadLuaFile() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "LoadLuaFile()", "InstanceCMonsterTransformMgr()");

	return std::tr1::tuple<bool,std::string,std::string>(true, "", "");
*/
}


hook_func<void (__cdecl *)()> _ZsvrCleanup2st(EXEPATH(), "`anonymous namespace'::ZsvrCleanup2st");
void ZsvrCleanup2st()
{
	return _ZsvrCleanup2st(); //TODO
/*
	shutdownlog();
	CMonsterTransformMgr::DestroyInstance();
	NEO_PACKAGEITEM::CNeoPackageItem::DestroyInstance();
	CScriptMobTombInfo::DestroyInstance();
	CSSIMgr::DestoryInstance();
	CBroadCastingSpecialItemListMgr::DestroyInstance();
	CGeneticSlingItemMgr::DestroyInstance();
	CObjectRecycleMgr<CSaveBodyItemADBWork>::DestoryInstance();
	CObjectRecycleMgr<CSaveCartADBWork>::DestoryInstance();
	CObjectRecycleMgr<CLoadCartADBWork>::DestoryInstance();
	CObjectRecycleMgr<CSaveStoreADBWork>::DestoryInstance();
	CObjectRecycleMgr<CLoadStoreADBWork>::DestoryInstance();
	CObjectRecycleMgr<CSaveQuestEventDBWork>::DestoryInstance();
	CObjectRecycleMgr<CSaveAllADBWork>::DestoryInstance();
	CObjectRecycleMgr<CLogonPermitADBWork>::DestoryInstance();
	CGenetic3rd2SkillDataMgr::DestroyInstance();
	CChangeMaterialMgr::DestroyInstance();
	CObjectRecycleMgr<CNpcElemental>::DestoryInstance();
	NLuaMonsterAIMgr::DestroyInstance();
	CUseItemBlockWhenSitdownMgr::DestroyInstance();
	CFixedSKCastingApplyObjMgr::DestroyInstance();
	CLevelPenaltyMgr::DestroyInstance();
	CZoneSkillGroupUniqueIDGenerator::DestroyInstance();
	CZoneUniqueIDGenerator::DestroyInstance();
	CNpcMobRecycleMgr::DestroyInstance();
	CDisconnectLog::DestroyInstance();
	CNpcEventLog::DestroyInstance();
	CStaticNPCAIDGenerator::DestroyInsance();
*/
}


hook_func<std::tr1::tuple<bool,std::string,std::string>* (__cdecl *)()> _ZsvrStartup1st(EXEPATH(), "`anonymous namespace'::ZsvrStartup1st");
std::tr1::tuple<bool,std::string,std::string> ZsvrStartup1st()
{
	std::tr1::tuple<bool,std::string,std::string> result;
	void* hookptr = _ZsvrStartup1st;
	__asm lea ecx, result
	__asm call hookptr
	return result; //TODO
/*
	if( !CUIDGenerator::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CUIDGenerator");

	if( !CUIDGenerator::GetObj()->CUIDGenerator::Init() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Init()", "CUIDGenerator");

	if( !CCheckUseItemList::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CCheckUseItemList");

	g_statpointPerLevel.CStatpointPerLevel::Init();
	g_statpointPerLevel.CStatpointPerLevel::LoadStatpointPerLevel();

	g_fsmMgr.CFSMMgr::Init();

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("item information loading...");
	g_itpMgr.CITPMgr::Init(SCRIPT_DSN_FILE);
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("item information loading...complete");

	g_metalItemList.CItemList::LoadFromFile(g_pathData.CPathData::SetFileName("metalitemlist.scp"), 20020627);

	g_weaponItemList.CItemList::LoadFromFile(g_pathData.CPathData::SetFileName("weaponitemList.scp"), 20020627);

	g_potionItemList.CItemList::LoadFromFile(g_pathData.CPathData::SetFileName("potionitemList.scp"), 20030515);

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("monster information loading...");
	g_monParameter.CMonParameterMgr::Init(SCRIPT_DSN_FILE);
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("monster information loading...complete");

	g_expParameter.CExpParameter::Init(SCRIPT_DSN_FILE);

	g_maxHpSp.CMaxHpSp::Init();
	g_maxHpSp.CMaxHpSp::LoadHp();
	g_maxHpSp.CMaxHpSp::LoadSp();
	g_maxHpSp.CMaxHpSp::LoadMaxHPSP();

	const char* PASS = GetCharDBPwd();

	g_AgitDB.CODBC::Init(CHARACTER_DSN_FILE, PASS);

	g_mvpInfo.CMVPInfo::Init(SCRIPT_DSN_FILE, g_GlobaldbPWD);

	g_charMTInfo.CCharMTInfo::Init();

	if( g_characterServerPort != 0 )
	{
		int HSID = g_serverInfo.CServerInfo::GetDestinationSID(TARGET_ONE_SID);
		g_serverInfo.CServerInfo::SetServerPort(HSID, g_characterServerPort);
	}

	g_ZGuildDB.CGuildDB::Init(CHARACTER_DSN_FILE, PASS);

	int MaxGuild = GetPrivateProfileIntA("ETC", "MAXGUILD", 0, g_infFile);
	g_ZGuildMgr.CZGuildMgr::Init(MaxGuild);

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("guild max number = %d", g_ZGuildMgr.CZGuildMgr::GetFreeSize());

	if( !CCharacterNameDictionary::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CCharacterNameDictionary");

	char encryptDBPWD[128] = "unknown";
	char DBPWD[256] = "unknown";
	GetPrivateProfileStringA("ETC", "DBPWD_CASHITEMSHOP", "unknown", encryptDBPWD, countof(encryptDBPWD), g_infFile);
	Decrypt(encryptDBPWD, (unsigned char*)DBPWD);
	CCashItemShopDB::GetObj()->CODBCV2::Init(CASHSHOT_DSN_FILE, DBPWD, CODBCV2Connector::FILE_DSN_CONNECT_TYPE, false);

	if( !CSimpleCashShopScript::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CSimpleCashShopScript");

	if( !CCashItemShopScript::GetObj()->CCashItemShopScript::Init() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Init()", "CCashItemShopScript");

	g_importantItem.CImportantItem::LoadImportantItem();

	if( !CMapInfoMgr::CreateInstance(std::string() + "FILEDSN=.\\" + IPINFO_DSN_FILE + ";PWD=" + g_dbPWD) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CMapInfoMgr");

	g_pvpScoreDB.CODBC::Init(CHARACTER_DSN_FILE, PASS);

	g_charInfoDB.CODBC::Init(CHARACTER_DSN_FILE, PASS);

	g_petDB.CODBC::Init(CHARACTER_DSN_FILE, PASS);

	g_merceDB.CODBC::Init(CHARACTER_DSN_FILE, PASS);

	g_skillTypeInfoMgr.CSkillTypeInfoMgr::Init();

	g_pcSkillDB.CODBC::Init(CHARACTER_DSN_FILE, PASS);

	g_makerRankDB.CODBC::Init(CHARACTER_DSN_FILE, PASS);

	if( IsSetting(SETTING_KILLER_SYSTEM) )
		g_PKInfoMgr.CODBC::Init(CHARACTER_DSN_FILE, PASS);

	g_StatusPlusnfoByJLV.CStatusPlusInfoByJLV::Init();

	if( !EStateTypeInfoMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "EStateTypeInfoMgr");

	if( !CMapTypePropertyMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CMapTypePropertyMgr");

	std::pair<bool,std::string> mresinitRet = g_mapResMgr.CMapResMgr::Init(g_serverInfo.CServerInfo::GetLocalServerID());
	if( !mresinitRet.first )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Init()", mresinitRet.second);

	if( !CCharacterMgr::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CCharacterMgr");

	int MaxCharacterCount = CGVar::GetObj()->CGVar::GetMaxCharacterCount();
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("characterMgr Init(%d)", MaxCharacterCount);
	CCharacterMgr::GetObj()->CCharacterMgr::Init(MaxCharacterCount);

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("roomMgr Init(%d)", 5000);
	g_roomMgr.CRoomMgr::Init(5000);

	g_summonItemTable.CMatchTable::LoadFromFile(g_pathData.CPathData::SetFileName("ItemSummonList.txt"));

	g_summonMonsterTable.CSummonMonsterTable::LoadFromFile(g_pathData.CPathData::SetFileName("MonsterSummonList.txt"));

	g_summonMobBySkillTable.CMatchTable::LoadFromFile(g_pathData.CPathData::SetFileName("ClassChange.txt"));

	if( !g_petDefaultValue.CPetDefaultValue::Load(g_pathData.CPathData::SetFileName("PetTable.txt")) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Check... PetTable.txt", "g_petDefaultValue");

	if( !g_npcAddSkillInfo.CNPCAddSkillInfo::Load(g_pathData.CPathData::SetFileName("NpcAddSkillInfo.txt")) )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Check NpcAddSkillInfo.txt", "g_npcAddSkillInfo");

	if( !ScriptCompile() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "error", "ScriptCompile");

	if( !EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::InitScript() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "InitScript()", "InstanceEStateTypeInfoMgr");

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("zone script init");
	g_zoneScript.CZoneScript::Init();

	if( !CNewPoisonItemInfo::CreateInstance() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "CreateInstance()", "CNewPoisonItemInfo");

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("item special init...");

	if( !g_specialItmMgr.CSpecialItemMgr::Init() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "Init()", "g_specialItmMgr");

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("item special init...complete");

	if( g_isMobileEventOn )
	{
		if( !g_MEventDB.CODBCV2::Init(GLOBALINFO_DSN_FILE, g_GlobaldbPWD, FILE_DSN_CONNECT_TYPE, true) )
			return std::tr1::tuple<bool,std::string,std::string>(false, "mobile event database init or connect error", "g_MEventDB");
	}

	g_PEventDB.CODBC::Init(GLOBALINFO_DSN_FILE, g_GlobaldbPWD);

	g_globalVarDB.CODBC::Init(CHARACTER_DSN_FILE, PASS);

	if( !g_jobCodeForItem.CJobCodeForItem::Init() )
		return std::tr1::tuple<bool,std::string,std::string>(false, "JobCodeForItem.scp error", "g_jobCodeForItem");

	CGameGuardLog::CreateInstance();

	if( g_isGameGuardOn == TRUE )
	{
		int ggRet = InitGameguardAuth(".", 50);
		if( ggRet != 0 )
		{
			NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("GameGuard ggauth.dll Load error : %d", ggRet);
			return std::tr1::tuple<bool,std::string,std::string>(false, "GameGuard ggauth.dll Load error", "InitGameguardAuth");
		}
	}

	if( g_storePasswordCheck == TRUE || g_cashShopPasswordCheck == TRUE )
	{
		if( !g_storePasswordDB.CODBC::Init(GLOBALINFO_DSN_FILE, g_GlobaldbPWD) )
			return std::tr1::tuple<bool,std::string,std::string>(false, "Init()", "g_storePasswordDB");
	}

	if( g_lottoCheck == TRUE )
	{
		if( !g_lottoDB.CODBC::Init(GLOBALINFO_DSN_FILE, g_GlobaldbPWD) )
			return std::tr1::tuple<bool,std::string,std::string>(false, "Init()", "g_lottoDB");
	}

	g_AuctionCtrl.CAuctionCtrl::Init(g_serverInfo.CServerInfo::GetLocalServerID(), CHARACTER_DSN_FILE, PASS);

	return std::tr1::tuple<bool,std::string,std::string>(true, "", "");
*/
}


hook_func<void (__cdecl *)()> _ZsvrCleanup1st(EXEPATH(), "`anonymous namespace'::ZsvrCleanup1st");
void ZsvrCleanup1st()
{
	return _ZsvrCleanup1st(); //TODO
/*
	CCharacterMgr::DestroyInstance();
	CGameGuardLog::DestroyInstance();
	if( g_isGameGuardOn == TRUE )
		CleanupGameguardAuth();
	CNewPoisonItemInfo::DestroyInstance();
	CMapTypePropertyMgr::DestroyInstance();
	EStateTypeInfoMgr::DestoryInstance();
	CMapInfoMgr::DestroyInstance();
	CSimpleCashShopScript::DestroyInstance();
	CCharacterNameDictionary::DestroyInstance();
	CCheckUseItemList::DestroyInstance();
	CUIDGenerator::DestroyInstance();
*/
}


hook_func<std::tr1::tuple<bool,std::string,std::string> (__cdecl *)()> _ZsvrStartupLog(EXEPATH(), "`anonymous namespace'::ZsvrStartupLog");
std::tr1::tuple<bool,std::string,std::string> ZsvrStartupLog()
{
	return _ZsvrStartupLog(); //TODO
/*
	g_logRecorder.CNewLogRecoder::BeginSaveToDatabase();
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("logRecoder start");

	g_itemLog.CPetLog::ConnectToDatabase(LOG_DSN_FILE);
	g_logRecorder.CNewLogRecoder::Add(&g_itemLog);

	g_UserBlockMgr.CUserBlockMgr::ConnectToDatabase(GLOBALINFO_DSN_FILE);
	g_logRecorder.CNewLogRecoder::Add(&g_UserBlockMgr);

	g_makingLog.CPetLog::ConnectToDatabase(LOG_DSN_FILE);
	g_logRecorder.CNewLogRecoder::Add(&g_makingLog);

	g_refiningLog.CPetLog::ConnectToDatabase(LOG_DSN_FILE);
	g_logRecorder.CNewLogRecoder::Add(&g_refiningLog);

	g_skillLog.CPetLog::ConnectToDatabase(LOG_DSN_FILE);
	g_logRecorder.CNewLogRecoder::Add(&g_skillLog);

	g_statusLog.CPetLog::ConnectToDatabase(LOG_DSN_FILE);
	g_logRecorder.CNewLogRecoder::Add(&g_statusLog);

	g_compositionLog.CCompositionLog::ConnectToDatabase(LOG_DSN_FILE);
	g_logRecorder.CNewLogRecoder::Add(&g_compositionLog);

	g_presentLog.CPetLog::ConnectToDatabase(LOG_DSN_FILE);
	g_logRecorder.CNewLogRecoder::Add(&g_presentLog);

	g_homunLog.CPetLog::ConnectToDatabase(LOG_DSN_FILE);
	g_logRecorder.CNewLogRecoder::Add(&g_homunLog);

	g_MercenaryLog.CPetLog::ConnectToDatabase(LOG_DSN_FILE);
	g_logRecorder.CNewLogRecoder::Add(&g_MercenaryLog);

	g_petLog.CPetLog::ConnectToDatabase(LOG_DSN_FILE);
	g_logRecorder.CNewLogRecoder::Add(&g_petLog);

	g_ChagneMaterialLog.CChangeMaterialLog::ConnectToDatabase(LOG_DSN_FILE);
	g_logRecorder.CNewLogRecoder::Add(&g_ChagneMaterialLog);

	return std::tr1::tuple<bool,std::string,std::string>(true, "", "");
*/
}


hook_func<void (__cdecl *)()> _ZsvrCleanupLog(EXEPATH(), "`anonymous namespace'::ZsvrCleanupLog");
void ZsvrCleanupLog()
{
	return _ZsvrCleanupLog(); //TODO
/*
	g_logRecorder.m_bReqExit = true;
*/
}


////////////////////////////////////////
}; // namespace


std::tr1::tuple<bool,std::string,std::string> CProcessMgr::Startup()
{
	std::tr1::tuple<bool,std::string,std::string> ret;

	ret = ZsvrStartup1st();
	if( !std::tr1::get<0>(ret) )
		return ret;
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZsvrStartup1st");

	ret = ZsvrStartup2st();
	if( !std::tr1::get<0>(ret) )
		return ret;
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZsvrStartup2st");

	ret = ZsvrStartup3st();
	if( !std::tr1::get<0>(ret) )
		return ret;
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZsvrStartup3st");

	ret = ZsvrStartup4st();
	if( !std::tr1::get<0>(ret) )
		return ret;
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZsvrStartup4st");

	ret = ZsvrStartupLog();
	if( !std::tr1::get<0>(ret) )
		return ret;
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZsvrStartupLog");

	ret = ZsvrStartup5st();
	if( !std::tr1::get<0>(ret) )
		return ret;
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZsvrStartup5st");

	ret = StartupNpcFirstEvent();
	if( !std::tr1::get<0>(ret) )
		return ret;
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("StartupNpcFirstEvent");

	ret = ZsvrStartup6st();
	if( !std::tr1::get<0>(ret) )
		return ret;
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZsvrStartup6st");

	ret = ZsvrStartupLastFirst();
	if( !std::tr1::get<0>(ret) )
		return ret;
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZsvrStartupLastFirst");

	return std::tr1::tuple<bool,std::string,std::string>(true, "", "");
}


void CProcessMgr::Cleanup()
{
	ZsvrCleanupLastFirst();
	ZsvrCleanup6st();
	ZsvrCleanupLog();
	ZsvrCleanup4st();
	ZsvrCleanup3st();
	ZsvrCleanup2st();
	ZsvrCleanup1st();
}


bool CProcessMgr::Start()
{
	if( this->N3Thread::Begin() != true )
		return false;

	unsigned long Mask = CThreadAffinityMgr::GetObj()->CThreadAffinityMgr::GetThreadAffinityMask();
	this->N3Thread::SetThreadAffinityMask(Mask);
	return true;
}


void CProcessMgr::Stop()
{
	this->N3Thread::End();
}


void CProcessMgr::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}


bool CProcessMgr::MessageProcess()
{
	for( int i = 1; i <= 100; ++i )
	{
		if( WaitForSingleObject(m_MessageQueue.N3MessageQueue::GetEventObj(), 0) == WAIT_OBJECT_0 )
		{
			N3MessageQueue::RETGET mRet = m_MessageQueue.N3MessageQueue::Get();
			if( std::tr1::get<0>(mRet) == true )
			{
				unsigned int Message = std::tr1::get<1>(mRet);
				switch( Message )
				{
				case N3MSGID(CProcessMgr,MSG_THREAD_QUIT):
				{
					return false;
				}
				break;
				case N3MSGID(CProcessMgr,MSG_ACCEPT):
				{
					SOCKET s = (SOCKET)std::tr1::get<2>(mRet);
					DWORD ip = (DWORD)std::tr1::get<3>(mRet);

					if( !g_zsAcceptHandler.CZSAcceptHandler::OnConnect(s, ip) )
						closesocket(s);
				}
				break;
				};
			}
		}
	}

	return true;
}


unsigned int CProcessMgr::ThreadFunction()
{
	srand(_getpid() + timeGetTime());

	std::tr1::tuple<bool,std::string,std::string> ret = this->CProcessMgr::Startup();
	if( !std::tr1::get<0>(ret) )
	{
		std::string message = std::tr1::get<1>(ret);
		std::string title = std::tr1::get<2>(ret);
		MessageBoxA(NULL, message.c_str(), title.c_str(), MB_OK);

		this->CProcessMgr::Cleanup();
		ExitProcess(EXIT_SUCCESS);
	}

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("Zone Server Start...");

	while( !m_bReqExit )
	{
		DWORD start_tick = timeGetTime();
		g_curTime = time(NULL);

		if( !this->CProcessMgr::MessageProcess() )
			break;

		g_mapResMgr.CMapResMgr::Process();
		g_npcSvr.CNpcSvr::Process();
		g_scriptEventMgr.CScriptEventMgr::Process();
		CCharacterMgr::GetObj()->CCharacterMgr::ProcessAllCharacter();
		C2ClientMgr::GetObj()->C2ClientMgr::Process();
		g_AuctionCtrl.CAuctionCtrl::Process();
		NAsyncDBMgr::GetObj()->NAsyncDBMgr::Process();
		CInstantMapMgr::GetObj()->CInstantMapMgr::Process();
		NLuaMonsterAIMgr::GetObj()->NLuaMonsterAIMgr::Process();
		CNpcMobRecycleMgr::GetObj()->CNpcMobRecycleMgr::Process();
		g_questArlimi.CQuestArlimi::Process();
		CSSIMgr::GetObj()->CSSIMgr::Proc();

		DWORD end_tick = timeGetTime();
		DWORD ProcessTime = end_tick - start_tick;

		g_loopCountPerSec = 1000 / max(1, ProcessTime);

		if( ProcessTime < 20 )
			Sleep(20 - ProcessTime);

		if( g_MaxProcessTime < ProcessTime )
			g_MaxProcessTime = ProcessTime;
		g_ProcessTime = ProcessTime;
	}

	this->CProcessMgr::Cleanup();
	return 0;
}


void CProcessMgr::PostThreadQuitMessage()
{
	m_bReqExit = true;
	m_MessageQueue.N3MessageQueue::Put(N3MSGID(CProcessMgr,MSG_THREAD_QUIT), 0, 0);
}


bool CProcessMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;
	
	m_cpSelf = new(std::nothrow) CProcessMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CProcessMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CProcessMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CProcessMgr* CProcessMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CProcessMgr::isOK() const
{
	return m_bOK;
}
