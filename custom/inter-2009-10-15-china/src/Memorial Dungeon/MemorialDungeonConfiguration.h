#pragma once


class CMemorialDungeonConfiguration
{
	class LCMemorialDungeon
	{
		class lcInstantMap
		{
			/* this+ 0 */ public: mystd::string m_PhysicalMapName;
			/* this+28 */ public: int m_Type;

			public: lcInstantMap::lcInstantMap(const mystd::string in_PhysicalMapName, const int in_Type) : m_PhysicalMapName(in_PhysicalMapName), m_Type(in_Type) { } // line 21
		};

		struct tagEnter
		{
			/* this+0 */ int X;
			/* this+4 */ int Y;
			/* this+8 */ mystd::string PhysicalMapName;
		};

		/* this+ 0 */ public: mystd::vector<lcInstantMap> m_MapList;
		/* this+16 */ public: mystd::string m_strPlaceWithMap;
		/* this+44 */ public: int m_LiveTimeMinute;
		/* this+48 */ public: const mystd::string m_strName;
		/* this+76 */ public: tagEnter m_Enter;

		public: LCMemorialDungeon::LCMemorialDungeon(const mystd::string in_strName) : m_strPlaceWithMap(""), m_LiveTimeMinute(300), m_strName(in_strName) { } // line 41
		//public: LCMemorialDungeon::LCMemorialDungeon(void);
		public: LCMemorialDungeon::~LCMemorialDungeon(void) { }; // line 43
	};

	/* this+ 0 */ public: //const CMemorialDungeonConfiguration::`vftable';
	/* this+ 4 */ private: mystd::map<mystd::string,LCMemorialDungeon> m_MemorialDungeonContainer;
	/* this+16 */ private: int m_EnterLimitMinute;
	/* this+20 */ private: bool m_bDataBaseLogOutput;
	/* this+24 */ private: int m_SubscriptionMinimumDelaySecond;
	/* this+28 */ private: bool m_bOpen;
	/* this+29 */ private: bool m_bOK;
	/* static  */ private: static hook_val<const mystd::string> m_szConfigFileName;
	/* static  */ private: static hook_ptr<CMemorialDungeonConfiguration*> m_cpSelf;

	typedef mystd::map<mystd::string,LCMemorialDungeon>::const_iterator MEMORIAL_DUNGEON_CONTAINER_ITER;
					 
	private: CMemorialDungeonConfiguration::CMemorialDungeonConfiguration(void);
	private: virtual CMemorialDungeonConfiguration::~CMemorialDungeonConfiguration(void);
	private: bool CMemorialDungeonConfiguration::Create(void);
	private: void CMemorialDungeonConfiguration::Destroy(void);
	//public: const bool CMemorialDungeonConfiguration::isOK() const;
	//public: CMemorialDungeonConfiguration::LCMemorialDungeon* CMemorialDungeonConfiguration::GetConfigurationPtr(const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >);
	//public: unsigned long CMemorialDungeonConfiguration::GetEnterLimitMinute();
	//public: unsigned long CMemorialDungeonConfiguration::GetSubscriptionMinimumDelaySecond();
	public: bool CMemorialDungeonConfiguration::IsDBLogOutput(void) const; // line 66
	public: bool CMemorialDungeonConfiguration::IsOpen(void);
	//private: bool CMemorialDungeonConfiguration::Anaysis(const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >);
	//private: bool CMemorialDungeonConfiguration::Anaysis_Dungeon(class N2FTAFile &, class N2FTALexicalAnalyzer &, class CMemorialDungeonConfiguration::LCMemorialDungeon &, class N2FTALexicalAnalyzer::FTARet &);
	//private: void CMemorialDungeonConfiguration::ErrorMessageBox(const char *, <NoType>);
	//private: class std::basic_string<char,std::char_traits<char>,std::allocator<char> > CMemorialDungeonConfiguration::GetTokenInfoStr(class N2FTAToken &, class N2FTAFile &);
	//private: bool CMemorialDungeonConfiguration::GetFTAToken(class N2FTALexicalAnalyzer &, class N2FTALexicalAnalyzer::FTARet &, enum N2FTAToken::enumTYPE);
	//private: bool CMemorialDungeonConfiguration::PeekFTAToken(class N2FTALexicalAnalyzer &, class N2FTALexicalAnalyzer::FTARet &, enum N2FTAToken::enumTYPE);
	//public: static bool CMemorialDungeonConfiguration::CreateInstance();
	//public: static void CMemorialDungeonConfiguration::DestroyInstance();
	friend CMemorialDungeonConfiguration* __cdecl InstanceCMemorialDungeonConfiguration(void);

private:
	static hook_method<bool (CMemorialDungeonConfiguration::*)(void)> CMemorialDungeonConfiguration::_Create;
	static hook_method<void (CMemorialDungeonConfiguration::*)(void)> CMemorialDungeonConfiguration::_Destroy;
	static hook_method<bool (CMemorialDungeonConfiguration::*)(void) const> CMemorialDungeonConfiguration::_IsDBLogOutput;
	static hook_method<bool (CMemorialDungeonConfiguration::*)(void)> CMemorialDungeonConfiguration::_IsOpen;
};


CMemorialDungeonConfiguration* __cdecl InstanceCMemorialDungeonConfiguration(void); // line 92
