struct PROTO_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO
{
	short PacketType;
	char MemorialDungeonName[60+1];
	short PriorityOrderNum;
};


struct PACKET_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char MemorialDungeonName[60+1];
	/* this+63 */ short PriorityOrderNum;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO> in(p);
		TPacket<PROTO_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO> out;

		out->PacketType = PacketType;
		memcpy(out->MemorialDungeonName, in->MemorialDungeonName, 60+1);
		out->PriorityOrderNum = in->PriorityOrderNum;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO> in(p);
		TPacket<PACKET_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO> out;

		out->PacketType = PacketType;
		memcpy(out->MemorialDungeonName, in->MemorialDungeonName, 60+1);
		out->PriorityOrderNum = in->PriorityOrderNum;

		return out;
	}
};
