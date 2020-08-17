struct PROTO_ZC_NPCSPRITE_CHANGE
{
	short PacketType;
	unsigned long GID;
	unsigned char type;
	unsigned long value;
};


struct PACKET_ZC_NPCSPRITE_CHANGE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char type;
	/* this+7 */ unsigned long value;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NPCSPRITE_CHANGE> in(p);
		TPacket<PROTO_ZC_NPCSPRITE_CHANGE> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->type = in->type;
		out->value = in->value;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NPCSPRITE_CHANGE> in(p);
		TPacket<PACKET_ZC_NPCSPRITE_CHANGE> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->type = in->type;
		out->value = in->value;

		return out;
	}
};
