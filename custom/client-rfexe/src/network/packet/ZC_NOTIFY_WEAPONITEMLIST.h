struct PROTO_ZC_NOTIFY_WEAPONITEMLIST
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
	Info[];
};


struct PACKET_ZC_NOTIFY_WEAPONITEMLIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+2 */ struct REPAIRITEM_INFO
	             {
	             	/* this+0 */ short index;
	             	/* this+2 */ unsigned short ITID;
	             	/* this+4 */ unsigned char refiningLevel;
	             	/* this+5 */ EQUIPSLOTINFO slot;
	             }
	             Info[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_WEAPONITEMLIST,PACKET_ZC_NOTIFY_WEAPONITEMLIST::REPAIRITEM_INFO> in(p);
		TPacket<PROTO_ZC_NOTIFY_WEAPONITEMLIST,PROTO_ZC_NOTIFY_WEAPONITEMLIST::REPAIRITEM_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].index = in->Info[i].index;
			out->Info[i].ITID = in->Info[i].ITID;
			out->Info[i].refiningLevel = in->Info[i].refiningLevel;
			out->Info[i].slot.info[0] = in->Info[i].slot.info[0];
			out->Info[i].slot.info[1] = in->Info[i].slot.info[1];
			out->Info[i].slot.info[2] = in->Info[i].slot.info[2];
			out->Info[i].slot.info[3] = in->Info[i].slot.info[3];
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_WEAPONITEMLIST,PROTO_ZC_NOTIFY_WEAPONITEMLIST::REPAIRITEM_INFO> in(p);
		TPacket<PACKET_ZC_NOTIFY_WEAPONITEMLIST,PACKET_ZC_NOTIFY_WEAPONITEMLIST::REPAIRITEM_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].index = in->Info[i].index;
			out->Info[i].ITID = in->Info[i].ITID;
			out->Info[i].refiningLevel = in->Info[i].refiningLevel;
			out->Info[i].slot.info[0] = in->Info[i].slot.info[0];
			out->Info[i].slot.info[1] = in->Info[i].slot.info[1];
			out->Info[i].slot.info[2] = in->Info[i].slot.info[2];
			out->Info[i].slot.info[3] = in->Info[i].slot.info[3];
		}

		return out;
	}
};
