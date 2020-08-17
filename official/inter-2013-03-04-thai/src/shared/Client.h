#pragma once
class CAsyncStream;


/// @see CClient::GetType()
enum enumCLIENTTYPE
{
	PC_TYPE            = 0,
	NPC_TYPE           = 1,
	ITEM_TYPE          = 2,
	SKILL_TYPE         = 3,
	UNKNOWN_TYPE       = 4,
	NPC_MOB_TYPE       = 5,
	NPC_EVT_TYPE       = 6,
	NPC_PET_TYPE       = 7,
	NPC_HO_TYPE        = 8,
	NPC_MERSOL_TYPE    = 9,
	NPC_ELEMENTAL_TYPE = 10,
};


class CClient
{
public:
	CClient();
	virtual ~CClient();

public:
	virtual int GetType();
	virtual void AddErrorCnt(const char* in_pszFileName, const int in_nLineNum, const DWORD in_Cnt, const DWORD in_TM);
	virtual void Init();
	BOOL IsErrorClient();
	BOOL IsErrorServer();
	BOOL Close();
	virtual void Send(int len, const char* buf);
	int GetErrorCount();

protected:
	/* this+ 0 */ //const CClient::`vftable';
	/* this+ 4 */ CAsyncStream* m_asyncStream;
	/* this+ 8 */ RTL_CRITICAL_SECTION m_disconnector_cs;
	/* this+32 */ DWORD m_dwErrorCount;
	/* this+36 */ DWORD m_nBanTime;
};
