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

#ifndef HLPMDBASE
#define HLPMDBASE

#include "../Base/HlpHashCryptoNotBuildIn.h"


class MDBase : public BlockHash, public IICryptoNotBuildIn
{
public:
	virtual void Initialize()
	{
		(*state)[0] = 0x67452301;
		(*state)[1] = 0xEFCDAB89;
		(*state)[2] = 0x98BADCFE;
		(*state)[3] = 0x10325476;

		BlockHash::Initialize();
	} // end function Initialize

protected:

	MDBase(const int32_t a_state_length, const int32_t a_hash_size)
		: BlockHash(a_hash_size, 64), size(a_state_length)
	{
		state = make_shared<HashLibUInt32Array>(size); //new uint32_t[size];		
	} // end constructor

	~MDBase()
	{
		//delete[] state;
	} // end destructor
	
	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(size * sizeof(uint32_t));

		Converters::le32_copy((uint32_t*)(&(*state)[0]), 0, (uint8_t*)&result[0], 0, size * sizeof(uint32_t));

		return result;
	} // end function GetResult

	virtual void Finish()
	{
		uint64_t bits;
		int32_t padindex;

		bits = processed_bytes * 8;
		if (buffer->GetPos() < 56)
			padindex = 56 - buffer->GetPos();
		else
			padindex = 120 - buffer->GetPos();

		HashLibByteArray pad = HashLibByteArray(padindex + 8);

		pad[0] = 0x80;

		bits = Converters::le2me_64(bits);

		Converters::ReadUInt64AsBytesLE(bits, pad, padindex);

		padindex = padindex + 8;

		TransformBytes(pad, 0, padindex);

	} // end function Finish
	
protected:
	static const uint32_t C1 = 0x50A28BE6;
	static const uint32_t C2 = 0x5A827999;
	static const uint32_t C3 = 0x5C4DD124;
	static const uint32_t C4 = 0x6ED9EBA1;
	static const uint32_t C5 = 0x6D703EF3;
	static const uint32_t C6 = 0x8F1BBCDC;
	static const uint32_t C7 = 0x7A6D76E9;
	static const uint32_t C8 = 0xA953FD4E;
	
	shared_ptr<HashLibUInt32Array> state;
	uint32_t size = 0;

}; // end class MDBase


#endif // !HLPMDBASE