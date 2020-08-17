#include "Globals.h"
#include "ItemInfo.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Base/ResMgr.h"


// locals
static IdMsgString(& g_idMsgStrings)[MSI_LAST] = VTOR<IdMsgString[MSI_LAST]>(DetourFindFunction(SAKEXE, "g_idMsgStrings")); // = { ... }
static mystd::vector<const char*>& s_msgStrings = VTOR<mystd::vector<const char*>>(DetourFindFunction(SAKEXE, "s_msgStrings"));
static mystd::vector<const char*>& s_msgStringTable = VTOR<mystd::vector<const char*>>(DetourFindFunction(SAKEXE, "s_msgStringTable"));
static CommonObject& s_obj = VTOR<CommonObject>(DetourFindFunction(SAKEXE, "s_obj"));


const char* __cdecl MsgStr(MSGSTRINGID id)
{
	return s_msgStrings[id];
}


bool __cdecl IsEventAID(unsigned long Aid)
{
	if( g_serviceType == ServiceKorea )
	{
		if( Aid == 2919549
		 || Aid == 2919550
		 || Aid == 2919551
		 || Aid == 2919552
		 || Aid == 2919554 )
			return true;
	}

	return false;
}


const char* __cdecl GetMsgString(MSGSTRINGID id)
{
	if( id >= (int)s_msgStringTable.size() )
	{
		Trace("다음 한글 메시지에 해당하는 번역 스크립트가 없습니다.\n ID:%d,메시지명:%s", id, g_idMsgStrings[id].msg);
		return "NO MSG";
	}

	return s_msgStringTable[id];
}


void __cdecl InitMsgStrings()
{
	if( g_serviceType == ServiceKorea )
	{
		for( int id = 0; id < MSI_LAST; ++id )
			s_msgStrings[id] = g_idMsgStrings[id].msg;
	}
	else
	{
		s_obj.CommonObject::TokenFileToPCharList(s_msgStringTable, "msgStringTable.txt", false);

		for( int id = 0; id < MSI_LAST; ++id )
			s_msgStrings[id] = GetMsgString(MSGSTRINGID(id)); // inlined
	}
}


const char* __cdecl UIBmp(const char* uiBmpName)
{
	// byte-length of "유저인터페이스" in UHC codepage
	// NOTE: really poor solution, should look for path separator instead
	#define UI_DIR_NAME_LEN 15

	if( g_skinMgr.CSkinMgr::GetNumSkin() != 0 && g_skinMgr.CSkinMgr::GetCurrentSkinNum() != -1 && g_modeMgr.CModeMgr::GetGameMode() != NULL )
	{
		// try skin folder
		mystd::string skinFolder = g_skinMgr.CSkinMgr::GetSkinCurrentFolderName();

		static mystd::string skinRName;
		mystd::string tmpName = uiBmpName;

		skinRName = "";
		for( size_t i = UI_DIR_NAME_LEN; i < tmpName.size(); ++i ) //NOTE: adjusted to avoid integer underflow in official code
			skinRName += tmpName[i];

		g_skinMgr.CSkinMgr::ExtractFilesIfZipSkin();

		skinRName = skinFolder + skinRName;
		if( g_resMgr().CResMgr::IsExist(skinRName.c_str()) )
			return skinRName.c_str();
	}

	if( g_serviceType != ServiceKorea )
	{
		if( g_resMgr().CResMgr::IsExist(uiBmpName) )
			return uiBmpName;

		// try "UI" folder
		static mystd::string uiRName;
		mystd::string tmpName = uiBmpName;

		uiRName = "";
		for( size_t i = UI_DIR_NAME_LEN; i < tmpName.size(); ++i ) //NOTE: adjusted to avoid integer underflow in official code
			uiRName += tmpName[i];

		uiRName = "UI\\" + uiRName;
		if( g_resMgr().CResMgr::IsExist(uiRName.c_str()) )
			return uiRName.c_str();
	}

	return uiBmpName;
}


char* __cdecl DataTxtDecode(char* str)
{
	if( g_serviceType == ServiceKorea )
	{
		for( size_t i = 0; i < strlen(str); ++i )
		{
			BYTE b = (BYTE)str[i];

			if( b >= 'a' && b <= 'z' )
				b = 0xDB - b;

			if( b >= 'A' && b <= 'Z' )
				b = 0x9B - b;
			else
			if( b >= 0xB0 && b <= 0xBF )
				b = 0x6F - b;

			str[i] = b;
		}
	}

	return str;
}
