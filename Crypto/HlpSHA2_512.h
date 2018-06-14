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

#ifndef HLPSHA2_512_H
#define HLPSHA2_512_H

#include "HlpSHA2_512Base.h"


class SHA2_512 : public SHA2_512Base
{
public:
	SHA2_512()
		: SHA2_512Base(64)
	{
		name = __func__;
	} // end constructor

	virtual void Initialize()
	{
		state.get()[0] = 0x6A09E667F3BCC908;
		state.get()[1] = 0xBB67AE8584CAA73B;
		state.get()[2] = 0x3C6EF372FE94F82B;
		state.get()[3] = 0xA54FF53A5F1D36F1;
		state.get()[4] = 0x510E527FADE682D1;
		state.get()[5] = 0x9B05688C2B3E6C1F;
		state.get()[6] = 0x1F83D9ABFB41BD6B;
		state.get()[7] = 0x5BE0CD19137E2179;

		SHA2_512Base::Initialize();
	} // end function Initialize

protected:
	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(8 * sizeof(uint64_t));
		Converters::be64_copy(&state.get()[0], 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult

}; // end class SHA2_512


#endif //!HLPSHA2_512_H