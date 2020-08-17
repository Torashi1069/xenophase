struct PROTO_CZ_REQ_STATUS_GM
{
	short PacketType;
	char CharName[24];
};


struct PACKET_CZ_REQ_STATUS_GM
{
	/* this+0 */ short PacketType;
	/* this+2 */ char CharName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_STATUS_GM> in(p);
		TPacket<PROTO_CZ_REQ_STATUS_GM> out;

		out->PacketType = PacketType;
		memcpy(out->CharName, in->CharName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_STATUS_GM> in(p);
		TPacket<PACKET_CZ_REQ_STATUS_GM> out;

		out->PacketType = PacketType;
		memcpy(out->CharName, in->CharName, 24);

		return out;
	}
};
