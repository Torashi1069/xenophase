void Hook()
{
	extern void Test(void);
	Test();

	extern void Hook_Alloc(void* pfnNew, void* pfnDelete, void* pfnInit);
	Hook_Alloc(DetourFindFunction(EXEPATH(), "??2@YAPAXI@Z"), DetourFindFunction(EXEPATH(), "??3@YAXPAX@Z"), DetourFindFunction(EXEPATH(), "_cinit"));

//	hookdb.Hook("WinMain", DetourFindFunction(EXEPATH(), "WinMain"), DetourFindFunction(DLLPATH(), "WinMain"));

	// fix broadcast logging | custom logging format
	HookDB::DB().Hook("CZSPacketHandler::OnBroadCast", DetourFindFunction(EXEPATH(), "CZSPacketHandler::OnBroadCast"), DetourFindFunction(DLLPATH(), "CZSPacketHandler::OnBroadCast"));

	// fix calculation performance from O(n) to O(1)
	HookDB::DB().Hook("CUserMgr::GetFreeSize", DetourFindFunction(EXEPATH(), "CUserMgr::GetFreeSize"), DetourFindFunction(DLLPATH(), "CUserMgr::GetFreeSize"));
	HookDB::DB().Hook("CPartyMgr::GetFreeSize", DetourFindFunction(EXEPATH(), "CPartyMgr::GetFreeSize"), DetourFindFunction(DLLPATH(), "CPartyMgr::GetFreeSize"));
	HookDB::DB().Hook("CIGuildMgr::GetFreeSize", DetourFindFunction(EXEPATH(), "CIGuildMgr::GetFreeSize"), DetourFindFunction(DLLPATH(), "CIGuildMgr::GetFreeSize"));
	HookDB::DB().Hook("CProcessThread::ThreadFunction", DetourFindFunction(EXEPATH(), "CProcessThread::ThreadFunction"), DetourFindFunction(DLLPATH(), "CProcessThread::ThreadFunction"));

	/// @patch change guild maxUserNum to 28 players (w/ GD_EXTENSION)
	HookDB::DB().Hook("CIGuildInfo::LoadSkill", DetourFindFunction(EXEPATH(), "CIGuildInfo::LoadSkill"), DetourFindFunction(DLLPATH(), "CIGuildInfo::LoadSkill"));
	HookDB::DB().Hook("CGuild::Init", DetourFindFunction(EXEPATH(), "CGuild::Init"), DetourFindFunction(DLLPATH(), "CGuild::Init")); // m_maxUserNum

	/// @patch build date in window title
	HookDB::DB().Hook("CreateWindowExA", DetourFindFunction("user32.dll", "CreateWindowExA"), DetourFindFunction(DLLPATH(), "my_CreateWindowExA"));

	/// @patch config-defined ip address
	HookDB::DB().Hook("GetLocalIPAddr", DetourFindFunction(EXEPATH(), "GetLocalIPAddr"), DetourFindFunction(DLLPATH(), "GetLocalIPAddr"));
	HookDB::DB().Hook("connect", DetourFindFunction("ws2_32.dll", "connect"), DetourFindFunction(DLLPATH(), "my_connect"));

	/// @patch unlock hidden third window mode [r3134]
	HookDB::DB().Hook("WndProc", DetourFindFunction(EXEPATH(), "WndProc"), DetourFindFunction(DLLPATH(), "WndProc"));

	/// @patch redraw window after switching modes [r3135]
	HookDB::DB().Hook("WndProc", DetourFindFunction(EXEPATH(), "WndProc"), DetourFindFunction(DLLPATH(), "WndProc"));

	/// @patch 'killall' system menu item [r3136]
	HookDB::DB().Hook("WndProc", DetourFindFunction(EXEPATH(), "WndProc"), DetourFindFunction(DLLPATH(), "WndProc"));
}


void UnHook()
{
}


void SymDBInitCallback()
{
}
