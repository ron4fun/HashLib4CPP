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

#ifndef HLPSIPHASH_H
#define HLPSIPHASH_H

#include "../Base/HlpHash.h"
#include "../Nullable/HlpNullable.h"
#include "../Interfaces/HlpIHashInfo.h"


class SipHash : public Hash, public IIHash64, public IIHashWithKey, public IITransformBlock
{
public:
	SipHash(const int32_t a_compression_rounds = 2, const int32_t a_finalization_rounds = 4)
		: Hash(8, 8)
	{
		name = __func__;

		key0 = KEY0;
		key1 = KEY1;
		cr = a_compression_rounds;
		fr = a_finalization_rounds;
		buf.resize(8);
	} // end constructor

	virtual void Initialize()
	{
		v0 = V0;
		v1 = V1;
		v2 = V2;
		v3 = V3;
		total_length = 0;
		idx = 0;

		v3 = v3 ^ key1;
		v2 = v2 ^ key0;
		v1 = v1 ^ key1;
		v0 = v0 ^ key0;
	} // end function Initialize

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		register int32_t i, Length, iter, offset;
		const uint8_t *ptr_a_data = &a_data[a_index];


		Length = a_length;
		i = a_index;

		total_length += Length;

		// consume last pending bytes

		if ((idx != 0) && (a_length != 0))
		{
			#ifdef DEBUG

			assert(a_index == 0); // nothing would work anyways if a_index is !=0

			#endif // DEBUG

			while ((idx < 8) && (Length != 0))
			{
				buf[idx] = *(ptr_a_data + a_index);
				idx++;
				a_index++;
				Length--;
			}
			if (idx == 8)
			{
				uint8_t *ptr_Fm_buf = &buf[0];
				m = Converters::ReadBytesAsUInt64LE(ptr_Fm_buf, 0);
				ProcessBlock(m);
				idx = 0;
			}
		}

		iter = Length >> 3;

		// body

		while (i < iter)
		{
			m = Converters::ReadBytesAsUInt64LE(ptr_a_data, a_index + (i * 8));
			ProcessBlock(m);
			i++;
		} // end while

		  // save pending end bytes
		offset = a_index + (i * 8);

		while (offset < (Length + a_index))
		{
			ByteUpdate(a_data[offset]);
			offset++;
		} // end while
	} // end function TransformBytes

	virtual IHashResult TransformFinal()
	{
		Finish();

		IHashResult result = make_shared<HashResult>(v0 ^ v1 ^ v2 ^ v3);

		Initialize();

		return result;
	} // end function TransformFinal

private:
	inline void Compress()
	{
		v0 = v0 + v1;
		v2 = v2 + v3;
		v1 = Bits::RotateLeft64(v1, 13);
		v3 = Bits::RotateLeft64(v3, 16);
		v1 = v1 ^ v0;
		v3 = v3 ^ v2;
		v0 = Bits::RotateLeft64(v0, 32);
		v2 = v2 + v1;
		v0 = v0 + v3;
		v1 = Bits::RotateLeft64(v1, 17);
		v3 = Bits::RotateLeft64(v3, 21);
		v1 = v1 ^ v2;
		v3 = v3 ^ v0;
		v2 = Bits::RotateLeft64(v2, 32);
	} // end function Compress

	inline void CompressTimes(const int32_t a_times)
	{
		register int32_t i = 0;
		
		while (i < a_times)
		{
			Compress();
			i++;
		} // end while
	} // end function CompressTimes

	inline void ProcessBlock(const uint64_t a_m)
	{
		v3 = v3 ^ a_m;
		CompressTimes(cr);
		v0 = v0 ^ a_m;
	} // end function ProcessBlock

	inline void ByteUpdate(const uint8_t a_b)
	{
		buf[idx] = a_b;
		idx++;
		if (idx >= 8)
		{
			uint8_t *ptr_Fm_buf = &buf[0];
			uint64_t m = Converters::ReadBytesAsUInt64LE(ptr_Fm_buf, 0);
			ProcessBlock(m);
			idx = 0;
		} // end if
	} // end function ByteUpdate

	void Finish()
	{
		register uint64_t b = uint64_t(total_length & 0xFF) << 56;
		
		if (idx != 0)
		{
			switch (idx)
			{
			case 7:
				b = b | (uint64_t(buf[6]) << 48);
				b = b | (uint64_t(buf[5]) << 40);
				b = b | (uint64_t(buf[4]) << 32);
				b = b | (uint64_t(buf[3]) << 24);
				b = b | (uint64_t(buf[2]) << 16);
				b = b | (uint64_t(buf[1]) << 8);
				b = b | (uint64_t(buf[0]));
				break;

			case 6:
				b = b | (uint64_t(buf[5]) << 40);
				b = b | (uint64_t(buf[4]) << 32);
				b = b | (uint64_t(buf[3]) << 24);
				b = b | (uint64_t(buf[2]) << 16);
				b = b | (uint64_t(buf[1]) << 8);
				b = b | (uint64_t(buf[0]));
				break;

			case 5:
				b = b | (uint64_t(buf[4]) << 32);
				b = b | (uint64_t(buf[3]) << 24);
				b = b | (uint64_t(buf[2]) << 16);
				b = b | (uint64_t(buf[1]) << 8);
				b = b | (uint64_t(buf[0]));
				break;

			case 4:
				b = b | (uint64_t(buf[3]) << 24);
				b = b | (uint64_t(buf[2]) << 16);
				b = b | (uint64_t(buf[1]) << 8);
				b = b | (uint64_t(buf[0]));
				break;

			case 3:
				b = b | (uint64_t(buf[2]) << 16);
				b = b | (uint64_t(buf[1]) << 8);
				b = b | (uint64_t(buf[0]));
				break;

			case 2:
				b = b | (uint64_t(buf[1]) << 8);
				b = b | (uint64_t(buf[0]));
				break;

			case 1:
				b = b | (uint64_t(buf[0]));
			} // end switch
		} // end if

		v3 = v3 ^ b;
		CompressTimes(cr);
		v0 = v0 ^ b;
		v2 = v2 ^ 0xFF;
		CompressTimes(fr);
	} // end function Finish

	virtual inline NullableInteger GetKeyLength() const
	{
		return 16;
	} // end function GetKeyLength

	virtual inline HashLibByteArray GetKey() const
	{
		HashLibByteArray LKey = HashLibByteArray(GetKeyLength().GetValue());

		Converters::ReadUInt64AsBytesLE(key0, LKey, 0);
		Converters::ReadUInt64AsBytesLE(key1, LKey, 8);

		return LKey;
	} // end function GetKey

	virtual inline void SetKey(const HashLibByteArray &value)
	{
		if (value.empty())
		{
			key0 = KEY0;
			key1 = KEY1;
		} // end if
		else
		{
			if (value.size() != GetKeyLength().GetValue())
				throw ArgumentHashLibException(InvalidKeyLength + GetKeyLength().GetValue());
		key0 = Converters::ReadBytesAsUInt64LE((uint8_t*)&value[0], 0);
		key1 = Converters::ReadBytesAsUInt64LE((uint8_t*)&value[0], 8);
		} // end else
	} // end function SetKey

protected:
	uint64_t v0, v1, v2, v3, key0, key1, total_length, m;
	int32_t cr, fr, idx;
	HashLibByteArray buf;

private:
	static const uint64_t V0 = uint64_t(0x736F6D6570736575);
	static const uint64_t V1 = uint64_t(0x646F72616E646F6D);
	static const uint64_t V2 = uint64_t(0x6C7967656E657261);
	static const uint64_t V3 = uint64_t(0x7465646279746573);
	static const uint64_t KEY0 = uint64_t(0x0706050403020100);
	static const uint64_t KEY1 = uint64_t(0x0F0E0D0C0B0A0908);

	static const char *InvalidKeyLength;

}; // end class SipHash

const char *SipHash::InvalidKeyLength = "KeyLength Must Be Equal to %d";


/// <summary>
/// SipHash 2 - 4 algorithm.
/// <summary>
class SipHash2_4 : public SipHash
{
public:
	SipHash2_4()
		: SipHash(2, 4)
	{} // end constructor

	virtual IHash Clone() const
	{
		SipHash2_4 HashInstance;

		HashInstance = SipHash2_4();
		HashInstance.v0 = v0;
		HashInstance.v1 = v1;
		HashInstance.v2 = v2;
		HashInstance.v3 = v3;
		HashInstance.key0 = key0;
		HashInstance.key1 = key1;
		HashInstance.total_length = total_length;
		HashInstance.cr = cr;
		HashInstance.fr = fr;
		HashInstance.idx = idx;
		HashInstance.buf = buf;

		IHash hash = make_shared<SipHash2_4>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class SipHash2_4


#endif // !HLPSIPHASH_H
