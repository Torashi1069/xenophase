struct PROTO_CZ_PC_BUY_CASH_POINT_ITEM
{
	short PacketType;
	unsigned short ITID;
	short count;
	unsigned long FreePoint;
};


struct PACKET_CZ_PC_BUY_CASH_POINT_ITEM
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short ITID;
	/* this+4 */ short count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_PC_BUY_CASH_POINT_ITEM> in(p);
		TPacket<PROTO_CZ_PC_BUY_CASH_POINT_ITEM> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;
		out->count = in->count;
		out->FreePoint = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PC_BUY_CASH_POINT_ITEM> in(p);
		TPacket<PACKET_CZ_PC_BUY_CASH_POINT_ITEM> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;
		out->count = in->count;
//		out->FreePoint = in->FreePoint; // adapt

		return out;
	}
};


struct PACKET_CZ_PC_BUY_CASH_POINT_ITEM__KRO2010
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short ITID;
	/* this+4 */ short count;
	/* this+6 */ unsigned long FreePoint;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_PC_BUY_CASH_POINT_ITEM__KRO2010> in(p);
		TPacket<PROTO_CZ_PC_BUY_CASH_POINT_ITEM> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;
		out->count = in->count;
		out->FreePoint = in->FreePoint;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PC_BUY_CASH_POINT_ITEM> in(p);
		TPacket<PACKET_CZ_PC_BUY_CASH_POINT_ITEM__KRO2010> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;
		out->count = in->count;
		out->FreePoint = in->FreePoint;

		return out;
	}
};
