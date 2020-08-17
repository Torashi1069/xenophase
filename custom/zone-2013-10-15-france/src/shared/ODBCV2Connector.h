#pragma once


class CODBCV2Connector
{
public:
	enum enumConncetType
	{
		UNKNOWN_CONNECT_TYPE  = 0,
		DSN_CONNECT_TYPE      = 1,
		DRIVER_CONNECT_TYPE   = 2,
		FILE_DSN_CONNECT_TYPE = 3,
	};

protected:
	/* this+  0 */ //const CODBCV2Connector::`vftable';
	/* this+  4 */ SQLHENV m_copyhENV;
	/* this+  8 */ SQLHDBC m_copyhDBC;
	/* this+ 12 */ std::string m_strDSN;
	/* this+ 40 */ std::string m_strID;
	/* this+ 68 */ std::string m_strPassword;
	/* this+ 96 */ std::string m_strDB;
	/* this+124 */ HANDLE m_hThread;
	/* this+128 */ const enumConncetType m_ConnectType;

	class CState
	{
	public:
		enum enumState
		{
			STATE_DISCONNECT  = 0,
			STATE_CONNECT     = 1,
			STATE_CONNECT_TRY = 2,
		};

	private:
		/* this+ 0 */ RTL_CRITICAL_SECTION m_CS;
		/* this+24 */ enumState m_State;

	public:
		operator enumState();
		void operator=(enumState in_rhs);
		bool operator==(const enumState& in_Rhs);
		bool operator!=(const enumState& in_Rhs);

	public:
		CState(const enumState in_State);
		~CState();
	};

protected:
	/* this+132 */ CState m_State;

private:
	static unsigned int __stdcall ThreadFunctionCaller(void* in_pParam);
	bool Connect();

private:
	/* this+160 */ std::string m_strFileDSN;

protected:
	bool isConnect();
	void AsyncConnect();
	void Disconnect();
	void SyncConnect();

protected:
	CODBCV2Connector(const SQLHENV in_hENV, const SQLHDBC in_hDBC, std::string in_strFileDSN, std::string in_strPassword, enumConncetType in_ConnectType);
	virtual ~CODBCV2Connector();

private:
	friend class CODBCV2;
};
