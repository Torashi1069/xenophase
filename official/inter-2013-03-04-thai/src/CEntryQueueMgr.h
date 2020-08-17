#pragma once


class CEntryQueueMgr
{
public:
	void AddEntryQueue(const std::string in_EntryQueueName, const int in_ZSID);
	int GetZSID(const std::string in_EntryQueueName) const;
	bool AddApplicant(const unsigned long in_GID, const unsigned long in_AID, const std::string in_EntryQueueName);
	void DelApplicant(const unsigned long in_GID);
	void LogOut(const unsigned long in_GID);
	bool IsApplicant(const unsigned long in_GID, std::string& out_EntryQueueName);
	void DisconnectZSVR(const unsigned long in_ZSID);
	bool IsBattleFieldMap(const std::string in_UserLocation) const;
	bool isOK() const;

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CEntryQueueMgr* GetObj(); /// @custom

private:
	bool Create();
	void Destroy();

private:
	CEntryQueueMgr();
	~CEntryQueueMgr();
	CEntryQueueMgr(const CEntryQueueMgr&); // = delete;
	CEntryQueueMgr& operator=(const CEntryQueueMgr&); // = delete;

private:
	/* static   */ static CEntryQueueMgr*& m_cpSelf; //TODO
	/* this+  0 */ bool m_bOK;
	typedef stdext::hash_map<std::string,int> HASHMAP_ENTRY_QUEUE;
	typedef std::map<unsigned long,std::pair<unsigned long,std::string>> ENTRY_QUEUE_NAME_FOR_GID;
	/* this+  4 */ HASHMAP_ENTRY_QUEUE m_hashmapEntryQueue;
	/* this+ 76 */ ENTRY_QUEUE_NAME_FOR_GID m_mapEntryQueueNameForGID;
	/* this+108 */ std::set<std::string> m_setBattleFieldMapName;
};
