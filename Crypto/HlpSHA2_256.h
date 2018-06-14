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

	virtual void Initialize()
	{
		state.get()[0] = 0x6A09E667;
		state.get()[1] = 0xBB67AE85;
		state.get()[2] = 0x3C6EF372;
		state.get()[3] = 0xA54FF53A;
		state.get()[4] = 0x510E527F;
		state.get()[5] = 0x9B05688C;
		state.get()[6] = 0x1F83D9AB;
		state.get()[7] = 0x5BE0CD19;

		SHA2_256Base::Initialize();
	} // end function Initialize

protected:
	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(8 * sizeof(uint32_t));
		Converters::be32_copy(&state.get()[0], 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult
	
}; // end class SHA2_256


#endif //!HLPSHA2_256_H