#pragma once
class N2ODBCCtrl;


class N2DBLog
{
private:
	/* this+0 */ //const N2DBLog::`vftable';
	/* this+4 */ bool m_bOK;

public:
	bool isOK() const;

private:
	virtual bool Run(N2ODBCCtrl& in_ODBCCtrl);

public:
	N2DBLog();
	virtual ~N2DBLog();

	friend class N2DBLogThread; // Run()
};
