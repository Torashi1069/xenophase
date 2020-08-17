struct PROTO_CZ_REQ_ACCOUNTNAME
{
	short PacketType;
	unsigned long AID;
};


struct PACKET_CZ_REQ_ACCOUNTNAME
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_ACCOUNTNAME> in(p);
		TPacket<PROTO_CZ_REQ_ACCOUNTNAME> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_ACCOUNTNAME> in(p);
		TPacket<PACKET_CZ_REQ_ACCOUNTNAME> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}
};
