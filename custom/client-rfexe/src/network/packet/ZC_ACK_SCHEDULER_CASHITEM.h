struct PROTO_ZC_ACK_SCHEDULER_CASHITEM
{
	short PacketType;
	short PacketLength;
	short ItemCount;
	short TabCode;
	struct CASH_ITEM_LIST2
	{
		unsigned short item_id;
		int price;
	}
	List[];
};


struct PACKET_ZC_ACK_SCHEDULER_CASHITEM
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ short ItemCount;
	/* this+6 */ short TabCode;
	/* this+8 */ struct CASH_ITEM_LIST2
	             {
	             	/* this+0 */ unsigned short item_id;
	             	/* this+2 */ int price;
	             }
	             List[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_SCHEDULER_CASHITEM,PACKET_ZC_ACK_SCHEDULER_CASHITEM::CASH_ITEM_LIST2> in(p);
		TPacket<PROTO_ZC_ACK_SCHEDULER_CASHITEM,PROTO_ZC_ACK_SCHEDULER_CASHITEM::CASH_ITEM_LIST2> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->List[i].item_id = in->List[i].item_id;
			out->List[i].price = in->List[i].price;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_SCHEDULER_CASHITEM,PROTO_ZC_ACK_SCHEDULER_CASHITEM::CASH_ITEM_LIST2> in(p);
		TPacket<PACKET_ZC_ACK_SCHEDULER_CASHITEM,PACKET_ZC_ACK_SCHEDULER_CASHITEM::CASH_ITEM_LIST2> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->List[i].item_id = in->List[i].item_id;
			out->List[i].price = in->List[i].price;
		}

		return out;
	}
};
