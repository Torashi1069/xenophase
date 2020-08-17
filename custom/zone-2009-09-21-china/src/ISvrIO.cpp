#include "CharacterMgr.h"
#include "CGVar.hpp"
#include "ISvrIO.h"
#include "Common/Packet.h"


CISvrIO::CISvrIO(void) // line 23-25
{
	m_PingTimer.CPollTimer::Init(timeGetTime(), CISvrIO::PING_TIME);
}


CISvrIO::~CISvrIO(void) // line 28-29
{
}


hook_method<void (CISvrIO::*)(void)> CISvrIO::_OnCustomInit(SERVER, "CISvrIO::OnCustomInit");
void CISvrIO::OnCustomInit(void) // line 86-93
{
	return (this->*_OnCustomInit)();

	PACKET_XX_CONNECT packet;
	packet.PacketType = HEADER_XX_CONNECT;
	m_asyncStream.CAsyncStream::GetRecvQueuePtr()->CPacketQueue::InsertData(sizeof(packet), (char*)&packet);
}


hook_method<int (CISvrIO::*)(void)> CISvrIO::_OnProcess(SERVER, "CISvrIO::OnProcess");
int CISvrIO::OnProcess(void) // line 75-78
{
	return (this->*_OnProcess)();

	DWORD now = timeGetTime();
	if( m_PingTimer.CPollTimer::CheckTimeout(now) )
	{
		m_PingTimer.CPollTimer::Reset(now);
		this->CISvrIO::SendPing();
	}

	return this->CSvrIO::OnProcess();
}


hook_method<void (CISvrIO::*)(void)> CISvrIO::_SendPing(SERVER, "CISvrIO::SendPing");
void CISvrIO::SendPing(void) // line 51-70
{
	return (this->*_SendPing)();

	PACKET_ZI_PING packet;
	packet.PacketType = HEADER_ZI_PING;
	packet.UsedKBytesMemory = CGVar::GetObj()->CGVar::GetUsedMemoryBytes() / 1024;
	packet.NumTotalNPC = g_characterMgr->CCharacterMgr::GetMonsterCount();
	this->CSvrIO::Send(sizeof(packet), (char*)&packet);
}
