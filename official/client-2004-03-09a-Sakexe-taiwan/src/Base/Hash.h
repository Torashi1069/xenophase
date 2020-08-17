#pragma once


/// Represents a lowercase string and its hash (djb2 algorithm).
/// @see http://www.cse.yorku.ca/~oz/hash.html
class CHash
{
public:
	CHash();
	CHash(const char* str);

public:
	void SetString(const char* str);
	const char* c_str() const;
	bool operator< (const CHash& hash) const;
	bool operator==(const CHash& hash) const;
	bool operator!=(const CHash& hash) const;

protected:
	/* this+0 */ unsigned long m_HashCode;
	/* this+4 */ char m_String[252];

protected:
	void CreateHashCode();
};
