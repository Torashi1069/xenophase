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


enum enumCLIENTTYPE
{
	CLIENTTYPE_KOREAN            = 0,
	CLIENTTYPE_ENGLISH           = 1,
	CLIENTTYPE_SAKRAY            = 2,
	CLIENTTYPE_JAPAN             = 3,
	CLIENTTYPE_CHINA             = 4,
	CLIENTTYPE_TAIWAN            = 5,
	CLIENTTYPE_HONGKONG          = 6,
	CLIENTTYPE_THAI              = 7,
	CLIENTTYPE_LOCAL             = 8,
	CLIENTTYPE_JAPAN_SAKRAY      = 9,
	CLIENTTYPE_THAI_SAKRAY       = 10,
	CLIENTTYPE_TAIWAN_SAKRAY     = 11,
	CLIENTTYPE_INDONESIA         = 12,
	CLIENTTYPE_INDONESIA_SAKRAY  = 13,
	CLIENTTYPE_ENGLISH_SAKRAY    = 14,
	CLIENTTYPE_PHILIPPINE        = 15,
	CLIENTTYPE_MALAYSIA          = 16,
	CLIENTTYPE_SINGAPORE         = 17,
	CLIENTTYPE_PHILIPPINE_SAKRAY = 18,
	CLIENTTYPE_THAI_FREE         = 19,
	CLIENTTYPE_GERMANY           = 20,
	CLIENTTYPE_INDIA             = 21,
	CLIENTTYPE_BRAZIL            = 22,
	CLIENTTYPE_AUSTRALIA         = 23,
	CLIENTTYPE_KOREAN_PK         = 24,
	CLIENTTYPE_RUSSIA            = 25,
	CLIENTTYPE_VIETNAM           = 26,
	CLIENTTYPE_PHILIPPINE_PK     = 27,
	CLIENTTYPE_JAPAN_PK          = 28,
	CLIENTTYPE_THAI_PK           = 29,
	MAX_CLIENTTYPE               = 30,
};


enum SEX_TYPE
{
	SEX_FEMALE = 0,
	SEX_MALE   = 1,
};


enum enumREFUSETYPE
{
	REFUSE_INVALID_ID                       = 0,
	REFUSE_INVALID_PASSWD                   = 1,
	REFUSE_ID_EXPIRED                       = 2,
	ACCEPT_ID_PASSWD                        = 3,
	REFUSE_NOT_CONFIRMED                    = 4,
	REFUSE_INVALID_VERSION                  = 5,
	REFUSE_BLOCK_TEMPORARY                  = 6,
	REFUSE_BILLING_NOT_READY                = 7,
	REFUSE_NONSAKRAY_ID_BLOCKED             = 8,
	REFUSE_BAN_BY_DBA                       = 9,
	REFUSE_EMAIL_NOT_CONFIRMED              = 10,
	REFUSE_BAN_BY_GM                        = 11,
	REFUSE_TEMP_BAN_FOR_DBWORK              = 12,
	REFUSE_SELF_LOCK                        = 13,
	REFUSE_NOT_PERMITTED_GROUP              = 14,
	REFUSE_WAIT_FOR_SAKRAY_ACTIVE           = 15,
	REFUSE_DELETED_ACCOUNT                  = 99,
	REFUSE_ALREADY_CONNECT                  = 100,
	REFUSE_TEMP_BAN_HACKING_INVESTIGATION   = 101,
	REFUSE_TEMP_BAN_BUG_INVESTIGATION       = 102,
	REFUSE_TEMP_BAN_DELETING_CHAR           = 103,
	REFUSE_TEMP_BAN_DELETING_SPOUSE_CHAR    = 104,
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
};
