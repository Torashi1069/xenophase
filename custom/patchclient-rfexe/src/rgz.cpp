#include "rgz.h"
#include <autorelease/AutoRelease.hpp>
#include <platform/disk.h> // mkdir(), FILE*
#include <platform/macro.h> // min()
#include <zlib/zlib.h> // gz*()


#define RGZ_TYPE_DIRECTORY	'd'
#define RGZ_TYPE_EOF		'e'
#define RGZ_TYPE_FILE		'f'


int rgz_unpack(const char* fname)
{
	gzFile rgzfile = gzopen(fname, "rb");
	if( rgzfile == NULL )
		return -1;
	AUTORELEASEL(rgzfile, (gzFile& file) { gzclose(file); });

	bool bDone = false;
	while( !bDone )
	{
		int type = 0;
		if( gzread(rgzfile, &type, 1) < 0 )
			return -1;

		int len = 0;
		if( gzread(rgzfile, &len, 1) < 0 )
			return -1;

		char name[256] = "";
		if( gzread(rgzfile, name, len) < 0 )
			return -1;

		switch( type )
		{
			case RGZ_TYPE_DIRECTORY:
			{
				int rc = mkdir(name);
				if( rc == -1 && errno == ENOENT )
					return -1; //the directory we're trying to create this directory in doesn't exist...
			}
			break;
			case RGZ_TYPE_FILE:
			{
				FILE* fp = fopen(name, "wb");
				if( fp == NULL )
					return -1;
				AUTORELEASEL(fp, (FILE*& fp) { fclose(fp); });

				int ulen = 0;
				if( gzread(rgzfile, &ulen, 4) < 0 )
					return -1;

				int i = 0;
				while( i != ulen )
				{
					char tmpbuf[1024];
					int chunkSize = min(ulen - i, sizeof(tmpbuf));

					int amountRead = gzread(rgzfile, tmpbuf, chunkSize);
					if (amountRead != chunkSize )
						return -1; // incomplete read

					int amountWritten = fwrite(tmpbuf, 1, chunkSize, fp);
					if( amountWritten != chunkSize )
						return -1; // incomplete write

					i += chunkSize;
				}
			}
			break;
			case RGZ_TYPE_EOF:
			{
				bDone = true;
			}
			break;
			default:
			{
				return -1;
			}
			break;
		}
	}

	return 0;
}
