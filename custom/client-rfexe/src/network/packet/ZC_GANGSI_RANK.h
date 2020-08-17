struct PROTO_ZC_GANGSI_RANK
{
	short PacketType;
	char Name[10][24];
	int Point[10];
	short PacketSwitch;
};


struct PACKET_ZC_GANGSI_RANK
{
	/* this+  0 */ short PacketType;
	/* this+  2 */ char Name[10][24];
	/* this+242 */ int Point[10];
	/* this+282 */ short PacketSwitch;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_GANGSI_RANK> in(p);
		TPacket<PROTO_ZC_GANGSI_RANK> out;

		out->PacketType = PacketType;
		for( size_t i = 0; i < 10; ++i )
		{
			memcpy(out->Name[i], in->Name[i], 24);
			out->Point[i] = in->Point[i];
		}
		out->PacketSwitch = in->PacketSwitch;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_GANGSI_RANK> in(p);
		TPacket<PACKET_ZC_GANGSI_RANK> out;

		out->PacketType = PacketType;
		for( size_t i = 0; i < 10; ++i )
		{
			memcpy(out->Name[i], in->Name[i], 24);
			out->Point[i] = in->Point[i];
		}
		out->PacketSwitch = in->PacketSwitch;

		return out;
	}
};
