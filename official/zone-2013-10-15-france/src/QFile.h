#pragma once


class CQFile
{
public:
	std::pair<bool,int> Open(const std::string in_filename);
	void Close();
	int Read(char* out_pBuffer, const int in_ReadBytes);

public:
	CQFile();
	virtual ~CQFile();

private:
	/* this+0 */ //const CQFile::`vftable';
	/* this+4 */ FILE* m_fp;
};
