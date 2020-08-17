#pragma once


class N3Thread
{
public:
	const bool isOK() const;
	bool Begin();
	void End();
	void Resume();
	void Suspend();
	std::string GetName();
	DWORD_PTR SetThreadAffinityMask(const DWORD_PTR in_Mask);

public:
	N3Thread(const std::string in_Name);
	virtual ~N3Thread();
	N3Thread(const N3Thread&); // = delete;
	N3Thread& operator=(const N3Thread&); // = delete;

private:
	static unsigned int __stdcall ThreadFunctionCaller(void* in_pParam);
	virtual unsigned int ThreadFunction() = 0;
	virtual void PostThreadQuitMessage() = 0;

private:
	/* this+ 0 */ //const N3Thread::`vftable';
	/* this+ 4 */ DWORD m_ThreadID;
	/* this+ 8 */ bool m_bOK;
	/* this+12 */ enum enumState { STATE_UNLOAD = 0, STATE_RUN = 1, STATE_PAUSE = 2 } m_State;
	/* this+16 */ HANDLE m_hThread;
	/* this+20 */ const std::string m_Name;
};
