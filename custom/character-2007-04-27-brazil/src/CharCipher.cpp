//http://en.wikipedia.org/wiki/CRYPTON
// The CRYPTON algorithm processes blocks of 128 bits in the form of 4×4 byte arrays. The round transformation
// consists of four steps: byte-wise substitution, column-wise bit permutation, column-to-row transposition
// and finally key addition. CRYPTON uses 12 rounds of this encryption process. Due to the algorithm's nature,
// the decryption process can be made identical to the encryption process using a different key.

//http://www.ussrback.com/crypto/aes/crypton/crypton2.c
// This is an independent implementation of the CRYPTON algorithm
// designed by Chae Hoon Lim of Future Systms Inc and submitted as
// a candidate for the NIST AES activity.
//
// Copyright in this implementation is held by Dr B R Gladman but
// I hereby give permission for its free direct or derivative use
// subject to acknowledgment of its origin and compliance with any
// conditions that the algorithm originators place on its use.
//
// Dr Brian Gladman (gladman@seven77.demon.co.uk) October 1998

typedef unsigned char u1byte;
typedef unsigned long u4byte;
#define byte(x, nr) ((unsigned char)((x) >> (nr*8)))
#define rotl32(x,n) (((x) << n) | ((x) >> (32 - n)))
#define rotr32(x,n) (((x) >> n) | ((x) << (32 - n)))
#define rotl rotl32
#define rotr rotr32

#define	gamma(x,p,q)								\
	(x) = (((u4byte)s_box[p][byte((x),0)]      ) |	\
	   	   ((u4byte)s_box[q][byte((x),1)] <<  8) |	\
		   ((u4byte)s_box[p][byte((x),2)] << 16) |	\
		   ((u4byte)s_box[q][byte((x),3)] << 24))

#define	gamma_tau(x,b,m,p,q)						\
	(x) = (((u4byte)s_box[p][byte(b[0],m)]      ) |	\
	  	   ((u4byte)s_box[q][byte(b[1],m)] <<  8) |	\
		   ((u4byte)s_box[p][byte(b[2],m)] << 16) |	\
		   ((u4byte)s_box[q][byte(b[3],m)] << 24))

#define	ma_0	0x3fcff3fc
#define	ma_1	0xfc3fcff3
#define	ma_2	0xf3fc3fcf
#define	ma_3	0xcff3fc3f

#define	mb_0	0xcffccffc
#define	mb_1	0xf33ff33f
#define	mb_2	0xfccffccf
#define	mb_3	0x3ff33ff3

#define	pi(b,n0,n1,n2,n3)		\
	(((b)[0] & ma_##n0) ^		\
	 ((b)[1] & ma_##n1) ^		\
     ((b)[2] & ma_##n2) ^		\
	 ((b)[3] & ma_##n3))

#define	phi_n(x,n0,n1,n2,n3)	\
	(     (x)      & mb_##n0) ^	\
	(rotl((x),  8) & mb_##n1) ^	\
	(rotl((x), 16) & mb_##n2) ^	\
	(rotl((x), 24) & mb_##n3)

#define	phi_00(x)	phi_n(x,0,1,2,3)
#define	phi_01(x)	phi_n(x,3,0,1,2)
#define	phi_02(x)	phi_n(x,2,3,0,1)
#define	phi_03(x)	phi_n(x,1,2,3,0)

#define	phi_10(x)	phi_n(x,3,0,1,2)
#define	phi_11(x)	phi_n(x,2,3,0,1)
#define	phi_12(x)	phi_n(x,1,2,3,0)
#define	phi_13(x)	phi_n(x,0,1,2,3)

#define	phi0(x,y)				\
	(y)[0] = phi_00((x)[0]);	\
	(y)[1] = phi_01((x)[1]);	\
	(y)[2] = phi_02((x)[2]);	\
	(y)[3] = phi_03((x)[3])

#define	phi1(x,y)				\
	(y)[0] = phi_10((x)[0]);	\
	(y)[1] = phi_11((x)[1]);	\
	(y)[2] = phi_12((x)[2]);	\
	(y)[3] = phi_13((x)[3])

u1byte p_box[3][16] = 
{	{ 15,  9,  6,  8,  9,  9,  4, 12,  6,  2,  6, 10,  1,  3,  5, 15 },
	{ 10, 15,  4,  7,  5,  2, 14,  6,  9,  3, 12,  8, 13,  1, 11,  0 },
	{  0,  4,  8,  4,  2, 15,  8, 13,  1,  1, 15,  7,  2, 11, 14, 15 }
};

u4byte	tab_gen = 0;
u1byte	s_box[2][256];
u4byte	s_tab[4][256];

u4byte l_key[104];
u4byte *e_key = l_key + 52;
u4byte *d_key = l_key;

void gen_tab(void)
{	u4byte	i, xl, xr, yl, yr;

	for(i = 0; i < 256; ++i)
	{
		xl = (i & 0xf0) >> 4; xr = i & 15;

		yr = xr ^ p_box[1][xl ^ p_box[0][xr]];
		yl = xl ^ p_box[0][xr] ^ p_box[2][yr];

		yr |= (yl << 4); s_box[0][i] = (u1byte)yr; s_box[1][yr] = (u1byte)i;

		xr = yr * 0x01010101; xl = i * 0x01010101;

		s_tab[0][ i] = xr & 0x3fcff3fc;
		s_tab[1][yr] = xl & 0xfc3fcff3;
		s_tab[2][ i] = xr & 0xf3fc3fcf;
		s_tab[3][yr] = xl & 0xcff3fc3f;
	}
};

/* initialise the key schedule from the user supplied key	*/

u4byte	kp[4] = { 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f };
u4byte	kq[4] = { 0x9b05688c, 0x1f83d9ab, 0x5be0cd19, 0xcbbb9d5d };

#define h0_block(n,r0,r1)							\
	e_key[4 * n +  8] = rotl(e_key[4 * n + 0], r0);	\
	e_key[4 * n +  9] = rc ^ e_key[4 * n + 1];		\
	e_key[4 * n + 10] = rotl(e_key[4 * n + 2], r1);	\
	e_key[4 * n + 11] = rc ^ e_key[4 * n + 3]

#define h1_block(n,r0,r1)							\
	e_key[4 * n +  8] = rc ^ e_key[4 * n + 0];		\
	e_key[4 * n +  9] = rotl(e_key[4 * n + 1], r0);	\
	e_key[4 * n + 10] = rc ^ e_key[4 * n + 2];		\
	e_key[4 * n + 11] = rotl(e_key[4 * n + 3], r1)

u4byte * crypton_set_key(const u4byte in_key[], const u4byte key_len)
{	u4byte	i, rc, t0, t1, tmp[4];

	if(!tab_gen)
	{
		gen_tab(); tab_gen = 1;
	}

	e_key[2] = e_key[3] = e_key[6] = e_key[7] = 0;

	switch((key_len + 63) / 64)
	{
	case 4: e_key[3] = in_key[6]; e_key[7] = in_key[7];
	case 3: e_key[2] = in_key[4]; e_key[6] = in_key[5];
	case 2: e_key[0] = in_key[0]; e_key[4] = in_key[1];
			e_key[1] = in_key[2]; e_key[5] = in_key[3];
	}

	tmp[0] = pi(e_key, 0, 1, 2, 3) ^ kp[0];
	tmp[1] = pi(e_key, 1, 2, 3, 0) ^ kp[1];
	tmp[2] = pi(e_key, 2, 3, 0, 1) ^ kp[2];
	tmp[3] = pi(e_key, 3, 0, 1, 2) ^ kp[3];
	
	gamma_tau(e_key[0], tmp, 0, 0, 1); 
	gamma_tau(e_key[1], tmp, 1, 1, 0);
	gamma_tau(e_key[2], tmp, 2, 0, 1); 
	gamma_tau(e_key[3], tmp, 3, 1, 0);

	tmp[0] = pi(e_key + 4, 1, 2, 3, 0) ^ kq[0]; 
	tmp[1] = pi(e_key + 4, 2, 3, 0, 1) ^ kq[1];
	tmp[2] = pi(e_key + 4, 3, 0, 1, 2) ^ kq[2]; 
	tmp[3] = pi(e_key + 4, 0, 1, 2, 3) ^ kq[3];

	gamma_tau(e_key[4], tmp, 0, 1, 0); 
	gamma_tau(e_key[5], tmp, 1, 0, 1);
	gamma_tau(e_key[6], tmp, 2, 1, 0); 
	gamma_tau(e_key[7], tmp, 3, 0, 1);

	t0 = e_key[0] ^ e_key[1] ^ e_key[2] ^ e_key[3];
	t1 = e_key[4] ^ e_key[5] ^ e_key[6] ^ e_key[7];
	
	e_key[0] ^= t1; e_key[1] ^= t1;
	e_key[2] ^= t1; e_key[3] ^= t1;
	e_key[4] ^= t0; e_key[5] ^= t0;
	e_key[6] ^= t0; e_key[7] ^= t0;

	rc = 0x01010101; 
	h0_block( 0,  8, 16); h1_block(1, 16, 24); rc <<= 1;
	h1_block( 2, 24,  8); h0_block(3,  8, 16); rc <<= 1;
	h0_block( 4, 16, 24); h1_block(5, 24,  8); rc <<= 1;
	h1_block( 6,  8, 16); h0_block(7, 16, 24); rc <<= 1;
	h0_block( 8, 24,  8); h1_block(9,  8, 16); rc <<= 1;
	h1_block(10, 16, 24);

	for(i = 0; i < 13; ++i)
	{
		if(i & 1)
		{
			phi0(e_key + 4 * i, d_key + 48 - 4 * i);
		}
		else
		{
			phi1(e_key + 4 * i, d_key + 48 - 4 * i);
		}
  }

	phi1(e_key + 48, e_key + 48);
	phi1(d_key + 48, d_key + 48);

	return l_key;
};

/* encrypt a block of text	*/

#define	fr0(i,k)									\
	b1[i] =	s_tab[ (i)         ][byte(b0[0],i)] ^	\
			s_tab[((i) + 1) & 3][byte(b0[1],i)] ^	\
			s_tab[((i) + 2) & 3][byte(b0[2],i)] ^	\
			s_tab[((i) + 3) & 3][byte(b0[3],i)]	^ (k)

#define	fr1(i,k)									\
	b0[i] =	s_tab[((i) + 1) & 3][byte(b1[0],i)] ^	\
			s_tab[((i) + 2) & 3][byte(b1[1],i)] ^	\
			s_tab[((i) + 3) & 3][byte(b1[2],i)] ^	\
			s_tab[(i)          ][byte(b1[3],i)]	^ (k)

#define	f0_rnd(kp)					\
	fr0(0,(kp)[0]); fr0(1,(kp)[1]);	\
	fr0(2,(kp)[2]); fr0(3,(kp)[3])

#define	f1_rnd(kp)					\
	fr1(0,(kp)[0]); fr1(1,(kp)[1]);	\
	fr1(2,(kp)[2]); fr1(3,(kp)[3])

void crypton_encrypt(const u4byte in_blk[4], u4byte out_blk[4])
{	u4byte	b0[4], b1[4];

	b0[0] = in_blk[0] ^ e_key[0];
	b0[1] = in_blk[1] ^ e_key[1];
	b0[2] = in_blk[2] ^ e_key[2];
	b0[3] = in_blk[3] ^ e_key[3];

	f0_rnd(e_key +  4); f1_rnd(e_key +  8);
	f0_rnd(e_key + 12); f1_rnd(e_key + 16);
	f0_rnd(e_key + 20); f1_rnd(e_key + 24);
	f0_rnd(e_key + 28); f1_rnd(e_key + 32);
	f0_rnd(e_key + 36); f1_rnd(e_key + 40);
	f0_rnd(e_key + 44);

	gamma_tau(b0[0], b1, 0, 1, 0); 
	gamma_tau(b0[1], b1, 1, 0, 1); 
	gamma_tau(b0[2], b1, 2, 1, 0); 
	gamma_tau(b0[3], b1, 3, 0, 1);

	out_blk[0] = b0[0] ^ e_key[48]; 
	out_blk[1] = b0[1] ^ e_key[49];
	out_blk[2] = b0[2] ^ e_key[50]; 
	out_blk[3] = b0[3] ^ e_key[51];
};

/* decrypt a block of text	*/

void crypton_decrypt(const u4byte in_blk[4], u4byte out_blk[4])
{	u4byte	b0[4], b1[4];

	b0[0] = in_blk[0] ^ d_key[0];
	b0[1] = in_blk[1] ^ d_key[1];
	b0[2] = in_blk[2] ^ d_key[2];
	b0[3] = in_blk[3] ^ d_key[3];

	f0_rnd(d_key +  4); f1_rnd(d_key +  8);
	f0_rnd(d_key + 12); f1_rnd(d_key + 16);
	f0_rnd(d_key + 20); f1_rnd(d_key + 24);
	f0_rnd(d_key + 28); f1_rnd(d_key + 32);
	f0_rnd(d_key + 36); f1_rnd(d_key + 40);
	f0_rnd(d_key + 44);

	gamma_tau(b0[0], b1, 0, 1, 0); 
	gamma_tau(b0[1], b1, 1, 0, 1); 
	gamma_tau(b0[2], b1, 2, 1, 0); 
	gamma_tau(b0[3], b1, 3, 0, 1);
	
	out_blk[0] = b0[0] ^ d_key[48]; 
	out_blk[1] = b0[1] ^ d_key[49];
	out_blk[2] = b0[2] ^ d_key[50]; 
	out_blk[3] = b0[3] ^ d_key[51];
};
