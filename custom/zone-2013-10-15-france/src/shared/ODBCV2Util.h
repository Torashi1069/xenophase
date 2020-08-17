#pragma once


class CODBCV2Util
{
private:
	/* this+0 */ //const CODBCV2Util::`vftable';
	/* static */ static CODBCV2Util*& m_cpSelf; //TODO

public:
	static CODBCV2Util* GetObj();
	std::string GetErrorString(const SQLSMALLINT in_HandleType, const SQLHANDLE in_Handle);
	bool AddSystemDSN(const std::string in_strDSN, const std::string in_ServerIP, const std::string in_strDBName);

private:
	CODBCV2Util();
	virtual ~CODBCV2Util();
};
