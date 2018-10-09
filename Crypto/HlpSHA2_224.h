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

#ifndef HLPSHA2_224_H
#define HLPSHA2_224_H

#include "HlpSHA2_256Base.h"


class SHA2_224 : public SHA2_256Base
{
public:
	SHA2_224()
		: SHA2_256Base(28)
	{
		name = __func__;
	} // end constructor

	virtual IHash Clone() const
	{
		SHA2_224 HashInstance;

		HashInstance = SHA2_224();
		HashInstance.state = state;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<SHA2_224>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		state[0] = 0xC1059ED8;
		state[1] = 0x367CD507;
		state[2] = 0x3070DD17;
		state[3] = 0xF70E5939;
		state[4] = 0xFFC00B31;
		state[5] = 0x68581511;
		state[6] = 0x64F98FA7;
		state[7] = 0xBEFA4FA4;

		SHA2_256Base::Initialize();
	} // end function Initialize

protected:
	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(7 * sizeof(uint32_t));
		Converters::be32_copy(&state[0], 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult


}; // end class SHA2_224


#endif //!HLPSHA2_224_H