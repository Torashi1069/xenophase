struct PROTO_ZC_USESKILL_ACK
{
	short PacketType;
	unsigned long AID;
	unsigned long targetID;
	short xPos;
	short yPos;
	unsigned short SKID;
	unsigned long property;
	unsigned long delayTime;
	bool isDisposable;
};


struct PACKET_ZC_USESKILL_ACK
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long targetID;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned short SKID;
	/* this+16 */ unsigned long property;
	/* this+20 */ unsigned long delayTime;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_USESKILL_ACK> in(p);
		TPacket<PROTO_ZC_USESKILL_ACK> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->targetID = in->targetID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->SKID = in->SKID;
		out->property = in->property;
		out->delayTime = in->delayTime;
		out->isDisposable = false; // adapt //TODO: verify

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_USESKILL_ACK> in(p);
		TPacket<PACKET_ZC_USESKILL_ACK> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->targetID = in->targetID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->SKID = in->SKID;
		out->property = in->property;
		out->delayTime = in->delayTime;
//		out->isDisposable = in->isDisposable; // adapt

		return out;
	}
};


struct PACKET_ZC_USESKILL_ACK2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long targetID;
	/* this+10 */ short xPos;
	/* this+12 */ short yPos;
	/* this+14 */ unsigned short SKID;
	/* this+16 */ unsigned long property;
	/* this+20 */ unsigned long delayTime;
	/* this+24 */ bool isDisposable;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_USESKILL_ACK2> in(p);
		TPacket<PROTO_ZC_USESKILL_ACK> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->targetID = in->targetID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->SKID = in->SKID;
		out->property = in->property;
		out->delayTime = in->delayTime;
		out->isDisposable = in->isDisposable;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_USESKILL_ACK> in(p);
		TPacket<PACKET_ZC_USESKILL_ACK2> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->targetID = in->targetID;
		out->xPos = in->xPos;
		out->yPos = in->yPos;
		out->SKID = in->SKID;
		out->property = in->property;
		out->delayTime = in->delayTime;
		out->isDisposable = in->isDisposable;

		return out;
	}
};
