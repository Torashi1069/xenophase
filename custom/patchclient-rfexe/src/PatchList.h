#pragma once
#include <list>
#include <string>


struct patchentry_t
{
	unsigned int num;    // patch level
	char filename[50+1]; // file name
	unsigned int size;   // file size, 0 = unknown
	char md5[32+1];      // md5 hash, "" = unknown

	bool loadFromStr(const char* str, size_t len);
	std::string ext() const;
	bool hasMD5() const;
	bool checkMD5() const;
};


typedef std::list<patchentry_t> patchlist_t;
