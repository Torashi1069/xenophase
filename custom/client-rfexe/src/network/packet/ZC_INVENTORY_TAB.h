struct PROTO_ZC_INVENTORY_TAB
{
	short PacketType;
	unsigned short Index;
	bool NORMALorPRIVATE;
};


struct PACKET_ZC_INVENTORY_TAB
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short Index;
	/* this+4 */ bool NORMALorPRIVATE;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_INVENTORY_TAB> in(p);
		TPacket<PROTO_ZC_INVENTORY_TAB> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->NORMALorPRIVATE = in->NORMALorPRIVATE;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_INVENTORY_TAB> in(p);
		TPacket<PACKET_ZC_INVENTORY_TAB> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->NORMALorPRIVATE = in->NORMALorPRIVATE;

		return out;
	}
};
