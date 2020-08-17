#pragma once
#include "Memorial Dungeon/MemorialDungeon.h"


class CMemorialDungeonMgr
{
public:
	enum enumOpenState
	{
		OPENSTATE_UNKNOWN = 0,
		OPENSTATE_OPEN    = 1,
		OPENSTATE_CLOSE   = 2,
	};

private:
	/* static  */ static CMemorialDungeonMgr*& m_cpSelf; //TODO
	/* this+ 0 */ //const CMemorialDungeonMgr::`vftable';
	/* this+ 4 */ bool m_bOK;
	typedef std::map<unsigned long,CMemorialDungeon> CONTAINER;
	typedef std::map<unsigned long,CMemorialDungeon>::iterator CONTAINER_ITER;
	/* this+ 8 */ CONTAINER m_Container;
	/* this+24 */ enumOpenState m_OpenState;

private:
	bool Create();
	void Destroy();

public:
	bool isOK() const;
	void Add(const unsigned long in_ExistZSID, const std::string in_Name, const unsigned long in_hPartyID, const std::string in_PartyName, const unsigned long in_MemorialDungeonID, const int in_Factor);
	void Remove(const unsigned long in_hPartyID);
	bool Exist(const unsigned long in_hPartyID, const std::string in_MDungeonName);
	void DisconnectISVR();
	enumOpenState GetOpenState();
	void SetOpenState(enumOpenState in_OpenState);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CMemorialDungeonMgr* GetObj(); /// @custom

private:
	CMemorialDungeonMgr();
	virtual ~CMemorialDungeonMgr();
};
