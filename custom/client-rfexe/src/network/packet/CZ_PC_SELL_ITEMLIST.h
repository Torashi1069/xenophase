struct PROTO_CZ_PC_SELL_ITEMLIST
{
	short PacketType;
	short PacketLength;
	struct CZ_SELL_ITEM
	{
		short index;
		short count;
	}
	Item[];
};


struct PACKET_CZ_PC_SELL_ITEMLIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct CZ_SELL_ITEM
	             {
	             	/* this+0 */ short index;
	             	/* this+2 */ short count;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_PC_SELL_ITEMLIST,PACKET_CZ_PC_SELL_ITEMLIST::CZ_SELL_ITEM> in(p);
		TPacket<PROTO_CZ_PC_SELL_ITEMLIST,PROTO_CZ_PC_SELL_ITEMLIST::CZ_SELL_ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].count = in->Item[i].count;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PC_SELL_ITEMLIST,PROTO_CZ_PC_SELL_ITEMLIST::CZ_SELL_ITEM> in(p);
		TPacket<PACKET_CZ_PC_SELL_ITEMLIST,PACKET_CZ_PC_SELL_ITEMLIST::CZ_SELL_ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].count = in->Item[i].count;
		}

		return out;
	}
};
