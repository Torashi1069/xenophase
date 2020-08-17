#pragma once


class N2SystemMgr
{
private:
	/* static */ static N2SystemMgr*& m_cpSelf; //TODO
	/* this+0 */ //const N2SystemMgr::`vftable';
	/* this+4 */ bool m_bOK;

private:
	bool Create();
	void Destory();

public:
	const bool isOK() const;
	static bool CreateInstance();
	static void DestoryInstance();

private:
	N2SystemMgr();
	virtual ~N2SystemMgr();
};
