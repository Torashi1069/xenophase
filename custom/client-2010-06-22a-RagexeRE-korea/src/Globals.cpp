#include "Globals.h"


const char*& g_accountAddr = VTOR<const char*>(SymDB::Find("g_accountAddr"));
const char*& g_accountPort = VTOR<const char*>(SymDB::Find("g_accountAddr"));
bool& g_readFolderFirst = VTOR<bool>(SymDB::Find("g_readFolderFirst"));
mystd::map<int,int>& g_packetLenMap = VTOR<mystd::map<int,int>>(SymDB::Find("g_packetLenMap"));
XMLDocument& document = VTOR<XMLDocument>(SymDB::Find("document"));
mystd::vector<mystd::string>& s_loadingScreenList = VTOR<mystd::vector<mystd::string>>(SymDB::Find("s_loadingScreenList"));
CFileMgr& g_fileMgr = VTOR<CFileMgr>(SymDB::Find("g_fileMgr"));
CModeMgr& g_modeMgr = VTOR<CModeMgr>(SymDB::Find("g_modeMgr"));
CWeather& g_Weather = VTOR<CWeather>(SymDB::Find("g_Weather"));
LanguageType& g_languageType = VTOR<LanguageType>(SymDB::Find("g_languageType")); // = ?;
ServiceType& g_serviceType = VTOR<ServiceType>(SymDB::Find("g_serviceType")); // = ?;
ServerType& g_serverType = VTOR<ServerType>(SymDB::Find("g_serverType")); // = ServerSakray;
int& g_loginStartMode = VTOR<int>(SymDB::Find("g_loginStartMode")); // = 3;
HWND& g_hMainWnd = VTOR<HWND>(SymDB::Find("g_hMainWnd"));
int& g_frameskip = VTOR<int>(SymDB::Find("g_frameskip")); // = 1;
int& g_sysQuit = VTOR<int>(SymDB::Find("g_sysQuit"));
Registry2& g_registry = VTOR<Registry2>(SymDB::Find("g_registry")); // = ?;
bool& g_bUseCommand = VTOR<bool>(SymDB::Find("g_bUseCommand")); // = ?;
char (& mutexKey)[8] = VTOR<char[8]>(SymDB::Find("mutexKey")); // = "Surface";
char& g_EXE_way = VTOR<char>(SymDB::Find("g_EXE_way")); // = ?;
const char*& WINDOW_NAME = VTOR<const char*>(SymDB::Find("WINDOW_NAME"));
const char*& PATCH_CLIENT = VTOR<const char*>(SymDB::Find("PATCH_CLIENT"));
const char*& PATCH_UP = VTOR<const char*>(SymDB::Find("PATCH_UP"));
const char*& PLEASE_EXCUTE_LAUNCHER = VTOR<const char*>(SymDB::Find("PLEASE_EXCUTE_LAUNCHER"));
float& g_avgPixelRatio = VTOR<float>(SymDB::Find("g_avgPixelRatio")); // = 1.34f; // = 0x3FAB851F;
float& g_zHover = VTOR<float>(SymDB::Find("g_zHover")); // = 0.000036000001f; // = 0x3816FEB5;
float& g_zOffset = VTOR<float>(SymDB::Find("")); // = 0.0000090000003f; // = 0x3716FEB5;
float& g_slope = VTOR<float>(SymDB::Find("g_slope")); // = 0.16f; // = 0x3E23D70A;
float& g_shadowSlope = VTOR<float>(SymDB::Find("g_shadowSlope")); // = 0.16f; // = 0x3E23D70A;
float& g_viewDistance = VTOR<float>(SymDB::Find("g_viewDistance")); // = 300.0f; // = 0x43960000;
mystd::vector<int>& stateId = VTOR<mystd::vector<int>>(SymDB::Find("stateId")); // = ?;
float (& g_sinTable)[722] = VTOR<float[722]>(SymDB::Find("g_sinTable")); // = ?;
BOOL& g_mustPumpOutReceiveQueue = VTOR<BOOL>(SymDB::Find("g_mustPumpOutReceiveQueue")); // = ?;
DWORD (& g_fontCharSet)[12] = VTOR<DWORD[12]>(SymDB::Find("g_fontCharSet")); // = { 129, 0, 128, 134, 136, 222, 162, 0, 0, 204, 163, 178 };
int& g_shiftKeyPressed = VTOR<int>(SymDB::Find("g_shiftKeyPressed")); // = ?;
CActorPickNode& g_actorPickNode = VTOR<CActorPickNode>(SymDB::Find("g_actorPickNode")); // = ?;
char& g_checkBOT = VTOR<char>(SymDB::Find("g_checkBOT")); // = ?;
int& g_isAppActive = VTOR<int>(SymDB::Find("g_isAppActive")); // = 1;
CHARACTER_INFO& g_charInfo = VTOR<CHARACTER_INFO>(SymDB::Find("g_charInfo")); // = ?;
bool& g_pingLog = VTOR<bool>(SymDB::Find("g_pingLog")); // = ?;
DWORD& g_pingLogStart = VTOR<DWORD>(SymDB::Find("g_pingLogStart")); // = ?;
mystd::list<DWORD>& g_pingLogList = VTOR<mystd::list<DWORD>>(SymDB::Find("g_pingLogList")); // = ?;
ServerAddressEx& g_charServerAddr = VTOR<ServerAddressEx>(SymDB::Find("g_charServerAddr")); // = ?;
ServerAddress& g_zoneServerAddr = VTOR<ServerAddress>(SymDB::Find("g_zoneServerAddr")); // = ?;
bool& g_passwordEncrypt = VTOR<bool>(SymDB::Find("g_passwordEncrypt")); // = ?;
bool& g_passwordEncrypt2 = VTOR<bool>(SymDB::Find("g_passwordEncrypt2")); // = ?;
int& g_version = VTOR<int>(SymDB::Find("g_version")); // = ?;
DWORD& g_codePage = VTOR<DWORD>(SymDB::Find("g_codePage")); // = ?;
bool& g_multiLang = VTOR<bool>(SymDB::Find("g_multiLang"));
CPathFinder& g_pathFinder = VTOR<CPathFinder>(SymDB::Find("g_pathFinder"));


hook_func<void (__cdecl *)(const char* str, ...)> _Trace("Trace");
void __cdecl Trace(const char* str, ...)
{
//	return (_Trace)(str, ...);

	;
}


hook_func<void (__cdecl *)(const char* msg)> _ErrorMsg("ErrorMsg"); // Mode.cpp
void __cdecl ErrorMsg(const char* msg)
{
	return (_ErrorMsg)(msg);
}


hook_func<void (__cdecl *)(void)> _GDIFlip("GDIFlip"); // 3dLib/Device.cpp
void __cdecl GDIFlip(void)
{
	return _GDIFlip();
}


class hook_ptr<struct mystd::_Tree<int, struct mystd::pair<int const, int>, struct mystd::map<int, int, struct mystd::less<int>, class mystd::allocator<int>>::_Kfn, struct mystd::less<int>, class mystd::allocator<int>>::_Node *> mystd::_Tree<int, struct mystd::pair<int const, int>, struct mystd::map<int, int, struct mystd::less<int>, class mystd::allocator<int>>::_Kfn, struct mystd::less<int>, class mystd::allocator<int>>::_Nil("?_Nil@?$_Tree@HU?$pair@$$CBHH@std@@U_Kfn@?$map@HHU?$less@H@std@@V?$allocator@H@2@@2@U?$less@H@2@V?$allocator@H@2@@std@@1PAU_Node@12@A");
