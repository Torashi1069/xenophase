struct PROTO_CZ_UPGRADE_SKILLLEVEL
{
	short PacketType;
	unsigned short SKID;
};


struct PACKET_CZ_UPGRADE_SKILLLEVEL
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_UPGRADE_SKILLLEVEL> in(p);
		TPacket<PROTO_CZ_UPGRADE_SKILLLEVEL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_UPGRADE_SKILLLEVEL> in(p);
		TPacket<PACKET_CZ_UPGRADE_SKILLLEVEL> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;

		return out;
	}
};
