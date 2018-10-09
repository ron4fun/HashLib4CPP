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

#ifndef HLPPBKDF2_PBKDF2_HMACNotBuildInAdapter_H
#define HLPPBKDF2_PBKDF2_HMACNotBuildInAdapter_H

#include "../Base/HlpKDF.h"
#include "../Base/HlpHMACNotBuildInAdapter.h"
#include "../Utils/HlpBitConverter.h"
#include "../Interfaces/HlpIHashInfo.h"


class PBKDF2_HMACNotBuildInAdapter : public KDF, public IIPBKDF2_HMACNotBuildIn
{
public:
	PBKDF2_HMACNotBuildInAdapter(IHash a_underlyingHash, const HashLibByteArray &a_password,
		const HashLibByteArray &a_salt, const uint32_t a_iterations)
	{
		hash = ::move(a_underlyingHash);

		buffer = make_shared<HashLibByteArray>();
		Password = make_shared<HashLibByteArray>(a_password);
		Salt = make_shared<HashLibByteArray>(a_salt);
		IterationCount = a_iterations;

		Initialize();
	} // end constructor

	~PBKDF2_HMACNotBuildInAdapter()
	{} // end destructor

	virtual HashLibByteArray GetBytes(const int32_t bc)
	{
		register int32_t LOffset, LSize, LRemainder;

		if (bc <= 0)
			throw ArgumentOutOfRangeHashLibException(InvalidArgument);

		HashLibByteArray LKey = HashLibByteArray(bc);

		LOffset = 0;
		LSize = endIndex - startIndex;
		if (LSize > 0)
		{
			if (bc >= LSize)
			{
				memmove(&LKey[0], &(*buffer)[startIndex], LSize);
				startIndex = 0;
				endIndex = 0;
				LOffset = LOffset + LSize;
			} // end if
			else
			{
				memmove(&LKey[0], &(*buffer)[startIndex], bc);
				startIndex = startIndex + bc;
				return LKey;
			} // end else
		} // end if

		if ((startIndex != 0) && (endIndex != 0))
			throw ArgumentHashLibException(InvalidIndex);

		while (LOffset < bc)
		{
			HashLibByteArray LT_block = Func();
			LRemainder = bc - LOffset;
			if (LRemainder > BlockSize)
			{
				memmove(&LKey[LOffset], &LT_block[0], BlockSize);
				LOffset = LOffset + BlockSize;
			} // end if
			else
			{
				memmove(&LKey[LOffset], &LT_block[0], LRemainder);
				memmove(&(*buffer)[startIndex], &LT_block[0], BlockSize - LRemainder);
				endIndex = endIndex + (BlockSize - LRemainder);
				return LKey;
			} // end else
		} // end while

		return LKey;
	} // end function GetBytes

private:
	// initializes the state of the operation.
	void Initialize()
	{
		if (buffer)
			memset(&(*buffer)[0], 0, buffer->size() * sizeof(uint8_t));

		HMAC = make_shared<HMACNotBuildInAdapter>(hash);

		HMAC->SetKey(*Password);
		BlockSize = HMAC->GetHashSize();
		buffer->resize(BlockSize);
		Block = 1;
		startIndex = 0;
		endIndex = 0;
	} // end function Initialize

	// iterative hash function
	HashLibByteArray Func()
	{
		HashLibByteArray INT_block  = PBKDF2_HMACNotBuildInAdapter::GetBigEndianBytes(Block);
		HMAC->Initialize();

		HMAC->TransformBytes(*Salt, 0, (int32_t)Salt->size());
		HMAC->TransformBytes(INT_block, 0, (int32_t)INT_block.size());

		HashLibByteArray temp = HMAC->TransformFinal()->GetBytes();
		HashLibByteArray ret = temp;

		register uint32_t i = 2;
		register int32_t j = 0;
		while (i <= IterationCount)
		{
			temp = HMAC->ComputeBytes(temp)->GetBytes();
			j = 0;
			while (j < BlockSize)
			{
				ret[j] = ret[j] ^ temp[j];
				j++;
			} // end while
			i++;
		} // end while

		Block++;

		return ret;
	} // end function Func

	/// <summary>
	/// Encodes an integer into a 4-byte array, in big endian.
	/// </summary>
	/// <param name="i">The integer to encode.</param>
	/// <returns>array of bytes, in big endian.</returns>
	inline static HashLibByteArray GetBigEndianBytes(const uint32_t i)
	{
		HashLibByteArray b = BitConverter::GetBytes(i);
		HashLibByteArray invertedBytes = HashLibByteArray({ b[3], b[2], b[1], b[0] });
		if (BitConverter::GetIsLittleEndian())
			return invertedBytes;
		return b;
	} // end function GetBigEndianBytes

private:
	IHash hash;
	IHMAC HMAC;
	shared_ptr<HashLibByteArray> Password, Salt, buffer;
	uint32_t IterationCount, Block;
	int32_t BlockSize, startIndex, endIndex;

public:
	static const char *InvalidArgument;
	static const char *InvalidIndex;
	static const char *UninitializedInstance;
	static const char *EmptyPassword;
	static const char *EmptySalt;
	static const char *IterationtooSmall;

}; // end class PBKDF2_HMACNotBuildInAdapter


const char *PBKDF2_HMACNotBuildInAdapter::InvalidArgument = "\"bc (ByteCount)\" Argument must be a value greater than zero.";
const char *PBKDF2_HMACNotBuildInAdapter::InvalidIndex = "Invalid start or end index in the internal buffer";
const char *PBKDF2_HMACNotBuildInAdapter::UninitializedInstance = "\"IHash\" instance is uninitialized";
const char *PBKDF2_HMACNotBuildInAdapter::EmptyPassword = "Password can't be empty";
const char *PBKDF2_HMACNotBuildInAdapter::EmptySalt = "Salt can't be empty";
const char *PBKDF2_HMACNotBuildInAdapter::IterationtooSmall = "Iteration must be greater than zero.";


#endif // !HLPPBKDF2_PBKDF2_HMACNotBuildInAdapter_H
