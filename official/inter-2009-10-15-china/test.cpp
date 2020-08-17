#include "std/deque"
#include "std/list"
#include "std/map"
#include "std/queue"
#include "std/set"
#include "std/string"
#include "std/vector"


void Test(void)
{
	CDia dia, dia2;
	dia.Open(EXEPATH());
	dia2.Open(DLLPATH());

	assert( sizeof(time_t) == 4 );
	assert( sizeof(mystd::deque<int>) == 32 );
	assert( sizeof(mystd::list<int>) == 12 );
	assert( sizeof(mystd::map<int,int>) == 12 );
	assert( sizeof(mystd::multimap<int,int>) == 12 );
	assert( sizeof(mystd::queue< int, mystd::deque<int> >) == 32 );
	assert( sizeof(mystd::set<int>) == 12 );
	assert( sizeof(mystd::string) == 28 );
	assert( sizeof(mystd::vector<int>) == 16 );

	//AcceptThread
	COMPARE_SIZE(CAcceptThread);
	//CMailCtrl
	COMPARE_SIZE(CMailCtrl);
	//CMailDB
	COMPARE_SIZE(CMailDB);
	//CMakerRankDB
	COMPARE_SIZE(CMakerRankDB);
	//CMakerRankMgr
	COMPARE_SIZE(CMakerRankMgr);
	//ExpParameter
	COMPARE_SIZE(CExpParameter);
	//FriendDB
	COMPARE_SIZE(CFriendDB);
	//GuildInfoPacketDispatcher
	COMPARE_SIZE(CIGuildInfoPacketDispatcher);
	//IGuildInfo
	COMPARE_SIZE(CIGuildInfo);
	//IGuildInfoDB
	COMPARE_SIZE(CIGuildInfoDB);
	COMPARE_SIZE(CIGuildSkillDB);
	//IGuildMgr
	COMPARE_SIZE(CIGuildMgr);
	//ISAcceptHandler
	COMPARE_SIZE(CISAcceptHandler);
	//ISDatabaseAccountMgr
	COMPARE_SIZE(ISDatabaseAccountMgr);
	//MGAcceptHandler
	COMPARE_SIZE(CMGAcceptHandler);
	//MServer
	COMPARE_SIZE(CMClient);
	//MServerMgr
	COMPARE_SIZE(CMClientMgr);
	//MSPacketHandler
	COMPARE_SIZE(CMCPacketHandler);
	//Party
	COMPARE_SIZE(CParty);
	//PartyDB
	COMPARE_SIZE(CPartyDB);
	//PartyMgr
	COMPARE_SIZE(CPartyMgr);
	//ProcessThread
	COMPARE_SIZE(CProcessThread);
	//UserMgr
	COMPARE_SIZE(CUserMgr);
	//ZServer
	COMPARE_SIZE(CZServer);
	//ZServerMgr
	COMPARE_SIZE(CZServerMgr);
	//ZSPacketHandler
	COMPARE_SIZE(CZSPacketHandler);

	//shared/CDateTime
	COMPARE_SIZE(CDateTime);
	//shared/Client
	COMPARE_SIZE(CClient);
	//shared/DBScriptInfo
	COMPARE_SIZE(CDBScriptInfo);
	//shared/ErrorLog
	COMPARE_SIZE(CErrorLog);
	//shared/Guild
	COMPARE_SIZE(CGuild);
	//shared/GuildDB
	COMPARE_SIZE(CGuildDB);
	//shared/GuildMgr
	COMPARE_SIZE(CGuildMgr);
	//shared/MapInfo
	COMPARE_SIZE(CMapInfo);
	//shared/ODBC
	COMPARE_SIZE(CODBC);
	//shared/ServerInfo
	COMPARE_SIZE(CServerInfo);
	//shared/N2System/N2DualKeyMap
//	COMPARE_SIZE(N2DualKeyMap<unsigned long, unsigned int, CMemorialDungeon *>);
	//shared/N2System/N2IDAllocator
	COMPARE_SIZE(N2IDAllocator);
	//shared/N2System/N2IDGenerator
	COMPARE_SIZE(N2IDGenerator);
	//shared/N2System/N2Inter
	COMPARE_SIZE(N2Inter);
	//shared/N2System/N2InterMessageQueue
	COMPARE_SIZE(N2InterMessageQueue);
	//shared/N2System/N2MessageQueue
	COMPARE_SIZE(N2MessageQueue<int>);
	//shared/N2System/N2Object
	COMPARE_SIZE(N2Object);
	//shared/N2System/N2SystemMgr
	COMPARE_SIZE(N2SystemMgr);
	//shared/N2System/N2Thread
	COMPARE_SIZE(N2Thread);
	//shared/N2System/DBLog/N2DBLog
	COMPARE_SIZE(N2DBLog);
	//shared/N2System/DBLog/N2DBLogMgr
	COMPARE_SIZE(N2DBLogMgr);
	//shared/N2System/DBLog/N2DBLogRequestQueue
	COMPARE_SIZE(N2DBLogRequestQueue);
	//shared/N2System/DBLog/N2DBLogThread
	COMPARE_SIZE(N2DBLogThread);
	//shared/N2System/ODBC/N2ODBCCtrl
	COMPARE_SIZE(N2ODBCCtrl);

	//Instant Map/InstantMap
	COMPARE_SIZE(CInstantMap);
	COMPARE_OFFSET(CInstantMap, m_bOK);
	COMPARE_OFFSET(CInstantMap, m_MessageQueue);
	COMPARE_OFFSET(CInstantMap, m_ZSID);
	COMPARE_OFFSET(CInstantMap, m_Name);
	COMPARE_OFFSET(CInstantMap, m_MapID);
	COMPARE_OFFSET(CInstantMap, m_MapType);
	COMPARE_OFFSET(CInstantMap, m_RequestCreateInter);
	COMPARE_OFFSET(CInstantMap, m_ZSVRregisteredFUCnt);
	COMPARE_OFFSET(CInstantMap, m_State);
	COMPARE_OFFSET(CInstantMap, m_ScheduleContainer);
	COMPARE_OFFSET(CInstantMap, m_ProcessFuncPtr);
	//Instant Map/InstantMapMgr
	COMPARE_SIZE(CInstantMapMgr);

	//Memorial Dungeon/MemorialDungeon
	COMPARE_SIZE(CMemorialDungeon);
	//Memorial Dungeon/MemorialDungeonMgr
	COMPARE_SIZE(CMemorialDungeonMgr);
	//Memorial Dungeon/MemorialDungeonReservedPlayer
	COMPARE_SIZE(CMemorialDungeonReservedPlayer);

	//NetLib/Acceptor
	COMPARE_SIZE(CAcceptHandler);
	//NetLib/AsyncStream
	COMPARE_SIZE(CAsyncStream);
	//NetLib/PacketHandler
	COMPARE_SIZE(CPacketHandler);
	//NetLib/PacketQueue
	COMPARE_SIZE(CPacketQueue);

	//Statistics/StatisticsMgr
	COMPARE_SIZE(CStatisticsMgr);
}
