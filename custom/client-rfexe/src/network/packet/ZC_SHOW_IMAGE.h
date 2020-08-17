struct PROTO_ZC_SHOW_IMAGE
{
	short PacketType;
	char imageName[64];
	unsigned char type;
};


struct PACKET_ZC_SHOW_IMAGE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char imageName[16];
	/* this+18 */ unsigned char type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SHOW_IMAGE> in(p);
		TPacket<PROTO_ZC_SHOW_IMAGE> out;

		//FIXME: truncation is no good; see if the 'illust/' path can be glued on to make it work
		out->PacketType = PacketType;
		_snprintf(out->imageName, sizeof(out->imageName), "%s", in->imageName);
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SHOW_IMAGE> in(p);
		TPacket<PACKET_ZC_SHOW_IMAGE> out;

		out->PacketType = PacketType;
		_snprintf(out->imageName, sizeof(out->imageName), "%s", in->imageName);
		out->type = in->type;

		return out;
	}
};


struct PACKET_ZC_SHOW_IMAGE2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char imageName[64];
	/* this+66 */ unsigned char type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SHOW_IMAGE2> in(p);
		TPacket<PROTO_ZC_SHOW_IMAGE> out;

		out->PacketType = PacketType;
		memcpy(out->imageName, in->imageName, 64);
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SHOW_IMAGE> in(p);
		TPacket<PACKET_ZC_SHOW_IMAGE2> out;

		out->PacketType = PacketType;
		memcpy(out->imageName, in->imageName, 64);
		out->type = in->type;

		return out;
	}
};
