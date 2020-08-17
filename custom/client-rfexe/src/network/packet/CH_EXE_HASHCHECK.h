struct PROTO_CH_EXE_HASHCHECK
{
	short PacketType; // PROTOID_CH_EXE_HASHCHECK
	unsigned char ClientType;
	unsigned char HashValue[16];
};


struct PACKET_CH_EXE_HASHCHECK
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ClientType;
	/* this+3 */ unsigned char HashValue[16];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CH_EXE_HASHCHECK> in(p);
		TPacket<PROTO_CH_EXE_HASHCHECK> out;

		out->PacketType = PacketType;
		out->ClientType = in->ClientType;
		memcpy(out->HashValue, in->HashValue, 16);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CH_EXE_HASHCHECK> in(p);
		TPacket<PACKET_CH_EXE_HASHCHECK> out;

		out->PacketType = PacketType;
		out->ClientType = in->ClientType;
		memcpy(out->HashValue, in->HashValue, 16);

		return out;
	}
};
