#include "CommonObject.h"
#include "Enum.h"
#include "Globals.h"
#include "Weather.h"
#include "WinMain.h"
#include "Base/File.h"
#include "Base/FileMgr.h"
#include "Base/Res.h"
#include "Base/Util.h" // MakeStringLower()
#include "Base/Xml.h"
#include "Framework/Language.h"
#include "Framework/Locale.h"
#include "Window/UIWindowMgr.h"


/// globals
bool g_isSetOptionDone;


static DWORD dwAdminAID[] = {
	 100118, 2750446, 2750961, 2750963, 2750964,
	2750966, 2750967, 2750969, 2750971, 2750972,
	2750973, 3143679, 3143680, 3143681, 3143682,
	3143684, 3143685, 3143686, 3143687, 3143688,
	3143689, 3143690, 3143691, 3143692, 3143693,
	3143695, 3143696, 3143699, 3143700, 3143701,
	3143702, 2919557, 3304372, 3376608, 4663634,
	4663643, 4663644, 4663633, 4663642, 4663649,
	4663632, 4663638, 4663645, 4841414, 4841415,
	4841416, 4841422, 5046468, 5046469, 5046470,
	5046471, 5046472, 5046473, 5046474, 5046475,
	5046476, 5046477, 5046478, 5046479, 5046480,
};

static DWORD dwYellowAID[] = {
	 100118, 2750446, 2750961, 2750963, 2750964,
	2750966, 2750967, 2750969, 2750971, 2750972,
	2750973, 3143679, 3143680, 3143681, 3143682,
	3143684, 3143685, 3143686, 3143687, 3143688,
	3143689, 3143690, 3143691, 3143692, 3143693,
	3143695, 3143696, 3143699, 3143700, 3143701,
	3143702, 2919557, 3304372, 3304363, 3304378,
	3304372, 3376608, 4663634, 4663643, 4663644,
	4663633, 4663642, 4663649, 4663632, 4663638,
	4663645, 4841414, 4841415, 4841416, 4841422,
	5046468, 5046469, 5046470, 5046471, 5046472,
	5046473, 5046474, 5046475, 5046476, 5046477,
	5046478, 5046479, 5046480,
};


void InitClientInfo(const char* clientInfo)
{
	CFile fp;
	if( fp.CFile::Open(clientInfo, 0) )
	{
		document.XMLDocument::ReadDocument((const char*)fp.GetCurBuf(0), (const char*)fp.GetCurBuf(fp.GetLength()));
		fp.CFile::Close();
	}

	InitDefaultServiceType();
	InitDefaultClientInfo();

	if( g_serviceType == ServiceKorea || g_serviceType == ServiceIndonesia )
	{
		NameBalloonfontSize = 13;
		NameBalloonShorten = true;
		NameBalloonfontBold = true;
	}
	else
	{
		NameBalloonfontSize = 12;
		NameBalloonShorten = false;
		NameBalloonfontBold = false;
	}

	SYSTEMTIME sTime;
	GetLocalTime(&sTime);

	g_licence = "..\\licence.txt";
	title_random = sTime.wSecond % 4;
	g_regPath = "Software\\Gravity Soft\\Ragnarok";
	WINDOW_NAME = "Ragnarok";

	switch( g_serverType )
	{
	case ServerSakray:
	default:
		PATCH_CLIENT = "Ragnarok_RE.exe";
		PATCH_UP = "Patchup_RE.exe";
		PLEASE_EXCUTE_LAUNCHER = "Please run Ragnarok_RE.exe";
	break;
	case ServerLocal:
		PATCH_CLIENT = "RagIndoor.exe";
		PATCH_UP = "Indoorup.exe";
		PLEASE_EXCUTE_LAUNCHER = "Please run RagIndoor.exe";
	break;
	case ServerInstantEvent:
		PATCH_CLIENT = "RagGuild.exe";
		PATCH_UP = "Guildup.exe";
		PLEASE_EXCUTE_LAUNCHER = "Please run RagGuild.exe";
	break;
	};
}


void SetOption(XMLElement* clientinfo) // (457-557)
{
	XMLElement* servicetype = clientinfo->XMLElement::FindChild("servicetype");
	if( servicetype != NULL )
	{
		if     ( servicetype->XMLElement::GetContents() == "korea"      ) g_serviceType = ServiceKorea;
		else if( servicetype->XMLElement::GetContents() == "america"    ) g_serviceType = ServiceAmerica;
		else if( servicetype->XMLElement::GetContents() == "japan"      ) g_serviceType = ServiceJapan;
		else if( servicetype->XMLElement::GetContents() == "china"      ) g_serviceType = ServiceChina;
		else if( servicetype->XMLElement::GetContents() == "taiwan"     ) g_serviceType = ServiceTaiwan;
		else if( servicetype->XMLElement::GetContents() == "thai"       ) g_serviceType = ServiceThai;
		else if( servicetype->XMLElement::GetContents() == "indonesia"  ) g_serviceType = ServiceIndonesia;
		else if( servicetype->XMLElement::GetContents() == "philippine" ) g_serviceType = ServicePhilippine;
		else if( servicetype->XMLElement::GetContents() == "malaysia"   ) g_serviceType = ServiceMalaysia;
		else if( servicetype->XMLElement::GetContents() == "singapore"  ) g_serviceType = ServiceSingapore;
		else if( servicetype->XMLElement::GetContents() == "germany"    ) g_serviceType = ServiceGermany;
		else if( servicetype->XMLElement::GetContents() == "india"      ) g_serviceType = ServiceIndia;
		else if( servicetype->XMLElement::GetContents() == "brazil"     ) g_serviceType = ServiceBrazil;
		else if( servicetype->XMLElement::GetContents() == "australia"  ) g_serviceType = ServiceAustralia;
		else if( servicetype->XMLElement::GetContents() == "russia"     ) g_serviceType = ServiceRussia;
		else if( servicetype->XMLElement::GetContents() == "vietnam"    ) g_serviceType = ServiceVietnam;
//		else if( servicetype->XMLElement::GetContents() == "indoor"     ) g_serviceType = ServiceIndoor;
		else if( servicetype->XMLElement::GetContents() == "chile"      ) g_serviceType = ServiceChile;
		else if( servicetype->XMLElement::GetContents() == "france"     ) g_serviceType = ServiceFrance;
		else if( servicetype->XMLElement::GetContents() == "uae"        ) g_serviceType = ServiceArabic;
		else
		{
			ErrorMsg("ServiceType Error !!");
		}
	}
	else
	{
		if( !g_isSetOptionDone )
			ErrorMsg("No ServiceType !!");
	}

	XMLElement* servertype = clientinfo->XMLElement::FindChild("servertype");
	if( servertype != NULL )
	{
		if     ( servertype->XMLElement::GetContents() == "primary"      ) g_serverType = ServerPrimary;
		else if( servertype->XMLElement::GetContents() == "sakray"       ) g_serverType = ServerSakray;
		else if( servertype->XMLElement::GetContents() == "local"        ) g_serverType = ServerLocal;
//		else if( servertype->XMLElement::GetContents() == "instantevent" ) g_serverType = ServerInstantEvent;
//		else if( servertype->XMLElement::GetContents() == "pvp"          ) g_serverType = ServerPVP;
		else if( servertype->XMLElement::GetContents() == "pk"           ) g_serverType = ServerPK;
		else
		{
			ErrorMsg("ServerType Error !!");
		}
	}
	else
	{
		if( !g_isSetOptionDone )
			ErrorMsg("No ServerType !!");
	}

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

	XMLElement* loading = clientinfo->XMLElement::FindChild("loading");
	if( loading != NULL )
	{
		for( XMLElement* image = loading->XMLElement::FindChild("image"); image != NULL; image = image->XMLElement::FindNext("image") )
		{
			char temp[256];
			sprintf(temp, "유저인터페이스\\%s", image->XMLElement::GetContents().c_str());
			s_loadingScreenList.push_back(temp);
		}
	}

	XMLElement* viewhomepage = clientinfo->XMLElement::FindChild("viewhomepage");
	if( viewhomepage != NULL )
	{
		sprintf(g_windowMgr.m_viewHomePageUrl, "");
		sprintf(g_windowMgr.m_viewHomePageUrl, "%s", viewhomepage->XMLElement::GetContents().c_str());
	}

	g_isSetOptionDone = true;
}


void InitDefaultClientInfo()
{
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
	case ServiceIndia:
	case ServiceBrazil:
	case ServiceAustralia:
	case ServiceRussia:
	case ServiceVietnam:
	case ServiceChile:
	case ServiceFrance:
	case ServiceArabic:
		SelectClientInfo(0);
	break;
	default:
		ErrorMsg("Unknown ServiceType !!!");
	break;
	};

	InitLanguage();
}


void InitDefaultServiceType()
{
	XMLElement* clientinfo = document.XMLDocument::GetRootElement()->XMLElement::FindChild("clientinfo");
	if( clientinfo != NULL )
		SetOption(clientinfo);

	if( CFile::IsFileExist("etcinfo.txt") )
	{
		CommonObject s_obj;
		s_loadingScreenList.clear();

		mystd::vector<const char*> pCharList;
		s_obj.CommonObject::TokenFileToPCharList(pCharList, "etcinfo.txt", 0);

		for( mystd::vector<const char*>::const_iterator iter = pCharList.begin(); iter != pCharList.end(); ++iter )
		{
			if( strcmp(*iter, "loadingscreen") == 0 )
			{
				int count = atoi(*(iter + 1));
				if( count > 0 )
					InitDefaultLoadingScreen(count);
//				++iter; //FIXME
			}
			else
			if( strcmp(*iter, "event") == 0 )
			{
				int event = atoi(*(iter + 1));
				if( event > 0 )
					g_fileMgr.CFileMgr::AddPak("event.grf");
//				++iter; //FIXME
			}
			else
			if( strcmp(*iter, "weather") == 0 )
			{
				mystd::string map = *(iter + 1);
				mystd::string weather = *(iter + 2);
				MakeStringLower(map);
				MakeStringLower(weather);
				g_Weather.CWeather::AddScript(map, weather);
				++iter;
				++iter;
			}
		}
	}

	if( s_loadingScreenList.size() == 0 )
		InitDefaultLoadingScreen(0);
}


void SelectClientInfo(int number)
{
	// get root
	XMLElement* clientinfo = document.XMLDocument::FindElement("clientinfo");
	if( clientinfo == NULL )
		return;

	// find the 'number'-th <connection> element
	XMLElement* connection = clientinfo->XMLElement::FindChild("connection");
	for( int i = 0; i < number && connection != NULL; ++i )
		connection = connection->XMLElement::FindNext("connection");
	if( connection == NULL )
		return;

	SetOption(connection);

	XMLElement* address = connection->XMLElement::FindChild("address");
	if( address != NULL )
		g_accountAddr = address->XMLElement::GetContents().c_str();

	XMLElement* port = connection->XMLElement::FindChild("port");
	if( port != NULL )
		g_accountPort = port->XMLElement::GetContents().c_str();

	XMLElement* version = connection->XMLElement::FindChild("version");
	if( version != NULL )
		g_version = atoi(version->XMLElement::GetContents().c_str());

	XMLElement* langtype = connection->XMLElement::FindChild("langtype");
	if( langtype != NULL )
		g_serviceType = (ServiceType)atoi(langtype->XMLElement::GetContents().c_str());

	XMLElement* registrationweb = connection->XMLElement::FindChild("registrationweb");
	if( registrationweb != NULL )
		g_regstrationWeb = registrationweb->XMLElement::GetContents().c_str();

	s_dwAdminAID.clear();
	XMLElement* aid = connection->XMLElement::FindChild("aid");
	if( aid != NULL )
	{
		for( XMLElement* admin = aid->XMLElement::FindChild("admin"); admin != NULL; admin = admin->XMLElement::FindNext("admin") )
			s_dwAdminAID.push_back(atoi(admin->XMLElement::GetContents().c_str()));

		std::sort(s_dwAdminAID.begin(), s_dwAdminAID.end());
	}

	s_dwYellowAID.clear();
	XMLElement* yellow = connection->XMLElement::FindChild("yellow");
	if( yellow != NULL )
	{
		for( XMLElement* admin = yellow->XMLElement::FindChild("admin"); admin != NULL; admin = admin->XMLElement::FindNext("admin") )
			s_dwYellowAID.push_back(atoi(admin->XMLElement::GetContents().c_str()));

		std::sort(s_dwYellowAID.begin(), s_dwYellowAID.end());
	}
	else
	{
		s_dwYellowAID.assign(s_dwAdminAID.begin(), s_dwAdminAID.end());
	}

	InitLanguage();
}


void SelectClientInfo2(int number, int number2)
{
	// get root
	XMLElement* clientinfo = document.XMLDocument::FindElement("clientinfo");
	if( clientinfo == NULL )
		return;

	// find the 'number'-th <connection> element
	XMLElement* connection = clientinfo->XMLElement::FindChild("connection");
	for( int i = 0; i < number && connection != NULL; ++i )
		connection = connection->XMLElement::FindNext("connection");
	if( connection == NULL )
		return;

	// find the 'number2'-th <subconnection> element
	XMLElement* subconnection = connection->XMLElement::FindChild("subconnection");
	for( int i = 0; i < number2 && subconnection != NULL; ++i )
		subconnection = subconnection->XMLElement::FindNext("subconnection");
	if( subconnection != NULL )
		connection = subconnection; /// @custom: simplify code below

	SetOption(connection);

	XMLElement* address = connection->XMLElement::FindChild("address");
	if( address != NULL )
		g_accountAddr = address->XMLElement::GetContents().c_str();

	XMLElement* port = connection->XMLElement::FindChild("port");
	if( port != NULL )
		g_accountPort = port->XMLElement::GetContents().c_str();

	XMLElement* version = connection->XMLElement::FindChild("version");
	if( version != NULL )
		g_version = atoi(version->XMLElement::GetContents().c_str());

	XMLElement* langtype = connection->XMLElement::FindChild("langtype");
	if( langtype != NULL )
		g_serviceType = (ServiceType)atoi(langtype->XMLElement::GetContents().c_str());

	XMLElement* registrationweb = connection->XMLElement::FindChild("registrationweb");
	if( registrationweb != NULL )
		g_regstrationWeb = registrationweb->XMLElement::GetContents().c_str();

	s_dwAdminAID.clear();
	XMLElement* aid = connection->XMLElement::FindChild("aid");
	if( aid != NULL )
	{
		for( XMLElement* admin = aid->XMLElement::FindChild("admin"); admin != NULL; admin = admin->XMLElement::FindNext("admin") )
			s_dwAdminAID.push_back(atoi(admin->XMLElement::GetContents().c_str()));

		std::sort(s_dwAdminAID.begin(), s_dwAdminAID.end());
	}

	s_dwYellowAID.clear();
	XMLElement* yellow = connection->XMLElement::FindChild("yellow");
	if( yellow != NULL )
	{
		for( XMLElement* admin = yellow->XMLElement::FindChild("admin"); admin != NULL; admin = admin->XMLElement::FindNext("admin") )
			s_dwYellowAID.push_back(atoi(admin->XMLElement::GetContents().c_str()));

		std::sort(s_dwYellowAID.begin(), s_dwYellowAID.end());
	}
	else
	{
		s_dwYellowAID.assign(s_dwAdminAID.begin(), s_dwAdminAID.end());
	}

	InitLanguage();
}


hook_func<void (__cdecl*)()> _InitLanguage("InitLanguage");
void InitLanguage()
{
	return _InitLanguage(); //TODO
/*
	static CLanguage language;
	static CLanguageTC languageTC;
	static CLanguageTH anguageTH;
	static CLanguageARB languageARB;

	switch( g_serviceType )
	{
	case ServiceKorea:
		g_languageType = LanguageKorean;
		g_codePage = 949; // UHC
		g_language = &language;
	break;
	case ServiceJapan:
		g_languageType = LanguageJapanese;
		g_codePage = 932; // SHIFTJIS
		g_language = &language;
	break;
	case ServiceChina:
		g_languageType = LanguageSimplifiedChinese;
		g_codePage = 936; // GB2312
		g_language = &languageTC;
	break;
	case ServiceTaiwan:
		g_languageType = LanguageTraditionalChinese;
		g_codePage = 950; // BIG5
		g_language = &languageTC;
	break;
	case ServiceThai:
		g_languageType = LanguageThai;
		g_codePage = 874; // THAI
		g_language = &languageTH;
	break;
	case ServiceIndia:
		g_languageType = LanguageEnglish;
		g_codePage = CP_ACP;
		g_language = &language;
		g_multiLang = false;
	break;
 	case ServiceGermany:
	case ServiceAustralia:
		g_languageType = LanguageEnglish;
		g_codePage = CP_ACP;
		g_language = &language;
		g_multiLang = true;
	break;
	case ServiceRussia:
		g_languageType = LanguageEnglish;
		g_codePage = 1251; // CYRILLIC
		g_language = &language;
		g_multiLang = false;
	break;
	case ServiceVietnam:
		g_languageType = LanguageVietnam;
		g_codePage = 1258; // VIETNAM
		g_language = &language;
		g_multiLang = false;
	break;
	case ServiceChile:
		g_languageType = LanguageEnglish;
		g_codePage = 1145; // SPANISH
		g_language = &language;
		g_multiLang = false;
	break;
	case ServiceBrazil:
	case ServiceFrance:
		g_languageType = LanguagePortuguese;
		g_codePage = 1252; // WESTERN
		g_language = &language;
		g_multiLang = false;
	break;
	case ServiceArabic:
		g_languageType = LanguageArabic;
		g_codePage = 1256; // ARABIC
		g_language = &languageARB;
	break;
	case ServiceAmerica:
	case ServiceIndonesia:
	case ServicePhilippine:
	case ServiceMalaysia:
	case ServiceSingapore:
		g_languageType = LanguageEnglish;
		g_codePage = CP_ACP;
		g_language = &language;
	break;
	default:
		ErrorMsg("no language setting !!!");
		g_languageType = LanguageEnglish;
		g_codePage = CP_ACP;
		g_language = &language;
	break;
	};

	if( g_serverType == ServerInstantEvent )
		g_multiLang = true;
*/
}


void SelectKoreaClientInfo()
{
	g_accountPort = "6900";
	g_regstrationWeb = "http://www.ragnarok.co.kr";
	g_extended_slot = true;

	switch( g_serverType )
	{
	case ServerPrimary:
		g_accountAddr = "112.175.128.138";
		g_version = 29;
		s_dwAdminAID.assign(&dwAdminAID[0], &dwAdminAID[countof(dwAdminAID)]);
		s_dwYellowAID.assign(&dwYellowAID[0], &dwYellowAID[countof(dwYellowAID)]);
	break;
	case ServerSakray:
		g_accountAddr = "112.175.128.138";
		g_version = 29;
		s_dwAdminAID.assign(&dwAdminAID[0], &dwAdminAID[countof(dwAdminAID)]);
		s_dwYellowAID.assign(&dwYellowAID[0], &dwYellowAID[countof(dwYellowAID)]);
	break;
	case ServerLocal:
		g_version = 14;
		g_accountAddr = "192.168.20.170";
		s_dwAdminAID.assign(&dwAdminAID[0], &dwAdminAID[countof(dwAdminAID)]);
		s_dwYellowAID.assign(&dwYellowAID[0], &dwYellowAID[countof(dwYellowAID)]);
	break;
	case ServerInstantEvent:
		g_accountPort = "6900";
		g_accountAddr = "211.172.247.115";
		g_version = 29;
		s_dwAdminAID.assign(&dwAdminAID[0], &dwAdminAID[countof(dwAdminAID)]);
		s_dwYellowAID.assign(&dwYellowAID[0], &dwYellowAID[countof(dwYellowAID)]);
	break;
	};
}


void InitDefaultLoadingScreen(int count)
{
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
		};
	}

	for( int i = 0; i < count; ++i )
	{
		char temp[256];
		sprintf(temp, "유저인터페이스\\loading%02d.jpg", i);

		if( !g_resMgr().CResMgr::IsExist(temp) )
			continue;

		s_loadingScreenList.push_back(temp);
	}
}


const char* GetLicenceText()
{
	static mystd::string s_LicenceText;

	if( s_LicenceText.size() == 0 )
	{
		CFile fp;
		if( fp.CFile::Open(g_licence, 0) )
		{
			s_LicenceText.assign((const char*)fp.GetCurBuf(0), (const char*)fp.GetCurBuf(fp.GetLength()));
			fp.CFile::Close();
		}
		else
		{
			s_LicenceText.assign("No EULA text file. (licence.txt)");
		}
	}

	return s_LicenceText.c_str();
}


XMLElement* GetClientInfo()
{
	return document.XMLDocument::FindElement("clientinfo");
}


bool IsNameYellow(unsigned long aid)
{
	return ( std::find(s_dwYellowAID.begin(), s_dwYellowAID.end(), aid) != s_dwYellowAID.end() );
}


bool IsGravityAid(unsigned long aid)
{
	return ( std::find(s_dwAdminAID.begin(), s_dwAdminAID.end(), aid) != s_dwAdminAID.end() );
}


void SetTextType(bool isShorten, bool isBold) /// @custom
{
	if( g_serviceType == ServiceKorea || g_serviceType == ServiceIndonesia || g_serviceType == ServiceGermany || g_serviceType == ServiceBrazil )
	{
		NameBalloonShorten = isShorten;
		NameBalloonfontBold = isBold;
	}
}


int IsNameSpecific(unsigned long aid)
{
	if( g_serviceType == ServiceIndonesia )
	{
		switch( aid )
		{
		case 100001:
		case 100064:
		case 100065:
		case 100068:
		case 100075:
		case 100076:
		case 441470:
		case 441474:
		case 441487:
		case 540397:
			return 255;
		};
	}

	return 0;
}
