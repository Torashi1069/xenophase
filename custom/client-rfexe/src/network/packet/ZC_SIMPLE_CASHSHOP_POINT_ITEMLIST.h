struct PROTO_ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST
{
	short PacketType;
	unsigned short PacketLength;
	unsigned long CashPoint;
	short md_itemcount;
	short md_itemSize;
	short best_itemcount;
	short best_itemsize;
	BYTE unknown[]; //TODO
};


struct PACKET_ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ unsigned long CashPoint;
	/* this+ 8 */ short md_itemcount;
	/* this+10 */ short md_itemSize;
	/* this+12 */ short best_itemcount;
	/* this+14 */ short best_itemsize;
	/* this+16 */ BYTE unknown[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST,BYTE> in(p);
		TPacket<PROTO_ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->CashPoint = in->CashPoint;
		out->md_itemcount = in->md_itemcount;
		out->md_itemSize = in->md_itemSize;
		out->best_itemcount = in->best_itemcount;
		out->best_itemsize = in->best_itemsize;
		memcpy(out->unknown, in->unknown, out.count());

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST,BYTE> in(p);
		TPacket<PACKET_ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST,BYTE> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->CashPoint = in->CashPoint;
		out->md_itemcount = in->md_itemcount;
		out->md_itemSize = in->md_itemSize;
		out->best_itemcount = in->best_itemcount;
		out->best_itemsize = in->best_itemsize;
		memcpy(out->unknown, in->unknown, out.count());

		return out;
	}
};
