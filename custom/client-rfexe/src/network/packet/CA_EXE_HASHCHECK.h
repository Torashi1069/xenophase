struct PROTO_CA_EXE_HASHCHECK
{
	short PacketType; // PROTOID_CA_EXE_HASHCHECK
	unsigned char HashValue[16];
};


struct PACKET_CA_EXE_HASHCHECK
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char HashValue[16];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_EXE_HASHCHECK> in(p);
		TPacket<PROTO_CA_EXE_HASHCHECK> out;

		out->PacketType = PacketType;
		memcpy(out->HashValue, in->HashValue, 16);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_EXE_HASHCHECK> in(p);
		TPacket<PACKET_CA_EXE_HASHCHECK> out;

		out->PacketType = PacketType;
		memcpy(out->HashValue, in->HashValue, 16);

		return out;
	}
};
