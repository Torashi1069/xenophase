#pragma once
#include "std/map"


template<typename K1, typename K2, typename D> class N2DualKeyMap
{
public:
	class CObject
	{
		/* this+0 */ public: //CObject::`vftable';
		/* this+4 */ public: D m_Object;
		/* this+8 */ public: unsigned int m_SecondaryKey;

		public: CObject(D in_Object, unsigned int in_SecondaryKey) : m_Object(in_Object), m_SecondaryKey(in_SecondaryKey) {} // line 17
		public: virtual ~CObject(void) {  }; // line 18
	};

	class Iterator
	{
		/* this+0 */ public: //Iterator::`vftable';
		/* this+4 */ private: typename mystd::map<K1,CObject>::iterator m_Iter;

		public: bool operator!=(const Iterator& in_Rhs) { return ( m_Iter != in_Rhs.m_Iter ); } // line 33
		public: bool operator==(const Iterator& in_Rhs) { return ( m_Iter == in_Rhs.m_Iter ); } // line 34
		public: void operator++(void) { ++m_Iter; } // line 35
		public: D& GetObj(void) { return m_Iter->second.m_Object; } // line 36

		public: Iterator(typename mystd::map<K1,CObject>::iterator& in_Iter) { m_Iter = in_Iter; } // line 38
		public: virtual ~Iterator(void) { } // line 39
	};

	/* this+ 0 */ public: //const N2DualKeyMap<K1,K2,D>::`vftable';
	/* this+ 4 */ private: mystd::map<K1,CObject> m_DataMap;
	/* this+16 */ private: mystd::map<K2,K1> m_IndexMap; 

	typedef typename mystd::map<K1,CObject>::const_iterator DATAMAP_ITER;
	typedef typename mystd::map<K2,K1>::const_iterator INDEXMAP_ITER;

	public: Iterator begin(void) { return m_DataMap.begin(); } // line 43
	public: Iterator end(void) { return m_DataMap.end(); } // line 44
	public: Iterator findPrimaryKey(const K1 in_PrimaryKey) { return m_DataMap.find(in_PrimaryKey); } // line 45
	public: Iterator findSecondaryKey(const K2 in_Key) // line 46-50
	{
		INDEXMAP_ITER it = m_IndexMap.find(in_Key);
		if( it == m_IndexMap.end() )
			return m_DataMap.end();
		return m_DataMap.find(it->second);
	}
	public: Iterator erase(Iterator in_Iter) // line 51-56
	{
		INDEXMAP_ITER it = m_IndexMap.find(in_Iter.GetObj().m_SecondaryKey);
		if( it != m_IndexMap.end() )
			m_IndexMap.erase(it);
		return m_DataMap.erase(in_Iter.m_Iter);
	}
	public: bool insert(K1 in_PrimaryKey, K2 in_SecondaryKey, D in_Object) // line 58-67
	{
		mystd::pair<mystd::map<K1,CObject>::iterator,bool> priamryRet = m_DataMap.insert(mystd::pair<const K1,CObject>(in_PrimaryKey, CObject(in_Object, in_SecondaryKey)));
		if ( !priamryRet.second )
			return false;

		mystd::pair<mystd::map<K2,K1>::iterator,bool> secondaryRet = m_IndexMap.insert(mystd::pair<const K2,K1>(in_SecondaryKey, in_PrimaryKey));
		if( !secondaryRet.second )
		{
			m_DataMap.erase(priamryRet.first);
			return false;
		}

		return true;
	}
	public: bool empty(void) { return m_DataMap.empty(); } // line 68
	public: int size(void) { return m_DataMap.size(); } // line 69
	public: void clear(void) { m_DataMap.clear(); m_IndexMap.clear(); } // line 70

	public: N2DualKeyMap<K1,K2,D>(void) { } // line 73
	public: virtual ~N2DualKeyMap<K1,K2,D>(void) { } // line 74
};
