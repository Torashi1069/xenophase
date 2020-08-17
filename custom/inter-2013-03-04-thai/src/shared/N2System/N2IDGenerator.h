#pragma once


class N2IDGenerator
{
private:
	/* this+ 0 */ //const N2IDGenerator::`vftable';
	/* this+ 4 */ const unsigned short m_MinID;
	/* this+ 6 */ const unsigned short m_MaxID;
	/* this+ 8 */ const unsigned short m_GroupID;
	typedef std::map<unsigned int,bool> IDCONTAINER;
	typedef std::map<unsigned int,bool>::iterator IDCONTAINERITOR;
	typedef std::queue<unsigned int,std::deque<unsigned int>> STANDBYIDQUEUE;
	/* this+12 */ STANDBYIDQUEUE m_StandbyIDqueue;
	/* this+44 */ IDCONTAINER m_IDContainer;
	/* this+76 */ bool m_bOK;

public:
	const bool isOK() const;
	unsigned int Alloc();
	void Free(const unsigned int in_ID);
	const int GetGroupID();

public:
	N2IDGenerator(const unsigned short in_GroupID, const unsigned short in_MinID, const unsigned short in_MaxID);
	virtual ~N2IDGenerator();
};
