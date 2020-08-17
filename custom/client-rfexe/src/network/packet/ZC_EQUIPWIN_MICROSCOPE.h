struct PROTO_ZC_EQUIPWIN_MICROSCOPE
{
	short PacketType;
	short Length;
	char characterName[24];
	short job;
	short head;
	short accessory;
	short accessory2;
	short accessory3;
	short robe;
	short headpalette;
	short bodypalette;
	unsigned char sex;
	struct EQUIPMENTITEM_EXTRAINFO301
	{
		short index;
		unsigned short ITID;
		unsigned char type;
		bool IsIdentified;
		unsigned short location;
		unsigned short WearState;
		bool IsDamaged;
		unsigned char RefiningLevel;
		EQUIPSLOTINFO slot;
		long HireExpireDate;
		unsigned short bindOnEquipType;
		unsigned short wItemSpriteNumber;
	}
	Item[];
};


struct PACKET_ZC_EQUIPWIN_MICROSCOPE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short Length;
	/* this+ 4 */ char characterName[24];
	/* this+28 */ short job;
	/* this+30 */ short head;
	/* this+32 */ short accessory;
	/* this+34 */ short accessory2;
	/* this+36 */ short accessory3;
	/* this+38 */ short headpalette;
	/* this+40 */ short bodypalette;
	/* this+42 */ unsigned char sex;
	/* this+43 */ struct EQUIPMENTITEM_EXTRAINFO3
	              {
	              	/* this+ 0 */ short index;
	              	/* this+ 2 */ unsigned short ITID;
	              	/* this+ 4 */ unsigned char type;
	              	/* this+ 5 */ bool IsIdentified;
	              	/* this+ 6 */ unsigned short location;
	              	/* this+ 8 */ unsigned short WearState;
	              	/* this+10 */ bool IsDamaged;
	              	/* this+11 */ unsigned char RefiningLevel;
	              	/* this+12 */ EQUIPSLOTINFO slot;
	              	/* this+20 */ long HireExpireDate;
	              	/* this+24 */ unsigned short bindOnEquipType;
	              }
	              Item[];


	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_EQUIPWIN_MICROSCOPE,PACKET_ZC_EQUIPWIN_MICROSCOPE::EQUIPMENTITEM_EXTRAINFO3> in(p);
		TPacket<PROTO_ZC_EQUIPWIN_MICROSCOPE,PROTO_ZC_EQUIPWIN_MICROSCOPE::EQUIPMENTITEM_EXTRAINFO301> out(in.count());

		out->PacketType = PacketType;
		out->Length = out.size();
		memcpy(out->characterName, in->characterName, 24);
		out->job = in->job;
		out->head = in->head;
		out->accessory = in->accessory;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->robe = 0; // adapt
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->sex = in->sex;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].location = in->Item[i].location;
			out->Item[i].WearState = in->Item[i].WearState;
			out->Item[i].IsDamaged = in->Item[i].IsDamaged;
			out->Item[i].RefiningLevel = in->Item[i].RefiningLevel;
			out->Item[i].slot = in->Item[i].slot;
			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate;
			out->Item[i].bindOnEquipType = in->Item[i].bindOnEquipType;
			out->Item[i].wItemSpriteNumber = 0; // adapt
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_EQUIPWIN_MICROSCOPE,PROTO_ZC_EQUIPWIN_MICROSCOPE::EQUIPMENTITEM_EXTRAINFO301> in(p);
		TPacket<PACKET_ZC_EQUIPWIN_MICROSCOPE,PACKET_ZC_EQUIPWIN_MICROSCOPE::EQUIPMENTITEM_EXTRAINFO3> out(in.count());

		out->PacketType = PacketType;
		out->Length = out.size();
		memcpy(out->characterName, in->characterName, 24);
		out->job = in->job;
		out->head = in->head;
		out->accessory = in->accessory;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
//		out->robe = in->robe; // adapt
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->sex = in->sex;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].location = in->Item[i].location;
			out->Item[i].WearState = in->Item[i].WearState;
			out->Item[i].IsDamaged = in->Item[i].IsDamaged;
			out->Item[i].RefiningLevel = in->Item[i].RefiningLevel;
			out->Item[i].slot = in->Item[i].slot;
			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate;
			out->Item[i].bindOnEquipType = in->Item[i].bindOnEquipType;
//			out->Item[i].wItemSpriteNumber = in->Item[i].wItemSpriteNumber; // adapt
		}

		return out;
	}
};


struct PACKET_ZC_EQUIPWIN_MICROSCOPE2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short Length;
	/* this+ 4 */ char characterName[24];
	/* this+28 */ short job;
	/* this+30 */ short head;
	/* this+32 */ short accessory;
	/* this+34 */ short accessory2;
	/* this+36 */ short accessory3;
	/* this+38 */ short robe;
	/* this+40 */ short headpalette;
	/* this+42 */ short bodypalette;
	/* this+44 */ unsigned char sex;
	/* this+45 */ struct EQUIPMENTITEM_EXTRAINFO301
	              {
	              	/* this+ 0 */ short index;
	              	/* this+ 2 */ unsigned short ITID;
	              	/* this+ 4 */ unsigned char type;
	              	/* this+ 5 */ bool IsIdentified;
	              	/* this+ 6 */ unsigned short location;
	              	/* this+ 8 */ unsigned short WearState;
	              	/* this+10 */ bool IsDamaged;
	              	/* this+11 */ unsigned char RefiningLevel;
	              	/* this+12 */ EQUIPSLOTINFO slot;
	              	/* this+20 */ long HireExpireDate;
	              	/* this+24 */ unsigned short bindOnEquipType;
	              	/* this+26 */ unsigned short wItemSpriteNumber;
	              }
	              Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_EQUIPWIN_MICROSCOPE2,PACKET_ZC_EQUIPWIN_MICROSCOPE2::EQUIPMENTITEM_EXTRAINFO301> in(p);
		TPacket<PROTO_ZC_EQUIPWIN_MICROSCOPE,PROTO_ZC_EQUIPWIN_MICROSCOPE::EQUIPMENTITEM_EXTRAINFO301> out(in.count());

		out->PacketType = PacketType;
		out->Length = out.size();
		memcpy(out->characterName, in->characterName, 24);
		out->job = in->job;
		out->head = in->head;
		out->accessory = in->accessory;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->robe = in->robe;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->sex = in->sex;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].location = in->Item[i].location;
			out->Item[i].WearState = in->Item[i].WearState;
			out->Item[i].IsDamaged = in->Item[i].IsDamaged;
			out->Item[i].RefiningLevel = in->Item[i].RefiningLevel;
			out->Item[i].slot = in->Item[i].slot;
			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate;
			out->Item[i].bindOnEquipType = in->Item[i].bindOnEquipType;
			out->Item[i].wItemSpriteNumber = in->Item[i].wItemSpriteNumber;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_EQUIPWIN_MICROSCOPE,PROTO_ZC_EQUIPWIN_MICROSCOPE::EQUIPMENTITEM_EXTRAINFO301> in(p);
		TPacket<PACKET_ZC_EQUIPWIN_MICROSCOPE2,PACKET_ZC_EQUIPWIN_MICROSCOPE2::EQUIPMENTITEM_EXTRAINFO301> out(in.count());

		out->PacketType = PacketType;
		out->Length = out.size();
		memcpy(out->characterName, in->characterName, 24);
		out->job = in->job;
		out->head = in->head;
		out->accessory = in->accessory;
		out->accessory2 = in->accessory2;
		out->accessory3 = in->accessory3;
		out->robe = in->robe;
		out->headpalette = in->headpalette;
		out->bodypalette = in->bodypalette;
		out->sex = in->sex;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].location = in->Item[i].location;
			out->Item[i].WearState = in->Item[i].WearState;
			out->Item[i].IsDamaged = in->Item[i].IsDamaged;
			out->Item[i].RefiningLevel = in->Item[i].RefiningLevel;
			out->Item[i].slot = in->Item[i].slot;
			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate;
			out->Item[i].bindOnEquipType = in->Item[i].bindOnEquipType;
			out->Item[i].wItemSpriteNumber = in->Item[i].wItemSpriteNumber;
		}

		return out;
	}
};
