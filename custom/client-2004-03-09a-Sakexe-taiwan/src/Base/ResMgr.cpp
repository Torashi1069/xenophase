#include "Globals.h"
#include "Base/File.h"
#include "Base/ResMgr.h"
#include "Base/Util.h"


CResMgr& g_resMgr()
{
	static CResMgr resMgr;
	return resMgr;
}


CResMgr::CResMgr()
{
	m_usedForSprTexture = 0;
	m_usedForModelTexture = 0;
	m_usedForGNDTexture = 0;
	m_usedForSprite = 0;
	m_usedForSprAction = 0;
	m_usedForGAT = 0;
	m_usedForGND = 0;
	m_usedForIMF = 0;
	m_usedForModel = 0;
	m_ResMemAmount = 0;
	m_ResSprAmount = 0;
	m_ResTexAmount = 0;
	m_ResGatAmount = 0;
	m_ResGndAmount = 0;
	m_ResRswAmount = 0;
	m_ResModAmount = 0;
	m_ResWavAmount = 0;

	InitializeCriticalSection(&m_GetResSection);
}


CResMgr::~CResMgr()
{
	this->CResMgr::UnloadAll();
	DeleteCriticalSection(&m_GetResSection);
}


void CResMgr::Reset()
{
	this->CResMgr::UnloadAll();
}


CRes* CResMgr::Get(const char* fNameInput)
{
	if( fNameInput == NULL )
		return NULL;

	EnterCriticalSection(&m_GetResSection);

	char fName[128];
	strcpy(fName, fNameInput);
	this->CResMgr::ToLower(fName);

	const char* ext = this->CResMgr::ExtractExt(fName);
	if( ext == NULL )
	{
		LeaveCriticalSection(&m_GetResSection);
		return NULL;
	}

	int index = this->CResMgr::FindExtIndex(ext);
	if( index < 0 )
	{
		LeaveCriticalSection(&m_GetResSection);
		return NULL;
	};

	char openFileName[256] = {};
	this->CResMgr::MakeOpenName(openFileName, fName, m_typeDir[index]);

	CRes* res = this->CResMgr::FindRes(index, openFileName);
	if( res != NULL )
	{// already loaded
		res->CRes::UpdateTimeStamp();
		LeaveCriticalSection(&m_GetResSection);
		return res;
	}

	CRes* newres = m_objTypes[index]->Clone();
	if( !newres->Load(openFileName) )
	{
		this->CResMgr::MakeOpenName(openFileName, this->CResMgr::GetRealResName(fName), m_typeDir[index]);
		if( !newres->Load(openFileName) )
		{
			newres->OnLoadError(fName);
			delete newres;
			LeaveCriticalSection(&m_GetResSection);
			return NULL;
		}
	}

	newres->CRes::UpdateInfo(openFileName, index);
	m_fileList[index].insert(res_map_value(&newres->m_fName, newres));

	LeaveCriticalSection(&m_GetResSection);
	return newres;
}


int CResMgr::IsExist(const char* fNameInput)
{
	if( fNameInput == NULL )
		return 0;

	char fName[128];
	strcpy(fName, fNameInput);
	this->CResMgr::ToLower(fName);

	const char* ext = this->CResMgr::ExtractExt(fName);
	if( ext == NULL )
		return 0;

	int index = this->CResMgr::FindExtIndex(ext);
	if( index < 0 )
		return 0;

	char openFileName[256] = {};
	this->CResMgr::MakeOpenName(openFileName, fName, m_typeDir[index]);

	CRes* res = this->CResMgr::FindRes(index, openFileName);
	if( res != NULL )
	{
		res->CRes::UpdateTimeStamp();
		return 1;
	}

	return CFile::IsFileExist(openFileName);
}


void CResMgr::Unload(CRes* res)
{
	res_map_iter iter = m_fileList[res->m_extIndex].find(&res->m_fName);
	iter->second->Reset();
	delete iter->second;
	m_fileList[res->m_extIndex].erase(iter);
}


void CResMgr::UnloadAll()
{
	for( size_t a = 0; a < m_fileList.size(); ++a )
	{
		res_map& map = m_fileList[a];
		for( res_map_iter iter = map.begin(); iter != map.end(); ++iter )
		{
			CRes* res = iter->second;
			res->Reset();
			delete res;
		}

		m_fileList.clear();
	}
}


void CResMgr::UnloadRarelyUsedRes()
{
	DWORD expireTime = timeGetTime() - EXPIRETIME;

	for( size_t a = 0; a < m_fileList.size(); ++a )
	{
		res_map& map = m_fileList[a];
		for( res_map_iter iter = map.begin(); iter != map.end(); )
		{
			CRes* res = iter->second;
			if( res->m_lockCnt == 0 && expireTime > res->m_timeStamp )
			{
				res->Reset();
				delete res;
				iter = map.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}


void CResMgr::UnloadUnlockedRes()
{
	DWORD expireTime = timeGetTime() - EXPIRETIME; // unused

	for( size_t a = 0; a < m_fileList.size(); ++a )
	{
		res_map& map = m_fileList[a];
		for( res_map_iter iter = map.begin(); iter != map.end(); )
		{
			CRes* res = iter->second;
			if( res->m_lockCnt == 0 )
			{
				res->Reset();
				delete res;
				iter = map.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}


void CResMgr::UnloadResByExt(const char* ext)
{
	int index = this->CResMgr::FindExtIndex(ext);
	if( index < 0 )
		return;

	res_map& map = m_fileList[index];
	for( res_map_iter iter = map.begin(); iter != map.end(); )
	{
		CRes* res = iter->second;
		if( res->m_lockCnt == 0 )
		{
			res->Reset();
			delete res;
			iter = map.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}


void CResMgr::RegisterType(const char* resId, const char* baseDir, CRes* t)
{
	int index = m_resExt.size();
	m_resExt.insert(ext_map_value(resId, index));
	m_objTypes.push_back(t);
	m_typeDir.push_back(baseDir);
	m_fileList.resize(index + 1);
}


void CResMgr::ReadResNameTable(const char* resNameTable)
{
	m_realResName.clear();

	CFile fp;
	if( !fp.CFile::Open("ResNameTable.txt", CFile::modeRead) )
		return;

	size_t size = fp.CFile::GetLength();
	char* buf = new char[size + 1];
	fp.CFile::Read(buf, size);
	buf[size] = '\0';

	fp.CFile::Close();

	mystd::string a;
	mystd::string b;
	char* p = buf;

	for( size_t i = 0; i < size; ++i )
	{
		if( buf[i] == '\n' || buf[i] == '\r' )
		{
			buf[i] = '\0';
			p = &buf[i + 1];
		}
		else
		if( buf[i] == '#' )
		{
			buf[i] = '\0';

			if( a.size() == 0 )
			{
				a = p;
			}
			else
			{
				b = p;

				m_realResName.insert(mystd::pair<mystd::string const,mystd::string>(a, b));
				a.erase();
				b.erase();
			}

			p = &buf[i + 1];
		}
	}

	delete[] buf;
}


void CResMgr::PrintRes(const char* fileName)
{
	FILE* file = fopen(fileName, "wt");
	if( file == NULL )
		return;

	for( mystd::vector<res_map>::iterator iter = m_fileList.begin(); iter != m_fileList.end(); ++iter )
	{
		res_map& map = *iter;
		for( res_map_iter iter = map.begin(); iter != map.end(); ++iter ) 
		{
			const CRes* res = iter->second;
			fprintf(file, "%s\n", res->m_fName); //FIXME: should be '.c_str()' (passing entire object on stack, will crash)
		}
	}

	fclose(file);
}


CRes* CResMgr::FindRes(int ext, const char* name)
{
	CHash fName(name);
	res_map_iter iter = m_fileList[ext].find(&fName);
	return ( iter != m_fileList[ext].end() ) ? iter->second : NULL;
}


void CResMgr::MakeOpenName(char* openName, const char* fName, const char* typeDir)
{
	size_t dirLen = strlen(typeDir);

	if( strncmp(fName, typeDir, dirLen) != 0 )
	{
		strcpy(openName, typeDir);
		strcpy(openName + dirLen, fName);
	}
	else
	{
		strcpy(openName, fName);
	}
}


const char* CResMgr::ExtractExt(const char* fName)
{
	const char* dot = StrChrBackward(fName, '.');
	return ( dot != NULL ) ? dot + 1 : NULL;
}


int CResMgr::FindExtIndex(const char* ext_str)
{
	if( ext_str == NULL )
		return -1;

	ext_map_iter iter = m_resExt.find(ext_str);
	if( iter == m_resExt.end() )
	{
		char msg[255];
		sprintf(msg, "ResourceError : %s is Undefined Ext \n", ext_str);
		return -1;
	}

	return iter->second;
}


const char* CResMgr::GetRealResName(const char* resName)
{
	mystd::map<mystd::string, mystd::string>::iterator iter = m_realResName.find(resName);
	return ( iter != m_realResName.end() ) ? iter->second.c_str() : resName;
}


char* CResMgr::ToLower(char* text)
{
	static const BYTE lower_table[256] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
		0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
		0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
		0x40,  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o',
		 'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
		0x60,  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o',
		 'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
		0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
		0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
		0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
		0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
		0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
		0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
		0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
		0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
	};

	for( char* p = text; *p != '\0'; ++p )
		*p = lower_table[BYTE(*p)];

	return text;
}


////////////////////////////////////////


class hook_ptr<struct mystd::_Tree<char const *,struct mystd::pair<char const * const,int>,struct mystd::map<char const *,int,class CharPrtLess,class mystd::allocator<int> >::_Kfn,class CharPrtLess,class mystd::allocator<int> >::_Node *> mystd::_Tree<char const *,struct mystd::pair<char const * const,int>,struct mystd::map<char const *,int,class CharPrtLess,class mystd::allocator<int> >::_Kfn,class CharPrtLess,class mystd::allocator<int> >::_Nil(SAKEXE, "?_Nil@?$_Tree@PBDU?$pair@QBDH@std@@U_Kfn@?$map@PBDHUCharPrtLess@@V?$allocator@H@std@@@2@UCharPrtLess@@V?$allocator@H@2@@std@@1PAU_Node@12@A");
class hook_val<unsigned int> mystd::_Tree<char const *,struct mystd::pair<char const * const,int>,struct mystd::map<char const *,int,class CharPrtLess,class mystd::allocator<int> >::_Kfn,class CharPrtLess,class mystd::allocator<int> >::_Nilrefs(SAKEXE, "?_Nilrefs@?$_Tree@PBDU?$pair@QBDH@std@@U_Kfn@?$map@PBDHUCharPrtLess@@V?$allocator@H@std@@@2@UCharPrtLess@@V?$allocator@H@2@@std@@1IA");
class hook_ptr<struct mystd::_Tree<class CHash *,struct mystd::pair<class CHash * const,class CRes *>,struct mystd::map<class CHash *,class CRes *,struct ResPtrLess,class mystd::allocator<class CRes *> >::_Kfn,struct ResPtrLess,class mystd::allocator<class CRes *> >::_Node *> mystd::_Tree<class CHash *,struct mystd::pair<class CHash * const,class CRes *>,struct mystd::map<class CHash *,class CRes *,struct ResPtrLess,class mystd::allocator<class CRes *> >::_Kfn,struct ResPtrLess,class mystd::allocator<class CRes *> >::_Nil(SAKEXE, "?_Nil@?$_Tree@PAVCHash@@U?$pair@QAVCHash@@PAVCRes@@@std@@U_Kfn@?$map@PAVCHash@@PAVCRes@@UResPtrLess@@V?$allocator@PAVCRes@@@std@@@3@UResPtrLess@@V?$allocator@PAVCRes@@@3@@std@@1PAU_Node@12@A");
class hook_val<unsigned int> mystd::_Tree<class CHash *,struct mystd::pair<class CHash * const,class CRes *>,struct mystd::map<class CHash *,class CRes *,struct ResPtrLess,class mystd::allocator<class CRes *> >::_Kfn,struct ResPtrLess,class mystd::allocator<class CRes *> >::_Nilrefs(SAKEXE, "?_Nilrefs@?$_Tree@PAVCHash@@U?$pair@QAVCHash@@PAVCRes@@@std@@U_Kfn@?$map@PAVCHash@@PAVCRes@@UResPtrLess@@V?$allocator@PAVCRes@@@std@@@3@UResPtrLess@@V?$allocator@PAVCRes@@@3@@std@@1IA");
class hook_ptr<struct mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > > >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > > >::_Node *> mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > > >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > > >::_Nil(SAKEXE, "?_Nil@?$_Tree@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@2@U_Kfn@?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$less@V?$b56f2d813");
class hook_val<unsigned int> mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > > >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > > >::_Nilrefs(SAKEXE, "?_Nilrefs@?$_Tree@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@2@U_Kfn@?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$less@6b63463b");
