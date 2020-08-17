struct PROTO_CZ_REQ_ITEMREPAIR
{
	short PacketType;
	struct REPAIRITEM_INFO
	{
		short index;
		unsigned short ITID;
		unsigned char refiningLevel;
		EQUIPSLOTINFO slot;
	}
	TargetItemInfo;
};


struct PACKET_CZ_REQ_ITEMREPAIR
{
	/* this+0 */ short PacketType;
	/* this+2 */ struct REPAIRITEM_INFO
	             {
	             	/* this+0 */ short index;
	             	/* this+2 */ unsigned short ITID;
	             	/* this+4 */ unsigned char refiningLevel;
	             	/* this+5 */ EQUIPSLOTINFO slot;
	             }
	             TargetItemInfo;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_ITEMREPAIR> in(p);
		TPacket<PROTO_CZ_REQ_ITEMREPAIR> out;

		out->PacketType = PacketType;
		out->TargetItemInfo.index = in->TargetItemInfo.index;
		out->TargetItemInfo.ITID = in->TargetItemInfo.ITID;
		out->TargetItemInfo.refiningLevel = in->TargetItemInfo.refiningLevel;
		out->TargetItemInfo.slot.info[0] = in->TargetItemInfo.slot.info[0];
		out->TargetItemInfo.slot.info[1] = in->TargetItemInfo.slot.info[1];
		out->TargetItemInfo.slot.info[2] = in->TargetItemInfo.slot.info[2];
		out->TargetItemInfo.slot.info[3] = in->TargetItemInfo.slot.info[3];

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_ITEMREPAIR> in(p);
		TPacket<PACKET_CZ_REQ_ITEMREPAIR> out;

		out->PacketType = PacketType;
		out->TargetItemInfo.index = in->TargetItemInfo.index;
		out->TargetItemInfo.ITID = in->TargetItemInfo.ITID;
		out->TargetItemInfo.refiningLevel = in->TargetItemInfo.refiningLevel;
		out->TargetItemInfo.slot.info[0] = in->TargetItemInfo.slot.info[0];
		out->TargetItemInfo.slot.info[1] = in->TargetItemInfo.slot.info[1];
		out->TargetItemInfo.slot.info[2] = in->TargetItemInfo.slot.info[2];
		out->TargetItemInfo.slot.info[3] = in->TargetItemInfo.slot.info[3];

		return out;
	}
};
