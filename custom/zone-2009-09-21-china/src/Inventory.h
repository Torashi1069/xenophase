#pragma once
struct Request;


class CInventory
{
	struct vtable_t // const CInventory::`vftable'
	{
		void* (CInventory::* scalar_deleting_destructor)(unsigned int flags);
		void (CInventory::* Delete)(Request* request);
		void (CInventory::* Load)(Request* request);
		void (CInventory::* Save)(Request* request);
		int (CInventory::* OnRequest)(Request* request);
	};

	/* this+0 */ public: //const CInventory::`vftable';

	public: CInventory::CInventory(void);
	public: virtual CInventory::~CInventory(void);
	public: virtual void CInventory::Delete(Request* request);
	public: virtual void CInventory::Load(Request* request);
	public: virtual void CInventory::Save(Request* request);
	public: virtual int  CInventory::OnRequest(Request* request);

private:
	static hook_method<void (CInventory::*)(Request* request)> CInventory::_Delete;
	static hook_method<void (CInventory::*)(Request* request)> CInventory::_Load;
	static hook_method<void (CInventory::*)(Request* request)> CInventory::_Save;
	static hook_method<int  (CInventory::*)(Request* request)> CInventory::_OnRequest;
};
