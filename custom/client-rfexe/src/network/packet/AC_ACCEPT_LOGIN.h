struct PROTO_AC_ACCEPT_LOGIN
{
	short PacketType; // PROTOID_AC_ACCEPT_LOGIN
	unsigned short PacketLength;
	int AuthCode;
	unsigned long AID;
	unsigned long userLevel;
	unsigned long lastLoginIP;
	char lastLoginTime[26];
	unsigned char Sex;
	int iAccountSID;
	struct SERVER_ADDR 
	{
		unsigned long ip;
		short port;
		unsigned char name[20];
		unsigned short usercount;
		unsigned short state; // enum SERVERSTATE
		unsigned short property; // enum SERVERPROPERTY
	}
	ServerAddr[];
};


struct PACKET_AC_ACCEPT_LOGIN
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ int AuthCode;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ unsigned long userLevel;
	/* this+16 */ unsigned long lastLoginIP;
	/* this+20 */ char lastLoginTime[26];
	/* this+46 */ unsigned char Sex;
	/* this+47 */ struct SERVER_ADDR 
	              {
	              	/* this+ 0 */ unsigned long ip;
	              	/* this+ 4 */ short port;
	              	/* this+ 6 */ unsigned char name[20];
	              	/* this+26 */ unsigned short usercount;
	              	/* this+28 */ unsigned short state;
	              	/* this+30 */ unsigned short property;
	              } ServerAddr[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_AC_ACCEPT_LOGIN,PACKET_AC_ACCEPT_LOGIN::SERVER_ADDR> in(p);
		TPacket<PROTO_AC_ACCEPT_LOGIN,PROTO_AC_ACCEPT_LOGIN::SERVER_ADDR> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AuthCode = in->AuthCode;
		out->AID = in->AID;
		out->userLevel = in->userLevel;
		out->lastLoginIP = in->lastLoginIP;
		memcpy(out->lastLoginTime, in->lastLoginTime, 26);
		out->Sex = in->Sex;
		out->iAccountSID = 0; // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->ServerAddr[i].ip = in->ServerAddr[i].ip;
			out->ServerAddr[i].port = in->ServerAddr[i].port;
			memcpy(out->ServerAddr[i].name, in->ServerAddr[i].name, 20);
			out->ServerAddr[i].usercount = in->ServerAddr[i].usercount;
			out->ServerAddr[i].state = in->ServerAddr[i].state;
			out->ServerAddr[i].property = in->ServerAddr[i].property;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_AC_ACCEPT_LOGIN,PROTO_AC_ACCEPT_LOGIN::SERVER_ADDR> in(p);
		TPacket<PACKET_AC_ACCEPT_LOGIN,PACKET_AC_ACCEPT_LOGIN::SERVER_ADDR> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AuthCode = in->AuthCode;
		out->AID = in->AID;
		out->userLevel = in->userLevel;
		out->lastLoginIP = in->lastLoginIP;
		memcpy(out->lastLoginTime, in->lastLoginTime, 26);
		out->Sex = in->Sex;
//		out->iAccountSID = in->iAccountSID; // adapt

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->ServerAddr[i].ip = in->ServerAddr[i].ip;
			out->ServerAddr[i].port = in->ServerAddr[i].port;
			memcpy(out->ServerAddr[i].name, in->ServerAddr[i].name, 20);
			out->ServerAddr[i].usercount = in->ServerAddr[i].usercount;
			out->ServerAddr[i].state = in->ServerAddr[i].state;
			out->ServerAddr[i].property = in->ServerAddr[i].property;
		}

		return out;
	}
};


struct PACKET_AC_ACCEPT_LOGIN2 //: public PACKET_AC_ACCEPT_LOGIN
{
	/* this+ 0 */ short PacketType;
	/* this+ 2 */ unsigned short PacketLength;
	/* this+ 4 */ int AuthCode;
	/* this+ 8 */ unsigned long AID;
	/* this+12 */ unsigned long userLevel;
	/* this+16 */ unsigned long lastLoginIP;
	/* this+20 */ char lastLoginTime[26];
	/* this+46 */ unsigned char Sex;
	/* this+47 */ int iAccountSID;
	/* this+51 */ struct SERVER_ADDR 
	              {
	              	/* this+ 0 */ unsigned long ip;
	              	/* this+ 4 */ short port;
	              	/* this+ 6 */ unsigned char name[20];
	              	/* this+26 */ unsigned short usercount;
	              	/* this+28 */ unsigned short state;
	              	/* this+30 */ unsigned short property;
	              } ServerAddr[];

	static Packet* ToProto(short PacketType, Packet* p)
	{
		TPacket<PACKET_AC_ACCEPT_LOGIN2,PACKET_AC_ACCEPT_LOGIN2::SERVER_ADDR> in(p);
		TPacket<PROTO_AC_ACCEPT_LOGIN,PROTO_AC_ACCEPT_LOGIN::SERVER_ADDR> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AuthCode = in->AuthCode;
		out->AID = in->AID;
		out->userLevel = in->userLevel;
		out->lastLoginIP = in->lastLoginIP;
		memcpy(out->lastLoginTime, in->lastLoginTime, 26);
		out->Sex = in->Sex;
		out->iAccountSID = in->iAccountSID;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->ServerAddr[i].ip = in->ServerAddr[i].ip;
			out->ServerAddr[i].port = in->ServerAddr[i].port;
			memcpy(out->ServerAddr[i].name, in->ServerAddr[i].name, 20);
			out->ServerAddr[i].usercount = in->ServerAddr[i].usercount;
			out->ServerAddr[i].state = in->ServerAddr[i].state;
			out->ServerAddr[i].property = in->ServerAddr[i].property;
		}

		return out;
	}

	static Packet* FromProto(short PacketType, Packet* p)
	{
		TPacket<PROTO_AC_ACCEPT_LOGIN,PROTO_AC_ACCEPT_LOGIN::SERVER_ADDR> in(p);
		TPacket<PACKET_AC_ACCEPT_LOGIN2,PACKET_AC_ACCEPT_LOGIN2::SERVER_ADDR> out(in.count());

		out->PacketType = PacketType;
		out->PacketLength = out.size();
		out->AuthCode = in->AuthCode;
		out->AID = in->AID;
		out->userLevel = in->userLevel;
		out->lastLoginIP = in->lastLoginIP;
		memcpy(out->lastLoginTime, in->lastLoginTime, 26);
		out->Sex = in->Sex;
		out->iAccountSID = in->iAccountSID;

		for( size_t i = 0; i < out.count(); ++i )
		{
			out->ServerAddr[i].ip = in->ServerAddr[i].ip;
			out->ServerAddr[i].port = in->ServerAddr[i].port;
			memcpy(out->ServerAddr[i].name, in->ServerAddr[i].name, 20);
			out->ServerAddr[i].usercount = in->ServerAddr[i].usercount;
			out->ServerAddr[i].state = in->ServerAddr[i].state;
			out->ServerAddr[i].property = in->ServerAddr[i].property;
		}

		return out;
	}
};
