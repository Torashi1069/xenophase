#include "NAsyncDBPacketRecorder.h"


hook_ptr<NAsyncDBPacketRecorder*> NAsyncDBPacketRecorder::m_cpSelf(SERVER, "NAsyncDBPacketRecorder::m_cpSelf");


NAsyncDBPacketRecorder::NAsyncDBPacketRecorder(void)
{
	m_bOK = false;
	m_szFileName[0] = '\0';

	InitializeCriticalSection(&m_CS);
	m_bOK = true;
}


NAsyncDBPacketRecorder::~NAsyncDBPacketRecorder(void)
{
	DeleteCriticalSection(&m_CS);
}
