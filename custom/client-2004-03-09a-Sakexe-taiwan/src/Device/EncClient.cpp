#include "Device/EncClient.h"


hook_method<void (EncClient::*)(void)> EncClient::_Reset(SAKEXE, "EncClient::Reset");
void EncClient::Reset(void) // line 35
{
	return (this->*_Reset)();

	//TODO
}


hook_method<void (EncClient::*)(const coder_packet& coderPacket, unsigned char* encKey)> EncClient::_AddEncKey(SAKEXE, "EncClient::AddEncKey");
void EncClient::AddEncKey(const coder_packet& coderPacket, unsigned char* encKey) // line 43
{
	return (this->*_AddEncKey)(coderPacket, encKey);

	//TODO
}


hook_method<void (EncClient::*)(const coder_packet& coderPacket, unsigned char* encKey)> EncClient::_AddDecKey(SAKEXE, "EncClient::AddDecKey");
void EncClient::AddDecKey(const coder_packet& coderPacket, unsigned char* encKey) // line 56
{
	return (this->*_AddDecKey)(coderPacket, encKey);

	//TODO
}


hook_method<void (EncClient::*)(unsigned char* buffer, int len)> EncClient::_EncData(SAKEXE, "EncClient::EncData");
void EncClient::EncData(unsigned char* buffer, int len) // line 69
{
	return (this->*_EncData)(buffer, len);

	//TODO
}


hook_method<void (EncClient::*)(unsigned char* buffer, int len)> EncClient::_DecData(SAKEXE, "EncClient::DecData");
void EncClient::DecData(unsigned char* buffer, int len) // line 79
{
	return (this->*_DecData)(buffer, len);

	//TODO
}


hook_method<unsigned char* (EncClient::*)(unsigned char* buf)> EncClient::_FindToken(SAKEXE, "EncClient::FindToken");
unsigned char* EncClient::FindToken(unsigned char* buf) // line 89
{
	return (this->*_FindToken)(buf);

	//TODO
}


hook_method<void (EncClient::*)(unsigned char* func, unsigned char* target)> EncClient::_SET_JMP(SAKEXE, "EncClient::SET_JMP");
void EncClient::SET_JMP(unsigned char* func, unsigned char* target) // line 97
{
	return (this->*_SET_JMP)(func, target);

	//TODO
}


hook_method<void (EncClient::*)(unsigned char* func, unsigned char* target)> EncClient::_SET_CALL(SAKEXE, "EncClient::SET_CALL");
void EncClient::SET_CALL(unsigned char* func, unsigned char* target) // line 104
{
	return (this->*_SET_CALL)(func, target);

	//TODO
}


hook_method<void (EncClient::*)(unsigned char* func, unsigned char* target)> EncClient::_SET_DEST_ADDR(SAKEXE, "EncClient::SET_DEST_ADDR");
void EncClient::SET_DEST_ADDR(unsigned char* func, unsigned char* target) // line 111
{
	return (this->*_SET_DEST_ADDR)(func, target);

	//TODO
}


hook_method<void (EncClient::*)(unsigned char* func)> EncClient::_InitCoder(SAKEXE, "EncClient::InitCoder");
void EncClient::InitCoder(unsigned char* func) // line 116
{
	return (this->*_InitCoder)(func);

	//TODO
}
