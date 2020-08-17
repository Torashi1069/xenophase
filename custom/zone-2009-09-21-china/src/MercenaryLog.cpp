#include "MercenaryLog.h"
#include "CNpcMercenary.hpp"
#include "PC.h"
#include "globals.hpp"


hook_method<int (CMercenaryLog::*)(SQLHSTMT in_hStmt, CMercenaryLogRecord* pLog)> CMercenaryLog::_SaveToDatabase(SERVER, "CMercenaryLog::SaveToDatabase");
int CMercenaryLog::SaveToDatabase(SQLHSTMT in_hStmt, CMercenaryLogRecord* pLog) // line 37
{
	return (this->*_SaveToDatabase)(in_hStmt, pLog);

	//TODO
}


hook_method<void (CMercenaryLog::*)(const char* Log)> CMercenaryLog::_ConnectToDatabase(SERVER, "CMercenaryLog::ConnectToDatabase");
void CMercenaryLog::ConnectToDatabase(const char* Log) // line ??
{
	return (this->*_ConnectToDatabase)(Log);

	this->CExtendedODBC::Connect("Loger", g_dbPWD, Log, 0, "");
}


hook_method<void (CMercenaryLog::*)(const enum CMercenaryLogRecord::enumType in_Type, CNpcMercenary* const in_cpMercenary, CPC* const in_cpOwner)> CMercenaryLog::_Add(SERVER, "CMercenaryLog::Add");
void CMercenaryLog::Add(const enum CMercenaryLogRecord::enumType in_Type, CNpcMercenary* const in_cpMercenary, CPC* const in_cpOwner) // line 124
{
	return (this->*_Add)(in_Type, in_cpMercenary, in_cpOwner);

	//TODO
}


CMercenaryLogRecord::CMercenaryLogRecord(const enum CMercenaryLogRecord::enumType in_Type, CNpcMercenary* const in_cpMercenary, CPC* const in_cpOwner) // line 93
{
	m_Type = in_Type;

	if( in_cpOwner != NULL )
	{
		m_dwAccountID = in_cpOwner->GetAccountID();
		strncpy(m_szAccountName, in_cpOwner->m_characterInfo.accountName, 24);
		m_szAccountName[23] = '\0';

		m_dwCharacterID = in_cpOwner->CPC::GetCharacterID();
		strncpy(m_szCharacterName, in_cpOwner->m_characterInfo.characterName, 24);
		m_szCharacterName[23] = '\0';
	}
	else
	{
		m_dwAccountID = 0;
		sprintf(m_szAccountName, "unknown");

		m_dwCharacterID = 0;
		sprintf(m_szCharacterName, "unknown");
	}

	if( in_cpMercenary != NULL )
	{
		m_Job = in_cpMercenary->CNpcMercenary::GetJob();
		m_RemainLifeSECOND = in_cpMercenary->CNpcMercenary::GetRemainLifeSECOND();
		m_approval_monster_kill_counter = in_cpMercenary->CNpcMercenary::GetApprovalMonsterKillCounter();
	}
	else
	{
		m_Job = 0;
		m_RemainLifeSECOND = 0;
		m_approval_monster_kill_counter = 0;
	}
}
