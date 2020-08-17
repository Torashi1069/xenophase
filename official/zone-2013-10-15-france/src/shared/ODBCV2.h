#pragma once
#include "shared/ODBCV2Connector.h"


class CODBCV2
{
private:
	/* this+ 0 */ //const CODBCV2::`vftable';
	/* this+ 4 */ SQLHENV m_henv;
	/* this+ 8 */ SQLHDBC m_hdbc;
	/* this+12 */ CODBCV2Connector* m_cpConnector;

public:
	bool Init(const std::string in_strDsnFile, const std::string in_strPassword, const CODBCV2Connector::enumConncetType in_eConnectType, const bool in_bConnect);
	SQLHDBC const GetDBCHandle();
	void Disconnect();
	void AsyncConnect();
	bool SyncConnect();

public:
	CODBCV2();
	virtual ~CODBCV2();
};
