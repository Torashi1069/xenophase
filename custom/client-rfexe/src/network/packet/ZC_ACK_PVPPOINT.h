struct PROTO_ZC_ACK_PVPPOINT
{
	short PacketType;
	unsigned long AID;
	unsigned long GID;
	struct PVPINFO
	{
		int WinPoint;
		int LosePoint;
		int Point;
	}
	PVP;
};


struct PACKET_ZC_ACK_PVPPOINT
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ unsigned long GID;
	/* this+10 */ struct PVPINFO
	              {
	              	/* this+0 */ int WinPoint;
	              	/* this+4 */ int LosePoint;
	              	/* this+8 */ int Point;
	              }
	              PVP;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_PVPPOINT> in(p);
		TPacket<PROTO_ZC_ACK_PVPPOINT> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		out->PVP.WinPoint = in->PVP.WinPoint;
		out->PVP.LosePoint = in->PVP.LosePoint;
		out->PVP.Point = in->PVP.Point;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_ACK_PVPPOINT> in(p);
		TPacket<PACKET_ZC_ACK_PVPPOINT> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->GID = in->GID;
		out->PVP.WinPoint = in->PVP.WinPoint;
		out->PVP.LosePoint = in->PVP.LosePoint;
		out->PVP.Point = in->PVP.Point;

		return out;
	}
};
