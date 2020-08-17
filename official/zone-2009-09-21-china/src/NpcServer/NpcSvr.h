#pragma once
#include "NpcServer/NpcEvent.h"
#include "NpcServer/NpcMgr.h"
#include "ScriptLib/BinBuf.h"
#include "CDGNpcMgr.hpp"
#include "std/map"
#include "std/set"
#include "std/string"
class CZNPC2Msg;


template<typename T> class pool
{
	/* this+0 */ private: mystd::map<T*,bool> m_TMap;

	public: pool<T>::pool(void) // line ??
	{
	}

	public: pool<T>::~pool(void) // line 54
	{
		this->pool<T>::clear();
	}

	public: T* pool<T>::Alloc(void) // line 61
	{
		T* result;

		mystd::map<T*,bool>::iterator mapi;
		for( mapi = m_TMap.begin(); mapi != m_TMap.end(); ++mapi )
			if( mapi->second == false )
				break;

		if( mapi != m_TMap.end() )
		{// replace existing
			result = mapi->first;
			mapi->second = true;
		}
		else
		{// insert new
			result = new CNpcEvent();
			m_TMap[result] = true;
		}

		return result;
	}

	public: void pool<T>::Free(T* pT) // line 79
	{
		mystd::map<T*,bool>::iterator mapi = m_TMap.find(pT);
		if( mapi != m_TMap.end() )
			if( mapi->second == true )
				mapi->second = false;
	}

	public: void pool<T>::clear(void) // line 94
	{
		for( mystd::map<T*,bool>::iterator it = m_TMap.begin(); it != m_TMap.end(); ++it )
			delete it->first;

		m_TMap.clear();
	}
};


class CNpcSvr
{
	/* this+ 0 */ public: CNpcMgr m_mobMgr;
	/* this+16 */ public: mystd::multiset<mystd::string> m_npcNames;
	/* this+28 */ public: mystd::set<mystd::string> m_cmdothernpcNames;
	/* this+40 */ private: CBinBuf m_binBuf;
	/* this+48 */ private: CNpcMgr m_npcMgr;
	/* this+64 */ private: int m_eventNo;
	/* this+68 */ private: bool m_clearFirstEvent;
	/* this+72 */ private: pool<CNpcEvent> m_pool;
	/* this+84 */ private: mystd::map<int,CNpcEvent*> m_eventMap;
	/* this+96 */ private: CDGNpcMgr m_dungeonNpcMgr;

	public: CNpcSvr::CNpcSvr(void);
	public: CNpcSvr::~CNpcSvr(void);
	public: bool CNpcSvr::Start(void);
	public: void CNpcSvr::Process(void);
	public: int CNpcSvr::SendMsg(unsigned long senderAID, unsigned long receiverAID, CZNPC2Msg* msg);
	public: int CNpcSvr::RunEvent(int pcId, int npcId, int act, int reserveTime, bool oninit);
	public: void CNpcSvr::CancelEvent(int eventNo);
	public: void CNpcSvr::CreateMobNameDbNameFile(void);
	public: CNpcMgr* CNpcSvr::GetNpcMgr(void);
	public: bool CNpcSvr::ClearFirstEvent(void);
	public: void CNpcSvr::FinalNpcEvent(mystd::string mapName);
	public: void CNpcSvr::FinalDungeonNpc(int npcId);
	public: bool CNpcSvr::AddGunGeon(const char* mapName, unsigned int instantID);
	public: int CNpcSvr::RunEvent_Dungeon(int pcId, int npcId, int act, int reserveTime, mystd::string mapName, unsigned int instantID, bool oninit);
	private: void CNpcSvr::Clear(void);
	private: bool CNpcSvr::LoadScript(void);
	private: bool CNpcSvr::Compile(void);

private:
	static hook_method<bool (CNpcSvr::*)(void)> CNpcSvr::_Start;
	static hook_method<void (CNpcSvr::*)(void)> CNpcSvr::_Process;
	static hook_method<int (CNpcSvr::*)(unsigned long senderAID, unsigned long receiverAID, CZNPC2Msg* msg)> CNpcSvr::_SendMsg;
	static hook_method<int (CNpcSvr::*)(int pcId, int npcId, int act, int reserveTime, bool oninit)> CNpcSvr::_RunEvent;
	static hook_method<void (CNpcSvr::*)(int eventNo)> CNpcSvr::_CancelEvent;
	static hook_method<void (CNpcSvr::*)(void)> CNpcSvr::_CreateMobNameDbNameFile;
	static hook_method<CNpcMgr* (CNpcSvr::*)(void)> CNpcSvr::_GetNpcMgr;
	static hook_method<bool (CNpcSvr::*)(void)> CNpcSvr::_ClearFirstEvent;
	static hook_method<void (CNpcSvr::*)(mystd::string mapName)> CNpcSvr::_FinalNpcEvent;
	static hook_method<void (CNpcSvr::*)(int npcId)> CNpcSvr::_FinalDungeonNpc;
	static hook_method<bool (CNpcSvr::*)(const char* mapName, unsigned int instantID)> CNpcSvr::_AddGunGeon;
	static hook_method<int (CNpcSvr::*)(int pcId, int npcId, int act, int reserveTime, mystd::string mapName, unsigned int instantID, bool oninit)> CNpcSvr::_RunEvent_Dungeon;
	static hook_method<void (CNpcSvr::*)(void)> CNpcSvr::_Clear;
	static hook_method<bool (CNpcSvr::*)(void)> CNpcSvr::_LoadScript;
	static hook_method<bool (CNpcSvr::*)(void)> CNpcSvr::_Compile;
};
