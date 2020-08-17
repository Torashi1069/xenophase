struct PROTO_ZC_NOTIFY_PLAYERMOVE
{
	short PacketType;
	unsigned long moveStartTime;
	unsigned char MoveData[6];
};


struct PACKET_ZC_NOTIFY_PLAYERMOVE
{
	/* this+0 */ short PacketType;
	/* this+2 */ unsigned long moveStartTime;
	/* this+6 */ unsigned char MoveData[6];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_PLAYERMOVE> in(p);
		TPacket<PROTO_ZC_NOTIFY_PLAYERMOVE> out;

		out->PacketType = PacketType;
		out->moveStartTime = in->moveStartTime;
		memcpy(out->MoveData, in->MoveData, 6);

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_PLAYERMOVE> in(p);
		TPacket<PACKET_ZC_NOTIFY_PLAYERMOVE> out;

		out->PacketType = PacketType;
		out->moveStartTime = in->moveStartTime;
		memcpy(out->MoveData, in->MoveData, 6);

		return out;
	}
};
