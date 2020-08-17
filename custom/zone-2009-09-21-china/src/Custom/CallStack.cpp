#include "CallStack.h"
#include <stackwalker/stackwalker.h>
#include <string>
#include <vector>


/// Internal stackwalker class.
class StackWalkerArray : private StackWalker
{
public:
	StackWalkerArray(void) : StackWalker(RetrieveSymbol|RetrieveLine)
	{
	}

	const std::vector<CallStackEntry>& makeSnapshot(void)
	{
		m_snapshot.clear();
		this->ShowCallstack();
		return m_snapshot;
	}

private:
	std::vector<CallStackEntry> m_snapshot;

protected:
	virtual void OnCallstackEntry(CallstackEntryType eType, CallstackEntry &entry)
	{
		if( eType == lastEntry || entry.offset == 0 )
			return;

		CallStackEntry st;
		st.address = (intptr_t)entry.offset;
		st.function = ( *entry.undFullName ) ? entry.undFullName : ( *entry.undName ) ? entry.undName : ( *entry.name ) ? entry.name : "";
		st.module = entry.moduleName;
		st.file = entry.lineFileName;
		st.line = entry.lineNumber;
		st.linedelta = entry.offsetFromLine;

		m_snapshot.push_back(st);
	}

	virtual void OnOutput(LPCSTR buffer)
	{
	}
};


CallStack::CallStack(void)
{
	m_sw = new StackWalkerArray();
}


CallStack::~CallStack(void)
{
	delete m_sw;
}


const std::vector<CallStackEntry>& CallStack::makeSnapshot(void)
{
	return m_sw->makeSnapshot();
}
