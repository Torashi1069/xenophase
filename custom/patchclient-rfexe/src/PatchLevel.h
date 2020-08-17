#pragma once


class PatchLevel
{
public:
	PatchLevel();
	~PatchLevel();

	bool Get(unsigned int* out_level);
	bool Set(unsigned int new_level);

private:
	unsigned int m_level; // cache
	bool m_loaded; // is cache filled?
	bool Load(); // load cache from disk
	bool Save(); // flush cache to disk
};
