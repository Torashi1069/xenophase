#include "PatchList.h"
#include <hash/md5.hpp>


bool patchentry_t::loadFromStr(const char* str, size_t len)
{
	if( len < 7 )
		return false; // too short

	if( str[0] == '/' && str[1] == '/' )
		return false; // comment

	char w1[200], w2[200], w3[200], w4[200];
	int nfields = _snscanf(str, len, "%200s%200s%200s%32s", w1, w2, w3, w4);
	if( nfields < 2 )
		return false; // wrong format

	// w1 - patch level
	this->num = atoi(w1);

	// w2 - file name
	strncpy(this->filename, w2, sizeof(this->filename)-1);
	this->filename[sizeof(this->filename)-1] = '\0';

	// w3 - file size
	this->size = 0;
	if( nfields >= 3 )
		this->size = atoi(w3);

	// w4 - md5 hash
	this->md5[0] = '\0';
	if( nfields >= 4 && strlen(w4) == 32 )
	{
		memcpy(this->md5, w4, 32);
		this->md5[sizeof(this->md5)-1] = '\0';
	}

	return true;
}


std::string patchentry_t::ext() const
{
	const char* p = strrchr(this->filename, '.');
	return ( p != NULL ) ? p + 1 : "";
}


bool patchentry_t::hasMD5() const
{
	return ( this->md5[0] != '\0' );
}


bool patchentry_t::checkMD5() const
{
	return ( this->md5 == MD5::filehash_hex(this->filename) );
}
