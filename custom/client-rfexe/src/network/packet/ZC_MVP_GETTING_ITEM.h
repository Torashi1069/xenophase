struct PROTO_ZC_MVP_GETTING_ITEM
{
	short PacketType;
	unsigned short ITID;
};


struct PACKET_ZC_MVP_GETTING_ITEM
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short ITID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MVP_GETTING_ITEM> in(p);
		TPacket<PROTO_ZC_MVP_GETTING_ITEM> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MVP_GETTING_ITEM> in(p);
		TPacket<PACKET_ZC_MVP_GETTING_ITEM> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;

		return out;
	}
};
