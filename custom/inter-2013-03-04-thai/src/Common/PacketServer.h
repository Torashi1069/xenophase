#pragma once
#include "FriendDB.h" // STRUCT_FRIEND
#include "shared/Guild.h"
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
	HEADER_ZI_MAIL_GET_LIST                           = 10659,
	HEADER_IZ_MAIL_REQ_GET_LIST                       = 10660,
	HEADER_ZI_MAIL_OPEN                               = 10661,
	HEADER_IZ_MAIL_REQ_OPEN                           = 10662,
	HEADER_ZI_MAIL_DELETE                             = 10663,
	HEADER_IZ_ACK_MAIL_DELETE                         = 10664,
	HEADER_ZI_MAIL_GET_ITEM                           = 10665,
	HEADER_IZ_MAIL_REQ_GET_ITEM                       = 10666,
	HEADER_ZI_MAIL_SEND                               = 10667,
	HEADER_IZ_MAIL_REQ_SEND                           = 10668,
	HEADER_IZ_MAIL_RECEIVE                            = 10669,
	HEADER_ZI_EPISODE_VERSION                         = 10670,
	HEADER_IZ_CHK_PROCESSTIME                         = 10671,
	HEADER_ZI_ACK_CHK_PROCESSTIME                     = 10672,
	HEADER_IZ_DISCONNECT_CHARACTER                    = 10673,
	HEADER_IZ_ACK_LOGON                               = 10674,
	HEADER_ZI_REQ_MAIL_RETURN                         = 10675,
	HEADER_IZ_ACK_MAIL_RETURN                         = 10676,
	HEADER_HZ_NOTIFY_PCBANG                           = 10677,
	HEADER_AH_LOGON_EXIST_PCBANG                      = 10678,
	HEADER_HA_CHAR_SVR_INFO                           = 10679,
	HEADER_HA_REQ_PLAYING_LIMITINFO                   = 10680,
	HEADER_AH_ACK_PLAYING_LIMITINFO                   = 10681,
	HEADER_AH_LOGON_EXIST_PCBANG_HAN                  = 10682,
	HEADER_HZ_PING                                    = 10683,
	HEADER_ZI_MEMORIALDUNGEON_SUBSCRIPTION            = 10684,
	NOT_USED_HEADER_IZ_MEMORIALDUNGEON_CREATE_RESULT  = 10685,
	HEADER_IZ_INSTANTMAP_CREATE_REQ                   = 10686,
	HEADER_ZI_INSTANTMAP_CREATE_RES                   = 10687,
	HEADER_HZ_NOTIFY_PCBANG_PLAYING_TIME              = 10688,
	HEADER_ZI_SERVERSTATE_HAN_GAME                    = 10689,
	HEADER_AH_NOTIFY_PCBANG_PLAYING_TIME              = 10690,
	HEADER_IZ_INSTANTMAP_PLAYER_ENTER                 = 10691,
	HEADER_ZI_INSTANTMAP_ERROR                        = 10692,
	HEADER_IZ_INSTNATMAP_DESTROY                      = 10693,
	HEADER_ZI_PING                                    = 10694,
	HEADER_ZI_INSTANTMAP_ALLOW                        = 10695,
	HEADER_XX_CONNECT                                 = 10696,
	HEADER_XX_DISCONNECT                              = 10697,
	HEADER_IZ_MEMORIALDUNGEON_MSG                     = 10698,
	NOT_USED_HEADER_ZI_MEMORIALDUNGEON_NOTIFY_CONFIRM = 10699,
	HEADER_ZI_PARTY_JOIN_REQ                          = 10700,
	HEADER_IZ_PARTY_JOIN_REQ_ACK                      = 10701,
	HEADER_IZ_PARTY_JOIN_REQ                          = 10702,
	HEADER_ZI_PARTY_JOIN_REQ_ACK                      = 10703,
	HEADER_AH_LOGON_ACK_EXTEND_BILLING_INFO           = 10704,
	HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO       = 10705,
	HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY     = 10706,
	HEADER_IZ_MEMORIALDUNGEON_INFO                    = 10707,
	HEADER_IZ_MEMORIALDUNGEON_NOTIFY                  = 10708,
	HEADER_ZI_MEMORIALDUNGEON_COMMAND                 = 10709,
	HEADER_IZ_MEMORIALDUNGEON_SYNC                    = 10710,
	HEADER_ZI_MEMORIALDUNGEON_VISA                    = 10711,
	HEADER_IZ_MEMORIALDUNGEON_VISA                    = 10712,
	HEADER_IZ_MEMORIALDUNGEON_COMMAND                 = 10713,
	HEADER_ZH_PLAYER_ALIVE                            = 10714,
	HEADER_IZ_LEAVE_GROUP                             = 10715,
	HEADER_ZI_MEMORIALDUNGEON_OPENSTATE               = 10716,
	HEADER_IZ_MEMORIALDUNGEON_OPENSTATE               = 10717,
	HEADER_ZI_ENTRANCESTATION_REGIST                  = 10718,
	HEADER_IZ_WAITINGROOM_SUBSCRIPTION_RESULT         = 10719,
	HEADER_ZI_WAITINGROOM_MY_SUBSCRIPTION_INFO        = 10720,
	HEADER_IZ_WAITINGROOM_MY_SUBSCRIPTION_INFO        = 10721,
	HEADER_IZ_WAITINGROOM_PARTYPLAY_JOIN_NOTI         = 10722,
	HEADER_ZI_WAITINGROOM_PARTYPLAY_JOIN_RESULT       = 10723,
	HEADER_IZ_WAITINGROOM_START                       = 10724,
	HEADER_ZI_WAITINGROOM_PLAYER_STATE                = 10725,
	HEADER_AH_DISPATCH_PREMIUM_INFO                   = 10726,
	HEADER_HZ_CHAR_NAME_CHANGED                       = 10727,
	HEADER_ZI_GROUPINFO_CHANGE_V2                     = 10728,
	HEADER_IZ_REQ_GROUPINFO_CHANGE_V2                 = 10729,
	HEADER_ZI_CHANGE_GROUP_MASTER                     = 10730,
	HEADER_ZH_CASTLE_MAP_MOVE                         = 10731,
	HEADER_AH_BILLING_ACK                             = 10732,
	HEADER_HA_LOGON2                                  = 10733,
	HEADER_ZI_SEEK_PARTY                              = 10734,
	HEADER_IZ_SEEK_PARTY                              = 10735,
	HEADER_ZI_SEEK_PARTY_MEMBER                       = 10736,
	HEADER_IZ_SEEK_PARTY_MEMBER                       = 10737,
	HEADER_ZI_GET_MY_BATTLEFILED_INFO                 = 10738,
	HEADER_IZ_BATTLEFILED_SETTING                     = 10739,
	HEADER_IZ_BATTLEFIELD_NOTI                        = 10740,
	HEADER_ZI_FINAL_BATTLE_PLAY                       = 10741,
	HEADER_DESTROY_PACKET_1                           = 10742,
	HEADER_DESTROY_PACKET_2                           = 10743,
	HEADER_DESTROY_PACKET_3                           = 10744,
	HEADER_DESTROY_PACKET_4                           = 10745,
	HEADER_DESTROY_PACKET_5                           = 10746,
	HEADER_DESTROY_PACKET_6                           = 10747,
	HEADER_DESTROY_PACKET_7                           = 10748,
	HEADER_DESTROY_PACKET_8                           = 10749,
	HEADER_DESTROY_PACKET_9                           = 10750,
	HEADER_DESTROY_PACKET_10                          = 10751,
	HEADER_ZI_INTERSERVER_ORDER                       = 10752,
	HEADER_AH_UPDATE_PCBANG_CNT                       = 10753,
	HEADER_HA_CHECKBOT_REQ                            = 10754,
	HEADER_AH_CHECKBOT_ACK                            = 10755,
	HEADER_HA_CHECKBOT_UPDATE                         = 10756,
	HEADER_ZI_BATTLE_FIELD_LIST                       = 10757,
	HEADER_IZ_BATTLE_FIELD_LIST                       = 10758,
	HEADER_ZI_JOIN_BATTLE_FIELD                       = 10759,
	HEADER_IZ_JOIN_BATTLE_FIELD                       = 10760,
	HEADER_ZI_CANCEL_BATTLE_FIELD                     = 10761,
	HEADER_IZ_CANCEL_BATTLE_FIELD                     = 10762,
	HEADER_ZI_REQ_BATTLE_STATE_MONITOR                = 10763,
	HEADER_IZ_ACK_BATTLE_STATE_MONITOR                = 10764,
	HEADER_IZ_BATTLE_NOTI_START_STEP                  = 10765,
	HEADER_IZ_BATTLE_JOIN_NOTI_DEFER                  = 10766,
	HEADER_IZ_BATTLE_JOIN_DISABLE_STATE               = 10767,
	HEADER_IZ_BATTLE_USER_STATE_CHECK                 = 10768,
	HEADER_ZI_BATTLE_USER_STATE_CHECK                 = 10769,
	HEADER_IZ_MOVE_FROM_BATTLEFIELD                   = 10770,
	HEADER_ZI_BEFORE_BATTLE_MY_POSITION               = 10771,
	HEADER_IZ_BEFORE_BATTLE_MY_POSITION               = 10772,
	HEADER_IZ_CHANGE_GROUP_MASTER                     = 10773,
	HEADER_ZI_BROADCASTING_SPECIAL_ITEM_OBTAIN        = 10774,
	HEADER_IZ_BROADCASTING_SPECIAL_ITEM_OBTAIN        = 10775,
	HEADER_IZ_DEFINE_CHECK                            = 10776,
	HEADER_ZI_SERVERSTATE_CHANNELING                  = 10777,
	HEADER_ZI_PARTY_BOOKING_NOTIFY_INSERT             = 10778,
	HEADER_IZ_PARTY_BOOKING_NOTIFY_INSERT             = 10779,
	HEADER_ZI_PARTY_BOOKING_NOTIFY_DELETE             = 10780,
	HEADER_IZ_PARTY_BOOKING_NOTIFY_DELETE             = 10781,
	HEADER_ZI_PARTY_BOOKING_NOTIFY_UPDATE             = 10782,
	HEADER_IZ_PARTY_BOOKING_NOTIFY_UPDATE             = 10783,
	HEADER_ZI_REQ_MAKE_GUILD_SSO                      = 10784,
	HEADER_ZI_REQ_BAN_GUILD_SSO                       = 10785,
	HEADER_IZ_ACK_BAN_GUILD_SSO                       = 10786,
	HEADER_ZI_JOIN_GUILD_SSO                          = 10787,
	HEADER_HZ_ZSVR_INFO                               = 10788,
	HEADER_ZH_ZSVR_INFO                               = 10789,
	HEADER_IH_PING                                    = 10790,
	HEADER_HI_PING                                    = 10791,
	HEADER_ZI_WHISPER_2                               = 10792,
	HEADER_IZ_WHISPER_2                               = 10793,
	HEADER_ZI_MOVE_2                                  = 10794,
	HEADER_XX_REQ_PACKAGEITEMLIST                     = 10795,
	HEADER_IZ_ACK_PACKAGEITEMLIST                     = 10796,
	HEADER_ZI_REQ_UNPACK_PACKAGE_ITEM                 = 10797,
	HEADER_IZ_ACK_UNPACK_PACKAGE_ITEM                 = 10798,
	HEADER_ZI_ROLLBACK_PACKAGE_ITEM                   = 10799,
	HEADER_ZI_GPK_DYNCODE_RELOAD                      = 10800,
	HEADER_IZ_GPK_DYNCODE_RELOAD                      = 10801,
	HEADER_HZ_USER_COUNT_REQ                          = 10802,
	HEADER_ZH_USER_COUNT_ACK                          = 10803,
	HEADER_ZH_CHAR_EXIT2                              = 10804,
	HEADER_ZH_RESTART2                                = 10805,
	HEADER_HA_REQ_AID_CHECK                           = 10806,
	HEADER_AH_ACK_AID_CHECK                           = 10807,
	HEADER_IZ_IRMAIL_NOTIFY                           = 10808,
	HEADER_HZ_PERSONAL_INFORMATION                    = 10809,
	HEADER_AH_LOGON_UNION_SECONDPW                    = 10810,
	HEADER_ZI_AUTH_REQ                                = 10811,
	HEADER_IZ_AUTH_ACK                                = 10812,
	HEADER_ZH_AUTH_REQ                                = 10813,
	HEADER_HZ_AUTH_ACK                                = 10814,
	HEADER_IZ_REQ_EDIT_EXP                            = 10815,
	HEADER_HZ_PERSONAL_INFORMATION_2ND                = 10816,
	HEADER_HA_IPBONUS_LIMIT                           = 10817,
	HEADER_ZI_INFO_ENTRY_QUEUE_APPLY                  = 10818,
	HEADER_IZ_INFO_ENTRY_QUEUE_APPLY                  = 10819,
	HEADER_ZI_REQ_ENTRY_QUEUE_APPLY                   = 10820,
	HEADER_IZ_NOTIFY_ENTRY_QUEUE_APPLY                = 10821,
	HEADER_ZI_RESULT_ENTRY_QUEUE_APPLY                = 10822,
	HEADER_IZ_RESULT_ENTRY_QUEUE_APPLY                = 10823,
	HEADER_ZI_INFO_ENTRY_QUEUE_CANCEL                 = 10824,
	HEADER_IZ_INFO_ENTRY_QUEUE_CANCEL                 = 10825,
	HEADER_ZI_REQ_ENTRY_QUEUE_CANCEL                  = 10826,
	HEADER_IZ_NOTIFY_ENTRY_QUEUE_CANCEL               = 10827,
	HEADER_ZI_RESULT_ENTRY_QUEUE_CANCEL               = 10828,
	HEADER_IZ_RESULT_ENTRY_QUEUE_CANCEL               = 10829,
	HEADER_ZI_ENTRY_QUEUE_ADMISSION                   = 10830,
	HEADER_IZ_ENTRY_QUEUE_ADMISSION                   = 10831,
	HEADER_ZI_ENTRY_QUEUE_ADMISSION_ACCEPT            = 10832,
	HEADER_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_ACCEPT     = 10833,
	HEADER_ZI_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT     = 10834,
	HEADER_IZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT     = 10835,
	HEADER_ZI_ENTRY_QUEUE_ADMISSION_REFUSE            = 10836,
	HEADER_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_REFUSE     = 10837,
	HEADER_ZI_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE     = 10838,
	HEADER_IZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE     = 10839,
	HEADER_ZI_LOBBY_ADMISSION                         = 10840,
	HEADER_IZ_LOBBY_ADMISSION                         = 10841,
	HEADER_ZI_LOBBY_ADMISSION_ACCEPT                  = 10842,
	HEADER_IZ_NOTIFY_LOBBY_ADMISSION_ACCEPT           = 10843,
	HEADER_ZI_RESULT_LOBBY_ADMISSION_ACCEPT           = 10844,
	HEADER_IZ_RESULT_LOBBY_ADMISSION_ACCEPT           = 10845,
	HEADER_ZI_LOBBY_ADMISSION_REFUSE                  = 10846,
	HEADER_IZ_NOTIFY_LOBBY_ADMISSION_REFUSE           = 10847,
	HEADER_ZI_RESULT_LOBBY_ADMISSION_REFUSE           = 10848,
	HEADER_IZ_RESULT_LOBBY_ADMISSION_REFUSE           = 10849,
	HEADER_IZ_ENTRY_QUEUE_LOGOUT                      = 10850,
	HEADER_ZI_ENTRY_QUEUE_MOVE_ROOM                   = 10851,
	HEADER_IZ_ENTRY_QUEUE_MOVE_ROOM                   = 10852,
	HEADER_ZI_LOBBY_MOVE_ROOM                         = 10853,
	HEADER_IZ_LOBBY_MOVE_ROOM                         = 10854,
	HEADER_ZI_ENTRY_QUEUE_NAME                        = 10855,
	HEADER_ZI_PARTY_RECRUIT_NOTIFY_INSERT             = 10856,
	HEADER_IZ_PARTY_RECRUIT_NOTIFY_INSERT             = 10857,
	HEADER_ZI_PARTY_RECRUIT_NOTIFY_DELETE             = 10858,
	HEADER_IZ_PARTY_RECRUIT_NOTIFY_DELETE             = 10859,
	HEADER_ZI_PARTY_RECRUIT_NOTIFY_UPDATE             = 10860,
	HEADER_IZ_PARTY_RECRUIT_NOTIFY_UPDATE             = 10861,
	HEADER_ZI_PARTY_RECRUIT_VOLUNTEER_INFO            = 10862,
	HEADER_IZ_PARTY_RECRUIT_VOLUNTEER_INFO            = 10863,
	HEADER_ZI_PARTY_RECRUIT_REQ_RECALL                = 10864,
	HEADER_IZ_PARTY_RECRUIT_REQ_RECALL                = 10865,
	HEADER_ZI_PARTY_RECRUIT_FAILED_RECALL             = 10866,
	HEADER_IZ_PARTY_RECRUIT_FAILED_RECALL             = 10867,
	HEADER_ZI_PARTY_RECRUIT_REFUSE_VOLUNTEER          = 10868,
	HEADER_IZ_PARTY_RECRUIT_REFUSE_VOLUNTEER          = 10869,
	HEADER_AH_JPN_LOGON_ACK                           = 10870,
	HEADER_HZ_JPN_PREMIUM_CAMPAIGN                    = 10871,
	HEADER_ZI_ENTRY_QUEUE_DELETE_GID                  = 10872,
	HEADER_ZI_MEMORIALDUNGEON_SUBSCRIPTION2           = 10873,
	HEADER_IZ_MEMORIALDUNGEON_SYNC2                   = 10874,
	HEADER_IZ_MEMORIALDUNGEON_MSG2                    = 10875,
	HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2      = 10876,
	HEADER_IZ_MEMORIALDUNGEON_INFO2                   = 10877,
	HEADER_ZI_PARTY_RECRUIT_CANCEL_VOLUNTEER          = 10878,
	HEADER_IZ_PARTY_RECRUIT_CANCEL_VOLUNTEER          = 10878,
	HEADER_ZH_PING                                    = 10879,
	HEADER_ZI_ENTRY_QUEUE_RANKING                     = 10880,
	HEADER_IZ_ENTRY_QUEUE_RANKING                     = 10881,
	HEADER_ZI_NOTIFY_ENTRY_QUEUE_RANKING              = 10882,
	HEADER_IZ_NOTIFY_ENTRY_QUEUE_RANKING              = 10883,
	HEADER_ZH_LOGON2RD                                = 10884,
	HEADER_ZH_START2RD                                = 10885,
	HEADER_ZI_JOB_CHANGE                              = 10886,
	HEADER_HZ_PREMIUM_CAMPAIGN_INFO                   = 10887,
	HEADER_ZI_LOBBY_ADMISSION_V2                      = 10888,
	HEADER_IZ_LOBBY_ADMISSION_V2                      = 10889,
	HEADER_ZI_REQ_JOIN_GUILD2                         = 10890,
	HEADER_IZ_REQ_JOIN_GUILD2                         = 10891,
	HEADER_ZI_LIST_JOIN_GUILD_INSERT_GID              = 10892,
	HEADER_ZI_LIST_JOIN_GUILD_CHECK_GID               = 10893,
	HEADER_ZI_PING_LIVE                               = 10894,
	HEADER_IZ_PING_LIVE                               = 10895,
	HEADER_ZI_STATEINFO                               = 10896,
	HEADER_ZH_PING_LIVE                               = 10897,
	HEADER_HZ_PING_LIVE                               = 10898,
	HEADER_HZ_PERSONAL_INFORMATION_BRZ                = 10899,
	HEADER_ZI_OTHER_ZONE_PC_SEND_MSG                  = 10900,
	HEADER_IZ_OTHER_ZONE_PC_SEND_MSG                  = 10901,
	HEADER_ZI_REQ_PRNPC_WINNER                        = 10902,
	HEADER_IZ_ACK_PRNPC_WINNER                        = 10903,
	HEADER_ZI_SET_PRNPC_WINNER                        = 10904,
	HEADER_IZ_SET_PRNPC_WINNER                        = 10905,
	HEADER_HZ_LOGON_KOR                               = 10906,
	HEADER_AH_LOGON_RUS                               = 10907,
	HEADER_HZ_LOGON_TW                                = 10908,
	HEADER_AH_DISPATCH_PREMIUM_INFO_CHN               = 10909,
	HEADER_HZ_FATIGUE_INFO_CHN                        = 10910,
	HEADER_HZ_LOGON_CHN                               = 10911,
	HEADER_HZ_PERSONAL_INFORMATION_CHN                = 10912,
	HEADER_AH_LOGON_ACK_CHN                           = 10913,
	HEADER_ZI_REQ_JOIN_CLAN                           = 10914,
	HEADER_ZI_REQ_LEAVE_CLAN                          = 10915,
	HEADER_IZ_CLAN_CONNECTINFO                        = 10916,
	HEADER_IZ_CLAN_CONNECTINFO_ALL                    = 10917,
	HEADER_ZI_CLAN_CHAT                               = 10918,
	HEADER_IZ_CLAN_CHAT                               = 10919,
	HEADER_IZ_ACK_JOIN_CLAN                           = 10920,
	HEADER_IZ_ACK_LEAVE_CLAN                          = 10921,
	HEADER_ZI_REQ_USER_CLANINFO                       = 10922,
	HEADER_IZ_ACK_USER_CLANINFO                       = 10923,
	HEADER_ZI_NPC_PROVIDE_EXPINFO                     = 10924,
	HEADER_ZI_MEMORIALDUNGEON_DESTROY                 = 10925,
	HEADER_IZ_INSTANTMAP_ADD3                         = 10928,
	HEADER_IZ_INSTANTMAP_REMOVE3                      = 10929,
	HEADER_IZ_INSTANTMAP_PLAYER_ENTER3                = 10930,
	HEADER_IZ_GET_GUILD_EMBLEM_IMG2                   = 10931,
	HEADER_AH_LOGON_BRZ                               = 10932,
	HEADER_AH_CONNECTED_CHN                           = 10933,
	HEADER_IZ_SET_EFFECT_HIGH_RANKER                  = 10934,
	HEADER_IZ_RESET_EFFECT_HIGH_RANKER                = 10935,
	HEADER_HZ_PERSONAL_INFORMATION_PHL                = 10936,
	HEADER_HZ_PERSONAL_INFORMATION_THAI               = 10937,
	HEADER_HZ_PERSONAL_INFORMATION_TW                 = 10939,
	HEADER_ZI_PRIVATE_DUNGEON_RESERVE                 = 20101,
	HEADER_IZ_PRIVATE_DUNGEON_RESERVE                 = 20102,
	HEADER_IZ_PRIVATE_DUNGEON_CREATE_RESULT           = 20103,
	HEADER_IZ_PRIVATE_DUNGEON_SYNC                    = 20104,
	HEADER_ZI_PRIVATE_DUNGEON_ENTER                   = 20105,
	HEADER_IZ_PRIVATE_DUNGEON_ENTER                   = 20106,
	HEADER_MI_ENTER                                   = 11000,
	HEADER_MI_REQ_SERVERSTATE                         = 11001,
	HEADER_MI_MSG                                     = 11002,
	HEADER_MI_SHOTDOWN                                = 11003,
	HEADER_IM_CONTROLFAIL                             = 11004,
	HEADER_IM_SERVERLIST                              = 11005,
	HEADER_IM_SERVERSTATE                             = 11006,
	HEADER_IM_ACKMSG                                  = 11007,
	HEADER_NOT_USE01                                  = 11008,
	HEADER_MI_GET_GUILD_INFO                          = 11009,
	HEADER_IM_REQ_GUILD_INFO                          = 11010,
	HEADER_MI_GUILD_INFO_INIT                         = 11011,
	HEADER_IM_RESULT_GUILD_INFO_INIT                  = 11012,
	HEADER_MI_ALLY_GUILD_INIT                         = 11013,
	HEADER_IM_REQ_ALLY_GUILD_INIT                     = 11014,
	HEADER_IM_SERVERSTATE_HAN_GAME                    = 11015,
	HEADER_IM_SERVERSTATE_CHANNELING                  = 11016,
	HEADER_MI_REQ_EDIT_EXP                            = 11017,
	HEADER_IM_ACK_EDIT_EXP                            = 11018,
};


struct PACKET_SERVER_ENTRY
{// 10500 (0x2904)
	/* this+0 */ short PacketType;
	/* this+2 */ int SID;
};


struct PACKET_ZI_LOGON
{// 10518 (0x2916)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int sex;
	/* this+14 */ short head;
	/* this+16 */ short headpalette;
	/* this+18 */ short level;
	/* this+20 */ short job;
	/* this+22 */ char accountName[24];
	/* this+46 */ char charName[24];
	/* this+70 */ char mapName[16];
};


struct PACKET_ZI_EXIT
{// 10519 (0x2917)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char charName[24];
};


struct PACKET_ZI_WHISPER
{// 10520 (0x2918)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long senderAID;
	/* this+ 8 */ char sender[24];
	/* this+32 */ char receiver[24];
	/* this+56 */ char senderAccountName[24];
	/* this+80 */ char Text[];
};


struct PACKET_IZ_WHISPER
{// 10521 (0x2919)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long receiverAID;
	/* this+ 8 */ unsigned long senderAID;
	/* this+12 */ char sender[24];
	/* this+36 */ char senderAccountName[24];
	/* this+60 */ char Text[];
};


enum enumWHISPERSENDRESULT
{
	WHISPER_SEND_SUCCEED               = 0,
	WHISPER_SEND_FAILED_PC_ABSENCE     = 1,
	WHISPER_SEND_FAILED_PC_REFUSAL     = 2,
	WHISPER_SEND_FAILED_PC_REFUSAL_ALL = 3,
};


struct PACKET_IZ_ACK_WHISPER
{// 10522 (0x291A)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long senderAID;
	/* this+6 */ unsigned char result; // enumWHISPERSENDRESULT
};


struct PACKET_ZI_ACK_WHISPER
{// 10523 (0x291B)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long senderAID;
	/* this+ 6 */ char sender[24];
	/* this+30 */ unsigned char result; // enumWHISPERSENDRESULT
};


struct PACKET_ZI_REQ_USER_COUNT
{// 10524 (0x291C)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_IZ_USER_COUNT
{// 10525 (0x291D)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ int count;
};


struct PACKET_ZI_BROADCAST
{// 10526
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_IZ_BROADCAST
{// 10527
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLen;
	/* this+4 */ char Text[];
};


struct PACKET_ZI_MAKE_GROUP
{// 10528 (0x2920)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char groupName[24];
};


struct PACKET_IZ_ACK_MAKE_GROUP
{// 10529 (0x2921)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ char groupName[24];
	/* this+34 */ unsigned char result;
};


struct GROUPMEMBER_INFO
{
	/* this+ 0 */ unsigned long AID;
	/* this+ 4 */ char characterName[24];
	/* this+28 */ char mapName[16];
	/* this+44 */ unsigned char role;
	/* this+45 */ unsigned char state;
};


struct PACKET_IZ_GROUP_LIST
{// 10530 (0x2922)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long expOption; // enumGROUPEXPOPTION
	/* this+12 */ char groupName[24];
	/* this+36 */ GROUPMEMBER_INFO Info[];
};


struct PACKET_ZI_REQ_JOIN_GROUP
{// 10531 (0x2923)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long senderAID;
	/* this+ 6 */ unsigned long receiverAID;
	/* this+10 */ unsigned long GRID;
};


struct PACKET_IZ_ACK_REQ_JOIN_GROUP
{// 10532 (0x2924)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ char characterName[24];
	/* this+30 */ unsigned char answer; // PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer
};


struct PACKET_IZ_REQ_JOIN_GROUP
{// 10533 (0x2925)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ char groupName[24];
};


struct PACKET_ZI_JOIN_GROUP
{// 10534 (0x2926)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long senderAID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ int answer;
};


struct PACKET_ZI_REQ_LEAVE_GROUP
{// 10535 (0x2927)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned long GID;
};


struct PACKET_ZI_REQ_EXPEL_GROUP_MEMBER
{// 10536 (0x2928)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ char characterName[24];
};


struct PACKET_IZ_ADD_MEMBER_TO_GROUP
{// 10537 (0x2929)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long receiverAID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long Role;
	/* this+14 */ unsigned char state;
	/* this+15 */ char groupName[24];
	/* this+39 */ char characterName[24];
	/* this+63 */ char mapName[16];
};


struct PACKET_IZ_DELETE_MEMBER_FROM_GROUP
{// 10538 (0x292A)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long receiverAID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ char characterName[24];
	/* this+34 */ unsigned char result;
};


struct PACKET_ZI_MAPMOVE
{// 10539 (0x292B)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char mapName[16];
};


struct PACKET_ZI_GRID_UPDATE
{// 10540 (0x292C)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ unsigned long expOption; // enumGROUPEXPOPTION
};


struct PACKET_ZI_CHAT_PARTY
{// 10541 (0x292D)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long GRID;
	/* this+12 */ char Text[];
};


struct PACKET_IZ_CHAT_PARTY
{// 10542 (0x292E)
	/* this+0 */ public: short PacketType;
	/* this+2 */ public: unsigned short PacketLength;
	/* this+4 */ public: unsigned long receiverAID;
	/* this+8 */ public: unsigned long senderAID;
};


struct PACKET_IZ_DISCONNECT_ALL
{// 10543
	/* this+0 */ short PacketType;
};


struct PACKET_ZI_DISCONNECT_ALL
{// 10544
	/* this+0 */ short PacketType;
};


struct PACKET_ZI_CHANGE_EXPOPTION
{// 10545 (0x2931)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GRID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long expOption; // enumGROUPEXPOPTION
};


struct PACKET_HA_PCINFOUPDATE
{// 10546 (0x2932)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_IZ_REQ_SERVERSTATE
{// 10547
	/* this+0 */ short PacketType;
	/* this+2 */ int packetNumber;
	/* this+6 */ int monitorNum;
};


struct PACKET_ZI_SERVERSTATE
{// 10549 (0x2935)
	/* this+0 */ short PacketType;
	/* this+2 */ int monitorNum;
	/* this+6 */ IM_SERVER_STATE state;
};


struct PACKET_ZI_REQ_MYGUILD_BASIC_INFO
{// 10550 (0x2936)
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE Data[12]; //TODO
};


struct PACKET_ZI_REQ_MAKE_GUILD
{// 10551 (0x2937)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ unsigned long AID;
	/* this+14 */ char GName[24];
	/* this+38 */ char MName[24];
	/* this+62 */ char AccountName[24];
};


struct PACKET_IZ_MYGUILD_BASICINFO
{// 10552 (0x2938)
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE Data[36]; //TODO
};


struct PACKET_ZI_REGISTER_GUILD_EMBLEM_IMG
{// 10558
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ unsigned long GID;
	/* this+16 */ BYTE Data[];
};


struct PACKET_IZ_GET_GUILD_EMBLEM_IMG
{// 10559
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ short emblemVersion;
	/* this+14 */ BYTE Data[];
};


struct PACKET_ZI_REQ_CHANGE_MEMBERPOS
{// 10562
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ unsigned long GID;
	/* this+16 */ MEMBER_POSITION_INFO Info[];
};


struct PACKET_IZ_ACK_CHANGE_MEMBERPOS
{// 10563
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ MEMBER_POSITION_INFO Info[];
};


struct PACKET_ZI_REQ_LEAVE_GUILD
{// 10566
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
	/* this+14 */ char reasonDesc[40];
};


struct PACKET_IZ_ACK_LEAVE_GUILD
{// 10567
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
	/* this+14 */ char charName[24];
	/* this+38 */ char reasonDesc[40];
};


struct PACKET_ZI_REQ_BAN_GUILD
{// 10568
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
	/* this+14 */ unsigned long MyGID;
	/* this+18 */ char AccountName[24];
	/* this+42 */ char reasonDesc[40];
};


struct PACKET_IZ_ACK_BAN_GUILD
{// 10569
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
	/* this+14 */ char charName[24];
	/* this+38 */ char AccountName[24];
	/* this+62 */ char reasonDesc[40];
};


struct PACKET_ZI_REQ_DISORGANIZE_GUILD
{// 10570 (0x294A)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
	/* this+14 */ char key[40];
};


struct PACKET_IZ_REQ_DISORGANIZE_GUILD_RESULT
{// 10571
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
	/* this+14 */ int result;
};


struct PACKET_ZI_REQ_GUILD_POSITION_INFO
{// 10572
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ GUILD_REG_POSITION_INFO Info[];
};


struct PACKET_IZ_ACK_GUILD_POSITION_INFO
{// 10573
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ GUILD_REG_POSITION_INFO Info[];
};


struct PACKET_ZI_REQ_JOIN_GUILD
{// 10577
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long myGID;
	/* this+10 */ unsigned long myAID;
	/* this+14 */ unsigned long GID;
};


struct PACKET_IZ_REQ_JOIN_GUILD
{// 10578
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ char guildName[24];
};


struct PACKET_ZI_JOIN_GUILD
{// 10579
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ char Name[24];
	/* this+30 */ char AccountName[24];
	/* this+54 */ unsigned long AID;
	/* this+58 */ unsigned long GID;
	/* this+62 */ int answer;
};


struct PACKET_IZ_ACK_REQ_JOIN_GUILD
{// 10580
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long ReqAID;
	/* this+10 */ unsigned long GDID;
	/* this+14 */ unsigned char answer;
};


struct PACKET_IZ_GUILDINFO_TOD
{// 10582
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ GUILDINFO Data;
};


struct PACKET_IZ_GUILD_MEMBERINFO_TOD
{// 10583
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ GUILDMINFO Data[];
};


struct PACKET_IZ_GUILD_ALLYINFO_TOD
{// 10584
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ GUILDALLYINFO Data[];
};


struct PACKET_IZ_GUILD_BANISHINFO_TOD
{// 10585
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ GUILDBANISHINFO Data[];
};


struct PACKET_IZ_GUILD_MPOSITION_TOD
{// 10586
	/* this+ 0 */ short PacketType;
	/* this +2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ GUILDMPOSITION Data[];
};


struct PACKET_IZ_RESULT_MAKE_GUILD
{// 10588
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ unsigned char result;
};


struct PACKET_IZ_UPDATE_CHARGDID
{// 10589
	enum
	{
		TYPE_JOIN             = 0,
		TYPE_DISORGANIZE      = 1,
		TYPE_LOGONUSER        = 2,
		TYPE_GUILDMAKE        = 3,
		TYPE_CHANGEZONESERVER = 4,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char Type;
	/* this+ 3 */ unsigned long GDID;
	/* this+ 7 */ int emblemVer;
	/* this+11 */ int InterSID;
	/* this+15 */ unsigned long GID;
	/* this+19 */ unsigned long AID;
	/* this+23 */ int right;
	/* this+27 */ bool isMaster;
	/* this+28 */ char GuildName[24];
};


struct PACKET_IZ_UPDATE_CHARSTAT
{// 10590
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ unsigned long AID;
	/* this+14 */ int status;
	/* this+18 */ short sex;
	/* this+20 */ short head;
	/* this+22 */ short headPalette;
	/* this+24 */ short job;
	/* this+26 */ int Level;
};


struct PACKET_ZI_GUILD_NOTICE
{// 10591
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ char subject[60];
	/* this+66 */ char notice[120];
};


struct PACKET_IZ_GUILD_NOTICE
{// 10592
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ char subject[60];
	/* this+66 */ char notice[120];
};


struct PACKET_ZI_ALLY_GUILD
{// 10593
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long otherGDID;
	/* this+10 */ unsigned long myAID;
	/* this+14 */ unsigned long myGID;
	/* this+18 */ unsigned long otherAID;
	/* this+22 */ unsigned long otherGID;
	/* this+26 */ int answer;
};


struct PACKET_IZ_ADD_ALLY_GUILD
{// 10595
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned char answer;
	/* this+11 */ GUILDALLYINFO Ally;
};


struct PACKET_ZI_REQ_HOSTILE_GUILD
{// 10596
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long OtherGDID;
	/* this+10 */ unsigned long MyAID;
};


struct PACKET_IZ_ADD_HOSTILE_GUILD
{// 10598
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned char answer;
	/* this+11 */ GUILDALLYINFO Hostile;
};


struct PACKET_IZ_GUILD_MEMBER_ADD
{// 10599
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GDID;
	/* this+6 */ GUILDMINFO Info;
};


struct PACKET_ZI_REQ_DELETE_RELATED_GUILD
{// 10600 (0x2968)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long OpponentGDID;
	/* this+10 */ int Relation;
};


struct PACKET_IZ_DELETE_RELATED_GUILD
{// 10601
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long OpponentGDID;
	/* this+10 */ int Relation;
};


struct PACKET_ZI_ACTOR_INIT
{// 10602 (0x296A)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned long GID;
};


struct PACKET_ZI_GUILD_CHAT
{// 10603
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long GDID;
	/* this+8 */ char Text[];
};


struct PACKET_IZ_GUILD_CHAT
{// 10604
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long GDID;
	/* this+8 */ char Text[];
};


struct PACKET_ZI_ADD_EXP
{// 10605
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int Exp;
};


struct PACKET_IZ_ADD_EXP
{// 10606
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int Exp;
	/* this+14 */ int MaxUserNum;
};


struct PACKET_ZI_CHAR_LEVEL_UP
{// 10613 (0x2975)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ BYTE unknown[]; //TODO
};


struct PACKET_ZI_GUILD_ZENY
{// 10614
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
	/* this+14 */ char mapName[16];
	/* this+30 */ unsigned char type;
	/* this+31 */ int zeny;
};


struct PACKET_IZ_GUILD_ZENY
{// 10615
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
	/* this+14 */ char mapName[16];
	/* this+30 */ unsigned char type;
	/* this+31 */ int zeny;
	/* this+35 */ unsigned char ret;
};


struct PACKET_IZ_GUILD_ZENY_UPDATE_ALL
{// 10617
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GDID;
	/* this+6 */ unsigned long Zeny;
};


struct PACKET_ZI_GUILD_CHANGEOWNER_AGIT
{// 10619 (0x297B)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long oldGDID;
	/* this+ 6 */ unsigned long newGDID;
	/* this+10 */ char mapName[16];
};


struct PACKET_IZ_GUILD_NOTIFYSKILLDATA
{// 10628
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ int isForceSend;
	/* this+12 */ int SkillPoint;
	/* this+16 */ BYTE Data[]; //TODO
};


struct PACKET_ZI_GDSKILL_UPDATE
{// 10629
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ int SkillPoint;
	/* this+12 */ BYTE Data[]; //TODO
};


enum SPECIALMOVETYPE
{
	SHIFTAID    = 0,
	SHIFTGID    = 1,
	SUMMONAID   = 2,
	SUMMONGID   = 3,
	SUMMONMARRY = 4,
};


struct PACKET_ZI_MOVE
{// 10632 (0x2988)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int MoveType; // SPECIALMOVETYPE
	/* this+ 6 */ unsigned long SrcID;
	/* this+10 */ int DestX;
	/* this+14 */ int DestY;
	/* this+18 */ char DestName[24];
};


struct PACKET_IZ_MOVE
{// 10633 (0x2989)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int MoveType; // SPECIALMOVETYPE
	/* this+ 6 */ unsigned long SrcID;
	/* this+10 */ unsigned long DestID;
	/* this+14 */ int DestX;
	/* this+18 */ int DestY;
	/* this+22 */ char MapName[16];
	/* this+38 */ char CharName[24];
};


struct PACKET_ZI_GUILD_CHANGEMAXUSER
{// 10634
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GDID;
	/* this+6 */ int maxNum;
};


struct PACKET_IZ_GUILD_CHANGEMAXUSER
{// 10635
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GDID;
	/* this+6 */ int maxNum;
};


struct PACKET_IZ_FREE_GUILD
{// 10636
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GDID;
};


struct PACKET_IZ_GUILD_CHANGEOWNER_AGIT
{// 10637 (0x298D)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long oldGDID;
	/* this+ 6 */ unsigned long newGDID;
	/* this+10 */ char mapName[16];
};


struct PACKET_ZI_MAKE_GROUP2
{// 10638 (0x298E)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char groupName[24];
	/* this+34 */ bool ItemPickupRule;
	/* this+35 */ bool ItemDivisionRule;
};


struct PACKET_IZ_ADD_MEMBER_TO_GROUP2
{// 10639 (0x298F)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long receiverAID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long Role;
	/* this+14 */ unsigned char state;
	/* this+15 */ char groupName[24];
	/* this+39 */ char characterName[24];
	/* this+63 */ char mapName[16];
	/* this+79 */ bool ItemPickupRule;
	/* this+80 */ bool ItemDivisionRule;
};


struct PACKET_ZI_MOVE_GID
{// 10640 (0x2990)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int MoveType;
	/* this+ 6 */ unsigned long SrcID;
	/* this+10 */ int DestX;
	/* this+14 */ int DestY;
	/* this+18 */ char DestName[24];
	/* this+42 */ unsigned long DestGID;
};


struct PACKET_IZ_GUILD_MAP_CHANGE
{// 10641
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ char mapName[16];
};


struct PACKET_ZI_VERSION
{// 10642 (0x2992)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long Version;
};


struct PACKET_ZI_DIVORCE
{// 10647 (0x2997)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char name[24];
};


struct PACKET_IZ_DIVORCE
{// 10648 (0x2998)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char name[24];
};


struct PACKET_IZ_FRIENDS_LIST
{// 10649 (0x2999)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long AID;
	/* this+8 */ STRUCT_FRIEND List[];
};


struct PACKET_IZ_FRIENDS_STATE
{// 10650 (0x299A)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long FriendAID;
	/* this+10 */ unsigned long FriendGID;
	/* this+14 */ bool State;
};


struct PACKET_ZI_ACK_REQ_ADD_FRIENDS
{// 10651 (0x299B)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long ReqAID;
	/* this+ 6 */ unsigned long ReqGID;
	/* this+10 */ unsigned long AckAID;
	/* this+14 */ unsigned long AckGID;
};


struct PACKET_IZ_ADD_FRIENDS
{// 10652 (0x299C)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short Result;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long FriendAID;
	/* this+12 */ unsigned long FriendGID;
	/* this+16 */ char Name[24];
};


struct PACKET_ZI_DELETE_FRIENDS
{// 10653 (0x299D)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long FriendAID;
	/* this+10 */ unsigned long FriendGID;
};


struct PACKET_IZ_DELETE_FRIENDS
{// 10654 (0x299E)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long FriendAID;
	/* this+10 */ unsigned long FriendGID;
};


struct PACKET_ZI_MOVE_SERVER
{// 10655 (0x299F)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char charName[24];
};


struct PACKET_SVR_PING
{// 10656 (0x29A0)
	/* this+0 */ short PacketType;
	/* this+2 */ int SID;
};


struct PACKET_IZ_NOTIFY_MAKERRANK
{// 10657
	/* this+  0 */ short PacketType;
	/* this+  2 */ short type;
	/* this+  4 */ unsigned long GID[10];
	/* this+ 44 */ char charname[10][24];
	/* this+284 */ int point[10];
};


struct PACKET_ZI_UPDATE_MAKERRANK
{// 10658 (0x29A2)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short type;
	/* this+ 4 */ unsigned long GID;
	/* this+ 8 */ int point;
	/* this+12 */ char charname[24];
};


struct PACKET_ZI_EPISODE_VERSION
{// 10670 (0x29AE)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long Episode_Ver;
	/* this+6 */ unsigned long Minor_Ver;
};


struct PACKET_IZ_CHK_PROCESSTIME
{// 10671 (0x29AF)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long InterProcessTime;
};


struct PACKET_ZI_ACK_CHK_PROCESSTIME
{// 10672 (0x29B0)
	/* this+0 */ short PacketType;
	/* this+2 */ time_t InterProcessTime;
	/* this+6 */ time_t ZoneProcessTime;
};


struct PACKET_IZ_DISCONNECT_CHARACTER
{// 10673 (0x29B1)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_IZ_ACK_LOGON
{// 10674 (0x29B2)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Type;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
};


struct PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION
{// 10684 (0x29BC)
	/* this+  0 */ short PacketType;
	/* this+  2 */ char Name[60+1];
	/* this+ 63 */ char NickName[60+1];
	/* this+124 */ unsigned long GRID;
	/* this+128 */ unsigned long AID;
	/* this+132 */ unsigned long GID;
};


struct PACKET_IZ_INSTANTMAP_CREATE_REQ
{// 10686 (0x29BE)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned int hRequestN2Obj;
	/* this+ 6 */ char mapName[16];
	/* this+22 */ int mapID;
	/* this+26 */ int mapType;
};


struct PACKET_ZI_INSTANTMAP_CREATE_RES
{// 10687 (0x29BF)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned int hRequestN2Obj;
	/* this+ 6 */ char mapName[16];
	/* this+22 */ int mapID;
	/* this+26 */ bool bSuccess;
};


struct PACKET_ZI_SERVERSTATE_HAN_GAME
{// 10689 (0x29C1)
	/* this+0 */ short PacketType;
	/* this+2 */ int monitorNum;
	/* this+6 */ IM_SERVER_STATE_HAN_GAME state;
};


struct PACKET_ZI_INSTANTMAP_ERROR
{// 10692 (0x29C4)
	enum enumWhy
	{
		WHY_UNKNOWN = 0,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned int hRequestN2Obj;
	/* this+ 6 */ int mapID;
	/* this+10 */ enumWhy why;
};


struct PACKET_IZ_INSTNATMAP_DESTROY
{// 10693 (0x29C5)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char mapName[16];
	/* this+18 */ int mapID;
};


struct PACKET_ZI_PING
{// 10694 (0x29C6)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned int UsedKBytesMemory;
	/* this+6 */ unsigned int NumTotalNPC;
};


struct PACKET_ZI_INSTANTMAP_ALLOW
{// 10695 (0x29C7)
	enum enumWhy
	{
		WHY_ZSVR_SETTING  = 0,
		WHY_AGITWAR_START = 1,
		WHY_AGITWAR_END   = 2,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ enumWhy why;
	/* this+6 */ bool bAllow;
};


struct PACKET_XX_CONNECT
{// 10696 (0x29C8)
	/* this+0 */ short PacketType;
};


struct PACKET_XX_DISCONNECT
{// 10697 (0x29C9)
	/* this+0 */ short PacketType;
};


struct PACKET_IZ_MEMORIALDUNGEON_MSG //: public PACKET_IZ_PARTY_BROADCAST
{// 10698 (0x29CA)
	enum enumNotify
	{
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_UNKNOWN   = 0,
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_DUPLICATE = 1,
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_RIGHT     = 2,
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_EXIST     = 3,
		MEMORIALDUNGEON_SUBSCRIPTION_CANCEL_FAIL     = 4,
		MEMORIALDUNGEON_SUBSCRIPTION_CANCEL_SUCCESS  = 5,
		MEMORIALDUNGEON_CREATE_FAIL                  = 6,
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_CLOSE     = 7,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ enumNotify Notify;
	/* this+14 */ char MemorialDungeonName[60+1];
};


struct PACKET_ZI_PARTY_JOIN_REQ
{// 10700 (0x29CC)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long senderAID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ char TargetCharName[24];
};


struct PACKET_IZ_PARTY_JOIN_REQ_ACK
{// 10701 (0x29CD)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long requestAID;
	/* this+ 6 */ char characterName[24];
	/* this+30 */ PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer answer;
};


struct PACKET_IZ_PARTY_JOIN_REQ
{// 10702 (0x29CE)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long targetAID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ char groupName[24];
};


struct PACKET_ZI_PARTY_JOIN_REQ_ACK
{// 10703 (0x29CF)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long targetAID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer answer;
};


struct PACKET_IZ_PARTY_BROADCAST
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned long AID;
};


struct PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY : public PACKET_IZ_PARTY_BROADCAST
{// 10706 (0x29D2)
	/* this+ 0 */ //short PacketType;
	/* this+ 2 */ //unsigned long GID;
	/* this+ 6 */ //unsigned long AID;
	/* this+10 */ short PriorityOrderNum;
};


struct PACKET_IZ_MEMORIALDUNGEON_NOTIFY : public PACKET_IZ_PARTY_BROADCAST
{// 10708 (0x29D4)
	/* this+ 0 */ //short PacketType;
	/* this+ 2 */ //unsigned long GID;
	/* this+ 6 */ //unsigned long AID;
	/* this+10 */ PACKET_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE Type;
	/* this+14 */ unsigned long EnterLimitDate;
};


struct PACKET_ZI_MEMORIALDUNGEON_COMMAND
{// 10709 (0x29D5)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ char partyName[24];
	/* this+34 */ PACKET_CZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND Command;
};


struct PACKET_IZ_MEMORIALDUNGEON_SYNC
{// 10710 (0x29D6)
	enum enumEVENT
	{
		EVENT_CREATE  = 0,
		EVENT_DESTROY = 1,
	};

	/* this+  0 */ short PacketType;
	/* this+  2 */ char MemorialDungeonName[60+1];
	/* this+ 63 */ unsigned long hPartyID;
	/* this+ 67 */ char partyName[24];
	/* this+ 91 */ unsigned long ExistZSID;
	/* this+ 95 */ unsigned long hMemorialDungeonID;
	/* this+ 99 */ int Factor;
	/* this+103 */ enumEVENT Event;
};


struct PACKET_ZI_MEMORIALDUNGEON_VISA
{// 10711 (0x29D7)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned long AID;
};


struct PACKET_IZ_MEMORIALDUNGEON_VISA
{// 10712 (0x29D8)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long ZSID;
	/* this+14 */ char mapName[16];
	/* this+30 */ int x;
	/* this+34 */ int y;
};


struct PACKET_IZ_MEMORIALDUNGEON_COMMAND
{// 10713 (0x29D9)
	enum enumCOMMAND
	{
		COMMAND_PLAYER_KICK = 0,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ enumCOMMAND Command;
};


struct PACKET_IZ_LEAVE_GROUP
{// 10715 (0x29DB)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned long GID;
};


struct PACKET_ZI_MEMORIALDUNGEON_OPENSTATE
{// 10716 (0x29DC)
	/* this+0 */ short PacketType;
	enum enumRequest
	{
		REQUEST_OPEN   = 0,
		REQUEST_CLOSE  = 1,
		REQUEST_UPDATE = 2,
	};
	/* this+ 2 */ enumRequest Request;
	/* this+ 6 */ unsigned long RequestGID;
	/* this+10 */ unsigned long RequestAID;
};


struct PACKET_IZ_MEMORIALDUNGEON_OPENSTATE
{// 10717 (0x29DD)
	/* this+0 */ short PacketType;
	/* this+2 */ bool bOpen;
	/* this+3 */ unsigned long ToGID;
	/* this+7 */ unsigned long ToAID;
};


struct PACKET_ZI_GROUPINFO_CHANGE_V2
{// 10728 (0x29E8)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GRID;
	/* this+ 6 */ unsigned long MasterAID;
	/* this+10 */ int FamilyGroup;
	/* this+14 */ unsigned long expOption; // enumGROUPEXPOPTION
	/* this+18 */ bool ItemPickupRule;
	/* this+19 */ bool ItemDivisionRule;
};


struct PACKET_IZ_REQ_GROUPINFO_CHANGE_V2
{// 10729 (0x29E9)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ unsigned long expOption; // enumGROUPEXPOPTION
	/* this+14 */ bool ItemPickupRule;
	/* this+15 */ bool ItemDivisionRule;
};


struct PACKET_ZI_CHANGE_GROUP_MASTER
{// 10730 (0x29EA)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GRID;
	/* this+ 6 */ unsigned long MasterAID;
	/* this+10 */ unsigned long AID;
};


struct PACKET_ZI_SEEK_PARTY
{// 10734 (0x29EE)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char Name[24];
	/* this+26 */ unsigned long Job;
	/* this+30 */ unsigned long Level;
	/* this+34 */ char mapName[16];
	/* this+50 */ unsigned long Option;
};


struct PACKET_IZ_SEEK_PARTY
{// 10735 (0x29EF)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char Name[24];
	/* this+26 */ unsigned long Job;
	/* this+30 */ unsigned long Level;
	/* this+34 */ char mapName[16];
	/* this+50 */ unsigned long Option;
};


struct PACKET_ZI_SEEK_PARTY_MEMBER
{// 10736 (0x29F0)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char Name[24];
	/* this+26 */ unsigned long Job;
	/* this+30 */ unsigned long Level;
	/* this+34 */ char mapName[16];
	/* this+50 */ unsigned long Option;
};


struct PACKET_IZ_SEEK_PARTY_MEMBER
{// 10737 (0x29F1)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char Name[24];
	/* this+26 */ unsigned long Job;
	/* this+30 */ unsigned long Level;
	/* this+34 */ char mapName[16];
	/* this+50 */ unsigned long Option;
};


struct PACKET_IZ_CHANGE_GROUP_MASTER
{// 10773 (0x2A15)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long receiverAID;
	/* this+ 6 */ unsigned long OldMasterAID;
	/* this+10 */ unsigned long NewMasterAID;
};


struct PACKET_ZI_BROADCASTING_SPECIAL_ITEM_OBTAIN : public PACKET_ZC_BROADCASTING_SPECIAL_ITEM_OBTAIN
{// 10774 (0x2A16)
};


struct PACKET_IZ_BROADCASTING_SPECIAL_ITEM_OBTAIN : public PACKET_ZC_BROADCASTING_SPECIAL_ITEM_OBTAIN
{// 10775 (0x2A17)
};


struct PACKET_IZ_DEFINE_CHECK : public PACKET_ZC_DEFINE_CHECK
{// 10776 (0x2A18)
};


struct PACKET_ZI_SERVERSTATE_CHANNELING
{// 10777 (02A19)
	/* this+0 */ short PacketType;
	/* this+2 */ int monitorNum;
	/* this+6 */ IM_SERVER_STATE_CHANNELING state;
};


struct PACKET_ZI_PARTY_BOOKING_NOTIFY_INSERT
{// 10778 (0x2A1A)
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE Data[52]; //TODO
};


struct PACKET_IZ_PARTY_BOOKING_NOTIFY_INSERT
{// 10779 (0x2A1B)
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE Data[52]; //TODO
};


struct PACKET_IZ_PARTY_BOOKING_NOTIFY_DELETE
{// 10781 (0x2A1D)
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE Data[4]; //TODO
};


struct PACKET_ZI_PARTY_BOOKING_NOTIFY_UPDATE
{// 10782 (0x2A1E)
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE Data[16]; //TODO
};


struct PACKET_ZI_MOVE_2
{// 10794 (0x2A2A)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int MoveType; // SPECIALMOVETYPE
	/* this+ 6 */ unsigned long SrcID;
	/* this+10 */ int DestX;
	/* this+14 */ int DestY;
	/* this+18 */ unsigned long DestAID;
	/* this+22 */ unsigned long DestGID;
	/* this+26 */ char DestName[24];
};


struct PACKET_ZI_GPK_DYNCODE_RELOAD
{// 10800 (0x2A30)
	/* this+0 */ short PacketType;
};


struct PACKET_IZ_GPK_DYNCODE_RELOAD
{// 10801 (0x2A31)
	/* this+0 */ short PacketType;
};


struct PACKET_ZI_AUTH_REQ
{// 10811
	/* this+0 */ short PacketType;
	/* this+2 */ DWORD dwIP;
	/* this+6 */ short sPort;
	/* this+8 */ int ZSID;
};


struct PACKET_IZ_AUTH_ACK
{// 10812
	/* this+0 */ short PacketType;
};


struct PACKET_IZ_REQ_EDIT_EXP
{// 10815
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int monitornum;
	/* this+ 6 */ int Exp;
	/* this+10 */ int Death;
	/* this+14 */ int Drop;
};


enum enumENTRYQUEUERETCODE
{
	EQ_SUCCESS                = 1,
	EQ_FULL                   = 2,
	EQ_INVALID_NAME           = 3,
	EQ_INVALID_TYPE           = 4,
	EQ_INVALID_MAX_MEMBER     = 5,
	EQ_INVALID_LEVEL          = 6,
	EQ_DUPLICATION            = 7,
	EQ_RECONNECT_INTER_SERVER = 8,
	EQ_NOT_MASTER             = 9,
	EQ_INVALID_JOB            = 10,
	EQ_NOT_FOUND_USER         = 11,
	EQ_INVALID_USER_COUNT     = 12,
	EQ_NOT_READY              = 13,
	EQ_ZSVR_DISCONNECT        = 14,
	EQ_LOCATION_BATTLEFIELD   = 15,
};


struct AID_GID_INFO
{
	AID_GID_INFO(const unsigned long in_AID, const unsigned long in_GID)
	{
		this->AID = in_AID;
		this->GID = in_GID;
	}

	/* this+0 */ unsigned long AID;
	/* this+4 */ unsigned long GID;
};


struct PACKET_ZI_INFO_ENTRY_QUEUE_APPLY
{// 10818 (0x2A42)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned char Result;
	/* this+ 5 */ char EntryQueueName[24];
	/* this+29 */ int Ranking;
	/* this+33 */ AID_GID_INFO Info[];
};


struct PACKET_IZ_INFO_ENTRY_QUEUE_APPLY
{// 10819 (0x2A43)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ char EntryQueueName[24];
	/* this+30 */ int Ranking;
};


struct ENTRY_QUEUE_APPLY_INFO
{
	ENTRY_QUEUE_APPLY_INFO(const unsigned long in_AID, const unsigned long in_GID, const std::string in_charName, const short in_job, const short in_sLevel)
	{
		this->AID = in_AID;
		this->GID = in_GID;
		strncpy_s(this->charName, countof(this->charName), in_charName.c_str(), _TRUNCATE);
		this->job = in_job;
		this->level = in_sLevel;
	}

	/* this+ 0 */ unsigned long AID;
	/* this+ 4 */ unsigned long GID;
	/* this+ 8 */ char charName[24];
	/* this+32 */ short job;
	/* this+34 */ short level;
};


struct PACKET_ZI_REQ_ENTRY_QUEUE_APPLY
{// 10820 (0x2A44)
	enum
	{
		SOLO  = 1,
		PARTY = 2,
		GUILD = 4,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
	/* this+34 */ short ApplyType;
	/* this+36 */ unsigned long GDID;
};


struct PACKET_IZ_NOTIFY_ENTRY_QUEUE_APPLY
{// 10821 (0x2A45)
	enum
	{
		SOLO  = 1,
		PARTY = 2,
		GUILD = 4,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long GID;
	/* this+12 */ char EntryQueueName[24];
	/* this+36 */ short ApplyType;
	/* this+38 */ ENTRY_QUEUE_APPLY_INFO Info[];
};


struct PACKET_ZI_RESULT_ENTRY_QUEUE_APPLY
{// 10822 (0x2A46)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ unsigned char Result;
	/* this+11 */ char EntryQueueName[24];
};


struct PACKET_IZ_RESULT_ENTRY_QUEUE_APPLY
{// 10823 (0x2A47)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char Result;
	/* this+7 */ char EntryQueueName[24];
};


//struct PACKET_ZI_INFO_ENTRY_QUEUE_CANCEL
//{// 10824 (0x2A48)
// TODO (34)
//};


//struct PACKET_IZ_INFO_ENTRY_QUEUE_CANCEL
//{// 10825 (0x2A49)
// TODO (30)
//};


struct PACKET_ZI_REQ_ENTRY_QUEUE_CANCEL
{// 10826 (0x2A4A)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
};


struct PACKET_IZ_NOTIFY_ENTRY_QUEUE_CANCEL
{// 10827 (0x2A4B)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
};


struct PACKET_ZI_RESULT_ENTRY_QUEUE_CANCEL
{// 10828 (0x2A4C)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ unsigned char Result;
	/* this+11 */ char EntryQueueName[24];
};


struct PACKET_IZ_RESULT_ENTRY_QUEUE_CANCEL
{// 10829 (0x2A4D)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char Result;
	/* this+7 */ char EntryQueueName[24];
};


struct PACKET_ZI_ENTRY_QUEUE_ADMISSION
{// 10830 (0x2A4E)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
};


struct PACKET_IZ_ENTRY_QUEUE_ADMISSION
{// 10831 (0x2A4F)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char EntryQueueName[24];
};


struct PACKET_ZI_ENTRY_QUEUE_ADMISSION_ACCEPT
{// 10832 (0x2A50)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
	/* this+34 */ char mapName[16];
	/* this+50 */ int xPos;
	/* this+54 */ int yPos;
};


struct PACKET_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_ACCEPT
{// 10833 (0x2A51)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
	/* this+34 */ char mapName[16];
	/* this+50 */ int xPos;
	/* this+54 */ int yPos;
};


struct PACKET_ZI_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT
{// 10834 (0x2A52)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ unsigned char Result;
	/* this+11 */ char EntryQueueName[24];
};


struct PACKET_IZ_RESULT_ENTRY_QUEUE_ADMISSION_ACCEPT
{// 10835 (0x2A53)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char Result;
	/* this+7 */ char EntryQueueName[24];
};


struct PACKET_ZI_ENTRY_QUEUE_ADMISSION_REFUSE
{// 10836 (0x2A54)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
};


struct PACKET_IZ_NOTIFY_ENTRY_QUEUE_ADMISSION_REFUSE
{// 10837 (0x2A55)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
};


struct PACKET_ZI_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE
{// 10838 (0x2A56)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ unsigned char Result;
	/* this+11 */ char EntryQueueName[24];
};


struct PACKET_IZ_RESULT_ENTRY_QUEUE_ADMISSION_REFUSE
{// 10839 (0x2A57)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char Result;
	/* this+7 */ char EntryQueueName[24];
};


struct PACKET_ZI_LOBBY_ADMISSION
{// 10840 (0x2A58)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
	/* this+34 */ char LobbyName[24];
};


struct PACKET_IZ_LOBBY_ADMISSION
{// 10841 (0x2A59)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ char EntryQueueName[24];
	/* this+30 */ char LobbyName[24];
};


struct PACKET_ZI_LOBBY_ADMISSION_ACCEPT
{// 10842 (0x2A5A)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
	/* this+34 */ char LobbyName[24];
	/* this+58 */ char mapName[16];
	/* this+74 */ int xPos;
	/* this+78 */ int yPos;
};


struct PACKET_IZ_NOTIFY_LOBBY_ADMISSION_ACCEPT
{// 10843 (0x2A5B)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
	/* this+34 */ char LobbyName[24];
	/* this+58 */ char mapName[16];
	/* this+74 */ int xPos;
	/* this+78 */ int yPos;
};


struct PACKET_ZI_RESULT_LOBBY_ADMISSION_ACCEPT
{// 10844 (0x2A5C)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ unsigned char Result;
	/* this+11 */ char EntryQueueName[24];
	/* this+35 */ char LobbyName[24];
};


struct PACKET_IZ_RESULT_LOBBY_ADMISSION_ACCEPT
{// 10845 (0x2A5D)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned char Result;
	/* this+ 7 */ char EntryQueueName[24];
	/* this+31 */ char LobbyName[24];
};


struct PACKET_ZI_LOBBY_ADMISSION_REFUSE
{// 10846 (0x2A5E)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
	/* this+34 */ char LobbyName[24];
};


struct PACKET_IZ_NOTIFY_LOBBY_ADMISSION_REFUSE
{// 10847 (0x2A5F)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
	/* this+34 */ char LobbyName[24];
};


struct PACKET_ZI_RESULT_LOBBY_ADMISSION_REFUSE
{// 10848 (0x2A60)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ unsigned char Result;
	/* this+11 */ char EntryQueueName[24];
	/* this+35 */ char LobbyName[24];
};


struct PACKET_IZ_RESULT_LOBBY_ADMISSION_REFUSE
{// 10849 (0x2A61)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned char Result;
	/* this+ 7 */ char EntryQueueName[24];
	/* this+31 */ char LobbyName[24];
};


struct PACKET_IZ_ENTRY_QUEUE_LOGOUT
{// 10850 (0x2A62)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char EntryQueueName[24];
	/* this+26 */ unsigned long GID;
};


struct PACKET_ZI_ENTRY_QUEUE_MOVE_ROOM
{// 10851 (0x2A63)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char mapName[16];
	/* this+26 */ int xPos;
	/* this+30 */ int yPos;
};


struct PACKET_IZ_ENTRY_QUEUE_MOVE_ROOM
{// 10852 (0x2A64)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ char mapName[16];
	/* this+22 */ int xPos;
	/* this+26 */ int yPos;
};


struct PACKET_ZI_LOBBY_MOVE_ROOM
{// 10853 (0x2A65)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char mapName[16];
	/* this+26 */ int xPos;
	/* this+30 */ int yPos;
};


struct PACKET_IZ_LOBBY_MOVE_ROOM
{// 10854 (0x2A66)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ char mapName[16];
	/* this+22 */ int xPos;
	/* this+26 */ int yPos;
};


struct PACKET_ZI_ENTRY_QUEUE_NAME
{// 10855 (0x2A67)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ char EntryQueueName[][24];
};


struct PACKET_ZI_ENTRY_QUEUE_DELETE_GID
{// 10872 (0x2A78)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
};


struct PACKET_ZI_MEMORIALDUNGEON_SUBSCRIPTION2
{// 10873 (0x2A79)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ char NickName[60+1];
	/* this+65 */ unsigned long GRID;
	/* this+69 */ unsigned long AID;
	/* this+73 */ unsigned long GID;
	/* this+77 */ char MemorialDungeonName[];
};


struct PACKET_IZ_MEMORIALDUNGEON_SYNC2
{// 10874 (0x2A7A)
	enum enumEVENT
	{
		EVENT_CREATE  = 0,
		EVENT_DESTROY = 1,
	};

	/* this+ 0 */ short PacketType;
	/* this +2 */ short PacketLength;
	/* this+ 4 */ unsigned long hPartyID;
	/* this+ 8 */ char partyName[24];
	/* this+32 */ unsigned long ExistZSID;
	/* this+36 */ unsigned long hMemorialDungeonID;
	/* this+40 */ int Factor;
	/* this+44 */ enumEVENT Event;
	/* this+48 */ char MemorialDungeonName[];
};


struct PACKET_IZ_PARTY_BROADCAST_VAR
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long GID;
	/* this+8 */ unsigned long AID;
};


struct PACKET_IZ_MEMORIALDUNGEON_MSG2 : public PACKET_IZ_PARTY_BROADCAST_VAR
{// 10875 (0x2A7B)
	enum enumNotify
	{
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_UNKNOWN   = 0,
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_DUPLICATE = 1,
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_RIGHT     = 2,
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_EXIST     = 3,
		MEMORIALDUNGEON_SUBSCRIPTION_CANCEL_FAIL     = 4,
		MEMORIALDUNGEON_SUBSCRIPTION_CANCEL_SUCCESS  = 5,
		MEMORIALDUNGEON_CREATE_FAIL                  = 6,
		MEMORIALDUNGEON_SUBSCRIPTION_ERROR_CLOSE     = 7,
	};

	/* this+ 0 */ //short PacketType;
	/* this+ 2 */ //short PacketLength;
	/* this+ 4 */ //unsigned long GID;
	/* this+ 8 */ //unsigned long AID;
	/* this+12 */ enumNotify Notify;
	/* this+16 */ char MemorialDungeonName[];
};


struct PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2 : public PACKET_IZ_PARTY_BROADCAST_VAR
{// 10876 (0x2A7C)
	/* this+ 0 */ //short PacketType;
	/* this+ 2 */ //short PacketLength;
	/* this+ 4 */ //unsigned long GID;
	/* this+ 8 */ //unsigned long AID;
	/* this+12 */ short PriorityOrderNum;
	/* this+14 */ char MemorialDungeonName[];
};


struct PACKET_IZ_MEMORIALDUNGEON_INFO2 : public PACKET_IZ_PARTY_BROADCAST_VAR
{// 10877 (0x2A7D)
	/* this+ 0 */ //short PacketType;
	/* this+ 2 */ //short PacketLength;
	/* this+ 4 */ //unsigned long GID;
	/* this+ 8 */ //unsigned long AID;
	/* this+12 */ unsigned long DestroyDate;
	/* this+16 */ unsigned long EnterTimeOutDate;
	/* this+20 */ char MemorialDungeonName[];
};


struct PACKET_ZI_ENTRY_QUEUE_RANKING
{// 10880 (0x2A80)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
};


struct PACKET_IZ_ENTRY_QUEUE_RANKING
{// 10881 (0x2A81)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
};


struct PACKET_ZI_NOTIFY_ENTRY_QUEUE_RANKING
{// 10882 (0x2A82)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
	/* this+34 */ int Ranking;
};


struct PACKET_IZ_NOTIFY_ENTRY_QUEUE_RANKING
{// 10883 (0x2A83)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ char EntryQueueName[24];
	/* this+30 */ int Ranking;
};
	

struct PACKET_ZI_JOB_CHANGE
{// 10886 (0x2A86)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ short job;
};


struct PACKET_ZI_LOBBY_ADMISSION_V2
{// 10888 (0x2A88)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char EntryQueueName[24];
	/* this+34 */ char LobbyName[24];
	/* this+58 */ char CampCode;
	/* this+59 */ short xPos;
	/* this+61 */ short yPos;
};


struct PACKET_IZ_LOBBY_ADMISSION_V2
{// 10889 (0x2A89)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ char EntryQueueName[24];
	/* this+30 */ char LobbyName[24];
	/* this+54 */ char CampCode;
	/* this+55 */ short xPos;
	/* this+57 */ short yPos;
};


struct PACKET_ZI_REQ_JOIN_GUILD2
{// 10890 (0x2A8A)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long myAID;
	/* this+ 6 */ unsigned long myGID;
	/* this+10 */ char receiverName[24];
};


struct PACKET_IZ_REQ_JOIN_GUILD2
{// 10891 (0x2A8B)
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE Data[36]; //TODO
};


struct PACKET_ZI_PING_LIVE
{// 10894 (0x2A8E)
	/* this+0 */ short PacketType;
};


struct PACKET_IZ_PING_LIVE
{// 10895 (0x2A8F)
	/* this+0 */ short PacketType;
};


struct PACKET_ZI_STATEINFO
{// 10896 (0x2A90)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned int UsedKBytesMemory;
	/* this+6 */ unsigned int NumTotalNPC;
};


struct PACKET_ZH_PING_LIVE
{// 10897 (0x2A91)
	/* this+0 */ short PacketType;
};


struct PACKET_HZ_PING_LIVE
{// 10898 (0x2A92)
	/* this+0 */ short PacketType;
};


struct PACKET_ZI_OTHER_ZONE_PC_SEND_MSG
{// 10900 (0x2A94)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short msg;
	/* this+4 */ unsigned long TargetAID;
};


//struct PACKET_IZ_OTHER_ZONE_PC_SEND_MSG
//{// 10901 (0x2A95)
// TODO (8)
//};


struct PACKET_ZI_MEMORIALDUNGEON_DESTROY
{// 10925 (0x2AAD)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GRID;
};


struct PACKET_IZ_INSTANTMAP_ADD3
{// 10928 (0x2AB0)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int ZSID;
	/* this+ 6 */ char mapName[16];
	/* this+22 */ int mapID;
	/* this+26 */ int mapType;
	/* this+30 */ bool bPlayerEnter;
};


struct PACKET_IZ_INSTANTMAP_REMOVE3
{// 10929 (0x2AB1)
	/* this+ 0 */ short PacketType;
	/* this +2 */ int ZSID;
	/* this+ 6 */ int mapID;
	/* this+10 */ char mapName[16];
};


struct PACKET_IZ_INSTANTMAP_PLAYER_ENTER3
{// 10930 (0x2AB2)
	/* this+0 */ short PacketType;
	/* this+2 */ int mapID;
	/* this+6 */ bool bPlayerEnter;
};


///////////////////////////////////////
#pragma pack(pop)
