struct PROTO_ZC_ACK_REMEMBER_WARPPOINT
{
	short PacketType;
	unsigned char errorCode;
};


struct PACKET_ZC_ACK_REMEMBER_WARPPOINT
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned char errorCode;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_REMEMBER_WARPPOINT> in(p);
		TPacket<PROTO_ZC_ACK_REMEMBER_WARPPOINT> out;

		out->PacketType = PacketType;
		out->errorCode = in->errorCode;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_REMEMBER_WARPPOINT> in(p);
		TPacket<PACKET_ZC_ACK_REMEMBER_WARPPOINT> out;

		out->PacketType = PacketType;
		out->errorCode = in->errorCode;

		return out;
	}
};
