#pragma once


enum MSGSTRINGID
{
	MSI_ACCESS_DENIED                             = 9,
	MSI_CHARACTER_NAME_ALREADY_EXISTS             = 10,
	MSI_CHARACTER_CREATION_DENIED                 = 11,
	MSI_CANNOT_DELETE_CHARACTER                   = 12,
	MSI_FRIEND                                    = 102,
	MSI_PLEASE_BE_PATIENT                         = 121,
	MSI_WAITING_RESPONSE_FROM_SERVER              = 122,
	MSI_ID_MISMATCH                               = 208,
	MSI_LIMIT_AGE                                 = 298,
	MSI_CANNOT_DELETE_CHARACTER_EMAIL             = 301,
	MSI_CANNOT_DELETE_CHARACTER_PEOPLE_REG_NUMBER = 303,
	MSI_CANT_MAKE_CHAT_ROOM                       = 661,
	MSI_ASK_PNGAMEROOM                            = 691,
	MSI_ID_WARNING                                = 917,
	MSI_ID_WARNING_GUILD                          = 919,
	MSI_LIMIT_CHAR_DELETE                         = 1272,
	MSI_VET_3HOUR                                 = 1403,
	MSI_VET_5HOUR                                 = 1404,
	MSI_FR_ERR_MKCHAR_INVALID_SLOT                = 1355,
	MSI_FR_ERR_DELCHAR_INVALID_SLOT               = 1356,
	MSI_NEED_PREMIUM_SERVICE                      = 1363,
	MSI_WHO_IS                                    = 1604,
	MSI_NOTIFY_WHO                                = 1612,
	MSI_NOTIFY_TARGET_WHO                         = 1624,
	MSI_NOTIFY_SKILL_TO_TARGET                    = 1625,
	MSI_LAST                                      = 1801,
};


struct IdMsgString
{
	/* this+0 */ MSGSTRINGID id;
	/* this+4 */ const char* msg;
};


const char* __cdecl MsgStr(MSGSTRINGID id);
const char* __cdecl MsgStrToCompare(MSGSTRINGID id);
bool __cdecl IsEventAID(unsigned long Aid);
const char* __cdecl GetMsgString(MSGSTRINGID id);
void __cdecl InitMsgStrings();
const char* __cdecl UIBmp(const char* uiBmpName);
char* __cdecl DataTxtDecode(char* str);
