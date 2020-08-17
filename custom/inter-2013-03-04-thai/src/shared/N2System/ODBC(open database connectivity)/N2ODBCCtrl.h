#pragma once


class N2ODBCCtrl
{
private:
	/* this+ 0 */ //const N2ODBCCtrl::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ SQLHENV m_hEnv;
	/* this+12 */ SQLHDBC m_hDbc;
	/* this+16 */ bool m_bConnect;

private:
	bool Init();

public:
	bool isOK() const;
	bool Connect(const std::string in_strConnectionStr);
	void Disconnect();
	operator SQLHDBC();
	const bool isConnect();
	void OutputErrorString(const SQLSMALLINT in_Type, const SQLHANDLE in_Handle, const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage);
	std::string GetErrorString(const SQLSMALLINT in_HandleType, const SQLHANDLE in_Handle);

public:
	N2ODBCCtrl();
	virtual ~N2ODBCCtrl();
};
