#pragma once


enum enumSERVERTYPE
{
	SERVERTYPE_NONE             = 0,
	SERVERTYPE_ACCOUNT          = 1,
	SERVERTYPE_CHARACTER        = 2,
	SERVERTYPE_ZONE             = 3,
	SERVERTYPE_INTER            = 4,
	SERVERTYPE_NPC              = 5,
	SERVERTYPE_ENGLISHCHARACTER = 6,
	SERVERTYPE_MONITOR          = 7,
	SERVERTYPE_BILLING          = 8,
	SERVERTYPE_GUM              = 9,
};


enum enumBANTYPE
{
	BAN_UNFAIR                               = 0,
	BAN_SERVER_SHUTDOWN                      = 1,
	BAN_ANOTHER_LOGIN                        = 2,
	BAN_DETECTED_SPEEDHACK                   = 3,
	BAN_PC_OVERFLOW                          = 4,
	BAN_UNDER_AGE                            = 5,
	BAN_NOT_SETTLED                          = 6,
	BAN_ACCOUNT_BUSY                         = 7,
	BAN_INFORMATION_REMAINED                 = 8,
	BAN_IP_OVERFLOW                          = 9,
	BAN_PAY_OUT                              = 10,
	BAN_PAY_SUSPEND                          = 11,
	BAN_PAY_CHANGE                           = 12,
	BAN_PAY_WRONGIP                          = 13,
	BAN_PAY_PNGAMEROOM                       = 14,
	BAN_OP_FORCE                             = 15,
	BAN_JAPAN_REFUSE1                        = 16,
	BAN_JAPAN_REFUSE2                        = 17,
	BAN_INFORMATION_REMAINED_ANOTHER_ACCOUNT = 18,
	BAN_PC_IP_UNFAIR                         = 100,
	BAN_PC_IP_COUNT_ALL                      = 101,
	BAN_PC_IP_COUNT                          = 102,
	BAN_END                                  = 255,
};


enum enumDISCONNECTEDTYPE
{
	NORMAL_DISCONNECT = 0,
	MOVE_SERVER       = 1,
	RESTART_HSERVER   = 2,
	HZMOVE            = 3,
	HAMOVE            = 4,
};


enum enumSEXTYPE
{
	SEX_FEMALE = 0,
	SEX_MALE   = 1,
};


enum enumMAPTYPE
{
	MAPTYPE_VILLAGE               = 0,
	MAPTYPE_VILLAGE_IN            = 1,
	MAPTYPE_FIELD                 = 2,
	MAPTYPE_DUNGEON               = 3,
	MAPTYPE_ARENA                 = 4,
	MAPTYPE_PENALTY_FREEPKZONE    = 5,
	MAPTYPE_NOPENALTY_FREEPKZONE  = 6,
	MAPTYPE_EVENT_GUILDWAR        = 7,
	MAPTYPE_AGIT                  = 8,
	MAPTYPE_DUNGEON2              = 9,
	MAPTYPE_DUNGEON3              = 10,
	MAPTYPE_PKSERVER              = 11,
	MAPTYPE_PVPSERVER             = 12,
	MAPTYPE_DENYSKILL             = 13,
	MAPTYPE_TURBOTRACK            = 14,
	MAPTYPE_JAIL                  = 15,
	MAPTYPE_MONSTERTRACK          = 16,
	MAPTYPE_PORINGBATTLE          = 17,
	MAPTYPE_AGIT_SIEGEV15         = 18,
	MAPTYPE_BATTLEFIELD           = 19,
	MAPTYPE_PVP_TOURNAMENT        = 20,
	MAPTYPE_UNUSED                = 29,
	MAPTYPE_LAST                  = 30,
};
