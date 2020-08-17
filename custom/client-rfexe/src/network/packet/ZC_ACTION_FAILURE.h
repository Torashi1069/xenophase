struct PROTO_ZC_ACTION_FAILURE
{
	short PacketType;
	short errorCode;
};


struct PACKET_ZC_ACTION_FAILURE
{
	/* this+0 */ short PacketType;
	/* this+2 */ short errorCode;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACTION_FAILURE> in(p);
		TPacket<PROTO_ZC_ACTION_FAILURE> out;

		out->PacketType = PacketType;
		out->errorCode = in->errorCode;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACTION_FAILURE> in(p);
		TPacket<PACKET_ZC_ACTION_FAILURE> out;

		out->PacketType = PacketType;
		out->errorCode = in->errorCode;

		return out;
	}
};
