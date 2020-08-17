#pragma once


namespace N2ObjectGroupID {
enum {
	CInstantMapMgr          = 0,
	CInstantMap             = 1,
	CMemorialDungeonMgr     = 2,
	CMemorialDungeon        = 3,
	ISAsyncDBMgr            = 4,
	ISAsyncDBThread         = 5,
	AsyncConnectMgr         = 6,
	Object                  = 7,
	CInstantMapWorkerThread = 100,
	CInstantMapCtrl         = 101,
};
}; // namespace


class N2Object
{
private:
	/* this+0 */ //const N2Object::`vftable';
	/* this+4 */ const unsigned int m_MyID;

public:
	const unsigned int GetMyID();
	const unsigned short GetMyGroupID();

public:
	N2Object(const unsigned short in_GroupID);
	virtual ~N2Object();
};
