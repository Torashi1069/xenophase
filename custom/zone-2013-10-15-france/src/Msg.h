#pragma once


enum enumMSGTYPE
{
	MSG_REQVAR                             = 0,
	MSG_REQITEMCOUNT                       = 1,
	MSG_REQREFINELEVEL                     = 2,
	ITZMSG_INCREASEHP                      = 3,
	ZITMSG_ANSWER_CHARNAME                 = 4,
	NPC2ZMSG_PACKET                        = 5,
	NPC2ZMSG_PACKETDATA                    = 6,
	NPC2ZMSG_CALLMONSTER                   = 7,
	NPC2ZMSG_ADDSKILL                      = 8,
	NPC2ZMSG_SETARENAEVENTSIZE             = 9,
	NPC2ZMSG_MAKEWAITINGROOM               = 10,
	NPC2ZMSG_ENABLEARENA                   = 11,
	NPC2ZMSG_DISABLEARENA                  = 12,
	NPC2ZMSG_WARPWAITINGPCTOARENA          = 13,
	NPC2ZMSG_RESETMYMOB                    = 14,
	NPC2ZMSG_WARPALLPCINTHEMAP             = 15,
	NPC2ZMSG_BROADCASTINTHEMAP             = 16,
	NPC2ZMSG_ENABLENPC                     = 17,
	NPC2ZMSG_DISABLENPC                    = 18,
	NPC2ZMSG_CALLNPC                       = 19,
	NPC2ZMSG_OPENDIALOG                    = 20,
	NPC2ZMSG_MAPMOVE                       = 21,
	NPC2ZMSG_DISABLEITEMMOVE               = 22,
	NPC2ZMSG_ENABLEITEMMOVE                = 23,
	NPC2ZMSG_SUCCESSREFITEM                = 24,
	NPC2ZMSG_FAILEDREFITEM                 = 25,
	NPC2ZMSG_NPCLOG2CLIENT                 = 26,
	NPC2ZMSG_SETEFFECTSTATE                = 27,
	NPC2ZMSG_ARENAROOM_SETFEEZENY          = 28,
	NPC2ZMSG_ARENAROOM_SETFEEITEM          = 29,
	NPC2ZMSG_ARENAROOM_SETLEVEL            = 30,
	NPC2ZMSG_ARENAROOM_SETEXJOB            = 31,
	NPC2ZMSG_CHANGE_MONEY                  = 32,
	NPC2ZMSG_RESET_STAT                    = 33,
	NPC2ZMSG_RESET_SKILL                   = 34,
	ZNPC2MSG_PACKET                        = 35,
	ZNPC2MSG_VARIABLEPACKET                = 36,
	ZNPC2MSG_CALLEVENT                     = 37,
	NPC2ZMSG_SHOWIMAGE                     = 38,
	NPC2ZMSG_CHANGEPALLETE                 = 39,
	NPC2ZMSG_COMPASS                       = 40,
	NPC2ZMSG_CHECKPOINT                    = 41,
	NPC2ZMSG_EXCHANGEITEM                  = 42,
	NPC2ZMSG_WAITDIALOG                    = 43,
	NPC2ZMSG_CLOSEDIALOG                   = 44,
	NPC2ZMSG_SETITEM                       = 45,
	NPC2ZMSG_CHANGEITEM                    = 46,
	NPC2ZMSG_HEAL                          = 47,
	NPC2ZMSG_CHANGEVAR                     = 48,
	NPC2ZMSG_DLGWRITE                      = 49,
	NPC2ZMSG_NUDE                          = 50,
	NPC2ZMSG_CARTON                        = 51,
	NPC2ZMSG_STORE                         = 52,
	NPC2ZMSG_MENU                          = 53,
	NPC2ZMSG_TRADERCMD                     = 54,
	NPC2ZMSG_GUIDENPC_CMD                  = 55,
	NPC2ZMSG_REGMAPMOVE                    = 56,
	NPC2ZMSG_SHOWDIGIT                     = 57,
	NPC2ZMSG_ENABLESKILL                   = 58,
	NPC2ZMSG_DISABLESKILL                  = 59,
	NPC2ZMSG_BROADCASTINTHEMAP2            = 60,
	NPC2ZMSG_BROADCASTINSERVER             = 61,
	NPC2ZMSG_SOUND                         = 62,
	NPC2ZMSG_DLGWRITESTR                   = 63,
	NPC2ZMSG_CHANGE_EXP                    = 64,
	NPC2ZMSG_USESKILL_TO_PC                = 65,
	NPC2ZMSG_CASHTRADERCMD                 = 66,
	NPC2ZMSG_CASHINFO                      = 67,
	ZNPC2MSG_CLEARFIRSTEVENT               = 68,
	ZNPC2MSG_UPDATE_PCCONTECTLIST          = 69,
	NPC2ZMSG_MOVENPC_CMD                   = 70,
	NPC2ZMSG_RELOADMOBILE_EVENT            = 71,
	NPC2ZMSG_QUEST_EVENTITEM               = 72,
	NPC2ZMSG_QUEST_SETITEMQUEST            = 73,
	NPC2ZMSG_QUEST_SETEVENTITEMQUEST       = 74,
	NPC2ZMSG_QUEST_SETQUEST                = 75,
	NPC2ZMSG_QUEST_CHECKQUEST              = 76,
	NPC2ZMSG_QUEST_COMPLATEQUEST           = 77,
	NPC2ZMSG_RELOADMOBILE_EVENT_EXCULUSIVE = 78,
	NPC2ZMSG_MYMOBSKILLUSE                 = 79,
	NPC2ZMSG_WIDEMOBSKILLUSE               = 80,
	NPC2ZMSG_WIDEMOBSKILLUSE2              = 81,
	NPC2ZMSG_GETITEMSOCKET                 = 82,
	NPC2ZMSG_GETNONSLOTITEMSOCKET          = 83,
	ZNPC2ZMSG_CLICK_MOBTOMB                = 84,
	NPC2ZMSG_GETNONSLOTITEMSOCKET2         = 85,
	NPC2ZMSG_OPENDIALOG2                   = 86,
	NPC2ZMSG_WAITDIALOG2                   = 87,
	NPC2ZMSG_OPEN_TRADE_BUY                = 88,
	NPC2ZMSG_OPEN_TRADE_SELL               = 89,
	NPC2ZMSG_OPEN_MARKET                   = 90,
	NPC2ZMSG_MARKET_PURCHASE               = 91,
};


class CMsg
{
public:
	unsigned long GetMsgID()
	{
		return m_MID;
	}

	void SetMsgID(unsigned long msgID)
	{
		m_MID = msgID;
	}

public:
	/* this+ 0 */ int par1;
	/* this+ 4 */ int par2;
	/* this+ 8 */ int par3;
	/* this+12 */ int par4;
	/* this+16 */ int par5;

protected:
	/* this+20 */ unsigned long m_MID;
};


class CITZMsg : public CMsg
{
public:
	CITZMsg()
	{
		this->par1 = 0;
		this->par2 = 0;
		this->par3 = 0;
		this->par4 = 0;
		this->par5 = 0;
	}

public:
	/* this+ 0 */ //CMsg baseclass_0;
	/* this+24 */ int m_ITID;
};


class CZNPC2Msg : public CMsg
{
public:
	/* this+0 */ //CMsg baseclass_0;
};


class CNPC2ZMsg : public CMsg
{
public:
	/* this+0 */ //CMsg baseclass_0;
};
