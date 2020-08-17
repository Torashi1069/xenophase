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
	XXX_HEADER_ZI_PARTY_RECRUIT_NOTIFY_INSERT         = 10856,
	XXX_HEADER_IZ_PARTY_RECRUIT_NOTIFY_INSERT         = 10857,
	XXX_HEADER_ZI_PARTY_RECRUIT_NOTIFY_DELETE         = 10858,
	XXX_HEADER_IZ_PARTY_RECRUIT_NOTIFY_DELETE         = 10859,
	XXX_HEADER_ZI_PARTY_RECRUIT_NOTIFY_UPDATE         = 10860,
	XXX_HEADER_IZ_PARTY_RECRUIT_NOTIFY_UPDATE         = 10861,
	XXX_HEADER_ZI_PARTY_RECRUIT_VOLUNTEER_INFO        = 10862,
	XXX_HEADER_IZ_PARTY_RECRUIT_VOLUNTEER_INFO        = 10863,
	XXX_HEADER_ZI_PARTY_RECRUIT_REQ_RECALL            = 10864,
	XXX_HEADER_IZ_PARTY_RECRUIT_REQ_RECALL            = 10865,
	XXX_HEADER_ZI_PARTY_RECRUIT_FAILED_RECALL         = 10866,
	XXX_HEADER_IZ_PARTY_RECRUIT_FAILED_RECALL         = 10867,
	XXX_HEADER_ZI_PARTY_RECRUIT_REFUSE_VOLUNTEER      = 10868,
	XXX_HEADER_IZ_PARTY_RECRUIT_REFUSE_VOLUNTEER      = 10869,
	HEADER_AH_JPN_LOGON_ACK                           = 10870,
	HEADER_HZ_JPN_PREMIUM_CAMPAIGN                    = 10871,
	HEADER_ZI_ENTRY_QUEUE_DELETE_GID                  = 10872,
	HEADER_ZI_MEMORIALDUNGEON_SUBSCRIPTION2           = 10873,
	HEADER_IZ_MEMORIALDUNGEON_SYNC2                   = 10874,
	HEADER_IZ_MEMORIALDUNGEON_MSG2                    = 10875,
	HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2      = 10876,
	HEADER_IZ_MEMORIALDUNGEON_INFO2                   = 10877,
	XXX_HEADER_ZI_PARTY_RECRUIT_CANCEL_VOLUNTEER      = 10878,
	XXX_HEADER_IZ_PARTY_RECRUIT_CANCEL_VOLUNTEER      = 10878,
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
	HEADER_HZ_DISPATCH_TIMING_CHN                     = 10938,
	HEADER_HZ_PERSONAL_INFORMATION_TW                 = 10939,
	HEADER_IZ_RELAY_NOTIFY                            = 10940,
	HEADER_ZI_REQ_APPLY_BARGAIN_SALE_ITEM             = 10941,
	HEADER_ZI_REQ_REMOVE_BARGAIN_SALE_ITEM            = 10942,
	HEADER_IZ_ACK_REMOVE_BARGAIN_SALE_ITEM            = 10943,
	HEADER_ZI_BUY_BARGAIN_SALE_ITEM                   = 10944,
	HEADER_AH_LOGON_FRA                               = 10945,
	HEADER_HZ_LOGON_FRA                               = 10946,
	HEADER_HZ_PERSONAL_INFORMATION_INDONESIA          = 10947,
	HEADER_HZ_LOGON_INDONESIA                         = 10948,
	HEADER_AH_LOGON_INDONESIA                         = 10949,
	HEADER_ZI_REQ_OPEN_GUILD_STORAGE                  = 10950,
	HEADER_IZ_ACK_OPEN_GUILD_STORAGE                  = 10951,
	HEADER_ZI_REQ_CLOSE_GUILD_STORAGE                 = 10952,
	HEADER_IZ_ACK_CLOSE_GUILD_STORAGE                 = 10953,
	HEADER_AH_LOGON_ACK_CHN2                          = 10954,
	HEADER_AH_LOGON_INDONESIA2                        = 10955,
	HEADER_ZI_REQ_ADD_MONITORINGUSER                  = 10956,
	HEADER_IZ_ACK_ADD_MONITORINGUSER                  = 10957,
	HEADER_ZI_REQ_DEL_MONITORINGUSER                  = 10958,
	HEADER_IZ_ACK_DEL_MONITORINGUSER                  = 10959,
	HEADER_ZI_REQ_CLEAR_MONITORINGUSER                = 10960,
	HEADER_IZ_ACK_CLEAR_MONITORINGUSER                = 10961,
	HEADER_ZI_REQ_MONITORINGUSERLIST                  = 10962,
	HEADER_IZ_ACK_MONITORINGUSERLIST                  = 10963,
	HEADER_SERVERMANAGER_RESERVED_START               = 10999,
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
	HEADER_MI_REQ_CLOSE_HACKSHIELD                    = 11019,
	HEADER_IM_ACK_CLOSE_HACKSHIELD                    = 11020,
	HEADER_MI_REQ_OPEN_HACKSHIELD                     = 11021,
	HEADER_IM_ACK_OPEN_HACKSHIELD                     = 11022,
	HEADER_SERVERMANAGER_RESERVED_END                 = 12000,
	HEADER_IZ_REQ_CLOSE_HACKSHIELD                    = 12001,
	HEADER_ZI_ACK_CLOSE_HACKSHIELD                    = 12002,
	HEADER_IZ_REQ_OPEN_HACKSHIELD                     = 12003,
	HEADER_ZI_ACK_OPEN_HACKSHIELD                     = 12004,
	HEADER_ZI_PRIVATE_DUNGEON_RESERVE                 = 20101,
	HEADER_IZ_PRIVATE_DUNGEON_RESERVE                 = 20102,
	HEADER_IZ_PRIVATE_DUNGEON_CREATE_RESULT           = 20103,
	HEADER_IZ_PRIVATE_DUNGEON_SYNC                    = 20104,
	HEADER_ZI_PRIVATE_DUNGEON_ENTER                   = 20105,
	HEADER_IZ_PRIVATE_DUNGEON_ENTER                   = 20106,
};


struct PACKET_CONNECTION_CLOSED
{// 10513
	/* this+0 */ short PacketType;
	/* this+2 */ short Type;
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


struct PACKET_REQ_REMAINTIME
{// 10622, 10623
	/* this+0 */ short PacketType;
	/* this+2 */ int AID;
};


struct PACKET_ZI_VERSION
{// 10642
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long Version;
};


struct PACKET_ZI_EPISODE_VERSION
{// 10670
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long Episode_Ver;
	/* this+6 */ unsigned long Minor_Ver;
};


struct PACKET_IZ_INSTANTMAP_CREATE_REQ
{// 10686
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned int hRequestN2Obj;
	/* this+ 6 */ char mapName[16];
	/* this+22 */ int mapID;
	/* this+26 */ int mapType;
};


struct PACKET_ZI_INSTANTMAP_CREATE_RES
{// 10687
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned int hRequestN2Obj;
	/* this+ 6 */ char mapName[16];
	/* this+22 */ int mapID;
	/* this+26 */ bool bSuccess;
};


struct PACKET_ZI_INSTANTMAP_ALLOW
{// 10695
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
{// 10696
	/* this+0 */ short PacketType;
};


struct PACKET_XX_DISCONNECT
{// 10697
	/* this+0 */ short PacketType;
};


struct PACKET_ZI_PARTY_JOIN_REQ_ACK
{// 10703
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long targetAID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer answer;
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


struct PACKET_ZH_AUTH_REQ
{// 10813
	/* this+0 */ short PacketType;
	/* this+2 */ DWORD dwIP;
	/* this+6 */ short sPort;
	/* this+8 */ int ZSID;
};


struct PACKET_HZ_AUTH_ACK
{// 10814
	/* this+0 */ short PacketType;
};


struct PACKET_IZ_NOTIFY_ENTRY_QUEUE_APPLY
{// 10821
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
	/* this+38 */ BYTE Data[]; //TODO
};


struct PACKET_ZI_RESULT_ENTRY_QUEUE_APPLY
{// 10822
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ unsigned char Result;
	/* this+11 */ char EntryQueueName[24];
};


struct PACKET_IZ_RESULT_ENTRY_QUEUE_APPLY
{// 10823
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char Result;
	/* this+7 */ char EntryQueueName[24];
};


struct PACKET_ZI_REQ_JOIN_GUILD2
{// 10890
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long myAID;
	/* this+ 6 */ unsigned long myGID;
	/* this+10 */ char receiverName[24];
};


struct PACKET_IZ_REQ_JOIN_GUILD2
{// 10891
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long ReqAID;
	/* this+14 */ char guildName[24];
};


struct PACKET_ZI_PING_LIVE
{// 10894
	/* this+0 */ short PacketType;
};


struct PACKET_IZ_PING_LIVE
{// 10895
	/* this+0 */ short PacketType;
};


struct PACKET_ZI_STATEINFO
{// 10896
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned int UsedKBytesMemory;
	/* this+6 */ unsigned int NumTotalNPC;
};


struct PACKET_ZH_PING_LIVE
{// 10897
	/* this+0 */ short PacketType;
};


struct PACKET_HZ_PING_LIVE
{// 10898
	/* this+0 */ short PacketType;
};


struct PACKET_IZ_OTHER_ZONE_PC_SEND_MSG
{// 10901
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short msg;
	/* this+4 */ unsigned long TargetAID;
};


struct PACKET_HZ_LOGON_KOR
{// 10906
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ bool bAuth;
	/* this+ 3 */ unsigned long AID;
	/* this+ 7 */ unsigned long GID;
	/* this+11 */ unsigned long TotalUsingTime;
	/* this+15 */ int selectedCharNum;
	/* this+19 */ bool bWorldEnterance;
};


struct PACKET_IZ_INSTANTMAP_ADD3
{// 10928
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int ZSID;
	/* this+ 6 */ char mapName[16];
	/* this+22 */ int mapID;
	/* this+26 */ int mapType;
	/* this+30 */ bool bPlayerEnter;
};


struct PACKET_IZ_INSTANTMAP_REMOVE3
{// 10929
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int ZSID;
	/* this+ 6 */ int mapID;
	/* this+10 */ char mapName[16];
};


struct PACKET_IZ_INSTANTMAP_PLAYER_ENTER3
{// 10930
	/* this+0 */ short PacketType;
	/* this+2 */ int mapID;
	/* this+6 */ bool bPlayerEnter;
};


struct PACKET_IZ_SET_EFFECT_HIGH_RANKER
{// 10934
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ int RankingType;
};


struct PACKET_IZ_RESET_EFFECT_HIGH_RANKER
{// 10935
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
};


struct PACKET_HZ_PERSONAL_INFORMATION_PHL
{// 10936
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	enum {
		FLAGMASK_WORLDENTRANCE = 1,
		FLAGMASK_FORCENOTIFY   = 2,
	};
	/* this+ 8 */ unsigned char flag;
	enum {
		PAYTYPEMASK_FREE    = 0,
		PAYTYPEMASK_PREMIUM = 4,
		PAYTYPEMASK_BILLING = 8,
	};
	/* this+ 9 */ int PayType;
	/* this+13 */ int MaxStoreCnt;
	/* this+17 */ int Exp;
	/* this+21 */ int Death;
	/* this+25 */ int Drop;
};


struct PACKET_HZ_PERSONAL_INFORMATION_THAI
{// 10937
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ int isPCBang;
	/* this+12 */ short PremiumType2;
	enum {
		FLAGMASK_WORLDENTRANCE = 1,
		FLAGMASK_FORCENOTIFY   = 2,
	};
	/* this+14 */ unsigned char flag;
	/* this+15 */ int MaxStoreCnt;
	/* this+19 */ int Exp;
	/* this+23 */ int Death;
	/* this+27 */ int Drop;
};


struct PACKET_HZ_PERSONAL_INFORMATION_TW
{// 10939
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	enum {
		FLAGMASK_WORLDENTRANCE = 1,
		FLAGMASK_FORCENOTIFY   = 2,
	};
	/* this+ 8 */ unsigned char flag;
	/* this+ 9 */ int Exp;
	/* this+13 */ int Death;
	/* this+17 */ int Drop;
	/* this+21 */ int MaxStoreCnt;
};


struct PACKET_IZ_RELAY_NOTIFY
{// 10940
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE Data[]; // TODO
};


struct PACKET_HZ_PERSONAL_INFORMATION_INDONESIA
{// 10947
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE Data[]; //TODO
};


struct PACKET_HZ_LOGON_INDONESIA
{// 10948
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char ID[24];
	/* this+34 */ unsigned long TotalUsingTime;
	/* this+38 */ int selectedCharNum;
	/* this+42 */ unsigned char Sex;
	/* this+43 */ bool bAuth;
};


///////////////////////////////////////
#pragma pack(pop)
