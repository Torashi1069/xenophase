// bug #119: stall in CGameMode::GetGroundAttrPos after map loading
// symptoms: randomly occuring hang after map loading with 100% cpu usage for several seconds
// cause: uninitialized vector/matrix variables in CView fed into raytracer code
namespace Fix_uninitialized_cview_stall
{


class CView
{
public:
	/* this+0 */ BYTE dummy[448];

	static hook_func<CView* (CView::*)(void)> CView::_ctorCView;
	CView* CView::ctorCView(void);
};


hook_func<CView* (CView::*)(void)> CView::_ctorCView("CView::CView");
CView* CView::ctorCView(void)
{
	memset(this, 0, sizeof(*this));
	return (this->*_ctorCView)();
}


};


using namespace Fix_uninitialized_cview_stall;
void Apply_fix_uninitialized_cview_stall()
{
	HookDB::DB().Hook("CView::CView", FTOV(&CView::_ctorCView), FTOV(&CView::ctorCView));
}
