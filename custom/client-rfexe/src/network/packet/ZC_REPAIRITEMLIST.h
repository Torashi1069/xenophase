struct PROTO_ZC_REPAIRITEMLIST
{
	short PacketType;
	short PacketLength;
	struct REPAIRITEM_INFO
	{
		short index;
		unsigned short ITID;
		unsigned char refiningLevel;
		EQUIPSLOTINFO slot;
	}
	ItemInfo[];
};


struct PACKET_ZC_REPAIRITEMLIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct REPAIRITEM_INFO
	             {
	             	/* this+0 */ short index;
	             	/* this+2 */ unsigned short ITID;
	             	/* this+4 */ unsigned char refiningLevel;
	             	/* this+5 */ EQUIPSLOTINFO slot;
	             }
	             ItemInfo[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_REPAIRITEMLIST,PACKET_ZC_REPAIRITEMLIST::REPAIRITEM_INFO> in(p);
		TPacket<PROTO_ZC_REPAIRITEMLIST,PROTO_ZC_REPAIRITEMLIST::REPAIRITEM_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->ItemInfo[i].index = in->ItemInfo[i].index;
			out->ItemInfo[i].ITID = in->ItemInfo[i].ITID;
			out->ItemInfo[i].refiningLevel = in->ItemInfo[i].refiningLevel;
			out->ItemInfo[i].slot.info[0] = in->ItemInfo[i].slot.info[0];
			out->ItemInfo[i].slot.info[1] = in->ItemInfo[i].slot.info[1];
			out->ItemInfo[i].slot.info[2] = in->ItemInfo[i].slot.info[2];
			out->ItemInfo[i].slot.info[3] = in->ItemInfo[i].slot.info[3];
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_REPAIRITEMLIST,PROTO_ZC_REPAIRITEMLIST::REPAIRITEM_INFO> in(p);
		TPacket<PACKET_ZC_REPAIRITEMLIST,PACKET_ZC_REPAIRITEMLIST::REPAIRITEM_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->ItemInfo[i].index = in->ItemInfo[i].index;
			out->ItemInfo[i].ITID = in->ItemInfo[i].ITID;
			out->ItemInfo[i].refiningLevel = in->ItemInfo[i].refiningLevel;
			out->ItemInfo[i].slot.info[0] = in->ItemInfo[i].slot.info[0];
			out->ItemInfo[i].slot.info[1] = in->ItemInfo[i].slot.info[1];
			out->ItemInfo[i].slot.info[2] = in->ItemInfo[i].slot.info[2];
			out->ItemInfo[i].slot.info[3] = in->ItemInfo[i].slot.info[3];
		}

		return out;
	}
};
