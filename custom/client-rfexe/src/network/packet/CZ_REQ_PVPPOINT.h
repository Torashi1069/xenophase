struct PROTO_CZ_REQ_PVPPOINT
{
	short PacketType;
	unsigned long AID;
	unsigned long GID;
};


struct PACKET_CZ_REQ_PVPPOINT
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ unsigned long GID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_PVPPOINT> in(p);
		TPacket<PROTO_CZ_REQ_PVPPOINT> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_PVPPOINT> in(p);
		TPacket<PACKET_CZ_REQ_PVPPOINT> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;

		return out;
	}
};
