#pragma once
#include "Struct.h"
class CBitmapRes;
class CDC; // 3dLib/Renderer_h


struct SnapInfo
{
	/* this+0 */ int points[3];
};


class CSnapInfo
{
public:
	CSnapInfo();
//	CSnapInfo(int, int, int, int);
	void SetInfo(int x, int y, int w, int h);
	void Reverse();
	void GetDeltaSnap(CSnapInfo* snapInfo, int& dx, int& dy);
	bool IsOverLapped(int s1, int d1, int s2, int d2);

public:
	/* this+0 */ SnapInfo m_info[4];

private:
	static hook_func<void (CSnapInfo::*)(CSnapInfo* snapInfo, int& dx, int& dy)> CSnapInfo::_GetDeltaSnap;
};


int __cdecl UIX(int x);
int __cdecl UIY(int y);
int __cdecl UICY(int y);
void __cdecl CutString(const char* msg, mystd::vector<mystd::string>& strings, int maxNumCharLine);
void __cdecl CutStringWithColor(const char* msg, mystd::vector<mystd::string>& strings, int maxNumCharLine, bool readCR);


/// @see UIWindow::m_id
enum UIID
{
	ID_NOTHING             = 93,
	ID_OK                  = 94,
	ID_CANCEL              = 95,
	ID_BASE                = 110,
	ID_CLOSE               = 111,
	ID_MINI                = 112,
	ID_MAKE                = 113,
	ID_SLOT                = 114,
	ID_DELETE              = 121,
	ID_CHECK               = 123,
	ID_PLUS                = 126,
	ID_MINUS               = 127,
	ID_EQUIP_OPTION_OFF    = 157,
	ID_EQUIP_OPTION_OPEN   = 158,
	ID_CARDITEM            = 159,
	ID_CHANGE_GUILD_EMBLEM = 187,
};


/// @see UIWindow::SendMsg()
enum UIMESSAGE
{
	UM_DEFPUSH                    = 0,
	UM_CANCELPUSH                 = 1,
	UM_TOGGLEPUSH                 = 2,
	UM_PAGEUPPUSH                 = 3,
	UM_PAGEDOWNPUSH               = 4,
//	UM_CLOSE                      = 5,
	UM_COMMAND                    = 6,
	UM_SCROLLVERT                 = 7,
	UM_SCROLLHORZ                 = 8,
	UM_SCROLLVERTPAGEUP           = 9,
	UM_SCROLLVERTPAGEDOWN         = 10,
//	UM_SCROLLHORZPAGEUP           = 11,
//	UM_SCROLLHORZPAGEDOWN         = 12,
	UM_SETSTATE                   = 13,
	UM_RESIZE                     = 14,
	UM_CHANGESTATUS               = 15,
	UM_OPENCHATWND                = 16,
	UM_LOADINGPERCENT             = 17,
	UM_UPPUSH                     = 18,
	UM_DOWNPUSH                   = 19,
//	UM_LEFTPUSH                   = 20,
//	UM_RIGHTPUSH                  = 21,
//	UM_TAB                        = 22,
	UM_REFRESHITEM                = 23,
	UM_ITEMEXPLANATION            = 24,
//	UM_ENABLENEXTBUTTON           = 25,
//	UM_SETSAYDIALOG               = 26,
//	UM_SETCHOOSE                  = 27,
//	UM_SETNAID                    = 28,
	UM_SETTEXT                    = 29,
	UM_ADJUSTSIZE                 = 30,
	UM_ADDITEM                    = 31,
//	UM_DISABLENEXTBUTTON          = 32,
//	UM_DELETE                     = 33,
	UM_SETINFO                    = 34,
//	UM_REFRESHBUTTON              = 35,
//	UM_SETTITLE                   = 36,
	UM_ADDCHAT                    = 37,
//	UM_DROP                       = 38,
	UM_COMBOBOX_SELECTED          = 39,
	UM_SETCURITEM                 = 40,
	UM_USE_SHORTEN_ITEM           = 41,
//	UM_SET_COLOR                  = 42,
//	UM_CLEARMEMBER                = 43,
//	UM_ADDMEMBER                  = 44,
//	UM_MEMBER_EXIT                = 45,
//	UM_ROLE_CHANGE                = 46,
//	UM_SETROOMID                  = 47,
	UM_MENU_SELECTED              = 48,
	UM_MAKEMENU                   = 49,
	UM_SET_EXCHANGE_CHAR_NAME     = 50,
//	UM_MYDRAGCLOSED               = 51,
//	UM_OTHERDRAGCLOSED            = 52,
//	UM_SETINFO2                   = 53,
	UM_GET_EDIT_FOCUS             = 54,
//	UM_SETCOUNTINFO               = 55,
//	UM_SET_JOIN_PARTY_MSG         = 56,
//	UM_CHANGEMSG                  = 57,
//	UM_USESKILL                   = 58,
//	UM_SETSKID                    = 59,
	UM_REFRESH                    = 60,
//	UM_SKILLDESCRIBE              = 61,
//	UM_CARDITEMILLUSTRATE         = 62,
//	UM_ENABLECLOSEBUTTON          = 63,
//	UM_PARAM                      = 64,
	UM_IME_SET_CANDIDATE          = 65,
//	UM_IME_SET_COMPOSITION_STRING = 66,
//	UM_SETCOUNTMSG                = 67,
	UM_SET_SKILL_INFO             = 68,
	UM_CHANGE_GUILD_TAB           = 69,
	UM_DELETE_WHISPER_NAME        = 70,
//	UM_MAKE_WHISPER_WINDOW        = 71,
//	UM_ADDBOUNDARY                = 72,
//	UM_SET_JOIN_GUILD_MSG         = 73,
//	UM_SET_ALLY_GUILD_MSG         = 74,
//	UM_CLEAR_ITEM                 = 75,
//	UM_SET_IDENTIFIY_INFO         = 76,
//	UM_SET_CARD_ITEM_INDEX        = 77,
//	UM_SET_BITMAP                 = 78,
//	UM_SET_MONSTER_INFO           = 79,
//	UM_SET_TARGET                 = 80,
//	UM_SET_COUNT                  = 81,
//	UM_SET_BUTTON_FACE            = 82,
	UM_SET_CALLER_WID             = 83,
//	UM_FIRSTSCREEN                = 84,
//	UM_ADD_BUTTON                 = 85,
//	UM_DELETE_BUTTON              = 86,
//	UM_SETPOS                     = 87,
	UM_ENABLE_CANCEL              = 88,
//	UM_ENABLE_EXIT                = 89,
//	UM_SET_COUPLE_MSG             = 90,
//	UM_SET_BABY_MSG               = 91,
//	UM_READBOOK                   = 92,
//	UM_AUTOREAD                   = 93,
//	UM_GETBOOKCONTENTS            = 94,
//	UM_SET_JOIN_FRIEND_MSG        = 95,
//	UM_SET_BABY_MSG2              = 96,
//	UM_TEXT_LBTN_DblClk           = 97,
//	UM_TEXT_LBTN_UP               = 98,
//	UM_TEXT_RBTN_UP               = 99,
//	UM_BMP_LBTN_UP                = 100,
//	UM_BMP_RBTN_UP                = 101,
//	UM_SETID                      = 102,
//	UM_NEWMAIL                    = 103,
//	UM_DECITEM                    = 104,
//	UM_SET_BAR                    = 105,
//	UM_SET_DISABLE                = 106,
//	UM_BEGIN_DRAG_BTN             = 107,
//	UM_MOUSE_HOVER_BTN            = 108,
//	UM_END_DRAG_BTN               = 109,
//	UM_CHANGE_TVITEM_TEXT         = 110,
//	UM_RECEIVE_MSG                = 111,
//	UM_SAVE_CHAT                  = 112,
//	UM_NOT_SAVE_CHAT              = 113,
//	UM_ENDPUSH                    = 114,
//	UM_ADDCHAT2                   = 115,
//	UM_LAST                       = 116,
};
