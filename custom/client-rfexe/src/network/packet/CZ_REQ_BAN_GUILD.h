struct PROTO_CZ_REQ_BAN_GUILD
{
	short PacketType;
	unsigned long GDID;
	int AID;
	int GID;
	char reasonDesc[40];
};


struct PACKET_CZ_REQ_BAN_GUILD
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ int AID;
	/* this+10 */ int GID;
	/* this+14 */ char reasonDesc[40];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_BAN_GUILD> in(p);
		TPacket<PROTO_CZ_REQ_BAN_GUILD> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		out->AID = in->AID;
		out->GID = in->GID;
		memcpy(out->reasonDesc, in->reasonDesc, 40);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_BAN_GUILD> in(p);
		TPacket<PACKET_CZ_REQ_BAN_GUILD> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		out->AID = in->AID;
		out->GID = in->GID;
		memcpy(out->reasonDesc, in->reasonDesc, 40);

		return out;
	}
};
