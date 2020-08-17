#include "Protocol.h"
#include "ProtocolMgr.h"


Protocol::Protocol(const char* name)
{
	m_name = name;
	m_initialized = false;
	m_rawpacket = NULL;
	ProtocolMgr::Register(name, this);
}


void Protocol::Init()
{
	if( m_initialized )
		return;

	this->InitInstance();
	m_initialized = true;
}


void Protocol::Register(short PacketType, PROTOID ProtoID, unsigned short Len, bool isVariable, AdapterFunc* ToProto, AdapterFunc* FromProto)
{
	if( Len == (unsigned short)-1 ) // compatibility
		Len = sizeof(PACKETV);

	PacketInfo info;
	info.PacketType = PacketType;
	info.ProtoID = ProtoID;
	info.Len = Len;
	info.isVariable = isVariable;
	info.ToProto = ToProto;
	info.FromProto = FromProto;

	m_map[PacketType] = info;
	m_proto.insert(std::pair<PROTOID,PacketInfo*>(ProtoID, &m_map[PacketType]));
}


const PacketInfo* Protocol::GetInfo(short PacketType) const
{
	std::map<short,PacketInfo>::const_iterator it = m_map.find(PacketType);
	return ( it != m_map.end() ) ? &it->second : NULL;
}


Packet* Protocol::ToProto(Packet* p) const
{
	if( p == NULL ) return NULL;

	short type = p->type();

	do
	{
		const PacketInfo* info = this->GetInfo(type);
		assert( info != NULL ); if( info == NULL ) continue;

		if( info->ToProto == NULL )
			return NULL; // explicit discard

		Packet* pkt = info->ToProto(info->ProtoID, p);
		if( pkt == NULL )
			continue; // rejected.

		return pkt; // success!
	}
	while( false );

	assert( false ); // report missing explicit discard
	return NULL; // no compatible adapters found.
}


Packet* Protocol::FromProto(Packet* p) const
{
	if( p == NULL ) return NULL;

	PROTOID type = (PROTOID)p->type();

	std::pair<std::multimap<PROTOID,PacketInfo*>::const_iterator,std::multimap<PROTOID,PacketInfo*>::const_iterator> range = m_proto.equal_range(type);
	std::multimap<PROTOID,PacketInfo*>::const_reverse_iterator begin(range.second);
	std::multimap<PROTOID,PacketInfo*>::const_reverse_iterator end(range.first);

	for( std::multimap<PROTOID,PacketInfo*>::const_reverse_iterator it = begin; it != end; ++it )
	{
		const PacketInfo* info = it->second;
		assert( info != NULL ); if( info == NULL ) continue;

		if( info->FromProto == NULL )
			return NULL; // explicit discard

		Packet* pkt = info->FromProto(info->PacketType, p);
		if( pkt == NULL )
			continue; // rejected.

		if( type == PROTOID_COPY )
		{// load actual values for validation
			info = this->GetInfo(pkt->type());
			assert( info != NULL ); if( info == NULL ) continue;
		}

		// validate output length
		assert( info->isVariable == true  && pkt->size() >= info->Len
		     || info->isVariable == false && pkt->size() == info->Len );

		return pkt; // success!
	}

	assert( false ); // report missing explicit discard
	return NULL; // no compatible adapters found.
}


// Info on initial raw packet sent.
const PacketInfo* Protocol::GetFirstRawPacketInfo() const
{
	return m_rawpacket;
}


// Info on initial raw packet sent.
void Protocol::SetFirstRawPacketInfo(short PacketType)
{
	m_rawpacket = this->GetInfo(PacketType);
}


// Instance-specific initialization callback.
void Protocol::InitInstance()
{
	return; // default
}
