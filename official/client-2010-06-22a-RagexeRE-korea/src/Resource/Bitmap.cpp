#include "Globals.h" // ErrorMsg()
#include "Base/File.h"
#include "Base/Res.h"
#include "Resource/Bitmap.h"


CBitmapRes::CBitmapRes()
{
	m_isAlpha = FALSE;
	m_data = NULL;
	m_data2 = NULL;
}


CBitmapRes::CBitmapRes(class Exemplar __formal, const char* resid, const char* baseDir)
{
	g_resMgr().CResMgr::RegisterType(resid, baseDir, this);
}


CBitmapRes::~CBitmapRes()
{
}


hook_func<bool (CBitmapRes::*)(const char* fName, const char* buffer, int size)> CBitmapRes::_LoadFromBuffer("CBitmapRes::LoadFromBuffer");
bool CBitmapRes::LoadFromBuffer(const char* fName, const char* buffer, int size)
{
//	return (this->*_LoadFromBuffer)(fName, buffer, size);

	const char* ext = strrchr(fName, '.');
	if( ext == NULL )
		return false;

	if( !lstrcmpiA(ext, ".bmp") )
		return this->CBitmapRes::LoadBMPData(buffer, size);
	if( !lstrcmpiA(ext, ".tga") )
		return this->CBitmapRes::LoadTGAData(buffer, size);
	if( !lstrcmpiA(ext, ".jpg") )
		return this->CBitmapRes::LoadJPGData(buffer, size);

	ErrorMsg("Unsupport fileformat!");
	return false;
}


hook_func<CRes* (CBitmapRes::*)(void)> CBitmapRes::_Clone("CBitmapRes::Clone");
CRes* CBitmapRes::Clone(void)
{
	return (this->*_Clone)();
}


hook_func<bool (CBitmapRes::*)(const char* fName)> CBitmapRes::_Load("CBitmapRes::Load");
bool CBitmapRes::Load(const char* fName)
{
	return (this->*_Load)(fName);
/*
	CFile fp;

	if( fName && fp.CFile::Open(fName, 0) )
		if( this->(this->baseclass_0.vtable + 1)(fName, fp.m_buf, fp.m_size) )
			return 1;

	return 0;
*/
}


hook_func<void (CBitmapRes::*)(void)> CBitmapRes::_Reset("CBitmapRes::Reset");
void CBitmapRes::Reset(void)
{
	return (this->*_Reset)();
}


void CBitmapRes::sub_4257C0_deldata2()
{
	if( m_data2 != NULL )
	{
		delete m_data2;
		m_data2 = NULL;
	}
}


hook_func<bool (CBitmapRes::*)(int a2)> CBitmapRes::_sub_4257F0("CBitmapRes::sub_4257F0");
bool CBitmapRes::sub_4257F0(int a2)
{
	return (this->*_sub_4257F0)(a2);

	//TODO
}


hook_func<bool (CBitmapRes::*)(const char* bitmap, int size)> CBitmapRes::_LoadBMPData("CBitmapRes::LoadBMPData");
bool CBitmapRes::LoadBMPData(const char* bitmap, int size)
{
	return (this->*_LoadBMPData)(bitmap, size);

	this->Reset();

	char magic[12+1];
	memcpy(magic, bitmap, 12);
	magic[12] = 0;

	BITMAPFILEHEADER bmfh;
	memcpy(&bmfh, bitmap, sizeof(bmfh));

	RGBTRIPLE* in_data = NULL;

	if( strcmp(magic, "\xC3\xD1\xBE\xCB\xC0\xCC\xBB\xA1\xC5\xE4\xB4\xCF") == 0 ) // "총알이빨토니"
	{
		/*
		int v10; // eax@9
		int v11; // esi@9
		unsigned int v12; // eax@10
		int v13; // ecx@10
		char *v14; // eax@11
		char *v15; // edi@11
		char *v16; // esi@11
		char v17; // dl@12
		char *v18; // esi@12
		char *v19; // edi@12
		char v20; // dl@12
		char *v21; // eax@14
		signed int v22; // ecx@14
		char *v23; // edi@14
		char *v24; // esi@14
		char v25; // dl@15
		char *v26; // esi@15
		char *v27; // edi@15
		char v28; // dl@15
		int v29; // eax@17
		int v30; // esi@17
		int v31; // esi@17
		unsigned int v32; // eax@17
		int v33; // edx@17
		int v34; // ecx@17
		int v35; // edi@17
		int v36; // eax@17
		int v37; // ecx@18
		int v38; // edi@18
		char v39; // dl@18
		char v40; // dl@18
		int v42; // eax@22
		int v43; // edx@22
		void *v44; // edi@22
		void *v45; // eax@22
		unsigned int v46; // ST00_4@22
		void *v47; // eax@22
		unsigned int v48; // ecx@23
		char v49; // al@24
		unsigned int v50; // ecx@24
		void *v51; // edi@24
		const void *v52; // esi@24
		int v53; // eax@24
		unsigned int v54; // ecx@27
		int v55; // edi@29
		char v56; // al@29
		unsigned int v57; // ecx@29
		void *v58; // edi@29
		const void *v59; // esi@29
		int v60; // eax@29
		int v61; // ecx@31
		int v62; // eax@32
		unsigned __int8 v65; // sf@34
		unsigned __int8 v66; // of@34
		char v103[512]; // [sp+100Ch] [bp-864h]@10
		char v104[512]; // [sp+120Ch] [bp-664h]@10
		void *v109; // [sp+1858h] [bp-18h]@22
		void *v110; // [sp+185Ch] [bp-14h]@22
		void *Memory; // [sp+1864h] [bp-Ch]@22
		unsigned __int8 v115; // [sp+1878h] [bp+8h]@4
		int v116; // [sp+1878h] [bp+8h]@9
		void *v118; // [sp+1878h] [bp+8h]@22

		unsigned int v5 = ((*((_DWORD *)bitmap + 3) >> 1) - 0x1929300u) >> 16;
		int v6 = (((*((_DWORD *)bitmap + 3) >> 1) - 0x1929300) & 0xFFFF) - 1;

		v115 = bitmap[16];
		if( v115 == 0 )
			bmih.biBitCount = 8;
		else
		if( v115 == 1 )
			bmih.biBitCount = 24;
		else
		{
			ErrorMsg("Only 16M or 8bit color format supported");
			return false;
		}

		void* v7 = &bitmap[17];
		void* v114 = (void *)v7;

		m_height = v6;
		m_width = v5;
		in_data = operator new(3 * m_width * m_height);
		m_data = operator new(4 * m_width * m_height);

		if( bmih.biBitCount == 8 )
		{
			v10 = *(_DWORD *)v7;
			v11 = v7 + 4;
			v116 = v10;
			v114 = (void *)v11;
			if ( v10 )
			{
				v12 = 2 * v10;
				memcpy(v104, (const void *)v11, v12);
				v114 = (char *)v114 + v12;
				memcpy(v103, v114, v12);
				v114 = (char *)v114 + v12;
				v13 = v116;
				if ( v116 )
				{
					v15 = v103;
					v16 = v104;
					v14 = &v105[3];
					do
					{
						v17 = *v16;
						v18 = v16 + 1;
						*(v14 - 2) = v17;
						*v14 = *v15;
						v19 = v15 + 1;
						*(v14 - 3) = *v18;
						v16 = v18 + 1;
						v14 += 4;
						v20 = *v19;
						v15 = v19 + 1;
						*(v14 - 5) = v20;
						--v13;
					}
					while ( v13 );
				}
			}
			else
			{
				memcpy(v104, (const void *)v11, sizeof(v104));
				memcpy(v103, (char *)v114 + 512, sizeof(v103));
				v114 = (char *)v114 + 1024;
				v23 = v103;
				v24 = v104;
				v21 = &v105[3];
				v22 = 256;
				do
				{
					v25 = *v24;
					v26 = v24 + 1;
					*(v21 - 2) = v25;
					*v21 = *v23;
					v27 = v23 + 1;
					*(v21 - 3) = *v26;
					v24 = v26 + 1;
					v21 += 4;
					v28 = *v27;
					v23 = v27 + 1;
					*(v21 - 5) = v28;
					--v22;
				}
				while ( v22 );
			}

			int v117 = m_height - 1;
			if ( v117 >= 0 )
			{
				do
				{
					v31 = (int)v114;
					v32 = m_width + 3;
					LOBYTE(v32) = v32 & 0xFC;

					char v102[4096]; // [sp+Ch] [bp-1864h]@17
					memcpy(v102, v114, 4 * (v32 >> 2));
					v33 = (int)in_data;
					memcpy(&v102[4 * (v32 >> 2)], (const void *)(v31 + 4 * (v32 >> 2)), v32 & 3);
					v34 = m_width;
					v35 = (int)((char *)v114 + v32);
					v36 = v117 * m_width;
					v30 = 0;
					v114 = (void *)v35;
					v29 = v33 + 3 * v36;
					if ( v34 > 0 )
					{
						do
						{
							v29 += 3;
							v37 = (unsigned __int8)v102[v30++];
							v38 = v37;
							v39 = v105[4 * v37];
							LOBYTE(v37) = v105[4 * v37 + 1];
							*(_BYTE *)(v29 - 3) = v39;
							v40 = v105[4 * v38 + 2];
							*(_BYTE *)(v29 - 2) = v37;
							*(_BYTE *)(v29 - 1) = v40;
						}
						while ( v30 < m_width );
					}
				}
				while ( v117-- - 1 >= 0 );
			}
		}
		else
		if ( bmih.biBitCount == 24 )
		{
			v45 = operator new(3 * m_width * m_height);
			v44 = v45;
			v46 = 2 * m_width * m_height;
			v110 = v45;
			v47 = operator new(v46);
			v43 = (int)in_data;
			Memory = v47;
			v42 = m_height - 1;
			v118 = v44;
			v109 = Memory;
			if ( v42 >= 0 )
			{
				v48 = 2 * m_width;
				v111 = v42 + 1;
				do
				{
					v49 = v48;
					v50 = v48 >> 2;
					memcpy(v118, (const void *)v7, 4 * v50);
					v52 = (const void *)(v7 + 4 * v50);
					v51 = (char *)v118 + 4 * v50;
					LOBYTE(v50) = v49;
					v53 = v111;
					memcpy(v51, v52, v50 & 3);
					v48 = 2 * m_width;
					v7 = (int)((char *)v114 + v48);
					v118 = (char *)v118 + v48;
					v114 = (char *)v114 + v48;
					v111 = v53 - 1;
				}
				while ( v53 != 1 );
				v44 = v110;
			}
			if ( m_height - 1 >= 0 )
			{
				v54 = m_width;
				int v119 = m_height;
				while ( 1 )
				{
					v55 = (int)v109;
					v56 = v54;
					v57 = v54 >> 2;
					memcpy(v109, (const void *)v7, 4 * v57);
					v59 = (const void *)(v7 + 4 * v57);
					v58 = (void *)(v55 + 4 * v57);
					LOBYTE(v57) = v56;
					v60 = v119;
					memcpy(v58, v59, v57 & 3);
					v54 = m_width;
					v109 = (char *)v109 + v54;
					v114 = (char *)v114 + v54;
					--v119;
					if ( v60 == 1 )
						break;
					v7 = (int)v114;
				}
				v44 = v110;
			}
			v61 = 0;
			int v120 = 0;
			if ( m_height > 0 )
			{
				do
				{
					v62 = m_width;
					for ( i = 0; i < v62; ++i )
					{
						v43 += 3;
						v44 = v110;
						v61 += 2;
						*(_BYTE *)(v43 - 3) = *((_BYTE *)Memory + v120 * v62 + i);
						*(_BYTE *)(v43 - 2) = *((_BYTE *)v44 + v61 - 2);
						*(_BYTE *)(v43 - 1) = *((_BYTE *)v44 + v61 - 1);
						v62 = m_width;
					}
					v66 = __SETO__(v120 + 1, m_height);
					v65 = v120++ + 1 - m_height < 0;
				}
				while ( v65 ^ v66 );
			}
			operator delete(v44);
			operator delete(Memory);
		}
		*/
	}
	else
	if( bmfh.bfType == 'MB' ) // "BM"
	{
		BITMAPINFOHEADER bmih;
		memcpy(&bmih, &bitmap[14], sizeof(bmih));

		if( bmih.biBitCount != 24 && bmih.biBitCount != 8 )
		{
			ErrorMsg("Only 16M or 8bit color format supported");
			return false;
		}

		int aligned_width = bmih.biWidth + (4 - bmih.biWidth % 4) % 4;

		m_width = bmih.biWidth;
		m_height = bmih.biHeight;

		in_data = new RGBTRIPLE[bmih.biWidth * bmih.biHeight];
		m_data = new unsigned long[m_width * m_height];

		if( bmih.biBitCount == 8 )
		{
			return (this->*_LoadBMPData)(bitmap, size);

			char palette[1024];
			int nColors = ( bmih.biClrUsed != 0 ) ? bmih.biClrUsed : 256;
			memcpy(palette, &bitmap[54], 4 * nColors);

			const char* pData = &bitmap[bmfh.bfOffBits];

			for( int i = m_height - 1; i >= 0; --i )
			{
				/*
				unsigned int v76 = m_width + 3;
				LOBYTE(v76) = v76 & 0xFC;

				char v102[4096];
				memcpy(v102, pData, v76);

				pData += v76;

				// convert row from 8-bit palette to 24bit RGB
				RGBTRIPLE* v73 = &in_data[i * m_width];
				for( int v74 = 0; v74 < m_width; ++v74 )
				{
					int v81 = (unsigned char)v102[v74];
					v73->rgbtBlue = palette[4 * v81 + 0];
					v73->rgbtGreen = palette[4 * v81 + 1];
					v73->rgbtRed = palette[4 * v81 + 2];
					v73++;
				}
				*/
			}
		}
		else
		if( bmih.biBitCount == 24 )
		{
			const char* pData = &bitmap[bmfh.bfOffBits];

			for( int i = m_height - 1; i >= 0; --i )
			{
				memcpy(&in_data[i * m_width], pData, sizeof(RGBTRIPLE) * m_width);
				pData += sizeof(RGBTRIPLE) * m_width;
				if( aligned_width != m_width )
					pData += 4 + m_width - aligned_width;
			}
		}
	}
	else
	{
		return 0;
	}

	// Assume in_data[] holds RGBTRIPLEs.
	// Convert to RGBQUADs and store in m_data.
	for( int j = 0; j < m_height; ++j )
	{
		RGBTRIPLE* v94 = &in_data[j * m_width];
		unsigned long* v101 = &m_data[j * m_width];
		for( int v100 = 0; v100 < m_width; ++v100 )
		{
			*v101 = v94->rgbtBlue + ((v94->rgbtGreen + ((v94->rgbtRed + 0xFF00) << 8)) << 8);
			v94++;
			v101++;
		}
	}

	if( in_data != NULL )
		delete[] in_data;

	m_isAlpha = 0;
	return true;
}


hook_func<bool (CBitmapRes::*)(const char* bitmap, int size)> CBitmapRes::_LoadTGAData("CBitmapRes::LoadTGAData");
bool CBitmapRes::LoadTGAData(const char* bitmap, int size)
{
	return (this->*_LoadTGAData)(bitmap, size);
}


hook_func<bool (CBitmapRes::*)(const char* bitmap, int size)> CBitmapRes::_LoadJPGData("CBitmapRes::LoadJPGData");
bool CBitmapRes::LoadJPGData(const char* bitmap, int size)
{
	return (this->*_LoadJPGData)(bitmap, size);
}
