#pragma once
#include "grfindex.h" // class GrfIndex
#include <string> // std::string
#include <vector> // std::vector<>
#include <platform/stdc.h> // size_t, uint*_t
#include <platform/disk.h> // FILE


class GrfFile : public GrfIndex
{
private:
	FILE* m_fd;
	bool m_need_save;

public:
	GrfFile(void);
	~GrfFile(void);
	bool create(const char* filename);
	bool load(const char* filename);
	bool save(void);
	bool merge(const GrfFile* src);
	bool repack(uint8_t repack_type);

	GrfNode* get_file(const char* filename);
	GrfNode* get_file_first(void);
	uint32_t get_file_list(GrfNode** arr, size_t num);
	uint32_t filecount(void) const;
	uint32_t wasted_space(void) const;

	GrfNode* file_add(const char* filename, const void* ptr, size_t size);
	bool file_rename(GrfNode* node, const char* newname);
	bool file_delete(GrfNode* node);
	bool file_get_contents(const GrfNode* node, std::vector<uint8_t>& outbuf) const;
	bool file_get_zcontents(const GrfNode* node, std::vector<uint8_t>& outbuf) const;
	uint32_t file_get_hash(const GrfNode* node, bool hack = false) const;

private:
	bool prv_load(void);
	bool prv_save(void);
	GrfNode* prv_find_free_space(size_t size);
	void prv_linkedlist_sort(void);
	GrfNode* prv_file_add(const std::string& name, uint8_t flags, uint32_t real_size, uint32_t zlen, uint32_t zlen_aligned, const uint8_t* zdata);
};
