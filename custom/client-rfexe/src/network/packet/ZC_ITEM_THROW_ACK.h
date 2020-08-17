struct PROTO_ZC_ITEM_THROW_ACK
{
	enum
	{
		DELETE_TYPE_NORMAL          = 0,
		DELETE_TYPE_USE_SKILL       = 1,
		DELETE_TYPE_FAIL_REFINING   = 2,
		DELETE_TYPE_CHANGE_MATERIAL = 3,
		DELETE_TYPE_MOVETO_STORE    = 4,
		DELETE_TYPE_MOVETO_CART     = 5,
		DELETE_TYPE_SELL_ITEM       = 6,
		DELETE_TYPE_EL_ANALYSIS     = 7,
	};

	short PacketType;
	short DeleteType;
	unsigned short Index;
	short Count;
};


struct PACKET_ZC_ITEM_THROW_ACK
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned short Index;
	/* this+4 */ short count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ITEM_THROW_ACK> in(p);
		TPacket<PROTO_ZC_ITEM_THROW_ACK> out;

		out->PacketType = PacketType;
		out->DeleteType = PROTO_ZC_ITEM_THROW_ACK::DELETE_TYPE_NORMAL; // adapt
		out->Index = in->Index;
		out->Count = in->count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ITEM_THROW_ACK> in(p);
		TPacket<PACKET_ZC_ITEM_THROW_ACK> out;

		out->PacketType = PacketType;
//		out->DeleteType = in->DeleteType; // adapt
		out->Index = in->Index;
		out->count = in->Count;

		return out;
	}
};


struct PACKET_ZC_DELETE_ITEM_FROM_BODY
{
	enum
	{
		DELETE_TYPE_NORMAL          = 0,
		DELETE_TYPE_USE_SKILL       = 1,
		DELETE_TYPE_FAIL_REFINING   = 2,
		DELETE_TYPE_CHANGE_MATERIAL = 3,
		DELETE_TYPE_MOVETO_STORE    = 4,
		DELETE_TYPE_MOVETO_CART     = 5,
		DELETE_TYPE_SELL_ITEM       = 6,
		DELETE_TYPE_EL_ANALYSIS     = 7,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ short DeleteType;
	/* this+4 */ unsigned short Index;
	/* this+6 */ short Count;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_DELETE_ITEM_FROM_BODY> in(p);
		TPacket<PROTO_ZC_ITEM_THROW_ACK> out;

		out->PacketType = PacketType;
		out->DeleteType = in->DeleteType;
		out->Index = in->Index;
		out->Count = in->Count;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ITEM_THROW_ACK> in(p);
		TPacket<PACKET_ZC_DELETE_ITEM_FROM_BODY> out;

		out->PacketType = PacketType;
		out->DeleteType = in->DeleteType;
		out->Index = in->Index;
		out->Count = in->Count;

		return out;
	}
};
