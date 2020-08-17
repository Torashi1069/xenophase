#pragma once
#include <string>
#include <vector>
class StackWalkerArray;


/// Data of a single call stack entry.
struct CallStackEntry
{
	intptr_t address;     // current instruction's memory address
	std::string function; // current function name
	std::string module;   // current module name
	std::string file;     // source code file path
	int line;             // source code line number
	int linedelta;        // binary instruction offset from last source line
};


/// Main stack handling class.
class CallStack
{
public:
	CallStack(void);
	~CallStack(void);

	/// Captures a snapshot of the current call stack.
	const std::vector<CallStackEntry>& makeSnapshot(void);

private:
	/// Internal stackwalker object.
	StackWalkerArray* m_sw;
};
