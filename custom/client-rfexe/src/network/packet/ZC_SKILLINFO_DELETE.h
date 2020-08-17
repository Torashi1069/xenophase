struct PROTO_ZC_SKILLINFO_DELETE
{
	short PacketType;
	unsigned short SKID;
};


struct PACKET_ZC_SKILLINFO_DELETE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short SKID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SKILLINFO_DELETE> in(p);
		TPacket<PROTO_ZC_SKILLINFO_DELETE> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SKILLINFO_DELETE> in(p);
		TPacket<PACKET_ZC_SKILLINFO_DELETE> out;

		out->PacketType = PacketType;
		out->SKID = in->SKID;

		return out;
	}
};
