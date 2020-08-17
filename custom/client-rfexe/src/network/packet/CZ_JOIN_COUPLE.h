struct PROTO_CZ_JOIN_COUPLE
{
	short PacketType;
	unsigned long AID;
	unsigned long GID;
	int answer;
};


struct PACKET_CZ_JOIN_COUPLE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ int answer;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_JOIN_COUPLE> in(p);
		TPacket<PROTO_CZ_JOIN_COUPLE> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		out->answer = in->answer;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_JOIN_COUPLE> in(p);
		TPacket<PACKET_CZ_JOIN_COUPLE> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		out->answer = in->answer;

		return out;
	}
};
