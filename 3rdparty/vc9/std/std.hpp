#pragma once


#define _MYSTD_BEGIN namespace mystd {
#define _MYSTD_END }
#define _MYSTD ::mystd::

#define _MYSTDEXT_BEGIN namespace mystdext {
#define _MYSTDEXT_END }
#define _MYSTDEXT ::mystdext::

// <yvals.h>
 #ifdef __cplusplus
_MYSTD_BEGIN
typedef bool _Bool;
_MYSTD_END

#undef _SCL_SECURE_VALIDATE
#define _SCL_SECURE_VALIDATE(cond)
#undef _SCL_SECURE_VALIDATE_RANGE
#define _SCL_SECURE_VALIDATE_RANGE(cond)
 #endif /* __cplusplus */

// <xstddef>
_MYSTD_BEGIN
 #ifndef _CONVERTIBLE_TO_TRUE
  #define _CONVERTIBLE_TO_TRUE	(&_STD _Bool_struct::_Member)
 #endif /* _CONVERTIBLE_TO_TRUE */

 #ifndef _SCL_CHECKED_ALGORITHM_WARN
  #define _SCL_CHECKED_ALGORITHM_WARN
 #endif /* _SCL_CHECKED_ALGORITHM_WARN */

 #ifndef _MESG
  #define _MESG(str)	str
 #endif /* _MESG */
 
 #ifndef _SECURE_VALIDATION_DEFAULT
  #define _SECURE_VALIDATION_DEFAULT false
 #endif

struct _Bool_struct
	{	// define member just for its address
	int _Member;
	};

typedef int _Bool_struct::* _Bool_type;
_MYSTD_END
