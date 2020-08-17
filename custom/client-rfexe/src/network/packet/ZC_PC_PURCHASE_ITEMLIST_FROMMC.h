struct PROTO_ZC_PC_PURCHASE_ITEMLIST_FROMMC
{
	short PacketType;
	short PacketLength;
	unsigned long AID;
	unsigned long UniqueID;
	struct PURCHASE_ITEM_FROMMC
	{
		int price;
		short count;
		short index;
		unsigned char type;
		unsigned short ITID;
		bool IsIdentified;
		bool IsDamaged;
		unsigned char refiningLevel;
		EQUIPSLOTINFO slot;
	}
	Item[];
};


struct PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ unsigned long AID;
	/* this+8 */ struct PURCHASE_ITEM_FROMMC
	             {
	             	/* this+ 0 */ int price;
	             	/* this+ 4 */ short count;
	             	/* this+ 6 */ short index;
	             	/* this+ 8 */ unsigned char type;
	             	/* this+ 9 */ unsigned short ITID;
	             	/* this+11 */ bool IsIdentified;
	             	/* this+12 */ bool IsDamaged;
	             	/* this+13 */ unsigned char refiningLevel;
	             	/* this+14 */ EQUIPSLOTINFO slot;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC,PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC::PURCHASE_ITEM_FROMMC> in(p);
		TPacket<PROTO_ZC_PC_PURCHASE_ITEMLIST_FROMMC,PROTO_ZC_PC_PURCHASE_ITEMLIST_FROMMC::PURCHASE_ITEM_FROMMC> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->UniqueID = 0; // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].price = in->Item[i].price;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].index = in->Item[i].index;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].IsDamaged = in->Item[i].IsDamaged;
			out->Item[i].refiningLevel = in->Item[i].refiningLevel;
			out->Item[i].slot.info[0] = in->Item[i].slot.info[0];
			out->Item[i].slot.info[1] = in->Item[i].slot.info[1];
			out->Item[i].slot.info[2] = in->Item[i].slot.info[2];
			out->Item[i].slot.info[3] = in->Item[i].slot.info[3];
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PC_PURCHASE_ITEMLIST_FROMMC,PROTO_ZC_PC_PURCHASE_ITEMLIST_FROMMC::PURCHASE_ITEM_FROMMC> in(p);
		TPacket<PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC,PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC::PURCHASE_ITEM_FROMMC> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
//		out->UniqueID = in->UniqueID; // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].price = in->Item[i].price;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].index = in->Item[i].index;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].IsDamaged = in->Item[i].IsDamaged;
			out->Item[i].refiningLevel = in->Item[i].refiningLevel;
			out->Item[i].slot.info[0] = in->Item[i].slot.info[0];
			out->Item[i].slot.info[1] = in->Item[i].slot.info[1];
			out->Item[i].slot.info[2] = in->Item[i].slot.info[2];
			out->Item[i].slot.info[3] = in->Item[i].slot.info[3];
		}

		return out;
	}
};


struct PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ unsigned long UniqueID;
	/* this+12 */ struct PURCHASE_ITEM_FROMMC
	              {
	              	/* this+ 0 */ int price;
	              	/* this+ 4 */ short count;
	              	/* this+ 6 */ short index;
	              	/* this+ 8 */ unsigned char type;
	              	/* this+ 9 */ unsigned short ITID;
	              	/* this+11 */ bool IsIdentified;
	              	/* this+12 */ bool IsDamaged;
	              	/* this+13 */ unsigned char refiningLevel;
	              	/* this+14 */ EQUIPSLOTINFO slot;
	              }
	              Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC2,PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC2::PURCHASE_ITEM_FROMMC> in(p);
		TPacket<PROTO_ZC_PC_PURCHASE_ITEMLIST_FROMMC,PROTO_ZC_PC_PURCHASE_ITEMLIST_FROMMC::PURCHASE_ITEM_FROMMC> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->UniqueID = in->UniqueID;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].price = in->Item[i].price;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].index = in->Item[i].index;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].IsDamaged = in->Item[i].IsDamaged;
			out->Item[i].refiningLevel = in->Item[i].refiningLevel;
			out->Item[i].slot.info[0] = in->Item[i].slot.info[0];
			out->Item[i].slot.info[1] = in->Item[i].slot.info[1];
			out->Item[i].slot.info[2] = in->Item[i].slot.info[2];
			out->Item[i].slot.info[3] = in->Item[i].slot.info[3];
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PC_PURCHASE_ITEMLIST_FROMMC,PROTO_ZC_PC_PURCHASE_ITEMLIST_FROMMC::PURCHASE_ITEM_FROMMC> in(p);
		TPacket<PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC2,PACKET_ZC_PC_PURCHASE_ITEMLIST_FROMMC2::PURCHASE_ITEM_FROMMC> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AID = in->AID;
		out->UniqueID = in->UniqueID;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].price = in->Item[i].price;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].index = in->Item[i].index;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].IsDamaged = in->Item[i].IsDamaged;
			out->Item[i].refiningLevel = in->Item[i].refiningLevel;
			out->Item[i].slot.info[0] = in->Item[i].slot.info[0];
			out->Item[i].slot.info[1] = in->Item[i].slot.info[1];
			out->Item[i].slot.info[2] = in->Item[i].slot.info[2];
			out->Item[i].slot.info[3] = in->Item[i].slot.info[3];
		}

		return out;
	}
};
