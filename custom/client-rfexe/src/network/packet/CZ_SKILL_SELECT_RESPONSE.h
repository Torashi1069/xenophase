struct PROTO_CZ_SKILL_SELECT_RESPONSE
{
	enum enumWHY
	{
		WHY_LOWERVER_COMPATIBILITY = 0,
		WHY_SC_AUTOSHADOWSPELL     = 1,
	};

	short PacketType;
	enumWHY why;
	unsigned short SKID;
};


struct PACKET_CZ_SKILL_SELECT_RESPONSE
{
	enum enumWHY
	{
		WHY_LOWERVER_COMPATIBILITY = 0,
		WHY_SC_AUTOSHADOWSPELL     = 1,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ enumWHY why;
	/* this+6 */ unsigned short SKID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_SKILL_SELECT_RESPONSE> in(p);
		TPacket<PROTO_CZ_SKILL_SELECT_RESPONSE> out;

		out->PacketType = PacketType;
		out->why = (PROTO_CZ_SKILL_SELECT_RESPONSE::enumWHY)in->why;
		out->SKID = in->SKID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_SKILL_SELECT_RESPONSE> in(p);
		TPacket<PACKET_CZ_SKILL_SELECT_RESPONSE> out;

		out->PacketType = PacketType;
		out->why = (PACKET_CZ_SKILL_SELECT_RESPONSE::enumWHY)in->why;
		out->SKID = in->SKID;

		return out;
	}
};
