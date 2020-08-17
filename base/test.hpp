#pragma once
#include <dia/CDia.hpp>
#include <assert.h> // assert()
#include <stddef.h> // offsetof()

#define GET_SIZE(type)           findClass(L#type).size()
#define GET_OFFSET(type, member) findClass(L#type).findMember(L#member).offset()
#define GET_VTABLE(type, method) findClass(L#type).findMethod(L#method).voffset()

#define VERIFY_SIZE(type)           assert( dia.GET_SIZE(type) == sizeof(type) )
#define VERIFY_OFFSET(type, member) assert( dia.GET_OFFSET(type, member) == offsetof(type, member) )
#define VERIFY_VTABLE(type, method) assert( dia.GET_VTABLE(type, method) == offsetof(type::vtable_t, method) )

#define COMPARE_SIZE(type)           assert( dia.GET_SIZE(type) == dia2.GET_SIZE(type) )
#define COMPARE_OFFSET(type, member) assert( dia.GET_OFFSET(type, member) == dia2.GET_OFFSET(type, member) )
#define COMPARE_VTABLE(type, method) assert( dia.GET_VTABLE(type, member) == dia2.GET_VTABLE(type, method) )
