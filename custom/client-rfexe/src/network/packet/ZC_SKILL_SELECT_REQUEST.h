struct PROTO_ZC_SKILL_SELECT_REQUEST
{
	enum enumWHY
	{
		WHY_LOWERVER_COMPATIBILITY = 0,
		WHY_SC_AUTOSHADOWSPELL     = 1,
	};

	short PacketType;
	unsigned short PacketLength;
	enumWHY why;
	unsigned short List[];
};


struct PACKET_ZC_SKILL_SELECT_REQUEST
{
	enum enumWHY
	{
		WHY_LOWERVER_COMPATIBILITY = 0,
		WHY_SC_AUTOSHADOWSPELL     = 1,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ enumWHY why;
	/* this+8 */ unsigned short List[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILL_SELECT_REQUEST,short> in(p);
		TPacket<PROTO_ZC_SKILL_SELECT_REQUEST,short> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->why = (PROTO_ZC_SKILL_SELECT_REQUEST::enumWHY)in->why;
		for( size_t i = 0; i < out.count(); ++i )
		{
			out->List[i] = in->List[i];
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILL_SELECT_REQUEST,short> in(p);
		TPacket<PACKET_ZC_SKILL_SELECT_REQUEST,short> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->why = (PACKET_ZC_SKILL_SELECT_REQUEST::enumWHY)in->why;
		for( size_t i = 0; i < out.count(); ++i )
		{
			out->List[i] = in->List[i];
		}

		return out;
	}
};
