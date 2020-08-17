#pragma once
#include "Struct.h" // EQUIPSLOTINFO
#pragma pack(push,1)
///////////////////////////////////////


enum
{
	HEADER_CA_LOGIN                                = 100,
	HEADER_CH_ENTER                                = 101,
	HEADER_CH_SELECT_CHAR                          = 102,
	HEADER_CH_MAKE_CHAR                            = 103,
	HEADER_CH_DELETE_CHAR                          = 104,
	HEADER_AC_ACCEPT_LOGIN                         = 105,
	HEADER_AC_REFUSE_LOGIN                         = 106,
	HEADER_HC_ACCEPT_ENTER                         = 107,
	HEADER_HC_REFUSE_ENTER                         = 108,
	HEADER_HC_ACCEPT_MAKECHAR                      = 109,
	HEADER_HC_REFUSE_MAKECHAR                      = 110,
	HEADER_HC_ACCEPT_DELETECHAR                    = 111,
	HEADER_HC_REFUSE_DELETECHAR                    = 112,
	HEADER_HC_NOTIFY_ZONESVR                       = 113,
	HEADER_CZ_ENTER                                = 114,
	HEADER_ZC_ACCEPT_ENTER                         = 115,
	HEADER_ZC_REFUSE_ENTER                         = 116,
	HEADER_ZC_NOTIFY_INITCHAR                      = 117,
	HEADER_ZC_NOTIFY_UPDATECHAR                    = 118,
	HEADER_ZC_NOTIFY_UPDATEPLAYER                  = 119,
	HEADER_ZC_NOTIFY_STANDENTRY                    = 120,
	HEADER_ZC_NOTIFY_NEWENTRY                      = 121,
	HEADER_ZC_NOTIFY_ACTENTRY                      = 122,
	HEADER_ZC_NOTIFY_MOVEENTRY                     = 123,
	HEADER_ZC_NOTIFY_STANDENTRY_NPC                = 124,
	HEADER_CZ_NOTIFY_ACTORINIT                     = 125,
	HEADER_CZ_REQUEST_TIME                         = 126,
	HEADER_ZC_NOTIFY_TIME                          = 127,
	HEADER_ZC_NOTIFY_VANISH                        = 128,
	HEADER_SC_NOTIFY_BAN                           = 129,
	HEADER_CZ_REQUEST_QUIT                         = 130,
	HEADER_ZC_ACCEPT_QUIT                          = 131,
	HEADER_ZC_REFUSE_QUIT                          = 132,
	HEADER_CZ_REQUEST_MOVE                         = 133,
	HEADER_ZC_NOTIFY_MOVE                          = 134,
	HEADER_ZC_NOTIFY_PLAYERMOVE                    = 135,
	HEADER_ZC_STOPMOVE                             = 136,
	HEADER_CZ_REQUEST_ACT                          = 137,
	HEADER_ZC_NOTIFY_ACT                           = 138,
	HEADER_ZC_NOTIFY_ACT_POSITION                  = 139,
	HEADER_CZ_REQUEST_CHAT                         = 140,
	HEADER_ZC_NOTIFY_CHAT                          = 141,
	HEADER_ZC_NOTIFY_PLAYERCHAT                    = 142,
	HEADER_SERVER_ENTRY_ACK                        = 143,
	HEADER_CZ_CONTACTNPC                           = 144,
	HEADER_ZC_NPCACK_MAPMOVE                       = 145,
	HEADER_ZC_NPCACK_SERVERMOVE                    = 146,
	HEADER_ZC_NPCACK_ENABLE                        = 147,
	HEADER_CZ_REQNAME                              = 148,
	HEADER_ZC_ACK_REQNAME                          = 149,
	HEADER_CZ_WHISPER                              = 150,
	HEADER_ZC_WHISPER                              = 151,
	HEADER_ZC_ACK_WHISPER                          = 152,
	HEADER_CZ_BROADCAST                            = 153,
	HEADER_ZC_BROADCAST                            = 154,
	HEADER_CZ_CHANGE_DIRECTION                     = 155,
	HEADER_ZC_CHANGE_DIRECTION                     = 156,
	HEADER_ZC_ITEM_ENTRY                           = 157,
	HEADER_ZC_ITEM_FALL_ENTRY                      = 158,
	HEADER_CZ_ITEM_PICKUP                          = 159,
	HEADER_ZC_ITEM_PICKUP_ACK                      = 160,
	HEADER_ZC_ITEM_DISAPPEAR                       = 161,
	HEADER_CZ_ITEM_THROW                           = 162,
	HEADER_ZC_NORMAL_ITEMLIST                      = 163,
	HEADER_ZC_EQUIPMENT_ITEMLIST                   = 164,
	HEADER_ZC_STORE_NORMAL_ITEMLIST                = 165,
	HEADER_ZC_STORE_EQUIPMENT_ITEMLIST             = 166,
	HEADER_CZ_USE_ITEM                             = 167,
	HEADER_ZC_USE_ITEM_ACK                         = 168,
	HEADER_CZ_REQ_WEAR_EQUIP                       = 169,
	HEADER_ZC_REQ_WEAR_EQUIP_ACK                   = 170,
	HEADER_CZ_REQ_TAKEOFF_EQUIP                    = 171,
	HEADER_ZC_REQ_TAKEOFF_EQUIP_ACK                = 172,
	HEADER_CZ_REQ_ITEM_EXPLANATION_BYNAME          = 173,
	HEADER_ZC_REQ_ITEM_EXPLANATION_ACK             = 174,
	HEADER_ZC_ITEM_THROW_ACK                       = 175,
	HEADER_ZC_PAR_CHANGE                           = 176,
	HEADER_ZC_LONGPAR_CHANGE                       = 177,
	HEADER_CZ_RESTART                              = 178,
	HEADER_ZC_RESTART_ACK                          = 179,
	HEADER_ZC_SAY_DIALOG                           = 180,
	HEADER_ZC_WAIT_DIALOG                          = 181,
	HEADER_ZC_CLOSE_DIALOG                         = 182,
	HEADER_ZC_MENU_LIST                            = 183,
	HEADER_CZ_CHOOSE_MENU                          = 184,
	HEADER_CZ_REQ_NEXT_SCRIPT                      = 185,
	HEADER_CZ_REQ_STATUS                           = 186,
	HEADER_CZ_STATUS_CHANGE                        = 187,
	HEADER_ZC_STATUS_CHANGE_ACK                    = 188,
	HEADER_ZC_STATUS                               = 189,
	HEADER_ZC_STATUS_CHANGE                        = 190,
	HEADER_CZ_REQ_EMOTION                          = 191,
	HEADER_ZC_EMOTION                              = 192,
	HEADER_CZ_REQ_USER_COUNT                       = 193,
	HEADER_ZC_USER_COUNT                           = 194,
	HEADER_ZC_SPRITE_CHANGE                        = 195,
	HEADER_ZC_SELECT_DEALTYPE                      = 196,
	HEADER_CZ_ACK_SELECT_DEALTYPE                  = 197,
	HEADER_ZC_PC_PURCHASE_ITEMLIST                 = 198,
	HEADER_ZC_PC_SELL_ITEMLIST                     = 199,
	HEADER_CZ_PC_PURCHASE_ITEMLIST                 = 200,
	HEADER_CZ_PC_SELL_ITEMLIST                     = 201,
	HEADER_ZC_PC_PURCHASE_RESULT                   = 202,
	HEADER_ZC_PC_SELL_RESULT                       = 203,
	HEADER_CZ_DISCONNECT_CHARACTER                 = 204,
	HEADER_ZC_ACK_DISCONNECT_CHARACTER             = 205,
	HEADER_CZ_DISCONNECT_ALL_CHARACTER             = 206,
	HEADER_CZ_SETTING_WHISPER_PC                   = 207,
	HEADER_CZ_SETTING_WHISPER_STATE                = 208,
	HEADER_ZC_SETTING_WHISPER_PC                   = 209,
	HEADER_ZC_SETTING_WHISPER_STATE                = 210,
	HEADER_CZ_REQ_WHISPER_LIST                     = 211,
	HEADER_ZC_WHISPER_LIST                         = 212,
	HEADER_CZ_CREATE_CHATROOM                      = 213,
	HEADER_ZC_ACK_CREATE_CHATROOM                  = 214,
	HEADER_ZC_ROOM_NEWENTRY                        = 215,
	HEADER_ZC_DESTROY_ROOM                         = 216,
	HEADER_CZ_REQ_ENTER_ROOM                       = 217,
	HEADER_ZC_REFUSE_ENTER_ROOM                    = 218,
	HEADER_ZC_ENTER_ROOM                           = 219,
	HEADER_ZC_MEMBER_NEWENTRY                      = 220,
	HEADER_ZC_MEMBER_EXIT                          = 221,
	HEADER_CZ_CHANGE_CHATROOM                      = 222,
	HEADER_ZC_CHANGE_CHATROOM                      = 223,
	HEADER_CZ_REQ_ROLE_CHANGE                      = 224,
	HEADER_ZC_ROLE_CHANGE                          = 225,
	HEADER_CZ_REQ_EXPEL_MEMBER                     = 226,
	HEADER_CZ_EXIT_ROOM                            = 227,
	HEADER_CZ_REQ_EXCHANGE_ITEM                    = 228,
	HEADER_ZC_REQ_EXCHANGE_ITEM                    = 229,
	HEADER_CZ_ACK_EXCHANGE_ITEM                    = 230,
	HEADER_ZC_ACK_EXCHANGE_ITEM                    = 231,
	HEADER_CZ_ADD_EXCHANGE_ITEM                    = 232,
	HEADER_ZC_ADD_EXCHANGE_ITEM                    = 233,
	HEADER_ZC_ACK_ADD_EXCHANGE_ITEM                = 234,
	HEADER_CZ_CONCLUDE_EXCHANGE_ITEM               = 235,
	HEADER_ZC_CONCLUDE_EXCHANGE_ITEM               = 236,
	HEADER_CZ_CANCEL_EXCHANGE_ITEM                 = 237,
	HEADER_ZC_CANCEL_EXCHANGE_ITEM                 = 238,
	HEADER_CZ_EXEC_EXCHANGE_ITEM                   = 239,
	HEADER_ZC_EXEC_EXCHANGE_ITEM                   = 240,
	HEADER_ZC_EXCHANGEITEM_UNDO                    = 241,
	HEADER_ZC_NOTIFY_STOREITEM_COUNTINFO           = 242,
	HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_STORE         = 243,
	HEADER_ZC_ADD_ITEM_TO_STORE                    = 244,
	HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_BODY         = 245,
	HEADER_ZC_DELETE_ITEM_FROM_STORE               = 246,
	HEADER_CZ_CLOSE_STORE                          = 247,
	HEADER_ZC_CLOSE_STORE                          = 248,
	HEADER_CZ_MAKE_GROUP                           = 249,
	HEADER_ZC_ACK_MAKE_GROUP                       = 250,
	HEADER_ZC_GROUP_LIST                           = 251,
	HEADER_CZ_REQ_JOIN_GROUP                       = 252,
	HEADER_ZC_ACK_REQ_JOIN_GROUP                   = 253,
	HEADER_ZC_REQ_JOIN_GROUP                       = 254,
	HEADER_CZ_JOIN_GROUP                           = 255,
	HEADER_CZ_REQ_LEAVE_GROUP                      = 256,
	HEADER_ZC_GROUPINFO_CHANGE                     = 257,
	HEADER_CZ_CHANGE_GROUPEXPOPTION                = 258,
	HEADER_CZ_REQ_EXPEL_GROUP_MEMBER               = 259,
	HEADER_ZC_ADD_MEMBER_TO_GROUP                  = 260,
	HEADER_ZC_DELETE_MEMBER_FROM_GROUP             = 261,
	HEADER_ZC_NOTIFY_HP_TO_GROUPM                  = 262,
	HEADER_ZC_NOTIFY_POSITION_TO_GROUPM            = 263,
	HEADER_CZ_REQUEST_CHAT_PARTY                   = 264,
	HEADER_ZC_NOTIFY_CHAT_PARTY                    = 265,
	HEADER_ZC_MVP_GETTING_ITEM                     = 266,
	HEADER_ZC_MVP_GETTING_SPECIAL_EXP              = 267,
	HEADER_ZC_MVP                                  = 268,
	HEADER_ZC_THROW_MVPITEM                        = 269,
	HEADER_ZC_SKILLINFO_UPDATE                     = 270,
	HEADER_ZC_SKILLINFO_LIST                       = 271,
	HEADER_ZC_ACK_TOUSESKILL                       = 272,
	HEADER_ZC_ADD_SKILL                            = 273,
	HEADER_CZ_UPGRADE_SKILLLEVEL                   = 274,
	HEADER_CZ_USE_SKILL                            = 275,
	HEADER_ZC_NOTIFY_SKILL                         = 276,
	HEADER_ZC_NOTIFY_SKILL_POSITION                = 277,
	HEADER_CZ_USE_SKILL_TOGROUND                   = 278,
	HEADER_ZC_NOTIFY_GROUNDSKILL                   = 279,
	HEADER_CZ_CANCEL_LOCKON                        = 280,
	HEADER_ZC_STATE_CHANGE                         = 281,
	HEADER_ZC_USE_SKILL                            = 282,
	HEADER_CZ_SELECT_WARPPOINT                     = 283,
	HEADER_ZC_WARPLIST                             = 284,
	HEADER_CZ_REMEMBER_WARPPOINT                   = 285,
	HEADER_ZC_ACK_REMEMBER_WARPPOINT               = 286,
	HEADER_ZC_SKILL_ENTRY                          = 287,
	HEADER_ZC_SKILL_DISAPPEAR                      = 288,
	HEADER_ZC_NOTIFY_CARTITEM_COUNTINFO            = 289,
	HEADER_ZC_CART_EQUIPMENT_ITEMLIST              = 290,
	HEADER_ZC_CART_NORMAL_ITEMLIST                 = 291,
	HEADER_ZC_ADD_ITEM_TO_CART                     = 292,
	HEADER_ZC_DELETE_ITEM_FROM_CART                = 293,
	HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_CART          = 294,
	HEADER_CZ_MOVE_ITEM_FROM_CART_TO_BODY          = 295,
	HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_CART         = 296,
	HEADER_CZ_MOVE_ITEM_FROM_CART_TO_STORE         = 297,
	HEADER_CZ_REQ_CARTOFF                          = 298,
	HEADER_ZC_CARTOFF                              = 299,
	HEADER_ZC_ACK_ADDITEM_TO_CART                  = 300,
	HEADER_ZC_OPENSTORE                            = 301,
	HEADER_CZ_REQ_CLOSESTORE                       = 302,
	HEADER_CZ_REQ_OPENSTORE                        = 303,
	HEADER_CZ_REQ_BUY_FROMMC                       = 304,
	HEADER_ZC_STORE_ENTRY                          = 305,
	HEADER_ZC_DISAPPEAR_ENTRY                      = 306,
	HEADER_ZC_PC_PURCHASE_ITEMLIST_FROMMC          = 307,
	HEADER_CZ_PC_PURCHASE_ITEMLIST_FROMMC          = 308,
	HEADER_ZC_PC_PURCHASE_RESULT_FROMMC            = 309,
	HEADER_ZC_PC_PURCHASE_MYITEMLIST               = 310,
	HEADER_ZC_DELETEITEM_FROM_MCSTORE              = 311,
	HEADER_CZ_PKMODE_CHANGE                        = 312,
	HEADER_ZC_ATTACK_FAILURE_FOR_DISTANCE          = 313,
	HEADER_ZC_ATTACK_RANGE                         = 314,
	HEADER_ZC_ACTION_FAILURE                       = 315,
	HEADER_ZC_EQUIP_ARROW                          = 316,
	HEADER_ZC_RECOVERY                             = 317,
	HEADER_ZC_USESKILL_ACK                         = 318,
	HEADER_CZ_ITEM_CREATE                          = 319,
	HEADER_CZ_MOVETO_MAP                           = 320,
	HEADER_ZC_COUPLESTATUS                         = 321,
	HEADER_ZC_OPEN_EDITDLG                         = 322,
	HEADER_CZ_INPUT_EDITDLG                        = 323,
	HEADER_ZC_COMPASS                              = 324,
	HEADER_ZC_SHOW_IMAGE                           = 325,
	HEADER_CZ_CLOSE_DIALOG                         = 326,
	HEADER_ZC_AUTORUN_SKILL                        = 327,
	HEADER_ZC_RESURRECTION                         = 328,
	HEADER_CZ_REQ_GIVE_MANNER_POINT                = 329,
	HEADER_ZC_ACK_GIVE_MANNER_POINT                = 330,
	HEADER_ZC_NOTIFY_MANNER_POINT_GIVEN            = 331,
	HEADER_ZC_MYGUILD_BASIC_INFO                   = 332,
	HEADER_CZ_REQ_GUILD_MENUINTERFACE              = 333,
	HEADER_ZC_ACK_GUILD_MENUINTERFACE              = 334,
	HEADER_CZ_REQ_GUILD_MENU                       = 335,
	HEADER_ZC_GUILD_INFO                           = 336,
	HEADER_CZ_REQ_GUILD_EMBLEM_IMG                 = 337,
	HEADER_ZC_GUILD_EMBLEM_IMG                     = 338,
	HEADER_CZ_REGISTER_GUILD_EMBLEM_IMG            = 339,
	HEADER_ZC_MEMBERMGR_INFO                       = 340,
	HEADER_CZ_REQ_CHANGE_MEMBERPOS                 = 341,
	HEADER_ZC_ACK_REQ_CHANGE_MEMBERS               = 342,
	HEADER_CZ_REQ_OPEN_MEMBER_INFO                 = 343,
	XXXXX_HEADER_ZC_ACK_OPEN_MEMBER_INFO           = 344,
	HEADER_CZ_REQ_LEAVE_GUILD                      = 345,
	HEADER_ZC_ACK_LEAVE_GUILD                      = 346,
	HEADER_CZ_REQ_BAN_GUILD                        = 347,
	HEADER_ZC_ACK_BAN_GUILD                        = 348,
	HEADER_CZ_REQ_DISORGANIZE_GUILD                = 349,
	HEADER_ZC_ACK_DISORGANIZE_GUILD_RESULT         = 350,
	HEADER_ZC_ACK_DISORGANIZE_GUILD                = 351,
	HEADER_ZC_POSITION_INFO                        = 352,
	HEADER_CZ_REG_CHANGE_GUILD_POSITIONINFO        = 353,
	HEADER_ZC_GUILD_SKILLINFO                      = 354,
	HEADER_ZC_BAN_LIST                             = 355,
	HEADER_ZC_OTHER_GUILD_LIST                     = 356,
	HEADER_CZ_REQ_MAKE_GUILD                       = 357,
	HEADER_ZC_POSITION_ID_NAME_INFO                = 358,
	HEADER_ZC_RESULT_MAKE_GUILD                    = 359,
	HEADER_CZ_REQ_JOIN_GUILD                       = 360,
	HEADER_ZC_ACK_REQ_JOIN_GUILD                   = 361,
	HEADER_ZC_REQ_JOIN_GUILD                       = 362,
	HEADER_CZ_JOIN_GUILD                           = 363,
	HEADER_ZC_UPDATE_GDID                          = 364,
	HEADER_ZC_UPDATE_CHARSTAT                      = 365,
	HEADER_CZ_GUILD_NOTICE                         = 366,
	HEADER_ZC_GUILD_NOTICE                         = 367,
	HEADER_CZ_REQ_ALLY_GUILD                       = 368,
	HEADER_ZC_REQ_ALLY_GUILD                       = 369,
	HEADER_CZ_ALLY_GUILD                           = 370,
	HEADER_ZC_ACK_REQ_ALLY_GUILD                   = 371,
	HEADER_ZC_ACK_CHANGE_GUILD_POSITIONINFO        = 372,
	HEADER_CZ_REQ_GUILD_MEMBER_INFO                = 373,
	HEADER_ZC_ACK_GUILD_MEMBER_INFO                = 374,
	HEADER_ZC_ITEMIDENTIFY_LIST                    = 375,
	HEADER_CZ_REQ_ITEMIDENTIFY                     = 376,
	HEADER_ZC_ACK_ITEMIDENTIFY                     = 377,
	HEADER_CZ_REQ_ITEMCOMPOSITION_LIST             = 378,
	HEADER_ZC_ITEMCOMPOSITION_LIST                 = 379,
	HEADER_CZ_REQ_ITEMCOMPOSITION                  = 380,
	HEADER_ZC_ACK_ITEMCOMPOSITION                  = 381,
	HEADER_CZ_GUILD_CHAT                           = 382,
	HEADER_ZC_GUILD_CHAT                           = 383,
	HEADER_CZ_REQ_HOSTILE_GUILD                    = 384,
	HEADER_ZC_ACK_REQ_HOSTILE_GUILD                = 385,
	HEADER_ZC_MEMBER_ADD                           = 386,
	HEADER_CZ_REQ_DELETE_RELATED_GUILD             = 387,
	HEADER_ZC_DELETE_RELATED_GUILD                 = 388,
	HEADER_ZC_ADD_RELATED_GUILD                    = 389,
	HEADER_COLLECTORDEAD                           = 390,
	HEADER_PING                                    = 391,
	HEADER_ZC_ACK_ITEMREFINING                     = 392,
	HEADER_ZC_NOTIFY_MAPINFO                       = 393,
	HEADER_CZ_REQ_DISCONNECT                       = 394,
	HEADER_ZC_ACK_REQ_DISCONNECT                   = 395,
	HEADER_ZC_MONSTER_INFO                         = 396,
	HEADER_ZC_MAKABLEITEMLIST                      = 397,
	HEADER_CZ_REQMAKINGITEM                        = 398,
	HEADER_ZC_ACK_REQMAKINGITEM                    = 399,
	HEADER_CZ_USE_SKILL_TOGROUND_WITHTALKBOX       = 400,
	HEADER_ZC_TALKBOX_CHATCONTENTS                 = 401,
	HEADER_ZC_UPDATE_MAPINFO                       = 402,
	HEADER_CZ_REQNAME_BYGID                        = 403,
	HEADER_ZC_ACK_REQNAME_BYGID                    = 404,
	HEADER_ZC_ACK_REQNAMEALL                       = 405,
	HEADER_ZC_MSG_STATE_CHANGE                     = 406,
	HEADER_CZ_RESET                                = 407,
	HEADER_CZ_CHANGE_MAPTYPE                       = 408,
	HEADER_ZC_NOTIFY_MAPPROPERTY                   = 409,
	HEADER_ZC_NOTIFY_RANKING                       = 410,
	HEADER_ZC_NOTIFY_EFFECT                        = 411,
	HEADER_CZ_LOCALBROADCAST                       = 412,
	HEADER_CZ_CHANGE_EFFECTSTATE                   = 413,
	HEADER_ZC_START_CAPTURE                        = 414,
	HEADER_CZ_TRYCAPTURE_MONSTER                   = 415,
	HEADER_ZC_TRYCAPTURE_MONSTER                   = 416,
	HEADER_CZ_COMMAND_PET                          = 417,
	HEADER_ZC_PROPERTY_PET                         = 418,
	HEADER_ZC_FEED_PET                             = 419,
	HEADER_ZC_CHANGESTATE_PET                      = 420,
	HEADER_CZ_RENAME_PET                           = 421,
	HEADER_ZC_PETEGG_LIST                          = 422,
	HEADER_CZ_SELECT_PETEGG                        = 423,
	HEADER_CZ_PETEGG_INFO                          = 424,
	HEADER_CZ_PET_ACT                              = 425,
	HEADER_ZC_PET_ACT                              = 426,
	HEADER_ZC_PAR_CHANGE_USER                      = 427,
	HEADER_ZC_SKILL_UPDATE                         = 428,
	HEADER_ZC_MAKINGARROW_LIST                     = 429,
	HEADER_CZ_REQ_MAKINGARROW                      = 430,
	HEADER_CZ_REQ_CHANGECART                       = 431,
	HEADER_ZC_NPCSPRITE_CHANGE                     = 432,
	HEADER_ZC_SHOWDIGIT                            = 433,
	HEADER_CZ_REQ_OPENSTORE2                       = 434,
	HEADER_ZC_SHOW_IMAGE2                          = 435,
	HEADER_ZC_CHANGE_GUILD                         = 436,
	HEADER_SC_BILLING_INFO                         = 437,
	HEADER_ZC_GUILD_INFO2                          = 438,
	HEADER_CZ_GUILD_ZENY                           = 439,
	HEADER_ZC_GUILD_ZENY_ACK                       = 440,
	HEADER_ZC_DISPEL                               = 441,
	HEADER_CZ_REMOVE_AID                           = 442,
	HEADER_CZ_SHIFT                                = 443,
	HEADER_CZ_RECALL                               = 444,
	HEADER_CZ_RECALL_GID                           = 445,
	HEADER_AC_ASK_PNGAMEROOM                       = 446,
	HEADER_CA_REPLY_PNGAMEROOM                     = 447,
	HEADER_CZ_REQ_REMAINTIME                       = 448,
	HEADER_ZC_REPLY_REMAINTIME                     = 449,
	HEADER_ZC_INFO_REMAINTIME                      = 450,
	HEADER_ZC_BROADCAST2                           = 451,
	HEADER_ZC_ADD_ITEM_TO_STORE2                   = 452,
	HEADER_ZC_ADD_ITEM_TO_CART2                    = 453,
	HEADER_CS_REQ_ENCRYPTION                       = 454,
	HEADER_SC_ACK_ENCRYPTION                       = 455,
	HEADER_ZC_USE_ITEM_ACK2                        = 456,
	HEADER_ZC_SKILL_ENTRY2                         = 457,
	HEADER_CZ_REQMAKINGHOMUN                       = 458,
	HEADER_CZ_MONSTER_TALK                         = 459,
	HEADER_ZC_MONSTER_TALK                         = 460,
	HEADER_ZC_AUTOSPELLLIST                        = 461,
	HEADER_CZ_SELECTAUTOSPELL                      = 462,
	HEADER_ZC_DEVOTIONLIST                         = 463,
	HEADER_ZC_SPIRITS                              = 464,
	HEADER_ZC_BLADESTOP                            = 465,
	HEADER_ZC_COMBODELAY                           = 466,
	HEADER_ZC_SOUND                                = 467,
	HEADER_ZC_OPEN_EDITDLGSTR                      = 468,
	HEADER_CZ_INPUT_EDITDLGSTR                     = 469,
	HEADER_ZC_NOTIFY_MAPPROPERTY2                  = 470,
	HEADER_ZC_SPRITE_CHANGE2                       = 471,
	HEADER_ZC_NOTIFY_STANDENTRY2                   = 472,
	HEADER_ZC_NOTIFY_NEWENTRY2                     = 473,
	HEADER_ZC_NOTIFY_MOVEENTRY2                    = 474,
	HEADER_CA_REQ_HASH                             = 475,
	HEADER_AC_ACK_HASH                             = 476,
	HEADER_CA_LOGIN2                               = 477,
	HEADER_ZC_NOTIFY_SKILL2                        = 478,
	HEADER_CZ_REQ_ACCOUNTNAME                      = 479,
	HEADER_ZC_ACK_ACCOUNTNAME                      = 480,
	HEADER_ZC_SPIRITS2                             = 481,
	HEADER_ZC_REQ_COUPLE                           = 482,
	HEADER_CZ_JOIN_COUPLE                          = 483,
	HEADER_ZC_START_COUPLE                         = 484,
	HEADER_CZ_REQ_JOIN_COUPLE                      = 485,
	HEADER_ZC_COUPLENAME                           = 486,
	HEADER_CZ_DORIDORI                             = 487,
	HEADER_CZ_MAKE_GROUP2                          = 488,
	HEADER_ZC_ADD_MEMBER_TO_GROUP2                 = 489,
	HEADER_ZC_CONGRATULATION                       = 490,
	HEADER_ZC_NOTIFY_POSITION_TO_GUILDM            = 491,
	HEADER_ZC_GUILD_MEMBER_MAP_CHANGE              = 492,
	HEADER_CZ_CHOPOKGI                             = 493,
	HEADER_ZC_NORMAL_ITEMLIST2                     = 494,
	HEADER_ZC_CART_NORMAL_ITEMLIST2                = 495,
	HEADER_ZC_STORE_NORMAL_ITEMLIST2               = 496,
	HEADER_AC_NOTIFY_ERROR                         = 497,
	HEADER_ZC_UPDATE_CHARSTAT2                     = 498,
	HEADER_ZC_NOTIFY_EFFECT2                       = 499,
	HEADER_ZC_REQ_EXCHANGE_ITEM2                   = 500,
	HEADER_ZC_ACK_EXCHANGE_ITEM2                   = 501,
	HEADER_ZC_REQ_BABY                             = 502,
	HEADER_CZ_JOIN_BABY                            = 503,
	HEADER_ZC_START_BABY                           = 504,
	HEADER_CZ_REQ_JOIN_BABY                        = 505,
	HEADER_CA_LOGIN3                               = 506,
	HEADER_CH_DELETE_CHAR2                         = 507,
	HEADER_ZC_REPAIRITEMLIST                       = 508,
	HEADER_CZ_REQ_ITEMREPAIR                       = 509,
	HEADER_ZC_ACK_ITEMREPAIR                       = 510,
	HEADER_ZC_HIGHJUMP                             = 511,
	HEADER_CA_CONNECT_INFO_CHANGED                 = 512,
	HEADER_ZC_FRIENDS_LIST                         = 513,
	HEADER_CZ_ADD_FRIENDS                          = 514,
	HEADER_CZ_DELETE_FRIENDS                       = 515,
	HEADER_CA_EXE_HASHCHECK                        = 516,
	HEADER_ZC_DIVORCE                              = 517,
	HEADER_ZC_FRIENDS_STATE                        = 518,
	HEADER_ZC_REQ_ADD_FRIENDS                      = 519,
	HEADER_CZ_ACK_REQ_ADD_FRIENDS                  = 520,
	HEADER_ZC_ADD_FRIENDS_LIST                     = 521,
	HEADER_ZC_DELETE_FRIENDS                       = 522,
	HEADER_CH_EXE_HASHCHECK                        = 523,
	HEADER_CZ_EXE_HASHCHECK                        = 524,
	HEADER_HC_BLOCK_CHARACTER                      = 525,
	HEADER_ZC_STARSKILL                            = 526,
	HEADER_CZ_REQ_PVPPOINT                         = 527,
	HEADER_ZC_ACK_PVPPOINT                         = 528,
	HEADER_ZH_MOVE_PVPWORLD                        = 529,
	HEADER_CZ_REQ_GIVE_MANNER_BYNAME               = 530,
	HEADER_CZ_REQ_STATUS_GM                        = 531,
	HEADER_ZC_ACK_STATUS_GM                        = 532,
	HEADER_ZC_SKILLMSG                             = 533,
	HEADER_ZC_BABYMSG                              = 534,
	HEADER_CZ_BLACKSMITH_RANK                      = 535,
	HEADER_CZ_ALCHEMIST_RANK                       = 536,
	HEADER_ZC_BLACKSMITH_RANK                      = 537,
	HEADER_ZC_ALCHEMIST_RANK                       = 538,
	HEADER_ZC_BLACKSMITH_POINT                     = 539,
	HEADER_ZC_ALCHEMIST_POINT                      = 540,
	HEADER_CZ_LESSEFFECT                           = 541,
	HEADER_ZC_LESSEFFECT                           = 542,
	HEADER_ZC_NOTIFY_PKINFO                        = 543,
	HEADER_ZC_NOTIFY_CRAZYKILLER                   = 544,
	HEADER_ZC_NOTIFY_WEAPONITEMLIST                = 545,
	HEADER_CZ_REQ_WEAPONREFINE                     = 546,
	HEADER_ZC_ACK_WEAPONREFINE                     = 547,
	HEADER_ZC_TAEKWON_POINT                        = 548,
	HEADER_CZ_TAEKWON_RANK                         = 549,
	HEADER_ZC_TAEKWON_RANK                         = 550,
	HEADER_ZC_GAME_GUARD                           = 551,
	HEADER_CZ_ACK_GAME_GUARD                       = 552,
	HEADER_ZC_STATE_CHANGE3                        = 553,
	HEADER_ZC_NOTIFY_STANDENTRY3                   = 554,
	HEADER_ZC_NOTIFY_NEWENTRY3                     = 555,
	HEADER_ZC_NOTIFY_MOVEENTRY3                    = 556,
	HEADER_CZ_COMMAND_MER                          = 557,
	HEADER_ZC_PROPERTY_HOMUN                       = 558,
	HEADER_ZC_FEED_MER                             = 559,
	HEADER_ZC_CHANGESTATE_MER                      = 560,
	HEADER_CZ_RENAME_MER                           = 561,
	HEADER_CZ_REQUEST_MOVENPC                      = 562,
	HEADER_CZ_REQUEST_ACTNPC                       = 563,
	HEADER_CZ_REQUEST_MOVETOOWNER                  = 564,
	HEADER_ZC_HOSKILLINFO_LIST                     = 565,
	HEADER_ZC_KILLER_POINT                         = 566,
	HEADER_CZ_KILLER_RANK                          = 567,
	HEADER_ZC_KILLER_RANK                          = 568,
	HEADER_ZC_HOSKILLINFO_UPDATE                   = 569,
	HEADER_ZC_REQ_STORE_PASSWORD                   = 570,
	HEADER_CZ_ACK_STORE_PASSWORD                   = 571,
	HEADER_ZC_RESULT_STORE_PASSWORD                = 572,
	HEADER_AC_EVENT_RESULT                         = 573,
	HEADER_HC_REQUEST_CHARACTER_PASSWORD           = 574,
	HEADER_CZ_MAIL_GET_LIST                        = 575,
	HEADER_ZC_MAIL_REQ_GET_LIST                    = 576,
	HEADER_CZ_MAIL_OPEN                            = 577,
	HEADER_ZC_MAIL_REQ_OPEN                        = 578,
	HEADER_CZ_MAIL_DELETE                          = 579,
	HEADER_CZ_MAIL_GET_ITEM                        = 580,
	HEADER_ZC_MAIL_REQ_GET_ITEM                    = 581,
	HEADER_CZ_MAIL_RESET_ITEM                      = 582,
	HEADER_CZ_MAIL_ADD_ITEM                        = 583,
	HEADER_CZ_MAIL_SEND                            = 584,
	HEADER_ZC_MAIL_REQ_SEND                        = 585,
	HEADER_ZC_MAIL_RECEIVE                         = 586,
	HEADER_CZ_AUCTION_CREATE                       = 587,
	HEADER_CZ_AUCTION_ADD_ITEM                     = 588,
	HEADER_CZ_AUCTION_ADD                          = 589,
	HEADER_CZ_AUCTION_ADD_CANCEL                   = 590,
	HEADER_CZ_AUCTION_BUY                          = 591,
	HEADER_ZC_AUCTION_RESULT                       = 592,
	HEADER_CZ_AUCTION_ITEM_SEARCH                  = 593,
	HEADER_ZC_AUCTION_ITEM_REQ_SEARCH              = 594,
	HEADER_ZC_STARPLACE                            = 595,
	HEADER_CZ_AGREE_STARPLACE                      = 596,
	HEADER_ZC_ACK_MAIL_ADD_ITEM                    = 597,
	HEADER_ZC_ACK_AUCTION_ADD_ITEM                 = 598,
	HEADER_ZC_ACK_MAIL_DELETE                      = 599,
	HEADER_CA_REQ_GAME_GUARD_CHECK                 = 600,
	HEADER_AC_ACK_GAME_GUARD                       = 601,
	HEADER_ZC_MAKINGITEM_LIST                      = 602,
	HEADER_CZ_REQ_MAKINGITEM                       = 603,
	HEADER_CZ_AUCTION_REQ_MY_INFO                  = 604,
	HEADER_CZ_AUCTION_REQ_MY_SELL_STOP             = 605,
	HEADER_ZC_AUCTION_ACK_MY_SELL_STOP             = 606,
	HEADER_ZC_AUCTION_WINDOWS                      = 607,
	HEADER_ZC_MAIL_WINDOWS                         = 608,
	HEADER_AC_REQ_LOGIN_OLDEKEY                    = 609,
	HEADER_AC_REQ_LOGIN_NEWEKEY                    = 610,
	HEADER_AC_REQ_LOGIN_CARDPASS                   = 611,
	HEADER_CA_ACK_LOGIN_OLDEKEY                    = 612,
	HEADER_CA_ACK_LOGIN_NEWEKEY                    = 613,
	HEADER_CA_ACK_LOGIN_CARDPASS                   = 614,
	HEADER_AC_ACK_EKEY_FAIL_NOTEXIST               = 615,
	HEADER_AC_ACK_EKEY_FAIL_NOTUSESEKEY            = 616,
	HEADER_AC_ACK_EKEY_FAIL_NOTUSEDEKEY            = 617,
	HEADER_AC_ACK_EKEY_FAIL_AUTHREFUSE             = 618,
	HEADER_AC_ACK_EKEY_FAIL_INPUTEKEY              = 619,
	HEADER_AC_ACK_EKEY_FAIL_NOTICE                 = 620,
	HEADER_AC_ACK_EKEY_FAIL_NEEDCARDPASS           = 621,
	HEADER_AC_ACK_AUTHEKEY_FAIL_NOTMATCHCARDPASS   = 622,
	HEADER_AC_ACK_FIRST_LOGIN                      = 623,
	HEADER_AC_REQ_LOGIN_ACCOUNT_INFO               = 624,
	HEADER_CA_ACK_LOGIN_ACCOUNT_INFO               = 625,
	HEADER_AC_ACK_PT_ID_INFO                       = 626,
	HEADER_CZ_REQ_MAIL_RETURN                      = 627,
	HEADER_ZC_ACK_MAIL_RETURN                      = 628,
	HEADER_CH_ENTER2                               = 629,
	HEADER_AC_ACCEPT_LOGIN2                        = 630,
	HEADER_CA_LOGIN_PCBANG                         = 631,
	HEADER_ZC_NOTIFY_PCBANG                        = 632,
	HEADER_CZ_HUNTINGLIST                          = 633,
	HEADER_ZC_HUNTINGLIST                          = 634,
	HEADER_ZC_PCBANG_EFFECT                        = 635,
	HEADER_CA_LOGIN4                               = 636,
	HEADER_ZC_PROPERTY_MERCE                       = 637,
	HEADER_ZC_SHANDA_PROTECT                       = 638,
	HEADER_CA_CLIENT_TYPE                          = 639,
	HEADER_ZC_GANGSI_POINT                         = 640,
	HEADER_CZ_GANGSI_RANK                          = 641,
	HEADER_ZC_GANGSI_RANK                          = 642,
	HEADER_ZC_AID                                  = 643,
	HEADER_ZC_NOTIFY_EFFECT3                       = 644,
	HEADER_ZC_DEATH_QUESTION                       = 645,
	HEADER_CZ_DEATH_QUESTION                       = 646,
	HEADER_ZC_PC_CASH_POINT_ITEMLIST               = 647,
	HEADER_CZ_PC_BUY_CASH_POINT_ITEM               = 648,
	HEADER_ZC_PC_CASH_POINT_UPDATE                 = 649,
	HEADER_ZC_NPC_SHOWEFST_UPDATE                  = 650,
	HEADER_HC_CHARNOTBEENSELECTED                  = 651,
	HEADER_CH_SELECT_CHAR_GOINGTOBEUSED            = 652,
	HEADER_CH_REQ_IS_VALID_CHARNAME                = 653,
	HEADER_HC_ACK_IS_VALID_CHARNAME                = 654,
	HEADER_CH_REQ_CHANGE_CHARNAME                  = 655,
	HEADER_HC_ACK_CHANGE_CHARNAME                  = 656,
	HEADER_ZC_MSG                                  = 657,
	HEADER_CZ_STANDING_RESURRECTION                = 658,
	HEADER_ZC_BOSS_INFO                            = 659,
	HEADER_ZC_READ_BOOK                            = 660,
	HEADER_ZC_EQUIPMENT_ITEMLIST2                  = 661,
	HEADER_ZC_STORE_EQUIPMENT_ITEMLIST2            = 662,
	HEADER_ZC_CART_EQUIPMENT_ITEMLIST2             = 663,
	HEADER_ZC_CASH_TIME_COUNTER                    = 664,
	HEADER_ZC_CASH_ITEM_DELETE                     = 665,
	HEADER_ZC_ITEM_PICKUP_ACK2                     = 666,
	HEADER_ZC_MER_INIT                             = 667,
	HEADER_ZC_MER_PROPERTY                         = 668,
	HEADER_ZC_MER_SKILLINFO_LIST                   = 669,
	HEADER_ZC_MER_SKILLINFO_UPDATE                 = 670,
	HEADER_CZ_MER_COMMAND                          = 671,
	UNUSED_HEADER_CZ_MER_USE_SKILL                 = 672,
	UNUSED_HEADER_CZ_MER_UPGRADE_SKILLLEVEL        = 673,
	HEADER_ZC_MER_PAR_CHANGE                       = 674,
	HEADER_ZC_GAMEGUARD_LINGO_KEY                  = 675,
	HEADER_CZ_GAMEGUARD_LINGO_READY                = 676,
	HEADER_CZ_KSY_EVENT                            = 677,
	HEADER_ZC_HACKSH_CPX_MSG                       = 678,
	HEADER_CZ_HACKSH_CPX_MSG                       = 679,
	HEADER_ZC_HACKSHIELD_CRC_MSG                   = 680,
	HEADER_CZ_HACKSHIELD_CRC_MSG                   = 681,
	HEADER_ZC_REQ_CASH_PASSWORD                    = 682,
	HEADER_CZ_ACK_CASH_PASSWORD                    = 683,
	HEADER_ZC_RESULT_CASH_PASSWORD                 = 684,
	HEADER_AC_REQUEST_SECOND_PASSWORD              = 685,
	HEADER_ZC_SRPACKET_INIT                        = 686,
	HEADER_CZ_SRPACKET_START                       = 687,
	HEADER_CA_LOGIN_CHANNEL                        = 688,
	HEADER_ZC_ALL_QUEST_LIST                       = 689,
	HEADER_ZC_ALL_QUEST_MISSION                    = 690,
	HEADER_ZC_ADD_QUEST                            = 691,
	HEADER_ZC_DEL_QUEST                            = 692,
	HEADER_ZC_UPDATE_MISSION_HUNT                  = 693,
	HEADER_CZ_ACTIVE_QUEST                         = 694,
	HEADER_ZC_ACTIVE_QUEST                         = 695,
	HEADER_ZC_ITEM_PICKUP_PARTY                    = 696,
	HEADER_ZC_SHORTCUT_KEY_LIST                    = 697,
	HEADER_CZ_SHORTCUT_KEY_CHANGE                  = 698,
	HEADER_ZC_EQUIPITEM_DAMAGED                    = 699,
	HEADER_ZC_NOTIFY_PCBANG_PLAYING_TIME           = 700,
	HEADER_ZC_SRCRYPTOR2_INIT                      = 701,
	HEADER_CZ_SRCRYPTOR2_START                     = 702,
	HEADER_ZC_SRPACKETR2_INIT                      = 703,
	HEADER_CZ_SRPACKETR2_START                     = 704,
	HEADER_ZC_NPC_CHAT                             = 705,
	HEADER_ZC_FORMATSTRING_MSG                     = 706,
	UNUSED_HEADER_CZ_FORMATSTRING_MSG_RES          = 707,
	HEADER_CZ_PARTY_JOIN_REQ                       = 708,
	HEADER_ZC_PARTY_JOIN_REQ_ACK                   = 709,
	HEADER_ZC_PARTY_JOIN_REQ                       = 710,
	HEADER_CZ_PARTY_JOIN_REQ_ACK                   = 711,
	HEADER_CZ_PARTY_CONFIG                         = 712,
	HEADER_ZC_PARTY_CONFIG                         = 713,
	HEADER_HC_REFUSE_SELECTCHAR                    = 714,
	HEADER_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO    = 715,
	HEADER_ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY  = 716,
	HEADER_ZC_MEMORIALDUNGEON_INFO                 = 717,
	HEADER_ZC_MEMORIALDUNGEON_NOTIFY               = 718,
	HEADER_CZ_MEMORIALDUNGEON_COMMAND              = 719,
	HEADER_ZC_EQUIPMENT_ITEMLIST3                  = 720,
	HEADER_ZC_STORE_EQUIPMENT_ITEMLIST3            = 721,
	HEADER_ZC_CART_EQUIPMENT_ITEMLIST3             = 722,
	HEADER_ZC_NOTIFY_BIND_ON_EQUIP                 = 723,
	HEADER_ZC_ITEM_PICKUP_ACK3                     = 724,
	HEADER_ZC_ISVR_DISCONNECT                      = 725,
	HEADER_CZ_EQUIPWIN_MICROSCOPE                  = 726,
	HEADER_ZC_EQUIPWIN_MICROSCOPE                  = 727,
	HEADER_CZ_CONFIG                               = 728,
	HEADER_ZC_CONFIG                               = 729,
	HEADER_ZC_CONFIG_NOTIFY                        = 730,
	HEADER_CZ_BATTLEFIELD_CHAT                     = 731,
	HEADER_ZC_BATTLEFIELD_CHAT                     = 732,
	HEADER_ZC_BATTLEFIELD_NOTIFY_CAMPINFO          = 733,
	HEADER_ZC_BATTLEFIELD_NOTIFY_POINT             = 734,
	HEADER_ZC_BATTLEFIELD_NOTIFY_POSITION          = 735,
	HEADER_ZC_BATTLEFIELD_NOTIFY_HP                = 736,
	HEADER_ZC_NOTIFY_ACT2                          = 737,
	HEADER_CZ_USE_ITEM_NEW_JAPEN                   = 738,
	HEADER_CZ_USE_SKILL_NEW_JAPEN                  = 739,
	HEADER_CZ_ITEM_PICKUP_NEW_JAPEN                = 740,
	HEADER_CZ_REQUEST_MOVE_NEW_JAPEN               = 741,
	HEADER_CZ_BOT_CHECK                            = 742,
	HEADER_ZC_MAPPROPERTY                          = 743,
	HEADER_ZC_NORMAL_ITEMLIST3                     = 744,
	HEADER_ZC_CART_NORMAL_ITEMLIST3                = 745,
	HEADER_ZC_STORE_NORMAL_ITEMLIST3               = 746,
	HEADER_ZC_ACCEPT_ENTER2                        = 747,
	HEADER_ZC_NOTIFY_MOVEENTRY4                    = 748,
	HEADER_ZC_NOTIFY_NEWENTRY4                     = 749,
	HEADER_ZC_NOTIFY_STANDENTRY4                   = 750,
	HEADER_ZC_NOTIFY_FONT                          = 751,
	HEADER_ZC_PROGRESS                             = 752,
	HEADER_CZ_PROGRESS                             = 753,
	HEADER_ZC_PROGRESS_CANCEL                      = 754,
	HEADER_CZ_IRMAIL_SEND                          = 755,
	HEADER_ZC_IRMAIL_SEND_RES                      = 756,
	HEADER_ZC_IRMAIL_NOTIFY                        = 757,
	HEADER_CZ_IRMAIL_LIST                          = 758,
	HEADER_CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST        = 860,
	HEADER_ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST       = 861,
	HEADER_CZ_CLOSE_WINDOW                         = 862,
	HEADER_CZ_REQUEST_MOVE2                        = 863,
	HEADER_CZ_REQUEST_TIME2                        = 864,
	HEADER_CZ_CHANGE_DIRECTION2                    = 865,
	HEADER_CZ_ITEM_PICKUP2                         = 866,
	HEADER_CZ_ITEM_THROW2                          = 867,
	HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_STORE2        = 868,
	HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2        = 869,
	HEADER_CZ_USE_SKILL_TOGROUND2                  = 870,
	HEADER_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2      = 871,
	HEADER_CZ_REQNAME2                             = 872,
	HEADER_CZ_REQNAME_BYGID2                       = 873,
	HEADER_AHC_GAME_GUARD                          = 989,
	HEADER_CAH_ACK_GAME_GUARD                      = 990,
	HEADER_ZC_WAITINGROOM_PARTYPLAY_JOIN           = 991,
	HEADER_CZ_WAITINGROOM_PARTYPLAY_JOIN_RESULT    = 992,
	HEADER_ZC_WAITINGROOM_SUBSCRIPTION_RESULT      = 993,
	HEADER_CZ_ENTER2                               = 1078,
	HEADER_CZ_REQUEST_ACT2                         = 1079,
	HEADER_CZ_USE_SKILL2                           = 1080,
	HEADER_CZ_USE_ITEM2                            = 1081,
	HEADER_ZC_REQ_CRACKPROOF                       = 1082,
	HEADER_CZ_ACK_CRACKPROOF                       = 1083,
	HEADER_ZC_CRACKPROOF_ERRCODE                   = 1084,
	HEADER_ZC_SKILL_POSTDELAY                      = 1085,
	HEADER_ZC_SKILL_POSTDELAY_LIST                 = 1086,
	HEADER_ZC_MSG_STATE_CHANGE2                    = 1087,
	HEADER_ZC_MILLENNIUMSHIELD                     = 1088,
	HEADER_ZC_SKILLINFO_DELETE                     = 1089,
	HEADER_ZC_SKILL_SELECT_REQUEST                 = 1090,
	HEADER_CZ_SKILL_SELECT_RESPONSE                = 1091,
	HEADER_ZC_SIMPLE_CASH_POINT_ITEMLIST           = 1092,
	HEADER_CZ_SIMPLE_BUY_CASH_POINT_ITEM           = 1093,
	HEADER_ZC_QUEST_NOTIFY_EFFECT                  = 1094,
	HEADER_CZ_BLOCKING_PLAY_CANCEL                 = 1095,
	HEADER_HC_CHARACTER_LIST                       = 1096,
	HEADER_ZC_HACKSH_ERROR_MSG                     = 1097,
	HEADER_CZ_CLIENT_VERSION                       = 1098,
	HEADER_CZ_CLOSE_SIMPLECASH_SHOP                = 1099,
	HEADER_ZC_ES_RESULT                            = 2000,
	HEADER_CZ_ES_GET_LIST                          = 2001,
	HEADER_ZC_ES_LIST                              = 2002,
	HEADER_CZ_ES_CHOOSE                            = 2003,
	HEADER_CZ_ES_CANCEL                            = 2004,
	HEADER_ZC_ES_READY                             = 2005,
	HEADER_ZC_ES_GOTO                              = 2006,
	HEADER_CZ_GROUPINFO_CHANGE_V2                  = 2007,
	HEADER_ZC_REQ_GROUPINFO_CHANGE_V2              = 2008,
	HEADER_ZC_SHORTCUT_KEY_LIST_V2                 = 2009,
	HEADER_CZ_CHANGE_GROUP_MASTER                  = 2010,
	HEADER_ZC_HO_PAR_CHANGE                        = 2011,
	HEADER_CZ_SEEK_PARTY                           = 2012,
	HEADER_ZC_SEEK_PARTY                           = 2013,
	HEADER_CZ_SEEK_PARTY_MEMBER                    = 2014,
	HEADER_ZC_SEEK_PARTY_MEMBER                    = 2015,
	HEADER_ZC_ES_NOTI_MYINFO                       = 2016,
	HEADER_ZC_SKILLINFO_UPDATE2                    = 2017,
	HEADER_ZC_MSG_VALUE                            = 2018,
	HEADER_ZC_ITEMLISTWIN_OPEN                     = 2019,
	HEADER_CZ_ITEMLISTWIN_RES                      = 2020,
	HEADER_CH_ENTER_CHECKBOT                       = 2021,
	HEADER_ZC_MSG_SKILL                            = 2022,
	HEADER_CH_CHECKBOT                             = 2023,
	HEADER_HC_CHECKBOT                             = 2024,
	HEADER_HC_CHECKBOT_RESULT                      = 2025,
	HEADER_CZ_BATTLE_FIELD_LIST                    = 2026,
	HEADER_ZC_BATTLE_FIELD_LIST                    = 2027,
	HEADER_CZ_JOIN_BATTLE_FIELD                    = 2028,
	HEADER_ZC_JOIN_BATTLE_FIELD                    = 2029,
	HEADER_CZ_CANCEL_BATTLE_FIELD                  = 2030,
	HEADER_ZC_CANCEL_BATTLE_FIELD                  = 2031,
	HEADER_CZ_REQ_BATTLE_STATE_MONITOR             = 2032,
	HEADER_ZC_ACK_BATTLE_STATE_MONITOR             = 2033,
	HEADER_ZC_BATTLE_NOTI_START_STEP               = 2034,
	HEADER_ZC_BATTLE_JOIN_NOTI_DEFER               = 2035,
	HEADER_ZC_BATTLE_JOIN_DISABLE_STATE            = 2036,
	HEADER_CZ_GM_FULLSTRIP                         = 2037,
	HEADER_ZC_NOTIFY_EXP                           = 2038,
	HEADER_ZC_NOTIFY_MOVEENTRY7                    = 2039,
	HEADER_ZC_NOTIFY_NEWENTRY5                     = 2040,
	HEADER_ZC_NOTIFY_STANDENTRY5                   = 2041,
	HEADER_ZC_DELETE_ITEM_FROM_BODY                = 2042,
	HEADER_ZC_USESKILL_ACK2                        = 2043,
	HEADER_ZC_CHANGE_GROUP_MASTER                  = 2044,
	HEADER_ZC_BROADCASTING_SPECIAL_ITEM_OBTAIN     = 2045,
	HEADER_ZC_PLAY_NPC_BGM                         = 2046,
	HEADER_ZC_DEFINE_CHECK                         = 2047,
	HEADER_ZC_PC_PURCHASE_ITEMLIST_FROMMC2         = 2048,
	HEADER_CZ_PC_PURCHASE_ITEMLIST_FROMMC2         = 2049,
	HEADER_CZ_PARTY_BOOKING_REQ_REGISTER           = 2050,
	HEADER_ZC_PARTY_BOOKING_ACK_REGISTER           = 2051,
	HEADER_CZ_PARTY_BOOKING_REQ_SEARCH             = 2052,
	HEADER_ZC_PARTY_BOOKING_ACK_SEARCH             = 2053,
	HEADER_CZ_PARTY_BOOKING_REQ_DELETE             = 2054,
	HEADER_ZC_PARTY_BOOKING_ACK_DELETE             = 2055,
	HEADER_CZ_PARTY_BOOKING_REQ_UPDATE             = 2056,
	HEADER_ZC_PARTY_BOOKING_NOTIFY_INSERT          = 2057,
	HEADER_ZC_PARTY_BOOKING_NOTIFY_UPDATE          = 2058,
	HEADER_ZC_PARTY_BOOKING_NOTIFY_DELETE          = 2059,
	HEADER_CZ_SIMPLE_CASH_BTNSHOW                  = 2060,
	HEADER_ZC_SIMPLE_CASH_BTNSHOW                  = 2061,
	HEADER_ZC_NOTIFY_HP_TO_GROUPM_R2               = 2062,
	HEADER_ZC_ADD_EXCHANGE_ITEM2                   = 2063,
	HEADER_ZC_OPEN_BUYING_STORE                    = 2064,
	HEADER_CZ_REQ_OPEN_BUYING_STORE                = 2065,
	HEADER_ZC_FAILED_OPEN_BUYING_STORE_TO_BUYER    = 2066,
	HEADER_ZC_MYITEMLIST_BUYING_STORE              = 2067,
	HEADER_ZC_BUYING_STORE_ENTRY                   = 2068,
	HEADER_CZ_REQ_CLOSE_BUYING_STORE               = 2069,
	HEADER_ZC_DISAPPEAR_BUYING_STORE_ENTRY         = 2070,
	HEADER_CZ_REQ_CLICK_TO_BUYING_STORE            = 2071,
	HEADER_ZC_ACK_ITEMLIST_BUYING_STORE            = 2072,
	HEADER_CZ_REQ_TRADE_BUYING_STORE               = 2073,
	HEADER_ZC_FAILED_TRADE_BUYING_STORE_TO_BUYER   = 2074,
	HEADER_ZC_UPDATE_ITEM_FROM_BUYING_STORE        = 2075,
	HEADER_ZC_ITEM_DELETE_BUYING_STORE             = 2076,
	HEADER_ZC_EL_INIT                              = 2077,
	HEADER_ZC_EL_PAR_CHANGE                        = 2078,
	HEADER_ZC_BROADCAST4                           = 2079,
	HEADER_ZC_COSTUME_SPRITE_CHANGE                = 2080,
	HEADER_AC_OTP_USER                             = 2081,
	HEADER_CA_OTP_AUTH_REQ                         = 2082,
	HEADER_AC_OTP_AUTH_ACK                         = 2083,
	HEADER_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER  = 2084,
	HEADER_CA_SSO_LOGIN_REQ                        = 2085,
	HEADER_AC_SSO_LOGIN_ACK                        = 2086,
	HEADER_CH_DELETE_CHAR3_RESERVED                = 2087,
	HEADER_HC_DELETE_CHAR3_RESERVED                = 2088,
	HEADER_CH_DELETE_CHAR3                         = 2089,
	HEADER_HC_DELETE_CHAR3                         = 2090,
	HEADER_CH_DELETE_CHAR3_CANCEL                  = 2091,
	HEADER_HC_DELETE_CHAR3_CANCEL                  = 2092,
	HEADER_HC_ACCEPT_ENTER2                        = 2093,
	HEADER_CZ_SEARCH_STORE_INFO                    = 2101,
	HEADER_ZC_SEARCH_STORE_INFO_ACK                = 2102,
	HEADER_ZC_SEARCH_STORE_INFO_FAILED             = 2103,
	HEADER_CZ_SEARCH_STORE_INFO_NEXT_PAGE          = 2104,
	HEADER_ZC_ACK_BAN_GUILD_SSO                    = 2105,
	HEADER_ZC_OPEN_SEARCH_STORE_INFO               = 2106,
	HEADER_CZ_CLOSE_SEARCH_STORE_INFO              = 2107,
	HEADER_CZ_SSILIST_ITEM_CLICK                   = 2108,
	HEADER_ZC_SSILIST_ITEM_CLICK_ACK               = 2109,
	HEADER_AC_REFUSE_LOGIN_R2                      = 2110,
	HEADER_ZC_SEARCH_STORE_OPEN_INFO               = 2111,
	HEADER_HC_NOTIFY_ACCESSIBLE_MAPNAME            = 2112,
	HEADER_CH_SELECT_ACCESSIBLE_MAPNAME            = 2113,
	HEADER_CZ_RECALL_SSO                           = 2114,
	HEADER_CZ_REMOVE_AID_SSO                       = 2115,
	HEADER_CZ_SE_CASHSHOP_OPEN                     = 2116,
	HEADER_ZC_SE_CASHSHOP_OPEN                     = 2117,
	HEADER_CZ_REQ_SE_CASH_TAB_CODE                 = 2118,
	HEADER_ZC_ACK_SE_CASH_ITEM_LIST                = 2119,
	HEADER_CZ_SE_PC_BUY_CASHITEM_LIST              = 2120,
	HEADER_ZC_SE_PC_BUY_CASHITEM_RESULT            = 2121,
	HEADER_CZ_SE_CASHSHOP_CLOSE                    = 2122,
	HEADER_ZC_ITEM_FALL_ENTRY4                     = 2123,
	HEADER_CZ_MACRO_USE_SKILL                      = 2124,
	HEADER_CZ_MACRO_USE_SKILL_TOGROUND             = 2125,
	HEADER_CZ_MACRO_REQUEST_MOVE                   = 2126,
	HEADER_CZ_MACRO_ITEM_PICKUP                    = 2127,
	HEADER_CZ_MACRO_REQUEST_ACT                    = 2128,
	HEADER_ZC_GPK_DYNCODE                          = 2129,
	HEADER_CZ_GPK_DYNCODE_RELOAD                   = 2130,
	HEADER_ZC_GPK_AUTH                             = 2131,
	HEADER_CZ_GPK_AUTH                             = 2132,
	HEADER_ZC_MACRO_ITEMPICKUP_FAIL                = 2133,
	HEADER_ZC_NOTIFY_MOVEENTRY8                    = 2134,
	HEADER_ZC_NOTIFY_STANDENTRY7                   = 2135,
	HEADER_ZC_NOTIFY_NEWENTRY6                     = 2136,
	HEADER_ZC_EQUIPWIN_MICROSCOPE2                 = 2137,
	HEADER_ZC_REASSEMBLY_AUTH01                    = 2138,
	HEADER_ZC_REASSEMBLY_AUTH02                    = 2139,
	HEADER_ZC_REASSEMBLY_AUTH03                    = 2140,
	HEADER_ZC_REASSEMBLY_AUTH04                    = 2141,
	HEADER_ZC_REASSEMBLY_AUTH05                    = 2142,
	HEADER_ZC_REASSEMBLY_AUTH06                    = 2143,
	HEADER_ZC_REASSEMBLY_AUTH07                    = 2144,
	HEADER_ZC_REASSEMBLY_AUTH08                    = 2145,
	HEADER_ZC_REASSEMBLY_AUTH09                    = 2146,
	HEADER_ZC_REASSEMBLY_AUTH10                    = 2147,
	HEADER_ZC_REASSEMBLY_AUTH11                    = 2148,
	HEADER_ZC_REASSEMBLY_AUTH12                    = 2149,
	HEADER_ZC_REASSEMBLY_AUTH13                    = 2150,
	HEADER_ZC_REASSEMBLY_AUTH14                    = 2151,
	HEADER_ZC_REASSEMBLY_AUTH15                    = 2152,
	HEADER_ZC_REASSEMBLY_AUTH16                    = 2153,
	HEADER_ZC_REASSEMBLY_AUTH17                    = 2154,
	HEADER_ZC_REASSEMBLY_AUTH18                    = 2155,
	HEADER_ZC_REASSEMBLY_AUTH19                    = 2156,
	HEADER_ZC_REASSEMBLY_AUTH20                    = 2157,
	HEADER_ZC_REASSEMBLY_AUTH21                    = 2158,
	HEADER_ZC_REASSEMBLY_AUTH22                    = 2159,
	HEADER_ZC_REASSEMBLY_AUTH23                    = 2160,
	HEADER_ZC_REASSEMBLY_AUTH24                    = 2161,
	HEADER_ZC_REASSEMBLY_AUTH25                    = 2162,
	HEADER_ZC_REASSEMBLY_AUTH26                    = 2163,
	HEADER_ZC_REASSEMBLY_AUTH27                    = 2164,
	HEADER_ZC_REASSEMBLY_AUTH28                    = 2165,
	HEADER_ZC_REASSEMBLY_AUTH29                    = 2166,
	HEADER_ZC_REASSEMBLY_AUTH30                    = 2167,
	HEADER_ZC_REASSEMBLY_AUTH31                    = 2168,
	HEADER_ZC_REASSEMBLY_AUTH32                    = 2169,
	HEADER_ZC_REASSEMBLY_AUTH33                    = 2170,
	HEADER_ZC_REASSEMBLY_AUTH34                    = 2171,
	HEADER_ZC_REASSEMBLY_AUTH35                    = 2172,
	HEADER_ZC_REASSEMBLY_AUTH36                    = 2173,
	HEADER_ZC_REASSEMBLY_AUTH37                    = 2174,
	HEADER_ZC_REASSEMBLY_AUTH38                    = 2175,
	HEADER_ZC_REASSEMBLY_AUTH39                    = 2176,
	HEADER_ZC_REASSEMBLY_AUTH40                    = 2177,
	HEADER_ZC_REASSEMBLY_AUTH41                    = 2178,
	HEADER_ZC_REASSEMBLY_AUTH42                    = 2179,
	HEADER_CZ_REASSEMBLY_AUTH01                    = 2180,
	HEADER_CZ_REASSEMBLY_AUTH02                    = 2181,
	HEADER_CZ_REASSEMBLY_AUTH03                    = 2182,
	HEADER_CZ_REASSEMBLY_AUTH04                    = 2183,
	HEADER_CZ_REASSEMBLY_AUTH05                    = 2184,
	HEADER_CZ_REASSEMBLY_AUTH06                    = 2185,
	HEADER_CZ_REASSEMBLY_AUTH07                    = 2186,
	HEADER_CZ_REASSEMBLY_AUTH08                    = 2187,
	HEADER_CZ_REASSEMBLY_AUTH09                    = 2188,
	HEADER_CZ_REASSEMBLY_AUTH10                    = 2189,
	HEADER_CZ_REASSEMBLY_AUTH11                    = 2190,
	HEADER_CZ_REASSEMBLY_AUTH12                    = 2191,
	HEADER_CZ_REASSEMBLY_AUTH13                    = 2192,
	HEADER_CZ_REASSEMBLY_AUTH14                    = 2193,
	HEADER_CZ_REASSEMBLY_AUTH15                    = 2194,
	HEADER_CZ_REASSEMBLY_AUTH16                    = 2195,
	HEADER_CZ_REASSEMBLY_AUTH17                    = 2196,
	HEADER_CZ_REASSEMBLY_AUTH18                    = 2197,
	HEADER_CZ_REASSEMBLY_AUTH19                    = 2198,
	HEADER_CZ_REASSEMBLY_AUTH20                    = 2199,
	HEADER_CZ_REASSEMBLY_AUTH21                    = 2200,
	HEADER_CZ_REASSEMBLY_AUTH22                    = 2201,
	HEADER_CZ_REASSEMBLY_AUTH23                    = 2202,
	HEADER_CZ_REASSEMBLY_AUTH24                    = 2203,
	HEADER_CZ_REASSEMBLY_AUTH25                    = 2204,
	HEADER_CZ_REASSEMBLY_AUTH26                    = 2205,
	HEADER_CZ_REASSEMBLY_AUTH27                    = 2206,
	HEADER_CZ_REASSEMBLY_AUTH28                    = 2207,
	HEADER_CZ_REASSEMBLY_AUTH29                    = 2208,
	HEADER_CZ_REASSEMBLY_AUTH30                    = 2209,
	HEADER_CZ_REASSEMBLY_AUTH31                    = 2210,
	HEADER_CZ_REASSEMBLY_AUTH32                    = 2211,
	HEADER_CZ_REASSEMBLY_AUTH33                    = 2212,
	HEADER_CZ_REASSEMBLY_AUTH34                    = 2213,
	HEADER_CZ_REASSEMBLY_AUTH35                    = 2214,
	HEADER_CZ_REASSEMBLY_AUTH36                    = 2215,
	HEADER_CZ_REASSEMBLY_AUTH37                    = 2216,
	HEADER_CZ_REASSEMBLY_AUTH38                    = 2217,
	HEADER_CZ_REASSEMBLY_AUTH39                    = 2218,
	HEADER_CZ_REASSEMBLY_AUTH40                    = 2219,
	HEADER_CZ_REASSEMBLY_AUTH41                    = 2220,
	HEADER_CZ_REASSEMBLY_AUTH42                    = 2221,
	HEADER_CC_REPLAYPACKET                         = 2222,
	HEADER_HC_WAITING_LOGIN                        = 2223,
	HEADER_CH_WAITING_LOGIN                        = 2224,
	HEADER_ZC_MCSTORE_NOTMOVEITEM_LIST             = 2225,
	HEADER_AC_REALNAME_AUTH                        = 2226,
	HEADER_ZC_SHOWSCRIPT                           = 2227,
	HEADER_ZC_START_COLLECTION                     = 2228,
	HEADER_CZ_TRYCOLLECTION                        = 2229,
	HEADER_ZC_TRYCOLLECTION                        = 2230,
	HEADER_HC_SECOND_PASSWD_REQ                    = 2231,
	HEADER_CH_SECOND_PASSWD_ACK                    = 2232,
	HEADER_HC_SECOND_PASSWD_LOGIN                  = 2233,
	HEADER_CH_MAKE_SECOND_PASSWD                   = 2234,
	HEADER_HC_MAKE_SECOND_PASSWD                   = 2235,
	HEADER_CH_DELETE_SECOND_PASSWD                 = 2236,
	HEADER_HC_DELETE_SECOND_PASSWD                 = 2237,
	HEADER_CH_EDIT_SECOND_PASSWD                   = 2238,
	HEADER_HC_EDIT_SECOND_PASSWD                   = 2239,
	HEADER_ZC_ACK_SE_CASH_ITEM_LIST2               = 2240,
	HEADER_CZ_MACRO_START                          = 2241,
	HEADER_CZ_MACRO_STOP                           = 2242,
	HEADER_CH_NOT_AVAILABLE_SECOND_PASSWD          = 2243,
	HEADER_HC_NOT_AVAILABLE_SECOND_PASSWD          = 2244,
	HEADER_CH_AVAILABLE_SECOND_PASSWD              = 2245,
	HEADER_HC_AVAILABLE_SECOND_PASSWD              = 2246,
	HEADER_ZC_SKILL_ENTRY3                         = 2247,
	HEADER_ZC_NOTIFY_ACT3                          = 2248,
	HEADER_CZ_REQ_SCHEDULER_CASHITEM               = 2249,
	HEADER_ZC_ACK_SCHEDULER_CASHITEM               = 2250,
	HEADER_ZC_PERSONAL_INFOMATION                  = 2251,
	HEADER_CA_LOGIN5                               = 2252,
	HEADER_ZC_STOPMOVE_FORCE                       = 2253,
	HEADER_ZC_FAILED_GET_ITEM_FROM_ZONEDA          = 2254,
	HEADER_ZC_SPIRITS_ATTRIBUTE                    = 2255,
	HEADER_ZC_REQ_WEAR_EQUIP_ACK2                  = 2256,
	HEADER_ZC_REQ_TAKEOFF_EQUIP_ACK2               = 2257,
	HEADER_ZC_FASTMOVE                             = 2258,
	HEADER_ZC_SE_CASHSHOP_UPDATE                   = 2259,
	HEADER_CH_REQ_CHANGE_CHARACTER_SLOT            = 2260,
	HEADER_HC_ACK_CHANGE_CHARACTER_SLOT            = 2261,
	HEADER_ZC_CLEAR_DIALOG                         = 2262,
	HEADER_CZ_REQ_ENTRY_QUEUE_APPLY                = 2263,
	HEADER_ZC_ACK_ENTRY_QUEUE_APPLY                = 2264,
	HEADER_ZC_NOTIFY_ENTRY_QUEUE_APPLY             = 2265,
	HEADER_CZ_REQ_ENTRY_QUEUE_CANCEL               = 2266,
	HEADER_ZC_ACK_ENTRY_QUEUE_CANCEL               = 2267,
	HEADER_ZC_NOTIFY_ENTRY_QUEUE_ADMISSION         = 2268,
	HEADER_CZ_REPLY_ENTRY_QUEUE_ADMISSION          = 2269,
	HEADER_ZC_REPLY_ACK_ENTRY_QUEUE_ADMISSION      = 2270,
	HEADER_ZC_NOTIFY_LOBBY_ADMISSION               = 2271,
	HEADER_CZ_REPLY_LOBBY_ADMISSION                = 2272,
	HEADER_ZC_REPLY_ACK_LOBBY_ADMISSION            = 2273,
	HEADER_ZC_NAVIGATION_ACTIVE                    = 2274,
	HEADER_HC_UPDATE_CHARINFO                      = 2275,
	HEADER_AC_SHUTDOWN_INFO                        = 2276,
	XXX_HEADER_CZ_PARTY_RECRUIT_REQ_REGISTER       = 2277,
	XXX_HEADER_ZC_PARTY_RECRUIT_ACK_REGISTER       = 2278,
	XXX_HEADER_CZ_PARTY_RECRUIT_REQ_SEARCH         = 2279,
	XXX_HEADER_ZC_PARTY_RECRUIT_ACK_SEARCH         = 2280,
	XXX_HEADER_CZ_PARTY_RECRUIT_REQ_DELETE         = 2281,
	XXX_HEADER_ZC_PARTY_RECRUIT_ACK_DELETE         = 2282,
	XXX_HEADER_CZ_PARTY_RECRUIT_REQ_UPDATE         = 2283,
	XXX_HEADER_ZC_PARTY_RECRUIT_NOTIFY_INSERT      = 2284,
	XXX_HEADER_ZC_PARTY_RECRUIT_NOTIFY_UPDATE      = 2285,
	XXX_HEADER_ZC_PARTY_RECRUIT_NOTIFY_DELETE      = 2286,
	XXX_HEADER_CZ_PARTY_RECRUIT_ADD_FILTERLINGLIST = 2287,
	XXX_HEADER_CZ_PARTY_RECRUIT_SUB_FILTERLINGLIST = 2288,
	XXX_HEADER_CZ_PARTY_RECRUIT_REQ_VOLUNTEER      = 2289,
	XXX_HEADER_ZC_PARTY_RECRUIT_VOLUNTEER_INFO     = 2290,
	XXX_HEADER_ZC_PARTY_RECRUIT_PERSONAL_SETTING   = 2291,
	XXX_HEADER_CZ_PARTY_RECRUIT_SHOW_EQUIPMENT     = 2292,
	XXX_HEADER_CZ_PARTY_RECRUIT_REQ_RECALL         = 2293,
	XXX_HEADER_ZC_PARTY_RECRUIT_RECALL_COST        = 2294,
	XXX_HEADER_CZ_PARTY_RECRUIT_ACK_RECALL         = 2295,
	XXX_HEADER_ZC_PARTY_RECRUIT_FAILED_RECALL      = 2296,
	XXX_HEADER_CZ_PARTY_RECRUIT_REFUSE_VOLUNTEER   = 2297,
	XXX_HEADER_ZC_PARTY_RECRUIT_REFUSE_VOLUNTEER   = 2298,
	XXX_HEADER_CZ_PARTY_RECRUIT_CANCEL_VOLUNTEER   = 2299,
	HEADER_CH_REQ_CHANGE_CHARACTERNAME             = 2300,
	HEADER_CH_ACK_CHANGE_CHARACTERNAME             = 2301,
	HEADER_ZC_HUNTING_QUEST_INFO                   = 2302,
	HEADER_ZC_EFST_SET_ENTER                       = 2303,
	HEADER_ZC_INVENTORY_ITEMLIST_NORMAL            = 2304,
	HEADER_ZC_INVENTORY_ITEMLIST_EQUIP             = 2305,
	HEADER_ZC_CART_ITEMLIST_NORMAL                 = 2306,
	HEADER_ZC_CART_ITEMLIST_EQUIP                  = 2307,
	HEADER_ZC_STORE_ITEMLIST_NORMAL                = 2308,
	HEADER_ZC_STORE_ITEMLIST_EQUIP                 = 2309,
	HEADER_ZC_MICROSCOPE                           = 2310,
	HEADER_CZ_INVENTORY_TAB                        = 2311,
	HEADER_ZC_INVENTORY_TAB                        = 2312,
	XXX_HEADER_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER   = 2313,
	HEADER_CZ_REQ_ENTRY_QUEUE_RANKING              = 2314,
	XXX_HEADER_ZC_PARTY_RECRUIT_ADD_FILTERLINGLIST = 2315,
	XXX_HEADER_ZC_PARTY_RECRUIT_SUB_FILTERLINGLIST = 2316,
	HEADER_ZC_PREMIUM_CAMPAIGN_INFO                = 2317,
	HEADER_ZC_ENTRY_QUEUE_INIT                     = 2318,
	HEADER_ZC_NOTIFY_NEWENTRY7                     = 2319,
	HEADER_CZ_REQ_PARTY_NAME                       = 2320,
	HEADER_ZC_ACK_PARTY_NAME                       = 2321,
	HEADER_CZ_REQ_GUILD_NAME                       = 2322,
	HEADER_ZC_ACK_GUILD_NAME                       = 2323,
	HEADER_ZC_NOTIFY_MOVEENTRY9                    = 2324,
	HEADER_ZC_NOTIFY_STANDENTRY8                   = 2325,
	HEADER_CZ_REQ_JOIN_GUILD2                      = 2326,
	HEADER_ZC_REASSEMBLY_AUTH43                    = 2327,
	HEADER_ZC_REASSEMBLY_AUTH44                    = 2328,
	HEADER_ZC_REASSEMBLY_AUTH45                    = 2329,
	HEADER_ZC_REASSEMBLY_AUTH46                    = 2330,
	HEADER_ZC_REASSEMBLY_AUTH47                    = 2331,
	HEADER_ZC_REASSEMBLY_AUTH48                    = 2332,
	HEADER_ZC_REASSEMBLY_AUTH49                    = 2333,
	HEADER_ZC_REASSEMBLY_AUTH50                    = 2334,
	HEADER_ZC_REASSEMBLY_AUTH51                    = 2335,
	HEADER_ZC_REASSEMBLY_AUTH52                    = 2336,
	HEADER_ZC_REASSEMBLY_AUTH53                    = 2337,
	HEADER_ZC_REASSEMBLY_AUTH54                    = 2338,
	HEADER_ZC_REASSEMBLY_AUTH55                    = 2339,
	HEADER_ZC_REASSEMBLY_AUTH56                    = 2340,
	HEADER_ZC_REASSEMBLY_AUTH57                    = 2341,
	HEADER_ZC_REASSEMBLY_AUTH58                    = 2342,
	HEADER_ZC_REASSEMBLY_AUTH59                    = 2343,
	HEADER_ZC_REASSEMBLY_AUTH60                    = 2344,
	HEADER_ZC_REASSEMBLY_AUTH61                    = 2345,
	HEADER_ZC_REASSEMBLY_AUTH62                    = 2346,
	HEADER_ZC_REASSEMBLY_AUTH63                    = 2347,
	HEADER_ZC_REASSEMBLY_AUTH64                    = 2348,
	HEADER_ZC_REASSEMBLY_AUTH65                    = 2349,
	HEADER_ZC_REASSEMBLY_AUTH66                    = 2350,
	HEADER_ZC_REASSEMBLY_AUTH67                    = 2351,
	HEADER_ZC_REASSEMBLY_AUTH68                    = 2352,
	HEADER_ZC_REASSEMBLY_AUTH69                    = 2353,
	HEADER_ZC_REASSEMBLY_AUTH70                    = 2354,
	HEADER_ZC_REASSEMBLY_AUTH71                    = 2355,
	HEADER_ZC_REASSEMBLY_AUTH72                    = 2356,
	HEADER_ZC_REASSEMBLY_AUTH73                    = 2357,
	HEADER_ZC_REASSEMBLY_AUTH74                    = 2358,
	HEADER_ZC_REASSEMBLY_AUTH75                    = 2359,
	HEADER_ZC_REASSEMBLY_AUTH76                    = 2360,
	HEADER_ZC_REASSEMBLY_AUTH77                    = 2361,
	HEADER_ZC_REASSEMBLY_AUTH78                    = 2362,
	HEADER_ZC_REASSEMBLY_AUTH79                    = 2363,
	HEADER_ZC_REASSEMBLY_AUTH80                    = 2364,
	HEADER_ZC_REASSEMBLY_AUTH81                    = 2365,
	HEADER_ZC_REASSEMBLY_AUTH82                    = 2366,
	HEADER_ZC_REASSEMBLY_AUTH83                    = 2367,
	HEADER_ZC_REASSEMBLY_AUTH84                    = 2368,
	HEADER_CZ_REASSEMBLY_AUTH43                    = 2369,
	HEADER_CZ_REASSEMBLY_AUTH44                    = 2370,
	HEADER_CZ_REASSEMBLY_AUTH45                    = 2371,
	HEADER_CZ_REASSEMBLY_AUTH46                    = 2372,
	HEADER_CZ_REASSEMBLY_AUTH47                    = 2373,
	HEADER_CZ_REASSEMBLY_AUTH48                    = 2374,
	HEADER_CZ_REASSEMBLY_AUTH49                    = 2375,
	HEADER_CZ_REASSEMBLY_AUTH50                    = 2376,
	HEADER_CZ_REASSEMBLY_AUTH51                    = 2377,
	HEADER_CZ_REASSEMBLY_AUTH52                    = 2378,
	HEADER_CZ_REASSEMBLY_AUTH53                    = 2379,
	HEADER_CZ_REASSEMBLY_AUTH54                    = 2380,
	HEADER_CZ_REASSEMBLY_AUTH55                    = 2381,
	HEADER_CZ_REASSEMBLY_AUTH56                    = 2382,
	HEADER_CZ_REASSEMBLY_AUTH57                    = 2383,
	HEADER_CZ_REASSEMBLY_AUTH58                    = 2384,
	HEADER_CZ_REASSEMBLY_AUTH59                    = 2385,
	HEADER_CZ_REASSEMBLY_AUTH60                    = 2386,
	HEADER_CZ_REASSEMBLY_AUTH61                    = 2387,
	HEADER_CZ_REASSEMBLY_AUTH62                    = 2388,
	HEADER_CZ_REASSEMBLY_AUTH63                    = 2389,
	HEADER_CZ_REASSEMBLY_AUTH64                    = 2390,
	HEADER_CZ_REASSEMBLY_AUTH65                    = 2391,
	HEADER_CZ_REASSEMBLY_AUTH66                    = 2392,
	HEADER_CZ_REASSEMBLY_AUTH67                    = 2393,
	HEADER_CZ_REASSEMBLY_AUTH68                    = 2394,
	HEADER_CZ_REASSEMBLY_AUTH69                    = 2395,
	HEADER_CZ_REASSEMBLY_AUTH70                    = 2396,
	HEADER_CZ_REASSEMBLY_AUTH71                    = 2397,
	HEADER_CZ_REASSEMBLY_AUTH72                    = 2398,
	HEADER_CZ_REASSEMBLY_AUTH73                    = 2399,
	HEADER_CZ_REASSEMBLY_AUTH74                    = 2400,
	HEADER_CZ_REASSEMBLY_AUTH75                    = 2401,
	HEADER_CZ_REASSEMBLY_AUTH76                    = 2402,
	HEADER_CZ_REASSEMBLY_AUTH77                    = 2403,
	HEADER_CZ_REASSEMBLY_AUTH78                    = 2404,
	HEADER_CZ_REASSEMBLY_AUTH79                    = 2405,
	HEADER_CZ_REASSEMBLY_AUTH80                    = 2406,
	HEADER_CZ_REASSEMBLY_AUTH81                    = 2407,
	HEADER_CZ_REASSEMBLY_AUTH82                    = 2408,
	HEADER_CZ_REASSEMBLY_AUTH83                    = 2409,
	HEADER_CZ_REASSEMBLY_AUTH84                    = 2410,
	HEADER_ZC_PRNPC_STATE                          = 2411,
	HEADER_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM = 2412,
	HEADER_ZC_MERGE_ITEM_OPEN                      = 2413,
	HEADER_CZ_REQ_MERGE_ITEM                       = 2414,
	HEADER_ZC_ACK_MERGE_ITEM                       = 2415,
	HEADER_CH_MAKE_CHAR_NOT_STATS                  = 2416,
	HEADER_ZC_PARTY_RECRUIT_REFUSE_VOLUNTEER_TO_PM = 2417,
	HEADER_ZC_SAY_DIALOG2                          = 2418,
	HEADER_ZC_WAIT_DIALOG2                         = 2419,
	HEADER_CZ_CANCEL_MERGE_ITEM                    = 2420,
	HEADER_ZC_STORE_ITEMLIST_NORMAL_V2             = 2421,
	HEADER_ZC_STORE_ITEMLIST_EQUIP_V2              = 2422,
	HEADER_ZC_HP_INFO                              = 2423,
	HEADER_CZ_REQ_BEFORE_WORLD_INFO                = 2424,
	HEADER_ZC_ACK_BEFORE_WORLD_INFO                = 2425,
	HEADER_ZC_ALL_QUEST_LIST2                      = 2426,
	HEADER_ZC_PERSONAL_INFOMATION2                 = 2427,
	HEADER_CZ_REQ_RANKING                          = 2428,
	HEADER_ZC_ACK_RANKING                          = 2429,
	HEADER_ZC_UPDATE_RANKING_POINT                 = 2430,
	HEADER_ZC_SELECTCART                           = 2431,
	HEADER_CZ_SELECTCART                           = 2432,
	HEADER_ZC_PERSONAL_INFOMATION_CHN              = 2433,
	HEADER_ZC_FATIGUE_CHN                          = 2434,
	HEADER_ZC_MSG_STATE_CHANGE3                    = 2435,
	HEADER_ZC_EFST_SET_ENTER2                      = 2436,
	HEADER_ZC_SKILL_POSTDELAY_LIST2                = 2437,
	HEADER_AC_SHUTDOWN_NOTIFY                      = 2438,
	HEADER_CA_LOGIN_CHN                            = 2439,
	HEADER_ZC_NOTIFY_CLAN_CONNECTINFO              = 2440,
	HEADER_ZC_ACK_CLAN_LEAVE                       = 2441,
	HEADER_ZC_CLANINFO                             = 2442,
	HEADER_AC_REQ_NEW_USER                         = 2443,
	HEADER_CA_ACK_NEW_USER                         = 2444,
	HEADER_CZ_CLAN_CHAT                            = 2445,
	HEADER_ZC_NOTIFY_CLAN_CHAT                     = 2446,
	HEADER_CH_DELETE_CHAR3_EXT                     = 2447,
	HEADER_ZC_ITEM_PICKUP_ACK_V5                   = 2448,
	HEADER_ZC_INVENTORY_ITEMLIST_NORMAL_V5         = 2449,
	HEADER_ZC_INVENTORY_ITEMLIST_EQUIP_V5          = 2450,
	HEADER_ZC_CART_ITEMLIST_NORMAL_V5              = 2451,
	HEADER_ZC_CART_ITEMLIST_EQUIP_V5               = 2452,
	HEADER_ZC_STORE_ITEMLIST_NORMAL_V5             = 2453,
	HEADER_ZC_STORE_ITEMLIST_EQUIP_V5              = 2454,
	HEADER_ZC_EQUIPWIN_MICROSCOPE_V5               = 2455,
	HEADER_CZ_REQ_WEAR_EQUIP_V5                    = 2456,
	HEADER_ZC_ACK_WEAR_EQUIP_V5                    = 2457,
	HEADER_ZC_ACK_TAKEOFF_EQUIP_V5                 = 2458,
	HEADER_ZC_MAPPROPERTY_R2                       = 2459,
	HEADER_CH_REQ_CHARINFO_PER_PAGE                = 2460,
	HEADER_HC_ACK_CHARINFO_PER_PAGE                = 2461,
	HEADER_HC_QUEUE_ORDER                          = 2462,
	HEADER_ZC_SKILL_ENTRY4                         = 2463,
	HEADER_HC_CHARLIST_NOTIFY                      = 2464,
	HEADER_CH_CHARLIST_REQ                         = 2465,
	HEADER_AC_REQ_MOBILE_OTP                       = 2466,
	HEADER_CA_ACK_MOBILE_OTP                       = 2467,
	HEADER_ZC_DISPATCH_TIMING_INFO_CHN             = 2468,
	HEADER_AC_REFUSE_LOGIN3                        = 2469,
	HEADER_ZC_BANKING_CHECK                        = 2470,
	HEADER_CZ_REQ_BANKING_DEPOSIT                  = 2471,
	HEADER_ZC_ACK_BANKING_DEPOSIT                  = 2472,
	HEADER_CZ_REQ_BANKING_WITHDRAW                 = 2473,
	HEADER_ZC_ACK_BANKING_WITHDRAW                 = 2474,
	HEADER_CZ_REQ_BANKING_CHECK                    = 2475,
	HEADER_CZ_REQ_CASH_BARGAIN_SALE_ITEM_INFO      = 2476,
	HEADER_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO      = 2477,
	HEADER_CZ_REQ_APPLY_BARGAIN_SALE_ITEM          = 2478,
	HEADER_ZC_ACK_APPLY_BARGAIN_SALE_ITEM          = 2479,
	HEADER_CZ_REQ_REMOVE_BARGAIN_SALE_ITEM         = 2480,
	HEADER_ZC_ACK_REMOVE_BARGAIN_SALE_ITEM         = 2481,
	HEADER_ZC_NOTIFY_BARGAIN_SALE_SELLING          = 2482,
	HEADER_ZC_NOTIFY_BARGAIN_SALE_CLOSE            = 2483,
	HEADER_CZ_OPEN_BARGAIN_SALE_TOOL               = 2484,
	HEADER_ZC_OPEN_BARGAIN_SALE_TOOL               = 2485,
	HEADER_CZ_REQ_OPEN_BANKING                     = 2486,
	HEADER_ZC_ACK_OPEN_BANKING                     = 2487,
	HEADER_CZ_REQ_CLOSE_BANKING                    = 2488,
	HEADER_ZC_ACK_CLOSE_BANKING                    = 2489,
	HEADER_CZ_REQ_OPEN_GUILD_STORAGE               = 2490,
	HEADER_ZC_ACK_OPEN_GUILD_STORAGE               = 2491,
	HEADER_CZ_CLOSE_BARGAIN_SALE_TOOL              = 2492,
	HEADER_ZC_CLOSE_BARGAIN_SALE_TOOL              = 2493,
	HEADER_CZ_REQ_CLOSE_GUILD_STORAGE              = 2494,
	HEADER_ZC_ACK_CLOSE_GUILD_STORAGE              = 2495,
	HEADER_ZC_ACTION_MOVE                          = 2496,
	HEADER_ZC_C_MARKERINFO                         = 2497,
	HEADER_HC_SECRETSCAN_DATA                      = 2498,
	HEADER_CZ_REQ_COUNT_BARGAIN_SALE_ITEM          = 2499,
	HEADER_ZC_ACK_COUNT_BARGAIN_SALE_ITEM          = 2500,
	HEADER_CS_LOGIN_QUERY                          = 2501,
	HEADER_SC_LOGIN_ANSWER                         = 2502,
	HEADER_SC_LOGIN_ERROR                          = 2503,
	HEADER_CA_LOGIN_OTP                            = 2504,
	HEADER_SC_SOCT                                 = 2505,
	HEADER_ZC_SKILL_ENTRY5                         = 2506,
	HEADER_ZC_USE_SKILL2                           = 2507,
	HEADER_ZC_SECRETSCAN_DATA                      = 2508,
	HEADER_ZC_MSG_COLOR                            = 2509,
	HEADER_CZ_ITEM_CREATE_EX                       = 2510,
	HEADER_ZC_NPROTECTGAMEGUARDCSAUTH              = 2511,
	HEADER_CZ_NPROTECTGAMEGUARDCSAUTH              = 2512,
	HEADER_ZC_PROGRESS_ACTOR                       = 2513,
	HEADER_ZC_GUILDSTORAGE_ITEMLIST_NORMAL_V5      = 2514,
	HEADER_ZC_GUILDSTORAGE_ITEMLIST_EQUIP_V5       = 2515,
	HEADER_CZ_NPC_TRADE_QUIT                       = 2516,
	HEADER_ZC_NPC_MARKET_OPEN                      = 2517,
	HEADER_CZ_NPC_MARKET_PURCHASE                  = 2518,
	HEADER_ZC_NPC_MARKET_PURCHASE_RESULT           = 2519,
	HEADER_CZ_NPC_MARKET_CLOSE                     = 2520,
	HEADER_CZ_REQ_GUILDSTORAGE_LOG                 = 2521,
	HEADER_ZC_ACK_GUILDSTORAGE_LOG                 = 2522,
	HEADER_LAST                                    = 2523,
};


struct PACKET_CZ_ENTER
{// 0x0072 (114)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int AuthCode;
	/* this+14 */ unsigned long clientTime;
	/* this+18 */ unsigned char Sex;
};


struct PACKET_CZ_NOTIFY_ACTORINIT
{// 0x007D (125)
	/* this+ 0 */ short PacketType;
};


struct PACKET_CZ_REQUEST_TIME
{// 0x007E (126)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long clientTime;
};


struct PACKET_CZ_REQUEST_MOVE
{// 0x0085 (133)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char dest[3];
};


struct PACKET_ZC_NOTIFY_MOVE
{// 0x0086 (134)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned char MoveData[6];
	/* this+12 */ unsigned long moveStartTime;
};


struct PACKET_ZC_NOTIFY_PLAYERMOVE
{// 0x0087 (135)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long moveStartTime;
	/* this+6 */ unsigned char MoveData[6];
};


struct PACKET_ZC_STOPMOVE
{// 0x0088 (136)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;
};


struct PACKET_CZ_REQUEST_CHAT
{// 0x008C (140)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_ZC_NOTIFY_CHAT
{// 0x008D (141)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long GID;
	/* this+8 */ char Text[];
};


struct PACKET_ZC_NOTIFY_PLAYERCHAT
{// 0x008E (142)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_CZ_CONTACTNPC
{// 0x0090 (144)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
	/* this+6 */ unsigned char type;
};


struct PACKET_CZ_REQNAME
{// 0x0094 (148)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_ACK_REQNAME
{// 0x0095 (149)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char CName[24];
};


struct PACKET_CZ_WHISPER
{// 0x0096 (150)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ char receiver[24];
	/* this+28 */ char Text[];
};


struct PACKET_ZC_WHISPER
{// 0x0097 (151)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ char sender[24];
	/* this+28 */ BOOL isAdmin;
	/* this+32 */ char Text[];
};


struct PACKET_ZC_ACK_WHISPER
{// 0x0098 (152)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_CZ_BROADCAST
{// 0x0099 (153)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_ZC_BROADCAST
{// 0x009A (154)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_CZ_CHANGE_DIRECTION
{// 0x009B (155)
	/* this+0 */ short PacketType;
	/* this+2 */ short headDir;
	/* this+4 */ unsigned char dir;
};


struct PACKET_ZC_CHANGE_DIRECTION
{// 0x009C (156)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short headDir;
	/* this+8 */ unsigned char dir;
};


struct PACKET_ZC_ITEM_ENTRY
{// 0x009D (157)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long ITAID;
	/* this+ 6 */ unsigned short ITID;
	/* this+ 8 */ bool IsIdentified;
	/* this+ 9 */ short xPos;
	/* this+11 */ short yPos;
	/* this+13 */ short count;
	/* this+15 */ unsigned char subX;
	/* this+16 */ unsigned char subY;
};


struct PACKET_ZC_ITEM_FALL_ENTRY
{// 0x009E (158)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long ITAID;
	/* this+ 6 */ unsigned short ITID;
	/* this+ 8 */ bool IsIdentified;
	/* this+ 9 */ short xPos;
	/* this+11 */ short yPos;
	/* this+13 */ unsigned char subX;
	/* this+14 */ unsigned char subY;
	/* this+15 */ short count;
};


struct PACKET_CZ_ITEM_PICKUP
{// 0x009F (159)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long ITAID;
};


struct PACKET_ZC_ITEM_PICKUP_ACK
{// 0x00A0 (160)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short Index;
	/* this+ 4 */ unsigned short count;
	/* this+ 6 */ unsigned short ITID;
	/* this+ 8 */ bool IsIdentified;
	/* this+ 9 */ bool IsDamaged;
	/* this+10 */ unsigned char refiningLevel;
	/* this+11 */ EQUIPSLOTINFO slot;
	/* this+19 */ unsigned short location;
	/* this+21 */ unsigned char type;
	/* this+22 */ unsigned char result;
};


struct PACKET_CZ_ITEM_THROW
{// 0x00A2 (162)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short Index;
	/* this+4 */ short count;
};


struct PACKET_CZ_USE_ITEM
{// 0x00A7 (167)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned long AID;
};


struct PACKET_ZC_USE_ITEM_ACK
{// 0x00A8 (168)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ short count;
	/* this+6 */ bool result;
};


struct PACKET_CZ_REQ_WEAR_EQUIP
{// 0x00A9 (169)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned short wearLocation;
};


struct PACKET_ZC_REQ_WEAR_EQUIP_ACK
{// 0x00AA (170)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned short wearLocation;
	/* this+6 */ unsigned short wItemSpriteNumber;
	/* this+8 */ unsigned char result;
};


struct PACKET_CZ_REQ_TAKEOFF_EQUIP
{// 0x00AB (171)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
};


struct PACKET_ZC_REQ_TAKEOFF_EQUIP_ACK
{// 0x00AC (172)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned short wearLocation;
	/* this+6 */ bool result;
};


struct PACKET_CZ_REQ_ITEM_EXPLANATION_BYNAME /// @custom
{// 0x00AD (173)
	/* this+0 */ short PacketType;
	/* this+2 */ short unknown;
};


struct PACKET_ZC_REQ_ITEM_EXPLANATION_ACK /// @custom
{// 0x00AE (174)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ BYTE unknown[];
};


struct PACKET_CZ_RESTART
{// 0x00B2 (178)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
};


struct PACKET_ZC_RESTART_ACK
{// 0x00B3 (179)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
};


struct PACKET_CZ_CHOOSE_MENU
{// 0x00B8 (184)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
	/* this+6 */ unsigned char num;
};


struct PACKET_CZ_REQ_NEXT_SCRIPT
{// 0x00B9 (185)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
};


struct PACKET_CZ_STATUS_CHANGE
{// 0x00BB (187)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short statusID;
	/* this+4 */ unsigned char changeAmount;
};


struct PACKET_ZC_STATUS_CHANGE_ACK
{// 0x00BC (188)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short statusID;
	/* this+4 */ bool result;
	/* this+5 */ unsigned char value;
};


struct PACKET_CZ_REQ_EMOTION
{// 0x00BF (191)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
};


struct PACKET_CZ_REQ_USER_COUNT
{// 0x00C1 (193)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_USER_COUNT
{// 0x00C2 (194)
	/* this+0 */ short PacketType;
	/* this+2 */ int count;
};


struct PACKET_ZC_SELECT_DEALTYPE
{// 0x00C4 (196)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
};


struct PACKET_CZ_ACK_SELECT_DEALTYPE
{// 0x00C5 (197)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
	/* this+6 */ unsigned char type;
};


struct PACKET_ZC_PC_PURCHASE_ITEMLIST
{// 0x00C6 (198)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ PURCHASE_ITEM Item[];
};


struct PACKET_ZC_PC_SELL_ITEMLIST
{// 0x00C7 (199)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ SELL_ITEM Item[];
};


struct PACKET_CZ_PC_PURCHASE_ITEMLIST
{// 0x00C8 (200)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ CZ_PURCHASE_ITEM Item[];
};


struct PACKET_CZ_PC_SELL_ITEMLIST
{// 0x00C9 (201)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ CZ_SELL_ITEM Item[];
};


struct PACKET_ZC_PC_PURCHASE_RESULT
{// 0x00CA (202)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_ZC_PC_SELL_RESULT
{// 0x00CB (203)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_CZ_DISCONNECT_CHARACTER
{// 0x00CC (204)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_ACK_DISCONNECT_CHARACTER
{// 0x00CD (205)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_CZ_DISCONNECT_ALL_CHARACTER
{// 0x00CE (206)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_SETTING_WHISPER_PC
{// 0x00CF (207)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char name[24];
	/* this+26 */ unsigned char type;
};


struct PACKET_CZ_SETTING_WHISPER_STATE
{// 0x00D0 (208)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
};


struct PACKET_ZC_SETTING_WHISPER_PC
{// 0x00D1 (209)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
	/* this+3 */ unsigned char result;
};


struct PACKET_ZC_SETTING_WHISPER_STATE
{// 0x00D2 (210)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
	/* this+3 */ unsigned char result;
};


struct PACKET_CZ_REQ_WHISPER_LIST
{// 0x00D3 (211)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_WHISPER_LIST
{// 0x00D4 (212)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ char List[][24];
};


struct PACKET_CZ_CREATE_CHATROOM
{// 0x00D5 (213)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ short size;
	/* this+ 6 */ unsigned char type;
	/* this+ 7 */ char passwd[8];
	/* this+15 */ char title[];
};


struct PACKET_ZC_ACK_CREATE_CHATROOM
{// 0x00D6 (214)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_ZC_ROOM_NEWENTRY
{// 0x00D7 (215)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long roomID;
	/* this+12 */ short maxcount;
	/* this+14 */ short curcount;
	/* this+16 */ unsigned char type;
	/* this+17 */ char title[];
};


struct PACKET_ZC_DESTROY_ROOM
{// 0x00D8 (216)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long roomID;
};


struct PACKET_CZ_REQ_ENTER_ROOM
{// 0x00D9 (217)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long roomID;
	/* this+6 */ char passwd[8];
};


struct PACKET_ZC_REFUSE_ENTER_ROOM
{// 0x00DA (218)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_ZC_ENTER_ROOM
{// 0x00DB (219)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long roomID;
	/* this+8 */ ROOM_MEMBER_DATA Members[];
};


struct PACKET_ZC_MEMBER_NEWENTRY
{// 0x00DC (220)
	/* this+0 */ short PacketType;
	/* this+2 */ short curcount;
	/* this+4 */ char name[24];
};


struct PACKET_ZC_MEMBER_EXIT
{// 0x00DD (221)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short curcount;
	/* this+ 4 */ char name[24];
	/* this+28 */ unsigned char type;
};


struct PACKET_CZ_CHANGE_CHATROOM
{// 0x00DE (222)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ short size;
	/* this+ 6 */ unsigned char type;
	/* this+ 7 */ char passwd[8];
	/* this+15 */ char title[];
};


struct PACKET_ZC_CHANGE_CHATROOM
{// 0x00DF (223)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long roomID;
	/* this+12 */ short maxcount;
	/* this+14 */ short curcount;
	/* this+16 */ unsigned char type;
};


struct PACKET_CZ_REQ_ROLE_CHANGE
{// 0x00E0 (224)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long role;
	/* this+6 */ char name[24];
};


struct PACKET_ZC_ROLE_CHANGE
{// 0x00E1 (225)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long role;
	/* this+6 */ char name[24];
};


struct PACKET_CZ_REQ_EXPEL_MEMBER
{// 0x00E2 (226)
	/* this+0 */ short PacketType;
	/* this+2 */ char name[24];
};


struct PACKET_CZ_EXIT_ROOM
{// 0x00E3 (227)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQ_EXCHANGE_ITEM
{// 0x00E4 (228)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_REQ_EXCHANGE_ITEM
{// 0x00E5 (229)
	/* this+0 */ short PacketType;
	/* this+2 */ char name[24];
};


struct PACKET_CZ_ACK_EXCHANGE_ITEM
{// 0x00E6 (230)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_ZC_ACK_EXCHANGE_ITEM
{// 0x00E7 (231)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_CZ_ADD_EXCHANGE_ITEM
{// 0x00E8 (232)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;
};


struct PACKET_ZC_ADD_EXCHANGE_ITEM
{// 0x00E9 (233)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int count;
	/* this+ 6 */ unsigned short ITID;
	/* this+ 8 */ bool IsIdentified;
	/* this+ 9 */ bool IsDamaged;
	/* this+10 */ unsigned char refiningLevel;
	/* this+11 */ EQUIPSLOTINFO slot;
};


struct PACKET_ZC_ACK_ADD_EXCHANGE_ITEM
{// 0x00EA (234)
	/* this+0 */ short PacketType;
	/* this+2 */ short Index;
	/* this+4 */ unsigned char result;
};


struct PACKET_CZ_CONCLUDE_EXCHANGE_ITEM
{// 0x00EB (235)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_CONCLUDE_EXCHANGE_ITEM
{// 0x00EC (236)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char who;
};


struct PACKET_CZ_CANCEL_EXCHANGE_ITEM
{// 0x00ED (237)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_CANCEL_EXCHANGE_ITEM
{// 0x00EE (238)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_EXEC_EXCHANGE_ITEM
{// 0x00EF (239)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_EXEC_EXCHANGE_ITEM
{// 0x00F0 (240)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_ZC_EXCHANGEITEM_UNDO
{// 0x00F1 (241)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE
{// 0x00F3 (243)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;
};


struct PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY
{// 0x00F5 (245)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;
};


struct PACKET_CZ_CLOSE_STORE
{// 0x00F7 (247)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_CLOSE_STORE
{// 0x00F8 (248)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_MAKE_GROUP
{// 0x00F9 (249)
	/* this+0 */ short PacketType;
	/* this+2 */ char groupName[24];
};


struct PACKET_ZC_ACK_MAKE_GROUP
{// 0x00FA (250)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_CZ_REQ_JOIN_GROUP
{// 0x00FC (252)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_CZ_JOIN_GROUP
{// 0x00FF (255)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GRID;
	/* this+6 */ int answer;
};


struct PACKET_CZ_REQ_LEAVE_GROUP
{// 0x0100 (256)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQ_EXPEL_GROUP_MEMBER
{// 0x0103 (259)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char characterName[24];
};


struct PACKET_ZC_NOTIFY_HP_TO_GROUPM
{// 0x0106 (262)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short hp;
	/* this+8 */ short maxhp;
};


struct PACKET_CZ_REQUEST_CHAT_PARTY
{// 0x0108 (264)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_ZC_NOTIFY_CHAT_PARTY
{// 0x0109 (265)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long AID;
	/* this+8 */ char Text[];
};


struct PACKET_CZ_UPGRADE_SKILLLEVEL
{// 0x0112 (274)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;
};


struct PACKET_CZ_USE_SKILL
{// 0x0113 (275)
	/* this+0 */ short PacketType;
	/* this+2 */ short selectedLevel;
	/* this+4 */ unsigned short SKID;
	/* this+6 */ unsigned long targetID;
};


struct PACKET_CZ_USE_SKILL_TOGROUND
{// 0x0116 (278)
	/* this+0 */ short PacketType;
	/* this+2 */ short selectedLevel;
	/* this+4 */ unsigned short SKID;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;
};


struct PACKET_CZ_CANCEL_LOCKON
{// 0x0118 (280)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_STATE_CHANGE
{// 0x0119 (281)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ short bodyState;
	/* this+ 8 */ short healthState;
	/* this+10 */ short effectState;
	/* this+12 */ bool isPKModeON;
};


struct PACKET_ZC_NOTIFY_CARTITEM_COUNTINFO
{// 0x0121 (289)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short curCount;
	/* this+ 4 */ short maxCount;
	/* this+ 6 */ int curWeight;
	/* this+10 */ int maxWeight;
};


struct PACKET_ZC_CART_NORMAL_ITEMLIST
{// 0x0123 (291)
	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ BYTE todo[];
};


struct PACKET_CZ_ITEM_CREATE
{// 0x013F (319)
	/* this+0 */ short PacketType;
	/* this+2 */ char itemName[24];
};


struct PACKET_CZ_MOVETO_MAP
{// 0x0140 (320)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char mapName[16];
	/* this+18 */ short xPos;
	/* this+20 */ short yPos;
};


struct PACKET_CZ_CLOSE_DIALOG
{// 0x0146 (326)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
};


struct PACKET_CZ_REQ_GUILD_MENUINTERFACE
{// 0x014D (333)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_ACK_GUILD_MENUINTERFACE
{// 0x014E (334)
	/* this+0 */ short PacketType;
	/* this+2 */ int guildMemuFlag;
};


struct PACKET_CZ_REQ_GUILD_MENU
{// 0x014F (335)
	/* this+0 */ short PacketType;
	/* this+2 */ int Type;
};


struct PACKET_ZC_GUILD_INFO
{// 0x0150 (336)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int GDID;
	/* this+ 6 */ int level;
	/* this+10 */ int userNum;
	/* this+14 */ int maxUserNum;
	/* this+18 */ int userAverageLevel;
	/* this+22 */ int exp;
	/* this+26 */ int maxExp;
	/* this+30 */ int point;
	/* this+34 */ int honor;
	/* this+38 */ int virtue;
	/* this+42 */ int emblemVersion;
	/* this+46 */ char guildname[24];
	/* this+70 */ char masterName[24];
	/* this+94 */ char manageLand[16];
};


struct PACKET_CZ_REQ_GUILD_EMBLEM_IMG
{// 0x0151 (337)
	/* this+0 */ short PacketType;
	/* this+2 */ int GDID;
};


struct PACKET_ZC_GUILD_EMBLEM_IMG
{// 0x0152 (338)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ int GDID;
	/* this+ 8 */ int emblemVersion;
	/* this+12 */ char Emblem[];
};


struct PACKET_CZ_REQ_JOIN_GUILD
{// 0x0168 (360)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long MyAID;
	/* this+10 */ unsigned long MyGID;
};


struct PACKET_ZC_REQ_JOIN_GUILD
{// 0x016A (362)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GDID;
	/* this+6 */ char guildName[24];
};


struct PACKET_CZ_JOIN_GUILD
{// 0x016B (363)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GDID;
	/* this+6 */ int answer;
};


struct PACKET_CZ_REQ_ITEMIDENTIFY
{// 0x0178 (376)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
};


struct PACKET_ZC_ACK_ITEMIDENTIFY
{// 0x0179 (377)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ unsigned char result;
};


struct PACKET_PING
{// 0x0187 (391)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_CZ_REQ_DISCONNECT
{// 0x018A (394)
	/* this+0 */ short PacketType;
	/* this+2 */ short type;
};


struct PACKET_ZC_ACK_REQ_DISCONNECT
{// 0x018B (395)
	/* this+0 */ short PacketType;
	/* this+2 */ short result;
};


struct PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX
{// 0x0190 (400)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short selectedLevel;
	/* this+ 4 */ unsigned short SKID;
	/* this+ 6 */ short xPos;
	/* this+ 8 */ short yPos;
	/* this+10 */ char contents[80];
};


struct PACKET_ZC_TALKBOX_CHATCONTENTS
{// 0x0191 (401)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char contents[80];
};


struct PACKET_CZ_REQNAME_BYGID
{// 0x0193 (403)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
};


struct PACKET_ZC_ACK_REQNAME_BYGID
{// 0x0194 (404)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char CName[24];
};


struct PACKET_CZ_RESET
{// 0x0197 (407)
	/* this+0 */ short PacketType;
	/* this+2 */ short type;
};


struct PACKET_CZ_LOCALBROADCAST /// @custom
{// 0x019C (412)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_CZ_REQ_MAKINGARROW
{// 0x01AE (430)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short id;
};


struct PACKET_CZ_REQ_CHANGECART
{// 0x01AF (431)
	/* this+0 */ short PacketType;
	/* this+2 */ short num;
};


struct PACKET_CZ_GUILD_ZENY
{// 0x01B7 (439)
	/* this+0 */ short PacketType;
	/* this+2 */ int zeny;
};


struct PACKET_ZC_GUILD_ZENY_ACK
{// 0x01B8 (440)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ret;
};


struct PACKET_CZ_REMOVE_AID
{// 0x01BA (442)
	/* this+0 */ short PacketType;
	/* this+2 */ char AccountName[24];
};


struct PACKET_CZ_SHIFT
{// 0x01BB (443)
	/* this+0 */ short PacketType;
	/* this+2 */ char CharacterName[24];
};


struct PACKET_CZ_RECALL
{// 0x01BC (444)
	/* this+0 */ short PacketType;
	/* this+2 */ char AccountName[24];
};


struct PACKET_CZ_RECALL_GID
{// 0x01BD (445)
	/* this+0 */ short PacketType;
	/* this+2 */ char AccountName[24];
};


struct PACKET_CZ_REQ_REMAINTIME
{// 0x01C0 (448)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_REPLY_REMAINTIME
{// 0x01C1 (449)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int Result;
	/* this+ 6 */ int ExpirationDate;
	/* this+10 */ int RemainTime;
};


struct PACKET_ZC_INFO_REMAINTIME
{// 0x01C2 (450)
	/* this+0 */ short PacketType;
	/* this+2 */ int Type;
	/* this+6 */ int RemainTime;
};


struct PACKET_ZC_USE_ITEM_ACK2
{// 0x01C8 (456)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short index;
	/* this+ 4 */ unsigned short id;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ short count;
	/* this+12 */ bool result;
};


struct PACKET_CZ_REQMAKINGHOMUN
{// 0x01CA (458)
	/* this+0 */ short PacketType;
	/* this+2 */ bool result;
};


struct PACKET_CZ_REQ_ACCOUNTNAME
{// 0x01DF (479)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_ACK_ACCOUNTNAME
{// 0x01E0 (480)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char name[24];
};


struct PACKET_ZC_REQ_COUPLE
{// 0x01E2 (482)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char name[24];
};


struct PACKET_CZ_JOIN_COUPLE
{// 0x01E3 (483)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int answer;
};


struct PACKET_ZC_START_COUPLE
{// 0x01E4 (484)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQ_JOIN_COUPLE
{// 0x01E5 (485)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_COUPLENAME
{// 0x01E6 (486)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char name[24];
};


struct PACKET_CZ_DORIDORI
{// 0x01E7 (487)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_CHOPOKGI
{// 0x01ED (493)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_REQ_EXCHANGE_ITEM2
{// 0x01F4 (500)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char name[24];
	/* this+26 */ unsigned long GID;
	/* this+30 */ short level;
};


struct PACKET_ZC_ACK_EXCHANGE_ITEM2
{// 0x01F5 (501)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
	/* this+3 */ unsigned long GID;
	/* this+7 */ short level;
};


struct PACKET_ZC_REQ_BABY
{// 0x01F6 (502)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char name[24];
};


struct PACKET_CZ_JOIN_BABY
{// 0x01F7 (503)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int answer;
};


struct PACKET_ZC_START_BABY
{// 0x01F8 (504)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQ_JOIN_BABY
{// 0x01F9 (505)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_CZ_REQ_ITEMREPAIR
{// 0x01FD (509)
	/* this+0 */ short PacketType;
	/* this+2 */ REPAIRITEM_INFO TargetItemInfo;
};


struct PACKET_ZC_ACK_ITEMREPAIR
{// 0x01FE (510)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ unsigned char result;
};


struct PACKET_ZC_STARSKILL
{// 0x020E (526)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char mapName[24];
	/* this+26 */ int monsterID;
	/* this+30 */ unsigned char star;
	/* this+31 */ unsigned char result;
};


struct PACKET_ZC_BABYMSG
{// 0x0216 (534)
	/* this+0 */ short PacketType;
	/* this+2 */ int MsgNo;
};


struct PACKET_CZ_LESSEFFECT
{// 0x021D (541)
	/* this+0 */ short PacketType;
	/* this+2 */ BOOL isLess;
};


struct PACKET_ZC_LESSEFFECT
{// 0x021E (542)
	/* this+0 */ short PacketType;
	/* this+2 */ BOOL isLess;
};


struct PACKET_CZ_REQ_WEAPONREFINE
{// 0x0222 (546)
	/* this+0 */ short PacketType;
	/* this+2 */ int Index;
};


struct PACKET_ZC_ACK_WEAPONREFINE
{// 0x0223 (547)
	/* this+0 */ short PacketType;
	/* this+2 */ int msg;
	/* this+6 */ unsigned short ITID;
};


struct PACKET_ZC_STATE_CHANGE3
{// 0x0229 (553)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ short bodyState;
	/* this+ 8 */ short healthState;
	/* this+10 */ int effectState;
	/* this+14 */ bool isPKModeON;
};


struct PACKET_CZ_REQUEST_ACTNPC
{// 0x0233 (563)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long targetGID;
	/* this+10 */ unsigned char action;
};


struct PACKET_CZ_AGREE_STARPLACE
{// 0x0254 (596)
	/* this+0 */ short PacketType;
	/* this+2 */ char which;
};


struct PACKET_ZC_READ_BOOK
{// 0x0294 (660)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long bookID;
	/* this+6 */ unsigned long page;
};


struct PACKET_CZ_MER_COMMAND
{// 0x029F (671)
	enum
	{
		COMMAND_REQ_NONE     = 0,
		COMMAND_REQ_PROPERTY = 1,
		COMMAND_REQ_DELETE   = 2,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ char command;
};


struct PACKET_CZ_PARTY_JOIN_REQ
{// 0x02C4 (708)
	/* this+0 */ short PacketType;
	/* this+2 */ char characterName[24];
};


struct PACKET_ZC_PARTY_JOIN_REQ_ACK
{// 0x02C5 (709)
	enum enumAnswer
	{
		ANSWER_ALREADY_OTHERGROUPM    = 0,
		ANSWER_MEMBER_OVERSIZE        = 3,
		ANSWER_JOIN_ACCEPT            = 2,
		ANSWER_JOIN_REFUSE            = 1,
		ANSWER_DUPLICATE              = 4,
		ANSWER_JOINMSG_REFUSE         = 5,
		ANSWER_UNKNOWN_ERROR          = 6,
		ANSWER_UNKNOWN_CHARACTER      = 7,
		ANSWER_INVALID_MAPPROPERTY    = 8,
		ANSWER_INVALID_MAPPROPERTY_ME = 9,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char characterName[24];
	/* this+26 */ enumAnswer answer;
};


struct PACKET_ZC_PARTY_JOIN_REQ
{// 0x02C6 (710)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GRID;
	/* this+6 */ char groupName[24];
};


struct PACKET_CZ_PARTY_JOIN_REQ_ACK
{// 0x02C7 (711)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GRID;
	/* this+6 */ bool bAccept;
};


struct PACKET_CZ_PARTY_CONFIG
{// 0x02C8 (712)
	/* this+0 */ short PacketType;
	/* this+2 */ bool bRefuseJoinMsg;
};


struct PACKET_ZC_PARTY_CONFIG
{// 0x02C9 (713)
	/* this+0 */ short PacketType;
	/* this+2 */ bool bRefuseJoinMsg;
};


struct PACKET_CZ_MEMORIALDUNGEON_COMMAND
{// 0x02CF (719)
	enum enumCOMMAND
	{
		COMMAND_SUBSCRIPTION_CANCEL           = 0,
		COMMAND_MEMORIALDUNGEON_DESTROY       = 1,
		COMMAND_MEMORIALDUNGEON_DESTROY_FORCE = 2,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ enumCOMMAND Command;
};


struct PACKET_CZ_EQUIPWIN_MICROSCOPE
{// 0x02D6 (726)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_CZ_CONFIG
{// 0x02D8 (728)
	enum enumConfig
	{
		CONFIG_OPEN_EQUIPMENT_WINDOW = 0,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ enumConfig Config;
	/* this+6 */ int Value;
};


struct PACKET_ZC_CONFIG
{// 0x02D9 (729)
	/* this+0 */ short PacketType;
	/* this+2 */ PACKET_CZ_CONFIG::enumConfig Config;
	/* this+6 */ int Value;
};


struct PACKET_ZC_ACCEPT_ENTER2
{// 0x02EB (747)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long startTime;
	/* this+ 6 */ unsigned char PosDir[3];
	/* this+ 9 */ unsigned char xSize;
	/* this+10 */ unsigned char ySize;
	/* this+11 */ short font;
};


struct PACKET_ZC_PROGRESS
{// 0x02F0 (752)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long color;
	/* this+6 */ unsigned long time;
};


struct PACKET_CZ_PROGRESS
{// 0x02F1 (753)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_PROGRESS_CANCEL
{// 0x02F2 (754)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQUEST_MOVE2
{// 0x035F (863)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char dest[3];
};


struct PACKET_CZ_REQUEST_TIME2
{// 0x0360 (864)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long clientTime;
};


struct PACKET_CZ_CHANGE_DIRECTION2
{// 0x0361 (865)
	/* this+0 */ short PacketType;
	/* this+2 */ short headDir;
	/* this+4 */ unsigned char dir;
};


struct PACKET_CZ_ITEM_PICKUP2
{// 0x0362 (866)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long ITAID;
};


struct PACKET_CZ_ITEM_THROW2
{// 0x0363 (867)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short Index;
	/* this+4 */ short count;
};


struct PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE2
{// 0x0364 (868)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;
};


struct PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2
{// 0x0365 (869)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;
};


struct PACKET_CZ_USE_SKILL_TOGROUND2
{// 0x0366 (870)
	/* this+0 */ short PacketType;
	/* this+2 */ short selectedLevel;
	/* this+4 */ unsigned short SKID;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;
};


struct PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2
{// 0x0367 (871)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short selectedLevel;
	/* this+ 4 */ unsigned short SKID;
	/* this+ 6 */ short xPos;
	/* this+ 8 */ short yPos;
	/* this+10 */ char contents[80];
};


struct PACKET_CZ_REQNAME2
{// 0x0368 (872)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_CZ_REQNAME_BYGID2
{// 0x0369 (873)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
};


struct PACKET_CZ_ENTER2
{// 0x0436 (1078)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int AuthCode;
	/* this+14 */ unsigned long clientTime;
	/* this+18 */ unsigned char Sex;
};


struct PACKET_CZ_REQUEST_ACT2
{// 0x0437 (1079)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long targetGID;
	/* this+6 */ unsigned char action;
};


struct PACKET_CZ_USE_SKILL2
{// 0x0438 (1080)
	/* this+0 */ short PacketType;
	/* this+2 */ short selectedLevel;
	/* this+4 */ unsigned short SKID;
	/* this+6 */ unsigned long targetID;
};


struct PACKET_CZ_USE_ITEM2
{// 0x0439 (1081)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned long AID;
};


struct PACKET_ZC_SKILL_SELECT_REQUEST
{// 0x0442 (1090)
	enum enumWHY
	{
		WHY_LOWERVER_COMPATIBILITY = 0,
		WHY_SC_AUTOSHADOWSPELL     = 1,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ enumWHY why;
};


struct PACKET_CZ_SKILL_SELECT_RESPONSE
{// 0x0443 (1091)
	/* this+0 */ short PacketType;
	/* this+2 */ PACKET_ZC_SKILL_SELECT_REQUEST::enumWHY why;
	/* this+6 */ unsigned short SKID;
};


struct PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM
{// 0x0445 (1093)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short ITID;
	/* this+4 */ short count;
};


struct PACKET_CZ_BLOCKING_PLAY_CANCEL
{// 0x0447 (1095)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_CLIENT_VERSION
{// 0x044A (1098)
	/* this+0 */ short PacketType;
	/* this+2 */ long clientVer;
};


struct PACKET_CZ_GROUPINFO_CHANGE_V2
{// 0x07D7 (2007)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long expOption;
	/* this+6 */ unsigned char ItemPickupRule;
	/* this+7 */ unsigned char ItemDivisionRule;
};


namespace ItemListWinPacket {
enum Type
{
	TYPE_CHANGEMATERIAL          = 0,
	TYPE_EL_ANALYSIS_DISASSEMBLY = 1,
	TYPE_EL_ANALYSIS_COMBINATION = 2,
};
enum Action
{
	ACTION_CANCEL = 0,
	ACTION_OK     = 1,
};
};// namespace


struct PACKET_ZC_ITEMLISTWIN_OPEN
{// 0x07E3 (2019)
	/* this+0 */ short PacketType;
	/* this+2 */ ItemListWinPacket::Type Type;
};


struct PACKET_CZ_ITEMLISTWIN_RES
{// 0x07E4 (2020)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ ItemListWinPacket::Type Type;
	/* this+ 8 */ ItemListWinPacket::Action Action;
	/* this+12 */ BYTE unknown[];
};


struct PACKET_CZ_GM_FULLSTRIP
{// 0x07F5 (2037)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long TargetAID;
};


struct PACKET_CZ_SE_CASHSHOP_OPEN
{// 0x0844 (2116)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_MACRO_USE_SKILL
{// 0x084C (2124)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;
	/* this+4 */ short selectedLevel;
	/* this+6 */ unsigned long targetID;
};


struct PACKET_CZ_MACRO_USE_SKILL_TOGROUND
{// 0x084D (2125)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;
	/* this+4 */ short selectedLevel;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;
};


struct PACKET_CZ_MACRO_REQUEST_MOVE
{// 0x084E (2126)
	enum { DESTSIZE = 3 };
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char dest[DESTSIZE];
};


struct PACKET_CZ_MACRO_ITEM_PICKUP
{// 0x084F (2127)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long ITAID;
};


struct PACKET_CZ_MACRO_REQUEST_ACT
{// 0x0850 (2128)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char action;
	/* this+3 */ unsigned long targetGID;
};


struct PACKET_ZC_GPK_DYNCODE
{// 0x0851 (2129)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ BYTE unknown[];
};


struct PACKET_CZ_GPK_DYNCODE_RELOAD
{// 0x0852 (2130)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_GPK_AUTH
{// 0x0853 (2131)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ BYTE unknown[];
};


struct PACKET_CZ_GPK_AUTH
{// 0x0854 (2132)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ BYTE unknown[];
};


struct PACKET_CZ_REASSEMBLY_AUTH
{// 0x0884-0x08AD, 0x0941-0x096A (2180-2221, 2369-2410)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_TRYCOLLECTION
{// 0x08B5 (2229)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long targetAID;
};


struct PACKET_ZC_TRYCOLLECTION
{// 0x08B6 (2230)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_CZ_MACRO_START
{// 0x08C1 (2241)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_MACRO_STOP
{// 0x08C2 (2242)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQ_SCHEDULER_CASHITEM
{// 0x08C9 (2249)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQ_ENTRY_QUEUE_APPLY
{// 0x08D7 (2263)
	enum
	{
		SOLO  = 1,
		PARTY = 2,
		GUILD = 4,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short ApplyType;
	/* this+4 */ char EntryQueueName[24];
};


struct PACKET_ZC_ACK_ENTRY_QUEUE_APPLY
{// 0x08D8 (2264)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char Result;
	/* this+3 */ char EntryQueueName[24];
};


struct PACKET_ZC_NOTIFY_ENTRY_QUEUE_APPLY
{// 0x08D9 (2265)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char EntryQueueName[24];
	/* this+26 */ int Ranking;
};


struct PACKET_CZ_REQ_ENTRY_QUEUE_CANCEL
{// 0x08DA (2266)
	/* this+0 */ short PacketType;
	/* this+2 */ char EntryQueueName[24];
};


struct PACKET_ZC_ACK_ENTRY_QUEUE_CANCEL
{// 0x08DB (2267)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char Result;
	/* this+3 */ char EntryQueueName[24];
};


struct PACKET_ZC_NOTIFY_ENTRY_QUEUE_ADMISSION
{// 0x08DC (2268)
	/* this+0 */ short PacketType;
	/* this+2 */ char EntryQueueName[24];
};


struct PACKET_CZ_REPLY_ENTRY_QUEUE_ADMISSION
{// 0x08DD (2269)
	enum
	{
		ACCEPT = 1,
		REFUSE = 2,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char Result;
	/* this+3 */ char EntryQueueName[24];
};


struct PACKET_ZC_REPLY_ACK_ENTRY_QUEUE_ADMISSION
{// 0x08DE (2270)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char Result;
	/* this+3 */ char EntryQueueName[24];
};


struct PACKET_ZC_NOTIFY_LOBBY_ADMISSION
{// 0x08DF (2271)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char EntryQueueName[24];
	/* this+26 */ char LobbyName[24];
};


struct PACKET_CZ_REPLY_LOBBY_ADMISSION
{// 0x08E0 (2272)
	enum
	{
		ACCEPT = 1,
		REFUSE = 2,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char Result;
	/* this+ 3 */ char EntryQueueName[24];
	/* this+27 */ char LobbyName[24];
};


struct PACKET_ZC_REPLY_ACK_LOBBY_ADMISSION
{// 0x08E1 (2273)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char Result;
	/* this+ 3 */ char EntryQueueName[24];
	/* this+27 */ char LobbyName[24];
};


struct PACKET_CZ_INVENTORY_TAB
{// 0x0907 (2311)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short Index;
	/* this+4 */ bool NORMALorPRIVATE;
};


struct PACKET_ZC_INVENTORY_TAB
{// 0x0908 (2312)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short Index;
	/* this+4 */ bool NORMALorPRIVATE;
};


struct PACKET_CZ_REQ_ENTRY_QUEUE_RANKING
{// 0x090A (2314)
	/* this+0 */ short PacketType;
	/* this+2 */ char EntryQueueName[24];
};


struct PACKET_CZ_REQ_JOIN_GUILD2
{// 0x0916 (2326)
	/* this+0 */ short PacketType;
	/* this+2 */ char characterName[24];
};


struct PACKET_CZ_REQ_MERGE_ITEM
{// 0x096E (2414)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ BYTE unknown[];
};


struct PACKET_ZC_ACK_MERGE_ITEM
{// 0x096F (2415)
	enum
	{
		SUCCESS               = 0,
		FAILED_NOT_MERGE_ITEM = 1,
		FAILED_MAX_COUNT      = 2,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short item_index;
	/* this+4 */ unsigned short item_count;
	/* this+6 */ unsigned char Result;
};


struct PACKET_CZ_CANCEL_MERGE_ITEM
{// 0x0974 (2420)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQ_RANKING
{// 0x097C (2428)
	/* this+0 */ short PacketType;
	/* this+2 */ short RankingType;
};


struct PACKET_ZC_ACK_RANKING
{// 0x097D (2429)
	/* this+  0 */ short PacketType;
	/* this+  2 */ short RankingType;
	/* this+  4 */ char CharName[10][24];
	/* this+244 */ int Point[10];
	/* this+284 */ int myPoint;
};


struct PACKET_CZ_SELECTCART
{// 0x0980 (2432)
	/* this+0 */ short PacketType;
	/* this+2 */ int Identity;
	/* this+6 */ unsigned char type;
};


struct PACKET_CZ_CLAN_CHAT
{// 0x098D (2445)
	enum { MAX_MSG_LENGTH = 220 };
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ BYTE unknown[];
};


struct PACKET_ZC_NPROTECTGAMEGUARDCSAUTH
{// 0x09CF (2511)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ BYTE unknown[];
};


struct PACKET_CZ_ITEM_CREATE_EX
{// 0x09CE (2510)
	enum { STRING_LENGTH = 100 };
	/* this+0 */ short PacketType;
	/* this+2 */ char itemName[100];
};


struct PACKET_CZ_NPROTECTGAMEGUARDCSAUTH
{// 0x09D0 (2512)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ BYTE unknown[];
};


///////////////////////////////////////
#pragma pack(pop)
