#ifndef HLPMURMURHASH3_X86_32_H
#define HLPMURMURHASH3_X86_32_H

#include "../Base/HlpHash.h"
#include "../Nullable/HlpNullable.h"
#include "../Interfaces/HlpIHashInfo.h"


class MurmurHash3_x86_32 : public Hash, public IIHash32, public IIHashWithKey, public IITransformBlock
{
public:
	MurmurHash3_x86_32()
		: Hash(4, 4)
	{
		name = __func__;

		key = CKEY;
		buf = make_shared<HashLibByteArray>(4);
	} // end constructor

	~MurmurHash3_x86_32()
	{} // end destructor

	virtual void Initialize()
	{
		h = key;
		total_length = 0;
		idx = 0;
	} // end function Initialize

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		register int32_t len, nBlocks, i, offset;
		register uint32_t k;
		const uint8_t *ptr_a_data;

		len = a_length;
		i = a_index;
		ptr_a_data = &a_data[0];
		nBlocks = len >> 2;

		// body
		while (i < nBlocks)
		{
			k = Converters::ReadBytesAsUInt32LE(ptr_a_data, a_index + i * 4);
			TransformUInt32Fast(k);
			i++;
		} // end while

		total_length += len;

		offset = (i * 4);

		while (offset < len)
		{
			ByteUpdate(a_data[offset]);
			offset++;
		} // end while
	} // end function TransformBytes

	virtual IHashResult TransformFinal()
	{
		Finish();

		IHashResult result(new HashResult(h));

		Initialize();

		return result;
	} // end function TransformFinal

private:
	inline void TransformUInt32Fast(const uint32_t a_data)
	{
		register uint32_t k = a_data;
		
		k = k * C1;
		k = Bits::RotateLeft32(k, 15);
		k = k * C2;

		h = h ^ k;
		h = Bits::RotateLeft32(h, 13);
		h = (h * 5) + C3;
	} // end function TransformUInt32Fast

	inline void ByteUpdate(const uint8_t a_b)
	{
		register uint32_t k = 0;
		uint8_t *ptr_Fm_buf = 0;
		
		(*buf)[idx] = a_b;
		idx++;
		if (idx >= 4)
		{
			ptr_Fm_buf = &(*buf)[0];
			k = Converters::ReadBytesAsUInt32LE(ptr_Fm_buf, 0);
			TransformUInt32Fast(k);
			idx = 0;
		} // end if
	} // end function ByteUpdate

	void Finish()
	{
		 register uint32_t k = 0;
		
		 // tail
		 if (idx != 0)
		 {
			 switch (idx)
			 {
			 case 3:
				 k = k ^ ((*buf)[2] << 16);
				 k = k ^ ((*buf)[1] << 8);
				 k = k ^ (*buf)[0];
				 k = k * C1;
				 k = Bits::RotateLeft32(k, 15);
				 k = k * C2;
				 h = h ^ k;
				 break;

			 case 2:
				 k = k ^ ((*buf)[1] << 8);
				 k = k ^ (*buf)[0];
				 k = k * C1;
				 k = Bits::RotateLeft32(k, 15);
				 k = k * C2;
				 h = h ^ k;
				 break;

			 case 1:
				 k = k ^ (*buf)[0];
				 k = k * C1;
				 k = Bits::RotateLeft32(k, 15);
				 k = k * C2;
				 h = h ^ k;
			 } // end switch
		 } // end if

		// finalization
		h = h ^ total_length;
		h = h ^ (h >> 16);
		h = h * C4;
		h = h ^ (h >> 13);
		h = h * C5;
		h = h ^ (h >> 16);
	} // end function Finish

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
	uint32_t key, h, total_length;
	int32_t idx;
	shared_ptr<HashLibByteArray> buf;

	static const uint32_t CKEY = uint32_t(0x0);

	static const uint32_t C1 = uint32_t(0xCC9E2D51);
	static const uint32_t C2 = uint32_t(0x1B873593);
	static const uint32_t C3 = uint32_t(0xE6546B64);
	static const uint32_t C4 = uint32_t(0x85EBCA6B);
	static const uint32_t C5 = uint32_t(0xC2B2AE35);
	
	static const char *InvalidKeyLength;

}; // end class MurmurHash3_x86_32

const char *MurmurHash3_x86_32::InvalidKeyLength = "KeyLength Must Be Equal to %d";

#endif // !HLPMURMURHASH3_X86_32_H
