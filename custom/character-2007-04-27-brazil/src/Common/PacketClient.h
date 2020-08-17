#pragma once
#include "PacketStruct.h"
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
//	HEADER_XX                                      = 114, // missing
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
//	HEADER_XX                                      = 126, // missing
	HEADER_ZC_NOTIFY_TIME                          = 127,
	HEADER_ZC_NOTIFY_VANISH                        = 128,
	HEADER_SC_NOTIFY_BAN                           = 129,
	HEADER_CZ_REQUEST_QUIT                         = 130,
	HEADER_ZC_ACCEPT_QUIT                          = 131,
	HEADER_ZC_REFUSE_QUIT                          = 132,
//	HEADER_XX                                      = 133, // missing
	HEADER_ZC_NOTIFY_MOVE                          = 134,
	HEADER_ZC_NOTIFY_PLAYERMOVE                    = 135,
	HEADER_ZC_STOPMOVE                             = 136,
//	HEADER_XX                                      = 137, // missing
	HEADER_ZC_NOTIFY_ACT                           = 138,
	HEADER_ZC_NOTIFY_ACT_POSITION                  = 139,
//	HEADER_XX                                      = 140, // missing
	HEADER_ZC_NOTIFY_CHAT                          = 141,
	HEADER_ZC_NOTIFY_PLAYERCHAT                    = 142,
	HEADER_SERVER_ENTRY_ACK                        = 143,
	HEADER_CZ_CONTACTNPC                           = 144,
	HEADER_ZC_NPCACK_MAPMOVE                       = 145,
	HEADER_ZC_NPCACK_SERVERMOVE                    = 146,
	HEADER_ZC_NPCACK_ENABLE                        = 147,
//	HEADER_XX                                      = 148, // missing
	HEADER_ZC_ACK_REQNAME                          = 149,
	HEADER_CZ_WHISPER                              = 150,
	HEADER_ZC_WHISPER                              = 151,
	HEADER_ZC_ACK_WHISPER                          = 152,
	HEADER_CZ_BROADCAST                            = 153,
	HEADER_ZC_BROADCAST                            = 154,
//	HEADER_XX                                      = 155, // missing
	HEADER_ZC_CHANGE_DIRECTION                     = 156,
	HEADER_ZC_ITEM_ENTRY                           = 157,
	HEADER_ZC_ITEM_FALL_ENTRY                      = 158,
//	HEADER_XX                                      = 159, // missing
	HEADER_ZC_ITEM_PICKUP_ACK                      = 160,
	HEADER_ZC_ITEM_DISAPPEAR                       = 161,
//	HEADER_XX                                      = 162, // missing
	HEADER_ZC_NORMAL_ITEMLIST                      = 163,
	HEADER_ZC_EQUIPMENT_ITEMLIST                   = 164,
	HEADER_ZC_STORE_NORMAL_ITEMLIST                = 165,
	HEADER_ZC_STORE_EQUIPMENT_ITEMLIST             = 166,
//	HEADER_XX                                      = 167, // missing
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
//	HEADER_XX                                      = 243, // missing
	HEADER_ZC_ADD_ITEM_TO_STORE                    = 244,
//	HEADER_XX                                      = 245, // missing
	HEADER_ZC_DELETE_ITEM_FROM_STORE               = 246,
//	HEADER_XX                                      = 247, // missing
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
//	HEADER_XX                                      = 275, // missing
	HEADER_ZC_NOTIFY_SKILL                         = 276,
	HEADER_ZC_NOTIFY_SKILL_POSITION                = 277,
//	HEADER_XX                                      = 278, // missing
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
	HEADER_ZC_ACK_OPEN_MEMBER_INFO                 = 344,
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
//	HEADER_XX                                      = 400, // missing
	HEADER_ZC_TALKBOX_CHATCONTENTS                 = 401,
	HEADER_ZC_UPDATE_MAPINFO                       = 402,
//	HEADER_XX                                      = 403, // missing
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
//	HEADER_ZH_MOVE_PVPWORLD                        = 529,
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
//	HEADER_XX                                      = 640, // missing
//	HEADER_XX                                      = 641, // missing
//	HEADER_XX                                      = 642, // missing
//	HEADER_XX                                      = 643, // missing
//	HEADER_XX                                      = 644, // missing
//	HEADER_XX                                      = 645, // missing
//	HEADER_XX                                      = 646, // missing
//	HEADER_XX                                      = 647, // missing
//	HEADER_XX                                      = 648, // missing
//	HEADER_XX                                      = 649, // missing
//	HEADER_XX                                      = 650, // missing
	HEADER_HC_CHARNOTBEENSELECTED                  = 651,
	HEADER_CH_SELECT_CHAR_GOINGTOBEUSED            = 652,
	HEADER_CH_REQ_IS_VALID_CHARNAME                = 653,
	HEADER_HC_ACK_IS_VALID_CHARNAME                = 654,
	HEADER_CH_REQ_CHANGE_CHARNAME                  = 655,
	HEADER_HC_ACK_CHANGE_CHARNAME                  = 656,
//	HEADER_XX                                      = 657, // missing
//	HEADER_XX                                      = 658, // missing
//	HEADER_XX                                      = 659, // missing
//	HEADER_XX                                      = 660, // missing
//	HEADER_XX                                      = 661, // missing
//	HEADER_XX                                      = 662, // missing
//	HEADER_XX                                      = 663, // missing
//	HEADER_XX                                      = 664, // missing
//	HEADER_XX                                      = 665, // missing
//	HEADER_XX                                      = 666, // missing
//	HEADER_XX                                      = 667, // missing
//	HEADER_XX                                      = 668, // missing
//	HEADER_XX                                      = 669, // missing
//	HEADER_XX                                      = 670, // missing
//	HEADER_XX                                      = 671, // missing
//	HEADER_XX                                      = 672, // missing
//	HEADER_XX                                      = 673, // missing
//	HEADER_XX                                      = 674, // missing
//	HEADER_XX                                      = 675, // missing
//	HEADER_XX                                      = 676, // missing
//	HEADER_XX                                      = 677, // missing
//	HEADER_XX                                      = 678, // missing
//	HEADER_XX                                      = 679, // missing
//	HEADER_XX                                      = 680, // missing
//	HEADER_XX                                      = 681, // missing
//	HEADER_XX                                      = 682, // missing
//	HEADER_XX                                      = 683, // missing
//	HEADER_XX                                      = 684, // missing
	HEADER_AC_REQUEST_SECOND_PASSWORD              = 685,
	HEADER_LAST                                    = 686,
};


struct PACKET_CH_ENTER
{// 101
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ int AuthCode;
	/* this+10 */ unsigned long userLevel;
	/* this+14 */ unsigned short clientType;
	/* this+16 */ unsigned char Sex;
};


struct PACKET_CH_SELECT_CHAR
{// 102
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char CharNum;
};


struct PACKET_CH_MAKE_CHAR
{// 103
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char name[24];
	/* this+26 */ unsigned char Str;
	/* this+27 */ unsigned char Agi;
	/* this+28 */ unsigned char Vit;
	/* this+29 */ unsigned char Int;
	/* this+30 */ unsigned char Dex;
	/* this+31 */ unsigned char Luk;
	/* this+32 */ unsigned char CharNum;
	/* this+33 */ short headPal;
	/* this+35 */ short head;
};


struct PACKET_CH_DELETE_CHAR
{// 104
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char key[40];
};


struct PACKET_HC_AID_RAW
{// N/A
	/* this+0 */ unsigned long AID;
};


struct PACKET_HC_ACCEPT_ENTER
{// 107
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ CHARACTER_INFO CharInfo[];
};


struct PACKET_HC_REFUSE_ENTER
{// 108
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode;
};


struct PACKET_HC_ACCEPT_MAKECHAR
{// 109
	/* this+0 */ short PacketType;
	/* this+2 */ CHARACTER_INFO charinfo;
};


struct PACKET_HC_REFUSE_MAKECHAR
{// 110
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode;
};


struct PACKET_HC_ACCEPT_DELETECHAR
{// 111
	/* this+0 */ short PacketType;
};


struct PACKET_HC_REFUSE_DELETECHAR
{// 112
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode;
};


struct PACKET_HC_NOTIFY_ZONESVR
{// 113
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned char mapName[15+1];
	/* this+22 */ ZSERVER_ADDR addr;
};


struct PACKET_SC_NOTIFY_BAN
{// 129
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode; // enum BAN_*
};


struct PACKET_COLLECTORDEAD
{// 390
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long ServerID;
};


struct PACKET_PING
{// 391
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


/// @see PacketServer.h
//struct PACKET_INFO_REMAINTIME
//{// 450
//	/* this+ 0 */ short PacketType;
//	/* this+ 2 */ int AID;
//	/* this+ 6 */ int Type;
//	/* this+10 */ int RemainTime;
//};


struct PACKET_CH_DELETE_CHAR2
{// 507
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char key[50];
};


/// @see PacketServer.h
//struct PACKET_ZH_MOVE_PVPWORLD
//{// 529
//	/* this+0 */ short PacketType;
//	/* this+2 */ unsigned long GID;
//};


struct PACKET_CZ_ACK_STORE_PASSWORD
{// 571
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short Type;
	/* this+ 4 */ unsigned char Password[16];
	/* this+20 */ unsigned char NewPassword[16];
};


struct PACKET_HC_REQUEST_CHARACTER_PASSWORD
{// 574
	/* this+0 */ short PacketType;
	/* this+2 */ short Result;
	/* this+4 */ DWORD dwSeed;
};


///////////////////////////////////////
#pragma pack(pop)
