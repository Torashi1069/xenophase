struct PROTO_CZ_CHANGE_GROUP_MASTER
{
	short PacketType;
	unsigned long AID;
};


struct PACKET_CZ_CHANGE_GROUP_MASTER
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CHANGE_GROUP_MASTER> in(p);
		TPacket<PROTO_CZ_CHANGE_GROUP_MASTER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CHANGE_GROUP_MASTER> in(p);
		TPacket<PACKET_CZ_CHANGE_GROUP_MASTER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}
};
