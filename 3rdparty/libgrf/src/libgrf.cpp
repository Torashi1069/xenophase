#include "convert.h" // uhc_to_utf8(), utf8_to_uhc()
#include "grffile.h"
#include "libgrf.h"


GRFEXPORT grf_handle grf_new(const char* filename)
{
	GrfFile* grf = new GrfFile();
	if( grf == NULL )
	{// allocation failed
		return NULL;
	}

	if( !grf->create(filename) )
	{// creation failed
		delete grf;
		return NULL;
	}

	return reinterpret_cast<grf_handle>(grf);
}


GRFEXPORT grf_handle grf_load(const char* filename)
{
	GrfFile* grf = new GrfFile();
	if( grf == NULL )
	{// allocation failed
		return NULL;
	}

	if( !grf->load(filename) )
	{// loading failed
		delete grf;
		return NULL;
	}

	return reinterpret_cast<grf_handle>(grf);
}


GRFEXPORT bool grf_save(grf_handle handler)
{
	GrfFile* grf = reinterpret_cast<GrfFile*>(handler);
	return grf->save();
}


GRFEXPORT void grf_free(grf_handle handler)
{
	GrfFile* grf = reinterpret_cast<GrfFile*>(handler);
	delete grf;
}


GRFEXPORT void grf_set_compression_level(grf_handle handler, int level)
{
	return; // do nothing
}


GRFEXPORT uint32_t grf_filecount(grf_handle handler)
{
	GrfFile* grf = reinterpret_cast<GrfFile*>(handler);
	return grf->filecount();
}


GRFEXPORT uint32_t grf_wasted_space(grf_handle handler)
{
	GrfFile* grf = reinterpret_cast<GrfFile*>(handler);
	return grf->wasted_space();
}


GRFEXPORT grf_node grf_file_add(grf_handle handler, const char* filename, void* ptr, size_t size)
{
	GrfFile* grf = reinterpret_cast<GrfFile*>(handler);
	GrfNode* node = grf->file_add(filename, ptr, size);
	return reinterpret_cast<grf_node>(node);
}


GRFEXPORT grf_node grf_get_file(grf_handle handler, const char* filename)
{
	GrfFile* grf = reinterpret_cast<GrfFile*>(handler);
	GrfNode* node = grf->get_file(filename);
	return reinterpret_cast<grf_node>(node);
}


GRFEXPORT const char* grf_file_get_filename(grf_node handler)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);
	return node->get_name().c_str();
}


/// Convenience function.
GRFEXPORT const char* grf_file_get_basename(grf_node handler)
{
	const char* fname = grf_file_get_filename(handler);
	const char* p = NULL;
	if( p == NULL )
		p = strrchr(fname, '/');
	if( p == NULL )
		p = strrchr(fname, '\\');
	if( p == NULL )
		p = fname;

	return p;
}


GRFEXPORT uint32_t grf_file_get_size(grf_node handler)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);
	return node->get_size();
}


GRFEXPORT uint32_t grf_file_get_zsize(grf_node handler)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);
	return node->get_zsize();
}


GRFEXPORT uint32_t grf_file_get_storage_pos(grf_node handler)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);
	return node->storage_pos();
}


GRFEXPORT uint32_t grf_file_get_storage_size(grf_node handler)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);
	return node->storage_size();
}


GRFEXPORT uint32_t grf_file_get_storage_flags(grf_node handler)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);
	return node->storage_flags();
}


GRFEXPORT uint32_t grf_file_get_contents(grf_node handler, void* ptr)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);

	std::vector<uint8_t> buf;
	if( !node->grf()->file_get_contents(node, buf) )
		return 0;

	memcpy(ptr, &buf.front(), buf.size());
	return buf.size();
}


GRFEXPORT uint32_t grf_file_get_zcontents(grf_node handler, void* ptr)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);

	std::vector<uint8_t> buf;
	if( !node->grf()->file_get_zcontents(node, buf) )
		return 0;

	memcpy(ptr, &buf.front(), buf.size());
	return buf.size();
}


GRFEXPORT bool grf_file_rename(grf_node handler, const char* newname)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);
	return node->grf()->file_rename(node, newname);
}


GRFEXPORT bool grf_file_delete(grf_node handler)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);
	return node->grf()->file_delete(node);
}


GRFEXPORT uint32_t grf_file_get_hash(grf_node handler, bool hack)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);
	return node->grf()->file_get_hash(node, hack);
}


GRFEXPORT grf_node* grf_get_file_list(grf_handle handler)
{
	GrfFile* grf = reinterpret_cast<GrfFile*>(handler);

	size_t num = grf->filecount() + 1; // null-terminated
	GrfNode** arr = (GrfNode**)malloc(num * sizeof(GrfNode*));
	grf->get_file_list(arr, num);

	return reinterpret_cast<grf_node*>(arr);
}


GRFEXPORT grf_node grf_get_file_first(grf_handle handler)
{
	GrfFile* grf = reinterpret_cast<GrfFile*>(handler);
	GrfNode* first = grf->get_file_first();
	return reinterpret_cast<grf_node>(first);
}


GRFEXPORT grf_node grf_get_file_next(grf_node handler)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);
	GrfNode* next = node->get_next();
	return reinterpret_cast<grf_node>(next);
}


GRFEXPORT grf_node grf_get_file_prev(grf_node handler)
{
	GrfNode* node = reinterpret_cast<GrfNode*>(handler);
	GrfNode* prev = node->get_prev();
	return reinterpret_cast<grf_node>(prev);
}


GRFEXPORT bool grf_repack(grf_handle handler, uint8_t repack_type)
{
	GrfFile* grf = reinterpret_cast<GrfFile*>(handler);
	return grf->repack(repack_type);
}


GRFEXPORT bool grf_merge(grf_handle dest, grf_handle src)
{
	GrfFile* grfDst = reinterpret_cast<GrfFile*>(dest);
	GrfFile* grfSrc = reinterpret_cast<GrfFile*>(src);
	return grfDst->merge(grfSrc);
}


GRFEXPORT char* euc_kr_to_utf8(const char* text)
{
	static char outbuf[4096]; // should be enough
	size_t outsize = sizeof(outbuf);
	return ( convert_uhc_to_utf8(text, strlen(text)+1, outbuf, outsize) ) ? outbuf : NULL;
}


GRFEXPORT char* euc_kr_to_utf8_r(const char* text, uint8_t* ptr)
{
	char* outbuf = (char*)ptr;
	size_t outsize = 4096; // real value not available
	return ( convert_uhc_to_utf8(text, strlen(text)+1, outbuf, outsize) ) ? outbuf : NULL;
}


GRFEXPORT char* utf8_to_euc_kr(const char* text)
{
	static char outbuf[4096]; // should be enough
	size_t outsize = sizeof(outbuf);
	return ( convert_utf8_to_uhc(text, strlen(text)+1, outbuf, outsize) ) ? outbuf : NULL;
}


GRFEXPORT char* utf8_to_euc_kr_r(const char* text, uint8_t* ptr)
{
	char* outbuf = (char*)ptr;
	size_t outsize = 4096; // real value not available
	return ( convert_utf8_to_uhc(text, strlen(text)+1, outbuf, outsize) ) ? outbuf : NULL;
}
