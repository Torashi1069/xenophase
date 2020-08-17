struct PROTO_CZ_REQ_ALLY_GUILD
{
	short PacketType;
	unsigned long AID;
	unsigned long MyAID;
	unsigned long MyGID;
};


struct PACKET_CZ_REQ_ALLY_GUILD
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long MyAID;
	/* this+10 */ unsigned long MyGID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_ALLY_GUILD> in(p);
		TPacket<PROTO_CZ_REQ_ALLY_GUILD> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->MyAID = in->MyAID;
		out->MyGID = in->MyGID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_ALLY_GUILD> in(p);
		TPacket<PACKET_CZ_REQ_ALLY_GUILD> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->MyAID = in->MyAID;
		out->MyGID = in->MyGID;

		return out;
	}
};
