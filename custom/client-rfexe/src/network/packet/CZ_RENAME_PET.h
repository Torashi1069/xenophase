struct PROTO_CZ_RENAME_PET
{
	short PacketType;
	char szName[24];
};


struct PACKET_CZ_RENAME_PET
{
	/* this+0 */ short PacketType;
	/* this+2 */ char szName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_RENAME_PET> in(p);
		TPacket<PROTO_CZ_RENAME_PET> out;

		out->PacketType = PacketType;
		memcpy(out->szName, in->szName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_RENAME_PET> in(p);
		TPacket<PACKET_CZ_RENAME_PET> out;

		out->PacketType = PacketType;
		memcpy(out->szName, in->szName, 24);

		return out;
	}
};
