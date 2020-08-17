struct PROTO_ZC_NPC_CHAT
{
	short PacketType;
	unsigned short packetLength;
	unsigned long accountID;
	unsigned long color;
	char Text[];
};


struct PACKET_ZC_NPC_CHAT
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short packetLength;
	/* this+ 4 */ unsigned long accountID;
	/* this+ 8 */ unsigned long color;
	/* this+12 */ char Text[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NPC_CHAT,char> in(p);
		TPacket<PROTO_ZC_NPC_CHAT,char> out(in.count());

		out->PacketType = PacketType;
		out->packetLength = out.size();
		out->accountID = in->accountID;
		out->color = in->color;
		memcpy(out->Text, in->Text, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NPC_CHAT,char> in(p);
		TPacket<PACKET_ZC_NPC_CHAT,char> out(in.count());

		out->PacketType = PacketType;
		out->packetLength = out.size();
		out->accountID = in->accountID;
		out->color = in->color;
		memcpy(out->Text, in->Text, out.count());

		return out;
	}
};
