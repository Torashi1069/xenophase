struct PROTO_ZC_SPRITE_CHANGE
{
	short PacketType;
	unsigned long GID;
	unsigned char type;
	int value;
};


struct PACKET_ZC_SPRITE_CHANGE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char type;
	/* this+7 */ unsigned char value;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SPRITE_CHANGE> in(p);
		TPacket<PROTO_ZC_SPRITE_CHANGE> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->type = in->type;
		out->value = in->value; // adapt
		//FIXME: unsigned char <-> int, meaning of value may be different
		//FIXME: v1 and v2 have different handling of weapon and shield

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SPRITE_CHANGE> in(p);
		TPacket<PACKET_ZC_SPRITE_CHANGE> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->type = in->type;
		out->value = static_cast<unsigned char>(in->value); // adapt
		//FIXME: unsigned char <-> int, meaning of value may be different
		//FIXME: v1 and v2 have different handling of weapon and shield

		return out;
	}
};


struct PACKET_ZC_SPRITE_CHANGE2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char type;
	/* this+7 */ int value;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SPRITE_CHANGE2> in(p);
		TPacket<PROTO_ZC_SPRITE_CHANGE> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->type = in->type;
		out->value = in->value;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SPRITE_CHANGE> in(p);
		TPacket<PACKET_ZC_SPRITE_CHANGE2> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->type = in->type;
		out->value = in->value;

		return out;
	}
};
