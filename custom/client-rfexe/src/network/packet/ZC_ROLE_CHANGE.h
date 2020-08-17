struct PROTO_ZC_ROLE_CHANGE
{
	short PacketType;
	unsigned long role;
	char name[24];
};


struct PACKET_ZC_ROLE_CHANGE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long role;
	/* this+6 */ char name[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ROLE_CHANGE> in(p);
		TPacket<PROTO_ZC_ROLE_CHANGE> out;

		out->PacketType = PacketType;
		out->role = in->role;
		memcpy(out->name, in->name, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ROLE_CHANGE> in(p);
		TPacket<PACKET_ZC_ROLE_CHANGE> out;

		out->PacketType = PacketType;
		out->role = in->role;
		memcpy(out->name, in->name, 24);

		return out;
	}
};
