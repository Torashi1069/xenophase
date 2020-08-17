#pragma once
#pragma pack(push,1)
///////////////////////////////////////


enum
{
	HEADER_SERVER_ENTRY                               = 10500,
	HEADER_HA_LOGON                                   = 10501,
	HEADER_AH_LOGON_EXIST                             = 10502,
	HEADER_AH_LOGON_NOTEXIST                          = 10503,
	HEADER_ZH_LOGON                                   = 10504,
	HEADER_HZ_LOGON_EXIST                             = 10505,
	HEADER_HZ_LOGON_NOTEXIST                          = 10506,
	HEADER_ZH_CHAR_EXIT                               = 10507,
	HEADER_HA_CHAR_EXIT                               = 10508,
	HEADER_AH_DISCONNECT                              = 10509,
	HEADER_HZ_DISCONNECT                              = 10510,
	HEADER_HZ_ACK_RESTART                             = 10511,
	HEADER_ZH_RESTART                                 = 10512,
	HEADER_CONNECTION_CLOSED                          = 10513,
	HEADER_SAVE_USING_TIME                            = 10514,
	HEADER_ZH_SAVECHARINFO                            = 10515,
	HEADER_ZH_MAPMOVE                                 = 10516,
	HEADER_HZ_ACK_MAPMOVE                             = 10517,
	HEADER_ZI_LOGON                                   = 10518,
	HEADER_ZI_EXIT                                    = 10519,
	HEADER_ZI_WHISPER                                 = 10520,
	HEADER_IZ_WHISPER                                 = 10521,
	HEADER_IZ_ACK_WHISPER                             = 10522,
	HEADER_ZI_ACK_WHISPER                             = 10523,
	HEADER_ZI_REQ_USER_COUNT                          = 10524,
	HEADER_IZ_USER_COUNT                              = 10525,
	HEADER_ZI_BROADCAST                               = 10526,
	HEADER_IZ_BROADCAST                               = 10527,
	HEADER_ZI_MAKE_GROUP                              = 10528,
	HEADER_IZ_ACK_MAKE_GROUP                          = 10529,
	HEADER_IZ_GROUP_LIST                              = 10530,
	HEADER_ZI_REQ_JOIN_GROUP                          = 10531,
	HEADER_IZ_ACK_REQ_JOIN_GROUP                      = 10532,
	HEADER_IZ_REQ_JOIN_GROUP                          = 10533,
	HEADER_ZI_JOIN_GROUP                              = 10534,
	HEADER_ZI_REQ_LEAVE_GROUP                         = 10535,
	HEADER_ZI_REQ_EXPEL_GROUP_MEMBER                  = 10536,
	HEADER_IZ_ADD_MEMBER_TO_GROUP                     = 10537,
	HEADER_IZ_DELETE_MEMBER_FROM_GROUP                = 10538,
	HEADER_ZI_MAPMOVE                                 = 10539,
	HEADER_ZI_GRID_UPDATE                             = 10540,
	HEADER_ZI_CHAT_PARTY                              = 10541,
	HEADER_IZ_CHAT_PARTY                              = 10542,
	HEADER_IZ_DISCONNECT_ALL                          = 10543,
	HEADER_ZI_DISCONNECT_ALL                          = 10544,
	HEADER_ZI_CHANGE_EXPOPTION                        = 10545,
	HEADER_HA_PCINFOUPDATE                            = 10546,
	HEADER_IZ_REQ_SERVERSTATE                         = 10547,
	HEADER_IZ_SHOTDOWN                                = 10548,
	HEADER_ZI_SERVERSTATE                             = 10549,
	HEADER_ZI_REQ_MYGUILD_BASIC_INFO                  = 10550,
	HEADER_ZI_REQ_MAKE_GUILD                          = 10551,
	HEADER_IZ_MYGUILD_BASICINFO                       = 10552,
	HEADER_ZI_REQ_GUILD_MENUINTERFACE                 = 10553,
	HEADER_IZ_ACK_MYGUILD_MEMBER_INFO                 = 10554,
	HEADER_IZ_ACK_MYGUILD_POSITION                    = 10555,
	HEADER_IZ_ACK_MYGUILD_BANISH                      = 10556,
	HEADER_IZ_ACK_MYGUILD_LIST                        = 10557,
	HEADER_ZI_REGISTER_GUILD_EMBLEM_IMG               = 10558,
	HEADER_IZ_GET_GUILD_EMBLEM_IMG                    = 10559,
	HEADER_ZI_MEMBERMGR_INFO                          = 10560,
	HEADER_IZ_MEMBERMGR_INFO                          = 10561,
	HEADER_ZI_REQ_CHANGE_MEMBERPOS                    = 10562,
	HEADER_IZ_ACK_CHANGE_MEMBERPOS                    = 10563,
	HEADER_ZI_REQ_OPEN_MEMBER_INFO                    = 10564,
	HEADER_IZ_ACK_OPEN_MEMBER_INFO                    = 10565,
	HEADER_ZI_REQ_LEAVE_GUILD                         = 10566,
	HEADER_IZ_ACK_LEAVE_GUILD                         = 10567,
	HEADER_ZI_REQ_BAN_GUILD                           = 10568,
	HEADER_IZ_ACK_BAN_GUILD                           = 10569,
	HEADER_ZI_REQ_DISORGANIZE_GUILD                   = 10570,
	HEADER_IZ_REQ_DISORGANIZE_GUILD_RESULT            = 10571,
	HEADER_ZI_REQ_GUILD_POSITION_INFO                 = 10572,
	HEADER_IZ_ACK_GUILD_POSITION_INFO                 = 10573,
	HEADER_IZ_SKILL_INFO                              = 10574,
	HEADER_IZ_BAN_LIST                                = 10575,
	HEADER_IZ_OTHER_GUILD_LIST                        = 10576,
	HEADER_ZI_REQ_JOIN_GUILD                          = 10577,
	HEADER_IZ_REQ_JOIN_GUILD                          = 10578,
	HEADER_ZI_JOIN_GUILD                              = 10579,
	HEADER_IZ_ACK_REQ_JOIN_GUILD                      = 10580,
	HEADER_IZ_GUILD_LIST_TOD                          = 10581,
	HEADER_IZ_GUILDINFO_TOD                           = 10582,
	HEADER_IZ_GUILD_MEMBERINFO_TOD                    = 10583,
	HEADER_IZ_GUILD_ALLYINFO_TOD                      = 10584,
	HEADER_IZ_GUILD_BANISHINFO_TOD                    = 10585,
	HEADER_IZ_GUILD_MPOSITION_TOD                     = 10586,
	HEADER_IZ_GUILD_NOTICE_TOD                        = 10587,
	HEADER_IZ_RESULT_MAKE_GUILD                       = 10588,
	HEADER_IZ_UPDATE_CHARGDID                         = 10589,
	HEADER_IZ_UPDATE_CHARSTAT                         = 10590,
	HEADER_ZI_GUILD_NOTICE                            = 10591,
	HEADER_IZ_GUILD_NOTICE                            = 10592,
	HEADER_ZI_ALLY_GUILD                              = 10593,
	HEADER_IZ_ACK_REQ_ALLY_GUILD                      = 10594,
	HEADER_IZ_ADD_ALLY_GUILD                          = 10595,
	HEADER_ZI_REQ_HOSTILE_GUILD                       = 10596,
	HEADER_IZ_ACK_REQ_HOSTILE_GUILD                   = 10597,
	HEADER_IZ_ADD_HOSTILE_GUILD                       = 10598,
	HEADER_IZ_GUILD_MEMBER_ADD                        = 10599,
	HEADER_ZI_REQ_DELETE_RELATED_GUILD                = 10600,
	HEADER_IZ_DELETE_RELATED_GUILD                    = 10601,
	HEADER_ZI_ACTOR_INIT                              = 10602,
	HEADER_ZI_GUILD_CHAT                              = 10603,
	HEADER_IZ_GUILD_CHAT                              = 10604,
	HEADER_ZI_ADD_EXP                                 = 10605,
	HEADER_IZ_ADD_EXP                                 = 10606,
	HEADER_IZ_GUILD_LEVEL_UP                          = 10607,
	HEADER_IZ_GUILD_MEMBERINFO_FRAG                   = 10608,
	HEADER_IZ_GET_GUILD_EMBLEM_IMG_FRAG               = 10609,
	HEADER_ZI_REGISTER_GUILD_EMBLEM_IMG_FRAG          = 10610,
	HEADER_AH_DISCONNECT_RIGHTNOW                     = 10611,
	HEADER_HZ_DISCONNECT_RIGHTNOW                     = 10612,
	HEADER_ZI_CHAR_LEVEL_UP                           = 10613,
	HEADER_ZI_GUILD_ZENY                              = 10614,
	HEADER_IZ_GUILD_ZENY                              = 10615,
	HEADER_ZI_GUILD_ZENY_UPDATE_ALL                   = 10616,
	HEADER_IZ_GUILD_ZENY_UPDATE_ALL                   = 10617,
	HEADER_ZI_GUILD_PRELOAD                           = 10618,
	HEADER_ZI_GUILD_CHANGEOWNER_AGIT                  = 10619,
	HEADER_HA_REQ_PACKETINFO                          = 10620,
	HEADER_AH_ACK_PACKETINFO                          = 10621,
	HEADER_ZH_REQ_REMAINTIME                          = 10622,
	HEADER_HA_REQ_REMAINTIME                          = 10623,
	HEADER_AH_RES_REMAINTIME                          = 10624,
	HEADER_HZ_RES_REMAINTIME                          = 10625,
	HEADER_AH_INFO_REMAINTIME                         = 10626,
	HEADER_HZ_INFO_REMAINTIME                         = 10627,
	HEADER_IZ_GUILD_NOTIFYSKILLDATA                   = 10628,
	HEADER_ZI_GDSKILL_UPDATE                          = 10629,
	HEADER_ZE_REQ_CERTIFICATE                         = 10630,
	HEADER_EZ_PERMIT_CERTIFICATE                      = 10631,
	HEADER_ZI_MOVE                                    = 10632,
	HEADER_IZ_MOVE                                    = 10633,
	HEADER_ZI_GUILD_CHANGEMAXUSER                     = 10634,
	HEADER_IZ_GUILD_CHANGEMAXUSER                     = 10635,
	HEADER_IZ_FREE_GUILD                              = 10636,
	HEADER_IZ_GUILD_CHANGEOWNER_AGIT                  = 10637,
	HEADER_ZI_MAKE_GROUP2                             = 10638,
	HEADER_IZ_ADD_MEMBER_TO_GROUP2                    = 10639,
	HEADER_ZI_MOVE_GID                                = 10640,
	HEADER_IZ_GUILD_MAP_CHANGE                        = 10641,
	HEADER_ZI_VERSION                                 = 10642,
	HEADER_ZI_CHANGE_EXPOPTION2                       = 10643,
	HEADER_HA_LOGON_SESSION                           = 10644,
	HEADER_AH_LOGON_EXIST_SESSION                     = 10645,
	HEADER_AH_LOGON_NOTEXIST_SESSION                  = 10646,
	HEADER_ZI_DIVORCE                                 = 10647,
	HEADER_IZ_DIVORCE                                 = 10648,
	HEADER_IZ_FRIENDS_LIST                            = 10649,
	HEADER_IZ_FRIENDS_STATE                           = 10650,
	HEADER_ZI_ACK_REQ_ADD_FRIENDS                     = 10651,
	HEADER_IZ_ADD_FRIENDS                             = 10652,
	HEADER_ZI_DELETE_FRIENDS                          = 10653,
	HEADER_IZ_DELETE_FRIENDS                          = 10654,
	HEADER_ZI_MOVE_SERVER                             = 10655,
	HEADER_SVR_PING                                   = 10656,
	HEADER_IZ_NOTIFY_MAKERRANK                        = 10657,
	HEADER_ZI_UPDATE_MAKERRANK                        = 10658,
	HEADER_ZH_MOVE_PVPWORLD                           = 529,
	HEADER_AH_BILLING_ACK                             = 10659,
	HEADER_MI_ENTER                                   = 11000,
	HEADER_MI_REQ_SERVERSTATE                         = 11001,
	HEADER_MI_MSG                                     = 11002,
	HEADER_MI_SHOTDOWN                                = 11003,
	HEADER_IM_CONTROLFAIL                             = 11004,
	HEADER_IM_SERVERLIST                              = 11005,
	HEADER_IM_SERVERSTATE                             = 11006,
	HEADER_IM_ACKMSG                                  = 11007,
	HEADER_IZ_DISCONNECT_CHARACTER                    = 11008,
	HEADER_MI_GET_GUILD_INFO                          = 11009,
	HEADER_IM_REQ_GUILD_INFO                          = 11010,
	HEADER_MI_GUILD_INFO_INIT                         = 11011,
	HEADER_IM_RESULT_GUILD_INFO_INIT                  = 11012,
	HEADER_MI_ALLY_GUILD_INIT                         = 11013,
	HEADER_IM_REQ_ALLY_GUILD_INIT                     = 11014,
};


struct PACKET_SERVER_ENTRY
{// 0x2904 (10500)
	/* this+0 */ short PacketType;
	/* this+2 */ int SID;
};


struct PACKET_HA_LOGON
{// 0x2905 (10501)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ DWORD AID;
	/* this+ 6 */ int AuthCode;
	/* this+10 */ unsigned char Sex;
	/* this+11 */ DWORD userCount;
	/* this+15 */ DWORD SID;
	/* this+19 */ DWORD IP;
};


struct PACKET_AH_LOGON_ACK
{// 0x2906 (10502), 0x2907 (10503)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ DWORD AID;
	/* this+ 6 */ char ID[24];
	/* this+30 */ char PERSONALNUMBER[24];
	/* this+54 */ char emailAddress[40];
	/* this+94 */ DWORD TotalUsingTime;
};


struct PACKET_HA_CHAR_EXIT
{// 0x290C (10508)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ DWORD TotalUsingTime;
	/* this+ 6 */ DWORD AID;
	/* this+10 */ unsigned char disconnectedType;
};


struct PACKET_AH_DISCONNECT
{// 0x290D (10509), 0x290F (10611)
	/* this+0 */ short PacketType;
	/* this+2 */ DWORD AID;
	/* this+6 */ unsigned char reason; // enum BAN_*
};


struct PACKET_HA_PCINFOUPDATE
{// 0x2932 (10546)
	/* this+0 */ short PacketType;
	/* this+2 */ DWORD AID;
};


struct PACKET_HA_LOGON_SESSION
{// 0x2994 (10644)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ DWORD AID;
	/* this+ 6 */ int AuthCode;
	/* this+10 */ unsigned char Sex;
	/* this+11 */ DWORD userCount;
	/* this+15 */ DWORD SID;
	/* this+19 */ DWORD IP;
	/* this+23 */ DWORD dwSessionID;
};


struct PACKET_AH_LOGON_ACK_SESSION
{// 0x2995 (10645), 0x2996 (10646)
	/* this+  0 */ short PacketType;
	/* this+  2 */ DWORD AID;
	/* this+  6 */ char ID[24];
	/* this+ 30 */ char PERSONALNUMBER[24];
	/* this+ 54 */ char emailAddress[50];
	/* this+104 */ DWORD TotalUsingTime;
	/* this+108 */ DWORD dwSessionID;
};


///////////////////////////////////////
#pragma pack(pop)
