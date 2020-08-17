#include "NetLib/PacketHandler.h"
#include "AutoCS.hpp"
#include "ErrorLog.h"
#include "ServerInfo.h"
#include "SvrIO.h"
#include "ZSAcceptHandler.h"
#include "Common/Packet.h"
#include "globals.hpp"
#include "shared.h"
#include <process.h>


unsigned int __stdcall ServerConnectThread(void* p) // line 10-14
{
	CSvrIO* self = reinterpret_cast<CSvrIO*>(p);
	self->CSvrIO::ProcMsg();
	return 1;
}


CSvrIO::CSvrIO(void) : m_asyncStream(10240000, 10240000) // line 21
{
	m_isOnline = false;
	m_packetHandler = NULL;
}


CSvrIO::~CSvrIO(void) // line 27
{
	if( m_packetHandler )
		delete m_packetHandler;
}


hook_method<int (CSvrIO::*)(unsigned long ip, short port, CPacketHandler* ph)> CSvrIO::_Init(SERVER, "CSvrIO::Init");
int CSvrIO::Init(unsigned long ip, short port, CPacketHandler* ph) // line 39
{
	return (this->*_Init)(ip, port, ph);

	if( ph == NULL )
	{
		MessageBoxA(0, "invalid packet handler for CSvrIO::Init", NULL, MB_OK);
		exit(EXIT_FAILURE);
	}
        
	m_ip = ip;
	m_port = port;
	m_packetHandler = ph;
	
	m_asyncStream.CAsyncStream::Init(ph);
	m_asyncStream.CAsyncStream::SetRecvQueueSize(8192000);
	
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &ServerConnectThread, this, 0, &m_connectThreadID);
	if( hThread == NULL )
	{
		MessageBoxA(0, "_beginthreadex() failed", NULL, MB_ICONHAND);
		ExitProcess(EXIT_FAILURE);
	}
	CloseHandle(hThread);
	return 1;
}


hook_method<int (CSvrIO::*)(void)> CSvrIO::_ProcMsg(SERVER, "CSvrIO::ProcMsg");
int CSvrIO::ProcMsg(void) // line 62
{
	return (this->*_ProcMsg)();

	tagMSG msg;
	PeekMessageA(&msg, 0, 0x400u, 0x400u, 0);

	if( !PostThreadMessageA(m_connectThreadID, 0x400u, 0, 0) )
		Trace("PostThreadMessage() failed : %d", GetLastError());

	static bool character_svr;
	static short character_port = g_serverInfo->CServerInfo::GetServerPrivatePort(g_serverInfo->CServerInfo::GetDestinationSID(1));
	if( character_port == 0 )
		character_port = g_serverInfo->CServerInfo::GetServerPort(g_serverInfo->CServerInfo::GetDestinationSID(1));

	static bool inter_svr;
	static short inter_port = g_serverInfo->CServerInfo::GetServerPrivatePort(g_serverInfo->CServerInfo::GetDestinationSID(2));
	if( inter_port == 0 )
		inter_port = g_serverInfo->CServerInfo::GetServerPort(g_serverInfo->CServerInfo::GetDestinationSID(2));

	while( GetMessageA(&msg, 0, 0, 0) )
	{
		switch( msg.message )
		{
		case 0x400u:
		{
			if( !this->CSvrIO::Connect() )
			{
				OutputDebugStringA("CSvrIO::Connect() failed\n");

				Sleep(5000);

				if( !PostThreadMessageA(m_connectThreadID, 0x400u, 0, 0) )
					Trace("PostThreadMessage() failed : %d", GetLastError());

				break;
			}

			m_isOnline = true;

			if( m_port == character_port )
				character_svr = 1;

			if( m_port == inter_port )
			{
				inter_svr = 1;

				PACKET_ZI_VERSION InterVersion;
				InterVersion.PacketType = HEADER_ZI_VERSION;
				InterVersion.Version = 4;
				this->CSvrIO::Send(sizeof(InterVersion), (char*)&InterVersion);

				PACKET_ZI_EPISODE_VERSION EpisodeVersion;
				EpisodeVersion.PacketType = HEADER_ZI_EPISODE_VERSION;
				EpisodeVersion.Episode_Ver = 99999;
				EpisodeVersion.Minor_Ver = 0;
				this->CSvrIO::Send(sizeof(EpisodeVersion), (char*)&EpisodeVersion);
			}

			if( inter_svr && character_svr )
				g_zsAcceptHandler->CZSAcceptHandler::SetAccpetable(1);

			Trace("Server[ip:%s, port:%d] connected\n", inet_ntoa(*(in_addr*)&m_ip), m_port);

			char tempbuffer[256];
			if( m_port == inter_port )
				sprintf(tempbuffer, "Inter connected");
			else
				sprintf(tempbuffer, "Character connected");

			g_errorLogs->CErrorLog::CriticalErrorLog(tempbuffer, 123, ".\\SvrIO.cpp");
		}
		break;
		case 0x401u:
		{
			if( !m_isOnline )
				break;

			Trace("CSvrIO disconnected.\n");

			if( m_port == inter_port )
			{
				inter_svr = 0;

				g_zsAcceptHandler->CZSAcceptHandler::SetAccpetable(0);
			}

			m_asyncStream.CAsyncStream::Close();
			m_isOnline = false;

			if( !PostThreadMessageA(m_connectThreadID, 0x400u, 0, 0) )
				Trace("PostThreadMessage() failed : %d", GetLastError());

			char tempbuffer[256];
			if( m_port == inter_port )
				sprintf(tempbuffer, "Inter disconnected");
			else
				sprintf(tempbuffer, "Character disconnected");

			g_errorLogs->CErrorLog::CriticalErrorLog(tempbuffer, 154, ".\\SvrIO.cpp");
		}
		break;
		case 0x402u:
			return 1;
		}
	}

	return 0;
}


hook_method<int (CSvrIO::*)(void)> CSvrIO::_OnProcess(SERVER, "CSvrIO::OnProcess");
int CSvrIO::OnProcess(void) // line 207
{
	return (this->*_OnProcess)();

	return ( m_packetHandler != NULL ) ? m_packetHandler->OnProcess() : -1;
}


hook_method<void (CSvrIO::*)(int len, const char* buf)> CSvrIO::_Send(SERVER, "CSvrIO::Send");
void CSvrIO::Send(int len, const char* buf) // line 216
{
	return (this->*_Send)(len, buf);

	if( m_isOnline )
		m_asyncStream.CAsyncStream::Send(len, buf);
}


hook_method<void (CSvrIO::*)(void)> CSvrIO::_OnClose(SERVER, "CSvrIO::OnClose");
void CSvrIO::OnClose(void) // line 226
{
	return (this->*_OnClose)();

	if( !PostThreadMessageA(m_connectThreadID, 0x401u, 0, 0) )
		Trace("PostThreadMessage() failed : %d", GetLastError());

	if( m_asyncStream.CAsyncStream::GetLastError() != 0 )
	{
		char temp[256];
		sprintf(temp, "io between servers closed. port:%d , %d", m_port, m_asyncStream.CAsyncStream::GetLastError());
		g_errorLogs->CErrorLog::CriticalErrorLog(temp, 234, ".\\SvrIO.cpp");
	}
}


//hook_method<const bool (CSvrIO::*)(void)> CSvrIO::_isOnline(SERVER, "CSvrIO::isOnline");
const bool CSvrIO::isOnline(void) // line ???
{
//	return (this->*_isOnline)();

	return m_isOnline; // made up
}


//hook_method<void (CSvrIO::*)(void)> CSvrIO::_OnCustomInit(SERVER, "CSvrIO::OnCustomInit");
void CSvrIO::OnCustomInit(void) // line ???
{
//	return (this->*_OnCustomInit)();

	;
}


hook_method<int (CSvrIO::*)(void)> CSvrIO::_Connect(SERVER, "CSvrIO::Connect");
int CSvrIO::Connect(void) // line 175
{
	return (this->*_Connect)();

	Addr addr;
	addr.port = m_port;
	addr.ip = m_ip;

	SOCKET s = m_connector.Connect(addr);
	if( s == INVALID_SOCKET )
		return 0;

	m_asyncStream.CAsyncStream::Init(m_packetHandler);
	this->OnCustomInit();

	if( !m_asyncStream.CAsyncStream::Open(s) )
	{
		closesocket(s);
		return 0;
	}

	return 1;
}


CSvrIO::COnline::COnline(void) // line ??
{
	m_isOnline = false;
	InitializeCriticalSection(&m_CS);
}


CSvrIO::COnline::~COnline(void) // line ??
{
	DeleteCriticalSection(&m_CS);
}


CSvrIO::COnline::operator bool(void) // line 63 (SvrIO.h)
{
	AutoCS sync(&m_CS);
	return m_isOnline;
}


void CSvrIO::COnline::operator =(bool in_rhs) // line 68 (SvrIO.h)
{
	AutoCS sync(&m_CS);
	m_isOnline = in_rhs;
}
