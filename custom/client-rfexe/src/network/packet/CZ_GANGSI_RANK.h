struct PROTO_CZ_GANGSI_RANK
{
	short PacketType;
	short PacketSwitch;
};


struct PACKET_CZ_GANGSI_RANK
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketSwitch;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_GANGSI_RANK> in(p);
		TPacket<PROTO_CZ_GANGSI_RANK> out;

		out->PacketType = PacketType;
		out->PacketSwitch = in->PacketSwitch;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_GANGSI_RANK> in(p);
		TPacket<PACKET_CZ_GANGSI_RANK> out;

		out->PacketType = PacketType;
		out->PacketSwitch = in->PacketSwitch;

		return out;
	}
};
