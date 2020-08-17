#pragma once
#include "std/string"


class CBuffInfo
{
	struct vtable_t // const CBuffInfo::`vftable'
	{
		bool (CBuffInfo::* IsResetPretendDead)(void);
		bool (CBuffInfo::* IsExistScript)(void);
	};

	/* this+ 0 */ //public: void* vtable;
	/* this+ 4 */ private: int m_type;
	/* this+ 8 */ private: bool m_isResetDead;
	/* this+ 9 */ private: bool m_isResetDispel;
	/* this+10 */ private: bool m_isSave;
	/* this+11 */ private: bool m_isSend;
	/* this+12 */ private: bool m_isIgnorePretendDead;
	/* this+13 */ private: bool m_isDeBuff;
	/* this+14 */ private: bool m_isResetCLEARANCE;
	/* this+15 */ private: bool m_isGC_NEWPOISON;
	/* this+16 */ private: mystd::string m_name;

	public: CBuffInfo::CBuffInfo(int buffType, const char* buffName) // line 6
	{
		m_type = buffType;
		m_isResetDead = false;
		m_isResetDispel = false;
		m_isSave = false;
		m_isSend = false;
		m_isIgnorePretendDead = false;
		m_isDeBuff = false;
		m_isResetCLEARANCE = false;
		m_isGC_NEWPOISON = false;
		m_name = buffName;
	}

	public: void CBuffInfo::Init(bool isResetDead, bool isResetDispel, bool isSave, bool isSend, bool isResetCLEARANCE)
	{
		m_isResetDead = isResetDead;
		m_isResetDispel = isResetDispel;
		m_isSave = isSave;
		m_isSend = isSend;
		m_isResetCLEARANCE = isResetCLEARANCE;
	}

	public: virtual bool CBuffInfo::IsResetPretendDead(void) // line 39
	{
		return ( m_isIgnorePretendDead ) ? false : m_isResetDead;
	}

	public: virtual bool CBuffInfo::IsExistScript(void)
	{
		return false;
	}

	public: int CBuffInfo::GetType(void)
	{
		return m_type;
	}

	public: const char* CBuffInfo::GetName(void)
	{
		return m_name.c_str();
	}

	public: bool IsResetDead(void)
	{
		return m_isResetDead;
	}

	public: void SetResetDead(bool flag)
	{
		m_isResetDead = flag;		
	}

	public: bool IsResetDispel(void)
	{
		return m_isResetDispel;
	}

	public: void SetResetDispel(bool flag)
	{
		m_isResetDispel = flag;
	}

	public: bool IsSave(void)
	{
		return m_isSave;
	}

	public: void SetSave(bool flag)
	{
		m_isSave = flag;
	}

	public: bool IsSend(void)
	{
		return m_isSend;
	}

	public: void SetSend(bool flag)
	{
		m_isSend = flag;
	}

	public: bool IsIgnorePretendDead(void)
	{
		return m_isIgnorePretendDead;
	}

	public: void SetIgnorePretendDead(bool flag)
	{
		m_isIgnorePretendDead = flag;
	}

	public: bool IsDeBuff(void)
	{
		return m_isDeBuff;
	}

	public: void SetDeBuff(bool flag)
	{
		m_isDeBuff = flag;
	}

	public: bool IsResetCLEARANCE(void)
	{
		return m_isResetCLEARANCE;
	}

	public: void SetResetCLEARANCE(bool flag)
	{
		m_isResetCLEARANCE = flag;
	}

	public: bool IsGC_NEWPOISON(void)
	{
		return m_isGC_NEWPOISON;
	}

	public: void SetGC_NEWPOISON(bool flag)
	{
		m_isGC_NEWPOISON = flag;
	}
};
