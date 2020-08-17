struct PROTO_ZC_PC_CASH_POINT_UPDATE
{
	short PacketType;
	unsigned long CashPoint;
	unsigned long FreePoint;
	short Error;
};


struct PACKET_ZC_PC_CASH_POINT_UPDATE
{
	enum enumError
	{
		ERROR_TYPE_NONE             = 0,
		ERROR_TYPE_NPC              = 1,
		ERROR_TYPE_SYSTEM           = 2,
		ERROR_TYPE_INVENTORY_WEIGHT = 3,
		ERROR_TYPE_EXCHANGE         = 4,
		ERROR_TYPE_ITEM_ID          = 5,
		ERROR_TYPE_MONEY            = 6,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long CashPoint;
	/* this+6 */ short Error;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PC_CASH_POINT_UPDATE> in(p);
		TPacket<PROTO_ZC_PC_CASH_POINT_UPDATE> out;

		out->PacketType = PacketType;
		out->CashPoint = in->CashPoint;
		out->FreePoint = 0; // adapt
		out->Error = in->Error;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PC_CASH_POINT_UPDATE> in(p);
		TPacket<PACKET_ZC_PC_CASH_POINT_UPDATE> out;

		out->PacketType = PacketType;
		out->CashPoint = in->CashPoint;
//		out->FreePoint = in->FreePoint; // adapt
		out->Error = in->Error;

		return out;
	}
};


struct PACKET_ZC_PC_CASH_POINT_UPDATE__KRO2010
{
	enum enumError
	{
		ERROR_TYPE_NONE                   = 0,
		ERROR_TYPE_NPC                    = 1,
		ERROR_TYPE_SYSTEM                 = 2,
		ERROR_TYPE_INVENTORY_WEIGHT       = 3,
		ERROR_TYPE_EXCHANGE               = 4,
		ERROR_TYPE_ITEM_ID                = 5,
		ERROR_TYPE_MONEY                  = 6,
		ERROR_TYPE_OVER_PRODUCT_TOTAL_CNT = 7,
		ERROR_TYPE_SOME_BUY_FAILURE       = 8,
		ERROR_TYPE_INVENTORY_ITEMCNT      = 9,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long CashPoint;
	/* this+ 6 */ unsigned long FreePoint;
	/* this+10 */ short Error;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PC_CASH_POINT_UPDATE__KRO2010> in(p);
		TPacket<PROTO_ZC_PC_CASH_POINT_UPDATE> out;

		out->PacketType = PacketType;
		out->CashPoint = in->CashPoint;
		out->FreePoint = in->FreePoint;
		out->Error = in->Error;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PC_CASH_POINT_UPDATE> in(p);
		TPacket<PACKET_ZC_PC_CASH_POINT_UPDATE__KRO2010> out;

		out->PacketType = PacketType;
		out->CashPoint = in->CashPoint;
		out->FreePoint = in->FreePoint;
		out->Error = in->Error;

		return out;
	}
};
