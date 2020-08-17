#pragma once
#include "Struct.h"
#pragma pack(push,1)


void EncodePosDir(int srcx, int srcy, int srcdir, BYTE* result);
void DecodePosDir(const unsigned char* packet, int& x, int& y, int& dir);
void EncodeSrcDst(int srcx, int srcy, int dstx, int dsty, int xcellpos, int ycellpos, BYTE* result);
void DecodeSrcDst(const unsigned char* packet, int& rsx, int& rsy, int& rdx, int& rdy, int& xcellpos, int& ycellpos);
bool IsFixedPacket(int packetType);
int GetPacketSize(int packetType);
void InitPacketLenWithClient();


enum ePacketType
{
//	HEADER_CA_LOGIN                               = 100, //TODO
//	HEADER_CH_ENTER                               = 101, //TODO
//	HEADER_CH_SELECT_CHAR                         = 102, //TODO
//	HEADER_CH_MAKE_CHAR                           = 103, //TODO
//	HEADER_CH_DELETE_CHAR                         = 104, //TODO
	HEADER_AC_ACCEPT_LOGIN                        = 105,
	HEADER_AC_REFUSE_LOGIN                        = 106,
	HEADER_HC_ACCEPT_ENTER                        = 107,
	HEADER_HC_REFUSE_ENTER                        = 108,
	HEADER_HC_ACCEPT_MAKECHAR                     = 109,
	HEADER_HC_REFUSE_MAKECHAR                     = 110,
	HEADER_HC_ACCEPT_DELETECHAR                   = 111,
	HEADER_HC_REFUSE_DELETECHAR                   = 112,
	HEADER_HC_NOTIFY_ZONESVR                      = 113,
//	HEADER_CZ_ENTER                               = 114, //TODO
	HEADER_ZC_ACCEPT_ENTER                        = 115,
	HEADER_ZC_REFUSE_ENTER                        = 116,
	HEADER_ZC_NOTIFY_INITCHAR                     = 117,
	HEADER_ZC_NOTIFY_UPDATECHAR                   = 118,
	HEADER_ZC_NOTIFY_UPDATEPLAYER                 = 119,
	HEADER_ZC_NOTIFY_STANDENTRY                   = 120,
	HEADER_ZC_NOTIFY_NEWENTRY                     = 121,
	HEADER_ZC_NOTIFY_ACTENTRY                     = 122,
	HEADER_ZC_NOTIFY_MOVEENTRY                    = 123,
	HEADER_ZC_NOTIFY_STANDENTRY_NPC               = 124,
//	HEADER_XX                                     = 125,
//	HEADER_XX                                     = 126,
	HEADER_ZC_NOTIFY_TIME                         = 127,
	HEADER_ZC_NOTIFY_VANISH                       = 128,
	HEADER_SC_NOTIFY_BAN                          = 129,
//	HEADER_XX                                     = 130,
	HEADER_ZC_ACCEPT_QUIT                         = 131,
	HEADER_ZC_REFUSE_QUIT                         = 132,
//	HEADER_XX                                     = 133,
	HEADER_ZC_NOTIFY_MOVE                         = 134,
	HEADER_ZC_NOTIFY_PLAYERMOVE                   = 135,
	HEADER_ZC_STOPMOVE                            = 136,
//	HEADER_XX                                     = 137,
	HEADER_ZC_NOTIFY_ACT                          = 138,
	HEADER_ZC_NOTIFY_ACT_POSITION                 = 139,
//	HEADER_XX                                     = 140,
	HEADER_ZC_NOTIFY_CHAT                         = 141,
	HEADER_ZC_NOTIFY_PLAYERCHAT                   = 142,
	HEADER_SERVER_ENTRY_ACK                       = 143,
//	HEADER_XX                                     = 144,
	HEADER_ZC_NPCACK_MAPMOVE                      = 145,
	HEADER_ZC_NPCACK_SERVERMOVE                   = 146,
	HEADER_ZC_NPCACK_ENABLE                       = 147,
//	HEADER_XX                                     = 148,
	HEADER_ZC_ACK_REQNAME                         = 149,
//	HEADER_XX                                     = 150,
	HEADER_ZC_WHISPER                             = 151,
	HEADER_ZC_ACK_WHISPER                         = 152,
//	HEADER_XX                                     = 153,
	HEADER_ZC_BROADCAST                           = 154,
//	HEADER_XX                                     = 155,
	HEADER_ZC_CHANGE_DIRECTION                    = 156,
	HEADER_ZC_ITEM_ENTRY                          = 157,
	HEADER_ZC_ITEM_FALL_ENTRY                     = 158,
//	HEADER_XX                                     = 159,
	HEADER_ZC_ITEM_PICKUP_ACK                     = 160,
	HEADER_ZC_ITEM_DISAPPEAR                      = 161,
//	HEADER_XX                                     = 162,
	HEADER_ZC_NORMAL_ITEMLIST                     = 163,
	HEADER_ZC_EQUIPMENT_ITEMLIST                  = 164,
	HEADER_ZC_STORE_NORMAL_ITEMLIST               = 165,
	HEADER_ZC_STORE_EQUIPMENT_ITEMLIST            = 166,
//	HEADER_XX                                     = 167,
	HEADER_ZC_USE_ITEM_ACK                        = 168,
//	HEADER_XX                                     = 169,
	HEADER_ZC_REQ_WEAR_EQUIP_ACK                  = 170,
//	HEADER_XX                                     = 171,
	HEADER_ZC_REQ_TAKEOFF_EQUIP_ACK               = 172,
	HEADER_CZ_REQ_ITEM_EXPLANATION_BYNAME         = 173,
//	HEADER_XX                                     = 174,
	HEADER_ZC_ITEM_THROW_ACK                      = 175,
	HEADER_ZC_PAR_CHANGE                          = 176,
	HEADER_ZC_LONGPAR_CHANGE                      = 177,
//	HEADER_XX                                     = 178,
	HEADER_ZC_RESTART_ACK                         = 179,
	HEADER_ZC_SAY_DIALOG                          = 180,
	HEADER_ZC_WAIT_DIALOG                         = 181,
	HEADER_ZC_CLOSE_DIALOG                        = 182,
	HEADER_ZC_MENU_LIST                           = 183,
//	HEADER_XX                                     = 184,
//	HEADER_XX                                     = 185,
//	HEADER_XX                                     = 186,
//	HEADER_XX                                     = 187,
	HEADER_ZC_STATUS_CHANGE_ACK                   = 188,
	HEADER_ZC_STATUS                              = 189,
	HEADER_ZC_STATUS_CHANGE                       = 190,
//	HEADER_XX                                     = 191,
	HEADER_ZC_EMOTION                             = 192,
//	HEADER_XX                                     = 193,
	HEADER_ZC_USER_COUNT                          = 194,
	HEADER_ZC_SPRITE_CHANGE                       = 195,
	HEADER_ZC_SELECT_DEALTYPE                     = 196,
//	HEADER_XX                                     = 197,
	HEADER_ZC_PC_PURCHASE_ITEMLIST                = 198,
	HEADER_ZC_PC_SELL_ITEMLIST                    = 199,
//	HEADER_XX                                     = 200,
//	HEADER_XX                                     = 201,
	HEADER_ZC_PC_PURCHASE_RESULT                  = 202,
	HEADER_ZC_PC_SELL_RESULT                      = 203,
//	HEADER_XX                                     = 204,
	HEADER_ZC_ACK_DISCONNECT_CHARACTER            = 205,
//	HEADER_XX                                     = 206,
//	HEADER_XX                                     = 207,
//	HEADER_XX                                     = 208,
	HEADER_ZC_SETTING_WHISPER_PC                  = 209,
	HEADER_ZC_SETTING_WHISPER_STATE               = 210,
//	HEADER_XX                                     = 211,
	HEADER_ZC_WHISPER_LIST                        = 212,
//	HEADER_XX                                     = 213,
	HEADER_ZC_ACK_CREATE_CHATROOM                 = 214,
	HEADER_ZC_ROOM_NEWENTRY                       = 215,
	HEADER_ZC_DESTROY_ROOM                        = 216,
//	HEADER_XX                                     = 217,
	HEADER_ZC_REFUSE_ENTER_ROOM                   = 218,
	HEADER_ZC_ENTER_ROOM                          = 219,
	HEADER_ZC_MEMBER_NEWENTRY                     = 220,
	HEADER_ZC_MEMBER_EXIT                         = 221,
//	HEADER_XX                                     = 222,
	HEADER_ZC_CHANGE_CHATROOM                     = 223,
//	HEADER_XX                                     = 224,
	HEADER_ZC_ROLE_CHANGE                         = 225,
//	HEADER_XX                                     = 226,
//	HEADER_XX                                     = 227,
//	HEADER_XX                                     = 228,
	HEADER_ZC_REQ_EXCHANGE_ITEM                   = 229,
//	HEADER_XX                                     = 230,
	HEADER_ZC_ACK_EXCHANGE_ITEM                   = 231,
//	HEADER_XX                                     = 232,
//	HEADER_XX                                     = 233,
	HEADER_ZC_ACK_ADD_EXCHANGE_ITEM               = 234,
//	HEADER_XX                                     = 235,
	HEADER_ZC_CONCLUDE_EXCHANGE_ITEM              = 236,
//	HEADER_XX                                     = 237,
	HEADER_ZC_CANCEL_EXCHANGE_ITEM                = 238,
//	HEADER_XX                                     = 239,
	HEADER_ZC_EXEC_EXCHANGE_ITEM                  = 240,
	HEADER_ZC_EXCHANGEITEM_UNDO                   = 241,
	HEADER_ZC_NOTIFY_STOREITEM_COUNTINFO          = 242,
//	HEADER_XX                                     = 243,
	HEADER_ZC_ADD_ITEM_TO_STORE                   = 244,
//	HEADER_XX                                     = 245,
	HEADER_ZC_DELETE_ITEM_FROM_STORE              = 246,
//	HEADER_XX                                     = 247,
	HEADER_ZC_CLOSE_STORE                         = 248,
//	HEADER_XX                                     = 249,
	HEADER_ZC_ACK_MAKE_GROUP                      = 250,
	HEADER_ZC_GROUP_LIST                          = 251,
//	HEADER_XX                                     = 252,
	HEADER_ZC_ACK_REQ_JOIN_GROUP                  = 253,
	HEADER_ZC_REQ_JOIN_GROUP                      = 254,
//	HEADER_XX                                     = 255,
//	HEADER_XX                                     = 256,
	HEADER_ZC_GROUPINFO_CHANGE                    = 257,
//	HEADER_XX                                     = 258,
//	HEADER_XX                                     = 259,
	HEADER_ZC_ADD_MEMBER_TO_GROUP                 = 260,
	HEADER_ZC_DELETE_MEMBER_FROM_GROUP            = 261,
	HEADER_ZC_NOTIFY_HP_TO_GROUPM                 = 262,
	HEADER_ZC_NOTIFY_POSITION_TO_GROUPM           = 263,
//	HEADER_XX                                     = 264,
	HEADER_ZC_NOTIFY_CHAT_PARTY                   = 265,
	HEADER_ZC_MVP_GETTING_ITEM                    = 266,
	HEADER_ZC_MVP_GETTING_SPECIAL_EXP             = 267,
	HEADER_ZC_MVP                                 = 268,
	HEADER_ZC_THROW_MVPITEM                       = 269,
	HEADER_ZC_SKILLINFO_UPDATE                    = 270,
	HEADER_ZC_SKILLINFO_LIST                      = 271,
	HEADER_ZC_ACK_TOUSESKILL                      = 272,
	HEADER_ZC_ADD_SKILL                           = 273,
//	HEADER_XX                                     = 274,
//	HEADER_XX                                     = 275,
	HEADER_ZC_NOTIFY_SKILL                        = 276,
	HEADER_ZC_NOTIFY_SKILL_POSITION               = 277,
//	HEADER_XX                                     = 278,
	HEADER_ZC_NOTIFY_GROUNDSKILL                  = 279,
//	HEADER_XX                                     = 280,
	HEADER_ZC_STATE_CHANGE                        = 281,
	HEADER_ZC_USE_SKILL                           = 282,
//	HEADER_XX                                     = 283,
	HEADER_ZC_WARPLIST                            = 284,
//	HEADER_XX                                     = 285,
	HEADER_ZC_ACK_REMEMBER_WARPPOINT              = 286,
	HEADER_ZC_SKILL_ENTRY                         = 287,
	HEADER_ZC_SKILL_DISAPPEAR                     = 288,
	HEADER_ZC_NOTIFY_CARTITEM_COUNTINFO           = 289,
	HEADER_ZC_CART_EQUIPMENT_ITEMLIST             = 290,
	HEADER_ZC_CART_NORMAL_ITEMLIST                = 291,
	HEADER_ZC_ADD_ITEM_TO_CART                    = 292,
	HEADER_ZC_DELETE_ITEM_FROM_CART               = 293,
//	HEADER_XX                                     = 294,
//	HEADER_XX                                     = 295,
//	HEADER_XX                                     = 296,
//	HEADER_XX                                     = 297,
//	HEADER_XX                                     = 298,
	HEADER_ZC_CARTOFF                             = 299,
	HEADER_ZC_ACK_ADDITEM_TO_CART                 = 300,
	HEADER_ZC_OPENSTORE                           = 301,
//	HEADER_XX                                     = 302,
//	HEADER_XX                                     = 303,
//	HEADER_XX                                     = 304,
	HEADER_ZC_STORE_ENTRY                         = 305,
	HEADER_ZC_DISAPPEAR_ENTRY                     = 306,
	HEADER_ZC_PC_PURCHASE_ITEMLIST_FROMMC         = 307,
//	HEADER_XX                                     = 308,
	HEADER_ZC_PC_PURCHASE_RESULT_FROMMC           = 309,
	HEADER_ZC_PC_PURCHASE_MYITEMLIST              = 310,
	HEADER_ZC_DELETEITEM_FROM_MCSTORE             = 311,
//	HEADER_XX                                     = 312,
	HEADER_ZC_ATTACK_FAILURE_FOR_DISTANCE         = 313,
	HEADER_ZC_ATTACK_RANGE                        = 314,
	HEADER_ZC_ACTION_FAILURE                      = 315,
	HEADER_ZC_EQUIP_ARROW                         = 316,
	HEADER_ZC_RECOVERY                            = 317,
	HEADER_ZC_USESKILL_ACK                        = 318,
//	HEADER_XX                                     = 319,
//	HEADER_XX                                     = 320,
	HEADER_ZC_COUPLESTATUS                        = 321,
	HEADER_ZC_OPEN_EDITDLG                        = 322,
//	HEADER_XX                                     = 323,
	HEADER_ZC_COMPASS                             = 324,
	HEADER_ZC_SHOW_IMAGE                          = 325,
//	HEADER_XX                                     = 326,
	HEADER_ZC_AUTORUN_SKILL                       = 327,
	HEADER_ZC_RESURRECTION                        = 328,
//	HEADER_XX                                     = 329,
	HEADER_ZC_ACK_GIVE_MANNER_POINT               = 330,
	HEADER_ZC_NOTIFY_MANNER_POINT_GIVEN           = 331,
	HEADER_ZC_MYGUILD_BASIC_INFO                  = 332,
//	HEADER_XX                                     = 333,
	HEADER_ZC_ACK_GUILD_MENUINTERFACE             = 334,
//	HEADER_XX                                     = 335,
	HEADER_ZC_GUILD_INFO                          = 336,
//	HEADER_XX                                     = 337,
	HEADER_ZC_GUILD_EMBLEM_IMG                    = 338,
//	HEADER_XX                                     = 339,
	HEADER_ZC_MEMBERMGR_INFO                      = 340,
//	HEADER_XX                                     = 341,
	HEADER_ZC_ACK_REQ_CHANGE_MEMBERS              = 342,
//	HEADER_XX                                     = 343,
	HEADER_ZC_ACK_OPEN_MEMBER_INFO                = 344,
//	HEADER_XX                                     = 345,
	HEADER_ZC_ACK_LEAVE_GUILD                     = 346,
//	HEADER_XX                                     = 347,
	HEADER_ZC_ACK_BAN_GUILD                       = 348,
//	HEADER_XX                                     = 349,
	HEADER_ZC_ACK_DISORGANIZE_GUILD_RESULT        = 350,
	HEADER_ZC_ACK_DISORGANIZE_GUILD               = 351,
	HEADER_ZC_POSITION_INFO                       = 352,
//	HEADER_XX                                     = 353,
	HEADER_ZC_GUILD_SKILLINFO                     = 354,
	HEADER_ZC_BAN_LIST                            = 355,
	HEADER_ZC_OTHER_GUILD_LIST                    = 356,
//	HEADER_XX                                     = 357,
	HEADER_ZC_POSITION_ID_NAME_INFO               = 358,
	HEADER_ZC_RESULT_MAKE_GUILD                   = 359,
//	HEADER_XX                                     = 360,
	HEADER_ZC_ACK_REQ_JOIN_GUILD                  = 361,
	HEADER_ZC_REQ_JOIN_GUILD                      = 362,
//	HEADER_XX                                     = 363,
	HEADER_ZC_UPDATE_GDID                         = 364,
	HEADER_ZC_UPDATE_CHARSTAT                     = 365,
//	HEADER_XX                                     = 366,
	HEADER_ZC_GUILD_NOTICE                        = 367,
//	HEADER_XX                                     = 368,
	HEADER_ZC_REQ_ALLY_GUILD                      = 369,
//	HEADER_XX                                     = 370,
	HEADER_ZC_ACK_REQ_ALLY_GUILD                  = 371,
	HEADER_ZC_ACK_CHANGE_GUILD_POSITIONINFO       = 372,
//	HEADER_XX                                     = 373,
//	HEADER_XX                                     = 374,
	HEADER_ZC_ITEMIDENTIFY_LIST                   = 375,
//	HEADER_XX                                     = 376,
	HEADER_ZC_ACK_ITEMIDENTIFY                    = 377,
//	HEADER_XX                                     = 378,
	HEADER_ZC_ITEMCOMPOSITION_LIST                = 379,
//	HEADER_XX                                     = 380,
	HEADER_ZC_ACK_ITEMCOMPOSITION                 = 381,
//	HEADER_XX                                     = 382,
	HEADER_ZC_GUILD_CHAT                          = 383,
//	HEADER_XX                                     = 384,
	HEADER_ZC_ACK_REQ_HOSTILE_GUILD               = 385,
	HEADER_ZC_MEMBER_ADD                          = 386,
//	HEADER_XX                                     = 387,
	HEADER_ZC_DELETE_RELATED_GUILD                = 388,
	HEADER_ZC_ADD_RELATED_GUILD                   = 389,
//	HEADER_XX                                     = 390,
	HEADER_PING                                   = 391,
	HEADER_ZC_ACK_ITEMREFINING                    = 392,
	HEADER_ZC_NOTIFY_MAPINFO                      = 393,
//	HEADER_XX                                     = 394,
	HEADER_ZC_ACK_REQ_DISCONNECT                  = 395,
	HEADER_ZC_MONSTER_INFO                        = 396,
	HEADER_ZC_MAKABLEITEMLIST                     = 397,
//	HEADER_XX                                     = 398,
	HEADER_ZC_ACK_REQMAKINGITEM                   = 399,
//	HEADER_XX                                     = 400,
	HEADER_ZC_TALKBOX_CHATCONTENTS                = 401,
	HEADER_ZC_UPDATE_MAPINFO                      = 402,
//	HEADER_XX                                     = 403,
	HEADER_ZC_ACK_REQNAME_BYGID                   = 404,
	HEADER_ZC_ACK_REQNAMEALL                      = 405,
	HEADER_ZC_MSG_STATE_CHANGE                    = 406,
//	HEADER_XX                                     = 407,
//	HEADER_XX                                     = 408,
	HEADER_ZC_NOTIFY_MAPPROPERTY                  = 409,
	HEADER_ZC_NOTIFY_RANKING                      = 410,
	HEADER_ZC_NOTIFY_EFFECT                       = 411,
//	HEADER_XX                                     = 412,
//	HEADER_XX                                     = 413,
	HEADER_ZC_START_CAPTURE                       = 414,
//	HEADER_XX                                     = 415,
	HEADER_ZC_TRYCAPTURE_MONSTER                  = 416,
//	HEADER_XX                                     = 417,
	HEADER_ZC_PROPERTY_PET                        = 418,
	HEADER_ZC_FEED_PET                            = 419,
	HEADER_ZC_CHANGESTATE_PET                     = 420,
//	HEADER_XX                                     = 421,
	HEADER_ZC_PETEGG_LIST                         = 422,
//	HEADER_XX                                     = 423,
//	HEADER_XX                                     = 424,
//	HEADER_XX                                     = 425,
	HEADER_ZC_PET_ACT                             = 426,
	HEADER_ZC_PAR_CHANGE_USER                     = 427,
	HEADER_ZC_SKILL_UPDATE                        = 428,
	HEADER_ZC_MAKINGARROW_LIST                    = 429,
//	HEADER_XX                                     = 430,
//	HEADER_XX                                     = 431,
	HEADER_ZC_NPCSPRITE_CHANGE                    = 432,
	HEADER_ZC_SHOWDIGIT                           = 433,
//	HEADER_XX                                     = 434,
	HEADER_ZC_SHOW_IMAGE2                         = 435,
	HEADER_ZC_CHANGE_GUILD                        = 436,
	HEADER_SC_BILLING_INFO                        = 437,
	HEADER_ZC_GUILD_INFO2                         = 438,
//	HEADER_XX                                     = 439,
	HEADER_ZC_GUILD_ZENY_ACK                      = 440,
	HEADER_ZC_DISPEL                              = 441,
//	HEADER_XX                                     = 442,
//	HEADER_XX                                     = 443,
//	HEADER_XX                                     = 444,
//	HEADER_XX                                     = 445,
	HEADER_AC_ASK_PNGAMEROOM                      = 446,
	HEADER_CA_REPLY_PNGAMEROOM                    = 447,
//	HEADER_XX                                     = 448,
	HEADER_ZC_REPLY_REMAINTIME                    = 449,
	HEADER_ZC_INFO_REMAINTIME                     = 450,
	HEADER_ZC_BROADCAST2                          = 451,
	HEADER_ZC_ADD_ITEM_TO_STORE2                  = 452,
	HEADER_ZC_ADD_ITEM_TO_CART2                   = 453,
//	HEADER_XX                                     = 454,
	HEADER_SC_ACK_ENCRYPTION                      = 455,
	HEADER_ZC_USE_ITEM_ACK2                       = 456,
	HEADER_ZC_SKILL_ENTRY2                        = 457,
//	HEADER_XX                                     = 458,
//	HEADER_XX                                     = 459,
	HEADER_ZC_MONSTER_TALK                        = 460,
	HEADER_ZC_AUTOSPELLLIST                       = 461,
//	HEADER_XX                                     = 462,
	HEADER_ZC_DEVOTIONLIST                        = 463,
	HEADER_ZC_SPIRITS                             = 464,
	HEADER_ZC_BLADESTOP                           = 465,
	HEADER_ZC_COMBODELAY                          = 466,
	HEADER_ZC_SOUND                               = 467,
	HEADER_ZC_OPEN_EDITDLGSTR                     = 468,
//	HEADER_XX                                     = 469,
	HEADER_ZC_NOTIFY_MAPPROPERTY2                 = 470,
	HEADER_ZC_SPRITE_CHANGE2                      = 471,
	HEADER_ZC_NOTIFY_STANDENTRY2                  = 472,
	HEADER_ZC_NOTIFY_NEWENTRY2                    = 473,
	HEADER_ZC_NOTIFY_MOVEENTRY2                   = 474,
	HEADER_CA_REQ_HASH                            = 475,
	HEADER_AC_ACK_HASH                            = 476,
	HEADER_CA_LOGIN2                              = 477,
	HEADER_ZC_NOTIFY_SKILL2                       = 478,
//	HEADER_XX                                     = 479,
	HEADER_ZC_ACK_ACCOUNTNAME                     = 480,
	HEADER_ZC_SPIRITS2                            = 481,
	HEADER_ZC_REQ_COUPLE                          = 482,
//	HEADER_XX                                     = 483,
	HEADER_ZC_START_COUPLE                        = 484,
//	HEADER_XX                                     = 485,
	HEADER_ZC_COUPLENAME                          = 486,
//	HEADER_XX                                     = 487,
//	HEADER_XX                                     = 488,
	HEADER_ZC_ADD_MEMBER_TO_GROUP2                = 489,
	HEADER_ZC_CONGRATULATION                      = 490,
	HEADER_ZC_NOTIFY_POSITION_TO_GUILDM           = 491,
	HEADER_ZC_GUILD_MEMBER_MAP_CHANGE             = 492,
//	HEADER_XX                                     = 493,
	HEADER_ZC_NORMAL_ITEMLIST2                    = 494,
	HEADER_ZC_CART_NORMAL_ITEMLIST2               = 495,
	HEADER_ZC_STORE_NORMAL_ITEMLIST2              = 496,
	HEADER_AC_NOTIFY_ERROR                        = 497,
	HEADER_ZC_UPDATE_CHARSTAT2                    = 498,
	HEADER_ZC_NOTIFY_EFFECT2                      = 499,
	HEADER_ZC_REQ_EXCHANGE_ITEM2                  = 500,
	HEADER_ZC_ACK_EXCHANGE_ITEM2                  = 501,
	HEADER_ZC_REQ_BABY                            = 502,
//	HEADER_XX                                     = 503,
	HEADER_ZC_START_BABY                          = 504,
//	HEADER_XX                                     = 505,
	HEADER_CA_LOGIN3                              = 506,
//	HEADER_XX                                     = 507,
	HEADER_ZC_REPAIRITEMLIST                      = 508,
//	HEADER_XX                                     = 509,
	HEADER_ZC_ACK_ITEMREPAIR                      = 510,
	HEADER_ZC_HIGHJUMP                            = 511,
//	HEADER_XX                                     = 512,
	HEADER_ZC_FRIENDS_LIST                        = 513,
//	HEADER_XX                                     = 514,
//	HEADER_XX                                     = 515,
//	HEADER_XX                                     = 516,
	HEADER_ZC_DIVORCE                             = 517,
	HEADER_ZC_FRIENDS_STATE                       = 518,
	HEADER_ZC_REQ_ADD_FRIENDS                     = 519,
//	HEADER_XX                                     = 520,
	HEADER_ZC_ADD_FRIENDS_LIST                    = 521,
	HEADER_ZC_DELETE_FRIENDS                      = 522,
	HEADER_CH_EXE_HASHCHECK                       = 523,
	HEADER_CZ_EXE_HASHCHECK                       = 524,
	HEADER_HC_BLOCK_CHARACTER                     = 525,
	HEADER_ZC_STARSKILL                           = 526,
//	HEADER_XX                                     = 527,
	HEADER_ZC_ACK_PVPPOINT                        = 528,
//	HEADER_XX                                     = 529,
//	HEADER_XX                                     = 530,
//	HEADER_XX                                     = 531,
	HEADER_ZC_ACK_STATUS_GM                       = 532,
	HEADER_ZC_SKILLMSG                            = 533,
	HEADER_ZC_BABYMSG                             = 534,
//	HEADER_XX                                     = 535,
//	HEADER_XX                                     = 536,
	HEADER_ZC_BLACKSMITH_RANK                     = 537,
	HEADER_ZC_ALCHEMIST_RANK                      = 538,
	HEADER_ZC_BLACKSMITH_POINT                    = 539,
	HEADER_ZC_ALCHEMIST_POINT                     = 540,
//	HEADER_XX                                     = 541,
//	HEADER_XX                                     = 542,
	HEADER_ZC_NOTIFY_PKINFO                       = 543,
	HEADER_ZC_NOTIFY_CRAZYKILLER                  = 544,
	HEADER_ZC_NOTIFY_WEAPONITEMLIST               = 545,
//	HEADER_XX                                     = 546,
	HEADER_ZC_ACK_WEAPONREFINE                    = 547,
	HEADER_ZC_TAEKWON_POINT                       = 548,
//	HEADER_XX                                     = 549,
	HEADER_ZC_TAEKWON_RANK                        = 550,
	HEADER_ZC_GAME_GUARD                          = 551,
//	HEADER_XX                                     = 552,
	HEADER_ZC_STATE_CHANGE3                       = 553,
	HEADER_ZC_NOTIFY_STANDENTRY3                  = 554,
	HEADER_ZC_NOTIFY_NEWENTRY3                    = 555,
	HEADER_ZC_NOTIFY_MOVEENTRY3                   = 556,
//	HEADER_XX                                     = 557,
	HEADER_ZC_PROPERTY_HOMUN                      = 558,
	HEADER_ZC_FEED_MER                            = 559,
	HEADER_ZC_CHANGESTATE_MER                     = 560,
//	HEADER_XX                                     = 561,
//	HEADER_XX                                     = 562,
//	HEADER_XX                                     = 563,
//	HEADER_XX                                     = 564,
	HEADER_ZC_HOSKILLINFO_LIST                    = 565,
	HEADER_ZC_KILLER_POINT                        = 566,
//	HEADER_XX                                     = 567,
	HEADER_ZC_KILLER_RANK                         = 568,
	HEADER_ZC_HOSKILLINFO_UPDATE                  = 569,
//	HEADER_XX                                     = 570,
//	HEADER_XX                                     = 571,
//	HEADER_XX                                     = 572,
	HEADER_AC_EVENT_RESULT                        = 573,
//	HEADER_XX                                     = 574,
//	HEADER_XX                                     = 575,
	HEADER_ZC_MAIL_REQ_GET_LIST                   = 576,
//	HEADER_XX                                     = 577,
	HEADER_ZC_MAIL_REQ_OPEN                       = 578,
//	HEADER_XX                                     = 579,
//	HEADER_XX                                     = 580,
	HEADER_ZC_MAIL_REQ_GET_ITEM                   = 581,
//	HEADER_XX                                     = 582,
//	HEADER_XX                                     = 583,
//	HEADER_XX                                     = 584,
	HEADER_ZC_MAIL_REQ_SEND                       = 585,
	HEADER_ZC_MAIL_RECEIVE                        = 586,
//	HEADER_XX                                     = 587,
//	HEADER_XX                                     = 588,
//	HEADER_XX                                     = 589,
//	HEADER_XX                                     = 590,
//	HEADER_XX                                     = 591,
	HEADER_ZC_AUCTION_RESULT                      = 592,
//	HEADER_XX                                     = 593,
	HEADER_ZC_AUCTION_ITEM_REQ_SEARCH             = 594,
	HEADER_ZC_STARPLACE                           = 595,
//	HEADER_XX                                     = 596,
	HEADER_ZC_ACK_MAIL_ADD_ITEM                   = 597,
	HEADER_ZC_ACK_AUCTION_ADD_ITEM                = 598,
	HEADER_ZC_ACK_MAIL_DELETE                     = 599,
//	HEADER_XX                                     = 600,
//	HEADER_XX                                     = 601,
	HEADER_ZC_MAKINGITEM_LIST                     = 602,
//	HEADER_XX                                     = 603,
//	HEADER_XX                                     = 604,
	HEADER_CZ_AUCTION_REQ_MY_SELL_STOP            = 605,
//	HEADER_XX                                     = 606,
	HEADER_ZC_AUCTION_WINDOWS                     = 607,
	HEADER_ZC_MAIL_WINDOWS                        = 608,
//	HEADER_XX                                     = 609,
//	HEADER_XX                                     = 610,
//	HEADER_XX                                     = 611,
//	HEADER_XX                                     = 612,
//	HEADER_XX                                     = 613,
//	HEADER_XX                                     = 614,
//	HEADER_XX                                     = 615,
//	HEADER_XX                                     = 616,
//	HEADER_XX                                     = 617,
//	HEADER_XX                                     = 618,
//	HEADER_XX                                     = 619,
//	HEADER_XX                                     = 620,
//	HEADER_XX                                     = 621,
//	HEADER_XX                                     = 622,
//	HEADER_XX                                     = 623,
//	HEADER_XX                                     = 624,
//	HEADER_XX                                     = 625,
//	HEADER_XX                                     = 626,
//	HEADER_XX                                     = 627,
	HEADER_ZC_ACK_MAIL_RETURN                     = 628,
//	HEADER_XX                                     = 629,
//	HEADER_XX                                     = 630,
//	HEADER_XX                                     = 631,
//	HEADER_XX                                     = 632,
//	HEADER_XX                                     = 633,
	HEADER_ZC_HUNTINGLIST                         = 634,
	HEADER_ZC_PCBANG_EFFECT                       = 635,
	HEADER_CA_LOGIN4                              = 636,
//	HEADER_XX                                     = 637,
//	HEADER_XX                                     = 638,
//	HEADER_XX                                     = 639,
	HEADER_ZC_GANGSI_POINT                        = 640,
//	HEADER_XX                                     = 641,
	HEADER_ZC_GANGSI_RANK                         = 642,
	HEADER_ZC_AID                                 = 643,
	HEADER_ZC_NOTIFY_EFFECT3                      = 644,
	HEADER_ZC_DEATH_QUESTION                      = 645,
//	HEADER_XX                                     = 646,
	HEADER_ZC_PC_CASH_POINT_ITEMLIST              = 647,
//	HEADER_XX                                     = 648,
	HEADER_ZC_PC_CASH_POINT_UPDATE                = 649,
	HEADER_ZC_NPC_SHOWEFST_UPDATE                 = 650,
	HEADER_HC_CHARNOTBEENSELECTED                 = 651,
//	HEADER_XX                                     = 652,
//	HEADER_XX                                     = 653,
	HEADER_HC_ACK_IS_VALID_CHARNAME               = 654,
//	HEADER_XX                                     = 655,
	HEADER_HC_ACK_CHANGE_CHARNAME                 = 656,
	HEADER_ZC_MSG                                 = 657,
//	HEADER_XX                                     = 658,
	HEADER_ZC_BOSS_INFO                           = 659,
	HEADER_ZC_READ_BOOK                           = 660,
	HEADER_ZC_EQUIPMENT_ITEMLIST2                 = 661,
	HEADER_ZC_STORE_EQUIPMENT_ITEMLIST2           = 662,
	HEADER_ZC_CART_EQUIPMENT_ITEMLIST2            = 663,
	HEADER_ZC_CASH_TIME_COUNTER                   = 664,
	HEADER_ZC_CASH_ITEM_DELETE                    = 665,
	HEADER_ZC_ITEM_PICKUP_ACK2                    = 666,
	HEADER_ZC_MER_INIT                            = 667,
//	HEADER_XX                                     = 668,
	HEADER_ZC_MER_SKILLINFO_LIST                  = 669,
	HEADER_ZC_MER_SKILLINFO_UPDATE                = 670,
//	HEADER_XX                                     = 671,
//	HEADER_XX                                     = 672,
//	HEADER_XX                                     = 673,
	HEADER_ZC_MER_PAR_CHANGE                      = 674,
//	HEADER_XX                                     = 675,
//	HEADER_XX                                     = 676,
//	HEADER_XX                                     = 677,
//	HEADER_XX                                     = 678,
//	HEADER_XX                                     = 679,
//	HEADER_XX                                     = 680,
//	HEADER_XX                                     = 681,
//	HEADER_XX                                     = 682,
//	HEADER_XX                                     = 683,
//	HEADER_XX                                     = 684,
//	HEADER_XX                                     = 685,
//	HEADER_XX                                     = 686,
//	HEADER_XX                                     = 687,
//	HEADER_XX                                     = 688,
	HEADER_ZC_ALL_QUEST_LIST                      = 689,
	HEADER_ZC_ALL_QUEST_MISSION                   = 690,
	HEADER_ZC_ADD_QUEST                           = 691,
	HEADER_ZC_DEL_QUEST                           = 692,
	HEADER_ZC_UPDATE_MISSION_HUNT                 = 693,
//	HEADER_XX                                     = 694,
	HEADER_ZC_ACTIVE_QUEST                        = 695,
	HEADER_ZC_ITEM_PICKUP_PARTY                   = 696,
	HEADER_ZC_SHORTCUT_KEY_LIST                   = 697,
//	HEADER_XX                                     = 698,
	HEADER_ZC_EQUIPITEM_DAMAGED                   = 699,
//	HEADER_XX                                     = 700,
//	HEADER_XX                                     = 701,
//	HEADER_XX                                     = 702,
	HEADER_ZC_SRPACKETR2_INIT                     = 703,
	HEADER_CZ_SRPACKETR2_START                    = 704,
	HEADER_ZC_NPC_CHAT                            = 705,
	HEADER_ZC_FORMATSTRING_MSG                    = 706,
//	HEADER_XX                                     = 707,
//	HEADER_XX                                     = 708,
	HEADER_ZC_PARTY_JOIN_REQ_ACK                  = 709,
	HEADER_ZC_PARTY_JOIN_REQ                      = 710,
//	HEADER_XX                                     = 711,
//	HEADER_XX                                     = 712,
	HEADER_ZC_PARTY_CONFIG                        = 713,
	HEADER_HC_REFUSE_SELECTCHAR                   = 714,
	HEADER_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO   = 715,
	HEADER_ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY = 716,
	HEADER_ZC_MEMORIALDUNGEON_INFO                = 717,
	HEADER_ZC_MEMORIALDUNGEON_NOTIFY              = 718,
//	HEADER_XX                                     = 719,
	HEADER_ZC_EQUIPMENT_ITEMLIST3                 = 720,
	HEADER_ZC_STORE_EQUIPMENT_ITEMLIST3           = 721,
	HEADER_ZC_CART_EQUIPMENT_ITEMLIST3            = 722,
	HEADER_ZC_NOTIFY_BIND_ON_EQUIP                = 723,
	HEADER_ZC_ITEM_PICKUP_ACK3                    = 724,
	HEADER_ZC_ISVR_DISCONNECT                     = 725,
//	HEADER_XX                                     = 726,
	HEADER_ZC_EQUIPWIN_MICROSCOPE                 = 727,
//	HEADER_XX                                     = 728,
	HEADER_ZC_CONFIG                              = 729,
	HEADER_ZC_CONFIG_NOTIFY                       = 730,
//	HEADER_XX                                     = 731,
	HEADER_ZC_BATTLEFIELD_CHAT                    = 732,
	HEADER_ZC_BATTLEFIELD_NOTIFY_CAMPINFO         = 733,
	HEADER_ZC_BATTLEFIELD_NOTIFY_POINT            = 734,
	HEADER_ZC_BATTLEFIELD_NOTIFY_POSITION         = 735,
	HEADER_ZC_BATTLEFIELD_NOTIFY_HP               = 736,
	HEADER_ZC_NOTIFY_ACT2                         = 737,
//	HEADER_XX                                     = 738,
//	HEADER_XX                                     = 739,
//	HEADER_XX                                     = 740,
//	HEADER_XX                                     = 741,
//	HEADER_XX                                     = 742,
	HEADER_ZC_MAPPROPERTY                         = 743,
	HEADER_ZC_NORMAL_ITEMLIST3                    = 744,
	HEADER_ZC_CART_NORMAL_ITEMLIST3               = 745,
	HEADER_ZC_STORE_NORMAL_ITEMLIST3              = 746,
	HEADER_ZC_ACCEPT_ENTER2                       = 747,
	HEADER_ZC_NOTIFY_MOVEENTRY4                   = 748,
	HEADER_ZC_NOTIFY_NEWENTRY4                    = 749,
	HEADER_ZC_NOTIFY_STANDENTRY4                  = 750,
	HEADER_ZC_NOTIFY_FONT                         = 751,
	HEADER_ZC_PROGRESS                            = 752,
//	HEADER_XX                                     = 753,
	HEADER_ZC_PROGRESS_CANCEL                     = 754,
	HEADER_ZC_ITEM_FALL_ENTRY2                    = 755,
	HEADER_ZC_ITEM_FALL_ENTRY2__M1                = 756,
	HEADER_ZC_ITEM_FALL_ENTRY2__M2                = 757,
	HEADER_ZC_ITEM_FALL_ENTRY2__M3                = 758,
	HEADER_ZC_ITEM_FALL_ENTRY2__M4                = 759,
	HEADER_ZC_ITEM_FALL_ENTRY2__M5                = 760,
	HEADER_ZC_ITEM_FALL_ENTRY2__M6                = 761,
	HEADER_ZC_NOTIFY_MOVEENTRY5                   = 762,
	HEADER_ZC_NOTIFY_MOVEENTRY5__M1               = 763,
	HEADER_ZC_NOTIFY_MOVEENTRY5__M2               = 764,
	HEADER_ZC_NOTIFY_MOVEENTRY5__M3               = 765,
	HEADER_ZC_NOTIFY_MOVEENTRY5__M4               = 766,
	HEADER_ZC_NOTIFY_MOVEENTRY5__M5               = 767,
	HEADER_ZC_NOTIFY_MOVEENTRY5__M6               = 768,
	HEADER_ZC_NOTIFY_NPC_STANDENTRY               = 769,
	HEADER_ZC_NOTIFY_NPC_STANDENTRY__M1           = 770,
	HEADER_ZC_NOTIFY_NPC_STANDENTRY__M2           = 771,
	HEADER_ZC_NOTIFY_NPC_STANDENTRY__M3           = 772,
	HEADER_ZC_NOTIFY_NPC_STANDENTRY__M4           = 773,
	HEADER_ZC_NOTIFY_NPC_STANDENTRY__M5           = 774,
	HEADER_ZC_NOTIFY_NPC_STANDENTRY__M6           = 775,
	HEADER_ZC_REASSEMBLY_CERTIFY                  = 776,
	HEADER_ZC_REASSEMBLY_CERTIFY__M01             = 777,
	HEADER_ZC_REASSEMBLY_CERTIFY__M02             = 778,
	HEADER_ZC_REASSEMBLY_CERTIFY__M03             = 779,
	HEADER_ZC_REASSEMBLY_CERTIFY__M04             = 780,
	HEADER_ZC_REASSEMBLY_CERTIFY__M05             = 781,
	HEADER_ZC_REASSEMBLY_CERTIFY__M06             = 782,
	HEADER_ZC_REASSEMBLY_CERTIFY__M07             = 783,
	HEADER_ZC_REASSEMBLY_CERTIFY__M08             = 784,
	HEADER_ZC_REASSEMBLY_CERTIFY__M09             = 785,
	HEADER_ZC_REASSEMBLY_CERTIFY__M10             = 786,
	HEADER_ZC_REASSEMBLY_CERTIFY__M11             = 787,
	HEADER_ZC_REASSEMBLY_CERTIFY__M12             = 788,
	HEADER_ZC_REASSEMBLY_CERTIFY__M13             = 789,
	HEADER_ZC_REASSEMBLY_CERTIFY__M14             = 790,
	HEADER_ZC_REASSEMBLY_CERTIFY__M15             = 791,
	HEADER_ZC_REASSEMBLY_CERTIFY__M16             = 792,
	HEADER_ZC_REASSEMBLY_CERTIFY__M17             = 793,
	HEADER_ZC_REASSEMBLY_CERTIFY__M18             = 794,
	HEADER_ZC_REASSEMBLY_CERTIFY__M19             = 795,
	HEADER_ZC_REASSEMBLY_CERTIFY__M20             = 796,
	HEADER_ZC_REASSEMBLY_CERTIFY__M21             = 797,
	HEADER_ZC_REASSEMBLY_CERTIFY__M22             = 798,
	HEADER_ZC_REASSEMBLY_CERTIFY__M23             = 799,
	HEADER_ZC_REASSEMBLY_CERTIFY__M24             = 800,
	HEADER_ZC_REASSEMBLY_CERTIFY__M25             = 801,
	HEADER_ZC_REASSEMBLY_CERTIFY__M26             = 802,
	HEADER_ZC_REASSEMBLY_CERTIFY__M27             = 803,
	HEADER_ZC_REASSEMBLY_CERTIFY__M28             = 804,
	HEADER_ZC_REASSEMBLY_CERTIFY__M29             = 805,
	HEADER_ZC_REASSEMBLY_CERTIFY__M30             = 806,
	HEADER_ZC_REASSEMBLY_CERTIFY__M31             = 807,
	HEADER_ZC_REASSEMBLY_CERTIFY__M32             = 808,
	HEADER_ZC_REASSEMBLY_CERTIFY__M33             = 809,
	HEADER_ZC_REASSEMBLY_CERTIFY__M34             = 810,
	HEADER_ZC_REASSEMBLY_CERTIFY__M35             = 811,
	HEADER_ZC_REASSEMBLY_CERTIFY__M36             = 812,
	HEADER_ZC_REASSEMBLY_CERTIFY__M37             = 813,
	HEADER_ZC_REASSEMBLY_CERTIFY__M38             = 814,
	HEADER_ZC_REASSEMBLY_CERTIFY__M39             = 815,
	HEADER_ZC_REASSEMBLY_CERTIFY__M40             = 816,
	HEADER_ZC_REASSEMBLY_CERTIFY__M41             = 817,
	HEADER_CZ_REASSEMBLY_IDENTITY                 = 818,
	HEADER_CZ_REASSEMBLY_IDENTITY__M01            = 819,
	HEADER_CZ_REASSEMBLY_IDENTITY__M02            = 820,
	HEADER_CZ_REASSEMBLY_IDENTITY__M03            = 821,
	HEADER_CZ_REASSEMBLY_IDENTITY__M04            = 822,
	HEADER_CZ_REASSEMBLY_IDENTITY__M05            = 823,
	HEADER_CZ_REASSEMBLY_IDENTITY__M06            = 824,
	HEADER_CZ_REASSEMBLY_IDENTITY__M07            = 825,
	HEADER_CZ_REASSEMBLY_IDENTITY__M08            = 826,
	HEADER_CZ_REASSEMBLY_IDENTITY__M09            = 827,
	HEADER_CZ_REASSEMBLY_IDENTITY__M10            = 828,
	HEADER_CZ_REASSEMBLY_IDENTITY__M11            = 829,
	HEADER_CZ_REASSEMBLY_IDENTITY__M12            = 830,
	HEADER_CZ_REASSEMBLY_IDENTITY__M13            = 831,
	HEADER_CZ_REASSEMBLY_IDENTITY__M14            = 832,
	HEADER_CZ_REASSEMBLY_IDENTITY__M15            = 833,
	HEADER_CZ_REASSEMBLY_IDENTITY__M16            = 834,
	HEADER_CZ_REASSEMBLY_IDENTITY__M17            = 835,
	HEADER_CZ_REASSEMBLY_IDENTITY__M18            = 836,
	HEADER_CZ_REASSEMBLY_IDENTITY__M19            = 837,
	HEADER_CZ_REASSEMBLY_IDENTITY__M20            = 838,
	HEADER_CZ_REASSEMBLY_IDENTITY__M21            = 839,
	HEADER_CZ_REASSEMBLY_IDENTITY__M22            = 840,
	HEADER_CZ_REASSEMBLY_IDENTITY__M23            = 841,
	HEADER_CZ_REASSEMBLY_IDENTITY__M24            = 842,
	HEADER_CZ_REASSEMBLY_IDENTITY__M25            = 843,
	HEADER_CZ_REASSEMBLY_IDENTITY__M26            = 844,
	HEADER_CZ_REASSEMBLY_IDENTITY__M27            = 845,
	HEADER_CZ_REASSEMBLY_IDENTITY__M28            = 846,
	HEADER_CZ_REASSEMBLY_IDENTITY__M29            = 847,
	HEADER_CZ_REASSEMBLY_IDENTITY__M30            = 848,
	HEADER_CZ_REASSEMBLY_IDENTITY__M31            = 849,
	HEADER_CZ_REASSEMBLY_IDENTITY__M32            = 850,
	HEADER_CZ_REASSEMBLY_IDENTITY__M33            = 851,
	HEADER_CZ_REASSEMBLY_IDENTITY__M34            = 852,
	HEADER_CZ_REASSEMBLY_IDENTITY__M35            = 853,
	HEADER_CZ_REASSEMBLY_IDENTITY__M36            = 854,
	HEADER_CZ_REASSEMBLY_IDENTITY__M37            = 855,
	HEADER_CZ_REASSEMBLY_IDENTITY__M38            = 856,
	HEADER_CZ_REASSEMBLY_IDENTITY__M39            = 857,
	HEADER_CZ_REASSEMBLY_IDENTITY__M40            = 858,
	HEADER_CZ_REASSEMBLY_IDENTITY__M41            = 859,
//	HEADER_XX                                     = 860,
//	HEADER_XX                                     = 861,
//	HEADER_XX                                     = 862,
	HEADER_ZC_NOTIFY_MOVEENTRY6                   = 863,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M01              = 864,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M02              = 865,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M03              = 866,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M04              = 867,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M05              = 868,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M06              = 869,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M07              = 870,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M08              = 871,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M09              = 872,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M10              = 873,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M11              = 874,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M12              = 875,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M13              = 876,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M14              = 877,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M15              = 878,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M16              = 879,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M17              = 880,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M18              = 881,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M19              = 882,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M20              = 883,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M21              = 884,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M22              = 885,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M23              = 886,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M24              = 887,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M25              = 888,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M26              = 889,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M27              = 890,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M28              = 891,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M29              = 892,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M30              = 893,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M31              = 894,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M32              = 895,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M33              = 896,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M34              = 897,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M35              = 898,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M36              = 899,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M37              = 900,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M38              = 901,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M39              = 902,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M40              = 903,
	HEADER_ZC_NOTIFY_MOVEENTRY6__M41              = 904,
	HEADER_ZC_NOTIFY_STANDENTRY6                  = 905,
	HEADER_ZC_NOTIFY_STANDENTRY6__M01             = 906,
	HEADER_ZC_NOTIFY_STANDENTRY6__M02             = 907,
	HEADER_ZC_NOTIFY_STANDENTRY6__M03             = 908,
	HEADER_ZC_NOTIFY_STANDENTRY6__M04             = 909,
	HEADER_ZC_NOTIFY_STANDENTRY6__M05             = 910,
	HEADER_ZC_NOTIFY_STANDENTRY6__M06             = 911,
	HEADER_ZC_NOTIFY_STANDENTRY6__M07             = 912,
	HEADER_ZC_NOTIFY_STANDENTRY6__M08             = 913,
	HEADER_ZC_NOTIFY_STANDENTRY6__M09             = 914,
	HEADER_ZC_NOTIFY_STANDENTRY6__M10             = 915,
	HEADER_ZC_NOTIFY_STANDENTRY6__M11             = 916,
	HEADER_ZC_NOTIFY_STANDENTRY6__M12             = 917,
	HEADER_ZC_NOTIFY_STANDENTRY6__M13             = 918,
	HEADER_ZC_NOTIFY_STANDENTRY6__M14             = 919,
	HEADER_ZC_NOTIFY_STANDENTRY6__M15             = 920,
	HEADER_ZC_NOTIFY_STANDENTRY6__M16             = 921,
	HEADER_ZC_NOTIFY_STANDENTRY6__M17             = 922,
	HEADER_ZC_NOTIFY_STANDENTRY6__M18             = 923,
	HEADER_ZC_NOTIFY_STANDENTRY6__M19             = 924,
	HEADER_ZC_NOTIFY_STANDENTRY6__M20             = 925,
	HEADER_ZC_NOTIFY_STANDENTRY6__M21             = 926,
	HEADER_ZC_NOTIFY_STANDENTRY6__M22             = 927,
	HEADER_ZC_NOTIFY_STANDENTRY6__M23             = 928,
	HEADER_ZC_NOTIFY_STANDENTRY6__M24             = 929,
	HEADER_ZC_NOTIFY_STANDENTRY6__M25             = 930,
	HEADER_ZC_NOTIFY_STANDENTRY6__M26             = 931,
	HEADER_ZC_NOTIFY_STANDENTRY6__M27             = 932,
	HEADER_ZC_NOTIFY_STANDENTRY6__M28             = 933,
	HEADER_ZC_NOTIFY_STANDENTRY6__M29             = 934,
	HEADER_ZC_NOTIFY_STANDENTRY6__M30             = 935,
	HEADER_ZC_NOTIFY_STANDENTRY6__M31             = 936,
	HEADER_ZC_NOTIFY_STANDENTRY6__M32             = 937,
	HEADER_ZC_NOTIFY_STANDENTRY6__M33             = 938,
	HEADER_ZC_NOTIFY_STANDENTRY6__M34             = 939,
	HEADER_ZC_NOTIFY_STANDENTRY6__M35             = 940,
	HEADER_ZC_NOTIFY_STANDENTRY6__M36             = 941,
	HEADER_ZC_NOTIFY_STANDENTRY6__M37             = 942,
	HEADER_ZC_NOTIFY_STANDENTRY6__M38             = 943,
	HEADER_ZC_NOTIFY_STANDENTRY6__M39             = 944,
	HEADER_ZC_NOTIFY_STANDENTRY6__M40             = 945,
	HEADER_ZC_NOTIFY_STANDENTRY6__M41             = 946,
	HEADER_ZC_ITEM_FALL_ENTRY3                    = 947,
	HEADER_ZC_ITEM_FALL_ENTRY3__M01               = 948,
	HEADER_ZC_ITEM_FALL_ENTRY3__M02               = 949,
	HEADER_ZC_ITEM_FALL_ENTRY3__M03               = 950,
	HEADER_ZC_ITEM_FALL_ENTRY3__M04               = 951,
	HEADER_ZC_ITEM_FALL_ENTRY3__M05               = 952,
	HEADER_ZC_ITEM_FALL_ENTRY3__M06               = 953,
	HEADER_ZC_ITEM_FALL_ENTRY3__M07               = 954,
	HEADER_ZC_ITEM_FALL_ENTRY3__M08               = 955,
	HEADER_ZC_ITEM_FALL_ENTRY3__M09               = 956,
	HEADER_ZC_ITEM_FALL_ENTRY3__M10               = 957,
	HEADER_ZC_ITEM_FALL_ENTRY3__M11               = 958,
	HEADER_ZC_ITEM_FALL_ENTRY3__M12               = 959,
	HEADER_ZC_ITEM_FALL_ENTRY3__M13               = 960,
	HEADER_ZC_ITEM_FALL_ENTRY3__M14               = 961,
	HEADER_ZC_ITEM_FALL_ENTRY3__M15               = 962,
	HEADER_ZC_ITEM_FALL_ENTRY3__M16               = 963,
	HEADER_ZC_ITEM_FALL_ENTRY3__M17               = 964,
	HEADER_ZC_ITEM_FALL_ENTRY3__M18               = 965,
	HEADER_ZC_ITEM_FALL_ENTRY3__M19               = 966,
	HEADER_ZC_ITEM_FALL_ENTRY3__M20               = 967,
	HEADER_ZC_ITEM_FALL_ENTRY3__M21               = 968,
	HEADER_ZC_ITEM_FALL_ENTRY3__M22               = 969,
	HEADER_ZC_ITEM_FALL_ENTRY3__M23               = 970,
	HEADER_ZC_ITEM_FALL_ENTRY3__M24               = 971,
	HEADER_ZC_ITEM_FALL_ENTRY3__M25               = 972,
	HEADER_ZC_ITEM_FALL_ENTRY3__M26               = 973,
	HEADER_ZC_ITEM_FALL_ENTRY3__M27               = 974,
	HEADER_ZC_ITEM_FALL_ENTRY3__M28               = 975,
	HEADER_ZC_ITEM_FALL_ENTRY3__M29               = 976,
	HEADER_ZC_ITEM_FALL_ENTRY3__M30               = 977,
	HEADER_ZC_ITEM_FALL_ENTRY3__M31               = 978,
	HEADER_ZC_ITEM_FALL_ENTRY3__M32               = 979,
	HEADER_ZC_ITEM_FALL_ENTRY3__M33               = 980,
	HEADER_ZC_ITEM_FALL_ENTRY3__M34               = 981,
	HEADER_ZC_ITEM_FALL_ENTRY3__M35               = 982,
	HEADER_ZC_ITEM_FALL_ENTRY3__M36               = 983,
	HEADER_ZC_ITEM_FALL_ENTRY3__M37               = 984,
	HEADER_ZC_ITEM_FALL_ENTRY3__M38               = 985,
	HEADER_ZC_ITEM_FALL_ENTRY3__M39               = 986,
	HEADER_ZC_ITEM_FALL_ENTRY3__M40               = 987,
	HEADER_ZC_ITEM_FALL_ENTRY3__M41               = 988,
//	HEADER_XX                                     = 989,
//	HEADER_XX                                     = 990,
//	HEADER_XX                                     = 991,
//	HEADER_XX                                     = 992,
//	HEADER_XX                                     = 993,
	HEADER_ZC_NOTIFY_ACT3                         = 994,
	HEADER_ZC_NOTIFY_ACT3__M01                    = 995,
	HEADER_ZC_NOTIFY_ACT3__M02                    = 996,
	HEADER_ZC_NOTIFY_ACT3__M03                    = 997,
	HEADER_ZC_NOTIFY_ACT3__M04                    = 998,
	HEADER_ZC_NOTIFY_ACT3__M05                    = 999,
	HEADER_ZC_NOTIFY_ACT3__M06                    = 1000,
	HEADER_ZC_NOTIFY_ACT3__M07                    = 1001,
	HEADER_ZC_NOTIFY_ACT3__M08                    = 1002,
	HEADER_ZC_NOTIFY_ACT3__M09                    = 1003,
	HEADER_ZC_NOTIFY_ACT3__M10                    = 1004,
	HEADER_ZC_NOTIFY_ACT3__M11                    = 1005,
	HEADER_ZC_NOTIFY_ACT3__M12                    = 1006,
	HEADER_ZC_NOTIFY_ACT3__M13                    = 1007,
	HEADER_ZC_NOTIFY_ACT3__M14                    = 1008,
	HEADER_ZC_NOTIFY_ACT3__M15                    = 1009,
	HEADER_ZC_NOTIFY_ACT3__M16                    = 1010,
	HEADER_ZC_NOTIFY_ACT3__M17                    = 1011,
	HEADER_ZC_NOTIFY_ACT3__M18                    = 1012,
	HEADER_ZC_NOTIFY_ACT3__M19                    = 1013,
	HEADER_ZC_NOTIFY_ACT3__M20                    = 1014,
	HEADER_ZC_NOTIFY_ACT3__M21                    = 1015,
	HEADER_ZC_NOTIFY_ACT3__M22                    = 1016,
	HEADER_ZC_NOTIFY_ACT3__M23                    = 1017,
	HEADER_ZC_NOTIFY_ACT3__M24                    = 1018,
	HEADER_ZC_NOTIFY_ACT3__M25                    = 1019,
	HEADER_ZC_NOTIFY_ACT3__M26                    = 1020,
	HEADER_ZC_NOTIFY_ACT3__M27                    = 1021,
	HEADER_ZC_NOTIFY_ACT3__M28                    = 1022,
	HEADER_ZC_NOTIFY_ACT3__M29                    = 1023,
	HEADER_ZC_NOTIFY_ACT3__M30                    = 1024,
	HEADER_ZC_NOTIFY_ACT3__M31                    = 1025,
	HEADER_ZC_NOTIFY_ACT3__M32                    = 1026,
	HEADER_ZC_NOTIFY_ACT3__M33                    = 1027,
	HEADER_ZC_NOTIFY_ACT3__M34                    = 1028,
	HEADER_ZC_NOTIFY_ACT3__M35                    = 1029,
	HEADER_ZC_NOTIFY_ACT3__M36                    = 1030,
	HEADER_ZC_NOTIFY_ACT3__M37                    = 1031,
	HEADER_ZC_NOTIFY_ACT3__M38                    = 1032,
	HEADER_ZC_NOTIFY_ACT3__M39                    = 1033,
	HEADER_ZC_NOTIFY_ACT3__M40                    = 1034,
	HEADER_ZC_NOTIFY_ACT3__M41                    = 1035,
	HEADER_ZC_BROADCAST3                          = 1036,
	HEADER_ZC_BROADCAST3__M01                     = 1037,
	HEADER_ZC_BROADCAST3__M02                     = 1038,
	HEADER_ZC_BROADCAST3__M03                     = 1039,
	HEADER_ZC_BROADCAST3__M04                     = 1040,
	HEADER_ZC_BROADCAST3__M05                     = 1041,
	HEADER_ZC_BROADCAST3__M06                     = 1042,
	HEADER_ZC_BROADCAST3__M07                     = 1043,
	HEADER_ZC_BROADCAST3__M08                     = 1044,
	HEADER_ZC_BROADCAST3__M09                     = 1045,
	HEADER_ZC_BROADCAST3__M10                     = 1046,
	HEADER_ZC_BROADCAST3__M11                     = 1047,
	HEADER_ZC_BROADCAST3__M12                     = 1048,
	HEADER_ZC_BROADCAST3__M13                     = 1049,
	HEADER_ZC_BROADCAST3__M14                     = 1050,
	HEADER_ZC_BROADCAST3__M15                     = 1051,
	HEADER_ZC_BROADCAST3__M16                     = 1052,
	HEADER_ZC_BROADCAST3__M17                     = 1053,
	HEADER_ZC_BROADCAST3__M18                     = 1054,
	HEADER_ZC_BROADCAST3__M19                     = 1055,
	HEADER_ZC_BROADCAST3__M20                     = 1056,
	HEADER_ZC_BROADCAST3__M21                     = 1057,
	HEADER_ZC_BROADCAST3__M22                     = 1058,
	HEADER_ZC_BROADCAST3__M23                     = 1059,
	HEADER_ZC_BROADCAST3__M24                     = 1060,
	HEADER_ZC_BROADCAST3__M25                     = 1061,
	HEADER_ZC_BROADCAST3__M26                     = 1062,
	HEADER_ZC_BROADCAST3__M27                     = 1063,
	HEADER_ZC_BROADCAST3__M28                     = 1064,
	HEADER_ZC_BROADCAST3__M29                     = 1065,
	HEADER_ZC_BROADCAST3__M30                     = 1066,
	HEADER_ZC_BROADCAST3__M31                     = 1067,
	HEADER_ZC_BROADCAST3__M32                     = 1068,
	HEADER_ZC_BROADCAST3__M33                     = 1069,
	HEADER_ZC_BROADCAST3__M34                     = 1070,
	HEADER_ZC_BROADCAST3__M35                     = 1071,
	HEADER_ZC_BROADCAST3__M36                     = 1072,
	HEADER_ZC_BROADCAST3__M37                     = 1073,
	HEADER_ZC_BROADCAST3__M38                     = 1074,
	HEADER_ZC_BROADCAST3__M39                     = 1075,
	HEADER_ZC_BROADCAST3__M40                     = 1076,
	HEADER_ZC_BROADCAST3__M41                     = 1077,
//	HEADER_XX                                     = 1078,
//	HEADER_XX                                     = 1079,
//	HEADER_XX                                     = 1080,
//	HEADER_XX                                     = 1081,
//	HEADER_XX                                     = 1082,
//	HEADER_XX                                     = 1083,
//	HEADER_XX                                     = 1084,
	HEADER_ZC_SKILL_POSTDELAY                     = 1085,
	HEADER_ZC_SKILL_POSTDELAY_LIST                = 1086,
	HEADER_ZC_MSG_STATE_CHANGE2                   = 1087,
	HEADER_ZC_MILLENNIUMSHIELD                    = 1088,
	HEADER_ZC_SKILLINFO_DELETE                    = 1089,
	HEADER_ZC_SKILL_SELECT_REQUEST                = 1090,
//	HEADER_XX                                     = 1091,
//	HEADER_XX                                     = 1092,
//	HEADER_XX                                     = 1093,
	HEADER_ZC_QUEST_NOTIFY_EFFECT                 = 1094,
//	HEADER_XX                                     = 1095,
	HEADER_HC_CHARACTER_LIST                      = 1096,
//	HEADER_XX                                     = 1097,
//	HEADER_XX                                     = 1098,
//	HEADER_XX                                     = 1099,

//	HEADER_XX                                     = 2000,
//	HEADER_XX                                     = 2001,
//	HEADER_XX                                     = 2002,
//	HEADER_XX                                     = 2003,
//	HEADER_XX                                     = 2004,
//	HEADER_XX                                     = 2005,
//	HEADER_XX                                     = 2006,
//	HEADER_XX                                     = 2007,
	HEADER_ZC_REQ_GROUPINFO_CHANGE_V2             = 2008,
	HEADER_ZC_SHORTCUT_KEY_LIST_V2                = 2009,
//	HEADER_XX                                     = 2010,
	HEADER_ZC_HO_PAR_CHANGE                       = 2011,
//	HEADER_XX                                     = 2012,
	HEADER_ZC_SEEK_PARTY                          = 2013,
//	HEADER_XX                                     = 2014,
//	HEADER_XX                                     = 2015,
//	HEADER_XX                                     = 2016,
	HEADER_ZC_SKILLINFO_UPDATE2                   = 2017,
	HEADER_ZC_MSG_VALUE                           = 2018,
	HEADER_ZC_ITEMLISTWIN_OPEN                    = 2019,
//	HEADER_XX                                     = 2020,
//	HEADER_XX                                     = 2021,
	HEADER_ZC_MSG_SKILL                           = 2022,
//	HEADER_XX                                     = 2023,
//	HEADER_XX                                     = 2024,
//	HEADER_XX                                     = 2025,
//	HEADER_XX                                     = 2026,
//	HEADER_XX                                     = 2027,
//	HEADER_XX                                     = 2028,
//	HEADER_XX                                     = 2029,
//	HEADER_XX                                     = 2030,
//	HEADER_XX                                     = 2031,
//	HEADER_XX                                     = 2032,
//	HEADER_XX                                     = 2033,
//	HEADER_XX                                     = 2034,
//	HEADER_XX                                     = 2035,
//	HEADER_XX                                     = 2036,
//	HEADER_XX                                     = 2037,
	HEADER_ZC_NOTIFY_EXP                          = 2038,
	HEADER_ZC_NOTIFY_MOVEENTRY7                   = 2039,
	HEADER_ZC_NOTIFY_NEWENTRY5                    = 2040,
	HEADER_ZC_NOTIFY_STANDENTRY5                  = 2041,
	HEADER_ZC_DELETE_ITEM_FROM_BODY               = 2042,
	HEADER_ZC_USESKILL_ACK2                       = 2043,
	HEADER_ZC_CHANGE_GROUP_MASTER                 = 2044,
	HEADER_ZC_BROADCASTING_SPECIAL_ITEM_OBTAIN    = 2045,
	HEADER_ZC_PLAY_NPC_BGM                        = 2046,
	HEADER_ZC_DEFINE_CHECK                        = 2047,
	HEADER_ZC_PC_PURCHASE_ITEMLIST_FROMMC2        = 2048,
//	HEADER_XX                                     = 2049,
//	HEADER_XX                                     = 2050,
	HEADER_ZC_PARTY_BOOKING_ACK_REGISTER          = 2051,
//	HEADER_XX                                     = 2052,
	HEADER_ZC_PARTY_BOOKING_ACK_SEARCH            = 2053,
//	HEADER_XX                                     = 2054,
	HEADER_ZC_PARTY_BOOKING_ACK_DELETE            = 2055,
//	HEADER_XX                                     = 2056,
	HEADER_ZC_PARTY_BOOKING_NOTIFY_INSERT         = 2057,
	HEADER_ZC_PARTY_BOOKING_NOTIFY_UPDATE         = 2058,
	HEADER_ZC_PARTY_BOOKING_NOTIFY_DELETE         = 2059,
//	HEADER_XX                                     = 2060,
//	HEADER_XX                                     = 2061,
	HEADER_ZC_NOTIFY_HP_TO_GROUPM_R2              = 2062,
	HEADER_ZC_ADD_EXCHANGE_ITEM2                  = 2063,
	HEADER_ZC_OPEN_BUYING_STORE                   = 2064,
//	HEADER_XX                                     = 2065,
	HEADER_ZC_FAILED_OPEN_BUYING_STORE_TO_BUYER   = 2066,
	HEADER_ZC_MYITEMLIST_BUYING_STORE             = 2067,
	HEADER_ZC_BUYING_STORE_ENTRY                  = 2068,
//	HEADER_XX                                     = 2069,
	HEADER_ZC_DISAPPEAR_BUYING_STORE_ENTRY        = 2070,
//	HEADER_XX                                     = 2071,
	HEADER_ZC_ACK_ITEMLIST_BUYING_STORE           = 2072,
//	HEADER_XX                                     = 2073,
	HEADER_ZC_FAILED_TRADE_BUYING_STORE_TO_BUYER  = 2074,
	HEADER_ZC_UPDATE_ITEM_FROM_BUYING_STORE       = 2075,
	HEADER_ZC_ITEM_DELETE_BUYING_STORE            = 2076,
	HEADER_ZC_EL_INIT                             = 2077,
	HEADER_ZC_EL_PAR_CHANGE                       = 2078,
	HEADER_ZC_BROADCAST4                          = 2079,
//	HEADER_XX                                     = 2080,
//	HEADER_XX                                     = 2081,
//	HEADER_XX                                     = 2082,
//	HEADER_XX                                     = 2083,
	HEADER_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER = 2084,
//	HEADER_XX                                     = 2085,
//	HEADER_XX                                     = 2086,
//	HEADER_XX                                     = 2087,
//	HEADER_XX                                     = 2088,
//	HEADER_XX                                     = 2089,
//	HEADER_XX                                     = 2090,
//	HEADER_XX                                     = 2091,
//	HEADER_XX                                     = 2092,
//	HEADER_XX                                     = 2093,
//	HEADER_XX                                     = 2094,
//	HEADER_XX                                     = 2095,
//	HEADER_XX                                     = 2096,
//	HEADER_XX                                     = 2097,
//	HEADER_XX                                     = 2098,
//	HEADER_XX                                     = 2099,
//	HEADER_XX                                     = 2100,
//	HEADER_XX                                     = 2101,
//	HEADER_XX                                     = 2102,
//	HEADER_XX                                     = 2103,
//	HEADER_XX                                     = 2104,
//	HEADER_XX                                     = 2105,
//	HEADER_XX                                     = 2106,
//	HEADER_XX                                     = 2107,
//	HEADER_XX                                     = 2108,
//	HEADER_XX                                     = 2109,
	HEADER_AC_REFUSE_LOGIN_R2                     = 2110,
//	HEADER_XX                                     = 2111,
	HEADER_LAST
};


struct PACKET_CA_LOGIN
{// 0x0064 (100)
	//TODO
};


struct PACKET_CH_ENTER
{// 0x0065 (101)
	//TODO
};


struct PACKET_CH_SELECT_CHAR
{// 0x0066 (102)
	//TODO
};


struct PACKET_CH_MAKE_CHAR
{// 0x0067 (103)
	//TODO
};


struct PACKET_CH_DELETE_CHAR
{// 0x0068 (104)
	//TODO
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
	/* this+2 */ unsigned char ErrorCode;
	/* this+3 */ char blockDate[20];
};


struct PACKET_HC_ACCEPT_ENTER
{// 0x006B (107)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned char TotalSlotNum;
	/* this+ 5 */ unsigned char PremiumStartSlot;
	/* this+ 6 */ unsigned char PremiumEndSlot;
	/* this+ 7 */ BILLING_INFO m_extension;
	/* this+27 */ CHARACTER_INFO CharInfo[];
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
	//TODO
};


struct PACKET_ZC_NOTIFY_STANDENTRY
{// 0x0078 (120)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char objecttype;
	/* this+ 3 */ unsigned long GID;
	/* this+ 7 */ short speed;
	/* this+ 9 */ short bodyState;
	/* this+11 */ short healthState;
	/* this+13 */ short effectState;
	/* this+15 */ short job;
	/* this+17 */ short head;
	/* this+19 */ short weapon;
	/* this+21 */ short accessory;
	/* this+23 */ short shield;
	/* this+25 */ short accessory2;
	/* this+27 */ short accessory3;
	/* this+29 */ short headpalette;
	/* this+31 */ short bodypalette;
	/* this+33 */ short headDir;
	/* this+35 */ unsigned long GUID;
	/* this+39 */ short GEmblemVer;
	/* this+41 */ short honor;
	/* this+43 */ short virtue;
	/* this+45 */ bool isPKModeON;
	/* this+46 */ unsigned char sex;
	/* this+47 */ unsigned char PosDir[3];
	/* this+50 */ unsigned char xSize;
	/* this+51 */ unsigned char ySize;
	/* this+52 */ unsigned char state;
	/* this+53 */ short clevel;
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


struct PACKET_SC_NOTIFY_BAN
{// 0x0081 (129)
	//TODO
};


struct PACKET_ZC_ACCEPT_QUIT
{// 0x0083 (131)
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_REFUSE_QUIT
{// 0x0084 (132)
	/* this+0 */ short PacketType;
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
	/* this+26 */ unsigned char action; // enum ACTIONTYPE
	/* this+27 */ short leftDamage;
};


struct PACKET_CZ_REQNAME
{// 0x008C (140)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char Unknown[8];
	/* this+10 */ unsigned long AID;
};


struct PACKET_ZC_NPCACK_MAPMOVE
{// 0x0091 (145)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char mapName[16];
	/* this+18 */ short xPos;
	/* this+20 */ short yPos;
};


struct PACKET_ZC_BROADCAST
{// 0x009A (154)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
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


struct PACKET_ZC_EQUIPMENT_ITEMLIST
{// 0x00A4 (164)
	struct ITEM
	{
		/* this+ 0 */ short index;
		/* this+ 2 */ unsigned short ITID;
		/* this+ 4 */ unsigned char type;
		/* this+ 5 */ bool IsIdentified;
		/* this+ 6 */ short location;
		/* this+ 8 */ short wearLocation;
		/* this+10 */ unsigned char isDamaged;
		/* this+11 */ unsigned char refiningLevel;
		/* this+12 */ EQUIPSLOTINFO slot;
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ ITEM Item[];
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


struct PACKET_PING
{// 0x0187 (391)
	//TODO
};


struct PACKET_SC_BILLING_INFO
{// 0x01B5 (437)
	//TODO
};


struct PACKET_AC_ASK_PNGAMEROOM
{// 0x01BE (446)
	//TODO
};


struct PACKET_CA_REPLY_PNGAMEROOM
{// 0x01BF (447)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char Permission;
};


struct PACKET_ZC_BROADCAST2
{// 0x01C3 (451)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ COLORREF fontColor;
	/* this+ 8 */ short fontType;
	/* this+10 */ short fontSize;
	/* this+12 */ short fontAlign;
	/* this+14 */ short fontY;
	/* this+16 */ char Text[];
};


struct PACKET_SC_ACK_ENCRYPTION
{// 0x01C7 (455)
	//TODO
};


struct PACKET_CA_REQ_HASH
{// 0x01DB (475)
	/* this+ 0 */ short PacketType;
};


struct PACKET_AC_ACK_HASH
{// 0x01DC (476)
	/* this+ 0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ char RandStr[];
};


struct PACKET_CA_LOGIN2
{// 0x01DD (477)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char PasswdMD5[16];
	/* this+46 */ unsigned char clienttype;
};


struct PACKET_AC_NOTIFY_ERROR
{// 0x01F1 (497)
	//TODO
};


struct PACKET_CA_LOGIN3
{// 0x01FA (506)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char PasswdMD5[16];
	/* this+46 */ unsigned char clienttype;
	/* this+47 */ unsigned char ClientInfo;
};


struct PACKET_HC_BLOCK_CHARACTER
{// 0x020D (525)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ TAG_CHARACTER_BLOCK_INFO CharBlockInfo[];
};


struct PACKET_AC_EVENT_RESULT
{// 0x023D (573)
	//TODO
};


struct PACKET_CA_LOGIN4
{// 0x027C (636)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char PasswdMD5[16];
	/* this+46 */ unsigned char clienttype;
	/* this+47 */ char macData[12+1];
};


struct PACKET_ZC_AID
{// 0x283 (643)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_HC_CHARNOTBEENSELECTED
{// 0x028B (651)
	//TODO
};


struct PACKET_HC_ACK_IS_VALID_CHARNAME
{// 0x028E (654)
	//TODO
};


struct PACKET_HC_ACK_CHANGE_CHARNAME
{// 0x0290 (656)
	//TODO
};


struct PACKET_ZC_EQUIPMENT_ITEMLIST2
{// 0x0295 (661)
	struct ITEM
	{
		/* this+ 0 */ short index;
		/* this+ 2 */ unsigned short ITID;
		/* this+ 4 */ unsigned char type;
		/* this+ 5 */ bool IsIdentified;
		/* this+ 6 */ short location;
		/* this+ 8 */ short wearLocation;
		/* this+10 */ unsigned char isDamaged;
		/* this+11 */ unsigned char refiningLevel;
		/* this+12 */ EQUIPSLOTINFO slot;
		/* this+20 */ int HireExpireDate;
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ ITEM Item[];
};


struct PACKET_ZC_SRPACKETR2_INIT
{// 0x02BF (703)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short ProtectFactor;
	/* this+4 */ unsigned int DeformSeedFactor;
	/* this+8 */ unsigned int DeformAddFactor;
};


struct PACKET_CZ_SRPACKETR2_START
{// 0x02C0 (704)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short ProtectFactor;
};


struct PACKET_HC_REFUSE_SELECTCHAR
{// 0x02CA (714)
	//TODO
};


struct PACKET_ZC_EQUIPMENT_ITEMLIST3
{// 0x02D0 (720)
	struct ITEM
	{
		/* this+ 0 */ short index;
		/* this+ 2 */ unsigned short ITID;
		/* this+ 4 */ unsigned char type;
		/* this+ 5 */ bool IsIdentified;
		/* this+ 6 */ short location;
		/* this+ 8 */ short wearLocation;
		/* this+10 */ unsigned char isDamaged;
		/* this+11 */ unsigned char refiningLevel;
		/* this+12 */ EQUIPSLOTINFO slot;
		/* this+20 */ long HireExpireDate;
		/* this+24 */ short isBind;
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ ITEM Item[];
};


struct PACKET_ZC_NOTIFY_ACT2
{// 0x02E1 (737)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long targetGID;
	/* this+10 */ unsigned long startTime;
	/* this+14 */ int attackMT;
	/* this+18 */ int attackedMT;
	/* this+22 */ int damage;
	/* this+26 */ short count;
	/* this+28 */ unsigned char action; // enum ACTIONTYPE
	/* this+29 */ int leftDamage;
};


struct PACKET_ZC_ACCEPT_ENTER2
{// 0x02EB (747)
	//TODO
};


struct PACKET_ZC_NOTIFY_MOVEENTRY4
{// 0x02EC (748)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char objecttype;
	/* this+ 3 */ unsigned long GID;
	/* this+ 7 */ short speed;
	/* this+ 9 */ short bodyState;
	/* this+11 */ short healthState;
	/* this+13 */ int effectState;
	/* this+17 */ short job;
	/* this+19 */ short head;
	/* this+21 */ int weapon;
	/* this+25 */ short accessory;
	/* this+27 */ unsigned long moveStartTime;
	/* this+31 */ short accessory2;
	/* this+33 */ short accessory3;
	/* this+35 */ short headpalette;
	/* this+37 */ short bodypalette;
	/* this+39 */ short headDir;
	/* this+41 */ unsigned long GUID;
	/* this+45 */ short GEmblemVer;
	/* this+47 */ short honor;
	/* this+49 */ int virtue;
	/* this+53 */ bool isPKModeON;
	/* this+54 */ unsigned char sex;
	/* this+55 */ unsigned char MoveData[6];
	/* this+61 */ unsigned char xSize;
	/* this+62 */ unsigned char ySize;
	/* this+63 */ short clevel;
	/* this+65 */ short font;
};


struct PACKET_ZC_ITEM_FALL_ENTRY2
{// 0x02F3 (755) .. 0x02F9 (761)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long ITAID;
	/* this+ 8 */ unsigned short ITID;
	/* this+10 */ bool IsIdentified;
	/* this+11 */ short xPos;
	/* this+13 */ short yPos;
	/* this+15 */ unsigned char subX;
	/* this+16 */ unsigned char subY;
	/* this+17 */ short count;
	/* this+19 */ BYTE unknown[]; //TODO
};


struct PACKET_ZC_NOTIFY_MOVEENTRY5
{// 0x02FA (762) .. 0x0300 (768)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned char objecttype;
	/* this+ 5 */ unsigned long GID;
	/* this+ 9 */ short speed;
	/* this+11 */ short bodyState;
	/* this+13 */ short healthState;
	/* this+15 */ int effectState;
	/* this+19 */ short job;
	/* this+21 */ short head;
	/* this+23 */ int weapon;
	/* this+27 */ short accessory;
	/* this+29 */ unsigned long moveStartTime;
	/* this+33 */ short accessory2;
	/* this+35 */ short accessory3;
	/* this+37 */ short headpalette;
	/* this+39 */ short bodypalette;
	/* this+41 */ short headDir;
	/* this+43 */ unsigned long GUID;
	/* this+47 */ short GEmblemVer;
	/* this+49 */ short honor;
	/* this+51 */ int virtue;
	/* this+55 */ bool isPKModeON;
	/* this+56 */ unsigned char sex;
	/* this+57 */ unsigned char MoveData[6];
	/* this+63 */ unsigned char xSize;
	/* this+64 */ unsigned char ySize;
	/* this+65 */ short clevel;
	/* this+67 */ BYTE unknown[]; //TODO
};


struct PACKET_ZC_REASSEMBLY_CERTIFY
{// 0x0308 (776) .. 0x0331 (817)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ BYTE unknown[]; //TODO
};


struct PACKET_CZ_REASSEMBLY_IDENTITY
{// 0x0332 (818) .. 0x035B (859)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ struct
	             {
					/* this(bf)+0:0 len(1) */ unsigned char Winsock : 1;
					/* this(bf)+0:1 len(1) */ unsigned char GDI32 : 1;
					/* this(bf)+0:2 len(1) */ unsigned char Debugging : 1;
					/* this(bf)+0:3 len(1) */ unsigned char ClientCheckSumError : 1;
					/* this(bf)+0:4 len(4) */ unsigned char Unused : 4;
	             }
	             ImportAddressTableModify;
};


struct PACKET_ZC_NOTIFY_MOVEENTRY6
{//	0x035F (863) .. 0x0388 (904)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned char objecttype;
	/* this+ 5 */ unsigned long GID;
	/* this+ 9 */ short speed;
	/* this+11 */ short bodyState;
	/* this+13 */ short healthState;
	/* this+15 */ int effectState;
	/* this+19 */ short job;
	/* this+21 */ short head;
	/* this+23 */ int weapon;
	/* this+27 */ short accessory;
	/* this+29 */ unsigned long moveStartTime;
	/* this+33 */ short accessory2;
	/* this+35 */ short accessory3;
	/* this+37 */ short headpalette;
	/* this+39 */ short bodypalette;
	/* this+41 */ short headDir;
	/* this+43 */ unsigned long GUID;
	/* this+47 */ short GEmblemVer;
	/* this+49 */ short honor;
	/* this+51 */ int virtue;
	/* this+55 */ bool isPKModeON;
	/* this+56 */ unsigned char sex;
	/* this+57 */ unsigned char MoveData[6];
	/* this+63 */ unsigned char xSize;
	/* this+64 */ unsigned char ySize;
	/* this+65 */ short clevel;
	/* this+67 */ short font;
	/* this+69 */ BYTE unknown[]; //TODO
};


struct PACKET_ZC_ITEM_FALL_ENTRY3
{// 0x03B3 (947) .. 0x03DC (988)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long ITAID;
	/* this+ 8 */ unsigned short ITID;
	/* this+10 */ bool IsIdentified;
	/* this+11 */ short xPos;
	/* this+13 */ short yPos;
	/* this+15 */ unsigned char subX;
	/* this+16 */ unsigned char subY;
	/* this+17 */ short count;
	/* this+18 */ BYTE unknown[]; //TODO
};


struct PACKET_ZC_NOTIFY_ACT3
{// 0x03E2 (994) .. 0x040B (1035)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GID;
	/* this+ 8 */ unsigned long targetGID;
	/* this+12 */ unsigned long startTime;
	/* this+16 */ int attackMT;
	/* this+20 */ int attackedMT;
	/* this+24 */ int damage;
	/* this+28 */ short count;
	/* this+30 */ unsigned char action; // enum ACTIONTYPE
	/* this+31 */ int leftDamage;
	/* this+35 */ BYTE unknown[]; //TODO
};


struct PACKET_ZC_BROADCAST3
{// 0x040C (1036) .. 0x0435 (1077)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ COLORREF fontColor;
	/* this+ 8 */ short fontType;
	/* this+10 */ short fontSize;
	/* this+12 */ short fontAlign;
	/* this+14 */ short fontY;
	/* this+16 */ char Text[];
};


struct PACKET_ZC_SKILL_SELECT_REQUEST
{// 0x0442 (1090)
	BYTE todo[8]; //TODO
};


struct PACKET_HC_CHARACTER_LIST
{// 0x0448 (1096)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ CHARACTER_INFO CharInfo[];
};


struct PACKET_ZC_NOTIFY_MOVEENTRY7
{// 0x07F7 (2039)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned char objecttype;
	/* this+ 5 */ unsigned long GID;
	/* this+ 9 */ short speed;
	/* this+11 */ short bodyState;
	/* this+13 */ short healthState;
	/* this+15 */ int effectState;
	/* this+19 */ short job;
	/* this+21 */ short head;
	/* this+23 */ int weapon;
	/* this+27 */ short accessory;
	/* this+29 */ unsigned long moveStartTime;
	/* this+33 */ short accessory2;
	/* this+35 */ short accessory3;
	/* this+37 */ short headpalette;
	/* this+39 */ short bodypalette;
	/* this+41 */ short headDir;
	/* this+43 */ unsigned long GUID;
	/* this+47 */ short GEmblemVer;
	/* this+49 */ short honor;
	/* this+51 */ int virtue;
	/* this+55 */ bool isPKModeON;
	/* this+56 */ unsigned char sex;
	/* this+57 */ unsigned char MoveData[6];
	/* this+63 */ unsigned char xSize;
	/* this+64 */ unsigned char ySize;
	/* this+65 */ short clevel;
	/* this+67 */ short font;
	/* this+69 */ char CName[];
};


struct PACKET_ZC_NOTIFY_STANDENTRY5
{// 0x07F9 (2041)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned char objecttype;
	/* this+ 5 */ unsigned long GID;
	/* this+ 9 */ short speed;
	/* this+11 */ short bodyState;
	/* this+13 */ short healthState;
	/* this+15 */ int effectState;
	/* this+19 */ short job;
	/* this+21 */ short head;
	/* this+23 */ int weapon;
	/* this+27 */ short accessory;
	/* this+29 */ short accessory2;
	/* this+31 */ short accessory3;
	/* this+33 */ short headpalette;
	/* this+35 */ short bodypalette;
	/* this+37 */ short headDir;
	/* this+39 */ unsigned long GUID;
	/* this+43 */ short GEmblemVer;
	/* this+45 */ short honor;
	/* this+47 */ int virtue;
	/* this+51 */ bool isPKModeON;
	/* this+52 */ unsigned char sex;
	/* this+53 */ unsigned char PosDir[3];
	/* this+56 */ unsigned char xSize;
	/* this+57 */ unsigned char ySize;
	/* this+58 */ unsigned char state;
	/* this+59 */ short clevel;
	/* this+61 */ short font;
	/* this+63 */ char name[];
};


struct PACKET_ZC_USESKILL_ACK2
{// 0x07FB (2043)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long targetID;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned short SKID;
	/* this+16 */ unsigned long property;
	/* this+20 */ unsigned long delayTime;
	/* this+24 */ bool isDisposable;
};


struct PACKET_ZC_DEFINE_CHECK
{// 0x07FF (2047)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned int Data;
	
	enum
	{
		DEFINE__BROADCASTING_SPECIAL_ITEM_OBTAIN = 1,
		DEFINE__RENEWAL_ADD_2 = 2,
		DEFINE__CHANNELING_SERVICE = 4,
	};

	//static unsigned int FIRST();

	static mystd::pair<int,mystd::string> CHECK_FIRST(const unsigned int in_data)
	{
		if( !(in_data & DEFINE__BROADCASTING_SPECIAL_ITEM_OBTAIN) )
			return mystd::pair<int,mystd::string>(1, "__BROADCASTING_SPECIAL_ITEM_OBTAIN");

		if( !(in_data & DEFINE__RENEWAL_ADD_2) )
			return mystd::pair<int,mystd::string>(2, "RENEWAL_ADD_2");

		return mystd::pair<int,mystd::string>(0, "ok");
	}
};


struct PACKET_AC_REFUSE_LOGIN_R2
{// 0x083E (2110)
	/* this+0 */ short PacketType;
	/* this+2 */ int ErrorCode;
	/* this+6 */ char blockDate[20];
};


#pragma pack(pop)
