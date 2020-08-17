/// Which allocator to use for new/delete.
static enum { OURS, THEIRS } allocator = OURS;


/// Global allocation operators.
static void* (* g_new)(size_t) = NULL;
static void (* g_delete)(void*) = NULL;


/// Global new/delete operator replacements.
void* operator new  (size_t size) { return( allocator != OURS ) ? g_new(size) : malloc(size); }
void* operator new[](size_t size) { return operator new(size); }
void operator delete  (void* p) { ( allocator != OURS ) ? g_delete(p) : free(p); }
void operator delete[](void* p) { operator delete(p); }


static int (* g_cinit)(int) = NULL;
int hook_cinit(int a)
{
	allocator = THEIRS;
	return g_cinit(a);
}


/// Hooks memory allocation. The only thing you need to call to make everything work.
/// @param pfnNew Pointer to the allocation function to use.
/// @param pfnDelete Pointer to the deallocation function to use.
/// @param pfnInit Pointer to the function whose use 
void Hook_Alloc(void* pfnNew, void* pfnDelete, void* pfnInit)
{
	assert( pfnNew != NULL );
	assert( pfnDelete != NULL );

	g_new = (void* (*)(size_t))pfnNew;
	g_delete = (void (*)(void*))pfnDelete;

	if( pfnInit != NULL )
	{
		HookDB::DB().Hook("_cinit", pfnInit, &hook_cinit);
		g_cinit = VTOF<int(*)(int)>(HookDB::DB().Get("_cinit")->original());
	}
	else
	{// switch immediately
		allocator = THEIRS;
	}
}


/// The atexit() handlers are registered in reverse order.
/// Thus the order of atexit processing is:
/// - local static objects created at runtime (from last to first)
/// - global static objects created at startup (from last to first)
///
/// We craft our class so that its own handler is inserted as the last global static object entry.
/// This ensures that its destructor runs right after all runtime objects have been dealt with,
/// and right before any local static objects are processed.
///
/// Microsoft's Visual Studio seems to process files in alphabetical order.
/// Thus we name our file so that it gets compiled last. Make sure this is the case!
class ZLast
{
public:
	~ZLast()
	{
		allocator = OURS;
	}
};
static ZLast zlast;
