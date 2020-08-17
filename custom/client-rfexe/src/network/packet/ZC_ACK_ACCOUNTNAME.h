struct PROTO_ZC_ACK_ACCOUNTNAME
{
	short PacketType;
	unsigned long AID;
	char name[24];
};


struct PACKET_ZC_ACK_ACCOUNTNAME
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ char name[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_ACCOUNTNAME> in(p);
		TPacket<PROTO_ZC_ACK_ACCOUNTNAME> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memcpy(out->name, in->name, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_ACCOUNTNAME> in(p);
		TPacket<PACKET_ZC_ACK_ACCOUNTNAME> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memcpy(out->name, in->name, 24);

		return out;
	}
};
