#pragma once


class CMemorialDungeonConfig
{
public:
	class lcMDConfigData
	{
	public:
		lcMDConfigData() { }
		lcMDConfigData(const std::string in_szTitle) : m_szTitle(in_szTitle), m_nLiveTimeMinute(0) { }
		~lcMDConfigData() { }

	public:
		class MDMapInfo
		{
		public:
			MDMapInfo(const std::string in_szMapName, const int in_nMapType) : m_szMapName(in_szMapName), m_nMapType(in_nMapType) { }
			~MDMapInfo() { }

		public:
			/* this+ 0 */ std::string m_szMapName;
			/* this+28 */ int m_nMapType;
		};

		class MDEnterMapInfo
		{
		public:
			MDEnterMapInfo(): m_szMapName(""), m_nXpos(0), m_nYpos(0) { }
			~MDEnterMapInfo() { }

		public:
			/* this+ 0 */ std::string m_szMapName;
			/* this+28 */ int m_nXpos;
			/* this+32 */ int m_nYpos;
		};

		/* this+ 0 */ std::string m_szTitle;
		/* this+28 */ std::list<MDMapInfo> m_MapInfoObj;
		/* this+56 */ MDEnterMapInfo m_lcEnterMapInfo;
		/* this+92 */ int m_nLiveTimeMinute;
		/* this+96 */ std::string m_szPlaceWithMap;
	};

public:
	bool isOK() const;
	bool Init();

private:
	bool LoadTbl();

private:
	/* this+0 */ bool m_bOK;
	/* static */ static CMemorialDungeonConfig*& m_cpSelf; //TODO
	typedef stdext::hash_map<std::string,lcMDConfigData> MDCONFIGOBJ;
	/* this+ 4 */ MDCONFIGOBJ m_MDConfigInfo;
	/* this+76 */ int m_nMaxMemoryBytes;
	/* this+80 */ int m_nEnterLimitMinute;
	/* this+84 */ int m_nSubscriptionMinimumDelaySecond;
	/* this+88 */ int m_nDatabaseLogOutput;
	/* this+92 */ bool m_bOpen;

public:
	bool SetBaseConfig(const int in_nMaxMemoryBytes, const int in_nEnterLimitMinute, const int in_nSubscriptionMinimumDelaySecond, const int in_nDatabaseLogOutput, const int in_nOpen);
	bool RegisterMemorialDungeon(const std::string in_szTitle);
	bool InsertMDMap(const std::string in_szIndex, const std::string in_szMapName, const int in_nMapType);
	bool InsertMDLiveTimeMinute(const std::string in_szIndex, const int in_nMinute);
	bool InsertMDEnterMap(const std::string in_szIndex, const std::string in_szMapName, const int in_nXpos, const int in_nYpos);
	bool InsertMDPlaceWithMap(const std::string in_szIndex, const std::string in_szMapName);

	std::pair<bool,lcMDConfigData> GetOnceMDObj(const std::string in_szIndex);

	MDCONFIGOBJ GetMDObj() { return m_MDConfigInfo; } //FIXME: return-by-value
	int GetMaximumZoneResourceMemory() { return m_nMaxMemoryBytes; }
	int GetEnterLimitMinute() { return m_nEnterLimitMinute; }
	int GetSubscriptionMinimumDelaySecond() { return m_nSubscriptionMinimumDelaySecond; }
	int GetDatabaseLogOutput() { return m_nDatabaseLogOutput; }
	bool isOpen() { return m_bOpen; }

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CMemorialDungeonConfig* GetObj(); /// @custom

private:
	CMemorialDungeonConfig();
	~CMemorialDungeonConfig();
	CMemorialDungeonConfig(CMemorialDungeonConfig&); // = delete;
	CMemorialDungeonConfig& operator=(CMemorialDungeonConfig&); // = delete;
};
