struct PROTO_CZ_MEMORIALDUNGEON_COMMAND
{
	enum enumCOMMAND
	{
		COMMAND_SUBSCRIPTION_CANCEL           = 0,
		COMMAND_MEMORIALDUNGEON_DESTROY       = 1,
		COMMAND_MEMORIALDUNGEON_DESTROY_FORCE = 2,
	};

	short PacketType;
	enumCOMMAND Command;
};


struct PACKET_CZ_MEMORIALDUNGEON_COMMAND
{
	enum enumCOMMAND
	{
		COMMAND_SUBSCRIPTION_CANCEL           = 0,
		COMMAND_MEMORIALDUNGEON_DESTROY       = 1,
		COMMAND_MEMORIALDUNGEON_DESTROY_FORCE = 2,
	};

	/* this+0 */ short PacketType;
	/* this+2 */ enumCOMMAND Command;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_MEMORIALDUNGEON_COMMAND> in(p);
		TPacket<PROTO_CZ_MEMORIALDUNGEON_COMMAND> out;

		out->PacketType = PacketType;
		out->Command = (PROTO_CZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND)in->Command;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_MEMORIALDUNGEON_COMMAND> in(p);
		TPacket<PACKET_CZ_MEMORIALDUNGEON_COMMAND> out;

		out->PacketType = PacketType;
		out->Command = (PACKET_CZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND)in->Command;

		return out;
	}
};
