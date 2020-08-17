struct PROTO_CZ_REQ_GIVE_MANNER_BYNAME
{
	short PacketType;
	char CharName[24];
};


struct PACKET_CZ_REQ_GIVE_MANNER_BYNAME
{
	/* this+0 */ short PacketType;
	/* this+2 */ char CharName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_GIVE_MANNER_BYNAME> in(p);
		TPacket<PROTO_CZ_REQ_GIVE_MANNER_BYNAME> out;

		out->PacketType = PacketType;
		memcpy(out->CharName, in->CharName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_GIVE_MANNER_BYNAME> in(p);
		TPacket<PACKET_CZ_REQ_GIVE_MANNER_BYNAME> out;

		out->PacketType = PacketType;
		memcpy(out->CharName, in->CharName, 24);

		return out;
	}
};
