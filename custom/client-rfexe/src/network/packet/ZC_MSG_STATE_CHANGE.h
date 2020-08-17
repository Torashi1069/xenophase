struct PROTO_ZC_MSG_STATE_CHANGE
{
	short PacketType;
	short index;
	unsigned long AID;
	bool state;
	unsigned long RemainMS;
	int val[3];
};


struct PACKET_ZC_MSG_STATE_CHANGE
{
	/* this+0 */ short PacketType;
	/* this+2 */ short index;
	/* this+4 */ unsigned long AID;
	/* this+8 */ bool state;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MSG_STATE_CHANGE> in(p);
		TPacket<PROTO_ZC_MSG_STATE_CHANGE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->AID = in->AID;
		out->state = in->state;
		out->RemainMS = 9999; // adapt
		out->val[0] = 0; // adapt
		out->val[1] = 0; // adapt
		out->val[2] = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MSG_STATE_CHANGE> in(p);
		TPacket<PACKET_ZC_MSG_STATE_CHANGE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->AID = in->AID;
		out->state = in->state;
//		out->RemainMS = in->RemainMS; // adapt
//		out->val[0] = in->val[0]; // adapt
//		out->val[1] = in->val[1]; // adapt
//		out->val[2] = in->val[2]; // adapt

		return out;
	}
};


struct PACKET_ZC_MSG_STATE_CHANGE2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short index;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ bool state;
	/* this+ 9 */ unsigned long RemainMS;
	/* this+13 */ int val[3];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MSG_STATE_CHANGE2> in(p);
		TPacket<PROTO_ZC_MSG_STATE_CHANGE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->AID = in->AID;
		out->state = in->state;
		out->RemainMS = in->RemainMS;
		out->val[0] = in->val[0];
		out->val[1] = in->val[1];
		out->val[2] = in->val[2];

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MSG_STATE_CHANGE> in(p);
		TPacket<PACKET_ZC_MSG_STATE_CHANGE2> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->AID = in->AID;
		out->state = in->state;
		out->RemainMS = in->RemainMS;
		out->val[0] = in->val[0];
		out->val[1] = in->val[1];
		out->val[2] = in->val[2];

		return out;
	}
};


struct PACKET_ZC_MSG_STATE_CHANGE3
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short index;
	/* this+ 4 */ unsigned long AID;
	/* this+ 8 */ bool state;
	/* this+ 9 */ unsigned long MaxMS;
	/* this+13 */ unsigned long RemainMS;
	/* this+17 */ int val[3];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MSG_STATE_CHANGE3> in(p);
		TPacket<PROTO_ZC_MSG_STATE_CHANGE> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->AID = in->AID;
		out->state = in->state;
		out->RemainMS = in->RemainMS;
		out->val[0] = in->val[0];
		out->val[1] = in->val[1];
		out->val[2] = in->val[2];

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MSG_STATE_CHANGE> in(p);
		TPacket<PACKET_ZC_MSG_STATE_CHANGE3> out;

		out->PacketType = PacketType;
		out->index = in->index;
		out->AID = in->AID;
		out->state = in->state;
		out->MaxMS = 0; // FIXME
		out->RemainMS = in->RemainMS;
		out->val[0] = in->val[0];
		out->val[1] = in->val[1];
		out->val[2] = in->val[2];

		return out;
	}
};
