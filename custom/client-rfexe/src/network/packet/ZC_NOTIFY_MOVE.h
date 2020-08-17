struct PROTO_ZC_NOTIFY_MOVE
{
	short PacketType;
	unsigned long GID;
	unsigned char MoveData[6];
	unsigned long moveStartTime;
};


struct PACKET_ZC_NOTIFY_MOVE
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long GID;
	/* this+ 6 */ unsigned char MoveData[6];
	/* this+12 */ unsigned long moveStartTime;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_MOVE> in(p);
		TPacket<PROTO_ZC_NOTIFY_MOVE> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memcpy(out->MoveData, in->MoveData, 6);
		out->moveStartTime = in->moveStartTime;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_MOVE> in(p);
		TPacket<PACKET_ZC_NOTIFY_MOVE> out;

		out->PacketType = PacketType;
		out->GID = in->GID;
		memcpy(out->MoveData, in->MoveData, 6);
		out->moveStartTime = in->moveStartTime;

		return out;
	}
};
