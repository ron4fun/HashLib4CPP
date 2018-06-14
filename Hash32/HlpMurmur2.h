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

#ifndef HLPMURMUR2_H
#define HLPMURMUR2_H

#include "../Nullable/HlpNullable.h"
#include "../Base/HlpMultipleTransformNonBlock.h"


class Murmur2 : public MultipleTransformNonBlock, public IIHash32, public IIHashWithKey, public IITransformBlock
{
public:
	Murmur2()
		: MultipleTransformNonBlock(4, 4)
	{
		name = __func__;

		key = CKEY;
	} // end constructor
	
	virtual void Initialize()
	{
		working_key = key;
		MultipleTransformNonBlock::Initialize();
	} // end function Initialize

protected:
	virtual IHashResult ComputeAggregatedBytes(const HashLibByteArray &a_data)
	{
		return IHashResult(new HashResult(InternalComputeBytes(a_data)));
	} // end function ComputeAggregatedBytes

private:
	int32_t InternalComputeBytes(const HashLibByteArray &a_data)
	{
		register int32_t Length, current_index;
		register uint32_t k;

		Length = (int32_t)a_data.size();
		const uint8_t *ptr_a_data = &a_data[0];

		if (Length == 0)
			return 0;
		
		h = working_key ^ uint32_t(Length);
		current_index = 0;

		while (Length >= 4)
		{
			k = Converters::ReadBytesAsUInt32LE(ptr_a_data, current_index);

			TransformUInt32Fast(k);
			current_index += 4;
			Length -= 4;
		} // end while

		switch (Length)
		{
		case 3:
			h = h ^ (a_data[current_index + 2] << 16);
			h = h ^ (a_data[current_index + 1] << 8);
			h = h ^ (a_data[current_index]);
			h = h * M;
			break;

		case 2:
			h = h ^ (a_data[current_index + 1] << 8);
			h = h ^ (a_data[current_index]);
			h = h * M;
			break;

		case 1:
			h = h ^ (a_data[current_index]);
			h = h * M;
		} // end switch

		h = h ^ (h >> 13);

		h = h * M;
		h = h ^ (h >> 15);

		return int32_t(h);
	} // end function InternalComputeBytes

	inline void TransformUInt32Fast(uint32_t a_data)
	{
		a_data = a_data * M;
		a_data = a_data ^ (a_data >> R);
		a_data = a_data * M;

		h = h * M;
		h = h ^ a_data;
	} // end function TransformUInt32Fast

	virtual inline NullableInteger GetKeyLength() const
	{
		return 4;
	} // end function GetKeyLength

	virtual inline HashLibByteArray GetKey() const
	{
		return Converters::ReadUInt32AsBytesLE(key);
	} // end function GetKey

	virtual inline void SetKey(const HashLibByteArray &value)
	{
		if (value.empty())
			key = CKEY;
		else
		{
			if (value.size() != GetKeyLength().GetValue())
				throw ArgumentHashLibException(InvalidKeyLength + GetKeyLength().GetValue());
			key = Converters::ReadBytesAsUInt32LE(&value[0], 0);
		} // end else
	} // end function SetKey

private:
	uint32_t key, working_key, h;

	static const uint32_t CKEY = uint32_t(0x0);
	static const uint32_t M = uint32_t(0x5BD1E995);
	static const int32_t R = int32_t(24);

	static const char *InvalidKeyLength;

}; // end class Murmur2

const char *Murmur2::InvalidKeyLength = "KeyLength Must Be Equal to %d";

#endif // !HLPMURMUR2_H
