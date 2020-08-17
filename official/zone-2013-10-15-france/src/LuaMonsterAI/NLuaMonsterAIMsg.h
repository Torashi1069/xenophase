#pragma once
namespace LuaMonsterAIStuff
{


enum enumMSGID
{
	MSGID_NONE     = 0,
	MSGID_ATTACKED = 1,
	MSGID_DEAD     = 2,
	MSGID_LOG      = 3,
	MSGID_TELEPORT = 4,
	MSGID_USER     = 5,
};


class NMSG
{
public:
	enumMSGID GetMSGID() { return m_MSGID; }

private:
	/* this+0 */ //const LuaMonsterAIStuff::NMSG::`vftable';
	/* this+4 */ enumMSGID m_MSGID;

public:
	NMSG(const enumMSGID in_MSGID) : m_MSGID(in_MSGID) { }
	virtual ~NMSG() { }
};


class NMSG_ATTACKED : public NMSG
{
public:
	/* this+ 0 */ //NMSG baseclass_0;
	/* this+ 8 */ const unsigned long m_AID;
	/* this+12 */ const int m_Damage;

public:
	NMSG_ATTACKED(const unsigned long in_AID, const int in_Damage) : NMSG(MSGID_ATTACKED), m_AID(in_AID), m_Damage(in_Damage) { }
	virtual ~NMSG_ATTACKED() { }
};


class NMSG_DEAD : public NMSG
{
public:
	/* this+0 */ //LuaMonsterAIStuff::NMSG baseclass_0;
	/* this+8 */ const unsigned long m_AID;

public:
	NMSG_DEAD(const unsigned long in_AID) : NMSG(MSGID_DEAD), m_AID(in_AID) { }
	virtual ~NMSG_DEAD() { }
};


class NMSG_LOG : public NMSG
{
public:
	/* this+0 */ //LuaMonsterAIStuff::NMSG baseclass_0;

public:
	NMSG_LOG() : NMSG(MSGID_LOG) { }
	virtual ~NMSG_LOG() { }
};


class NMSG_TELEPORT : public NMSG
{
public:
	/* this+ 0 */ //NMSG baseclass_0;
	/* this+ 8 */ const int m_xPos;
	/* this+12 */ const int m_yPos;
	/* this+16 */ const char* m_MapName;

public:
	NMSG_TELEPORT(const int in_xPos, const int in_yPos, const char* in_MapName) : NMSG(MSGID_TELEPORT), m_xPos(in_xPos), m_yPos(in_yPos), m_MapName(in_MapName) { }
	virtual ~NMSG_TELEPORT() { }
};


class NMSG_USER : public NMSG
{
public:
	/* this+ 0 */ //NMSG baseclass_0;
	/* this+ 8 */ const int m_wParam;
	/* this+12 */ const int m_lParam;

public:
	NMSG_USER(const int in_wParam, const int in_lParam) : NMSG(MSGID_USER), m_wParam(in_wParam), m_lParam(in_lParam) { }
	virtual ~NMSG_USER() { }
};


}; // namespace LuaMonsterAIStuff
