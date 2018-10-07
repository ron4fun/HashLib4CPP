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

#ifndef HLPSHA2_256_H
#define HLPSHA2_256_H

#include "HlpSHA2_256Base.h"


class SHA2_256 : public SHA2_256Base
{
public:
	SHA2_256()
		: SHA2_256Base(32)
	{
		name = __func__;
	} // end constructor

	virtual IHash Clone() const
	{
		SHA2_256 HashInstance;

		HashInstance = SHA2_256();
		HashInstance.state = state;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<SHA2_256>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		state[0] = 0x6A09E667;
		state[1] = 0xBB67AE85;
		state[2] = 0x3C6EF372;
		state[3] = 0xA54FF53A;
		state[4] = 0x510E527F;
		state[5] = 0x9B05688C;
		state[6] = 0x1F83D9AB;
		state[7] = 0x5BE0CD19;

		SHA2_256Base::Initialize();
	} // end function Initialize

protected:
	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(8 * sizeof(uint32_t));
		Converters::be32_copy(&state[0], 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult
	
}; // end class SHA2_256


#endif //!HLPSHA2_256_H