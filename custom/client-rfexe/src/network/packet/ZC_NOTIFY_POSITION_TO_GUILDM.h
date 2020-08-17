struct PROTO_ZC_NOTIFY_POSITION_TO_GUILDM
{
	short PacketType;
	unsigned long AID;
	short xPos;
	short yPos;
};


struct PACKET_ZC_NOTIFY_POSITION_TO_GUILDM
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long AID;
	/* this+6 */ short xPos;
	/* this+8 */ short yPos;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_POSITION_TO_GUILDM> in(p);
		TPacket<PROTO_ZC_NOTIFY_POSITION_TO_GUILDM> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_POSITION_TO_GUILDM> in(p);
		TPacket<PACKET_ZC_NOTIFY_POSITION_TO_GUILDM> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;

		return out;
	}
};
