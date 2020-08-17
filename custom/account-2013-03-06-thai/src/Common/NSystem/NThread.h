#pragma once


class NThread
{
public:
//	const bool isOK() const;
	bool Begin();
	bool isRun();
	void End();
//	void Resume();
//	void Suspend();
//	std::string GetName();
	NThread(const std::string in_Name);
	virtual ~NThread();

private:
	static unsigned int __stdcall ThreadFunctionCaller(void* in_pParam);
	virtual unsigned int ThreadFunction() = 0;
	virtual void PostThreadQuitMessage() = 0;

private:
	/* this+ 0 */ //const NThread::`vftable';
	/* this+ 4 */ unsigned int m_ThreadID;
	/* this+ 8 */ bool m_bOK;
	/* this+12 */ enum enumState { STATE_UNLOAD = 0, STATE_RUN = 1, STATE_PAUSE = 2 } m_State;
	/* this+16 */ HANDLE m_hThread;
	/* this+20 */ const std::string m_Name;
};
