#pragma once
#include "Base/Hash.h"


class CRes
{
protected:
	/* this+ 0 */ //const CRes::`vftable';
	/* this+ 4 */ int m_lockCnt;
	/* this+ 8 */ DWORD m_timeStamp;
	/* this+12 */ int m_extIndex;
	/* this+16 */ CHash m_fName;

public:
	CRes();
	virtual ~CRes();
	virtual bool LoadFromBuffer(const char* fName, const unsigned char* buffer, int size);
	int Lock();
	int Unlock();
	const char* GetName();
	void UpdateInfo(const char* fName, int extIndex);
	void UpdateTimeStamp();

protected:
	virtual CRes* Clone() const = 0;
	virtual bool Load(const char* fName) = 0;
	virtual void Reset();
	virtual void OnLoadError(const char* fName);

private:
	friend class CResMgr;
};


struct CResVtbl
{
	void* (CRes::* scalar_deleting_destructor)(unsigned int flags);
	bool (CRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
	CRes* (CRes::* Clone)() const; // __purecall
	bool (CRes::* Load)(const char* fName); // __purecall
	void (CRes::* Reset)();
	void (CRes::* OnLoadError)(const char* fName);
};


struct ResPtrLess : public std::binary_function<CHash*,CHash*,bool>
{
	public: bool ResPtrLess::operator()(CHash* left, CHash* right) const
	{
		if( *left == *right )
			return true;

		return( *left < *right );
	}
};


class Exemplar
{
	/* this+0 */ char dummy;
};
