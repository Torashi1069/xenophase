struct PROTO_ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY
{
	short PacketType;
	short PriorityOrderNum;
};


struct PACKET_ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PriorityOrderNum;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY> in(p);
		TPacket<PROTO_ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY> out;

		out->PacketType = PacketType;
		out->PriorityOrderNum = in->PriorityOrderNum;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY> in(p);
		TPacket<PACKET_ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY> out;

		out->PacketType = PacketType;
		out->PriorityOrderNum = in->PriorityOrderNum;

		return out;
	}
};
