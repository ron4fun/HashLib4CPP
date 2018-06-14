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

#ifndef HLPHAS160_H
#define HLPHAS160_H

#include "../Base/HlpHashCryptoNotBuildIn.h"


class HAS160 : public BlockHash, public IICryptoNotBuildIn, public IITransformBlock
{
public:
	HAS160()
		: BlockHash(20, 64)
	{
		name = __func__;

		hash = shared_ptr<uint32_t>(new uint32_t[5], default_delete<uint32_t[]>());
		data = shared_ptr<uint32_t>(new uint32_t[20], default_delete<uint32_t[]>());
	} // end constructor

	~HAS160()
	{
		//delete[] hash;
		//delete[] data;
	} // end destructor

	virtual void Initialize()
	{
		hash.get()[0] = 0x67452301;
		hash.get()[1] = 0xEFCDAB89;
		hash.get()[2] = 0x98BADCFE;
		hash.get()[3] = 0x10325476;
		hash.get()[4] = 0xC3D2E1F0;

		BlockHash::Initialize();
	} // end function Initialize

protected:
	virtual void Finish()
	{
		int32_t pad_index;

		uint64_t bits = processed_bytes * 8;
		if (buffer->GetPos() < 56)
			pad_index = 56 - buffer->GetPos();
		else
			pad_index = 120 - buffer->GetPos();

		HashLibByteArray pad = HashLibByteArray(pad_index + 8);

		pad[0] = 0x80;

		bits = Converters::le2me_64(bits);

		Converters::ReadUInt64AsBytesLE(bits, pad, pad_index);

		pad_index = pad_index + 8;

		TransformBytes(pad, 0, pad_index);

	} // end function Finish
	
	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(5 * sizeof(uint32_t));

		Converters::le32_copy(&hash.get()[0], 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult
		
	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t A, B, C, D, E, T;

		A = hash.get()[0];
		B = hash.get()[1];
		C = hash.get()[2];
		D = hash.get()[3];
		E = hash.get()[4];

		Converters::le32_copy(a_data, a_index, &data.get()[0], 0, 64);

		data.get()[16] = data.get()[0] ^ data.get()[1] ^ data.get()[2] ^ data.get()[3];
		data.get()[17] = data.get()[4] ^ data.get()[5] ^ data.get()[6] ^ data.get()[7];
		data.get()[18] = data.get()[8] ^ data.get()[9] ^ data.get()[10] ^ data.get()[11];
		data.get()[19] = data.get()[12] ^ data.get()[13] ^ data.get()[14] ^ data.get()[15];

		register uint32_t r = 0;
		while (r < 20)
		{
			T = data.get()[index[r]] + (A << rot[r] | A >> tor[r]) + ((B & C) | (~B & D)) + E;
			E = D;
			D = C;
			C = B << 10 | B >> 22;
			B = A;
			A = T;
			r += 1;
		} // end while

		data.get()[16] = data.get()[3] ^ data.get()[6] ^ data.get()[9] ^ data.get()[12];
		data.get()[17] = data.get()[2] ^ data.get()[5] ^ data.get()[8] ^ data.get()[15];
		data.get()[18] = data.get()[1] ^ data.get()[4] ^ data.get()[11] ^ data.get()[14];
		data.get()[19] = data.get()[0] ^ data.get()[7] ^ data.get()[10] ^ data.get()[13];

		r = 20;
		while (r < 40)
		{
			T = data.get()[index[r]] + 0x5A827999 + (A << rot[r - 20] | A >> tor[r - 20]) + (B ^ C ^ D) + E;
			E = D;
			D = C;
			C = B << 17 | B >> 15;
			B = A;
			A = T;
			r += 1;
		} // end while
			
		data.get()[16] = data.get()[5] ^ data.get()[7] ^ data.get()[12] ^ data.get()[14];
		data.get()[17] = data.get()[0] ^ data.get()[2] ^ data.get()[9] ^ data.get()[11];
		data.get()[18] = data.get()[4] ^ data.get()[6] ^ data.get()[13] ^ data.get()[15];
		data.get()[19] = data.get()[1] ^ data.get()[3] ^ data.get()[8] ^ data.get()[10];

		r = 40;
		while (r < 60)
		{
			T = data.get()[index[r]] + 0x6ED9EBA1 + (A << rot[r - 40] | A >> tor[r - 40]) + (C ^ (B | ~D)) + E;
			E = D;
			D = C;
			C = B << 25 | B >> 7;
			B = A;
			A = T;
			r += 1;
 		} // end while
	
		data.get()[16] = data.get()[2] ^ data.get()[7] ^ data.get()[8] ^ data.get()[13];
		data.get()[17] = data.get()[3] ^ data.get()[4] ^ data.get()[9] ^ data.get()[14];
		data.get()[18] = data.get()[0] ^ data.get()[5] ^ data.get()[10] ^ data.get()[15];
		data.get()[19] = data.get()[1] ^ data.get()[6] ^ data.get()[11] ^ data.get()[12];

		r = 60;
		while (r < 80)
		{
			T = data.get()[index[r]] + 0x8F1BBCDC + (A << rot[r - 60] | A >> tor[r - 60]) + (B ^ C ^ D) + E;
			E = D;
			D = C;
			C = B << 30 | B >> 2;
			B = A;
			A = T;
			r += 1;
		} // end while
	
		hash.get()[0] = hash.get()[0] + A;
		hash.get()[1] = hash.get()[1] + B;
		hash.get()[2] = hash.get()[2] + C;
		hash.get()[3] = hash.get()[3] + D;
		hash.get()[4] = hash.get()[4] + E;

		memset(&data.get()[0], 0, 20 * sizeof(uint32_t));

	} // end function TransformBlock

private:
	shared_ptr<uint32_t> hash;
	shared_ptr<uint32_t> data;

	static const int32_t rot[20]; 
	static const int32_t tor[20];
	static const int32_t index[80];


}; // end class HAS160

const int32_t HAS160::rot[20] = { 5, 11, 7, 15, 6, 13, 8, 14, 7, 12, 9, 11, 8, 15, 6, 12, 9, 14, 5, 13 };

const int32_t HAS160::tor[20] = { 27, 21, 25, 17, 26, 19, 24, 18, 25, 20, 23, 21, 24, 17, 26, 20, 23, 18, 27, 19 };

const int32_t HAS160::index[80] = { 18, 0, 1, 2, 3, 19, 4, 5, 6, 7, 16, 8,
									9, 10, 11, 17, 12, 13, 14, 15, 18, 3, 6, 9, 12, 19, 15, 2, 5, 8, 16, 11,
									14, 1, 4, 17, 7, 10, 13, 0, 18, 12, 5, 14, 7, 19, 0, 9, 2, 11, 16, 4, 13,
									6, 15, 17, 8, 1, 10, 3, 18, 7, 2, 13, 8, 19, 3, 14, 9, 4, 16, 15, 10, 5,
									0, 17, 11, 6, 1, 12 };


#endif // !HLPHAS160_H