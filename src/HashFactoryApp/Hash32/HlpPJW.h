#ifndef HLPPJW_H
#define HLPPJW_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class PJW : public Hash, public IIBlockHash, public IIHash32, public IITransformBlock
{
public:
	PJW()
		: Hash(4, 1)
	{
		name = __func__;
	} // end constructor

	virtual void Initialize()
	{
		hash = 0;
	} // end function Initialize

	virtual IHashResult TransformFinal()
	{
		IHashResult result(new HashResult(hash));

		Initialize();

		return result;
	} // end function TransformFinal

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		register uint32_t test, i = a_index;

		while (a_length > 0)
		{
			hash = (hash << OneEighth) + a_data[i];
			test = hash & HighBits;
			if (test != 0)
				hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
			i++;
			a_length--;
		} // end while
	} // end function TransformBytes

private:
	uint32_t hash;

	static const uint32_t UInt32MaxValue = uint32_t(4294967295);
	static const int32_t BitsInUnsignedInt = int32_t(sizeof(uint32_t) * 8);
	static const int32_t ThreeQuarters = int32_t(BitsInUnsignedInt * 3) >> 2;
	static const int32_t OneEighth = int32_t(BitsInUnsignedInt >> 3);
	static const uint32_t HighBits = uint32_t(UInt32MaxValue << (BitsInUnsignedInt - OneEighth));

}; // end class PJW


#endif // !HLPPJW_H
