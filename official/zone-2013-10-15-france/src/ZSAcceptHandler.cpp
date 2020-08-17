#include "CharacterMgr.h"
#include "ZSAcceptHandler.h"


CZSAcceptHandler::CZSAcceptHandler()
{
	m_acceptable = false;
}


CZSAcceptHandler::~CZSAcceptHandler()
{
}


hook_func<BOOL (CZSAcceptHandler::*)(SOCKET s, DWORD ip)> CZSAcceptHandler__OnConnect(EXEPATH(), "CZSAcceptHandler::OnConnect");
BOOL CZSAcceptHandler::OnConnect(SOCKET s, DWORD ip)
{
	return (this->*CZSAcceptHandler__OnConnect)(s, ip);

	//TODO
/*
	if( !m_acceptable )
		return FALSE;
	
	CAsyncStream* stream = this->CZSAcceptHandler::AllocStream();
	if( stream == NULL )
		return FALSE;

	CPC* pc = CCharacterMgr::GetObj()->CCharacterMgr::AllocPC();
	if( pc == NULL )
	{
		this->CZSAcceptHandler::FreeStream(stream);
		return FALSE;
	}

	stream->Init(pc->CPC::GetPacketHandler());
	pc->CPC::Init(stream, ip);

	if( !CCharacterMgr::GetObj()->CCharacterMgr::AddCharacter(pc) )
	{
		CCharacterMgr::GetObj()->CCharacterMgr::Free(pc);
		this->CZSAcceptHandler::FreeStream(stream);
		return FALSE;
	}

	if( !stream->Open(s) )
	{
		CCharacterMgr::GetObj()->CCharacterMgr::RemoveCharacter(pc);
		return FALSE;
	}

	return TRUE;
*/
}


BOOL CZSAcceptHandler::Init(int streamPoolSize)
{
	return m_streamPool.CMemoryMgr<CAsyncStream>::Init(streamPoolSize);
}


CAsyncStream* CZSAcceptHandler::AllocStream()
{
	return m_streamPool.CMemoryMgr<CAsyncStream>::Alloc();
}


void CZSAcceptHandler::FreeStream(CAsyncStream* stream)
{
	m_streamPool.CMemoryMgr<CAsyncStream>::Free(stream);
}


void CZSAcceptHandler::SetAccpetable(BOOL b)
{
	m_acceptable = b;
}


BOOL CZSAcceptHandler::GetAcceptable()
{
	return m_acceptable;
}
