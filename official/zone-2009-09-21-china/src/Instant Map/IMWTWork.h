#pragma once


class CIMWTWork
{
public:
	struct vtable_t
	{
		void (CIMWTWork::* Run)(void);
		void* (CIMWTWork::* vector_deleting_destructor)(unsigned int);
	};

	enum enumTYPE
	{
		TYPE_LOADMAP = 0x0,
	};

	/* this+0x0 */ //const CIMWTWork::`vftable'
	/* this+0x4 */ private: const enum CIMWTWork::enumTYPE m_Type;

	private: virtual void CIMWTWork::Run(void);
	public: const enum CIMWTWork::enumTYPE CIMWTWork::GetType(void);
	public: CIMWTWork::CIMWTWork(const enum CIMWTWork::enumTYPE in_Type);
	public: virtual CIMWTWork::~CIMWTWork(void);

private:
	static hook_method<void (CIMWTWork::*)(void)> CIMWTWork::_Run;
	static hook_method<const enum CIMWTWork::enumTYPE (CIMWTWork::*)(void)> CIMWTWork::_GetType;
};
