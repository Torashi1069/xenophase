#pragma once


class NXObject
{
private:
	/* this+ 0 */ //const NXObject::`vftable';
	/* this+ 4 */ const std::string m_strOBJname;
	/* this+32 */ const unsigned int m_MyID;

public:
	std::string GetOBJName() const;
	const unsigned int GetMyID() const;

public:
	NXObject(const std::string in_strOBJname);
	virtual ~NXObject();
};
