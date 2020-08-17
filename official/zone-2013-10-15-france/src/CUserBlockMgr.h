#pragma once
#include "shared/DatabaseLog.h"


class CUserBlock
{
public:
	enum enumREASON
	{
		REASON_UNKNOWN_PACKET           = 1,
		REASON_CLIENT_INVALID           = 2,
		REASON_CLIENT_MODIFYIMT_WINSOCK = 3,
		REASON_ZENY_ERROR               = 4,
		REASON_CLIENT_MODIFYIMT_GDI32   = 5,
		REASON_CLIENT_DEBUGGING         = 6,
		REASON_CLIENT_CHECKSUM_ERROR    = 7,
		REASON_RESPONSE_TIMEOUT         = 8,
		REASON_HACKSHIELD_ERROR         = 9,
	};

	enum enumTYPE
	{
		TYPE_WARNNING = 1,
		TYPE_BLOCK    = 2,
	};

private:
	/* this+ 0 */ int m_Type; // enumTYPE
	/* this+ 4 */ unsigned long m_AID;
	/* this+ 8 */ int m_Reason; // enumREASON
	/* this+12 */ time_t m_EndDate;

public:
	CUserBlock(const enumTYPE in_Type, const unsigned long in_AID, const enumREASON in_Reason, const long in_Second) : m_Type(in_Type), m_AID(in_AID), m_Reason(in_Reason), m_EndDate(in_Second + time(NULL)) { }
	~CUserBlock() { }

	friend class CUserBlockMgr;
};


class CUserBlockMgr : public CDatabaseLog<CUserBlock*>
{
public:
	virtual void ConnectToDatabase(const char* in_DSN);
	void AddR2(const CUserBlock::enumTYPE in_Type, const CUserBlock::enumREASON in_Reason, const unsigned long in_AID, const int in_Second);

private:
	virtual BOOL SaveToDatabase(SQLHSTMT in_hStmt, CUserBlock* in_cpUserBlock);

public:
	CUserBlockMgr();
	virtual ~CUserBlockMgr();
};
