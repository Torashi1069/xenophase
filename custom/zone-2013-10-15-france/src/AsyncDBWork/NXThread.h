#pragma once


class NXThread
{
public:
	bool isOK() const;
	bool Begin();
	void End();
	void Resume();
	void Suspend();
	DWORD_PTR SetThreadAffinityMask(const DWORD_PTR in_Mask);
	std::string GetName();

private:
	static unsigned int __stdcall ThreadFunctionCaller(void* in_pParam);
	virtual unsigned int ThreadFunction() = 0;
	virtual void PostThreadQuitMessage() = 0;

public:
	NXThread(const std::string in_Name);
	virtual ~NXThread();

private:
	/* this+ 0 */ //const NXThread::`vftable';
	/* this+ 4 */ unsigned long m_ThreadID;
	/* this+ 8 */ bool m_bOK;
	/* this+12 */ enum enumState { STATE_UNLOAD = 0, STATE_RUN = 1, STATE_PAUSE = 2 } m_State;
	/* this+16 */ HANDLE m_hThread;
	/* this+20 */ const std::string m_Name;
};
