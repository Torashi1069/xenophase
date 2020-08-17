#pragma once


template<typename K1, typename K2, typename D> class N2DualKeyMap
{
private:
	class CObject
	{
	public:
		/* this+0 */ //const N2DualKeyMap<K1,K2,D>::CObject::`vftable';
		/* this+4 */ D m_Object;
		/* this+? */ K2 m_SecondaryKey;

	public:
		CObject(D in_Object, K2 in_SecondaryKey) : m_Object(in_Object), m_SecondaryKey(in_SecondaryKey) { }
		virtual ~CObject() { }
	};

	typedef typename std::map<K1,CObject> DATAMAP;
	typedef typename std::map<K1,CObject>::iterator DATAMAP_ITER;
	typedef typename std::map<K2,K1> INDEXMAP;
	typedef typename std::map<K2,K1>::iterator INDEXMAP_ITER;

private:
	/* this+ 0 */ //const N2DualKeyMap<K1,K2,D>::`vftable';
	/* this+ 4 */ DATAMAP m_DataMap;
	/* this+36 */ INDEXMAP m_IndexMap;

public:
	class Iterator
	{
	private:
		/* this+0 */ //const N2DualKeyMap<K1,K2,D>::Iterator::`vftable';
		/* this+4 */ DATAMAP_ITER m_Iter;

	public:
		bool operator!=(const Iterator& in_Rhs) { return ( m_Iter != in_Rhs.m_Iter ); }
		bool operator==(const Iterator& in_Rhs) { return ( m_Iter == in_Rhs.m_Iter ); }
		void operator++() { ++m_Iter; }
		D& GetObj() { return m_Iter->second.m_Object; }

	public:
		Iterator(DATAMAP_ITER& in_Iter) : m_Iter(in_Iter) { }
		virtual ~Iterator() { }

		friend class N2DualKeyMap;
	};

public:
	Iterator begin()
	{
		return m_DataMap.begin();
	}

	Iterator end()
	{
		return m_DataMap.end();
	}

	Iterator findPrimaryKey(const K1 in_PrimaryKey)
	{
		return m_DataMap.find(in_PrimaryKey);
	}

	Iterator findSecondaryKey(const K2 in_Key)
	{
		INDEXMAP_ITER iter = m_IndexMap.find(in_Key);
		if( iter == m_IndexMap.end() )
			return m_DataMap.end();

		return this->N2DualKeyMap::findPrimaryKey(iter->second);
	}

	Iterator erase(Iterator in_Iter)
	{
		INDEXMAP_ITER IndexIter = m_IndexMap.find(in_Iter.m_Iter->second.m_SecondaryKey);
		if( IndexIter != m_IndexMap.end() )
			m_IndexMap.erase(IndexIter);
		return m_DataMap.erase(in_Iter.m_Iter);
	}

	bool insert(K1 in_PrimaryKey, K2 in_SecondaryKey, D in_Object)
	{
		std::pair<DATAMAP_ITER,bool> priamryRet = m_DataMap.insert(std::make_pair(in_PrimaryKey, CObject(in_Object, in_SecondaryKey)));
		if( !priamryRet.second )
			return false;

		std::pair<INDEXMAP_ITER,bool> secondaryRet = m_IndexMap.insert(std::make_pair(in_SecondaryKey, in_PrimaryKey));
		if( !secondaryRet.second )
		{
			m_DataMap.erase(priamryRet.first);
			return false;
		}

		return true;
	}

	bool empty() const
	{
		return ( m_DataMap.size() == 0 );
	}

	int size() const
	{
		return m_DataMap.size();
	}

	void clear()
	{
		m_DataMap.clear();
		m_IndexMap.clear();
	}

public:
	N2DualKeyMap() { }
	virtual ~N2DualKeyMap() { }
};
