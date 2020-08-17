void Debug(void)
{
/*
	// replace exe's allocator with ours
	HookDB::DB().Hook("operator new", SymDB::Find("operator new"), (void*(*)(size_t))&::operator new);
	HookDB::DB().Hook("operator new(nothrow)", SymDB::Find("operator new(nothrow)"), (void*(*)(size_t,std::nothrow_t const &))&::operator new);
	HookDB::DB().Hook("operator delete", SymDB::Find("operator delete"), (void(*)(void*))&::operator delete);

	HookDB::DB().Hook("WinMain", FTOV(&_WinMain), FTOV(&WinMain));
//	HookDB::DB().Hook("UIWindow::InvalidateWallPaper", FTOV(&UIWindow::_InvalidateWallPaper), FTOV(&UIWindow::InvalidateWallPaper));
	HookDB::DB().Hook("UIWindow::InvalidateChildren", FTOV(&UIWindow::_InvalidateChildren), FTOV(&UIWindow::InvalidateChildren));
	HookDB::DB().Hook("CGameMode::OnRun", FTOV(&CGameMode::_OnRun), FTOV(&CGameMode::OnRun));
	HookDB::DB().Hook("CGameMode::OnUpdate", FTOV(&CGameMode::_OnUpdate), FTOV(&CGameMode::OnUpdate));
	HookDB::DB().Hook("CGameMode::Zc_Par_Change", FTOV(&CGameMode::_Zc_Par_Change), FTOV(&CGameMode::Zc_Par_Change));
	HookDB::DB().Hook("CGameMode::PollNetworkStatus", FTOV(&CGameMode::_PollNetworkStatus), FTOV(&CGameMode::PollNetworkStatus));
	HookDB::DB().Hook("CModeMgr::Run", FTOV(&CModeMgr::_Run), FTOV(&CModeMgr::Run));
	HookDB::DB().Hook("CResMgr::Get", FTOV(&CResMgr::_Get), FTOV(&CResMgr::Get));
	HookDB::DB().Hook("CSession::InvalidateBasicWnd", FTOV(&CSession::_InvalidateBasicWnd), FTOV(&CSession::InvalidateBasicWnd));
	HookDB::DB().Hook("CSession::ChangeXorValue", FTOV(&CSession::_ChangeXorValue), FTOV(&CSession::ChangeXorValue));
	HookDB::DB().Hook("CPc::RenderBodyLayer", FTOV(&CPc::_RenderBodyLayer), FTOV(&CPc::RenderBodyLayer));
*/
}
