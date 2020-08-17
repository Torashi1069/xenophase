struct PROTO_CZ_MAKE_GROUP
{
	short PacketType;
	char groupName[24];
	unsigned char ItemPickupRule;
	unsigned char ItemDivisionRule;
};


struct PACKET_CZ_MAKE_GROUP
{
	/* this+0 */ short PacketType;
	/* this+2 */ char groupName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_MAKE_GROUP> in(p);
		TPacket<PROTO_CZ_MAKE_GROUP> out;

		out->PacketType = PacketType;
		memcpy(out->groupName, in->groupName, 24);
		out->ItemPickupRule = 0; // adapt //FIXME
		out->ItemDivisionRule = 0; // adapt //FIXME

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_MAKE_GROUP> in(p);
		TPacket<PACKET_CZ_MAKE_GROUP> out;

		out->PacketType = PacketType;
		memcpy(out->groupName, in->groupName, 24);
//		out->ItemPickupRule = in->ItemPickupRule; // adapt
//		out->ItemDivisionRule = in->ItemDivisionRule; // adapt

		return out;
	}
};


struct PACKET_CZ_MAKE_GROUP2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char groupName[24];
	/* this+26 */ unsigned char ItemPickupRule;
	/* this+27 */ unsigned char ItemDivisionRule;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_MAKE_GROUP2> in(p);
		TPacket<PROTO_CZ_MAKE_GROUP> out;

		out->PacketType = PacketType;
		memcpy(out->groupName, in->groupName, 24);
		out->ItemPickupRule = in->ItemPickupRule;
		out->ItemDivisionRule = in->ItemDivisionRule;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_MAKE_GROUP> in(p);
		TPacket<PACKET_CZ_MAKE_GROUP2> out;

		out->PacketType = PacketType;
		memcpy(out->groupName, in->groupName, 24);
		out->ItemPickupRule = in->ItemPickupRule;
		out->ItemDivisionRule = in->ItemDivisionRule;

		return out;
	}
};
