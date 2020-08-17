struct PROTO_CZ_ACK_REQ_ADD_FRIENDS
{
	short PacketType;
	unsigned long ReqAID;
	unsigned long ReqGID;
	int Result;
};


struct PACKET_CZ_ACK_REQ_ADD_FRIENDS
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long ReqAID;
	/* this+ 6 */ unsigned long ReqGID;
	/* this+10 */ int Result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_ACK_REQ_ADD_FRIENDS> in(p);
		TPacket<PROTO_CZ_ACK_REQ_ADD_FRIENDS> out;

		out->PacketType = PacketType;
		out->ReqAID = in->ReqAID;
		out->ReqGID = in->ReqGID;
		out->Result = in->Result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_ACK_REQ_ADD_FRIENDS> in(p);
		TPacket<PACKET_CZ_ACK_REQ_ADD_FRIENDS> out;

		out->PacketType = PacketType;
		out->ReqAID = in->ReqAID;
		out->ReqGID = in->ReqGID;
		out->Result = in->Result;

		return out;
	}
};
