#pragma once
#include "DatabaseLog.h"
class CNpcMercenary;
class CPC;


class CMercenaryLogRecord
{
	public: enum enumType
	{
		TYPE_UNKNOWN                    = 0,
		TYPE_EMPLOYMENT                 = 1,
		TYPE_DELETE_BECAUSE_DEAD        = 2,
		TYPE_DELETE_BECAUSE_EXPIRE_TIME = 3,
		TYPE_DELETE_BECAUSE_OWNER       = 4,
		TYPE_DELETE_BECAUSE_OWNER_DEAD  = 5,
		TYPE_DELETE_BECAUSE_UNKNOWN     = 6,
		TYPE_TIME                       = 7,
	};

	/* this+ 0 */ public: enum CMercenaryLogRecord::enumType m_Type;
	/* this+ 4 */ public: DWORD m_dwAccountID;
	/* this+ 8 */ public: char m_szAccountName[25];
	/* this+36 */ public: DWORD m_dwCharacterID;
	/* this+40 */ public: char m_szCharacterName[25];
	/* this+68 */ public: int m_Job;
	/* this+72 */ public: int m_RemainLifeSECOND;
	/* this+76 */ public: int m_approval_monster_kill_counter;

	//private: void AlwaysDestIncNULLstrncpy(char * const, const char *, const int);
	public: CMercenaryLogRecord::CMercenaryLogRecord(const enum CMercenaryLogRecord::enumType in_Type, CNpcMercenary* const in_cpMercenary, CPC* const in_cpOwner);
};


class CMercenaryLog : public CDatabaseLog<CMercenaryLogRecord*>
{
	/* this+0 */ public: //CDatabaseLog<CMercenaryLogRecord*> baseclass_0;

	private: virtual int CMercenaryLog::SaveToDatabase(SQLHSTMT in_hStmt, CMercenaryLogRecord* pLog);
	public: virtual void CMercenaryLog::ConnectToDatabase(const char* Log);
	public: void CMercenaryLog::Add(const enum CMercenaryLogRecord::enumType in_Type, CNpcMercenary* const in_cpMercenary, CPC* const in_cpOwner);

private:
	static hook_method<int (CMercenaryLog::*)(SQLHSTMT in_hStmt, CMercenaryLogRecord* pLog)> CMercenaryLog::_SaveToDatabase;
	static hook_method<void (CMercenaryLog::*)(const char* Log)> CMercenaryLog::_ConnectToDatabase;
	static hook_method<void (CMercenaryLog::*)(const enum CMercenaryLogRecord::enumType in_Type, CNpcMercenary* const in_cpMercenary, CPC* const in_cpOwner)> CMercenaryLog::_Add;
};
