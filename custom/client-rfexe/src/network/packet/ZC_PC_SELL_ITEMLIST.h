struct PROTO_ZC_PC_SELL_ITEMLIST
{
	short PacketType;
	short PacketLength;
	struct SELL_ITEM
	{
		short index;
		int price;
		int overchargeprice;
	}
	Item[];
};


struct PACKET_ZC_PC_SELL_ITEMLIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct SELL_ITEM
	             {
	             	/* this+0 */ short index;
	             	/* this+2 */ int price;
	             	/* this+6 */ int overchargeprice;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PC_SELL_ITEMLIST,PACKET_ZC_PC_SELL_ITEMLIST::SELL_ITEM> in(p);
		TPacket<PROTO_ZC_PC_SELL_ITEMLIST,PROTO_ZC_PC_SELL_ITEMLIST::SELL_ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].price = in->Item[i].price;
			out->Item[i].overchargeprice = in->Item[i].overchargeprice;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PC_SELL_ITEMLIST,PROTO_ZC_PC_SELL_ITEMLIST::SELL_ITEM> in(p);
		TPacket<PACKET_ZC_PC_SELL_ITEMLIST,PACKET_ZC_PC_SELL_ITEMLIST::SELL_ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].price = in->Item[i].price;
			out->Item[i].overchargeprice = in->Item[i].overchargeprice;
		}

		return out;
	}
};
