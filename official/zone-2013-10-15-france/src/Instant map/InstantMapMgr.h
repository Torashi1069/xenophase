#pragma once
class CInstantMapCtrl;


class CInstantMapMgr
{
private:
	typedef std::map<unsigned int,CInstantMapCtrl*> INSTANTMAPCTRL_CONTAINER;
	typedef std::map<unsigned int,CInstantMapCtrl*>::iterator INSTANTMAPCTRL_CONTAINER_ITER;
	/* this+ 4 */ INSTANTMAPCTRL_CONTAINER m_InstantMapCtrlContainer;
	/* this+20 */ bool m_bOK;
	/* static  */ static CInstantMapMgr*& m_cpSelf; //TODO

private:
	bool Create();
	void Destory();
	const bool isOK() const;
	CInstantMapCtrl* GetInstantMapCtrlPtr(const std::string in_mapName, const int in_mapID);

public:
	void Process();
	bool Start();
	void Stop();
	bool RequestCreate(const unsigned int in_hRequestN2Obj, const int in_hInstantMapID, const std::string in_MapName, const int in_MapType);
	void RequestDestory(const int in_hInstantMapID, const std::string in_MapName);
	int GetCtrlCount();
	void Add(const int in_ZSID, const std::string in_mapName, const int in_mapID, const int in_mapType, const bool in_bPlayerEnter);
	void Remove(const int in_ZSID, const std::string in_mapName, const int in_mapID);
	void SetPlayerEnter(const int in_mapID, const bool in_bPlayerEnter);
	void DisconnectISVR();

public:
	static bool CreateInstance();
	static void DestoryInstance();
	static CInstantMapMgr* GetObj(); /// @custom

private:
	CInstantMapMgr();
	virtual ~CInstantMapMgr();
};
