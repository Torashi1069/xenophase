struct PROTO_ZC_NPCACK_ENABLE
{
	short PacketType;
};


struct PACKET_ZC_NPCACK_ENABLE
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NPCACK_ENABLE> in(p);
		TPacket<PROTO_ZC_NPCACK_ENABLE> out;

		out->PacketType = PacketType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NPCACK_ENABLE> in(p);
		TPacket<PACKET_ZC_NPCACK_ENABLE> out;

		out->PacketType = PacketType;

		return out;
	}
};
