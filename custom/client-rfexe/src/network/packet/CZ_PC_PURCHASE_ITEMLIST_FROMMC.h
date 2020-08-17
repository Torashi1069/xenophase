struct PROTO_CZ_PC_PURCHASE_ITEMLIST_FROMMC
{
	short PacketType;
	short PacketLength;
	unsigned long AID;
	unsigned long UniqueID;
	struct CZ_PURCHASE_ITEM_FROMMC
	{
		short count;
		short index;
	}
	Item[];
};


struct PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long AID;
	/* this+8 */ struct CZ_PURCHASE_ITEM_FROMMC
	             {
	             	/* this+0 */ short count;
	             	/* this+2 */ short index;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC,PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC::CZ_PURCHASE_ITEM_FROMMC> in(p);
		TPacket<PROTO_CZ_PC_PURCHASE_ITEMLIST_FROMMC,PROTO_CZ_PC_PURCHASE_ITEMLIST_FROMMC::CZ_PURCHASE_ITEM_FROMMC> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->UniqueID = 0; // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].count = in->Item[i].count;
			out->Item[i].index = in->Item[i].index;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PC_PURCHASE_ITEMLIST_FROMMC,PROTO_CZ_PC_PURCHASE_ITEMLIST_FROMMC::CZ_PURCHASE_ITEM_FROMMC> in(p);
		TPacket<PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC,PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC::CZ_PURCHASE_ITEM_FROMMC> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
//		out->UniqueID = in->UniqueID; // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].count = in->Item[i].count;
			out->Item[i].index = in->Item[i].index;
		}

		return out;
	}
};


struct PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long UniqueID;
	/* this+12 */ struct CZ_PURCHASE_ITEM_FROMMC
	             {
	             	/* this+0 */ short count;
	             	/* this+2 */ short index;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC2,PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC2::CZ_PURCHASE_ITEM_FROMMC> in(p);
		TPacket<PROTO_CZ_PC_PURCHASE_ITEMLIST_FROMMC,PROTO_CZ_PC_PURCHASE_ITEMLIST_FROMMC::CZ_PURCHASE_ITEM_FROMMC> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->UniqueID = in->UniqueID;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].count = in->Item[i].count;
			out->Item[i].index = in->Item[i].index;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_PC_PURCHASE_ITEMLIST_FROMMC,PROTO_CZ_PC_PURCHASE_ITEMLIST_FROMMC::CZ_PURCHASE_ITEM_FROMMC> in(p);
		TPacket<PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC2,PACKET_CZ_PC_PURCHASE_ITEMLIST_FROMMC2::CZ_PURCHASE_ITEM_FROMMC> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->UniqueID = in->UniqueID;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].count = in->Item[i].count;
			out->Item[i].index = in->Item[i].index;
		}

		return out;
	}
};
