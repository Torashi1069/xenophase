#include "Common/NSystem/NObject.h"
/////////////////////////////////////////


namespace {
class NObjectIDGenerator
{
public:
	NObjectIDGenerator() { m_Num = 0; }
	unsigned int operator()() { return ++m_Num; }
	
private:
	/* this+0 */ unsigned int m_Num;
};

NObjectIDGenerator InstanceNObjectIDGenerator;
}; // namespace


/////////////////////////////////////////


NObject::NObject()
: m_MyID(InstanceNObjectIDGenerator())
{
}


NObject::~NObject()
{
}


const unsigned int NObject::GetMyID() const
{
	return m_MyID;
}


/////////////////////////////////////////
