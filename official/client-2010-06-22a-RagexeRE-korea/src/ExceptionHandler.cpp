#include "ExceptionHandler.h"


hook_func<LONG (__stdcall *)(struct _EXCEPTION_POINTERS* pExceptionInfo)> _ExceptionFilter("ExceptionFilter");
LONG __stdcall ExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionInfo)
{
	return (_ExceptionFilter)(pExceptionInfo);
}
