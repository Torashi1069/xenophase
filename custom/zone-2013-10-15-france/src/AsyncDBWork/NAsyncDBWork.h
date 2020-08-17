#pragma once
#include "HomunDataStuff.h" // HomunDataStuff::CHomunData
#include "NpcHomun.h" // HO_SKINFO
#include "PC.h" // CHARINFO_TO_CHARACTERDB
#include "AsyncDBWork/Effect3rd.h"
#include "AsyncDBWork/NODBCCtrl.h"


class NAsyncDBWork
{
public:
	enum enumType
	{
		TYPE_NONE                          = 0,
		TYPE_UNZIP                         = 1,
		TYPE_ZIP                           = 2,
		TYPE_LOGON_PERMIT                  = 3,
		TYPE_SAVE_ALL                      = 4,
		TYPE_SAVE_BODYITEM                 = 5,
		TYPE_SAVE_CHARACTERINFO            = 6,
		TYPE_SAVE_SKILL                    = 7,
		TYPE_LOAD_STORE                    = 8,
		TYPE_SAVE_STORE                    = 9,
		TYPE_LOAD_CART                     = 10,
		TYPE_SAVE_CART                     = 11,
		TYPE_MERCENARY_CREATE              = 12,
		TYPE_MERCENARY_DELETE              = 13,
		TYPE_SAVE_EFFECTIVEINFO            = 14,
		TYPE_SAVE_QUESTEVENT               = 15,
		TYPE_SAVE_BATTLEFIELD              = 16,
		TYPE_SKILL3RD_UPDATE               = 17,
		TYPE_SKILL3RD_DELETE               = 18,
		TYPE_SKILL3RD_RESET                = 19,
		TYPE_JOB_CHANGE                    = 20,
		TYPE_JOB_TRANSCENDENT              = 21,
		TYPE_EFFECT3RD_DELETE              = 22,
		TYPE_EFFECT3RD_UPDATEALL           = 23,
		TYPE_LOAD_CHARNAME                 = 24,
		TYPE_PARTY_BOOKING_INSERT          = 25,
		TYPE_PARTY_BOOKING_DELETE          = 26,
		TYPE_PARTY_BOOKING_UPDATE          = 27,
		TYPE_ELEMENTAL_CREATE              = 28,
		TYPE_ELEMENTAL_DELETE              = 29,
		TYPE_INSERT_QUEST                  = 30,
		TYPE_ERASE_QUEST                   = 31,
		TYPE_UPDATE_QUEST                  = 32,
		TYPE_HOMUNSKILL_UPDATE             = 33,
		TYPE_HOMUNDATA_SAVE                = 34,
		TYPE_INSERT_IRINVENTORY            = 35,
		TYPE_DELETE_IRINVENTORY            = 36,
		TYPE_IRMAIL_SEND                   = 37,
		TYPE_INSERT_COUPLE                 = 38,
		TYPE_DELETE_COUPLE                 = 39,
		TYPE_INSERT_FAMILY                 = 40,
		TYPE_DELETE_FAMILY                 = 41,
		TYPE_PARTY_RECRUIT_INSERT          = 42,
		TYPE_PARTY_RECRUIT_DELETE          = 43,
		TYPE_PARTY_RECRUIT_UPDATE          = 44,
		TYPE_PARTY_RECRUIT_ADDBLOCKLIST    = 45,
		TYPE_PARTY_RECRUIT_DELETEBLOCKLIST = 46,
		TYPE_LOAD_WARPINFO                 = 47,
		TYPE_GET_BEFOR_WORLD_INFO          = 48,
		TYPE_GET_GUILD_EMBLEM              = 49,
		TYPE_BANKING_DEPOSIT               = 50,
		TYPE_BANKING_WITHDRAW              = 51,
		TYPE_BANKING_VIEW                  = 52,
		TYPE_BANKING_CHECK                 = 53,
		TYPE_INSERT_BARGAIN_SALE           = 54,
		TYPE_UPDATE_BARGAIN_SALE           = 55,
		TYPE_DELETE_BARGAIN_SALE           = 56,
		TYPE_INIT_BARGAIN_SALE             = 57,
		TYPE_SELECT_BARGAIN_SALE           = 58,
		TYPE_LOAD_GUILD_STORE              = 59,
		TYPE_INSERT_GUILD_STORE            = 60,
		TYPE_UPDATE_AID_GUILD_STORE        = 61,
		TYPE_UPDATE_ITEM_GUILD_STORE       = 62,
		TYPE_CHECKZENYWHENLOGOUT           = 63,
		TYPE_INSERTGUILDSTORAGELOG         = 64,
		TYPE_SELECTGUILDSTORAGELOG         = 65,
	};

public:
	enum enumRETURN
	{
		RETURN_SUCCESS    = 0,
		RETURN_ERROR_ODBC = 1,
		RETURN_ERROR      = 2,
		RETURN_NO_DATA    = 3,
	};

private:
	enum { MAXNUM_TRYCNT = 65535 };

private:
	/* this+ 0 */ //const NAsyncDBWork::`vftable';
	/* this+ 4 */ const enumType m_Type;
	/* this+ 8 */ unsigned int m_ID;
	/* this+12 */ DWORD m_StartTM;
	/* this+16 */ int m_Identity;

private:
	virtual bool ExecQuery(NODBCCtrl& in_ODBCCtrl) = 0;

protected:
	enumRETURN SaveBodyItem(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const unsigned char* in_pBodyItemDataBuffer, const int in_Length);
	enumRETURN SaveCharacterInfo(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const char* in_pCharName, CHARINFO_TO_CHARACTERDB& info);
	enumRETURN SaveStoreItem(NODBCCtrl& in_ODBCCtrl, const unsigned long in_AID, const unsigned char* in_pData, const int in_Length);
	enumRETURN SaveCartItem(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const unsigned char* in_pData, const int in_Length);
	enumRETURN SaveQuestEvent(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const unsigned char* in_pData_quest, const int in_Length_quest, const unsigned char* in_pData_hunt, const int in_Length_hunt, const unsigned char* in_pData_time, const int in_Length_time, const unsigned char* in_pData_completeQueue, const int in_Length_completeQueue);
	enumRETURN Skill3rd_Update(NODBCCtrl& in_ODBCCtrl, const int in_GID, const int in_ID, const int in_Level, const int in_RemainMS, const int in_Attr, const int in_Data);
	enumRETURN SaveEffect3rd(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, std::vector<Effect3rd::tagEffect3rdDBFmt> in_List); //FIXME: vector pass-by-value
	enumRETURN UpdateHomunEffect(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const std::vector<Effect3rd::tagEffect3rdDBFmt>& in_List);
	enumRETURN DeleteHomunEffectAll(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID);
	enumRETURN SaveHomunSkill(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const std::map<unsigned short,HO_SKINFO>& in_Skill);
	enumRETURN SaveHomunData(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const HomunDataStuff::CHomunData& in_HomunData);

public:
	const enumType GetType() const;
	const unsigned int GetID() const;
	const DWORD GetStartTM() const;
	const int GetIdentity() const;
	void Init(const unsigned int in_ID);

public:
	NAsyncDBWork(const enumType in_Type);
	virtual ~NAsyncDBWork();

private:
	friend class NAsyncDBThread; // ExecQuery()
};
