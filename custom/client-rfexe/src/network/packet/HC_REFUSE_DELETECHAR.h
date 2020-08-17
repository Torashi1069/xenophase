struct PROTO_HC_REFUSE_DELETECHAR
{
	short PacketType;
	unsigned char ErrorCode;
};


struct PACKET_HC_REFUSE_DELETECHAR
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char ErrorCode;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_HC_REFUSE_DELETECHAR> in(p);
		TPacket<PROTO_HC_REFUSE_DELETECHAR> out;

		out->PacketType = PacketType;
		out->ErrorCode = in->ErrorCode;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_HC_REFUSE_DELETECHAR> in(p);
		TPacket<PACKET_HC_REFUSE_DELETECHAR> out;

		out->PacketType = PacketType;
		out->ErrorCode = in->ErrorCode;

		return out;
	}
};
