struct PROTO_ZC_AUTOSPELLLIST
{
	short PacketType;
	int SKID[7];
};


struct PACKET_ZC_AUTOSPELLLIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ int SKID[7];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_AUTOSPELLLIST> in(p);
		TPacket<PROTO_ZC_AUTOSPELLLIST> out;

		out->PacketType = PacketType;
		
		for( size_t i = 0; i < 7; ++i )
		{
			out->SKID[i] = in->SKID[i];
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_AUTOSPELLLIST> in(p);
		TPacket<PACKET_ZC_AUTOSPELLLIST> out;

		out->PacketType = PacketType;

		for( size_t i = 0; i < 7; ++i )
		{
			out->SKID[i] = in->SKID[i];
		}

		return out;
	}
};
