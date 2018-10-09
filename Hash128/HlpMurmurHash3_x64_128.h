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

#ifndef HLPMURMURHASH3_X64_128_H
#define HLPMURMURHASH3_X64_128_H

#include "../Base/HlpHash.h"
#include "../Nullable/HlpNullable.h"
#include "../Interfaces/HlpIHashInfo.h"
#include "../Utils/HlpUtils.h"


class MurmurHash3_x64_128 : public Hash, public IIHash128, public IIHashWithKey, public IITransformBlock
{
public:
	MurmurHash3_x64_128()
		: Hash(16, 16)
	{
		name = __func__;

		key = CKEY;
		buf.resize(16);
	} // end constructor

	virtual IHash Clone() const
	{
		MurmurHash3_x64_128 HashInstance;

		HashInstance = MurmurHash3_x64_128();
		HashInstance.h1 = h1;
		HashInstance.h2 = h2;
		HashInstance.total_length = total_length;
		HashInstance.key = key;
		HashInstance.idx = idx;
		HashInstance.buf = buf;

		IHash hash = make_shared<MurmurHash3_x64_128>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		h1 = key;
		h2 = key;

		total_length = 0;
		idx = 0;
	} // end function Initialize

	virtual IHashResult TransformFinal()
	{
		Finish();

		HashLibUInt64Array tempBufUInt64 = HashLibUInt64Array({ h1, h2 });
		HashLibByteArray tempBufByte = HashLibByteArray(tempBufUInt64.size() * sizeof(uint64_t));

		Converters::be64_copy(&tempBufUInt64[0], 0, &tempBufByte[0], 0, (int32_t)tempBufByte.size());

		IHashResult result = make_shared<HashResult>(tempBufByte);

		Initialize();

		return result;
	} // end function TransformFinal

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		register int32_t len, nBlocks, i, offset, lIdx;
		register uint64_t k1, k2;
		const uint8_t *ptr_a_data = 0;

		len = a_length;
		i = a_index;
		lIdx = 0;
		total_length += len;
		ptr_a_data = &a_data[0];

        //consume last pending bytes
		if (idx && a_length)
		{
			//assert(a_index == 0); //nothing would work anyways if a_index is !=0

			while (idx < 16 && len)
			{
				buf[idx++] = *(ptr_a_data + a_index);
				a_index++;
				len--;
			}

			if (idx == 16)
				ProcessPendings();
		}
		else
			i = 0;

		nBlocks = len >> 4;

        // body
		while (i < nBlocks)
		{
			k1 = Converters::ReadBytesAsUInt64LE(ptr_a_data, a_index + lIdx);
			lIdx += 8;

			k2 = Converters::ReadBytesAsUInt64LE(ptr_a_data, a_index +lIdx);
			lIdx += 8;

			k1 = k1 * C1;
			k1 = Bits::RotateLeft64(k1, 31);
			k1 = k1 * C2;
			h1 = h1 ^ k1;

			h1 = Bits::RotateLeft64(h1, 27);
			h1 = h1 + h2;
			h1 = h1 * 5 + C3;

			k2 = k2 * C2;
			k2 = Bits::RotateLeft64(k2, 33);
			k2 = k2 * C1;
			h2 = h2 ^ k2;

			h2 = Bits::RotateLeft64(h2, 31);
			h2 = h2 + h1;
			h2 = h2 * 5 + C4;

			i++;
		} // end if

		offset = a_index + (i * 16);
		while (offset < (a_index + len))
		{
			ByteUpdate(a_data[offset]);
			offset++;
		} // end while
	} // end function TransformBytes

private:
	void ByteUpdate(const uint8_t a_b)
	{
		buf[idx] = a_b;
		idx++;
        ProcessPendings();
    }

    void ProcessPendings()
    {
		register uint64_t k1, k2;
		uint8_t *ptr_Fm_buf = 0;

		if (idx >= 16)
		{
			ptr_Fm_buf = &buf[0];
			k1 = Converters::ReadBytesAsUInt64LE(ptr_Fm_buf, 0);
			k2 = Converters::ReadBytesAsUInt64LE(ptr_Fm_buf, 8);

			k1 = k1 * C1;
			k1 = Bits::RotateLeft64(k1, 31);
			k1 = k1 * C2;
			h1 = h1 ^ k1;

			h1 = Bits::RotateLeft64(h1, 27);
			h1 = h1 + h2;
			h1 = h1 * 5 + C3;

			k2 = k2 * C2;
			k2 = Bits::RotateLeft64(k2, 33);
			k2 = k2 * C1;
			h2 = h2 ^ k2;

			h2 = Bits::RotateLeft64(h2, 31);
			h2 = h2 + h1;
			h2 = h2 * 5 + C4;

			idx = 0;
		} // end if

	} // end function ByteUpdate

	void Finish()
	{
		register uint64_t k1, k2;
		register int32_t Length;

		// tail
		k1 = 0;
		k2 = 0;

		Length = idx;
		if (Length != 0)
		{
			switch (Length)
			{
			case 15:
				k2 = k2 ^ (uint64_t(buf[14]) << 48);
				k2 = k2 ^ (uint64_t(buf[13]) << 40);
				k2 = k2 ^ (uint64_t(buf[12]) << 32);
				k2 = k2 ^ (uint64_t(buf[11]) << 24);
				k2 = k2 ^ (uint64_t(buf[10]) << 16);
				k2 = k2 ^ (uint64_t(buf[9]) << 8);
				k2 = k2 ^ (uint64_t(buf[8]) << 0);
				k2 = k2 * C2;
				k2 = Bits::RotateLeft64(k2, 33);
				k2 = k2 * C1;
				h2 = h2 ^ k2;
				break;

			case 14:
				k2 = k2 ^ (uint64_t(buf[13]) << 40);
				k2 = k2 ^ (uint64_t(buf[12]) << 32);
				k2 = k2 ^ (uint64_t(buf[11]) << 24);
				k2 = k2 ^ (uint64_t(buf[10]) << 16);
				k2 = k2 ^ (uint64_t(buf[9]) << 8);
				k2 = k2 ^ (uint64_t(buf[8]) << 0);
				k2 = k2 * C2;
				k2 = Bits::RotateLeft64(k2, 33);
				k2 = k2 * C1;
				h2 = h2 ^ k2;
				break;

			case 13:
				k2 = k2 ^ (uint64_t(buf[12]) << 32);
				k2 = k2 ^ (uint64_t(buf[11]) << 24);
				k2 = k2 ^ (uint64_t(buf[10]) << 16);
				k2 = k2 ^ (uint64_t(buf[9]) << 8);
				k2 = k2 ^ (uint64_t(buf[8]) << 0);
				k2 = k2 * C2;
				k2 = Bits::RotateLeft64(k2, 33);
				k2 = k2 * C1;
				h2 = h2 ^ k2;
				break;

			case 12:
				k2 = k2 ^ (uint64_t(buf[11]) << 24);
				k2 = k2 ^ (uint64_t(buf[10]) << 16);
				k2 = k2 ^ (uint64_t(buf[9]) << 8);
				k2 = k2 ^ (uint64_t(buf[8]) << 0);
				k2 = k2 * C2;
				k2 = Bits::RotateLeft64(k2, 33);
				k2 = k2 * C1;
				h2 = h2 ^ k2;
				break;

			case 11:
				k2 = k2 ^ (uint64_t(buf[10]) << 16);
				k2 = k2 ^ (uint64_t(buf[9]) << 8);
				k2 = k2 ^ (uint64_t(buf[8]) << 0);
				k2 = k2 * C2;
				k2 = Bits::RotateLeft64(k2, 33);
				k2 = k2 * C1;
				h2 = h2 ^ k2;
				break;

			case 10:
				k2 = k2 ^ (uint64_t(buf[9]) << 8);
				k2 = k2 ^ (uint64_t(buf[8]) << 0);
				k2 = k2 * C2;
				k2 = Bits::RotateLeft64(k2, 33);
				k2 = k2 * C1;
				h2 = h2 ^ k2;
				break;

			case 9:
				k2 = k2 ^ (uint64_t(buf[8]) << 0);
				k2 = k2 * C2;
				k2 = Bits::RotateLeft64(k2, 33);
				k2 = k2 * C1;
				h2 = h2 ^ k2;
				break;
			} // end switch
			
			if (Length > 8)
				Length = 8;

			switch (Length)
			{
			case 8:
				k1 = k1 ^ (uint64_t(buf[7]) << 56);
				k1 = k1 ^ (uint64_t(buf[6]) << 48);
				k1 = k1 ^ (uint64_t(buf[5]) << 40);
				k1 = k1 ^ (uint64_t(buf[4]) << 32);
				k1 = k1 ^ (uint64_t(buf[3]) << 24);
				k1 = k1 ^ (uint64_t(buf[2]) << 16);
				k1 = k1 ^ (uint64_t(buf[1]) << 8);
				k1 = k1 ^ (uint64_t(buf[0]) << 0);
				k1 = k1 * C1;
				k1 = Bits::RotateLeft64(k1, 31);
				k1 = k1 * C2;
				h1 = h1 ^ k1;
				break;

			case 7:
				k1 = k1 ^ (uint64_t(buf[6]) << 48);
				k1 = k1 ^ (uint64_t(buf[5]) << 40);
				k1 = k1 ^ (uint64_t(buf[4]) << 32);
				k1 = k1 ^ (uint64_t(buf[3]) << 24);
				k1 = k1 ^ (uint64_t(buf[2]) << 16);
				k1 = k1 ^ (uint64_t(buf[1]) << 8);
				k1 = k1 ^ (uint64_t(buf[0]) << 0);
				k1 = k1 * C1;
				k1 = Bits::RotateLeft64(k1, 31);
				k1 = k1 * C2;
				h1 = h1 ^ k1;
				break;

			case 6:
				k1 = k1 ^ (uint64_t(buf[5]) << 40);
				k1 = k1 ^ (uint64_t(buf[4]) << 32);
				k1 = k1 ^ (uint64_t(buf[3]) << 24);
				k1 = k1 ^ (uint64_t(buf[2]) << 16);
				k1 = k1 ^ (uint64_t(buf[1]) << 8);
				k1 = k1 ^ (uint64_t(buf[0]) << 0);
				k1 = k1 * C1;
				k1 = Bits::RotateLeft64(k1, 31);
				k1 = k1 * C2;
				h1 = h1 ^ k1;
				break;

			case 5:
				k1 = k1 ^ (uint64_t(buf[4]) << 32);
				k1 = k1 ^ (uint64_t(buf[3]) << 24);
				k1 = k1 ^ (uint64_t(buf[2]) << 16);
				k1 = k1 ^ (uint64_t(buf[1]) << 8);
				k1 = k1 ^ (uint64_t(buf[0]) << 0);
				k1 = k1 * C1;
				k1 = Bits::RotateLeft64(k1, 31);
				k1 = k1 * C2;
				h1 = h1 ^ k1;
				break;

			case 4:
				k1 = k1 ^ (uint64_t(buf[3]) << 24);
				k1 = k1 ^ (uint64_t(buf[2]) << 16);
				k1 = k1 ^ (uint64_t(buf[1]) << 8);
				k1 = k1 ^ (uint64_t(buf[0]) << 0);
				k1 = k1 * C1;
				k1 = Bits::RotateLeft64(k1, 31);
				k1 = k1 * C2;
				h1 = h1 ^ k1;
				break;

			case 3:
				k1 = k1 ^ (uint64_t(buf[2]) << 16);
				k1 = k1 ^ (uint64_t(buf[1]) << 8);
				k1 = k1 ^ (uint64_t(buf[0]) << 0);
				k1 = k1 * C1;
				k1 = Bits::RotateLeft64(k1, 31);
				k1 = k1 * C2;
				h1 = h1 ^ k1;
				break;

			case 2:
				k1 = k1 ^ (uint64_t(buf[1]) << 8);
				k1 = k1 ^ (uint64_t(buf[0]) << 0);
				k1 = k1 * C1;
				k1 = Bits::RotateLeft64(k1, 31);
				k1 = k1 * C2;
				h1 = h1 ^ k1;
				break;

			case 1:
				k1 = k1 ^ (uint64_t(buf[0]) << 0);
				k1 = k1 * C1;
				k1 = Bits::RotateLeft64(k1, 31);
				k1 = k1 * C2;
				h1 = h1 ^ k1;
				break;

			} // end switch

		} // end if

		// finalization

		h1 = h1 ^ total_length;
		h2 = h2 ^ total_length;

		h1 = h1 + h2;
		h2 = h2 + h1;

		h1 = h1 ^ (h1 >> 33);
		h1 = h1 * C5;
		h1 = h1 ^ (h1 >> 33);
		h1 = h1 * C6;
		h1 = h1 ^ (h1 >> 33);

		h2 = h2 ^ (h2 >> 33);
		h2 = h2 * C5;
		h2 = h2 ^ (h2 >> 33);
		h2 = h2 * C6;
		h2 = h2 ^ (h2 >> 33);

		h1 = h1 + h2;
		h2 = h2 + h1;
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
				throw ArgumentHashLibException(Utils::string_format(InvalidKeyLength, GetKeyLength().GetValue()));
			key = Converters::ReadBytesAsUInt32LE(&value[0], 0);
		} // end else
	} // end function SetKey

private:
	uint64_t h1, h2, total_length;
	uint32_t key;
	int32_t idx;
	HashLibByteArray buf;

	static const uint32_t CKEY = uint32_t(0x0);

	static const uint64_t C1 = uint64_t(0x87C37B91114253D5);
	static const uint64_t C5 = uint64_t(0xFF51AFD7ED558CCD);
	static const uint64_t C6 = uint64_t(0xC4CEB9FE1A85EC53);

	static const uint64_t C2 = uint64_t(0x4CF5AD432745937F);
	static const uint32_t C3 = uint32_t(0x52DCE729);
	static const uint32_t C4 = uint32_t(0x38495AB5);

	static const char *InvalidKeyLength;

}; // end class MurmurHash3_x64_128

const char *MurmurHash3_x64_128::InvalidKeyLength = "KeyLength Must Be Equal to %d";

#endif // !HLPMURMURHASH3_X64_128_H
