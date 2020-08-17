struct PROTO_ZC_ACK_BAN_GUILD
{
	short PacketType;
	char charName[24];
	char reasonDesc[40];
	char account[24];
};


struct PACKET_ZC_ACK_BAN_GUILD
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char charName[24];
	/* this+26 */ char reasonDesc[40];
	/* this+66 */ char account[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_BAN_GUILD> in(p);
		TPacket<PROTO_ZC_ACK_BAN_GUILD> out;

		out->PacketType = PacketType;
		memcpy(out->charName, in->charName, 24);
		memcpy(out->reasonDesc, in->reasonDesc, 40);
		memcpy(out->account, in->account, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_BAN_GUILD> in(p);
		TPacket<PACKET_ZC_ACK_BAN_GUILD> out;

		out->PacketType = PacketType;
		memcpy(out->charName, in->charName, 24);
		memcpy(out->reasonDesc, in->reasonDesc, 40);
		memcpy(out->account, in->account, 24);

		return out;
	}
};
