#ifndef HLPHASHRESULT_H
#define HLPHASHRESULT_H

#include "HlpConverters.h"
#include "../Interfaces/HlpIHashResult.h"

class HashResult : public IIHashResult
{
private:
	static const char *ImpossibleRepresentationInt32;
	static const char *ImpossibleRepresentationUInt8;
	static const char *ImpossibleRepresentationUInt16;
	static const char *ImpossibleRepresentationUInt32;
	static const char *ImpossibleRepresentationUInt64;

public:
	HashResult() 
		: hash(make_shared<HashLibByteArray>(0))
	{} // end constructor

	HashResult(const uint64_t a_hash)
		: hash(make_shared<HashLibByteArray>(8))
	{
		(*hash)[0] = uint8_t(a_hash >> 56);
		(*hash)[1] = uint8_t(a_hash >> 48);
		(*hash)[2] = uint8_t(a_hash >> 40);
		(*hash)[3] = uint8_t(a_hash >> 32);
		(*hash)[4] = uint8_t(a_hash >> 24);
		(*hash)[5] = uint8_t(a_hash >> 16);
		(*hash)[6] = uint8_t(a_hash >> 8);
		(*hash)[7] = uint8_t(a_hash);
	} // end constructor
	
	HashResult(const HashLibByteArray &a_hash)
	{
		hash = make_shared<HashLibByteArray>(a_hash.size());
		memmove(&(*hash)[0], &a_hash[0], a_hash.size() * sizeof(uint8_t));		
	} // end constructor
	
	HashResult(const uint32_t a_hash)
		: hash(make_shared<HashLibByteArray>(4))
	{
		(*hash)[0] = uint8_t(a_hash >> 24);
		(*hash)[1] = uint8_t(a_hash >> 16);
		(*hash)[2] = uint8_t(a_hash >> 8);
		(*hash)[3] = uint8_t(a_hash);
	} // end constructor

	HashResult(const uint8_t a_hash)
		: hash(make_shared<HashLibByteArray>(1))
	{
		(*hash)[0] = a_hash;
	} // end constructor
	
	HashResult(const uint16_t a_hash)
		: hash(make_shared<HashLibByteArray>(2))
	{
		(*hash)[0] = uint8_t(a_hash >> 8);
		(*hash)[1] = uint8_t(a_hash);
	} // end constructor
	
	HashResult(const int32_t a_hash)
		: hash(make_shared<HashLibByteArray>(4))
	{
		(*hash)[0] = uint8_t(Bits::Asr32(a_hash, 24));
		(*hash)[1] = uint8_t(Bits::Asr32(a_hash, 16));
		(*hash)[2] = uint8_t(Bits::Asr32(a_hash, 8));
		(*hash)[3] = uint8_t(a_hash);
	} // end constructor

	~HashResult()
	{} // end destructor
	
	const HashResult& operator=(const HashResult &right)
	{
		if (&right != this)
		{
			hash = ::move(right.hash);
		} // end if

		return *this;
	} // end funcion operator=
	
	virtual bool CompareTo(const IHashResult &a_hashResult) const
	{
		return HashResult::SlowEquals(a_hashResult->GetBytes(), *hash);
	} // end function CompareTo

	bool operator==(const HashResult &a_hashResult) const
	{
		return HashResult::SlowEquals(a_hashResult.GetBytes(), *hash);
	} // end function operator==

	virtual HashLibByteArray GetBytes() const
	{
		return *hash;
	} // end function GetBytesAsVector

	virtual inline int32_t GetHashCode() const
	{
		shared_ptr<uint8_t> TempHolder = shared_ptr<uint8_t>(new uint8_t[hash->size()], default_delete<uint8_t[]>());
		
		Converters::toUpper(TempHolder.get(), hash->size());
		
		//transform(TempHolder->begin(), TempHolder->end(), TempHolder->begin(), ::toupper);

		int32_t LResult = 0;
		int32_t I = 0;
		int32_t Top = hash->size();

		while (I < Top)
		{
			LResult = Bits::RotateLeft32(LResult, 5);
			LResult = LResult ^ uint32_t(TempHolder.get()[I]);
			I += 1;
		} // end while
		
		return LResult;
	} // end function GetHashCode

	virtual inline int32_t GetInt32() const
	{
		if (hash->size() != 4)
		{
			throw InvalidOperationHashLibException(HashResult::ImpossibleRepresentationInt32);
		} // end if
		
		return (int32_t((*hash)[0]) << 24) | (int32_t((*hash)[1]) << 16) | 
			(int32_t((*hash)[2]) << 8) | int32_t((*hash)[3]);
	} // end function GetInt32
		
	virtual inline uint8_t GetUInt8() const
	{
		if (hash->size() != 1)
		{
			throw InvalidOperationHashLibException(HashResult::ImpossibleRepresentationUInt8);
		} // end if
		
		return (*hash)[0];
	} // end function GetUInt8
			
	virtual inline  uint16_t GetUInt16() const
	{
		if (hash->size() != 2)
		{
			throw InvalidOperationHashLibException(HashResult::ImpossibleRepresentationUInt16);
		} // end if
		 
		return (uint16_t((*hash)[0]) << 8) | uint16_t((*hash)[1]);
	} // end function GetUInt16
				
	virtual inline uint32_t GetUInt32() const
	{
		if (hash->size() != 4)
		{
			throw InvalidOperationHashLibException(HashResult::ImpossibleRepresentationUInt32);
		} // end if
		
		return (uint32_t((*hash)[0]) << 24) | (uint32_t((*hash)[1]) << 16) |
			(uint32_t((*hash)[2]) << 8) | uint32_t((*hash)[3]);
	} // end function GetUInt32
					
	virtual inline uint64_t GetUInt64() const
	{
		if (hash->size() != 8)
		{
			throw InvalidOperationHashLibException(HashResult::ImpossibleRepresentationUInt64);
		} // end if
		
		return (uint64_t((*hash)[0]) << 56) | (uint64_t((*hash)[1]) << 48) | (uint64_t((*hash)[2]) << 40) | (uint64_t((*hash)[3]) << 32) |
			(uint64_t((*hash)[4]) << 24) | (uint64_t((*hash)[5]) << 16) | (uint64_t((*hash)[6]) << 8) | uint64_t((*hash)[7]);
	} // end function GetUInt64
						
	static inline bool SlowEquals(const HashLibByteArray &a_ar1, const HashLibByteArray &a_ar2)
	{
		register uint32_t diff = a_ar1.size() ^ a_ar2.size();
		register uint32_t I = 0;

		while (I <= (a_ar1.size() - 1) && I <= (a_ar2.size() - 1))
		{
			diff = (diff | (a_ar1[I] ^ a_ar2[I]));
			I += 1;
		} // end while
		
		return diff == 0;
	} // end function SlowEquals
							
	virtual inline string ToString(const bool a_group = false) const
	{
		return Converters::ConvertBytesToHexString(&(*hash)[0], hash->size(), a_group);
	} // end function ToString
			

private:
	shared_ptr<HashLibByteArray> hash;

}; // end class HashResult

const char *HashResult::ImpossibleRepresentationInt32 = "Current Data Structure cannot be Represented as an 'Int32' Type.";
const char *HashResult::ImpossibleRepresentationUInt8 = "Current Data Structure cannot be Represented as an 'UInt8' Type.";
const char *HashResult::ImpossibleRepresentationUInt16 = "Current Data Structure cannot be Represented as an 'UInt16' Type.";
const char *HashResult::ImpossibleRepresentationUInt32 = "Current Data Structure cannot be Represented as an 'UInt32' Type.";
const char *HashResult::ImpossibleRepresentationUInt64 = "Current Data Structure cannot be Represented as an 'UInt64' Type.";


#endif // !HLPHASHRESULT_H