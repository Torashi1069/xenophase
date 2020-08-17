struct PROTO_AC_EVENT_RESULT
{
	short PacketType;
	unsigned long EventItemCount;
};


struct PACKET_AC_EVENT_RESULT
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long EventItemCount;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_AC_EVENT_RESULT> in(p);
		TPacket<PROTO_AC_EVENT_RESULT> out;

		out->PacketType = PacketType;
		out->EventItemCount = in->EventItemCount;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_AC_EVENT_RESULT> in(p);
		TPacket<PACKET_AC_EVENT_RESULT> out;

		out->PacketType = PacketType;
		out->EventItemCount = in->EventItemCount;

		return out;
	}
};
