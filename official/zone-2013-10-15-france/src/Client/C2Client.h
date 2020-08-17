#pragma once
#include "Client/C2StreamObject.h"
#include "NetLib/PacketHandler.h"
#include "shared/N3System/N3Inter.h"
#include "shared/N3System/N3IPAddr.h"
#include "shared/N3System/N3MessageQueue.h"
#include "shared/N3System/N3Object.h"


class C2Client : public N3Inter, public N3Object
{
public:
	N3IPAddr GetServerIPAddr();
	int GetServerPortNum();
	virtual void Process();
	bool Init(SOCKET in_hSocket, CPacketHandler* in_cpPacketHandler);
	void AddDisconnectReqCnt(const char* in_pSourceFileName, const int in_SourceLineNum);
	int GetDisconnectReqCnt();
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

public:
	C2Client(N3IPAddr in_ServerIPAddr, int in_ServerPortNum);
	virtual ~C2Client();

protected:
	/* this+    0 */ //N3Inter baseclass_0;
	/* this+    4 */ //N3Object baseclass_4;
	/* this+   12 */ const N3IPAddr m_ServerIPAddr;
	/* this+   20 */ const int m_ServerPortNum;
	/* this+   24 */ C2StreamObject m_asyncStream;
	/* this+20748 */ N3MessageQueue m_MessageQueue;
	/* this+20808 */ int m_DisconnectReqCnt;
};
