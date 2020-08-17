#pragma once


struct coder_data
{
	/* this+     0 */ unsigned long temp[65536];
	/* this+262144 */ unsigned char func[4096];
};


struct coder_packet
{
	/* this+0 */ short len;
	/* this+2 */ short random;
};


class EncClient
{
	/* this+ 0 */ private: mystd::list<coder_data> m_decoderData;
	/* this+12 */ private: mystd::list<coder_data> m_encoderData;
	/* this+24 */ private: unsigned char* m_coderDestAddr;
	typedef mystd::list<coder_data>::const_iterator coder_list_iter;

	//public: EncClient::EncClient(void);
	public: void EncClient::Reset(void);
	//public: int GetKeySize(const struct coder_packet &);
	public: void EncClient::AddEncKey(const coder_packet& coderPacket, unsigned char* encKey);
	public: void EncClient::AddDecKey(const coder_packet& coderPacket, unsigned char* encKey);
	public: void EncClient::EncData(unsigned char* buffer, int len);
	public: void EncClient::DecData(unsigned char* buffer, int len);
	//public: bool IsEnable(void);
	private: unsigned char* EncClient::FindToken(unsigned char* buf);
	private: void EncClient::SET_JMP(unsigned char* func, unsigned char* target);
	private: void EncClient::SET_CALL(unsigned char* func, unsigned char* target);
	private: void EncClient::SET_DEST_ADDR(unsigned char* func, unsigned char* target);
	private: void EncClient::InitCoder(unsigned char* func);

private:
	static hook_method<void (EncClient::*)(void)> EncClient::_Reset;
	static hook_method<void (EncClient::*)(const coder_packet& coderPacket, unsigned char* encKey)> EncClient::_AddEncKey;
	static hook_method<void (EncClient::*)(const coder_packet& coderPacket, unsigned char* encKey)> EncClient::_AddDecKey;
	static hook_method<void (EncClient::*)(unsigned char* buffer, int len)> EncClient::_EncData;
	static hook_method<void (EncClient::*)(unsigned char* buffer, int len)> EncClient::_DecData;
	static hook_method<unsigned char* (EncClient::*)(unsigned char* buf)> EncClient::_FindToken;
	static hook_method<void (EncClient::*)(unsigned char* func, unsigned char* target)> EncClient::_SET_JMP;
	static hook_method<void (EncClient::*)(unsigned char* func, unsigned char* target)> EncClient::_SET_CALL;
	static hook_method<void (EncClient::*)(unsigned char* func, unsigned char* target)> EncClient::_SET_DEST_ADDR;
	static hook_method<void (EncClient::*)(unsigned char* func)> EncClient::_InitCoder;
};
