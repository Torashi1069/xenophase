#pragma once


namespace FixedSKcastingTMvarStuff
{


enum enumIDENTITY
{
	IDENTITY_NONE  = 0,
	IDENTITY_SKILL = 1,
	IDENTITY_EFST  = 2,
	IDENTITY_ITEM  = 3,
};


class CIdentity
{
public:
	CIdentity(const enumIDENTITY in_Kind, const int in_ID) : m_Kind(in_Kind), m_ID(in_ID) { }
	~CIdentity() { }
public:
	bool operator==(const CIdentity& in_Identity) const { return ( m_Kind == in_Identity.m_Kind && m_ID == in_Identity.m_ID ); }
	enumIDENTITY GetKind() const { return m_Kind; }
	int GetID() const { return m_ID; }
private:
	/* this+0 */ const enumIDENTITY m_Kind;
	/* this+4 */ const int m_ID;
};


class CApply
{
public:
	virtual bool operator()(const int in_SKID) const = 0;
public:
	CApply() { }
	virtual ~CApply() { }
private:
	CApply(const CApply&); // = delete;
	CApply& operator=(const CApply&); // = delete;
};


class CItem
{
public:
	CItem(const CIdentity in_Identity, const CApply* in_cpApply, const int in_Value) : m_Identity(in_Identity), m_cpApply(in_cpApply), m_Value(in_Value) { }
	virtual ~CItem() { }
private:
	CItem(const CItem&); // = delete;
	CItem& operator=(const CItem&); // = delete;
public:
	/* this+ 0 */ //const FixedSKcastingTMvarStuff::CItem::`vftable';
	/* this+ 4 */ const CIdentity m_Identity;
	/* this+12 */ const CApply* m_cpApply;
	/* this+16 */ int m_Value;
};


class CAmount
{
public:
	virtual int Get(const int in_SKID) const;
	virtual void Add(const std::tr1::shared_ptr<CItem>& in_ItemPtr);
	void Remove(const CIdentity& in_Identity);
	void Init();
protected:
	/* this+0 */ //const FixedSKcastingTMvarStuff::CAmount::`vftable';
	typedef std::vector<std::tr1::shared_ptr<CItem>> CONTAINER;
	/* this+4 */ CONTAINER m_Amounts;
public:
	CAmount();
	virtual ~CAmount();
private:
	CAmount(const CAmount&); // = delete;
	CAmount& operator=(const CAmount&); // = delete;
};


class CPermill : public CAmount
{
public:
	virtual void Add(const std::tr1::shared_ptr<CItem>& in_ItemPtr);
	virtual int Get(const int in_SKID) const;
public:
	CPermill();
	virtual ~CPermill();
private:
	CPermill(const CPermill&); // = delete;
	CPermill& operator=(const CPermill&); // = delete;
};


}; // namespace FixedSKcastingTMvarStuff


class CFixedSKcastingTMvar
{
public:
	void Init();
	void PropertyAmountAdd(std::tr1::shared_ptr<FixedSKcastingTMvarStuff::CItem>& ); //TODO
	void PropertyAmountRemove(const FixedSKcastingTMvarStuff::CIdentity& ); //TODO
	void PropertyPermillAdd(std::tr1::shared_ptr<FixedSKcastingTMvarStuff::CItem>& ); //TODO
	void PropertyPermillRemove(const FixedSKcastingTMvarStuff::CIdentity& ); //TODO
	int Get(const int in_Value, const int in_SKID);

private:
	/* this+ 0 */ FixedSKcastingTMvarStuff::CAmount m_Amount;
	/* this+20 */ FixedSKcastingTMvarStuff::CPermill m_Permill;

public:
	CFixedSKcastingTMvar();
	~CFixedSKcastingTMvar();
};
