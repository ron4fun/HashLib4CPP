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

#ifndef HLPMURMURHASH3_X86_32_H
#define HLPMURMURHASH3_X86_32_H

#include "../Base/HlpHash.h"
#include "../Nullable/HlpNullable.h"
#include "../Interfaces/HlpIHashInfo.h"
#include "../Utils/HlpUtils.h"

class MurmurHash3_x86_32 : public Hash, public IIHash32, public IIHashWithKey, public IITransformBlock
{
public:
	MurmurHash3_x86_32()
		: Hash(4, 4)
	{
		name = __func__;

		key = CKEY;
		buf.resize(4);
	} // end constructor

	virtual IHashWithKey CloneHashWithKey() const
	{
		IHashWithKey hash = make_shared<MurmurHash3_x86_32>(Copy());
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual IHash Clone() const
	{
		IHash hash = make_shared<MurmurHash3_x86_32>(Copy());
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

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
		total_length += len;
        
        //consume last pending bytes
        if (idx != 0 && a_length != 0)
        {
            /*                       buf    data
                 idx = 1, len = 3 -> [0, 1[ + [0, 3[ => Block = [], buf []
                 idx = 1, len = 4 -> [0, 1[ + [0, 3[ => Block = [], buf = data[3, 4[
                 idx = 1, len = 5 -> [0, 1[ + [0, 3[ => Block = [], buf = data[3, 5[
                 ...
                 idx = 1, len = 7 -> [0, 1[ + [0, 3[ => Block = [3,7[, buf []
                 idx = 2, len = 3 -> [0, 2[ + [0, 2[ => Block = [], buf [2, 3[
                 idx = 2, len = 4 -> [0, 2[ + [0, 2[ => Block = [], buf [2, 4[
                 ...
                 idx = 2, len = 6 -> [0, 2[ + [0, 2[ => Block = [2,6[, buf []
            */
            //assert(a_index == 0); //nothing would work anyways if a_index is !=0
			
            while (idx < 4 && len != 0)
            {
                buf[idx++] = *(ptr_a_data + a_index);
                a_index++;
                len--;
            }
            
            if (idx == 4)
            {
                uint8_t *ptr_Fm_buf = &buf[0];
			    k = Converters::ReadBytesAsUInt32LE(ptr_Fm_buf, 0);
			    TransformUInt32Fast(k);
                idx = 0;
            }
        } 
		else
		{
			i = 0;
		}

        nBlocks = (len) >> 2;
        offset = 0;

		// body
		while (i < nBlocks)
		{
			k = Converters::ReadBytesAsUInt32LE(ptr_a_data, a_index + (i * 4));
			TransformUInt32Fast(k);
			i++;
		} // end while

        //save pending end bytes
        offset = a_index + (i * 4);
		while (offset < (len + a_index))
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

	MurmurHash3_x86_32 Copy() const
	{
		MurmurHash3_x86_32 HashInstance;

		HashInstance = MurmurHash3_x86_32();
		HashInstance.key = key;
		HashInstance.h = h;
		HashInstance.total_length = total_length;
		HashInstance.idx = idx;
		HashInstance.buf = buf;

		return HashInstance;
	}

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
		
		buf[idx] = a_b;
		idx++;
		if (idx >= 4)
		{
			ptr_Fm_buf = &buf[0];
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
				 k = k ^ (buf[2] << 16);
				 k = k ^ (buf[1] << 8);
				 k = k ^ buf[0];
				 k = k * C1;
				 k = Bits::RotateLeft32(k, 15);
				 k = k * C2;
				 h = h ^ k;
				 break;

			 case 2:
				 k = k ^ (buf[1] << 8);
				 k = k ^ buf[0];
				 k = k * C1;
				 k = Bits::RotateLeft32(k, 15);
				 k = k * C2;
				 h = h ^ k;
				 break;

			 case 1:
				 k = k ^ buf[0];
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
				throw ArgumentHashLibException(Utils::string_format(InvalidKeyLength, GetKeyLength().GetValue()));
			key = Converters::ReadBytesAsUInt32LE(&value[0], 0);
		} // end else
	} // end function SetKey

private:
	uint32_t key, h, total_length;
	int32_t idx;
	HashLibByteArray buf;

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
