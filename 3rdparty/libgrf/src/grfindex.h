#pragma once
#include "hash_tables.h" // HashTable<>
#include <string> // std::string
#include <platform/stdc.h> // size_t, uint*_t
class GrfEntry;
class GrfNode;
class GrfFile;


class GrfEntry
{
public:
	GrfFile* parent; // grf container
	std::string name;
	uint8_t flags;
	uint32_t size; // real size
	uint32_t len; // compressed size
	uint32_t len_aligned; // storage size in grf
	uint32_t pos; // offset in grf

public:
	GrfFile* grf() const { return parent; }
	const std::string& get_name() const { return name; }
	uint32_t get_size() const { return size; }
	uint32_t get_zsize() const { return len; }
	uint8_t storage_flags() const { return flags; }
	uint32_t storage_size() const { return len_aligned; }
	uint32_t storage_pos() const { return pos; }
};


class GrfNode : public GrfEntry
{
public:
	GrfNode* prev;
	GrfNode* next;

public:
	GrfNode(const GrfEntry& entry) : prev(NULL), next(NULL), GrfEntry(entry) { }
	GrfNode* get_prev() const { return prev; }
	GrfNode* get_next() const { return next; }
};


class GrfIndex
{
public:
	GrfIndex();
	~GrfIndex();
	size_t size() const;
	GrfNode* find(const std::string& name);
	GrfNode* insert(GrfEntry entry, GrfNode* anchor);
	bool insert(GrfNode* node, GrfNode* anchor);
	bool rename(GrfNode* node, const std::string& newname);
	void erase(GrfNode* node);

private:
	void attach(GrfNode* node, GrfNode* anchor);
	void detach(GrfNode* node);

public:
	GrfNode* m_first_node; // linked list
	HashTable<GrfNode> m_fast_table;
	size_t m_count; // number of nodes
};
