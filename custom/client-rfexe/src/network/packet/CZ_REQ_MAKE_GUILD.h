struct PROTO_CZ_REQ_MAKE_GUILD
{
	short PacketType;
	unsigned long GID;
	char GName[24];
};


struct PACKET_CZ_REQ_MAKE_GUILD
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char GName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_MAKE_GUILD> in(p);
		TPacket<PROTO_CZ_REQ_MAKE_GUILD> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memcpy(out->GName, in->GName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_MAKE_GUILD> in(p);
		TPacket<PACKET_CZ_REQ_MAKE_GUILD> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memcpy(out->GName, in->GName, 24);

		return out;
	}
};
