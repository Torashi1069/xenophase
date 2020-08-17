struct PROTO_ZC_NOTIFY_VANISH
{
	short PacketType;
	unsigned long GID;
	unsigned char type; // enum eVanishType
};


struct PACKET_ZC_NOTIFY_VANISH
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ unsigned char type;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_VANISH> in(p);
		TPacket<PROTO_ZC_NOTIFY_VANISH> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->type = in->type;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_VANISH> in(p);
		TPacket<PACKET_ZC_NOTIFY_VANISH> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		out->type = in->type;

		return out;
	}
};
