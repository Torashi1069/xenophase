struct PROTO_CA_LOGIN2
{
	short PacketType;
	unsigned long Version;
	unsigned char ID[24];
	unsigned char PasswdMD5[16];
	unsigned char clienttype;
	unsigned char ClientInfo; // index of the connection in the clientinfo file (+10 if the command-line contains "pc")
};


struct PACKET_CA_LOGIN2
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char PasswdMD5[16];
	/* this+46 */ unsigned char clienttype;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_LOGIN2> in(p);
		TPacket<PROTO_CA_LOGIN2> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->PasswdMD5, in->PasswdMD5, 16);
		out->clienttype = in->clienttype;
		out->ClientInfo = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_LOGIN2> in(p);
		TPacket<PACKET_CA_LOGIN2> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->PasswdMD5, in->PasswdMD5, 16);
		out->clienttype = in->clienttype;
//		out->ClientInfo = in->ClientInfo; // adapt

		return out;
	}
};


struct PACKET_CA_LOGIN3
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char PasswdMD5[16];
	/* this+46 */ unsigned char clienttype;
	/* this+47 */ unsigned char ClientInfo;

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_LOGIN3> in(p);
		TPacket<PROTO_CA_LOGIN2> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->PasswdMD5, in->PasswdMD5, 16);
		out->clienttype = in->clienttype;
		out->ClientInfo = in->ClientInfo;

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_LOGIN2> in(p);
		TPacket<PACKET_CA_LOGIN3> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->PasswdMD5, in->PasswdMD5, 16);
		out->clienttype = in->clienttype;
		out->ClientInfo = in->ClientInfo;

		return out;
	}
};


struct PACKET_CA_LOGIN4
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned long Version;
	/* this+ 6 */ unsigned char ID[24];
	/* this+30 */ unsigned char PasswdMD5[16];
	/* this+46 */ unsigned char clienttype;
	/* this+47 */ char macData[12+1];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_CA_LOGIN4> in(p);
		TPacket<PROTO_CA_LOGIN2> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->PasswdMD5, in->PasswdMD5, 16);
		out->clienttype = in->clienttype;
		out->ClientInfo = 0; // adapt

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_CA_LOGIN2> in(p);
		TPacket<PACKET_CA_LOGIN4> out;

		out->PacketType = PacketType;
		out->Version = in->Version;
		memcpy(out->ID, in->ID, 24);
		memcpy(out->PasswdMD5, in->PasswdMD5, 16);
		out->clienttype = in->clienttype;
//		out->ClientInfo = in->ClientInfo; // adapt
		memset(out->macData, 0, 12+1); // adapt //TODO: revisit this

		return out;
	}
};


//TODO
struct PACKET_CA_LOGIN5
{
	/* this+  0 */ short PacketType;
	/* this+  2 */ unsigned long Version;
	/* this+  6 */ unsigned char ID[50+1];
	/* this+ 57 */ unsigned char Passwd[50+1];
	/* this+108 */ unsigned char clienttype;
};


//TODO
struct PACKET_CA_LOGIN_CHN
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ short PacketLength;
	/* this+ 4 */ unsigned long Version;
	/* this+ 8 */ unsigned char PasswdMD5[32];
	/* this+40 */ unsigned char clienttype;
	/* this+41 */ BYTE unknown[];
};
