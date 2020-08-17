#pragma once


class NODBCCtrl
{
private:
	/* this+ 0 */ //const NODBCCtrl::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ SQLHENV m_hEnv;
	/* this+12 */ SQLHDBC m_hDbc;

private:
	bool Init();

public:
	bool isOK() const;
	bool Connect(const std::string in_strConnectionStr);
	void Disconnect();
	operator SQLHDBC();
	void OutputErrorString(const short in_Type, void* const in_Handle, const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage);

public:
	NODBCCtrl();
	virtual ~NODBCCtrl();
};
