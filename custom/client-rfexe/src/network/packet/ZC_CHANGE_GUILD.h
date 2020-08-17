struct PROTO_ZC_CHANGE_GUILD
{
	short PacketType;
	unsigned long AID;
	unsigned long GDID;
	short emblemVersion;
};


struct PACKET_ZC_CHANGE_GUILD
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GDID;
	/* this+10 */ short emblemVersion;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_CHANGE_GUILD> in(p);
		TPacket<PROTO_ZC_CHANGE_GUILD> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GDID = in->GDID;
		out->emblemVersion = in->emblemVersion;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_CHANGE_GUILD> in(p);
		TPacket<PACKET_ZC_CHANGE_GUILD> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GDID = in->GDID;
		out->emblemVersion = in->emblemVersion;

		return out;
	}
};
