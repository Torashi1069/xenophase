#include "CharacterMgr.h"
#include "ZSAcceptHandler.h"
#include "shared.h" // Trace


CZSAcceptHandler::CZSAcceptHandler(void) // line 10-13
{
	m_acceptable = 0;
}


CZSAcceptHandler::~CZSAcceptHandler(void) // line 15-16
{
}


hook_method<int (CZSAcceptHandler::*)(int streamPoolSize)> CZSAcceptHandler::_Init(SERVER, "CZSAcceptHandler::Init");
int CZSAcceptHandler::Init(int streamPoolSize) // line 54-56
{
	return (this->*_Init)(streamPoolSize);

	return m_streamPool.Init(streamPoolSize);
}


hook_method<int (CZSAcceptHandler::*)(unsigned int s, unsigned long ip)> CZSAcceptHandler::_OnConnect(SERVER, "CZSAcceptHandler::OnConnect");
int CZSAcceptHandler::OnConnect(unsigned int s, unsigned long ip) // line 20-51
{
	return (this->*_OnConnect)(s, ip);

	if( m_acceptable == 0 )
	{
		Trace("CZSAcceptHandler :: m_acceptable is false!");
		return 0;
	}

	CAsyncStream* stream = this->CZSAcceptHandler::AllocStream();
	if( stream == NULL )
		return 0;

	CPC* pc = g_characterMgr->CCharacterMgr::AllocPC();
	if( pc != NULL )
	{
		stream->CAsyncStream::Init(pc->CPC::GetPacketHandler());
		pc->CPC::Init(stream, ip);

		if( g_characterMgr->CCharacterMgr::AddCharacter(pc) )
		{
			if( stream->CAsyncStream::Open(s) )
			{
				return true;
			}
			else
			{
				g_characterMgr->CCharacterMgr::RemoveCharacter(pc);
				return false;
			}
		}

		g_characterMgr->CCharacterMgr::Free(pc);
	}

	this->CZSAcceptHandler::FreeStream(stream);
	return false;
}


//hook_method<CAsyncStream* (CZSAcceptHandler::*)(void)> CZSAcceptHandler::_AllocStream(SERVER, "CZSAcceptHandler::AllocStream");
CAsyncStream* CZSAcceptHandler::AllocStream(void) // line ???
{
//	return (this->*_AllocStream)();

	return m_streamPool.CMemoryMgr<CAsyncStream>::Alloc();
}


//hook_method<void (CZSAcceptHandler::*)(CAsyncStream* stream)> CZSAcceptHandler::_FreeStream(SERVER, "CZSAcceptHandler::FreeStream");
void CZSAcceptHandler::FreeStream(CAsyncStream* stream) // line ???
{
//	return (this->*_FreeStream)(stream);

	m_streamPool.CMemoryMgr<CAsyncStream>::Free(stream);
}


//hook_method<void (CZSAcceptHandler::*)(int acceptable)> CZSAcceptHandler::_SetAccpetable(SERVER, "CZSAcceptHandler::SetAccpetable");
void CZSAcceptHandler::SetAccpetable(int acceptable) // line ???
{
//	return (this->*_SetAccpetable)(acceptable);

	m_acceptable = acceptable;
}


//hook_method<int (CZSAcceptHandler::*)(void)> CZSAcceptHandler::_GetAcceptable(SERVER, "CZSAcceptHandler::GetAcceptable");
int CZSAcceptHandler::GetAcceptable(void) // line ???
{
//	return (this->*_GetAcceptable)();

	return m_acceptable;
}
