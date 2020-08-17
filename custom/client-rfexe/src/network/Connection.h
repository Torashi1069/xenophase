#pragma once
#include "Stream.h"
#include <vector>


class Connection
{
public:
	Connection();
	~Connection();
	void SetStream(CStream* stream);

	int OnRecv(BYTE* buffer, int capacity);
	int OnSend(const BYTE* buffer, int size);
	bool isRecvSignaled();
	bool isSendSignaled();

private:
	// protocol handler
	CStream* m_stream;

	// partial recv/send support
	std::vector<BYTE> m_recvbuf;
	std::vector<BYTE> m_sendbuf;
};
