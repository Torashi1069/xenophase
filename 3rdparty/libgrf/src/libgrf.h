/// libgrf public header file
#pragma once
#include <platform/stdc.h> // size_t, uint*_t
#define GRFEXPORT extern

#ifdef __cplusplus
extern "C" {
#endif

/// opaque types
struct grf_handle_;
struct grf_node_;
typedef struct grf_handle_* grf_handle;
typedef struct grf_node_* grf_node;

/// grf entry flags (bitfield)
/// @see grf_file_get_storage_flags()
#define GRF_FLAG_FILE     1
#define GRF_FLAG_MIXCRYPT 2
#define GRF_FLAG_DES      4

/// grf repack options
/// @see grf_repack()
#define GRF_REPACK_FAST       1 // shift contents to remove any unused space
#define GRF_REPACK_DECRYPT    2 // also decrypt any encrypted files
#define GRF_REPACK_RECOMPRESS 3 // also recompress everything (slow)

/// *****************************************************************************
/// *************************** BASE FUNCTIONS **********************************
/// *****************************************************************************

/// Creates a new GRF.
GRFEXPORT grf_handle grf_new(const char* filename);

/// Loads an existing GRF.
GRFEXPORT grf_handle grf_load(const char* filename);

/// Writes the GRF's files table to disk.
GRFEXPORT bool grf_save(grf_handle handle);

/// Frees a GRF and all the memory used by it, and closes the GRF's fd.
/// If any change was made to the GRF, a best-effort grf_save() is also called.
GRFEXPORT void grf_free(grf_handle handle);

/// Sets the compression level used on this GRF. (IGNORED, libgrf always uses best compression).
GRFEXPORT void grf_set_compression_level(grf_handle handle, int level);

/// Returns the number of files currently in the GRF.
GRFEXPORT uint32_t grf_filecount(grf_handle handle);

/// Returns the amount of unused space (in bytes) that could be recovered by a repack operation.
GRFEXPORT uint32_t grf_wasted_space(grf_handle handle);

/// *****************************************************************************
/// **************************** FILES FUNCTIONS ********************************
/// *****************************************************************************

/// Add a file to the specified GRF and return its handle.
GRFEXPORT grf_node grf_file_add(grf_handle handle, const char* name, void* buffer, size_t size);

/// Returns a node handle to the specified file inside the GRF.
/// If the function fails, NULL is returned.
GRFEXPORT grf_node grf_get_file(grf_handle handle, const char* filename);

/// Returns the full filename of a file.
GRFEXPORT const char* grf_file_get_filename(grf_node node);

/// Returns only the filename (no path info)
GRFEXPORT const char* grf_file_get_basename(grf_node node);

/// Returns the real size of the file.
GRFEXPORT uint32_t grf_file_get_size(grf_node node);

/// Returns the compressed size of the file.
GRFEXPORT uint32_t grf_file_get_zsize(grf_node node);

/// Returns the position of the file in the archive.
GRFEXPORT uint32_t grf_file_get_storage_pos(grf_node node);

/// Returns the size of the file in the archive (compressed size + padding).
GRFEXPORT uint32_t grf_file_get_storage_size(grf_node node);

/// Returns the archive flags of the file.
/// Test if the first bit is set to know if a node is a file, or not.
GRFEXPORT uint32_t grf_file_get_storage_flags(grf_node node);

/// Extracts the file to the provided buffer and returns the number of bytes successfully extracted.
/// Assumes that at least grf_file_get_size() bytes can be safely written into ptr.
GRFEXPORT uint32_t grf_file_get_contents(grf_node node, void* ptr);

/// Reads the compressed contents of the file to the provided buffer and returns the number of bytes successfully extracted.
/// Assumes that at least grf_file_get_zsize() bytes can be safely written into ptr.
GRFEXPORT uint32_t grf_file_get_zcontents(grf_node node, void* ptr);

/// Rename the given file to new_name.
/// You must provide the full path, eg: "data\file.txt".
/// Renaming to an already existing file will delete it.
/// Renaming to a directory name will give unexpected results.
GRFEXPORT bool grf_file_rename(grf_node node, const char* new_name);

/// Removes a file from the GRF (marking its data as free space).
GRFEXPORT bool grf_file_delete(grf_node node);

/// Generates an adler32 hash of the specified file.
/// @param hack if true, try to extract hash directly from zlib stream on disk
GRFEXPORT uint32_t grf_file_get_hash(grf_node node, bool hack);

/// *****************************************************************************
/// ************************** FILE LISTING FUNCTIONS ***************************
/// *****************************************************************************

/// Allocates a null-terminated array of nodes contained in the GRF. Use free() to release. The order of nodes may be different on each call.
GRFEXPORT grf_node* grf_get_file_list(grf_handle handle);

/// Returns the first file's node pointer in the GRF, or NULL if no files were found.
GRFEXPORT grf_node grf_get_file_first(grf_handle handle);

/// Returns next file, or NULL if this was the last file.
GRFEXPORT grf_node grf_get_file_next(grf_node node);

/// Returns previous file, or NULL if this was the first file.
GRFEXPORT grf_node grf_get_file_prev(grf_node node);

/// *****************************************************************************
/// *************************** GRF MASS OPERATIONS *****************************
/// *****************************************************************************

/// Repack given GRF, to save wasted_bytes and maybe more (if using the recompress option).
/// Valid options :
/// - GRF_REPACK_FAST (just move files)
/// - GRF_REPACK_DECRYPT (move files, and decrypt files if any was found encrypted)
/// - GRF_REPACK_RECOMPRESS (recompress all files, and replace if newly compressed file is smaller than the one previously stored)
GRFEXPORT bool grf_repack(grf_handle handle, uint8_t options);

/// Copy files from "src" grf_handle to "dest" grf_handle.
GRFEXPORT bool grf_merge(grf_handle dest, grf_handle src);

/// *****************************************************************************
/// **************************** CHARSET FUNCTIONS ******************************
/// *****************************************************************************

/// Converts EUC-KR text as encoded in GRFs to UTF-8.
/// The first form uses a static buffer (4096 bytes), the second is re-entrant.
/// If a symbol cannot be represented in the output codepage, returns NULL.
GRFEXPORT char* euc_kr_to_utf8(const char* text);
GRFEXPORT char* euc_kr_to_utf8_r(const char* text, uint8_t* ptr);

/// Converts UTF-8 text to EUC-KR as used to encode filenames in GRFs.
/// The first form uses a static buffer (4096 bytes), the second is re-entrant.
/// If a symbol cannot be represented in the output codepage, returns NULL.
GRFEXPORT char* utf8_to_euc_kr(const char* text);
GRFEXPORT char* utf8_to_euc_kr_r(const char* text, uint8_t* ptr);

#ifdef __cplusplus
}
#endif
