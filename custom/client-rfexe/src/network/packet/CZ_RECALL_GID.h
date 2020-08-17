struct PROTO_CZ_RECALL_GID
{
	short PacketType;
	char CharacterName[24];
};


struct PACKET_CZ_RECALL_GID
{
	/* this+0 */ short PacketType;
	/* this+2 */ char CharacterName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_RECALL_GID> in(p);
		TPacket<PROTO_CZ_RECALL_GID> out;

		out->PacketType = PacketType;
		memcpy(out->CharacterName, in->CharacterName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_RECALL_GID> in(p);
		TPacket<PACKET_CZ_RECALL_GID> out;

		out->PacketType = PacketType;
		memcpy(out->CharacterName, in->CharacterName, 24);

		return out;
	}
};
