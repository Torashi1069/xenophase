struct PROTO_SC_ACK_ENCRYPTION
{
	short PacketType; // PROTOID_SC_ACK_ENCRYPTION
};


struct PACKET_SC_ACK_ENCRYPTION
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_SC_ACK_ENCRYPTION> in(p);
		TPacket<PROTO_SC_ACK_ENCRYPTION> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_SC_ACK_ENCRYPTION> in(p);
		TPacket<PACKET_SC_ACK_ENCRYPTION> out;

		out->PacketType = PacketType;

		return out;
	}
};
