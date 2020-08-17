#include "GVar.h"
#include "AsyncDBWork/Effect3rd.h"
#include "AsyncDBWork/NASyncDBWork.h"
#include "AsyncDBWork/NODBCHandler.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/ZLib.h"


namespace {
class CNAsyncDBWorkIdentityGenerator
{
public:
	int operator()()
	{
		++m_IdentityCnt;
		if( m_IdentityCnt < MINIMUM_IDENTITY )
			m_IdentityCnt = MINIMUM_IDENTITY;

		return m_IdentityCnt;
	}

private:
	/* this+0 */ int m_IdentityCnt;

private:
	enum { MINIMUM_IDENTITY = 100 };

public:
	CNAsyncDBWorkIdentityGenerator() : m_IdentityCnt(MINIMUM_IDENTITY) { }
	~CNAsyncDBWorkIdentityGenerator() { }
};

CNAsyncDBWorkIdentityGenerator& NAsyncDBWorkIdentityGenerator = VTOR<CNAsyncDBWorkIdentityGenerator>(DetourFindFunction(EXEPATH(), "?NAsyncDBWorkIdentityGenerator@?A0xcd9f9e86@@3VCNAsyncDBWorkIdentityGenerator@1@A"));
}; // namespace


NAsyncDBWork::NAsyncDBWork(const enumType in_Type)
: m_Type(in_Type), m_ID(0), m_StartTM(timeGetTime()), m_Identity(0)
{
}


NAsyncDBWork::~NAsyncDBWork()
{
}


void NAsyncDBWork::Init(const unsigned int in_ID)
{
	m_ID = in_ID;
	m_StartTM = timeGetTime();
	m_Identity = NAsyncDBWorkIdentityGenerator();
}


const NAsyncDBWork::enumType NAsyncDBWork::GetType() const
{
	return m_Type;
}


const unsigned int NAsyncDBWork::GetID() const
{
	return m_ID;
}


const DWORD NAsyncDBWork::GetStartTM() const
{
	return m_StartTM;
}


const int NAsyncDBWork::GetIdentity() const
{
	return m_Identity;
}


NAsyncDBWork::enumRETURN NAsyncDBWork::SaveBodyItem(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const unsigned char* in_pBodyItemDataBuffer, const int in_Length) // 163-233
{
	return NAsyncDBWork::RETURN_ERROR;
	//TOOD
}


NAsyncDBWork::enumRETURN NAsyncDBWork::SaveCharacterInfo(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const char* in_pCharName, CHARINFO_TO_CHARACTERDB& info) // 353-490
{
	return NAsyncDBWork::RETURN_ERROR;
	//TOOD
}


NAsyncDBWork::enumRETURN NAsyncDBWork::SaveEffect3rd(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, std::vector<Effect3rd::tagEffect3rdDBFmt> in_List) // 534-560
{
	NODBCHandler Handler(in_ODBCCtrl);

	Effect3rd::tagEffect3rdDBFmt Effect;
	SQLINTEGER cbInt = 0;

	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<unsigned long*>(&in_GID), 0, &cbInt);
	Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Effect.ID, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Effect.TimeMS, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Effect.Data1, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Effect.Data2, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Effect.Data3, 0, &cbInt);

	for( std::vector<Effect3rd::tagEffect3rdDBFmt>::iterator iter = in_List.begin(); iter != in_List.end(); ++iter )
	{
		memcpy(&Effect, &*iter, sizeof(Effect));

		if( !SQL_SUCCEEDED(Handler.NODBCHandler::ExecDirect("{call usp_effect_Rebuild_update(?, ?, ?, ?, ?, ?)}")) )
		{
			Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
			return NAsyncDBWork::RETURN_ERROR_ODBC;
		}
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}


NAsyncDBWork::enumRETURN NAsyncDBWork::Skill3rd_Update(NODBCCtrl& in_ODBCCtrl, const int in_GID, const int in_ID, const int in_Level, const int in_RemainMS, const int in_Attr, const int in_Data) // 648-667
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}


NAsyncDBWork::enumRETURN NAsyncDBWork::SaveStoreItem(NODBCCtrl& in_ODBCCtrl, const unsigned long in_AID, const unsigned char* in_pData, const int in_Length) // 771-807
{
	return NAsyncDBWork::RETURN_ERROR;
	//TOOD
}


NAsyncDBWork::enumRETURN NAsyncDBWork::SaveCartItem(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const unsigned char* in_pData, const int in_Length) // 912-949
{
	NODBCHandler Handler(in_ODBCCtrl);

	if( in_Length <= 0 )
	{
		unsigned long GID = in_GID;
		SQLINTEGER cbGID = 0;
		Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

		if( !SQL_SUCCEEDED(Handler.NODBCHandler::ExecDirect("{call UpdateItemCart(NULL, ?)}")) )
		{
			Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
			return NAsyncDBWork::RETURN_ERROR_ODBC;
		}

		return NAsyncDBWork::RETURN_SUCCESS;
	}
	else
	{
		BYTE CompressBuffer[16300];
		memset(CompressBuffer, 0x00, sizeof(CompressBuffer));
		unsigned long destLen = sizeof(CompressBuffer) - 2;

		CZLib zlib;
		int zRet = zlib.CZLib::Compress(CompressBuffer + 2, &destLen, in_pData + 2, in_Length - 2, 6);
		if( zRet != 0 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "item compress: error %d\n", zRet);
			return NAsyncDBWork::RETURN_ERROR;
		}

		int maxsize = CGVar::GetObj()->CGVar::GetDBColumnSizeCartItem();
		int totalsize = destLen + 2;
		if( totalsize > maxsize * 0.8L )
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "cart item db column size %d/%d warning", totalsize, maxsize);

		*(WORD*)CompressBuffer = 4; // version

		unsigned long GID = in_GID;
		SQLINTEGER cbcartbin = totalsize;
		SQLINTEGER cbGID = 0;
		Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, totalsize, 0, CompressBuffer, 0, &cbcartbin);
		Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &GID, 0, &cbGID);

		if( !SQL_SUCCEEDED(Handler.NODBCHandler::ExecDirect("{call UpdateItemCart(?, ?)}")) )
		{
			Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
			return NAsyncDBWork::RETURN_ERROR_ODBC;
		}

		return NAsyncDBWork::RETURN_SUCCESS;
	}
}


NAsyncDBWork::enumRETURN NAsyncDBWork::SaveQuestEvent(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const unsigned char* in_pData_quest, const int in_Length_quest, const unsigned char* in_pData_hunt, const int in_Length_hunt, const unsigned char* in_pData_time, const int in_Length_time, const unsigned char* in_pData_completeQueue, const int in_Length_completeQueue) // 976-1069
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}


NAsyncDBWork::enumRETURN NAsyncDBWork::UpdateHomunEffect(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const std::vector<Effect3rd::tagEffect3rdDBFmt>& in_List) // 1081-1102
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}


NAsyncDBWork::enumRETURN NAsyncDBWork::DeleteHomunEffectAll(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID) // 1105-1116
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}


NAsyncDBWork::enumRETURN NAsyncDBWork::SaveHomunSkill(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const std::map<unsigned short,HO_SKINFO>& in_Skill) // 1119-1141
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}


NAsyncDBWork::enumRETURN NAsyncDBWork::SaveHomunData(NODBCCtrl& in_ODBCCtrl, const unsigned long in_GID, const HomunDataStuff::CHomunData& in_HomunData) // 1147-1155
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}
