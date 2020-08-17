#pragma once


class N3Object
{
public:
	enum
	{
		NetworkWorkThread          = 0,
		ProcessMgr                 = 1,
		ClientMgr                  = 2,
		ClientWorkThread           = 3,
		SteamObject                = 4,
		InterServerClient          = 5,
		GlobalDBMgr                = 6,
		GlobalWorkThread           = 7,
		CInstantMapMgr             = 8,
		CInstantMap                = 9,
		CMemorialDungeonMgr        = 10,
		CMemorialDungeon           = 11,
		PrivateDungeon             = 12,
		PrivateDungeonWorkerThread = 13,
		CLogDBManager              = 14,
		LogDBThread                = 15,
		CInstantMapWorkerThread    = 100,
		CInstantMapCtrl            = 101,
		CZsvrMgr                   = 102,
		CZsvrAcceptThread          = 103,
		CMsvrMgr                   = 104,
		CMsvrAcceptThread          = 105,
		CNpcProvideExpInfoMgr      = 106,
		CharacterWorkThread        = 107,
		CharacterDBMgr             = 108,
		ItemTradeLogMgr            = 109,
		ItemTradeLogThread         = 110,
		CASyncDBLogMgr             = 111,
	};

	#define N3MSG(_type_,_msg_) ( ((unsigned short)(N3Object::_type_) << 16) | ((unsigned short)(_type_::_msg_)) )

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
