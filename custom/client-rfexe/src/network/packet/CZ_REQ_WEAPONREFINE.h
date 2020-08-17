struct PROTO_CZ_REQ_WEAPONREFINE
{
	short PacketType;
	int Index;
};


struct PACKET_CZ_REQ_WEAPONREFINE
{
	/* this+0 */ short PacketType;
	/* this+2 */ int Index;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_WEAPONREFINE> in(p);
		TPacket<PROTO_CZ_REQ_WEAPONREFINE> out;

		out->PacketType = PacketType;
		out->Index = in->Index;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_WEAPONREFINE> in(p);
		TPacket<PACKET_CZ_REQ_WEAPONREFINE> out;

		out->PacketType = PacketType;
		out->Index = in->Index;

		return out;
	}
};
