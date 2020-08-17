struct PROTO_ZC_ROOM_NEWENTRY
{
	short PacketType;
	short PacketLength;
	unsigned long AID;
	unsigned long roomID;
	short maxcount;
	short curcount;
	unsigned char type;
	char title[];
};


struct PACKET_ZC_ROOM_NEWENTRY
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long roomID;
	/* this+12 */ short maxcount;
	/* this+14 */ short curcount;
	/* this+16 */ unsigned char type;
	/* this+17 */ char title[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ROOM_NEWENTRY,char> in(p);
		TPacket<PROTO_ZC_ROOM_NEWENTRY,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->roomID = in->roomID;
		out->maxcount = in->maxcount;
		out->curcount = in->curcount;
		out->type = in->type;
		memcpy(out->title, in->title, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ROOM_NEWENTRY,char> in(p);
		TPacket<PACKET_ZC_ROOM_NEWENTRY,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->roomID = in->roomID;
		out->maxcount = in->maxcount;
		out->curcount = in->curcount;
		out->type = in->type;
		memcpy(out->title, in->title, out.count());

		return out;
	}
};
