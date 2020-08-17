struct PROTO_ZC_NOTIFY_PKINFO
{
	short PacketType;
	int winPoint;
	int losePoint;
	char killName[24];
	char killedName[24];
	FILETIME expireTime;
};


struct PACKET_ZC_NOTIFY_PKINFO
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ int winPoint;
	/* this+ 6 */ int losePoint;
	/* this+10 */ char killName[24];
	/* this+34 */ char killedName[24];
	/* this+58 */ FILETIME expireTime;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_NOTIFY_PKINFO> in(p);
		TPacket<PROTO_ZC_NOTIFY_PKINFO> out;

		out->PacketType = PacketType;
		out->winPoint = in->winPoint;
		out->losePoint = in->losePoint;
		memcpy(out->killName, in->killName, 24);
		memcpy(out->killedName, in->killedName, 24);
		out->expireTime = in->expireTime;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_NOTIFY_PKINFO> in(p);
		TPacket<PACKET_ZC_NOTIFY_PKINFO> out;

		out->PacketType = PacketType;
		out->winPoint = in->winPoint;
		out->losePoint = in->losePoint;
		memcpy(out->killName, in->killName, 24);
		memcpy(out->killedName, in->killedName, 24);
		out->expireTime = in->expireTime;

		return out;
	}
};
