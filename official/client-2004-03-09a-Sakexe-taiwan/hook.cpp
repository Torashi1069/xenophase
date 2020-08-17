void Hook()
{
	#define HOOK(S) HookDB::DB().Hook(S, SymDB::Add(S, SAKEXE, S), SymDB::Add("dll!"##S, DLLPATH(), S))

	extern void Test(void);
	Test();

	extern void Hook_Alloc(void* pfnNew, void* pfnDelete, void* pfnInit);
	Hook_Alloc(DetourFindFunction(SAKEXE, "??2@YAPAXI@Z"), DetourFindFunction(SAKEXE, "??3@YAXPAX@Z"), DetourFindFunction(SAKEXE, "__cinit"));
}


void UnHook()
{
}


void Test()
{
	CDia dia, dia2;
	dia.Open(EXEPATH());
	dia2.Open(DLLPATH());

	COMPARE_SIZE(C3dDevice);
	COMPARE_SIZE(CFile);
	COMPARE_OFFSET(CFile, m_hFile);
	COMPARE_OFFSET(CFile, m_buf);
	COMPARE_OFFSET(CFile, m_cursor);
	COMPARE_OFFSET(CFile, m_size);
	COMPARE_OFFSET(CFile, m_fileName);
	COMPARE_SIZE(CFileMgr);
	COMPARE_SIZE(CGameMode);
	COMPARE_SIZE(CGPak);
	COMPARE_SIZE(CHash);
	COMPARE_SIZE(CLoginMode);
	COMPARE_SIZE(CMemFile);
	COMPARE_SIZE(CRenderer); // 0x294
	COMPARE_OFFSET(CRenderer, m_hpc);
	COMPARE_OFFSET(CRenderer, m_vpc);
	COMPARE_OFFSET(CRenderer, m_hratio);
	COMPARE_OFFSET(CRenderer, m_vratio);
	COMPARE_OFFSET(CRenderer, m_aspectRatio);
	COMPARE_OFFSET(CRenderer, m_screenXFactor);
	COMPARE_OFFSET(CRenderer, m_screenYFactor);
	COMPARE_OFFSET(CRenderer, m_xoffset);
	COMPARE_OFFSET(CRenderer, m_yoffset);
	COMPARE_OFFSET(CRenderer, m_width);
	COMPARE_OFFSET(CRenderer, m_height);
	COMPARE_OFFSET(CRenderer, m_halfWidth);
	COMPARE_OFFSET(CRenderer, m_halfHeight);
	COMPARE_OFFSET(CRenderer, m_curFrame);
	COMPARE_OFFSET(CRenderer, m_bRGBBitCount);
	COMPARE_OFFSET(CRenderer, m_fpsFrameCount);
	COMPARE_OFFSET(CRenderer, m_fpsStartTick);
	COMPARE_OFFSET(CRenderer, m_isFoggy);
	COMPARE_OFFSET(CRenderer, m_fogChanged);
	COMPARE_OFFSET(CRenderer, m_isVertexFog);
	COMPARE_OFFSET(CRenderer, m_oldTexture);
	COMPARE_OFFSET(CRenderer, m_oldLmapTexture);
	COMPARE_OFFSET(CRenderer, m_guardBandLeft);
	COMPARE_OFFSET(CRenderer, m_guardBandRight);
	COMPARE_OFFSET(CRenderer, m_guardBandTop);
	COMPARE_OFFSET(CRenderer, m_guardBandBottom);
	COMPARE_OFFSET(CRenderer, m_isShowInfo);
	COMPARE_OFFSET(CRenderer, m_eyeVector);
	COMPARE_OFFSET(CRenderer, m_nClearColor);
	COMPARE_OFFSET(CRenderer, m_device);
	COMPARE_OFFSET(CRenderer, m_lpSurface);
	COMPARE_OFFSET(CRenderer, m_dwScreenWidth);
	COMPARE_OFFSET(CRenderer, m_dwScreenHeight);
	COMPARE_OFFSET(CRenderer, m_pf);
	COMPARE_OFFSET(CRenderer, m_lpSurfacePtr);
	COMPARE_OFFSET(CRenderer, m_lPitch);
	COMPARE_OFFSET(CRenderer, m_rpFaceList);
	COMPARE_OFFSET(CRenderer, m_rpLMGroundList);
	COMPARE_OFFSET(CRenderer, m_rpLMLightList);
	COMPARE_OFFSET(CRenderer, m_rpAlphaDepthList);
	COMPARE_OFFSET(CRenderer, m_rpAlphaList);
	COMPARE_OFFSET(CRenderer, m_rpAlphaNoDepthList);
	COMPARE_OFFSET(CRenderer, m_rpEmissiveDepthList);
	COMPARE_OFFSET(CRenderer, m_rpEmissiveList);
	COMPARE_OFFSET(CRenderer, m_rpEmissiveNoDepthList);
	COMPARE_OFFSET(CRenderer, m_rpRawList);
	COMPARE_OFFSET(CRenderer, m_rpRawAlphaList);
	COMPARE_OFFSET(CRenderer, m_rpRawEmissiveList);
	COMPARE_OFFSET(CRenderer, m_rpAlphaOPList);
	COMPARE_OFFSET(CRenderer, m_rpLmList);
	COMPARE_OFFSET(CRenderer, m_rpBumpFaceList);
	COMPARE_OFFSET(CRenderer, m_cacheSurfaces);
	COMPARE_OFFSET(CRenderer, m_unusedCacheSurfaces);
	COMPARE_OFFSET(CRenderer, m_rpNullFaceList);
	COMPARE_OFFSET(CRenderer, m_rpNullFaceListIter);
	COMPARE_OFFSET(CRenderer, m_rpQuadFaceList);
	COMPARE_OFFSET(CRenderer, m_rpQuadFaceListIter);
	COMPARE_OFFSET(CRenderer, m_rpLmQuadFaceList);
	COMPARE_OFFSET(CRenderer, m_rpLmQuadFaceListIter);
	COMPARE_OFFSET(CRenderer, m_vertBuffer);
	COMPARE_SIZE(CSession); // 0x18B8
	COMPARE_SIZE(CSurface); // 0x10
	COMPARE_SIZE(CTexture); // 0x128
	COMPARE_SIZE(XMLElement);
	COMPARE_SIZE(XMLDocument);
	COMPARE_SIZE(ITEM_INFO);

	COMPARE_SIZE(_DDSURFACEDESC2); // 0x7C
	COMPARE_SIZE(_DDPIXELFORMAT); // 0x20

	assert( DetourFindFunction(SAKEXE, "PLEASE_EXCUTE_LAUNCHER") );
	assert( DetourFindFunction(SAKEXE, "g_fileMgr") );
	assert( DetourFindFunction(SAKEXE, "g_hMainWnd") );
	assert( DetourFindFunction(SAKEXE, "g_3dDevice") );
	assert( DetourFindFunction(SAKEXE, "g_baseDir") );
	assert( DetourFindFunction(SAKEXE, "g_readFolderFirst") );
	assert( DetourFindFunction(SAKEXE, "document") );
	assert( DetourFindFunction(SAKEXE, "g_serviceType") );
	assert( DetourFindFunction(SAKEXE, "g_serverType") );
	assert( DetourFindFunction(SAKEXE, "s_loadingScreenList") );
	assert( DetourFindFunction(SAKEXE, "g_hideAccountList") );
	assert( DetourFindFunction(SAKEXE, "g_passwordEncrypt") );
	assert( DetourFindFunction(SAKEXE, "g_passwordEncrypt2") );
	assert( DetourFindFunction(SAKEXE, "g_extended_slot") );
	assert( DetourFindFunction(SAKEXE, "g_accountAddr") );
	assert( DetourFindFunction(SAKEXE, "g_accountPort") );
	assert( DetourFindFunction(SAKEXE, "g_regstrationWeb") );

	assert( sizeof(float) == 4 );
	assert( sizeof(mystd::deque<int>) == 48 );
	assert( sizeof(mystd::list<int>) == 12 );
	assert( sizeof(mystd::pair<int,int>) == 8 );
	assert( sizeof(mystd::string) == 16 );
	assert( sizeof(mystd::vector<int>) == 16 );
}


void SymDBInitCallback()
{
	SymDB::Add("mystd::_Tree<int,struct mystd::pair<int const ,struct SKILL_DESC>,struct mystd::map<int,struct SKILL_DESC,struct mystd::less<int>,class mystd::allocator<struct SKILL_DESC> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct SKILL_DESC> >::_Nil", 0x665398);
}
