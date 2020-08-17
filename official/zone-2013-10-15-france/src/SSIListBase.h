#pragma once
#include "Struct.h" // EQUIPSLOTINFO
#include "Common/Packet.h" // ResultItemInfo


struct SSIListInfo
{
	/* this+ 0 */ unsigned int SSI_ID;
	/* this+ 4 */ unsigned int AID;
	/* this+ 8 */ std::string StoreName;
	/* this+36 */ short x;
	/* this+38 */ short y;
	/* this+40 */ int price;
	/* this+44 */ unsigned short ITID;
	/* this+46 */ unsigned char ItemType;
	/* this+48 */ unsigned short count;
	/* this+50 */ unsigned char refiningLevel;
	/* this+51 */ EQUIPSLOTINFO CardSlot;

	operator ResultItemInfo()
	{
		ResultItemInfo result;

		result.SSI_ID = this->SSI_ID;
		result.AID = this->AID;
		result.price = this->price;
		result.CardSlot.info[0] = this->CardSlot.info[0];
		result.CardSlot.info[1] = this->CardSlot.info[1];
		result.CardSlot.info[2] = this->CardSlot.info[2];
		result.CardSlot.info[3] = this->CardSlot.info[3];
		result.ITID = this->ITID;
		result.ItemType = this->ItemType;
		result.count = this->count;
		result.refiningLevel = this->refiningLevel;
		memcpy_s(result.StoreName, sizeof(result.StoreName), this->StoreName.c_str(), this->StoreName.size());

		return result;
	}

	SSIListInfo()
	{
		this->SSIListInfo::Clear();
	}

	void Clear()
	{
		this->SSI_ID = 0;
		this->AID = 0;
		this->StoreName.clear();
		this->x = 0;
		this->y = 0;
		this->price = 0;
		this->ITID = 0;
		this->ItemType = 0;
		this->count = 0;
		this->refiningLevel = 0;
		this->CardSlot.info[0] = 0;
		this->CardSlot.info[1] = 0;
		this->CardSlot.info[2] = 0;
		this->CardSlot.info[3] = 0;
	}
};


struct AllocSSIListInfoData
{
	AllocSSIListInfoData();
	virtual ~AllocSSIListInfoData();

	SSIListInfo* operator->(); //TODO
	bool operator==(SSIListInfo* ); //TODO
	bool operator==(const SSIListInfo* ); //TODO

	operator const SSIListInfo*(); //TODO
	operator const SSIListInfo(); //TODO
	operator SSIListInfo*(); //TODO
	operator SSIListInfo(); //TODO

	/* this+0 */ //const AllocSSIListInfoData::`vftable';
	/* this+4 */ SSIListInfo* m_pData;
};


template<typename T> class CMemoryAllocator
{
public:
	CMemoryAllocator();
	~CMemoryAllocator();

public:
	T* Alloc();
	void Free(T* t);
	int GetFreeSize(); //TODO
	int GetAllocSize(); //TODO
	void AllFree();

private:
	/* this+0 */ //const CMemoryAllocator<T>::`vftable';
	/* this+4 */ std::map<T*,bool> m_list;
};



template<typename T> CMemoryAllocator<T>::CMemoryAllocator()
{
}


template<typename T> CMemoryAllocator<T>::~CMemoryAllocator()
{
	this->CMemoryAllocator<T>::AllFree();
}


template<typename T> void CMemoryAllocator<T>::AllFree()
{
	for( std::map<T*,bool>::iterator iter_list = m_list.begin(); iter_list != m_list.end(); ++iter_list )
		if( iter_list->first )
			delete iter_list->second;

	m_list.clear();
}


template<typename T> T* CMemoryAllocator<T>::Alloc()
{
	for( std::map<T*,bool>::iterator iter_list = m_list.begin(); iter_list != m_list.end(); ++iter_list )
	{
		if( !iter_list->second )
		{
			iter_list->second = true;
			return iter_list->first; // use existing node.
		}
	}

	T* p = new(std::nothrow) T;
	if( p == NULL )
		return NULL;

	m_list[p] = true;
	return p;
}


template<typename T> void CMemoryAllocator<T>::Free(T* t)
{
	if( t == NULL )
		return;

	std::map<T*,bool>::iterator iter_list = m_list.find(t);
	if( iter_list == m_list.end() )
		return;

	iter_list->second = false;
}
