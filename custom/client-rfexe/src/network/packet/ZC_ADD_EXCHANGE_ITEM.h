struct PROTO_ZC_ADD_EXCHANGE_ITEM
{
	short PacketType;
	unsigned short ITID;
	unsigned char type; // enum ITEM_TYPE 
	int count;
	bool IsIdentified;
	bool IsDamaged;
	unsigned char refiningLevel;
	EQUIPSLOTINFO slot;
};


struct PACKET_ZC_ADD_EXCHANGE_ITEM
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int count;
	/* this+ 6 */ unsigned short ITID;
	/* this+ 8 */ bool IsIdentified;
	/* this+ 9 */ bool IsDamaged;
	/* this+10 */ unsigned char refiningLevel;
	/* this+11 */ EQUIPSLOTINFO slot;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ADD_EXCHANGE_ITEM> in(p);
		TPacket<PROTO_ZC_ADD_EXCHANGE_ITEM> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;
		out->type = 4; // TYPE_ARMOR // adapt //FIXME
		out->count = in->count;
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
		TPacket<PROTO_ZC_ADD_EXCHANGE_ITEM> in(p);
		TPacket<PACKET_ZC_ADD_EXCHANGE_ITEM> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;
//		out->type = in->type; // adapt
		out->count = in->count;
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


struct PACKET_ZC_ADD_EXCHANGE_ITEM2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short ITID;
	/* this+ 4 */ unsigned char type;
	/* this+ 5 */ int count;
	/* this+ 9 */ bool IsIdentified;
	/* this+10 */ bool IsDamaged;
	/* this+11 */ unsigned char refiningLevel;
	/* this+12 */ EQUIPSLOTINFO slot;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ADD_EXCHANGE_ITEM2> in(p);
		TPacket<PROTO_ZC_ADD_EXCHANGE_ITEM> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;
		out->type = in->type;
		out->count = in->count;
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
		TPacket<PROTO_ZC_ADD_EXCHANGE_ITEM> in(p);
		TPacket<PACKET_ZC_ADD_EXCHANGE_ITEM2> out;

		out->PacketType = PacketType;
		out->ITID = in->ITID;
		out->type = in->type;
		out->count = in->count;
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
