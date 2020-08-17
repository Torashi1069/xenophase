struct PROTO_SC_COLLECTORDEAD
{
	short PacketType; // PROTOID_SC_COLLECTORDEAD
	unsigned long ServerID;
};


struct PACKET_SC_COLLECTORDEAD
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long ServerID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_SC_COLLECTORDEAD> in(p);
		TPacket<PROTO_SC_COLLECTORDEAD> out;

		out->PacketType = PacketType;
		out->ServerID = in->ServerID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_SC_COLLECTORDEAD> in(p);
		TPacket<PACKET_SC_COLLECTORDEAD> out;

		out->PacketType = PacketType;
		out->ServerID = in->ServerID;

		return out;
	}
};
