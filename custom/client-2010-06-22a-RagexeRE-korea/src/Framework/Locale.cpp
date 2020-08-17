#include "Base/File.h"
#include "Base/FileMgr.h"
#include "Base/Res.h"
#include "Base/Util.h" // MakeStringLower()
#include "Base/Xml.h"
#include "Framework/Locale.h"
#include "CommonObject.h"
#include "Weather.h"
#include "Enum.h"
#include "Globals.h"


hook_func<void (__cdecl *)(const char* clientInfo)> _InitClientInfo("InitClientInfo");
void __cdecl InitClientInfo(const char* clientInfo)
{
	return (_InitClientInfo)(clientInfo);
}


hook_func<void (__cdecl *)()> _InitDefaultServiceType("InitDefaultServiceType");
void __cdecl InitDefaultServiceType()
{
	return _InitDefaultServiceType();

	XMLElement* clientinfo = document.XMLDocument::GetRootElement()->XMLElement::FindChild("clientinfo");
	if( clientinfo != NULL )
		SetOption(clientinfo);

	if( CFile::IsFileExist("etcinfo.txt") )
	{
		CommonObject s_obj;
		s_loadingScreenList.clear();

		mystd::vector<const char*> pCharList;
		s_obj.CommonObject::TokenFileToPCharList(pCharList, "etcinfo.txt", 0);

		for( mystd::vector<const char*>::const_iterator it = pCharList.begin(); it != pCharList.end(); ++it )
		{
			if( strcmp(*(it + 0), "loadingscreen") == 0 )
			{
				int count = atoi(*(it + 1));
				if( count > 0 )
					InitDefaultLoadingScreen(count);
				//FIXME: loop only advances iterator by 1 field
			}
			else
			if( strcmp(*(it + 0), "event") == 0 )
			{
				int event = atoi(*(it + 1));
				if( event > 0 )
					g_fileMgr.CFileMgr::AddPak("event.grf");
				//FIXME: loop only advances iterator by 1 field
			}
			else
			if( strcmp(*(it + 0), "weather") == 0 )
			{
				mystd::string map = *(it + 1);
				mystd::string weather = *(it + 2);
				MakeStringLower(map);
				MakeStringLower(weather);
				g_Weather.CWeather::AddScript(map, weather);
				++it;
			}
		}
	}

	if( s_loadingScreenList.size() == 0 )
		InitDefaultLoadingScreen(0);
}


hook_func<void (__cdecl *)(XMLElement* clientinfo)> _SetOption("SetOption");
void __cdecl SetOption(XMLElement* clientinfo)
{
	return _SetOption(clientinfo);

	//TODO
}


hook_func<void (__cdecl *)(int count)> _InitDefaultLoadingScreen("InitDefaultLoadingScreen");
void __cdecl InitDefaultLoadingScreen(int count)
{
	return _InitDefaultLoadingScreen(count);

	if( count == 0 )
	{
		switch( g_serviceType )
		{
		case ServiceKorea:      count = 7; break;
		case ServiceAmerica:    count = 12; break;
		case ServiceChina:      count = 4; break;
		case ServiceThai:       count = 8; break;
		case ServiceIndonesia:  count = 9; break;
		case ServicePhilippine: count = 6; break;
		default:                count = 1; break;
		}
	}

	for( int i = 0; i < count; ++i )
	{
		char temp[256];
		sprintf(temp, "유저인터페이스\\loading%02d.jpg", i);
		if( g_resMgr().CResMgr::IsExist(temp) )
			s_loadingScreenList.push_back(temp);
	}
}


hook_func<bool (__cdecl *)(unsigned long aid)> _IsNameYellow("IsNameYellow");
bool __cdecl IsNameYellow(unsigned long aid)
{
	return (_IsNameYellow)(aid);
}


hook_func<bool (__cdecl *)(unsigned long aid)> _IsGravityAid("IsGravityAid");
bool __cdecl IsGravityAid(unsigned long aid)
{
	return (_IsGravityAid)(aid);
}
