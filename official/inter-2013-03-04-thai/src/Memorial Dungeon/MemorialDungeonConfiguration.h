#pragma once
#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTAFile.h"
#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTALexicalAnalyzer.h"


class CMemorialDungeonConfiguration
{
public:
	class LCMemorialDungeon
	{
	public:
		class lcInstantMap
		{
		public:
			/* this+ 0 */ std::string m_PhysicalMapName;
			/* this+28 */ int m_Type;

		public:
			lcInstantMap(const std::string in_PhysicalMapName, const int in_Type) : m_PhysicalMapName(in_PhysicalMapName), m_Type(in_Type) { }
		};

		typedef std::vector<lcInstantMap> MAPLISTCONTAINER;
		typedef std::vector<lcInstantMap>::iterator MAPLISTCONTAINER_ITER;
		/* this+ 0 */ MAPLISTCONTAINER m_MapList;
		/* this+24 */ std::string m_strPlaceWithMap;
		/* this+52 */ int m_LiveTimeMinute;
		/* this+56 */ const std::string m_strName;

		struct tagEnter
		{
			/* this+0 */ int X;
			/* this+4 */ int Y;
			/* this+8 */ std::string PhysicalMapName;
		};
		/* this+84 */ tagEnter m_Enter;

	public:
		LCMemorialDungeon(const std::string in_strName) : m_MapList(), m_strPlaceWithMap(""), m_LiveTimeMinute(300), m_strName(in_strName), m_Enter() { }
		LCMemorialDungeon(); //TODO
		~LCMemorialDungeon() { }
	};

private:
	/* static  */ static const std::string& m_szConfigFileName; //TODO
	/* this+ 0 */ //const CMemorialDungeonConfiguration::`vftable';
	typedef std::map<std::string,LCMemorialDungeon> MEMORIAL_DUNGEON_CONTAINER;
	typedef std::map<std::string,LCMemorialDungeon>::iterator MEMORIAL_DUNGEON_CONTAINER_ITER;
	/* this+ 4 */ std::map<std::string,LCMemorialDungeon> m_MemorialDungeonContainer;
	/* this+36 */ int m_EnterLimitMinute;
	/* this+40 */ bool m_bDataBaseLogOutput;
	/* this+44 */ int m_SubscriptionMinimumDelaySecond;
	/* this+48 */ unsigned int m_under_zsvr_memory_mbytes;
	/* this+52 */ bool m_bOpen;
	/* this+53 */ bool m_bOK;
	/* static  */ static CMemorialDungeonConfiguration*& m_cpSelf; //TODO

private:
	bool Create();
	void Destroy();

public:
	const bool isOK() const;
	LCMemorialDungeon* GetConfigurationPtr(const std::string in_Name);
	unsigned long GetEnterLimitMinute() const;
	unsigned long GetSubscriptionMinimumDelaySecond() const;
	unsigned int Get_under_zsvr_memory_mbytes() const;
	bool IsDBLogOutput() const;
	bool IsOpen();

private:
	bool Anaysis(const std::string in_strFileName);
	bool Anaysis_Dungeon(N2FTAFile& in_ftFile, N2FTALexicalAnalyzer& in_LexicalAnalyzer, LCMemorialDungeon& io_Dungeon, N2FTALexicalAnalyzer::FTARet& io_Ret);
	void ErrorMessageBox(const char* in_pFmt, ...);
	std::string GetTokenInfoStr(N2FTAToken& in_Token, N2FTAFile& in_ftFile);
	bool GetFTAToken(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, N2FTAToken::enumTYPE in_ReqType);
	bool PeekFTAToken(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, N2FTAToken::enumTYPE in_ReqType);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CMemorialDungeonConfiguration* GetObj(); /// @custom

private:
	CMemorialDungeonConfiguration();
	virtual ~CMemorialDungeonConfiguration();
};
