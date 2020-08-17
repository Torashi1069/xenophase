// from http://int64.svn.sourceforge.net/viewvc/int64/snips/sfmt.hpp

#ifndef SFMT_CPP_SSE2_HPP
#define SFMT_CPP_SSE2_HPP

/*
	SFMT C++ random number generator, for SSE2.
	Copyright (c) 2007 Cory Nelson

	Based on C SFMT 1.3 code.
	Copyright (c) 2006,2007 Mutsuo Saito, Makoto Matsumoto and Hiroshima
	University. All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are
	met:

	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above
	  copyright notice, this list of conditions and the following
	  disclaimer in the documentation and/or other materials provided
	  with the distribution.
	* Neither the name of the Hiroshima University nor the names of
	  its contributors may be used to endorse or promote products
	  derived from this software without specific prior written
	  permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <cstddef>
#include <new>
#include <emmintrin.h>

#ifdef _MSC_VER
// in VC++, use _aligned_malloc() and _aligned_free
#include <malloc.h>
#else
// otherwise assume POSIX and use posix_memalign
#include <cstdlib>
#endif

template<unsigned int MEXP, unsigned int POS1, int SL1, int SL2, int SR1, int SR2, unsigned int MSK1, unsigned int MSK2, unsigned int MSK3, unsigned int MSK4, unsigned int PARITY1, unsigned int PARITY2, unsigned int PARITY3, unsigned int PARITY4>
class sfmt_generator {
public:
	static const unsigned int N = (MEXP / 128 + 1);
	static const unsigned int N32 = (N * 4);
	static const unsigned int N64 = (N * 2);

	sfmt_generator() {
		parity[0] = PARITY1;
		parity[1] = PARITY2;
		parity[2] = PARITY3;
		parity[3] = PARITY4;

#ifdef _MSC_VER
		sfmt = (__m128i*)_aligned_malloc(sizeof(__m128i) * N, 16);
		if(!sfmt) throw std::bad_alloc();
#else
		if(posix_memalign((void**)&sfmt, 16, sizeof(__m128i) * N)) {
			throw std::bad_alloc();
		}
#endif
	}

	~sfmt_generator() {
#ifdef _MSC_VER
		_aligned_free((void*)sfmt);
#else
		free((void*)sfmt);
#endif
	}
	
	void seed(unsigned int seed) {
		unsigned int *psfmt32 = (unsigned int*)sfmt;
		unsigned int i;

		psfmt32[0] = seed;
		for (i = 1; i < N32; i++) {
			psfmt32[i] = 1812433253UL * (psfmt32[i - 1] ^ (psfmt32[i - 1] >> 30)) + i;
		}

		idx = N32;
		period_certification();
	}

	void seed(unsigned int *init_key, unsigned int key_length) {
		unsigned int *psfmt32 = (unsigned int*)sfmt;
		unsigned int i, j, count;
		unsigned int r;
		unsigned int lag;
		unsigned int mid;
		unsigned int size = N * 4;

		if (size >= 623) {
			lag = 11;
		}
		else if (size >= 68) {
			lag = 7;
		}
		else if (size >= 39) {
			lag = 5;
		}
		else {
			lag = 3;
		}
		mid = (size - lag) / 2u;

		memset(sfmt, 0x8b, sizeof(sfmt));
		if (key_length + 1 > N32) {
			count = key_length + 1;
		}
		else {
			count = N32;
		}
		r = func1(psfmt32[0] ^ psfmt32[mid] ^ psfmt32[N32 - 1]);
		psfmt32[mid] += r;
		r += key_length;
		psfmt32[mid + lag] += r;
		psfmt32[0] = r;

		count--;
		for (i = 1, j = 0; (j < count) && (j < key_length); j++) {
			r = func1(psfmt32[i] ^ psfmt32[(i + mid) % N32] ^ psfmt32[(i + N32 - 1) % N32]);
			psfmt32[(i + mid) % N32] += r;
			r += init_key[j] + i;
			psfmt32[(i + mid + lag) % N32] += r;
			psfmt32[i] = r;
			i = (i + 1) % N32;
		}
		for (; j < count; j++) {
			r = func1(psfmt32[i] ^ psfmt32[(i + mid) % N32] ^ psfmt32[(i + N32 - 1) % N32]);
			psfmt32[(i + mid) % N32] += r;
			r += i;
			psfmt32[(i + mid + lag) % N32] += r;
			psfmt32[i] = r;
			i = (i + 1) % N32;
		}
		for (j = 0; j < N32; j++) {
			r = func2(psfmt32[i] + psfmt32[(i + mid) % N32] + psfmt32[(i + N32 - 1) % N32]);
			psfmt32[(i + mid) % N32] ^= r;
			r -= i;
			psfmt32[(i + mid + lag) % N32] ^= r;
			psfmt32[i] = r;
			i = (i + 1) % N32;
		}

		idx = N32;
		period_certification();
	}

	unsigned int rand32() {
		unsigned int *psfmt32 = (unsigned int*)sfmt;
		unsigned int r;

		if (idx >= N32) {
			gen_rand_all();
			idx = 0;
		}

		r = psfmt32[idx++];
		return r;
	}
	
	unsigned __int64 rand64() {
		unsigned __int64 *psfmt64 = (unsigned __int64*)sfmt;
		unsigned __int64 r;

		if (idx >= N32) {
			gen_rand_all();
			idx = 0;
		}

		r = psfmt64[idx / 2];
		idx += 2;

		return r;
	}

	// [0,1]
	double drand1() { return rand32() * (1.0 / 4294967295.0); }

	// [0,1)
	double drand2() { return rand32() * (1.0 / 4294967296.0); }

	// (0,1)
	double drand3() { return (rand32() + 0.5) * (1.0 / 4294967295.0); }

	// [0,1), with 53-bit res.
	double drand53() { return rand64() * (1.0 / 18446744073709551616.0L); }

	// array must be 16-byte aligned
	// size must be >= N32, and a multiple of 4.
	void rand(unsigned int *array, unsigned int size) {
		gen_rand_array((__m128i*)array, size / 4);
		idx = N32;
	}

	// array must be 16-byte aligned
	// size must be >= N64, and a multiple of 2.
	void rand(unsigned __int64 *array, unsigned int size) {
		gen_rand_array((__m128i*)array, size / 2);
		idx = N32;
	}

private:
	static __m128i mm_recursion(__m128i *a, __m128i *b, __m128i c, __m128i d, __m128i mask) {
		 __m128i v, x, y, z;
	    
		 x = _mm_load_si128(a);
		 y = _mm_srli_epi32(_mm_load_si128(b), SR1);
		 z = _mm_srli_si128(c, SR2);
		 v = _mm_slli_epi32(d, SL1);
		 z = _mm_xor_si128(z, x);
		 z = _mm_xor_si128(z, v);
		 x = _mm_slli_si128(x, SL2);
		 y = _mm_and_si128(y, mask);
		 z = _mm_xor_si128(z, x);
		 z = _mm_xor_si128(z, y);

		 return z;
	}

	void gen_rand_all(void) {
		int i;
		__m128i r, r1, r2, mask;
		
		mask = _mm_set_epi32(MSK4, MSK3, MSK2, MSK1);
		r1 = _mm_load_si128(&sfmt[N - 2]);
		r2 = _mm_load_si128(&sfmt[N - 1]);

		for (i = 0; i < N - POS1; i++) {
			r = mm_recursion(&sfmt[i], &sfmt[i + POS1], r1, r2, mask);
			_mm_store_si128(&sfmt[i], r);
			r1 = r2;
			r2 = r;
		}

		for (; i < N; i++) {
			r = mm_recursion(&sfmt[i], &sfmt[i + POS1 - N], r1, r2, mask);
			_mm_store_si128(&sfmt[i], r);
			r1 = r2;
			r2 = r;
		}
	}

	void gen_rand_array(__m128i *array, unsigned int size) {
		unsigned int i, j;
		__m128i r, r1, r2, mask;

		mask = _mm_set_epi32(MSK4, MSK3, MSK2, MSK1);
		r1 = _mm_load_si128(&sfmt[N - 2]);
		r2 = _mm_load_si128(&sfmt[N - 1]);

		for (i = 0; i < N - POS1; i++) {
			r = mm_recursion(&sfmt[i], &sfmt[i + POS1], r1, r2, mask);
			_mm_store_si128(&array[i], r);
			r1 = r2;
			r2 = r;
		}

		for (; i < N; i++) {
			r = mm_recursion(&sfmt[i], &array[i + POS1 - N], r1, r2, mask);
			_mm_store_si128(&array[i], r);
			r1 = r2;
			r2 = r;
		}

		for (; i < size - N; i++) {
			r = mm_recursion(&array[i - N], &array[i + POS1 - N], r1, r2, mask);
			_mm_store_si128(&array[i], r);
			r1 = r2;
			r2 = r;
		}

		for (j = 0; j < 2 * N - size; j++) {
			r = _mm_load_si128(&array[j + size - N]);
			_mm_store_si128(&sfmt[j], r);
		}

		for (; i < size; i++) {
			r = mm_recursion(&array[i - N], &array[i + POS1 - N], r1, r2, mask);
			_mm_store_si128(&array[i], r);
			_mm_store_si128(&sfmt[j++], r);
			r1 = r2;
			r2 = r;
		}
	}

	static unsigned int func1(unsigned int x) {
		return (x ^ (x >> 27)) * 1664525UL;
	}

	static unsigned int func2(unsigned int x) {
		return (x ^ (x >> 27)) * 1566083941UL;
	}

	void period_certification(void) {
		unsigned int *psfmt32 = (unsigned int*)sfmt;
		unsigned int inner = 0;
		unsigned int i, j;
		unsigned int work;

		for (i = 0; i < 4; i++) {
			inner ^= psfmt32[i] & parity[i];
		}
		for (i = 16; i > 0; i >>= 1) {
			inner ^= inner >> i;
		}
		inner &= 1;
		/* check OK */
		if (inner == 1) {
			return;
		}
		/* check NG, and modification */
		for (i = 0; i < 4; i++) {
			work = 1;
			for (j = 0; j < 32; j++) {
				if ((work & parity[i]) != 0) {
					psfmt32[i] ^= work;
					return;
				}
				work = work << 1;
			}
		}
	}

	__m128i *sfmt;

	unsigned int idx;
	unsigned int parity[4];
};

typedef sfmt_generator<607,2,15,3,13,3,0xfdff37ffU,0xef7f3f7dU,0xff777b7dU,0x7ff7fb2fU,0x00000001U,0x00000000U,0x00000000U,0x5986f054U> sfmt_607_generator;
typedef sfmt_generator<1279,7,14,3,5,1,0xf7fefffdU,0x7fefcfffU,0xaff3ef3fU,0xb5ffff7fU,0x00000001U,0x00000000U,0x00000000U,0x20000000U> sfmt_1279_generator;
typedef sfmt_generator<2281,12,19,1,5,1,0xbff7ffbfU,0xfdfffffeU,0xf7ffef7fU,0xf2f7cbbfU,0x00000001U,0x00000000U,0x00000000U,0x41dfa600U> sfmt_2281_generator;
typedef sfmt_generator<4253,17,20,1,7,1,0x9f7bffffU,0x9fffff5fU,0x3efffffbU,0xfffff7bbU,0xa8000001U,0xaf5390a3U,0xb740b3f8U,0x6c11486dU> sfmt_4253_generator;
typedef sfmt_generator<11213,68,14,3,7,3,0xeffff7fbU,0xffffffefU,0xdfdfbfffU,0x7fffdbfdU,0x00000001U,0x00000000U,0xe8148000U,0xd0c7afa3U> sfmt_11213_generator;
typedef sfmt_generator<19937,122,18,1,11,1,0xdfffffefU,0xddfecb7fU,0xbffaffffU,0xbffffff6U,0x00000001U,0x00000000U,0x00000000U,0xc98e126aU> sfmt_19937_generator;
typedef sfmt_generator<44497,330,5,3,9,3,0xeffffffbU,0xdfbebfffU,0xbfbf7befU,0x9ffd7bffU,0x00000001U,0x00000000U,0xa3ac4000U,0xecc1327aU> sfmt_44497_generator;
typedef sfmt_generator<86243,366,6,7,19,1,0xfdbffbffU,0xbff7ff3fU,0xfd77efffU,0xbf9ff3ffU,0x00000001U,0x00000000U,0x00000000U,0xe9528d85U> sfmt_86243_generator;
typedef sfmt_generator<132049,110,19,1,21,1,0xffffbb5fU,0xfb6ebf95U,0xfffefffaU,0xcff77fffU,0x00000001U,0x00000000U,0xcb520000U,0xc7e91c7dU> sfmt_132049_generator;
typedef sfmt_generator<216091,627,11,3,10,1,0xbff7bff7U,0xbfffffffU,0xbffffa7fU,0xffddfbfbU,0xf8000001U,0x89e80709U,0x3bd2b64bU,0x0c64b1e4U> sfmt_216091_generator;

#endif
