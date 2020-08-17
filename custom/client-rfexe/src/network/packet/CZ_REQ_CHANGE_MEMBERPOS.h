struct PROTO_CZ_REQ_CHANGE_MEMBERPOS
{
	short PacketType;
	short PacketLength;
	struct MEMBER_POSITION_INFORMATION
	{
		int AID;
		int GID;
		int positionID;
	}
	Info[];
};


struct PACKET_CZ_REQ_CHANGE_MEMBERPOS
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct MEMBER_POSITION_INFORMATION
	             {
	             	/* this+0 */ int AID;
	             	/* this+4 */ int GID;
	             	/* this+8 */ int positionID;
	             }
	             Info[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CZ_REQ_CHANGE_MEMBERPOS,PACKET_CZ_REQ_CHANGE_MEMBERPOS::MEMBER_POSITION_INFORMATION> in(p);
		TPacket<PROTO_CZ_REQ_CHANGE_MEMBERPOS,PROTO_CZ_REQ_CHANGE_MEMBERPOS::MEMBER_POSITION_INFORMATION> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].AID = in->Info[i].AID;
			out->Info[i].GID = in->Info[i].GID;
			out->Info[i].positionID = in->Info[i].positionID;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CZ_REQ_CHANGE_MEMBERPOS,PROTO_CZ_REQ_CHANGE_MEMBERPOS::MEMBER_POSITION_INFORMATION> in(p);
		TPacket<PACKET_CZ_REQ_CHANGE_MEMBERPOS,PACKET_CZ_REQ_CHANGE_MEMBERPOS::MEMBER_POSITION_INFORMATION> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].AID = in->Info[i].AID;
			out->Info[i].GID = in->Info[i].GID;
			out->Info[i].positionID = in->Info[i].positionID;
		}

		return out;
	}
};
