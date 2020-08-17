#pragma once
#include "DGNpcMgr.h"
#include "Msg.h"
#include "NpcServer/CStaticNpcMgr.h"
#include "NpcServer/NpcEvent.h"
#include "ScriptLib/BinBuf.h"


template<typename T> class pool
{
public:
	pool()
	{
	}

	~pool()
	{
		for( std::map<T*,bool>::iterator mapi = m_TMap.begin(); mapi != m_TMap.end(); ++mapi )
			delete mapi->first;
	}

	T* Alloc()
	{
		T* ret;

		std::map<T*,bool>::iterator mapi;
		for( mapi = m_TMap.begin(); mapi != m_TMap.end(); ++mapi )
			if( mapi->second == false )
				break; // found unused item

		if( mapi == m_TMap.end() )
		{
			T* ret = new T;
			m_TMap[ret] = true;
		}
		else
		{
			ret = mapi->first;
			mapi->second = true;
		}

		return ret;
	}

	void Free(T* pT)
	{
		std::map<T*,bool>::iterator mapi = m_TMap.find(pT);
		if( mapi == m_TMap.end() )
			return;

		if( mapi->second == true )
			mapi->second = false;
	}

	void clear()
	{
		for( std::map<T*,bool>::iterator mapi = m_TMap.begin(); mapi != m_TMap.end(); ++mapi )
			delete mapi->first;

		m_TMap.clear();
	}

private:
	/* this+0 */ std::map<T*,bool> m_TMap;
};


class CNpcSvr
{
public:
	CNpcSvr();
	~CNpcSvr();

public:
	bool Start();
	void Process();
	int SendMsg(unsigned long senderAID, unsigned long receiverAID, CZNPC2Msg* msg);
	int RunEvent(int pcId, int npcId, int act, int reserveTime, bool oninit);
	void CancelEvent(int eventNo);
	bool IsExistScriptEvent(const int in_AID, const int in_Event);
	CStaticNpcMgr* GetStaticNpcMgr();
	bool ClearFirstEvent();
	void FinalNpcEvent(std::string mapName);
	void FinalDungeonNpc(int npcId);
	bool AddDunGeon(const char* mapName, unsigned int instantID);
	int RunEvent_Dungeon(int pcId, int npcId, int act, int reserveTime, std::string mapName, unsigned int instantID, bool oninit);

public:
	/* this+  0 */ std::multiset<std::string> m_npcNames;
	/* this+ 16 */ std::set<std::string> m_cmdothernpcNames;
private:
	void Clear();
	bool LoadScript();
private:
	/* this+ 32 */ CBinBuf m_binBuf;
	/* this+ 40 */ CStaticNpcMgr m_staticNpcMgr;
	/* this+ 60 */ int m_eventNo;
	/* this+ 64 */ bool m_clearFirstEvent;
	/* this+ 68 */ pool<CNpcEvent> m_pool;
	/* this+ 84 */ std::map<int,CNpcEvent*> m_eventMap;
	/* this+100 */ CDGNpcMgr m_dungeonNpcMgr;
};


extern std::map<int,int>& g_mapNormal2BabyJob;
extern std::map<int,int>& g_mapBabyJob2Normal;
