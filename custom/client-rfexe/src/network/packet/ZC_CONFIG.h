struct PROTO_ZC_CONFIG
{
	enum enumConfig { CONFIG_OPEN_EQUIPMENT_WINDOW = 0 };

	short PacketType;
	enumConfig Config;
	int Value;
};


struct PACKET_ZC_CONFIG
{
	enum enumConfig { CONFIG_OPEN_EQUIPMENT_WINDOW = 0 };

	/* this+0 */ short PacketType;
	/* this+2 */ enumConfig Config;
	/* this+6 */ int Value;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_CONFIG> in(p);
		TPacket<PROTO_ZC_CONFIG> out;

		out->PacketType = PacketType;
		out->Config = (PROTO_ZC_CONFIG::enumConfig)in->Config;
		out->Value = in->Value;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_CONFIG> in(p);
		TPacket<PACKET_ZC_CONFIG> out;

		out->PacketType = PacketType;
		out->Config = (PACKET_ZC_CONFIG::enumConfig)in->Config;
		out->Value = in->Value;

		return out;
	}
};
