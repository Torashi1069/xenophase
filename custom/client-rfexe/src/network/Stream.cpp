#include "Stream.h"
#include "Packet.hpp"
#include "Protocol.h"
#include "ProtocolMgr.h"


CStream::CStream(std::string localver, std::string remotever)
{
	m_localproto = ProtocolMgr::Get(localver);
	m_remoteproto = ProtocolMgr::Get(remotever);

	m_send.Init(m_localproto);
	m_recv.Init(m_remoteproto);
}


CStream::~CStream()
{
}


void CStream::RecvIn(const BYTE* input, size_t size)
{
	m_recv.Process(input, size);
}


void CStream::SendIn(const BYTE* input, size_t size)
{
	m_send.Process(input, size);
}


void CStream::RecvOut(std::vector<BYTE>& outbuf)
{
	// process all pending packets
	while( Packet* pkt = m_recv.Next() )
	{
		Packet* up = m_remoteproto->ToProto(pkt);
		Packet* p = m_localproto->FromProto(up);

		// write into output buffer
		if( p != NULL ) outbuf.insert(outbuf.end(), p->data(), p->data() + p->size());

		// cleanup
		delete pkt; delete up; delete p;
	};
}


void CStream::SendOut(std::vector<BYTE>& outbuf)
{
	// process all pending packets
	while( Packet* pkt = m_send.Next() )
	{
		Packet* up = m_localproto->ToProto(pkt);
		Packet* p = m_remoteproto->FromProto(up);

		// write into output buffer
		if( p != NULL ) outbuf.insert(outbuf.end(), p->data(), p->data() + p->size());

		// cleanup
		delete pkt; delete up; delete p;
	};
}
