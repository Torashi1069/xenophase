#pragma once
class N2IDGenerator;


class N2IDAllocator
{
private:
	/* this+0  */ //const N2IDAllocator::`vftable';
	/* static  */ static N2IDAllocator*& m_cpSelf; //TODO
	/* this+ 4 */ RTL_CRITICAL_SECTION m_CS;
	/* this+28 */ bool m_bOK;
	typedef std::map<unsigned short,N2IDGenerator*> GROUPCONTAINER;
	typedef std::map<unsigned short,N2IDGenerator*>::iterator GROUPCONTAINERITOR;
	/* this+32 */ GROUPCONTAINER m_GroupContainer;

private:
	bool Create();
	void Destroy();

public:
	bool isOK() const;
	bool RegisterGroup(const unsigned short in_GroupID, const unsigned short in_MinID, const unsigned short in_MaxID);
	unsigned int Alloc(const unsigned short in_GroupID);
	static unsigned short GetGroupID(const unsigned int in_ID);
	void Free(const unsigned int in_ID);

public:
	static bool CreateInstance();
	static void DestoryInstance();
	static N2IDAllocator* GetObj(); ///@custom

protected:
	N2IDAllocator();
	virtual ~N2IDAllocator();
};
