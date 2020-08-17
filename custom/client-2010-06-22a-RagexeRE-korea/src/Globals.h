#pragma once


extern const char*& g_accountAddr;
extern const char*& g_accountPort;
extern bool& g_readFolderFirst;
extern mystd::map<int,int>& g_packetLenMap;
extern class XMLDocument& document;
extern mystd::vector<mystd::string>& s_loadingScreenList;
extern class CFileMgr& g_fileMgr;
extern class CModeMgr& g_modeMgr;
extern class CWeather& g_Weather;
extern enum LanguageType& g_languageType;
extern enum ServiceType& g_serviceType;
extern enum ServerType& g_serverType;
extern int& g_loginStartMode;
extern HWND& g_hMainWnd;
extern int& g_frameskip;
extern int& g_sysQuit;
extern struct Registry2& g_registry;
extern bool& g_bUseCommand;
extern char (& mutexKey)[8];
extern char& g_EXE_way;
extern const char*& WINDOW_NAME;
extern const char*& PATCH_CLIENT;
extern const char*& PATCH_UP;
extern const char*& PLEASE_EXCUTE_LAUNCHER;
extern float& g_avgPixelRatio;
extern float& g_zHover;
extern float& g_zOffset;
extern float& g_slope;
extern float& g_shadowSlope;
extern float& g_viewDistance;
extern mystd::vector<int>& stateId;
extern float (& g_sinTable)[722];
extern BOOL& g_mustPumpOutReceiveQueue;
extern DWORD (& g_fontCharSet)[12];
extern int& g_shiftKeyPressed;
extern class CActorPickNode& g_actorPickNode;
extern char& g_checkBOT;
extern int& g_isAppActive;
extern struct CHARACTER_INFO& g_charInfo;
extern bool& g_pingLog;
extern DWORD& g_pingLogStart;
extern mystd::list<DWORD>& g_pingLogList;
extern struct ServerAddressEx& g_charServerAddr;
extern struct ServerAddress& g_zoneServerAddr;
extern bool& g_passwordEncrypt;
extern bool& g_passwordEncrypt2;
extern int& g_version;
extern DWORD& g_codePage;
extern bool& g_multiLang;
extern class CPathFinder& g_pathFinder;


void __cdecl Trace(const char* str, ...);
void __cdecl ErrorMsg(const char* msg);
void __cdecl GDIFlip(void);
