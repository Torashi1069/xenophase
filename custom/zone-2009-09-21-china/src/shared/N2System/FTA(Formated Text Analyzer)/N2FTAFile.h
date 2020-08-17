#pragma once
#include "std/map"
#include "std/string"


class N2FTAFile
{
public:
	struct tagCur
	{
		/* this+0x0 */ int Idx;
		/* this+0x4 */ int Line;
		/* this+0x8 */ int Col;
	};

	class CLineInfo
	{
		/* this+0x0 */ public: unsigned char* m_pBuffer;
		/* this+0x4 */ public: int m_Bytes;

		public: CLineInfo::CLineInfo(unsigned char* in_pBuffer, int in_Bytes)
		{
			m_pBuffer = in_pBuffer;
			m_Bytes = in_Bytes;
		}

		public: CLineInfo::~CLineInfo(void)
		{
		}
	};

	typedef mystd::map<int,N2FTAFile::CLineInfo> LINEINFOCONTAINERITER;

	/* this+0x0  */ //const N2FTAFile::`vftable'
	/* this+0x4  */ private: const int m_TABSIZE;
	/* this+0x8  */ private: unsigned char* m_pBuffer;
	/* this+0xC  */ private: int m_TotalBytes;
	/* this+0x10 */ private: mystd::string m_strFileName;
	/* this+0x2C */ private: N2FTAFile::tagCur m_Cur;
	/* this+0x38 */ private: mystd::map<int,N2FTAFile::CLineInfo> m_LineInfoContainer;

	public: N2FTAFile::N2FTAFile(const int in_TABSIZE);
	public: virtual N2FTAFile::~N2FTAFile(void);
	private: void N2FTAFile::Clear(void);
	private: bool N2FTAFile::ParseLine(void);
	public: bool N2FTAFile::Load(const mystd::string in_strFileName);
	//public: bool N2FTAFile::Write(const mystd::string);
	//public: bool N2FTAFile::isEOF();
	//public: bool N2FTAFile::GetByte(char &);
	//public: const int N2FTAFile::GetCurIdx();
	//public: const bool N2FTAFile::ViewByte(char &, const int);
	//public: const bool N2FTAFile::ViewByte(char &);
	//public: const int N2FTAFile::GetLine();
	//public: const int N2FTAFile::GetCol();
	//public: const mystd::string N2FTAFile::GetLineStr(const int);
	//public: const mystd::string N2FTAFile::GetFileName();

private:
	static hook_method<void (N2FTAFile::*)(void)> N2FTAFile::_Clear;
	static hook_method<bool (N2FTAFile::*)(void)> N2FTAFile::_ParseLine;
	static hook_method<bool (N2FTAFile::*)(const mystd::string in_strFileName)> N2FTAFile::_Load;
};
