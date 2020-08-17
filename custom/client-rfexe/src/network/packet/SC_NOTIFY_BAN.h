struct PROTO_SC_NOTIFY_BAN
{
	short PacketType; // PROTOID_SC_NOTIFY_BAN
	BYTE ErrorCode; // enum BAN_*
};


struct PACKET_SC_NOTIFY_BAN
{
	/* this+0 */ short PacketType;
	/* this+2 */ BYTE ErrorCode;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_SC_NOTIFY_BAN> in(p);
		TPacket<PROTO_SC_NOTIFY_BAN> out;

		out->PacketType = PacketType;
		out->ErrorCode = in->ErrorCode;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_SC_NOTIFY_BAN> in(p);
		TPacket<PACKET_SC_NOTIFY_BAN> out;

		out->PacketType = PacketType;
		out->ErrorCode = in->ErrorCode;

		return out;
	}
};
