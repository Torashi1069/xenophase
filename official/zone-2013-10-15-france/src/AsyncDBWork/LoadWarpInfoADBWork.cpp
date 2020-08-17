#include "AsyncDBWork/LoadWarpInfoADBWork.h"
#include "AsyncDBWork/NODBCHandler.h"


CLoadWarpInfoADBWork::CLoadWarpInfoADBWork(const unsigned long in_AID, const unsigned long in_GID, const int in_LoadType)
: NAsyncDBWork(TYPE_LOAD_WARPINFO),
  m_Result(RESULT_ERROR_UNKNOWN),
  m_LoadType(in_LoadType),
  m_GID(in_GID),
  m_WarpInfo()
{
	this->NAsyncDBWork::Init(in_AID);
}


CLoadWarpInfoADBWork::~CLoadWarpInfoADBWork()
{
}


const CLoadWarpInfoADBWork::enumResult CLoadWarpInfoADBWork::GetResult()
{
	return m_Result;
}


const unsigned long CLoadWarpInfoADBWork::GetGID()
{
	return m_GID;
}


const WARPPORTAL_INFO& CLoadWarpInfoADBWork::GetWarpInfo()
{
	return m_WarpInfo;
}


const int CLoadWarpInfoADBWork::GetLoadType()
{
	return m_LoadType;
}


namespace {
SQLRETURN InsertWarpInfo(NODBCCtrl& in_CharacterODBCCtrl, const int in_GID)
{
	NODBCHandler Handler(in_CharacterODBCCtrl);

	SQLINTEGER cbGID = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&in_GID), 0, 0);

	SQLRETURN ret = Handler.NODBCHandler::ExecDirect("{call InsertWarpInfo(?)}");
	if( !SQL_SUCCEEDED(ret) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return ret;
	}

	return ret;
}
}; // namespace


namespace {
SQLRETURN LoadWarpInfo(NODBCCtrl& in_CharacterODBCCtrl, const int in_GID, WARPPORTAL_INFO& out_WarpInfo)
{
	NODBCHandler Handler(in_CharacterODBCCtrl);

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&in_GID), 0, 0);
	SQLRETURN ret = Handler.NODBCHandler::ExecDirect("{call usp_GetWarpInfo(?)}");
	if( !SQL_SUCCEEDED(ret) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return ret;
	}

	Handler.NODBCHandler::BindCol(1, SQL_C_CHAR, out_WarpInfo.mapName[0], sizeof(out_WarpInfo.mapName[0]), &cbChar);
	Handler.NODBCHandler::BindCol(2, SQL_C_SSHORT, &out_WarpInfo.xPos[0], 0, &cbInt);
	Handler.NODBCHandler::BindCol(3, SQL_C_SSHORT, &out_WarpInfo.yPos[0], 0, &cbInt);
	Handler.NODBCHandler::BindCol(4, SQL_C_CHAR, &out_WarpInfo.mapName[1], sizeof(out_WarpInfo.mapName[1]), &cbChar);
	Handler.NODBCHandler::BindCol(5, SQL_C_SSHORT, &out_WarpInfo.xPos[1], 0, &cbInt);
	Handler.NODBCHandler::BindCol(6, SQL_C_SSHORT, &out_WarpInfo.yPos[1], 0, &cbInt);
	Handler.NODBCHandler::BindCol(7, SQL_C_CHAR, &out_WarpInfo.mapName[2], sizeof(out_WarpInfo.mapName[2]), &cbChar);
	Handler.NODBCHandler::BindCol(8, SQL_C_SSHORT, &out_WarpInfo.xPos[2], 0, &cbInt);
	Handler.NODBCHandler::BindCol(9, SQL_C_SSHORT, &out_WarpInfo.yPos[2], 0, &cbInt);
	ret = Handler.NODBCHandler::Fetch();
//	if( !SQL_SUCCEEDED(ret) )
//	{
//		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
//		return ret;
//	}

	return ret;
}
}; // namespace


bool CLoadWarpInfoADBWork::ExecQuery(NODBCCtrl& in_CharacterODBCCtrl)
{
	SQLRETURN loadRet = LoadWarpInfo(in_CharacterODBCCtrl, m_GID, m_WarpInfo);
	if( SQL_SUCCEEDED(loadRet) )
	{
		if( loadRet != SQL_NO_DATA )
			return false;
		
		SQLRETURN insertRet = InsertWarpInfo(in_CharacterODBCCtrl, m_GID);
		if( !SQL_SUCCEEDED(insertRet) )
		{
			if( insertRet != SQL_NO_DATA )
				return false;
		}
	}

	m_Result = CLoadWarpInfoADBWork::RESULT_SUCCESS;
	return true;
}
