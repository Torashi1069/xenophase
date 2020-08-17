#pragma once
#pragma pack(push,1)
///////////////////////////////////////


struct PACKET_ZC_PARTY_JOIN_REQ_ACK
{// 709 (0x02C5)
	enum enumAnswer
	{
		ANSWER_ALREADY_OTHERGROUPM    = 0,
		ANSWER_MEMBER_OVERSIZE        = 3,
		ANSWER_JOIN_ACCEPT            = 2,
		ANSWER_JOIN_REFUSE            = 1,
		ANSWER_DUPLICATE              = 4,
		ANSWER_JOINMSG_REFUSE         = 5,
		ANSWER_UNKNOWN_ERROR          = 6,
		ANSWER_UNKNOWN_CHARACTER      = 7,
		ANSWER_INVALID_MAPPROPERTY    = 8,
		ANSWER_INVALID_MAPPROPERTY_ME = 9,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char characterName[24];
	/* this+26 */ enumAnswer answer;
};


struct PACKET_ZC_MEMORIALDUNGEON_NOTIFY
{// 718 (0x02CE)
	enum enumTYPE
	{
		TYPE_NOTIFY                = 0,
		TYPE_DESTROY_LIVE_TIMEOUT  = 1,
		TYPE_DESTROY_ENTER_TIMEOUT = 2,
		TYPE_DESTROY_USER_REQUEST  = 3,
		TYPE_CREATE_FAIL           = 4,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ enumTYPE Type;
	/* this+6 */ unsigned long EnterLimitDate;
};


struct PACKET_CZ_MEMORIALDUNGEON_COMMAND
{// 719 (0x02CF)
	enum enumCOMMAND
	{
		COMMAND_SUBSCRIPTION_CANCEL           = 0,
		COMMAND_MEMORIALDUNGEON_DESTROY       = 1,
		COMMAND_MEMORIALDUNGEON_DESTROY_FORCE = 2,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ enumCOMMAND Command;
};


struct PACKET_ZC_BROADCASTING_SPECIAL_ITEM_OBTAIN
{// 2045 (0x07FD)
	enum { 
		TYPE_BOXITEM = 0,
		TYPE_MONSTER_ITEM = 1,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned char type;
	/* this+5 */ unsigned short ItemID;
	/* this+7 */ //TODO <str1len>.b <str1>.? (type==0:<itid>.w | type==1:<str2len>.b <str2>.?)
};


struct PACKET_ZC_DEFINE_CHECK
{// 2047 (0x07FF)
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ //TODO

	enum
	{
		DEFINE__BROADCASTING_SPECIAL_ITEM_OBTAIN = 1,
		DEFINE__RENEWAL_ADD_2 = 2,
		DEFINE__CHANNELING_SERVICE = 4,
	};

	static unsigned int FIRST(); //TODO
	static std::pair<int,std::string> CHECK_FIRST(const unsigned int ); //TODO
};


///////////////////////////////////////
#pragma pack(pop)
