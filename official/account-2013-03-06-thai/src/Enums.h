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
	CLIENTTYPE_CHILE             = 30,
	CLIENTTYPE_FRANCE            = 31,
	CLIENTTYPE_VIETNAM_PK        = 32,
	CLIENTTYPE_VIETNAM_SAKRAY    = 33,
	CLIENTTYPE_INDONESIA_PK      = 34,
	CLIENTTYPE_UAE               = 35,
	MAX_CLIENTTYPE               = 36
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
	REFUSE_NOT_CHANGED_PASSWD               = 16,
	REFUSE_BLOCK_INVALID                    = 17,
	REFUSE_WARNING                          = 18,
	REFUSE_NOT_OTP_USER_INFO                = 19,
	REFUSE_OTP_AUTH_FAILED                  = 20,
	REFUSE_SSO_AUTH_FAILED                  = 21,
	REFUSE_NOT_ALLOWED_IP_ON_TESTING        = 22,
	REFUSE_OVER_BANDWIDTH                   = 23,
	REFUSE_OVER_USERLIMIT                   = 24,
	REFUSE_UNDER_RESTRICTION                = 25,
	REFUSE_BY_OUTER_SERVER                  = 26,
	REFUSE_BY_UNIQUESERVER_CONNECTION       = 27,
	REFUSE_BY_AUTHSERVER_CONNECTION         = 28,
	REFUSE_BY_BILLSERVER_CONNECTION         = 29,
	REFUSE_BY_AUTH_WAITING                  = 30,
	REFUSE_REMAINED_INFOMATION_USER         = 31,
	REFUSE_DB_ERROR                         = 32,
	REFUSE_DELETED_ACCOUNT                  = 99,
	REFUSE_ALREADY_CONNECT                  = 100,
	REFUSE_TEMP_BAN_HACKING_INVESTIGATION   = 101,
	REFUSE_TEMP_BAN_BUG_INVESTIGATION       = 102,
	REFUSE_TEMP_BAN_DELETING_CHAR           = 103,
	REFUSE_TEMP_BAN_DELETING_SPOUSE_CHAR    = 104,
	REFUSE_USER_PHONE_BLOCK                 = 105,
	ACCEPT_LOGIN_USER_PHONE_BLOCK           = 106,
	ACCEPT_LOGIN_CHILD                      = 107,
	REFUSE_IS_NOT_FREEUSER                  = 108,
	REFUSE_INVALID_ONETIMELIMIT             = 109,
	REFUSE_CHANGE_PASSWD_FORCE              = 110,
	REFUSE_OUTOFDATE_PASSWORD               = 111,
	REFUSE_NOT_ACTIVE_USER                  = 112,
	REFUSE_DISCONNECT_KEEP_TIME             = 113,
	REFUSE_BILLING_SERVER_ERROR             = 114,
	REFUSE_WEB_AUTH_BILL_ERROR              = 115,
	REFUSE_WEB_AUTH_FAILED                  = 116,
	REFUSE_MOBILE_OTP_AUTH_FAILED           = 117,
	REFUSE_NOT_CHANGE_ACCOUNTID             = 240,
	REFUSE_NOT_CHANGE_CHARACTERID           = 241,
	REFUSE_SSO_AUTH_BLOCK_USER              = 5012,
	REFUSE_SSO_AUTH_GAME_APPLY              = 5013,
	REFUSE_SSO_AUTH_INVALID_GAMENUM         = 5014,
	REFUSE_SSO_AUTH_INVALID_USER            = 5015,
	REFUSE_SSO_AUTH_OTHERS                  = 5016,
	REFUSE_SSO_AUTH_INVALID_AGE             = 5017,
	REFUSE_SSO_AUTH_INVALID_MACADDRESS      = 5018,
	REFUSE_SSO_AUTH_BLOCK_ETERNAL           = 5062,
	REFUSE_SSO_AUTH_BLOCK_ACCOUNT_STEAL     = 5063,
	REFUSE_SSO_AUTH_BLOCK_BUG_INVESTIGATION = 5064,
	REFUSE_SSO_NOT_PAY_USER                 = 5050,
	REFUSE_SSO_ALREADY_LOGIN_USER           = 5051,
	REFUSE_SSO_CURRENT_USED_USER            = 5052,
	REFUSE_SSO_OTHER_1                      = 5053,
	REFUSE_SSO_DROP_USER                    = 5054,
	REFUSE_SSO_NOTHING_USER                 = 5055,
	REFUSE_SSO_OTHER_2                      = 5056,
	REFUSE_SSO_WRONG_RATETYPE_1             = 5057,
	REFUSE_SSO_EXTENSION_PCBANG_TIME        = 5058,
	REFUSE_SSO_WRONG_RATETYPE_2             = 5059,
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
	BAN_GRAVITY_MEM_AGREE                    = 103,
	BAN_GAME_MEM_AGREE                       = 104,
	BAN_HAN_VALID                            = 105,
	BAN_PC_IP_LIMIT_ACCESS                   = 106,
	BAN_OVER_CHARACTER_LIST                  = 107,
	BAN_IP_BLOCK                             = 108,
	BAN_INVALID_PWD_CNT                      = 109,
	BAN_NOT_ALLOWED_JOBCLASS                 = 110,
	BAN_MAX_CONNECT_USER_COUNT               = 111,
	BAN_INVALID_SECOND_PWD                   = 112,
	BAN_SHUTDOWN_TEENAGER                    = 113,
	BAN_BILLING_SERVER_ERROR                 = 114,
	BAN_PLANNED_TIME_SHUTDOWN                = 115,
	BAN_END                                  = 255,
};
