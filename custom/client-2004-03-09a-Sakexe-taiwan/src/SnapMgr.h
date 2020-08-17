#pragma once
class UIWindow;


class SnapObject
{
	/* this+ 0 */ public: //const SnapObject::`vftable';
	/* this+ 4 */ private: UIWindow* m_careWindow;
	/* this+ 8 */ private: mystd::list<SnapObject*> m_snapObjectList[4];
	/* this+56 */ private: int m_isProcessed;

	public: SnapObject::SnapObject(void);
	public: virtual SnapObject::~SnapObject(void);
	//public: unsigned char SnapObject::IsOverLapped(int, int, int, int);
	//public: int SnapObject::CheckSnapType(class SnapObject *);
	//public: void SnapObject::ConnectSnapObjectEachOther(class SnapObject *, int);
	//public: void SnapObject::ConnectSnapObject(class SnapObject *, int);
	//public: void SnapObject::DisconnectSnapObject(class SnapObject *);
	//public: unsigned char SnapObject::IsConnectedRoot(class SnapObject *);
	//public: unsigned char SnapObject::IsConnected(class SnapObject *);
	//public: void SnapObject::MoveConnectedObject(int, int, int);
	//public: void SnapObject::MoveConnectedObjectRoot(int, int, int);
	//public: unsigned char SnapObject::IsSnapedTop(class SnapObject *);
	//public: unsigned char SnapObject::IsSnapedTopRoot(class SnapObject *);
	//public: void SnapObject::GetHeightOfGroup(int &, int);
	//public: int SnapObject::GetHeight();
};


class CSnapMgr
{
	/* this+0 */ public: //const CSnapMgr::`vftable';
	/* this+4 */ private: SnapObject* m_masterObject;
	/* this+8 */ private: mystd::list<SnapObject*> m_snapObjectList;

	public: CSnapMgr::CSnapMgr(void);
	public: virtual CSnapMgr::~CSnapMgr(void);
	public: void CSnapMgr::RemoveAll(void);
	public: void CSnapMgr::ClearWayAll(void);
	public: void CSnapMgr::AddSnapMasterObject(UIWindow* masterWindow);
	public: void CSnapMgr::AddSnapObject(UIWindow* window);
	public: void CSnapMgr::RemoveSnapObject(UIWindow* window);
	//public: void CSnapMgr::OrganizeSnap(class SnapObject *);
	//public: unsigned char CSnapMgr::IsWindowSnapedToMaster(class UIWindow *);
	public: void CSnapMgr::BeginMove(UIWindow* masterWindow);
	public: void CSnapMgr::EndMove(UIWindow* moveWindow);
	//public: void CSnapMgr::MoveDelta(class UIWindow *, int, int);
	//public: unsigned char CSnapMgr::IsMasterSnap(class SnapObject *);
	//public: unsigned char CSnapMgr::IsMasterSnap(class UIWindow *);
	//public: void CSnapMgr::MoveObject(class UIWindow *, int, int);
	//public: unsigned char CSnapMgr::IsConnected(class UIWindow *, class UIWindow *);
	//public: void CSnapMgr::GetDeltaDrag(class UIWindow *, int &, int &);
	//public: unsigned char CSnapMgr::IsRegisteredToSnap(class UIWindow *);
	public: void CSnapMgr::MoveConnectedObject(UIWindow* window, int dx, int dy, int snapType);
	//public: unsigned char CSnapMgr::IsSnapedTopOfMaster(class SnapObject *);
	//public: unsigned char CSnapMgr::IsThisGroupSnapedBottomOfScreen(class SnapObject *, int);
	//public: unsigned char CSnapMgr::IsThisGroupSnapedTopOfScreen(class SnapObject *);
	//public: class SnapObject * CSnapMgr::GetSnapObject(class UIWindow *);

private:
	static hook_method<void (CSnapMgr::*)(void)> CSnapMgr::_RemoveAll;
	static hook_method<void (CSnapMgr::*)(void)> CSnapMgr::_ClearWayAll;
	static hook_method<void (CSnapMgr::*)(UIWindow* masterWindow)> CSnapMgr::_AddSnapMasterObject;
	static hook_method<void (CSnapMgr::*)(UIWindow* window)> CSnapMgr::_AddSnapObject;
	static hook_method<void (CSnapMgr::*)(UIWindow* window)> CSnapMgr::_RemoveSnapObject;
	static hook_method<void (CSnapMgr::*)(UIWindow* masterWindow)> CSnapMgr::_BeginMove;
	static hook_method<void (CSnapMgr::*)(UIWindow* moveWindow)> CSnapMgr::_EndMove;
	static hook_method<void (CSnapMgr::*)(UIWindow* window, int dx, int dy, int snapType)> CSnapMgr::_MoveConnectedObject;
};
