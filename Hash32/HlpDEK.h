#ifndef HLPDEK_H
#define HLPDEK_H

#include "../Base/HlpMultipleTransformNonBlock.h"


class DEK : public MultipleTransformNonBlock, public IIHash32, public IITransformBlock
{
public:
	DEK()
		: MultipleTransformNonBlock(4, 1)
	{
		name = __func__;
	} // end constructor

protected:
	virtual IHashResult ComputeAggregatedBytes(const HashLibByteArray &a_data)
	{
		register uint32_t hash = uint32_t(a_data.size());

		for (register uint32_t i = 0; i < a_data.size(); i++)
			hash = Bits::RotateLeft32(hash, 5) ^ a_data[i];
		
		return IHashResult(new HashResult(hash));
	} // end function ComputeAggregatedBytes

}; // end class DEK


#endif // !HLPDEK_H
