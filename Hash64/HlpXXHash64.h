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

#ifndef HLPXXHASH64_H
#define HLPXXHASH64_H

#include "../Base/HlpHash.h"
#include "../Nullable/HlpNullable.h"
#include "../Interfaces/HlpIHashInfo.h"



class XXHash64 : public Hash, public IIBlockHash, public IIHash64, public IIHashWithKey, public IITransformBlock
{
public:
	XXHash64()
		: Hash(8, 32)
	{
		name = __func__;

		key = CKEY;
		memory.resize(32);
	} // end constructor

	virtual IHashWithKey CloneHashWithKey() const
	{
		IHashWithKey hash = make_shared<XXHash64>(Copy());
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual IHash Clone() const
	{
		IHash hash = make_shared<XXHash64>(Copy());
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		hash = 0;
		v1 = key + PRIME64_1 + PRIME64_2;
		v2 = key + PRIME64_2;
		v3 = key + 0;
		v4 = key - PRIME64_1;
		total_len = 0;
		memsize = 0;
	} // end function Initialize

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		register uint64_t _v1, _v2, _v3, _v4;

		const uint8_t *ptrBuffer = &a_data[a_index];
		uint8_t * ptrTemp, *ptrMemory = &memory[0];
		total_len = total_len + uint64_t(a_length);

		if ((memsize + uint32_t(a_length)) < uint32_t(32))
		{
			ptrTemp = (uint8_t *)&memory[0] + memsize;

			memmove(ptrTemp, ptrBuffer, a_length);

			memsize = memsize + uint32_t(a_length);

			return;
		} // end if

		const uint8_t * ptrEnd = ptrBuffer + uint32_t(a_length);

		if (memsize > 0)
		{
			ptrTemp = (uint8_t *)&memory[0] + memsize;

			memmove(ptrTemp, ptrBuffer, 32 - memsize);

			v1 = PRIME64_1 * Bits::RotateLeft64(v1 + PRIME64_2 * Converters::ReadBytesAsUInt64LE(ptrMemory, 0), 31);
			v2 = PRIME64_1 * Bits::RotateLeft64(v2 + PRIME64_2 * Converters::ReadBytesAsUInt64LE(ptrMemory, 8), 31);
			v3 = PRIME64_1 * Bits::RotateLeft64(v3 + PRIME64_2 * Converters::ReadBytesAsUInt64LE(ptrMemory, 16), 31);
			v4 = PRIME64_1 * Bits::RotateLeft64(v4 + PRIME64_2 * Converters::ReadBytesAsUInt64LE(ptrMemory, 24), 31);

			ptrBuffer = ptrBuffer + (32 - memsize);
			memsize = 0;
		} // end if

		if (ptrBuffer <= (ptrEnd - 32))
		{
			_v1 = v1;
			_v2 = v2;
			_v3 = v3;
			_v4 = v4;

			const uint8_t *ptrLimit = ptrEnd - 32;

			do
			{
				_v1 = PRIME64_1 * Bits::RotateLeft64(_v1 + PRIME64_2 * Converters::ReadBytesAsUInt64LE(ptrBuffer, 0), 31);
				_v2 = PRIME64_1 * Bits::RotateLeft64(_v2 + PRIME64_2 * Converters::ReadBytesAsUInt64LE(ptrBuffer, 8), 31);
				_v3 = PRIME64_1 * Bits::RotateLeft64(_v3 + PRIME64_2 * Converters::ReadBytesAsUInt64LE(ptrBuffer, 16), 31);
				_v4 = PRIME64_1 * Bits::RotateLeft64(_v4 + PRIME64_2 * Converters::ReadBytesAsUInt64LE(ptrBuffer, 24), 31);
				ptrBuffer += 32;
			} while (ptrBuffer <= ptrLimit);

			v1 = _v1;
			v2 = _v2;
			v3 = _v3;
			v4 = _v4;
		} // end if

		if (ptrBuffer < ptrEnd)
		{
			ptrTemp = &memory[0];
			memmove(ptrTemp, ptrBuffer, ptrEnd - ptrBuffer);
			memsize = ptrEnd - ptrBuffer;
		} // end if
	} // end function TransformBytes

	virtual IHashResult TransformFinal()
	{
		register uint64_t _v1, _v2, _v3, _v4;
		uint8_t *ptrEnd, *ptrBuffer;

		if (total_len >= uint64_t(32))
		{
			_v1 = v1;
			_v2 = v2;
			_v3 = v3;
			_v4 = v4;

			hash = Bits::RotateLeft64(_v1, 1) + Bits::RotateLeft64(_v2, 7) + Bits::RotateLeft64(_v3, 12) + Bits::RotateLeft64(_v4, 18);

			_v1 = Bits::RotateLeft64(_v1 * PRIME64_2, 31) * PRIME64_1;
			hash = (hash ^ _v1) * PRIME64_1 + PRIME64_4;

			_v2 = Bits::RotateLeft64(_v2 * PRIME64_2, 31) * PRIME64_1;
			hash = (hash ^ _v2) * PRIME64_1 + PRIME64_4;

			_v3 = Bits::RotateLeft64(_v3 * PRIME64_2, 31) * PRIME64_1;
			hash = (hash ^ _v3) * PRIME64_1 + PRIME64_4;

			_v4 = Bits::RotateLeft64(_v4 * PRIME64_2, 31) * PRIME64_1;
			hash = (hash ^ _v4) * PRIME64_1 + PRIME64_4;
		} // end if				 
		else
			hash = key + PRIME64_5;

		hash += total_len;

		ptrBuffer = &memory[0];

		ptrEnd = ptrBuffer + memsize;
		while ((ptrBuffer + 8) <= ptrEnd)
		{
			hash = hash ^ (PRIME64_1 * Bits::RotateLeft64(PRIME64_2 * Converters::ReadBytesAsUInt64LE(ptrBuffer, 0), 31));
			hash = Bits::RotateLeft64(hash, 27) * PRIME64_1 + PRIME64_4;
			ptrBuffer += 8;
		} // end while

		if ((ptrBuffer + 4) <= ptrEnd)
		{
			hash = hash ^ Converters::ReadBytesAsUInt32LE(ptrBuffer, 0) * PRIME64_1;
			hash = Bits::RotateLeft64(hash, 23) * PRIME64_2 + PRIME64_3;
			ptrBuffer += 4;
		} // end if

		while (ptrBuffer < ptrEnd)
		{
			hash = hash ^ (*ptrBuffer) * PRIME64_5;
			hash = Bits::RotateLeft64(hash, 11) * PRIME64_1;
			ptrBuffer++;
		} // end while

		hash = hash ^ (hash >> 33);
		hash = hash * PRIME64_2;
		hash = hash ^ (hash >> 29);
		hash = hash * PRIME64_3;
		hash = hash ^ (hash >> 32);

		IHashResult result = make_shared<HashResult>(hash);

		Initialize();

		return result;
	} // end function TransformFinal

private:
	XXHash64 Copy() const
	{
		XXHash64 HashInstance;

		HashInstance = XXHash64();
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
		return 8;
	} // end function GetKeyLength

	virtual inline HashLibByteArray GetKey() const
	{
		return Converters::ReadUInt64AsBytesLE(key);
	} // end function GetKey

	virtual inline void SetKey(const HashLibByteArray &value)
	{
		if (value.empty())
			key = CKEY;
		else
		{
			if (value.size() != GetKeyLength().GetValue())
				throw ArgumentHashLibException(Utils::string_format(InvalidKeyLength, GetKeyLength().GetValue()));
			key = Converters::ReadBytesAsUInt64LE(&value[0], 0);
		} // end else
	} // end function SetKey

private:
	uint64_t key, hash;

	static const uint64_t CKEY = uint64_t(0x0);

	static const uint64_t PRIME64_1 = uint64_t(11400714785074694791);
	static const uint64_t PRIME64_2 = uint64_t(14029467366897019727);
	static const uint64_t PRIME64_3 = uint64_t(1609587929392839161);
	static const uint64_t PRIME64_4 = uint64_t(9650029242287828579);
	static const uint64_t PRIME64_5 = uint64_t(2870177450012600261);

	uint64_t total_len, v1, v2, v3, v4;
	uint32_t memsize;
	HashLibByteArray memory;

	static const char *InvalidKeyLength;

}; // end class XXHash64

const char *XXHash64::InvalidKeyLength = "KeyLength Must Be Equal to %d";

#endif // !HLPXXHASH64_H
