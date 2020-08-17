struct PROTO_ZC_ITEM_PICKUP_ACK
{
	short PacketType;
	unsigned short Index;
	unsigned short count;
	unsigned short ITID;
	bool IsIdentified;
	bool IsDamaged;
	unsigned char refiningLevel;
	EQUIPSLOTINFO slot;
	unsigned short location;
	unsigned char type;
	unsigned char result;
	long HireExpireDate;
	unsigned short bindOnEquipType;
};


struct PACKET_ZC_ITEM_PICKUP_ACK
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short Index;
	/* this+ 4 */ unsigned short count;
	/* this+ 6 */ unsigned short ITID;
	/* this+ 8 */ bool IsIdentified;
	/* this+ 9 */ bool IsDamaged;
	/* this+10 */ unsigned char refiningLevel;
	/* this+11 */ EQUIPSLOTINFO slot;
	/* this+19 */ unsigned short location;
	/* this+21 */ unsigned char type;
	/* this+22 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ITEM_PICKUP_ACK> in(p);
		TPacket<PROTO_ZC_ITEM_PICKUP_ACK> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->count = in->count;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->IsDamaged = in->IsDamaged;
		out->refiningLevel = in->refiningLevel;
		memcpy(&out->slot, &in->slot, sizeof(EQUIPSLOTINFO));
		out->location = in->location;
		out->type = in->type;
		out->result = in->result;
		out->HireExpireDate = 0; // adapt
		out->bindOnEquipType = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ITEM_PICKUP_ACK> in(p);
		TPacket<PACKET_ZC_ITEM_PICKUP_ACK> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->count = in->count;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->IsDamaged = in->IsDamaged;
		out->refiningLevel = in->refiningLevel;
		memcpy(&out->slot, &in->slot, sizeof(EQUIPSLOTINFO));
		out->location = in->location;
		out->type = in->type;
		out->result = in->result;
//		out->HireExpireDate = in->HireExpireDate; // adapt
//		out->bindOnEquipType = in->bindOnEquipType; // adapt

		return out;
	}
};


struct PACKET_ZC_ITEM_PICKUP_ACK2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short Index;
	/* this+ 4 */ unsigned short count;
	/* this+ 6 */ unsigned short ITID;
	/* this+ 8 */ bool IsIdentified;
	/* this+ 9 */ bool IsDamaged;
	/* this+10 */ unsigned char refiningLevel;
	/* this+11 */ EQUIPSLOTINFO slot;
	/* this+19 */ unsigned short location;
	/* this+21 */ unsigned char type;
	/* this+22 */ unsigned char result;
	/* this+23 */ long HireExpireDate;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ITEM_PICKUP_ACK2> in(p);
		TPacket<PROTO_ZC_ITEM_PICKUP_ACK> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->count = in->count;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->IsDamaged = in->IsDamaged;
		out->refiningLevel = in->refiningLevel;
		memcpy(&out->slot, &in->slot, sizeof(EQUIPSLOTINFO));
		out->location = in->location;
		out->type = in->type;
		out->result = in->result;
		out->HireExpireDate = in->HireExpireDate;
		out->bindOnEquipType = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ITEM_PICKUP_ACK> in(p);
		TPacket<PACKET_ZC_ITEM_PICKUP_ACK2> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->count = in->count;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->IsDamaged = in->IsDamaged;
		out->refiningLevel = in->refiningLevel;
		memcpy(&out->slot, &in->slot, sizeof(EQUIPSLOTINFO));
		out->location = in->location;
		out->type = in->type;
		out->result = in->result;
		out->HireExpireDate = in->HireExpireDate;
//		out->bindOnEquipType = in->bindOnEquipType; // adapt

		return out;
	}
};


struct PACKET_ZC_ITEM_PICKUP_ACK3
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short Index;
	/* this+ 4 */ unsigned short count;
	/* this+ 6 */ unsigned short ITID;
	/* this+ 8 */ bool IsIdentified;
	/* this+ 9 */ bool IsDamaged;
	/* this+10 */ unsigned char refiningLevel;
	/* this+11 */ EQUIPSLOTINFO slot;
	/* this+19 */ unsigned short location;
	/* this+21 */ unsigned char type;
	/* this+22 */ unsigned char result;
	/* this+23 */ long HireExpireDate;
	/* this+27 */ unsigned short bindOnEquipType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ITEM_PICKUP_ACK3> in(p);
		TPacket<PROTO_ZC_ITEM_PICKUP_ACK> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->count = in->count;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->IsDamaged = in->IsDamaged;
		out->refiningLevel = in->refiningLevel;
		memcpy(&out->slot, &in->slot, sizeof(EQUIPSLOTINFO));
		out->location = in->location;
		out->type = in->type;
		out->result = in->result;
		out->HireExpireDate = in->HireExpireDate;
		out->bindOnEquipType = in->bindOnEquipType;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ITEM_PICKUP_ACK> in(p);
		TPacket<PACKET_ZC_ITEM_PICKUP_ACK3> out;

		out->PacketType = PacketType;
		out->Index = in->Index;
		out->count = in->count;
		out->ITID = in->ITID;
		out->IsIdentified = in->IsIdentified;
		out->IsDamaged = in->IsDamaged;
		out->refiningLevel = in->refiningLevel;
		memcpy(&out->slot, &in->slot, sizeof(EQUIPSLOTINFO));
		out->location = in->location;
		out->type = in->type;
		out->result = in->result;
		out->HireExpireDate = in->HireExpireDate;
		out->bindOnEquipType = in->bindOnEquipType;

		return out;
	}
};
