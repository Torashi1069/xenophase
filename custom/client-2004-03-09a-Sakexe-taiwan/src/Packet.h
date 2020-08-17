#pragma once
#include "Struct.h"
#pragma pack(push,1)


void __cdecl EncodePosDir(int srcx, int srcy, int srcdir, BYTE* result); // line 5374-5378
void __cdecl DecodePosDir(unsigned char* packet, int& x, int& y, int& dir);
void __cdecl EncodeSrcDst(int srcx, int srcy, int dstx, int dsty, int xcellpos, int ycellpos, BYTE* result);
void __cdecl DecodeSrcDst(unsigned char* packet, int& rsx, int& rsy, int& rdx, int& rdy, int& xcellpos, int& ycellpos); // line 5400-5411


enum PacketType
{
	HEADER_CA_LOGIN                          = 100,
	HEADER_CH_ENTER                          = 101,
	HEADER_CH_SELECT_CHAR                    = 102,
	HEADER_CH_MAKE_CHAR                      = 103,
	HEADER_CH_DELETE_CHAR                    = 104,
	HEADER_AC_ACCEPT_LOGIN                   = 105,
	HEADER_AC_REFUSE_LOGIN                   = 106,
	HEADER_HC_ACCEPT_ENTER                   = 107,
	HEADER_HC_REFUSE_ENTER                   = 108,
	HEADER_HC_ACCEPT_MAKECHAR                = 109,
	HEADER_HC_REFUSE_MAKECHAR                = 110,
	HEADER_HC_ACCEPT_DELETECHAR              = 111,
	HEADER_HC_REFUSE_DELETECHAR              = 112,
	HEADER_HC_NOTIFY_ZONESVR                 = 113,
	HEADER_CZ_ENTER                          = 114,
	HEADER_ZC_ACCEPT_ENTER                   = 115,
	HEADER_ZC_REFUSE_ENTER                   = 116,
	HEADER_ZC_NOTIFY_INITCHAR                = 117,
	HEADER_ZC_NOTIFY_UPDATECHAR              = 118,
	HEADER_ZC_NOTIFY_UPDATEPLAYER            = 119,
	HEADER_ZC_NOTIFY_STANDENTRY              = 120,
	HEADER_ZC_NOTIFY_NEWENTRY                = 121,
	HEADER_ZC_NOTIFY_ACTENTRY                = 122,
	HEADER_ZC_NOTIFY_MOVEENTRY               = 123,
	HEADER_ZC_NOTIFY_STANDENTRY_NPC          = 124,
	HEADER_CZ_NOTIFY_ACTORINIT               = 125,
	HEADER_CZ_REQUEST_TIME                   = 126,
	HEADER_ZC_NOTIFY_TIME                    = 127,
	HEADER_ZC_NOTIFY_VANISH                  = 128,
	HEADER_SC_NOTIFY_BAN                     = 129,
	HEADER_CZ_REQUEST_QUIT                   = 130,
	HEADER_ZC_ACCEPT_QUIT                    = 131,
	HEADER_ZC_REFUSE_QUIT                    = 132,
	HEADER_CZ_REQUEST_MOVE                   = 133,
	HEADER_ZC_NOTIFY_MOVE                    = 134,
	HEADER_ZC_NOTIFY_PLAYERMOVE              = 135,
	HEADER_ZC_STOPMOVE                       = 136,
	HEADER_CZ_REQUEST_ACT                    = 137,
	HEADER_ZC_NOTIFY_ACT                     = 138,
	HEADER_ZC_NOTIFY_ACT_POSITION            = 139,
	HEADER_CZ_REQUEST_CHAT                   = 140,
	HEADER_ZC_NOTIFY_CHAT                    = 141,
	HEADER_ZC_NOTIFY_PLAYERCHAT              = 142,
	HEADER_SERVER_ENTRY_ACK                  = 143,
	HEADER_CZ_CONTACTNPC                     = 144,
	HEADER_ZC_NPCACK_MAPMOVE                 = 145,
	HEADER_ZC_NPCACK_SERVERMOVE              = 146,
	HEADER_ZC_NPCACK_ENABLE                  = 147,
	HEADER_CZ_REQNAME                        = 148,
	HEADER_ZC_ACK_REQNAME                    = 149,
	HEADER_CZ_WHISPER                        = 150,
	HEADER_ZC_WHISPER                        = 151,
	HEADER_ZC_ACK_WHISPER                    = 152,
	HEADER_CZ_BROADCAST                      = 153,
	HEADER_ZC_BROADCAST                      = 154,
	HEADER_CZ_CHANGE_DIRECTION               = 155,
	HEADER_ZC_CHANGE_DIRECTION               = 156,
	HEADER_ZC_ITEM_ENTRY                     = 157,
	HEADER_ZC_ITEM_FALL_ENTRY                = 158,
	HEADER_CZ_ITEM_PICKUP                    = 159,
	HEADER_ZC_ITEM_PICKUP_ACK                = 160,
	HEADER_ZC_ITEM_DISAPPEAR                 = 161,
	HEADER_CZ_ITEM_THROW                     = 162,
	HEADER_ZC_NORMAL_ITEMLIST                = 163,
	HEADER_ZC_EQUIPMENT_ITEMLIST             = 164,
	HEADER_ZC_STORE_NORMAL_ITEMLIST          = 165,
	HEADER_ZC_STORE_EQUIPMENT_ITEMLIST       = 166,
	HEADER_CZ_USE_ITEM                       = 167,
	HEADER_ZC_USE_ITEM_ACK                   = 168,
	HEADER_CZ_REQ_WEAR_EQUIP                 = 169,
	HEADER_ZC_REQ_WEAR_EQUIP_ACK             = 170,
	HEADER_CZ_REQ_TAKEOFF_EQUIP              = 171,
	HEADER_ZC_REQ_TAKEOFF_EQUIP_ACK          = 172,
	HEADER_CZ_REQ_ITEM_EXPLANATION_BYNAME    = 173,
	HEADER_ZC_REQ_ITEM_EXPLANATION_ACK       = 174,
	HEADER_ZC_ITEM_THROW_ACK                 = 175,
	HEADER_ZC_PAR_CHANGE                     = 176,
	HEADER_ZC_LONGPAR_CHANGE                 = 177,
	HEADER_CZ_RESTART                        = 178,
	HEADER_ZC_RESTART_ACK                    = 179,
	HEADER_ZC_SAY_DIALOG                     = 180,
	HEADER_ZC_WAIT_DIALOG                    = 181,
	HEADER_ZC_CLOSE_DIALOG                   = 182,
	HEADER_ZC_MENU_LIST                      = 183,
	HEADER_CZ_CHOOSE_MENU                    = 184,
	HEADER_CZ_REQ_NEXT_SCRIPT                = 185,
	HEADER_CZ_REQ_STATUS                     = 186,
	HEADER_CZ_STATUS_CHANGE                  = 187,
	HEADER_ZC_STATUS_CHANGE_ACK              = 188,
	HEADER_ZC_STATUS                         = 189,
	HEADER_ZC_STATUS_CHANGE                  = 190,
	HEADER_CZ_REQ_EMOTION                    = 191,
	HEADER_ZC_EMOTION                        = 192,
	HEADER_CZ_REQ_USER_COUNT                 = 193,
	HEADER_ZC_USER_COUNT                     = 194,
	HEADER_ZC_SPRITE_CHANGE                  = 195,
	HEADER_ZC_SELECT_DEALTYPE                = 196,
	HEADER_CZ_ACK_SELECT_DEALTYPE            = 197,
	HEADER_ZC_PC_PURCHASE_ITEMLIST           = 198,
	HEADER_ZC_PC_SELL_ITEMLIST               = 199,
	HEADER_CZ_PC_PURCHASE_ITEMLIST           = 200,
	HEADER_CZ_PC_SELL_ITEMLIST               = 201,
	HEADER_ZC_PC_PURCHASE_RESULT             = 202,
	HEADER_ZC_PC_SELL_RESULT                 = 203,
	HEADER_CZ_DISCONNECT_CHARACTER           = 204,
	HEADER_ZC_ACK_DISCONNECT_CHARACTER       = 205,
	HEADER_CZ_DISCONNECT_ALL_CHARACTER       = 206,
	HEADER_CZ_SETTING_WHISPER_PC             = 207,
	HEADER_CZ_SETTING_WHISPER_STATE          = 208,
	HEADER_ZC_SETTING_WHISPER_PC             = 209,
	HEADER_ZC_SETTING_WHISPER_STATE          = 210,
	HEADER_CZ_REQ_WHISPER_LIST               = 211,
	HEADER_ZC_WHISPER_LIST                   = 212,
	HEADER_CZ_CREATE_CHATROOM                = 213,
	HEADER_ZC_ACK_CREATE_CHATROOM            = 214,
	HEADER_ZC_ROOM_NEWENTRY                  = 215,
	HEADER_ZC_DESTROY_ROOM                   = 216,
	HEADER_CZ_REQ_ENTER_ROOM                 = 217,
	HEADER_ZC_REFUSE_ENTER_ROOM              = 218,
	HEADER_ZC_ENTER_ROOM                     = 219,
	HEADER_ZC_MEMBER_NEWENTRY                = 220,
	HEADER_ZC_MEMBER_EXIT                    = 221,
	HEADER_CZ_CHANGE_CHATROOM                = 222,
	HEADER_ZC_CHANGE_CHATROOM                = 223,
	HEADER_CZ_REQ_ROLE_CHANGE                = 224,
	HEADER_ZC_ROLE_CHANGE                    = 225,
	HEADER_CZ_REQ_EXPEL_MEMBER               = 226,
	HEADER_CZ_EXIT_ROOM                      = 227,
	HEADER_CZ_REQ_EXCHANGE_ITEM              = 228,
	HEADER_ZC_REQ_EXCHANGE_ITEM              = 229,
	HEADER_CZ_ACK_EXCHANGE_ITEM              = 230,
	HEADER_ZC_ACK_EXCHANGE_ITEM              = 231,
	HEADER_CZ_ADD_EXCHANGE_ITEM              = 232,
	HEADER_ZC_ADD_EXCHANGE_ITEM              = 233,
	HEADER_ZC_ACK_ADD_EXCHANGE_ITEM          = 234,
	HEADER_CZ_CONCLUDE_EXCHANGE_ITEM         = 235,
	HEADER_ZC_CONCLUDE_EXCHANGE_ITEM         = 236,
	HEADER_CZ_CANCEL_EXCHANGE_ITEM           = 237,
	HEADER_ZC_CANCEL_EXCHANGE_ITEM           = 238,
	HEADER_CZ_EXEC_EXCHANGE_ITEM             = 239,
	HEADER_ZC_EXEC_EXCHANGE_ITEM             = 240,
	HEADER_ZC_EXCHANGEITEM_UNDO              = 241,
	HEADER_ZC_NOTIFY_STOREITEM_COUNTINFO     = 242,
	HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_STORE   = 243,
	HEADER_ZC_ADD_ITEM_TO_STORE              = 244,
	HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_BODY   = 245,
	HEADER_ZC_DELETE_ITEM_FROM_STORE         = 246,
	HEADER_CZ_CLOSE_STORE                    = 247,
	HEADER_ZC_CLOSE_STORE                    = 248,
	HEADER_CZ_MAKE_GROUP                     = 249,
	HEADER_ZC_ACK_MAKE_GROUP                 = 250,
	HEADER_ZC_GROUP_LIST                     = 251,
	HEADER_CZ_REQ_JOIN_GROUP                 = 252,
	HEADER_ZC_ACK_REQ_JOIN_GROUP             = 253,
	HEADER_ZC_REQ_JOIN_GROUP                 = 254,
	HEADER_CZ_JOIN_GROUP                     = 255,
	HEADER_CZ_REQ_LEAVE_GROUP                = 256,
	HEADER_ZC_GROUPINFO_CHANGE               = 257,
	HEADER_CZ_CHANGE_GROUPEXPOPTION          = 258,
	HEADER_CZ_REQ_EXPEL_GROUP_MEMBER         = 259,
	HEADER_ZC_ADD_MEMBER_TO_GROUP            = 260,
	HEADER_ZC_DELETE_MEMBER_FROM_GROUP       = 261,
	HEADER_ZC_NOTIFY_HP_TO_GROUPM            = 262,
	HEADER_ZC_NOTIFY_POSITION_TO_GROUPM      = 263,
	HEADER_CZ_REQUEST_CHAT_PARTY             = 264,
	HEADER_ZC_NOTIFY_CHAT_PARTY              = 265,
	HEADER_ZC_MVP_GETTING_ITEM               = 266,
	HEADER_ZC_MVP_GETTING_SPECIAL_EXP        = 267,
	HEADER_ZC_MVP                            = 268,
	HEADER_ZC_THROW_MVPITEM                  = 269,
	HEADER_ZC_SKILLINFO_UPDATE               = 270,
	HEADER_ZC_SKILLINFO_LIST                 = 271,
	HEADER_ZC_ACK_TOUSESKILL                 = 272,
	HEADER_ZC_ADD_SKILL                      = 273,
	HEADER_CZ_UPGRADE_SKILLLEVEL             = 274,
	HEADER_CZ_USE_SKILL                      = 275,
	HEADER_ZC_NOTIFY_SKILL                   = 276,
	HEADER_ZC_NOTIFY_SKILL_POSITION          = 277,
	HEADER_CZ_USE_SKILL_TOGROUND             = 278,
	HEADER_ZC_NOTIFY_GROUNDSKILL             = 279,
	HEADER_CZ_CANCEL_LOCKON                  = 280,
	HEADER_ZC_STATE_CHANGE                   = 281,
	HEADER_ZC_USE_SKILL                      = 282,
	HEADER_CZ_SELECT_WARPPOINT               = 283,
	HEADER_ZC_WARPLIST                       = 284,
	HEADER_CZ_REMEMBER_WARPPOINT             = 285,
	HEADER_ZC_ACK_REMEMBER_WARPPOINT         = 286,
	HEADER_ZC_SKILL_ENTRY                    = 287,
	HEADER_ZC_SKILL_DISAPPEAR                = 288,
	HEADER_ZC_NOTIFY_CARTITEM_COUNTINFO      = 289,
	HEADER_ZC_CART_EQUIPMENT_ITEMLIST        = 290,
	HEADER_ZC_CART_NORMAL_ITEMLIST           = 291,
	HEADER_ZC_ADD_ITEM_TO_CART               = 292,
	HEADER_ZC_DELETE_ITEM_FROM_CART          = 293,
	HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_CART    = 294,
	HEADER_CZ_MOVE_ITEM_FROM_CART_TO_BODY    = 295,
	HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_CART   = 296,
	HEADER_CZ_MOVE_ITEM_FROM_CART_TO_STORE   = 297,
	HEADER_CZ_REQ_CARTOFF                    = 298,
	HEADER_ZC_CARTOFF                        = 299,
	HEADER_ZC_ACK_ADDITEM_TO_CART            = 300,
	HEADER_ZC_OPENSTORE                      = 301,
	HEADER_CZ_REQ_CLOSESTORE                 = 302,
	HEADER_CZ_REQ_OPENSTORE                  = 303,
	HEADER_CZ_REQ_BUY_FROMMC                 = 304,
	HEADER_ZC_STORE_ENTRY                    = 305,
	HEADER_ZC_DISAPPEAR_ENTRY                = 306,
	HEADER_ZC_PC_PURCHASE_ITEMLIST_FROMMC    = 307,
	HEADER_CZ_PC_PURCHASE_ITEMLIST_FROMMC    = 308,
	HEADER_ZC_PC_PURCHASE_RESULT_FROMMC      = 309,
	HEADER_ZC_PC_PURCHASE_MYITEMLIST         = 310,
	HEADER_ZC_DELETEITEM_FROM_MCSTORE        = 311,
	HEADER_CZ_PKMODE_CHANGE                  = 312,
	HEADER_ZC_ATTACK_FAILURE_FOR_DISTANCE    = 313,
	HEADER_ZC_ATTACK_RANGE                   = 314,
	HEADER_ZC_ACTION_FAILURE                 = 315,
	HEADER_ZC_EQUIP_ARROW                    = 316,
	HEADER_ZC_RECOVERY                       = 317,
	HEADER_ZC_USESKILL_ACK                   = 318,
	HEADER_CZ_ITEM_CREATE                    = 319,
	HEADER_CZ_MOVETO_MAP                     = 320,
	HEADER_ZC_COUPLESTATUS                   = 321,
	HEADER_ZC_OPEN_EDITDLG                   = 322,
	HEADER_CZ_INPUT_EDITDLG                  = 323,
	HEADER_ZC_COMPASS                        = 324,
	HEADER_ZC_SHOW_IMAGE                     = 325,
	HEADER_CZ_CLOSE_DIALOG                   = 326,
	HEADER_ZC_AUTORUN_SKILL                  = 327,
	HEADER_ZC_RESURRECTION                   = 328,
	HEADER_CZ_REQ_GIVE_MANNER_POINT          = 329,
	HEADER_ZC_ACK_GIVE_MANNER_POINT          = 330,
	HEADER_ZC_NOTIFY_MANNER_POINT_GIVEN      = 331,
	HEADER_ZC_MYGUILD_BASIC_INFO             = 332,
	HEADER_CZ_REQ_GUILD_MENUINTERFACE        = 333,
	HEADER_ZC_ACK_GUILD_MENUINTERFACE        = 334,
	HEADER_CZ_REQ_GUILD_MENU                 = 335,
	HEADER_ZC_GUILD_INFO                     = 336,
	HEADER_CZ_REQ_GUILD_EMBLEM_IMG           = 337,
	HEADER_ZC_GUILD_EMBLEM_IMG               = 338,
	HEADER_CZ_REGISTER_GUILD_EMBLEM_IMG      = 339,
	HEADER_ZC_MEMBERMGR_INFO                 = 340,
	HEADER_CZ_REQ_CHANGE_MEMBERPOS           = 341,
	HEADER_ZC_ACK_REQ_CHANGE_MEMBERS         = 342,
	HEADER_CZ_REQ_OPEN_MEMBER_INFO           = 343,
	HEADER_ZC_ACK_OPEN_MEMBER_INFO           = 344,
	HEADER_CZ_REQ_LEAVE_GUILD                = 345,
	HEADER_ZC_ACK_LEAVE_GUILD                = 346,
	HEADER_CZ_REQ_BAN_GUILD                  = 347,
	HEADER_ZC_ACK_BAN_GUILD                  = 348,
	HEADER_CZ_REQ_DISORGANIZE_GUILD          = 349,
	HEADER_ZC_ACK_DISORGANIZE_GUILD_RESULT   = 350,
	HEADER_ZC_ACK_DISORGANIZE_GUILD          = 351,
	HEADER_ZC_POSITION_INFO                  = 352,
	HEADER_CZ_REG_CHANGE_GUILD_POSITIONINFO  = 353,
	HEADER_ZC_GUILD_SKILLINFO                = 354,
	HEADER_ZC_BAN_LIST                       = 355,
	HEADER_ZC_OTHER_GUILD_LIST               = 356,
	HEADER_CZ_REQ_MAKE_GUILD                 = 357,
	HEADER_ZC_POSITION_ID_NAME_INFO          = 358,
	HEADER_ZC_RESULT_MAKE_GUILD              = 359,
	HEADER_CZ_REQ_JOIN_GUILD                 = 360,
	HEADER_ZC_ACK_REQ_JOIN_GUILD             = 361,
	HEADER_ZC_REQ_JOIN_GUILD                 = 362,
	HEADER_CZ_JOIN_GUILD                     = 363,
	HEADER_ZC_UPDATE_GDID                    = 364,
	HEADER_ZC_UPDATE_CHARSTAT                = 365,
	HEADER_CZ_GUILD_NOTICE                   = 366,
	HEADER_ZC_GUILD_NOTICE                   = 367,
	HEADER_CZ_REQ_ALLY_GUILD                 = 368,
	HEADER_ZC_REQ_ALLY_GUILD                 = 369,
	HEADER_CZ_ALLY_GUILD                     = 370,
	HEADER_ZC_ACK_REQ_ALLY_GUILD             = 371,
	HEADER_ZC_ACK_CHANGE_GUILD_POSITIONINFO  = 372,
	HEADER_CZ_REQ_GUILD_MEMBER_INFO          = 373,
	HEADER_ZC_ACK_GUILD_MEMBER_INFO          = 374,
	HEADER_ZC_ITEMIDENTIFY_LIST              = 375,
	HEADER_CZ_REQ_ITEMIDENTIFY               = 376,
	HEADER_ZC_ACK_ITEMIDENTIFY               = 377,
	HEADER_CZ_REQ_ITEMCOMPOSITION_LIST       = 378,
	HEADER_ZC_ITEMCOMPOSITION_LIST           = 379,
	HEADER_CZ_REQ_ITEMCOMPOSITION            = 380,
	HEADER_ZC_ACK_ITEMCOMPOSITION            = 381,
	HEADER_CZ_GUILD_CHAT                     = 382,
	HEADER_ZC_GUILD_CHAT                     = 383,
	HEADER_CZ_REQ_HOSTILE_GUILD              = 384,
	HEADER_ZC_ACK_REQ_HOSTILE_GUILD          = 385,
	HEADER_ZC_MEMBER_ADD                     = 386,
	HEADER_CZ_REQ_DELETE_RELATED_GUILD       = 387,
	HEADER_ZC_DELETE_RELATED_GUILD           = 388,
	HEADER_ZC_ADD_RELATED_GUILD              = 389,
	HEADER_COLLECTORDEAD                     = 390,
	HEADER_PING                              = 391,
	HEADER_ZC_ACK_ITEMREFINING               = 392,
	HEADER_ZC_NOTIFY_MAPINFO                 = 393,
	HEADER_CZ_REQ_DISCONNECT                 = 394,
	HEADER_ZC_ACK_REQ_DISCONNECT             = 395,
	HEADER_ZC_MONSTER_INFO                   = 396,
	HEADER_ZC_MAKABLEITEMLIST                = 397,
	HEADER_CZ_REQMAKINGITEM                  = 398,
	HEADER_ZC_ACK_REQMAKINGITEM              = 399,
	HEADER_CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 400,
	HEADER_ZC_TALKBOX_CHATCONTENTS           = 401,
	HEADER_ZC_UPDATE_MAPINFO                 = 402,
	HEADER_CZ_REQNAME_BYGID                  = 403,
	HEADER_ZC_ACK_REQNAME_BYGID              = 404,
	HEADER_ZC_ACK_REQNAMEALL                 = 405,
	HEADER_ZC_MSG_STATE_CHANGE               = 406,
	HEADER_CZ_RESET                          = 407,
	HEADER_CZ_CHANGE_MAPTYPE                 = 408,
	HEADER_ZC_NOTIFY_MAPPROPERTY             = 409,
	HEADER_ZC_NOTIFY_RANKING                 = 410,
	HEADER_ZC_NOTIFY_EFFECT                  = 411,
	HEADER_CZ_LOCALBROADCAST                 = 412,
	HEADER_CZ_CHANGE_EFFECTSTATE             = 413,
	HEADER_ZC_START_CAPTURE                  = 414,
	HEADER_CZ_TRYCAPTURE_MONSTER             = 415,
	HEADER_ZC_TRYCAPTURE_MONSTER             = 416,
	HEADER_CZ_COMMAND_PET                    = 417,
	HEADER_ZC_PROPERTY_PET                   = 418,
	HEADER_ZC_FEED_PET                       = 419,
	HEADER_ZC_CHANGESTATE_PET                = 420,
	HEADER_CZ_RENAME_PET                     = 421,
	HEADER_ZC_PETEGG_LIST                    = 422,
	HEADER_CZ_SELECT_PETEGG                  = 423,
	HEADER_CZ_PETEGG_INFO                    = 424,
	HEADER_CZ_PET_ACT                        = 425,
	HEADER_ZC_PET_ACT                        = 426,
	HEADER_ZC_PAR_CHANGE_USER                = 427,
	HEADER_ZC_SKILL_UPDATE                   = 428,
	HEADER_ZC_MAKINGARROW_LIST               = 429,
	HEADER_CZ_REQ_MAKINGARROW                = 430,
	HEADER_CZ_REQ_CHANGECART                 = 431,
	HEADER_ZC_NPCSPRITE_CHANGE               = 432,
	HEADER_ZC_SHOWDIGIT                      = 433,
	HEADER_CZ_REQ_OPENSTORE2                 = 434,
	HEADER_ZC_SHOW_IMAGE2                    = 435,
	HEADER_ZC_CHANGE_GUILD                   = 436,
	HEADER_SC_BILLING_INFO                   = 437,
	HEADER_ZC_GUILD_INFO2                    = 438,
	HEADER_CZ_GUILD_ZENY                     = 439,
	HEADER_ZC_GUILD_ZENY_ACK                 = 440,
	HEADER_ZC_DISPEL                         = 441,
	HEADER_CZ_REMOVE_AID                     = 442,
	HEADER_CZ_SHIFT                          = 443,
	HEADER_CZ_RECALL                         = 444,
	HEADER_CZ_RECALL_GID                     = 445,
	HEADER_AC_ASK_PNGAMEROOM                 = 446,
	HEADER_CA_REPLY_PNGAMEROOM               = 447,
	HEADER_CZ_REQ_REMAINTIME                 = 448,
	HEADER_ZC_REPLY_REMAINTIME               = 449,
	HEADER_ZC_INFO_REMAINTIME                = 450,
	HEADER_ZC_BROADCAST2                     = 451,
	HEADER_ZC_ADD_ITEM_TO_STORE2             = 452,
	HEADER_ZC_ADD_ITEM_TO_CART2              = 453,
	HEADER_CS_REQ_ENCRYPTION                 = 454,
	HEADER_SC_ACK_ENCRYPTION                 = 455,
	HEADER_ZC_USE_ITEM_ACK2                  = 456,
	HEADER_ZC_SKILL_ENTRY2                   = 457,
	HEADER_CZ_REQMAKINGHOMUN                 = 458,
	HEADER_CZ_MONSTER_TALK                   = 459,
	HEADER_ZC_MONSTER_TALK                   = 460,
	HEADER_ZC_AUTOSPELLLIST                  = 461,
	HEADER_CZ_SELECTAUTOSPELL                = 462,
	HEADER_ZC_DEVOTIONLIST                   = 463,
	HEADER_ZC_SPIRITS                        = 464,
	HEADER_ZC_BLADESTOP                      = 465,
	HEADER_ZC_COMBODELAY                     = 466,
	HEADER_ZC_SOUND                          = 467,
	HEADER_ZC_OPEN_EDITDLGSTR                = 468,
	HEADER_CZ_INPUT_EDITDLGSTR               = 469,
	HEADER_ZC_NOTIFY_MAPPROPERTY2            = 470,
	HEADER_ZC_SPRITE_CHANGE2                 = 471,
	HEADER_ZC_NOTIFY_STANDENTRY2             = 472,
	HEADER_ZC_NOTIFY_NEWENTRY2               = 473,
	HEADER_ZC_NOTIFY_MOVEENTRY2              = 474,
	HEADER_CA_REQ_HASH                       = 475,
	HEADER_AC_ACK_HASH                       = 476,
	HEADER_CA_LOGIN2                         = 477,
	HEADER_ZC_NOTIFY_SKILL2                  = 478,
	HEADER_CZ_REQ_ACCOUNTNAME                = 479,
	HEADER_ZC_ACK_ACCOUNTNAME                = 480,
	HEADER_ZC_SPIRITS2                       = 481,
	HEADER_ZC_REQ_COUPLE                     = 482,
	HEADER_CZ_JOIN_COUPLE                    = 483,
	HEADER_ZC_START_COUPLE                   = 484,
	HEADER_CZ_REQ_JOIN_COUPLE                = 485,
	HEADER_ZC_COUPLENAME                     = 486,
	HEADER_CZ_DORIDORI                       = 487,
	HEADER_CZ_MAKE_GROUP2                    = 488,
	HEADER_ZC_ADD_MEMBER_TO_GROUP2           = 489,
	HEADER_ZC_CONGRATULATION                 = 490,
	HEADER_ZC_NOTIFY_POSITION_TO_GUILDM      = 491,
	HEADER_ZC_GUILD_MEMBER_MAP_CHANGE        = 492,
	HEADER_CZ_CHOPOKGI                       = 493,
	HEADER_ZC_NORMAL_ITEMLIST2               = 494,
	HEADER_ZC_CART_NORMAL_ITEMLIST2          = 495,
	HEADER_ZC_STORE_NORMAL_ITEMLIST2         = 496,
	HEADER_AC_NOTIFY_ERROR                   = 497,
	HEADER_ZC_UPDATE_CHARSTAT2               = 498,
	HEADER_ZC_NOTIFY_EFFECT2                 = 499,
	HEADER_ZC_REQ_EXCHANGE_ITEM2             = 500,
	HEADER_ZC_ACK_EXCHANGE_ITEM2             = 501,
	HEADER_ZC_REQ_BABY                       = 502,
	HEADER_CZ_JOIN_BABY                      = 503,
	HEADER_ZC_START_BABY                     = 504,
	HEADER_CZ_REQ_JOIN_BABY                  = 505,
};


struct ZSERVER_ADDR
{
	/* this+0 */ unsigned long ip;
	/* this+4 */ short port;
};


struct SKILLINFO
{
	/* this+ 0 */ unsigned short SKID;
	/* this+ 2 */ int type;
	/* this+ 6 */ short level;
	/* this+ 8 */ short spcost;
	/* this+10 */ short attackRange;
	/* this+12 */ char skillName[24];
	/* this+36 */ bool upgradable;
};


struct NORMALITEM_EXTRAINFO
{
	/* this+0 */ short index;
	/* this+2 */ unsigned short ITID;
	/* this+4 */ unsigned char type;
	/* this+5 */ bool IsIdentified;
	/* this+6 */ short count;
	/* this+8 */ unsigned short WearState;
};


struct NORMALITEM_EXTRAINFO2 : public NORMALITEM_EXTRAINFO
{
	/* this+ 0 */ //NORMALITEM_EXTRAINFO baseclass_0;
	/* this+10 */ EQUIPSLOTINFO slot;
};


struct EQUIPMENTITEM_EXTRAINFO
{
	/* this+ 0 */ short index;
	/* this+ 2 */ unsigned short ITID;
	/* this+ 4 */ unsigned char type;
	/* this+ 5 */ bool IsIdentified;
	/* this+ 6 */ unsigned short location;
	/* this+ 8 */ unsigned short WearState;
	/* this+10 */ bool IsDamaged;
	/* this+11 */ unsigned char RefiningLevel;
	/* this+12 */ EQUIPSLOTINFO slot;
};


struct GUILD_MEMBER_INFO
{
	/* this+ 0 */ int AID;
	/* this+ 4 */ int GID;
	/* this+ 8 */ short head;
	/* this+10 */ short headPalette;
	/* this+12 */ short sex;
	/* this+14 */ short job;
	/* this+16 */ short level;
	/* this+18 */ int contributionExp;
	/* this+22 */ int currentState;
	/* this+26 */ int positionID;
	/* this+30 */ char intro[50];
	/* this+80 */ char charname[24];
};


struct RELATED_GUILD_INFO
{
	/* this+0 */ int relation;
	/* this+4 */ int GDID;
	/* this+8 */ char guildname[24];
};


struct MAKABLEITEM_INFO
{
	/* this+0 */ unsigned short ITID;
	/* this+2 */ unsigned short material_ID[3];
};


////////////////////////////////////////


struct PACKET_CA_LOGIN
{// 0x0064 (100)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char Passwd[24];
	/* this+54 */ unsigned char clienttype;
};


struct PACKET_CH_ENTER
{// 0x0065 (101)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ int AuthCode;
	/* this+10 */ unsigned long userLevel;
	/* this+14 */ unsigned short clientType;
	/* this+16 */ unsigned char Sex;
};


struct PACKET_CH_SELECT_CHAR
{// 0x0066 (102)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char CharNum;
};


struct PACKET_CH_MAKE_CHAR
{// 0x0067 (103)
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
{// 0x0068 (104)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char key[40];
};


struct PACKET_AC_ACCEPT_LOGIN
{// 0x0069 (105)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ int AuthCode;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ unsigned long userLevel;
	/* this+16 */ unsigned long lastLoginIP;
	/* this+20 */ char lastLoginTime[26];
	/* this+46 */ unsigned char Sex;
	/* this+47 */ SERVER_ADDR ServerAddr[];
};


struct PACKET_AC_REFUSE_LOGIN
{// 0x006A (106)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode; // enum REFUSETYPE
	/* this+3 */ char blockDate[20];
};


struct PACKET_HC_ACCEPT_ENTER
{// 0x006B (107)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ CHARACTER_INFO Chars[];
};


struct PACKET_HC_REFUSE_ENTER
{// 0x006C (108)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode;
};


struct PACKET_HC_ACCEPT_MAKECHAR
{// 0x006D (109)
	/* this+0 */ short PacketType;
	/* this+2 */ CHARACTER_INFO charinfo;
};


struct PACKET_HC_REFUSE_MAKECHAR
{// 0x006E (110)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode;
};


struct PACKET_HC_ACCEPT_DELETECHAR
{// 0x006F (111)
	/* this+0 */ short PacketType;
};


struct PACKET_HC_REFUSE_DELETECHAR
{// 0x0070 (112)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode;
};


struct PACKET_HC_NOTIFY_ZONESVR
{// 0x0071 (113)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned char mapName[16];
	/* this+22 */ ZSERVER_ADDR addr;
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


struct PACKET_ZC_ACCEPT_ENTER
{// 0x0073 (115)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long startTime;
	/* this+ 6 */ unsigned char PosDir[3];
	/* this+ 9 */ unsigned char xSize;
	/* this+10 */ unsigned char ySize;
};


struct PACKET_ZC_REFUSE_ENTER
{// 0x0074 (116)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode;
};


struct PACKET_ZC_NOTIFY_INITCHAR
{// 0x0075 (117)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GID;
	/* this+ 8 */ short Style;
	/* this+10 */ unsigned char Item;
	/* this+11 */ unsigned char Unknown[]; //TODO
};


struct PACKET_ZC_NOTIFY_UPDATECHAR
{// 0x0076 (118)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ short Style;
	/* this+8 */ unsigned char Item;
};


struct PACKET_ZC_NOTIFY_UPDATEPLAYER
{// 0x0077 (119)
	/* this+0 */ short PacketType;
	/* this+2 */ short Style;
	/* this+4 */ unsigned char Item;
};


struct PACKET_ZC_NOTIFY_STANDENTRY
{// 0x0078 (120)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ short effectState;
	/* this+14 */ short job;
	/* this+16 */ short head;
	/* this+18 */ short weapon;
	/* this+20 */ short accessory;
	/* this+22 */ short shield;
	/* this+24 */ short accessory2;
	/* this+26 */ short accessory3;
	/* this+28 */ short headpalette;
	/* this+30 */ short bodypalette;
	/* this+32 */ short headDir;
	/* this+34 */ unsigned long GUID;
	/* this+38 */ short GEmblemVer;
	/* this+40 */ short honor;
	/* this+42 */ short virtue;
	/* this+44 */ bool isPKModeON;
	/* this+45 */ unsigned char sex;
	/* this+46 */ unsigned char PosDir[3];
	/* this+49 */ unsigned char xSize;
	/* this+50 */ unsigned char ySize;
	/* this+51 */ unsigned char state;
	/* this+52 */ short clevel;
};


struct PACKET_ZC_NOTIFY_NEWENTRY
{// 0x0079 (121)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ short effectState;
	/* this+14 */ short job;
	/* this+16 */ short head;
	/* this+18 */ short weapon;
	/* this+20 */ short accessory;
	/* this+22 */ short shield;
	/* this+24 */ short accessory2;
	/* this+26 */ short accessory3;
	/* this+28 */ short headpalette;
	/* this+30 */ short bodypalette;
	/* this+32 */ short headDir;
	/* this+34 */ unsigned long GUID;
	/* this+38 */ short GEmblemVer;
	/* this+40 */ short honor;
	/* this+42 */ short virtue;
	/* this+44 */ bool isPKModeON;
	/* this+45 */ unsigned char sex;
	/* this+46 */ unsigned char PosDir[3];
	/* this+49 */ unsigned char xSize;
	/* this+50 */ unsigned char ySize;
	/* this+51 */ short clevel;
};


struct PACKET_ZC_NOTIFY_ACTENTRY
{// 0x007A (122)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ short effectState;
	/* this+14 */ short job;
	/* this+16 */ short head;
	/* this+18 */ short weapon;
	/* this+20 */ short accessory;
	/* this+22 */ short shield;
	/* this+24 */ short accessory2;
	/* this+26 */ short accessory3;
	/* this+28 */ short headpalette;
	/* this+30 */ short bodypalette;
	/* this+32 */ short headDir;
	/* this+34 */ unsigned long GUID;
	/* this+38 */ short GEmblemVer;
	/* this+40 */ short honor;
	/* this+42 */ short virtue;
	/* this+44 */ bool isPKModeON;
	/* this+45 */ unsigned char sex;
	/* this+46 */ unsigned char PosDir[3];
	/* this+49 */ unsigned char xSize;
	/* this+50 */ unsigned char ySize;
	/* this+51 */ unsigned char action;
	/* this+52 */ unsigned long actStartTime;
	/* this+56 */ short clevel;
};


struct PACKET_ZC_NOTIFY_MOVEENTRY
{// 0x007B (123)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ short effectState;
	/* this+14 */ short job;
	/* this+16 */ short head;
	/* this+18 */ short weapon;
	/* this+20 */ short accessory;
	/* this+22 */ unsigned long moveStartTime;
	/* this+26 */ short shield;
	/* this+28 */ short accessory2;
	/* this+30 */ short accessory3;
	/* this+32 */ short headpalette;
	/* this+34 */ short bodypalette;
	/* this+36 */ short headDir;
	/* this+38 */ unsigned long GUID;
	/* this+42 */ short GEmblemVer;
	/* this+44 */ short honor;
	/* this+46 */ short virtue;
	/* this+48 */ bool isPKModeON;
	/* this+49 */ unsigned char sex;
	/* this+50 */ unsigned char MoveData[6];
	/* this+56 */ unsigned char xSize;
	/* this+57 */ unsigned char ySize;
	/* this+58 */ short clevel;
};


struct PACKET_ZC_NOTIFY_STANDENTRY_NPC
{// 0x007C (124)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ short effectState;
	/* this+14 */ short head;
	/* this+16 */ short weapon;
	/* this+18 */ short accessory;
	/* this+20 */ short job;
	/* this+22 */ short shield;
	/* this+24 */ short accessory2;
	/* this+26 */ short accessory3;
	/* this+28 */ short headpalette;
	/* this+30 */ short bodypalette;
	/* this+32 */ short headDir;
	/* this+34 */ bool isPKModeON;
	/* this+35 */ unsigned char sex;
	/* this+36 */ unsigned char PosDir[3];
	/* this+39 */ unsigned char xSize;
	/* this+40 */ unsigned char ySize;
};


struct PACKET_CZ_NOTIFY_ACTORINIT
{// 0x007D (125)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQUEST_TIME
{// 0x007E (126)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long clientTime;
};


struct PACKET_ZC_NOTIFY_TIME
{// 0x007F (127)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long time;
};


struct PACKET_ZC_NOTIFY_VANISH
{// 0x0080 (128)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char type;
};


struct PACKET_SC_NOTIFY_BAN
{// 0x0081 (129)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode; // enum BAN_*
};


struct PACKET_CZ_REQUEST_QUIT
{// 0x0082 (130)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_ACCEPT_QUIT
{// 0x0083 (131)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_REFUSE_QUIT
{// 0x0084 (132)
	/* this+0 */ short PacketType;
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


struct PACKET_CZ_REQUEST_ACT
{// 0x0089 (137)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long targetGID;
	/* this+6 */ unsigned char action;
};


struct PACKET_ZC_NOTIFY_ACT
{// 0x008A (138)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long targetGID;
	/* this+10 */ unsigned long startTime;
	/* this+14 */ int attackMT;
	/* this+18 */ int attackedMT;
	/* this+22 */ short damage;
	/* this+24 */ short count;
	/* this+26 */ unsigned char action;
	/* this+27 */ short leftDamage;
};


struct PACKET_ZC_NOTIFY_ACT_POSITION
{// 0x008B (139)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long targetGID;
	/* this+10 */ unsigned long startTime;
	/* this+14 */ short xPos;
	/* this+16 */ short yPos;
	/* this+18 */ short damage;
	/* this+20 */ short count;
	/* this+22 */ unsigned char action;
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


struct PACKET_SERVER_ENTRY_ACK
{// 0x008F (143)
	/* this+0 */ short Header;
	/* this+2 */ int AID;
};


struct PACKET_CZ_CONTACTNPC
{// 0x0090 (144)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
	/* this+6 */ unsigned char type;
};


struct PACKET_ZC_NPCACK_MAPMOVE
{// 0x0091 (145)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char mapName[16];
	/* this+18 */ short xPos;
	/* this+20 */ short yPos;
};


struct PACKET_ZC_NPCACK_SERVERMOVE
{// 0x0092 (146)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char mapName[16];
	/* this+18 */ short xPos;
	/* this+20 */ short yPos;
	/* this+22 */ ZSERVER_ADDR addr;
};


struct PACKET_ZC_NPCACK_ENABLE
{// 0x0093 (147)
	/* this+0 */ short PacketType;
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
	/* this+28 */ char Text[];
};


struct PACKET_ZC_ACK_WHISPER
{// 0x0098 (152)
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE result; // enum WHISPER_SEND_*
};


struct PACKET_CZ_BROADCAST
{// 0x0099 (153), 0x019C (412)
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


struct PACKET_ZC_ITEM_DISAPPEAR
{// 0x00A1 (161)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long ITAID;
};


struct PACKET_CZ_ITEM_THROW
{// 0x00A2 (162)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short Index;
	/* this+4 */ short count;
};


struct PACKET_ZC_NORMAL_ITEMLIST
{// 0x00A3 (163)
	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ NORMALITEM_EXTRAINFO Item[];
};


struct PACKET_ZC_EQUIPMENT_ITEMLIST
{// 0x00A4 (164)
	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ EQUIPMENTITEM_EXTRAINFO Item[];
};


struct PACKET_ZC_STORE_NORMAL_ITEMLIST
{// 0x00A5 (165)
	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ NORMALITEM_EXTRAINFO Item[];
};


struct PACKET_ZC_STORE_EQUIPMENT_ITEMLIST
{// 0x00A6 (166)
	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ EQUIPMENTITEM_EXTRAINFO Item[];
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
	/* this+6 */ unsigned char result;
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


struct PACKET_CZ_REQ_ITEM_EXPLANATION_BYNAME
{// 0x00AD (173)
	/* this+0 */ short PacketType;
	/* this+2 */ short unknown; //TODO
};


struct PACKET_ZC_REQ_ITEM_EXPLANATION_ACK
{// 0x00AE (174)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ BYTE unknown[]; //TODO
};


struct PACKET_ZC_ITEM_THROW_ACK
{// 0x00AF (175)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short Index;
	/* this+4 */ short count;
};


struct PACKET_ZC_PAR_CHANGE
{// 0x00B0 (176)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short varID;
	/* this+4 */ int count;
};


struct PACKET_ZC_LONGPAR_CHANGE
{// 0x00B1 (177)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short varID;
	/* this+4 */ int amount;
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


struct PACKET_ZC_SAY_DIALOG
{// 0x00B4 (180)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long NAID;
	/* this+8 */ char Text[];
};


struct PACKET_ZC_WAIT_DIALOG
{// 0x00B5 (181)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
};


struct PACKET_ZC_CLOSE_DIALOG
{// 0x00B6 (182)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
};


struct PACKET_ZC_MENU_LIST
{// 0x00B7 (183)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long NAID;
	/* this+8 */ char MenuListStr[];
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


struct PACKET_CZ_REQ_STATUS
{// 0x00BA (186)
	/* this+0 */ short PacketType;
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


struct PACKET_ZC_STATUS
{// 0x00BD (189)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short point;
	/* this+ 4 */ unsigned char str;
	/* this+ 5 */ unsigned char standardStr;
	/* this+ 6 */ unsigned char agi;
	/* this+ 7 */ unsigned char standardAgi;
	/* this+ 8 */ unsigned char vit;
	/* this+ 9 */ unsigned char standardVit;
	/* this+10 */ unsigned char Int;
	/* this+11 */ unsigned char standardInt;
	/* this+12 */ unsigned char dex;
	/* this+13 */ unsigned char standardDex;
	/* this+14 */ unsigned char luk;
	/* this+15 */ unsigned char standardLuk;
	/* this+16 */ short attPower;
	/* this+18 */ short refiningPower;
	/* this+20 */ short max_mattPower;
	/* this+22 */ short min_mattPower;
	/* this+24 */ short itemdefPower;
	/* this+26 */ short plusdefPower;
	/* this+28 */ short mdefPower;
	/* this+30 */ short plusmdefPower;
	/* this+32 */ short hitSuccessValue;
	/* this+34 */ short avoidSuccessValue;
	/* this+36 */ short plusAvoidSuccessValue;
	/* this+38 */ short criticalSuccessValue;
	/* this+40 */ short ASPD;
	/* this+42 */ short plusASPD;
};


struct PACKET_ZC_STATUS_CHANGE
{// 0x00BE (190)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short statusID;
	/* this+4 */ unsigned char value;
};


struct PACKET_CZ_REQ_EMOTION
{// 0x00BF (191)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
};


struct PACKET_ZC_EMOTION
{// 0x00C0 (192)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char type;
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


struct PACKET_ZC_SPRITE_CHANGE
{// 0x00C3 (195)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char type;
	/* this+7 */ unsigned char value;
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
	/* this+6 */ unsigned char type; //enum DEALTYPE
};


struct PACKET_ZC_PC_PURCHASE_ITEMLIST
{// 0x00C6 (198)
	struct PURCHASE_ITEM
	{
		/* this+0 */ int price;
		/* this+4 */ int discountprice;
		/* this+8 */ unsigned char type;
		/* this+9 */ unsigned short ITID;
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ PURCHASE_ITEM Item[];
};


struct PACKET_ZC_PC_SELL_ITEMLIST
{// 0x00C7 (199)
	struct SELL_ITEM
	{
		/* this+0 */ short index;
		/* this+2 */ int price;
		/* this+6 */ int overchargeprice;
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ SELL_ITEM Item[];
};


struct PACKET_CZ_PC_PURCHASE_ITEMLIST
{// 0x00C8 (200)
	struct CZ_PURCHASE_ITEM
	{
		/* this+0 */ short index;
		/* this+2 */ short count;
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ CZ_PURCHASE_ITEM Item[];
};


struct PACKET_CZ_PC_SELL_ITEMLIST
{// 0x00C9 (201)
	struct CZ_SELL_ITEM
	{
		/* this+0 */ short index;
		/* this+2 */ short count;
	};

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
	struct ROOM_MEMBER_DATA
	{
		/* this+0 */ unsigned long role;
		/* this+4 */ char name[24];
	};

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
	/* this+17 */ char title[];
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


struct PACKET_ZC_NOTIFY_STOREITEM_COUNTINFO
{// 0x00F2 (242)
	/* this+0 */ short PacketType;
	/* this+2 */ short curCount;
	/* this+4 */ short maxCount;
};


struct PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE
{// 0x00F3 (243)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;
};


struct PACKET_ZC_ADD_ITEM_TO_STORE
{// 0x00F4 (244)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short index;
	/* this+ 4 */ int count;
	/* this+ 8 */ unsigned short ITID;
	/* this+10 */ bool IsIdentified;
	/* this+11 */ bool IsDamaged;
	/* this+12 */ unsigned char refiningLevel;
	/* this+13 */ EQUIPSLOTINFO slot;
};


struct PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY
{// 0x00F5 (245)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;
};


struct PACKET_ZC_DELETE_ITEM_FROM_STORE
{// 0x00F6 (246)
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


struct PACKET_ZC_GROUP_LIST
{// 0x00FB (251)
	struct GROUPMEMBER_INFO
	{
		/* this+ 0 */ unsigned long AID;
		/* this+ 4 */ char characterName[24];
		/* this+28 */ char mapName[16];
		/* this+44 */ unsigned char Role;
		/* this+45 */ unsigned char State;
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ char groupName[24];
	/* this+28 */ GROUPMEMBER_INFO Info[];
};


struct PACKET_CZ_REQ_JOIN_GROUP
{// 0x00FC (252)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_ACK_REQ_JOIN_GROUP
{// 0x00FD (253)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char characterName[24];
	/* this+26 */ unsigned char result;
};


struct PACKET_ZC_REQ_JOIN_GROUP
{// 0x00FE (254)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GRID;
	/* this+6 */ char groupName[24];
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


struct PACKET_ZC_GROUPINFO_CHANGE
{// 0x0101 (257)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long expDivType;
};


struct PACKET_CZ_CHANGE_GROUPEXPOPTION
{// 0x0102 (258)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long expOption;
};


struct PACKET_CZ_REQ_EXPEL_GROUP_MEMBER
{// 0x0103 (259)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char characterName[24];
};


struct PACKET_ZC_ADD_MEMBER_TO_GROUP
{// 0x0104 (260)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long Role;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned char state;
	/* this+15 */ char groupName[24];
	/* this+39 */ char characterName[24];
	/* this+63 */ char mapName[16];
};


struct PACKET_ZC_DELETE_MEMBER_FROM_GROUP
{// 0x0105 (261)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ char characterName[24];
	/* this+30 */ unsigned char result;
};


struct PACKET_ZC_NOTIFY_HP_TO_GROUPM
{// 0x0106 (262)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short hp;
	/* this+8 */ short maxhp;
};


struct PACKET_ZC_NOTIFY_POSITION_TO_GROUPM
{// 0x0107 (263)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;
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
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long AID;
	/* this+8 */ char Text[];
};


struct PACKET_ZC_MVP_GETTING_ITEM
{// 0x010A (266)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short ITID;
};


struct PACKET_ZC_MVP_GETTING_SPECIAL_EXP
{// 0x010B (267)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long exp;
};


struct PACKET_ZC_MVP
{// 0x010C (268)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_THROW_MVPITEM
{// 0x010D (269)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_SKILLINFO_UPDATE
{// 0x010E (270)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ short level;
	/* this+ 6 */ short spcost;
	/* this+ 8 */ short attackRange;
	/* this+10 */ bool upgradable;
};


struct PACKET_ZC_SKILLINFO_LIST
{// 0x010F (271)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ SKILLINFO SkillInfo[];
};


struct PACKET_ZC_ACK_TOUSESKILL
{// 0x0110 (272)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;
	/* this+4 */ unsigned long NUM;
	/* this+8 */ bool result;
	/* this+9 */ unsigned char cause;
};


struct PACKET_ZC_ADD_SKILL
{// 0x0111 (273)
	/* this+0 */ short PacketType;
	/* this+2 */ SKILLINFO data;
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


struct PACKET_ZC_NOTIFY_SKILL
{// 0x0114 (276)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long targetID;
	/* this+12 */ unsigned long startTime;
	/* this+16 */ int attackMT;
	/* this+20 */ int attackedMT;
	/* this+24 */ short damage;
	/* this+26 */ short level;
	/* this+28 */ short count;
	/* this+30 */ unsigned char action;
};


struct PACKET_ZC_NOTIFY_SKILL_POSITION
{// 0x0115 (277)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long targetID;
	/* this+12 */ unsigned long startTime;
	/* this+16 */ int attackMT;
	/* this+20 */ int attackedMT;
	/* this+24 */ short xPos;
	/* this+26 */ short yPos;
	/* this+28 */ short damage;
	/* this+30 */ short level;
	/* this+32 */ short count;
	/* this+34 */ unsigned char action;
};


struct PACKET_CZ_USE_SKILL_TOGROUND
{// 0x0116 (278)
	/* this+0 */ short PacketType;
	/* this+2 */ short selectedLevel;
	/* this+4 */ unsigned short SKID;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;
};


struct PACKET_ZC_NOTIFY_GROUNDSKILL
{// 0x0117 (279)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ short level;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned long startTime;
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


struct PACKET_ZC_USE_SKILL
{// 0x011A (282)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ short level;
	/* this+ 6 */ unsigned long targetAID;
	/* this+10 */ unsigned long srcAID;
	/* this+14 */ bool result;
};


struct PACKET_CZ_SELECT_WARPPOINT
{// 0x011B (283)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;
	/* this+4 */ char mapName[16];
};


struct PACKET_ZC_WARPLIST
{// 0x011C (284)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;
	/* this+4 */ char mapName[4][16];
};


struct PACKET_CZ_REMEMBER_WARPPOINT
{// 0x011D (285)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_ACK_REMEMBER_WARPPOINT
{// 0x011E (286)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char errorCode;
};


struct PACKET_ZC_SKILL_ENTRY
{// 0x011F (287)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long creatorAID;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned char job;
	/* this+15 */ bool isVisible;
};


struct PACKET_ZC_SKILL_DISAPPEAR
{// 0x0120 (288)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_NOTIFY_CARTITEM_COUNTINFO
{// 0x0121 (289)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short curCount;
	/* this+ 4 */ short maxCount;
	/* this+ 6 */ int curWeight;
	/* this+10 */ int maxWeight;
};


struct PACKET_ZC_CART_EQUIPMENT_ITEMLIST
{// 0x0122 (290)
	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ EQUIPMENTITEM_EXTRAINFO Item[];
};


struct PACKET_ZC_CART_NORMAL_ITEMLIST
{// 0x0123 (291)
	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ NORMALITEM_EXTRAINFO Item[];
};


struct PACKET_ZC_ADD_ITEM_TO_CART
{// 0x0124 (292)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short index;
	/* this+ 4 */ int count;
	/* this+ 8 */ unsigned short ITID;
	/* this+10 */ bool IsIdentified;
	/* this+11 */ bool IsDamaged;
	/* this+12 */ unsigned char refiningLevel;
	/* this+13 */ EQUIPSLOTINFO slot;
};


struct PACKET_ZC_DELETE_ITEM_FROM_CART
{// 0x0125 (293)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;
};


struct PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_CART
{// 0x0126 (294)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;
};


struct PACKET_CZ_MOVE_ITEM_FROM_CART_TO_BODY
{// 0x0127 (295)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;
};


struct PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_CART
{// 0x0128 (296)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;
};


struct PACKET_CZ_MOVE_ITEM_FROM_CART_TO_STORE
{// 0x0129 (297)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ int count;
};


struct PACKET_CZ_REQ_CARTOFF
{// 0x012A (298)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_CARTOFF
{// 0x012B (299)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_ACK_ADDITEM_TO_CART
{// 0x012C (300)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_ZC_OPENSTORE
{// 0x012D (301)
	/* this+0 */ short PacketType;
	/* this+2 */ short itemcount;
};


struct PACKET_CZ_REQ_CLOSESTORE
{// 0x012E (302)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQ_OPENSTORE
{// 0x012F (303)
	struct PRODUCTINFO_INSTORE
	{
		/* this+0 */ short index;
		/* this+2 */ short count;
		/* this+4 */ int price;
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ char storeName[80];
	/* this+84 */ PRODUCTINFO_INSTORE Info[];
};


struct PACKET_CZ_REQ_BUY_FROMMC
{// 0x0130 (304)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_STORE_ENTRY
{// 0x0131 (305)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long makerAID;
	/* this+6 */ char storeName[80];
};


struct PACKET_ZC_DISAPPEAR_ENTRY
{// 0x0132 (306)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long makerAID;
};


struct PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC
{// 0x0133 (307)
	struct PURCHASE_ITEM_FROMMC
	{
		/* this+ 0 */ int price;
		/* this+ 4 */ short count;
		/* this+ 6 */ short index;
		/* this+ 8 */ unsigned char type;
		/* this+ 9 */ unsigned short ITID;
		/* this+11 */ bool IsIdentified;
		/* this+12 */ bool IsDamaged;
		/* this+13 */ unsigned char refiningLevel;
		/* this+14 */ EQUIPSLOTINFO slot;
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long AID;
	/* this+8 */ PURCHASE_ITEM_FROMMC Item[];
};


struct PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC
{// 0x0134 (308)
	struct CZ_PURCHASE_ITEM_FROMMC
	{
		/* this+0 */ short count;
		/* this+2 */ short index;
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long AID;
	/* this+8 */ CZ_PURCHASE_ITEM_FROMMC Item[];
};


struct PACKET_ZC_PC_PURCHASE_RESULT_FROMMC
{// 0x0135 (309)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ short curcount;
	/* this+6 */ unsigned char result;
};


struct PACKET_ZC_PC_PURCHASE_MYITEMLIST
{// 0x0136 (310)
	struct PURCHASE_MYITEM
	{
		/* this+ 0 */ int price;
		/* this+ 4 */ short index;
		/* this+ 6 */ short count;
		/* this+ 8 */ unsigned char type;
		/* this+ 9 */ unsigned short ITID;
		/* this+11 */ bool IsIdentified;
		/* this+12 */ bool IsDamaged;
		/* this+13 */ unsigned char refiningLevel;
		/* this+14 */ EQUIPSLOTINFO slot;
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long AID;
	/* this+8 */ PURCHASE_MYITEM Item[];
};


struct PACKET_ZC_DELETEITEM_FROM_MCSTORE
{// 0x0137 (311)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ short count;
};


struct PACKET_CZ_PKMODE_CHANGE
{// 0x0138 (312)
	/* this+0 */ short PacketType;
	/* this+2 */ bool isTurnOn;
};


struct PACKET_ZC_ATTACK_FAILURE_FOR_DISTANCE
{// 0x0139 (313)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long targetAID;
	/* this+ 6 */ short targetXPos;
	/* this+ 8 */ short targetYPos;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ short currentAttRange;
};


struct PACKET_ZC_ATTACK_RANGE
{// 0x013A (314)
	/* this+0 */ short PacketType;
	/* this+2 */ short currentAttRange;
};


struct PACKET_ZC_ACTION_FAILURE
{// 0x013B (315)
	/* this+0 */ short PacketType;
	/* this+2 */ short errorCode;
};


struct PACKET_ZC_EQUIP_ARROW
{// 0x013C (316)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
};


struct PACKET_ZC_RECOVERY
{// 0x013D (317)
	/* this+0 */ short PacketType;
	/* this+2 */ short varID;
	/* this+4 */ short amount;
};


struct PACKET_ZC_USESKILL_ACK
{// 0x013E (318)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long targetID;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned short SKID;
	/* this+16 */ unsigned long property;
	/* this+20 */ unsigned long delayTime;
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


struct PACKET_ZC_COUPLESTATUS
{// 0x0141 (321)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long statusType;
	/* this+ 6 */ int defaultStatus;
	/* this+10 */ int plusStatus;
};


struct PACKET_ZC_OPEN_EDITDLG
{// 0x0142 (322)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
};


struct PACKET_CZ_INPUT_EDITDLG
{// 0x0143 (323)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
	/* this+6 */ int value;
};


struct PACKET_ZC_COMPASS
{// 0x0144 (324)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long NAID;
	/* this+ 6 */ int type;
	/* this+10 */ int xPos;
	/* this+14 */ int yPos;
	/* this+18 */ unsigned char id;
	/* this+19 */ unsigned long color;
};


struct PACKET_ZC_SHOW_IMAGE
{// 0x0145 (325)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char imageName[16];
	/* this+18 */ unsigned char type;
};


struct PACKET_CZ_CLOSE_DIALOG
{// 0x0146 (326)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
};


struct PACKET_ZC_AUTORUN_SKILL
{// 0x0147 (327)
	/* this+0 */ short PacketType;
	/* this+2 */ SKILLINFO data;
};


struct PACKET_ZC_RESURRECTION
{// 0x0148 (328)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short type;
};


struct PACKET_CZ_REQ_GIVE_MANNER_POINT
{// 0x0149 (329)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long otherAID;
	/* this+6 */ unsigned char type;
	/* this+7 */ short point;
};


struct PACKET_ZC_ACK_GIVE_MANNER_POINT
{// 0x014A (330)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long result;
};


struct PACKET_ZC_NOTIFY_MANNER_POINT_GIVEN
{// 0x014B (331)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
	/* this+3 */ char otherCharName[24];
};


struct PACKET_ZC_MYGUILD_BASIC_INFO
{// 0x014C (332)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ RELATED_GUILD_INFO Info[];
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


struct PACKET_CZ_REGISTER_GUILD_EMBLEM_IMG
{// 0x0153 (339)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ char Emblem[];
};


struct PACKET_ZC_MEMBERMGR_INFO
{// 0x0154 (340)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ GUILD_MEMBER_INFO Info[];
};


struct PACKET_CZ_REQ_CHANGE_MEMBERPOS
{// 0x0155 (341)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ MEMBER_POSITION_INFORMATION Info[];
};


struct PACKET_ZC_ACK_REQ_CHANGE_MEMBERS
{// 0x0156 (342)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ MEMBER_POSITION_INFORMATION Info[];
};


struct PACKET_CZ_REQ_OPEN_MEMBER_INFO
{// 0x0157 (343)
	/* this+0 */ short PacketType;
	/* this+2 */ int AID;
};


struct PACKET_ZC_ACK_OPEN_MEMBER_INFO
{// 0x0158 (344)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQ_LEAVE_GUILD
{// 0x0159 (345)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ int AID;
	/* this+10 */ int GID;
	/* this+14 */ char reasonDesc[40];
};


struct PACKET_ZC_ACK_LEAVE_GUILD
{// 0x015A (346)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char charName[24];
	/* this+26 */ char reasonDesc[40];
};


struct PACKET_CZ_REQ_BAN_GUILD
{// 0x015B (347)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ int AID;
	/* this+10 */ int GID;
	/* this+14 */ char reasonDesc[40];
};


struct PACKET_ZC_ACK_BAN_GUILD
{// 0x015C (348)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char charName[24];
	/* this+26 */ char reasonDesc[40];
	/* this+66 */ char account[24];
};


struct PACKET_CZ_REQ_DISORGANIZE_GUILD
{// 0x015D (349)
	/* this+0 */ short PacketType;
	/* this+2 */ char key[40];
};


struct PACKET_ZC_ACK_DISORGANIZE_GUILD_RESULT
{// 0x015E (350)
	/* this+0 */ short PacketType;
	/* this+2 */ int reason;
};


struct PACKET_ZC_ACK_DISORGANIZE_GUILD
{// 0x015F (351)
	/* this+0 */ short PacketType;
	/* this+2 */ char reasonDesc[40];
};


struct PACKET_ZC_POSITION_INFO
{// 0x0160 (352)
	struct GUILD_POSITION_INFO
	{
		/* this+ 0 */ int positionID;
		/* this+ 4 */ int right;
		/* this+ 8 */ int ranking;
		/* this+12 */ int payRate;
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ GUILD_POSITION_INFO Info[];
};


struct PACKET_CZ_REG_CHANGE_GUILD_POSITIONINFO
{// 0x0161 (353)
	struct GUILD_REG_POSITION_INFO
	{
		/* this+ 0 */ int positionID;
		/* this+ 4 */ int right;
		/* this+ 8 */ int ranking;
		/* this+12 */ int payRate;
		/* this+16 */ char posName[24];
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ GUILD_REG_POSITION_INFO Info[];
};


struct PACKET_ZC_GUILD_SKILLINFO
{// 0x0162 (354)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ short skillPoint;
	/* this+6 */ SKILLINFO Info[];
};


struct PACKET_ZC_BAN_LIST
{// 0x0163 (355)
	struct GUILD_BAN_INFO
	{
		/* this+ 0 */ char charname[24];
		/* this+24 */ char account[24];
		/* this+48 */ char reason[40];
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ GUILD_BAN_INFO Info[];
};


struct PACKET_ZC_OTHER_GUILD_LIST
{// 0x0164 (356)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ BYTE unknown[]; //TODO
};


struct PACKET_CZ_REQ_MAKE_GUILD
{// 0x0165 (357)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char GName[24];
};


struct PACKET_ZC_POSITION_ID_NAME_INFO
{// 0x0166 (358)
	struct MEMBER_POSITION_ID_NAME_INFO
	{
		/* this+0 */ int positionID;
		/* this+4 */ char posName[24];
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ MEMBER_POSITION_ID_NAME_INFO Info[];
};


struct PACKET_ZC_RESULT_MAKE_GUILD
{// 0x0167 (359)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_CZ_REQ_JOIN_GUILD
{// 0x0168 (360)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long MyAID;
	/* this+10 */ unsigned long MyGID;
};


struct PACKET_ZC_ACK_REQ_JOIN_GUILD
{// 0x0169 (361)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char answer;
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


struct PACKET_ZC_UPDATE_GDID
{// 0x016C (364)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ int emblemVersion;
	/* this+10 */ int right;
	/* this+14 */ bool isMaster;
	/* this+15 */ int InterSID;
	/* this+19 */ char GName[24];
};


struct PACKET_ZC_UPDATE_CHARSTAT
{// 0x016D (365)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int status;
};


struct PACKET_CZ_GUILD_NOTICE
{// 0x016E (366)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ char subject[60];
	/* this+66 */ char notice[120];
};


struct PACKET_ZC_GUILD_NOTICE
{// 0x016F (367)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char subject[60];
	/* this+62 */ char notice[120];
};


struct PACKET_CZ_REQ_ALLY_GUILD
{// 0x170 (368)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long MyAID;
	/* this+10 */ unsigned long MyGID;
};


struct PACKET_ZC_REQ_ALLY_GUILD
{// 0x0171 (369)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long otherAID;
	/* this+6 */ char guildName[24];
};


struct PACKET_CZ_ALLY_GUILD
{// 0x0172 (370)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long otherAID;
	/* this+6 */ int answer;
};


struct PACKET_ZC_ACK_REQ_ALLY_GUILD
{// 0x0173 (371)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char answer;
};


struct PACKET_ZC_ACK_CHANGE_GUILD_POSITIONINFO
{// 0x0174 (372)
	struct GUILD_REG_POSITION_INFO
	{
		/* this+ 0 */ int positionID;
		/* this+ 4 */ int right;
		/* this+ 8 */ int ranking;
		/* this+12 */ int payRate;
		/* this+16 */ char posName[24];
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ GUILD_REG_POSITION_INFO Info[];
};


struct PACKET_CZ_REQ_GUILD_MEMBER_INFO
{// 0x0175 (373)
	/* this+0 */ short PacketType;
	/* this+2 */ int GID;
};


struct PACKET_ZC_ACK_GUILD_MEMBER_INFO
{// 0x0176 (374)
	/* this+0 */ short PacketType;
	/* this+2 */ GUILD_MEMBER_INFO Info;
};


struct PACKET_ZC_ITEMIDENTIFY_LIST
{// 0x0177 (375)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ short Index[];
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


struct PACKET_CZ_REQ_ITEMCOMPOSITION_LIST
{// 0x017A (378)
	/* this+0 */ short PacketType;
	/* this+2 */ short cardIndex;
};


struct PACKET_ZC_ITEMCOMPOSITION_LIST
{// 0x017B (379)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ short Index[];
};


struct PACKET_CZ_REQ_ITEMCOMPOSITION
{// 0x017C (380)
	/* this+0 */ short PacketType;
	/* this+2 */ short cardIndex;
	/* this+4 */ short equipIndex;
};


struct PACKET_ZC_ACK_ITEMCOMPOSITION
{// 0x0174 (381)
	/* this+0 */ short PacketType;
	/* this+2 */ short equipIndex;
	/* this+4 */ short cardIndex;
	/* this+6 */ unsigned char result;
};


struct PACKET_CZ_GUILD_CHAT
{// 0x017E (382)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_ZC_GUILD_CHAT
{// 0x017F (383)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_CZ_REQ_HOSTILE_GUILD
{// 0x0180 (384)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_ACK_REQ_HOSTILE_GUILD
{// 0x0181 (385)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_ZC_MEMBER_ADD
{// 0x0182 (386)
	/* this+0 */ short PacketType;
	/* this+2 */ GUILD_MEMBER_INFO Info;
};


struct PACKET_CZ_REQ_DELETE_RELATED_GUILD
{// 0x0183 (387)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long OpponentGDID;
	/* this+6 */ int Relation;
};


struct PACKET_ZC_DELETE_RELATED_GUILD
{// 0x0184 (388)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long OpponentGDID;
	/* this+6 */ int Relation;
};


struct PACKET_ZC_ADD_RELATED_GUILD
{// 0x0185 (389)
	/* this+0 */ short PacketType;
	/* this+2 */ RELATED_GUILD_INFO Info;
};


struct PACKET_COLLECTORDEAD
{// 0x0186 (390)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long ServerID;
};


struct PACKET_PING
{// 0x0187 (391)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_ACK_ITEMREFINING
{// 0x0188 (392)
	/* this+0 */ short PacketType;
	/* this+2 */ short result;
	/* this+4 */ short itemIndex;
	/* this+6 */ short refiningLevel;
};


struct PACKET_ZC_NOTIFY_MAPINFO
{// 0x0189 (393)
	/* this+0 */ short PacketType;
	/* this+2 */ short type;
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


struct PACKET_ZC_MONSTER_INFO
{// 0x018C (396)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short job;
	/* this+ 4 */ short level;
	/* this+ 6 */ short size;
	/* this+ 8 */ int hp;
	/* this+12 */ short def;
	/* this+14 */ short raceType;
	/* this+16 */ short mdefPower;
	/* this+18 */ short property;
	/* this+22 */ struct {
		/* this+0 */ unsigned char water;
		/* this+1 */ unsigned char earth;
		/* this+2 */ unsigned char fire;
		/* this+3 */ unsigned char wind;
		/* this+4 */ unsigned char poison;
		/* this+5 */ unsigned char saint;
		/* this+6 */ unsigned char dark;
		/* this+7 */ unsigned char mental;
		/* this+8 */ unsigned char undead;
	              } propertyTable;
};


struct PACKET_ZC_MAKABLEITEMLIST
{// 0x018D (397)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ MAKABLEITEM_INFO Info[];
};


struct PACKET_CZ_REQMAKINGITEM
{// 0x018E (398)
	/* this+0 */ short PacketType;
	/* this+2 */ MAKABLEITEM_INFO info;
};


struct PACKET_ZC_ACK_REQMAKINGITEM
{// 0x018F (399)
	/* this+0 */ short PacketType;
	/* this+2 */ short result;
	/* this+4 */ unsigned short ITID;
};


struct PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX : public PACKET_CZ_USE_SKILL_TOGROUND
{// 0x0190 (400)
	/* this+ 0 */ //PACKET_CZ_USE_SKILL_TOGROUND baseclass_0;
	/* this+10 */ char contents[80];
};


struct PACKET_ZC_TALKBOX_CHATCONTENTS
{// 0x0191 (401)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char contents[80];
};


struct PACKET_ZC_UPDATE_MAPINFO
{// 0x0192 (402)
	/* this+0 */ short PacketType;
	/* this+2 */ short xPos;
	/* this+4 */ short yPos;
	/* this+6 */ short type;
	/* this+8 */ char mapName[16];
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


struct PACKET_ZC_ACK_REQNAMEALL
{// 0x0195 (405)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ char CName[24];
	/* this+30 */ char PName[24];
	/* this+54 */ char GName[24];
	/* this+78 */ char RName[24];
};


struct PACKET_ZC_MSG_STATE_CHANGE
{// 0x0196 (406)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ unsigned long AID;
	/* this+8 */ bool state;
};


struct PACKET_CZ_RESET
{// 0x0197 (407)
	/* this+0 */ short PacketType;
	/* this+2 */ short type;
};


struct PACKET_CZ_CHANGE_MAPTYPE
{// 0x0198 (408)
	/* this+0 */ short PacketType;
	/* this+2 */ short xPos;
	/* this+4 */ short yPos;
	/* this+6 */ short type;
};


struct PACKET_ZC_NOTIFY_MAPPROPERTY
{// 0x0199 (409)
	/* this+0 */ short PacketType;
	/* this+2 */ short type; // 1:PK, 2:PVP 3:WOE
};


struct PACKET_ZC_NOTIFY_RANKING
{// 0x019A (410)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ int ranking;
	/* this+10 */ int total;
};


struct PACKET_ZC_NOTIFY_EFFECT
{// 0x019B (411)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ int effectID;
};


// @see PACKET_CZ_BROADCAST
// 0x019C (412)


struct PACKET_CZ_CHANGE_EFFECTSTATE
{// 0x019D (413)
	/* this+0 */ short PacketType;
	/* this+2 */ int EffectState;
};


struct PACKET_ZC_START_CAPTURE
{// 0x019E (414)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_TRYCAPTURE_MONSTER
{// 0x019F (415)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long targetAID;
};


struct PACKET_ZC_TRYCAPTURE_MONSTER
{// 0x01A0 (416)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_CZ_COMMAND_PET
{// 0x01A1 (417)
	/* this+0 */ short PacketType;
	/* this+2 */ char cSub;
};


struct PACKET_ZC_PROPERTY_PET
{// 0x01A2 (418)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char szName[24];
	/* this+26 */ unsigned char bModified;
	/* this+27 */ short nLevel;
	/* this+29 */ short nFullness;
	/* this+31 */ short nRelationship;
	/* this+33 */ unsigned short ITID;
};


struct PACKET_ZC_FEED_PET
{// 0x01A3 (419)
	/* this+0 */ short PacketType;
	/* this+2 */ char cRet;
	/* this+3 */ unsigned short ITID;
};


struct PACKET_ZC_CHANGESTATE_PET
{// 0x01A4 (420)
	/* this+0 */ short PacketType;
	/* this+2 */ char type;
	/* this+3 */ int GID;
	/* this+7 */ int data;
};


struct PACKET_CZ_RENAME_PET
{// 0x01A5 (421)
	/* this+0 */ short PacketType;
	/* this+2 */ char szName[24];
};


struct PACKET_ZC_PETEGG_LIST
{// 0x01A6 (422)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ short List[];
};


struct PACKET_CZ_SELECT_PETEGG
{// 0x01A7 (423)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
};


struct PACKET_CZ_PETEGG_INFO
{// 0x01A8 (424)
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
};


struct PACKET_CZ_PET_ACT
{// 0x01A9 (425)
	/* this+0 */ short PacketType;
	/* this+2 */ int data;
};


struct PACKET_ZC_PET_ACT
{// 0x01AA (426)
	/* this+0 */ short PacketType;
	/* this+2 */ int GID;
	/* this+6 */ int data;
};


struct PACKET_ZC_PAR_CHANGE_USER
{// 0x01AB (427)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned short varID;
	/* this+8 */ int count;
};


struct PACKET_ZC_SKILL_UPDATE
{// 0x01AC (428)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_MAKINGARROW_LIST
{// 0x01AD (429)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned short ITID[];
};


struct PACKET_CZ_REQ_MAKINGARROW
{// 0x01AE (430)
	/* this+0 */ short packetType;
	/* this+2 */ unsigned short id;
};


struct PACKET_CZ_REQ_CHANGECART
{// 0x01AF (431)
	/* this+0 */ short packetType;
	/* this+2 */ short num;
};


struct PACKET_ZC_NPCSPRITE_CHANGE
{// 0x01B0 (432)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char type;
	/* this+7 */ unsigned long value;
};


struct PACKET_ZC_SHOWDIGIT
{// 0x01B1 (433)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
	/* this+3 */ int value;
};


struct PACKET_CZ_REQ_OPENSTORE2
{// 0x01B2 (434)
	struct PRODUCTINFO_INSTORE
	{
		/* this+0 */ short index;
		/* this+2 */ short count;
		/* this+4 */ int price;
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ char storeName[80];
	/* this+84 */ bool result;
	/* this+85 */ PRODUCTINFO_INSTORE Info[];
};


struct PACKET_ZC_SHOW_IMAGE2
{// 0x01B3 (435)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char imageName[64];
	/* this+66 */ unsigned char type;
};


struct PACKET_ZC_CHANGE_GUILD
{// 0x01B4 (436)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GDID;
	/* this+10 */ short emblemVersion;
};


struct PACKET_SC_BILLING_INFO
{// 0x01B5 (437)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ DWORD dwAmountRemain;
	/* this+ 6 */ DWORD dwQuantityRemain;
	/* this+10 */ DWORD dwReserved1;
	/* this+14 */ DWORD dwReserved2;
};


struct PACKET_ZC_GUILD_INFO2
{// 0x01B6 (438)
	/* this+  0 */ short PacketType;
	/* this+  2 */ int GDID;
	/* this+  6 */ int level;
	/* this+ 10 */ int userNum;
	/* this+ 14 */ int maxUserNum;
	/* this+ 18 */ int userAverageLevel;
	/* this+ 22 */ int exp;
	/* this+ 26 */ int maxExp;
	/* this+ 30 */ int point;
	/* this+ 34 */ int honor;
	/* this+ 38 */ int virtue;
	/* this+ 42 */ int emblemVersion;
	/* this+ 46 */ char guildname[24];
	/* this+ 70 */ char masterName[24];
	/* this+ 94 */ char manageLand[16];
	/* this+110 */ int zeny;
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


struct PACKET_ZC_DISPEL
{// 0x01B9 (441)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
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
	/* this+2 */ char CharacterName[24];
};


struct PACKET_AC_ASK_PNGAMEROOM
{// 0x01BE (446)
	/* this+0 */ short PacketType;
};


struct PACKET_CA_REPLY_PNGAMEROOM
{// 0x01BF (447)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char Permission;
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


struct PACKET_ZC_BROADCAST2
{// 0x01C3 (451)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long fontColor;
	/* this+ 8 */ short fontType;
	/* this+10 */ short fontSize;
	/* this+12 */ short fontAlign;
	/* this+14 */ short fontY;
	/* this+16 */ char Text[];
};


struct PACKET_ZC_ADD_ITEM_TO_STORE2
{// 0x01C4 (452)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short index;
	/* this+ 4 */ int count;
	/* this+ 8 */ unsigned short ITID;
	/* this+10 */ unsigned char type;
	/* this+11 */ bool IsIdentified;
	/* this+12 */ bool IsDamaged;
	/* this+13 */ unsigned char refiningLevel;
	/* this+14 */ EQUIPSLOTINFO slot;
};


struct PACKET_ZC_ADD_ITEM_TO_CART2
{// 0x01C5 (453)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short index;
	/* this+ 4 */ int count;
	/* this+ 8 */ unsigned short ITID;
	/* this+10 */ unsigned char type;
	/* this+11 */ bool IsIdentified;
	/* this+12 */ bool IsDamaged;
	/* this+13 */ unsigned char refiningLevel;
	/* this+14 */ EQUIPSLOTINFO slot;
};


struct PACKET_CS_REQ_ENCRYPTION
{// 0x01C6 (454)
	/* this+0 */ short PacketType;
	/* this+2 */ char encCount;
	/* this+3 */ char decCount;
};


struct PACKET_SC_ACK_ENCRYPTION
{// 0x01C7 (455)
	/* this+0 */ short PacketType;
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


struct PACKET_ZC_SKILL_ENTRY2
{// 0x01C9 (457)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long creatorAID;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned char job;
	/* this+15 */ bool isVisible;
	/* this+16 */ bool isContens;
	/* this+17 */ char msg[80];
};


struct PACKET_CZ_REQMAKINGHOMUN
{// 0x01CA (458)
	/* this+0 */ short PacketType;
	/* this+2 */ bool result;
};


struct PACKET_CZ_MONSTER_TALK
{// 0x01CB (459)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char stateId;
	/* this+7 */ unsigned char skillId;
	/* this+8 */ unsigned char arg1;
};


struct PACKET_ZC_MONSTER_TALK
{// 0x01CC (460)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char stateId;
	/* this+7 */ unsigned char skillId;
	/* this+8 */ unsigned char arg1;
};


struct PACKET_ZC_AUTOSPELLLIST
{// 0x01CD (461)
	/* this+0 */ short PacketType;
	/* this+2 */ int SKID[7];
};


struct PACKET_CZ_SELECTAUTOSPELL
{// 0x01CE (462)
	/* this+0 */ short PacketType;
	/* this+2 */ int SKID;
};


struct PACKET_ZC_DEVOTIONLIST
{// 0x01CF (463)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long myAID;
	/* this+ 6 */ unsigned long AID[5];
	/* this+26 */ short range;
};


struct PACKET_ZC_SPIRITS
{// 0x01D0 (464)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short num;
};


struct PACKET_ZC_BLADESTOP
{// 0x01D1 (465)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long srcAID;
	/* this+ 6 */ unsigned long destAID;
	/* this+10 */ int flag;
};


struct PACKET_ZC_COMBODELAY
{// 0x01D2 (466)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned long delayTime;
};


struct PACKET_ZC_SOUND
{// 0x01D3 (467)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char fileName[24];
	/* this+26 */ unsigned char act;
	/* this+27 */ unsigned long term;
	/* this+31 */ unsigned long NAID;
};


struct PACKET_ZC_OPEN_EDITDLGSTR
{// 0x01D4 (468)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long NAID;
};


struct PACKET_CZ_INPUT_EDITDLGSTR
{// 0x01D5 (469)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long NAID;
	/* this+8 */ char Text[];
};


struct PACKET_ZC_NOTIFY_MAPPROPERTY2
{// 0x01D6 (470)
	/* this+0 */ short PacketType;
	/* this+2 */ short type; // enum MAPTYPE
};


struct PACKET_ZC_SPRITE_CHANGE2
{// 0x01D7 (471)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char type;
	/* this+7 */ int value;
};


struct PACKET_ZC_NOTIFY_STANDENTRY2
{// 0x01D8 (472)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ short effectState;
	/* this+14 */ short job;
	/* this+16 */ short head;
	/* this+18 */ int weapon;
	/* this+22 */ short accessory;
	/* this+24 */ short accessory2;
	/* this+26 */ short accessory3;
	/* this+28 */ short headpalette;
	/* this+30 */ short bodypalette;
	/* this+32 */ short headDir;
	/* this+34 */ unsigned long GUID;
	/* this+38 */ short GEmblemVer;
	/* this+40 */ short honor;
	/* this+42 */ short virtue;
	/* this+44 */ bool isPKModeON;
	/* this+45 */ unsigned char sex;
	/* this+46 */ unsigned char PosDir[3];
	/* this+49 */ unsigned char xSize;
	/* this+50 */ unsigned char ySize;
	/* this+51 */ unsigned char state;
	/* this+52 */ short clevel;
};


struct PACKET_ZC_NOTIFY_NEWENTRY2
{// 0x01D9 (473)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ short effectState;
	/* this+14 */ short job;
	/* this+16 */ short head;
	/* this+18 */ int weapon;
	/* this+22 */ short accessory;
	/* this+24 */ short accessory2;
	/* this+26 */ short accessory3;
	/* this+28 */ short headpalette;
	/* this+30 */ short bodypalette;
	/* this+32 */ short headDir;
	/* this+34 */ unsigned long GUID;
	/* this+38 */ short GEmblemVer;
	/* this+40 */ short honor;
	/* this+42 */ short virtue;
	/* this+44 */ bool isPKModeON;
	/* this+45 */ unsigned char sex;
	/* this+46 */ unsigned char PosDir[3];
	/* this+49 */ unsigned char xSize;
	/* this+50 */ unsigned char ySize;
	/* this+51 */ short clevel;
};


struct PACKET_ZC_NOTIFY_MOVEENTRY2
{// 0x01DA (474)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ short speed;
	/* this+ 8 */ short bodyState;
	/* this+10 */ short healthState;
	/* this+12 */ short effectState;
	/* this+14 */ short job;
	/* this+16 */ short head;
	/* this+18 */ int weapon;
	/* this+22 */ short accessory;
	/* this+24 */ unsigned long moveStartTime;
	/* this+28 */ short accessory2;
	/* this+30 */ short accessory3;
	/* this+32 */ short headpalette;
	/* this+34 */ short bodypalette;
	/* this+36 */ short headDir;
	/* this+38 */ unsigned long GUID;
	/* this+42 */ short GEmblemVer;
	/* this+44 */ short honor;
	/* this+46 */ short virtue;
	/* this+48 */ bool isPKModeON;
	/* this+49 */ unsigned char sex;
	/* this+50 */ unsigned char MoveData[6];
	/* this+56 */ unsigned char xSize;
	/* this+57 */ unsigned char ySize;
	/* this+58 */ short clevel;
};


struct PACKET_CA_REQ_HASH
{// 0x01DB (475)
	/* this+0 */ short PacketType;
};


struct PACKET_AC_ACK_HASH
{// 0x01DC (476)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ char Hash[];
};


struct PACKET_CA_LOGIN2
{// 0x01DD (477)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char PasswdMD5[16];
	/* this+46 */ unsigned char clienttype;
};


struct PACKET_ZC_NOTIFY_SKILL2
{// 0x01DE (478)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long targetID;
	/* this+12 */ unsigned long startTime;
	/* this+16 */ int attackMT;
	/* this+20 */ int attackedMT;
	/* this+24 */ int damage;
	/* this+28 */ short level;
	/* this+30 */ short count;
	/* this+32 */ unsigned char action;
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


struct PACKET_ZC_SPIRITS2
{// 0x01E1 (481)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short num;
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
	/* this+2 */ char CoupleName[24];
};


struct PACKET_CZ_DORIDORI
{// 0x01E7 (487)
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_MAKE_GROUP2
{// 0x01E8 (488)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char groupName[24];
	/* this+26 */ unsigned char ItemPickupRule;
	/* this+27 */ unsigned char ItemDivisionRule;
};


struct PACKET_ZC_ADD_MEMBER_TO_GROUP2
{// 0x01E9 (489)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long Role;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned char state;
	/* this+15 */ char groupName[24];
	/* this+39 */ char characterName[24];
	/* this+63 */ char mapName[16];
	/* this+79 */ unsigned char ItemPickupRule;
	/* this+80 */ unsigned char ItemDivisionRule;
};


struct PACKET_ZC_CONGRATULATION
{// 0x01EA (490)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_NOTIFY_POSITION_TO_GUILDM
{// 0x01EB (491)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;
};


struct PACKET_ZC_GUILD_MEMBER_MAP_CHANGE
{// 0x01EC (492)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ char mapName[16];
};


struct PACKET_CZ_CHOPOKGI
{// 0x01ED (493)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_NORMAL_ITEMLIST2
{// 0x01EE (494)
	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ NORMALITEM_EXTRAINFO2 Item[];
};


struct PACKET_ZC_CART_NORMAL_ITEMLIST2
{// 0x01EF (495)
	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ NORMALITEM_EXTRAINFO2 Item[];
};


struct PACKET_ZC_STORE_NORMAL_ITEMLIST2
{// 0x01F0 (496)
	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ NORMALITEM_EXTRAINFO2 Item[];
};


struct PACKET_AC_NOTIFY_ERROR
{// 0x01F1 (497)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_ZC_UPDATE_CHARSTAT2
{// 0x01F2 (498)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int status;
	/* this+14 */ short sex;
	/* this+16 */ short head;
	/* this+18 */ short headPalette;
};


struct PACKET_ZC_NOTIFY_EFFECT2
{// 0x01F3 (499)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ int effectID;
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


#pragma pack(pop)
