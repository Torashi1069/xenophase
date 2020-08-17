struct PROTO_ZC_STORE_ENTRY
{
	short PacketType;
	unsigned long makerAID;
	char storeName[80];
};


struct PACKET_ZC_STORE_ENTRY
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long makerAID;
	/* this+6 */ char storeName[80];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_STORE_ENTRY> in(p);
		TPacket<PROTO_ZC_STORE_ENTRY> out;

		out->PacketType = PacketType;
		out->makerAID = in->makerAID;
		memcpy(out->storeName, in->storeName, 80);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_STORE_ENTRY> in(p);
		TPacket<PACKET_ZC_STORE_ENTRY> out;

		out->PacketType = PacketType;
		out->makerAID = in->makerAID;
		memcpy(out->storeName, in->storeName, 80);

		return out;
	}
};
