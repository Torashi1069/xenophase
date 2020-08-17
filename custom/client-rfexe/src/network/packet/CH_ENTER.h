struct PROTO_CH_ENTER
{
	short PacketType;
	unsigned long AID;
	int AuthCode;
	unsigned long userLevel;
	unsigned short clientType;
	unsigned char Sex;
	char macData[16];
	int iAccountSID;
};


struct PACKET_CH_ENTER
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ int AuthCode;
	/* this+10 */ unsigned long userLevel;
	/* this+14 */ unsigned short clientType;
	/* this+16 */ unsigned char Sex;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CH_ENTER> in(p);
		TPacket<PROTO_CH_ENTER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->AuthCode = in->AuthCode;
		out->userLevel = in->userLevel;
		out->clientType = in->clientType;
		out->Sex = in->Sex;
		memset(out->macData, 0, 16); // adapt
		out->iAccountSID = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CH_ENTER> in(p);
		TPacket<PACKET_CH_ENTER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->AuthCode = in->AuthCode;
		out->userLevel = in->userLevel;
		out->clientType = in->clientType;
		out->Sex = in->Sex;
//		memcpy(out->macData, in->macData, 16); // adapt
//		out->iAccountSID = in->iAccountSID; // adapt

		return out;
	}
};


struct PACKET_CH_ENTER2 //: public PACKET_CH_ENTER
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long AID;
	/* this+ 6 */ int AuthCode;
	/* this+10 */ unsigned long userLevel;
	/* this+14 */ unsigned short clientType;
	/* this+16 */ unsigned char Sex;
	/* this+17 */ char macData[16];
	/* this+33 */ int iAccountSID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CH_ENTER2> in(p);
		TPacket<PROTO_CH_ENTER> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->AuthCode = in->AuthCode;
		out->userLevel = in->userLevel;
		out->clientType = in->clientType;
		out->Sex = in->Sex;
		memcpy(out->macData, in->macData, 16);
		out->iAccountSID = in->iAccountSID;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CH_ENTER> in(p);
		TPacket<PACKET_CH_ENTER2> out;

		out->PacketType = PacketType;
		out->AID = in->AID;
		out->AuthCode = in->AuthCode;
		out->userLevel = in->userLevel;
		out->clientType = in->clientType;
		out->Sex = in->Sex;
		memcpy(out->macData, in->macData, 16);
		out->iAccountSID = in->iAccountSID;

		return out;
	}
};
