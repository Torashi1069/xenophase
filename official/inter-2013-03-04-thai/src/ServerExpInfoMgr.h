#pragma once


class CServerExpInfoMgr
{
	enum
	{
		EXPINFO_RESTRICT_EXP   = 0,
		EXPINFO_RESTRICT_DEATH = 1,
		EXPINFO_RESTRICT_DROP  = 2,
	};

public:
	bool Init();
	bool SetExpIAuthenticate(const std::string in_strID, const std::string in_strPW);
	bool SetServerEXPInfo(const int in_nExp, const int in_nDeath, const int in_nDrop);
	void CreateServerEXPFile(const int in_nExp, const int in_nDeath, const int in_nDrop);
	bool SetRestrictEXPInfo(const int in_nMinExp, const int in_nMaxExp, const int in_nMinDeath, const int in_nMaxDeath, const int in_nMinDrop, const int in_nMaxDrop);
	int GetExp();
	int GetDeath();
	int GetDrop();
	bool IsAuthenticate(const std::string in_ID, const std::string in_Pwd);
	bool isOK() const;

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CServerExpInfoMgr* GetObj(); /// @custom

private:
	bool LoadTbl();

private:
	CServerExpInfoMgr();
	~CServerExpInfoMgr();
	CServerExpInfoMgr(CServerExpInfoMgr&); // = delete;
	CServerExpInfoMgr& operator=(CServerExpInfoMgr&); // = delete;

private:
	class lcFactor
	{
	public:
		/* this+ 0 */ //const CServerExpInfoMgr::lcFactor::`vftable';
		/* this+ 4 */ int m_Max;
		/* this+ 8 */ int m_Min;
		/* this+12 */ int m_Value;

	public:
		lcFactor() { };
		virtual ~lcFactor() { };
		int operator()(); //TODO
		void operator=(const int ); //TODO
	};

private:
	/* this+ 0 */ lcFactor m_Exp;
	/* this+16 */ lcFactor m_Death;
	/* this+32 */ lcFactor m_Drop;
	/* this+48 */ bool m_bOK;
	/* this+52 */ std::string m_strID;
	/* this+80 */ std::string m_strPW;
	/* static  */ static CServerExpInfoMgr*& m_cpSelf; //TODO
};
