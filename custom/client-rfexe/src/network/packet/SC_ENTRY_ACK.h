struct PROTO_SC_ENTRY_ACK
{
	short Header; // PROTOID_SC_ENTRY_ACK
	int AID;
};


struct PACKET_SC_ENTRY_ACK
{
	/* this+0 */ short Header;
	/* this+2 */ int AID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_SC_ENTRY_ACK> in(p);
		TPacket<PROTO_SC_ENTRY_ACK> out;

		out->Header = PacketType;
		out->AID = in->AID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_SC_ENTRY_ACK> in(p);
		TPacket<PACKET_SC_ENTRY_ACK> out;

		out->Header = PacketType;
		out->AID = in->AID;

		return out;
	}
};
