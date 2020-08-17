#pragma once
class N2Inter;


class N2InterMessageSystem
{
private:
	/* static  */ static N2InterMessageSystem*& m_cpSelf; //TODO
	/* this+ 0 */ //const N2InterMessageSystem::`vftable';
	/* this+ 4 */ RTL_CRITICAL_SECTION m_CS;
	/* this+28 */ bool m_bOK;
	typedef std::map<unsigned int,N2Inter*> IOBJCONTAINER;
	typedef std::map<unsigned int,N2Inter*>::iterator IOBJCONTAINERITOR;
	/* this+32 */ IOBJCONTAINER m_InterObjContainer;

public:
	bool isOK() const;
	bool Insert(const unsigned int in_hID, N2Inter* in_cpInter);
	void Remove(const unsigned int in_hID, N2Inter* in_cpInter);
	bool PostInterMessage(const unsigned int in_ToInter, const unsigned int in_FromInter, const int in_Msg, const int in_wParam, const int in_lParam);

public:
	static bool CreateInstance();
	static void DestoryInstance();

protected:
	N2InterMessageSystem();
	virtual ~N2InterMessageSystem();
};
