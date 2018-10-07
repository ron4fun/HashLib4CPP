// ///////////////////////////////////////////////////////////////// //
// *C++ 11 HashFactory Library                                 
// *Copyright(c) 2018  Mbadiwe Nnaemeka Ronald                 
// *Github Repository <https://github.com/ron4fun>             

// *Distributed under the MIT soTware license, see the accompanying file LICENSE 
// *or visit http ://www.opensource.org/licenses/mit-license.php.           

// *Acknowledgements:                                  
// ** //
// *Thanks to Ugochukwu Mmaduekwe (https://github.com/^-el) for his creative        
// *development of this library in Pascal/Delphi                         

// ////////////////////////////////////////////////////// ///////////////

#ifndef HLPGOST3411_2012_H
#define HLPGOST3411_2012_H

#include "../Base/HlpHashCryptoNotBuildIn.h"
#include "../Base/HlpHashSize.h"
#include "../Utils/HlpUtils.h"


class GOST3411_2012 : public Hash, public IICryptoNotBuildIn, public IITransformBlock
{
public:
	virtual void Initialize()
	{
		bOff = 64;
		
		memset(&N[0], 0, N.size() * sizeof(uint8_t));
		memset(&Sigma[0], 0, Sigma.size() * sizeof(uint8_t));

		memmove(&h[0], &IV[0], 64 * sizeof(uint8_t));

		memset(&block[0], 0, block.size() * sizeof(uint8_t));

	} // end function Initialize

	virtual void TransformBytes(const HashLibByteArray &a_data, const int32_t _a_index, const int32_t _a_data_length)
	{
		int32_t a_index = _a_index, a_data_length = _a_data_length;

		while ((bOff != 64) && (a_data_length > 0))
		{
			InternalUpdate(a_data[a_index]);
			a_index++;
			a_data_length--;
		}

		while (a_data_length >= 64)
		{
			memmove(&tmp[0], &a_data[a_index], 64 * sizeof(uint8_t));
			reverse(tmp, block);
			g_N(h, N, block);
			addMod512(N, 512);
			addMod512(Sigma, block);

			a_data_length = a_data_length - 64;
			a_index = a_index + 64;
		}

		while (a_data_length > 0)
		{
			InternalUpdate(a_data[a_index]);
			a_index++;
			a_data_length--;
		}
		
	}

	virtual IHashResult TransformFinal()
	{
		HashLibByteArray tempRes;
		size_t lenM, i;

		lenM = 64 - bOff;

		// At this point it is certain that lenM is smaller than 64
		i = 0;
		while (i != (64 - lenM))
		{
			m[i] = 0;
			i++;
		}

		m[63 - lenM] = 1;

		if (bOff != 64) memmove(&m[64 - lenM], &block[bOff], lenM * sizeof(uint8_t));
		
		g_N(h, N, m);
		addMod512(N, lenM * 8);
		addMod512(Sigma, m);
		g_N(h, Zero, N);
		g_N(h, Zero, Sigma);

		reverse(h, tmp);

		tempRes.resize(64);
		memmove(&tempRes[0], &tmp[0], 64 * sizeof(uint8_t));

		IHashResult result = make_shared<HashResult>(tempRes);

		Initialize();

		return result;
	}

protected:
	GOST3411_2012(const int32_t a_hash_size, const HashLibByteArray &_IV)
		: Hash(a_hash_size, 64)
	{
		IV.resize(64);
		N.resize(64);
		Sigma.resize(64);
		Ki.resize(64);
		m.resize(64);
		h.resize(64);

		// Temporary buffers
		tmp.resize(64);
		block.resize(64);

		bOff = 64;

		memmove(&IV[0], &_IV[0], 64 * sizeof(uint8_t));
		memmove(&h[0], &_IV[0], 64 * sizeof(uint8_t));
	} // end constructor

private:
	static HashLibByteArray Zero;
	static HashLibMatrixByteArray C;
	static HashLibMatrixUInt64Array T;

	inline void InternalUpdate(const uint8_t input)
	{
		bOff--;
		block[bOff] = input;

		if (bOff == 0)
		{
			g_N(h, N, block);
			addMod512(N, 512);
			addMod512(Sigma, block);
			bOff = 64;
		}

	}

	static inline void xor512(HashLibByteArray &A, const HashLibByteArray &B)
	{
		register uint32_t i = 0;
		for (; i < 64; i++) A[i] = A[i] ^ B[i];
	}

	void E(HashLibByteArray &K, const HashLibByteArray &a_m)
	{
		int32_t i;
		
		memmove(&Ki[0], &K[0], 64 * sizeof(uint8_t));
		xor512(K, a_m);
		F(K);

		for (i = 0; i < 11; i++)
		{
			xor512(Ki, C[i]);
			F(Ki);
			xor512(K, Ki);
			F(K);
		}

		xor512(Ki, C[11]);
		F(Ki);
		xor512(K, Ki);
	}

	static void F(HashLibByteArray &V)
	{
		uint64_t * res = new uint64_t[8];
		uint64_t r;
		
		r = 0;
		r = r ^ (T[0][(V[56] & 0xFF)]);
		r = r ^ (T[1][(V[48] & 0xFF)]);
		r = r ^ (T[2][(V[40] & 0xFF)]);
		r = r ^ (T[3][(V[32] & 0xFF)]);
		r = r ^ (T[4][(V[24] & 0xFF)]);
		r = r ^ (T[5][(V[16] & 0xFF)]);
		r = r ^ (T[6][(V[8] & 0xFF)]);
		r = r ^ (T[7][(V[0] & 0xFF)]);
		res[0] = r;

		r = 0;
		r = r ^ (T[0][(V[57] & 0xFF)]);
		r = r ^ (T[1][(V[49] & 0xFF)]);
		r = r ^ (T[2][(V[41] & 0xFF)]);
		r = r ^ (T[3][(V[33] & 0xFF)]);
		r = r ^ (T[4][(V[25] & 0xFF)]);
		r = r ^ (T[5][(V[17] & 0xFF)]);
		r = r ^ (T[6][(V[9] & 0xFF)]);
		r = r ^ (T[7][(V[1] & 0xFF)]);
		res[1] = r;

		r = 0;
		r = r ^ (T[0][(V[58] & 0xFF)]);
		r = r ^ (T[1][(V[50] & 0xFF)]);
		r = r ^ (T[2][(V[42] & 0xFF)]);
		r = r ^ (T[3][(V[34] & 0xFF)]);
		r = r ^ (T[4][(V[26] & 0xFF)]);
		r = r ^ (T[5][(V[18] & 0xFF)]);
		r = r ^ (T[6][(V[10] & 0xFF)]);
		r = r ^ (T[7][(V[2] & 0xFF)]);
		res[2] = r;

		r = 0;
		r = r ^ (T[0][(V[59] & 0xFF)]);
		r = r ^ (T[1][(V[51] & 0xFF)]);
		r = r ^ (T[2][(V[43] & 0xFF)]);
		r = r ^ (T[3][(V[35] & 0xFF)]);
		r = r ^ (T[4][(V[27] & 0xFF)]);
		r = r ^ (T[5][(V[19] & 0xFF)]);
		r = r ^ (T[6][(V[11] & 0xFF)]);
		r = r ^ (T[7][(V[3] & 0xFF)]);
		res[3] = r;

		r = 0;
		r = r ^ (T[0][(V[60] & 0xFF)]);
		r = r ^ (T[1][(V[52] & 0xFF)]);
		r = r ^ (T[2][(V[44] & 0xFF)]);
		r = r ^ (T[3][(V[36] & 0xFF)]);
		r = r ^ (T[4][(V[28] & 0xFF)]);
		r = r ^ (T[5][(V[20] & 0xFF)]);
		r = r ^ (T[6][(V[12] & 0xFF)]);
		r = r ^ (T[7][(V[4] & 0xFF)]);
		res[4] = r;

		r = 0;
		r = r ^ (T[0][(V[61] & 0xFF)]);
		r = r ^ (T[1][(V[53] & 0xFF)]);
		r = r ^ (T[2][(V[45] & 0xFF)]);
		r = r ^ (T[3][(V[37] & 0xFF)]);
		r = r ^ (T[4][(V[29] & 0xFF)]);
		r = r ^ (T[5][(V[21] & 0xFF)]);
		r = r ^ (T[6][(V[13] & 0xFF)]);
		r = r ^ (T[7][(V[5] & 0xFF)]);
		res[5] = r;

		r = 0;
		r = r ^ (T[0][(V[62] & 0xFF)]);
		r = r ^ (T[1][(V[54] & 0xFF)]);
		r = r ^ (T[2][(V[46] & 0xFF)]);
		r = r ^ (T[3][(V[38] & 0xFF)]);
		r = r ^ (T[4][(V[30] & 0xFF)]);
		r = r ^ (T[5][(V[22] & 0xFF)]);
		r = r ^ (T[6][(V[14] & 0xFF)]);
		r = r ^ (T[7][(V[6] & 0xFF)]);
		res[6] = r;

		r = 0;
		r = r ^ (T[0][(V[63] & 0xFF)]);
		r = r ^ (T[1][(V[55] & 0xFF)]);
		r = r ^ (T[2][(V[47] & 0xFF)]);
		r = r ^ (T[3][(V[39] & 0xFF)]);
		r = r ^ (T[4][(V[31] & 0xFF)]);
		r = r ^ (T[5][(V[23] & 0xFF)]);
		r = r ^ (T[6][(V[15] & 0xFF)]);
		r = r ^ (T[7][(V[7] & 0xFF)]);
		res[7] = r;

		r = res[0];
		V[7] = uint8_t(r >> 56);
		V[6]  = uint8_t(r >> 48);
		V[5] = uint8_t(r >> 40);
		V[4] = uint8_t(r >> 32);
		V[3] = uint8_t(r >> 24);
		V[2] = uint8_t(r >> 16);
		V[1] = uint8_t(r >> 8);
		V[0] = uint8_t(r);

		r = res[1];
		V[15] = uint8_t(r >> 56);
		V[14] = uint8_t(r >> 48);
		V[13] = uint8_t(r >> 40);
		V[12] = uint8_t(r >> 32);
		V[11] = uint8_t(r >> 24);
		V[10] = uint8_t(r >> 16);
		V[9] = uint8_t(r >> 8);
		V[8] = uint8_t(r);

		r = res[2];
		V[23] = uint8_t(r >> 56);
		V[22] = uint8_t(r >> 48);
		V[21] = uint8_t(r >> 40);
		V[20] = uint8_t(r >> 32);
		V[19] = uint8_t(r >> 24);
		V[18] = uint8_t(r >> 16);
		V[17] = uint8_t(r >> 8);
		V[16] = uint8_t(r);

		r = res[3];
		V[31] = uint8_t(r >> 56);
		V[30] = uint8_t(r >> 48);
		V[29] = uint8_t(r >> 40);
		V[28] = uint8_t(r >> 32);
		V[27] = uint8_t(r >> 24);
		V[26] = uint8_t(r >> 16);
		V[25] = uint8_t(r >> 8);
		V[24] = uint8_t(r);

		r = res[4];
		V[39] = uint8_t(r >> 56);
		V[38] = uint8_t(r >> 48);
		V[37] = uint8_t(r >> 40);
		V[36] = uint8_t(r >> 32);
		V[35] = uint8_t(r >> 24);
		V[34] = uint8_t(r >> 16);
		V[33] = uint8_t(r >> 8);
		V[32] = uint8_t(r);

		r = res[5];
		V[47] = uint8_t(r >> 56);
		V[46] = uint8_t(r >> 48);
		V[45] = uint8_t(r >> 40);
		V[44] = uint8_t(r >> 32);
		V[43] = uint8_t(r >> 24);
		V[42] = uint8_t(r >> 16);
		V[41] = uint8_t(r >> 8);
		V[40] = uint8_t(r);

		r = res[6];
		V[55] = uint8_t(r >> 56);
		V[54] = uint8_t(r >> 48);
		V[53] = uint8_t(r >> 40);
		V[52] = uint8_t(r >> 32);
		V[51] = uint8_t(r >> 24);
		V[50] = uint8_t(r >> 16);
		V[49] = uint8_t(r >> 8);
		V[48] = uint8_t(r);

		r = res[7];
		V[63] = uint8_t(r >> 56);
		V[62] = uint8_t(r >> 48);
		V[61] = uint8_t(r >> 40);
		V[60] = uint8_t(r >> 32);
		V[59] = uint8_t(r >> 24);
		V[58] = uint8_t(r >> 16);
		V[57] = uint8_t(r >> 8);
		V[56] = uint8_t(r);

		memset(res, uint64_t(0), sizeof(res));
		delete[] res;
	}

	inline void g_N(HashLibByteArray &a_h, HashLibByteArray &a_N, HashLibByteArray &a_m)
	{
		memmove(&tmp[0], &a_h[0], 64 * sizeof(uint8_t));

		xor512(a_h, a_N);
		F(a_h);

		E(a_h, a_m);
		xor512(a_h, tmp);
		xor512(a_h, a_m);
	}

	static void addMod512(HashLibByteArray &A, const int32_t num) 
	{
		int32_t c, i;
		
		c = (A[63] & 0xFF) + (num & 0xFF);
		A[63] = uint8_t(c);

		c = (A[62] & 0xFF) + ((Bits::Asr32(num, 8)) & 0xFF) + (Bits::Asr32(c, 8));
		A[62] = uint8_t(c);

		i = 61;
		while ((i >= 0) && (c > 0))
		{
			c = (A[i] & 0xFF) + (Bits::Asr32(c, 8));
			A[i] = uint8_t(c);
			i--;
		}

	}

	static void addMod512(HashLibByteArray &A, const HashLibByteArray &B)
	{
		int32_t i, c;
		
		c = 0;
		i = 63;

		while (i >= 0)
		{
			c = int32_t(A[i] & 0xFF) + int32_t(B[i] & 0xFF) + (Bits::Asr32(c, 8));
			A[i] = uint8_t(c);
			i--;
		}

	}

	static void reverse(const HashLibByteArray &src, HashLibByteArray &dst)
	{
		register size_t len, i;

		len = src.size();
		for (i = 0; i < len; i++) dst[len - 1 - i] = src[i];
	}

protected:
	HashLibByteArray IV, N, Sigma, Ki, m, h, tmp, block;
	int32_t bOff;

}; // end class GOST3411_2012

HashLibMatrixByteArray GOST3411_2012::C = HashLibMatrixByteArray({ HashLibByteArray({uint8_t(0xB1),
	uint8_t(0x08), uint8_t(0x5B), uint8_t(0xDA), uint8_t(0x1E), uint8_t(0xCA), uint8_t(0xDA), uint8_t(0xE9),
	uint8_t(0xEB), uint8_t(0xCB), uint8_t(0x2F), uint8_t(0x81), uint8_t(0xC0), uint8_t(0x65), uint8_t(0x7C),
	uint8_t(0x1F), uint8_t(0x2F), uint8_t(0x6A), uint8_t(0x76), uint8_t(0x43), uint8_t(0x2E), uint8_t(0x45),
	uint8_t(0xD0), uint8_t(0x16), uint8_t(0x71), uint8_t(0x4E), uint8_t(0xB8), uint8_t(0x8D), uint8_t(0x75),
	uint8_t(0x85), uint8_t(0xC4), uint8_t(0xFC), uint8_t(0x4B), uint8_t(0x7C), uint8_t(0xE0), uint8_t(0x91),
	uint8_t(0x92), uint8_t(0x67), uint8_t(0x69), uint8_t(0x01), uint8_t(0xA2), uint8_t(0x42), uint8_t(0x2A),
	uint8_t(0x08), uint8_t(0xA4), uint8_t(0x60), uint8_t(0xD3), uint8_t(0x15), uint8_t(0x05), uint8_t(0x76),
	uint8_t(0x74), uint8_t(0x36), uint8_t(0xCC), uint8_t(0x74), uint8_t(0x4D), uint8_t(0x23), uint8_t(0xDD),
	uint8_t(0x80), uint8_t(0x65), uint8_t(0x59), uint8_t(0xF2), uint8_t(0xA6), uint8_t(0x45),
	uint8_t(0x07)}),

	HashLibByteArray({uint8_t(0x6F), uint8_t(0xA3), uint8_t(0xB5), uint8_t(0x8A),
		uint8_t(0xA9), uint8_t(0x9D), uint8_t(0x2F), uint8_t(0x1A), uint8_t(0x4F), uint8_t(0xE3), uint8_t(0x9D),
		uint8_t(0x46), uint8_t(0x0F), uint8_t(0x70), uint8_t(0xB5), uint8_t(0xD7), uint8_t(0xF3), uint8_t(0xFE),
		uint8_t(0xEA), uint8_t(0x72), uint8_t(0x0A), uint8_t(0x23), uint8_t(0x2B), uint8_t(0x98), uint8_t(0x61),
		uint8_t(0xD5), uint8_t(0x5E), uint8_t(0x0F), uint8_t(0x16), uint8_t(0xB5), uint8_t(0x01), uint8_t(0x31),
		uint8_t(0x9A), uint8_t(0xB5), uint8_t(0x17), uint8_t(0x6B), uint8_t(0x12), uint8_t(0xD6), uint8_t(0x99),
		uint8_t(0x58), uint8_t(0x5C), uint8_t(0xB5), uint8_t(0x61), uint8_t(0xC2), uint8_t(0xDB), uint8_t(0x0A),
		uint8_t(0xA7), uint8_t(0xCA), uint8_t(0x55), uint8_t(0xDD), uint8_t(0xA2), uint8_t(0x1B), uint8_t(0xD7),
		uint8_t(0xCB), uint8_t(0xCD), uint8_t(0x56), uint8_t(0xE6), uint8_t(0x79), uint8_t(0x04), uint8_t(0x70),
		uint8_t(0x21), uint8_t(0xB1), uint8_t(0x9B), uint8_t(0xB7)}),

	HashLibByteArray({uint8_t(0xF5), uint8_t(0x74), uint8_t(0xDC), uint8_t(0xAC),
		uint8_t(0x2B), uint8_t(0xCE), uint8_t(0x2F), uint8_t(0xC7), uint8_t(0x0A), uint8_t(0x39), uint8_t(0xFC),
		uint8_t(0x28), uint8_t(0x6A), uint8_t(0x3D), uint8_t(0x84), uint8_t(0x35), uint8_t(0x06), uint8_t(0xF1),
		uint8_t(0x5E), uint8_t(0x5F), uint8_t(0x52), uint8_t(0x9C), uint8_t(0x1F), uint8_t(0x8B), uint8_t(0xF2),
		uint8_t(0xEA), uint8_t(0x75), uint8_t(0x14), uint8_t(0xB1), uint8_t(0x29), uint8_t(0x7B), uint8_t(0x7B),
		uint8_t(0xD3), uint8_t(0xE2), uint8_t(0x0F), uint8_t(0xE4), uint8_t(0x90), uint8_t(0x35), uint8_t(0x9E),
		uint8_t(0xB1), uint8_t(0xC1), uint8_t(0xC9), uint8_t(0x3A), uint8_t(0x37), uint8_t(0x60), uint8_t(0x62),
		uint8_t(0xDB), uint8_t(0x09), uint8_t(0xC2), uint8_t(0xB6), uint8_t(0xF4), uint8_t(0x43), uint8_t(0x86),
		uint8_t(0x7A), uint8_t(0xDB), uint8_t(0x31), uint8_t(0x99), uint8_t(0x1E), uint8_t(0x96), uint8_t(0xF5),
		uint8_t(0x0A), uint8_t(0xBA), uint8_t(0x0A), uint8_t(0xB2)}),

	HashLibByteArray({uint8_t(0xEF), uint8_t(0x1F), uint8_t(0xDF), uint8_t(0xB3),
		uint8_t(0xE8), uint8_t(0x15), uint8_t(0x66), uint8_t(0xD2), uint8_t(0xF9), uint8_t(0x48), uint8_t(0xE1),
		uint8_t(0xA0), uint8_t(0x5D), uint8_t(0x71), uint8_t(0xE4), uint8_t(0xDD), uint8_t(0x48), uint8_t(0x8E),
		uint8_t(0x85), uint8_t(0x7E), uint8_t(0x33), uint8_t(0x5C), uint8_t(0x3C), uint8_t(0x7D), uint8_t(0x9D),
		uint8_t(0x72), uint8_t(0x1C), uint8_t(0xAD), uint8_t(0x68), uint8_t(0x5E), uint8_t(0x35), uint8_t(0x3F),
		uint8_t(0xA9), uint8_t(0xD7), uint8_t(0x2C), uint8_t(0x82), uint8_t(0xED), uint8_t(0x03), uint8_t(0xD6),
		uint8_t(0x75), uint8_t(0xD8), uint8_t(0xB7), uint8_t(0x13), uint8_t(0x33), uint8_t(0x93), uint8_t(0x52),
		uint8_t(0x03), uint8_t(0xBE), uint8_t(0x34), uint8_t(0x53), uint8_t(0xEA), uint8_t(0xA1), uint8_t(0x93),
		uint8_t(0xE8), uint8_t(0x37), uint8_t(0xF1), uint8_t(0x22), uint8_t(0x0C), uint8_t(0xBE), uint8_t(0xBC),
		uint8_t(0x84), uint8_t(0xE3), uint8_t(0xD1), uint8_t(0x2E)}),

	HashLibByteArray({uint8_t(0x4B), uint8_t(0xEA), uint8_t(0x6B), uint8_t(0xAC),
		uint8_t(0xAD), uint8_t(0x47), uint8_t(0x47), uint8_t(0x99), uint8_t(0x9A), uint8_t(0x3F), uint8_t(0x41),
		uint8_t(0x0C), uint8_t(0x6C), uint8_t(0xA9), uint8_t(0x23), uint8_t(0x63), uint8_t(0x7F), uint8_t(0x15),
		uint8_t(0x1C), uint8_t(0x1F), uint8_t(0x16), uint8_t(0x86), uint8_t(0x10), uint8_t(0x4A), uint8_t(0x35),
		uint8_t(0x9E), uint8_t(0x35), uint8_t(0xD7), uint8_t(0x80), uint8_t(0x0F), uint8_t(0xFF), uint8_t(0xBD),
		uint8_t(0xBF), uint8_t(0xCD), uint8_t(0x17), uint8_t(0x47), uint8_t(0x25), uint8_t(0x3A), uint8_t(0xF5),
		uint8_t(0xA3), uint8_t(0xDF), uint8_t(0xFF), uint8_t(0x00), uint8_t(0xB7), uint8_t(0x23), uint8_t(0x27),
		uint8_t(0x1A), uint8_t(0x16), uint8_t(0x7A), uint8_t(0x56), uint8_t(0xA2), uint8_t(0x7E), uint8_t(0xA9),
		uint8_t(0xEA), uint8_t(0x63), uint8_t(0xF5), uint8_t(0x60), uint8_t(0x17), uint8_t(0x58), uint8_t(0xFD),
		uint8_t(0x7C), uint8_t(0x6C), uint8_t(0xFE), uint8_t(0x57)}),

	HashLibByteArray({uint8_t(0xAE), uint8_t(0x4F), uint8_t(0xAE), uint8_t(0xAE),
		uint8_t(0x1D), uint8_t(0x3A), uint8_t(0xD3), uint8_t(0xD9), uint8_t(0x6F), uint8_t(0xA4), uint8_t(0xC3),
		uint8_t(0x3B), uint8_t(0x7A), uint8_t(0x30), uint8_t(0x39), uint8_t(0xC0), uint8_t(0x2D), uint8_t(0x66),
		uint8_t(0xC4), uint8_t(0xF9), uint8_t(0x51), uint8_t(0x42), uint8_t(0xA4), uint8_t(0x6C), uint8_t(0x18),
		uint8_t(0x7F), uint8_t(0x9A), uint8_t(0xB4), uint8_t(0x9A), uint8_t(0xF0), uint8_t(0x8E), uint8_t(0xC6),
		uint8_t(0xCF), uint8_t(0xFA), uint8_t(0xA6), uint8_t(0xB7), uint8_t(0x1C), uint8_t(0x9A), uint8_t(0xB7),
		uint8_t(0xB4), uint8_t(0x0A), uint8_t(0xF2), uint8_t(0x1F), uint8_t(0x66), uint8_t(0xC2), uint8_t(0xBE),
		uint8_t(0xC6), uint8_t(0xB6), uint8_t(0xBF), uint8_t(0x71), uint8_t(0xC5), uint8_t(0x72), uint8_t(0x36),
		uint8_t(0x90), uint8_t(0x4F), uint8_t(0x35), uint8_t(0xFA), uint8_t(0x68), uint8_t(0x40), uint8_t(0x7A),
		uint8_t(0x46), uint8_t(0x64), uint8_t(0x7D), uint8_t(0x6E)}),

	HashLibByteArray({uint8_t(0xF4), uint8_t(0xC7), uint8_t(0x0E), uint8_t(0x16),
		uint8_t(0xEE), uint8_t(0xAA), uint8_t(0xC5), uint8_t(0xEC), uint8_t(0x51), uint8_t(0xAC), uint8_t(0x86),
		uint8_t(0xFE), uint8_t(0xBF), uint8_t(0x24), uint8_t(0x09), uint8_t(0x54), uint8_t(0x39), uint8_t(0x9E),
		uint8_t(0xC6), uint8_t(0xC7), uint8_t(0xE6), uint8_t(0xBF), uint8_t(0x87), uint8_t(0xC9), uint8_t(0xD3),
		uint8_t(0x47), uint8_t(0x3E), uint8_t(0x33), uint8_t(0x19), uint8_t(0x7A), uint8_t(0x93), uint8_t(0xC9),
		uint8_t(0x09), uint8_t(0x92), uint8_t(0xAB), uint8_t(0xC5), uint8_t(0x2D), uint8_t(0x82), uint8_t(0x2C),
		uint8_t(0x37), uint8_t(0x06), uint8_t(0x47), uint8_t(0x69), uint8_t(0x83), uint8_t(0x28), uint8_t(0x4A),
		uint8_t(0x05), uint8_t(0x04), uint8_t(0x35), uint8_t(0x17), uint8_t(0x45), uint8_t(0x4C), uint8_t(0xA2),
		uint8_t(0x3C), uint8_t(0x4A), uint8_t(0xF3), uint8_t(0x88), uint8_t(0x86), uint8_t(0x56), uint8_t(0x4D),
		uint8_t(0x3A), uint8_t(0x14), uint8_t(0xD4), uint8_t(0x93)}),

	HashLibByteArray({uint8_t(0x9B), uint8_t(0x1F), uint8_t(0x5B), uint8_t(0x42),
		uint8_t(0x4D), uint8_t(0x93), uint8_t(0xC9), uint8_t(0xA7), uint8_t(0x03), uint8_t(0xE7), uint8_t(0xAA),
		uint8_t(0x02), uint8_t(0x0C), uint8_t(0x6E), uint8_t(0x41), uint8_t(0x41), uint8_t(0x4E), uint8_t(0xB7),
		uint8_t(0xF8), uint8_t(0x71), uint8_t(0x9C), uint8_t(0x36), uint8_t(0xDE), uint8_t(0x1E), uint8_t(0x89),
		uint8_t(0xB4), uint8_t(0x44), uint8_t(0x3B), uint8_t(0x4D), uint8_t(0xDB), uint8_t(0xC4), uint8_t(0x9A),
		uint8_t(0xF4), uint8_t(0x89), uint8_t(0x2B), uint8_t(0xCB), uint8_t(0x92), uint8_t(0x9B), uint8_t(0x06),
		uint8_t(0x90), uint8_t(0x69), uint8_t(0xD1), uint8_t(0x8D), uint8_t(0x2B), uint8_t(0xD1), uint8_t(0xA5),
		uint8_t(0xC4), uint8_t(0x2F), uint8_t(0x36), uint8_t(0xAC), uint8_t(0xC2), uint8_t(0x35), uint8_t(0x59),
		uint8_t(0x51), uint8_t(0xA8), uint8_t(0xD9), uint8_t(0xA4), uint8_t(0x7F), uint8_t(0x0D), uint8_t(0xD4),
		uint8_t(0xBF), uint8_t(0x02), uint8_t(0xE7), uint8_t(0x1E)}),

	HashLibByteArray({uint8_t(0x37), uint8_t(0x8F), uint8_t(0x5A), uint8_t(0x54),
		uint8_t(0x16), uint8_t(0x31), uint8_t(0x22), uint8_t(0x9B), uint8_t(0x94), uint8_t(0x4C), uint8_t(0x9A),
		uint8_t(0xD8), uint8_t(0xEC), uint8_t(0x16), uint8_t(0x5F), uint8_t(0xDE), uint8_t(0x3A), uint8_t(0x7D),
		uint8_t(0x3A), uint8_t(0x1B), uint8_t(0x25), uint8_t(0x89), uint8_t(0x42), uint8_t(0x24), uint8_t(0x3C),
		uint8_t(0xD9), uint8_t(0x55), uint8_t(0xB7), uint8_t(0xE0), uint8_t(0x0D), uint8_t(0x09), uint8_t(0x84),
		uint8_t(0x80), uint8_t(0x0A), uint8_t(0x44), uint8_t(0x0B), uint8_t(0xDB), uint8_t(0xB2), uint8_t(0xCE),
		uint8_t(0xB1), uint8_t(0x7B), uint8_t(0x2B), uint8_t(0x8A), uint8_t(0x9A), uint8_t(0xA6), uint8_t(0x07),
		uint8_t(0x9C), uint8_t(0x54), uint8_t(0x0E), uint8_t(0x38), uint8_t(0xDC), uint8_t(0x92), uint8_t(0xCB),
		uint8_t(0x1F), uint8_t(0x2A), uint8_t(0x60), uint8_t(0x72), uint8_t(0x61), uint8_t(0x44), uint8_t(0x51),
		uint8_t(0x83), uint8_t(0x23), uint8_t(0x5A), uint8_t(0xDB)}),

	HashLibByteArray({uint8_t(0xAB), uint8_t(0xBE), uint8_t(0xDE), uint8_t(0xA6),
		uint8_t(0x80), uint8_t(0x05), uint8_t(0x6F), uint8_t(0x52), uint8_t(0x38), uint8_t(0x2A), uint8_t(0xE5),
		uint8_t(0x48), uint8_t(0xB2), uint8_t(0xE4), uint8_t(0xF3), uint8_t(0xF3), uint8_t(0x89), uint8_t(0x41),
		uint8_t(0xE7), uint8_t(0x1C), uint8_t(0xFF), uint8_t(0x8A), uint8_t(0x78), uint8_t(0xDB), uint8_t(0x1F),
		uint8_t(0xFF), uint8_t(0xE1), uint8_t(0x8A), uint8_t(0x1B), uint8_t(0x33), uint8_t(0x61), uint8_t(0x03),
		uint8_t(0x9F), uint8_t(0xE7), uint8_t(0x67), uint8_t(0x02), uint8_t(0xAF), uint8_t(0x69), uint8_t(0x33),
		uint8_t(0x4B), uint8_t(0x7A), uint8_t(0x1E), uint8_t(0x6C), uint8_t(0x30), uint8_t(0x3B), uint8_t(0x76),
		uint8_t(0x52), uint8_t(0xF4), uint8_t(0x36), uint8_t(0x98), uint8_t(0xFA), uint8_t(0xD1), uint8_t(0x15),
		uint8_t(0x3B), uint8_t(0xB6), uint8_t(0xC3), uint8_t(0x74), uint8_t(0xB4), uint8_t(0xC7), uint8_t(0xFB),
		uint8_t(0x98), uint8_t(0x45), uint8_t(0x9C), uint8_t(0xED)}),

	HashLibByteArray({ uint8_t(0x7B), uint8_t(0xCD), uint8_t(0x9E), uint8_t(0xD0),
		uint8_t(0xEF), uint8_t(0xC8), uint8_t(0x89), uint8_t(0xFB), uint8_t(0x30), uint8_t(0x02), uint8_t(0xC6),
		uint8_t(0xCD), uint8_t(0x63), uint8_t(0x5A), uint8_t(0xFE), uint8_t(0x94), uint8_t(0xD8), uint8_t(0xFA),
		uint8_t(0x6B), uint8_t(0xBB), uint8_t(0xEB), uint8_t(0xAB), uint8_t(0x07), uint8_t(0x61), uint8_t(0x20),
		uint8_t(0x01), uint8_t(0x80), uint8_t(0x21), uint8_t(0x14), uint8_t(0x84), uint8_t(0x66), uint8_t(0x79),
		uint8_t(0x8A), uint8_t(0x1D), uint8_t(0x71), uint8_t(0xEF), uint8_t(0xEA), uint8_t(0x48), uint8_t(0xB9),
		uint8_t(0xCA), uint8_t(0xEF), uint8_t(0xBA), uint8_t(0xCD), uint8_t(0x1D), uint8_t(0x7D), uint8_t(0x47),
		uint8_t(0x6E), uint8_t(0x98), uint8_t(0xDE), uint8_t(0xA2), uint8_t(0x59), uint8_t(0x4A), uint8_t(0xC0),
		uint8_t(0x6F), uint8_t(0xD8), uint8_t(0x5D), uint8_t(0x6B), uint8_t(0xCA), uint8_t(0xA4), uint8_t(0xCD),
		uint8_t(0x81), uint8_t(0xF3), uint8_t(0x2D), uint8_t(0x1B) }),

	HashLibByteArray({ uint8_t(0x37), uint8_t(0x8E), uint8_t(0xE7), uint8_t(0x67),
		uint8_t(0xF1), uint8_t(0x16), uint8_t(0x31), uint8_t(0xBA), uint8_t(0xD2), uint8_t(0x13), uint8_t(0x80),
		uint8_t(0xB0), uint8_t(0x04), uint8_t(0x49), uint8_t(0xB1), uint8_t(0x7A), uint8_t(0xCD), uint8_t(0xA4),
		uint8_t(0x3C), uint8_t(0x32), uint8_t(0xBC), uint8_t(0xDF), uint8_t(0x1D), uint8_t(0x77), uint8_t(0xF8),
		uint8_t(0x20), uint8_t(0x12), uint8_t(0xD4), uint8_t(0x30), uint8_t(0x21), uint8_t(0x9F), uint8_t(0x9B),
		uint8_t(0x5D), uint8_t(0x80), uint8_t(0xEF), uint8_t(0x9D), uint8_t(0x18), uint8_t(0x91), uint8_t(0xCC),
		uint8_t(0x86), uint8_t(0xE7), uint8_t(0x1D), uint8_t(0xA4), uint8_t(0xAA), uint8_t(0x88), uint8_t(0xE1),
		uint8_t(0x28), uint8_t(0x52), uint8_t(0xFA), uint8_t(0xF4), uint8_t(0x17), uint8_t(0xD5), uint8_t(0xD9),
		uint8_t(0xB2), uint8_t(0x1B), uint8_t(0x99), uint8_t(0x48), uint8_t(0xBC), uint8_t(0x92), uint8_t(0x4A),
		uint8_t(0xF1), uint8_t(0x1B), uint8_t(0xD7), uint8_t(0x20) })
	
	});

HashLibByteArray GOST3411_2012::Zero = HashLibByteArray({ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });

HashLibMatrixUInt64Array GOST3411_2012::T = HashLibMatrixUInt64Array
({ HashLibUInt64Array({uint64_t(0xE6F87E5C5B711FD0),
	uint64_t(0x258377800924FA16), uint64_t(0xC849E07E852EA4A8),
	uint64_t(0x5B4686A18F06C16A), uint64_t(0x0B32E9A2D77B416E),
	uint64_t(0xABDA37A467815C66), uint64_t(0xF61796A81A686676),
	uint64_t(0xF5DC0B706391954B), uint64_t(0x4862F38DB7E64BF1),
	uint64_t(0xFF5C629A68BD85C5), uint64_t(0xCB827DA6FCD75795),
	uint64_t(0x66D36DAF69B9F089), uint64_t(0x356C9F74483D83B0),
	uint64_t(0x7CBCECB1238C99A1), uint64_t(0x36A702AC31C4708D),
	uint64_t(0x9EB6A8D02FBCDFD6), uint64_t(0x8B19FA51E5B3AE37),
	uint64_t(0x9CCFB5408A127D0B), uint64_t(0xBC0C78B508208F5A),
	uint64_t(0xE533E3842288ECED), uint64_t(0xCEC2C7D377C15FD2),
	uint64_t(0xEC7817B6505D0F5E), uint64_t(0xB94CC2C08336871D),
	uint64_t(0x8C205DB4CB0B04AD), uint64_t(0x763C855B28A0892F),
	uint64_t(0x588D1B79F6FF3257), uint64_t(0x3FECF69E4311933E),
	uint64_t(0x0FC0D39F803A18C9), uint64_t(0xEE010A26F5F3AD83),
	uint64_t(0x10EFE8F4411979A6), uint64_t(0x5DCDA10C7DE93A10),
	uint64_t(0x4A1BEE1D1248E92C), uint64_t(0x53BFF2DB21847339),
	uint64_t(0xB4F50CCFA6A23D09), uint64_t(0x5FB4BC9CD84798CD),
	uint64_t(0xE88A2D8B071C56F9), uint64_t(0x7F7771695A756A9C),
	uint64_t(0xC5F02E71A0BA1EBC), uint64_t(0xA663F9AB4215E672),
	uint64_t(0x2EB19E22DE5FBB78), uint64_t(0x0DB9CE0F2594BA14),
	uint64_t(0x82520E6397664D84), uint64_t(0x2F031E6A0208EA98),
	uint64_t(0x5C7F2144A1BE6BF0), uint64_t(0x7A37CB1CD16362DB),
	uint64_t(0x83E08E2B4B311C64), uint64_t(0xCF70479BAB960E32),
	uint64_t(0x856BA986B9DEE71E), uint64_t(0xB5478C877AF56CE9),
	uint64_t(0xB8FE42885F61D6FD), uint64_t(0x1BDD0156966238C8),
	uint64_t(0x622157923EF8A92E), uint64_t(0xFC97FF42114476F8),
	uint64_t(0x9D7D350856452CEB), uint64_t(0x4C90C9B0E0A71256),
	uint64_t(0x2308502DFBCB016C), uint64_t(0x2D7A03FAA7A64845),
	uint64_t(0xF46E8B38BFC6C4AB), uint64_t(0xBDBEF8FDD477DEBA),
	uint64_t(0x3AAC4CEBC8079B79), uint64_t(0xF09CB105E8879D0C),
	uint64_t(0x27FA6A10AC8A58CB), uint64_t(0x8960E7C1401D0CEA),
	uint64_t(0x1A6F811E4A356928), uint64_t(0x90C4FB0773D196FF),
	uint64_t(0x43501A2F609D0A9F), uint64_t(0xF7A516E0C63F3796),
	uint64_t(0x1CE4A6B3B8DA9252), uint64_t(0x1324752C38E08A9B),
	uint64_t(0xA5A864733BEC154F), uint64_t(0x2BF124575549B33F),
	uint64_t(0xD766DB15440DC5C7), uint64_t(0xA7D179E39E42B792),
	uint64_t(0xDADF151A61997FD3), uint64_t(0x86A0345EC0271423),
	uint64_t(0x38D5517B6DA939A4), uint64_t(0x6518F077104003B4),
	uint64_t(0x02791D90A5AEA2DD), uint64_t(0x88D267899C4A5D0A),
	uint64_t(0x930F66DF0A2865C2), uint64_t(0x4EE9D4204509B08B),
	uint64_t(0x325538916685292A), uint64_t(0x412907BFC533A842),
	uint64_t(0xB27E2B62544DC673), uint64_t(0x6C5304456295E007),
	uint64_t(0x5AF406E95351908A), uint64_t(0x1F2F3B6BC123616F),
	uint64_t(0xC37B09DC5255E5C6), uint64_t(0x3967D133B1FE6844),
	uint64_t(0x298839C7F0E711E2), uint64_t(0x409B87F71964F9A2),
	uint64_t(0xE938ADC3DB4B0719), uint64_t(0x0C0B4E47F9C3EBF4),
	uint64_t(0x5534D576D36B8843), uint64_t(0x4610A05AEB8B02D8),
	uint64_t(0x20C3CDF58232F251), uint64_t(0x6DE1840DBEC2B1E7),
	uint64_t(0xA0E8DE06B0FA1D08), uint64_t(0x7B854B540D34333B),
	uint64_t(0x42E29A67BCCA5B7F), uint64_t(0xD8A6088AC437DD0E),
	uint64_t(0xC63BB3A9D943ED81), uint64_t(0x21714DBD5E65A3B1),
	uint64_t(0x6761EDE7B5EEA169), uint64_t(0x2431F7C8D573ABF6),
	uint64_t(0xD51FC685E1A3671A), uint64_t(0x5E063CD40410C92D),
	uint64_t(0x283AB98F2CB04002), uint64_t(0x8FEBC06CB2F2F790),
	uint64_t(0x17D64F116FA1D33C), uint64_t(0xE07359F1A99EE4AA),
	uint64_t(0x784ED68C74CDC006), uint64_t(0x6E2A19D5C73B42DA),
	uint64_t(0x8712B4161C7045C3), uint64_t(0x371582E4ED93216D),
	uint64_t(0xACE390414939F6FC), uint64_t(0x7EC5F12186223B7C),
	uint64_t(0xC0B094042BAC16FB), uint64_t(0xF9D745379A527EBF),
	uint64_t(0x737C3F2EA3B68168), uint64_t(0x33E7B8D9BAD278CA),
	uint64_t(0xA9A32A34C22FFEBB), uint64_t(0xE48163CCFEDFBD0D),
	uint64_t(0x8E5940246EA5A670), uint64_t(0x51C6EF4B842AD1E4),
	uint64_t(0x22BAD065279C508C), uint64_t(0xD91488C218608CEE),
	uint64_t(0x319EA5491F7CDA17), uint64_t(0xD394E128134C9C60),
	uint64_t(0x094BF43272D5E3B3), uint64_t(0x9BF612A5A4AAD791),
	uint64_t(0xCCBBDA43D26FFD0F), uint64_t(0x34DE1F3C946AD250),
	uint64_t(0x4F5B5468995EE16B), uint64_t(0xDF9FAF6FEA8F7794),
	uint64_t(0x2648EA5870DD092B), uint64_t(0xBFC7E56D71D97C67),
	uint64_t(0xDDE6B2FF4F21D549), uint64_t(0x3C276B463AE86003),
	uint64_t(0x91767B4FAF86C71F), uint64_t(0x68A13E7835D4B9A0),
	uint64_t(0xB68C115F030C9FD4), uint64_t(0x141DD2C916582001),
	uint64_t(0x983D8F7DDD5324AC), uint64_t(0x64AA703FCC175254),
	uint64_t(0xC2C989948E02B426), uint64_t(0x3E5E76D69F46C2DE),
	uint64_t(0x50746F03587D8004), uint64_t(0x45DB3D829272F1E5),
	uint64_t(0x60584A029B560BF3), uint64_t(0xFBAE58A73FFCDC62),
	uint64_t(0xA15A5E4E6CAD4CE8), uint64_t(0x4BA96E55CE1FB8CC),
	uint64_t(0x08F9747AAE82B253), uint64_t(0xC102144CF7FB471B),
	uint64_t(0x9F042898F3EB8E36), uint64_t(0x068B27ADF2EFFB7A),
	uint64_t(0xEDCA97FE8C0A5EBE), uint64_t(0x778E0513F4F7D8CF),
	uint64_t(0x302C2501C32B8BF7), uint64_t(0x8D92DDFC175C554D),
	uint64_t(0xF865C57F46052F5F), uint64_t(0xEAF3301BA2B2F424),
	uint64_t(0xAA68B7ECBBD60D86), uint64_t(0x998F0F350104754C),
	uint64_t(0x0000000000000000), uint64_t(0xF12E314D34D0CCEC),
	uint64_t(0x710522BE061823B5), uint64_t(0xAF280D9930C005C1),
	uint64_t(0x97FD5CE25D693C65), uint64_t(0x19A41CC633CC9A15),
	uint64_t(0x95844172F8C79EB8), uint64_t(0xDC5432B7937684A9),
	uint64_t(0x9436C13A2490CF58), uint64_t(0x802B13F332C8EF59),
	uint64_t(0xC442AE397CED4F5C), uint64_t(0xFA1CD8EFE3AB8D82),
	uint64_t(0xF2E5AC954D293FD1), uint64_t(0x6AD823E8907A1B7D),
	uint64_t(0x4D2249F83CF043B6), uint64_t(0x03CB9DD879F9F33D),
	uint64_t(0xDE2D2F2736D82674), uint64_t(0x2A43A41F891EE2DF),
	uint64_t(0x6F98999D1B6C133A), uint64_t(0xD4AD46CD3DF436FA),
	uint64_t(0xBB35DF50269825C0), uint64_t(0x964FDCAA813E6D85),
	uint64_t(0xEB41B0537EE5A5C4), uint64_t(0x0540BA758B160847),
	uint64_t(0xA41AE43BE7BB44AF), uint64_t(0xE3B8C429D0671797),
	uint64_t(0x819993BBEE9FBEB9), uint64_t(0xAE9A8DD1EC975421),
	uint64_t(0xF3572CDD917E6E31), uint64_t(0x6393D7DAE2AFF8CE),
	uint64_t(0x47A2201237DC5338), uint64_t(0xA32343DEC903EE35),
	uint64_t(0x79FC56C4A89A91E6), uint64_t(0x01B28048DC5751E0),
	uint64_t(0x1296F564E4B7DB7B), uint64_t(0x75F7188351597A12),
	uint64_t(0xDB6D9552BDCE2E33), uint64_t(0x1E9DBB231D74308F),
	uint64_t(0x520D7293FDD322D9), uint64_t(0xE20A44610C304677),
	uint64_t(0xFEEEE2D2B4EAD425), uint64_t(0xCA30FDEE20800675),
	uint64_t(0x61EACA4A47015A13), uint64_t(0xE74AFE1487264E30),
	uint64_t(0x2CC883B27BF119A5), uint64_t(0x1664CF59B3F682DC),
	uint64_t(0xA811AA7C1E78AF5B), uint64_t(0x1D5626FB648DC3B2),
	uint64_t(0xB73E9117DF5BCE34), uint64_t(0xD05F7CF06AB56F5D),
	uint64_t(0xFD257F0ACD132718), uint64_t(0x574DC8E676C52A9E),
	uint64_t(0x0739A7E52EB8AA9A), uint64_t(0x5486553E0F3CD9A3),
	uint64_t(0x56FF48AEAA927B7E), uint64_t(0xBE756525AD8E2D87),
	uint64_t(0x7D0E6CF9FFDBC841), uint64_t(0x3B1ECCA31450CA99),
	uint64_t(0x6913BE30E983E840), uint64_t(0xAD511009956EA71C),
	uint64_t(0xB1B5B6BA2DB4354E), uint64_t(0x4469BDCA4E25A005),
	uint64_t(0x15AF5281CA0F71E1), uint64_t(0x744598CB8D0E2BF2),
	uint64_t(0x593F9B312AA863B7), uint64_t(0xEFB38A6E29A4FC63),
	uint64_t(0x6B6AA3A04C2D4A9D), uint64_t(0x3D95EB0EE6BF31E3),
	uint64_t(0xA291C3961554BFD5), uint64_t(0x18169C8EEF9BCBF5),
	uint64_t(0x115D68BC9D4E2846), uint64_t(0xBA875F18FACF7420),
	uint64_t(0xD1EDFCB8B6E23EBD), uint64_t(0xB00736F2F1E364AE),
	uint64_t(0x84D929CE6589B6FE), uint64_t(0x70B7A2F6DA4F7255),
	uint64_t(0x0E7253D75C6D4929), uint64_t(0x04F23A3D574159A7),
	uint64_t(0x0A8069EA0B2C108E), uint64_t(0x49D073C56BB11A11),
	uint64_t(0x8AAB7A1939E4FFD7), uint64_t(0xCD095A0B0E38ACEF),
	uint64_t(0xC9FB60365979F548), uint64_t(0x92BDE697D67F3422),
	uint64_t(0xC78933E10514BC61), uint64_t(0xE1C1D9B975C9B54A),
	uint64_t(0xD2266160CF1BCD80), uint64_t(0x9A4492ED78FD8671),
	uint64_t(0xB3CCAB2A881A9793), uint64_t(0x72CEBF667FE1D088),
	uint64_t(0xD6D45B5D985A9427)}),

	HashLibUInt64Array({ uint64_t(0xC811A8058C3F55DE),
		uint64_t(0x65F5B43196B50619), uint64_t(0xF74F96B1D6706E43),
		uint64_t(0x859D1E8BCB43D336), uint64_t(0x5AAB8A85CCFA3D84),
		uint64_t(0xF9C7BF99C295FCFD), uint64_t(0xA21FD5A1DE4B630F),
		uint64_t(0xCDB3EF763B8B456D), uint64_t(0x803F59F87CF7C385),
		uint64_t(0xB27C73BE5F31913C), uint64_t(0x98E3AC6633B04821),
		uint64_t(0xBF61674C26B8F818), uint64_t(0x0FFBC995C4C130C8),
		uint64_t(0xAAA0862010761A98), uint64_t(0x6057F342210116AA),
		uint64_t(0xF63C760C0654CC35), uint64_t(0x2DDB45CC667D9042),
		uint64_t(0xBCF45A964BD40382), uint64_t(0x68E8A0C3EF3C6F3D),
		uint64_t(0xA7BD92D269FF73BC), uint64_t(0x290AE20201ED2287),
		uint64_t(0xB7DE34CDE885818F), uint64_t(0xD901EEA7DD61059B),
		uint64_t(0xD6FA273219A03553), uint64_t(0xD56F1AE874CCCEC9),
		uint64_t(0xEA31245C2E83F554), uint64_t(0x7034555DA07BE499),
		uint64_t(0xCE26D2AC56E7BEF7), uint64_t(0xFD161857A5054E38),
		uint64_t(0x6A0E7DA4527436D1), uint64_t(0x5BD86A381CDE9FF2),
		uint64_t(0xCAF7756231770C32), uint64_t(0xB09AAED9E279C8D0),
		uint64_t(0x5DEF1091C60674DB), uint64_t(0x111046A2515E5045),
		uint64_t(0x23536CE4729802FC), uint64_t(0xC50CBCF7F5B63CFA),
		uint64_t(0x73A16887CD171F03), uint64_t(0x7D2941AFD9F28DBD),
		uint64_t(0x3F5E3EB45A4F3B9D), uint64_t(0x84EEFE361B677140),
		uint64_t(0x3DB8E3D3E7076271), uint64_t(0x1A3A28F9F20FD248),
		uint64_t(0x7EBC7C75B49E7627), uint64_t(0x74E5F293C7EB565C),
		uint64_t(0x18DCF59E4F478BA4), uint64_t(0x0C6EF44FA9ADCB52),
		uint64_t(0xC699812D98DAC760), uint64_t(0x788B06DC6E469D0E),
		uint64_t(0xFC65F8EA7521EC4E), uint64_t(0x30A5F7219E8E0B55),
		uint64_t(0x2BEC3F65BCA57B6B), uint64_t(0xDDD04969BAF1B75E),
		uint64_t(0x99904CDBE394EA57), uint64_t(0x14B201D1E6EA40F6),
		uint64_t(0xBBB0C08241284ADD), uint64_t(0x50F20463BF8F1DFF),
		uint64_t(0xE8D7F93B93CBACB8), uint64_t(0x4D8CB68E477C86E8),
		uint64_t(0xC1DD1B3992268E3F), uint64_t(0x7C5AA11209D62FCB),
		uint64_t(0x2F3D98ABDB35C9AE), uint64_t(0x671369562BFD5FF5),
		uint64_t(0x15C1E16C36CEE280), uint64_t(0x1D7EB2EDF8F39B17),
		uint64_t(0xDA94D37DB00DFE01), uint64_t(0x877BC3EC760B8ADA),
		uint64_t(0xCB8495DFE153AE44), uint64_t(0x05A24773B7B410B3),
		uint64_t(0x12857B783C32ABDF), uint64_t(0x8EB770D06812513B),
		uint64_t(0x536739B9D2E3E665), uint64_t(0x584D57E271B26468),
		uint64_t(0xD789C78FC9849725), uint64_t(0xA935BBFA7D1AE102),
		uint64_t(0x8B1537A3DFA64188), uint64_t(0xD0CD5D9BC378DE7A),
		uint64_t(0x4AC82C9A4D80CFB7), uint64_t(0x42777F1B83BDB620),
		uint64_t(0x72D2883A1D33BD75), uint64_t(0x5E7A2D4BAB6A8F41),
		uint64_t(0xF4DAAB6BBB1C95D9), uint64_t(0x905CFFE7FD8D31B6),
		uint64_t(0x83AA6422119B381F), uint64_t(0xC0AEFB8442022C49),
		uint64_t(0xA0F908C663033AE3), uint64_t(0xA428AF0804938826),
		uint64_t(0xADE41C341A8A53C7), uint64_t(0xAE7121EE77E6A85D),
		uint64_t(0xC47F5C4A25929E8C), uint64_t(0xB538E9AA55CDD863),
		uint64_t(0x06377AA9DAD8EB29), uint64_t(0xA18AE87BB3279895),
		uint64_t(0x6EDFDA6A35E48414), uint64_t(0x6B7D9D19825094A7),
		uint64_t(0xD41CFA55A4E86CBF), uint64_t(0xE5CAEDC9EA42C59C),
		uint64_t(0xA36C351C0E6FC179), uint64_t(0x5181E4DE6FABBF89),
		uint64_t(0xFFF0C530184D17D4), uint64_t(0x9D41EB1584045892),
		uint64_t(0x1C0D525028D73961), uint64_t(0xF178EC180CA8856A),
		uint64_t(0x9A0571018EF811CD), uint64_t(0x4091A27C3EF5EFCC),
		uint64_t(0x19AF15239F6329D2), uint64_t(0x347450EFF91EB990),
		uint64_t(0xE11B4A078DD27759), uint64_t(0xB9561DE5FC601331),
		uint64_t(0x912F1F5A2DA993C0), uint64_t(0x1654DCB65BA2191A),
		uint64_t(0x3E2DDE098A6B99EB), uint64_t(0x8A66D71E0F82E3FE),
		uint64_t(0x8C51ADB7D55A08D7), uint64_t(0x4533E50F8941FF7F),
		uint64_t(0x02E6DD67BD4859EC), uint64_t(0xE068AABA5DF6D52F),
		uint64_t(0xC24826E3FF4A75A5), uint64_t(0x6C39070D88ACDDF8),
		uint64_t(0x6486548C4691A46F), uint64_t(0xD1BEBD26135C7C0C),
		uint64_t(0xB30F93038F15334A), uint64_t(0x82D9849FC1BF9A69),
		uint64_t(0x9C320BA85420FAE4), uint64_t(0xFA528243AFF90767),
		uint64_t(0x9ED4D6CFE968A308), uint64_t(0xB825FD582C44B147),
		uint64_t(0x9B7691BC5EDCB3BB), uint64_t(0xC7EA619048FE6516),
		uint64_t(0x1063A61F817AF233), uint64_t(0x47D538683409A693),
		uint64_t(0x63C2CE984C6DED30), uint64_t(0x2A9FDFD86C81D91D),
		uint64_t(0x7B1E3B06032A6694), uint64_t(0x666089EBFBD9FD83),
		uint64_t(0x0A598EE67375207B), uint64_t(0x07449A140AFC495F),
		uint64_t(0x2CA8A571B6593234), uint64_t(0x1F986F8A45BBC2FB),
		uint64_t(0x381AA4A050B372C2), uint64_t(0x5423A3ADD81FAF3A),
		uint64_t(0x17273C0B8B86BB6C), uint64_t(0xFE83258DC869B5A2),
		uint64_t(0x287902BFD1C980F1), uint64_t(0xF5A94BD66B3837AF),
		uint64_t(0x88800A79B2CABA12), uint64_t(0x55504310083B0D4C),
		uint64_t(0xDF36940E07B9EEB2), uint64_t(0x04D1A7CE6790B2C5),
		uint64_t(0x612413FFF125B4DC), uint64_t(0x26F12B97C52C124F),
		uint64_t(0x86082351A62F28AC), uint64_t(0xEF93632F9937E5E7),
		uint64_t(0x3507B052293A1BE6), uint64_t(0xE72C30AE570A9C70),
		uint64_t(0xD3586041AE1425E0), uint64_t(0xDE4574B3D79D4CC4),
		uint64_t(0x92BA228040C5685A), uint64_t(0xF00B0CA5DC8C271C),
		uint64_t(0xBE1287F1F69C5A6E), uint64_t(0xF39E317FB1E0DC86),
		uint64_t(0x495D114020EC342D), uint64_t(0x699B407E3F18CD4B),
		uint64_t(0xDCA3A9D46AD51528), uint64_t(0x0D1D14F279896924),
		uint64_t(0x0000000000000000), uint64_t(0x593EB75FA196C61E),
		uint64_t(0x2E4E78160B116BD8), uint64_t(0x6D4AE7B058887F8E),
		uint64_t(0xE65FD013872E3E06), uint64_t(0x7A6DDBBBD30EC4E2),
		uint64_t(0xAC97FC89CAAEF1B1), uint64_t(0x09CCB33C1E19DBE1),
		uint64_t(0x89F3EAC462EE1864), uint64_t(0x7770CF49AA87ADC6),
		uint64_t(0x56C57ECA6557F6D6), uint64_t(0x03953DDA6D6CFB9A),
		uint64_t(0x36928D884456E07C), uint64_t(0x1EEB8F37959F608D),
		uint64_t(0x31D6179C4EAAA923), uint64_t(0x6FAC3AD7E5C02662),
		uint64_t(0x43049FA653991456), uint64_t(0xABD3669DC052B8EE),
		uint64_t(0xAF02C153A7C20A2B), uint64_t(0x3CCB036E3723C007),
		uint64_t(0x93C9C23D90E1CA2C), uint64_t(0xC33BC65E2F6ED7D3),
		uint64_t(0x4CFF56339758249E), uint64_t(0xB1E94E64325D6AA6),
		uint64_t(0x37E16D359472420A), uint64_t(0x79F8E661BE623F78),
		uint64_t(0x5214D90402C74413), uint64_t(0x482EF1FDF0C8965B),
		uint64_t(0x13F69BC5EC1609A9), uint64_t(0x0E88292814E592BE),
		uint64_t(0x4E198B542A107D72), uint64_t(0xCCC00FCBEBAFE71B),
		uint64_t(0x1B49C844222B703E), uint64_t(0x2564164DA840E9D5),
		uint64_t(0x20C6513E1FF4F966), uint64_t(0xBAC3203F910CE8AB),
		uint64_t(0xF2EDD1C261C47EF0), uint64_t(0x814CB945ACD361F3),
		uint64_t(0x95FEB8944A392105), uint64_t(0x5C9CF02C1622D6AD),
		uint64_t(0x971865F3F77178E9), uint64_t(0xBD87BA2B9BF0A1F4),
		uint64_t(0x444005B259655D09), uint64_t(0xED75BE48247FBC0B),
		uint64_t(0x7596122E17CFF42A), uint64_t(0xB44B091785E97A15),
		uint64_t(0x966B854E2755DA9F), uint64_t(0xEEE0839249134791),
		uint64_t(0x32432A4623C652B9), uint64_t(0xA8465B47AD3E4374),
		uint64_t(0xF8B45F2412B15E8B), uint64_t(0x2417F6F078644BA3),
		uint64_t(0xFB2162FE7FDDA511), uint64_t(0x4BBBCC279DA46DC1),
		uint64_t(0x0173E0BDD024A276), uint64_t(0x22208C59A2BCA08A),
		uint64_t(0x8FC4906DB836F34D), uint64_t(0xE4B90D743A6667EA),
		uint64_t(0x7147B5E0705F46EF), uint64_t(0x2782CB2A1508B039),
		uint64_t(0xEC065EF5F45B1E7D), uint64_t(0x21B5B183CFD05B10),
		uint64_t(0xDBE733C060295C77), uint64_t(0x9FA73672394C017E),
		uint64_t(0xCF55321186C31C81), uint64_t(0xD8720E1A0D45A7ED),
		uint64_t(0x3B8F997A3DDF8958), uint64_t(0x3AFC79C7EDFB2B2E),
		uint64_t(0xE9A4198643EF0ECE), uint64_t(0x5F09CDF67B4E2D37),
		uint64_t(0x4F6A6BE9FA34DF04), uint64_t(0xB6ADD47038A123F9),
		uint64_t(0x8D224D0A057EAAA1), uint64_t(0xC96248B85C1BF7A8),
		uint64_t(0xE3FD9760309A2EB5), uint64_t(0x0B2A6E5BA351820D),
		uint64_t(0xEB42C4E1FEA75722), uint64_t(0x948D58299A1D8373),
		uint64_t(0x7FCF9CC864BAD451), uint64_t(0xA55B4FB5D4B72A50),
		uint64_t(0x08BF5381CE3D7997), uint64_t(0x46A6D8D5E42D04E5),
		uint64_t(0xD22B80FC7E308796), uint64_t(0x57B69E77B57354A0),
		uint64_t(0x3969441D8097D0B4), uint64_t(0x3330CAFBF3E2F0CF),
		uint64_t(0xE28E77DDE0BE8CC3), uint64_t(0x62B12E259C494F46),
		uint64_t(0xA6CE726FB9DBD1CA), uint64_t(0x41E242C1EED14DBA),
		uint64_t(0x76032FF47AA30FB0) }),

	HashLibUInt64Array({ uint64_t(0x45B268A93ACDE4CC),
		uint64_t(0xAF7F0BE884549D08), uint64_t(0x048354B3C1468263),
		uint64_t(0x925435C2C80EFED2), uint64_t(0xEE4E37F27FDFFBA7),
		uint64_t(0x167A33920C60F14D), uint64_t(0xFB123B52EA03E584),
		uint64_t(0x4A0CAB53FDBB9007), uint64_t(0x9DEAF6380F788A19),
		uint64_t(0xCB48EC558F0CB32A), uint64_t(0xB59DC4B2D6FEF7E0),
		uint64_t(0xDCDBCA22F4F3ECB6), uint64_t(0x11DF5813549A9C40),
		uint64_t(0xE33FDEDF568ACED3), uint64_t(0xA0C1C8124322E9C3),
		uint64_t(0x07A56B8158FA6D0D), uint64_t(0x77279579B1E1F3DD),
		uint64_t(0xD9B18B74422AC004), uint64_t(0xB8EC2D9FFFABC294),
		uint64_t(0xF4ACF8A82D75914F), uint64_t(0x7BBF69B1EF2B6878),
		uint64_t(0xC4F62FAF487AC7E1), uint64_t(0x76CE809CC67E5D0C),
		uint64_t(0x6711D88F92E4C14C), uint64_t(0x627B99D9243DEDFE),
		uint64_t(0x234AA5C3DFB68B51), uint64_t(0x909B1F15262DBF6D),
		uint64_t(0x4F66EA054B62BCB5), uint64_t(0x1AE2CF5A52AA6AE8),
		uint64_t(0xBEA053FBD0CE0148), uint64_t(0xED6808C0E66314C9),
		uint64_t(0x43FE16CD15A82710), uint64_t(0xCD049231A06970F6),
		uint64_t(0xE7BC8A6C97CC4CB0), uint64_t(0x337CE835FCB3B9C0),
		uint64_t(0x65DEF2587CC780F3), uint64_t(0x52214EDE4132BB50),
		uint64_t(0x95F15E4390F493DF), uint64_t(0x870839625DD2E0F1),
		uint64_t(0x41313C1AFB8B66AF), uint64_t(0x91720AF051B211BC),
		uint64_t(0x477D427ED4EEA573), uint64_t(0x2E3B4CEEF6E3BE25),
		uint64_t(0x82627834EB0BCC43), uint64_t(0x9C03E3DD78E724C8),
		uint64_t(0x2877328AD9867DF9), uint64_t(0x14B51945E243B0F2),
		uint64_t(0x574B0F88F7EB97E2), uint64_t(0x88B6FA989AA4943A),
		uint64_t(0x19C4F068CB168586), uint64_t(0x50EE6409AF11FAEF),
		uint64_t(0x7DF317D5C04EABA4), uint64_t(0x7A567C5498B4C6A9),
		uint64_t(0xB6BBFB804F42188E), uint64_t(0x3CC22BCF3BC5CD0B),
		uint64_t(0xD04336EAAA397713), uint64_t(0xF02FAC1BEC33132C),
		uint64_t(0x2506DBA7F0D3488D), uint64_t(0xD7E65D6BF2C31A1E),
		uint64_t(0x5EB9B2161FF820F5), uint64_t(0x842E0650C46E0F9F),
		uint64_t(0x716BEB1D9E843001), uint64_t(0xA933758CAB315ED4),
		uint64_t(0x3FE414FDA2792265), uint64_t(0x27C9F1701EF00932),
		uint64_t(0x73A4C1CA70A771BE), uint64_t(0x94184BA6E76B3D0E),
		uint64_t(0x40D829FF8C14C87E), uint64_t(0x0FBEC3FAC77674CB),
		uint64_t(0x3616A9634A6A9572), uint64_t(0x8F139119C25EF937),
		uint64_t(0xF545ED4D5AEA3F9E), uint64_t(0xE802499650BA387B),
		uint64_t(0x6437E7BD0B582E22), uint64_t(0xE6559F89E053E261),
		uint64_t(0x80AD52E305288DFC), uint64_t(0x6DC55A23E34B9935),
		uint64_t(0xDE14E0F51AD0AD09), uint64_t(0xC6390578A659865E),
		uint64_t(0x96D7617109487CB1), uint64_t(0xE2D6CB3A21156002),
		uint64_t(0x01E915E5779FAED1), uint64_t(0xADB0213F6A77DCB7),
		uint64_t(0x9880B76EB9A1A6AB), uint64_t(0x5D9F8D248644CF9B),
		uint64_t(0xFD5E4536C5662658), uint64_t(0xF1C6B9FE9BACBDFD),
		uint64_t(0xEACD6341BE9979C4), uint64_t(0xEFA7221708405576),
		uint64_t(0x510771ECD88E543E), uint64_t(0xC2BA51CB671F043D),
		uint64_t(0x0AD482AC71AF5879), uint64_t(0xFE787A045CDAC936),
		uint64_t(0xB238AF338E049AED), uint64_t(0xBD866CC94972EE26),
		uint64_t(0x615DA6EBBD810290), uint64_t(0x3295FDD08B2C1711),
		uint64_t(0xF834046073BF0AEA), uint64_t(0xF3099329758FFC42),
		uint64_t(0x1CAEB13E7DCFA934), uint64_t(0xBA2307481188832B),
		uint64_t(0x24EFCE42874CE65C), uint64_t(0x0E57D61FB0E9DA1A),
		uint64_t(0xB3D1BAD6F99B343C), uint64_t(0xC0757B1C893C4582),
		uint64_t(0x2B510DB8403A9297), uint64_t(0x5C7698C1F1DB614A),
		uint64_t(0x3E0D0118D5E68CB4), uint64_t(0xD60F488E855CB4CF),
		uint64_t(0xAE961E0DF3CB33D9), uint64_t(0x3A8E55AB14A00ED7),
		uint64_t(0x42170328623789C1), uint64_t(0x838B6DD19C946292),
		uint64_t(0x895FEF7DED3B3AEB), uint64_t(0xCFCBB8E64E4A3149),
		uint64_t(0x064C7E642F65C3DC), uint64_t(0x3D2B3E2A4C5A63DA),
		uint64_t(0x5BD3F340A9210C47), uint64_t(0xB474D157A1615931),
		uint64_t(0xAC5934DA1DE87266), uint64_t(0x6EE365117AF7765B),
		uint64_t(0xC86ED36716B05C44), uint64_t(0x9BA6885C201D49C5),
		uint64_t(0xB905387A88346C45), uint64_t(0x131072C4BAB9DDFF),
		uint64_t(0xBF49461EA751AF99), uint64_t(0xD52977BC1CE05BA1),
		uint64_t(0xB0F785E46027DB52), uint64_t(0x546D30BA6E57788C),
		uint64_t(0x305AD707650F56AE), uint64_t(0xC987C682612FF295),
		uint64_t(0xA5AB8944F5FBC571), uint64_t(0x7ED528E759F244CA),
		uint64_t(0x8DDCBBCE2C7DB888), uint64_t(0xAA154ABE328DB1BA),
		uint64_t(0x1E619BE993ECE88B), uint64_t(0x09F2BD9EE813B717),
		uint64_t(0x7401AA4B285D1CB3), uint64_t(0x21858F143195CAEE),
		uint64_t(0x48C381841398D1B8), uint64_t(0xFCB750D3B2F98889),
		uint64_t(0x39A86A998D1CE1B9), uint64_t(0x1F888E0CE473465A),
		uint64_t(0x7899568376978716), uint64_t(0x02CF2AD7EE2341BF),
		uint64_t(0x85C713B5B3F1A14E), uint64_t(0xFF916FE12B4567E7),
		uint64_t(0x7C1A0230B7D10575), uint64_t(0x0C98FCC85ECA9BA5),
		uint64_t(0xA3E7F720DA9E06AD), uint64_t(0x6A6031A2BBB1F438),
		uint64_t(0x973E74947ED7D260), uint64_t(0x2CF4663918C0FF9A),
		uint64_t(0x5F50A7F368678E24), uint64_t(0x34D983B4A449D4CD),
		uint64_t(0x68AF1B755592B587), uint64_t(0x7F3C3D022E6DEA1B),
		uint64_t(0xABFC5F5B45121F6B), uint64_t(0x0D71E92D29553574),
		uint64_t(0xDFFDF5106D4F03D8), uint64_t(0x081BA87B9F8C19C6),
		uint64_t(0xDB7EA1A3AC0981BB), uint64_t(0xBBCA12AD66172DFA),
		uint64_t(0x79704366010829C7), uint64_t(0x179326777BFF5F9C),
		uint64_t(0x0000000000000000), uint64_t(0xEB2476A4C906D715),
		uint64_t(0x724DD42F0738DF6F), uint64_t(0xB752EE6538DDB65F),
		uint64_t(0x37FFBC863DF53BA3), uint64_t(0x8EFA84FCB5C157E6),
		uint64_t(0xE9EB5C73272596AA), uint64_t(0x1B0BDABF2535C439),
		uint64_t(0x86E12C872A4D4E20), uint64_t(0x9969A28BCE3E087A),
		uint64_t(0xFAFB2EB79D9C4B55), uint64_t(0x056A4156B6D92CB2),
		uint64_t(0x5A3AE6A5DEBEA296), uint64_t(0x22A3B026A8292580),
		uint64_t(0x53C85B3B36AD1581), uint64_t(0xB11E900117B87583),
		uint64_t(0xC51F3A4A3FE56930), uint64_t(0xE019E1EDCF3621BD),
		uint64_t(0xEC811D2591FCBA18), uint64_t(0x445B7D4C4D524A1D),
		uint64_t(0xA8DA6069DCAEF005), uint64_t(0x58F5CC72309DE329),
		uint64_t(0xD4C062596B7FF570), uint64_t(0xCE22AD0339D59F98),
		uint64_t(0x591CD99747024DF8), uint64_t(0x8B90C5AA03187B54),
		uint64_t(0xF663D27FC356D0F0), uint64_t(0xD8589E9135B56ED5),
		uint64_t(0x35309651D3D67A1C), uint64_t(0x12F96721CD26732E),
		uint64_t(0xD28C1C3D441A36AC), uint64_t(0x492A946164077F69),
		uint64_t(0x2D1D73DC6F5F514B), uint64_t(0x6F0A70F40D68D88A),
		uint64_t(0x60B4B30ECA1EAC41), uint64_t(0xD36509D83385987D),
		uint64_t(0x0B3D97490630F6A8), uint64_t(0x9ECCC90A96C46577),
		uint64_t(0xA20EE2C5AD01A87C), uint64_t(0xE49AB55E0E70A3DE),
		uint64_t(0xA4429CA182646BA0), uint64_t(0xDA97B446DB962F6A),
		uint64_t(0xCCED87D4D7F6DE27), uint64_t(0x2AB8185D37A53C46),
		uint64_t(0x9F25DCEFE15BCBA6), uint64_t(0xC19C6EF9FEA3EB53),
		uint64_t(0xA764A3931BD884CE), uint64_t(0x2FD2590B817C10F4),
		uint64_t(0x56A21A6D80743933), uint64_t(0xE573A0BB79EF0D0F),
		uint64_t(0x155C0CA095DC1E23), uint64_t(0x6C2C4FC694D437E4),
		uint64_t(0x10364DF623053291), uint64_t(0xDD32DFC7836C4267),
		uint64_t(0x03263F3299BCEF6E), uint64_t(0x66F8CD6AE57B6F9D),
		uint64_t(0x8C35AE2B5BE21659), uint64_t(0x31B3C2E21290F87F),
		uint64_t(0x93BD2027BF915003), uint64_t(0x69460E90220D1B56),
		uint64_t(0x299E276FAE19D328), uint64_t(0x63928C3C53A2432F),
		uint64_t(0x7082FEF8E91B9ED0), uint64_t(0xBC6F792C3EED40F7),
		uint64_t(0x4C40D537D2DE53DB), uint64_t(0x75E8BFAE5FC2B262),
		uint64_t(0x4DA9C0D2A541FD0A), uint64_t(0x4E8FFFE03CFD1264),
		uint64_t(0x2620E495696FA7E3), uint64_t(0xE1F0F408B8A98F6C),
		uint64_t(0xD1AA230FDDA6D9C2), uint64_t(0xC7D0109DD1C6288F),
		uint64_t(0x8A79D04F7487D585), uint64_t(0x4694579BA3710BA2),
		uint64_t(0x38417F7CFA834F68), uint64_t(0x1D47A4DB0A5007E5),
		uint64_t(0x206C9AF1460A643F), uint64_t(0xA128DDF734BD4712),
		uint64_t(0x8144470672B7232D), uint64_t(0xF2E086CC02105293),
		uint64_t(0x182DE58DBC892B57), uint64_t(0xCAA1F9B0F8931DFB),
		uint64_t(0x6B892447CC2E5AE9), uint64_t(0xF9DD11850420A43B),
		uint64_t(0x4BE5BEB68A243ED6), uint64_t(0x5584255F19C8D65D),
		uint64_t(0x3B67404E633FA006), uint64_t(0xA68DB6766C472A1F),
		uint64_t(0xF78AC79AB4C97E21), uint64_t(0xC353442E1080AAEC),
		uint64_t(0x9A4F9DB95782E714) }),

	HashLibUInt64Array({ uint64_t(0x05BA7BC82C9B3220),
		uint64_t(0x31A54665F8B65E4F), uint64_t(0xB1B651F77547F4D4),
		uint64_t(0x8BFA0D857BA46682), uint64_t(0x85A96C5AA16A98BB),
		uint64_t(0x990FAEF908EB79C9), uint64_t(0xA15E37A247F4A62D),
		uint64_t(0x76857DCD5D27741E), uint64_t(0xF8C50B800A1820BC),
		uint64_t(0xBE65DCB201F7A2B4), uint64_t(0x666D1B986F9426E7),
		uint64_t(0x4CC921BF53C4E648), uint64_t(0x95410A0F93D9CA42),
		uint64_t(0x20CDCCAA647BA4EF), uint64_t(0x429A4060890A1871),
		uint64_t(0x0C4EA4F69B32B38B), uint64_t(0xCCDA362DDE354CD3),
		uint64_t(0x96DC23BC7C5B2FA9), uint64_t(0xC309BB68AA851AB3),
		uint64_t(0xD26131A73648E013), uint64_t(0x021DC52941FC4DB2),
		uint64_t(0xCD5ADAB7704BE48A), uint64_t(0xA77965D984ED71E6),
		uint64_t(0x32386FD61734BBA4), uint64_t(0xE82D6DD538AB7245),
		uint64_t(0x5C2147EA6177B4B1), uint64_t(0x5DA1AB70CF091CE8),
		uint64_t(0xAC907FCE72B8BDFF), uint64_t(0x57C85DFD972278A8),
		uint64_t(0xA4E44C6A6B6F940D), uint64_t(0x3851995B4F1FDFE4),
		uint64_t(0x62578CCAED71BC9E), uint64_t(0xD9882BB0C01D2C0A),
		uint64_t(0x917B9D5D113C503B), uint64_t(0xA2C31E11A87643C6),
		uint64_t(0xE463C923A399C1CE), uint64_t(0xF71686C57EA876DC),
		uint64_t(0x87B4A973E096D509), uint64_t(0xAF0D567D9D3A5814),
		uint64_t(0xB40C2A3F59DCC6F4), uint64_t(0x3602F88495D121DD),
		uint64_t(0xD3E1DD3D9836484A), uint64_t(0xF945E71AA46688E5),
		uint64_t(0x7518547EB2A591F5), uint64_t(0x9366587450C01D89),
		uint64_t(0x9EA81018658C065B), uint64_t(0x4F54080CBC4603A3),
		uint64_t(0x2D0384C65137BF3D), uint64_t(0xDC325078EC861E2A),
		uint64_t(0xEA30A8FC79573FF7), uint64_t(0x214D2030CA050CB6),
		uint64_t(0x65F0322B8016C30C), uint64_t(0x69BE96DD1B247087),
		uint64_t(0xDB95EE9981E161B8), uint64_t(0xD1FC1814D9CA05F8),
		uint64_t(0x820ED2BBCC0DE729), uint64_t(0x63D76050430F14C7),
		uint64_t(0x3BCCB0E8A09D3A0F), uint64_t(0x8E40764D573F54A2),
		uint64_t(0x39D175C1E16177BD), uint64_t(0x12F5A37C734F1F4B),
		uint64_t(0xAB37C12F1FDFC26D), uint64_t(0x5648B167395CD0F1),
		uint64_t(0x6C04ED1537BF42A7), uint64_t(0xED97161D14304065),
		uint64_t(0x7D6C67DAAB72B807), uint64_t(0xEC17FA87BA4EE83C),
		uint64_t(0xDFAF79CB0304FBC1), uint64_t(0x733F060571BC463E),
		uint64_t(0x78D61C1287E98A27), uint64_t(0xD07CF48E77B4ADA1),
		uint64_t(0xB9C262536C90DD26), uint64_t(0xE2449B5860801605),
		uint64_t(0x8FC09AD7F941FCFB), uint64_t(0xFAD8CEA94BE46D0E),
		uint64_t(0xA343F28B0608EB9F), uint64_t(0x9B126BD04917347B),
		uint64_t(0x9A92874AE7699C22), uint64_t(0x1B017C42C4E69EE0),
		uint64_t(0x3A4C5C720EE39256), uint64_t(0x4B6E9F5E3EA399DA),
		uint64_t(0x6BA353F45AD83D35), uint64_t(0xE7FEE0904C1B2425),
		uint64_t(0x22D009832587E95D), uint64_t(0x842980C00F1430E2),
		uint64_t(0xC6B3C0A0861E2893), uint64_t(0x087433A419D729F2),
		uint64_t(0x341F3DADD42D6C6F), uint64_t(0xEE0A3FAEFBB2A58E),
		uint64_t(0x4AEE73C490DD3183), uint64_t(0xAAB72DB5B1A16A34),
		uint64_t(0xA92A04065E238FDF), uint64_t(0x7B4B35A1686B6FCC),
		uint64_t(0x6A23BF6EF4A6956C), uint64_t(0x191CB96B851AD352),
		uint64_t(0x55D598D4D6DE351A), uint64_t(0xC9604DE5F2AE7EF3),
		uint64_t(0x1CA6C2A3A981E172), uint64_t(0xDE2F9551AD7A5398),
		uint64_t(0x3025AAFF56C8F616), uint64_t(0x15521D9D1E2860D9),
		uint64_t(0x506FE31CFA45073A), uint64_t(0x189C55F12B647B0B),
		uint64_t(0x0180EC9AAE7EA859), uint64_t(0x7CEC8B40050C105E),
		uint64_t(0x2350E5198BF94104), uint64_t(0xEF8AD33455CC0DD7),
		uint64_t(0x07A7BEE16D677F92), uint64_t(0xE5E325B90DE76997),
		uint64_t(0x5A061591A26E637A), uint64_t(0xB611EF1618208B46),
		uint64_t(0x09F4DF3EB7A981AB), uint64_t(0x1EBB078AE87DACC0),
		uint64_t(0xB791038CB65E231F), uint64_t(0x0FD38D4574B05660),
		uint64_t(0x67EDF702C1EA8EBE), uint64_t(0xBA5F4BE0831238CD),
		uint64_t(0xE3C477C2CEFEBE5C), uint64_t(0x0DCE486C354C1BD2),
		uint64_t(0x8C5DB36416C31910), uint64_t(0x26EA9ED1A7627324),
		uint64_t(0x039D29B3EF82E5EB), uint64_t(0x9F28FC82CBF2AE02),
		uint64_t(0xA8AAE89CF05D2786), uint64_t(0x431AACFA2774B028),
		uint64_t(0xCF471F9E31B7A938), uint64_t(0x581BD0B8E3922EC8),
		uint64_t(0xBC78199B400BEF06), uint64_t(0x90FB71C7BF42F862),
		uint64_t(0x1F3BEB1046030499), uint64_t(0x683E7A47B55AD8DE),
		uint64_t(0x988F4263A695D190), uint64_t(0xD808C72A6E638453),
		uint64_t(0x0627527BC319D7CB), uint64_t(0xEBB04466D72997AE),
		uint64_t(0xE67E0C0AE2658C7C), uint64_t(0x14D2F107B056C880),
		uint64_t(0x7122C32C30400B8C), uint64_t(0x8A7AE11FD5DACEDB),
		uint64_t(0xA0DEDB38E98A0E74), uint64_t(0xAD109354DCC615A6),
		uint64_t(0x0BE91A17F655CC19), uint64_t(0x8DDD5FFEB8BDB149),
		uint64_t(0xBFE53028AF890AED), uint64_t(0xD65BA6F5B4AD7A6A),
		uint64_t(0x7956F0882997227E), uint64_t(0x10E8665532B352F9),
		uint64_t(0x0E5361DFDACEFE39), uint64_t(0xCEC7F3049FC90161),
		uint64_t(0xFF62B561677F5F2E), uint64_t(0x975CCF26D22587F0),
		uint64_t(0x51EF0F86543BAF63), uint64_t(0x2F1E41EF10CBF28F),
		uint64_t(0x52722635BBB94A88), uint64_t(0xAE8DBAE73344F04D),
		uint64_t(0x410769D36688FD9A), uint64_t(0xB3AB94DE34BBB966),
		uint64_t(0x801317928DF1AA9B), uint64_t(0xA564A0F0C5113C54),
		uint64_t(0xF131D4BEBDB1A117), uint64_t(0x7F71A2F3EA8EF5B5),
		uint64_t(0x40878549C8F655C3), uint64_t(0x7EF14E6944F05DEC),
		uint64_t(0xD44663DCF55137D8), uint64_t(0xF2ACFD0D523344FC),
		uint64_t(0x0000000000000000), uint64_t(0x5FBC6E598EF5515A),
		uint64_t(0x16CF342EF1AA8532), uint64_t(0xB036BD6DDB395C8D),
		uint64_t(0x13754FE6DD31B712), uint64_t(0xBBDFA77A2D6C9094),
		uint64_t(0x89E7C8AC3A582B30), uint64_t(0x3C6B0E09CDFA459D),
		uint64_t(0xC4AE0589C7E26521), uint64_t(0x49735A777F5FD468),
		uint64_t(0xCAFD64561D2C9B18), uint64_t(0xDA1502032F9FC9E1),
		uint64_t(0x8867243694268369), uint64_t(0x3782141E3BAF8984),
		uint64_t(0x9CB5D53124704BE9), uint64_t(0xD7DB4A6F1AD3D233),
		uint64_t(0xA6F989432A93D9BF), uint64_t(0x9D3539AB8A0EE3B0),
		uint64_t(0x53F2CAAF15C7E2D1), uint64_t(0x6E19283C76430F15),
		uint64_t(0x3DEBE2936384EDC4), uint64_t(0x5E3C82C3208BF903),
		uint64_t(0x33B8834CB94A13FD), uint64_t(0x6470DEB12E686B55),
		uint64_t(0x359FD1377A53C436), uint64_t(0x61CAA57902F35975),
		uint64_t(0x043A975282E59A79), uint64_t(0xFD7F70482683129C),
		uint64_t(0xC52EE913699CCD78), uint64_t(0x28B9FF0E7DAC8D1D),
		uint64_t(0x5455744E78A09D43), uint64_t(0xCB7D88CCB3523341),
		uint64_t(0x44BD121B4A13CFBA), uint64_t(0x4D49CD25FDBA4E11),
		uint64_t(0x3E76CB208C06082F), uint64_t(0x3FF627BA2278A076),
		uint64_t(0xC28957F204FBB2EA), uint64_t(0x453DFE81E46D67E3),
		uint64_t(0x94C1E6953DA7621B), uint64_t(0x2C83685CFF491764),
		uint64_t(0xF32C1197FC4DECA5), uint64_t(0x2B24D6BD922E68F6),
		uint64_t(0xB22B78449AC5113F), uint64_t(0x48F3B6EDD1217C31),
		uint64_t(0x2E9EAD75BEB55AD6), uint64_t(0x174FD8B45FD42D6B),
		uint64_t(0x4ED4E4961238ABFA), uint64_t(0x92E6B4EEFEBEB5D0),
		uint64_t(0x46A0D7320BEF8208), uint64_t(0x47203BA8A5912A51),
		uint64_t(0x24F75BF8E69E3E96), uint64_t(0xF0B1382413CF094E),
		uint64_t(0xFEE259FBC901F777), uint64_t(0x276A724B091CDB7D),
		uint64_t(0xBDF8F501EE75475F), uint64_t(0x599B3C224DEC8691),
		uint64_t(0x6D84018F99C1EAFE), uint64_t(0x7498B8E41CDB39AC),
		uint64_t(0xE0595E71217C5BB7), uint64_t(0x2AA43A273C50C0AF),
		uint64_t(0xF50B43EC3F543B6E), uint64_t(0x838E3E2162734F70),
		uint64_t(0xC09492DB4507FF58), uint64_t(0x72BFEA9FDFC2EE67),
		uint64_t(0x11688ACF9CCDFAA0), uint64_t(0x1A8190D86A9836B9),
		uint64_t(0x7ACBD93BC615C795), uint64_t(0xC7332C3A286080CA),
		uint64_t(0x863445E94EE87D50), uint64_t(0xF6966A5FD0D6DE85),
		uint64_t(0xE9AD814F96D5DA1C), uint64_t(0x70A22FB69E3EA3D5),
		uint64_t(0x0A69F68D582B6440), uint64_t(0xB8428EC9C2EE757F),
		uint64_t(0x604A49E3AC8DF12C), uint64_t(0x5B86F90B0C10CB23),
		uint64_t(0xE1D9B2EB8F02F3EE), uint64_t(0x29391394D3D22544),
		uint64_t(0xC8E0A17F5CD0D6AA), uint64_t(0xB58CC6A5F7A26EAD),
		uint64_t(0x8193FB08238F02C2), uint64_t(0xD5C68F465B2F9F81),
		uint64_t(0xFCFF9CD288FDBAC5), uint64_t(0x77059157F359DC47),
		uint64_t(0x1D262E3907FF492B), uint64_t(0xFB582233E59AC557),
		uint64_t(0xDDB2BCE242F8B673), uint64_t(0x2577B76248E096CF),
		uint64_t(0x6F99C4A6D83DA74C), uint64_t(0xC1147E41EB795701),
		uint64_t(0xF48BAF76912A9337) }),

	HashLibUInt64Array({ uint64_t(0x3EF29D249B2C0A19),
		uint64_t(0xE9E16322B6F8622F), uint64_t(0x5536994047757F7A),
		uint64_t(0x9F4D56D5A47B0B33), uint64_t(0x822567466AA1174C),
		uint64_t(0xB8F5057DEB082FB2), uint64_t(0xCC48C10BF4475F53),
		uint64_t(0x373088D4275DEC3A), uint64_t(0x968F4325180AED10),
		uint64_t(0x173D232CF7016151), uint64_t(0xAE4ED09F946FCC13),
		uint64_t(0xFD4B4741C4539873), uint64_t(0x1B5B3F0DD9933765),
		uint64_t(0x2FFCB0967B644052), uint64_t(0xE02376D20A89840C),
		uint64_t(0xA3AE3A70329B18D7), uint64_t(0x419CBD2335DE8526),
		uint64_t(0xFAFEBF115B7C3199), uint64_t(0x0397074F85AA9B0D),
		uint64_t(0xC58AD4FB4836B970), uint64_t(0xBEC60BE3FC4104A8),
		uint64_t(0x1EFF36DC4B708772), uint64_t(0x131FDC33ED8453B6),
		uint64_t(0x0844E33E341764D3), uint64_t(0x0FF11B6EAB38CD39),
		uint64_t(0x64351F0A7761B85A), uint64_t(0x3B5694F509CFBA0E),
		uint64_t(0x30857084B87245D0), uint64_t(0x47AFB3BD2297AE3C),
		uint64_t(0xF2BA5C2F6F6B554A), uint64_t(0x74BDC4761F4F70E1),
		uint64_t(0xCFDFC64471EDC45E), uint64_t(0xE610784C1DC0AF16),
		uint64_t(0x7ACA29D63C113F28), uint64_t(0x2DED411776A859AF),
		uint64_t(0xAC5F211E99A3D5EE), uint64_t(0xD484F949A87EF33B),
		uint64_t(0x3CE36CA596E013E4), uint64_t(0xD120F0983A9D432C),
		uint64_t(0x6BC40464DC597563), uint64_t(0x69D5F5E5D1956C9E),
		uint64_t(0x9AE95F043698BB24), uint64_t(0xC9ECC8DA66A4EF44),
		uint64_t(0xD69508C8A5B2EAC6), uint64_t(0xC40C2235C0503B80),
		uint64_t(0x38C193BA8C652103), uint64_t(0x1CEEC75D46BC9E8F),
		uint64_t(0xD331011937515AD1), uint64_t(0xD8E2E56886ECA50F),
		uint64_t(0xB137108D5779C991), uint64_t(0x709F3B6905CA4206),
		uint64_t(0x4FEB50831680CAEF), uint64_t(0xEC456AF3241BD238),
		uint64_t(0x58D673AFE181ABBE), uint64_t(0x242F54E7CAD9BF8C),
		uint64_t(0x0211F1810DCC19FD), uint64_t(0x90BC4DBB0F43C60A),
		uint64_t(0x9518446A9DA0761D), uint64_t(0xA1BFCBF13F57012A),
		uint64_t(0x2BDE4F8961E172B5), uint64_t(0x27B853A84F732481),
		uint64_t(0xB0B1E643DF1F4B61), uint64_t(0x18CC38425C39AC68),
		uint64_t(0xD2B7F7D7BF37D821), uint64_t(0x3103864A3014C720),
		uint64_t(0x14AA246372ABFA5C), uint64_t(0x6E600DB54EBAC574),
		uint64_t(0x394765740403A3F3), uint64_t(0x09C215F0BC71E623),
		uint64_t(0x2A58B947E987F045), uint64_t(0x7B4CDF18B477BDD8),
		uint64_t(0x9709B5EB906C6FE0), uint64_t(0x73083C268060D90B),
		uint64_t(0xFEDC400E41F9037E), uint64_t(0x284948C6E44BE9B8),
		uint64_t(0x728ECAE808065BFB), uint64_t(0x06330E9E17492B1A),
		uint64_t(0x5950856169E7294E), uint64_t(0xBAE4F4FCE6C4364F),
		uint64_t(0xCA7BCF95E30E7449), uint64_t(0x7D7FD186A33E96C2),
		uint64_t(0x52836110D85AD690), uint64_t(0x4DFAA1021B4CD312),
		uint64_t(0x913ABB75872544FA), uint64_t(0xDD46ECB9140F1518),
		uint64_t(0x3D659A6B1E869114), uint64_t(0xC23F2CABD719109A),
		uint64_t(0xD713FE062DD46836), uint64_t(0xD0A60656B2FBC1DC),
		uint64_t(0x221C5A79DD909496), uint64_t(0xEFD26DBCA1B14935),
		uint64_t(0x0E77EDA0235E4FC9), uint64_t(0xCBFD395B6B68F6B9),
		uint64_t(0x0DE0EAEFA6F4D4C4), uint64_t(0x0422FF1F1A8532E7),
		uint64_t(0xF969B85EDED6AA94), uint64_t(0x7F6E2007AEF28F3F),
		uint64_t(0x3AD0623B81A938FE), uint64_t(0x6624EE8B7AADA1A7),
		uint64_t(0xB682E8DDC856607B), uint64_t(0xA78CC56F281E2A30),
		uint64_t(0xC79B257A45FAA08D), uint64_t(0x5B4174E0642B30B3),
		uint64_t(0x5F638BFF7EAE0254), uint64_t(0x4BC9AF9C0C05F808),
		uint64_t(0xCE59308AF98B46AE), uint64_t(0x8FC58DA9CC55C388),
		uint64_t(0x803496C7676D0EB1), uint64_t(0xF33CAAE1E70DD7BA),
		uint64_t(0xBB6202326EA2B4BF), uint64_t(0xD5020F87201871CB),
		uint64_t(0x9D5CA754A9B712CE), uint64_t(0x841669D87DE83C56),
		uint64_t(0x8A6184785EB6739F), uint64_t(0x420BBA6CB0741E2B),
		uint64_t(0xF12D5B60EAC1CE47), uint64_t(0x76AC35F71283691C),
		uint64_t(0x2C6BB7D9FECEDB5F), uint64_t(0xFCCDB18F4C351A83),
		uint64_t(0x1F79C012C3160582), uint64_t(0xF0ABADAE62A74CB7),
		uint64_t(0xE1A5801C82EF06FC), uint64_t(0x67A21845F2CB2357),
		uint64_t(0x5114665F5DF04D9D), uint64_t(0xBF40FD2D74278658),
		uint64_t(0xA0393D3FB73183DA), uint64_t(0x05A409D192E3B017),
		uint64_t(0xA9FB28CF0B4065F9), uint64_t(0x25A9A22942BF3D7C),
		uint64_t(0xDB75E22703463E02), uint64_t(0xB326E10C5AB5D06C),
		uint64_t(0xE7968E8295A62DE6), uint64_t(0xB973F3B3636EAD42),
		uint64_t(0xDF571D3819C30CE5), uint64_t(0xEE549B7229D7CBC5),
		uint64_t(0x12992AFD65E2D146), uint64_t(0xF8EF4E9056B02864),
		uint64_t(0xB7041E134030E28B), uint64_t(0xC02EDD2ADAD50967),
		uint64_t(0x932B4AF48AE95D07), uint64_t(0x6FE6FB7BC6DC4784),
		uint64_t(0x239AACB755F61666), uint64_t(0x401A4BEDBDB807D6),
		uint64_t(0x485EA8D389AF6305), uint64_t(0xA41BC220ADB4B13D),
		uint64_t(0x753B32B89729F211), uint64_t(0x997E584BB3322029),
		uint64_t(0x1D683193CEDA1C7F), uint64_t(0xFF5AB6C0C99F818E),
		uint64_t(0x16BBD5E27F67E3A1), uint64_t(0xA59D34EE25D233CD),
		uint64_t(0x98F8AE853B54A2D9), uint64_t(0x6DF70AFACB105E79),
		uint64_t(0x795D2E99B9BBA425), uint64_t(0x8E437B6744334178),
		uint64_t(0x0186F6CE886682F0), uint64_t(0xEBF092A3BB347BD2),
		uint64_t(0xBCD7FA62F18D1D55), uint64_t(0xADD9D7D011C5571E),
		uint64_t(0x0BD3E471B1BDFFDE), uint64_t(0xAA6C2F808EEAFEF4),
		uint64_t(0x5EE57D31F6C880A4), uint64_t(0xF50FA47FF044FCA0),
		uint64_t(0x1ADDC9C351F5B595), uint64_t(0xEA76646D3352F922),
		uint64_t(0x0000000000000000), uint64_t(0x85909F16F58EBEA6),
		uint64_t(0x46294573AAF12CCC), uint64_t(0x0A5512BF39DB7D2E),
		uint64_t(0x78DBD85731DD26D5), uint64_t(0x29CFBE086C2D6B48),
		uint64_t(0x218B5D36583A0F9B), uint64_t(0x152CD2ADFACD78AC),
		uint64_t(0x83A39188E2C795BC), uint64_t(0xC3B9DA655F7F926A),
		uint64_t(0x9ECBA01B2C1D89C3), uint64_t(0x07B5F8509F2FA9EA),
		uint64_t(0x7EE8D6C926940DCF), uint64_t(0x36B67E1AAF3B6ECA),
		uint64_t(0x86079859702425AB), uint64_t(0xFB7849DFD31AB369),
		uint64_t(0x4C7C57CC932A51E2), uint64_t(0xD96413A60E8A27FF),
		uint64_t(0x263EA566C715A671), uint64_t(0x6C71FC344376DC89),
		uint64_t(0x4A4F595284637AF8), uint64_t(0xDAF314E98B20BCF2),
		uint64_t(0x572768C14AB96687), uint64_t(0x1088DB7C682EC8BB),
		uint64_t(0x887075F9537A6A62), uint64_t(0x2E7A4658F302C2A2),
		uint64_t(0x619116DBE582084D), uint64_t(0xA87DDE018326E709),
		uint64_t(0xDCC01A779C6997E8), uint64_t(0xEDC39C3DAC7D50C8),
		uint64_t(0xA60A33A1A078A8C0), uint64_t(0xC1A82BE452B38B97),
		uint64_t(0x3F746BEA134A88E9), uint64_t(0xA228CCBEBAFD9A27),
		uint64_t(0xABEAD94E068C7C04), uint64_t(0xF48952B178227E50),
		uint64_t(0x5CF48CB0FB049959), uint64_t(0x6017E0156DE48ABD),
		uint64_t(0x4438B4F2A73D3531), uint64_t(0x8C528AE649FF5885),
		uint64_t(0xB515EF924DFCFB76), uint64_t(0x0C661C212E925634),
		uint64_t(0xB493195CC59A7986), uint64_t(0x9CDA519A21D1903E),
		uint64_t(0x32948105B5BE5C2D), uint64_t(0x194ACE8CD45F2E98),
		uint64_t(0x438D4CA238129CDB), uint64_t(0x9B6FA9CABEFE39D4),
		uint64_t(0x81B26009EF0B8C41), uint64_t(0xDED1EBF691A58E15),
		uint64_t(0x4E6DA64D9EE6481F), uint64_t(0x54B06F8ECF13FD8A),
		uint64_t(0x49D85E1D01C9E1F5), uint64_t(0xAFC826511C094EE3),
		uint64_t(0xF698A33075EE67AD), uint64_t(0x5AC7822EEC4DB243),
		uint64_t(0x8DD47C28C199DA75), uint64_t(0x89F68337DB1CE892),
		uint64_t(0xCDCE37C57C21DDA3), uint64_t(0x530597DE503C5460),
		uint64_t(0x6A42F2AA543FF793), uint64_t(0x5D727A7E73621BA9),
		uint64_t(0xE232875307459DF1), uint64_t(0x56A19E0FC2DFE477),
		uint64_t(0xC61DD3B4CD9C227D), uint64_t(0xE5877F03986A341B),
		uint64_t(0x949EB2A415C6F4ED), uint64_t(0x6206119460289340),
		uint64_t(0x6380E75AE84E11B0), uint64_t(0x8BE772B6D6D0F16F),
		uint64_t(0x50929091D596CF6D), uint64_t(0xE86795EC3E9EE0DF),
		uint64_t(0x7CF927482B581432), uint64_t(0xC86A3E14EEC26DB4),
		uint64_t(0x7119CDA78DACC0F6), uint64_t(0xE40189CD100CB6EB),
		uint64_t(0x92ADBC3A028FDFF7), uint64_t(0xB2A017C2D2D3529C),
		uint64_t(0x200DABF8D05C8D6B), uint64_t(0x34A78F9BA2F77737),
		uint64_t(0xE3B4719D8F231F01), uint64_t(0x45BE423C2F5BB7C1),
		uint64_t(0xF71E55FEFD88E55D), uint64_t(0x6853032B59F3EE6E),
		uint64_t(0x65B3E9C4FF073AAA), uint64_t(0x772AC3399AE5EBEC),
		uint64_t(0x87816E97F842A75B), uint64_t(0x110E2DB2E0484A4B),
		uint64_t(0x331277CB3DD8DEDD), uint64_t(0xBD510CAC79EB9FA5),
		uint64_t(0x352179552A91F5C7) }),

	HashLibUInt64Array({ uint64_t(0x8AB0A96846E06A6D),
		uint64_t(0x43C7E80B4BF0B33A), uint64_t(0x08C9B3546B161EE5),
		uint64_t(0x39F1C235EBA990BE), uint64_t(0xC1BEF2376606C7B2),
		uint64_t(0x2C209233614569AA), uint64_t(0xEB01523B6FC3289A),
		uint64_t(0x946953AB935ACEDD), uint64_t(0x272838F63E13340E),
		uint64_t(0x8B0455ECA12BA052), uint64_t(0x77A1B2C4978FF8A2),
		uint64_t(0xA55122CA13E54086), uint64_t(0x2276135862D3F1CD),
		uint64_t(0xDB8DDFDE08B76CFE), uint64_t(0x5D1E12C89E4A178A),
		uint64_t(0x0E56816B03969867), uint64_t(0xEE5F79953303ED59),
		uint64_t(0xAFED748BAB78D71D), uint64_t(0x6D929F2DF93E53EE),
		uint64_t(0xF5D8A8F8BA798C2A), uint64_t(0xF619B1698E39CF6B),
		uint64_t(0x95DDAF2F749104E2), uint64_t(0xEC2A9C80E0886427),
		uint64_t(0xCE5C8FD8825B95EA), uint64_t(0xC4E0D9993AC60271),
		uint64_t(0x4699C3A5173076F9), uint64_t(0x3D1B151F50A29F42),
		uint64_t(0x9ED505EA2BC75946), uint64_t(0x34665ACFDC7F4B98),
		uint64_t(0x61B1FB53292342F7), uint64_t(0xC721C0080E864130),
		uint64_t(0x8693CD1696FD7B74), uint64_t(0x872731927136B14B),
		uint64_t(0xD3446C8A63A1721B), uint64_t(0x669A35E8A6680E4A),
		uint64_t(0xCAB658F239509A16), uint64_t(0xA4E5DE4EF42E8AB9),
		uint64_t(0x37A7435EE83F08D9), uint64_t(0x134E6239E26C7F96),
		uint64_t(0x82791A3C2DF67488), uint64_t(0x3F6EF00A8329163C),
		uint64_t(0x8E5A7E42FDEB6591), uint64_t(0x5CAAEE4C7981DDB5),
		uint64_t(0x19F234785AF1E80D), uint64_t(0x255DDDE3ED98BD70),
		uint64_t(0x50898A32A99CCCAC), uint64_t(0x28CA4519DA4E6656),
		uint64_t(0xAE59880F4CB31D22), uint64_t(0x0D9798FA37D6DB26),
		uint64_t(0x32F968F0B4FFCD1A), uint64_t(0xA00F09644F258545),
		uint64_t(0xFA3AD5175E24DE72), uint64_t(0xF46C547C5DB24615),
		uint64_t(0x713E80FBFF0F7E20), uint64_t(0x7843CF2B73D2AAFA),
		uint64_t(0xBD17EA36AEDF62B4), uint64_t(0xFD111BACD16F92CF),
		uint64_t(0x4ABAA7DBC72D67E0), uint64_t(0xB3416B5DAD49FAD3),
		uint64_t(0xBCA316B24914A88B), uint64_t(0x15D150068AECF914),
		uint64_t(0xE27C1DEBE31EFC40), uint64_t(0x4FE48C759BEDA223),
		uint64_t(0x7EDCFD141B522C78), uint64_t(0x4E5070F17C26681C),
		uint64_t(0xE696CAC15815F3BC), uint64_t(0x35D2A64B3BB481A7),
		uint64_t(0x800CFF29FE7DFDF6), uint64_t(0x1ED9FAC3D5BAA4B0),
		uint64_t(0x6C2663A91EF599D1), uint64_t(0x03C1199134404341),
		uint64_t(0xF7AD4DED69F20554), uint64_t(0xCD9D9649B61BD6AB),
		uint64_t(0xC8C3BDE7EADB1368), uint64_t(0xD131899FB02AFB65),
		uint64_t(0x1D18E352E1FAE7F1), uint64_t(0xDA39235AEF7CA6C1),
		uint64_t(0xA1BBF5E0A8EE4F7A), uint64_t(0x91377805CF9A0B1E),
		uint64_t(0x3138716180BF8E5B), uint64_t(0xD9F83ACBDB3CE580),
		uint64_t(0x0275E515D38B897E), uint64_t(0x472D3F21F0FBBCC6),
		uint64_t(0x2D946EB7868EA395), uint64_t(0xBA3C248D21942E09),
		uint64_t(0xE7223645BFDE3983), uint64_t(0xFF64FEB902E41BB1),
		uint64_t(0xC97741630D10D957), uint64_t(0xC3CB1722B58D4ECC),
		uint64_t(0xA27AEC719CAE0C3B), uint64_t(0x99FECB51A48C15FB),
		uint64_t(0x1465AC826D27332B), uint64_t(0xE1BD047AD75EBF01),
		uint64_t(0x79F733AF941960C5), uint64_t(0x672EC96C41A3C475),
		uint64_t(0xC27FEBA6524684F3), uint64_t(0x64EFD0FD75E38734),
		uint64_t(0xED9E60040743AE18), uint64_t(0xFB8E2993B9EF144D),
		uint64_t(0x38453EB10C625A81), uint64_t(0x6978480742355C12),
		uint64_t(0x48CF42CE14A6EE9E), uint64_t(0x1CAC1FD606312DCE),
		uint64_t(0x7B82D6BA4792E9BB), uint64_t(0x9D141C7B1F871A07),
		uint64_t(0x5616B80DC11C4A2E), uint64_t(0xB849C198F21FA777),
		uint64_t(0x7CA91801C8D9A506), uint64_t(0xB1348E487EC273AD),
		uint64_t(0x41B20D1E987B3A44), uint64_t(0x7460AB55A3CFBBE3),
		uint64_t(0x84E628034576F20A), uint64_t(0x1B87D16D897A6173),
		uint64_t(0x0FE27DEFE45D5258), uint64_t(0x83CDE6B8CA3DBEB7),
		uint64_t(0x0C23647ED01D1119), uint64_t(0x7A362A3EA0592384),
		uint64_t(0xB61F40F3F1893F10), uint64_t(0x75D457D1440471DC),
		uint64_t(0x4558DA34237035B8), uint64_t(0xDCA6116587FC2043),
		uint64_t(0x8D9B67D3C9AB26D0), uint64_t(0x2B0B5C88EE0E2517),
		uint64_t(0x6FE77A382AB5DA90), uint64_t(0x269CC472D9D8FE31),
		uint64_t(0x63C41E46FAA8CB89), uint64_t(0xB7ABBC771642F52F),
		uint64_t(0x7D1DE4852F126F39), uint64_t(0xA8C6BA3024339BA0),
		uint64_t(0x600507D7CEE888C8), uint64_t(0x8FEE82C61A20AFAE),
		uint64_t(0x57A2448926D78011), uint64_t(0xFCA5E72836A458F0),
		uint64_t(0x072BCEBB8F4B4CBD), uint64_t(0x497BBE4AF36D24A1),
		uint64_t(0x3CAFE99BB769557D), uint64_t(0x12FA9EBD05A7B5A9),
		uint64_t(0xE8C04BAA5B836BDB), uint64_t(0x4273148FAC3B7905),
		uint64_t(0x908384812851C121), uint64_t(0xE557D3506C55B0FD),
		uint64_t(0x72FF996ACB4F3D61), uint64_t(0x3EDA0C8E64E2DC03),
		uint64_t(0xF0868356E6B949E9), uint64_t(0x04EAD72ABB0B0FFC),
		uint64_t(0x17A4B5135967706A), uint64_t(0xE3C8E16F04D5367F),
		uint64_t(0xF84F30028DAF570C), uint64_t(0x1846C8FCBD3A2232),
		uint64_t(0x5B8120F7F6CA9108), uint64_t(0xD46FA231ECEA3EA6),
		uint64_t(0x334D947453340725), uint64_t(0x58403966C28AD249),
		uint64_t(0xBED6F3A79A9F21F5), uint64_t(0x68CCB483A5FE962D),
		uint64_t(0xD085751B57E1315A), uint64_t(0xFED0023DE52FD18E),
		uint64_t(0x4B0E5B5F20E6ADDF), uint64_t(0x1A332DE96EB1AB4C),
		uint64_t(0xA3CE10F57B65C604), uint64_t(0x108F7BA8D62C3CD7),
		uint64_t(0xAB07A3A11073D8E1), uint64_t(0x6B0DAD1291BED56C),
		uint64_t(0xF2F366433532C097), uint64_t(0x2E557726B2CEE0D4),
		uint64_t(0x0000000000000000), uint64_t(0xCB02A476DE9B5029),
		uint64_t(0xE4E32FD48B9E7AC2), uint64_t(0x734B65EE2C84F75E),
		uint64_t(0x6E5386BCCD7E10AF), uint64_t(0x01B4FC84E7CBCA3F),
		uint64_t(0xCFE8735C65905FD5), uint64_t(0x3613BFDA0FF4C2E6),
		uint64_t(0x113B872C31E7F6E8), uint64_t(0x2FE18BA255052AEB),
		uint64_t(0xE974B72EBC48A1E4), uint64_t(0x0ABC5641B89D979B),
		uint64_t(0xB46AA5E62202B66E), uint64_t(0x44EC26B0C4BBFF87),
		uint64_t(0xA6903B5B27A503C7), uint64_t(0x7F680190FC99E647),
		uint64_t(0x97A84A3AA71A8D9C), uint64_t(0xDD12EDE16037EA7C),
		uint64_t(0xC554251DDD0DC84E), uint64_t(0x88C54C7D956BE313),
		uint64_t(0x4D91696048662B5D), uint64_t(0xB08072CC9909B992),
		uint64_t(0xB5DE5962C5C97C51), uint64_t(0x81B803AD19B637C9),
		uint64_t(0xB2F597D94A8230EC), uint64_t(0x0B08AAC55F565DA4),
		uint64_t(0xF1327FD2017283D6), uint64_t(0xAD98919E78F35E63),
		uint64_t(0x6AB9519676751F53), uint64_t(0x24E921670A53774F),
		uint64_t(0xB9FD3D1C15D46D48), uint64_t(0x92F66194FBDA485F),
		uint64_t(0x5A35DC7311015B37), uint64_t(0xDED3F4705477A93D),
		uint64_t(0xC00A0EB381CD0D8D), uint64_t(0xBB88D809C65FE436),
		uint64_t(0x16104997BEACBA55), uint64_t(0x21B70AC95693B28C),
		uint64_t(0x59F4C5E225411876), uint64_t(0xD5DB5EB50B21F499),
		uint64_t(0x55D7A19CF55C096F), uint64_t(0xA97246B4C3F8519F),
		uint64_t(0x8552D487A2BD3835), uint64_t(0x54635D181297C350),
		uint64_t(0x23C2EFDC85183BF2), uint64_t(0x9F61F96ECC0C9379),
		uint64_t(0x534893A39DDC8FED), uint64_t(0x5EDF0B59AA0A54CB),
		uint64_t(0xAC2C6D1A9F38945C), uint64_t(0xD7AEBBA0D8AA7DE7),
		uint64_t(0x2ABFA00C09C5EF28), uint64_t(0xD84CC64F3CF72FBF),
		uint64_t(0x2003F64DB15878B3), uint64_t(0xA724C7DFC06EC9F8),
		uint64_t(0x069F323F68808682), uint64_t(0xCC296ACD51D01C94),
		uint64_t(0x055E2BAE5CC0C5C3), uint64_t(0x6270E2C21D6301B6),
		uint64_t(0x3B842720382219C0), uint64_t(0xD2F0900E846AB824),
		uint64_t(0x52FC6F277A1745D2), uint64_t(0xC6953C8CE94D8B0F),
		uint64_t(0xE009F8FE3095753E), uint64_t(0x655B2C7992284D0B),
		uint64_t(0x984A37D54347DFC4), uint64_t(0xEAB5AEBF8808E2A5),
		uint64_t(0x9A3FD2C090CC56BA), uint64_t(0x9CA0E0FFF84CD038),
		uint64_t(0x4C2595E4AFADE162), uint64_t(0xDF6708F4B3BC6302),
		uint64_t(0xBF620F237D54EBCA), uint64_t(0x93429D101C118260),
		uint64_t(0x097D4FD08CDDD4DA), uint64_t(0x8C2F9B572E60ECEF),
		uint64_t(0x708A7C7F18C4B41F), uint64_t(0x3A30DBA4DFE9D3FF),
		uint64_t(0x4006F19A7FB0F07B), uint64_t(0x5F6BF7DD4DC19EF4),
		uint64_t(0x1F6D064732716E8F), uint64_t(0xF9FBCC866A649D33),
		uint64_t(0x308C8DE567744464), uint64_t(0x8971B0F972A0292C),
		uint64_t(0xD61A47243F61B7D8), uint64_t(0xEFEB8511D4C82766),
		uint64_t(0x961CB6BE40D147A3), uint64_t(0xAAB35F25F7B812DE),
		uint64_t(0x76154E407044329D), uint64_t(0x513D76B64E570693),
		uint64_t(0xF3479AC7D2F90AA8), uint64_t(0x9B8B2E4477079C85),
		uint64_t(0x297EB99D3D85AC69) }),

	HashLibUInt64Array({ uint64_t(0x7E37E62DFC7D40C3),
		uint64_t(0x776F25A4EE939E5B), uint64_t(0xE045C850DD8FB5AD),
		uint64_t(0x86ED5BA711FF1952), uint64_t(0xE91D0BD9CF616B35),
		uint64_t(0x37E0AB256E408FFB), uint64_t(0x9607F6C031025A7A),
		uint64_t(0x0B02F5E116D23C9D), uint64_t(0xF3D8486BFB50650C),
		uint64_t(0x621CFF27C40875F5), uint64_t(0x7D40CB71FA5FD34A),
		uint64_t(0x6DAA6616DAA29062), uint64_t(0x9F5F354923EC84E2),
		uint64_t(0xEC847C3DC507C3B3), uint64_t(0x025A3668043CE205),
		uint64_t(0xA8BF9E6C4DAC0B19), uint64_t(0xFA808BE2E9BEBB94),
		uint64_t(0xB5B99C5277C74FA3), uint64_t(0x78D9BC95F0397BCC),
		uint64_t(0xE332E50CDBAD2624), uint64_t(0xC74FCE129332797E),
		uint64_t(0x1729ECEB2EA709AB), uint64_t(0xC2D6B9F69954D1F8),
		uint64_t(0x5D898CBFBAB8551A), uint64_t(0x859A76FB17DD8ADB),
		uint64_t(0x1BE85886362F7FB5), uint64_t(0xF6413F8FF136CD8A),
		uint64_t(0xD3110FA5BBB7E35C), uint64_t(0x0A2FEED514CC4D11),
		uint64_t(0xE83010EDCD7F1AB9), uint64_t(0xA1E75DE55F42D581),
		uint64_t(0xEEDE4A55C13B21B6), uint64_t(0xF2F5535FF94E1480),
		uint64_t(0x0CC1B46D1888761E), uint64_t(0xBCE15FDB6529913B),
		uint64_t(0x2D25E8975A7181C2), uint64_t(0x71817F1CE2D7A554),
		uint64_t(0x2E52C5CB5C53124B), uint64_t(0xF9F7A6BEEF9C281D),
		uint64_t(0x9E722E7D21F2F56E), uint64_t(0xCE170D9B81DCA7E6),
		uint64_t(0x0E9B82051CB4941B), uint64_t(0x1E712F623C49D733),
		uint64_t(0x21E45CFA42F9F7DC), uint64_t(0xCB8E7A7F8BBA0F60),
		uint64_t(0x8E98831A010FB646), uint64_t(0x474CCF0D8E895B23),
		uint64_t(0xA99285584FB27A95), uint64_t(0x8CC2B57205335443),
		uint64_t(0x42D5B8E984EFF3A5), uint64_t(0x012D1B34021E718C),
		uint64_t(0x57A6626AAE74180B), uint64_t(0xFF19FC06E3D81312),
		uint64_t(0x35BA9D4D6A7C6DFE), uint64_t(0xC9D44C178F86ED65),
		uint64_t(0x506523E6A02E5288), uint64_t(0x03772D5C06229389),
		uint64_t(0x8B01F4FE0B691EC0), uint64_t(0xF8DABD8AED825991),
		uint64_t(0x4C4E3AEC985B67BE), uint64_t(0xB10DF0827FBF96A9),
		uint64_t(0x6A69279AD4F8DAE1), uint64_t(0xE78689DCD3D5FF2E),
		uint64_t(0x812E1A2B1FA553D1), uint64_t(0xFBAD90D6EBA0CA18),
		uint64_t(0x1AC543B234310E39), uint64_t(0x1604F7DF2CB97827),
		uint64_t(0xA6241C6951189F02), uint64_t(0x753513CCEAAF7C5E),
		uint64_t(0x64F2A59FC84C4EFA), uint64_t(0x247D2B1E489F5F5A),
		uint64_t(0xDB64D718AB474C48), uint64_t(0x79F4A7A1F2270A40),
		uint64_t(0x1573DA832A9BEBAE), uint64_t(0x3497867968621C72),
		uint64_t(0x514838D2A2302304), uint64_t(0xF0AF6537FD72F685),
		uint64_t(0x1D06023E3A6B44BA), uint64_t(0x678588C3CE6EDD73),
		uint64_t(0x66A893F7CC70ACFF), uint64_t(0xD4D24E29B5EDA9DF),
		uint64_t(0x3856321470EA6A6C), uint64_t(0x07C3418C0E5A4A83),
		uint64_t(0x2BCBB22F5635BACD), uint64_t(0x04B46CD00878D90A),
		uint64_t(0x06EE5AB80C443B0F), uint64_t(0x3B211F4876C8F9E5),
		uint64_t(0x0958C38912EEDE98), uint64_t(0xD14B39CDBF8B0159),
		uint64_t(0x397B292072F41BE0), uint64_t(0x87C0409313E168DE),
		uint64_t(0xAD26E98847CAA39F), uint64_t(0x4E140C849C6785BB),
		uint64_t(0xD5FF551DB7F3D853), uint64_t(0xA0CA46D15D5CA40D),
		uint64_t(0xCD6020C787FE346F), uint64_t(0x84B76DCF15C3FB57),
		uint64_t(0xDEFDA0FCA121E4CE), uint64_t(0x4B8D7B6096012D3D),
		uint64_t(0x9AC642AD298A2C64), uint64_t(0x0875D8BD10F0AF14),
		uint64_t(0xB357C6EA7B8374AC), uint64_t(0x4D6321D89A451632),
		uint64_t(0xEDA96709C719B23F), uint64_t(0xF76C24BBF328BC06),
		uint64_t(0xC662D526912C08F2), uint64_t(0x3CE25EC47892B366),
		uint64_t(0xB978283F6F4F39BD), uint64_t(0xC08C8F9E9D6833FD),
		uint64_t(0x4F3917B09E79F437), uint64_t(0x593DE06FB2C08C10),
		uint64_t(0xD6887841B1D14BDA), uint64_t(0x19B26EEE32139DB0),
		uint64_t(0xB494876675D93E2F), uint64_t(0x825937771987C058),
		uint64_t(0x90E9AC783D466175), uint64_t(0xF1827E03FF6C8709),
		uint64_t(0x945DC0A8353EB87F), uint64_t(0x4516F9658AB5B926),
		uint64_t(0x3F9573987EB020EF), uint64_t(0xB855330B6D514831),
		uint64_t(0x2AE6A91B542BCB41), uint64_t(0x6331E413C6160479),
		uint64_t(0x408F8E8180D311A0), uint64_t(0xEFF35161C325503A),
		uint64_t(0xD06622F9BD9570D5), uint64_t(0x8876D9A20D4B8D49),
		uint64_t(0xA5533135573A0C8B), uint64_t(0xE168D364DF91C421),
		uint64_t(0xF41B09E7F50A2F8F), uint64_t(0x12B09B0F24C1A12D),
		uint64_t(0xDA49CC2CA9593DC4), uint64_t(0x1F5C34563E57A6BF),
		uint64_t(0x54D14F36A8568B82), uint64_t(0xAF7CDFE043F6419A),
		uint64_t(0xEA6A2685C943F8BC), uint64_t(0xE5DCBFB4D7E91D2B),
		uint64_t(0xB27ADDDE799D0520), uint64_t(0x6B443CAED6E6AB6D),
		uint64_t(0x7BAE91C9F61BE845), uint64_t(0x3EB868AC7CAE5163),
		uint64_t(0x11C7B65322E332A4), uint64_t(0xD23C1491B9A992D0),
		uint64_t(0x8FB5982E0311C7CA), uint64_t(0x70AC6428E0C9D4D8),
		uint64_t(0x895BC2960F55FCC5), uint64_t(0x76423E90EC8DEFD7),
		uint64_t(0x6FF0507EDE9E7267), uint64_t(0x3DCF45F07A8CC2EA),
		uint64_t(0x4AA06054941F5CB1), uint64_t(0x5810FB5BB0DEFD9C),
		uint64_t(0x5EFEA1E3BC9AC693), uint64_t(0x6EDD4B4ADC8003EB),
		uint64_t(0x741808F8E8B10DD2), uint64_t(0x145EC1B728859A22),
		uint64_t(0x28BC9F7350172944), uint64_t(0x270A06424EBDCCD3),
		uint64_t(0x972AEDF4331C2BF6), uint64_t(0x059977E40A66A886),
		uint64_t(0x2550302A4A812ED6), uint64_t(0xDD8A8DA0A7037747),
		uint64_t(0xC515F87A970E9B7B), uint64_t(0x3023EAA9601AC578),
		uint64_t(0xB7E3AA3A73FBADA6), uint64_t(0x0FB699311EAAE597),
		uint64_t(0x0000000000000000), uint64_t(0x310EF19D6204B4F4),
		uint64_t(0x229371A644DB6455), uint64_t(0x0DECAF591A960792),
		uint64_t(0x5CA4978BB8A62496), uint64_t(0x1C2B190A38753536),
		uint64_t(0x41A295B582CD602C), uint64_t(0x3279DCC16426277D),
		uint64_t(0xC1A194AA9F764271), uint64_t(0x139D803B26DFD0A1),
		uint64_t(0xAE51C4D441E83016), uint64_t(0xD813FA44AD65DFC1),
		uint64_t(0xAC0BF2BC45D4D213), uint64_t(0x23BE6A9246C515D9),
		uint64_t(0x49D74D08923DCF38), uint64_t(0x9D05032127D066E7),
		uint64_t(0x2F7FDEFF5E4D63C7), uint64_t(0xA47E2A0155247D07),
		uint64_t(0x99B16FF12FA8BFED), uint64_t(0x4661D4398C972AAF),
		uint64_t(0xDFD0BBC8A33F9542), uint64_t(0xDCA79694A51D06CB),
		uint64_t(0xB020EBB67DA1E725), uint64_t(0xBA0F0563696DAA34),
		uint64_t(0xE4F1A480D5F76CA7), uint64_t(0xC438E34E9510EAF7),
		uint64_t(0x939E81243B64F2FC), uint64_t(0x8DEFAE46072D25CF),
		uint64_t(0x2C08F3A3586FF04E), uint64_t(0xD7A56375B3CF3A56),
		uint64_t(0x20C947CE40E78650), uint64_t(0x43F8A3DD86F18229),
		uint64_t(0x568B795EAC6A6987), uint64_t(0x8003011F1DBB225D),
		uint64_t(0xF53612D3F7145E03), uint64_t(0x189F75DA300DEC3C),
		uint64_t(0x9570DB9C3720C9F3), uint64_t(0xBB221E576B73DBB8),
		uint64_t(0x72F65240E4F536DD), uint64_t(0x443BE25188ABC8AA),
		uint64_t(0xE21FFE38D9B357A8), uint64_t(0xFD43CA6EE7E4F117),
		uint64_t(0xCAA3614B89A47EEC), uint64_t(0xFE34E732E1C6629E),
		uint64_t(0x83742C431B99B1D4), uint64_t(0xCF3A16AF83C2D66A),
		uint64_t(0xAAE5A8044990E91C), uint64_t(0x26271D764CA3BD5F),
		uint64_t(0x91C4B74C3F5810F9), uint64_t(0x7C6DD045F841A2C6),
		uint64_t(0x7F1AFD19FE63314F), uint64_t(0xC8F957238D989CE9),
		uint64_t(0xA709075D5306EE8E), uint64_t(0x55FC5402AA48FA0E),
		uint64_t(0x48FA563C9023BEB4), uint64_t(0x65DFBEABCA523F76),
		uint64_t(0x6C877D22D8BCE1EE), uint64_t(0xCC4D3BF385E045E3),
		uint64_t(0xBEBB69B36115733E), uint64_t(0x10EAAD6720FD4328),
		uint64_t(0xB6CEB10E71E5DC2A), uint64_t(0xBDCC44EF6737E0B7),
		uint64_t(0x523F158EA412B08D), uint64_t(0x989C74C52DB6CE61),
		uint64_t(0x9BEB59992B945DE8), uint64_t(0x8A2CEFCA09776F4C),
		uint64_t(0xA3BD6B8D5B7E3784), uint64_t(0xEB473DB1CB5D8930),
		uint64_t(0xC3FBA2C29B4AA074), uint64_t(0x9C28181525CE176B),
		uint64_t(0x683311F2D0C438E4), uint64_t(0x5FD3BAD7BE84B71F),
		uint64_t(0xFC6ED15AE5FA809B), uint64_t(0x36CDB0116C5EFE77),
		uint64_t(0x29918447520958C8), uint64_t(0xA29070B959604608),
		uint64_t(0x53120EBAA60CC101), uint64_t(0x3A0C047C74D68869),
		uint64_t(0x691E0AC6D2DA4968), uint64_t(0x73DB4974E6EB4751),
		uint64_t(0x7A838AFDF40599C9), uint64_t(0x5A4ACD33B4E21F99),
		uint64_t(0x6046C94FC03497F0), uint64_t(0xE6AB92E8D1CB8EA2),
		uint64_t(0x3354C7F5663856F1), uint64_t(0xD93EE170AF7BAE4D),
		uint64_t(0x616BD27BC22AE67C), uint64_t(0x92B39A10397A8370),
		uint64_t(0xABC8B3304B8E9890), uint64_t(0xBF967287630B02B2),
		uint64_t(0x5B67D607B6FC6E15) }),

	HashLibUInt64Array({ uint64_t(0xD031C397CE553FE6),
		uint64_t(0x16BA5B01B006B525), uint64_t(0xA89BADE6296E70C8),
		uint64_t(0x6A1F525D77D3435B), uint64_t(0x6E103570573DFA0B),
		uint64_t(0x660EFB2A17FC95AB), uint64_t(0x76327A9E97634BF6),
		uint64_t(0x4BAD9D6462458BF5), uint64_t(0xF1830CAEDBC3F748),
		uint64_t(0xC5C8F542669131FF), uint64_t(0x95044A1CDC48B0CB),
		uint64_t(0x892962DF3CF8B866), uint64_t(0xB0B9E208E930C135),
		uint64_t(0xA14FB3F0611A767C), uint64_t(0x8D2605F21C160136),
		uint64_t(0xD6B71922FECC549E), uint64_t(0x37089438A5907D8B),
		uint64_t(0x0B5DA38E5803D49C), uint64_t(0x5A5BCC9CEA6F3CBC),
		uint64_t(0xEDAE246D3B73FFE5), uint64_t(0xD2B87E0FDE22EDCE),
		uint64_t(0x5E54ABB1CA8185EC), uint64_t(0x1DE7F88FE80561B9),
		uint64_t(0xAD5E1A870135A08C), uint64_t(0x2F2ADBD665CECC76),
		uint64_t(0x5780B5A782F58358), uint64_t(0x3EDC8A2EEDE47B3F),
		uint64_t(0xC9D95C3506BEE70F), uint64_t(0x83BE111D6C4E05EE),
		uint64_t(0xA603B90959367410), uint64_t(0x103C81B4809FDE5D),
		uint64_t(0x2C69B6027D0C774A), uint64_t(0x399080D7D5C87953),
		uint64_t(0x09D41E16487406B4), uint64_t(0xCDD63B1826505E5F),
		uint64_t(0xF99DC2F49B0298E8), uint64_t(0x9CD0540A943CB67F),
		uint64_t(0xBCA84B7F891F17C5), uint64_t(0x723D1DB3B78DF2A6),
		uint64_t(0x78AA6E71E73B4F2E), uint64_t(0x1433E699A071670D),
		uint64_t(0x84F21BE454620782), uint64_t(0x98DF3327B4D20F2F),
		uint64_t(0xF049DCE2D3769E5C), uint64_t(0xDB6C60199656EB7A),
		uint64_t(0x648746B2078B4783), uint64_t(0x32CD23598DCBADCF),
		uint64_t(0x1EA4955BF0C7DA85), uint64_t(0xE9A143401B9D46B5),
		uint64_t(0xFD92A5D9BBEC21B8), uint64_t(0xC8138C790E0B8E1B),
		uint64_t(0x2EE00B9A6D7BA562), uint64_t(0xF85712B893B7F1FC),
		uint64_t(0xEB28FED80BEA949D), uint64_t(0x564A65EB8A40EA4C),
		uint64_t(0x6C9988E8474A2823), uint64_t(0x4535898B121D8F2D),
		uint64_t(0xABD8C03231ACCBF4), uint64_t(0xBA2E91CAB9867CBD),
		uint64_t(0x7960BE3DEF8E263A), uint64_t(0x0C11A977602FD6F0),
		uint64_t(0xCB50E1AD16C93527), uint64_t(0xEAE22E94035FFD89),
		uint64_t(0x2866D12F5DE2CE1A), uint64_t(0xFF1B1841AB9BF390),
		uint64_t(0x9F9339DE8CFE0D43), uint64_t(0x964727C8C48A0BF7),
		uint64_t(0x524502C6AAAE531C), uint64_t(0x9B9C5EF3AC10B413),
		uint64_t(0x4FA2FA4942AB32A5), uint64_t(0x3F165A62E551122B),
		uint64_t(0xC74148DA76E6E3D7), uint64_t(0x924840E5E464B2A7),
		uint64_t(0xD372AE43D69784DA), uint64_t(0x233B72A105E11A86),
		uint64_t(0xA48A04914941A638), uint64_t(0xB4B68525C9DE7865),
		uint64_t(0xDDEABAACA6CF8002), uint64_t(0x0A9773C250B6BD88),
		uint64_t(0xC284FFBB5EBD3393), uint64_t(0x8BA0DF472C8F6A4E),
		uint64_t(0x2AEF6CB74D951C32), uint64_t(0x427983722A318D41),
		uint64_t(0x73F7CDFFBF389BB2), uint64_t(0x074C0AF9382C026C),
		uint64_t(0x8A6A0F0B243A035A), uint64_t(0x6FDAE53C5F88931F),
		uint64_t(0xC68B98967E538AC3), uint64_t(0x44FF59C71AA8E639),
		uint64_t(0xE2FCE0CE439E9229), uint64_t(0xA20CDE2479D8CD40),
		uint64_t(0x19E89FA2C8EBD8E9), uint64_t(0xF446BBCFF398270C),
		uint64_t(0x43B3533E2284E455), uint64_t(0xD82F0DCD8E945046),
		uint64_t(0x51066F12B26CE820), uint64_t(0xE73957AF6BC5426D),
		uint64_t(0x081ECE5A40C16FA0), uint64_t(0x3B193D4FC5BFAB7B),
		uint64_t(0x7FE66488DF174D42), uint64_t(0x0E9814EF705804D8),
		uint64_t(0x8137AC857C39D7C6), uint64_t(0xB1733244E185A821),
		uint64_t(0x695C3F896F11F867), uint64_t(0xF6CF0657E3EFF524),
		uint64_t(0x1AABF276D02963D5), uint64_t(0x2DA3664E75B91E5E),
		uint64_t(0x0289BD981077D228), uint64_t(0x90C1FD7DF413608F),
		uint64_t(0x3C5537B6FD93A917), uint64_t(0xAA12107E3919A2E0),
		uint64_t(0x0686DAB530996B78), uint64_t(0xDAA6B0559EE3826E),
		uint64_t(0xC34E2FF756085A87), uint64_t(0x6D5358A44FFF4137),
		uint64_t(0xFC587595B35948AC), uint64_t(0x7CA5095CC7D5F67E),
		uint64_t(0xFB147F6C8B754AC0), uint64_t(0xBFEB26AB91DDACF9),
		uint64_t(0x6896EFC567A49173), uint64_t(0xCA9A31E11E7C5C33),
		uint64_t(0xBBE44186B13315A9), uint64_t(0x0DDB793B689ABFE4),
		uint64_t(0x70B4A02BA7FA208E), uint64_t(0xE47A3A7B7307F951),
		uint64_t(0x8CECD5BE14A36822), uint64_t(0xEEED49B923B144D9),
		uint64_t(0x17708B4DB8B3DC31), uint64_t(0x6088219F2765FED3),
		uint64_t(0xB3FA8FDCF1F27A09), uint64_t(0x910B2D31FCA6099B),
		uint64_t(0x0F52C4A378ED6DCC), uint64_t(0x50CCBF5EBAD98134),
		uint64_t(0x6BD582117F662A4F), uint64_t(0x94CE9A50D4FDD9DF),
		uint64_t(0x2B25BCFB45207526), uint64_t(0x67C42B661F49FCBF),
		uint64_t(0x492420FC723259DD), uint64_t(0x03436DD418C2BB3C),
		uint64_t(0x1F6E4517F872B391), uint64_t(0xA08563BC69AF1F68),
		uint64_t(0xD43EA4BAEEBB86B6), uint64_t(0x01CAD04C08B56914),
		uint64_t(0xAC94CACB0980C998), uint64_t(0x54C3D8739A373864),
		uint64_t(0x26FEC5C02DBACAC2), uint64_t(0xDEA9D778BE0D3B3E),
		uint64_t(0x040F672D20EEB950), uint64_t(0xE5B0EA377BB29045),
		uint64_t(0xF30AB136CBB42560), uint64_t(0x62019C0737122CFB),
		uint64_t(0xE86B930C13282FA1), uint64_t(0xCC1CEB542EE5374B),
		uint64_t(0x538FD28AA21B3A08), uint64_t(0x1B61223AD89C0AC1),
		uint64_t(0x36C24474AD25149F), uint64_t(0x7A23D3E9F74C9D06),
		uint64_t(0xBE21F6E79968C5ED), uint64_t(0xCF5F868036278C77),
		uint64_t(0xF705D61BEB5A9C30), uint64_t(0x4D2B47D152DCE08D),
		uint64_t(0x5F9E7BFDC234ECF8), uint64_t(0x247778583DCD18EA),
		uint64_t(0x867BA67C4415D5AA), uint64_t(0x4CE1979D5A698999),
		uint64_t(0x0000000000000000), uint64_t(0xEC64F42133C696F1),
		uint64_t(0xB57C5569C16B1171), uint64_t(0xC1C7926F467F88AF),
		uint64_t(0x654D96FE0F3E2E97), uint64_t(0x15F936D5A8C40E19),
		uint64_t(0xB8A72C52A9F1AE95), uint64_t(0xA9517DAA21DB19DC),
		uint64_t(0x58D27104FA18EE94), uint64_t(0x5918A148F2AD8780),
		uint64_t(0x5CDD1629DAF657C4), uint64_t(0x8274C15164FB6CFA),
		uint64_t(0xD1FB13DBC6E056F2), uint64_t(0x7D6FD910CF609F6A),
		uint64_t(0xB63F38BDD9A9AA4D), uint64_t(0x3D9FE7FAF526C003),
		uint64_t(0x74BBC706871499DE), uint64_t(0xDF630734B6B8522A),
		uint64_t(0x3AD3ED03CD0AC26F), uint64_t(0xFADEAF2083C023D4),
		uint64_t(0xC00D42234ECAE1BB), uint64_t(0x8538CBA85CD76E96),
		uint64_t(0xC402250E6E2458EB), uint64_t(0x47BC3413026A5D05),
		uint64_t(0xAFD7A71F114272A4), uint64_t(0x978DF784CC3F62E3),
		uint64_t(0xB96DFC1EA144C781), uint64_t(0x21B2CF391596C8AE),
		uint64_t(0x318E4E8D950916F3), uint64_t(0xCE9556CC3E92E563),
		uint64_t(0x385A509BDD7D1047), uint64_t(0x358129A0B5E7AFA3),
		uint64_t(0xE6F387E363702B79), uint64_t(0xE0755D5653E94001),
		uint64_t(0x7BE903A5FFF9F412), uint64_t(0x12B53C2C90E80C75),
		uint64_t(0x3307F315857EC4DB), uint64_t(0x8FAFB86A0C61D31E),
		uint64_t(0xD9E5DD8186213952), uint64_t(0x77F8AAD29FD622E2),
		uint64_t(0x25BDA814357871FE), uint64_t(0x7571174A8FA1F0CA),
		uint64_t(0x137FEC60985D6561), uint64_t(0x30449EC19DBC7FE7),
		uint64_t(0xA540D4DD41F4CF2C), uint64_t(0xDC206AE0AE7AE916),
		uint64_t(0x5B911CD0E2DA55A8), uint64_t(0xB2305F90F947131D),
		uint64_t(0x344BF9ECBD52C6B7), uint64_t(0x5D17C665D2433ED0),
		uint64_t(0x18224FEEC05EB1FD), uint64_t(0x9E59E992844B6457),
		uint64_t(0x9A568EBFA4A5DD07), uint64_t(0xA3C60E68716DA454),
		uint64_t(0x7E2CB4C4D7A22456), uint64_t(0x87B176304CA0BCBE),
		uint64_t(0x413AEEA632F3367D), uint64_t(0x9915E36BBC67663B),
		uint64_t(0x40F03EEA3A465F69), uint64_t(0x1C2D28C3E0B008AD),
		uint64_t(0x4E682A054A1E5BB1), uint64_t(0x05C5B761285BD044),
		uint64_t(0xE1BF8D1A5B5C2915), uint64_t(0xF2C0617AC3014C74),
		uint64_t(0xB7F5E8F1D11CC359), uint64_t(0x63CB4C4B3FA745EF),
		uint64_t(0x9D1A84469C89DF6B), uint64_t(0xE33630824B2BFB3D),
		uint64_t(0xD5F474F6E60EEFA2), uint64_t(0xF58C6B83FB2D4E18),
		uint64_t(0x4676E45F0ADF3411), uint64_t(0x20781F751D23A1BA),
		uint64_t(0xBD629B3381AA7ED1), uint64_t(0xAE1D775319F71BB0),
		uint64_t(0xFED1C80DA32E9A84), uint64_t(0x5509083F92825170),
		uint64_t(0x29AC01635557A70E), uint64_t(0xA7C9694551831D04),
		uint64_t(0x8E65682604D4BA0A), uint64_t(0x11F651F8882AB749),
		uint64_t(0xD77DC96EF6793D8A), uint64_t(0xEF2799F52B042DCD),
		uint64_t(0x48EEF0B07A8730C9), uint64_t(0x22F1A2ED0D547392),
		uint64_t(0x6142F1D32FD097C7), uint64_t(0x4A674D286AF0E2E1),
		uint64_t(0x80FD7CC9748CBED2), uint64_t(0x717E7067AF4F499A),
		uint64_t(0x938290A9ECD1DBB3), uint64_t(0x88E3B293344DD172),
		uint64_t(0x2734158C250FA3D6) })

	});


class GOST3411_2012_256 : public GOST3411_2012
{
public:
	GOST3411_2012_256()
		: GOST3411_2012(32, IV_256)
	{
		name = __func__;
	}

	virtual IHash Clone() const
	{
		GOST3411_2012_256 HashInstance = GOST3411_2012_256();

		HashInstance.IV = IV;
		HashInstance.N = N;
		HashInstance.Sigma = Sigma;
		HashInstance.Ki = Ki;
		HashInstance.m = m;
		HashInstance.h = h;
		HashInstance.tmp = tmp;
		HashInstance.block = block;
		HashInstance.bOff = bOff;

		IHash hash = make_shared<GOST3411_2012_256>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual IHashResult TransformFinal()
	{
		HashLibByteArray output, tempRes;

		output = GOST3411_2012::TransformFinal()->GetBytes();
		tempRes.resize(hash_size);

		memmove(&tempRes[0], &output[32], 32 * sizeof(uint8_t));

		IHashResult result = make_shared<HashResult>(tempRes);

		return result;
	}

private:
	static HashLibByteArray IV_256;

}; // end class GOST3411_2012_256

HashLibByteArray GOST3411_2012_256::IV_256 = HashLibByteArray({ 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 });

class GOST3411_2012_512 : public GOST3411_2012
{
public:
	GOST3411_2012_512()
		: GOST3411_2012(64, IV_512)
	{
		name = __func__;
	}

	virtual IHash Clone() const
	{
		GOST3411_2012_512 HashInstance = GOST3411_2012_512();

		HashInstance.IV = IV;
		HashInstance.N = N;
		HashInstance.Sigma = Sigma;
		HashInstance.Ki = Ki;
		HashInstance.m = m;
		HashInstance.h = h;
		HashInstance.tmp = tmp;
		HashInstance.block = block;
		HashInstance.bOff = bOff;

		IHash hash = make_shared<GOST3411_2012_512>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

private:
	static HashLibByteArray IV_512;

}; // end class GOST3411_2012_512

HashLibByteArray GOST3411_2012_512::IV_512 = HashLibByteArray({ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });


#endif // !HLPGOST3411_2012_H