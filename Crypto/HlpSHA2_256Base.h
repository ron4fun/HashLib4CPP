// ///////////////////////////////////////////////////////////////// //
// *C++ 11 HashFactory Library                                 
// *Copyright(c) 2018  Mbadiwe Nnaemeka Ronald                 
// *Github Repository <https://github.com/ron4fun>             

// *Distributed under the MIT software license, see the accompanying file LICENSE 
// *or visit http ://www.opensource.org/licenses/mit-license.php.           

// *Acknowledgements:                                  
// ** //
// *Thanks to Ugochukwu Mmaduekwe (https://github.com/Xor-el) for his creative        
// *development of this library in Pascal/Delphi                         

// ////////////////////////////////////////////////////// ///////////////

#ifndef HLPSHA2_256BASE_H
#define HLPSHA2_256BASE_H

#include "../Base/HlpHashCryptoNotBuildIn.h"


class SHA2_256Base : public BlockHash, public IICryptoNotBuildIn, public IITransformBlock
{
protected:
	SHA2_256Base(const int32_t a_hash_size)
		: BlockHash(a_hash_size, 64)
	{
		state = shared_ptr<uint32_t>(new uint32_t[8], default_delete<uint32_t[]>());
		data = shared_ptr<uint32_t>(new uint32_t[64], default_delete<uint32_t[]>());
	} // end constructor

	~SHA2_256Base()
	{} // end destructor

	virtual void Finish()
	{
		int32_t padindex;

		uint64_t bits = processed_bytes * 8;
		if (buffer->GetPos() < 56)
			padindex = 56 - buffer->GetPos();
		else
			padindex = 120 - buffer->GetPos();

		HashLibByteArray pad = HashLibByteArray(padindex + 8);

		pad[0] = 0x80;

		bits = Converters::be2me_64(bits);

		Converters::ReadUInt64AsBytesLE(bits, pad, padindex);

		padindex = padindex + 8;

		TransformBytes(pad, 0, padindex);

	} // end function Finish

	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t A, B, C, D, E, F, G, H, T, T2;
	
		Converters::be32_copy(a_data, a_index, data.get(), 0, 64);

		A = state.get()[0];
		B = state.get()[1];
		C = state.get()[2];
		D = state.get()[3];
		E = state.get()[4];
		F = state.get()[5];
		G = state.get()[6];
		H = state.get()[7];

		// Step 1

		T = data.get()[14];
		T2 = data.get()[1];
		data.get()[16]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[9] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[0];

		T = data.get()[15];
		T2 = data.get()[2];
		data.get()[17]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[10] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[1];

		T = data.get()[16];
		T2 = data.get()[3];
		data.get()[18]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[11] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[2];

		T = data.get()[17];
		T2 = data.get()[4];
		data.get()[19]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[12] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[3];

		T = data.get()[18];
		T2 = data.get()[5];
		data.get()[20]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[13] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[4];

		T = data.get()[19];
		T2 = data.get()[6];
		data.get()[21]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[14] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[5];

		T = data.get()[20];
		T2 = data.get()[7];
		data.get()[22]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[15] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[6];

		T = data.get()[21];
		T2 = data.get()[8];
		data.get()[23]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[16] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[7];

		T = data.get()[22];
		T2 = data.get()[9];
		data.get()[24]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[17] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[8];

		T = data.get()[23];
		T2 = data.get()[10];
		data.get()[25]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[18] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[9];

		T = data.get()[24];
		T2 = data.get()[11];
		data.get()[26]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[19] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[10];

		T = data.get()[25];
		T2 = data.get()[12];
		data.get()[27]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[20] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[11];

		T = data.get()[26];
		T2 = data.get()[13];
		data.get()[28]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[21] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[12];

		T = data.get()[27];
		T2 = data.get()[14];
		data.get()[29]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[22] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[13];

		T = data.get()[28];
		T2 = data.get()[15];
		data.get()[30]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[23] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[14];

		T = data.get()[29];
		T2 = data.get()[16];
		data.get()[31]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[24] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[15];

		T = data.get()[30];
		T2 = data.get()[17];
		data.get()[32]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[25] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[16];

		T = data.get()[31];
		T2 = data.get()[18];
		data.get()[33]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[26] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[17];

		T = data.get()[32];
		T2 = data.get()[19];
		data.get()[34]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[27] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[18];

		T = data.get()[33];
		T2 = data.get()[20];
		data.get()[35]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[28] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[19];

		T = data.get()[34];
		T2 = data.get()[21];
		data.get()[36]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[29] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[20];

		T = data.get()[35];
		T2 = data.get()[22];
		data.get()[37]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[30] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[21];

		T = data.get()[36];
		T2 = data.get()[23];
		data.get()[38]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[31] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[22];

		T = data.get()[37];
		T2 = data.get()[24];
		data.get()[39]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[32] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[23];

		T = data.get()[38];
		T2 = data.get()[25];
		data.get()[40]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[33] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[24];

		T = data.get()[39];
		T2 = data.get()[26];
		data.get()[41]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[34] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[25];

		T = data.get()[40];
		T2 = data.get()[27];
		data.get()[42]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[35] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[26];

		T = data.get()[41];
		T2 = data.get()[28];
		data.get()[43]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[36] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[27];

		T = data.get()[42];
		T2 = data.get()[29];
		data.get()[44]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[37] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[28];

		T = data.get()[43];
		T2 = data.get()[30];
		data.get()[45]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[38] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[29];

		T = data.get()[44];
		T2 = data.get()[31];
		data.get()[46]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[39] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[30];

		T = data.get()[45];
		T2 = data.get()[32];
		data.get()[47]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[40] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[31];

		T = data.get()[46];
		T2 = data.get()[33];
		data.get()[48]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[41] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[32];

		T = data.get()[47];
		T2 = data.get()[34];
		data.get()[49]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[42] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[33];

		T = data.get()[48];
		T2 = data.get()[35];
		data.get()[50]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[43] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[34];

		T = data.get()[49];
		T2 = data.get()[36];
		data.get()[51]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[44] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[35];

		T = data.get()[50];
		T2 = data.get()[37];
		data.get()[52]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[45] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[36];

		T = data.get()[51];
		T2 = data.get()[38];
		data.get()[53]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[46] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[37];

		T = data.get()[52];
		T2 = data.get()[39];
		data.get()[54]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[47] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[38];

		T = data.get()[53];
		T2 = data.get()[40];
		data.get()[55]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[48] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[39];

		T = data.get()[54];
		T2 = data.get()[41];
		data.get()[56]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[49] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[40];

		T = data.get()[55];
		T2 = data.get()[42];
		data.get()[57]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[50] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[41];

		T = data.get()[56];
		T2 = data.get()[43];
		data.get()[58]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[51] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[42];

		T = data.get()[57];
		T2 = data.get()[44];
		data.get()[59]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[52] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[43];

		T = data.get()[58];
		T2 = data.get()[45];
		data.get()[60]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[53] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[44];

		T = data.get()[59];
		T2 = data.get()[46];
		data.get()[61]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[54] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[45];

		T = data.get()[60];
		T2 = data.get()[47];
		data.get()[62]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[55] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[46];

		T = data.get()[61];
		T2 = data.get()[48];
		data.get()[63]  = ((Bits::RotateRight32(T, 17)) ^ (Bits::RotateRight32(T, 19))
			^ (T >> 10)) + data.get()[56] +
			((Bits::RotateRight32(T2, 7)) ^ (Bits::RotateRight32(T2, 18))
				^ (T2 >> 3)) + data.get()[47];

		// Step 2

		T = H + ((Bits::RotateRight32(E, 6)) ^ (Bits::RotateRight32(E, 11))
			^ (Bits::RotateRight32(E, 25))) + ((E & F) ^ (~E & G)) +
			0x428A2F98 + data.get()[0];
		T2 = ((Bits::RotateRight32(A, 2)) ^ (Bits::RotateRight32(A, 13))
			^ ((A >> 22) ^ (A << 10))) + ((A & B) ^ (A & C) ^ (B & C));
		H = T + T2;
		D = D + T;
		T = G + ((Bits::RotateRight32(D, 6)) ^ (Bits::RotateRight32(D, 11))
			^ (Bits::RotateRight32(D, 25))) + ((D & E) ^ (~D & F)) +
			0x71374491 + data.get()[1];
		T2 = ((Bits::RotateRight32(H, 2)) ^ (Bits::RotateRight32(H, 13))
			^ ((H >> 22) ^ (H << 10))) + ((H & A) ^ (H & B) ^ (A & B));
		G = T + T2;
		C = C + T;
		T = F + ((Bits::RotateRight32(C, 6)) ^ (Bits::RotateRight32(C, 11))
			^ (Bits::RotateRight32(C, 25))) + ((C & D) ^ (~C & E)) +
			0xB5C0FBCF + data.get()[2];
		T2 = ((Bits::RotateRight32(G, 2)) ^ (Bits::RotateRight32(G, 13))
			^ ((G >> 22) ^ (G << 10))) + ((G & H) ^ (G & A) ^ (H & A));
		F = T + T2;
		B = B + T;
		T = E + ((Bits::RotateRight32(B, 6)) ^ (Bits::RotateRight32(B, 11))
			^ (Bits::RotateRight32(B, 25))) + ((B & C) ^ (~B & D)) +
			0xE9B5DBA5 + data.get()[3];
		T2 = ((Bits::RotateRight32(F, 2)) ^ (Bits::RotateRight32(F, 13))
			^ ((F >> 22) ^ (F << 10))) + ((F & G) ^ (F & H) ^ (G & H));
		E = T + T2;
		A = A + T;
		T = D + ((Bits::RotateRight32(A, 6)) ^ (Bits::RotateRight32(A, 11))
			^ (Bits::RotateRight32(A, 25))) + ((A & B) ^ (~A & C)) +
			0x3956C25B + data.get()[4];
		T2 = ((Bits::RotateRight32(E, 2)) ^ (Bits::RotateRight32(E, 13))
			^ ((E >> 22) ^ (E << 10))) + ((E & F) ^ (E & G) ^ (F & G));
		D = T + T2;
		H = H + T;
		T = C + ((Bits::RotateRight32(H, 6)) ^ (Bits::RotateRight32(H, 11))
			^ (Bits::RotateRight32(H, 25))) + ((H & A) ^ (~H & B)) +
			0x59F111F1 + data.get()[5];
		T2 = ((Bits::RotateRight32(D, 2)) ^ (Bits::RotateRight32(D, 13))
			^ ((D >> 22) ^ (D << 10))) + ((D & E) ^ (D & F) ^ (E & F));
		C = T + T2;
		G = G + T;
		T = B + ((Bits::RotateRight32(G, 6)) ^ (Bits::RotateRight32(G, 11))
			^ (Bits::RotateRight32(G, 25))) + ((G & H) ^ (~G & A)) +
			0x923F82A4 + data.get()[6];
		T2 = ((Bits::RotateRight32(C, 2)) ^ (Bits::RotateRight32(C, 13))
			^ ((C >> 22) ^ (C << 10))) + ((C & D) ^ (C & E) ^ (D & E));
		B = T + T2;
		F = F + T;
		T = A + ((Bits::RotateRight32(F, 6)) ^ (Bits::RotateRight32(F, 11))
			^ (Bits::RotateRight32(F, 25))) + ((F & G) ^ (~F & H)) +
			0xAB1C5ED5 + data.get()[7];
		T2 = ((Bits::RotateRight32(B, 2)) ^ (Bits::RotateRight32(B, 13))
			^ ((B >> 22) ^ (B << 10))) + ((B & C) ^ (B & D) ^ (C & D));
		A = T + T2;
		E = E + T;
		T = H + ((Bits::RotateRight32(E, 6)) ^ (Bits::RotateRight32(E, 11))
			^ (Bits::RotateRight32(E, 25))) + ((E & F) ^ (~E & G)) +
			0xD807AA98 + data.get()[8];
		T2 = ((Bits::RotateRight32(A, 2)) ^ (Bits::RotateRight32(A, 13))
			^ ((A >> 22) ^ (A << 10))) + ((A & B) ^ (A & C) ^ (B & C));
		H = T + T2;
		D = D + T;
		T = G + ((Bits::RotateRight32(D, 6)) ^ (Bits::RotateRight32(D, 11))
			^ (Bits::RotateRight32(D, 25))) + ((D & E) ^ (~D & F)) +
			0x12835B01 + data.get()[9];
		T2 = ((Bits::RotateRight32(H, 2)) ^ (Bits::RotateRight32(H, 13))
			^ ((H >> 22) ^ (H << 10))) + ((H & A) ^ (H & B) ^ (A & B));
		G = T + T2;
		C = C + T;
		T = F + ((Bits::RotateRight32(C, 6)) ^ (Bits::RotateRight32(C, 11))
			^ (Bits::RotateRight32(C, 25))) + ((C & D) ^ (~C & E)) +
			0x243185BE + data.get()[10];
		T2 = ((Bits::RotateRight32(G, 2)) ^ (Bits::RotateRight32(G, 13))
			^ ((G >> 22) ^ (G << 10))) + ((G & H) ^ (G & A) ^ (H & A));
		F = T + T2;
		B = B + T;
		T = E + ((Bits::RotateRight32(B, 6)) ^ (Bits::RotateRight32(B, 11))
			^ (Bits::RotateRight32(B, 25))) + ((B & C) ^ (~B & D)) +
			0x550C7DC3 + data.get()[11];
		T2 = ((Bits::RotateRight32(F, 2)) ^ (Bits::RotateRight32(F, 13))
			^ ((F >> 22) ^ (F << 10))) + ((F & G) ^ (F & H) ^ (G & H));
		E = T + T2;
		A = A + T;
		T = D + ((Bits::RotateRight32(A, 6)) ^ (Bits::RotateRight32(A, 11))
			^ (Bits::RotateRight32(A, 25))) + ((A & B) ^ (~A & C)) +
			0x72BE5D74 + data.get()[12];
		T2 = ((Bits::RotateRight32(E, 2)) ^ (Bits::RotateRight32(E, 13))
			^ ((E >> 22) ^ (E << 10))) + ((E & F) ^ (E & G) ^ (F & G));
		D = T + T2;
		H = H + T;
		T = C + ((Bits::RotateRight32(H, 6)) ^ (Bits::RotateRight32(H, 11))
			^ (Bits::RotateRight32(H, 25))) + ((H & A) ^ (~H & B)) +
			0x80DEB1FE + data.get()[13];
		T2 = ((Bits::RotateRight32(D, 2)) ^ (Bits::RotateRight32(D, 13))
			^ ((D >> 22) ^ (D << 10))) + ((D & E) ^ (D & F) ^ (E & F));
		C = T + T2;
		G = G + T;
		T = B + ((Bits::RotateRight32(G, 6)) ^ (Bits::RotateRight32(G, 11))
			^ (Bits::RotateRight32(G, 25))) + ((G & H) ^ (~G & A)) +
			0x9BDC06A7 + data.get()[14];
		T2 = ((Bits::RotateRight32(C, 2)) ^ (Bits::RotateRight32(C, 13))
			^ ((C >> 22) ^ (C << 10))) + ((C & D) ^ (C & E) ^ (D & E));
		B = T + T2;
		F = F + T;
		T = A + ((Bits::RotateRight32(F, 6)) ^ (Bits::RotateRight32(F, 11))
			^ (Bits::RotateRight32(F, 25))) + ((F & G) ^ (~F & H)) +
			0xC19BF174 + data.get()[15];
		T2 = ((Bits::RotateRight32(B, 2)) ^ (Bits::RotateRight32(B, 13))
			^ ((B >> 22) ^ (B << 10))) + ((B & C) ^ (B & D) ^ (C & D));
		A = T + T2;
		E = E + T;
		T = H + ((Bits::RotateRight32(E, 6)) ^ (Bits::RotateRight32(E, 11))
			^ (Bits::RotateRight32(E, 25))) + ((E & F) ^ (~E & G)) +
			0xE49B69C1 + data.get()[16];
		T2 = ((Bits::RotateRight32(A, 2)) ^ (Bits::RotateRight32(A, 13))
			^ ((A >> 22) ^ (A << 10))) + ((A & B) ^ (A & C) ^ (B & C));
		H = T + T2;
		D = D + T;
		T = G + ((Bits::RotateRight32(D, 6)) ^ (Bits::RotateRight32(D, 11))
			^ (Bits::RotateRight32(D, 25))) + ((D & E) ^ (~D & F)) +
			0xEFBE4786 + data.get()[17];
		T2 = ((Bits::RotateRight32(H, 2)) ^ (Bits::RotateRight32(H, 13))
			^ ((H >> 22) ^ (H << 10))) + ((H & A) ^ (H & B) ^ (A & B));
		G = T + T2;
		C = C + T;
		T = F + ((Bits::RotateRight32(C, 6)) ^ (Bits::RotateRight32(C, 11))
			^ (Bits::RotateRight32(C, 25))) + ((C & D) ^ (~C & E)) +
			0x0FC19DC6 + data.get()[18];
		T2 = ((Bits::RotateRight32(G, 2)) ^ (Bits::RotateRight32(G, 13))
			^ ((G >> 22) ^ (G << 10))) + ((G & H) ^ (G & A) ^ (H & A));
		F = T + T2;
		B = B + T;
		T = E + ((Bits::RotateRight32(B, 6)) ^ (Bits::RotateRight32(B, 11))
			^ (Bits::RotateRight32(B, 25))) + ((B & C) ^ (~B & D)) +
			0x240CA1CC + data.get()[19];
		T2 = ((Bits::RotateRight32(F, 2)) ^ (Bits::RotateRight32(F, 13))
			^ ((F >> 22) ^ (F << 10))) + ((F & G) ^ (F & H) ^ (G & H));
		E = T + T2;
		A = A + T;
		T = D + ((Bits::RotateRight32(A, 6)) ^ (Bits::RotateRight32(A, 11))
			^ (Bits::RotateRight32(A, 25))) + ((A & B) ^ (~A & C)) +
			0x2DE92C6F + data.get()[20];
		T2 = ((Bits::RotateRight32(E, 2)) ^ (Bits::RotateRight32(E, 13))
			^ ((E >> 22) ^ (E << 10))) + ((E & F) ^ (E & G) ^ (F & G));
		D = T + T2;
		H = H + T;
		T = C + ((Bits::RotateRight32(H, 6)) ^ (Bits::RotateRight32(H, 11))
			^ (Bits::RotateRight32(H, 25))) + ((H & A) ^ (~H & B)) +
			0x4A7484AA + data.get()[21];
		T2 = ((Bits::RotateRight32(D, 2)) ^ (Bits::RotateRight32(D, 13))
			^ ((D >> 22) ^ (D << 10))) + ((D & E) ^ (D & F) ^ (E & F));
		C = T + T2;
		G = G + T;
		T = B + ((Bits::RotateRight32(G, 6)) ^ (Bits::RotateRight32(G, 11))
			^ (Bits::RotateRight32(G, 25))) + ((G & H) ^ (~G & A)) +
			0x5CB0A9DC + data.get()[22];
		T2 = ((Bits::RotateRight32(C, 2)) ^ (Bits::RotateRight32(C, 13))
			^ ((C >> 22) ^ (C << 10))) + ((C & D) ^ (C & E) ^ (D & E));
		B = T + T2;
		F = F + T;
		T = A + ((Bits::RotateRight32(F, 6)) ^ (Bits::RotateRight32(F, 11))
			^ (Bits::RotateRight32(F, 25))) + ((F & G) ^ (~F & H)) +
			0x76F988DA + data.get()[23];
		T2 = ((Bits::RotateRight32(B, 2)) ^ (Bits::RotateRight32(B, 13))
			^ ((B >> 22) ^ (B << 10))) + ((B & C) ^ (B & D) ^ (C & D));
		A = T + T2;
		E = E + T;
		T = H + ((Bits::RotateRight32(E, 6)) ^ (Bits::RotateRight32(E, 11))
			^ (Bits::RotateRight32(E, 25))) + ((E & F) ^ (~E & G)) +
			0x983E5152 + data.get()[24];
		T2 = ((Bits::RotateRight32(A, 2)) ^ (Bits::RotateRight32(A, 13))
			^ ((A >> 22) ^ (A << 10))) + ((A & B) ^ (A & C) ^ (B & C));
		H = T + T2;
		D = D + T;
		T = G + ((Bits::RotateRight32(D, 6)) ^ (Bits::RotateRight32(D, 11))
			^ (Bits::RotateRight32(D, 25))) + ((D & E) ^ (~D & F)) +
			0xA831C66D + data.get()[25];
		T2 = ((Bits::RotateRight32(H, 2)) ^ (Bits::RotateRight32(H, 13))
			^ ((H >> 22) ^ (H << 10))) + ((H & A) ^ (H & B) ^ (A & B));
		G = T + T2;
		C = C + T;
		T = F + ((Bits::RotateRight32(C, 6)) ^ (Bits::RotateRight32(C, 11))
			^ (Bits::RotateRight32(C, 25))) + ((C & D) ^ (~C & E)) +
			0xB00327C8 + data.get()[26];
		T2 = ((Bits::RotateRight32(G, 2)) ^ (Bits::RotateRight32(G, 13))
			^ ((G >> 22) ^ (G << 10))) + ((G & H) ^ (G & A) ^ (H & A));
		F = T + T2;
		B = B + T;
		T = E + ((Bits::RotateRight32(B, 6)) ^ (Bits::RotateRight32(B, 11))
			^ (Bits::RotateRight32(B, 25))) + ((B & C) ^ (~B & D)) +
			0xBF597FC7 + data.get()[27];
		T2 = ((Bits::RotateRight32(F, 2)) ^ (Bits::RotateRight32(F, 13))
			^ ((F >> 22) ^ (F << 10))) + ((F & G) ^ (F & H) ^ (G & H));
		E = T + T2;
		A = A + T;
		T = D + ((Bits::RotateRight32(A, 6)) ^ (Bits::RotateRight32(A, 11))
			^ (Bits::RotateRight32(A, 25))) + ((A & B) ^ (~A & C)) +
			0xC6E00BF3 + data.get()[28];
		T2 = ((Bits::RotateRight32(E, 2)) ^ (Bits::RotateRight32(E, 13))
			^ ((E >> 22) ^ (E << 10))) + ((E & F) ^ (E & G) ^ (F & G));
		D = T + T2;
		H = H + T;
		T = C + ((Bits::RotateRight32(H, 6)) ^ (Bits::RotateRight32(H, 11))
			^ (Bits::RotateRight32(H, 25))) + ((H & A) ^ (~H & B)) +
			0xD5A79147 + data.get()[29];
		T2 = ((Bits::RotateRight32(D, 2)) ^ (Bits::RotateRight32(D, 13))
			^ ((D >> 22) ^ (D << 10))) + ((D & E) ^ (D & F) ^ (E & F));
		C = T + T2;
		G = G + T;
		T = B + ((Bits::RotateRight32(G, 6)) ^ (Bits::RotateRight32(G, 11))
			^ (Bits::RotateRight32(G, 25))) + ((G & H) ^ (~G & A)) +
			0x06CA6351 + data.get()[30];
		T2 = ((Bits::RotateRight32(C, 2)) ^ (Bits::RotateRight32(C, 13))
			^ ((C >> 22) ^ (C << 10))) + ((C & D) ^ (C & E) ^ (D & E));
		B = T + T2;
		F = F + T;
		T = A + ((Bits::RotateRight32(F, 6)) ^ (Bits::RotateRight32(F, 11))
			^ (Bits::RotateRight32(F, 25))) + ((F & G) ^ (~F & H)) +
			0x14292967 + data.get()[31];
		T2 = ((Bits::RotateRight32(B, 2)) ^ (Bits::RotateRight32(B, 13))
			^ ((B >> 22) ^ (B << 10))) + ((B & C) ^ (B & D) ^ (C & D));
		A = T + T2;
		E = E + T;
		T = H + ((Bits::RotateRight32(E, 6)) ^ (Bits::RotateRight32(E, 11))
			^ (Bits::RotateRight32(E, 25))) + ((E & F) ^ (~E & G)) +
			0x27B70A85 + data.get()[32];
		T2 = ((Bits::RotateRight32(A, 2)) ^ (Bits::RotateRight32(A, 13))
			^ ((A >> 22) ^ (A << 10))) + ((A & B) ^ (A & C) ^ (B & C));
		H = T + T2;
		D = D + T;
		T = G + ((Bits::RotateRight32(D, 6)) ^ (Bits::RotateRight32(D, 11))
			^ (Bits::RotateRight32(D, 25))) + ((D & E) ^ (~D & F)) +
			0x2E1B2138 + data.get()[33];
		T2 = ((Bits::RotateRight32(H, 2)) ^ (Bits::RotateRight32(H, 13))
			^ ((H >> 22) ^ (H << 10))) + ((H & A) ^ (H & B) ^ (A & B));
		G = T + T2;
		C = C + T;
		T = F + ((Bits::RotateRight32(C, 6)) ^ (Bits::RotateRight32(C, 11))
			^ (Bits::RotateRight32(C, 25))) + ((C & D) ^ (~C & E)) +
			0x4D2C6DFC + data.get()[34];
		T2 = ((Bits::RotateRight32(G, 2)) ^ (Bits::RotateRight32(G, 13))
			^ ((G >> 22) ^ (G << 10))) + ((G & H) ^ (G & A) ^ (H & A));
		F = T + T2;
		B = B + T;
		T = E + ((Bits::RotateRight32(B, 6)) ^ (Bits::RotateRight32(B, 11))
			^ (Bits::RotateRight32(B, 25))) + ((B & C) ^ (~B & D)) +
			0x53380D13 + data.get()[35];
		T2 = ((Bits::RotateRight32(F, 2)) ^ (Bits::RotateRight32(F, 13))
			^ ((F >> 22) ^ (F << 10))) + ((F & G) ^ (F & H) ^ (G & H));
		E = T + T2;
		A = A + T;
		T = D + ((Bits::RotateRight32(A, 6)) ^ (Bits::RotateRight32(A, 11))
			^ (Bits::RotateRight32(A, 25))) + ((A & B) ^ (~A & C)) +
			0x650A7354 + data.get()[36];
		T2 = ((Bits::RotateRight32(E, 2)) ^ (Bits::RotateRight32(E, 13))
			^ ((E >> 22) ^ (E << 10))) + ((E & F) ^ (E & G) ^ (F & G));
		D = T + T2;
		H = H + T;
		T = C + ((Bits::RotateRight32(H, 6)) ^ (Bits::RotateRight32(H, 11))
			^ (Bits::RotateRight32(H, 25))) + ((H & A) ^ (~H & B)) +
			0x766A0ABB + data.get()[37];
		T2 = ((Bits::RotateRight32(D, 2)) ^ (Bits::RotateRight32(D, 13))
			^ ((D >> 22) ^ (D << 10))) + ((D & E) ^ (D & F) ^ (E & F));
		C = T + T2;
		G = G + T;
		T = B + ((Bits::RotateRight32(G, 6)) ^ (Bits::RotateRight32(G, 11))
			^ (Bits::RotateRight32(G, 25))) + ((G & H) ^ (~G & A)) +
			0x81C2C92E + data.get()[38];
		T2 = ((Bits::RotateRight32(C, 2)) ^ (Bits::RotateRight32(C, 13))
			^ ((C >> 22) ^ (C << 10))) + ((C & D) ^ (C & E) ^ (D & E));
		B = T + T2;
		F = F + T;
		T = A + ((Bits::RotateRight32(F, 6)) ^ (Bits::RotateRight32(F, 11))
			^ (Bits::RotateRight32(F, 25))) + ((F & G) ^ (~F & H)) +
			0x92722C85 + data.get()[39];
		T2 = ((Bits::RotateRight32(B, 2)) ^ (Bits::RotateRight32(B, 13))
			^ ((B >> 22) ^ (B << 10))) + ((B & C) ^ (B & D) ^ (C & D));
		A = T + T2;
		E = E + T;
		T = H + ((Bits::RotateRight32(E, 6)) ^ (Bits::RotateRight32(E, 11))
			^ (Bits::RotateRight32(E, 25))) + ((E & F) ^ (~E & G)) +
			0xA2BFE8A1 + data.get()[40];
		T2 = ((Bits::RotateRight32(A, 2)) ^ (Bits::RotateRight32(A, 13))
			^ ((A >> 22) ^ (A << 10))) + ((A & B) ^ (A & C) ^ (B & C));
		H = T + T2;
		D = D + T;
		T = G + ((Bits::RotateRight32(D, 6)) ^ (Bits::RotateRight32(D, 11))
			^ (Bits::RotateRight32(D, 25))) + ((D & E) ^ (~D & F)) +
			0xA81A664B + data.get()[41];
		T2 = ((Bits::RotateRight32(H, 2)) ^ (Bits::RotateRight32(H, 13))
			^ ((H >> 22) ^ (H << 10))) + ((H & A) ^ (H & B) ^ (A & B));
		G = T + T2;
		C = C + T;
		T = F + ((Bits::RotateRight32(C, 6)) ^ (Bits::RotateRight32(C, 11))
			^ (Bits::RotateRight32(C, 25))) + ((C & D) ^ (~C & E)) +
			0xC24B8B70 + data.get()[42];
		T2 = ((Bits::RotateRight32(G, 2)) ^ (Bits::RotateRight32(G, 13))
			^ ((G >> 22) ^ (G << 10))) + ((G & H) ^ (G & A) ^ (H & A));
		F = T + T2;
		B = B + T;
		T = E + ((Bits::RotateRight32(B, 6)) ^ (Bits::RotateRight32(B, 11))
			^ (Bits::RotateRight32(B, 25))) + ((B & C) ^ (~B & D)) +
			0xC76C51A3 + data.get()[43];
		T2 = ((Bits::RotateRight32(F, 2)) ^ (Bits::RotateRight32(F, 13))
			^ ((F >> 22) ^ (F << 10))) + ((F & G) ^ (F & H) ^ (G & H));
		E = T + T2;
		A = A + T;
		T = D + ((Bits::RotateRight32(A, 6)) ^ (Bits::RotateRight32(A, 11))
			^ (Bits::RotateRight32(A, 25))) + ((A & B) ^ (~A & C)) +
			0xD192E819 + data.get()[44];
		T2 = ((Bits::RotateRight32(E, 2)) ^ (Bits::RotateRight32(E, 13))
			^ ((E >> 22) ^ (E << 10))) + ((E & F) ^ (E & G) ^ (F & G));
		D = T + T2;
		H = H + T;
		T = C + ((Bits::RotateRight32(H, 6)) ^ (Bits::RotateRight32(H, 11))
			^ (Bits::RotateRight32(H, 25))) + ((H & A) ^ (~H & B)) +
			0xD6990624 + data.get()[45];
		T2 = ((Bits::RotateRight32(D, 2)) ^ (Bits::RotateRight32(D, 13))
			^ ((D >> 22) ^ (D << 10))) + ((D & E) ^ (D & F) ^ (E & F));
		C = T + T2;
		G = G + T;
		T = B + ((Bits::RotateRight32(G, 6)) ^ (Bits::RotateRight32(G, 11))
			^ (Bits::RotateRight32(G, 25))) + ((G & H) ^ (~G & A)) +
			0xF40E3585 + data.get()[46];
		T2 = ((Bits::RotateRight32(C, 2)) ^ (Bits::RotateRight32(C, 13))
			^ ((C >> 22) ^ (C << 10))) + ((C & D) ^ (C & E) ^ (D & E));
		B = T + T2;
		F = F + T;
		T = A + ((Bits::RotateRight32(F, 6)) ^ (Bits::RotateRight32(F, 11))
			^ (Bits::RotateRight32(F, 25))) + ((F & G) ^ (~F & H)) +
			0x106AA070 + data.get()[47];
		T2 = ((Bits::RotateRight32(B, 2)) ^ (Bits::RotateRight32(B, 13))
			^ ((B >> 22) ^ (B << 10))) + ((B & C) ^ (B & D) ^ (C & D));
		A = T + T2;
		E = E + T;
		T = H + ((Bits::RotateRight32(E, 6)) ^ (Bits::RotateRight32(E, 11))
			^ (Bits::RotateRight32(E, 25))) + ((E & F) ^ (~E & G)) +
			0x19A4C116 + data.get()[48];
		T2 = ((Bits::RotateRight32(A, 2)) ^ (Bits::RotateRight32(A, 13))
			^ ((A >> 22) ^ (A << 10))) + ((A & B) ^ (A & C) ^ (B & C));
		H = T + T2;
		D = D + T;
		T = G + ((Bits::RotateRight32(D, 6)) ^ (Bits::RotateRight32(D, 11))
			^ (Bits::RotateRight32(D, 25))) + ((D & E) ^ (~D & F)) +
			0x1E376C08 + data.get()[49];
		T2 = ((Bits::RotateRight32(H, 2)) ^ (Bits::RotateRight32(H, 13))
			^ ((H >> 22) ^ (H << 10))) + ((H & A) ^ (H & B) ^ (A & B));
		G = T + T2;
		C = C + T;
		T = F + ((Bits::RotateRight32(C, 6)) ^ (Bits::RotateRight32(C, 11))
			^ (Bits::RotateRight32(C, 25))) + ((C & D) ^ (~C & E)) +
			0x2748774C + data.get()[50];
		T2 = ((Bits::RotateRight32(G, 2)) ^ (Bits::RotateRight32(G, 13))
			^ ((G >> 22) ^ (G << 10))) + ((G & H) ^ (G & A) ^ (H & A));
		F = T + T2;
		B = B + T;
		T = E + ((Bits::RotateRight32(B, 6)) ^ (Bits::RotateRight32(B, 11))
			^ (Bits::RotateRight32(B, 25))) + ((B & C) ^ (~B & D)) +
			0x34B0BCB5 + data.get()[51];
		T2 = ((Bits::RotateRight32(F, 2)) ^ (Bits::RotateRight32(F, 13))
			^ ((F >> 22) ^ (F << 10))) + ((F & G) ^ (F & H) ^ (G & H));
		E = T + T2;
		A = A + T;
		T = D + ((Bits::RotateRight32(A, 6)) ^ (Bits::RotateRight32(A, 11))
			^ (Bits::RotateRight32(A, 25))) + ((A & B) ^ (~A & C)) +
			0x391C0CB3 + data.get()[52];
		T2 = ((Bits::RotateRight32(E, 2)) ^ (Bits::RotateRight32(E, 13))
			^ ((E >> 22) ^ (E << 10))) + ((E & F) ^ (E & G) ^ (F & G));
		D = T + T2;
		H = H + T;
		T = C + ((Bits::RotateRight32(H, 6)) ^ (Bits::RotateRight32(H, 11))
			^ (Bits::RotateRight32(H, 25))) + ((H & A) ^ (~H & B)) +
			0x4ED8AA4A + data.get()[53];
		T2 = ((Bits::RotateRight32(D, 2)) ^ (Bits::RotateRight32(D, 13))
			^ ((D >> 22) ^ (D << 10))) + ((D & E) ^ (D & F) ^ (E & F));
		C = T + T2;
		G = G + T;
		T = B + ((Bits::RotateRight32(G, 6)) ^ (Bits::RotateRight32(G, 11))
			^ (Bits::RotateRight32(G, 25))) + ((G & H) ^ (~G & A)) +
			0x5B9CCA4F + data.get()[54];
		T2 = ((Bits::RotateRight32(C, 2)) ^ (Bits::RotateRight32(C, 13))
			^ ((C >> 22) ^ (C << 10))) + ((C & D) ^ (C & E) ^ (D & E));
		B = T + T2;
		F = F + T;
		T = A + ((Bits::RotateRight32(F, 6)) ^ (Bits::RotateRight32(F, 11))
			^ (Bits::RotateRight32(F, 25))) + ((F & G) ^ (~F & H)) +
			0x682E6FF3 + data.get()[55];
		T2 = ((Bits::RotateRight32(B, 2)) ^ (Bits::RotateRight32(B, 13))
			^ ((B >> 22) ^ (B << 10))) + ((B & C) ^ (B & D) ^ (C & D));
		A = T + T2;
		E = E + T;
		T = H + ((Bits::RotateRight32(E, 6)) ^ (Bits::RotateRight32(E, 11))
			^ (Bits::RotateRight32(E, 25))) + ((E & F) ^ (~E & G)) +
			0x748F82EE + data.get()[56];
		T2 = ((Bits::RotateRight32(A, 2)) ^ (Bits::RotateRight32(A, 13))
			^ ((A >> 22) ^ (A << 10))) + ((A & B) ^ (A & C) ^ (B & C));
		H = T + T2;
		D = D + T;
		T = G + ((Bits::RotateRight32(D, 6)) ^ (Bits::RotateRight32(D, 11))
			^ (Bits::RotateRight32(D, 25))) + ((D & E) ^ (~D & F)) +
			0x78A5636F + data.get()[57];
		T2 = ((Bits::RotateRight32(H, 2)) ^ (Bits::RotateRight32(H, 13))
			^ ((H >> 22) ^ (H << 10))) + ((H & A) ^ (H & B) ^ (A & B));
		G = T + T2;
		C = C + T;
		T = F + ((Bits::RotateRight32(C, 6)) ^ (Bits::RotateRight32(C, 11))
			^ (Bits::RotateRight32(C, 25))) + ((C & D) ^ (~C & E)) +
			0x84C87814 + data.get()[58];
		T2 = ((Bits::RotateRight32(G, 2)) ^ (Bits::RotateRight32(G, 13))
			^ ((G >> 22) ^ (G << 10))) + ((G & H) ^ (G & A) ^ (H & A));
		F = T + T2;
		B = B + T;
		T = E + ((Bits::RotateRight32(B, 6)) ^ (Bits::RotateRight32(B, 11))
			^ (Bits::RotateRight32(B, 25))) + ((B & C) ^ (~B & D)) +
			0x8CC70208 + data.get()[59];
		T2 = ((Bits::RotateRight32(F, 2)) ^ (Bits::RotateRight32(F, 13))
			^ ((F >> 22) ^ (F << 10))) + ((F & G) ^ (F & H) ^ (G & H));
		E = T + T2;
		A = A + T;
		T = D + ((Bits::RotateRight32(A, 6)) ^ (Bits::RotateRight32(A, 11))
			^ (Bits::RotateRight32(A, 25))) + ((A & B) ^ (~A & C)) +
			0x90BEFFFA + data.get()[60];
		T2 = ((Bits::RotateRight32(E, 2)) ^ (Bits::RotateRight32(E, 13))
			^ ((E >> 22) ^ (E << 10))) + ((E & F) ^ (E & G) ^ (F & G));
		D = T + T2;
		H = H + T;
		T = C + ((Bits::RotateRight32(H, 6)) ^ (Bits::RotateRight32(H, 11))
			^ (Bits::RotateRight32(H, 25))) + ((H & A) ^ (~H & B)) +
			0xA4506CEB + data.get()[61];
		T2 = ((Bits::RotateRight32(D, 2)) ^ (Bits::RotateRight32(D, 13))
			^ ((D >> 22) ^ (D << 10))) + ((D & E) ^ (D & F) ^ (E & F));
		C = T + T2;
		G = G + T;
		T = B + ((Bits::RotateRight32(G, 6)) ^ (Bits::RotateRight32(G, 11))
			^ (Bits::RotateRight32(G, 25))) + ((G & H) ^ (~G & A)) +
			0xBEF9A3F7 + data.get()[62];
		T2 = ((Bits::RotateRight32(C, 2)) ^ (Bits::RotateRight32(C, 13))
			^ ((C >> 22) ^ (C << 10))) + ((C & D) ^ (C & E) ^ (D & E));
		B = T + T2;
		F = F + T;
		T = A + ((Bits::RotateRight32(F, 6)) ^ (Bits::RotateRight32(F, 11))
			^ (Bits::RotateRight32(F, 25))) + ((F & G) ^ (~F & H)) +
			0xC67178F2 + data.get()[63];
		T2 = ((Bits::RotateRight32(B, 2)) ^ (Bits::RotateRight32(B, 13))
			^ ((B >> 22) ^ (B << 10))) + ((B & C) ^ (B & D) ^ (C & D));
		A = T + T2;
		E = E + T;

		state.get()[0]  = state.get()[0] + A;
		state.get()[1]  = state.get()[1] + B;
		state.get()[2]  = state.get()[2] + C;
		state.get()[3]  = state.get()[3] + D;
		state.get()[4]  = state.get()[4] + E;
		state.get()[5]  = state.get()[5] + F;
		state.get()[6]  = state.get()[6] + G;
		state.get()[7]  = state.get()[7] + H;

		memset(data.get(), 0, sizeof(data.get()));

	} // end function TransformBlock

protected:
	shared_ptr<uint32_t> state;
	shared_ptr<uint32_t> data;
	
}; // end class SHA2_256Base


#endif //!HLPSHA2_256BASE_H