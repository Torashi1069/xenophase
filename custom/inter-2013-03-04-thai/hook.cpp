void Hook()
{
	C_ASSERT( sizeof std::string == 28 );
	C_ASSERT( sizeof std::vector<int> == 24 );
	C_ASSERT( sizeof std::list<int> == 28 );
	struct tmp { std::map<int,int> a; }; C_ASSERT( sizeof tmp == 32 );

	extern void Hook_Alloc(void* pfnNew, void* pfnDelete, void* pfnInit);
	Hook_Alloc(DetourFindFunction(EXEPATH(), "??2@YAPAXI@Z"), DetourFindFunction(EXEPATH(), "??3@YAXPAX@Z"), DetourFindFunction(EXEPATH(), "_cinit"));

#if 0
	HookDB::DB().Hook("WinMain", DetourFindFunction(EXEPATH(), "WinMain"), DetourFindFunction(DLLPATH(), "WinMain");
#else
	/// reduce cpu load by skipping the unused, excessive and inefficient memory statistics in the processing thread
	Hex(0x42BB8C, 1, "\x75", "\xEB"); /// jnz -> jmp @ CProcessThread::ThreadFunction()

	/// change guild maxUserNum to 28 players (w/ GD_EXTENSION)
	Hex(0x412DF3, 7, "\x8D\x04\x85\x10\x00\x00\x00", "\x8D\x04\x45\x08\x00\x00\x00"); /// lea eax, 16[eax*4] -> 8[eax*2] @ CIGuildInfo::LoadSkill()
	Hex(0x43463D, 7, "\xC7\x41\x3C\x10\x00\x00\x00", "\xC7\x41\x3C\x08\x00\x00\x00"); /// mov dword ptr [this+60], 16 -> 8 @ CGuild::Init()

	/// custom broadcast log format with daily log rotation
	extern void CZSPacketHandler__OnBroadCast_shim();
	HookDB::DB().Hook("CZSPacketHandler::OnBroadCast", DetourFindFunction(EXEPATH(), "CZSPacketHandler::OnBroadCast"), &CZSPacketHandler__OnBroadCast_shim);

	/// config-controlled ip address
	void GetLocalIPAddr__shim();
	HookDB::DB().Hook("GetLocalIPAddr", DetourFindFunction(EXEPATH(), "GetLocalIPAddr"), &GetLocalIPAddr__shim);

	/// build date in window title
	void InitInstance__shim();
	HookDB::DB().Hook("InitInstance", DetourFindFunction(EXEPATH(), "InitInstance"), &InitInstance__shim);

	/// 'killall' system menu item
	HookDB::DB().Hook("WndProc", DetourFindFunction(EXEPATH(), "WndProc"), DetourFindFunction(DLLPATH(), "WndProc"));
#endif
}


void UnHook()
{
}


void SymDBInitCallback()
{
}


#ifndef NDEBUG
extern "C" void __cdecl _invalid_parameter(_In_opt_z_ const wchar_t *, _In_opt_z_ const wchar_t *, _In_opt_z_ const wchar_t *, unsigned int, uintptr_t);
extern "C" void __cdecl _invalid_parameter_noinfo(void)
{
    _invalid_parameter(NULL, NULL, NULL, 0, 0);
}
#endif


static void* CZSPacketHandler__OnBroadCast__ptr = DetourFindFunction(DLLPATH(), "CZSPacketHandler::OnBroadCast");
__declspec(naked) void CZSPacketHandler__OnBroadCast_shim()
{
	__asm {
	mov eax, [esp+4]
	mov [esp+4], ecx
	mov ecx, eax
	jmp CZSPacketHandler__OnBroadCast__ptr
	}
}


static void* GetLocalIPAddr__ptr = DetourFindFunction(DLLPATH(), "GetLocalIPAddr");
__declspec(naked) void GetLocalIPAddr__shim()
{
	__asm {
	push 0
	call GetLocalIPAddr__ptr
	add esp, 4
	ret
	}
}


static void* InitInstance__ptr = DetourFindFunction(DLLPATH(), "InitInstance");
__declspec(naked) void InitInstance__shim()
{
	__asm {
	mov eax, [esp+4]
	push eax
	push 0
	call InitInstance__ptr
	add esp, 8
	ret
	}
}
