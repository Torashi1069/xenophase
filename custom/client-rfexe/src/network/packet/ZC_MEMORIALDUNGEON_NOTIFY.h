struct PROTO_ZC_MEMORIALDUNGEON_NOTIFY
{
	enum enumTYPE
	{
		TYPE_NOTIFY                = 0,
		TYPE_DESTROY_LIVE_TIMEOUT  = 1,
		TYPE_DESTROY_ENTER_TIMEOUT = 2,
		TYPE_DESTROY_USER_REQUEST  = 3,
		TYPE_CREATE_FAIL           = 4,
	};

	short PacketType;
	enumTYPE Type;
	unsigned long EnterLimitDate;
};


struct PACKET_ZC_MEMORIALDUNGEON_NOTIFY
{
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

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MEMORIALDUNGEON_NOTIFY> in(p);
		TPacket<PROTO_ZC_MEMORIALDUNGEON_NOTIFY> out;

		out->PacketType = PacketType;
		out->Type = (PROTO_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE)in->Type;
		out->EnterLimitDate = in->EnterLimitDate;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MEMORIALDUNGEON_NOTIFY> in(p);
		TPacket<PACKET_ZC_MEMORIALDUNGEON_NOTIFY> out;

		out->PacketType = PacketType;
		out->Type = (PACKET_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE)in->Type;
		out->EnterLimitDate = in->EnterLimitDate;

		return out;
	}
};
