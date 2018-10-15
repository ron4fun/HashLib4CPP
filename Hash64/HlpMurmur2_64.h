// ///////////////////////////////////////////////////////////////// //
// *C++ 11 HashLib4CPP Library                                 
// *Copyright(c) 2018  Mbadiwe Nnaemeka Ronald                 
// *Github Repository <https://github.com/ron4fun>             

// *Distributed under the MIT software license, see the accompanying file LICENSE 
// *or visit http ://www.opensource.org/licenses/mit-license.php.           

// *Acknowledgements:                                  
// ** //
// *Thanks to Ugochukwu Mmaduekwe (https://github.com/Xor-el) for his creative        
// *development of this library in Pascal/Delphi                         

// ////////////////////////////////////////////////////// ///////////////

#ifndef HLPMURMUR2_64_H
#define HLPMURMUR2_64_H

#include "../Nullable/HlpNullable.h"
#include "../Base/HlpMultipleTransformNonBlock.h"
#include "../Utils/HlpUtils.h"


class Murmur2_64 : public MultipleTransformNonBlock, public IIHash64, public IIHashWithKey, public IITransformBlock
{
public:
	Murmur2_64()
		: MultipleTransformNonBlock(8, 8)
	{
		name = __func__;

		key = CKEY;
	} // end constructor

	virtual IHashWithKey CloneHashWithKey() const
	{
		IHashWithKey hash = make_shared<Murmur2_64>(Copy());
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual IHash Clone() const
	{
		IHash hash = make_shared<Murmur2_64>(Copy());
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		working_key = key;
		MultipleTransformNonBlock::Initialize();
	} // end function Initialize

protected:
	virtual IHashResult ComputeAggregatedBytes(const HashLibByteArray &a_data)
	{
		register int32_t Length, current_index;
		register uint64_t k, h;

		Length = (int32_t)a_data.size();
		const uint8_t * ptr_a_data = &a_data[0];

		if (Length == 0)
			return make_shared<HashResult>(uint64_t(0));
		
		h = working_key ^ uint64_t(Length);
		current_index = 0;

		while (Length >= 8)
		{
			k = Converters::ReadBytesAsUInt64LE(ptr_a_data, current_index);

			k = k * M;
			k = k ^ (k >> R);
			k = k * M;

			h = h ^ k;
			h = h * M;

			current_index += 8;
			Length -= 8;
		} // end while

		switch (Length)
		{
		case 7:
			h = h ^ ((uint64_t(a_data[current_index]) << 48));
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 40);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 32);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 24);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 16);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 8);
			current_index++;
			h = h ^ uint64_t(a_data[current_index]);
			h = h * M;
			break;

		case 6:
			h = h ^ (uint64_t(a_data[current_index]) << 40);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 32);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 24);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 16);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 8);
			current_index++;
			h = h ^ uint64_t(a_data[current_index]);
			h = h * M;
			break;

		case 5:
			h = h ^ (uint64_t(a_data[current_index]) << 32);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 24);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 16);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 8);
			current_index++;
			h = h ^ uint64_t(a_data[current_index]);
			h = h * M;
			break;

		case 4:
			h = h ^ (uint64_t(a_data[current_index]) << 24);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 16);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 8);
			current_index++;
			h = h ^ uint64_t(a_data[current_index]);
			h = h * M;
			break;

		case 3:
			h = h ^ (uint64_t(a_data[current_index]) << 16);
			current_index++;
			h = h ^ (uint64_t(a_data[current_index]) << 8);
			current_index++;
			h = h ^ uint64_t(a_data[current_index]);
			h = h * M;
			break;

		case 2:
			h = h ^ (uint64_t(a_data[current_index]) << 8);
			current_index++;
			h = h ^ uint64_t(a_data[current_index]);
			h = h * M;
			break;

		case 1:
			h = h ^ uint64_t(a_data[current_index]);
			h = h * M;
		} // end switch

		h = h ^ (h >> R);
		h = h * M;
		h = h ^ (h >> R);

		return make_shared<HashResult>(h);
	} // end function ComputeAggregatedBytes

private:
	Murmur2_64 Copy() const
	{
		Murmur2_64 HashInstance;

		HashInstance = Murmur2_64();
		HashInstance.key = key;
		HashInstance.working_key = working_key;
		HashInstance._list = _list;

		return HashInstance;
	}

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
				throw ArgumentHashLibException(Utils::string_format(InvalidKeyLength, GetKeyLength().GetValue()));
			key = Converters::ReadBytesAsUInt32LE(&value[0], 0);
		} // end else
	} // end function SetKey

private:
	uint32_t key, working_key;

	static const uint32_t CKEY = uint32_t(0x0);
	static const uint64_t M = uint64_t(0xC6A4A7935BD1E995);
	static const int32_t R = int32_t(47);

	static const char *InvalidKeyLength;

}; // end class Murmur2_64

const char *Murmur2_64::InvalidKeyLength = "KeyLength Must Be Equal to %d";

#endif // !HLPMURMUR2_64_H
