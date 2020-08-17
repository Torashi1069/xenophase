#pragma once
#include "AsyncDBWork/NXInter.h"


class NInterMessageSystem
{
private:
	/* static  */ static NInterMessageSystem*& m_cpSelf; //TODO
	/* this+ 0 */ //const NInterMessageSystem::`vftable';
	/* this+ 4 */ RTL_CRITICAL_SECTION m_CS;
	/* this+28 */ bool m_bOK;
	typedef std::map<unsigned int,NXInter*> IOBJCONTAINER;
	typedef std::map<unsigned int,NXInter*>::iterator IOBJCONTAINERITOR;
	/* this+32 */ IOBJCONTAINER m_InterObjContainer;

public:
	bool isOK() const;
	bool Insert(const unsigned int in_hID, NXInter* in_cpInter);
	void Remove(const unsigned int in_hID, NXInter* in_cpInter);
	bool PostInterMessage(const unsigned int in_ToInter, const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Msg, const int in_wParam, const int in_lParam);

public:
	static NInterMessageSystem* GetObj();
	static bool CreateInstance();
	static void DestoryInstance();

protected:
	NInterMessageSystem();
	virtual ~NInterMessageSystem();
};
