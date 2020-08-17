struct PROTO_CZ_CHANGE_EFFECTSTATE
{
	short PacketType;
	int EffectState;
};


struct PACKET_CZ_CHANGE_EFFECTSTATE
{
	/* this+0 */ short PacketType;
	/* this+2 */ int EffectState;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_CHANGE_EFFECTSTATE> in(p);
		TPacket<PROTO_CZ_CHANGE_EFFECTSTATE> out;

		out->PacketType = PacketType;
		out->EffectState = in->EffectState;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_CHANGE_EFFECTSTATE> in(p);
		TPacket<PACKET_CZ_CHANGE_EFFECTSTATE> out;

		out->PacketType = PacketType;
		out->EffectState = in->EffectState;

		return out;
	}
};
