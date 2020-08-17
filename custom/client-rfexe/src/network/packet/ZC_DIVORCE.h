struct PROTO_ZC_DIVORCE
{
	short PacketType;
	char name[24];
};


struct PACKET_ZC_DIVORCE
{
	/* this+0 */ short PacketType;
	/* this+2 */ char name[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_DIVORCE> in(p);
		TPacket<PROTO_ZC_DIVORCE> out;

		out->PacketType = PacketType;
		memcpy(out->name, in->name, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_DIVORCE> in(p);
		TPacket<PACKET_ZC_DIVORCE> out;

		out->PacketType = PacketType;
		memcpy(out->name, in->name, 24);

		return out;
	}
};
