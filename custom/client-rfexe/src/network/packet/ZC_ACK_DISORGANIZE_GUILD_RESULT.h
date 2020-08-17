struct PROTO_ZC_ACK_DISORGANIZE_GUILD_RESULT
{
	short PacketType;
	int reason;
};


struct PACKET_ZC_ACK_DISORGANIZE_GUILD_RESULT
{
	/* this+0 */ short PacketType;
	/* this+2 */ int reason;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_DISORGANIZE_GUILD_RESULT> in(p);
		TPacket<PROTO_ZC_ACK_DISORGANIZE_GUILD_RESULT> out;

		out->PacketType = PacketType;
		out->reason = in->reason;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_DISORGANIZE_GUILD_RESULT> in(p);
		TPacket<PACKET_ZC_ACK_DISORGANIZE_GUILD_RESULT> out;

		out->PacketType = PacketType;
		out->reason = in->reason;

		return out;
	}
};
