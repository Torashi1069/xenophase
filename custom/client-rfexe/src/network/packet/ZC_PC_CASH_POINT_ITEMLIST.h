struct PROTO_ZC_PC_CASH_POINT_ITEMLIST
{
	short PacketType;
	short PacketLength;
	unsigned long CashPoint;
	unsigned long FreePoint;
	struct PURCHASE_ITEM
	{
		int price;
		int discountprice;
		unsigned char type;
		unsigned short ITID;
	}
	Item[];
};


struct PACKET_ZC_PC_CASH_POINT_ITEMLIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long CashPoint;
	/* this+8 */ struct PURCHASE_ITEM
	             {
	             	/* this+0 */ int price;
	             	/* this+4 */ int discountprice;
	             	/* this+8 */ unsigned char type;
	             	/* this+9 */ unsigned short ITID;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PC_CASH_POINT_ITEMLIST,PACKET_ZC_PC_CASH_POINT_ITEMLIST::PURCHASE_ITEM> in(p);
		TPacket<PROTO_ZC_PC_CASH_POINT_ITEMLIST,PROTO_ZC_PC_CASH_POINT_ITEMLIST::PURCHASE_ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->CashPoint = in->CashPoint;
		out->FreePoint = 0; // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].price = in->Item[i].price;
			out->Item[i].discountprice = in->Item[i].discountprice;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].ITID = in->Item[i].ITID;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PC_CASH_POINT_ITEMLIST,PROTO_ZC_PC_CASH_POINT_ITEMLIST::PURCHASE_ITEM> in(p);
		TPacket<PACKET_ZC_PC_CASH_POINT_ITEMLIST,PACKET_ZC_PC_CASH_POINT_ITEMLIST::PURCHASE_ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->CashPoint = in->CashPoint;
//		out->FreePoint = in->FreePoint; // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].price = in->Item[i].price;
			out->Item[i].discountprice = in->Item[i].discountprice;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].ITID = in->Item[i].ITID;
		}

		return out;
	}
};


struct PACKET_ZC_PC_CASH_POINT_ITEMLIST__KRO2010
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long CashPoint;
	/* this+ 8 */ unsigned long FreePoint;
	/* this+12 */ struct PURCHASE_ITEM
	             {
	             	/* this+0 */ int price;
	             	/* this+4 */ int discountprice;
	             	/* this+8 */ unsigned char type;
	             	/* this+9 */ unsigned short ITID;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PC_CASH_POINT_ITEMLIST__KRO2010,PACKET_ZC_PC_CASH_POINT_ITEMLIST__KRO2010::PURCHASE_ITEM> in(p);
		TPacket<PROTO_ZC_PC_CASH_POINT_ITEMLIST,PROTO_ZC_PC_CASH_POINT_ITEMLIST::PURCHASE_ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->CashPoint = in->CashPoint;
		out->FreePoint = in->FreePoint;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].price = in->Item[i].price;
			out->Item[i].discountprice = in->Item[i].discountprice;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].ITID = in->Item[i].ITID;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PC_CASH_POINT_ITEMLIST,PROTO_ZC_PC_CASH_POINT_ITEMLIST::PURCHASE_ITEM> in(p);
		TPacket<PACKET_ZC_PC_CASH_POINT_ITEMLIST__KRO2010,PACKET_ZC_PC_CASH_POINT_ITEMLIST__KRO2010::PURCHASE_ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->CashPoint = in->CashPoint;
		out->FreePoint = in->FreePoint;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].price = in->Item[i].price;
			out->Item[i].discountprice = in->Item[i].discountprice;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].ITID = in->Item[i].ITID;
		}

		return out;
	}
};
