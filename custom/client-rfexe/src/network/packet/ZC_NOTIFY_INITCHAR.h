struct PROTO_ZC_NOTIFY_INITCHAR
{
	short PacketType;
	unsigned short PacketLength;
	unsigned long GID;
	short Style;
	unsigned char Item;
	BYTE unknown[];
};


struct PACKET_ZC_NOTIFY_INITCHAR
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long GID;
	/* this+ 8 */ short Style;
	/* this+10 */ unsigned char Item;
	/* this+11 */ BYTE unknown[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_INITCHAR,BYTE> in(p);
		TPacket<PROTO_ZC_NOTIFY_INITCHAR,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->GID = in->GID;
		out->Style = in->Style;
		out->Item = in->Item;
		memcpy(out->unknown, in->unknown, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_INITCHAR,BYTE> in(p);
		TPacket<PACKET_ZC_NOTIFY_INITCHAR,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->GID = in->GID;
		out->Style = in->Style;
		out->Item = in->Item;
		memcpy(out->unknown, in->unknown, out.count());

		return out;
	}
};
