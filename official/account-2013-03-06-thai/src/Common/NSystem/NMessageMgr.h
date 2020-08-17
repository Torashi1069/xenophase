#pragma once
class NInter;


class NMessageMgr
{
public:
	bool isOK() const;
	bool Insert(const unsigned int in_ID, NInter* in_Obj);
	void Remove(const unsigned int in_ID, NInter* in_Obj);
	bool Post(const unsigned int in_ID, const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static NMessageMgr* GetObj();

private:
	NMessageMgr();
	virtual ~NMessageMgr();

private:
	/* this+ 0 */ //const NMessageMgr::`vftable';
	/* this+ 4 */ RTL_CRITICAL_SECTION m_CS;
	/* this+28 */ bool m_bOK;
	/* this+32 */ std::map<unsigned int,NInter*> m_ObjContainer;
	/* static  */ static NMessageMgr* m_cpSelf;
};
