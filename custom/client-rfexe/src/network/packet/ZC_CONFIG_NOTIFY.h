struct PROTO_ZC_CONFIG_NOTIFY
{
	short PacketType;
	bool bOpenEquipmentWin;
};


struct PACKET_ZC_CONFIG_NOTIFY
{
	/* this+0 */ short PacketType;
	/* this+2 */ bool bOpenEquipmentWin;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_CONFIG_NOTIFY> in(p);
		TPacket<PROTO_ZC_CONFIG_NOTIFY> out;

		out->PacketType = PacketType;
		out->bOpenEquipmentWin = in->bOpenEquipmentWin;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_CONFIG_NOTIFY> in(p);
		TPacket<PACKET_ZC_CONFIG_NOTIFY> out;

		out->PacketType = PacketType;
		out->bOpenEquipmentWin = in->bOpenEquipmentWin;

		return out;
	}
};
