#include "AsyncDBWork/LogonPermitADBWork.h"
#include "AsyncDBWork/NODBCHandler.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/ZLib.h"


CLogonPermitADBWork::CLogonPermitADBWork()
: NAsyncDBWork(TYPE_LOGON_PERMIT),
  m_AID(0),
  m_GID(0),
  m_SelectedCharNum(0),
//m_Sex(0),
//m_IDstr(),
  m_TotalUsingTime(0),
  m_Result(RESULT_ERROR_UNKNOWN),
  m_BodyItemInfo(),
  m_CharacterInfo(),
  m_Skill3rdData(),
  m_MercenaryData(),
  m_Effect3rd(),
  m_StateData(),
  m_HomunData(),
  m_questData(),
  m_battleFieldData(),
  m_Elemental(),
  m_CoupleInfo(),
  m_FamilyInfo()
{
}


CLogonPermitADBWork::~CLogonPermitADBWork()
{
}


const unsigned long CLogonPermitADBWork::GetGID() const
{
	return m_GID;
}


const unsigned long CLogonPermitADBWork::GetAID() const
{
	return m_AID;
}


char CLogonPermitADBWork::GetSex() const
{
	return m_Sex;
}


const char* CLogonPermitADBWork::GetIDstr() const
{
	return m_IDstr;
}


const DWORD CLogonPermitADBWork::GettotalUsingTime() const
{
	return m_TotalUsingTime;
}


const int CLogonPermitADBWork::GetSelectedCharNum() const
{
	return m_SelectedCharNum;
}


const CLogonPermitADBWork::enumResult CLogonPermitADBWork::GetResult() const
{
	return m_Result;
}


void CLogonPermitADBWork::Init(const unsigned long in_AID, const unsigned long in_GID, const int in_SelectedCharNum, const char* in_pIDstr, const DWORD in_TotalUsingTime, const char in_Sex) // 68-139
{
	this->NAsyncDBWork::Init(in_AID);

	m_Sex = in_Sex;
	m_GID = in_GID;
	m_AID = in_AID;
	m_SelectedCharNum = in_SelectedCharNum;
	m_TotalUsingTime = in_TotalUsingTime;
	m_Result = RESULT_ERROR_UNKNOWN;
	memcpy_s(m_IDstr, sizeof(m_IDstr), in_pIDstr, sizeof(in_pIDstr));

	m_BodyItemInfo.CLogonPermitADBWork::CBodyItemData::Init();
	m_Skill3rdData.CLogonPermitADBWork::CSkill3rdData::Init();
	m_MercenaryData.CLogonPermitADBWork::CMercenaryData::Init();
	m_Effect3rd.CLogonPermitADBWork::CEffect3rd::Init();
	m_StateData.CLogonPermitADBWork::CStateData::Init();
	m_HomunData.Init();
	m_questData.CLogonPermitADBWork::CQuestEventData::Init();
	m_CoupleInfo.CLogonPermitADBWork::CoupleInfo::Init();
	m_FamilyInfo.CLogonPermitADBWork::FamilyInfo::Init();
	m_battleFieldData.CLogonPermitADBWork::CBattleFieldData::Init();
	m_Elemental.CLogonPermitADBWorkStuff::CElementalData::Init();
}


bool CLogonPermitADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl) // 496-912
{
	return false;
	//TODO
}


int CLogonPermitADBWork::CSkill3rdData::GetTotalFirstJobSkillLevel(const int in_Job) // 1297-1304
{
	return 0;
	//TODO
}


int CLogonPermitADBWork::CSkill3rdData::GetTotalSecondJobSkillLevel(const int in_Job) // 1309-1316
{
	return 0;
	//TODO
}


NAsyncDBWork::enumRETURN CLogonPermitADBWork::LoadQuestEventInfo(NODBCCtrl& in_ODBCCtrl) // 2342-2451
{
	NODBCHandler Handler(in_ODBCCtrl);

	m_questData.m_questEvent_Length = -1;
	m_questData.m_completeQuest_Length = -1;
	m_questData.m_quest_hunt_Length = -1;
	m_questData.m_quest_time_Length = -1;

	SQLINTEGER cbAID = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_GID, 0, &cbAID);
	if( !SQL_SUCCEEDED(Handler.NODBCHandler::ExecDirect("{call GetQuestEvent(?)}")) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	//FIXME: only the first 4000 bytes are used
	unsigned char zipQuestEventBuff[8000] = {};
	unsigned char zipCompleteQuestBuff[4000] = {};
	unsigned char zipQuest_HuntBuff[8000] = {};
	unsigned char zipQuest_TimeBuff[8000] = {};
	SQLINTEGER cbstoredbin = SQL_NTS;
	SQLINTEGER cbstoredbin2 = SQL_NTS;
	SQLINTEGER cbstoredbin3 = SQL_NTS;
	SQLINTEGER cbstoredbin4 = SQL_NTS;

	Handler.NODBCHandler::BindCol(1, SQL_C_BINARY, zipQuestEventBuff, 4000, &cbstoredbin);
	Handler.NODBCHandler::BindCol(2, SQL_C_BINARY, zipCompleteQuestBuff, 4000, &cbstoredbin2);
	Handler.NODBCHandler::BindCol(3, SQL_C_BINARY, zipQuest_HuntBuff, 4000, &cbstoredbin3);
	Handler.NODBCHandler::BindCol(4, SQL_C_BINARY, zipQuest_TimeBuff, 4000, &cbstoredbin4);

	SQLRETURN ret = Handler.NODBCHandler::Fetch();
	if( ret < 0 )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}
	if( !SQL_SUCCEEDED(ret) )
	{
		if( ret == SQL_NO_DATA )
		{
			m_questData.m_questEvent_Length = 0;
			m_questData.m_completeQuest_Length = 0;
			m_questData.m_quest_hunt_Length = 0;
			m_questData.m_quest_time_Length = 0;
			return NAsyncDBWork::RETURN_NO_DATA;
		}

		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	if( cbstoredbin == -1 )
	{
		m_questData.m_questEvent_Length = 0;
	}
	else
	{
		CZLib zlib;
		unsigned long unZipLength = sizeof(m_questData.m_questEvent_Data);
		int error = zlib.CZLib::Uncompress(m_questData.m_questEvent_Data, &unZipLength, zipQuestEventBuff, cbstoredbin);
		if( error != 0 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "QuestEvent uncompress: error %d, AID:%d,GID:%d\n", error, m_AID, m_GID);
			return NAsyncDBWork::RETURN_ERROR;
		}

		m_questData.m_questEvent_Length = unZipLength;
	}

	if( cbstoredbin2 == -1 )
	{
		m_questData.m_completeQuest_Length = 0;
	}
	else
	{
		CZLib zlib;
		unsigned long unZipLength = sizeof(m_questData.m_completeQuest_Data);
		int error = zlib.CZLib::Uncompress(m_questData.m_completeQuest_Data, &unZipLength, zipCompleteQuestBuff, cbstoredbin2);
		if( error != 0 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "QuestEvent Complete queue uncompress: error %d, AID:%d,GID:%d\n", error, m_AID, m_GID);
			return NAsyncDBWork::RETURN_ERROR;
		}

		m_questData.m_completeQuest_Length = unZipLength;
	}

	if( cbstoredbin3 == -1 )
	{
		m_questData.m_quest_hunt_Length = 0;
	}
	else
	{
		CZLib zlib;
		unsigned long unZipLength = 4000; //FIXME: should be sizeof(m_questData.m_quest_hunt_Data)
		unsigned long error = zlib.CZLib::Uncompress(m_questData.m_quest_hunt_Data, &unZipLength, zipQuest_HuntBuff, cbstoredbin3);
		if( error != 0 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "QuestEvent Hunting List uncompress: error %d, AID:%d,GID:%d\n", error, m_AID, m_GID);
			return NAsyncDBWork::RETURN_ERROR;
		}

		m_questData.m_quest_hunt_Length = unZipLength;
	}

	if( cbstoredbin4 == -1 )
	{
		m_questData.m_quest_time_Length = 0;
	}
	else
	{
		CZLib zlib;
		unsigned long unZipLength = sizeof(m_questData.m_quest_time_Data);
		int error = zlib.CZLib::Uncompress(m_questData.m_quest_time_Data, &unZipLength, zipQuest_TimeBuff, cbstoredbin4);
		if( error != 0 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "QuestEvent Hunting List uncompress: error %d, AID:%d,GID:%d\n", error, m_AID, m_GID);
			return NAsyncDBWork::RETURN_ERROR;
		}

		m_questData.m_quest_time_Length = unZipLength;
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}
