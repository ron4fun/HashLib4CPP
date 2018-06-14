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

#ifndef HLPSHA2_512_256_H
#define HLPSHA2_512_256_H

#include "HlpSHA2_512Base.h"


class SHA2_512_256 : public SHA2_512Base
{
public:
	SHA2_512_256()
		: SHA2_512Base(32)
	{
		name = __func__;
	} // end constructor

	virtual void Initialize()
	{
		state.get()[0] = 0x22312194FC2BF72C;
		state.get()[1] = 0x9F555FA3C84C64C2;
		state.get()[2] = 0x2393B86B6F53B151;
		state.get()[3] = 0x963877195940EABD;
		state.get()[4] = 0x96283EE2A88EFFE3;
		state.get()[5] = 0xBE5E1E2553863992;
		state.get()[6] = 0x2B0199FC2C85B8AA;
		state.get()[7] = 0x0EB72DDC81C52CA2;

		SHA2_512Base::Initialize();
	} // end function Initialize

protected:
	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(4 * sizeof(uint64_t));
		Converters::be64_copy(&state.get()[0], 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult

}; // end class SHA2_512_256


#endif //!HLPSHA2_512_256_H