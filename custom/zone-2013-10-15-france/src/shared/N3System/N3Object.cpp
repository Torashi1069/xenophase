#include "shared/N3System/N3Object.h"


namespace {
class N3ObjectIDGenerator
{
public:
	unsigned int operator()() { return ++m_Num; }

public:
	N3ObjectIDGenerator() { m_Num = 0; }
	virtual ~N3ObjectIDGenerator() { }

private:
	/* this+0 */ //const N3ObjectIDGenerator::`vftable';
	/* this+4 */ unsigned int m_Num;
};
}; // namespace


/// locals
N3ObjectIDGenerator& InstanceN3ObjectIDGenerator = VTOR<N3ObjectIDGenerator>(DetourFindFunction(EXEPATH(), "InstanceN3ObjectIDGenerator"));


N3Object::N3Object()
: m_MyID(InstanceN3ObjectIDGenerator())
{
}


N3Object::~N3Object()
{
}


unsigned int N3Object::GetMyID()
{
	return m_MyID;
}
