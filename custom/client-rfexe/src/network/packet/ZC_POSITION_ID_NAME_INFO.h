struct PROTO_ZC_POSITION_ID_NAME_INFO
{
	short PacketType;
	short PacketLength;
	struct MEMBER_POSITION_ID_NAME_INFO
	{
		int positionID;
		char posName[24];
	}
	Info[];
};


struct PACKET_ZC_POSITION_ID_NAME_INFO
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct MEMBER_POSITION_ID_NAME_INFO
	             {
	             	/* this+0 */ int positionID;
	             	/* this+4 */ char posName[24];
	             }
	             Info[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_POSITION_ID_NAME_INFO,PACKET_ZC_POSITION_ID_NAME_INFO::MEMBER_POSITION_ID_NAME_INFO> in(p);
		TPacket<PROTO_ZC_POSITION_ID_NAME_INFO,PROTO_ZC_POSITION_ID_NAME_INFO::MEMBER_POSITION_ID_NAME_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].positionID = in->Info[i].positionID;
			memcpy(out->Info[i].posName, in->Info[i].posName, 24);
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_POSITION_ID_NAME_INFO,PROTO_ZC_POSITION_ID_NAME_INFO::MEMBER_POSITION_ID_NAME_INFO> in(p);
		TPacket<PACKET_ZC_POSITION_ID_NAME_INFO,PACKET_ZC_POSITION_ID_NAME_INFO::MEMBER_POSITION_ID_NAME_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].positionID = in->Info[i].positionID;
			memcpy(out->Info[i].posName, in->Info[i].posName, 24);
		}

		return out;
	}
};
