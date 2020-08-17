#include "Globals.h"
#include "ModeMgr.h"
#include "Base/File.h"
#include "Base/FileMgr.h"


CFileMgr& g_fileMgr = *(CFileMgr*)DetourFindFunction(SAKEXE, "g_fileMgr"); // = ?
HWND& g_hMainWnd = *(HWND*)DetourFindFunction(SAKEXE, "g_hMainWnd"); // = 0
C3dDevice& g_3dDevice = *(C3dDevice*)DetourFindFunction(SAKEXE, "g_3dDevice"); // = { ...0... }
char(& mutexKey)[8] = *(char(*)[8])DetourFindFunction(SAKEXE, "mutexKey"); // = "Surface"
char(& g_baseDir)[128] = *(char(*)[128])DetourFindFunction(SAKEXE, "g_baseDir"); // = "data\\"
char(& g_baseDir3)[128] = *(char(*)[128])DetourFindFunction(SAKEXE, "g_baseDir3"); // = ?
bool& g_readFolderFirst = *(bool*)DetourFindFunction(SAKEXE, "g_readFolderFirst"); // = ?
XMLDocument& document = *(XMLDocument*)DetourFindFunction(SAKEXE, "document"); // = ?
enum ServiceType& g_serviceType = *(enum ServiceType*)DetourFindFunction(SAKEXE, "g_serviceType"); // = ?
enum ServerType& g_serverType = *(enum ServerType*)DetourFindFunction(SAKEXE, "g_serverType"); // = ServerSakray
enum LanguageType& g_languageType = *(enum LanguageType*)DetourFindFunction(SAKEXE, "g_languageType"); // = ?
mystd::vector<mystd::string>& s_loadingScreenList = *(mystd::vector<mystd::string>*)DetourFindFunction(SAKEXE, "s_loadingScreenList"); // = ?
bool& g_hideAccountList = *(bool*)DetourFindFunction(SAKEXE, "g_hideAccountList"); // = ?
bool& g_passwordEncrypt = *(bool*)DetourFindFunction(SAKEXE, "g_passwordEncrypt"); // = ?
bool& g_passwordEncrypt2 = *(bool*)DetourFindFunction(SAKEXE, "g_passwordEncrypt2"); // = ?
bool& g_extended_slot = *(bool*)DetourFindFunction(SAKEXE, "g_extended_slot"); // = ?
int& g_version = *(int*)DetourFindFunction(SAKEXE, "g_version"); // = ?
const char*& g_licence = *(const char**)DetourFindFunction(SAKEXE, "g_licence"); // = ""
const char*& g_regPath = *(const char**)DetourFindFunction(SAKEXE, "g_regPath"); // = ""
const char*& g_optionPath = *(const char**)DetourFindFunction(SAKEXE, "g_optionPath"); // = "\\Option";
const char*& WINDOW_NAME = *(const char**)DetourFindFunction(SAKEXE, "WINDOW_NAME"); // = ""
const char*& PATCH_CLIENT = *(const char**)DetourFindFunction(SAKEXE, "PATCH_CLIENT"); // = ""
const char*& PATCH_UP = *(const char**)DetourFindFunction(SAKEXE, "PATCH_UP"); // = ""
const char*& PLEASE_EXCUTE_LAUNCHER = *(const char**)DetourFindFunction(SAKEXE, "PLEASE_EXCUTE_LAUNCHER"); // = ""
const char*& g_accountAddr = *(const char**)DetourFindFunction(SAKEXE, "g_accountAddr"); // = ""
const char*& g_accountPort = *(const char**)DetourFindFunction(SAKEXE, "g_accountPort"); // = ""
const char*& g_regstrationWeb = *(const char**)DetourFindFunction(SAKEXE, "g_regstrationWeb"); // = ""
DWORD(& dwAdminAID)[32] = *(DWORD(*)[32])DetourFindFunction(SAKEXE, "dwAdminAID");   // = { 100118, 2750446, 2750961, 2750963, 2750964, 2750966, 2750967, 2750969, 2750971, 2750972, 2750973, 3143679, 3143680, 3143681, 3143682, 3143684, 3143685, 3143686, 3143680, 3143681, 3143682, 3143684, 3143685, 3143686, 3143687, 3143688, 3143689, 3143690, 3143691, 3143692, 3143693, 3143695, 3143696, 3143699, 3143700, 3143701, 3143701, 2919557 }
DWORD(& dwYellowAID)[35] = *(DWORD(*)[35])DetourFindFunction(SAKEXE, "dwYellowAID"); // = { 100118, 2750446, 2750961, 2750963, 2750964, 2750966, 2750967, 2750969, 2750971, 2750972, 2750973, 3143679, 3143680, 3143681, 3143682, 3143684, 3143685, 3143686, 3143680, 3143681, 3143682, 3143684, 3143685, 3143686, 3143687, 3143688, 3143689, 3143690, 3143691, 3143692, 3143693, 3143695, 3143696, 3143699, 3143700, 3143701, 3143701, 2919557, 3143702, 2919557, 3304372, 3304363, 3304378 }
mystd::vector<DWORD>& s_dwAdminAID = *(mystd::vector<DWORD>*)DetourFindFunction(SAKEXE, "s_dwAdminAID"); // = ?
mystd::vector<DWORD>& s_dwYellowAID = *(mystd::vector<DWORD>*)DetourFindFunction(SAKEXE, "s_dwYellowAID"); // = ?
bool& g_multiLang = *(bool*)DetourFindFunction(SAKEXE, "g_multiLang"); // = ?
unsigned long& g_codePage = *(unsigned long*)DetourFindFunction(SAKEXE, "g_codePage");
CLanguage*& g_language = *(CLanguage**)DetourFindFunction(SAKEXE, "g_language"); // = ?
bool& NameBalloonShorten = *(bool*)DetourFindFunction(SAKEXE, "NameBalloonShorten"); // = ?
bool& NameBalloonfontBold = *(bool*)DetourFindFunction(SAKEXE, "NameBalloonfontBold"); // = ?
int& NameBalloonfontSize = *(int*)DetourFindFunction(SAKEXE, "NameBalloonfontSize"); // = 12
bool& g_sendUDPPacket = *(bool*)DetourFindFunction(SAKEXE, "g_sendUDPPacket"); // = ?
CSession& g_session = *(CSession*)DetourFindFunction(SAKEXE, "g_session"); // = ?
UIWindowMgr& g_windowMgr = *(UIWindowMgr*)DetourFindFunction(SAKEXE, "g_windowMgr"); // = ?
CSkinMgr& g_skinMgr = *(CSkinMgr*)DetourFindFunction(SAKEXE, "g_skinMgr"); // = ?
CModeMgr& g_modeMgr = *(CModeMgr*)DetourFindFunction(SAKEXE, "g_modeMgr"); // = ?
mystd::string& s_basicSkinName = *(mystd::string*)DetourFindFunction(SAKEXE, "s_basicSkinName"); // = "<Basic Skin>";
Registry2& g_registry = *(Registry2*)DetourFindFunction(SAKEXE, "g_registry"); // = ?
unsigned long& g_soundMode = *(unsigned long*)DetourFindFunction(SAKEXE, "g_soundMode"); // = 2
CRenderer*& g_renderer = *(CRenderer**)DetourFindFunction(SAKEXE, "g_renderer"); // = ?
CRagConnection& g_connection = *(CRagConnection*)DetourFindFunction(SAKEXE, "g_connection"); // = ?
CMouse& g_mouse = *(CMouse*)DetourFindFunction(SAKEXE, "g_mouse"); // = ?
int& g_loginStartMode = *(int*)DetourFindFunction(SAKEXE, "g_loginStartMode"); // = 3
CTexMgr& g_texMgr = *(CTexMgr*)DetourFindFunction(SAKEXE, "g_texMgr"); // = ?
C3dGrannyBoneRes& g_GrannyBoneRes = *(C3dGrannyBoneRes*)DetourFindFunction(SAKEXE, "g_GrannyBoneRes"); // = ?
CBink& g_Bink = *(CBink*)DetourFindFunction(SAKEXE, "g_Bink"); // = ?
BOOL& g_sysQuit = *(BOOL*)DetourFindFunction(SAKEXE, "g_sysQuit"); // = ?
GuildInfo& g_guildInfo = *(GuildInfo*)DetourFindFunction(SAKEXE, "g_guildInfo"); // = ?
int& g_isStopByLogin = *(int*)DetourFindFunction(SAKEXE, "g_isStopByLogin"); // = ?
CSnapMgr& g_snapMgr = *(CSnapMgr*)DetourFindFunction(SAKEXE, "g_snapMgr"); // = ?
CHARACTER_INFO& g_charInfo = *(CHARACTER_INFO*)DetourFindFunction(SAKEXE, "g_charInfo"); // = ?
ServerAddress& g_charServerAddr = *(ServerAddress*)DetourFindFunction(SAKEXE, "g_charServerAddr"); // = ?
ServerAddress& g_zoneServerAddr = *(ServerAddress*)DetourFindFunction(SAKEXE, "g_zoneServerAddr"); // = ?
BOOL& g_mustPumpOutReceiveQueue = *(BOOL*)DetourFindFunction(SAKEXE, "g_mustPumpOutReceiveQueue"); // = ?
unsigned char(& lower_table)[256] = *(unsigned char(*)[256])DetourFindFunction(SAKEXE, "lower_table"); // = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF }
vector3d& g_WorldUp = *(vector3d*)DetourFindFunction(SAKEXE, "g_WorldUp"); // (0., 1., 0.);
CBitmapRes& CBitmapResInstance = *(CBitmapRes*)DetourFindFunction(SAKEXE, "CBitmapResInstance"); // (???, "bmp", "texture\\");
CBitmapRes& CBitmapResInstance2 = *(CBitmapRes*)DetourFindFunction(SAKEXE, "CBitmapResInstance2"); // (???, "tga", "texture\\");
CBitmapRes& CBitmapResInstance3 = *(CBitmapRes*)DetourFindFunction(SAKEXE, "CBitmapResInstance3"); // (???, "jpg", "texture\\");
bool& g_pingLog = *(bool*)DetourFindFunction(SAKEXE, "g_pingLog"); // = ?
unsigned long& g_pingLogStart = *(unsigned long*)DetourFindFunction(SAKEXE, "g_pingLogStart"); // = ?
mystd::list<unsigned long>& g_pingLogList = *(mystd::list<unsigned long>*)DetourFindFunction(SAKEXE, "g_pingLogList"); // = ?
CFile& saveChatFp = *(CFile*)DetourFindFunction(SAKEXE, "saveChatFp"); // = ?
CMssVariables& g_mssVar = *(CMssVariables*)DetourFindFunction(SAKEXE, "g_mssVar"); // = ?
vector3d& player_pos = *(vector3d*)DetourFindFunction(SAKEXE, "player_pos"); // = ? { 0, 0, 0 }
int(& durationTable)[1024] = *(int(*)[1024])DetourFindFunction(SAKEXE, "durationTable"); // = { 50, 50, 50, 50, 50, 50, 100, 50, 80, 80, 100, 80, 40, 9999, 50, 100, 40, 30, 50, 50, 100, 100, 270, 999, 100, 40, 160, 150, 100, 200, 104, 160, 100, 200, 100, 100, 100, 100, 100, 100, 999, 999, 150, 100, 50, 100, 180, 250, 130, 50, 50, 50, 40, 50, 40, 40, 40, 40, 40, 40, 200, 250, 250, 250, 999, 999, 999, 999, 999, 9999, 999, 250, 500, 250, 250, 999, 999, 999, 999, 250, 250, 250, 250, 999, 999, 999, 999, 999, 999, 9999, 9999, 9999, 9999, 250, 250, 150, 9999, 9999, 250, 250, 70, 9999, 9999, 999, 999, 250, 9999, 9999, 9999, 9999, 9999, 9999, 999, 9999, 350, 250, 250, 100, 250, 250, 250, 40, 250, 250, 9999, 250, 9999, 9999, 250, 9999, 9999, 9999, 250, 9999, 9999, 9999, 250, 350, 8000, 9999, 250, 9999, 250, 999, 999, 32797, 999, 999, 999, 999, 999, 999, 100, 999, 999, 999, 999, 999, 999, 9999, 9999, 99999999, 99999999, 99999999, 9999, 1000, 9999, 999, 999, 9999, 999, 9999, 100, 100, 100, 100, 100, 100, 100, 100, 50, 9999, 9999, 9999, 0, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 150, 9999, 0, 9999, 99999999, 99999999, 99999999, 99999, 100, 100, 100, 100, 100, 100, 100, 100, 500, 9999, 9999, 500, 200, 200, 199, 199, 199, 150, 200, 9999, 300, 300, 999, 999, 999999, 99999999, 99999999, 999, 99999, 99999999, 999, 999, 999, 999, 999, 29999, 29999, 29999, 29999, 99999, 999, 999, 999, 999, 200, 999, 9999, 150, 200, 100, 99999, 999, 999, 999, 999, 999, 999, 300, 300, 300, 300, 300, 300, 16, 300, 300, 300, 300, 300, 300, 300, 300, 300, 29999, 29999, 29999, 29999, 29999, 29999, 29999, 29999, 29999, 29999, 29999, 29999, 29999, 29999, 29999, 29999, 29999, 29999, 999, 999, 99999999, 300, 300, 300, 99999999, 99999, 300, 200, 200, 200, 36000, 300, 299, 300, 300, 100, 100, 200, 9999, 200, 9999, 9999, 9999, 100, 99999999, 36000, 36000, 36000, 100, 340, 340, 1000, 100, 200, 300, 300, 99999999, 99999999, 99999999, 200, 200, 200, 100, 3000, 9999, 1000, 1000, 100, 99999999, 99999999, 9999, 99999999, 99999999, 99999999, 99999999, 99999999, 99999999, 99999999, 99999999, 99999999, 99999999, 4000, 4000, 4000, 300, 99999999, 100, 100, 300, 300, 99999999, 99999, 99999, 19999, 200, 200, 50, 29999, 99999, 200, 200, 200, 200, 100, 99999999, 99999999, 200, 200, 200, 250, 200, 200, 200, 250, 150, 200, 200, 99999, 99999999, 99999999, 99999999, 99999999, 9999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int(& g_recentEffectId)[32] = *(int(*)[32])DetourFindFunction(SAKEXE, "g_recentEffectId"); // = ?
float(& g_radTable)[722] = *(float(*)[722])DetourFindFunction(SAKEXE, "g_radTable"); // = ?
float(& g_sinTable)[722] = *(float(*)[722])DetourFindFunction(SAKEXE, "g_sinTable"); // = ?
float(& g_cosTable)[722] = *(float(*)[722])DetourFindFunction(SAKEXE, "g_cosTable"); // = ?
extern int& g_isAppActive = *(int*)DetourFindFunction(SAKEXE, "g_isAppActive"); // = 1;
extern int& g_activatedNow = *(int*)DetourFindFunction(SAKEXE, "g_activatedNow"); // = ?
extern int& g_isLightMap = *(int*)DetourFindFunction(SAKEXE, "g_isLightMap"); // = 1;
extern bool& g_isSupportLMTex = *(bool*)DetourFindFunction(SAKEXE, "g_isSupportLMTex"); // = true;
extern CWeather& g_Weather = *(CWeather*)DetourFindFunction(SAKEXE, "g_Weather"); // = ?
extern int& g_isSkipFrame = *(int*)DetourFindFunction(SAKEXE, "g_isSkipFrame"); // = ?
extern CActorPickNode& g_actorPickNode = *(CActorPickNode*)DetourFindFunction(SAKEXE, "g_actorPickNode"); // = ?
extern mystd::vector<int>& stateId = *(mystd::vector<int>*)DetourFindFunction(SAKEXE, "stateId"); // = ?
extern int& guildWndWidth = *(int*)SymDB::Add("guildWndWidth", SAKEXE, "guildWndWidth"); // = 400;
extern int& guildWndHeight = *(int*)SymDB::Add("guildWndHeight", SAKEXE, "guildWndHeight"); // = 317;
extern int& g_isSoundOn = *(int*)SymDB::Add("g_isSoundOn", SAKEXE, "g_isSoundOn"); // = 1;
extern int& g_isFixedCamera = *(int*)SymDB::Add("g_isFixedCamera", SAKEXE, "g_isFixedCamera"); // = ?;
extern const char*& boundaryText = *(const char**)SymDB::Add("boundaryText", SAKEXE, "boundaryText"); // = "-";
extern vector3d& lightDir = VTOR<vector3d>(SymDB::Add("lightDir", SAKEXE, "lightDir")); // = ?;
extern vector3d& diffuseCol = VTOR<vector3d>(SymDB::Add("diffuseCol", SAKEXE, "diffuseCol")); // = ?;
extern vector3d& ambientCol = VTOR<vector3d>(SymDB::Add("ambientCol", SAKEXE, "ambientCol")); // = ?;
extern GroundAttrPosInfo& g_groundAttrPosInfo = VTOR<GroundAttrPosInfo>(SymDB::Add("g_groundAttrPosInfo", SAKEXE, "g_groundAttrPosInfo")); // = ?;
extern CPathFinder& g_pathFinder = VTOR<CPathFinder>(SymDB::Add("g_pathFinder", SAKEXE, "g_pathFinder")); // = ?;
extern HANDLE& g_farModelThread = VTOR<HANDLE>(SymDB::Add("g_farModelThread", SAKEXE, "g_farModelThread")); // = ?;
extern HINSTANCE& g_hInstance = VTOR<HINSTANCE>(SymDB::Add("g_hInstance", SAKEXE, "g_hInstance")); // = ?;
extern int& WINDOW_WIDTH = VTOR<int>(SymDB::Add("WINDOW_WIDTH", SAKEXE, "WINDOW_WIDTH")); // = 640;
extern int& WINDOW_HEIGHT = VTOR<int>(SymDB::Add("WINDOW_HEIGHT", SAKEXE, "WINDOW_HEIGHT")); // = 480;
extern int& g_isVoodoo = VTOR<int>(SymDB::Add("g_isVoodoo", SAKEXE, "g_isVoodoo")); // = ?;
extern int& g_showTipsAtStartup = VTOR<int>(SymDB::Add("g_showTipsAtStartup", SAKEXE, "g_showTipsAtStartup")); // = 1;
extern int& g_isXHalfSpr = VTOR<int>(SymDB::Add("g_isXHalfSpr", SAKEXE, "g_isXHalfSpr")); // = ?;
extern int& g_isYHalfSpr = VTOR<int>(SymDB::Add("g_isYHalfSpr", SAKEXE, "g_isYHalfSpr")); // = ?;
extern int& g_texLenDivFactor = VTOR<int>(SymDB::Add("g_texLenDivFactor", SAKEXE, "g_texLenDivFactor")); // = 1;
extern const char*& whisperWindowOpenSound = VTOR<const char*>(SymDB::Add("whisperWindowOpenSound", SAKEXE, "whisperWindowOpenSound")); // = "..\\..\\BGM\\Msg_NewMsg.wav";
extern CInsultFilter& g_insultFilter = VTOR<CInsultFilter>(SymDB::Add("g_insultFilter", SAKEXE, "g_insultFilter")); // = ?;
float& g_zOffset = VTOR<float>(SymDB::Add("g_zOffset", SAKEXE, "g_zOffset")); // = 0.000009f;
float& g_zHover = VTOR<float>(SymDB::Add("g_zHover", SAKEXE, "g_zHover")); // = 0.000036f;
float& g_avgPixelRatio = VTOR<float>(SymDB::Add("g_avgPixelRatio", SAKEXE, "g_avgPixelRatio")); // = 1.34f;
float& g_gradient = VTOR<float>(SymDB::Add("g_gradient", SAKEXE, "g_gradient")); // = 0.16f;
float& g_slope = VTOR<float>(SymDB::Add("g_slope", SAKEXE, "g_slope")); // = 0.16f;
float& g_shadowSlope = VTOR<float>(SymDB::Add("g_shadowSlope", SAKEXE, "g_shadowSlope")); // = 0.16f;
int& g_bOldServer = VTOR<int>(SymDB::Add("g_bOldServer", SAKEXE, "g_bOldServer")); // = ?;
int& g_isGoodSkillHanging = VTOR<int>(SymDB::Add("g_isGoodSkillHanging", SAKEXE, "g_isGoodSkillHanging")); // = ?;
float& CLOSE_DIST = VTOR<float>(SymDB::Add("CLOSE_DIST", SAKEXE, "CLOSE_DIST")); // = 230.0f;
float& FAR_DIST = VTOR<float>(SymDB::Add("FAR_DIST", SAKEXE, "FAR_DIST")); // = 400.0f;
float& AVG_DIST = VTOR<float>(SymDB::Add("AVG_DIST", SAKEXE, "AVG_DIST")); // = 300.0f;
float& g_viewLatitude = VTOR<float>(SymDB::Add("g_viewLatitude", SAKEXE, "g_viewLatitude")); // = -45.0f;
float& g_viewDistance = VTOR<float>(SymDB::Add("g_viewDistance", SAKEXE, "g_viewDistance")); // = 300.0f;
float& g_indoorViewLatitude = VTOR<float>(SymDB::Add("g_indoorViewLatitude", SAKEXE, "g_indoorViewLatitude")); // = -45.0f;
float& g_indoorViewDistance = VTOR<float>(SymDB::Add("g_indoorViewDistance", SAKEXE, "g_indoorViewDistance")); // = 300.0f;
float& g_outdoorViewLatitude = VTOR<float>(SymDB::Add("g_outdoorViewLatitude", SAKEXE, "g_outdoorViewLatitude")); // = -45.0f;
float& g_outdoorViewDistance = VTOR<float>(SymDB::Add("g_outdoorViewDistance", SAKEXE, "g_outdoorViewDistance")); // = 300.0f;
CTipOfTheDay& g_tipOfTheDay = VTOR<CTipOfTheDay>(SymDB::Add("g_tipOfTheDay", SAKEXE, "g_tipOfTheDay")); // = ?;
int& g_isBlackWorld = VTOR<int>(SymDB::Add("g_isBlackWorld", SAKEXE, "g_isBlackWorld")); // = ?;
RECT& g_drawRect = VTOR<RECT>(SymDB::Add("g_drawRect", SAKEXE, "g_drawRect")); // = ?;
matrix& _IdentityMatrix = VTOR<matrix>(SymDB::Add("_IdentityMatrix", SAKEXE, "_IdentityMatrix")); // = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 };
int& g_shiftKeyPressed = VTOR<int>(SymDB::Add("g_shiftKeyPressed", SAKEXE, "g_shiftKeyPressed")); // = ?;
int& MAX_ATTACKMT = VTOR<int>(SymDB::Add("MAX_ATTACKMT", SAKEXE, "MAX_ATTACKMT")); // = 432;
DWORD& EXPIRETIME = VTOR<DWORD>(SymDB::Add("EXPIRETIME", SAKEXE, "EXPIRETIME")); // = 15000;


void Trace(const char* str, ...) // line 66 (common.h)
{
}


void ErrorMsg(const char* msg) // line 552-555 (Mode.cpp)
{
	GDIFlip();
	MessageBoxA(g_hMainWnd, msg, "Error", MB_OK);
}


void ErrorMsg(int num) // line 558-564 (Mode.cpp)
{
	char buf[80];
	wsprintfA(buf, "%d\n", num); //FIXME: deprecated API

	GDIFlip();
	MessageBoxA(g_hMainWnd, buf, "Error", MB_OK);
}
