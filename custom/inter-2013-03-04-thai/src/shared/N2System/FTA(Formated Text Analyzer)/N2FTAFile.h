#pragma once


class N2FTAFile
{
private:
	/* this+ 0 */ //const N2FTAFile::`vftable';
	/* this+ 4 */ const int m_TABSIZE;
	/* this+ 8 */ BYTE* m_pBuffer;
	/* this+12 */ int m_TotalBytes;
	/* this+16 */ std::string m_strFileName;

	struct tagCur
	{
		/* this+0 */ int Idx;
		/* this+4 */ int Line;
		/* this+8 */ int Col;
	};

	/* this+44 */ tagCur m_Cur;

	class CLineInfo
	{
	public:
		/* this+0 */ BYTE* m_pBuffer;
		/* this+4 */ int m_Bytes;

		CLineInfo(BYTE* in_pBuffer, int in_Bytes) : m_pBuffer(in_pBuffer), m_Bytes(in_Bytes) { }
		~CLineInfo() { }
	};

	typedef std::map<int,N2FTAFile::CLineInfo> LINEINFOCONTAINER;
	typedef std::map<int,N2FTAFile::CLineInfo>::iterator LINEINFOCONTAINERITER;

	/* this+56 */ LINEINFOCONTAINER m_LineInfoContainer;

private:
	void Clear();
	bool ParseLine();

public:
	bool Load(const std::string in_strFileName);
	bool Write(const std::string in_strFileName);
	bool isEOF();
	bool GetByte(char& out_ch);
	const int GetCurIdx() const;
	const bool ViewByte(char& out_ch) const;
	const bool ViewByte(char& out_ch, const int in_Idx) const;
	const int GetLine() const;
	const int GetCol() const;
	const std::string GetLineStr(const int in_Line);
	const std::string GetFileName() const;

public:
	N2FTAFile(const int in_TABSIZE);
	virtual ~N2FTAFile();
};
