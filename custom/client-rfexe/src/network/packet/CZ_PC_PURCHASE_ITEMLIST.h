struct PROTO_CZ_PC_PURCHASE_ITEMLIST
{
	short PacketType;
	short PacketLength;
	struct CZ_PURCHASE_ITEM
	{
		short count;
		unsigned short ITID;
	}
	Item[];
};


struct PACKET_CZ_PC_PURCHASE_ITEMLIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct CZ_PURCHASE_ITEM
	             {
	             	/* this+0 */ short count;
	             	/* this+2 */ unsigned short ITID;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_PC_PURCHASE_ITEMLIST,PACKET_CZ_PC_PURCHASE_ITEMLIST::CZ_PURCHASE_ITEM> in(p);
		TPacket<PROTO_CZ_PC_PURCHASE_ITEMLIST,PROTO_CZ_PC_PURCHASE_ITEMLIST::CZ_PURCHASE_ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].count = in->Item[i].count;
			out->Item[i].ITID = in->Item[i].ITID;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PC_PURCHASE_ITEMLIST,PROTO_CZ_PC_PURCHASE_ITEMLIST::CZ_PURCHASE_ITEM> in(p);
		TPacket<PACKET_CZ_PC_PURCHASE_ITEMLIST,PACKET_CZ_PC_PURCHASE_ITEMLIST::CZ_PURCHASE_ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].count = in->Item[i].count;
			out->Item[i].ITID = in->Item[i].ITID;
		}

		return out;
	}
};
