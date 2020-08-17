struct PROTO_ZC_TALKBOX_CHATCONTENTS
{
	short PacketType;
	unsigned long AID;
	char contents[80];
};


struct PACKET_ZC_TALKBOX_CHATCONTENTS
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char contents[80];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_TALKBOX_CHATCONTENTS> in(p);
		TPacket<PROTO_ZC_TALKBOX_CHATCONTENTS> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memcpy(out->contents, in->contents, 80);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_TALKBOX_CHATCONTENTS> in(p);
		TPacket<PACKET_ZC_TALKBOX_CHATCONTENTS> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memcpy(out->contents, in->contents, 80);

		return out;
	}
};
