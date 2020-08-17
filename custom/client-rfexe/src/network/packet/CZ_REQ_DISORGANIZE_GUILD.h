struct PROTO_CZ_REQ_DISORGANIZE_GUILD
{
	short PacketType;
	char key[40];
};


struct PACKET_CZ_REQ_DISORGANIZE_GUILD
{
	/* this+0 */ short PacketType;
	/* this+2 */ char key[40];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_DISORGANIZE_GUILD> in(p);
		TPacket<PROTO_CZ_REQ_DISORGANIZE_GUILD> out;

		out->PacketType = PacketType;
		memcpy(out->key, in->key, 40);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_DISORGANIZE_GUILD> in(p);
		TPacket<PACKET_CZ_REQ_DISORGANIZE_GUILD> out;

		out->PacketType = PacketType;
		memcpy(out->key, in->key, 40);

		return out;
	}
};
