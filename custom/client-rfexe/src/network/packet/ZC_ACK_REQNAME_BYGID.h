struct PROTO_ZC_ACK_REQNAME_BYGID
{
	short PacketType;
	unsigned long GID;
	char CName[24];
};


struct PACKET_ZC_ACK_REQNAME_BYGID
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long GID;
	/* this+6 */ char CName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_REQNAME_BYGID> in(p);
		TPacket<PROTO_ZC_ACK_REQNAME_BYGID> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memcpy(out->CName, in->CName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_REQNAME_BYGID> in(p);
		TPacket<PACKET_ZC_ACK_REQNAME_BYGID> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memcpy(out->CName, in->CName, 24);

		return out;
	}
};
