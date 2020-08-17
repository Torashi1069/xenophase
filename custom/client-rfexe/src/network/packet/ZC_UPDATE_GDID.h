struct PROTO_ZC_UPDATE_GDID
{
	short PacketType;
	unsigned long GDID;
	int emblemVersion;
	int right;
	bool isMaster;
	int InterSID;
	char GName[24];
};


struct PACKET_ZC_UPDATE_GDID
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GDID;
	/* this+ 6 */ int emblemVersion;
	/* this+10 */ int right;
	/* this+14 */ bool isMaster;
	/* this+15 */ int InterSID;
	/* this+19 */ char GName[24];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_UPDATE_GDID> in(p);
		TPacket<PROTO_ZC_UPDATE_GDID> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		out->emblemVersion = in->emblemVersion;
		out->right = in->right;
		out->isMaster = in->isMaster;
		out->InterSID = in->InterSID;
		memcpy(out->GName, in->GName, 24);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_UPDATE_GDID> in(p);
		TPacket<PACKET_ZC_UPDATE_GDID> out;

		out->PacketType = PacketType;
		out->GDID = in->GDID;
		out->emblemVersion = in->emblemVersion;
		out->right = in->right;
		out->isMaster = in->isMaster;
		out->InterSID = in->InterSID;
		memcpy(out->GName, in->GName, 24);

		return out;
	}
};
