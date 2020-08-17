#pragma once
#include "NetLib/AsyncStream.h"
#include "NetLib/Connector.h"
#include "NetLib/PacketHandler.h"


class CSvrIO
{
public:
	struct vtable_t // const CSvrIO::`vftable'
	{
		void* (CSvrIO::* scalar_deleting_destructor)(unsigned int flags);
		int (CSvrIO::* OnProcess)(void);
		void (CSvrIO::* OnCustomInit)(void);
	};

	class COnline
	{
	public:
		/* this+ 0 */ private: RTL_CRITICAL_SECTION m_CS;
		/* this+24 */ private: bool m_isOnline;

		public: CSvrIO::COnline::COnline(void);
		public: CSvrIO::COnline::~COnline(void);
		public: operator bool(void);
		public: void CSvrIO::COnline::operator =(bool in_rhs);
		//public: bool CSvrIO::COnline::operator ==(bool in_rhs);
		//public: bool CSvrIO::COnline::operator !=(bool);
	};

	/* this+    0 */ //const CSvrIO::`vftable';
	/* this+    4 */ protected: CPacketHandler* m_packetHandler;
	/* this+    8 */ protected: CConnector m_connector;
	/* this+   12 */ protected: CAsyncStream m_asyncStream;
	/* this+20700 */ protected: unsigned int m_connectThreadID;
	/* this+20704 */ protected: unsigned long m_ip;
	/* this+20708 */ protected: short m_port;
	/* this+20712 */ protected: CSvrIO::COnline m_isOnline;

	public: CSvrIO::CSvrIO(void);
	public: virtual CSvrIO::~CSvrIO(void);
	public: int CSvrIO::Init(unsigned long ip, short port, CPacketHandler* ph);
	public: int CSvrIO::ProcMsg(void);
	public: virtual int CSvrIO::OnProcess(void);
	public: void CSvrIO::Send(int len, const char* buf);
	public: void CSvrIO::OnClose(void);
	public: const bool CSvrIO::isOnline(void);
	protected: virtual void CSvrIO::OnCustomInit(void);
	protected: int CSvrIO::Connect(void);

private:
	static hook_method<int (CSvrIO::*)(unsigned long ip, short port, CPacketHandler* ph)> CSvrIO::_Init;
	static hook_method<int (CSvrIO::*)(void)> CSvrIO::_ProcMsg;
	static hook_method<int (CSvrIO::*)(void)> CSvrIO::_OnProcess;
	static hook_method<void (CSvrIO::*)(int len, const char* buf)> CSvrIO::_Send;
	static hook_method<void (CSvrIO::*)(void)> CSvrIO::_OnClose;
	static hook_method<const bool (CSvrIO::*)(void)> CSvrIO::_isOnline;
	static hook_method<void (CSvrIO::*)(void)> CSvrIO::_OnCustomInit;
	static hook_method<int (CSvrIO::*)(void)> CSvrIO::_Connect;
};
