struct PROTO_ZC_THROW_MVPITEM
{
	short PacketType;
};


struct PACKET_ZC_THROW_MVPITEM
{
	/* this+0 */ short PacketType;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_THROW_MVPITEM> in(p);
		TPacket<PROTO_ZC_THROW_MVPITEM> out;

		out->PacketType = PacketType;
		
		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_THROW_MVPITEM> in(p);
		TPacket<PACKET_ZC_THROW_MVPITEM> out;

		out->PacketType = PacketType;

		return out;
	}
};
