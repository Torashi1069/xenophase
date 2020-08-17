struct PROTO_ZC_STORE_NORMAL_ITEMLIST
{
	short PacketType;
	short PacketLength;
	struct ITEM
	{
		short index;
		unsigned short ITID;
		unsigned char type;
		bool IsIdentified;
		short count;
		unsigned short WearState;
		EQUIPSLOTINFO slot;
		long HireExpireDate;
	}
	Item[];
};


struct PACKET_ZC_STORE_NORMAL_ITEMLIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct ITEM
	             {
	             	/* this+ 0 */ short index;
	             	/* this+ 2 */ unsigned short ITID;
	             	/* this+ 4 */ unsigned char type;
	             	/* this+ 5 */ bool IsIdentified;
	             	/* this+ 6 */ short count;
	             	/* this+ 8 */ unsigned short WearState;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_STORE_NORMAL_ITEMLIST,PACKET_ZC_STORE_NORMAL_ITEMLIST::ITEM> in(p);
		TPacket<PROTO_ZC_STORE_NORMAL_ITEMLIST,PROTO_ZC_STORE_NORMAL_ITEMLIST::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].WearState = in->Item[i].WearState;
			out->Item[i].slot.info[0] = 0; // adapt
			out->Item[i].slot.info[1] = 0; // adapt
			out->Item[i].slot.info[2] = 0; // adapt
			out->Item[i].slot.info[3] = 0; // adapt
			out->Item[i].HireExpireDate = 0; // adapt
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_STORE_NORMAL_ITEMLIST,PROTO_ZC_STORE_NORMAL_ITEMLIST::ITEM> in(p);
		TPacket<PACKET_ZC_STORE_NORMAL_ITEMLIST,PACKET_ZC_STORE_NORMAL_ITEMLIST::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].WearState = in->Item[i].WearState;
//			out->Item[i].slot.info[0] = in->Item[i].slot.info[0]; // adapt
//			out->Item[i].slot.info[1] = in->Item[i].slot.info[1]; // adapt
//			out->Item[i].slot.info[2] = in->Item[i].slot.info[2]; // adapt
//			out->Item[i].slot.info[3] = in->Item[i].slot.info[3]; // adapt
//			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate; // adapt
		}

		return out;
	}
};


struct PACKET_ZC_STORE_NORMAL_ITEMLIST2
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct ITEM
	             {
	             	/* this+ 0 */ short index;
	             	/* this+ 2 */ unsigned short ITID;
	             	/* this+ 4 */ unsigned char type;
	             	/* this+ 5 */ bool IsIdentified;
	             	/* this+ 6 */ short count;
	             	/* this+ 8 */ unsigned short WearState;
	             	/* this+10 */ EQUIPSLOTINFO slot;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_STORE_NORMAL_ITEMLIST2,PACKET_ZC_STORE_NORMAL_ITEMLIST2::ITEM> in(p);
		TPacket<PROTO_ZC_STORE_NORMAL_ITEMLIST,PROTO_ZC_STORE_NORMAL_ITEMLIST::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].WearState = in->Item[i].WearState;
			out->Item[i].slot.info[0] = in->Item[i].slot.info[0];
			out->Item[i].slot.info[1] = in->Item[i].slot.info[1];
			out->Item[i].slot.info[2] = in->Item[i].slot.info[2];
			out->Item[i].slot.info[3] = in->Item[i].slot.info[3];
			out->Item[i].HireExpireDate = 0; // adapt
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_STORE_NORMAL_ITEMLIST,PROTO_ZC_STORE_NORMAL_ITEMLIST::ITEM> in(p);
		TPacket<PACKET_ZC_STORE_NORMAL_ITEMLIST2,PACKET_ZC_STORE_NORMAL_ITEMLIST2::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].WearState = in->Item[i].WearState;
			out->Item[i].slot.info[0] = in->Item[i].slot.info[0];
			out->Item[i].slot.info[1] = in->Item[i].slot.info[1];
			out->Item[i].slot.info[2] = in->Item[i].slot.info[2];
			out->Item[i].slot.info[3] = in->Item[i].slot.info[3];
//			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate; // adapt
		}

		return out;
	}
};


struct PACKET_ZC_STORE_NORMAL_ITEMLIST3
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct ITEM
	             {
	             	/* this+ 0 */ short index;
	             	/* this+ 2 */ unsigned short ITID;
	             	/* this+ 4 */ unsigned char type;
	             	/* this+ 5 */ bool IsIdentified;
	             	/* this+ 6 */ short count;
	             	/* this+ 8 */ unsigned short WearState;
	             	/* this+10 */ EQUIPSLOTINFO slot;
	             	/* this+18 */ long HireExpireDate;
	             }
	             Item[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_STORE_NORMAL_ITEMLIST3,PACKET_ZC_STORE_NORMAL_ITEMLIST3::ITEM> in(p);
		TPacket<PROTO_ZC_STORE_NORMAL_ITEMLIST,PROTO_ZC_STORE_NORMAL_ITEMLIST::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].WearState = in->Item[i].WearState;
			out->Item[i].slot.info[0] = in->Item[i].slot.info[0];
			out->Item[i].slot.info[1] = in->Item[i].slot.info[1];
			out->Item[i].slot.info[2] = in->Item[i].slot.info[2];
			out->Item[i].slot.info[3] = in->Item[i].slot.info[3];
			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_STORE_NORMAL_ITEMLIST,PROTO_ZC_STORE_NORMAL_ITEMLIST::ITEM> in(p);
		TPacket<PACKET_ZC_STORE_NORMAL_ITEMLIST3,PACKET_ZC_STORE_NORMAL_ITEMLIST3::ITEM> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Item[i].index = in->Item[i].index;
			out->Item[i].ITID = in->Item[i].ITID;
			out->Item[i].type = in->Item[i].type;
			out->Item[i].IsIdentified = in->Item[i].IsIdentified;
			out->Item[i].count = in->Item[i].count;
			out->Item[i].WearState = in->Item[i].WearState;
			out->Item[i].slot.info[0] = in->Item[i].slot.info[0];
			out->Item[i].slot.info[1] = in->Item[i].slot.info[1];
			out->Item[i].slot.info[2] = in->Item[i].slot.info[2];
			out->Item[i].slot.info[3] = in->Item[i].slot.info[3];
			out->Item[i].HireExpireDate = in->Item[i].HireExpireDate;
		}

		return out;
	}
};
