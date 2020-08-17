void Hex(unsigned int addr, int size, const char* from, const char* to)
{
	void* ptr = (void*)addr;
	DWORD oldprotect;

	VirtualProtect(ptr, size, PAGE_READWRITE, &oldprotect);
	assert(memcmp(ptr, from, size) == 0);
	memcpy(ptr, to, size);
	VirtualProtect(ptr, size, oldprotect, &oldprotect);
}


void Hook()
{
	extern void Test(void);
	Test();

	extern void Hook_Alloc(void* pfnNew, void* pfnDelete, void* pfnInit);
	Hook_Alloc(DetourFindFunction(EXEPATH(), "??2@YAPAXI@Z"), DetourFindFunction(EXEPATH(), "??3@YAXPAX@Z"), DetourFindFunction(EXEPATH(), "_cinit"));

	// atcommands
	HookDB::DB().Hook("CPCPacketHandler::OnChat", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnChat"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnChat"));
	HookDB::DB().Hook("CPCPacketHandler::OnChatParty", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnChatParty"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnChatParty"));
	HookDB::DB().Hook("CPCPacketHandler::OnGuildChat", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnGuildChat"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnGuildChat"));
	HookDB::DB().Hook("CPCPacketHandler::OnWhisper", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnWhisper"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnWhisper"));

	// mem usage reduction
	HookDB::DB().Hook("CCharacterMgr::Init", DetourFindFunction(EXEPATH(), "CCharacterMgr::Init"), DetourFindFunction(DLLPATH(), "CCharacterMgr::Init"));
	HookDB::DB().Hook("CZSAcceptHandler::Init", DetourFindFunction(EXEPATH(), "CZSAcceptHandler::Init"), DetourFindFunction(DLLPATH(), "CZSAcceptHandler::Init"));
	HookDB::DB().Hook("CPacketQueue::Init", DetourFindFunction(EXEPATH(), "CPacketQueue::Init"), DetourFindFunction(DLLPATH(), "CPacketQueue::Init"));
	HookDB::DB().Hook("CAuctionCtrl::Init", DetourFindFunction(EXEPATH(), "CAuctionCtrl::Init"), DetourFindFunction(DLLPATH(), "CAuctionCtrl::Init"));

	// fair party item share
	HookDB::DB().Hook("CPCItemInventoryMgr::OnPickUpItem", DetourFindFunction(EXEPATH(), "CPCItemInventoryMgr::OnPickUpItem"), DetourFindFunction(DLLPATH(), "CPCItemInventoryMgr::OnPickUpItem"));

	// autoloot
	HookDB::DB().Hook("CNPCStateUpdater::DropItem", DetourFindFunction(EXEPATH(), "CNPCStateUpdater::DropItem"), DetourFindFunction(DLLPATH(), "CNPCStateUpdater::DropItem"));

	// quicker minimap update
	HookDB::DB().Hook("CPC::isNotifyPosition", DetourFindFunction(EXEPATH(), "CPC::isNotifyPosition"), DetourFindFunction(DLLPATH(), "CPC::isNotifyPosition"));

	// don't kick players because of skill usage
	HookDB::DB().Hook("CCharacter::IsDirectPath", DetourFindFunction(EXEPATH(), "CCharacter::IsDirectPath"), DetourFindFunction(DLLPATH(), "CCharacter::IsDirectPath"));

	// always display party name | only process requests on same map
	HookDB::DB().Hook("CPCPacketHandler::OnReqName", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnReqName"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnReqName"));

	// cpu usage reduction by delaying npc/mob processing
	HookDB::DB().Hook("CCharacterMgr::ProcessAllCharacter", DetourFindFunction(EXEPATH(), "CCharacterMgr::ProcessAllCharacter"), DetourFindFunction(DLLPATH(), "CCharacterMgr::ProcessAllCharacter"));

	// obey DATA_PATH setting
	HookDB::DB().Hook("CMapTypePropertyMgr::Create", DetourFindFunction(EXEPATH(), "CMapTypePropertyMgr::Create"), DetourFindFunction(DLLPATH(), "CMapTypePropertyMgr::Create"));

	// obey NPC_DATA_PATH setting
	HookDB::DB().Hook("CScriptCompiler::InitDungenNpcScript", DetourFindFunction(EXEPATH(), "CScriptCompiler::InitDungenNpcScript"), DetourFindFunction(DLLPATH(), "CScriptCompiler::InitDungenNpcScript"));

	// dump with heap | fix stackdump code
	HookDB::DB().Hook("CMyMiniDumpUnhandledExceptionHandler::UnhandledExceptionHandler", DetourFindFunction(EXEPATH(), "CMyMiniDumpUnhandledExceptionHandler::UnhandledExceptionHandler"), DetourFindFunction(DLLPATH(), "CMyMiniDumpUnhandledExceptionHandler::UnhandledExceptionHandler"));

	// high-efficiency Mersenne Twister PRNG
	HookDB::DB().Hook("GetServerRandom",DetourFindFunction(EXEPATH(), "GetServerRandom"), DetourFindFunction(DLLPATH(), "GetServerRandom"));

	// prevent portal-casting and related exploits
	HookDB::DB().Hook("CPCPacketHandler::DispatchPacket", DetourFindFunction(EXEPATH(), "CPCPacketHandler::DispatchPacket"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::DispatchPacket"));

	// identified wedding rings
	HookDB::DB().Hook("CPC::OnMakeCouple", DetourFindFunction(EXEPATH(), "CPC::OnMakeCouple"), DetourFindFunction(DLLPATH(), "CPC::OnMakeCouple"));

	// remove 'savageox' guild creation backdoor
	HookDB::DB().Hook("CPCPacketHandler::OnReqMakeGuild", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnReqMakeGuild"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnReqMakeGuild"));

	// buffer overflow bugfix
	HookDB::DB().Hook("CPCPacketHandler::OnBattleFieldChat", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnBattleFieldChat"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnBattleFieldChat"));

	// buffer overflow bugfix
	HookDB::DB().Hook("CPCPacketHandler::OnMailSend", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnMailSend"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnMailSend"));

	// proper graceful socket shutdown
	HookDB::DB().Hook("CAsyncStream::Close", DetourFindFunction(EXEPATH(), "CAsyncStream::Close"), DetourFindFunction(DLLPATH(), "CAsyncStream::Close"));

	// close emptied shops serverside
	HookDB::DB().Hook("CPCItemInventoryMgr::PurchaseItemFromMCStore", DetourFindFunction(EXEPATH(), "CPCItemInventoryMgr::PurchaseItemFromMCStore"), DetourFindFunction(DLLPATH(), "CPCItemInventoryMgr::PurchaseItemFromMCStore"));

	// make sure shop is open before processing shop close request
	HookDB::DB().Hook("CPCPacketHandler::OnReqCloseMCStore", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnReqCloseMCStore"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnReqCloseMCStore"));

	// autotrade - detach session, skip sends, disconnect after everything sells
	HookDB::DB().Hook("CPCPacketHandler::OnClose", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnClose"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnClose"));
	HookDB::DB().Hook("CPC::Send", DetourFindFunction(EXEPATH(), "CPC::Send"), DetourFindFunction(DLLPATH(), "CPC::Send"));
	HookDB::DB().Hook("CPC::ForceSend", DetourFindFunction(EXEPATH(), "CPC::ForceSend"), DetourFindFunction(DLLPATH(), "CPC::ForceSend"));
	HookDB::DB().Hook("CPC::CancelMCStore", DetourFindFunction(EXEPATH(), "CPC::CancelMCStore"), DetourFindFunction(DLLPATH(), "CPC::CancelMCStore"));

	// don't abort npc parsing after encountering a kvm_npc on a nonexistent map
	HookDB::DB().Hook("CNpcEvent::FuncKVMNpc", DetourFindFunction(EXEPATH(), "CNpcEvent::FuncKVMNpc"), DetourFindFunction(DLLPATH(), "CNpcEvent::FuncKVMNpc"));

	// emperium damage cap
	HookDB::DB().Hook("?GetAttackFinalDamage@CPC@@AAEHPAVCCharacter@@HHHHHHGF@Z", DetourFindFunction(EXEPATH(), "?GetAttackFinalDamage@CPC@@AAEHPAVCCharacter@@HHHHHHGF@Z"), DetourFindFunction(DLLPATH(), "?GetAttackFinalDamage@CPC@@AAEHPAVCCharacter@@HHHHHHGF@Z"));
	HookDB::DB().Hook("CPCBattle::ModifyDamage_ATK", DetourFindFunction(EXEPATH(), "CPCBattle::ModifyDamage_ATK"), DetourFindFunction(DLLPATH(), "CPCBattle::ModifyDamage_ATK"));

	// always display the correct def bonus from refined equipment
	HookDB::DB().Hook("CPC::GetItemDef", DetourFindFunction(EXEPATH(), "CPC::GetItemDef"), DetourFindFunction(DLLPATH(), "CPC::GetItemDef"));

	// main chat
	HookDB::DB().Hook("CISvrIOPacketHandler::OnBroadCast", DetourFindFunction(EXEPATH(), "CISvrIOPacketHandler::OnBroadCast"), DetourFindFunction(DLLPATH(), "CISvrIOPacketHandler::OnBroadCast"));
	HookDB::DB().Hook("CPCPacketHandler::OnWhisper", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnWhisper"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnWhisper"));

	// only send guild notice once when entering zone
	HookDB::DB().Hook("CZGuildInfo::SendGuildNotice", DetourFindFunction(EXEPATH(), "CZGuildInfo::SendGuildNotice"), DetourFindFunction(DLLPATH(), "CZGuildInfo::SendGuildNotice"));

	// proper AID packet for PACKETVER >= 20070521
	HookDB::DB().Hook("CHSvrIOPacketHandler::OnLogonPermit", DetourFindFunction(EXEPATH(), "CHSvrIOPacketHandler::OnLogonPermit"), DetourFindFunction(DLLPATH(), "CHSvrIOPacketHandler::OnLogonPermit"));

	// change Gospel perma-voke to 60 seconds duration
	HookDB::DB().Hook("CPC::SetEffectByGospel", DetourFindFunction(EXEPATH(), "CPC::SetEffectByGospel"), DetourFindFunction(DLLPATH(), "CPC::SetEffectByGospel"));

	// don't kick players because of binding hotkeys above the limit (kRO renewal client support)
	HookDB::DB().Hook("CPCPacketHandler::OnShortcutKey_Change", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnShortcutKey_Change"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnShortcutKey_Change"));

	// validate emblem bitmap data
	HookDB::DB().Hook("CPCPacketHandler::OnRegisterGuildEmblemImg", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnRegisterGuildEmblemImg"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnRegisterGuildEmblemImg"));

	/// @patch initialize CCompiler members - r2543
	HookDB::DB().Hook("CCompiler::CCompiler", DetourFindFunction(EXEPATH(), "CCompiler::CCompiler"), DetourFindFunction(DLLPATH(), "CCompiler::CCompilerCtorHookHelper"));

	/// @patch dynamic client cache memmgr - r2556
	HookDB::DB().Hook("CNeighborCache::CNeighborCache", DetourFindFunction(EXEPATH(), "CNeighborCache::CNeighborCache"), DetourFindFunction(DLLPATH(), "CNeighborCache::CNeighborCache"));
	HookDB::DB().Hook("CNeighborCache::~CNeighborCache", DetourFindFunction(EXEPATH(), "CNeighborCache::~CNeighborCache"), DetourFindFunction(DLLPATH(), "CNeighborCache::~CNeighborCache"));
	HookDB::DB().Hook("CNeighborCache::Insert", DetourFindFunction(EXEPATH(), "CNeighborCache::Insert"), DetourFindFunction(DLLPATH(), "CNeighborCache::Insert"));

	/// @patch dynamic guild cache memmgr - r2559 r2560
 	HookDB::DB().Hook("CZGuildMgr::CZGuildMgr", DetourFindFunction(EXEPATH(), "CZGuildMgr::CZGuildMgr"), DetourFindFunction(DLLPATH(), "CZGuildMgr::CZGuildMgr"));
 	HookDB::DB().Hook("CZGuildMgr::~CZGuildMgr", DetourFindFunction(EXEPATH(), "CZGuildMgr::~CZGuildMgr"), DetourFindFunction(DLLPATH(), "CZGuildMgr::~CZGuildMgr"));
 	HookDB::DB().Hook("?Init@CZGuildMgr@@UAEXXZ", DetourFindFunction(EXEPATH(), "?Init@CZGuildMgr@@UAEXXZ"), DetourFindFunction(DLLPATH(), "?Init@CZGuildMgr@@UAEXXZ"));
 	HookDB::DB().Hook("?Init@CZGuildMgr@@QAEXH@Z", DetourFindFunction(EXEPATH(), "?Init@CZGuildMgr@@QAEXH@Z"), DetourFindFunction(DLLPATH(), "?Init@CZGuildMgr@@QAEXH@Z"));
 	HookDB::DB().Hook("CZGuildMgr::MakeGuild", DetourFindFunction(EXEPATH(), "CZGuildMgr::MakeGuild"), DetourFindFunction(DLLPATH(), "CZGuildMgr::MakeGuild"));
 	HookDB::DB().Hook("CZGuildMgr::AllocGuild", DetourFindFunction(EXEPATH(), "CZGuildMgr::AllocGuild"), DetourFindFunction(DLLPATH(), "CZGuildMgr::AllocGuild"));
 	HookDB::DB().Hook("CZGuildMgr::GetOffset", DetourFindFunction(EXEPATH(), "CZGuildMgr::GetOffset"), DetourFindFunction(DLLPATH(), "CZGuildMgr::GetOffset"));

	/// @patch dynamic mob loot memmgr
	HookDB::DB().Hook("CNPC::CNPC", DetourFindFunction(EXEPATH(), "CNPC::CNPC"), DetourFindFunction(DLLPATH(), "CNPC::CNPCCtorHookHelper"));
	HookDB::DB().Hook("CNPC::~CNPC", DetourFindFunction(EXEPATH(), "CNPC::~CNPC"), DetourFindFunction(DLLPATH(), "CNPC::CNPCDtorHookHelper"));
	HookDB::DB().Hook("CNPCStateUpdater::OnPickUpItem", DetourFindFunction(EXEPATH(), "CNPCStateUpdater::OnPickUpItem"), DetourFindFunction(DLLPATH(), "CNPCStateUpdater::OnPickUpItem"));

	/// @patch athena-style circular mob loot list
	HookDB::DB().Hook("CNPCStateUpdater::OnPickUpItem", DetourFindFunction(EXEPATH(), "CNPCStateUpdater::OnPickUpItem"), DetourFindFunction(DLLPATH(), "CNPCStateUpdater::OnPickUpItem"));

	/// @patch backport "disable hostile request", "disable ally request" setting from 20100527ZoneProcess
	HookDB::DB().Hook("CPCPacketHandler::OnReqHostileGuild", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnReqHostileGuild"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnReqHostileGuild"));
	HookDB::DB().Hook("CPCPacketHandler::OnReqAllyGuild", DetourFindFunction(EXEPATH(), "CPCPacketHandler::OnReqAllyGuild"), DetourFindFunction(DLLPATH(), "CPCPacketHandler::OnReqAllyGuild"));

	// @patch backport "output disconnect log" setting from 20100527ZoneProcess
	HookDB::DB().Hook("CCharacterMgr::ProcessAllCharacter", DetourFindFunction(EXEPATH(), "CCharacterMgr::ProcessAllCharacter"), DetourFindFunction(DLLPATH(), "CCharacterMgr::ProcessAllCharacter"));

	/// @patch custom killer system (configurable manner points, killler/victim expire timeouts), remove bonus effects and bad packet sends - r2640
	HookDB::DB().Hook("CPC::IsCrazyKiller", DetourFindFunction(EXEPATH(), "CPC::IsCrazyKiller"), DetourFindFunction(DLLPATH(), "CPC::IsCrazyKiller"));
	HookDB::DB().Hook("CPC::NotifyPKInfo", DetourFindFunction(EXEPATH(), "CPC::NotifyPKInfo"), DetourFindFunction(DLLPATH(), "CPC::NotifyPKInfo"));
	HookDB::DB().Hook("CPC::OnDead", DetourFindFunction(EXEPATH(), "CPC::OnDead"), DetourFindFunction(DLLPATH(), "CPC::OnDead"));
	HookDB::DB().Hook("CPC::SetKillerSystem", DetourFindFunction(EXEPATH(), "CPC::SetKillerSystem"), DetourFindFunction(DLLPATH(), "CPC::SetKillerSystem"));
	HookDB::DB().Hook("CPC::SetPKInfo", DetourFindFunction(EXEPATH(), "CPC::SetPKInfo"), DetourFindFunction(DLLPATH(), "CPC::SetPKInfo"));
	HookDB::DB().Hook("CPC::UpdatePKInfo", DetourFindFunction(EXEPATH(), "CPC::UpdatePKInfo"), DetourFindFunction(DLLPATH(), "CPC::UpdatePKInfo"));

	/// @patch make base treasure box count on investment a setting - r2693
	HookDB::DB().Hook("CAgitMapRes::GetTreasureBoxCount", DetourFindFunction(EXEPATH(), "CAgitMapRes::GetTreasureBoxCount"), DetourFindFunction(DLLPATH(), "CAgitMapRes::GetTreasureBoxCount"));

	/// @patch improve critical error log code
	/// @patch capture critical error log caller's call stack
	HookDB::DB().Hook("CErrorLog::CriticalErrorLog", DetourFindFunction(EXEPATH(), "CErrorLog::CriticalErrorLog"), DetourFindFunction(DLLPATH(), "CErrorLog::CriticalErrorLog"));
	HookDB::DB().Hook("CErrorLog::CriticalErrorLogFmt", DetourFindFunction(EXEPATH(), "CErrorLog::CriticalErrorLogFmt"), DetourFindFunction(DLLPATH(), "CErrorLog::CriticalErrorLogFmt"));

	/// @patch change guild maxUserNum to 28 players (w/ GD_EXTENSION)
	HookDB::DB().Hook("CZGuildInfo::OnNotifySkillData", DetourFindFunction(EXEPATH(), "CZGuildInfo::OnNotifySkillData"), DetourFindFunction(DLLPATH(), "CZGuildInfo::OnNotifySkillData")); // m_maxUserNum
	HookDB::DB().Hook("CZGuildInfoPacketDispatcher::GetGuildInfo", DetourFindFunction(EXEPATH(), "CZGuildInfoPacketDispatcher::GetGuildInfo"), DetourFindFunction(DLLPATH(), "CZGuildInfoPacketDispatcher::GetGuildInfo"));
	HookDB::DB().Hook("CGuild::Init", DetourFindFunction(EXEPATH(), "CGuild::Init"), DetourFindFunction(DLLPATH(), "CGuild::Init")); // m_maxUserNum
	HookDB::DB().Hook("SK_GD_EXTENSION::OnMsg", DetourFindFunction(EXEPATH(), "SK_GD_EXTENSION::OnMsg"), DetourFindFunction(DLLPATH(), "SK_GD_EXTENSION::OnMsg"));

	/// @patch obey defined mob spawn area
	HookDB::DB().Hook("CScriptEventHandler::AddNpc", DetourFindFunction(EXEPATH(), "CScriptEventHandler::AddNpc"), DetourFindFunction(DLLPATH(), "CScriptEventHandler::AddNpc"));

	/// @patch config-defined ip address
	HookDB::DB().Hook("GetLocalIPAddr", DetourFindFunction(EXEPATH(), "GetLocalIPAddr"), DetourFindFunction(DLLPATH(), "GetLocalIPAddr"));
	HookDB::DB().Hook("connect", DetourFindFunction("ws2_32.dll", "connect"), DetourFindFunction(DLLPATH(), "my_connect"));

	/// @patch ip address in mutex name to allow multiple zones on one system
	HookDB::DB().Hook("CreateMutexA", DetourFindFunction("kernel32.dll", "CreateMutexA"), DetourFindFunction(DLLPATH(), "my_CreateMutexA"));

	/// @patch ip address in window title
	HookDB::DB().Hook("CreateWindowExA", DetourFindFunction("user32.dll", "CreateWindowExA"), DetourFindFunction(DLLPATH(), "my_CreateWindowExA"));

	/// @patch TCP_NODELAY on all inbound connections
	HookDB::DB().Hook("WSAAccept", DetourFindFunction("ws2_32.dll", "WSAAccept"), DetourFindFunction(DLLPATH(), "my_WSAAccept"));

	/// @patch handle all the remaining eClientType types instead of using the default handler
	HookDB::DB().Hook("?FindCharacter@CCharacterMgr@@QAEPAVCCharacter@@KK@Z", DetourFindFunction(EXEPATH(), "?FindCharacter@CCharacterMgr@@QAEPAVCCharacter@@KK@Z"), DetourFindFunction(DLLPATH(), "?FindCharacter@CCharacterMgr@@QAEPAVCCharacter@@KK@Z"));

	/// @patch updated npc IDs and JOBTYPEs
	HookDB::DB().Hook("CMonsterParameterTable::SetTable", DetourFindFunction(EXEPATH(), "CMonsterParameterTable::SetTable"), DetourFindFunction(DLLPATH(), "CMonsterParameterTable::SetTable"));

	/// @patch more room for scripted npcs and mobs (change NPC_MINIMUM_AID)
	Hex(0x4F224B, 4, "\x50\xC3\x00\x00", "\x30\x75\x00\x00"); // 50000 -> 30000 in CCharacterMgr::Init()
	Hex(0x4F0F20, 4, "\x50\xC3\x00\x00", "\x30\x75\x00\x00"); // 50000 -> 30000 in CCharacterMgr::Free()
	Hex(0x575AA4, 4, "\x50\xC3\x00\x00", "\x30\x75\x00\x00"); // 50000 -> 30000 in CNpcMgr::Clear()
}


void UnHook()
{
}


void SymDBInitCallback()
{
}
