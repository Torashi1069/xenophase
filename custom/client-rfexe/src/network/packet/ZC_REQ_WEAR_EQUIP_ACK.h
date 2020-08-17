struct PROTO_ZC_REQ_WEAR_EQUIP_ACK
{
	short PacketType;
	unsigned short index;
	unsigned short wearLocation;
	unsigned short wItemSpriteNumber;
	unsigned char result;
};


struct PACKET_ZC_REQ_WEAR_EQUIP_ACK
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned short wearLocation;
	/* this+6 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_REQ_WEAR_EQUIP_ACK> in(p);
		TPacket<PROTO_ZC_REQ_WEAR_EQUIP_ACK> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->wearLocation = in->wearLocation;
		out->wItemSpriteNumber = 0; // adapt
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_REQ_WEAR_EQUIP_ACK> in(p);
		TPacket<PACKET_ZC_REQ_WEAR_EQUIP_ACK> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->wearLocation = in->wearLocation;
//		out->wItemSpriteNumber = in->wItemSpriteNumber; // adapt
		out->result = in->result;

		return out;
	}
};


struct PACKET_ZC_REQ_WEAR_EQUIP_ACK__FRANCE20131015
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short index;
	/* this+4 */ unsigned short wearLocation;
	/* this+6 */ unsigned short wItemSpriteNumber;
	/* this+8 */ unsigned char result;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_REQ_WEAR_EQUIP_ACK__FRANCE20131015> in(p);
		TPacket<PROTO_ZC_REQ_WEAR_EQUIP_ACK> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->wearLocation = in->wearLocation;
		out->wItemSpriteNumber = in->wItemSpriteNumber;
		out->result = in->result;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_REQ_WEAR_EQUIP_ACK> in(p);
		TPacket<PACKET_ZC_REQ_WEAR_EQUIP_ACK__FRANCE20131015> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->wearLocation = in->wearLocation;
		out->wItemSpriteNumber = in->wItemSpriteNumber;
		out->result = in->result;

		return out;
	}
};
