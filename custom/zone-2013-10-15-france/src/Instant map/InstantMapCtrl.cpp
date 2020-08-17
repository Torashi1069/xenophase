#include "Instant map/InstantMapCtrl.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/N3System/N3MessageMgr.h"


CInstantMapCtrl::CInstantMapCtrl(const unsigned int in_hRequestN2Obj, const int in_hInstantMapID, const std::string in_MapName, const int in_MapType) // 60-68
: N3Object(), N3Inter(),
  m_hInstantMapID(in_hInstantMapID),
  m_MapName(in_MapName),
  m_MapType(in_MapType),
  m_hRequestN2Obj(in_hRequestN2Obj),
  m_cpInstantMapRes(NULL),
  m_MessageQueue(),
  m_bOK(false),
  m_ScriptFirstEventRequestTM(0),
  m_State(STATE_CREATE),
  m_ProcessFuncPtr(&CInstantMapCtrl::ProcCreate)
{
	if( this->N3Object::GetMyID() == 0 )
		return; // ???

	N3MessageMgr::GetObj()->N3MessageMgr::Insert(this->N3Object::GetMyID(), this);
	m_ProcessFuncPtr = &CInstantMapCtrl::ProcCreate;
	N3MessageMgr::GetObj()->N3MessageMgr::Post(this->N3Object::GetMyID(), 0x650001, 0, 0);
	m_bOK = true;
}


CInstantMapCtrl::~CInstantMapCtrl()
{
	//TODO
/*
	g_mapResMgr.CMapResMgr::InstantMapRemove(m_cpInstantMapRes);

	if( m_cpInstantMapRes != NULL )
	{
		delete m_cpInstantMapRes;
		m_cpInstantMapRes = NULL;
	}

	N3MessageMgr::GetObj()->N3MessageMgr::Remove(this->N3Object::GetMyID(), this);
*/
}


void CInstantMapCtrl::ProcOperation(const int in_Message, const int in_wParam, const int in_lParam)
{
	//TODO
/*
	if( in_Message == 0x650000 )
	{
		Sleep(0);
	}
	else
	if( in_Message == 0x650002 )
	{
		CMapInfoMgr::GetObj()->CMapInfoMgr::SetPlayerEnter(m_MapName, false);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Request Destroy InstantMap");
		m_ProcessFuncPtr = &CInstantMapCtrl::ProcDestroy;
		N3MessageMgr::GetObj()->N3MessageMgr::Post(this->N3Object::GetMyID(), 0x650000, 0, 0);
	}
	else
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown message receive(Msg:0x%X)", in_Message);
	}
*/
}


void CInstantMapCtrl::ProcDestroy(const int in_Message, const int in_wParam, const int in_lParam)
{
	//TODO
}


void CInstantMapCtrl::ProcCreate_MSG_REQUEST_MAPLOADING()
{
	//TODO
}


void CInstantMapCtrl::ProcCreate_WorkerThread_MSG_RESPONSE_WORK(const CIMWTWork* in_cpWork)
{
	//TODO
}


void CInstantMapCtrl::ProcCreate(const int in_Message, const int in_wParam, const int in_lParam)
{
	//TODO
}


void CInstantMapCtrl::Process()
{
	N3MessageQueue::RETGET ret = m_MessageQueue.N3MessageQueue::Get();
	if( std::tr1::get<0>(ret) == true )
	{
		const unsigned int Message = std::tr1::get<1>(ret);
		const unsigned int wParam = std::tr1::get<2>(ret);
		const unsigned int lParam = std::tr1::get<3>(ret);

		(this->*m_ProcessFuncPtr)(Message, wParam, lParam);
	}
}


void CInstantMapCtrl::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}


const bool CInstantMapCtrl::isOK() const
{
	return m_bOK;
}


const std::string CInstantMapCtrl::GetMapName() const
{
	return m_MapName;
}


const int CInstantMapCtrl::GetMapID() const
{
	return m_hInstantMapID;
}


const unsigned int CInstantMapCtrl::GetRequestN2Obj() const
{
	return m_hRequestN2Obj;
}


CInstantMapRes* CInstantMapCtrl::GetMapResPtr()
{
	return m_cpInstantMapRes;
}


const bool CInstantMapCtrl::IsDestroyReady()
{
	return false;
	//TODO
}
