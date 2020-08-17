#include "grffile.h"
#include "compress.h"
#include "decode.h"
#include "hash_tables.h"
#include "libgrf.h"
#include <algorithm> // std::replace<>
#include <memory> // std::auto_ptr<>
#include <platform/stdc.h> // size_t, uint*_t
#include <platform/disk.h> // FILE, f*()
#include <platform/macro.h> // C_ASSERT()


#pragma pack(push,1)
struct grf_header
{
	char header_magic[16]; // "Master of Magic" + 0x00
	char header_key[14];   // GRF_KEY_CRYPT[] or GRF_KEY_NOCRYPT[]
	uint32_t offset;       // offset of file table
	uint32_t seed;         // obfuscation for filecount
	uint32_t filecount;    // nfiles = filecount - seed - 7
	uint32_t version;      // 0x102 0x103 0x200
};
#pragma pack(pop)
C_ASSERT( sizeof(grf_header) == 46 );

#pragma pack(push,1)
struct grf_table_entry_data
{
//	char filename[];
	uint32_t len;         // compressed size
	uint32_t len_aligned; // size on disk (len + padding)
	uint32_t size;        // real file size (unpacked)
	uint8_t flags;        // file flags (GRF_FLAG_FILE, GRF_FLAG_MIXCRYPT, GRF_FLAG_DES)
	uint32_t pos;         // offset in the grf file (starting from after grf header)
};
#pragma pack(pop)
C_ASSERT( sizeof(grf_table_entry_data) == 17 );

// byte sequence after header_magic (ignored by everything since forever)
static const unsigned char GRF_KEY_CRYPT[14]   = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E };
static const unsigned char GRF_KEY_NOCRYPT[14] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// some magic constants
#define GRF_HEADER_SIZE sizeof(grf_header)
#define GRF_HEADER_MAGIC "Master of Magic"
#define GRF_FILE_OUTPUT_VERSION 0x200


GrfFile::GrfFile(void)
{
	m_fd = NULL;
	m_need_save = false;
}


GrfFile::~GrfFile(void)
{
	if( m_need_save )
		this->GrfFile::save();

	if( m_fd != NULL )
		fclose(m_fd);
}


bool GrfFile::create(const char* filename)
{
	FILE* fp = fopen(filename, "wb+");
	if( fp == NULL )
		return false;

	m_fd = fp;
	setbuf(m_fd, NULL); // no buffering
	m_need_save = true;
	return true;
}


bool GrfFile::load(const char* filename)
{
	FILE* fp = fopen(filename, "rb+");
	if( fp == NULL )
		return false;

	m_fd = fp;
	setbuf(m_fd, NULL); // no buffering
	return this->GrfFile::prv_load();
}


bool GrfFile::save(void)
{
	return this->GrfFile::prv_save();
}


GrfNode* GrfFile::file_add(const char* filename, const void* ptr, size_t size)
{
	uint8_t* zdata = new uint8_t[zlib_compressbound(size)];
	std::auto_ptr<uint8_t> autorelease(zdata);
	if( zdata == NULL )
		return NULL;

	uint32_t zlen = zlib_buffer_deflate(zdata, zlib_compressbound(size), ptr, size);
	return this->GrfFile::prv_file_add(filename, GRF_FLAG_FILE, size, zlen, zlen, zdata);
}


/// Rename the given file to new_name. Any existing entry with the same name will be deleted.
bool GrfFile::file_rename(GrfNode* node, const char* newname)
{
	GrfNode* old = this->find(newname);
	if( old != NULL ) this->erase(old);

	this->rename(node, newname);
	m_need_save = true;
	return true;
}


/// Removes a file from the GRF.
bool GrfFile::file_delete(GrfNode* node)
{
	this->erase(node);
	m_need_save = true;
	return true;
}


bool GrfFile::file_get_contents(const GrfNode* node, std::vector<uint8_t>& outbuf) const
{
	std::vector<uint8_t> zbuf;
	if( !this->file_get_zcontents(node, zbuf) )
		return false; // error

	outbuf.resize(node->size);
	uint32_t size = zlib_buffer_inflate(&outbuf[0], node->size, &zbuf[0], node->len);
	if( size == 0 )
		return false; // error

	return true;
}


bool GrfFile::file_get_zcontents(const GrfNode* node, std::vector<uint8_t>& outbuf) const
{
	outbuf.resize(DES_ALIGN(node->len_aligned));

	fseek(m_fd, node->pos + GRF_HEADER_SIZE, SEEK_SET);
	if( fread(&outbuf[0], 1, node->len_aligned, m_fd) != node->len_aligned )
		return false; // read failed

	grf_decode_data(&outbuf[0], node->len_aligned, node->flags, node->len);

	outbuf.resize(node->len);
	return true;
}


bool GrfFile::merge(const GrfFile* src)
{
	for( const GrfNode* node = src->m_first_node; node != NULL; node = node->next )
	{
		/// [patch] zero size means deletion
		if( node->size == 0 )
		{
			GrfNode* old_node = this->GrfFile::find(node->name);
			if( old_node != NULL ) this->GrfFile::file_delete(old_node);
			continue;
		}

		std::vector<uint8_t> zbuf;
		if( !src->GrfFile::file_get_zcontents(node, zbuf) )
			return false; // read error

		uint8_t flags = node->flags & ~(GRF_FLAG_MIXCRYPT | GRF_FLAG_DES);
		this->GrfFile::prv_file_add(node->name, flags, node->size, node->len, node->len_aligned, &zbuf.front());
	}

	return true;
}


bool GrfFile::repack(uint8_t repack_type)
{
	for( GrfNode* node = m_first_node; node != NULL; node = node->next )
	{
		uint32_t prevendpos = ( node->prev == NULL ) ? 0 : node->prev->pos + node->prev->len_aligned;

		bool bNeedShift   = ( node->pos > prevendpos );
		bool bNeedDecrypt = ( repack_type >= GRF_REPACK_DECRYPT && node->flags & (GRF_FLAG_MIXCRYPT | GRF_FLAG_DES) );
		bool bNeedRepack  = ( repack_type >= GRF_REPACK_RECOMPRESS );
		bool bChanged = false;

		if( !bNeedShift && !bNeedDecrypt && !bNeedRepack )
			continue; // no work needed

		// prepare data storage
		std::vector<uint8_t> zbuf;
		zbuf.resize(node->len_aligned);

		// read from disk
		fseek(m_fd, node->pos + GRF_HEADER_SIZE, SEEK_SET);
		fread(&zbuf.front(), 1, node->len_aligned, m_fd);

		if( bNeedDecrypt )
		{// remove encryption
			zbuf.reserve(DES_ALIGN(node->len_aligned)); //NOTE: potential read/write into vector reserve area during decode
			grf_decode_data(&zbuf.front(), node->len_aligned, node->flags, node->len);
			node->flags &= ~(GRF_FLAG_MIXCRYPT | GRF_FLAG_DES);
			bChanged = true;
		}

		if( bNeedRepack )
		{// recompress
			//TODO: unpack, pack again, compare sizes, if smaller copy to filemem and set bChanged = true
			//TODO: also update the node len/len_aligned values
		}

		if( bNeedShift )
		{// update location
			node->pos = prevendpos;
			bChanged = true;
		}

		if( bChanged )
		{// write to disk
			fseek(m_fd, node->pos + GRF_HEADER_SIZE, SEEK_SET);
			fwrite(&zbuf.front(), 1, node->len_aligned, m_fd);
			m_need_save = true;
		}
	}

	return true;
}


/// Generates an adler32 hash of the specified file.
/// @param hack if true, try to extract hash directly from zlib stream on disk
/// NOTE: The hack relies on implementation-specific assumptions about zlib streams in the grf:
/// * that the last 4 bytes of a zlib streams are the checksum (should be true)
/// * that the checksum part of the stream is byte-aligned (seems true)
/// * that node->len is actually the real zlib stream length (false, some files have extra zero padding included)
uint32_t GrfFile::file_get_hash(const GrfNode* node, bool hack) const
{
	uint32_t hash;

	// 32-bit big-endian to little-endian helper macro
	#define BE2LE32(x) ((((x) >> 24) & 0xff) + (((x) >> 8) & 0xff00) + (((x) & 0xff00) << 8) + (((x) & 0xff) << 24))
	
	if( node->len < 4 )
		return 0; // broken stream?!

	if( !hack )
	{// slowest method (read, decrypt, extract, compute hash)
		std::vector<uint8_t> buf;
		if( !this->GrfFile::file_get_contents(node, buf) )
			return 0;

		hash = zlib_adler32(&buf.front(), buf.size());
	}
	else
	if( node->flags & GRF_FLAG_MIXCRYPT || node->flags & GRF_FLAG_DES )
	{// slow method (read, decrypt, rip hash)
		std::vector<uint8_t> zbuf;
		if( !this->GrfFile::file_get_zcontents(node, zbuf) )
			return 0;

		memcpy(&hash, &zbuf[node->len - 4], 4);
		hash = BE2LE32(hash);
	}
	else
	{// fast method (read hash directly)
		fseek(m_fd, node->pos + GRF_HEADER_SIZE + node->len - 4, SEEK_SET);
		if( fread(&hash, 1, 4, m_fd) != 4 )
			return 0;

		hash = BE2LE32(hash);
	}

	#undef BE2LE32
	return hash;
}


GrfNode* GrfFile::get_file(const char* filename)
{
	return this->find(filename);
}


GrfNode* GrfFile::get_file_first(void)
{
	return m_first_node;
}


uint32_t GrfFile::get_file_list(GrfNode** arr, size_t num)
{
	int n = 0;

	// record nodes of linked list
	for( GrfNode* node = this->get_file_first(); node != NULL && n < num; node = node->get_next() )
		arr[n++] = node;

	// zero out the rest
	memset(&arr[n], (int)NULL, (num - n) * sizeof(GrfNode*));

	return n;
}


uint32_t GrfFile::filecount(void) const
{
	return this->size();
}


/// Returns the amount of data (in bytes) that would be theorically saved if the file gets repacked.
uint32_t GrfFile::wasted_space(void) const
{
	struct stat s;
	if( fstat(fileno(m_fd), &s) != 0 )
		return 0;

	uint32_t data = 0;
	uint32_t table = 0;
	for( GrfNode* node = m_first_node; node != NULL; node = node->next )
	{
		data += node->len_aligned;
		table += node->name.size()+1 + sizeof(struct grf_table_entry_data);
	}

	uint32_t wasted = s.st_size - GRF_HEADER_SIZE - data - table;
	return wasted;
}


bool GrfFile::prv_load(void)
{
	m_need_save = false;

	fseek(m_fd, 0, SEEK_SET);

	// load header...
	struct grf_header head;
	if( fread(&head, 1, sizeof(head), m_fd) != sizeof(head) ) return false; // read error
	if( strncmp(head.header_magic, GRF_HEADER_MAGIC, sizeof(head.header_magic)) != 0 ) return false; // bad magic !
	if( memcmp(head.header_key, GRF_KEY_CRYPT, sizeof(GRF_KEY_CRYPT)) != 0 && memcmp(head.header_key, GRF_KEY_NOCRYPT, sizeof(GRF_KEY_NOCRYPT)) != 0 ) return false;
	if( head.version != 0x102 && head.version != 0x103 && head.version != 0x200 ) return false; // unsupported version

	uint32_t table_pos = head.offset;
	uint32_t filecount = head.filecount - head.seed - 7;

	if( filecount == 0 ) return true; // do not even bother reading file table, it's empty

	struct stat grfstat;
	if( fstat(fileno(m_fd), &grfstat) != 0 ) return false;

	int grfsize = grfstat.st_size;
	if( table_pos + GRF_HEADER_SIZE > grfsize ) return false;

	GrfNode* last = NULL; // helper pointer to speed up inserts
	uint32_t remaining_files = filecount;

	switch( head.version )
	{
		case 0x102:
		case 0x103:
		{// old GRF files
			/// table: [ <size>.l <unknown>.w <name>.s <unknown>.l <entry>.17b ]* , strlen(name) == size - 6
			/// entry: [ <len>.l <len_aligned>.l <size>.l <flags>.b <pos>.l ].17b

			fseek(m_fd, table_pos + GRF_HEADER_SIZE, SEEK_SET);

			int dlen = grfsize - (table_pos + GRF_HEADER_SIZE);
			uint8_t* table = new uint8_t[dlen];
			std::auto_ptr<uint8_t> autorelease(table);
			if( fread(table, 1, dlen, m_fd) != dlen ) return false;

			uint8_t* pos = table;
			uint8_t* pos_max = table + dlen;
			while( pos < pos_max )
			{
				remaining_files--;
				size_t available_data = pos_max - pos;

				int fn_len = (*(uint32_t*)pos) - (4+2);
				if( fn_len > available_data ) return false;
				pos += 4; // size
				pos += 2; // unknown field

				const char* fn_name = (char*)pos;
				pos += fn_len; // name

				pos += 4; // unknown field

				struct grf_table_entry_data tmpentry;
				memcpy(&tmpentry, pos, sizeof(tmpentry));
				pos += sizeof(tmpentry);

				if( (tmpentry.flags & GRF_FLAG_FILE) == 0 )
					continue; // do not register "directory" entries

				uint8_t* encname = new uint8_t[DES_ALIGN(fn_len)];
				std::auto_ptr<uint8_t> autorelease(encname);
				memcpy(encname, fn_name, fn_len);
				grf_decode_filename(encname, fn_len);
				fn_name = (char*)encname;

				GrfEntry entry;
				entry.parent = this;
				entry.name.assign(fn_name, fn_len);
				entry.flags = tmpentry.flags;
				entry.size = tmpentry.size;
				entry.len = tmpentry.len-tmpentry.size-715;
				entry.len_aligned = tmpentry.len_aligned-37579;
				entry.pos = tmpentry.pos;

				// mandatory encryption, type is based on file extension
				entry.flags |= ( grf_file_is_mixcrypt(entry.name.c_str()) ) ? GRF_FLAG_MIXCRYPT : GRF_FLAG_DES;

				last = this->insert(entry, last); //FIXME: if this fails, everything will break
			}
		}
		break;
		case 0x200:
		{// new GRF files
			/// table: <compsize>.l <realsize>.l [ <name>.s <entry>.17b ]*
			/// entry: [ <compsize>.l <datasize>.l <size>.l <type>.b <offset>.l ].17b

			fseek(m_fd, table_pos + GRF_HEADER_SIZE, SEEK_SET);

			uint32_t table_zsize, table_size;
			if( fread(&table_zsize, 1, sizeof(table_zsize), m_fd) != sizeof(table_zsize) ) return false;
			if( fread(&table_size, 1, sizeof(table_size), m_fd) != sizeof(table_size) ) return false;
			if( table_pos + GRF_HEADER_SIZE + 8 + table_zsize > grfsize ) return false;

			uint8_t* table_comp = new uint8_t[table_zsize];
			uint8_t* table = new uint8_t[table_size];
			std::auto_ptr<uint8_t> autorelease1(table_comp);
			std::auto_ptr<uint8_t> autorelease2(table);
			if( fread(table_comp, 1, table_zsize, m_fd) != table_zsize ) return false;
			if( zlib_buffer_inflate(table, table_size, table_comp, table_zsize) != table_size ) return false;
			autorelease1.reset();

			uint8_t* pos = table;
			uint8_t* pos_max = table + table_size;
			while( pos < pos_max )
			{
				remaining_files--;
				size_t available_data = pos_max - pos;

				const char* fn_name = (char*)pos; 
				int fn_len = strnlen(fn_name, available_data);
				if( fn_len + sizeof(struct grf_table_entry_data) > available_data ) return false;
				pos += fn_len + 1;

				struct grf_table_entry_data tmpentry;
				memcpy(&tmpentry, pos, sizeof(tmpentry));
				pos += sizeof(tmpentry);

				if( (tmpentry.flags & GRF_FLAG_FILE) == 0 )
					continue; // do not register "directory" entries

				GrfEntry entry;
				entry.parent = this;
				entry.name.assign(fn_name, fn_len);
				entry.flags = tmpentry.flags;
				entry.size = tmpentry.size;
				entry.len = tmpentry.len;
				entry.len_aligned = tmpentry.len_aligned;
				entry.pos = tmpentry.pos;

				last = this->insert(entry, last); //FIXME: if this fails, everything will break
			}
		}
		break;
		default:
		{// shouldn't happen
			return false;
		}
		break;
	}

	/// [patch] compatibility fix for grfs broken by old grf library
//	if( remaining_files != 0 ) return false;

	// sort entries by offset
	this->GrfFile::prv_linkedlist_sort();

	return true;
}


bool GrfFile::prv_save(void)
{
	// write table
	//////////////
	uint32_t table_size = 0;
	for( GrfNode* node = m_first_node; node != NULL; node = node->next )
		table_size += node->name.size()+1 + sizeof(struct grf_table_entry_data);

	uint8_t* table;
	if( table_size == 0 )
	{
		table = new uint8_t[1];
		table[0] = 0;
	}
	else
	{
		table = new uint8_t[table_size];

		uint8_t* pos = table;
		for( GrfNode* node = m_first_node; node != NULL; node = node->next )
		{
			size_t namelen = node->name.size() + 1;
			memcpy(pos, node->name.c_str(), namelen);
			pos += namelen;

			grf_table_entry_data te;
			te.len = node->len;
			te.len_aligned = node->len_aligned;
			te.size = node->size;
			te.pos = node->pos;
			te.flags = node->flags;
			memcpy(pos, &te, sizeof(grf_table_entry_data));
			pos += sizeof(grf_table_entry_data);
		}
	}

	uint8_t* buf = new uint8_t[8 + zlib_compressbound(table_size)];
	std::auto_ptr<uint8_t> autorelease(buf);

	// Compress the table using zlib
	uint32_t table_zsize = zlib_buffer_deflate(buf + 8, zlib_compressbound(table_size), table, table_size);
	delete[] table;

	if( table_zsize == 0 )
		return false; // zlib error
	
	*(uint32_t*)(buf+0) = table_zsize; // compressed size
	*(uint32_t*)(buf+4) = table_size; // real size
	uint32_t table_len = 8 + table_zsize;

	// compute new position for the table
	GrfNode* gap = this->GrfFile::prv_find_free_space(table_len);
	uint32_t table_pos = ( gap == NULL ) ? 0 : gap->pos + gap->len_aligned;

	// write table to file
	fseek(m_fd, table_pos + GRF_HEADER_SIZE, SEEK_SET);
	if( fwrite(buf, 1, table_len, m_fd) != table_len )
		return false;

	// adjust file size
	uint32_t endpos = 0;
	if( gap == NULL ) // no file found in archive -> truncate at end of table
		endpos = table_pos + table_len;
	else
	if( gap->next == NULL ) // file was EOF -> truncate at end of table 
		endpos = table_pos + table_len;
	else
	{// some files are after us, truncate at end of last file
		for( GrfNode* node = m_first_node; node != NULL; node = node->next ) // TODO: Optimize this (as we know that files are sorted, optimization is possible)
		{
			uint32_t p = node->pos + node->len_aligned; // position of EOF
			if( endpos < p )
				endpos = p;
		}
	}

	ftruncate(fileno(m_fd), endpos + GRF_HEADER_SIZE);

	// write header
	///////////////
	struct grf_header file_header;
	strncpy(file_header.header_magic, GRF_HEADER_MAGIC, sizeof(file_header.header_magic));
	memcpy(file_header.header_key, GRF_KEY_CRYPT, sizeof(GRF_KEY_CRYPT));
	file_header.offset = table_pos;
	file_header.seed = 0;
	file_header.filecount = this->filecount() + file_header.seed + 7;
	file_header.version = GRF_FILE_OUTPUT_VERSION;

	fseek(m_fd, 0, SEEK_SET);
	if( fwrite(&file_header, 1, sizeof(file_header), m_fd) != sizeof(file_header) )
		return false;

	m_need_save = false;
	return true;
}


/// Find first node with at least 'size' free space after it.
/// If there are no nodes, returns NULL. If there is no room, returns last node.
GrfNode* GrfFile::prv_find_free_space(size_t size)
{
	if( m_first_node == NULL )
		return NULL; // special case : nothing in the grf

	if( m_first_node->pos - 0 >= size )
		return NULL; // special case : enough empty space at the beginning

	GrfNode* node;

	for( node = m_first_node; node->next != NULL; node = node->next ) 
	{
		uint32_t avail = node->next->pos - (node->pos + node->len_aligned);
		if( avail >= size )
			break; //found.
	}

	return node;
}


int grf_quicksort_sub(const void* left, const void* right)
{
	GrfNode* l = *(GrfNode**)left;
	GrfNode* r = *(GrfNode**)right;
	return ( l->pos < r->pos ) ? -1
	     : ( l->pos > r->pos ) ? +1
	     :                        0;
}


void GrfFile::prv_linkedlist_sort(void)
{
	size_t num = this->filecount();
	std::vector<GrfNode*> arr(num);
	this->GrfFile::get_file_list(&arr[0], arr.size());
	qsort(&arr[0], num, sizeof(GrfNode*), &grf_quicksort_sub);

	// restore order~
	m_first_node = arr[0];
	arr[0]->prev = NULL;
	for( int i = 1; i < num; ++i )
	{
		arr[i]->prev = arr[i-1];
		arr[i-1]->next = arr[i];
	}
	arr[num-1]->next = NULL;
}


GrfNode* GrfFile::prv_file_add(const std::string& name, uint8_t flags, uint32_t real_size, uint32_t zlen, uint32_t zlen_aligned, const uint8_t* zdata)
{
	m_need_save = true;

	// remove previous entry, if it exists
	GrfNode* old_node = this->find(name);
	if( old_node != NULL ) this->GrfFile::file_delete(old_node);

	// find a free spot in the grf archive
	GrfNode* prev = this->GrfFile::prv_find_free_space(zlen_aligned);
	uint32_t pos = ( prev == NULL ) ? 0 : prev->pos + prev->len_aligned;

	// write data to disk
	fseek(m_fd, pos + GRF_HEADER_SIZE, SEEK_SET);
	if( fwrite(zdata, 1, zlen_aligned, m_fd) != zlen_aligned )
		return NULL; // write failed

	// prepare new entry
	GrfEntry entry;
	entry.parent = this;
	entry.name = name;
	entry.flags = flags;
	entry.size = real_size;
	entry.len = zlen;
	entry.len_aligned = zlen_aligned;
	entry.pos = pos;

	// register new entry
	return this->insert(entry, prev);
}
