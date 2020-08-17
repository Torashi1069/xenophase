#pragma once


class CMapInfo
{
public:
	/* this+ 0 */ //const CMapInfo::`vftable';
	/* this+ 4 */ int MapID;
	/* this+ 8 */ char Name[24];
	/* this+32 */ int type; // enumMAPTYPE
	/* this+36 */ bool bPlayerEnter;
	/* this+40 */ int ZSID;

public:
	CMapInfo() : MapID(0), type(0), bPlayerEnter(true), ZSID(0) { }
	virtual ~CMapInfo() { }
};


class CMapInfoMgr
{
public:
	bool isOK() const;
	int GetServerID(const std::string in_mapName) const;
	int GetMapID(const std::string in_mapName) const; //TODO
	int GetMapType(const std::string in_mapName) const; //TODO
	bool IsSiege(const std::string in_mapName) const;
	bool InstantMapAdd2(const CMapInfo& in_MapInfo);
	void InstantMapRemove(const std::string in_mapName);
	bool GetPlayerEnter(const std::string in_mapName) const;
	void SetPlayerEnter(const std::string in_mapName, const bool in_bPlayerEnter);
	void SetPlayerEnter(const unsigned int in_MapID, const bool in_bPlayerEnter);
	std::pair<int,bool> GetZSVRandPlayerEnter(const std::string in_mapName);
	std::vector<int> GetMapIDList() const;
	std::pair<bool,CMapInfo> GetMapInfo(const int MapID) const;

private:
	bool Create(const std::string in_ConnectionString);
	std::pair<bool,std::string> LoadMapInfo(const std::string in_ConnectionString);
	void Destroy();

public:
	static bool CreateInstance(const std::string in_ConnectionString);
	static void DestroyInstance();
	static CMapInfoMgr* GetObj(); /// @custom

public:
	CMapInfoMgr(const std::string in_ConnectionString);
	virtual ~CMapInfoMgr();
	CMapInfoMgr(CMapInfoMgr&); // = delete;
	CMapInfoMgr& operator=(CMapInfoMgr&); // = delete;

private:
	/* static  */ static CMapInfoMgr*& m_cpSelf; //TODO
	/* this+ 0 */ //const CMapInfoMgr::`vftable';
	/* this+ 4 */ bool m_bOK;
	typedef std::map<unsigned int,CMapInfo> MAPINFOTBL;
	/* this+ 8 */ MAPINFOTBL m_MapInfoTbl;
	typedef std::map<std::string,unsigned int> MAPPINGTBL;
	/* this+24 */ MAPPINGTBL m_MappingTbl;
};
