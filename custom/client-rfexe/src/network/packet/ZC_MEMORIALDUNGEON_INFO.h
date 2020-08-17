struct PROTO_ZC_MEMORIALDUNGEON_INFO
{
	short PacketType;
	char MemorialDungeonName[60+1];
	unsigned long DestroyDate;
	unsigned long EnterTimeOutDate;
};


struct PACKET_ZC_MEMORIALDUNGEON_INFO
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char MemorialDungeonName[60+1];
	/* this+63 */ unsigned long DestroyDate;
	/* this+67 */ unsigned long EnterTimeOutDate;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MEMORIALDUNGEON_INFO> in(p);
		TPacket<PROTO_ZC_MEMORIALDUNGEON_INFO> out;

		out->PacketType = PacketType;
		memcpy(out->MemorialDungeonName, in->MemorialDungeonName, 60+1);
		out->DestroyDate = in->DestroyDate;
		out->EnterTimeOutDate = in->EnterTimeOutDate;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MEMORIALDUNGEON_INFO> in(p);
		TPacket<PACKET_ZC_MEMORIALDUNGEON_INFO> out;

		out->PacketType = PacketType;
		memcpy(out->MemorialDungeonName, in->MemorialDungeonName, 60+1);
		out->DestroyDate = in->DestroyDate;
		out->EnterTimeOutDate = in->EnterTimeOutDate;

		return out;
	}
};
