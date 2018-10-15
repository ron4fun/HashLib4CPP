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

#ifndef HLPMURMURHASH3_X86_128_H
#define HLPMURMURHASH3_X86_128_H

#include "../Base/HlpHash.h"
#include "../Nullable/HlpNullable.h"
#include "../Interfaces/HlpIHashInfo.h"
#include "../Utils/HlpUtils.h"


class MurmurHash3_x86_128 : public Hash, public IIHash128, public IIHashWithKey, public IITransformBlock
{
public:
	MurmurHash3_x86_128()
		: Hash(16, 16)
	{
		name = __func__;

		key = CKEY;
		buf.resize(16); 
	} // end constructor

	virtual IHashWithKey CloneHashWithKey() const
	{
		IHashWithKey hash = make_shared<MurmurHash3_x86_128>(Copy());
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual IHash Clone() const
	{
		IHash hash = make_shared<MurmurHash3_x86_128>(Copy());
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		h1 = key;
		h2 = key;
		h3 = key;
		h4 = key;

		total_length = 0;
		idx = 0;
	} // end function Initialize

	virtual IHashResult TransformFinal()
	{
		Finish();

		HashLibUInt32Array tempBufUInt32 = HashLibUInt32Array({ h1, h2, h3, h4 });
		HashLibByteArray tempBufByte = HashLibByteArray(tempBufUInt32.size() * sizeof(uint32_t));
		
		Converters::be32_copy(&tempBufUInt32[0], 0, &tempBufByte[0], 0, (int32_t)tempBufByte.size());

		IHashResult result = make_shared<HashResult>(tempBufByte);

		Initialize();

		return result;
	} // end function TransformFinal

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		register int32_t len, nBlocks, i, offset, lIdx;
		register uint32_t k1, k2, k3, k4;
		const uint8_t *ptr_a_data = 0;
		
		len = a_length;
		i = a_index;
		lIdx = 0;
		total_length += len;
		ptr_a_data = &a_data[0];

        //consume last pending bytes
        if (idx && len)
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
			k1 = Converters::ReadBytesAsUInt32LE(ptr_a_data, a_index + lIdx);
			lIdx += 4;
			k2 = Converters::ReadBytesAsUInt32LE(ptr_a_data, a_index + lIdx);
			lIdx += 4;
			k3 = Converters::ReadBytesAsUInt32LE(ptr_a_data, a_index + lIdx);
			lIdx += 4;
			k4 = Converters::ReadBytesAsUInt32LE(ptr_a_data, a_index + lIdx);
			lIdx += 4;

			k1 = k1 * C1;
			k1 = Bits::RotateLeft32(k1, 15);
			k1 = k1 * C2;
			h1 = h1 ^ k1;

			h1 = Bits::RotateLeft32(h1, 19);

			h1 = h1 + h2;
			h1 = h1 * 5 + C7;

			k2 = k2 * C2;
			k2 = Bits::RotateLeft32(k2, 16);
			k2 = k2 * C3;
			h2 = h2 ^ k2;

			h2 = Bits::RotateLeft32(h2, 17);

			h2 = h2 + h3;
			h2 = h2 * 5 + C8;

			k3 = k3 * C3;
			k3 = Bits::RotateLeft32(k3, 17);
			k3 = k3 * C4;
			h3 = h3 ^ k3;

			h3 = Bits::RotateLeft32(h3, 15);

			h3 = h3 + h4;
			h3 = h3 * 5 + C9;

			k4 = k4 * C4;
			k4 = Bits::RotateLeft32(k4, 18);
			k4 = k4 * C1;
			h4 = h4 ^ k4;

			h4 = Bits::RotateLeft32(h4, 13);

			h4 = h4 + h1;
			h4 = h4 * 5 + C10;

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
	MurmurHash3_x86_128 Copy() const
	{
		MurmurHash3_x86_128 HashInstance;

		HashInstance = MurmurHash3_x86_128();
		HashInstance.key = key;
		HashInstance.h1 = h1;
		HashInstance.h2 = h2;
		HashInstance.h3 = h3;
		HashInstance.h4 = h4;
		HashInstance.total_length = total_length;
		HashInstance.idx = idx;
		HashInstance.buf = buf;

		return HashInstance;
	}

	void ByteUpdate(const uint8_t a_b)
	{
		buf[idx] = a_b;
		idx++;
        ProcessPendings();
    }

    void ProcessPendings()
    {
		register uint32_t k1, k2, k3, k4;
		uint8_t *ptr_Fm_buf = 0;
		
		if (idx >= 16)
		{
			ptr_Fm_buf = &buf[0];
			k1 = Converters::ReadBytesAsUInt32LE(ptr_Fm_buf, 0);
			k2 = Converters::ReadBytesAsUInt32LE(ptr_Fm_buf, 4);
			k3 = Converters::ReadBytesAsUInt32LE(ptr_Fm_buf, 8);
			k4 = Converters::ReadBytesAsUInt32LE(ptr_Fm_buf, 12);

			k1 = k1 * C1;
			k1 = Bits::RotateLeft32(k1, 15);
			k1 = k1 * C2;
			h1 = h1 ^ k1;

			h1 = Bits::RotateLeft32(h1, 19);

			h1 = h1 + h2;
			h1 = h1 * 5 + C7;

			k2 = k2 * C2;
			k2 = Bits::RotateLeft32(k2, 16);
			k2 = k2 * C3;
			h2 = h2 ^ k2;

			h2 = Bits::RotateLeft32(h2, 17);

			h2 = h2 + h3;
			h2 = h2 * 5 + C8;

			k3 = k3 * C3;
			k3 = Bits::RotateLeft32(k3, 17);
			k3 = k3 * C4;
			h3 = h3 ^ k3;

			h3 = Bits::RotateLeft32(h3, 15);

			h3 = h3 + h4;
			h3 = h3 * 5 + C9;

			k4 = k4 * C4;
			k4 = Bits::RotateLeft32(k4, 18);
			k4 = k4 * C1;
			h4 = h4 ^ k4;

			h4 = Bits::RotateLeft32(h4, 13);

			h4 = h4 + h1;
			h4 = h4 * 5 + C10;

			idx = 0;
		} // end if
		
	} // end function ByteUpdate

	void Finish()
	{
		register uint32_t k1, k2, k3, k4;
		register int32_t Length;
		
		// tail
		k1  = 0;
		k2 = 0;
		k3 = 0;
		k4 = 0;

		Length = idx;
		if (Length != 0)
		{
			switch (Length)
			{
			case 15:
				k4 = k4 ^ (buf[14] << 16);
				k4 = k4 ^ (buf[13] << 8);
				k4 = k4 ^ (buf[12] << 0);

				k4 = k4 * C4;
				k4 = Bits::RotateLeft32(k4, 18);
				k4 = k4 * C1;
				h4 = h4 ^ k4;
				break;

			case 14:
				k4 = k4 ^ (buf[13] << 8);
				k4 = k4 ^ (buf[12] << 0);
				k4 = k4 * C4;
				k4 = Bits::RotateLeft32(k4, 18);
				k4 = k4 * C1;
				h4 = h4 ^ k4;
				break;

			case 13:
				k4 = k4 ^ (buf[12] << 0);
				k4 = k4 * C4;
				k4 = Bits::RotateLeft32(k4, 18);
				k4 = k4 * C1;
				h4 = h4 ^ k4;
				break;
			} // end switch

			if (Length > 12)
				Length = 12;

			switch (Length)
			{
			case 12:
				k3 = k3 ^ (buf[11] << 24);
				k3 = k3 ^ (buf[10] << 16);
				k3 = k3 ^ (buf[9] << 8);
				k3 = k3 ^ (buf[8] << 0);

				k3 = k3 * C3;
				k3 = Bits::RotateLeft32(k3, 17);
				k3 = k3 * C4;
				h3 = h3 ^ k3;
				break;

			case 11:
				k3 = k3 ^ (buf[10] << 16);
				k3 = k3 ^ (buf[9] << 8);
				k3 = k3 ^ (buf[8] << 0);

				k3 = k3 * C3;
				k3 = Bits::RotateLeft32(k3, 17);
				k3 = k3 * C4;
				h3 = h3 ^ k3;
				break;

			case 10:
				k3 = k3 ^ (buf[9] << 8);
				k3 = k3 ^ (buf[8] << 0);

				k3 = k3 * C3;
				k3 = Bits::RotateLeft32(k3, 17);
				k3 = k3 * C4;
				h3 = h3 ^ k3;
				break;

			case 9:
				k3 = k3 ^ (buf[8] << 0);

				k3 = k3 * C3;
				k3 = Bits::RotateLeft32(k3, 17);
				k3 = k3 * C4;
				h3 = h3 ^ k3;
			} // end switch

			if (Length > 8)
				Length = 8;

			switch (Length)
			{
			case 8:
				k2 = k2 ^ (buf[7] << 24);
				k2 = k2 ^ (buf[6] << 16);
				k2 = k2 ^ (buf[5] << 8);
				k2 = k2 ^ (buf[4] << 0);

				k2 = k2 * C2;
				k2 = Bits::RotateLeft32(k2, 16);
				k2 = k2 * C3;
				h2 = h2 ^ k2;
				break;

			case 7:
				k2 = k2 ^ (buf[6] << 16);
				k2 = k2 ^ (buf[5] << 8);
				k2 = k2 ^ (buf[4] << 0);

				k2 = k2 * C2;
				k2 = Bits::RotateLeft32(k2, 16);
				k2 = k2 * C3;
				h2 = h2 ^ k2;
				break;

			case 6:
				k2 = k2 ^ (buf[5] << 8);
				k2 = k2 ^ (buf[4] << 0);

				k2 = k2 * C2;
				k2 = Bits::RotateLeft32(k2, 16);
				k2 = k2 * C3;
				h2 = h2 ^ k2;
				break;

			case 5:
				k2 = k2 ^ (buf[4] << 0);

				k2 = k2 * C2;
				k2 = Bits::RotateLeft32(k2, 16);
				k2 = k2 * C3;
				h2 = h2 ^ k2;
				break;
			} // end switch

			if (Length > 4)
				Length = 4;

			switch (Length)
			{
			case 4:
				k1 = k1 ^ (buf[3] << 24);
				k1 = k1 ^ (buf[2] << 16);
				k1 = k1 ^ (buf[1] << 8);
				k1 = k1 ^ (buf[0] << 0);

				k1 = k1 * C1;
				k1 = Bits::RotateLeft32(k1, 15);
				k1 = k1 * C2;
				h1 = h1 ^ k1;
				break;

			case 3:
				k1 = k1 ^ (buf[2] << 16);
				k1 = k1 ^ (buf[1] << 8);
				k1 = k1 ^ (buf[0] << 0);

				k1 = k1 * C1;
				k1 = Bits::RotateLeft32(k1, 15);
				k1 = k1 * C2;
				h1 = h1 ^ k1;
				break;

			case 2:
				k1 = k1 ^ (buf[1] << 8);
				k1 = k1 ^ (buf[0] << 0);

				k1 = k1 * C1;
				k1 = Bits::RotateLeft32(k1, 15);
				k1 = k1 * C2;
				h1 = h1 ^ k1;
				break;

			case 1:
				k1 = k1 ^ (buf[0] << 0);

				k1 = k1 * C1;
				k1 = Bits::RotateLeft32(k1, 15);
				k1 = k1 * C2;
				h1 = h1 ^ k1;
			} // end switch
		} // end if

		// finalization

		h1 = h1 ^ total_length;
		h2 = h2 ^ total_length;
		h3 = h3 ^ total_length;
		h4 = h4 ^ total_length;

		h1 = h1 + h2;
		h1 = h1 + h3;
		h1 = h1 + h4;
		h2 = h2 + h1;
		h3 = h3 + h1;
		h4 = h4 + h1;

		h1 = h1 ^ (h1 >> 16);
		h1 = h1 * C5;
		h1 = h1 ^ (h1 >> 13);
		h1 = h1 * C6;
		h1 = h1 ^ (h1 >> 16);

		h2 = h2 ^ (h2 >> 16);
		h2 = h2 * C5;
		h2 = h2 ^ (h2 >> 13);
		h2 = h2 * C6;
		h2 = h2 ^ (h2 >> 16);

		h3 = h3 ^ (h3 >> 16);
		h3 = h3 * C5;
		h3 = h3 ^ (h3 >> 13);
		h3 = h3 * C6;
		h3 = h3 ^ (h3 >> 16);

		h4 = h4 ^ (h4 >> 16);
		h4 = h4 * C5;
		h4 = h4 ^ (h4 >> 13);
		h4 = h4 * C6;
		h4 = h4 ^ (h4 >> 16);

		h1 = h1 + h2;
		h1 = h1 + h3;
		h1 = h1 + h4;
		h2 = h2 + h1;
		h3 = h3 + h1;
		h4 = h4 + h1;
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
	uint32_t key, h1, h2, h3, h4, total_length;
	int32_t idx;
	HashLibByteArray buf;

	static const uint32_t CKEY = uint32_t(0x0);

	static const uint32_t C1 = uint32_t(0x239B961B);
	static const uint32_t C2 = uint32_t(0xAB0E9789);
	static const uint32_t C3 = uint32_t(0x38B34AE5);
	static const uint32_t C4 = uint32_t(0xA1E38B93);
	static const uint32_t C5 = uint32_t(0x85EBCA6B);
	static const uint32_t C6 = uint32_t(0xC2B2AE35);

	static const uint32_t C7 = uint32_t(0x561CCD1B);
	static const uint32_t C8 = uint32_t(0x0BCAA747);
	static const uint32_t C9 = uint32_t(0x96CD1C35);
	static const uint32_t C10 = uint32_t(0x32AC3B17);

	static const char *InvalidKeyLength;

}; // end class MurmurHash3_x86_128

const char *MurmurHash3_x86_128::InvalidKeyLength = "KeyLength Must Be Equal to %d";

#endif // !HLPMURMURHASH3_X86_128_H
