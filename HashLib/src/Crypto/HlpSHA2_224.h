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

	virtual void Initialize()
	{
		state.get()[0] = 0xC1059ED8;
		state.get()[1] = 0x367CD507;
		state.get()[2] = 0x3070DD17;
		state.get()[3] = 0xF70E5939;
		state.get()[4] = 0xFFC00B31;
		state.get()[5] = 0x68581511;
		state.get()[6] = 0x64F98FA7;
		state.get()[7] = 0xBEFA4FA4;

		SHA2_256Base::Initialize();
	} // end function Initialize

protected:
	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(7 * sizeof(uint32_t));
		Converters::be32_copy(&state.get()[0], 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult


}; // end class SHA2_224


#endif //!HLPSHA2_224_H