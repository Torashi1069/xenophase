#pragma once


class NIDAllocator
{
private:
	/* static  */ static NIDAllocator*& m_cpSelf; //TODO
	/* this+ 0 */ //const NIDAllocator::`vftable';
	/* this+ 4 */ RTL_CRITICAL_SECTION m_CS;
	/* this+28 */ bool m_bOK;

private:
	class NIDGenerator
	{
	private:
		/* this+ 0 */ //const NIDGenerator::`vftable';
		/* this+ 4 */ const unsigned int m_MinID;
		/* this+ 8 */ const unsigned int m_MaxID;
		/* this+12 */ const unsigned char m_GroupID;
		typedef std::map<unsigned int,bool> IDCONTAINER;
		typedef std::map<unsigned int,bool>::iterator IDCONTAINERITOR;
		typedef std::queue<unsigned int> STANDBYIDQUEUE;
		/* this+16 */ STANDBYIDQUEUE m_StandbyIDqueue;
		/* this+40 */ IDCONTAINER m_IDContainer;
		/* this+56 */ bool m_bOK;

	public:
		bool isOK() const;
		unsigned int Alloc();
		void Free(const unsigned int in_ID);
		const int GetGroupID();

	public:
		NIDGenerator(const unsigned int in_GroupID, const unsigned int in_MinID, const unsigned int in_MaxID);
		virtual ~NIDGenerator();
	};

private:
	typedef std::map<std::string,NIDGenerator*> GROUPCONTAINER;
	typedef std::map<std::string,NIDGenerator*>::iterator GROUPCONTAINERITOR;
	/* this+32 */ GROUPCONTAINER m_GroupContainer;
	/* this+48 */ unsigned int m_LastAlloGroupNum;

private:
	bool Create();
	void Destory();

public:
	bool isOK() const;
	bool RegisterGroup(const std::string in_strGroupName, const unsigned int in_MinID, const unsigned int in_MaxID);
	unsigned int Alloc(const std::string in_strGroupName);
	void Free(const std::string in_strGroupName, const unsigned int in_ID);
	const int GetGroupID(const unsigned int in_ID);
	const int GetGroupID(const std::string in_strGroupName);

public:
	static NIDAllocator* GetObj();
	static bool CreateInstance();
	static void DestoryInstance();

protected:
	NIDAllocator();
	virtual ~NIDAllocator();
};
