struct PROTO_SC_PING
{
	short PacketType; // PROTOID_SC_PING
	unsigned long AID;
};


struct PACKET_SC_PING
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_SC_PING> in(p);
		TPacket<PROTO_SC_PING> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_SC_PING> in(p);
		TPacket<PACKET_SC_PING> out;

		out->PacketType = PacketType;
		out->AID = in->AID;

		return out;
	}
};
