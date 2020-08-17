struct PROTO_CZ_REQUEST_ACT
{
	short PacketType;
	unsigned long targetGID;
	unsigned char action;
};


struct PACKET_CZ_REQUEST_ACT
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long targetGID;
	/* this+6 */ unsigned char action;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQUEST_ACT> in(p);
		TPacket<PROTO_CZ_REQUEST_ACT> out;

		out->PacketType = PacketType;
		out->targetGID = in->targetGID;
		out->action = in->action;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQUEST_ACT> in(p);
		TPacket<PACKET_CZ_REQUEST_ACT> out;

		out->PacketType = PacketType;
		out->targetGID = in->targetGID;
		out->action = in->action;

		return out;
	}
};


struct PACKET_CZ_REQUEST_ACT2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long targetGID;
	/* this+6 */ unsigned char action;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQUEST_ACT2> in(p);
		TPacket<PROTO_CZ_REQUEST_ACT> out;

		out->PacketType = PacketType;
		out->targetGID = in->targetGID;
		out->action = in->action;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQUEST_ACT> in(p);
		TPacket<PACKET_CZ_REQUEST_ACT2> out;

		out->PacketType = PacketType;
		out->targetGID = in->targetGID;
		out->action = in->action;

		return out;
	}
};
