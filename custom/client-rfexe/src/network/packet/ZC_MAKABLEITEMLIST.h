struct PROTO_ZC_MAKABLEITEMLIST
{
	short PacketType;
	short PacketLength;
	struct MAKABLEITEM_INFO
	{
		unsigned short ITID;
		unsigned short material_ID[3];
	}
	Info[];
};


struct PACKET_ZC_MAKABLEITEMLIST
{
	/* this+0 */ short PacketType;
	/* this+2 */ short PacketLength;
	/* this+4 */ struct MAKABLEITEM_INFO
	             {
	             	/* this+0 */ unsigned short ITID;
	             	/* this+2 */ unsigned short material_ID[3];
	             }
	             Info[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_MAKABLEITEMLIST,PACKET_ZC_MAKABLEITEMLIST::MAKABLEITEM_INFO> in(p);
		TPacket<PROTO_ZC_MAKABLEITEMLIST,PROTO_ZC_MAKABLEITEMLIST::MAKABLEITEM_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].ITID = in->Info[i].ITID;
			out->Info[i].material_ID[0] = in->Info[i].material_ID[0];
			out->Info[i].material_ID[1] = in->Info[i].material_ID[1];
			out->Info[i].material_ID[2] = in->Info[i].material_ID[2];
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_MAKABLEITEMLIST,PROTO_ZC_MAKABLEITEMLIST::MAKABLEITEM_INFO> in(p);
		TPacket<PACKET_ZC_MAKABLEITEMLIST,PACKET_ZC_MAKABLEITEMLIST::MAKABLEITEM_INFO> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->Info[i].ITID = in->Info[i].ITID;
			out->Info[i].material_ID[0] = in->Info[i].material_ID[0];
			out->Info[i].material_ID[1] = in->Info[i].material_ID[1];
			out->Info[i].material_ID[2] = in->Info[i].material_ID[2];
		}

		return out;
	}
};
