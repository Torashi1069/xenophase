#pragma once
#include "Packet.hpp"
#include <windows.h> // BYTE
#include <vector>
class Protocol;


class Parser
{
public:
	/// Ctor/Dtor.
	Parser();
	~Parser();

	/// Initializes the object.
	void Init(const Protocol* proto);

	/// Adds new data to be processed.
	void Process(const BYTE* input, size_t size);

	/// Retrieves a single packet from the internal buffer.
	Packet* Next();

private:
	/// Determines if there's full packet at the beginning of the buffer.
	/// @return newly allocated Packet object, or NULL
	Packet* Recognize();

	/// Matches packet against packet table to determine the packet's length.
	/// @return full packet length if successful, nonzero if more data is needed, 0 if unknown/invalid/malformed
	size_t DetermineLength(const BYTE* in_data, size_t in_size);

	/// Dumps useful state information into a log file.
	void Dump();

private:
	std::vector<BYTE> m_buffer;  // unprocessed data
	const Protocol* m_proto;     // packet length information
	bool m_expectingrawdata;     // non-conformant raw data handling
	std::vector<BYTE> m_prevPacket; // last recognized packet (debugging)
};
