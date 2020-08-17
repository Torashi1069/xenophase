struct PROTO_ZC_PROPERTY_PET
{
	short PacketType;
	char szName[24];
	bool bModified;
	short nLevel;
	short nFullness;
	short nRelationship;
	unsigned short ITID;
	short job;
};


struct PACKET_ZC_PROPERTY_PET
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char szName[24];
	/* this+26 */ bool bModified;
	/* this+27 */ short nLevel;
	/* this+29 */ short nFullness;
	/* this+31 */ short nRelationship;
	/* this+33 */ unsigned short ITID;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PROPERTY_PET> in(p);
		TPacket<PROTO_ZC_PROPERTY_PET> out;

		out->PacketType = PacketType;
		memcpy(out->szName, in->szName, 24);
		out->bModified = in->bModified;
		out->nLevel = in->nLevel;
		out->nFullness = in->nFullness;
		out->nRelationship = in->nRelationship;
		out->ITID = in->ITID;
		out->job = 0; // adapt //TODO: verify

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PROPERTY_PET> in(p);
		TPacket<PACKET_ZC_PROPERTY_PET> out;

		out->PacketType = PacketType;
		memcpy(out->szName, in->szName, 24);
		out->bModified = in->bModified;
		out->nLevel = in->nLevel;
		out->nFullness = in->nFullness;
		out->nRelationship = in->nRelationship;
		out->ITID = in->ITID;
//		out->job = in->job; // adapt

		return out;
	}
};


struct PACKET_ZC_PROPERTY_PET_2009
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ char szName[24];
	/* this+26 */ bool bModified;
	/* this+27 */ short nLevel;
	/* this+29 */ short nFullness;
	/* this+31 */ short nRelationship;
	/* this+33 */ unsigned short ITID;
	/* this+35 */ short job;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_ZC_PROPERTY_PET_2009> in(p);
		TPacket<PROTO_ZC_PROPERTY_PET> out;

		out->PacketType = PacketType;
		memcpy(out->szName, in->szName, 24);
		out->bModified = in->bModified;
		out->nLevel = in->nLevel;
		out->nFullness = in->nFullness;
		out->nRelationship = in->nRelationship;
		out->ITID = in->ITID;
		out->job = in->job;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_ZC_PROPERTY_PET> in(p);
		TPacket<PACKET_ZC_PROPERTY_PET_2009> out;

		out->PacketType = PacketType;
		memcpy(out->szName, in->szName, 24);
		out->bModified = in->bModified;
		out->nLevel = in->nLevel;
		out->nFullness = in->nFullness;
		out->nRelationship = in->nRelationship;
		out->ITID = in->ITID;
		out->job = in->job;

		return out;
	}
};
