#include "Packet.hpp"
#include "Parser.h"
#include "Protocol.h"
#include <windows.h>


Parser::Parser()
: m_buffer(), m_proto(NULL), m_expectingrawdata(false), m_prevPacket()
{
}


Parser::~Parser()
{
}


/// Initializes the object.
void Parser::Init(const Protocol* proto)
{
	m_proto = proto;
	m_expectingrawdata = ( m_proto->GetFirstRawPacketInfo() != NULL );
}


/// Retrieves a single packet from the internal buffer.
Packet* Parser::Next()
{
	// handle edge case
	if( m_buffer.size() == 0 )
		return NULL;

	// recognize packet
	Packet* p = this->Recognize();
	if( p == NULL )
		return NULL;

	// hand packet to caller
	return p;
}


/// Adds new data to be processed.
void Parser::Process(const BYTE* input, size_t insize)
{
	// append input to current unprocessed data
	m_buffer.insert(m_buffer.end(), input, input + insize);
}


/// Determines if there's full packet at the beginning of the buffer.
/// @return newly allocated Packet object, or NULL
Packet* Parser::Recognize()
{
	Packet* p = NULL;
	size_t length = 0;

	if( m_expectingrawdata )
	{// raw data
		const PacketInfo* info = m_proto->GetFirstRawPacketInfo();

		length = info->Len;
		if( length > m_buffer.size() )
			return NULL; // need more data

		// clear temporary state
		m_expectingrawdata = false;

		// wrap raw data in custom RO packet
		TPacket<PACKET,BYTE> pkt(length);
		p = static_cast<Packet*>(pkt); // extract
		pkt->PacketType = info->PacketType;
		memcpy(pkt->Data, &m_buffer.front(), length);
	}
	else
	{// RO packet
		length = this->DetermineLength(&m_buffer.front(), m_buffer.size());
		if( length > m_buffer.size() )
			return NULL; // need more data

		if( length == 0 )
		{// unable to proceed
			Dump(); // write log file
			FatalAppExitA(0, "Client has encountered an unsupported packet and will now exit. Please submit 'rfexe-packet.log' to support@xenophase.net.");
		}

		TPacket<PACKET,BYTE> pkt(length - sizeof(PACKET));
		p = static_cast<Packet*>(pkt); // extract
		memcpy(p->data(), &m_buffer.front(), length);
	}

	// remove data from buffer
	m_buffer.erase(m_buffer.begin(), m_buffer.begin() + length);

	// store backup (debugging)
	m_prevPacket.assign(p->data(), p->data() + p->size());

	return p;
}


/// Matches packet against packet table to determine the packet's length.
/// @return full packet length if successful, nonzero if more data is needed, 0 if unknown/invalid/malformed
size_t Parser::DetermineLength(const BYTE* in_data, size_t in_size)
{
	if( in_size < sizeof(PACKET) )
		return sizeof(PACKET); // more data needed.

	// get packet type
	int type = reinterpret_cast<const PACKET*>(in_data)->PacketType;

	// look up length information
	const PacketInfo* info = m_proto->GetInfo(type);
	if( info == NULL )
		return 0; // unknown type!

	size_t len;
	if( info->isVariable )
	{// variable-length packet
		if( in_size < sizeof(PACKETV) )
			return sizeof(PACKETV); // more data needed.

		// retrieve real packet length
		len = reinterpret_cast<const PACKETV*>(in_data)->PacketLength;

		// validate length value
		if( len < sizeof(PACKETV) || len < info->Len )
			return 0; // bogus value in packet!
	}
	else
	{// fixed-size packet
		len = info->Len;
	}

	// success.
	return len;
}


static std::string tohex(uint8_t* data, size_t size)
{
	std::string result;
	result.reserve(2*size + 1);

	for( size_t i = 0; i < size; ++i )
	{
		char buf[2+1];
		sprintf(buf, "%2.2X", data[i]);
		result += buf;
	}

	return result;
}


/// Dumps useful state information into a log file.
void Parser::Dump()
{
	FILE* fp = fopen("rfexe-packet.log", "w");
	if( fp == NULL )
	{
		FatalAppExitA(0, "Failed to create packet log file.");
		return;
	}

	// save last known packet
	if( m_prevPacket.size() != 0 )
		fprintf(fp, "Previous packet: size=%u data=%s\n", m_prevPacket.size(), tohex(&m_prevPacket.front(), m_prevPacket.size()).c_str());

	// save work buffer
	if( m_buffer.size() != 0 )
		fprintf(fp, "Work buffer: size=%u data=%s\n", m_buffer.size(), tohex(&m_buffer.front(), m_buffer.size()).c_str());

	fclose(fp);
}
