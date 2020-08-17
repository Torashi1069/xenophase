struct PROTO_ZC_NOTIFY_CHAT_PARTY
{
	short PacketType;
	unsigned short PacketLength;
	unsigned long AID;
	char Text[];
};


struct PACKET_ZC_NOTIFY_CHAT_PARTY
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short PacketLength;
	/* this+4 */ unsigned long AID;
	/* this+8 */ char Text[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_CHAT_PARTY,char> in(p);
		TPacket<PROTO_ZC_NOTIFY_CHAT_PARTY,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		memcpy(out->Text, in->Text, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_CHAT_PARTY,char> in(p);
		TPacket<PACKET_ZC_NOTIFY_CHAT_PARTY,char> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		memcpy(out->Text, in->Text, out.count());

		return out;
	}
};
