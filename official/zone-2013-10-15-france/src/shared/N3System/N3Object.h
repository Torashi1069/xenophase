#pragma once


class N3Object
{
public:
	struct e { enum
	{
		NNetworkWorkThread          = 0,
		CProcessMgr                 = 1,
		C2ClientMgr                 = 2,
		C2ClientWorkThread          = 3,
		C2StreamObject              = 4,
		C2InterServerClient         = 5,
		CGlobalDBMgr                = 6,
		CGlobalWorkThread           = 7,
		CInstantMapMgr              = 8,
		CInstantMap                 = 9,
		CMemorialDungeonMgr         = 10,
		CMemorialDungeon            = 11,
		CPrivateDungeon             = 12,
		CPrivateDungeonWorkerThread = 13,
		CAdvancedDBLogMgr           = 14,
		CAdvancedDBLogThread        = 15,
		CInstantMapWorkerThread     = 100,
		CInstantMapCtrl             = 101,
		CZsvrMgr                    = 102,
		CZsvrAcceptThread           = 103,
		CMsvrMgr                    = 104,
		CMsvrAcceptThread           = 105,
		CNpcProvideExpInfoMgr       = 106,
		CCharacterWorkThread        = 107,
		CCharacterDBMgr             = 108,
		CItemTradeLogMgr            = 109,
		CItemTradeLogThread         = 110,
		CASyncDBLogMgr              = 111,
		CBankingMgr                 = 112,
		NODBCSessionMgr             = 113,
		NODBCSessionThread          = 114,
		CGuildStorageMgr            = 115,
		CUserScanLogMgr             = 116,
		CMonitoringUserMgr          = 117,
	}; };

	#define N3MSGID(_type_,_msg_) ( ((unsigned short)(N3Object::e::_type_) << 16) | ((unsigned short)(_type_::_msg_)) )

public:
	unsigned int GetMyID();

public:
	N3Object();
	N3Object(const N3Object&); // = delete;
	N3Object& operator=(const N3Object&); // = delete;
	virtual ~N3Object();

private:
	/* this+0 */ //const N3Object::`vftable';
	/* this+4 */ const unsigned int m_MyID;
};
