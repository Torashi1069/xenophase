#pragma once


class NAsyncDBPacketRecorder
{
	/* this+0x0  */ //const NAsyncDBPacketRecorder::`vftable'
	/* static    */ private: static hook_ptr<NAsyncDBPacketRecorder*> m_cpSelf;
	/* this+0x4  */ private: bool m_bOK;
	/* this+0x8  */ private: RTL_CRITICAL_SECTION m_CS;
	/* this+0x20 */ private: char m_szFileName[MAX_PATH];

	//public: const bool isOK();
	//public: const bool isCaptureAID(const unsigned long);
	//public: void NewFile();
	//public: void Write(const unsigned char *, const int);
	//public: static class NAsyncDBPacketRecorder * GetObj();
	//public: static bool CreateInstance();
	//public: static void DestoryInstance();
	private: NAsyncDBPacketRecorder::NAsyncDBPacketRecorder(void);
	private: virtual NAsyncDBPacketRecorder::~NAsyncDBPacketRecorder(void);
};
