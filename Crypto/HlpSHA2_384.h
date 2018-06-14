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

#ifndef HLPSHA2_384_H
#define HLPSHA2_384_H

#include "HlpSHA2_512Base.h"


class SHA2_384 : public SHA2_512Base
{
public:
	SHA2_384()
		: SHA2_512Base(48)
	{
		name = __func__;
	} // end constructor

	virtual void Initialize()
	{
		state.get()[0] = 0xCBBB9D5DC1059ED8;
		state.get()[1] = 0x629A292A367CD507;
		state.get()[2] = 0x9159015A3070DD17;
		state.get()[3] = 0x152FECD8F70E5939;
		state.get()[4] = 0x67332667FFC00B31;
		state.get()[5] = 0x8EB44A8768581511;
		state.get()[6] = 0xDB0C2E0D64F98FA7;
		state.get()[7] = 0x47B5481DBEFA4FA4;

		SHA2_512Base::Initialize();
	} // end function Initialize

protected:
	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(6 * sizeof(uint64_t));
		Converters::be64_copy(&state.get()[0], 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult

}; // end class SHA2_384


#endif //!HLPSHA2_384_H