#include "CMailCtrl.h"


hook_method<void (CMailCtrl::*)(void)> CMailCtrl::_Process(SERVER, "CMailCtrl::Process");
void CMailCtrl::Process(void)
{
	return (this->*_Process)();

	//TODO
}


hook_method<int (CMailCtrl::*)(unsigned long AID, unsigned long GID, DBMAILINFO* pMail)> CMailCtrl::_GetMail(SERVER, "CMailCtrl::GetMail");
int CMailCtrl::GetMail(unsigned long AID, unsigned long GID, DBMAILINFO* pMail) // line 394-396
{
	return (this->*_GetMail)(AID, GID, pMail);

	// TODO
}


hook_method<void (CMailCtrl::*)(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type)> CMailCtrl::_Init(SERVER, "CMailCtrl::Init");
void CMailCtrl::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type)
{
	return (this->*_Init)(DSN, UID, PASS, DB, type);

	//TODO
}
