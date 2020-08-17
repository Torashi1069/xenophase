struct PROTO_ZC_ADD_ITEM_TO_STORE
{
	short PacketType;
	short index;
	int count;
	unsigned short ITID;
	unsigned char type;
	bool IsIdentified;
	bool IsDamaged;
	unsigned char refiningLevel;
	EQUIPSLOTINFO slot;
};


struct PACKET_ZC_ADD_ITEM_TO_STORE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short index;
	/* this+ 4 */ int count;
	/* this+ 8 */ unsigned short ITID;
	/* this+10 */ bool IsIdentified;
	/* this+11 */ bool IsDamaged;
	/* this+12 */ unsigned char refiningLevel;
	/* this+13 */ EQUIPSLOTINFO slot;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ADD_ITEM_TO_STORE> in(p);
		TPacket<PROTO_ZC_ADD_ITEM_TO_STORE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;
		out->ITID = in->ITID;
		out->type = 4; // TYPE_ARMOR // adapt //FIXME
		out->IsIdentified = in->IsIdentified;
		out->IsDamaged = in->IsDamaged;
		out->refiningLevel = in->refiningLevel;
		out->slot.info[0] = in->slot.info[0];
		out->slot.info[1] = in->slot.info[1];
		out->slot.info[2] = in->slot.info[2];
		out->slot.info[3] = in->slot.info[3];

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ADD_ITEM_TO_STORE> in(p);
		TPacket<PACKET_ZC_ADD_ITEM_TO_STORE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;
		out->ITID = in->ITID;
//		out->type = in->type; // adapt
		out->IsIdentified = in->IsIdentified;
		out->IsDamaged = in->IsDamaged;
		out->refiningLevel = in->refiningLevel;
		out->slot.info[0] = in->slot.info[0];
		out->slot.info[1] = in->slot.info[1];
		out->slot.info[2] = in->slot.info[2];
		out->slot.info[3] = in->slot.info[3];

		return out;
	}
};


struct PACKET_ZC_ADD_ITEM_TO_STORE2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short index;
	/* this+ 4 */ int count;
	/* this+ 8 */ unsigned short ITID;
	/* this+10 */ unsigned char type;
	/* this+11 */ bool IsIdentified;
	/* this+12 */ bool IsDamaged;
	/* this+13 */ unsigned char refiningLevel;
	/* this+14 */ struct EQUIPSLOTINFO
	              {
	              	/* this+0 */ unsigned short info[4];
	              }
	              slot;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ADD_ITEM_TO_STORE2> in(p);
		TPacket<PROTO_ZC_ADD_ITEM_TO_STORE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;
		out->ITID = in->ITID;
		out->type = in->type;
		out->IsIdentified = in->IsIdentified;
		out->IsDamaged = in->IsDamaged;
		out->refiningLevel = in->refiningLevel;
		out->slot.info[0] = in->slot.info[0];
		out->slot.info[1] = in->slot.info[1];
		out->slot.info[2] = in->slot.info[2];
		out->slot.info[3] = in->slot.info[3];

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ADD_ITEM_TO_STORE> in(p);
		TPacket<PACKET_ZC_ADD_ITEM_TO_STORE2> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->count = in->count;
		out->ITID = in->ITID;
		out->type = in->type;
		out->IsIdentified = in->IsIdentified;
		out->IsDamaged = in->IsDamaged;
		out->refiningLevel = in->refiningLevel;
		out->slot.info[0] = in->slot.info[0];
		out->slot.info[1] = in->slot.info[1];
		out->slot.info[2] = in->slot.info[2];
		out->slot.info[3] = in->slot.info[3];

		return out;
	}
};
