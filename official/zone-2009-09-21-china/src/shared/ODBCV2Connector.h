#pragma once
#include "std/string"
#include <sql.h>


class CODBCV2Connector
{
public:
	class CState
	{
	public:
		enum enumState
		{
			STATE_DISCONNECT = 0x0,
			STATE_CONNECT = 0x1,
			STATE_CONNECT_TRY = 0x2,
		};

		/* this+0x0  */ private: RTL_CRITICAL_SECTION m_CS;
		/* this+0x18 */ private: enum CODBCV2Connector::CState::enumState m_State;

		//public: enum CODBCV2Connector::CState::enumState operator enum CODBCV2Connector::CState::enumState();
		//public: bool CODBCV2Connector::CState::operator==(const enum CODBCV2Connector::CState::enumState &);
		//public: bool CODBCV2Connector::CState::operator!=(const enum CODBCV2Connector::CState::enumState &);
		public: CODBCV2Connector::CState::CState(const enum CODBCV2Connector::CState::enumState in_State);
		public: CODBCV2Connector::CState::~CState(void);
	};

	public: enum enumConnectType
	{
		UNKNOWN_CONNECT_TYPE = 0x0,
		DSN_CONNECT_TYPE = 0x1,
		DRIVER_CONNECT_TYPE = 0x2,
	};

	/* this+0x0  */ //const CODBCV2Connector::`vftable'
	/* this+0x4  */ protected: SQLHENV m_copyhENV;
	/* this+0x8  */ protected: SQLHDBC m_copyhDBC;
	/* this+0xC  */ protected: mystd::string m_strDSN;
	/* this+0x28 */ protected: mystd::string m_strID;
	/* this+0x44 */ protected: mystd::string m_strPassword;
	/* this+0x60 */ protected: mystd::string m_strDB;
	/* this+0x7C */ protected: HANDLE m_hThread;
	/* this+0x80 */ protected: const enum CODBCV2Connector::enumConnectType m_ConnectType;
	/* this+0x84 */ protected: CODBCV2Connector::CState m_State;

	//private: static unsigned int CODBCV2Connector::ThreadFunctionCaller(void *);
	private: bool CODBCV2Connector::Connect(void);
	protected: bool CODBCV2Connector::isConnect(void);
	protected: void CODBCV2Connector::AsyncConnect(void);
	protected: void CODBCV2Connector::Disconnect(void);
	protected: void CODBCV2Connector::SyncConnect(void);
	protected: CODBCV2Connector::CODBCV2Connector(void* const, void* const, mystd::string, mystd::string, mystd::string, mystd::string, enum CODBCV2Connector::enumConnectType);
	protected: virtual CODBCV2Connector::~CODBCV2Connector(void);

private:
	static hook_method<bool (CODBCV2Connector::*)(void)> CODBCV2Connector::_Connect;
	static hook_method<bool (CODBCV2Connector::*)(void)> CODBCV2Connector::_isConnect;
	static hook_method<void (CODBCV2Connector::*)(void)> CODBCV2Connector::_AsyncConnect;
	static hook_method<void (CODBCV2Connector::*)(void)> CODBCV2Connector::_Disconnect;
	static hook_method<void (CODBCV2Connector::*)(void)> CODBCV2Connector::_SyncConnect;

	friend class CODBCV2;
};
