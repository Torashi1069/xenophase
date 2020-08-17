struct PROTO_CZ_GROUPINFO_CHANGE
{
	short PacketType;
	int PacketVersion; // 1:basic, 2:w/itemshare
	unsigned long expOption;
	unsigned char ItemPickupRule;
	unsigned char ItemDivisionRule;
};


struct PACKET_CZ_CHANGE_GROUPEXPOPTION
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long expOption;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CHANGE_GROUPEXPOPTION> in(p);
		TPacket<PROTO_CZ_GROUPINFO_CHANGE> out;

		out->PacketType = PacketType;
		out->PacketVersion = 1;
		out->expOption = in->expOption;
		out->ItemPickupRule = 0; // adapt // broken
		out->ItemDivisionRule = 0; // adapt // broken

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_GROUPINFO_CHANGE> in(p);
		TPacket<PACKET_CZ_CHANGE_GROUPEXPOPTION> out;

		out->PacketType = PacketType;
		out->expOption = in->expOption;
//		out->ItemPickupRule = in->ItemPickupRule; // adapt
//		out->ItemDivisionRule = in->ItemDivisionRule; // adapt

		return out;
	}
};


struct PACKET_CZ_GROUPINFO_CHANGE_V2
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long expOption;
	/* this+6 */ unsigned char ItemPickupRule;
	/* this+7 */ unsigned char ItemDivisionRule;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_GROUPINFO_CHANGE_V2> in(p);
		TPacket<PROTO_CZ_GROUPINFO_CHANGE> out;

		out->PacketType = PacketType;
		out->PacketVersion = 2;
		out->expOption = in->expOption;
		out->ItemPickupRule = in->ItemPickupRule;
		out->ItemDivisionRule = in->ItemDivisionRule;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_GROUPINFO_CHANGE> in(p);
		if( in->PacketVersion < 2 ) return NULL;
		TPacket<PACKET_CZ_GROUPINFO_CHANGE_V2> out;

		out->PacketType = PacketType;
		out->expOption = in->expOption;
		out->ItemPickupRule = in->ItemPickupRule;
		out->ItemDivisionRule = in->ItemDivisionRule;

		return out;
	}
};
