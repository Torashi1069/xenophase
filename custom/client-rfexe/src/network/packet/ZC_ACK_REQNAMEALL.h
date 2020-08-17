struct PROTO_ZC_ACK_REQNAMEALL
{
	short PacketType;
	unsigned long AID;
	char CName[24];
	char PName[24];
	char GName[24];
	char RName[24];
};


struct PACKET_ZC_ACK_REQNAMEALL
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ char CName[24];
	/* this+30 */ char PName[24];
	/* this+54 */ char GName[24];
	/* this+78 */ char RName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_REQNAMEALL> in(p);
		TPacket<PROTO_ZC_ACK_REQNAMEALL> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memcpy(out->CName, in->CName, 24);
		memcpy(out->PName, in->PName, 24);
		memcpy(out->GName, in->GName, 24);
		memcpy(out->RName, in->RName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_REQNAMEALL> in(p);
		TPacket<PACKET_ZC_ACK_REQNAMEALL> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		memcpy(out->CName, in->CName, 24);
		memcpy(out->PName, in->PName, 24);
		memcpy(out->GName, in->GName, 24);
		memcpy(out->RName, in->RName, 24);

		return out;
	}
};
