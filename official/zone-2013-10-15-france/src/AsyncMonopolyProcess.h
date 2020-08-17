#pragma once


namespace AsyncMonopolyProcess {
enum enumType
{
	TYPE_NONE          = 0,
	TYPE_ONACTORINIT   = 1,
	TYPE_LOGONPERMIT   = 2,
	TYPE_BANKINGPERMIT = 3,
};
} // namespace AsyncMonopolyProcess


class CAsyncMonopolyProcess
{
public:
	virtual bool operator()() { return true; }
	enum AsyncMonopolyProcess::enumType GetType() { return m_Type; }

public:
	CAsyncMonopolyProcess(const AsyncMonopolyProcess::enumType in_Type) : m_Type(in_Type) { }
	virtual ~CAsyncMonopolyProcess() { }

private:
	/* this+0 */ //const CAsyncMonopolyProcess::`vftable';
	/* this+4 */ const AsyncMonopolyProcess::enumType m_Type;
};
