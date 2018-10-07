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

#ifndef HLPRADIOGATUN32_H
#define HLPRADIOGATUN32_H

#include "../Base/HlpHashCryptoNotBuildIn.h"


class RadioGatun32 : public BlockHash, public IICryptoNotBuildIn, public IITransformBlock
{
public:
	RadioGatun32()
		: BlockHash(32, 12)
	{
		name = __func__;

		mill.resize(19);
		a.resize(19);
		data.resize(3);

		belt.resize(13);
		
		for (register uint32_t i = 0; i < 13; i++)
			belt[i] = HashLibUInt32Array(3);
	
	} // end constructor

	virtual IHash Clone() const
	{
		RadioGatun32 HashInstance;

		HashInstance = RadioGatun32();
		HashInstance.mill = mill;
		HashInstance.belt = belt;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<RadioGatun32>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		memset(&mill[0], 0, 19 * sizeof(uint32_t));
		
		for (register uint32_t i = 0; i < 13; i++)
			memset(&belt[i][0], 0, 3 * sizeof(uint32_t));

		BlockHash::Initialize();
	} // end function Initialize

protected:
	virtual void Finish()
	{
		int32_t padding_size = 12 - (processed_bytes % 12);

		HashLibByteArray pad = HashLibByteArray(padding_size);

		pad[0] = 0x01;

		TransformBytes(pad, 0, padding_size);

		for (register uint32_t i = 0; i < 16; i++)
			RoundFunction();

	} // end function Finish

	virtual HashLibByteArray GetResult()
	{
		HashLibUInt32Array tempRes = HashLibUInt32Array(8);

		HashLibByteArray result = HashLibByteArray(8 * sizeof(uint32_t));

		for (register uint32_t i = 0; i < 4; i++)
		{
			RoundFunction();
			memmove(&tempRes[i * 2], &mill[1], 2 * sizeof(uint32_t));
		} // end for

		Converters::le32_copy(&tempRes[0], 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult

	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		Converters::le32_copy(a_data, a_index, &data[0], 0, 12);

		register uint32_t i = 0;
		while (i < 3)
		{
			mill[i + 16] = mill[i + 16] ^ data[i];
			belt[0][i] = belt[0][i] ^ data[i];
			i++;
		} // end while

		RoundFunction();

		memset(&data[0], 0, 3 * sizeof(uint32_t));
	} // end function TransformBlock

private:
	inline void RoundFunction()
	{
		HashLibUInt32Array q = belt[12];
		
		register uint32_t i = 12;
		while (i > 0)
		{
			belt[i] = belt[i - 1];
			i--;
		} // end while

		belt[0] = q;

		i = 0;
		while (i < 12)
		{
			belt[i + 1][i % 3] = belt[i + 1][i % 3] ^ mill[i + 1];
			i++;
		} // end while

		i = 0;
		while (i < 19)
		{
			a[i] = mill[i] ^ (mill[(i + 1) % 19] | ~mill[(i + 2) % 19]);
			i++;
		} // end while

		i = 0;
		while (i < 19)
		{
			mill[i] = Bits::RotateRight32(a[(7 * i) % 19], (i * (i + 1)) >> 1);
			i++;
		} // end while

		i = 0;
		while (i < 19)
		{
			a[i] = mill[i] ^ mill[(i + 1) % 19] ^ mill[(i + 4) % 19];
			i++;
		} // end while

		a[0] = a[0] ^ 1;

		i = 0;
		while (i < 19)
		{
			mill[i] = a[i];
			i++;
		} // end while

		i = 0;
		while (i < 3)
		{
			mill[i + 13] = mill[i + 13] ^ q[i];
			i++;
		} // end while
	} // end function RoundFunction

private:
	HashLibUInt32Array mill, data, a;

	HashLibMatrixUInt32Array belt;
			 
}; // end class RadioGatun32


#endif // !HLPRADIOGATUN32_H

