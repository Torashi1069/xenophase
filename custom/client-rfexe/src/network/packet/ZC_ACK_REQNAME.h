struct PROTO_ZC_ACK_REQNAME
{
	short PacketType;
	unsigned long AID;
	char CName[24];
};


struct PACKET_ZC_ACK_REQNAME
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char CName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_REQNAME> in(p);
		TPacket<PROTO_ZC_ACK_REQNAME> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memcpy(out->CName, in->CName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_REQNAME> in(p);
		TPacket<PACKET_ZC_ACK_REQNAME> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memcpy(out->CName, in->CName, 24);

		return out;
	}
};
