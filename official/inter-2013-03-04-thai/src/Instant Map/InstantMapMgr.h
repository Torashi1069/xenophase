#pragma once
class CInstantMap;


class CInstantMapMgr
{
private:
	/* this+ 0 */ //const CInstantMapMgr::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* static  */ static CInstantMapMgr*& m_cpSelf; //TODO

	typedef std::map<unsigned int,CInstantMap*> CONTAINER;
	typedef std::map<unsigned int,CInstantMap*>::iterator CONTAINER_ITER;
	/* this+ 8 */ CONTAINER m_Container;

	typedef std::map<std::string,unsigned int> INDEXMAP;
	typedef std::map<std::string,unsigned int>::iterator INDEXMAP_ITER;
	/* this+40 */ INDEXMAP m_IndexMap;

private:
	bool Create();
	void Destroy();

public:
	const bool isOK() const;
	void Process();
	const int GetNum() const;
	std::pair<bool,std::string> InstantMapCreate(const unsigned int in_FromInter, const int in_TargetZSID, const std::string in_Name, const int in_mapType);
	bool InstantMapDestory(const unsigned int in_FromInter, const std::string in_Name);
	std::string GetInstantMapName(const unsigned int in_hInstantMap);
	void NotifyAllInstantMap(const int in_ZSVR, const unsigned long& in_ZSVRRegisteredMgrFUCnt);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CInstantMapMgr* GetObj(); /// @custom

private:
	CInstantMapMgr();
	virtual ~CInstantMapMgr();
};
