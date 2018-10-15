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

#ifndef HLPXXHASH32_H
#define HLPXXHASH32_H

#include "../Base/HlpHash.h"
#include "../Nullable/HlpNullable.h"
#include "../Interfaces/HlpIHashInfo.h"
#include "../Utils/HlpUtils.h"


class XXHash32 : public Hash, public IIBlockHash, public IIHash32, public IIHashWithKey, public IITransformBlock
{
public:
	XXHash32()
		: Hash(4, 16)
	{
		name = __func__;

		key = CKEY;
		memory = make_shared<HashLibByteArray>(16);
	} // end constructor

	virtual IHashWithKey CloneHashWithKey() const
	{
		IHashWithKey hash = make_shared<XXHash32>(Copy());
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual IHash Clone() const
	{
		IHash hash = make_shared<XXHash32>(Copy());
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		hash = 0;
		v1 = key + PRIME32_1 + PRIME32_2;
		v2 = key + PRIME32_2;
		v3 = key + 0;
		v4 = key - PRIME32_1;
		total_len = 0;
		memsize = 0;
	} // end function Initialize
	
	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		register uint32_t _v1, _v2, _v3, _v4;

		const uint8_t *ptrBuffer = &a_data[a_index];
		uint8_t * ptrTemp, *ptrMemory = &(*memory)[0];
		total_len = total_len + uint64_t(a_length);

		if ((memsize + uint32_t(a_length)) < uint32_t(16))
		{
			ptrTemp = (uint8_t *)&(*memory)[0] + memsize;

			memmove(ptrTemp, ptrBuffer, a_length);

			memsize = memsize + uint32_t(a_length);
			
			return;
		} // end if

		const uint8_t * ptrEnd = ptrBuffer + uint32_t(a_length);

		if (memsize > 0)
		{
			ptrTemp = (uint8_t *)&(*memory)[0] + memsize;

			memmove(ptrTemp, ptrBuffer, 16 - memsize);

			v1 = PRIME32_1 * Bits::RotateLeft32(v1 + PRIME32_2 * Converters::ReadBytesAsUInt32LE(ptrMemory, 0), 13);
			v2 = PRIME32_1 * Bits::RotateLeft32(v2 + PRIME32_2 * Converters::ReadBytesAsUInt32LE(ptrMemory, 4), 13);
			v3 = PRIME32_1 * Bits::RotateLeft32(v3 + PRIME32_2 * Converters::ReadBytesAsUInt32LE(ptrMemory, 8), 13);
			v4 = PRIME32_1 * Bits::RotateLeft32(v4 + PRIME32_2 * Converters::ReadBytesAsUInt32LE(ptrMemory, 12), 13);

			ptrBuffer = ptrBuffer + (16 - memsize);
			memsize = 0;
		} // end if

		if (ptrBuffer <= (ptrEnd - 16))
		{
			_v1 = v1;
			_v2 = v2;
			_v3 = v3;
			_v4 = v4;

			const uint8_t *ptrLimit = ptrEnd - 16;
			
			do 
			{
				_v1 = PRIME32_1 * Bits::RotateLeft32(_v1 + PRIME32_2 * Converters::ReadBytesAsUInt32LE(ptrBuffer, 0), 13);
				_v2 = PRIME32_1 * Bits::RotateLeft32(_v2 + PRIME32_2 * Converters::ReadBytesAsUInt32LE(ptrBuffer, 4), 13);
				_v3 = PRIME32_1 * Bits::RotateLeft32(_v3 + PRIME32_2 * Converters::ReadBytesAsUInt32LE(ptrBuffer, 8), 13);
				_v4 = PRIME32_1 * Bits::RotateLeft32(_v4 + PRIME32_2 * Converters::ReadBytesAsUInt32LE(ptrBuffer, 12), 13);
				ptrBuffer += 16;
			}
			while (ptrBuffer <= ptrLimit);

			v1 = _v1;
			v2 = _v2;
			v3 = _v3;
			v4 = _v4;
		} // end if

		if (ptrBuffer < ptrEnd)
		{
			ptrTemp = &(*memory)[0];
			memmove(ptrTemp, ptrBuffer, ptrEnd - ptrBuffer);
			memsize = ptrEnd - ptrBuffer;
		} // end if
	} // end function TransformBytes

	virtual IHashResult TransformFinal()
	{
		uint8_t *ptrEnd, *ptrBuffer;
		
		if (total_len >= uint64_t(16))
			hash = Bits::RotateLeft32(v1, 1) + Bits::RotateLeft32(v2, 7) + 
			Bits::RotateLeft32(v3, 12) + Bits::RotateLeft32(v4, 18);
		else
			hash = key + PRIME32_5;
		
		hash += total_len;

		ptrBuffer = &(*memory)[0];

		ptrEnd = ptrBuffer + memsize;
		while ((ptrBuffer + 4) <= ptrEnd)
		{
			hash = hash + Converters::ReadBytesAsUInt32LE(ptrBuffer, 0) * PRIME32_3;
			hash = Bits::RotateLeft32(hash, 17) * PRIME32_4;
			ptrBuffer += 4;
		} // end while

		while (ptrBuffer < ptrEnd)
		{
			hash = hash + (*ptrBuffer) * PRIME32_5;
			hash = Bits::RotateLeft32(hash, 11) * PRIME32_1;
			ptrBuffer++;
		} // end while

		hash = hash ^ (hash >> 15);
		hash = hash * PRIME32_2;
		hash = hash ^ (hash >> 13);
		hash = hash * PRIME32_3;
		hash = hash ^ (hash >> 16);

		IHashResult result = make_shared<HashResult>(hash);
			
		Initialize();
		
		return result;
	} // end function TransformFinal

private:
	XXHash32 Copy() const
	{
		XXHash32 HashInstance;

		HashInstance = XXHash32();
		HashInstance.key = key;
		HashInstance.hash = hash;
		HashInstance.total_len = total_len;
		HashInstance.memsize = memsize;
		HashInstance.v1 = v1;
		HashInstance.v2 = v2;
		HashInstance.v3 = v3;
		HashInstance.v4 = v4;
		HashInstance.memory = memory;

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
	uint32_t key, hash;

	static const uint32_t CKEY = uint32_t(0x0);

	static const uint32_t PRIME32_1 = uint32_t(2654435761);
	static const uint32_t PRIME32_2 = uint32_t(2246822519);
	static const uint32_t PRIME32_3 = uint32_t(3266489917);
	static const uint32_t PRIME32_4 = uint32_t(668265263);
	static const uint32_t PRIME32_5 = uint32_t(374761393);

	uint64_t total_len;
	uint32_t memsize, v1, v2, v3, v4;
	shared_ptr<HashLibByteArray> memory;

	static const char *InvalidKeyLength;

}; // end class XXHash32

const char *XXHash32::InvalidKeyLength = "KeyLength Must Be Equal to %d";

#endif // !HLPXXHASH32_H
