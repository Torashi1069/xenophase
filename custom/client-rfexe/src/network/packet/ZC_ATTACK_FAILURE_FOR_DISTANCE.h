struct PROTO_ZC_ATTACK_FAILURE_FOR_DISTANCE
{
	short PacketType;
	unsigned long targetAID;
	short targetXPos;
	short targetYPos;
	short xPos;
	short yPos;
	short currentAttRange;
};


struct PACKET_ZC_ATTACK_FAILURE_FOR_DISTANCE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long targetAID;
	/* this+ 6 */ short targetXPos;
	/* this+ 8 */ short targetYPos;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ short currentAttRange;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ATTACK_FAILURE_FOR_DISTANCE> in(p);
		TPacket<PROTO_ZC_ATTACK_FAILURE_FOR_DISTANCE> out;

		out->PacketType = PacketType;
		out->targetAID = in->targetAID;
		out->targetXPos = in->targetXPos;
		out->targetYPos = in->targetYPos;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->currentAttRange = in->currentAttRange;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ATTACK_FAILURE_FOR_DISTANCE> in(p);
		TPacket<PACKET_ZC_ATTACK_FAILURE_FOR_DISTANCE> out;

		out->PacketType = PacketType;
		out->targetAID = in->targetAID;
		out->targetXPos = in->targetXPos;
		out->targetYPos = in->targetYPos;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->currentAttRange = in->currentAttRange;

		return out;
	}
};
