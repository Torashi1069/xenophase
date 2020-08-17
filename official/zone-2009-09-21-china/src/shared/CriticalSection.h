#pragma once


class CCriticalSection
{
public:
	/* this+0x0 */ private: RTL_CRITICAL_SECTION m_CriticalSection;

	public:      CCriticalSection::CCriticalSection(void);
	public:      CCriticalSection::~CCriticalSection(void);
	public: void CCriticalSection::Init(void);
	public: void CCriticalSection::Delete(void);
	public: void CCriticalSection::Enter(void);
	public: void CCriticalSection::Leave(void);
};
