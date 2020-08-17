#include "Globals.h"
#include "Language.h"
#include "Locale.h"
#include "Base/File.h"
#include "Base/RegMgr.h"


hook_func<void (__cdecl *)(const char* clientInfo)> _InitClientInfo(SAKEXE, "InitClientInfo");
void __cdecl InitClientInfo(const char* clientInfo) // line 126
{
	return (_InitClientInfo)(clientInfo);

	CFile fp;
	if( fp.CFile::Open(clientInfo, 0) )
		document.XMLDocument::ReadDocument((const char*)fp.GetCurBuf(0), (const char*)fp.GetCurBuf(fp.GetLength()));

	InitDefaultServiceType();
	InitDefaultClientInfo(); //inlined

	if( g_serviceType == ServiceKorea )
	{
		NameBalloonShorten = true;
		NameBalloonfontBold = true;
		NameBalloonfontSize = 13;
	}
	else
	{
		NameBalloonShorten = false;
		NameBalloonfontBold = false;
		NameBalloonfontSize = 12;
	}

	if( g_serviceType == ServiceAmerica && g_serverType == ServerSakray )
		g_licence = "..\\slicence.txt";
	else
		g_licence = "..\\licence.txt";

	if( g_serviceType == ServiceChina && g_serverType != ServerSakray )
	{
		g_regPath = "Software\\Gravity Soft\\RoClient";
		WINDOW_NAME = "仙境传说";

		if( g_serverType == ServerSakray )
		{
			PATCH_CLIENT = "SakClient.exe";
			PATCH_UP = "Sakup.exe";
			PLEASE_EXCUTE_LAUNCHER = "Please run SakClient.exe";
		}
		else
		{
			PATCH_CLIENT = "RoClient.exe";
			PATCH_UP = "Patchup.exe";
			PLEASE_EXCUTE_LAUNCHER = "Please run RoClient.exe";
		}

		RegKey RunCount;
		RunCount.RegKey::open(HKEY_LOCAL_MACHINE, "Software\\Gravity Soft\\RoClient");

		int dwRunCount;
		if( RunCount.RegKey::queryValue("RunCount", REG_DWORD, (LPBYTE)&dwRunCount, sizeof(dwRunCount)) )
		{
			++dwRunCount;

			if( dwRunCount > 200 )
				g_sendUDPPacket = true;
		}
		else
		{
			dwRunCount = 1;
		}

		RunCount.RegKey::setValue("RunCount", REG_DWORD, (LPBYTE)&dwRunCount, sizeof(dwRunCount));
	}
	else
	{
		g_regPath = "Software\\Gravity Soft\\Ragnarok";
		WINDOW_NAME = "Ragnarok";

		if( g_serverType == ServerSakray )
		{
			PATCH_CLIENT = "sakray.exe";
			PATCH_UP = "Sakup.exe";
			PLEASE_EXCUTE_LAUNCHER = "Please run sakray.exe";
		}
		else
		if( g_serverType == ServerLocal )
		{
			PATCH_CLIENT = "RagIndoor.exe";
			PATCH_UP = "Indoorup.exe";
			PLEASE_EXCUTE_LAUNCHER = "Please run RagIndoor.exe";
		}
		else
		{
			PATCH_CLIENT = "Ragnarok.exe";
			PATCH_UP = "Patchup.exe";
			PLEASE_EXCUTE_LAUNCHER = "Please run Ragnarok.exe";
		}
	}
}


hook_func<void (__cdecl *)(void)> _InitDefaultServiceType(SAKEXE, "InitDefaultServiceType");
void __cdecl InitDefaultServiceType(void) // line 220
{
	return (_InitDefaultServiceType)();

	XMLElement* clientinfo = document.XMLDocument::GetRootElement()->XMLElement::FindChild("clientinfo");
	if( clientinfo == NULL )
		ErrorMsg("No ClientInfo File !!");
	else
	{
		// load servicetype
		XMLElement* v3 = clientinfo->XMLElement::FindChild("servicetype");
		if( v3 == NULL )
			ErrorMsg("No ServiceType !!");
		else
		if( v3->XMLElement::GetContents() == "korea" )
			g_serviceType = ServiceKorea;
		else
		if( v3->XMLElement::GetContents() == "america" )
			g_serviceType = ServiceAmerica;
		else
		if( v3->XMLElement::GetContents() == "japan" )
			g_serviceType = ServiceJapan;
		else
		if( v3->XMLElement::GetContents() == "china" )
			g_serviceType = ServiceChina;
		else
		if( v3->XMLElement::GetContents() == "taiwan" )
			g_serviceType = ServiceTaiwan;
		else
		if( v3->XMLElement::GetContents() == "thai" )
			g_serviceType = ServiceThai;
		else
		if( v3->XMLElement::GetContents() == "indonesia" )
			g_serviceType = ServiceIndonesia;
		else
		if( v3->XMLElement::GetContents() == "philippine" )
			g_serviceType = ServicePhilippine;
		else
		if( v3->XMLElement::GetContents() == "malaysia" )
			g_serviceType = ServiceMalaysia;
		else
		if( v3->XMLElement::GetContents() == "singapore" )
			g_serviceType = ServiceSingapore;
		else
		if( v3->XMLElement::GetContents() == "germany" )
			g_serviceType = ServiceGermany;
		else
			ErrorMsg("ServiceType Error !!");

		// load servertype
		XMLElement* v16 = clientinfo->XMLElement::FindChild("servertype");
		if( v16 == NULL )
			ErrorMsg("No ServerType !!");
		else
		if( v16->XMLElement::GetContents() == "primary" )
			g_serverType = ServerPrimary;
		else
		if( v16->XMLElement::GetContents() == "sakray" )
			g_serverType = ServerSakray;
		else
		if( v16->XMLElement::GetContents() == "local" )
			g_serverType = ServerLocal;
		else
			ErrorMsg("ServerType Error !!");

		// load various flags
		if( clientinfo->XMLElement::FindChild("hideaccountlist") )
			g_hideAccountList = true;

		if( clientinfo->XMLElement::FindChild("passwordencrypt") )
			g_passwordEncrypt = true;

		if( clientinfo->XMLElement::FindChild("passwordencrypt2") )
		{
			g_passwordEncrypt = true;
			g_passwordEncrypt2 = true;
		}

		if( clientinfo->XMLElement::FindChild("extendedslot") )
			g_extended_slot = true;

		if( clientinfo->XMLElement::FindChild("readfolder") )
			g_readFolderFirst = true;

		// load user-defined loading screens
		XMLElement* v21 = clientinfo->XMLElement::FindChild("loading");
		if( v21 != NULL )
		{
			for( XMLElement* i = v21->XMLElement::FindChild("image"); i != NULL; i = i->XMLElement::FindNext("image") )
			{
				char temp[256];
				sprintf(temp, "유저인터페이스\\%s", i->XMLElement::GetContents().c_str());
				s_loadingScreenList.push_back(temp);
			}
		}
	}

	if( s_loadingScreenList.size() == 0 )
		InitDefaultLoadingScreen();
}


hook_func<void (__cdecl *)(void)> _InitDefaultClientInfo(SAKEXE, "InitDefaultClientInfo");
void __cdecl InitDefaultClientInfo(void) // line 313
{
	return (_InitDefaultClientInfo)();

	switch( g_serviceType )
	{
	case ServiceKorea:
		SelectKoreaClientInfo();
		break;
	case ServiceAmerica:
	case ServiceJapan:
	case ServiceChina:
	case ServiceTaiwan:
	case ServiceThai:
	case ServiceIndonesia:
	case ServicePhilippine:
	case ServiceMalaysia:
	case ServiceSingapore:
	case ServiceGermany:
		SelectClientInfo(0);
		break;
	default:
		ErrorMsg("Unknown ServiceType !!!");
		break;
	}

	InitLanguage();
}


hook_func<void (__cdecl *)(void)> _SelectKoreaClientInfo(SAKEXE, "SelectKoreaClientInfo");
void __cdecl SelectKoreaClientInfo(void) // line 345
{
	return (_SelectKoreaClientInfo)();

	g_accountPort = "6900";
	g_regstrationWeb = "http://www.ragnarok.co.kr";
	g_extended_slot = true;

	switch( g_serverType )
	{
	case ServerPrimary:
		g_accountAddr = "211.172.247.192";
		g_version = 19;
		s_dwAdminAID.assign(&dwAdminAID[0], &dwAdminAID[32]);
		s_dwYellowAID.assign(&dwYellowAID[0], &dwYellowAID[35]);
		break;
	case ServerSakray:
		g_accountAddr = "211.172.247.192";
		g_version = 29;
		s_dwAdminAID.assign(&dwAdminAID[0], &dwAdminAID[32]);
		s_dwYellowAID.assign(&dwYellowAID[0], &dwYellowAID[35]);
		break;
	case ServerLocal:
		g_version = 14;
		g_accountAddr = "192.168.0.100";
		s_dwAdminAID.assign(&dwAdminAID[0], &dwAdminAID[32]);
		s_dwYellowAID.assign(&dwYellowAID[0], &dwYellowAID[35]);
		break;
	case ServerInstantEvent:
		g_accountPort = "6900";
		g_accountAddr = "211.172.247.110";
		g_version = 29;
		s_dwAdminAID.assign(&dwAdminAID[0], &dwAdminAID[32]);
		s_dwYellowAID.assign(&dwYellowAID[0], &dwYellowAID[35]);
	default:
		break;
	}
}


hook_func<void (__cdecl *)(int number)> _SelectClientInfo(SAKEXE, "SelectClientInfo");
void __cdecl SelectClientInfo(int number) // line 379
{
	return (_SelectClientInfo)(number);

	// get root
	XMLElement* info = document.XMLDocument::GetRootElement()->XMLElement::FindChild("clientinfo");
	if( info == NULL )
		return;

	// find the 'number'-th <connection> element
	XMLElement* conn;
	for( conn = info->XMLElement::FindChild("connection"); conn != NULL && number != 0; conn = conn->XMLElement::FindNext("connection") )
		number--;
	if( conn == NULL )
		return;

	XMLElement* address = conn->XMLElement::FindChild("address");
	if( address != NULL )
		g_accountAddr = address->XMLElement::GetContents().c_str();

	XMLElement* port = conn->XMLElement::FindChild("port");
	if( port != NULL )
		g_accountPort = port->XMLElement::GetContents().c_str();

	XMLElement* version = conn->XMLElement::FindChild("version");
	if( version != NULL )
		g_version = atoi(version->XMLElement::GetContents().c_str());

	XMLElement* langtype = conn->XMLElement::FindChild("langtype");
	if( langtype != NULL )
		g_serviceType = (ServiceType)atoi(langtype->XMLElement::GetContents().c_str());

	XMLElement* web = conn->XMLElement::FindChild("registrationweb");
	if( web != NULL )
		g_regstrationWeb = web->XMLElement::GetContents().c_str();

	s_dwAdminAID.clear();
	XMLElement* aid = conn->XMLElement::FindChild("aid");
	if( aid != NULL )
	{
		for( XMLElement* admin = aid->XMLElement::FindChild("admin"); admin != NULL; admin = admin->XMLElement::FindNext("admin") )
		{
			number = atoi(admin->XMLElement::GetContents().c_str());
			s_dwAdminAID.push_back(number);
		}

		std::sort(s_dwAdminAID.begin(), s_dwAdminAID.end());
	}

	s_dwYellowAID.clear();
	XMLElement* yellow = conn->XMLElement::FindChild("yellow");
	if( yellow != NULL )
	{
		for( XMLElement* admin = yellow->XMLElement::FindChild("admin"); admin != NULL; admin = admin->XMLElement::FindNext("admin") )
		{
			number = atoi(admin->XMLElement::GetContents().c_str());
			s_dwYellowAID.push_back(number);
		}

		std::sort(s_dwYellowAID.begin(), s_dwYellowAID.end());
	}

	InitLanguage();
}


hook_func<void (__cdecl *)(void)> _InitDefaultLoadingScreen(SAKEXE, "InitDefaultLoadingScreen");
void __cdecl InitDefaultLoadingScreen(void) // line 431
{
	int count;

	switch( g_serviceType )
	{
	case 0: count = 8; break;
	case 1: count = 12; break;
	case 3: count = 4; break;
	case 5: count = 8; break;
	case 6: count = 9; break;
	case 7: count = 6; break;
	default: count = 1; break;
	}

	for( int i = 0; i < count; ++i )
	{
		char temp[256];
		sprintf(temp, "유저인터페이스\\loading%02d.jpg", i);
		s_loadingScreenList.push_back(temp);
	}
}


hook_func<void (__cdecl *)(void)> _InitLanguage(SAKEXE, "InitLanguage");
void __cdecl InitLanguage(void) // line 467
{
	return (_InitLanguage)();

	static CLanguage language;
	static CLanguageTC languageTC;
	static CLanguageTH languageTH;

	switch( g_serviceType )
	{
	case ServiceKorea:
		g_languageType = LanguageKorean;
		g_codePage = 949;
		g_language = &language;
		return;
	case ServiceJapan:
		g_languageType = LanguageJapanese;
		g_codePage = 932;
		g_language = &language;
		return;
	case ServiceChina:
		g_languageType = LanguageSimplifiedChinese;
		g_codePage = 936;
		g_language = &languageTC;
		return;
	case ServiceTaiwan:
		g_languageType = LanguageTraditionalChinese;
		g_codePage = 950;
		g_language = &languageTC;
		return;
	case ServiceThai:
		g_languageType = LanguageThai;
		g_codePage = 874;
		g_language = &languageTH;
		return;
	case ServiceAmerica:
	case ServiceIndonesia:
	case ServicePhilippine:
	case ServiceMalaysia:
	case ServiceSingapore:
		break;
	case ServiceGermany:
		g_multiLang = true;
		break;
	default:
		ErrorMsg("no language setting !!!");
		break;
	}

	g_languageType = LanguageEnglish;
	g_codePage = 0;
	g_language = &language;
}


hook_func<XMLElement* (__cdecl *)(void)> _GetClientInfo(SAKEXE, "GetClientInfo");
XMLElement* __cdecl GetClientInfo(void) // line 539
{
	return (_GetClientInfo)();

	return document.GetRootElement()->XMLElement::FindChild("clientinfo");
}


hook_func<const char* (__cdecl *)(void)> _GetLicenceText(SAKEXE, "GetLicenceText");
const char* __cdecl GetLicenceText(void) // line 542
{
	return (_GetLicenceText)();

	//TODO
}


hook_func<bool (__cdecl *)(unsigned long aid)> _IsNameYellow(SAKEXE, "IsNameYellow");
bool __cdecl IsNameYellow(unsigned long aid) // line 560
{
	return (_IsNameYellow)(aid);

	return ( std::find(s_dwYellowAID.begin(), s_dwYellowAID.end(), aid) != s_dwYellowAID.end() );
}


hook_func<bool (__cdecl *)(unsigned long aid)> _IsGravityAid(SAKEXE, "IsGravityAid");
bool __cdecl IsGravityAid(unsigned long aid) // line 565
{
	return (_IsGravityAid)(aid);

	return ( std::find(s_dwAdminAID.begin(), s_dwAdminAID.end(), aid) != s_dwAdminAID.end() );
}
