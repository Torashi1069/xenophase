#pragma once
#include "Parser.h"
class Protocol;


class CStream
{
public:
	CStream(std::string localver, std::string remotever);
	~CStream();

	void RecvIn(const BYTE* input, size_t size);
	void SendIn(const BYTE* input, size_t size);
	void RecvOut(std::vector<BYTE>& outbuf);
	void SendOut(std::vector<BYTE>& outbuf);

private:
	Parser m_recv; // packets from server
	Parser m_send; // packets from client
	const Protocol* m_localproto;
	const Protocol* m_remoteproto;
};
