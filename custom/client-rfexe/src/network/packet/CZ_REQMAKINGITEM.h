struct PROTO_CZ_REQMAKINGITEM
{
	short PacketType;
	struct MAKABLEITEM_INFO
	{
		unsigned short ITID;
		unsigned short material_ID[3];
	}
	info;
};


struct PACKET_CZ_REQMAKINGITEM
{
	/* this+0 */ short PacketType;
	/* this+2 */ struct MAKABLEITEM_INFO
	             {
	             	/* this+0 */ unsigned short ITID;
	             	/* this+2 */ unsigned short material_ID[3];
	             }
	             info;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQMAKINGITEM> in(p);
		TPacket<PROTO_CZ_REQMAKINGITEM> out;

		out->PacketType = PacketType;
		out->info.ITID = in->info.ITID;
		out->info.material_ID[0] = in->info.material_ID[0];
		out->info.material_ID[1] = in->info.material_ID[1];
		out->info.material_ID[2] = in->info.material_ID[2];

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQMAKINGITEM> in(p);
		TPacket<PACKET_CZ_REQMAKINGITEM> out;

		out->PacketType = PacketType;
		out->info.ITID = in->info.ITID;
		out->info.material_ID[0] = in->info.material_ID[0];
		out->info.material_ID[1] = in->info.material_ID[1];
		out->info.material_ID[2] = in->info.material_ID[2];

		return out;
	}
};
