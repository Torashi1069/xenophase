#pragma once
#include "Enum.h"
#include "GuildInfo.h"
#include "RagEffect2.h"
#include "Session.h"
#include "Skin.h"
#include "SnapMgr.h"
#include "Struct.h"
#include "Base/Xml.h"
#include "3dLib/Device.h"
#include "3dLib/Renderer.h"
#include "3dLib/Texture.h"
#include "Device/Control.h"
#include "Device/Sound.h"
#include "Framework/Language.h"
#include "Movie/CBink.h"
#include "Resource/Bitmap.h"
#include "Resource/Model.h"
#include "Window/UIWindowMgr.h"
class CActorPickNode;
class CInsultFilter;
class CPathFinder;
class CTipOfTheDay;
struct matrix;


extern class CFileMgr& g_fileMgr;
extern HWND& g_hMainWnd;
extern C3dDevice& g_3dDevice;
extern char(& mutexKey)[8];
extern char(& g_baseDir)[128];
extern char(& g_baseDir3)[128];
extern bool& g_readFolderFirst;
extern XMLDocument& document;
extern enum ServiceType& g_serviceType;
extern enum ServerType& g_serverType;
extern enum LanguageType& g_languageType;
extern mystd::vector<mystd::string>& s_loadingScreenList;
extern bool& g_hideAccountList;
extern bool& g_passwordEncrypt;
extern bool& g_passwordEncrypt2;
extern bool& g_extended_slot;
extern int& g_version;
extern const char*& g_licence;
extern const char*& g_regPath;
extern const char*& g_optionPath;
extern const char*& WINDOW_NAME;
extern const char*& PATCH_CLIENT;
extern const char*& PATCH_UP;
extern const char*& PLEASE_EXCUTE_LAUNCHER;
extern const char*& g_accountAddr;
extern const char*& g_accountPort;
extern const char*& g_regstrationWeb;
extern DWORD(& dwAdminAID)[32];
extern DWORD(& dwYellowAID)[35];
extern mystd::vector<DWORD>& s_dwAdminAID;
extern mystd::vector<DWORD>& s_dwYellowAID;
extern bool& g_multiLang;
extern unsigned long& g_codePage;
extern CLanguage*& g_language;
extern bool& NameBalloonShorten;
extern bool& NameBalloonfontBold;
extern int& NameBalloonfontSize;
extern bool& g_sendUDPPacket;
extern CSession& g_session;
extern UIWindowMgr& g_windowMgr;
extern CSkinMgr& g_skinMgr;
extern class CModeMgr& g_modeMgr;
extern mystd::string& s_basicSkinName;
extern Registry2& g_registry;
extern unsigned long& g_soundMode;
extern CRenderer*& g_renderer;
extern class CRagConnection& g_connection;
extern CMouse& g_mouse;
extern int& g_loginStartMode;
extern CTexMgr& g_texMgr;
extern C3dGrannyBoneRes& g_GrannyBoneRes;
extern CBink& g_Bink;
extern BOOL& g_sysQuit;
extern GuildInfo& g_guildInfo;
extern int& g_isStopByLogin;
extern CSnapMgr& g_snapMgr;
extern CHARACTER_INFO& g_charInfo;
extern struct ServerAddress& g_charServerAddr;
extern struct ServerAddress& g_zoneServerAddr;
extern BOOL& g_mustPumpOutReceiveQueue;
extern unsigned char(& lower_table)[256];
extern vector3d& g_WorldUp;
extern CBitmapRes& CBitmapResInstance;
extern CBitmapRes& CBitmapResInstance2;
extern CBitmapRes& CBitmapResInstance3;
extern bool& g_pingLog;
extern unsigned long& g_pingLogStart;
extern mystd::list<unsigned long>& g_pingLogList;
extern class CFile& saveChatFp;
extern CMssVariables& g_mssVar;
extern vector3d& player_pos;
extern int(& durationTable)[1024];
extern int(& g_recentEffectId)[32];
extern float(& g_radTable)[722];
extern float(& g_sinTable)[722];
extern float(& g_cosTable)[722];
extern int& g_isAppActive;
extern int& g_activatedNow;
extern int& g_isLightMap;
extern bool& g_isSupportLMTex;
extern CWeather& g_Weather;
extern int& g_isSkipFrame;
extern CActorPickNode& g_actorPickNode;
extern mystd::vector<int>& stateId;
extern int& guildWndWidth;
extern int& guildWndHeight;
extern int& g_isSoundOn;
extern int& g_isFixedCamera;
extern const char*& boundaryText;
extern vector3d& lightDir;
extern vector3d& diffuseCol;
extern vector3d& ambientCol;
extern GroundAttrPosInfo& g_groundAttrPosInfo;
extern CPathFinder& g_pathFinder;
extern HANDLE& g_farModelThread;
extern HINSTANCE& g_hInstance;
extern int& WINDOW_WIDTH;
extern int& WINDOW_HEIGHT;
extern int& g_isVoodoo;
extern int& g_showTipsAtStartup;
extern int& g_isXHalfSpr;
extern int& g_isYHalfSpr;
extern int& g_texLenDivFactor;
extern const char*& whisperWindowOpenSound;
extern CInsultFilter& g_insultFilter;
extern float& g_zOffset;
extern float& g_zHover;
extern float& g_avgPixelRatio;
extern float& g_gradient;
extern float& g_slope;
extern float& g_shadowSlope;
extern int& g_bOldServer;
extern int& g_isGoodSkillHanging;
extern float& CLOSE_DIST;
extern float& FAR_DIST;
extern float& AVG_DIST;
extern float& g_viewLatitude;
extern float& g_viewDistance;
extern float& g_indoorViewLatitude;
extern float& g_indoorViewDistance;
extern float& g_outdoorViewLatitude;
extern float& g_outdoorViewDistance;
extern CTipOfTheDay& g_tipOfTheDay;
extern int& g_isBlackWorld;
extern RECT& g_drawRect;
extern matrix& _IdentityMatrix;
extern int& g_shiftKeyPressed;
extern int& MAX_ATTACKMT;
extern DWORD& EXPIRETIME;


// global functions
void Trace(const char* str, ...);
void ErrorMsg(const char* msg);
void ErrorMsg(int msg);
