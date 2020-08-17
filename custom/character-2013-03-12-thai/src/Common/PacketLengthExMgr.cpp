#include "Common/PacketLengthExMgr.h"


/// globals
CPacketLengthExMgr g_packetLenMapEx;


CPacketLengthExMgr::CPacketLengthExMgr()
{
	this->CPacketLengthExMgr::InitPacketLen();
	this->CPacketLengthExMgr::InitPacketLenWithClient();
}


CPacketLengthExMgr::~CPacketLengthExMgr()
{
}


std::pair<CPacketLengthExMgr::enumFixedPacketRet,int> CPacketLengthExMgr::IsFixedPacket(const int in_Header) const
{
	std::map<int,CData>::const_iterator it = m_LengthMap.find(in_Header);
	if( it != m_LengthMap.end() )
	{
		if( it->second.m_Len == -1 )
			return std::pair<enumFixedPacketRet,int>(VARIABLE, it->second.m_Min);

		if( it->second.m_Len >= 0 )
			return std::pair<enumFixedPacketRet,int>(FIXED, it->second.m_Len);
	}

	return std::pair<enumFixedPacketRet,int>(UNKNOWN, 4);
}


int CPacketLengthExMgr::GetReplayFactor(const int in_Header) const
{
	std::map<int,CData>::const_iterator it = m_LengthMap.find(in_Header);
	if( it == m_LengthMap.end() )
		return 0;

	return it->second.m_ReplayFactor;
}


void CPacketLengthExMgr::Add(const int in_Header, const int in_Length, const int in_MinLength, const int in_ReplayFactor)
{
	m_LengthMap.insert(std::pair<int,CData>(in_Header, CData(in_Length, in_MinLength, in_ReplayFactor)));
}


void CPacketLengthExMgr::InitPacketLen()
{
	this->CPacketLengthExMgr::Add(10500,    6,    6, 0); // HEADER_SERVER_ENTRY
	this->CPacketLengthExMgr::Add(10501,   23,   23, 0); // HEADER_HA_LOGON
	this->CPacketLengthExMgr::Add(10733,   39,   39, 0); // HEADER_HA_LOGON2
	this->CPacketLengthExMgr::Add(10732,    6,    6, 0); // HEADER_AH_BILLING_ACK
	this->CPacketLengthExMgr::Add(10502,   98,   98, 0); // HEADER_AH_LOGON_EXIST
	this->CPacketLengthExMgr::Add(10678,  151,  151, 0); // HEADER_AH_LOGON_EXIST_PCBANG
	this->CPacketLengthExMgr::Add(10682,  204,  204, 0); // ?? HEADER_AH_LOGON_EXIST_PCBANG_HAN
	this->CPacketLengthExMgr::Add(10726,   20,   20, 0); // HEADER_AH_DISPATCH_PREMIUM_INFO
	this->CPacketLengthExMgr::Add(10503,   98,   98, 0); // HEADER_AH_LOGON_NOTEXIST
	this->CPacketLengthExMgr::Add(10505,   42,   42, 0); // HEADER_HZ_LOGON_EXIST
	this->CPacketLengthExMgr::Add(10506,   42,   42, 0); // HEADER_HZ_LOGON_NOTEXIST
	this->CPacketLengthExMgr::Add(10504,   19,   19, 0); // HEADER_ZH_LOGON
	this->CPacketLengthExMgr::Add(10507,    7,    7, 0); // HEADER_ZH_CHAR_EXIT
	this->CPacketLengthExMgr::Add(10508,   11,   11, 0); // HEADER_HA_CHAR_EXIT
	this->CPacketLengthExMgr::Add(10509,    7,    7, 0); // HEADER_AH_DISCONNECT
	this->CPacketLengthExMgr::Add(10510,    7,    7, 0); // HEADER_HZ_DISCONNECT
	this->CPacketLengthExMgr::Add(10612,    7,    7, 0); // HEADER_HZ_DISCONNECT_RIGHTNOW
	this->CPacketLengthExMgr::Add(10611,    7,    7, 0); // HEADER_AH_DISCONNECT_RIGHTNOW
	this->CPacketLengthExMgr::Add(10677,   54,   54, 0); // HEADER_HZ_NOTIFY_PCBANG
	this->CPacketLengthExMgr::Add(10679,    6,    6, 0); // ?? HEADER_HA_CHAR_SVR_INFO
	this->CPacketLengthExMgr::Add(10680,    6,    6, 0); // HEADER_HA_REQ_PLAYING_LIMITINFO
	this->CPacketLengthExMgr::Add(10681,   10,   10, 0); // HEADER_AH_ACK_PLAYING_LIMITINFO
	this->CPacketLengthExMgr::Add(  143,    6,    6, 0); // ?? HEADER_SERVER_ENTRY_ACK
	this->CPacketLengthExMgr::Add(10513,    4,    4, 0); // ?? HEADER_CONNECTION_CLOSED
	this->CPacketLengthExMgr::Add(10000,   -1,   71, 0); // ?? HEADER_NZ_NEWNPC
	this->CPacketLengthExMgr::Add(10515,   14,   14, 0); // HEADER_ZH_SAVECHARINFO
	this->CPacketLengthExMgr::Add(10516,   15,   15, 0); // HEADER_ZH_MAPMOVE
	this->CPacketLengthExMgr::Add(10517,   10,   10, 0); // HEADER_HZ_ACK_MAPMOVE
	this->CPacketLengthExMgr::Add(10009,   15,   15, 0); // ?? HEADER_ZN_ANSWER
	this->CPacketLengthExMgr::Add(10546,    6,    6, 0); // HEADER_HA_PCINFOUPDATE
	this->CPacketLengthExMgr::Add(10019,   18,   18, 0); // ?? HEADER_NZ_EXCHANGE_ITEM
	this->CPacketLengthExMgr::Add(10017,   -1,   12, 0); // ?? HEADER_NZ_DIALOG_ACK
	this->CPacketLengthExMgr::Add(10514,   10,   10, 0); // HEADER_SAVE_USING_TIME
	this->CPacketLengthExMgr::Add(10511,    6,    6, 0); // HEADER_HZ_ACK_RESTART
	this->CPacketLengthExMgr::Add(10512,    6,    6, 0); // HEADER_ZH_RESTART
	this->CPacketLengthExMgr::Add(10020,   30,   30, 0); // ?? HEADER_NZ_CHECKPOINT
	this->CPacketLengthExMgr::Add(10518,   86,   86, 0); // ?? HEADER_ZI_LOGON
	this->CPacketLengthExMgr::Add(10519,   34,   34, 0); // ?? HEADER_ZI_EXIT
	this->CPacketLengthExMgr::Add(10520,   -1,   80, 0); // ?? HEADER_ZI_WHISPER
	this->CPacketLengthExMgr::Add(10521,   -1,   60, 0); // ?? HEADER_IZ_WHISPER
	this->CPacketLengthExMgr::Add(10522,    7,    7, 0); // ?? HEADER_IZ_ACK_WHISPER
	this->CPacketLengthExMgr::Add(10523,   31,   31, 0); // ?? HEADER_ZI_ACK_WHISPER
	this->CPacketLengthExMgr::Add(10524,    6,    6, 0); // ?? HEADER_ZI_REQ_USER_COUNT
	this->CPacketLengthExMgr::Add(10525,   10,   10, 0); // ?? HEADER_IZ_USER_COUNT
	this->CPacketLengthExMgr::Add(10526,   -1,    4, 0); // ?? HEADER_ZI_BROADCAST
	this->CPacketLengthExMgr::Add(10527,   -1,    4, 0); // ?? HEADER_IZ_BROADCAST
	this->CPacketLengthExMgr::Add(10528,   34,   34, 0); // ?? HEADER_ZI_MAKE_GROUP
	this->CPacketLengthExMgr::Add(10638,   36,   36, 0); // ?? HEADER_ZI_MAKE_GROUP2
	this->CPacketLengthExMgr::Add(10529,   35,   35, 0); // ?? HEADER_IZ_ACK_MAKE_GROUP
	this->CPacketLengthExMgr::Add(10530,   -1,   36, 0); // ?? HEADER_IZ_GROUP_LIST
	this->CPacketLengthExMgr::Add(10531,   14,   14, 0); // ?? HEADER_ZI_REQ_JOIN_GROUP
	this->CPacketLengthExMgr::Add(10532,   31,   31, 0); // ?? HEADER_IZ_ACK_REQ_JOIN_GROUP
	this->CPacketLengthExMgr::Add(10533,   34,   34, 0); // ?? HEADER_IZ_REQ_JOIN_GROUP
	this->CPacketLengthExMgr::Add(10534,   14,   14, 0); // ?? HEADER_ZI_JOIN_GROUP
	this->CPacketLengthExMgr::Add(10545,   14,   14, 0); // ?? HEADER_ZI_CHANGE_EXPOPTION
	this->CPacketLengthExMgr::Add(10643,   14,   14, 0); // ?? HEADER_ZI_CHANGE_EXPOPTION2
	this->CPacketLengthExMgr::Add(10535,   10,   10, 0); // ?? HEADER_ZI_REQ_LEAVE_GROUP
	this->CPacketLengthExMgr::Add(10536,   34,   34, 0); // ?? HEADER_ZI_REQ_EXPEL_GROUP_MEMBER
	this->CPacketLengthExMgr::Add(10537,   79,   79, 0); // ?? HEADER_IZ_ADD_MEMBER_TO_GROUP
	this->CPacketLengthExMgr::Add(10639,   81,   81, 0); // ?? HEADER_IZ_ADD_MEMBER_TO_GROUP2
	this->CPacketLengthExMgr::Add(10538,   35,   35, 0); // ?? HEADER_IZ_DELETE_MEMBER_FROM_GROUP
	this->CPacketLengthExMgr::Add(10539,   22,   22, 0); // ?? HEADER_ZI_MAPMOVE
	this->CPacketLengthExMgr::Add(10540,   14,   14, 0); // ?? HEADER_ZI_GRID_UPDATE
	this->CPacketLengthExMgr::Add(10541,   -1,   12, 0); // ?? HEADER_ZI_CHAT_PARTY
	this->CPacketLengthExMgr::Add(10542,   -1,   12, 0); // ?? HEADER_IZ_CHAT_PARTY
	this->CPacketLengthExMgr::Add(10543,    2,    2, 0); // ?? HEADER_IZ_DISCONNECT_ALL
	this->CPacketLengthExMgr::Add(10544,    2,    2, 0); // ?? HEADER_ZI_DISCONNECT_ALL
	this->CPacketLengthExMgr::Add(10547,   10,   10, 0); // ?? HEADER_IZ_REQ_SERVERSTATE
	this->CPacketLengthExMgr::Add(10548,    2,    2, 0); // ?? HEADER_IZ_SHOTDOWN
	this->CPacketLengthExMgr::Add(10549,   22,   22, 0); // ?? HEADER_ZI_SERVERSTATE
	this->CPacketLengthExMgr::Add(11000,   50,   50, 0); // ?? HEADER_MI_ENTER
	this->CPacketLengthExMgr::Add(11001,   10,   10, 0); // ?? HEADER_MI_REQ_SERVERSTATE
	this->CPacketLengthExMgr::Add(11002,   -1,    8, 0); // ?? HEADER_MI_MSG
	this->CPacketLengthExMgr::Add(11003,   30,   30, 0); // ?? HEADER_MI_SHOTDOWN
	this->CPacketLengthExMgr::Add(10673,    6,    6, 0); // ?? HEADER_IZ_DISCONNECT_CHARACTER
	this->CPacketLengthExMgr::Add(11009,    6,    6, 0); // ?? HEADER_MI_GET_GUILD_INFO
	this->CPacketLengthExMgr::Add(11011,    6,    6, 0); // ?? HEADER_MI_GUILD_INFO_INIT
	this->CPacketLengthExMgr::Add(11013,    6,    6, 0); // ?? HEADER_MI_ALLY_GUILD_INIT
	this->CPacketLengthExMgr::Add(10550,   14,   14, 0); // ?? HEADER_ZI_REQ_MYGUILD_BASIC_INFO
	this->CPacketLengthExMgr::Add(10552,   38,   38, 0); // ?? HEADER_IZ_MYGUILD_BASICINFO
	this->CPacketLengthExMgr::Add(10553,   14,   14, 0); // ?? HEADER_ZI_REQ_GUILD_MENUINTERFACE
	this->CPacketLengthExMgr::Add(10554,   -1,   20, 0); // ?? HEADER_IZ_ACK_MYGUILD_MEMBER_INFO
	this->CPacketLengthExMgr::Add(10555,   -1,   20, 0); // ?? HEADER_IZ_ACK_MYGUILD_POSITION
	this->CPacketLengthExMgr::Add(10556,   -1,   20, 0); // ?? HEADER_IZ_ACK_MYGUILD_BANISH
	this->CPacketLengthExMgr::Add(10557,   -1,   20, 0); // ?? HEADER_IZ_ACK_MYGUILD_LIST
	this->CPacketLengthExMgr::Add(10558,   -1,   16, 0); // ?? HEADER_ZI_REGISTER_GUILD_EMBLEM_IMG
	this->CPacketLengthExMgr::Add(10559,   -1,   14, 0); // ?? HEADER_IZ_GET_GUILD_EMBLEM_IMG
	this->CPacketLengthExMgr::Add(10560,   14,   14, 0); // ?? HEADER_ZI_MEMBERMGR_INFO
	this->CPacketLengthExMgr::Add(10561,   -1,    8, 0); // ?? HEADER_IZ_MEMBERMGR_INFO
	this->CPacketLengthExMgr::Add(10562,   -1,   16, 0); // ?? HEADER_ZI_REQ_CHANGE_MEMBERPOS
	this->CPacketLengthExMgr::Add(10563,   -1,   12, 0); // ?? HEADER_IZ_ACK_CHANGE_MEMBERPOS
	this->CPacketLengthExMgr::Add(10564,   14,   14, 0); // ?? HEADER_ZI_REQ_OPEN_MEMBER_INFO
	this->CPacketLengthExMgr::Add(10565,   -1,   16, 0); // ?? HEADER_IZ_ACK_OPEN_MEMBER_INFO
	this->CPacketLengthExMgr::Add(10566,   54,   54, 0); // ?? HEADER_ZI_REQ_LEAVE_GUILD
	this->CPacketLengthExMgr::Add(10567,   78,   78, 0); // ?? HEADER_IZ_ACK_LEAVE_GUILD
	this->CPacketLengthExMgr::Add(10568,   82,   82, 0); // ?? HEADER_ZI_REQ_BAN_GUILD
	this->CPacketLengthExMgr::Add(10569,  102,  102, 0); // ?? HEADER_IZ_ACK_BAN_GUILD
	this->CPacketLengthExMgr::Add(10570,   54,   54, 0); // ?? HEADER_ZI_REQ_DISORGANIZE_GUILD
	this->CPacketLengthExMgr::Add(10571,   18,   18, 0); // ?? HEADER_IZ_REQ_DISORGANIZE_GUILD_RESULT
	this->CPacketLengthExMgr::Add(10572,   -1,   12, 0); // ?? HEADER_ZI_REQ_GUILD_POSITION_INFO
	this->CPacketLengthExMgr::Add(10573,   -1,   12, 0); // ?? HEADER_IZ_ACK_GUILD_POSITION_INFO
	this->CPacketLengthExMgr::Add(10574,   -1,    8, 0); // ?? HEADER_IZ_SKILL_INFO
	this->CPacketLengthExMgr::Add(10575,   -1,    8, 0); // ?? HEADER_IZ_BAN_LIST
	this->CPacketLengthExMgr::Add(10576,   -1,    8, 0); // ?? HEADER_IZ_OTHER_GUILD_LIST
	this->CPacketLengthExMgr::Add(10551,   86,   86, 0); // ?? HEADER_ZI_REQ_MAKE_GUILD
	this->CPacketLengthExMgr::Add(10577,   18,   18, 0); // ?? HEADER_ZI_REQ_JOIN_GUILD
	this->CPacketLengthExMgr::Add(10579,   66,   66, 0); // ?? HEADER_ZI_JOIN_GUILD
	this->CPacketLengthExMgr::Add(10580,   15,   15, 0); // ?? HEADER_IZ_ACK_REQ_JOIN_GUILD
	this->CPacketLengthExMgr::Add(10578,   34,   34, 0); // ?? HEADER_IZ_REQ_JOIN_GUILD
	this->CPacketLengthExMgr::Add(10581,   -1,   12, 0); // ?? HEADER_IZ_GUILD_LIST_TOD
	this->CPacketLengthExMgr::Add(10582,  222,  222, 0); // ?? HEADER_IZ_GUILDINFO_TOD
	this->CPacketLengthExMgr::Add(10583,   -1,   12, 0); // ?? HEADER_IZ_GUILD_MEMBERINFO_TOD
	this->CPacketLengthExMgr::Add(10584,   -1,   12, 0); // ?? HEADER_IZ_GUILD_ALLYINFO_TOD
	this->CPacketLengthExMgr::Add(10585,   -1,   12, 0); // ?? HEADER_IZ_GUILD_BANISHINFO_TOD
	this->CPacketLengthExMgr::Add(10586,   -1,   12, 0); // ?? HEADER_IZ_GUILD_MPOSITION_TOD
	this->CPacketLengthExMgr::Add(10587,   -1, 1010, 0); // ?? HEADER_IZ_GUILD_NOTICE_TOD
	this->CPacketLengthExMgr::Add(10588,   11,   11, 0); // ?? HEADER_IZ_RESULT_MAKE_GUILD
	this->CPacketLengthExMgr::Add(10589,   52,   52, 0); // ?? HEADER_IZ_UPDATE_CHARGDID
	this->CPacketLengthExMgr::Add(10590,   30,   30, 0); // ?? HEADER_IZ_UPDATE_CHARSTAT
	this->CPacketLengthExMgr::Add(10591,  186,  186, 0); // ?? HEADER_ZI_GUILD_NOTICE
	this->CPacketLengthExMgr::Add(10592,  186,  186, 0); // ?? HEADER_IZ_GUILD_NOTICE
	this->CPacketLengthExMgr::Add(10593,   30,   30, 0); // ?? HEADER_ZI_ALLY_GUILD
	this->CPacketLengthExMgr::Add(10594,    7,    7, 0); // ?? HEADER_IZ_ACK_REQ_ALLY_GUILD
	this->CPacketLengthExMgr::Add(10595,   47,   47, 0); // ?? HEADER_IZ_ADD_ALLY_GUILD
	this->CPacketLengthExMgr::Add(10596,   14,   14, 0); // ?? HEADER_ZI_REQ_HOSTILE_GUILD
	this->CPacketLengthExMgr::Add(10597,   15,   15, 0); // ?? HEADER_IZ_ACK_REQ_HOSTILE_GUILD
	this->CPacketLengthExMgr::Add(10598,   47,   47, 0); // ?? HEADER_IZ_ADD_HOSTILE_GUILD
	this->CPacketLengthExMgr::Add(10599,  146,  146, 0); // ?? HEADER_IZ_GUILD_MEMBER_ADD
	this->CPacketLengthExMgr::Add(10601,   14,   14, 0); // ?? HEADER_IZ_DELETE_RELATED_GUILD
	this->CPacketLengthExMgr::Add(10600,   14,   14, 0); // ?? HEADER_ZI_REQ_DELETE_RELATED_GUILD
	this->CPacketLengthExMgr::Add(10602,   10,   10, 0); // ?? HEADER_ZI_ACTOR_INIT
	this->CPacketLengthExMgr::Add(10603,   -1,    8, 0); // ?? HEADER_ZI_GUILD_CHAT
	this->CPacketLengthExMgr::Add(10604,   -1,    8, 0); // ?? HEADER_IZ_GUILD_CHAT
	this->CPacketLengthExMgr::Add(10605,   14,   14, 0); // ?? HEADER_ZI_ADD_EXP
	this->CPacketLengthExMgr::Add(10606,   18,   18, 0); // ?? HEADER_IZ_ADD_EXP
	this->CPacketLengthExMgr::Add(10607,   18,   18, 0); // ?? HEADER_IZ_GUILD_LEVEL_UP
	this->CPacketLengthExMgr::Add(10608,  150,  150, 0); // ?? HEADER_IZ_GUILD_MEMBERINFO_FRAG
	this->CPacketLengthExMgr::Add(10609,   14,   14, 0); // ?? HEADER_IZ_GET_GUILD_EMBLEM_IMG_FRAG
	this->CPacketLengthExMgr::Add(10610,   16,   16, 0); // ?? HEADER_ZI_REGISTER_GUILD_EMBLEM_IMG_FRAG
	this->CPacketLengthExMgr::Add(10613,   12,   12, 0); // ?? HEADER_ZI_CHAR_LEVEL_UP
	this->CPacketLengthExMgr::Add(10614,   35,   35, 0); // ?? HEADER_ZI_GUILD_ZENY
	this->CPacketLengthExMgr::Add(10615,   36,   36, 0); // ?? HEADER_IZ_GUILD_ZENY
	this->CPacketLengthExMgr::Add(10617,   10,   10, 0); // ?? HEADER_IZ_GUILD_ZENY_UPDATE_ALL
	this->CPacketLengthExMgr::Add(10616,   10,   10, 0); // ?? HEADER_ZI_GUILD_ZENY_UPDATE_ALL
	this->CPacketLengthExMgr::Add(10618,   -1,    8, 0); // ?? HEADER_ZI_GUILD_PRELOAD
	this->CPacketLengthExMgr::Add(10619,   26,   26, 0); // ?? HEADER_ZI_GUILD_CHANGEOWNER_AGIT
	this->CPacketLengthExMgr::Add(10637,   26,   26, 0); // ?? HEADER_IZ_GUILD_CHANGEOWNER_AGIT
	this->CPacketLengthExMgr::Add(10641,   26,   26, 0); // ?? HEADER_IZ_GUILD_MAP_CHANGE
	this->CPacketLengthExMgr::Add(10642,    6,    6, 0); // ?? HEADER_ZI_VERSION
	this->CPacketLengthExMgr::Add(10670,   10,   10, 0); // ?? HEADER_ZI_EPISODE_VERSION
	this->CPacketLengthExMgr::Add(10620,    2,    2, 0); // HEADER_HA_REQ_PACKETINFO
	this->CPacketLengthExMgr::Add(10621,   82,   82, 0); // ?? HEADER_AH_ACK_PACKETINFO
	this->CPacketLengthExMgr::Add(10622,    6,    6, 0); // HEADER_ZH_REQ_REMAINTIME
	this->CPacketLengthExMgr::Add(10623,    6,    6, 0); // HEADER_HA_REQ_REMAINTIME
	this->CPacketLengthExMgr::Add(10624,   18,   18, 0); // HEADER_AH_RES_REMAINTIME
	this->CPacketLengthExMgr::Add(10625,   18,   18, 0); // HEADER_HZ_RES_REMAINTIME
	this->CPacketLengthExMgr::Add(10626,   14,   14, 0); // HEADER_AH_INFO_REMAINTIME
	this->CPacketLengthExMgr::Add(10627,   14,   14, 0); // HEADER_HZ_INFO_REMAINTIME
	this->CPacketLengthExMgr::Add(10628,   -1,   16, 0); // ?? HEADER_IZ_GUILD_NOTIFYSKILLDATA
	this->CPacketLengthExMgr::Add(10629,   -1,   12, 0); // ?? HEADER_ZI_GDSKILL_UPDATE
	this->CPacketLengthExMgr::Add(10632,   42,   42, 0); // ?? HEADER_ZI_MOVE
	this->CPacketLengthExMgr::Add(10640,   46,   46, 0); // ?? HEADER_ZI_MOVE_GID
	this->CPacketLengthExMgr::Add(10633,   62,   62, 0); // ?? HEADER_IZ_MOVE
	this->CPacketLengthExMgr::Add(10634,   10,   10, 0); // ?? HEADER_ZI_GUILD_CHANGEMAXUSER
	this->CPacketLengthExMgr::Add(10635,   10,   10, 0); // ?? HEADER_IZ_GUILD_CHANGEMAXUSER
	this->CPacketLengthExMgr::Add(10636,    6,    6, 0); // ?? HEADER_IZ_FREE_GUILD
	this->CPacketLengthExMgr::Add(10630,   10,   10, 0); // ?? HEADER_ZE_REQ_CERTIFICATE
	this->CPacketLengthExMgr::Add(10631,    2,    2, 0); // ?? HEADER_EZ_PERMIT_CERTIFICATE
//	this->CPacketLengthExMgr::Add(10644,    ?,    ?, ?); // ?? HEADER_HA_LOGON_SESSION
//	this->CPacketLengthExMgr::Add(10645,  112,  112, ?); // HEADER_AH_LOGON_EXIST_SESSION
//	this->CPacketLengthExMgr::Add(10646,  112,  112, ?); // HEADER_AH_LOGON_NOTEXIST_SESSION
	this->CPacketLengthExMgr::Add(10647,   30,   30, 0); // ?? HEADER_ZI_DIVORCE
	this->CPacketLengthExMgr::Add(10648,   30,   30, 0); // ?? HEADER_IZ_DIVORCE
	this->CPacketLengthExMgr::Add(10649,   -1,    8, 0); // ?? HEADER_IZ_FRIENDS_LIST
	this->CPacketLengthExMgr::Add(10650,   15,   15, 0); // ?? HEADER_IZ_FRIENDS_STATE
	this->CPacketLengthExMgr::Add(10651,   18,   18, 0); // ?? HEADER_ZI_ACK_REQ_ADD_FRIENDS
	this->CPacketLengthExMgr::Add(10652,   40,   40, 0); // ?? HEADER_IZ_ADD_FRIENDS
	this->CPacketLengthExMgr::Add(10653,   14,   14, 0); // ?? HEADER_ZI_DELETE_FRIENDS
	this->CPacketLengthExMgr::Add(10654,   14,   14, 0); // ?? HEADER_IZ_DELETE_FRIENDS
	this->CPacketLengthExMgr::Add(10655,   34,   34, 0); // ?? HEADER_ZI_MOVE_SERVER
//	this->CPacketLengthExMgr::Add(10656,    ?,    ?, ?); // ?? HEADER_SVR_PING
	this->CPacketLengthExMgr::Add(10657,  324,  324, 0); // ?? HEADER_IZ_NOTIFY_MAKERRANK
	this->CPacketLengthExMgr::Add(10658,   36,   36, 0); // ?? HEADER_ZI_UPDATE_MAKERRANK
	this->CPacketLengthExMgr::Add(  529,    6,    6, 0); // ?? HEADER_ZH_MOVE_PVPWORLD
	this->CPacketLengthExMgr::Add(10659,   10,   10, 0); // ?? HEADER_ZI_MAIL_GET_LIST
	this->CPacketLengthExMgr::Add(10660,   -1,   12, 0); // ?? HEADER_IZ_MAIL_REQ_GET_LIST
	this->CPacketLengthExMgr::Add(10661,   14,   14, 0); // ?? HEADER_ZI_MAIL_OPEN
	this->CPacketLengthExMgr::Add(10662,   -1,  125, 0); // ?? HEADER_IZ_MAIL_REQ_OPEN
	this->CPacketLengthExMgr::Add(10663,   14,   14, 0); // ?? HEADER_ZI_MAIL_DELETE
	this->CPacketLengthExMgr::Add(10664,   16,   16, 0); // ?? HEADER_IZ_ACK_MAIL_DELETE
	this->CPacketLengthExMgr::Add(10665,   14,   14, 0); // ?? HEADER_ZI_MAIL_GET_ITEM
	this->CPacketLengthExMgr::Add(10666,   79,   79, 0); // ?? HEADER_IZ_MAIL_REQ_GET_ITEM
	this->CPacketLengthExMgr::Add(10667,   -1,  125, 0); // ?? HEADER_ZI_MAIL_SEND
	this->CPacketLengthExMgr::Add(10668,    7,    7, 0); // ?? HEADER_IZ_MAIL_REQ_SEND
	this->CPacketLengthExMgr::Add(10669,   74,   74, 0); // ?? HEADER_IZ_MAIL_RECEIVE
	this->CPacketLengthExMgr::Add(10671,    6,    6, 0); // ?? HEADER_IZ_CHK_PROCESSTIME
	this->CPacketLengthExMgr::Add(10672,   10,   10, 0); // ?? HEADER_ZI_ACK_CHK_PROCESSTIME
	this->CPacketLengthExMgr::Add(10674,   14,   14, 0); // ?? HEADER_IZ_ACK_LOGON
	this->CPacketLengthExMgr::Add(10675,   46,   46, 0); // ?? HEADER_ZI_REQ_MAIL_RETURN
	this->CPacketLengthExMgr::Add(10676,   85,   85, 0); // ?? HEADER_IZ_ACK_MAIL_RETURN
	this->CPacketLengthExMgr::Add(10683,    2,    2, 0); // HEADER_HZ_PING
	this->CPacketLengthExMgr::Add(10684,  136,  136, 0); // ?? HEADER_ZI_MEMORIALDUNGEON_SUBSCRIPTION
	this->CPacketLengthExMgr::Add(10698,   75,   75, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_MSG
	this->CPacketLengthExMgr::Add(10705,   73,   73, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO
	this->CPacketLengthExMgr::Add(10706,   12,   12, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY
	this->CPacketLengthExMgr::Add(10707,   79,   79, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_INFO
	this->CPacketLengthExMgr::Add(10708,   18,   18, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_NOTIFY
	this->CPacketLengthExMgr::Add(10709,   38,   38, 0); // ?? HEADER_ZI_MEMORIALDUNGEON_COMMAND
	this->CPacketLengthExMgr::Add(10710,  107,  107, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_SYNC
	this->CPacketLengthExMgr::Add(10711,   10,   10, 0); // ?? HEADER_ZI_MEMORIALDUNGEON_VISA
	this->CPacketLengthExMgr::Add(10712,   38,   38, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_VISA
	this->CPacketLengthExMgr::Add(10713,   14,   14, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_COMMAND
	this->CPacketLengthExMgr::Add(10686,   30,   30, 0); // ?? HEADER_IZ_INSTANTMAP_CREATE_REQ
	this->CPacketLengthExMgr::Add(10687,   27,   27, 0); // ?? HEADER_ZI_INSTANTMAP_CREATE_RES
	this->CPacketLengthExMgr::Add(10691,   35,   35, 0); // ?? HEADER_IZ_INSTANTMAP_PLAYER_ENTER
	this->CPacketLengthExMgr::Add(10692,   14,   14, 0); // ?? HEADER_ZI_INSTANTMAP_ERROR
	this->CPacketLengthExMgr::Add(10693,   22,   22, 0); // ?? HEADER_IZ_INSTNATMAP_DESTROY
	this->CPacketLengthExMgr::Add(10695,    7,    7, 0); // ?? HEADER_ZI_INSTANTMAP_ALLOW
	this->CPacketLengthExMgr::Add(10694,   10,   10, 0); // ?? HEADER_ZI_PING
	this->CPacketLengthExMgr::Add(10696,    2,    2, 0); // ?? HEADER_XX_CONNECT
	this->CPacketLengthExMgr::Add(10697,    2,    2, 0); // ?? HEADER_XX_DISCONNECT
	this->CPacketLengthExMgr::Add(11015,   22,   22, 0); // ?? HEADER_IM_SERVERSTATE_HAN_GAME
	this->CPacketLengthExMgr::Add(11016,   38,   38, 0); // ?? HEADER_IM_SERVERSTATE_CHANNELING
	this->CPacketLengthExMgr::Add(10688,   10,   10, 0); // HEADER_HZ_NOTIFY_PCBANG_PLAYING_TIME
	this->CPacketLengthExMgr::Add(10689,   26,   26, 0); // ?? HEADER_ZI_SERVERSTATE_HAN_GAME
	this->CPacketLengthExMgr::Add(10777,   42,   42, 0); // ?? HEADER_ZI_SERVERSTATE_CHANNELING
	this->CPacketLengthExMgr::Add(10690,   10,   10, 0); // HEADER_AH_NOTIFY_PCBANG_PLAYING_TIME
	this->CPacketLengthExMgr::Add(10700,   34,   34, 0); // ?? HEADER_ZI_PARTY_JOIN_REQ
	this->CPacketLengthExMgr::Add(10701,   34,   34, 0); // ?? HEADER_IZ_PARTY_JOIN_REQ_ACK
	this->CPacketLengthExMgr::Add(10702,   34,   34, 0); // ?? HEADER_IZ_PARTY_JOIN_REQ
	this->CPacketLengthExMgr::Add(10703,   14,   14, 0); // ?? HEADER_ZI_PARTY_JOIN_REQ_ACK
	this->CPacketLengthExMgr::Add(10704,  104,  104, 0); // HEADER_AH_LOGON_ACK_EXTEND_BILLING_INFO
	this->CPacketLengthExMgr::Add(10714,   10,   10, 0); // HEADER_ZH_PLAYER_ALIVE
	this->CPacketLengthExMgr::Add(10715,   10,   10, 0); // ?? HEADER_IZ_LEAVE_GROUP
	this->CPacketLengthExMgr::Add(10716,   14,   14, 0); // ?? HEADER_ZI_MEMORIALDUNGEON_OPENSTATE
	this->CPacketLengthExMgr::Add(10717,   11,   11, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_OPENSTATE
//	this->CPacketLengthExMgr::Add(10718,    ?,    ?, ?); // ?? HEADER_ZI_ENTRANCESTATION_REGIST
//	this->CPacketLengthExMgr::Add(10719,    ?,    ?, ?); // ?? HEADER_IZ_WAITINGROOM_SUBSCRIPTION_RESULT
//	this->CPacketLengthExMgr::Add(10720,    ?,    ?, ?); // ?? HEADER_ZI_WAITINGROOM_MY_SUBSCRIPTION_INFO
//	this->CPacketLengthExMgr::Add(10721,    ?,    ?, ?); // ?? HEADER_IZ_WAITINGROOM_MY_SUBSCRIPTION_INFO
//	this->CPacketLengthExMgr::Add(10722,    ?,    ?, ?); // ?? HEADER_IZ_WAITINGROOM_PARTYPLAY_JOIN_NOTI
//	this->CPacketLengthExMgr::Add(10723,    ?,    ?, ?); // ?? HEADER_ZI_WAITINGROOM_PARTYPLAY_JOIN_RESULT
//	this->CPacketLengthExMgr::Add(10724,    ?,    ?, ?); // ?? HEADER_IZ_WAITINGROOM_START
//	this->CPacketLengthExMgr::Add(10725,    ?,    ?, ?); // ?? HEADER_ZI_WAITINGROOM_PLAYER_STATE
	this->CPacketLengthExMgr::Add(10727,    6,    6, 0); // ?? HEADER_HZ_CHAR_NAME_CHANGED
	this->CPacketLengthExMgr::Add(10728,   20,   20, 0); // ?? HEADER_ZI_GROUPINFO_CHANGE_V2
	this->CPacketLengthExMgr::Add(10729,   16,   16, 0); // ?? HEADER_IZ_REQ_GROUPINFO_CHANGE_V2
	this->CPacketLengthExMgr::Add(10730,   14,   14, 0); // ?? HEADER_ZI_CHANGE_GROUP_MASTER
	this->CPacketLengthExMgr::Add(10734,   54,   54, 0); // ?? HEADER_ZI_SEEK_PARTY
	this->CPacketLengthExMgr::Add(10735,   54,   54, 0); // ?? HEADER_IZ_SEEK_PARTY
	this->CPacketLengthExMgr::Add(10736,   54,   54, 0); // ?? HEADER_ZI_SEEK_PARTY_MEMBER
	this->CPacketLengthExMgr::Add(10737,   54,   54, 0); // ?? HEADER_IZ_SEEK_PARTY_MEMBER
	this->CPacketLengthExMgr::Add(10731,    6,    6, 0); // ?? HEADER_ZH_CASTLE_MAP_MOVE
	this->CPacketLengthExMgr::Add(10738,    2,    2, 0); // ?? HEADER_ZI_GET_MY_BATTLEFILED_INFO
	this->CPacketLengthExMgr::Add(10739,   22,   22, 0); // ?? HEADER_IZ_BATTLEFILED_SETTING
	this->CPacketLengthExMgr::Add(10740,   24,   24, 0); // ?? HEADER_IZ_BATTLEFIELD_NOTI
	this->CPacketLengthExMgr::Add(10741,    8,    8, 0); // ?? HEADER_ZI_FINAL_BATTLE_PLAY
	this->CPacketLengthExMgr::Add(10757,   16,   16, 0); // ?? HEADER_ZI_BATTLE_FIELD_LIST
	this->CPacketLengthExMgr::Add(10758,   -1,   12, 0); // ?? HEADER_IZ_BATTLE_FIELD_LIST
	this->CPacketLengthExMgr::Add(10759,   20,   20, 0); // ?? HEADER_ZI_JOIN_BATTLE_FIELD
	this->CPacketLengthExMgr::Add(10760,   18,   18, 0); // ?? HEADER_IZ_JOIN_BATTLE_FIELD
	this->CPacketLengthExMgr::Add(10761,   14,   14, 0); // ?? HEADER_ZI_CANCEL_BATTLE_FIELD
	this->CPacketLengthExMgr::Add(10762,   16,   16, 0); // ?? HEADER_IZ_CANCEL_BATTLE_FIELD
	this->CPacketLengthExMgr::Add(10763,   14,   14, 0); // ?? HEADER_ZI_REQ_BATTLE_STATE_MONITOR
	this->CPacketLengthExMgr::Add(10764,   22,   22, 0); // ?? HEADER_IZ_ACK_BATTLE_STATE_MONITOR
	this->CPacketLengthExMgr::Add(10765,   16,   16, 0); // ?? HEADER_IZ_BATTLE_NOTI_START_STEP
	this->CPacketLengthExMgr::Add(10766,   14,   14, 0); // ?? HEADER_IZ_BATTLE_JOIN_NOTI_DEFER
//	this->CPacketLengthExMgr::Add(10767,    ?,    ?, ?); // ?? HEADER_IZ_BATTLE_JOIN_DISABLE_STATE
	this->CPacketLengthExMgr::Add(10768,   16,   16, 0); // ?? HEADER_IZ_BATTLE_USER_STATE_CHECK
	this->CPacketLengthExMgr::Add(10769,   22,   22, 0); // ?? HEADER_ZI_BATTLE_USER_STATE_CHECK
	this->CPacketLengthExMgr::Add(10770,   32,   32, 0); // ?? HEADER_IZ_MOVE_FROM_BATTLEFIELD
	this->CPacketLengthExMgr::Add(10771,   30,   30, 0); // ?? HEADER_ZI_BEFORE_BATTLE_MY_POSITION
	this->CPacketLengthExMgr::Add(10772,   30,   30, 0); // ?? HEADER_IZ_BEFORE_BATTLE_MY_POSITION
	this->CPacketLengthExMgr::Add(10773,   14,   14, 0); // ?? HEADER_IZ_CHANGE_GROUP_MASTER
	this->CPacketLengthExMgr::Add(10752,   18,   18, 0); // ?? HEADER_ZI_INTERSERVER_ORDER
	this->CPacketLengthExMgr::Add(10753,    7,    7, 0); // ?? HEADER_AH_UPDATE_PCBANG_CNT
	this->CPacketLengthExMgr::Add(10754,    6,    6, 0); // ?? HEADER_HA_CHECKBOT_REQ
	this->CPacketLengthExMgr::Add(10755,    7,    7, 0); // ?? HEADER_AH_CHECKBOT_ACK
	this->CPacketLengthExMgr::Add(10756,    6,    6, 0); // ?? HEADER_HA_CHECKBOT_UPDATE
	this->CPacketLengthExMgr::Add(10774,   -1,    7, 0); // ?? HEADER_ZI_BROADCASTING_SPECIAL_ITEM_OBTAIN
	this->CPacketLengthExMgr::Add(10775,   -1,    7, 0); // ?? HEADER_IZ_BROADCASTING_SPECIAL_ITEM_OBTAIN
//	this->CPacketLengthExMgr::Add(10776,    ?,    ?, ?); // ?? HEADER_IZ_DEFINE_CHECK
	this->CPacketLengthExMgr::Add(10778,   54,   54, 0); // ?? HEADER_ZI_PARTY_BOOKING_NOTIFY_INSERT
	this->CPacketLengthExMgr::Add(10779,   54,   54, 0); // ?? HEADER_IZ_PARTY_BOOKING_NOTIFY_INSERT
	this->CPacketLengthExMgr::Add(10780,   6,     6, 0); // ?? HEADER_ZI_PARTY_BOOKING_NOTIFY_DELETE
	this->CPacketLengthExMgr::Add(10781,   6,     6, 0); // ?? HEADER_IZ_PARTY_BOOKING_NOTIFY_DELETE
	this->CPacketLengthExMgr::Add(10782,   18,   18, 0); // ?? HEADER_ZI_PARTY_BOOKING_NOTIFY_UPDATE
	this->CPacketLengthExMgr::Add(10783,   18,   18, 0); // ?? HEADER_IZ_PARTY_BOOKING_NOTIFY_UPDATE
	this->CPacketLengthExMgr::Add(10784,   62,   62, 0); // ?? HEADER_ZI_REQ_MAKE_GUILD_SSO
	this->CPacketLengthExMgr::Add(10785,   58,   58, 0); // ?? HEADER_ZI_REQ_BAN_GUILD_SSO
	this->CPacketLengthExMgr::Add(10786,   78,   78, 0); // ?? HEADER_IZ_ACK_BAN_GUILD_SSO
	this->CPacketLengthExMgr::Add(10787,   42,   42, 0); // ?? HEADER_ZI_JOIN_GUILD_SSO
	this->CPacketLengthExMgr::Add(10788,    8,    8, 0); // ?? HEADER_HZ_ZSVR_INFO
	this->CPacketLengthExMgr::Add(10789,   10,   10, 0); // ?? HEADER_ZH_ZSVR_INFO
	this->CPacketLengthExMgr::Add(10790,    2,    2, 0); // ?? HEADER_IH_PING
	this->CPacketLengthExMgr::Add(10791,    2,    2, 0); // ?? HEADER_HI_PING
	this->CPacketLengthExMgr::Add(10792,   -1,   56, 0); // ?? HEADER_ZI_WHISPER_2
	this->CPacketLengthExMgr::Add(10793,   -1,   36, 0); // ?? HEADER_IZ_WHISPER_2
	this->CPacketLengthExMgr::Add(10794,   50,   50, 0); // ?? HEADER_ZI_MOVE_2
	this->CPacketLengthExMgr::Add(10795,    2,    2, 0); // ?? HEADER_XX_REQ_PACKAGEITEMLIST
	this->CPacketLengthExMgr::Add(10796,   -1,    6, 0); // ?? HEADER_IZ_ACK_PACKAGEITEMLIST
	this->CPacketLengthExMgr::Add(10797,   12,   12, 0); // ?? HEADER_ZI_REQ_UNPACK_PACKAGE_ITEM
	this->CPacketLengthExMgr::Add(10798,   -1,   15, 0); // ?? HEADER_IZ_ACK_UNPACK_PACKAGE_ITEM
	this->CPacketLengthExMgr::Add(10799,   -1,    7, 0); // ?? HEADER_ZI_ROLLBACK_PACKAGE_ITEM
	this->CPacketLengthExMgr::Add(10800,    2,    2, 0); // ?? HEADER_ZI_GPK_DYNCODE_RELOAD
	this->CPacketLengthExMgr::Add(10801,    2,    2, 0); // ?? HEADER_IZ_GPK_DYNCODE_RELOAD
	this->CPacketLengthExMgr::Add(10804,   11,   11, 0); // HEADER_ZH_CHAR_EXIT2
	this->CPacketLengthExMgr::Add(10805,   10,   10, 0); // HEADER_ZH_RESTART2
	this->CPacketLengthExMgr::Add(10802,    2,    2, 0); // ?? HEADER_HZ_USER_COUNT_REQ
	this->CPacketLengthExMgr::Add(10803,    6,    6, 0); // HEADER_ZH_USER_COUNT_ACK
	this->CPacketLengthExMgr::Add(10806,    6,    6, 0); // ?? HEADER_HA_REQ_AID_CHECK
	this->CPacketLengthExMgr::Add(10807,    7,    7, 0); // ?? HEADER_AH_ACK_AID_CHECK
	this->CPacketLengthExMgr::Add(10808,   15,   15, 0); // ?? HEADER_IZ_IRMAIL_NOTIFY
	this->CPacketLengthExMgr::Add(10809,   58,   58, 0); // HEADER_HZ_PERSONAL_INFORMATION
	this->CPacketLengthExMgr::Add(10810,  187,  187, 0); // ?? HEADER_AH_LOGON_UNION_SECONDPW
	this->CPacketLengthExMgr::Add(10811,   12,   12, 0); // ?? HEADER_ZI_AUTH_REQ
	this->CPacketLengthExMgr::Add(10812,    2,    2, 0); // ?? HEADER_IZ_AUTH_ACK
	this->CPacketLengthExMgr::Add(10813,   12,   12, 0); // HEADER_ZH_AUTH_REQ
	this->CPacketLengthExMgr::Add(10814,    2,    2, 0); // HEADER_HZ_AUTH_ACK
	this->CPacketLengthExMgr::Add(11017,   62,   62, 0); // ?? HEADER_MI_REQ_EDIT_EXP
	this->CPacketLengthExMgr::Add(11018,   18,   18, 0); // ?? HEADER_IM_ACK_EDIT_EXP
	this->CPacketLengthExMgr::Add(10815,   18,   18, 0); // ?? HEADER_IZ_REQ_EDIT_EXP
	this->CPacketLengthExMgr::Add(10816,   -1,   61, 0); // ?? HEADER_HZ_PERSONAL_INFORMATION_2ND
	this->CPacketLengthExMgr::Add(10818,   -1,   33, 0); // ?? HEADER_ZI_INFO_ENTRY_QUEUE_APPLY
	this->CPacketLengthExMgr::Add(10819,   34,   34, 0); // ?? HEADER_IZ_INFO_ENTRY_QUEUE_APPLY
	this->CPacketLengthExMgr::Add(10820,   40,   40, 0); // ?? HEADER_ZI_REQ_ENTRY_QUEUE_APPLY
	this->CPacketLengthExMgr::Add(10821,   -1,   38, 0); // ?? HEADER_IZ_NOTIFY_ENTRY_QUEUE_APPLY
	this->CPacketLengthExMgr::Add(10822,   35,   35, 0); // ?? HEADER_ZI_RESULT_ENTRY_QUEUE_APPLY
	this->CPacketLengthExMgr::Add(10823,   31,   31, 0); // ?? HEADER_IZ_RESULT_ENTRY_QUEUE_APPLY
	this->CPacketLengthExMgr::Add(10824,   34,   34, 0); // ?? HEADER_ZI_INFO_ENTRY_QUEUE_CANCEL
	this->CPacketLengthExMgr::Add(10825,   30,   30, 0); // ?? HEADER_IZ_INFO_ENTRY_QUEUE_CANCEL
	this->CPacketLengthExMgr::Add(10826,   34,   34, 0); // ?? HEADER_ZI_REQ_ENTRY_QUEUE_CANCEL
	this->CPacketLengthExMgr::Add(10827,   34,   34, 0); // ?? HEADER_IZ_NOTIFY_ENTRY_QUEUE_CANCEL
	this->CPacketLengthExMgr::Add(10828,   35,   35, 0); // ?? HEADER_ZI_RESULT_ENTRY_QUEUE_CANCEL
	this->CPacketLengthExMgr::Add(10829,   31,   31, 0); // ?? HEADER_IZ_RESULT_ENTRY_QUEUE_CANCEL
	this->CPacketLengthExMgr::Add(10830,   34,   34, 0); // ?? HEADER_ZI_ENTRY_QUEUE_ADMISSION
	this->CPacketLengthExMgr::Add(10831,   30,   30, 0); // ?? HEADER_IZ_ENTRY_QUEUE_ADMISSION
	this->CPacketLengthExMgr::Add(10832,   58,   58, 0); // ?? HEADER_ZI_ENTRY_QUEUE_ADMISSION_ACCEPT
	this->CPacketLengthExMgr::Add(10833,   58,   58, 0); // ?? HEADER_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_ACCEPT
	this->CPacketLengthExMgr::Add(10834,   35,   35, 0); // ?? HEADER_ZI_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT
	this->CPacketLengthExMgr::Add(10835,   31,   31, 0); // ?? HEADER_IZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT
	this->CPacketLengthExMgr::Add(10836,   34,   34, 0); // ?? HEADER_ZI_ENTRY_QUEUE_ADMISSION_REFUSE
	this->CPacketLengthExMgr::Add(10837,   34,   34, 0); // ?? HEADER_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_REFUSE
	this->CPacketLengthExMgr::Add(10838,   35,   35, 0); // ?? HEADER_ZI_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE
	this->CPacketLengthExMgr::Add(10839,   31,   31, 0); // ?? HEADER_IZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE
	this->CPacketLengthExMgr::Add(10840,   58,   58, 0); // ?? HEADER_ZI_LOBBY_ADMISSION
	this->CPacketLengthExMgr::Add(10841,   54,   54, 0); // ?? HEADER_IZ_LOBBY_ADMISSION
	this->CPacketLengthExMgr::Add(10842,   82,   82, 0); // ?? HEADER_ZI_LOBBY_ADMISSION_ACCEPT
	this->CPacketLengthExMgr::Add(10843,   82,   82, 0); // ?? HEADER_IZ_NOTIFY_LOBBY_ADMISSION_ACCEPT
	this->CPacketLengthExMgr::Add(10844,   59,   59, 0); // ?? HEADER_ZI_RESULT_LOBBY_ADMISSION_ACCEPT
	this->CPacketLengthExMgr::Add(10845,   55,   55, 0); // ?? HEADER_IZ_RESULT_LOBBY_ADMISSION_ACCEPT
	this->CPacketLengthExMgr::Add(10846,   58,   58, 0); // ?? HEADER_ZI_LOBBY_ADMISSION_REFUSE
	this->CPacketLengthExMgr::Add(10847,   58,   58, 0); // ?? HEADER_IZ_NOTIFY_LOBBY_ADMISSION_REFUSE
	this->CPacketLengthExMgr::Add(10848,   59,   59, 0); // ?? HEADER_ZI_RESULT_LOBBY_ADMISSION_REFUSE
	this->CPacketLengthExMgr::Add(10849,   55,   55, 0); // ?? HEADER_IZ_RESULT_LOBBY_ADMISSION_REFUSE
	this->CPacketLengthExMgr::Add(10850,   30,   30, 0); // ?? HEADER_IZ_ENTRY_QUEUE_LOGOUT
	this->CPacketLengthExMgr::Add(10851,   34,   34, 0); // ?? HEADER_ZI_ENTRY_QUEUE_MOVE_ROOM
	this->CPacketLengthExMgr::Add(10852,   30,   30, 0); // ?? HEADER_IZ_ENTRY_QUEUE_MOVE_ROOM
	this->CPacketLengthExMgr::Add(10853,   34,   34, 0); // ?? HEADER_ZI_LOBBY_MOVE_ROOM
	this->CPacketLengthExMgr::Add(10854,   30,   30, 0); // ?? HEADER_IZ_LOBBY_MOVE_ROOM
	this->CPacketLengthExMgr::Add(10855,   -1,    4, 0); // ?? HEADER_ZI_ENTRY_QUEUE_NAME
	this->CPacketLengthExMgr::Add(10856,   81,   81, 0); // ?? HEADER_ZI_PARTY_RECRUIT_NOTIFY_INSERT
	this->CPacketLengthExMgr::Add(10857,   81,   81, 0); // ?? HEADER_IZ_PARTY_RECRUIT_NOTIFY_INSERT
	this->CPacketLengthExMgr::Add(10858,    6,    6, 0); // ?? HEADER_ZI_PARTY_RECRUIT_NOTIFY_DELETE
	this->CPacketLengthExMgr::Add(10859,    6,    6, 0); // ?? HEADER_IZ_PARTY_RECRUIT_NOTIFY_DELETE
	this->CPacketLengthExMgr::Add(10860,   43,   43, 0); // ?? HEADER_ZI_PARTY_RECRUIT_NOTIFY_UPDATE
	this->CPacketLengthExMgr::Add(10861,   43,   43, 0); // ?? HEADER_IZ_PARTY_RECRUIT_NOTIFY_UPDATE
	this->CPacketLengthExMgr::Add(10862,   40,   40, 0); // ?? HEADER_ZI_PARTY_RECRUIT_VOLUNTEER_INFO
	this->CPacketLengthExMgr::Add(10863,   40,   40, 0); // ?? HEADER_IZ_PARTY_RECRUIT_VOLUNTEER_INFO
	this->CPacketLengthExMgr::Add(10864,   -1,   16, 0); // ?? HEADER_ZI_PARTY_RECRUIT_REQ_RECALL
	this->CPacketLengthExMgr::Add(10865,   30,   30, 0); // ?? HEADER_IZ_PARTY_RECRUIT_REQ_RECALL
	this->CPacketLengthExMgr::Add(10866,   11,   11, 0); // ?? HEADER_ZI_PARTY_RECRUIT_FAILED_RECALL
	this->CPacketLengthExMgr::Add(10867,   11,   11, 0); // ?? HEADER_IZ_PARTY_RECRUIT_FAILED_RECALL
	this->CPacketLengthExMgr::Add(10868,   10,   10, 0); // ?? HEADER_ZI_PARTY_RECRUIT_REFUSE_VOLUNTEER
	this->CPacketLengthExMgr::Add(10869,   10,   10, 0); // ?? HEADER_IZ_PARTY_RECRUIT_REFUSE_VOLUNTEER
	this->CPacketLengthExMgr::Add(10878,   10,   10, 0); // ?? HEADER_ZI_PARTY_RECRUIT_CANCEL_VOLUNTEER
	this->CPacketLengthExMgr::Add(10878,   10,   10, 0); // ?? HEADER_IZ_PARTY_RECRUIT_CANCEL_VOLUNTEER //FIXME: duplicate
	this->CPacketLengthExMgr::Add(10870,  102,  102, 0); // ?? HEADER_AH_JPN_LOGON_ACK
	this->CPacketLengthExMgr::Add(10871,   10,   10, 0); // ?? HEADER_HZ_JPN_PREMIUM_CAMPAIGN
	this->CPacketLengthExMgr::Add(10872,    6,    6, 0); // ?? HEADER_ZI_ENTRY_QUEUE_DELETE_GID
	this->CPacketLengthExMgr::Add(10873,   -1,   77, 0); // ?? HEADER_ZI_MEMORIALDUNGEON_SUBSCRIPTION2
	this->CPacketLengthExMgr::Add(10874,   -1,   48, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_SYNC2
	this->CPacketLengthExMgr::Add(10875,   -1,   16, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_MSG2
	this->CPacketLengthExMgr::Add(10876,   -1,   14, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2
	this->CPacketLengthExMgr::Add(10877,   -1,   20, 0); // ?? HEADER_IZ_MEMORIALDUNGEON_INFO2
	this->CPacketLengthExMgr::Add(10879,    2,    2, 0); // ?? HEADER_ZH_PING
	this->CPacketLengthExMgr::Add(10880,   34,   34, 0); // ?? HEADER_ZI_ENTRY_QUEUE_RANKING
	this->CPacketLengthExMgr::Add(10881,   34,   34, 0); // ?? HEADER_IZ_ENTRY_QUEUE_RANKING
	this->CPacketLengthExMgr::Add(10882,   38,   38, 0); // ?? HEADER_ZI_NOTIFY_ENTRY_QUEUE_RANKING
	this->CPacketLengthExMgr::Add(10883,   34,   34, 0); // ?? HEADER_IZ_NOTIFY_ENTRY_QUEUE_RANKING
	this->CPacketLengthExMgr::Add(10884,   14,   14, 0); // ?? HEADER_ZH_LOGON2RD
	this->CPacketLengthExMgr::Add(10885,   18,   18, 0); // ?? HEADER_ZH_START2RD
	this->CPacketLengthExMgr::Add(10886,   12,   12, 0); // ?? HEADER_ZI_JOB_CHANGE
	this->CPacketLengthExMgr::Add(10887,   -1,    5, 0); // ?? HEADER_HZ_PREMIUM_CAMPAIGN_INFO
	this->CPacketLengthExMgr::Add(10888,   63,   63, 0); // ?? HEADER_ZI_LOBBY_ADMISSION_V2
	this->CPacketLengthExMgr::Add(10889,   59,   59, 0); // ?? HEADER_IZ_LOBBY_ADMISSION_V2
	this->CPacketLengthExMgr::Add(10890,   34,   34, 1); // ?? HEADER_ZI_REQ_JOIN_GUILD2
	this->CPacketLengthExMgr::Add(10891,   38,   38, 1); // ?? HEADER_IZ_REQ_JOIN_GUILD2
	this->CPacketLengthExMgr::Add(10892,   14,   14, 1); // ?? HEADER_ZI_LIST_JOIN_GUILD_INSERT_GID
//	this->CPacketLengthExMgr::Add(10893,    ?,    ?, ?); // ?? HEADER_ZI_LIST_JOIN_GUILD_CHECK_GID
	this->CPacketLengthExMgr::Add(10894,    2,    2, 0); // ?? HEADER_ZI_PING_LIVE
	this->CPacketLengthExMgr::Add(10895,    2,    2, 0); // ?? HEADER_IZ_PING_LIVE
	this->CPacketLengthExMgr::Add(10896,   10,   10, 0); // ?? HEADER_ZI_STATEINFO
	this->CPacketLengthExMgr::Add(10817,    8,    8, 0); // HEADER_HA_IPBONUS_LIMIT
	this->CPacketLengthExMgr::Add(10897,    2,    2, 0); // HEADER_ZH_PING_LIVE
	this->CPacketLengthExMgr::Add(10898,    2,    2, 0); // HEADER_HZ_PING_LIVE
	this->CPacketLengthExMgr::Add(10899,   -1,   29, 0); // ?? HEADER_HZ_PERSONAL_INFORMATION_BRZ
	this->CPacketLengthExMgr::Add(10900,    8,    8, 1); // ?? HEADER_ZI_OTHER_ZONE_PC_SEND_MSG
	this->CPacketLengthExMgr::Add(10901,    8,    8, 1); // ?? HEADER_IZ_OTHER_ZONE_PC_SEND_MSG
	this->CPacketLengthExMgr::Add(10903,    4,    4, 0); // ?? HEADER_IZ_ACK_PRNPC_WINNER
	this->CPacketLengthExMgr::Add(10905,    4,    4, 0); // ?? HEADER_IZ_SET_PRNPC_WINNER
	this->CPacketLengthExMgr::Add(10904,    4,    4, 0); // ?? HEADER_ZI_SET_PRNPC_WINNER
	this->CPacketLengthExMgr::Add(10902,    2,    2, 0); // ?? HEADER_ZI_REQ_PRNPC_WINNER
	this->CPacketLengthExMgr::Add(10906,   20,   20, 0); // ?? HEADER_HZ_LOGON_KOR
//	this->CPacketLengthExMgr::Add(10907,    ?,    ?, ?); // ?? HEADER_AH_LOGON_RUS
	this->CPacketLengthExMgr::Add(20101,   -1,   12, 0); // ?? HEADER_ZI_PRIVATE_DUNGEON_RESERVE
	this->CPacketLengthExMgr::Add(20102,   -1,   18, 0); // ?? HEADER_IZ_PRIVATE_DUNGEON_RESERVE
	this->CPacketLengthExMgr::Add(20103,   -1,   14, 0); // ?? HEADER_IZ_PRIVATE_DUNGEON_CREATE_RESULT
	this->CPacketLengthExMgr::Add(20104,   -1,   22, 0); // ?? HEADER_IZ_PRIVATE_DUNGEON_SYNC
	this->CPacketLengthExMgr::Add(20105,   -1,   12, 0); // ?? HEADER_ZI_PRIVATE_DUNGEON_ENTER
	this->CPacketLengthExMgr::Add(20106,   38,   38, 0); // ?? HEADER_IZ_PRIVATE_DUNGEON_ENTER
	this->CPacketLengthExMgr::Add(10924,   18,   18, 1); // ?? HEADER_ZI_NPC_PROVIDE_EXPINFO
	this->CPacketLengthExMgr::Add(10908,   44,   44, 1); // HEADER_HZ_LOGON_TW
	this->CPacketLengthExMgr::Add(10909,   22,   22, 0); // ?? HEADER_AH_DISPATCH_PREMIUM_INFO_CHN
	this->CPacketLengthExMgr::Add(10910,   12,   12, 0); // ?? HEADER_HZ_FATIGUE_INFO_CHN
	this->CPacketLengthExMgr::Add(10911,   52,   52, 0); // ?? HEADER_HZ_LOGON_CHN
	this->CPacketLengthExMgr::Add(10912,   -1,   36, 0); // ?? HEADER_HZ_PERSONAL_INFORMATION_CHN
	this->CPacketLengthExMgr::Add(10913,  125,  125, 0); // ?? HEADER_AH_LOGON_ACK_CHN
	this->CPacketLengthExMgr::Add(10914,   14,   14, 0); // ?? HEADER_ZI_REQ_JOIN_CLAN
	this->CPacketLengthExMgr::Add(10915,   14,   14, 0); // ?? HEADER_ZI_REQ_LEAVE_CLAN
	this->CPacketLengthExMgr::Add(10916,   10,   10, 0); // ?? HEADER_IZ_CLAN_CONNECTINFO
	this->CPacketLengthExMgr::Add(10917,   -1,    6, 0); // ?? HEADER_IZ_CLAN_CONNECTINFO_ALL
	this->CPacketLengthExMgr::Add(10918,   -1,   12, 0); // ?? HEADER_ZI_CLAN_CHAT
	this->CPacketLengthExMgr::Add(10919,   -1,    8, 0); // ?? HEADER_IZ_CLAN_CHAT
	this->CPacketLengthExMgr::Add(10920,   10,   10, 0); // ?? HEADER_IZ_ACK_JOIN_CLAN
	this->CPacketLengthExMgr::Add(10921,   10,   10, 0); // ?? HEADER_IZ_ACK_LEAVE_CLAN
	this->CPacketLengthExMgr::Add(10922,    6,    6, 0); // ?? HEADER_ZI_REQ_USER_CLANINFO
	this->CPacketLengthExMgr::Add(10923,   10,   10, 0); // ?? HEADER_IZ_ACK_USER_CLANINFO
	this->CPacketLengthExMgr::Add(10925,    6,    6, 0); // ?? HEADER_ZI_MEMORIALDUNGEON_DESTROY
	this->CPacketLengthExMgr::Add(10928,   31,   31, 0); // ?? HEADER_IZ_INSTANTMAP_ADD3
	this->CPacketLengthExMgr::Add(10929,   26,   26, 0); // ?? HEADER_IZ_INSTANTMAP_REMOVE3
	this->CPacketLengthExMgr::Add(10930,    7,    7, 0); // ?? HEADER_IZ_INSTANTMAP_PLAYER_ENTER3
	this->CPacketLengthExMgr::Add(10931,   12,   12, 0); // ?? HEADER_IZ_GET_GUILD_EMBLEM_IMG2
	this->CPacketLengthExMgr::Add(10934,   10,   10, 0); // ?? HEADER_IZ_SET_EFFECT_HIGH_RANKER
	this->CPacketLengthExMgr::Add(10935,    6,    6, 0); // ?? HEADER_IZ_RESET_EFFECT_HIGH_RANKER
//	this->CPacketLengthExMgr::Add(10932,    ?,    ?, ?); // ?? HEADER_AH_LOGON_BRZ
	this->CPacketLengthExMgr::Add(10933,   10,   10, 0); // ?? HEADER_AH_CONNECTED_CHN
	this->CPacketLengthExMgr::Add(10936,   -1,   29, 0); // ?? HEADER_HZ_PERSONAL_INFORMATION_PHL
	this->CPacketLengthExMgr::Add(10937,   -1,   31, 0); // HEADER_HZ_PERSONAL_INFORMATION_THAI
	this->CPacketLengthExMgr::Add(10939,   -1,   25, 0); // HEADER_HZ_PERSONAL_INFORMATION_TW
}


void CPacketLengthExMgr::InitPacketLenWithClient()
{
	this->CPacketLengthExMgr::InitPacketLenWithClientSecure();

	this->CPacketLengthExMgr::Add( 391,   6,   6, 0); // HEADER_PING
	this->CPacketLengthExMgr::Add( 129,   3,   3, 0); // HEADER_SC_NOTIFY_BAN
	this->CPacketLengthExMgr::Add( 454,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 455,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 100,  55,  55, 0);
	this->CPacketLengthExMgr::Add( 105,  -1,  47, 0);
	this->CPacketLengthExMgr::Add( 106,  23,  23, 0);
	this->CPacketLengthExMgr::Add( 475,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 476,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 477,  47,  47, 0);
	this->CPacketLengthExMgr::Add( 506,  48,  48, 0);
	this->CPacketLengthExMgr::Add( 516,  18,  18, 0);
	this->CPacketLengthExMgr::Add( 497,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 512,  26,  26, 0);
	this->CPacketLengthExMgr::Add( 446,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 447,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 101,  17,  17, 0);
	this->CPacketLengthExMgr::Add( 102,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 103,  37,  37, 0);
	this->CPacketLengthExMgr::Add(2416,  31,  31, 0);
	this->CPacketLengthExMgr::Add( 525,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 107,  -1,   4, 0); // HEADER_HC_ACCEPT_ENTER
	this->CPacketLengthExMgr::Add( 108,   3,   3, 0); // HEADER_HC_REFUSE_ENTER
	this->CPacketLengthExMgr::Add( 109, 118, 118, 0);
	this->CPacketLengthExMgr::Add( 110,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 113,  28,  28, 0);
	this->CPacketLengthExMgr::Add( 104,  46,  46, 0);
	this->CPacketLengthExMgr::Add( 507,  56,  56, 0);
	this->CPacketLengthExMgr::Add( 111,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 112,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 714,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 155,  19,  19, 0);
	this->CPacketLengthExMgr::Add( 130,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 167,   5,   5, 0);
	this->CPacketLengthExMgr::Add( 400,   7,   7, 0);
	this->CPacketLengthExMgr::Add( 243,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 137,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 125,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 144,   7,   7, 0);
	this->CPacketLengthExMgr::Add( 153,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 412,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 133,   5,   5, 0);
	this->CPacketLengthExMgr::Add( 204,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 206,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 245,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 278,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 159,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 169,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 171,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 184,   7,   7, 0);
	this->CPacketLengthExMgr::Add( 185,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 178,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 186,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 187,   5,   5, 0);
	this->CPacketLengthExMgr::Add( 191,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 193,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 197,   7,   7, 0);
	this->CPacketLengthExMgr::Add( 200,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 201,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 150,  -1,  28, 0);
	this->CPacketLengthExMgr::Add( 207,  27,  27, 0);
	this->CPacketLengthExMgr::Add( 208,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 211,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 213,  -1,  15, 0);
	this->CPacketLengthExMgr::Add( 217,  14,  14, 0);
	this->CPacketLengthExMgr::Add( 222,  -1,  15, 0);
	this->CPacketLengthExMgr::Add( 224,  30,  30, 0);
	this->CPacketLengthExMgr::Add( 226,  26,  26, 0);
	this->CPacketLengthExMgr::Add( 227,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 228,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 230,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 232,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 235,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 237,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 239,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 148,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 247,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 403,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 249,  26,  26, 0);
	this->CPacketLengthExMgr::Add( 488,  28,  28, 0);
	this->CPacketLengthExMgr::Add( 252,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 255,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 258,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 256,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 259,  30,  30, 0);
	this->CPacketLengthExMgr::Add( 264,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 274,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 114,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 275,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 280,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 283,  20,  20, 0);
	this->CPacketLengthExMgr::Add( 285,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 294,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 295,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 296,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 297,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 298,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 302,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 303,  -1,  84, 0);
	this->CPacketLengthExMgr::Add( 434,  -1,  85, 0);
	this->CPacketLengthExMgr::Add( 308,  -1,   8, 0);
	this->CPacketLengthExMgr::Add( 304,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 312,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 319,  26,  26, 0);
	this->CPacketLengthExMgr::Add( 320,  22,  22, 0);
	this->CPacketLengthExMgr::Add( 323,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 326,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 376,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 378,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 380,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 509,  15,  15, 0);
	this->CPacketLengthExMgr::Add( 394,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 398,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 126,  90,  90, 0);
	this->CPacketLengthExMgr::Add( 407,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 408,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 430,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 603,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 431,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 441,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 461,  30,  30, 1);
	this->CPacketLengthExMgr::Add( 462,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 1091,  8,   8, 0);
	this->CPacketLengthExMgr::Add( 463,  28,  28, 1);
	this->CPacketLengthExMgr::Add( 464,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 481,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 465,  14,  14, 1);
	this->CPacketLengthExMgr::Add( 466,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 140,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 149,  30,  30, 1);
	this->CPacketLengthExMgr::Add( 405, 102, 102, 1);
	this->CPacketLengthExMgr::Add( 162,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 373,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 374, 106, 106, 0);
	this->CPacketLengthExMgr::Add( 121,  53,  53, 1);
	this->CPacketLengthExMgr::Add( 413,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 332,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 333,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 334,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 335,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 336, 110, 110, 1);
	this->CPacketLengthExMgr::Add( 438, 114, 114, 1);
	this->CPacketLengthExMgr::Add( 337,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 338,  -1,  12, 1);
	this->CPacketLengthExMgr::Add( 339,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 340,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 358,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 341,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 342,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 343,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 345,  54,  54, 0);
	this->CPacketLengthExMgr::Add( 346,  66,  66, 1);
	this->CPacketLengthExMgr::Add( 347,  54,  54, 0);
	this->CPacketLengthExMgr::Add( 348,  90,  90, 1);
	this->CPacketLengthExMgr::Add( 349,  42,  42, 0);
	this->CPacketLengthExMgr::Add( 350,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 351,  42,  42, 1);
	this->CPacketLengthExMgr::Add( 352,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 353,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 354,  -1,   6, 1);
	this->CPacketLengthExMgr::Add( 355,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 356,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 357,  30,  30, 0);
	this->CPacketLengthExMgr::Add( 359,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 360,  14,  14, 0);
	this->CPacketLengthExMgr::Add( 361,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 362,  30,  30, 1);
	this->CPacketLengthExMgr::Add( 363,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 329,   9,   9, 0);
	this->CPacketLengthExMgr::Add( 330,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 331,  27,  27, 1);
	this->CPacketLengthExMgr::Add( 366, 186, 186, 0);
	this->CPacketLengthExMgr::Add( 367, 182, 182, 1);
	this->CPacketLengthExMgr::Add( 382,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 383,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 357,  30,  30, 0);
	this->CPacketLengthExMgr::Add( 358,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 359,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 360,  14,  14, 0);
	this->CPacketLengthExMgr::Add( 361,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 362,  30,  30, 1);
	this->CPacketLengthExMgr::Add( 363,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 364,  43,  43, 1);
	this->CPacketLengthExMgr::Add( 364,  43,  43, 1);
	this->CPacketLengthExMgr::Add( 365,  14,  14, 1);
	this->CPacketLengthExMgr::Add( 498,  20,  20, 1);
	this->CPacketLengthExMgr::Add( 368,  14,  14, 0);
	this->CPacketLengthExMgr::Add( 369,  30,  30, 1);
	this->CPacketLengthExMgr::Add( 370,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 371,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 372,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 384,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 385,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 386, 106, 106, 1);
	this->CPacketLengthExMgr::Add( 387,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 388,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 389,  34,  34, 1);
	this->CPacketLengthExMgr::Add( 414,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 415,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 416,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 417,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 418,  37,  37, 1);
	this->CPacketLengthExMgr::Add( 419,   5,   5, 1);
	this->CPacketLengthExMgr::Add( 420,  11,  11, 1);
	this->CPacketLengthExMgr::Add( 421,  26,  26, 0);
	this->CPacketLengthExMgr::Add( 422,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 423,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 424,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 425,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 426,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 458,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 432,  11,  11, 1);
	this->CPacketLengthExMgr::Add( 433,   7,   7, 1);
	this->CPacketLengthExMgr::Add( 442,  26,  26, 0);
	this->CPacketLengthExMgr::Add( 443,  26,  26, 0);
	this->CPacketLengthExMgr::Add( 444,  26,  26, 0);
	this->CPacketLengthExMgr::Add( 445,  26,  26, 0);
	this->CPacketLengthExMgr::Add( 448,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 449,  14,  14, 1);
	this->CPacketLengthExMgr::Add( 450,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 467,  35,  35, 1);
	this->CPacketLengthExMgr::Add( 469,  -1,   8, 0);
	this->CPacketLengthExMgr::Add( 468,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 479,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 499,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 644,  14,  14, 1);
	this->CPacketLengthExMgr::Add( 511,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 493,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 487,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 439,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 503,  14,  14, 0);
	this->CPacketLengthExMgr::Add( 483,  14,  14, 0);
	this->CPacketLengthExMgr::Add( 459,   9,   9, 0);
	this->CPacketLengthExMgr::Add( 505,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 485,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 513,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 515,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 517,  26,  26, 1);
	this->CPacketLengthExMgr::Add( 518,  11,  11, 1);
	this->CPacketLengthExMgr::Add( 519,  34,  34, 1);
	this->CPacketLengthExMgr::Add( 520,  14,  14, 0);
	this->CPacketLengthExMgr::Add( 521,  36,  36, 1);
	this->CPacketLengthExMgr::Add( 522,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 526,  32,  32, 1);
	this->CPacketLengthExMgr::Add( 530,  26,  26, 0);
	this->CPacketLengthExMgr::Add( 531,  26,  26, 0);
	this->CPacketLengthExMgr::Add( 532,  42,  42, 1);
	this->CPacketLengthExMgr::Add( 533,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 534,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 535,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 536,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 549,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 537, 282, 282, 1);
	this->CPacketLengthExMgr::Add( 538, 282, 282, 1);
	this->CPacketLengthExMgr::Add( 550, 282, 282, 1);
	this->CPacketLengthExMgr::Add( 642, 284, 284, 1);
	this->CPacketLengthExMgr::Add( 539,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 540,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 548,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 640,  12,  12, 1);
	this->CPacketLengthExMgr::Add( 645,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 646,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 541,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 542,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 543,  66,  66, 1);
	this->CPacketLengthExMgr::Add( 546,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 545,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 544,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 547,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 115,  11,  11, 1);
	this->CPacketLengthExMgr::Add( 116,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 117,  -1,  11, 1);
	this->CPacketLengthExMgr::Add( 118,   9,   9, 1);
	this->CPacketLengthExMgr::Add( 119,   5,   5, 1);
	this->CPacketLengthExMgr::Add( 120,  55,  55, 1);
	this->CPacketLengthExMgr::Add( 122,  58,  58, 1);
	this->CPacketLengthExMgr::Add( 123,  60,  60, 1);
	this->CPacketLengthExMgr::Add( 124,  44,  44, 1);
	this->CPacketLengthExMgr::Add( 127,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 128,   7,   7, 1);
	this->CPacketLengthExMgr::Add( 131,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 132,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 134,  16,  16, 1);
	this->CPacketLengthExMgr::Add( 135,  12,  12, 1);
	this->CPacketLengthExMgr::Add( 136,  10,  10, 1);
	this->CPacketLengthExMgr::Add(2253,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 138,  29,  29, 1);
	this->CPacketLengthExMgr::Add( 139,  23,  23, 1);
	this->CPacketLengthExMgr::Add( 141,  -1,   8, 1);
	this->CPacketLengthExMgr::Add( 142,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 145,  22,  22, 1);
	this->CPacketLengthExMgr::Add( 146,  28,  28, 1);
	this->CPacketLengthExMgr::Add( 147,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 151,  -1,  32, 1);
	this->CPacketLengthExMgr::Add( 152,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 154,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 156,   9,   9, 1);
	this->CPacketLengthExMgr::Add( 157,  17,  17, 1);
	this->CPacketLengthExMgr::Add( 158,  17,  17, 1);
	this->CPacketLengthExMgr::Add( 160,  23,  23, 1);
	this->CPacketLengthExMgr::Add( 161,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 163,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 164,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 165,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 166,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 168,   7,   7, 1);
	this->CPacketLengthExMgr::Add( 170,   9,   9, 1);
	this->CPacketLengthExMgr::Add( 172,   7,   7, 1);
	this->CPacketLengthExMgr::Add( 174,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 175,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 176,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 177,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 179,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 180,  -1,   8, 1);
	this->CPacketLengthExMgr::Add( 181,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 182,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 183,  -1,   8, 1);
	this->CPacketLengthExMgr::Add( 188,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 189,  44,  44, 1);
	this->CPacketLengthExMgr::Add( 190,   5,   5, 1);
	this->CPacketLengthExMgr::Add( 192,   7,   7, 1);
	this->CPacketLengthExMgr::Add( 194,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 195,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 196,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 198,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 199,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 202,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 203,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 205,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 209,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 210,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 212,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 214,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 215,  -1,  17, 1);
	this->CPacketLengthExMgr::Add( 216,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 218,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 219,  -1,   8, 1);
	this->CPacketLengthExMgr::Add( 220,  28,  28, 1);
	this->CPacketLengthExMgr::Add( 221,  29,  29, 1);
	this->CPacketLengthExMgr::Add( 223,  -1,  17, 1);
	this->CPacketLengthExMgr::Add( 225,  30,  30, 1);
	this->CPacketLengthExMgr::Add( 229,  26,  26, 1);
	this->CPacketLengthExMgr::Add( 231,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 233,  19,  19, 1);
	this->CPacketLengthExMgr::Add( 234,   5,   5, 1);
	this->CPacketLengthExMgr::Add( 236,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 238,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 240,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 241,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 242,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 244,  21,  21, 1);
	this->CPacketLengthExMgr::Add( 246,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 248,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 250,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 251,  -1,  28, 1);
	this->CPacketLengthExMgr::Add( 253,  27,  27, 1);
	this->CPacketLengthExMgr::Add( 254,  30,  30, 1);
	this->CPacketLengthExMgr::Add( 257,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 260,  79,  79, 1);
	this->CPacketLengthExMgr::Add( 261,  31,  31, 1);
	this->CPacketLengthExMgr::Add( 262,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 263,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 265,  -1,   8, 1);
	this->CPacketLengthExMgr::Add( 266,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 267,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 268,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 269,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 270,  11,  11, 1);
	this->CPacketLengthExMgr::Add( 271,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 689,  -1,   8, 1);
	this->CPacketLengthExMgr::Add( 690,  -1,   8, 1);
	this->CPacketLengthExMgr::Add( 693,  -1,   6, 1);
	this->CPacketLengthExMgr::Add( 272,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 273,  39,  39, 1);
	this->CPacketLengthExMgr::Add( 276,  31,  31, 1);
	this->CPacketLengthExMgr::Add( 277,  35,  35, 1);
	this->CPacketLengthExMgr::Add( 279,  18,  18, 1);
	this->CPacketLengthExMgr::Add( 281,  13,  13, 1);
	this->CPacketLengthExMgr::Add( 553,  15,  15, 1);
	this->CPacketLengthExMgr::Add( 282,  15,  15, 1);
	this->CPacketLengthExMgr::Add( 284,  68,  68, 1);
	this->CPacketLengthExMgr::Add( 286,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 287,  16,  16, 1);
	this->CPacketLengthExMgr::Add( 288,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 289,  14,  14, 1);
	this->CPacketLengthExMgr::Add( 290,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 291,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 292,  21,  21, 1);
	this->CPacketLengthExMgr::Add( 293,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 299,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 300,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 301,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 305,  86,  86, 1);
	this->CPacketLengthExMgr::Add( 306,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 307,  -1,   8, 1);
	this->CPacketLengthExMgr::Add( 309,   7,   7, 1);
	this->CPacketLengthExMgr::Add( 310,  -1,   8, 1);
	this->CPacketLengthExMgr::Add( 311,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 313,  16,  16, 1);
	this->CPacketLengthExMgr::Add( 314,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 315,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 316,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 317,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 318,  24,  24, 1);
	this->CPacketLengthExMgr::Add( 321,  14,  14, 1);
	this->CPacketLengthExMgr::Add( 322,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 324,  23,  23, 1);
	this->CPacketLengthExMgr::Add( 325,  19,  19, 1);
	this->CPacketLengthExMgr::Add( 327,  39,  39, 1);
	this->CPacketLengthExMgr::Add( 328,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 375,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 377,   5,   5, 1);
	this->CPacketLengthExMgr::Add( 379,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 381,   7,   7, 1);
	this->CPacketLengthExMgr::Add( 392,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 393,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 395,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 396,  29,  29, 1);
	this->CPacketLengthExMgr::Add( 397,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 399,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 401,  86,  86, 1);
	this->CPacketLengthExMgr::Add( 402,  24,  24, 1);
	this->CPacketLengthExMgr::Add( 404,  30,  30, 1);
	this->CPacketLengthExMgr::Add( 406,   9,   9, 1);
	this->CPacketLengthExMgr::Add( 650,  18,  18, 1);
	this->CPacketLengthExMgr::Add( 409,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 410,  14,  14, 1);
	this->CPacketLengthExMgr::Add( 411,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 427,  12,  12, 1);
	this->CPacketLengthExMgr::Add( 428,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 429,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 602,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 435,  67,  67, 1);
	this->CPacketLengthExMgr::Add( 436,  12,  12, 1);
	this->CPacketLengthExMgr::Add( 437,  18,  18, 0);
	this->CPacketLengthExMgr::Add( 440,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 451,  -1,  16, 1);
	this->CPacketLengthExMgr::Add( 452,  22,  22, 1);
	this->CPacketLengthExMgr::Add( 453,  22,  22, 1);
	this->CPacketLengthExMgr::Add( 456,  13,  13, 1);
	this->CPacketLengthExMgr::Add( 457,  97,  97, 1);
	this->CPacketLengthExMgr::Add( 460,   9,   9, 1);
	this->CPacketLengthExMgr::Add( 470,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 471,  11,  11, 1);
	this->CPacketLengthExMgr::Add( 472,  54,  54, 1);
	this->CPacketLengthExMgr::Add( 554,  58,  58, 1);
	this->CPacketLengthExMgr::Add( 473,  53,  53, 1);
	this->CPacketLengthExMgr::Add( 555,  57,  57, 1);
	this->CPacketLengthExMgr::Add( 474,  60,  60, 1);
	this->CPacketLengthExMgr::Add( 556,  65,  65, 1);
	this->CPacketLengthExMgr::Add( 478,  33,  33, 1);
	this->CPacketLengthExMgr::Add( 480,  30,  30, 1);
	this->CPacketLengthExMgr::Add( 482,  34,  34, 1);
	this->CPacketLengthExMgr::Add( 484,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 486,  26,  26, 1);
	this->CPacketLengthExMgr::Add( 489,  81,  81, 1);
	this->CPacketLengthExMgr::Add( 490,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 491,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 492,  26,  26, 1);
	this->CPacketLengthExMgr::Add( 494,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 495,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 496,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 500,  32,  32, 1);
	this->CPacketLengthExMgr::Add( 501,   9,   9, 1);
	this->CPacketLengthExMgr::Add( 502,  34,  34, 1);
	this->CPacketLengthExMgr::Add( 595,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 596,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 504,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 508,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 510,   5,   5, 1);
	this->CPacketLengthExMgr::Add( 551,  18,  18, 0);
	this->CPacketLengthExMgr::Add( 552,  18,  18, 0);
	this->CPacketLengthExMgr::Add( 562,   9,   9, 0);
	this->CPacketLengthExMgr::Add( 563,  11,  11, 0);
	this->CPacketLengthExMgr::Add( 564,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 560,  12,  12, 1);
	this->CPacketLengthExMgr::Add( 558,  71,  71, 1);
	this->CPacketLengthExMgr::Add( 637,  62,  62, 0);
	this->CPacketLengthExMgr::Add( 565,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 569,  11,  11, 1);
	this->CPacketLengthExMgr::Add( 559,   5,   5, 1);
	this->CPacketLengthExMgr::Add( 561,  26,  26, 0);
	this->CPacketLengthExMgr::Add( 567,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 568, 282, 282, 1);
	this->CPacketLengthExMgr::Add( 566,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 570,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 572,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 573,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 574,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 575,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 576,  -1,   8, 1);
	this->CPacketLengthExMgr::Add( 577,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 578,  -1,  99, 1);
	this->CPacketLengthExMgr::Add( 579,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 599,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 580,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 581,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 582,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 583,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 584,  -1,  68, 0);
	this->CPacketLengthExMgr::Add( 585,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 586,  70,  70, 1);
	this->CPacketLengthExMgr::Add( 587,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 588,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 589,  12,  12, 0);
	this->CPacketLengthExMgr::Add( 590,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 591,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 592,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 593,  34,  34, 0);
	this->CPacketLengthExMgr::Add( 594,  -1,  12, 1);
	this->CPacketLengthExMgr::Add( 597,   5,   5, 1);
	this->CPacketLengthExMgr::Add( 598,   5,   5, 1);
	this->CPacketLengthExMgr::Add( 600,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 601,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 604,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 605,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 606,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 607,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 608,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 609,  11,  11, 0);
	this->CPacketLengthExMgr::Add( 610,  11,  11, 0);
	this->CPacketLengthExMgr::Add( 611,  11,  11, 0);
	this->CPacketLengthExMgr::Add( 612,  20,  20, 0);
	this->CPacketLengthExMgr::Add( 613,  20,  20, 0);
	this->CPacketLengthExMgr::Add( 614,  30,  30, 0);
	this->CPacketLengthExMgr::Add( 615,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 616,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 617,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 618,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 619,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 620,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 621,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 623,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 624,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 625,  40,  40, 0);
	this->CPacketLengthExMgr::Add( 626,  44,  44, 0);
	this->CPacketLengthExMgr::Add( 627,  30,  30, 0);
	this->CPacketLengthExMgr::Add( 628,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 629,  37,  37, 0);
	this->CPacketLengthExMgr::Add( 630,  -1,  51, 0);
	this->CPacketLengthExMgr::Add( 631,  84,  84, 0);
	this->CPacketLengthExMgr::Add( 632,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 633,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 634,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 635,  14,  14, 0);
	this->CPacketLengthExMgr::Add( 636,  60,  60, 0);
	this->CPacketLengthExMgr::Add( 638,  -1,   6, 0);
	this->CPacketLengthExMgr::Add( 639,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 643,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 647,  -1,   8, 1);
	this->CPacketLengthExMgr::Add( 648,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 649,   8,   8, 1);
	this->CPacketLengthExMgr::Add(1092,  -1,   8, 1);
	this->CPacketLengthExMgr::Add(1093,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 651,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 652,  46,  46, 0);
	this->CPacketLengthExMgr::Add( 653,  34,  34, 0);
	this->CPacketLengthExMgr::Add( 654,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 655,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 656,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 657,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 658,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 659,  70,  70, 1);
	this->CPacketLengthExMgr::Add( 660,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 661,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 662,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 663,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 664,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 665,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 666,  27,  27, 1);
	this->CPacketLengthExMgr::Add( 667,  80,  80, 1);
	this->CPacketLengthExMgr::Add( 668,  66,  66, 0);
	this->CPacketLengthExMgr::Add( 669,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 670,  11,  11, 1);
	this->CPacketLengthExMgr::Add( 671,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 674,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 677,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 678,  -1,  10, 0);
	this->CPacketLengthExMgr::Add( 679,  -1,  10, 0);
	this->CPacketLengthExMgr::Add( 682,   4,   4, 0);
	this->CPacketLengthExMgr::Add( 683,  36,  36, 0);
	this->CPacketLengthExMgr::Add( 684,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 685,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 688,  85,  85, 0);
	this->CPacketLengthExMgr::Add( 696,  22,  22, 1);
	this->CPacketLengthExMgr::Add( 699,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 697, 191, 191, 1);
	this->CPacketLengthExMgr::Add( 698,  11,  11, 0);
	this->CPacketLengthExMgr::Add( 700,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 691, 107, 107, 1);
	this->CPacketLengthExMgr::Add( 692,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 694,   7,   7, 0);
	this->CPacketLengthExMgr::Add( 695,   7,   7, 1);
	this->CPacketLengthExMgr::Add( 705,  -1,  12, 1);
	this->CPacketLengthExMgr::Add( 706,  -1,   6, 1);
	this->CPacketLengthExMgr::Add( 709,  30,  30, 1);
	this->CPacketLengthExMgr::Add( 712,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 713,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 710,  30,  30, 1);
	this->CPacketLengthExMgr::Add( 711,   7,   7, 0);
	this->CPacketLengthExMgr::Add( 715,  65,  65, 1);
	this->CPacketLengthExMgr::Add( 716,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 717,  71,  71, 1);
	this->CPacketLengthExMgr::Add( 718,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 719,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 725,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 720,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 721,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 722,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 723,   4,   4, 1);
	this->CPacketLengthExMgr::Add( 724,  29,  29, 1);
	this->CPacketLengthExMgr::Add( 726,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 727,  -1,  43, 1);
	this->CPacketLengthExMgr::Add( 728,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 729,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 730,   3,   3, 1);
	this->CPacketLengthExMgr::Add( 731,  -1,   4, 0);
	this->CPacketLengthExMgr::Add( 732,  -1,  32, 1);
	this->CPacketLengthExMgr::Add( 733,  32,  32, 1);
	this->CPacketLengthExMgr::Add( 734,   6,   6, 1);
	this->CPacketLengthExMgr::Add( 735,  36,  36, 1);
	this->CPacketLengthExMgr::Add( 736,  34,  34, 1);
	this->CPacketLengthExMgr::Add( 737,  33,  33, 1);
	this->CPacketLengthExMgr::Add( 738,   8,   8, 0);
	this->CPacketLengthExMgr::Add( 739,  10,  10, 0);
	this->CPacketLengthExMgr::Add( 740,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 741,   5,   5, 0);
	this->CPacketLengthExMgr::Add( 742,   6,   6, 0);
	this->CPacketLengthExMgr::Add( 743,  -1,   6, 1);
	this->CPacketLengthExMgr::Add( 744,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 745,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 746,  -1,   4, 1);
	this->CPacketLengthExMgr::Add( 747,  13,  13, 1);
	this->CPacketLengthExMgr::Add( 748,  67,  67, 1);
	this->CPacketLengthExMgr::Add( 749,  59,  59, 1);
	this->CPacketLengthExMgr::Add( 750,  60,  60, 1);
	this->CPacketLengthExMgr::Add( 751,   8,   8, 1);
	this->CPacketLengthExMgr::Add( 752,  10,  10, 1);
	this->CPacketLengthExMgr::Add( 753,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 754,   2,   2, 1);
	this->CPacketLengthExMgr::Add( 860,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 861,  -1,  16, 0);
	this->CPacketLengthExMgr::Add( 862,   2,   2, 0);
	this->CPacketLengthExMgr::Add( 989,  18,  18, 0);
	this->CPacketLengthExMgr::Add( 990,  18,  18, 0);
	this->CPacketLengthExMgr::Add(1081,   8,   8, 0);
	this->CPacketLengthExMgr::Add(1085,   8,   8, 1);
	this->CPacketLengthExMgr::Add(1086,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(1087,  25,  25, 1);
	this->CPacketLengthExMgr::Add(1088,  10,  10, 1);
	this->CPacketLengthExMgr::Add(1089,   4,   4, 1);
	this->CPacketLengthExMgr::Add(1090,  -1,   8, 1);
	this->CPacketLengthExMgr::Add(1091,   8,   8, 0);
	this->CPacketLengthExMgr::Add(1094,  14,  14, 1);
	this->CPacketLengthExMgr::Add(1096,  -1,   4, 0);
	this->CPacketLengthExMgr::Add(1097,   4,   4, 0);
	this->CPacketLengthExMgr::Add(1098,   6,   6, 0);
	this->CPacketLengthExMgr::Add(1099,   2,   2, 0);
	this->CPacketLengthExMgr::Add(1095,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2007,   8,   8, 0);
	this->CPacketLengthExMgr::Add(2008,   8,   8, 1);
	this->CPacketLengthExMgr::Add(2009, 268, 268, 1);
	this->CPacketLengthExMgr::Add(2010,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2011,   8,   8, 1);
	this->CPacketLengthExMgr::Add(2012,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2013,  54,  54, 1);
	this->CPacketLengthExMgr::Add(2014,  30,  30, 0);
	this->CPacketLengthExMgr::Add(2015,  54,  54, 0);
	this->CPacketLengthExMgr::Add(2016,  58,  58, 0);
	this->CPacketLengthExMgr::Add(2017,  15,  15, 1);
	this->CPacketLengthExMgr::Add(2018,   8,   8, 1);
	this->CPacketLengthExMgr::Add(2019,   6,   6, 1);
	this->CPacketLengthExMgr::Add(2022,   8,   8, 1);
	this->CPacketLengthExMgr::Add(2021,   4,   4, 0);
	this->CPacketLengthExMgr::Add(2024,  -1,   4, 0);
	this->CPacketLengthExMgr::Add(2023,  32,  32, 0);
	this->CPacketLengthExMgr::Add(2025,   5,   5, 0);
	this->CPacketLengthExMgr::Add(2026,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2027,  -1,   8, 1);
	this->CPacketLengthExMgr::Add(2029,  10,  10, 1);
	this->CPacketLengthExMgr::Add(2030,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2031,   8,   8, 1);
	this->CPacketLengthExMgr::Add(2032,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2033,  18,  18, 1);
	this->CPacketLengthExMgr::Add(2034,   8,   8, 1);
	this->CPacketLengthExMgr::Add(2035,   6,   6, 1);
	this->CPacketLengthExMgr::Add(2036,   3,   3, 0);
	this->CPacketLengthExMgr::Add(2037,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2038,  14,  14, 1);
	this->CPacketLengthExMgr::Add(2039,  -1,  69, 1);
	this->CPacketLengthExMgr::Add(2040,  -1,  62, 1);
	this->CPacketLengthExMgr::Add(2041,  -1,  63, 1);
	this->CPacketLengthExMgr::Add(2042,   8,   8, 1);
	this->CPacketLengthExMgr::Add(2043,  25,  25, 1);
	this->CPacketLengthExMgr::Add(2044,  10,  10, 1);
	this->CPacketLengthExMgr::Add(2045,  -1,   7, 1);
	this->CPacketLengthExMgr::Add(2046,  26,  26, 1);
	this->CPacketLengthExMgr::Add(2048,  -1,  12, 1);
	this->CPacketLengthExMgr::Add(2049,  -1,  12, 0);
	this->CPacketLengthExMgr::Add(2051,   4,   4, 1);
	this->CPacketLengthExMgr::Add(2052,  14,  14, 0);
	this->CPacketLengthExMgr::Add(2053,  -1,   5, 1);
	this->CPacketLengthExMgr::Add(2054,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2055,   4,   4, 1);
	this->CPacketLengthExMgr::Add(2056,  14,  14, 0);
	this->CPacketLengthExMgr::Add(2057,  50,  50, 1);
	this->CPacketLengthExMgr::Add(2058,  18,  18, 1);
	this->CPacketLengthExMgr::Add(2059,   6,   6, 1);
	this->CPacketLengthExMgr::Add(2060,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2061,   3,   3, 1);
	this->CPacketLengthExMgr::Add(2062,  14,  14, 1);
	this->CPacketLengthExMgr::Add(2063,  20,  20, 1);
	this->CPacketLengthExMgr::Add(2064,   3,   3, 1);
	this->CPacketLengthExMgr::Add(2066,   8,   8, 1);
	this->CPacketLengthExMgr::Add(2067,  -1,  12, 1);
	this->CPacketLengthExMgr::Add(2068,  86,  86, 1);
	this->CPacketLengthExMgr::Add(2070,   6,   6, 1);
	this->CPacketLengthExMgr::Add(2072,  -1,  16, 1);
	this->CPacketLengthExMgr::Add(2074,   4,   4, 1);
	this->CPacketLengthExMgr::Add(2084,   6,   6, 1);
	this->CPacketLengthExMgr::Add(2075,  10,  10, 1);
	this->CPacketLengthExMgr::Add(2076,  10,  10, 1);
	this->CPacketLengthExMgr::Add(2077,  22,  22, 1);
	this->CPacketLengthExMgr::Add(2078,   8,   8, 1);
	this->CPacketLengthExMgr::Add(2079,  -1,   9, 1);
	this->CPacketLengthExMgr::Add(2080,  11,  11, 0);
	this->CPacketLengthExMgr::Add(2081,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2082,   9,   9, 0);
	this->CPacketLengthExMgr::Add(2083, - 1,   6, 0);
	this->CPacketLengthExMgr::Add(2085, - 1,  65, 0);
	this->CPacketLengthExMgr::Add(2086,   4,   4, 0);
	this->CPacketLengthExMgr::Add(2102,  -1,   7, 0);
	this->CPacketLengthExMgr::Add(2103,   3,   3, 0);
	this->CPacketLengthExMgr::Add(2105,  66,  66, 1);
	this->CPacketLengthExMgr::Add(2106,   5,   5, 0);
	this->CPacketLengthExMgr::Add(2107,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2109,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2110,  26,  26, 0);
	this->CPacketLengthExMgr::Add(2112,  -1,   4, 0);
	this->CPacketLengthExMgr::Add(2113,   4,   4, 0);
	this->CPacketLengthExMgr::Add(2087,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2088,  14,  14, 0);
	this->CPacketLengthExMgr::Add(2089,  12,  12, 0);
	this->CPacketLengthExMgr::Add(2090,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2091,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2092,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2114,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2115,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2116,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2117,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2118,   4,   4, 0);
	this->CPacketLengthExMgr::Add(2119,  -1,   6, 0);
	this->CPacketLengthExMgr::Add(2120,  -1,   6, 0);
	this->CPacketLengthExMgr::Add(2121,  12,  12, 0);
	this->CPacketLengthExMgr::Add(2122,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2123,  19,  19, 1);
	this->CPacketLengthExMgr::Add(2124,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2125,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2126,   5,   5, 0);
	this->CPacketLengthExMgr::Add(2127,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2128,   7,   7, 0);
	this->CPacketLengthExMgr::Add(2133,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2129,  -1,   4, 0);
	this->CPacketLengthExMgr::Add(2130,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2131,  -1,   4, 0);
	this->CPacketLengthExMgr::Add(2132,  -1,   4, 0);
	this->CPacketLengthExMgr::Add(2134,  -1,  71, 1);
	this->CPacketLengthExMgr::Add(2135,  -1,  65, 1);
	this->CPacketLengthExMgr::Add(2136,  -1,  64, 1);
	this->CPacketLengthExMgr::Add(2137,  -1,  45, 1);
	this->CPacketLengthExMgr::Add(2225,  -1,   4, 0);
	this->CPacketLengthExMgr::Add(2093,  -1,  29, 0);
	this->CPacketLengthExMgr::Add(2226,  -1,   6, 0);
	this->CPacketLengthExMgr::Add(2223,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2224,  17,  17, 0);
	this->CPacketLengthExMgr::Add(2227,  -1,   8, 0);
	this->CPacketLengthExMgr::Add(2228,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2229,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2230,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 755,  -1,  68, 0);
	this->CPacketLengthExMgr::Add( 756,   3,   3, 0);
	this->CPacketLengthExMgr::Add( 757,   7,   7, 0);
	this->CPacketLengthExMgr::Add( 758,   7,   7, 0);
	this->CPacketLengthExMgr::Add(2232,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2233,  12,  12, 0);
	this->CPacketLengthExMgr::Add(2234,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2235,   8,   8, 0);
	this->CPacketLengthExMgr::Add(2236,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2237,   8,   8, 0);
	this->CPacketLengthExMgr::Add(2238,  14,  14, 0);
	this->CPacketLengthExMgr::Add(2239,   8,   8, 0);
	this->CPacketLengthExMgr::Add(2243,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2244,   8,   8, 0);
	this->CPacketLengthExMgr::Add(2245,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2246,   4,   4, 0);
	this->CPacketLengthExMgr::Add(2240,  -1,  10, 0);
	this->CPacketLengthExMgr::Add(2241,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2242,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2247,  -1,  19, 1);
	this->CPacketLengthExMgr::Add(2248,  34,  34, 1);
	this->CPacketLengthExMgr::Add(2249,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2250,  -1,   8, 0);
	this->CPacketLengthExMgr::Add(2251,  -1,  10, 0);
	this->CPacketLengthExMgr::Add(2427,  -1,  16, 0);
	this->CPacketLengthExMgr::Add(2252, 109, 109, 0);
	this->CPacketLengthExMgr::Add(2254,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2255,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2256,   9,   9, 1);
	this->CPacketLengthExMgr::Add(2257,   7,   7, 1);
	this->CPacketLengthExMgr::Add(2258,  10,  10, 1);
	this->CPacketLengthExMgr::Add(2259,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2260,   8,   8, 0);
	this->CPacketLengthExMgr::Add(2261,  -1,   8, 0);
	this->CPacketLengthExMgr::Add(2262,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2263,  28,  28, 1);
	this->CPacketLengthExMgr::Add(2264,  27,  27, 1);
	this->CPacketLengthExMgr::Add(2265,  30,  30, 1);
	this->CPacketLengthExMgr::Add(2266,  26,  26, 1);
	this->CPacketLengthExMgr::Add(2267,  27,  27, 1);
	this->CPacketLengthExMgr::Add(2268,  26,  26, 1);
	this->CPacketLengthExMgr::Add(2269,  27,  27, 1);
	this->CPacketLengthExMgr::Add(2270,  27,  27, 1);
	this->CPacketLengthExMgr::Add(2271,  50,  50, 1);
	this->CPacketLengthExMgr::Add(2272,  51,  51, 1);
	this->CPacketLengthExMgr::Add(2273,  51,  51, 1);
	this->CPacketLengthExMgr::Add(2274,  27,  27, 0);
	this->CPacketLengthExMgr::Add(2275, 118, 118, 0);
	this->CPacketLengthExMgr::Add(2276,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2277,  41,  41, 0);
	this->CPacketLengthExMgr::Add(2278,   4,   4, 0);
	this->CPacketLengthExMgr::Add(2279,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2280,  -1,   5, 1);
	this->CPacketLengthExMgr::Add(2281,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2282,   4,   4, 0);
	this->CPacketLengthExMgr::Add(2283,  39,  39, 0);
	this->CPacketLengthExMgr::Add(2284,  73,  73, 0);
	this->CPacketLengthExMgr::Add(2285,  43,  43, 0);
	this->CPacketLengthExMgr::Add(2286,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2287,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2288,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2289,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2290,  36,  36, 0);
	this->CPacketLengthExMgr::Add(2291,  -1,   8, 0);
	this->CPacketLengthExMgr::Add(2292,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2293,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2294,  22,  22, 1);
	this->CPacketLengthExMgr::Add(2295,   3,   3, 1);
	this->CPacketLengthExMgr::Add(2296,   7,   7, 1);
	this->CPacketLengthExMgr::Add(2297,   6,   6, 1);
	this->CPacketLengthExMgr::Add(2298,   6,   6, 1);
	this->CPacketLengthExMgr::Add(2299,   6,   6, 1);
	this->CPacketLengthExMgr::Add(2313,   6,   6, 1);
	this->CPacketLengthExMgr::Add(2315,  30,  30, 0);
	this->CPacketLengthExMgr::Add(2316,  30,  30, 0);
	this->CPacketLengthExMgr::Add(2300,  30,  30, 0);
	this->CPacketLengthExMgr::Add(2301,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2302,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2303,  24,  24, 1);
	this->CPacketLengthExMgr::Add(2304,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2305,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2306,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2307,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2308,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2309,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2310,  -1,  45, 1);
	this->CPacketLengthExMgr::Add(2311,   5,   5, 0);
	this->CPacketLengthExMgr::Add(2312,   5,   5, 1);
	this->CPacketLengthExMgr::Add(2314,  26,  26, 1);
	this->CPacketLengthExMgr::Add(2317,  -1,  10, 1);
	this->CPacketLengthExMgr::Add(2318,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2320,  10,  10, 1);
	this->CPacketLengthExMgr::Add(2321,  30,  30, 1);
	this->CPacketLengthExMgr::Add(2322,  10,  10, 1);
	this->CPacketLengthExMgr::Add(2323,  30,  30, 1);
	this->CPacketLengthExMgr::Add(2324,  -1,  80, 1);
	this->CPacketLengthExMgr::Add(2319,  -1,  73, 1);
	this->CPacketLengthExMgr::Add(2325,  -1,  74, 1);
	this->CPacketLengthExMgr::Add(2326,  26,  26, 1);
	this->CPacketLengthExMgr::Add(2411,   4,   4, 1);
	this->CPacketLengthExMgr::Add(2412,   6,   6, 1);
	this->CPacketLengthExMgr::Add(2413,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2414,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2415,   7,   7, 1);
	this->CPacketLengthExMgr::Add(2417,   6,   6, 1);
	this->CPacketLengthExMgr::Add(2418,  -1,   9, 1);
	this->CPacketLengthExMgr::Add(2419,   7,   7, 1);
	this->CPacketLengthExMgr::Add(2420,   2,   2, 1);
	this->CPacketLengthExMgr::Add(2421,  -1,  28, 1);
	this->CPacketLengthExMgr::Add(2422,  -1,  28, 1);
	this->CPacketLengthExMgr::Add(2423,  14,  14, 1);
	this->CPacketLengthExMgr::Add(2424,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2425,  50,  50, 0);
	this->CPacketLengthExMgr::Add(2426,  -1,   8, 1);
	this->CPacketLengthExMgr::Add(2428,   4,   4, 0);
	this->CPacketLengthExMgr::Add(2429, 288, 288, 1);
	this->CPacketLengthExMgr::Add(2430,  12,  12, 1);
	this->CPacketLengthExMgr::Add(2431,  -1,   8, 1);
	this->CPacketLengthExMgr::Add(2432,   7,   7, 1);
	this->CPacketLengthExMgr::Add(2433,  -1,  12, 0);
	this->CPacketLengthExMgr::Add(2434,   7,   7, 0);
	this->CPacketLengthExMgr::Add(2435,  29,  29, 1);
	this->CPacketLengthExMgr::Add(2436,  28,  28, 1);
	this->CPacketLengthExMgr::Add(2437,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2438,  10,  10, 0);
	this->CPacketLengthExMgr::Add(2439,  -1,  41, 0);
	this->CPacketLengthExMgr::Add(2440,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2441,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2442,  -1,  74, 0);
	this->CPacketLengthExMgr::Add(2445,  -1,   4, 0);
	this->CPacketLengthExMgr::Add(2446,  -1,  28, 0);
	this->CPacketLengthExMgr::Add(2443,   2,   2, 0);
	this->CPacketLengthExMgr::Add(2444,   4,   4, 0);
	this->CPacketLengthExMgr::Add(2447,  -1,   8, 0);
	this->CPacketLengthExMgr::Add(2448,  31,  31, 1);
	this->CPacketLengthExMgr::Add(2449,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2450,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2451,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2452,  -1,   4, 1);
	this->CPacketLengthExMgr::Add(2453,  -1,  28, 1);
	this->CPacketLengthExMgr::Add(2454,  -1,  28, 1);
	this->CPacketLengthExMgr::Add(2455,  -1,  45, 1);
	this->CPacketLengthExMgr::Add(2456,   8,   8, 1);
	this->CPacketLengthExMgr::Add(2457,  11,  11, 1);
	this->CPacketLengthExMgr::Add(2458,   9,   9, 1);
	this->CPacketLengthExMgr::Add(2459,   8,   8, 1);
	this->CPacketLengthExMgr::Add(2460,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2461,  -1,   4, 0);
	this->CPacketLengthExMgr::Add(2462,  12,  12, 0);
	this->CPacketLengthExMgr::Add(2463,  -1,  22, 1);
	this->CPacketLengthExMgr::Add(2464,   6,   6, 0);
	this->CPacketLengthExMgr::Add(2465,   2,   2, 0);
}


void CPacketLengthExMgr::InitPacketLenWithClientSecure()
{
	this->CPacketLengthExMgr::Add(1079,  7,  7, 0);
	this->CPacketLengthExMgr::Add(1080, 10, 10, 0);
	this->CPacketLengthExMgr::Add( 863,  5,  5, 0);
	this->CPacketLengthExMgr::Add( 864,  6,  6, 0);
	this->CPacketLengthExMgr::Add( 865,  5,  5, 0);
	this->CPacketLengthExMgr::Add( 866,  6,  6, 0);
	this->CPacketLengthExMgr::Add( 867,  6,  6, 0);
	this->CPacketLengthExMgr::Add( 868,  8,  8, 0);
	this->CPacketLengthExMgr::Add( 869,  8,  8, 0);
	this->CPacketLengthExMgr::Add( 870, 10, 10, 0);
	this->CPacketLengthExMgr::Add( 871, 90, 90, 0);
	this->CPacketLengthExMgr::Add( 872,  6,  6, 0);
	this->CPacketLengthExMgr::Add( 873,  6,  6, 0);
	this->CPacketLengthExMgr::Add(2108, 12, 12, 0);
	this->CPacketLengthExMgr::Add(2104,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2101, -1, 15, 0);
	this->CPacketLengthExMgr::Add(2073, -1, 12, 0);
	this->CPacketLengthExMgr::Add(2071,  6,  6, 0);
	this->CPacketLengthExMgr::Add(2069,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2065, -1, 89, 0);
	this->CPacketLengthExMgr::Add(2050, 18, 18, 0);
	this->CPacketLengthExMgr::Add(2028,  8,  8, 0);
	this->CPacketLengthExMgr::Add(2020, -1, 12, 0);
	this->CPacketLengthExMgr::Add(1078, 19, 19, 0);
	this->CPacketLengthExMgr::Add( 708, 26, 26, 0);
	this->CPacketLengthExMgr::Add( 641,  4,  4, 0);
	this->CPacketLengthExMgr::Add( 514, 26, 26, 0);
	this->CPacketLengthExMgr::Add( 557,  5,  5, 0);
	this->CPacketLengthExMgr::Add( 571, 36, 36, 0);
	this->CPacketLengthExMgr::Add(2138,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2139,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2140,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2141,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2142,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2143,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2144,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2145,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2146,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2147,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2148,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2149,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2150,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2151,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2152,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2153,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2154,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2155,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2156,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2157,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2158,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2159,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2160,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2161,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2162,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2163,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2164,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2165,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2166,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2167,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2168,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2169,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2170,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2171,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2172,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2173,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2174,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2175,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2176,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2177,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2178,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2179,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2327,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2328,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2329,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2330,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2331,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2332,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2333,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2334,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2335,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2336,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2337,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2338,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2339,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2340,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2341,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2342,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2343,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2344,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2345,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2346,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2347,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2348,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2349,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2350,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2351,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2352,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2353,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2354,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2355,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2356,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2357,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2358,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2359,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2360,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2361,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2362,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2363,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2364,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2365,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2366,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2367,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2368,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2180,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2181,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2182,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2183,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2184,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2185,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2186,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2187,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2188,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2189,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2190,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2191,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2192,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2193,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2194,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2195,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2196,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2197,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2198,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2199,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2200,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2201,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2202,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2203,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2204,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2205,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2206,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2207,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2208,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2209,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2210,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2211,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2212,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2213,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2214,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2215,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2216,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2217,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2218,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2219,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2220,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2221,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2369,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2370,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2371,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2372,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2373,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2374,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2375,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2376,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2377,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2378,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2379,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2380,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2381,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2382,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2383,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2384,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2385,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2386,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2387,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2388,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2389,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2390,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2391,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2392,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2393,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2394,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2395,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2396,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2397,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2398,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2399,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2400,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2401,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2402,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2403,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2404,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2405,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2406,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2407,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2408,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2409,  2,  2, 0);
	this->CPacketLengthExMgr::Add(2410,  2,  2, 0);
}
