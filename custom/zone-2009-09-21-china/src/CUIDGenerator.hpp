#pragma once


class CUIDGenerator
{
public:
	enum { MAXIMUN_SEQEUNCE_NUM = -1 };

	/* this+ 0 */ public: //const CUIDGenerator::`vftable';
	/* this+ 4 */ private: unsigned int m_ServerBootSequeceNum;
	/* this+ 8 */ private: unsigned int m_SequenceNum;
	/* this+12 */ private: bool m_bOK;
	/* static  */ private: static hook_ptr<CUIDGenerator *> m_cpSelf;

	private: bool CUIDGenerator::LoadBootingSequenceNum(void);
	public: static CUIDGenerator* __cdecl CUIDGenerator::GetObj(void);
	public: __int64 CUIDGenerator::Get(void);
	public: bool CUIDGenerator::isOK(void);
	public: bool CUIDGenerator::Init(void);
	private: CUIDGenerator::CUIDGenerator(void);
	private: virtual CUIDGenerator::~CUIDGenerator(void);

private:
	static hook_method<bool (CUIDGenerator::*)(void)> CUIDGenerator::_LoadBootingSequenceNum;
	static hook_method<static CUIDGenerator* (__cdecl *)(void)> CUIDGenerator::_GetObj;
	static hook_method<__int64 (CUIDGenerator::*)(void)> CUIDGenerator::_Get;
	static hook_method<bool (CUIDGenerator::*)(void)> CUIDGenerator::_isOK;
	static hook_method<bool (CUIDGenerator::*)(void)> CUIDGenerator::_Init;
};
