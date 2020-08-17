#pragma once


class CFTFile
{
private:
	/* this+ 0 */ //const CFTFile::`vftable';
	/* this+ 4 */ const std::string m_strFileName;
	/* this+32 */ char* m_pBuffer;
	/* this+36 */ int m_TotalBytes;
	/* this+40 */ bool m_bOK;
	/* this+44 */ int m_ReadPositionIdx;
	/* this+48 */ int m_Line;
	/* this+52 */ int m_Col;

private:
	bool Load();
	long GetLength() const;

protected:
	bool isOK() const;
	bool ReadByte(char& out_ch);
	void UndoByte();
	bool ViewByte(char& out_ch);
	int GetCurLine();
	int GetCurCol();
	bool isEOF();
	const std::string GetFileName() const;

protected:
	CFTFile(const std::string in_strFileName);
	virtual ~CFTFile();
};
