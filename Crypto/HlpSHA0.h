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

#ifndef HLPSHA0_H
#define HLPSHA0_H

#include "../Base/HlpHashCryptoNotBuildIn.h"


class SHA0 : public BlockHash, public IICryptoNotBuildIn, public IITransformBlock
{
public:
	SHA0()
		: BlockHash(20, 64)
	{
		name = __func__;

		state = shared_ptr<uint32_t>(new uint32_t[5], default_delete<uint32_t[]>());
		data = shared_ptr<uint32_t>(new uint32_t[80], default_delete<uint32_t[]>());
	} // end constructor

	~SHA0()
	{} // end destructor

	virtual void Initialize()
	{
		state.get()[0] = 0x67452301;
		state.get()[1] = 0xEFCDAB89;
		state.get()[2] = 0x98BADCFE;
		state.get()[3] = 0x10325476;
		state.get()[4] = 0xC3D2E1F0;

		BlockHash::Initialize();
	} // end function Initialize

protected:
	virtual void Expand(uint32_t *a_data)
	{
		a_data[16] = ((a_data[16 - 3] ^ a_data[16 - 8]) ^ a_data[16 - 14]) ^ a_data[0];
		a_data[17] = ((a_data[17 - 3] ^ a_data[17 - 8]) ^ a_data[17 - 14]) ^ a_data[17 - 16];
		a_data[18] = ((a_data[18 - 3] ^ a_data[18 - 8]) ^ a_data[18 - 14]) ^ a_data[18 - 16];
		a_data[19] = ((a_data[19 - 3] ^ a_data[19 - 8]) ^ a_data[19 - 14]) ^ a_data[19 - 16];
		a_data[20] = ((a_data[20 - 3] ^ a_data[20 - 8]) ^ a_data[20 - 14]) ^ a_data[20 - 16];
		a_data[21] = ((a_data[21 - 3] ^ a_data[21 - 8]) ^ a_data[21 - 14]) ^ a_data[21 - 16];
		a_data[22] = ((a_data[22 - 3] ^ a_data[22 - 8]) ^ a_data[22 - 14]) ^ a_data[22 - 16];
		a_data[23] = ((a_data[23 - 3] ^ a_data[23 - 8]) ^ a_data[23 - 14]) ^ a_data[23 - 16];
		a_data[24] = ((a_data[24 - 3] ^ a_data[24 - 8]) ^ a_data[24 - 14]) ^ a_data[24 - 16];
		a_data[25] = ((a_data[25 - 3] ^ a_data[25 - 8]) ^ a_data[25 - 14]) ^ a_data[25 - 16];
		a_data[26] = ((a_data[26 - 3] ^ a_data[26 - 8]) ^ a_data[26 - 14]) ^ a_data[26 - 16];
		a_data[27] = ((a_data[27 - 3] ^ a_data[27 - 8]) ^ a_data[27 - 14]) ^ a_data[27 - 16];
		a_data[28] = ((a_data[28 - 3] ^ a_data[28 - 8]) ^ a_data[28 - 14]) ^ a_data[28 - 16];
		a_data[29] = ((a_data[29 - 3] ^ a_data[29 - 8]) ^ a_data[29 - 14]) ^ a_data[29 - 16];
		a_data[30] = ((a_data[30 - 3] ^ a_data[30 - 8]) ^ a_data[30 - 14]) ^ a_data[30 - 16];
		a_data[31] = ((a_data[31 - 3] ^ a_data[31 - 8]) ^ a_data[31 - 14]) ^ a_data[31 - 16];
		a_data[32] = ((a_data[32 - 3] ^ a_data[32 - 8]) ^ a_data[32 - 14]) ^ a_data[32 - 16];
		a_data[33] = ((a_data[33 - 3] ^ a_data[33 - 8]) ^ a_data[33 - 14]) ^ a_data[33 - 16];
		a_data[34] = ((a_data[34 - 3] ^ a_data[34 - 8]) ^ a_data[34 - 14]) ^ a_data[34 - 16];
		a_data[35] = ((a_data[35 - 3] ^ a_data[35 - 8]) ^ a_data[35 - 14]) ^ a_data[35 - 16];
		a_data[36] = ((a_data[36 - 3] ^ a_data[36 - 8]) ^ a_data[36 - 14]) ^ a_data[36 - 16];
		a_data[37] = ((a_data[37 - 3] ^ a_data[37 - 8]) ^ a_data[37 - 14]) ^ a_data[37 - 16];
		a_data[38] = ((a_data[38 - 3] ^ a_data[38 - 8]) ^ a_data[38 - 14]) ^ a_data[38 - 16];
		a_data[39] = ((a_data[39 - 3] ^ a_data[39 - 8]) ^ a_data[39 - 14]) ^ a_data[39 - 16];
		a_data[40] = ((a_data[40 - 3] ^ a_data[40 - 8]) ^ a_data[40 - 14]) ^ a_data[40 - 16];
		a_data[41] = ((a_data[41 - 3] ^ a_data[41 - 8]) ^ a_data[41 - 14]) ^ a_data[41 - 16];
		a_data[42] = ((a_data[42 - 3] ^ a_data[42 - 8]) ^ a_data[42 - 14]) ^ a_data[42 - 16];
		a_data[43] = ((a_data[43 - 3] ^ a_data[43 - 8]) ^ a_data[43 - 14]) ^ a_data[43 - 16];
		a_data[44] = ((a_data[44 - 3] ^ a_data[44 - 8]) ^ a_data[44 - 14]) ^ a_data[44 - 16];
		a_data[45] = ((a_data[45 - 3] ^ a_data[45 - 8]) ^ a_data[45 - 14]) ^ a_data[45 - 16];
		a_data[46] = ((a_data[46 - 3] ^ a_data[46 - 8]) ^ a_data[46 - 14]) ^ a_data[46 - 16];
		a_data[47] = ((a_data[47 - 3] ^ a_data[47 - 8]) ^ a_data[47 - 14]) ^ a_data[47 - 16];
		a_data[48] = ((a_data[48 - 3] ^ a_data[48 - 8]) ^ a_data[48 - 14]) ^ a_data[48 - 16];
		a_data[49] = ((a_data[49 - 3] ^ a_data[49 - 8]) ^ a_data[49 - 14]) ^ a_data[49 - 16];
		a_data[50] = ((a_data[50 - 3] ^ a_data[50 - 8]) ^ a_data[50 - 14]) ^ a_data[50 - 16];
		a_data[51] = ((a_data[51 - 3] ^ a_data[51 - 8]) ^ a_data[51 - 14]) ^ a_data[51 - 16];
		a_data[52] = ((a_data[52 - 3] ^ a_data[52 - 8]) ^ a_data[52 - 14]) ^ a_data[52 - 16];
		a_data[53] = ((a_data[53 - 3] ^ a_data[53 - 8]) ^ a_data[53 - 14]) ^ a_data[53 - 16];
		a_data[54] = ((a_data[54 - 3] ^ a_data[54 - 8]) ^ a_data[54 - 14]) ^ a_data[54 - 16];
		a_data[55] = ((a_data[55 - 3] ^ a_data[55 - 8]) ^ a_data[55 - 14]) ^ a_data[55 - 16];
		a_data[56] = ((a_data[56 - 3] ^ a_data[56 - 8]) ^ a_data[56 - 14]) ^ a_data[56 - 16];
		a_data[57] = ((a_data[57 - 3] ^ a_data[57 - 8]) ^ a_data[57 - 14]) ^ a_data[57 - 16];
		a_data[58] = ((a_data[58 - 3] ^ a_data[58 - 8]) ^ a_data[58 - 14]) ^ a_data[58 - 16];
		a_data[59] = ((a_data[59 - 3] ^ a_data[59 - 8]) ^ a_data[59 - 14]) ^ a_data[59 - 16];
		a_data[60] = ((a_data[60 - 3] ^ a_data[60 - 8]) ^ a_data[60 - 14]) ^ a_data[60 - 16];
		a_data[61] = ((a_data[61 - 3] ^ a_data[61 - 8]) ^ a_data[61 - 14]) ^ a_data[61 - 16];
		a_data[62] = ((a_data[62 - 3] ^ a_data[62 - 8]) ^ a_data[62 - 14]) ^ a_data[62 - 16];
		a_data[63] = ((a_data[63 - 3] ^ a_data[63 - 8]) ^ a_data[63 - 14]) ^ a_data[63 - 16];
		a_data[64] = ((a_data[64 - 3] ^ a_data[64 - 8]) ^ a_data[64 - 14]) ^ a_data[64 - 16];
		a_data[65] = ((a_data[65 - 3] ^ a_data[65 - 8]) ^ a_data[65 - 14]) ^ a_data[65 - 16];
		a_data[66] = ((a_data[66 - 3] ^ a_data[66 - 8]) ^ a_data[66 - 14]) ^ a_data[66 - 16];
		a_data[67] = ((a_data[67 - 3] ^ a_data[67 - 8]) ^ a_data[67 - 14]) ^ a_data[67 - 16];
		a_data[68] = ((a_data[68 - 3] ^ a_data[68 - 8]) ^ a_data[68 - 14]) ^ a_data[68 - 16];
		a_data[69] = ((a_data[69 - 3] ^ a_data[69 - 8]) ^ a_data[69 - 14]) ^ a_data[69 - 16];
		a_data[70] = ((a_data[70 - 3] ^ a_data[70 - 8]) ^ a_data[70 - 14]) ^ a_data[70 - 16];
		a_data[71] = ((a_data[71 - 3] ^ a_data[71 - 8]) ^ a_data[71 - 14]) ^ a_data[71 - 16];
		a_data[72] = ((a_data[72 - 3] ^ a_data[72 - 8]) ^ a_data[72 - 14]) ^ a_data[72 - 16];
		a_data[73] = ((a_data[73 - 3] ^ a_data[73 - 8]) ^ a_data[73 - 14]) ^ a_data[73 - 16];
		a_data[74] = ((a_data[74 - 3] ^ a_data[74 - 8]) ^ a_data[74 - 14]) ^ a_data[74 - 16];
		a_data[75] = ((a_data[75 - 3] ^ a_data[75 - 8]) ^ a_data[75 - 14]) ^ a_data[75 - 16];
		a_data[76] = ((a_data[76 - 3] ^ a_data[76 - 8]) ^ a_data[76 - 14]) ^ a_data[76 - 16];
		a_data[77] = ((a_data[77 - 3] ^ a_data[77 - 8]) ^ a_data[77 - 14]) ^ a_data[77 - 16];
		a_data[78] = ((a_data[78 - 3] ^ a_data[78 - 8]) ^ a_data[78 - 14]) ^ a_data[78 - 16];
		a_data[79] = ((a_data[79 - 3] ^ a_data[79 - 8]) ^ a_data[79 - 14]) ^ a_data[79 - 16];

	} // end function Expand
		
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
	
	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(5 * sizeof(uint32_t));
		Converters::be32_copy(&state.get()[0], 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult
		
	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		uint32_t A, B, C, D, E;

		Converters::be32_copy(a_data, a_index, &data.get()[0], 0, 64);

		Expand(&data.get()[0]);

		A = state.get()[0];
		B = state.get()[1];
		C = state.get()[2];
		D = state.get()[3];
		E = state.get()[4];

		E = (data.get()[0] + C1 + Bits::RotateLeft32(A, 5) +
			(D ^ (B & (C ^ D)))) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[1] + C1 + Bits::RotateLeft32(E, 5) +
			(C ^ (A & (B ^ C)))) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[2] + C1 + Bits::RotateLeft32(D, 5) +
			(B ^ (E & (A ^ B)))) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[3] + C1 + Bits::RotateLeft32(C, 5) +
			(A ^ (D & (E ^ A)))) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[4] + C1 + Bits::RotateLeft32(B, 5) +
			(E ^ (C & (D ^ E)))) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[5] + C1 + Bits::RotateLeft32(A, 5) +
			(D ^ (B & (C ^ D)))) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[6] + C1 + Bits::RotateLeft32(E, 5) +
			(C ^ (A & (B ^ C)))) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[7] + C1 + Bits::RotateLeft32(D, 5) +
			(B ^ (E & (A ^ B)))) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[8] + C1 + Bits::RotateLeft32(C, 5) +
			(A ^ (D & (E ^ A)))) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[9] + C1 + Bits::RotateLeft32(B, 5) +
			(E ^ (C & (D ^ E)))) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[10] + C1 + Bits::RotateLeft32(A, 5) +
			(D ^ (B & (C ^ D)))) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[11] + C1 + Bits::RotateLeft32(E, 5) +
			(C ^ (A & (B ^ C)))) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[12] + C1 + Bits::RotateLeft32(D, 5) +
			(B ^ (E & (A ^ B)))) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[13] + C1 + Bits::RotateLeft32(C, 5) +
			(A ^ (D & (E ^ A)))) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[14] + C1 + Bits::RotateLeft32(B, 5) +
			(E ^ (C & (D ^ E)))) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[15] + C1 + Bits::RotateLeft32(A, 5) +
			(D ^ (B & (C ^ D)))) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[16] + C1 + Bits::RotateLeft32(E, 5) +
			(C ^ (A & (B ^ C)))) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[17] + C1 + Bits::RotateLeft32(D, 5) +
			(B ^ (E & (A ^ B)))) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[18] + C1 + Bits::RotateLeft32(C, 5) +
			(A ^ (D & (E ^ A)))) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[19] + C1 + Bits::RotateLeft32(B, 5) +
			(E ^ (C & (D ^ E)))) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[20] + C2 + Bits::RotateLeft32(A, 5) + (B ^ C ^ D)) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[21] + C2 + Bits::RotateLeft32(E, 5) + (A ^ B ^ C)) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[22] + C2 + Bits::RotateLeft32(D, 5) + (E ^ A ^ B)) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[23] + C2 + Bits::RotateLeft32(C, 5) + (D ^ E ^ A)) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[24] + C2 + Bits::RotateLeft32(B, 5) + (C ^ D ^ E)) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[25] + C2 + Bits::RotateLeft32(A, 5) + (B ^ C ^ D)) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[26] + C2 + Bits::RotateLeft32(E, 5) + (A ^ B ^ C)) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[27] + C2 + Bits::RotateLeft32(D, 5) + (E ^ A ^ B)) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[28] + C2 + Bits::RotateLeft32(C, 5) + (D ^ E ^ A)) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[29] + C2 + Bits::RotateLeft32(B, 5) + (C ^ D ^ E)) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[30] + C2 + Bits::RotateLeft32(A, 5) + (B ^ C ^ D)) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[31] + C2 + Bits::RotateLeft32(E, 5) + (A ^ B ^ C)) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[32] + C2 + Bits::RotateLeft32(D, 5) + (E ^ A ^ B)) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[33] + C2 + Bits::RotateLeft32(C, 5) + (D ^ E ^ A)) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[34] + C2 + Bits::RotateLeft32(B, 5) + (C ^ D ^ E)) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[35] + C2 + Bits::RotateLeft32(A, 5) + (B ^ C ^ D)) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[36] + C2 + Bits::RotateLeft32(E, 5) + (A ^ B ^ C)) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[37] + C2 + Bits::RotateLeft32(D, 5) + (E ^ A ^ B)) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[38] + C2 + Bits::RotateLeft32(C, 5) + (D ^ E ^ A)) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[39] + C2 + Bits::RotateLeft32(B, 5) + (C ^ D ^ E)) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[40] + C3 + Bits::RotateLeft32(A, 5) +
			((B & C) | (D & (B | C)))) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[41] + C3 + Bits::RotateLeft32(E, 5) +
			((A & B) | (C & (A | B)))) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[42] + C3 + Bits::RotateLeft32(D, 5) +
			((E & A) | (B & (E | A)))) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[43] + C3 + Bits::RotateLeft32(C, 5) +
			((D & E) | (A & (D | E)))) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[44] + C3 + Bits::RotateLeft32(B, 5) +
			((C & D) | (E & (C | D)))) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[45] + C3 + Bits::RotateLeft32(A, 5) +
			((B & C) | (D & (B | C)))) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[46] + C3 + Bits::RotateLeft32(E, 5) +
			((A & B) | (C & (A | B)))) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[47] + C3 + Bits::RotateLeft32(D, 5) +
			((E & A) | (B & (E | A)))) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[48] + C3 + Bits::RotateLeft32(C, 5) +
			((D & E) | (A & (D | E)))) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[49] + C3 + Bits::RotateLeft32(B, 5) +
			((C & D) | (E & (C | D)))) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[50] + C3 + Bits::RotateLeft32(A, 5) +
			((B & C) | (D & (B | C)))) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[51] + C3 + Bits::RotateLeft32(E, 5) +
			((A & B) | (C & (A | B)))) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[52] + C3 + Bits::RotateLeft32(D, 5) +
			((E & A) | (B & (E | A)))) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[53] + C3 + Bits::RotateLeft32(C, 5) +
			((D & E) | (A & (D | E)))) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[54] + C3 + Bits::RotateLeft32(B, 5) +
			((C & D) | (E & (C | D)))) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[55] + C3 + Bits::RotateLeft32(A, 5) +
			((B & C) | (D & (B | C)))) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[56] + C3 + Bits::RotateLeft32(E, 5) +
			((A & B) | (C & (A | B)))) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[57] + C3 + Bits::RotateLeft32(D, 5) +
			((E & A) | (B & (E | A)))) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[58] + C3 + Bits::RotateLeft32(C, 5) +
			((D & E) | (A & (D | E)))) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[59] + C3 + Bits::RotateLeft32(B, 5) +
			((C & D) | (E & (C | D)))) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[60] + C4 + Bits::RotateLeft32(A, 5) + (B ^ C ^ D)) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[61] + C4 + Bits::RotateLeft32(E, 5) + (A ^ B ^ C)) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[62] + C4 + Bits::RotateLeft32(D, 5) + (E ^ A ^ B)) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[63] + C4 + Bits::RotateLeft32(C, 5) + (D ^ E ^ A)) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[64] + C4 + Bits::RotateLeft32(B, 5) + (C ^ D ^ E)) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[65] + C4 + Bits::RotateLeft32(A, 5) + (B ^ C ^ D)) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[66] + C4 + Bits::RotateLeft32(E, 5) + (A ^ B ^ C)) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[67] + C4 + Bits::RotateLeft32(D, 5) + (E ^ A ^ B)) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[68] + C4 + Bits::RotateLeft32(C, 5) + (D ^ E ^ A)) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[69] + C4 + Bits::RotateLeft32(B, 5) + (C ^ D ^ E)) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[70] + C4 + Bits::RotateLeft32(A, 5) + (B ^ C ^ D)) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[71] + C4 + Bits::RotateLeft32(E, 5) + (A ^ B ^ C)) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[72] + C4 + Bits::RotateLeft32(D, 5) + (E ^ A ^ B)) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[73] + C4 + Bits::RotateLeft32(C, 5) + (D ^ E ^ A)) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[74] + C4 + Bits::RotateLeft32(B, 5) + (C ^ D ^ E)) + A;

		C = Bits::RotateLeft32(C, 30);
		E = (data.get()[75] + C4 + Bits::RotateLeft32(A, 5) + (B ^ C ^ D)) + E;

		B = Bits::RotateLeft32(B, 30);
		D = (data.get()[76] + C4 + Bits::RotateLeft32(E, 5) + (A ^ B ^ C)) + D;

		A = Bits::RotateLeft32(A, 30);
		C = (data.get()[77] + C4 + Bits::RotateLeft32(D, 5) + (E ^ A ^ B)) + C;

		E = Bits::RotateLeft32(E, 30);
		B = (data.get()[78] + C4 + Bits::RotateLeft32(C, 5) + (D ^ E ^ A)) + B;

		D = Bits::RotateLeft32(D, 30);
		A = (data.get()[79] + C4 + Bits::RotateLeft32(B, 5) + (C ^ D ^ E)) + A;

		C = Bits::RotateLeft32(C, 30);

		state.get()[0] = state.get()[0] + A;
		state.get()[1] = state.get()[1] + B;
		state.get()[2] = state.get()[2] + C;
		state.get()[3] = state.get()[3] + D;
		state.get()[4] = state.get()[4] + E;

		memset(data.get(), 0, sizeof(data.get()));
	} // end function TransformBlock


protected:
	shared_ptr<uint32_t> state;
	shared_ptr<uint32_t> data;

	static const uint32_t C1 = 0x5A827999;
	static const uint32_t C2 = 0x6ED9EBA1;
	static const uint32_t C3 = 0x8F1BBCDC;
	static const uint32_t C4 = 0xCA62C1D6;
	

}; // end class SHA0


#endif //!HLPSHA0_H