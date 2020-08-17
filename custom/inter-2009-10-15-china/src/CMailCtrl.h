#pragma once
#include "CDateTime.h"
#include "CMailDB.h"
#include "structs.hpp"


class CMailCtrl
{
	/* this+0x0  */ void* vtable;
	/* this+0x4  */ private: CMailDB m_MailDB;
	/* this+0x16 */ private: MAILTIME m_DeleteTime;
	/* this+0x20 */ private: unsigned long m_lastTime;
	/* this+0x24 */ private: CDateTime m_DateTime;

	public: void CMailCtrl::Process(void);
	//public: void CMailCtrl::GetMaillist(unsigned long, unsigned long);
	//public: void CMailCtrl::MailOpen(unsigned long, unsigned long, unsigned long);
	//public: void CMailCtrl::GetMailItem(unsigned long, unsigned long, unsigned long);
	//public: void CMailCtrl::SendMail(unsigned long, unsigned long, unsigned long, char *, char *, int, unsigned long, char *, unsigned long, char *, int);
	//public: void CMailCtrl::DeleteMail(unsigned long, unsigned long);
	//public: int CMailCtrl::DeleteMail(unsigned long, unsigned long, unsigned long);
	//public: int CMailCtrl::ReturnMail(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
	public: int CMailCtrl::GetMail(unsigned long AID, unsigned long GID, DBMAILINFO* pMail);
	public: void CMailCtrl::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type);
	//public: void CMailCtrl::CMailCtrl();
	//public: void CMailCtrl::~CMailCtrl();

private:
	static hook_method<void (CMailCtrl::*)(void)> CMailCtrl::_Process;
	static hook_method<int (CMailCtrl::*)(unsigned long AID, unsigned long GID, DBMAILINFO* pMail)> CMailCtrl::_GetMail;
	static hook_method<void (CMailCtrl::*)(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type)> CMailCtrl::_Init;
};
