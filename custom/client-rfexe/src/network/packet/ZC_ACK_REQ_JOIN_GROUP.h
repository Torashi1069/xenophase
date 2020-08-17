struct PROTO_ZC_PARTY_JOIN_REQ_ACK
{
	enum enumAnswer
	{
		ANSWER_ALREADY_OTHERGROUPM = 0,
		ANSWER_MEMBER_OVERSIZE     = 3,
		ANSWER_JOIN_ACCEPT         = 2,
		ANSWER_JOIN_REFUSE         = 1,
		ANSWER_DUPLICATE           = 4,
		ANSWER_JOINMSG_REFUSE      = 5,
		ANSWER_UNKNOWN_ERROR       = 6,
		ANSWER_UNKNOWN_CHARACTER   = 7,
		ANSWER_INVALID_MAPPROPERTY = 8,
	};

	short PacketType;
	char characterName[24];
	enumAnswer answer;
};


struct PACKET_ZC_ACK_REQ_JOIN_GROUP
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char characterName[24];
	/* this+26 */ unsigned char answer;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_ACK_REQ_JOIN_GROUP> in(p);
		TPacket<PROTO_ZC_PARTY_JOIN_REQ_ACK> out;

		out->PacketType = PacketType;
		memcpy(out->characterName, in->characterName, 24);
		out->answer = (PROTO_ZC_PARTY_JOIN_REQ_ACK::enumAnswer)in->answer;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PARTY_JOIN_REQ_ACK> in(p);
		TPacket<PACKET_ZC_ACK_REQ_JOIN_GROUP> out;

		out->PacketType = PacketType;
		memcpy(out->characterName, in->characterName, 24);
		out->answer = (unsigned char)in->answer;

		return out;
	}
};


struct PACKET_ZC_PARTY_JOIN_REQ_ACK
{
	enum enumAnswer
	{
		ANSWER_ALREADY_OTHERGROUPM = 0,
		ANSWER_MEMBER_OVERSIZE     = 3,
		ANSWER_JOIN_ACCEPT         = 2,
		ANSWER_JOIN_REFUSE         = 1,
		ANSWER_DUPLICATE           = 4,
		ANSWER_JOINMSG_REFUSE      = 5,
		ANSWER_UNKNOWN_ERROR       = 6,
		ANSWER_UNKNOWN_CHARACTER   = 7,
		ANSWER_INVALID_MAPPROPERTY = 8,
	};

	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char characterName[24];
	/* this+26 */ enumAnswer answer;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PARTY_JOIN_REQ_ACK> in(p);
		TPacket<PROTO_ZC_PARTY_JOIN_REQ_ACK> out;

		out->PacketType = PacketType;
		memcpy(out->characterName, in->characterName, 24);
		out->answer = (PROTO_ZC_PARTY_JOIN_REQ_ACK::enumAnswer)in->answer;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PARTY_JOIN_REQ_ACK> in(p);
		TPacket<PACKET_ZC_PARTY_JOIN_REQ_ACK> out;

		out->PacketType = PacketType;
		memcpy(out->characterName, in->characterName, 24);
		out->answer = (PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer)in->answer;

		return out;
	}
};
