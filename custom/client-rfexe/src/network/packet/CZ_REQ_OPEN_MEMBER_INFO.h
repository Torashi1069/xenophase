struct PROTO_CZ_REQ_OPEN_MEMBER_INFO
{
	short PacketType;
	int AID;
};


struct PACKET_CZ_REQ_OPEN_MEMBER_INFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ int AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_OPEN_MEMBER_INFO> in(p);
		TPacket<PROTO_CZ_REQ_OPEN_MEMBER_INFO> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_OPEN_MEMBER_INFO> in(p);
		TPacket<PACKET_CZ_REQ_OPEN_MEMBER_INFO> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}
};
