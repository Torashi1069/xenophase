struct PROTO_ZC_EQUIPMENT_ITEMLIST
{
	short PacketType;
	short PacketLength;
	struct ITEM
	{
		short index;
		unsigned short ITID;
		unsigned char type;
		bool IsIdentified;
		short location;
		short wearLocation;
		unsigned char isDamaged;
		unsigned char refiningLevel;
		EQUIPSLOTINFO slot;
		long HireExpireDate;
		unsigned short bindOnEquipType;
		unsigned short wItemSpriteNumber;
	}
	Item[];
};


struct PACKET_ZC_EQUIPMENT_ITEMLIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct ITEM
	             {
	             	/* this+ 0 */ short index;
	             	/* this+ 2 */ unsigned short ITID;
	             	/* this+ 4 */ unsigned char type;
	             	/* this+ 5 */ bool IsIdentified;
	             	/* this+ 6 */ short location;
	             	/* this+ 8 */ short wearLocation;
	             	/* this+10 */ unsigned char isDamaged;
	             	/* this+11 */ unsigned char refiningLevel;
	             	/* this+12 */ EQUIPSLOTINFO slot;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_EQUIPMENT_ITEMLIST,PACKET_ZC_EQUIPMENT_ITEMLIST::ITEM> in(p);
		TPacket<PROTO_ZC_EQUIPMENT_ITEMLIST,PROTO_ZC_EQUIPMENT_ITEMLIST::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].location = in->Item[i].location;
			out->Item[i].wearLocation = in->Item[i].wearLocation;
			out->Item[i].isDamaged = in->Item[i].isDamaged;
			out->Item[i].refiningLevel = in->Item[i].refiningLevel;
			memcpy(&out->Item[i].slot, &in->Item[i].slot, sizeof(out->Item[i].slot));
			out->Item[i].HireExpireDate = 0; // adapt
			out->Item[i].bindOnEquipType = 0; // adapt
			out->Item[i].wItemSpriteNumber = 0; // adapt
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_EQUIPMENT_ITEMLIST,PROTO_ZC_EQUIPMENT_ITEMLIST::ITEM> in(p);
		TPacket<PACKET_ZC_EQUIPMENT_ITEMLIST,PACKET_ZC_EQUIPMENT_ITEMLIST::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].location = in->Item[i].location;
			out->Item[i].wearLocation = in->Item[i].wearLocation;
			out->Item[i].isDamaged = in->Item[i].isDamaged;
			out->Item[i].refiningLevel = in->Item[i].refiningLevel;
			memcpy(&out->Item[i].slot, &in->Item[i].slot, sizeof(out->Item[i].slot));
//			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate; // adapt
//			out->Item[i].bindOnEquipType = in->Item[i].bindOnEquipType; // adapt
//			out->Item[i].wItemSpriteNumber = in->Item[i].wItemSpriteNumber; // adapt
		}

		return out;
	}
};


struct PACKET_ZC_EQUIPMENT_ITEMLIST2
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct ITEM
	             {
	             	/* this+ 0 */ short index;
	             	/* this+ 2 */ unsigned short ITID;
	             	/* this+ 4 */ unsigned char type;
	             	/* this+ 5 */ bool IsIdentified;
	             	/* this+ 6 */ short location;
	             	/* this+ 8 */ short wearLocation;
	             	/* this+10 */ unsigned char isDamaged;
	             	/* this+11 */ unsigned char refiningLevel;
	             	/* this+12 */ EQUIPSLOTINFO slot;
	             	/* this+20 */ int HireExpireDate;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_EQUIPMENT_ITEMLIST2,PACKET_ZC_EQUIPMENT_ITEMLIST2::ITEM> in(p);
		TPacket<PROTO_ZC_EQUIPMENT_ITEMLIST,PROTO_ZC_EQUIPMENT_ITEMLIST::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].location = in->Item[i].location;
			out->Item[i].wearLocation = in->Item[i].wearLocation;
			out->Item[i].isDamaged = in->Item[i].isDamaged;
			out->Item[i].refiningLevel = in->Item[i].refiningLevel;
			memcpy(&out->Item[i].slot, &in->Item[i].slot, sizeof(out->Item[i].slot));
			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate;
			out->Item[i].bindOnEquipType = 0; // adapt
			out->Item[i].wItemSpriteNumber = 0; // adapt
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_EQUIPMENT_ITEMLIST,PROTO_ZC_EQUIPMENT_ITEMLIST::ITEM> in(p);
		TPacket<PACKET_ZC_EQUIPMENT_ITEMLIST2,PACKET_ZC_EQUIPMENT_ITEMLIST2::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].location = in->Item[i].location;
			out->Item[i].wearLocation = in->Item[i].wearLocation;
			out->Item[i].isDamaged = in->Item[i].isDamaged;
			out->Item[i].refiningLevel = in->Item[i].refiningLevel;
			memcpy(&out->Item[i].slot, &in->Item[i].slot, sizeof(out->Item[i].slot));
			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate;
//			out->Item[i].bindOnEquipType = in->Item[i].bindOnEquipType; // adapt
//			out->Item[i].wItemSpriteNumber = in->Item[i].wItemSpriteNumber; // adapt
		}

		return out;
	}
};


struct PACKET_ZC_EQUIPMENT_ITEMLIST3
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct ITEM
	             {
	             	/* this+ 0 */ short index;
	             	/* this+ 2 */ unsigned short ITID;
	             	/* this+ 4 */ unsigned char type;
	             	/* this+ 5 */ bool IsIdentified;
	             	/* this+ 6 */ short location;
	             	/* this+ 8 */ short wearLocation;
	             	/* this+10 */ unsigned char isDamaged;
	             	/* this+11 */ unsigned char refiningLevel;
	             	/* this+12 */ EQUIPSLOTINFO slot;
	             	/* this+20 */ long HireExpireDate;
	             	/* this+24 */ unsigned short bindOnEquipType;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_EQUIPMENT_ITEMLIST3,PACKET_ZC_EQUIPMENT_ITEMLIST3::ITEM> in(p);
		TPacket<PROTO_ZC_EQUIPMENT_ITEMLIST,PROTO_ZC_EQUIPMENT_ITEMLIST::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].location = in->Item[i].location;
			out->Item[i].wearLocation = in->Item[i].wearLocation;
			out->Item[i].isDamaged = in->Item[i].isDamaged;
			out->Item[i].refiningLevel = in->Item[i].refiningLevel;
			memcpy(&out->Item[i].slot, &in->Item[i].slot, sizeof(out->Item[i].slot));
			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate;
			out->Item[i].bindOnEquipType = in->Item[i].bindOnEquipType;
			out->Item[i].wItemSpriteNumber = 0; // adapt
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_EQUIPMENT_ITEMLIST,PROTO_ZC_EQUIPMENT_ITEMLIST::ITEM> in(p);
		TPacket<PACKET_ZC_EQUIPMENT_ITEMLIST3,PACKET_ZC_EQUIPMENT_ITEMLIST3::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].location = in->Item[i].location;
			out->Item[i].wearLocation = in->Item[i].wearLocation;
			out->Item[i].isDamaged = in->Item[i].isDamaged;
			out->Item[i].refiningLevel = in->Item[i].refiningLevel;
			memcpy(&out->Item[i].slot, &in->Item[i].slot, sizeof(out->Item[i].slot));
			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate;
			out->Item[i].bindOnEquipType = in->Item[i].bindOnEquipType;
//			out->Item[i].wItemSpriteNumber = in->Item[i].wItemSpriteNumber; // adapt
		}

		return out;
	}
};


//TODO: determine real origin date
struct PACKET_ZC_EQUIPMENT_ITEMLIST3__KRO20120207
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct EQUIPMENTITEM_EXTRAINFO301
	             {
	             	/* this+ 0 */ short index;
	             	/* this+ 2 */ unsigned short ITID;
	             	/* this+ 4 */ unsigned char type;
	             	/* this+ 5 */ bool IsIdentified;
	             	/* this+ 6 */ short location;
	             	/* this+ 8 */ short wearLocation;
	             	/* this+10 */ unsigned char isDamaged;
	             	/* this+11 */ unsigned char refiningLevel;
	             	/* this+12 */ EQUIPSLOTINFO slot;
	             	/* this+20 */ long HireExpireDate;
	             	/* this+24 */ unsigned short bindOnEquipType;
	             	/* this+26 */ unsigned short wItemSpriteNumber;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_EQUIPMENT_ITEMLIST3__KRO20120207,PACKET_ZC_EQUIPMENT_ITEMLIST3__KRO20120207::EQUIPMENTITEM_EXTRAINFO301> in(p);
		TPacket<PROTO_ZC_EQUIPMENT_ITEMLIST,PROTO_ZC_EQUIPMENT_ITEMLIST::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].location = in->Item[i].location;
			out->Item[i].wearLocation = in->Item[i].wearLocation;
			out->Item[i].isDamaged = in->Item[i].isDamaged;
			out->Item[i].refiningLevel = in->Item[i].refiningLevel;
			memcpy(&out->Item[i].slot, &in->Item[i].slot, sizeof(out->Item[i].slot));
			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate;
			out->Item[i].bindOnEquipType = in->Item[i].bindOnEquipType;
			out->Item[i].wItemSpriteNumber = in->Item[i].wItemSpriteNumber;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_EQUIPMENT_ITEMLIST,PROTO_ZC_EQUIPMENT_ITEMLIST::ITEM> in(p);
		TPacket<PACKET_ZC_EQUIPMENT_ITEMLIST3__KRO20120207,PACKET_ZC_EQUIPMENT_ITEMLIST3__KRO20120207::EQUIPMENTITEM_EXTRAINFO301> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].location = in->Item[i].location;
			out->Item[i].wearLocation = in->Item[i].wearLocation;
			out->Item[i].isDamaged = in->Item[i].isDamaged;
			out->Item[i].refiningLevel = in->Item[i].refiningLevel;
			memcpy(&out->Item[i].slot, &in->Item[i].slot, sizeof(out->Item[i].slot));
			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate;
			out->Item[i].bindOnEquipType = in->Item[i].bindOnEquipType;
			out->Item[i].wItemSpriteNumber = in->Item[i].wItemSpriteNumber;
		}

		return out;
	}
};
