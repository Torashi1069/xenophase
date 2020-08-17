// bug #120: crash in CBlurPC->CPc::RenderBodyLayer
// symptoms: randomly occuring crash when a character with Energy Coat active is onscreen
// cause: uninitialized accessory view id variables in CBlurPC/CPc fed into fragile sprite rendering code
namespace Fix_uninitialized_cblurpc_crash
{


class CPc
{
public:
	/* this+0 */ BYTE dummy[996];

	static hook_func<CPc* (CPc::*)(void)> CPc::_ctorCPc;
	CPc* CPc::ctorCPc(void);
};


hook_func<CPc* (CPc::*)(void)> CPc::_ctorCPc("CPc::CPc");
CPc* CPc::ctorCPc(void)
{
	memset(this, 0, sizeof(*this));
	return (this->*_ctorCPc)();
}


};


using namespace Fix_uninitialized_cblurpc_crash;
void Apply_fix_uninitialized_cblurpc_crash()
{
	HookDB::DB().Hook("CPc::CPc", FTOV(&CPc::_ctorCPc), FTOV(&CPc::ctorCPc));
}
