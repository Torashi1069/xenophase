#pragma once
#include "struct.hpp"
#pragma pack(push,1)


bool __cdecl IsFixedPacket(int packetType);
int __cdecl GetPacketSize(int packetType);
void __cdecl InitPacketLen();
void __cdecl InitPacketLenWithClient();
void __cdecl EncodePosDir(int srcx, int srcy, int srcdir, BYTE* result); // line 9615-9619
void __cdecl DecodePosDir(unsigned char* packet, int& x, int& y, int& dir);
void __cdecl EncodeSrcDst(int srcx, int srcy, int dstx, int dsty, int xcellpos, int ycellpos, BYTE* result); // line 9631-9638
void __cdecl DecodeSrcDst(unsigned char* packet, int& rsx, int& rsy, int& rdx, int& rdy, int& xcellpos, int& ycellpos);


enum ePacketType
{
	HEADER_CA_LOGIN                               = 100,
	HEADER_CH_ENTER                               = 101,
	HEADER_CH_SELECT_CHAR                         = 102,
	HEADER_CH_MAKE_CHAR                           = 103,
	HEADER_CH_DELETE_CHAR                         = 104,
	HEADER_AC_ACCEPT_LOGIN                        = 105,
	HEADER_AC_REFUSE_LOGIN                        = 106,
	HEADER_HC_ACCEPT_ENTER                        = 107,
	HEADER_HC_REFUSE_ENTER                        = 108,
	HEADER_HC_ACCEPT_MAKECHAR                     = 109,
	HEADER_HC_REFUSE_MAKECHAR                     = 110,
	HEADER_HC_ACCEPT_DELETECHAR                   = 111,
	HEADER_HC_REFUSE_DELETECHAR                   = 112,
	HEADER_HC_NOTIFY_ZONESVR                      = 113,
	HEADER_CZ_ENTER                               = 114,
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
	HEADER_CZ_NOTIFY_ACTORINIT                    = 125,
	HEADER_CZ_REQUEST_TIME                        = 126,
	HEADER_ZC_NOTIFY_TIME                         = 127,
	HEADER_ZC_NOTIFY_VANISH                       = 128,
	HEADER_SC_NOTIFY_BAN                          = 129,
	HEADER_CZ_REQUEST_QUIT                        = 130,
	HEADER_ZC_ACCEPT_QUIT                         = 131,
	HEADER_ZC_REFUSE_QUIT                         = 132,
	HEADER_CZ_REQUEST_MOVE                        = 133,
	HEADER_ZC_NOTIFY_MOVE                         = 134,
	HEADER_ZC_NOTIFY_PLAYERMOVE                   = 135,
	HEADER_ZC_STOPMOVE                            = 136,
	HEADER_CZ_REQUEST_ACT                         = 137,
	HEADER_ZC_NOTIFY_ACT                          = 138,
	HEADER_ZC_NOTIFY_ACT_POSITION                 = 139,
	HEADER_CZ_REQUEST_CHAT                        = 140,
	HEADER_ZC_NOTIFY_CHAT                         = 141,
	HEADER_ZC_NOTIFY_PLAYERCHAT                   = 142,
	HEADER_SERVER_ENTRY_ACK                       = 143,
	HEADER_CZ_CONTACTNPC                          = 144,
	HEADER_ZC_NPCACK_MAPMOVE                      = 145,
	HEADER_ZC_NPCACK_SERVERMOVE                   = 146,
	HEADER_ZC_NPCACK_ENABLE                       = 147,
	HEADER_CZ_REQNAME                             = 148,
	HEADER_ZC_ACK_REQNAME                         = 149,
	HEADER_CZ_WHISPER                             = 150,
	HEADER_ZC_WHISPER                             = 151,
	HEADER_ZC_ACK_WHISPER                         = 152,
	HEADER_CZ_BROADCAST                           = 153,
	HEADER_ZC_BROADCAST                           = 154,
	HEADER_CZ_CHANGE_DIRECTION                    = 155,
	HEADER_ZC_CHANGE_DIRECTION                    = 156,
	HEADER_ZC_ITEM_ENTRY                          = 157,
	HEADER_ZC_ITEM_FALL_ENTRY                     = 158,
	HEADER_CZ_ITEM_PICKUP                         = 159,
	HEADER_ZC_ITEM_PICKUP_ACK                     = 160,
	HEADER_ZC_ITEM_DISAPPEAR                      = 161,
	HEADER_CZ_ITEM_THROW                          = 162,
	HEADER_ZC_NORMAL_ITEMLIST                     = 163,
	HEADER_ZC_EQUIPMENT_ITEMLIST                  = 164,
	HEADER_ZC_STORE_NORMAL_ITEMLIST               = 165,
	HEADER_ZC_STORE_EQUIPMENT_ITEMLIST            = 166,
	HEADER_CZ_USE_ITEM                            = 167,
	HEADER_ZC_USE_ITEM_ACK                        = 168,
	HEADER_CZ_REQ_WEAR_EQUIP                      = 169,
	HEADER_ZC_REQ_WEAR_EQUIP_ACK                  = 170,
	HEADER_CZ_REQ_TAKEOFF_EQUIP                   = 171,
	HEADER_ZC_REQ_TAKEOFF_EQUIP_ACK               = 172,
	HEADER_CZ_REQ_ITEM_EXPLANATION_BYNAME         = 173,
	HEADER_ZC_REQ_ITEM_EXPLANATION_ACK            = 174,
	HEADER_ZC_ITEM_THROW_ACK                      = 175,
	HEADER_ZC_PAR_CHANGE                          = 176,
	HEADER_ZC_LONGPAR_CHANGE                      = 177,
	HEADER_CZ_RESTART                             = 178,
	HEADER_ZC_RESTART_ACK                         = 179,
	HEADER_ZC_SAY_DIALOG                          = 180,
	HEADER_ZC_WAIT_DIALOG                         = 181,
	HEADER_ZC_CLOSE_DIALOG                        = 182,
	HEADER_ZC_MENU_LIST                           = 183,
	HEADER_CZ_CHOOSE_MENU                         = 184,
	HEADER_CZ_REQ_NEXT_SCRIPT                     = 185,
	HEADER_CZ_REQ_STATUS                          = 186,
	HEADER_CZ_STATUS_CHANGE                       = 187,
	HEADER_ZC_STATUS_CHANGE_ACK                   = 188,
	HEADER_ZC_STATUS                              = 189,
	HEADER_ZC_STATUS_CHANGE                       = 190,
	HEADER_CZ_REQ_EMOTION                         = 191,
	HEADER_ZC_EMOTION                             = 192,
	HEADER_CZ_REQ_USER_COUNT                      = 193,
	HEADER_ZC_USER_COUNT                          = 194,
	HEADER_ZC_SPRITE_CHANGE                       = 195,
	HEADER_ZC_SELECT_DEALTYPE                     = 196,
	HEADER_CZ_ACK_SELECT_DEALTYPE                 = 197,
	HEADER_ZC_PC_PURCHASE_ITEMLIST                = 198,
	HEADER_ZC_PC_SELL_ITEMLIST                    = 199,
	HEADER_CZ_PC_PURCHASE_ITEMLIST                = 200,
	HEADER_CZ_PC_SELL_ITEMLIST                    = 201,
	HEADER_ZC_PC_PURCHASE_RESULT                  = 202,
	HEADER_ZC_PC_SELL_RESULT                      = 203,
	HEADER_CZ_DISCONNECT_CHARACTER                = 204,
	HEADER_ZC_ACK_DISCONNECT_CHARACTER            = 205,
	HEADER_CZ_DISCONNECT_ALL_CHARACTER            = 206,
	HEADER_CZ_SETTING_WHISPER_PC                  = 207,
	HEADER_CZ_SETTING_WHISPER_STATE               = 208,
	HEADER_ZC_SETTING_WHISPER_PC                  = 209,
	HEADER_ZC_SETTING_WHISPER_STATE               = 210,
	HEADER_CZ_REQ_WHISPER_LIST                    = 211,
	HEADER_ZC_WHISPER_LIST                        = 212,
	HEADER_CZ_CREATE_CHATROOM                     = 213,
	HEADER_ZC_ACK_CREATE_CHATROOM                 = 214,
	HEADER_ZC_ROOM_NEWENTRY                       = 215,
	HEADER_ZC_DESTROY_ROOM                        = 216,
	HEADER_CZ_REQ_ENTER_ROOM                      = 217,
	HEADER_ZC_REFUSE_ENTER_ROOM                   = 218,
	HEADER_ZC_ENTER_ROOM                          = 219,
	HEADER_ZC_MEMBER_NEWENTRY                     = 220,
	HEADER_ZC_MEMBER_EXIT                         = 221,
	HEADER_CZ_CHANGE_CHATROOM                     = 222,
	HEADER_ZC_CHANGE_CHATROOM                     = 223,
	HEADER_CZ_REQ_ROLE_CHANGE                     = 224,
	HEADER_ZC_ROLE_CHANGE                         = 225,
	HEADER_CZ_REQ_EXPEL_MEMBER                    = 226,
	HEADER_CZ_EXIT_ROOM                           = 227,
	HEADER_CZ_REQ_EXCHANGE_ITEM                   = 228,
	HEADER_ZC_REQ_EXCHANGE_ITEM                   = 229,
	HEADER_CZ_ACK_EXCHANGE_ITEM                   = 230,
	HEADER_ZC_ACK_EXCHANGE_ITEM                   = 231,
	HEADER_CZ_ADD_EXCHANGE_ITEM                   = 232,
	HEADER_ZC_ADD_EXCHANGE_ITEM                   = 233,
	HEADER_ZC_ACK_ADD_EXCHANGE_ITEM               = 234,
	HEADER_CZ_CONCLUDE_EXCHANGE_ITEM              = 235,
	HEADER_ZC_CONCLUDE_EXCHANGE_ITEM              = 236,
	HEADER_CZ_CANCEL_EXCHANGE_ITEM                = 237,
	HEADER_ZC_CANCEL_EXCHANGE_ITEM                = 238,
	HEADER_CZ_EXEC_EXCHANGE_ITEM                  = 239,
	HEADER_ZC_EXEC_EXCHANGE_ITEM                  = 240,
	HEADER_ZC_EXCHANGEITEM_UNDO                   = 241,
	HEADER_ZC_NOTIFY_STOREITEM_COUNTINFO          = 242,
	HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_STORE        = 243,
	HEADER_ZC_ADD_ITEM_TO_STORE                   = 244,
	HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_BODY        = 245,
	HEADER_ZC_DELETE_ITEM_FROM_STORE              = 246,
	HEADER_CZ_CLOSE_STORE                         = 247,
	HEADER_ZC_CLOSE_STORE                         = 248,
	HEADER_CZ_MAKE_GROUP                          = 249,
	HEADER_ZC_ACK_MAKE_GROUP                      = 250,
	HEADER_ZC_GROUP_LIST                          = 251,
	HEADER_CZ_REQ_JOIN_GROUP                      = 252,
	HEADER_ZC_ACK_REQ_JOIN_GROUP                  = 253,
	HEADER_ZC_REQ_JOIN_GROUP                      = 254,
	HEADER_CZ_JOIN_GROUP                          = 255,
	HEADER_CZ_REQ_LEAVE_GROUP                     = 256,
	HEADER_ZC_GROUPINFO_CHANGE                    = 257,
	HEADER_CZ_CHANGE_GROUPEXPOPTION               = 258,
	HEADER_CZ_REQ_EXPEL_GROUP_MEMBER              = 259,
	HEADER_ZC_ADD_MEMBER_TO_GROUP                 = 260,
	HEADER_ZC_DELETE_MEMBER_FROM_GROUP            = 261,
	HEADER_ZC_NOTIFY_HP_TO_GROUPM                 = 262,
	HEADER_ZC_NOTIFY_POSITION_TO_GROUPM           = 263,
	HEADER_CZ_REQUEST_CHAT_PARTY                  = 264,
	HEADER_ZC_NOTIFY_CHAT_PARTY                   = 265,
	HEADER_ZC_MVP_GETTING_ITEM                    = 266,
	HEADER_ZC_MVP_GETTING_SPECIAL_EXP             = 267,
	HEADER_ZC_MVP                                 = 268,
	HEADER_ZC_THROW_MVPITEM                       = 269,
	HEADER_ZC_SKILLINFO_UPDATE                    = 270,
	HEADER_ZC_SKILLINFO_LIST                      = 271,
	HEADER_ZC_ACK_TOUSESKILL                      = 272,
	HEADER_ZC_ADD_SKILL                           = 273,
	HEADER_CZ_UPGRADE_SKILLLEVEL                  = 274,
	HEADER_CZ_USE_SKILL                           = 275,
	HEADER_ZC_NOTIFY_SKILL                        = 276,
	HEADER_ZC_NOTIFY_SKILL_POSITION               = 277,
	HEADER_CZ_USE_SKILL_TOGROUND                  = 278,
	HEADER_ZC_NOTIFY_GROUNDSKILL                  = 279,
	HEADER_CZ_CANCEL_LOCKON                       = 280,
	HEADER_ZC_STATE_CHANGE                        = 281,
	HEADER_ZC_USE_SKILL                           = 282,
	HEADER_CZ_SELECT_WARPPOINT                    = 283,
	HEADER_ZC_WARPLIST                            = 284,
	HEADER_CZ_REMEMBER_WARPPOINT                  = 285,
	HEADER_ZC_ACK_REMEMBER_WARPPOINT              = 286,
	HEADER_ZC_SKILL_ENTRY                         = 287,
	HEADER_ZC_SKILL_DISAPPEAR                     = 288,
	HEADER_ZC_NOTIFY_CARTITEM_COUNTINFO           = 289,
	HEADER_ZC_CART_EQUIPMENT_ITEMLIST             = 290,
	HEADER_ZC_CART_NORMAL_ITEMLIST                = 291,
	HEADER_ZC_ADD_ITEM_TO_CART                    = 292,
	HEADER_ZC_DELETE_ITEM_FROM_CART               = 293,
	HEADER_CZ_MOVE_ITEM_FROM_BODY_TO_CART         = 294,
	HEADER_CZ_MOVE_ITEM_FROM_CART_TO_BODY         = 295,
	HEADER_CZ_MOVE_ITEM_FROM_STORE_TO_CART        = 296,
	HEADER_CZ_MOVE_ITEM_FROM_CART_TO_STORE        = 297,
	HEADER_CZ_REQ_CARTOFF                         = 298,
	HEADER_ZC_CARTOFF                             = 299,
	HEADER_ZC_ACK_ADDITEM_TO_CART                 = 300,
	HEADER_ZC_OPENSTORE                           = 301,
	HEADER_CZ_REQ_CLOSESTORE                      = 302,
	HEADER_CZ_REQ_OPENSTORE                       = 303,
	HEADER_CZ_REQ_BUY_FROMMC                      = 304,
	HEADER_ZC_STORE_ENTRY                         = 305,
	HEADER_ZC_DISAPPEAR_ENTRY                     = 306,
	HEADER_ZC_PC_PURCHASE_ITEMLIST_FROMMC         = 307,
	HEADER_CZ_PC_PURCHASE_ITEMLIST_FROMMC         = 308,
	HEADER_ZC_PC_PURCHASE_RESULT_FROMMC           = 309,
	HEADER_ZC_PC_PURCHASE_MYITEMLIST              = 310,
	HEADER_ZC_DELETEITEM_FROM_MCSTORE             = 311,
	HEADER_CZ_PKMODE_CHANGE                       = 312,
	HEADER_ZC_ATTACK_FAILURE_FOR_DISTANCE         = 313,
	HEADER_ZC_ATTACK_RANGE                        = 314,
	HEADER_ZC_ACTION_FAILURE                      = 315,
	HEADER_ZC_EQUIP_ARROW                         = 316,
	HEADER_ZC_RECOVERY                            = 317,
	HEADER_ZC_USESKILL_ACK                        = 318,
	HEADER_CZ_ITEM_CREATE                         = 319,
	HEADER_CZ_MOVETO_MAP                          = 320,
	HEADER_ZC_COUPLESTATUS                        = 321,
	HEADER_ZC_OPEN_EDITDLG                        = 322,
	HEADER_CZ_INPUT_EDITDLG                       = 323,
	HEADER_ZC_COMPASS                             = 324,
	HEADER_ZC_SHOW_IMAGE                          = 325,
	HEADER_CZ_CLOSE_DIALOG                        = 326,
	HEADER_ZC_AUTORUN_SKILL                       = 327,
	HEADER_ZC_RESURRECTION                        = 328,
	HEADER_CZ_REQ_GIVE_MANNER_POINT               = 329,
	HEADER_ZC_ACK_GIVE_MANNER_POINT               = 330,
	HEADER_ZC_NOTIFY_MANNER_POINT_GIVEN           = 331,
	HEADER_ZC_MYGUILD_BASIC_INFO                  = 332,
	HEADER_CZ_REQ_GUILD_MENUINTERFACE             = 333,
	HEADER_ZC_ACK_GUILD_MENUINTERFACE             = 334,
	HEADER_CZ_REQ_GUILD_MENU                      = 335,
	HEADER_ZC_GUILD_INFO                          = 336,
	HEADER_CZ_REQ_GUILD_EMBLEM_IMG                = 337,
	HEADER_ZC_GUILD_EMBLEM_IMG                    = 338,
	HEADER_CZ_REGISTER_GUILD_EMBLEM_IMG           = 339,
	HEADER_ZC_MEMBERMGR_INFO                      = 340,
	HEADER_CZ_REQ_CHANGE_MEMBERPOS                = 341,
	HEADER_ZC_ACK_REQ_CHANGE_MEMBERS              = 342,
	HEADER_CZ_REQ_OPEN_MEMBER_INFO                = 343,
	HEADER_ZC_ACK_OPEN_MEMBER_INFO                = 344,
	HEADER_CZ_REQ_LEAVE_GUILD                     = 345,
	HEADER_ZC_ACK_LEAVE_GUILD                     = 346,
	HEADER_CZ_REQ_BAN_GUILD                       = 347,
	HEADER_ZC_ACK_BAN_GUILD                       = 348,
	HEADER_CZ_REQ_DISORGANIZE_GUILD               = 349,
	HEADER_ZC_ACK_DISORGANIZE_GUILD_RESULT        = 350,
	HEADER_ZC_ACK_DISORGANIZE_GUILD               = 351,
	HEADER_ZC_POSITION_INFO                       = 352,
	HEADER_CZ_REG_CHANGE_GUILD_POSITIONINFO       = 353,
	HEADER_ZC_GUILD_SKILLINFO                     = 354,
	HEADER_ZC_BAN_LIST                            = 355,
	HEADER_ZC_OTHER_GUILD_LIST                    = 356,
	HEADER_CZ_REQ_MAKE_GUILD                      = 357,
	HEADER_ZC_POSITION_ID_NAME_INFO               = 358,
	HEADER_ZC_RESULT_MAKE_GUILD                   = 359,
	HEADER_CZ_REQ_JOIN_GUILD                      = 360,
	HEADER_ZC_ACK_REQ_JOIN_GUILD                  = 361,
	HEADER_ZC_REQ_JOIN_GUILD                      = 362,
	HEADER_CZ_JOIN_GUILD                          = 363,
	HEADER_ZC_UPDATE_GDID                         = 364,
	HEADER_ZC_UPDATE_CHARSTAT                     = 365,
	HEADER_CZ_GUILD_NOTICE                        = 366,
	HEADER_ZC_GUILD_NOTICE                        = 367,
	HEADER_CZ_REQ_ALLY_GUILD                      = 368,
	HEADER_ZC_REQ_ALLY_GUILD                      = 369,
	HEADER_CZ_ALLY_GUILD                          = 370,
	HEADER_ZC_ACK_REQ_ALLY_GUILD                  = 371,
	HEADER_ZC_ACK_CHANGE_GUILD_POSITIONINFO       = 372,
	HEADER_CZ_REQ_GUILD_MEMBER_INFO               = 373,
	HEADER_ZC_ACK_GUILD_MEMBER_INFO               = 374,
	HEADER_ZC_ITEMIDENTIFY_LIST                   = 375,
	HEADER_CZ_REQ_ITEMIDENTIFY                    = 376,
	HEADER_ZC_ACK_ITEMIDENTIFY                    = 377,
	HEADER_CZ_REQ_ITEMCOMPOSITION_LIST            = 378,
	HEADER_ZC_ITEMCOMPOSITION_LIST                = 379,
	HEADER_CZ_REQ_ITEMCOMPOSITION                 = 380,
	HEADER_ZC_ACK_ITEMCOMPOSITION                 = 381,
	HEADER_CZ_GUILD_CHAT                          = 382,
	HEADER_ZC_GUILD_CHAT                          = 383,
	HEADER_CZ_REQ_HOSTILE_GUILD                   = 384,
	HEADER_ZC_ACK_REQ_HOSTILE_GUILD               = 385,
	HEADER_ZC_MEMBER_ADD                          = 386,
	HEADER_CZ_REQ_DELETE_RELATED_GUILD            = 387,
	HEADER_ZC_DELETE_RELATED_GUILD                = 388,
	HEADER_ZC_ADD_RELATED_GUILD                   = 389,
	HEADER_COLLECTORDEAD                          = 390,
	HEADER_PING                                   = 391,
	HEADER_ZC_ACK_ITEMREFINING                    = 392,
	HEADER_ZC_NOTIFY_MAPINFO                      = 393,
	HEADER_CZ_REQ_DISCONNECT                      = 394,
	HEADER_ZC_ACK_REQ_DISCONNECT                  = 395,
	HEADER_ZC_MONSTER_INFO                        = 396,
	HEADER_ZC_MAKABLEITEMLIST                     = 397,
	HEADER_CZ_REQMAKINGITEM                       = 398,
	HEADER_ZC_ACK_REQMAKINGITEM                   = 399,
	HEADER_CZ_USE_SKILL_TOGROUND_WITHTALKBOX      = 400,
	HEADER_ZC_TALKBOX_CHATCONTENTS                = 401,
	HEADER_ZC_UPDATE_MAPINFO                      = 402,
	HEADER_CZ_REQNAME_BYGID                       = 403,
	HEADER_ZC_ACK_REQNAME_BYGID                   = 404,
	HEADER_ZC_ACK_REQNAMEALL                      = 405,
	HEADER_ZC_MSG_STATE_CHANGE                    = 406,
	HEADER_CZ_RESET                               = 407,
	HEADER_CZ_CHANGE_MAPTYPE                      = 408,
	HEADER_ZC_NOTIFY_MAPPROPERTY                  = 409,
	HEADER_ZC_NOTIFY_RANKING                      = 410,
	HEADER_ZC_NOTIFY_EFFECT                       = 411,
	HEADER_CZ_LOCALBROADCAST                      = 412,
	HEADER_CZ_CHANGE_EFFECTSTATE                  = 413,
	HEADER_ZC_START_CAPTURE                       = 414,
	HEADER_CZ_TRYCAPTURE_MONSTER                  = 415,
	HEADER_ZC_TRYCAPTURE_MONSTER                  = 416,
	HEADER_CZ_COMMAND_PET                         = 417,
	HEADER_ZC_PROPERTY_PET                        = 418,
	HEADER_ZC_FEED_PET                            = 419,
	HEADER_ZC_CHANGESTATE_PET                     = 420,
	HEADER_CZ_RENAME_PET                          = 421,
	HEADER_ZC_PETEGG_LIST                         = 422,
	HEADER_CZ_SELECT_PETEGG                       = 423,
	HEADER_CZ_PETEGG_INFO                         = 424,
	HEADER_CZ_PET_ACT                             = 425,
	HEADER_ZC_PET_ACT                             = 426,
	HEADER_ZC_PAR_CHANGE_USER                     = 427,
	HEADER_ZC_SKILL_UPDATE                        = 428,
	HEADER_ZC_MAKINGARROW_LIST                    = 429,
	HEADER_CZ_REQ_MAKINGARROW                     = 430,
	HEADER_CZ_REQ_CHANGECART                      = 431,
	HEADER_ZC_NPCSPRITE_CHANGE                    = 432,
	HEADER_ZC_SHOWDIGIT                           = 433,
	HEADER_CZ_REQ_OPENSTORE2                      = 434,
	HEADER_ZC_SHOW_IMAGE2                         = 435,
	HEADER_ZC_CHANGE_GUILD                        = 436,
	HEADER_SC_BILLING_INFO                        = 437,
	HEADER_ZC_GUILD_INFO2                         = 438,
	HEADER_CZ_GUILD_ZENY                          = 439,
	HEADER_ZC_GUILD_ZENY_ACK                      = 440,
	HEADER_ZC_DISPEL                              = 441,
	HEADER_CZ_REMOVE_AID                          = 442,
	HEADER_CZ_SHIFT                               = 443,
	HEADER_CZ_RECALL                              = 444,
	HEADER_CZ_RECALL_GID                          = 445,
	HEADER_AC_ASK_PNGAMEROOM                      = 446,
	HEADER_CA_REPLY_PNGAMEROOM                    = 447,
	HEADER_CZ_REQ_REMAINTIME                      = 448,
	HEADER_ZC_REPLY_REMAINTIME                    = 449,
	HEADER_ZC_INFO_REMAINTIME                     = 450,
	HEADER_ZC_BROADCAST2                          = 451,
	HEADER_ZC_ADD_ITEM_TO_STORE2                  = 452,
	HEADER_ZC_ADD_ITEM_TO_CART2                   = 453,
	HEADER_CS_REQ_ENCRYPTION                      = 454,
	HEADER_SC_ACK_ENCRYPTION                      = 455,
	HEADER_ZC_USE_ITEM_ACK2                       = 456,
	HEADER_ZC_SKILL_ENTRY2                        = 457,
	HEADER_CZ_REQMAKINGHOMUN                      = 458,
	HEADER_CZ_MONSTER_TALK                        = 459,
	HEADER_ZC_MONSTER_TALK                        = 460,
	HEADER_ZC_AUTOSPELLLIST                       = 461,
	HEADER_CZ_SELECTAUTOSPELL                     = 462,
	HEADER_ZC_DEVOTIONLIST                        = 463,
	HEADER_ZC_SPIRITS                             = 464,
	HEADER_ZC_BLADESTOP                           = 465,
	HEADER_ZC_COMBODELAY                          = 466,
	HEADER_ZC_SOUND                               = 467,
	HEADER_ZC_OPEN_EDITDLGSTR                     = 468,
	HEADER_CZ_INPUT_EDITDLGSTR                    = 469,
	HEADER_ZC_NOTIFY_MAPPROPERTY2                 = 470,
	HEADER_ZC_SPRITE_CHANGE2                      = 471,
	HEADER_ZC_NOTIFY_STANDENTRY2                  = 472,
	HEADER_ZC_NOTIFY_NEWENTRY2                    = 473,
	HEADER_ZC_NOTIFY_MOVEENTRY2                   = 474,
	HEADER_CA_REQ_HASH                            = 475,
	HEADER_AC_ACK_HASH                            = 476,
	HEADER_CA_LOGIN2                              = 477,
	HEADER_ZC_NOTIFY_SKILL2                       = 478,
	HEADER_CZ_REQ_ACCOUNTNAME                     = 479,
	HEADER_ZC_ACK_ACCOUNTNAME                     = 480,
	HEADER_ZC_SPIRITS2                            = 481,
	HEADER_ZC_REQ_COUPLE                          = 482,
	HEADER_CZ_JOIN_COUPLE                         = 483,
	HEADER_ZC_START_COUPLE                        = 484,
	HEADER_CZ_REQ_JOIN_COUPLE                     = 485,
	HEADER_ZC_COUPLENAME                          = 486,
	HEADER_CZ_DORIDORI                            = 487,
	HEADER_CZ_MAKE_GROUP2                         = 488,
	HEADER_ZC_ADD_MEMBER_TO_GROUP2                = 489,
	HEADER_ZC_CONGRATULATION                      = 490,
	HEADER_ZC_NOTIFY_POSITION_TO_GUILDM           = 491,
	HEADER_ZC_GUILD_MEMBER_MAP_CHANGE             = 492,
	HEADER_CZ_CHOPOKGI                            = 493,
	HEADER_ZC_NORMAL_ITEMLIST2                    = 494,
	HEADER_ZC_CART_NORMAL_ITEMLIST2               = 495,
	HEADER_ZC_STORE_NORMAL_ITEMLIST2              = 496,
	HEADER_AC_NOTIFY_ERROR                        = 497,
	HEADER_ZC_UPDATE_CHARSTAT2                    = 498,
	HEADER_ZC_NOTIFY_EFFECT2                      = 499,
	HEADER_ZC_REQ_EXCHANGE_ITEM2                  = 500,
	HEADER_ZC_ACK_EXCHANGE_ITEM2                  = 501,
	HEADER_ZC_REQ_BABY                            = 502,
	HEADER_CZ_JOIN_BABY                           = 503,
	HEADER_ZC_START_BABY                          = 504,
	HEADER_CZ_REQ_JOIN_BABY                       = 505,
	HEADER_CA_LOGIN3                              = 506,
	HEADER_CH_DELETE_CHAR2                        = 507,
	HEADER_ZC_REPAIRITEMLIST                      = 508,
	HEADER_CZ_REQ_ITEMREPAIR                      = 509,
	HEADER_ZC_ACK_ITEMREPAIR                      = 510,
	HEADER_ZC_HIGHJUMP                            = 511,
	HEADER_CA_CONNECT_INFO_CHANGED                = 512,
	HEADER_ZC_FRIENDS_LIST                        = 513,
	HEADER_CZ_ADD_FRIENDS                         = 514,
	HEADER_CZ_DELETE_FRIENDS                      = 515,
	HEADER_CA_EXE_HASHCHECK                       = 516,
	HEADER_ZC_DIVORCE                             = 517,
	HEADER_ZC_FRIENDS_STATE                       = 518,
	HEADER_ZC_REQ_ADD_FRIENDS                     = 519,
	HEADER_CZ_ACK_REQ_ADD_FRIENDS                 = 520,
	HEADER_ZC_ADD_FRIENDS_LIST                    = 521,
	HEADER_ZC_DELETE_FRIENDS                      = 522,
	HEADER_CH_EXE_HASHCHECK                       = 523,
	HEADER_CZ_EXE_HASHCHECK                       = 524,
	HEADER_HC_BLOCK_CHARACTER                     = 525,
	HEADER_ZC_STARSKILL                           = 526,
	HEADER_CZ_REQ_PVPPOINT                        = 527,
	HEADER_ZC_ACK_PVPPOINT                        = 528,
//	HEADER_ZH_MOVE_PVPWORLD                       = 529,
	HEADER_CZ_REQ_GIVE_MANNER_BYNAME              = 530,
	HEADER_CZ_REQ_STATUS_GM                       = 531,
	HEADER_ZC_ACK_STATUS_GM                       = 532,
	HEADER_ZC_SKILLMSG                            = 533,
	HEADER_ZC_BABYMSG                             = 534,
	HEADER_CZ_BLACKSMITH_RANK                     = 535,
	HEADER_CZ_ALCHEMIST_RANK                      = 536,
	HEADER_ZC_BLACKSMITH_RANK                     = 537,
	HEADER_ZC_ALCHEMIST_RANK                      = 538,
	HEADER_ZC_BLACKSMITH_POINT                    = 539,
	HEADER_ZC_ALCHEMIST_POINT                     = 540,
	HEADER_CZ_LESSEFFECT                          = 541,
	HEADER_ZC_LESSEFFECT                          = 542,
	HEADER_ZC_NOTIFY_PKINFO                       = 543,
	HEADER_ZC_NOTIFY_CRAZYKILLER                  = 544,
	HEADER_ZC_NOTIFY_WEAPONITEMLIST               = 545,
	HEADER_CZ_REQ_WEAPONREFINE                    = 546,
	HEADER_ZC_ACK_WEAPONREFINE                    = 547,
	HEADER_ZC_TAEKWON_POINT                       = 548,
	HEADER_CZ_TAEKWON_RANK                        = 549,
	HEADER_ZC_TAEKWON_RANK                        = 550,
	HEADER_ZC_GAME_GUARD                          = 551,
	HEADER_CZ_ACK_GAME_GUARD                      = 552,
	HEADER_ZC_STATE_CHANGE3                       = 553,
	HEADER_ZC_NOTIFY_STANDENTRY3                  = 554,
	HEADER_ZC_NOTIFY_NEWENTRY3                    = 555,
	HEADER_ZC_NOTIFY_MOVEENTRY3                   = 556,
	HEADER_CZ_COMMAND_MER                         = 557,
	HEADER_ZC_PROPERTY_HOMUN                      = 558,
	HEADER_ZC_FEED_MER                            = 559,
	HEADER_ZC_CHANGESTATE_MER                     = 560,
	HEADER_CZ_RENAME_MER                          = 561,
	HEADER_CZ_REQUEST_MOVENPC                     = 562,
	HEADER_CZ_REQUEST_ACTNPC                      = 563,
	HEADER_CZ_REQUEST_MOVETOOWNER                 = 564,
	HEADER_ZC_HOSKILLINFO_LIST                    = 565,
	HEADER_ZC_KILLER_POINT                        = 566,
	HEADER_CZ_KILLER_RANK                         = 567,
	HEADER_ZC_KILLER_RANK                         = 568,
	HEADER_ZC_HOSKILLINFO_UPDATE                  = 569,
	HEADER_ZC_REQ_STORE_PASSWORD                  = 570,
	HEADER_CZ_ACK_STORE_PASSWORD                  = 571,
	HEADER_ZC_RESULT_STORE_PASSWORD               = 572,
	HEADER_AC_EVENT_RESULT                        = 573,
	HEADER_HC_REQUEST_CHARACTER_PASSWORD          = 574,
	HEADER_CZ_MAIL_GET_LIST                       = 575,
	HEADER_ZC_MAIL_REQ_GET_LIST                   = 576,
	HEADER_CZ_MAIL_OPEN                           = 577,
	HEADER_ZC_MAIL_REQ_OPEN                       = 578,
	HEADER_CZ_MAIL_DELETE                         = 579,
	HEADER_CZ_MAIL_GET_ITEM                       = 580,
	HEADER_ZC_MAIL_REQ_GET_ITEM                   = 581,
	HEADER_CZ_MAIL_RESET_ITEM                     = 582,
	HEADER_CZ_MAIL_ADD_ITEM                       = 583,
	HEADER_CZ_MAIL_SEND                           = 584,
	HEADER_ZC_MAIL_REQ_SEND                       = 585,
	HEADER_ZC_MAIL_RECEIVE                        = 586,
	HEADER_CZ_AUCTION_CREATE                      = 587,
	HEADER_CZ_AUCTION_ADD_ITEM                    = 588,
	HEADER_CZ_AUCTION_ADD                         = 589,
	HEADER_CZ_AUCTION_ADD_CANCEL                  = 590,
	HEADER_CZ_AUCTION_BUY                         = 591,
	HEADER_ZC_AUCTION_RESULT                      = 592,
	HEADER_CZ_AUCTION_ITEM_SEARCH                 = 593,
	HEADER_ZC_AUCTION_ITEM_REQ_SEARCH             = 594,
	HEADER_ZC_STARPLACE                           = 595,
	HEADER_CZ_AGREE_STARPLACE                     = 596,
	HEADER_ZC_ACK_MAIL_ADD_ITEM                   = 597,
	HEADER_ZC_ACK_AUCTION_ADD_ITEM                = 598,
	HEADER_ZC_ACK_MAIL_DELETE                     = 599,
	HEADER_CA_REQ_GAME_GUARD_CHECK                = 600,
	HEADER_AC_ACK_GAME_GUARD                      = 601,
	HEADER_ZC_MAKINGITEM_LIST                     = 602,
	HEADER_CZ_REQ_MAKINGITEM                      = 603,
	HEADER_CZ_AUCTION_REQ_MY_INFO                 = 604,
	HEADER_CZ_AUCTION_REQ_MY_SELL_STOP            = 605,
	HEADER_ZC_AUCTION_ACK_MY_SELL_STOP            = 606,
	HEADER_ZC_AUCTION_WINDOWS                     = 607,
	HEADER_ZC_MAIL_WINDOWS                        = 608,
	HEADER_AC_REQ_LOGIN_OLDEKEY                   = 609,
	HEADER_AC_REQ_LOGIN_NEWEKEY                   = 610,
	HEADER_AC_REQ_LOGIN_CARDPASS                  = 611,
	HEADER_CA_ACK_LOGIN_OLDEKEY                   = 612,
	HEADER_CA_ACK_LOGIN_NEWEKEY                   = 613,
	HEADER_CA_ACK_LOGIN_CARDPASS                  = 614,
	HEADER_AC_ACK_EKEY_FAIL_NOTEXIST              = 615,
	HEADER_AC_ACK_EKEY_FAIL_NOTUSESEKEY           = 616,
	HEADER_AC_ACK_EKEY_FAIL_NOTUSEDEKEY           = 617,
	HEADER_AC_ACK_EKEY_FAIL_AUTHREFUSE            = 618,
	HEADER_AC_ACK_EKEY_FAIL_INPUTEKEY             = 619,
	HEADER_AC_ACK_EKEY_FAIL_NOTICE                = 620,
	HEADER_AC_ACK_EKEY_FAIL_NEEDCARDPASS          = 621,
	HEADER_AC_ACK_AUTHEKEY_FAIL_NOTMATCHCARDPASS  = 622,
	HEADER_AC_ACK_FIRST_LOGIN                     = 623,
	HEADER_AC_REQ_LOGIN_ACCOUNT_INFO              = 624,
	HEADER_CA_ACK_LOGIN_ACCOUNT_INFO              = 625,
	HEADER_AC_ACK_PT_ID_INFO                      = 626,
	HEADER_CZ_REQ_MAIL_RETURN                     = 627,
	HEADER_ZC_ACK_MAIL_RETURN                     = 628,
	HEADER_CH_ENTER2                              = 629,
	HEADER_AC_ACCEPT_LOGIN2                       = 630,
	HEADER_CA_LOGIN_PCBANG                        = 631,
	HEADER_ZC_NOTIFY_PCBANG                       = 632,
	HEADER_CZ_HUNTINGLIST                         = 633,
	HEADER_ZC_HUNTINGLIST                         = 634,
	HEADER_ZC_PCBANG_EFFECT                       = 635,
	HEADER_CA_LOGIN4                              = 636,
	HEADER_ZC_PROPERTY_MERCE                      = 637,
	HEADER_ZC_SHANDA_PROTECT                      = 638,
	HEADER_CA_CLIENT_TYPE                         = 639,
	HEADER_ZC_GANGSI_POINT                        = 640,
	HEADER_CZ_GANGSI_RANK                         = 641,
	HEADER_ZC_GANGSI_RANK                         = 642,
	HEADER_ZC_AID                                 = 643,
	HEADER_ZC_NOTIFY_EFFECT3                      = 644,
	HEADER_ZC_DEATH_QUESTION                      = 645,
	HEADER_CZ_DEATH_QUESTION                      = 646,
	HEADER_ZC_PC_CASH_POINT_ITEMLIST              = 647,
	HEADER_CZ_PC_BUY_CASH_POINT_ITEM              = 648,
	HEADER_ZC_PC_CASH_POINT_UPDATE                = 649,
	HEADER_ZC_NPC_SHOWEFST_UPDATE                 = 650,
	HEADER_HC_CHARNOTBEENSELECTED                 = 651,
	HEADER_CH_SELECT_CHAR_GOINGTOBEUSED           = 652,
	HEADER_CH_REQ_IS_VALID_CHARNAME               = 653,
	HEADER_HC_ACK_IS_VALID_CHARNAME               = 654,
	HEADER_CH_REQ_CHANGE_CHARNAME                 = 655,
	HEADER_HC_ACK_CHANGE_CHARNAME                 = 656,
	HEADER_ZC_MSG                                 = 657,
	HEADER_CZ_STANDING_RESURRECTION               = 658,
	HEADER_ZC_BOSS_INFO                           = 659,
	HEADER_ZC_READ_BOOK                           = 660,
	HEADER_ZC_EQUIPMENT_ITEMLIST2                 = 661,
	HEADER_ZC_STORE_EQUIPMENT_ITEMLIST2           = 662,
	HEADER_ZC_CART_EQUIPMENT_ITEMLIST2            = 663,
	HEADER_ZC_CASH_TIME_COUNTER                   = 664,
	HEADER_ZC_CASH_ITEM_DELETE                    = 665,
	HEADER_ZC_ITEM_PICKUP_ACK2                    = 666,
	HEADER_ZC_MER_INIT                            = 667,
	HEADER_ZC_MER_PROPERTY                        = 668,
	HEADER_ZC_MER_SKILLINFO_LIST                  = 669,
	HEADER_ZC_MER_SKILLINFO_UPDATE                = 670,
	HEADER_CZ_MER_COMMAND                         = 671,
	UNUSED_HEADER_CZ_MER_USE_SKILL                = 672,
	UNUSED_HEADER_CZ_MER_UPGRADE_SKILLLEVEL       = 673,
	HEADER_ZC_MER_PAR_CHANGE                      = 674,
	HEADER_ZC_GAMEGUARD_LINGO_KEY                 = 675,
	HEADER_CZ_GAMEGUARD_LINGO_READY               = 676,
	HEADER_CZ_KSY_EVENT                           = 677,
	HEADER_ZC_HACKSH_CPX_MSG                      = 678,
	HEADER_CZ_HACKSH_CPX_MSG                      = 679,
	HEADER_ZC_HACKSHIELD_CRC_MSG                  = 680,
	HEADER_CZ_HACKSHIELD_CRC_MSG                  = 681,
	HEADER_ZC_REQ_CASH_PASSWORD                   = 682,
	HEADER_CZ_ACK_CASH_PASSWORD                   = 683,
	HEADER_ZC_RESULT_CASH_PASSWORD                = 684,
	HEADER_AC_REQUEST_SECOND_PASSWORD             = 685,
	HEADER_ZC_SRPACKET_INIT                       = 686,
	HEADER_CZ_SRPACKET_START                      = 687,
	HEADER_CA_LOGIN_HAN                           = 688,
	HEADER_ZC_ALL_QUEST_LIST                      = 689,
	HEADER_ZC_ALL_QUEST_MISSION                   = 690,
	HEADER_ZC_ADD_QUEST                           = 691,
	HEADER_ZC_DEL_QUEST                           = 692,
	HEADER_ZC_UPDATE_MISSION_HUNT                 = 693,
	HEADER_CZ_ACTIVE_QUEST                        = 694,
	HEADER_ZC_ACTIVE_QUEST                        = 695,
	HEADER_ZC_ITEM_PICKUP_PARTY                   = 696,
	HEADER_ZC_SHORTCUT_KEY_LIST                   = 697,
	HEADER_CZ_SHORTCUT_KEY_CHANGE                 = 698,
	HEADER_ZC_EQUIPITEM_DAMAGED                   = 699,
	HEADER_ZC_NOTIFY_PCBANG_PLAYING_TIME          = 700,
	HEADER_ZC_SRCRYPTOR2_INIT                     = 701,
	HEADER_CZ_SRCRYPTOR2_START                    = 702,
	HEADER_ZC_SRPACKETR2_INIT                     = 703,
	HEADER_CZ_SRPACKETR2_START                    = 704,
	HEADER_ZC_NPC_CHAT                            = 705,
	HEADER_ZC_FORMATSTRING_MSG                    = 706,
	UNUSED_HEADER_CZ_FORMATSTRING_MSG_RES         = 707,
	HEADER_CZ_PARTY_JOIN_REQ                      = 708,
	HEADER_ZC_PARTY_JOIN_REQ_ACK                  = 709,
	HEADER_ZC_PARTY_JOIN_REQ                      = 710,
	HEADER_CZ_PARTY_JOIN_REQ_ACK                  = 711,
	HEADER_CZ_PARTY_CONFIG                        = 712,
	HEADER_ZC_PARTY_CONFIG                        = 713,
	HEADER_HC_REFUSE_SELECTCHAR                   = 714,
	HEADER_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO   = 715,
	HEADER_ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY = 716,
	HEADER_ZC_MEMORIALDUNGEON_INFO                = 717,
	HEADER_ZC_MEMORIALDUNGEON_NOTIFY              = 718,
	HEADER_CZ_MEMORIALDUNGEON_COMMAND             = 719,
	HEADER_ZC_EQUIPMENT_ITEMLIST3                 = 720,
	HEADER_ZC_STORE_EQUIPMENT_ITEMLIST3           = 721,
	HEADER_ZC_CART_EQUIPMENT_ITEMLIST3            = 722,
	HEADER_ZC_NOTIFY_BIND_ON_EQUIP                = 723,
	HEADER_ZC_ITEM_PICKUP_ACK3                    = 724,
	HEADER_ZC_ISVR_DISCONNECT                     = 725,
	HEADER_CZ_EQUIPWIN_MICROSCOPE                 = 726,
	HEADER_ZC_EQUIPWIN_MICROSCOPE                 = 727,
	HEADER_CZ_CONFIG                              = 728,
	HEADER_ZC_CONFIG                              = 729,
	HEADER_ZC_CONFIG_NOTIFY                       = 730,
	HEADER_CZ_BATTLEFIELD_CHAT                    = 731,
	HEADER_ZC_BATTLEFIELD_CHAT                    = 732,
	HEADER_ZC_BATTLEFIELD_NOTIFY_CAMPINFO         = 733,
	HEADER_ZC_BATTLEFIELD_NOTIFY_POINT            = 734,
	HEADER_ZC_BATTLEFIELD_NOTIFY_POSITION         = 735,
	HEADER_ZC_BATTLEFIELD_NOTIFY_HP               = 736,
	HEADER_ZC_NOTIFY_ACT2                         = 737,
	HEADER_CZ_USE_ITEM_NEW_JAPEN                  = 738,
	HEADER_CZ_USE_SKILL_NEW_JAPEN                 = 739,
	HEADER_CZ_ITEM_PICKUP_NEW_JAPEN               = 740,
	HEADER_CZ_REQUEST_MOVE_NEW_JAPEN              = 741,
	HEADER_CZ_BOT_CHECK                           = 742,
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
	HEADER_CZ_PROGRESS                            = 753,
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
	HEADER_CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST       = 860,
	HEADER_ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST      = 861,
	HEADER_CZ_CLOSE_WINDOW                        = 862,
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
	HEADER_AHC_GAME_GUARD                         = 989,
	HEADER_CAH_ACK_GAME_GUARD                     = 990,
	HEADER_ZC_WAITINGROOM_PARTYPLAY_JOIN          = 991,
	HEADER_CZ_WAITINGROOM_PARTYPLAY_JOIN_RESULT   = 992,
	HEADER_ZC_WAITINGROOM_SUBSCRIPTION_RESULT     = 993,
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
	HEADER_CZ_ENTER2                              = 1078,
	HEADER_CZ_REQUEST_ACT2                        = 1079,
	HEADER_CZ_USE_SKILL2                          = 1080,
	HEADER_CZ_USE_ITEM2                           = 1081,
	HEADER_ZC_REQ_CRACKPROOF                      = 1082,
	HEADER_CZ_ACK_CRACKPROOF                      = 1083,
	HEADER_ZC_CRACKPROOF_ERRCODE                  = 1084,
	HEADER_ZC_SKILL_POSTDELAY                     = 1085,
	HEADER_ZC_SKILL_POSTDELAY_LIST                = 1086,
	HEADER_ZC_MSG_STATE_CHANGE2                   = 1087,
	HEADER_ZC_MILLENNIUMSHIELD                    = 1088,
	HEADER_ZC_SKILLINFO_DELETE                    = 1089,
	HEADER_ZC_SKILL_SELECT_REQUEST                = 1090,
	HEADER_CZ_SKILL_SELECT_RESPONSE               = 1091,
	HEADER_ZC_SIMPLE_CASH_POINT_ITEMLIST          = 1092,
	HEADER_CZ_SIMPLE_BUY_CASH_POINT_ITEM          = 1093,
	HEADER_ZC_QUEST_NOTIFY_EFFECT                 = 1094,
	HEADER_ZC_BLOCKING_PLAY_CANCEL                = 1095,
	HEADER_HC_CHARACTER_LIST                      = 1096,
	HEADER_ZC_HACKSH_ERROR_MSG                    = 1097,
	HEADER_CZ_CLIENT_VERSION                      = 1098,
	HEADER_CZ_CLOSE_SIMPLECASH_SHOP               = 1099,

	HEADER_ZC_ES_RESULT                           = 2000,
	HEADER_CZ_ES_GET_LIST                         = 2001,
	HEADER_ZC_ES_LIST                             = 2002,
	HEADER_CZ_ES_CHOOSE                           = 2003,
	HEADER_CZ_ES_CANCEL                           = 2004,
	HEADER_ZC_ES_READY                            = 2005,
	HEADER_ZC_ES_GOTO                             = 2006,
	HEADER_CZ_GROUPINFO_CHANGE_V2                 = 2007,
	HEADER_ZC_REQ_GROUPINFO_CHANGE_V2             = 2008,
	HEADER_ZC_SHORTCUT_KEY_LIST_V2                = 2009,
	HEADER_CZ_CHANGE_GROUP_MASTER                 = 2010,
	HEADER_ZC_HO_PAR_CHANGE                       = 2011,
	HEADER_CZ_SEEK_PARTY                          = 2012,
	HEADER_ZC_SEEK_PARTY                          = 2013,
	HEADER_CZ_SEEK_PARTY_MEMBER                   = 2014,
	HEADER_ZC_SEEK_PARTY_MEMBER                   = 2015,
	HEADER_ZC_ES_NOTI_MYINFO                      = 2016,
	HEADER_ZC_SKILLINFO_UPDATE2                   = 2017,
	HEADER_ZC_MSG_VALUE                           = 2018,
	HEADER_ZC_ITEMLISTWIN_OPEN                    = 2019,
	HEADER_CZ_ITEMLISTWIN_RES                     = 2020,
	HDADER_CH_ENTER_CHECKBOT                      = 2021,
	HEADER_ZC_MSG_SKILL                           = 2022,
	HEADER_CH_CHECKBOT                            = 2023,
	HEADER_HC_CHECKBOT                            = 2024,
	HEADER_HC_CHECKBOT_RESULT                     = 2025,
	HEADER_LAST                                   = 2026,
};


enum
{
	HEADER_NZ_NEWNPC                              = 0x2710, //10000
	HEADER_ZN_ACKNEWNPC                           = 0x2711,
	HEADER_ZN_CONTACT                             = 0x2712,
	HEADER_NZ_MAPMOVE_ACK                         = 0x2713,
	HEADER_NZ_MENU_ACK                            = 0x2714,
	HEADER_NZ_ITEMLIST                            = 0x2715,
	HEADER_NZ_WARPNPC_COMMAND                     = 0x2716,
	HEADER_NZ_GUIDENPC_COMMAND                    = 0x2717,
	HEADER_NZ_TRADERNPC_COMMAND                   = 0x2718,
	HEADER_ZN_ANSWER                              = 0x2719,
	HEADER_NZ_CHANGE_MONEY                        = 0x271A,
	HEADER_NZ_CHANGE_ITEM                         = 0x271B,
	HEADER_NZ_CHANGE_VAR                          = 0x271C,
	HEADER_NZ_CHANGE_STATE                        = 0x271D,
	HEADER_NZ_SET_ITEM                            = 0x271E,
	HEADER_NZ_WAIT_DIALOG                         = 0x271F,
	HEADER_NZ_CLOSE_DIALOG                        = 0x2720,
	HEADER_NZ_DIALOG_ACK                          = 0x2721,
	HEADER_NZ_HEAL                                = 0x2722,
	HEADER_NZ_EXCHANGE_ITEM                       = 0x2723,
	HEADER_NZ_CHECKPOINT                          = 0x2724,
	HEADER_NZ_NOTIFY_STOREDITEM                   = 0x2725,
	HEADER_NZ_CARTON                              = 0x2726,
	HEADER_NZ_DLG_WRITE                           = 0x2727,
	HEADER_NZ_TRADER                              = 0x2728,
	HEADER_NZ_COMPASS                             = 0x2729,
	HEADER_NZ_NUDE                                = 0x272A,
	HEADER_NZ_SHOW_IMAGE                          = 0x272B,
	HEADER_NZ_CHANGEPALLETE                       = 0x272C,
	HEADER_NZ_ADDSKILL                            = 0x272D,
};


enum
{
	HEADER_SERVER_ENTRY                               = 0x2904, //10500
	HEADER_HA_LOGON                                   = 0x2905,
	HEADER_AH_LOGON_EXIST                             = 0x2906,
	HEADER_AH_LOGON_NOTEXIST                          = 0x2907,
	HEADER_ZH_LOGON                                   = 0x2908,
	HEADER_HZ_LOGON_EXIST                             = 0x2909,
	HEADER_HZ_LOGON_NOTEXIST                          = 0x290A,
	HEADER_ZH_CHAR_EXIT                               = 0x290B,
	HEADER_HA_CHAR_EXIT                               = 0x290C,
	HEADER_AH_DISCONNECT                              = 0x290D,
	HEADER_HZ_DISCONNECT                              = 0x290E,
	HEADER_HZ_ACK_RESTART                             = 0x290F,
	HEADER_ZH_RESTART                                 = 0x2910,
	HEADER_CONNECTION_CLOSED                          = 0x2911,
	HEADER_SAVE_USING_TIME                            = 0x2912,
	HEADER_ZH_SAVECHARINFO                            = 0x2913,
	HEADER_ZH_MAPMOVE                                 = 0x2914,
	HEADER_HZ_ACK_MAPMOVE                             = 0x2915,
	HEADER_ZI_LOGON                                   = 0x2916,
	HEADER_ZI_EXIT                                    = 0x2917,
	HEADER_ZI_WHISPER                                 = 0x2918,
	HEADER_IZ_WHISPER                                 = 0x2919,
	HEADER_IZ_ACK_WHISPER                             = 0x291A,
	HEADER_ZI_ACK_WHISPER                             = 0x291B,
	HEADER_ZI_REQ_USER_COUNT                          = 0x291C,
	HEADER_IZ_USER_COUNT                              = 0x291D,
	HEADER_ZI_BROADCAST                               = 0x291E,
	HEADER_IZ_BROADCAST                               = 0x291F,
	HEADER_ZI_MAKE_GROUP                              = 0x2920,
	HEADER_IZ_ACK_MAKE_GROUP                          = 0x2921,
	HEADER_IZ_GROUP_LIST                              = 0x2922,
	HEADER_ZI_REQ_JOIN_GROUP                          = 0x2923,
	HEADER_IZ_ACK_REQ_JOIN_GROUP                      = 0x2924,
	HEADER_IZ_REQ_JOIN_GROUP                          = 0x2925,
	HEADER_ZI_JOIN_GROUP                              = 0x2926,
	HEADER_ZI_REQ_LEAVE_GROUP                         = 0x2927,
	HEADER_ZI_REQ_EXPEL_GROUP_MEMBER                  = 0x2928,
	HEADER_IZ_ADD_MEMBER_TO_GROUP                     = 0x2929,
	HEADER_IZ_DELETE_MEMBER_FROM_GROUP                = 0x292A,
	HEADER_ZI_MAPMOVE                                 = 0x292B,
	HEADER_ZI_GRID_UPDATE                             = 0x292C,
	HEADER_ZI_CHAT_PARTY                              = 0x292D,
	HEADER_IZ_CHAT_PARTY                              = 0x292E,
	HEADER_IZ_DISCONNECT_ALL                          = 0x292F,
	HEADER_ZI_DISCONNECT_ALL                          = 0x2930,
	HEADER_ZI_CHANGE_EXPOPTION                        = 0x2931,
	HEADER_HA_PCINFOUPDATE                            = 0x2932,
	HEADER_IZ_REQ_SERVERSTATE                         = 0x2933,
	HEADER_IZ_SHOTDOWN                                = 0x2934,
	HEADER_ZI_SERVERSTATE                             = 0x2935,
	HEADER_ZI_REQ_MYGUILD_BASIC_INFO                  = 0x2936,
	HEADER_ZI_REQ_MAKE_GUILD                          = 0x2937,
	HEADER_IZ_MYGUILD_BASICINFO                       = 0x2938,
	HEADER_ZI_REQ_GUILD_MENUINTERFACE                 = 0x2939,
	HEADER_IZ_ACK_MYGUILD_MEMBER_INFO                 = 0x293A,
	HEADER_IZ_ACK_MYGUILD_POSITION                    = 0x293B,
	HEADER_IZ_ACK_MYGUILD_BANISH                      = 0x293C,
	HEADER_IZ_ACK_MYGUILD_LIST                        = 0x293D,
	HEADER_ZI_REGISTER_GUILD_EMBLEM_IMG               = 0x293E,
	HEADER_IZ_GET_GUILD_EMBLEM_IMG                    = 0x293F,
	HEADER_ZI_MEMBERMGR_INFO                          = 0x2940,
	HEADER_IZ_MEMBERMGR_INFO                          = 0x2941,
	HEADER_ZI_REQ_CHANGE_MEMBERPOS                    = 0x2942,
	HEADER_IZ_ACK_CHANGE_MEMBERPOS                    = 0x2943,
	HEADER_ZI_REQ_OPEN_MEMBER_INFO                    = 0x2944,
	HEADER_IZ_ACK_OPEN_MEMBER_INFO                    = 0x2945,
	HEADER_ZI_REQ_LEAVE_GUILD                         = 0x2946,
	HEADER_IZ_ACK_LEAVE_GUILD                         = 0x2947,
	HEADER_ZI_REQ_BAN_GUILD                           = 0x2948,
	HEADER_IZ_ACK_BAN_GUILD                           = 0x2949,
	HEADER_ZI_REQ_DISORGANIZE_GUILD                   = 0x294A,
	HEADER_IZ_REQ_DISORGANIZE_GUILD_RESULT            = 0x294B,
	HEADER_ZI_REQ_GUILD_POSITION_INFO                 = 0x294C,
	HEADER_IZ_ACK_GUILD_POSITION_INFO                 = 0x294D,
	HEADER_IZ_SKILL_INFO                              = 0x294E,
	HEADER_IZ_BAN_LIST                                = 0x294F,
	HEADER_IZ_OTHER_GUILD_LIST                        = 0x2950,
	HEADER_ZI_REQ_JOIN_GUILD                          = 0x2951,
	HEADER_IZ_REQ_JOIN_GUILD                          = 0x2952,
	HEADER_ZI_JOIN_GUILD                              = 0x2953,
	HEADER_IZ_ACK_REQ_JOIN_GUILD                      = 0x2954,
	HEADER_IZ_GUILD_LIST_TOD                          = 0x2955,
	HEADER_IZ_GUILDINFO_TOD                           = 0x2956,
	HEADER_IZ_GUILD_MEMBERINFO_TOD                    = 0x2957,
	HEADER_IZ_GUILD_ALLYINFO_TOD                      = 0x2958,
	HEADER_IZ_GUILD_BANISHINFO_TOD                    = 0x2959,
	HEADER_IZ_GUILD_MPOSITION_TOD                     = 0x295A,
	HEADER_IZ_GUILD_NOTICE_TOD                        = 0x295B,
	HEADER_IZ_RESULT_MAKE_GUILD                       = 0x295C,
	HEADER_IZ_UPDATE_CHARGDID                         = 0x295D,
	HEADER_IZ_UPDATE_CHARSTAT                         = 0x295E,
	HEADER_ZI_GUILD_NOTICE                            = 0x295F,
	HEADER_IZ_GUILD_NOTICE                            = 0x2960,
	HEADER_ZI_ALLY_GUILD                              = 0x2961,
	HEADER_IZ_ACK_REQ_ALLY_GUILD                      = 0x2962,
	HEADER_IZ_ADD_ALLY_GUILD                          = 0x2963,
	HEADER_ZI_REQ_HOSTILE_GUILD                       = 0x2964,
	HEADER_IZ_ACK_REQ_HOSTILE_GUILD                   = 0x2965,
	HEADER_IZ_ADD_HOSTILE_GUILD                       = 0x2966,
	HEADER_IZ_GUILD_MEMBER_ADD                        = 0x2967,
	HEADER_ZI_REQ_DELETE_RELATED_GUILD                = 0x2968,
	HEADER_IZ_DELETE_RELATED_GUILD                    = 0x2969,
	HEADER_ZI_ACTOR_INIT                              = 0x296A,
	HEADER_ZI_GUILD_CHAT                              = 0x296B,
	HEADER_IZ_GUILD_CHAT                              = 0x296C,
	HEADER_ZI_ADD_EXP                                 = 0x296D,
	HEADER_IZ_ADD_EXP                                 = 0x296E,
	HEADER_IZ_GUILD_LEVEL_UP                          = 0x296F,
	HEADER_IZ_GUILD_MEMBERINFO_FRAG                   = 0x2970,
	HEADER_IZ_GET_GUILD_EMBLEM_IMG_FRAG               = 0x2971,
	HEADER_ZI_REGISTER_GUILD_EMBLEM_IMG_FRAG          = 0x2972,
	HEADER_AH_DISCONNECT_RIGHTNOW                     = 0x2973,
	HEADER_HZ_DISCONNECT_RIGHTNOW                     = 0x2974,
	HEADER_ZI_CHAR_LEVEL_UP                           = 0x2975,
	HEADER_ZI_GUILD_ZENY                              = 0x2976,
	HEADER_IZ_GUILD_ZENY                              = 0x2977,
	HEADER_ZI_GUILD_ZENY_UPDATE_ALL                   = 0x2978,
	HEADER_IZ_GUILD_ZENY_UPDATE_ALL                   = 0x2979,
	HEADER_ZI_GUILD_PRELOAD                           = 0x297A,
	HEADER_ZI_GUILD_CHANGEOWNER_AGIT                  = 0x297B,
	HEADER_HA_REQ_PACKETINFO                          = 0x297C,
	HEADER_AH_ACK_PACKETINFO                          = 0x297D,
	HEADER_ZH_REQ_REMAINTIME                          = 0x297E,
	HEADER_HA_REQ_REMAINTIME                          = 0x297F,
	HEADER_AH_RES_REMAINTIME                          = 0x2980,
	HEADER_HZ_RES_REMAINTIME                          = 0x2981,
	HEADER_AH_INFO_REMAINTIME                         = 0x2982,
	HEADER_HZ_INFO_REMAINTIME                         = 0x2983,
	HEADER_IZ_GUILD_NOTIFYSKILLDATA                   = 0x2984,
	HEADER_ZI_GDSKILL_UPDATE                          = 0x2985,
	HEADER_ZE_REQ_CERTIFICATE                         = 0x2986,
	HEADER_EZ_PERMIT_CERTIFICATE                      = 0x2987,
	HEADER_ZI_MOVE                                    = 0x2988,
	HEADER_IZ_MOVE                                    = 0x2989,
	HEADER_ZI_GUILD_CHANGEMAXUSER                     = 0x298A,
	HEADER_IZ_GUILD_CHANGEMAXUSER                     = 0x298B,
	HEADER_IZ_FREE_GUILD                              = 0x298C,
	HEADER_IZ_GUILD_CHANGEOWNER_AGIT                  = 0x298D,
	HEADER_ZI_MAKE_GROUP2                             = 0x298E,
	HEADER_IZ_ADD_MEMBER_TO_GROUP2                    = 0x298F,
	HEADER_ZI_MOVE_GID                                = 0x2990,
	HEADER_IZ_GUILD_MAP_CHANGE                        = 0x2991,
	HEADER_ZI_VERSION                                 = 0x2992,
	HEADER_ZI_CHANGE_EXPOPTION2                       = 0x2993,
	HEADER_HA_LOGON_SESSION                           = 0x2994,
	HEADER_AH_LOGON_EXIST_SESSION                     = 0x2995,
	HEADER_AH_LOGON_NOTEXIST_SESSION                  = 0x2996,
	HEADER_ZI_DIVORCE                                 = 0x2997,
	HEADER_IZ_DIVORCE                                 = 0x2998,
	HEADER_IZ_FRIENDS_LIST                            = 0x2999,
	HEADER_IZ_FRIENDS_STATE                           = 0x299A,
	HEADER_ZI_ACK_REQ_ADD_FRIENDS                     = 0x299B,
	HEADER_IZ_ADD_FRIENDS                             = 0x299C,
	HEADER_ZI_DELETE_FRIENDS                          = 0x299D,
	HEADER_IZ_DELETE_FRIENDS                          = 0x299E,
	HEADER_ZI_MOVE_SERVER                             = 0x299F,
	HEADER_SVR_PING                                   = 0x29A0,
	HEADER_IZ_NOTIFY_MAKERRANK                        = 0x29A1,
	HEADER_ZI_UPDATE_MAKERRANK                        = 0x29A2,
	HEADER_ZI_MAIL_GET_LIST                           = 0x29A3,
	HEADER_ZH_MOVE_PVPWORLD                           = 529,
	HEADER_IZ_MAIL_REQ_GET_LIST                       = 0x29A4,
	HEADER_ZI_MAIL_OPEN                               = 0x29A5,
	HEADER_IZ_MAIL_REQ_OPEN                           = 0x29A6,
	HEADER_ZI_MAIL_DELETE                             = 0x29A7,
	HEADER_IZ_ACK_MAIL_DELETE                         = 0x29A8,
	HEADER_ZI_MAIL_GET_ITEM                           = 0x29A9,
	HEADER_IZ_MAIL_REQ_GET_ITEM                       = 0x29AA,
	HEADER_ZI_MAIL_SEND                               = 0x29AB,
	HEADER_IZ_MAIL_REQ_SEND                           = 0x29AC,
	HEADER_IZ_MAIL_RECEIVE                            = 0x29AD,
	HEADER_ZI_EPISODE_VERSION                         = 0x29AE,
	HEADER_IZ_CHK_PROCESSTIME                         = 0x29AF,
	HEADER_ZI_ACK_CHK_PROCESSTIME                     = 0x29B0,
	HEADER_IZ_DISCONNECT_CHARACTER                    = 0x29B1,
	HEADER_IZ_ACK_LOGON                               = 0x29B2,
	HEADER_ZI_REQ_MAIL_RETURN                         = 0x29B3,
	HEADER_IZ_ACK_MAIL_RETURN                         = 0x29B4,
	HEADER_HZ_NOTIFY_PCBANG                           = 0x29B5,
	HEADER_AH_LOGON_EXIST_PCBANG                      = 0x29B6,
	HEADER_HA_CHAR_SVR_INFO                           = 0x29B7,
	HEADER_HA_REQ_PLAYING_LIMITINFO                   = 0x29B8,
	HEADER_AH_ACK_PLAYING_LIMITINFO                   = 0x29B9,
	HEADER_AH_LOGON_EXIST_PCBANG_HAN                  = 0x29BA,
	HEADER_HZ_PING                                    = 0x29BB,
	HEADER_ZI_MEMORIALDUNGEON_SUBSCRIPTION            = 0x29BC,
	NOT_USED_HEADER_IZ_MEMORIALDUNGEON_CREATE_RESULT  = 0x29BD,
	HEADER_IZ_INSTANTMAP_CREATE_REQ                   = 0x29BE,
	HEADER_ZI_INSTANTMAP_CREATE_RES                   = 0x29BF,
	HEADER_HZ_NOTIFY_PCBANG_PLAYING_TIME              = 0x29C0,
	HEADER_ZI_SERVERSTATE_HAN_GAME                    = 0x29C1,
	HEADER_AH_NOTIFY_PCBANG_PLAYING_TIME              = 0x29C2,
	HEADER_IZ_INSTANTMAP_PLAYER_ENTER                 = 0x29C3,
	HEADER_ZI_INSTANTMAP_ERROR                        = 0x29C4,
	HEADER_IZ_INSTNATMAP_DESTROY                      = 0x29C5,
	HEADER_ZI_PING                                    = 0x29C6,
	HEADER_ZI_INSTANTMAP_ALLOW                        = 0x29C7,
	HEADER_XX_CONNECT                                 = 0x29C8,
	HEADER_XX_DISCONNECT                              = 0x29C9,
	HEADER_IZ_MEMORIALDUNGEON_MSG                     = 0x29CA,
	NOT_USED_HEADER_ZI_MEMORIALDUNGEON_NOTIFY_CONFIRM = 0x29CB,
	HEADER_ZI_PARTY_JOIN_REQ                          = 0x29CC,
	HEADER_IZ_PARTY_JOIN_REQ_ACK                      = 0x29CD,
	HEADER_IZ_PARTY_JOIN_REQ                          = 0x29CE,
	HEADER_ZI_PARTY_JOIN_REQ_ACK                      = 0x29CF,
	HEADER_AH_LOGON_ACK_EXTEND_BILLING_INFO           = 0x29D0,
	HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO       = 0x29D1,
	HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY     = 0x29D2,
	HEADER_IZ_MEMORIALDUNGEON_INFO                    = 0x29D3,
	HEADER_IZ_MEMORIALDUNGEON_NOTIFY                  = 0x29D4,
	HEADER_ZI_MEMORIALDUNGEON_COMMAND                 = 0x29D5,
	HEADER_IZ_MEMORIALDUNGEON_SYNC                    = 0x29D6,
	HEADER_ZI_MEMORIALDUNGEON_VISA                    = 0x29D7,
	HEADER_IZ_MEMORIALDUNGEON_VISA                    = 0x29D8,
	HEADER_IZ_MEMORIALDUNGEON_COMMAND                 = 0x29D9,
	HEADER_ZH_PLAYER_ALIVE                            = 0x29DA,
	HEADER_IZ_LEAVE_GROUP                             = 0x29DB,
	HEADER_ZI_MEMORIALDUNGEON_OPENSTATE               = 0x29DC,
	HEADER_IZ_MEMORIALDUNGEON_OPENSTATE               = 0x29DD,
	HEADER_ZI_ENTRANCESTATION_REGIST                  = 0x29DE,
	HEADER_IZ_WAITINGROOM_SUBSCRIPTION_RESULT         = 0x29DF,
	HEADER_ZI_WAITINGROOM_MY_SUBSCRIPTION_INFO        = 0x29E0,
	HEADER_IZ_WAITINGROOM_MY_SUBSCRIPTION_INFO        = 0x29E1,
	HEADER_IZ_WAITINGROOM_PARTYPLAY_JOIN_NOTI         = 0x29E2,
	HEADER_ZI_WAITINGROOM_PARTYPLAY_JOIN_RESULT       = 0x29E3,
	HEADER_IZ_WAITINGROOM_START                       = 0x29E4,
	HEADER_ZI_WAITINGROOM_PLAYER_STATE                = 0x29E5,
	HEADER_AH_DISPATCH_PREMIUM_INFO                   = 0x29E6,
	HEADER_HZ_CHAR_NAME_CHANGED                       = 0x29E7,
	HEADER_ZI_GROUPINFO_CHANGE_V2                     = 0x29E8,
	HEADER_IZ_REQ_GROUPINFO_CHANGE_V2                 = 0x29E9,
	HEADER_ZI_CHANGE_GROUP_MASTER                     = 0x29EA,
	HEADER_ZH_CASTLE_MAP_MOVE                         = 0x29EB,
	HEADER_AH_BILLING_ACK                             = 0x29EC,
	HEADER_HA_LOGON2                                  = 0x29ED,
	HEADER_ZI_SEEK_PARTY                              = 0x29EE,
	HEADER_IZ_SEEK_PARTY                              = 0x29EF,
	HEADER_ZI_SEEK_PARTY_MEMBER                       = 0x29F0,
	HEADER_IZ_SEEK_PARTY_MEMBER                       = 0x29F1,
	HEADER_ZI_GET_MY_BATTLEFILED_INFO                 = 0x29F2,
	HEADER_IZ_BATTLEFILED_SETTING                     = 0x29F3,
	HEADER_IZ_BATTLEFIELD_NOTI                        = 0x29F4,
	HEADER_ZI_BATTLEFIELD_NOTI                        = 0x29F5,
	HEADER_ZI_GET_ES_LIST                             = 0x29F6,
	HEADER_IZ_ES_LIST                                 = 0x29F7,
	HEADER_ZI_ENTER_ES_USER                           = 0x29F8,
	HEADER_ZI_ES_CANCEL                               = 0x29F9,
	HEADER_IZ_ACK_ES_RESULTCODE                       = 0x29FA,
	HEADER_IZ_ES_STATUS_CHECK                         = 0x29FB,
	HEADER_ZI_ES_ACK_STATUS_CHECK                     = 0x29FC,
	HEADER_IZ_ES_ENTER_READY                          = 0x29FD,
	HEADER_IZ_ES_ENTER_START                          = 0x29FE,
	HEADER_IZ_ES_NOTI_MYINFO                          = 0x29FF,
	HEADER_ZI_INTERSERVER_ORDER                       = 0x2A00,
	HEADER_AH_UPDATE_PCBANG_CNT                       = 0x2A01,
	HEADER_HA_CHECKBOT_REQ                            = 0x2A02,
	HEADER_AH_CHECKBOT_ACK                            = 0x2A03,
	HEADER_HA_CHECKBOT_UPDATE                         = 0x2A04,

	HEADER_MI_ENTER                                   = 0x2AF8, //11000
	HEADER_MI_REQ_SERVERSTATE                         = 0x2AF9,
	HEADER_MI_MSG                                     = 0x2AFA,
	HEADER_MI_SHOTDOWN                                = 0x2AFB,
	HEADER_IM_CONTROLFAIL                             = 0x2AFC,
	HEADER_IM_SERVERLIST                              = 0x2AFD,
	HEADER_IM_SERVERSTATE                             = 0x2AFE,
	HEADER_IM_ACKMSG                                  = 0x2AFF,
	HEADER_NOT_USE01                                  = 0x2B00,
	HEADER_MI_GET_GUILD_INFO                          = 0x2B01,
	HEADER_IM_REQ_GUILD_INFO                          = 0x2B02,
	HEADER_MI_GUILD_INFO_INIT                         = 0x2B03,
	HEADER_IM_RESULT_GUILD_INFO_INIT                  = 0x2B04,
	HEADER_MI_ALLY_GUILD_INIT                         = 0x2B05,
	HEADER_IM_REQ_ALLY_GUILD_INIT                     = 0x2B06,
	HEADER_IM_SERVERSTATE_HAN_GAME                    = 0x2B07,
};


struct PACKET
{
	/* this+0 */ short PacketType;
	/* this+2 */ char Data[];
};


struct PACKET_CZ_ENTER
{// 0x0072
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int AuthCode;
	/* this+14 */ unsigned long clientTime;
	/* this+18 */ unsigned char Sex;
};


struct PACKET_ZC_REFUSE_ENTER
{// 0x0074
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode;
};


struct PACKET_ZC_NOTIFY_STANDENTRY
{// 0x0078
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


struct PACKET_ZC_NOTIFY_STANDENTRY_NPC
{// 0x007C
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned char objecttype;
	/* this+ 3 */ unsigned long GID;
	/* this+ 7 */ short speed;
	/* this+ 9 */ short bodyState;
	/* this+11 */ short healthState;
	/* this+13 */ short effectState;
	/* this+15 */ short head;
	/* this+17 */ short weapon;
	/* this+19 */ short accessory;
	/* this+21 */ short job;
	/* this+23 */ short shield;
	/* this+25 */ short accessory2;
	/* this+27 */ short accessory3;
	/* this+29 */ short headpalette;
	/* this+31 */ short bodypalette;
	/* this+33 */ short headDir;
	/* this+35 */ bool isPKModeON;
	/* this+36 */ unsigned char sex;
	/* this+37 */ unsigned char PosDir[3];
	/* this+40 */ unsigned char xSize;
	/* this+41 */ unsigned char ySize;
};


struct PACKET_CZ_NOTIFY_ACTORINIT
{// 0x007D
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQUEST_TIME
{// 0x007E
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long clientTime;
};


struct PACKET_ZC_NOTIFY_TIME
{// 0x007F
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long time;
};


struct PACKET_ZC_NOTIFY_VANISH
{// 0x0080
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char type; // enum eVanishType
};
C_ASSERT(sizeof PACKET_ZC_NOTIFY_VANISH == 7);


struct PACKET_SC_NOTIFY_BAN
{// 0x0081
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode;
};


struct PACKET_CZ_REQUEST_MOVE
{// 0x0085
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char dest[3];
};


struct PACKET_ZC_NOTIFY_PLAYERMOVE
{// 0x0087
	/* this+0 */ short PacketType;
	/* this+2 */ DWORD moveStartTime;
	/* this+6 */ BYTE MoveData[6];
};


struct PACKET_ZC_STOPMOVE
{// 0x0088 (136)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;
};


struct PACKET_CZ_REQUEST_ACT
{// 0x0089
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long targetGID;
	/* this+6 */ unsigned char action;
};

struct PACKET_ZC_NOTIFY_ACT
{// 0x008A
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
C_ASSERT(sizeof PACKET_ZC_NOTIFY_ACT == 29);


struct PACKET_CZ_REQUEST_CHAT
{// 0x008C
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_ZC_NOTIFY_CHAT
{// 0x008D
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long GID;
	/* this+8 */ char Text[]; //dynamic
};

struct PACKET_ZC_NOTIFY_PLAYERCHAT
{// 0x008E
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[]; //dynamic
};


struct PACKET_ZC_NPCACK_SERVERMOVE
{// 0x0092
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char mapName[15+1];
	/* this+18 */ short xPos;
	/* this+20 */ short yPos;
	/* this+22 */ ZSERVER_ADDR addr;
};


struct PACKET_ZC_NPCACK_ENABLE
{// 0x0093
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_REQNAME
{// 0x0094
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_ACK_REQNAME
{// 0x0095
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char CName[24];
};
C_ASSERT(sizeof PACKET_ZC_ACK_REQNAME == 30);


struct PACKET_CZ_WHISPER
{// 0x0096
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ char receiver[24];
	/* this+28 */ char message[];
};


struct PACKET_ZC_WHISPER
{// 0x0097
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ char sender[24];
	/* this+28 */ char message[];
};


struct PACKET_ZC_BROADCAST
{// 0x009A
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_CZ_ITEM_PICKUP
{// 0x009F
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long ITAID;
};


struct PACKET_ZC_STORE_NORMAL_ITEMLIST
{// 0x00A5 (165)
	struct ITEM
	{
		/* this+ 0 */ short index;
		/* this+ 2 */ unsigned short ITID;
		/* this+ 4 */ unsigned char type;
		/* this+ 5 */ bool IsIdentified;
		/* this+ 6 */ short count;
		/* this+ 8 */ unsigned short WearState;
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ ITEM Item[];
};


struct PACKET_CZ_USE_ITEM
{// 0x00A7
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned long AID;
};


struct PACKET_CZ_REQ_WEAR_EQUIP
{// 0x00A9
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned short wearLocation;
};


struct PACKET_ZC_REQ_WEAR_EQUIP_ACK
{// 0x00AA
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned short wearLocation;
	/* this+6 */ unsigned char result;
};


struct PACKET_CZ_REQ_TAKEOFF_EQUIP
{// 0x00AB
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
};


struct PACKET_ZC_REQ_TAKEOFF_EQUIP_ACK
{// 0x00AC
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned short wearLocation;
	/* this+6 */ bool result;
};


struct PACKET_ZC_PAR_CHANGE
{// 0x00B0
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short varID;
	/* this+4 */ int count;
};


struct PACKET_ZC_RESTART_ACK
{// 0x00B3
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
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


struct PACKET_CZ_DISCONNECT_ALL_CHARACTER
{// 0x00CE
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_SETTING_WHISPER_PC
{// 0x00CF
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char name[24];
	/* this+26 */ unsigned char type;
};


struct PACKET_ZC_SETTING_WHISPER_PC
{// 0x00D1
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
	/* this+3 */ unsigned char result;
};


struct PACKET_ZC_MEMBER_NEWENTRY
{// 0x00DC
	/* this+0 */ short PacketType;
	/* this+2 */ short curcount;
	/* this+4 */ char name[24];
};


struct PACKET_CZ_REQ_EXCHANGE_ITEM
{// 0x00E4
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_ACK_EXCHANGE_ITEM
{// 0x00E7
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_ZC_CANCEL_EXCHANGE_ITEM
{// 0x00EE
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_MAKE_GROUP
{// 0x00F9
	/* this+0 */ short PacketType;
	/* this+2 */ char groupName[24];
};


struct PACKET_ZC_ACK_MAKE_GROUP
{// 0x00FA
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_CZ_REQ_LEAVE_GROUP
{// 0x0100
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_GROUPINFO_CHANGE
{// 0x0101
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long expOption;
};


struct PACKET_CZ_CHANGE_GROUPEXPOPTION
{// 0x0102
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long expOption;
};


struct PACKET_ZC_NOTIFY_HP_TO_GROUPM
{// 0x0106
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short hp;
	/* this+8 */ short maxhp;
};


struct PACKET_ZC_NOTIFY_POSITION_TO_GROUPM
{// 0x0107
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;
};


struct PACKET_CZ_REQUEST_CHAT_PARTY
{// 0x0108
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[]; // dynamic
};


struct PACKET_ZC_MVP_GETTING_ITEM
{// 0x010A
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short ITID;
};


struct PACKET_ZC_MVP_GETTING_SPECIAL_EXP
{// 0x010B
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long exp;
};


struct PACKET_ZC_SKILLINFO_LIST
{// 0x010F
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
};


struct PACKET_CZ_USE_SKILL
{// 0x0113 | 0x02E3
	/* this+0 */ short PacketType;
	/* this+2 */ short selectedLevel;
	/* this+4 */ unsigned short SKID;
	/* this+6 */ unsigned long targetID;
};


struct PACKET_CZ_USE_SKILL_TOGROUND
{// 0x0116
	/* this+0 */ short PacketType;
	/* this+2 */ short selectedLevel;
	/* this+4 */ unsigned short SKID;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;
};


struct PACKET_ZC_USE_SKILL
{// 0x011A
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short SKID;
	/* this+ 4 */ short level;
	/* this+ 6 */ unsigned long targetAID;
	/* this+10 */ unsigned long srcAID;
	/* this+14 */ bool result;

	//public: void PACKET_ZC_USE_SKILL::Crypt(void);
};


struct PACKET_ZC_SKILL_ENTRY
{// 0x011F
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long creatorAID;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned char job;
	/* this+15 */ bool isVisible;
};


struct PACKET_ZC_SKILL_DISAPPEAR
{// 0x0120
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_OPENSTORE
{// 0x012D
	/* this+0 */ short PacketType;
	/* this+2 */ short itemcount;
};
C_ASSERT(sizeof PACKET_ZC_OPENSTORE == 4);


struct PACKET_CZ_REQ_CLOSESTORE
{// 0x012E
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_DISAPPEAR_ENTRY
{// 0x0132
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long makerAID;
};


struct PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC
{// 0x0133 (307)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long AID;
	/* this+8 */ PURCHASE_ITEM_FROMMC Item[];
};


struct PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC
{// 0x0134
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long AID;
	/* this+8 */ CZ_PURCHASE_ITEM_FROMMC Item[];
};


struct PACKET_ZC_PC_PURCHASE_RESULT_FROMMC
{// 0x0135
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ short curcount;
	/* this+6 */ unsigned char result;
};


struct PACKET_ZC_USESKILL_ACK
{// 0x013E
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
{// 0x013F
	/* this+0 */ short PacketType;
	/* this+2 */ char itemName[24];
};
C_ASSERT(sizeof PACKET_CZ_ITEM_CREATE == 26);


struct PACKET_ZC_MYGUILD_BASIC_INFO
{// 0x014C
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ RELATED_GUILD_INFO Info[];
};


struct PACKET_CZ_REQ_GUILD_MENU
{// 0x014F
	/* this+0 */ short PacketType;
	/* this+2 */ int Type;
};


struct PACKET_CZ_REGISTER_GUILD_EMBLEM_IMG
{// 0x0153
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ char Emblem[];
};


struct PACKET_ZC_MEMBERMGR_INFO
{// 0x0154
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ //TODO
};


struct PACKET_CZ_REQ_BAN_GUILD
{// 0x015B
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ int AID;
	/* this+10 */ int GID;
	/* this+14 */ char reasonDesc[40];
};


struct PACKET_ZC_POSITION_INFO
{// 0x0160
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ //TODO
};


struct PACKET_ZC_BAN_LIST
{// 0x0163
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ //TODO
};


struct PACKET_CZ_REQ_MAKE_GUILD
{// 0x0165
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char GName[24];
};


struct PACKET_ZC_POSITION_ID_NAME_INFO
{// 0x0166
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ //TODO
};


struct PACKET_ZC_RESULT_MAKE_GUILD
{// 0x0167
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
};


struct PACKET_ZC_GUILD_NOTICE
{// 0x016F
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char subject[60];
	/* this+62 */ char notice[120];
};


struct PACKET_CZ_REQ_ALLY_GUILD
{// 0x170
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long MyAID;
	/* this+10 */ unsigned long MyGID;
};


struct PACKET_ZC_REQ_ALLY_GUILD
{// 0x171
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long otherAID;
	/* this+6 */ char guildName[24];
};


struct PACKET_CZ_REQ_GUILD_MEMBER_INFO
{// 0x0175
	/* this+0 */ short PacketType;
	/* this+2 */ int GID;
};


struct PACKET_ZC_ACK_GUILD_MEMBER_INFO
{// 0x0176
	/* this+0 */ short PacketType;
	/* this+2 */ GUILD_MEMBER_INFO Info;
};


struct PACKET_CZ_GUILD_CHAT
{// 0x017E
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char Text[]; //dynamic
};


struct PACKET_CZ_REQ_HOSTILE_GUILD
{// 0x0180
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_DELETE_RELATED_GUILD
{// 0x0184
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long OpponentGDID;
	/* this+6 */ int Relation;
};


struct PACKET_PING
{// 0x0187
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_CZ_REQ_DISCONNECT
{// 0x018A
	/* this+0 */ short PacketType;
	/* this+2 */ short type;
};
C_ASSERT(sizeof PACKET_CZ_REQ_DISCONNECT == 4);


struct PACKET_ZC_ACK_REQ_DISCONNECT
{// 0x018B
	/* this+0 */ short PacketType;
	/* this+2 */ short result;
};
C_ASSERT(sizeof PACKET_ZC_ACK_REQ_DISCONNECT == 4);


struct PACKET_ZC_MAKABLEITEMLIST
{// 0x018D (397)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ MAKABLEITEM_INFO Info[];
};


struct PACKET_ZC_ACK_REQMAKINGITEM
{// 0x018F
	/* this+0 */ short PacketType;
	/* this+2 */ short result;
	/* this+4 */ unsigned short ITID;
};


struct PACKET_ZC_ACK_REQNAMEALL
{// 0x0195
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ char CName[24];
	/* this+30 */ char PName[24];
	/* this+54 */ char GName[24];
	/* this+78 */ char RName[24];
};
C_ASSERT(sizeof PACKET_ZC_ACK_REQNAMEALL == 102);


struct PACKET_ZC_MSG_STATE_CHANGE
{// 0x0196
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ unsigned long AID;
	/* this+8 */ bool state;
};


struct PACKET_ZC_NOTIFY_MAPPROPERTY
{// 0x0199
	/* this+0 */ short PacketType;
	/* this+2 */ short type;
};


struct PACKET_ZC_NOTIFY_EFFECT
{// 0x019B (411)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ int effectID; // enum enumEFFECT
};


struct PACKET_ZC_PET_ACT
{// 0x01AA
	/* this+0 */ short PacketType;
	/* this+2 */ int GID;
	/* this+6 */ int data;
};


struct PACKET_CZ_REQ_MAKINGARROW
{// 0x01AE
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short id;
};


struct PACKET_CZ_REQ_CHANGECART
{// 0x01AF
	/* this+0 */ short PacketType;
	/* this+2 */ short num;
};


struct PACKET_ZC_SHOWDIGIT
{// 0x01B1
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char type;
	/* this+3 */ int value;
};


struct PACKET_ZC_GUILD_INFO2
{// 0x01B6
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
{// 0x01B7
	/* this+0 */ short PacketType;
	/* this+2 */ int zeny;
};


struct PACKET_ZC_GUILD_ZENY_ACK
{// 0x01B8
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
	/* this+2 */ char CharacterName[24];
};


struct PACKET_CZ_REQ_REMAINTIME
{// 0x01C0
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_SKILL_ENTRY2
{// 0x01C9
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
{// 0x01CA
	/* this+0 */ short PacketType;
	/* this+2 */ bool result;
};


struct PACKET_ZC_NOTIFY_MAPPROPERTY2
{// 0x01D6
	/* this+0 */ short PacketType;
	/* this+2 */ short type;
};


struct PACKET_ZC_NOTIFY_SKILL2
{// 0x01DE
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
{// 0x01DF
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZC_ACK_ACCOUNTNAME
{// 0x01E0
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char name[24];
};


struct PACKET_ZC_REQ_COUPLE
{// 0x01E2
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char name[24];
};


struct PACKET_CZ_JOIN_COUPLE
{// 0x01E3
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int answer;
};


struct PACKET_CZ_REQ_JOIN_COUPLE
{// 0x01E5
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_CZ_DORIDORI
{// 0x01E7
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_MAKE_GROUP2
{// 0x01E8
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char groupName[24];
	/* this+26 */ unsigned char ItemPickupRule;
	/* this+27 */ unsigned char ItemDivisionRule;
};


struct PACKET_ZC_ADD_MEMBER_TO_GROUP2
{// 0x01E9
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
{// 0x01EA
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_CZ_CHOPOKGI
{// 0x01ED
	/* this+0 */ short PacketType;
};


struct PACKET_ZC_NOTIFY_EFFECT2
{// 0x01F3 (499)
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ int effectID;
};


struct PACKET_ZC_REQ_EXCHANGE_ITEM2
{// 0x01F4
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char name[24];
	/* this+26 */ unsigned long GID;
	/* this+30 */ short level;
};


struct PACKET_ZC_ACK_EXCHANGE_ITEM2
{// 0x01F5
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char result;
	/* this+3 */ unsigned long GID;
	/* this+7 */ short level;
};


struct PACKET_ZC_REQ_BABY
{// 0x01F6
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char name[24];
};


struct PACKET_CZ_JOIN_BABY
{// 0x01F7
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int answer;
};


struct PACKET_CZ_REQ_JOIN_BABY
{// 0x01F9
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_CZ_REQ_ITEMREPAIR
{// 0x01FD
	/* this+0 */ short PacketType;
	/* this+2 */ REPAIRITEM_INFO TargetItemInfo;
};
C_ASSERT(sizeof PACKET_CZ_REQ_ITEMREPAIR == 15);


struct PACKET_ZC_STARSKILL
{// 0x020E
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char mapName[24];
	/* this+26 */ int monsterID;
	/* this+30 */ unsigned char star;
	/* this+31 */ unsigned char result;
};


struct PACKET_ZC_SKILLMSG
{// 0x0215
	/* this+0 */ short PacketType;
	/* this+2 */ int MsgNo;
};


struct PACKET_ZC_BABYMSG
{// 0x0216
	/* this+0 */ short PacketType;
	/* this+2 */ int MsgNo;
};


struct PACKET_ZC_NOTIFY_CRAZYKILLER
{// 0x0220
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ int isCrazyKiller;
};
C_ASSERT(sizeof PACKET_ZC_NOTIFY_CRAZYKILLER == 10);


struct PACKET_CZ_REQ_WEAPONREFINE
{// 0x0222
	/* this+0 */ short PacketType;
	/* this+2 */ int Index;
};


struct PACKET_ZC_STATE_CHANGE3
{// 0x0229
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ short bodyState;
	/* this+ 8 */ short healthState;
	/* this+10 */ int effectState;
	/* this+14 */ bool isPKModeON;
};


struct PACKET_ZC_NOTIFY_MOVEENTRY3
{// 0x022C
	/* this+ 0 */ short PacketType;
	/* this +2 */ unsigned char objecttype;
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
};


struct PACKET_CZ_REQUEST_ACTNPC
{// 0x0233
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long targetGID;
	/* this+10 */ unsigned char action;
};


struct PACKET_CZ_REQUEST_MOVETOOWNER
{// 0x0234
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
};


struct PACKET_CZ_MAIL_SEND
{// 0x0248
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ char ReceiveName[24];
	/* this+28 */ char Header[40];
	/* this+68 */ char Message[];
};


struct PACKET_ZC_MAIL_REQ_SEND
{// 0x0249
	enum
	{
		RESULT_SUCCESS = 0,
		RESULT_USER_NOT_FOUND = 1,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ char Result;
};


struct PACKET_CZ_AGREE_STARPLACE
{// 0x0254
	/* this+0 */ short PacketType;
	/* this+2 */ char which;
};


struct PACKET_ZC_PCBANG_EFFECT
{// 0x027B
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int ExpFactor;
	/* this+ 6 */ int ExpFactor2;
	/* this+10 */ int DropFactor;
};


struct PACKET_ZC_NOTIFY_EFFECT3
{// 0x0284 (644)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ int effectID;
	/* this+10 */ int numdata;
};


struct PACKET_CZ_MER_COMMAND
{// 0x029F
	enum
	{
		COMMAND_REQ_NONE = 0x0,
		COMMAND_REQ_PROPERTY = 0x1,
		COMMAND_REQ_DELETE = 0x2,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ char command;
};


struct PACKET_ZC_ITEM_PICKUP_PARTY
{// 0x02B8
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long accountID;
	/* this+ 6 */ unsigned short ITID;
	/* this+ 8 */ bool IsIdentified;
	/* this+ 9 */ bool IsDamaged;
	/* this+10 */ unsigned char refiningLevel;
	/* this+11 */ EQUIPSLOTINFO slot;
	/* this+19 */ unsigned short location;
	/* this+21 */ unsigned char type;
};
C_ASSERT(sizeof PACKET_ZC_ITEM_PICKUP_PARTY == 22);


struct PACKET_CZ_SHORTCUT_KEY_CHANGE
{// 0x02BA
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short Index;
	/* this+4 */ ShortCutKey ShortCutKey;
};


struct PACKET_ZC_UPDATE_MISSION_HUNT
{// 0x02B5
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ short count;
	/* this+6 */ PACKET_MOB_HUNTING Hunt[];
};


struct PACKET_ZC_NPC_CHAT
{// 0x02C1
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short packetLength;
	/* this+ 4 */ unsigned long accountID;
	/* this+ 8 */ unsigned long color;
	/* this+12 */ char Text[]; //dynamic
};


struct PACKET_CZ_PARTY_JOIN_REQ
{// 0x02C4
	/* this+0 */ short PacketType;
	/* this+2 */ char characterName[24];
};


struct PACKET_ZC_PARTY_JOIN_REQ_ACK
{// 0x02C5
	enum enumAnswer
	{
		ANSWER_ALREADY_OTHERGROUPM = 0,
		ANSWER_JOIN_REFUSE         = 1,
		ANSWER_JOIN_ACCEPT         = 2,
		ANSWER_MEMBER_OVERSIZE     = 3,
		ANSWER_DUPLICATE           = 4,
		ANSWER_JOINMSG_REFUSE      = 5,
		ANSWER_UNKNOWN_ERROR       = 6,
		ANSWER_UNKNOWN_CHARACTER   = 7,
		ANSWER_INVALID_MAPPROPERTY = 8,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char characterName[24];
	/* this+26 */ enum PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer answer;
};


struct PACKET_ZC_PARTY_JOIN_REQ
{// 0x02C6
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GRID;
	/* this+6 */ char groupName[24];
};


struct PACKET_CZ_PARTY_JOIN_REQ_ACK
{// 0x02C7
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GRID;
	/* this+6 */ bool bAccept;
};


struct PACKET_CZ_PARTY_CONFIG
{// 0x02C8
	/* this+0 */ short PacketType;
	/* this+2 */ bool bRefuseJoinMsg;
};


struct PACKET_ZC_PARTY_CONFIG
{// 0x02C9
	/* this+0 */ short PacketType;
	/* this+2 */ bool bRefuseJoinMsg;
};


struct PACKET_ZC_MEMORIALDUNGEON_NOTIFY
{// 0x02CE
	enum enumTYPE
	{
		TYPE_NOTIFY                = 0,
		TYPE_DESTROY_LIVE_TIMEOUT  = 1,
		TYPE_DESTROY_ENTER_TIMEOUT = 2,
		TYPE_DESTROY_USER_REQUEST  = 3,
		TYPE_CREATE_FAIL           = 4,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ enum PACKET_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE Type;
	/* this+6 */ unsigned long EnterLimitDate;
};


struct PACKET_CZ_MEMORIALDUNGEON_COMMAND
{// 0x02CF
	enum enumCOMMAND
	{
		COMMAND_SUBSCRIPTION_CANCEL = 0x0,
		COMMAND_MEMORIALDUNGEON_DESTROY = 0x1,
		COMMAND_MEMORIALDUNGEON_DESTROY_FORCE = 0x2,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ enum PACKET_CZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND Command;
};


struct PACKET_ZC_EQUIPMENT_ITEMLIST3
{// 0x02D0
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
	/* this+4 */ //ITEM Item[]; //error C2503
};


struct PACKET_ZC_STORE_EQUIPMENT_ITEMLIST3 : public PACKET_ZC_EQUIPMENT_ITEMLIST3
{// 0x02D1
};


struct PACKET_ZC_CART_EQUIPMENT_ITEMLIST3 : public PACKET_ZC_EQUIPMENT_ITEMLIST3
{// 0x02D2
};


struct PACKET_CZ_EQUIPWIN_MICROSCOPE
{// 0x02D6
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_CZ_CONFIG
{// 0x02D8
	enum enumConfig
	{
		CONFIG_OPEN_EQUIPMENT_WINDOW = 0x0,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ enum PACKET_CZ_CONFIG::enumConfig Config;
	/* this+6 */ int Value;
};


struct PACKET_ZC_CONFIG_NOTIFY
{// 0x02DA
	/* this+0 */ short PacketType;
	/* this+2 */ bool bOpenEquipmentWin;
};


struct PACKET_CZ_BATTLEFIELD_CHAT
{// 0x02DB
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ char message[];
};


struct PACKET_ZC_BATTLEFIELD_CHAT
{// 0x02DC
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long accountID;
	/* this+ 8 */ char name[24];
	/* this+32 */ char message[];
};


struct PACKET_ZC_BATTLEFIELD_NOTIFY_POSITION
{// 0x02DF
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long accountID;
	/* this+ 6 */ char name[24];
	/* this+30 */ unsigned short job;
	/* this+32 */ short x;
	/* this+34 */ short y;
};


struct PACKET_ZC_NOTIFY_ACT2
{// 0x02E1
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long targetGID;
	/* this+10 */ unsigned long startTime;
	/* this+14 */ int attackMT;
	/* this+18 */ int attackedMT;
	/* this+22 */ int damage;
	/* this+26 */ short count;
	/* this+28 */ unsigned char action;
	/* this+29 */ int leftDamage;
};


struct PACKET_ZC_MAPPROPERTY
{// 0x02E7
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ short type;
	/* this+6 */ unsigned char array[];
};


struct PACKET_ZC_NORMAL_ITEMLIST3
{// 0x02E8
	struct ITEM
	{
		/* this+ 0 */ short index;
		/* this+ 2 */ unsigned short ITID;
		/* this+ 4 */ unsigned char type;
		/* this+ 5 */ bool IsIdentified;
		/* this+ 6 */ short count;
		/* this+ 8 */ unsigned short WearState;
		/* this+10 */ EQUIPSLOTINFO slot;
		/* this+16 */ long HireExpireDate;
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short Length;
	/* this+4 */ //ITEM Item[]; //error C2503
};


struct PACKET_ZC_CART_NORMAL_ITEMLIST3 : public PACKET_ZC_NORMAL_ITEMLIST3
{// 0x02E9
};


struct PACKET_ZC_STORE_NORMAL_ITEMLIST3 : public PACKET_ZC_NORMAL_ITEMLIST3
{// 0x02EA
};


struct PACKET_ZC_ACCEPT_ENTER2
{// 0x02EB
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long startTime;
	/* this+ 6 */ unsigned char PosDir[3];
	/* this+ 9 */ unsigned char xSize;
	/* this+10 */ unsigned char ySize;
	/* this+11 */ short font;
};


struct PACKET_CZ_REASSEMBLY_IDENTITY
{// 0x0332
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
C_ASSERT(sizeof PACKET_CZ_REASSEMBLY_IDENTITY == 5);


struct PACKET_CZ_ENTER2
{// 0x0436
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int AuthCode;
	/* this+14 */ unsigned long clientTime;
	/* this+18 */ unsigned char Sex;

	//public: void PACKET_CZ_ENTER2::Crypt(void);
};


struct PACKET_CZ_REQUEST_ACT2
{// 0x0437
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long targetGID;
	/* this+6 */ unsigned char action;
	
	//public: void PACKET_CZ_REQUEST_ACT2::Crypt(unsigned int);
};


struct PACKET_CZ_USE_SKILL2
{// 0x0438
	/* this+0 */ short PacketType;
	/* this+2 */ short selectedLevel;
	/* this+4 */ unsigned short SKID;
	/* this+6 */ unsigned long targetID;

	//public: void PACKET_CZ_USE_SKILL2::Crypt(unsigned int);
};


struct PACKET_CZ_USE_ITEM2
{// 0x0439
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned long AID;
};


struct PACKET_ZC_SKILL_SELECT_REQUEST
{// 0x0442
	enum enumWHY
	{
		WHY_LOWERVER_COMPATIBILITY = 0x0,
		WHY_SC_AUTOSHADOWSPELL = 0x1,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ enum PACKET_ZC_SKILL_SELECT_REQUEST::enumWHY why;
};


struct PACKET_CZ_SKILL_SELECT_RESPONSE
{// 0x0443
	/* this+0 */ short PacketType;
	/* this+2 */ enum PACKET_ZC_SKILL_SELECT_REQUEST::enumWHY why;
	/* this+6 */ unsigned short SKID;
};


struct PACKET_ZC_BLOCKING_PLAY_CANCEL
{// 0x0447
	/* this+0 */ short PacketType;
};


struct PACKET_CZ_GROUPINFO_CHANGE_V2
{// 0x07D7
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long expOption;
	/* this+6 */ unsigned char ItemPickupRule;
	/* this+7 */ unsigned char ItemDivisionRule;
};


struct PACKET_ZC_REQ_GROUPINFO_CHANGE_V2
{// 0x07D8
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long expOption;
	/* this+6 */ unsigned char ItemPickupRule;
	/* this+7 */ unsigned char ItemDivisionRule;
};


struct PACKET_CZ_SEEK_PARTY
{// 0x07DC (2012)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Job;
	/* this+ 6 */ unsigned long Level;
	/* this+10 */ char mapName[15+1];
	/* this+26 */ unsigned long Option;
};


struct PACKET_NZ_NEWNPC
{// 0x2710 (10000)
	/* this+ 0 */ int NAID;
	/* this+ 4 */ short xPos;
	/* this+ 6 */ short yPos;
	/* this+ 8 */ short spriteType;
	/* this+10 */ int RegenMinTime;
	/* this+14 */ int RegenMaxTime;
	/* this+18 */ int RegenType;
	/* this+22 */ int sizeType;
	/* this+26 */ unsigned char npcType;
	/* this+27 */ char direction;
	/* this+28 */ char mapName[16];
	/* this+44 */ char NPCName[24];
	/* this+68 */ unsigned char xSize;
	/* this+69 */ unsigned char ySize;
	/* this+70 */ bool force;
};


struct PACKET_ZH_SAVECHARINFO
{// 0x2913
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ unsigned long AuthCode;
};


struct PACKET_ZI_LOGON
{// 0x2916
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


struct PACKET_ZH_LOGON
{// 0x2908
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int AuthCode;
	/* this+14 */ int curUser;
	/* this+18 */ unsigned char sex;
};


struct PACKET_HZ_LOGON_ACK
{// 0x2909 | 0x290A
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char ID[24];
	/* this+34 */ unsigned long TotalUsingTime;
	/* this+38 */ int selectedCharNum;
};


struct PACKET_HZ_DISCONNECT
{// 0x290E
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned char reason;
};


struct PACKET_CONNECTION_CLOSED
{// 0x2911
	/* this+0 */ short PacketType;
	/* this+2 */ short Type;
};


struct PACKET_ZH_MAPMOVE
{// 0x2914
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long NID;
	/* this+10 */ unsigned long ServerID;
	/* this+14 */ unsigned char sex;
};


struct PACKET_ZI_BROADCAST
{// 0x291E
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_IZ_BROADCAST
{// 0x291F
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ char Text[];
};


struct PACKET_ZI_REQ_LEAVE_GROUP
{// 0x2927
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned long GID;
};


struct PACKET_ZI_CHAT_PARTY
{// 0x292D
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long GRID;
	/* this+12 */ char Text[];
};


struct PACKET_IZ_DISCONNECT_ALL
{// 0x292F
	/* this+0 */ short PacketType;
};


struct PACKET_ZI_DISCONNECT_ALL
{// 0x2930
	/* this+0 */ short PacketType;
};


struct PACKET_ZI_CHANGE_EXPOPTION
{// 0x2931
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GRID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long expOption;
};


struct PACKET_ZI_REQ_MAKE_GUILD
{// 0x2937
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ unsigned long AID;
	/* this+14 */ char GName[24];
	/* this+38 */ char MName[24];
	/* this+62 */ char AccountName[24];
};


struct PACKET_ZI_REGISTER_GUILD_EMBLEM_IMG
{// 0x293E
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ unsigned long GID;
};


struct PACKET_IZ_GET_GUILD_EMBLEM_IMG
{// 0x293F
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ short emblemVersion;
	/* this+16 */ BYTE emblemData[];
};


struct PACKET_ZI_REQ_BAN_GUILD
{// 0x2948
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
	/* this+14 */ unsigned long MyGID;
	/* this+18 */ char AccountName[24];
	/* this+42 */ char reasonDesc[40];
};


struct PACKET_IZ_GUILDINFO_TOD
{// 0x2956
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ GUILDINFO Data;
};


struct PACKET_IZ_GUILD_NOTICE
{// 0x2960
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ char subject[60];
	/* this+66 */ char notice[120];
};


struct PACKET_ZI_REQ_HOSTILE_GUILD
{// 0x2964
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long OtherGDID;
	/* this+10 */ unsigned long MyAID;
};


struct PACKET_IZ_DELETE_RELATED_GUILD
{// 0x2969
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long OpponentGDID;
	/* this+10 */ int Relation;
};


struct PACKET_ZI_GUILD_CHAT
{// 0x296B
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long GDID;
	/* this+8 */ char Text[]; //dynamic
};


struct PACKET_IZ_GUILD_CHAT
{// 0x296C
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long GDID;
	/* this+8 */ char Text[]; //dynamic
};


struct PACKET_ZI_ADD_EXP
{// 0x296D
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int Exp;
};


struct PACKET_ZI_GUILD_ZENY
{// 0x2976
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
	/* this+14 */ char mapName[16];
	/* this+30 */ unsigned char type;
	/* this+31 */ int zeny;
};


struct PACKET_IZ_GUILD_ZENY
{// 0x2977
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long GID;
	/* this+14 */ char mapName[16];
	/* this+30 */ unsigned char type;
	/* this+31 */ int zeny;
	/* this+35 */ unsigned char ret;
};


// made up
struct PACKET_ZH_REQ_REMAINTIME
{// 0x297E
	short PacketType;
	unsigned long AID;
};


struct PACKET_IZ_GUILD_NOTIFYSKILLDATA
{// 0x2984
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GDID;
	/* this+ 8 */ int isForceSend;
	/* this+12 */ int SkillPoint;
	/* this+16 */ struct { unsigned short id; unsigned short lv; } Skill[];
};


struct PACKET_ZI_MOVE
{// 0x2988 (10632)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int MoveType; // enum SPECIALMOVETYPE
	/* this+ 6 */ unsigned long SrcID;
	/* this+10 */ int DestX;
	/* this+14 */ int DestY;
	/* this+18 */ char DestName[24];
};


struct PACKET_IZ_MOVE
{// 0x2989 (10633)
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int MoveType; // enum SPECIALMOVETYPE
	/* this+ 6 */ unsigned long SrcID;
	/* this+10 */ unsigned long DestID;
	/* this+14 */ int DestX;
	/* this+18 */ int DestY;
	/* this+22 */ char MapName[16];
	/* this+38 */ char CharName[24];
};


struct PACKET_ZI_MAKE_GROUP2
{// 0x298E
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ char groupName[24];
	/* this+34 */ unsigned char ItemPickupRule;
	/* this+35 */ unsigned char ItemDivisionRule;
};


struct PACKET_IZ_ADD_MEMBER_TO_GROUP2
{// 0x298F
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long receiverAID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long Role;
	/* this+14 */ unsigned char state;
	/* this+15 */ char groupName[24];
	/* this+39 */ char characterName[24];
	/* this+63 */ char mapName[16];
	/* this+79 */ unsigned char ItemPickupRule;
	/* this+80 */ unsigned char ItemDivisionRule;
};


struct PACKET_ZI_VERSION
{// 0x2992
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long Version;
};


struct PACKET_ZI_CHANGE_EXPOPTION2
{// 0x2993
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GRID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long expOption;
};


struct PACKET_IZ_NOTIFY_MAKERRANK
{// 0x29A1
	/* this+  0 */ short PacketType;
	/* this+  2 */ short type;
	/* this+  4 */ unsigned long GID[10];
	/* this+ 44 */ char charname[10][24];
	/* this+284 */ int point[10];
};


struct PACKET_ZI_MAIL_SEND
{// 0x29AB
	/* this+  0 */ short PacketType; 
	/* this+  2 */ unsigned short PacketLength;
	/* this+  4 */ unsigned long AID;
	/* this+  8 */ unsigned long GID;
	/* this+ 12 */ char Header[40];
	/* this+ 52 */ char ItemInfo[40];
	/* this+ 92 */ char ItemLen;
	/* this+ 93 */ unsigned long Money;
	/* this+ 97 */ char SendName[24];
	/* this+121 */ unsigned long SendAID;
};


struct PACKET_ZI_EPISODE_VERSION
{// 0x29AE
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long Episode_Ver;
	/* this+6 */ unsigned long Minor_Ver;
};


struct PACKET_HZ_PING
{// 0x29BB
	/* this+0 */ short PacketType;
};


struct PACKET_IZ_INSTANTMAP_CREATE_REQ
{// 0x29BE
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned int hRequestN2Obj;
	/* this+ 6 */ char mapName[16];
	/* this+22 */ int mapID;
	/* this+26 */ int mapType;
};


struct PACKET_IZ_INSTANTMAP_PLAYER_ENTER
{// 0x29C3
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned int hRequestN2Obj;
	/* this+ 6 */ int ZSID;
	/* this+10 */ char mapName[16];
	/* this+26 */ int mapID;
	/* this+30 */ int mapType;
	/* this+34 */ bool bPlayerEnter;
};


struct PACKET_ZI_INSTANTMAP_ERROR
{// 0x29C4
	enum enumWhy
	{
		WHY_UNKNOWN = 0
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned int hRequestN2Obj;
	/* this+ 6 */ int mapID;
	/* this+10 */ enum PACKET_ZI_INSTANTMAP_ERROR::enumWhy why;
};


struct PACKET_IZ_INSTNATMAP_DESTROY
{// 0x29C5
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char mapName[16];
	/* this+18 */ int mapID;
};


struct PACKET_ZI_PING
{// 0x29C6
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned int UsedKBytesMemory;
	/* this+6 */ unsigned int NumTotalNPC;
};


struct PACKET_ZI_INSTANTMAP_ALLOW
{// 0x29C7
	enum enumWhy
	{
		WHY_ZSVR_SETTING  = 0,
		WHY_AGITWAR_START = 1,
		WHY_AGITWAR_END   = 2,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ enum PACKET_ZI_INSTANTMAP_ALLOW::enumWhy why;
	/* this+6 */ bool bAllow;
};


struct PACKET_XX_CONNECT
{// 0x29C8
	/* this+0 */ short PacketType;
};


struct PACKET_XX_DISCONNECT
{// 0x29C9
	/* this+0 */ short PacketType;
};


struct PACKET_IZ_PARTY_BROADCAST
{// ????
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned long AID;
};


struct PACKET_IZ_MEMORIALDUNGEON_MSG : public PACKET_IZ_PARTY_BROADCAST
{// 0x29CA
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

	/* this+ 0 */ //PACKET_IZ_PARTY_BROADCAST baseclass_0;
	/* this+10 */ enum PACKET_IZ_MEMORIALDUNGEON_MSG::enumNotify Notify;
	/* this+14 */ char MemorialDungeonName[60+1];
};


struct PACKET_ZI_PARTY_JOIN_REQ
{// 0x29CC
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long senderAID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ char TargetCharName[24];
};


struct PACKET_IZ_PARTY_JOIN_REQ_ACK
{// 0x29CD
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long requestAID;
	/* this+ 6 */ char characterName[24];
	/* this+30 */ enum PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer answer;
};


struct PACKET_IZ_PARTY_JOIN_REQ
{// 0x29CE
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long targetAID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ char groupName[24];
};


struct PACKET_ZI_PARTY_JOIN_REQ_ACK
{// 0x29CF
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long targetAID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ enum PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer answer;
};


struct PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO : public PACKET_IZ_PARTY_BROADCAST
{// 0x29D1
	/* this+ 0 */ //PACKET_IZ_PARTY_BROADCAST baseclass_0;
	/* this+10 */ char MemorialDungeonName[60+1];
	/* this+71 */ short PriorityOrderNum;
};


struct PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY : public PACKET_IZ_PARTY_BROADCAST
{// 0x29D2
	/* this+ 0 */ //PACKET_IZ_PARTY_BROADCAST baseclass_0;
	/* this+10 */ short PriorityOrderNum;
};


struct PACKET_IZ_MEMORIALDUNGEON_INFO : public PACKET_IZ_PARTY_BROADCAST
{// 0x29D3
	/* this+ 0 */ //PACKET_IZ_PARTY_BROADCAST baseclass_0;
	/* this+10 */ char MemorialDungeonName[60+1];
	/* this+71 */ unsigned long DestroyDate;
	/* this+75 */ unsigned long EnterTimeOutDate;
};


struct PACKET_IZ_MEMORIALDUNGEON_NOTIFY : public PACKET_IZ_PARTY_BROADCAST
{// 0x29D4
	/* this+ 0 */ //PACKET_IZ_PARTY_BROADCAST baseclass_0;
	/* this+10 */ enum PACKET_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE Type;
	/* this+14 */ unsigned long EnterLimitDate;
};


struct PACKET_IZ_MEMORIALDUNGEON_SYNC
{// 0x29D6
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
	/* this+103 */ enum PACKET_IZ_MEMORIALDUNGEON_SYNC::enumEVENT Event;
};


struct PACKET_IZ_MEMORIALDUNGEON_VISA
{// 0x29D8
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ unsigned long ZSID;
	/* this+14 */ char mapName[16];
	/* this+30 */ int x;
	/* this+34 */ int y;
};


struct PACKET_IZ_MEMORIALDUNGEON_COMMAND
{// 0x29D9
	enum enumCOMMAND
	{
		COMMAND_PLAYER_KICK = 0,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned long AID;
	/* this+10 */ enum PACKET_IZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND Command;
};


struct PACKET_IZ_LEAVE_GROUP
{// 0x29DB
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned long GID;
};


struct PACKET_IZ_MEMORIALDUNGEON_OPENSTATE
{// 0x29DD
	/* this+0 */ short PacketType;
	/* this+2 */ bool bOpen;
	/* this+3 */ unsigned long ToGID;
	/* this+7 */ unsigned long ToAID;
};


struct PACKET_HZ_CHAR_NAME_CHANGED
{// 0x29E7
	/* this+0 */ short sPacketType;
	/* this+2 */ unsigned long dwGID;
};


struct PACKET_ZI_GROUPINFO_CHANGE_V2
{// 0x29E8
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GRID;
	/* this+ 6 */ unsigned long MasterAID;
	/* this+10 */ int FamilyGroup;
	/* this+14 */ unsigned long expOption;
	/* this+18 */ unsigned char ItemPickupRule;
	/* this+19 */ unsigned char ItemDivisionRule;
};


struct PACKET_IZ_REQ_GROUPINFO_CHANGE_V2
{// 0x29E9
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GRID;
	/* this+10 */ unsigned long expOption;
	/* this+14 */ unsigned char ItemPickupRule;
	/* this+15 */ unsigned char ItemDivisionRule;
};


struct PACKET_ZH_CASTLE_MAP_MOVE
{// 0x29EB
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
};


struct PACKET_ZI_SEEK_PARTY
{// 0x29EE
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char Name[24];
	/* this+26 */ unsigned long Job;
	/* this+30 */ unsigned long Level;
	/* this+34 */ char mapName[16];
	/* this+50 */ unsigned long Option;
};


#pragma pack(pop)
