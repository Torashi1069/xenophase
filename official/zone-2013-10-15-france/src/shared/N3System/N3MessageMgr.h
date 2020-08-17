#pragma once
#include "shared/N3System/N3Inter.h"


class N3MessageMgr
{
public:
	bool isOK() const;
	bool Insert(const unsigned int in_hID, N3Inter* in_cpInter);
	void Remove(const unsigned int in_hID, N3Inter* in_cpInter);
	bool Post(const unsigned int in_ToInter, const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static N3MessageMgr* GetObj(); /// @custom

private:
	N3MessageMgr();
	N3MessageMgr(const N3MessageMgr&); // = delete;
	N3MessageMgr& operator=(const N3MessageMgr&); // = delete;
	virtual ~N3MessageMgr();

private:
	/* static  */ static N3MessageMgr*& m_cpSelf; //TODO
	/* this+ 0 */ //const N3MessageMgr::`vftable';
	/* this+ 4 */ RTL_CRITICAL_SECTION m_CS;
	/* this+28 */ bool m_bOK;
	typedef std::map<unsigned int,N3Inter*> OBJCONTAINER;
	/* this+32 */ OBJCONTAINER m_ObjContainer;
};
