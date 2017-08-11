#ifndef HLPFNV1A_H
#define HLPFNV1A_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class FNV1a : public Hash, public IIBlockHash, public IIHash32, public IITransformBlock
{
public:
	FNV1a()
		: Hash(4, 1)
	{
		name = __func__;
	} // end constructor

	virtual void Initialize()
	{
		hash = 2166136261;
	} // end function Initialize

	virtual IHashResult TransformFinal()
	{
		IHashResult result(new HashResult(hash));

		Initialize();

		return result;
	} // end function TransformFinal

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		register uint32_t i = a_index;

		while (a_length > 0)
		{
			hash = (hash ^ a_data[i]) * 16777619;
			i++;
			a_length--;
		} // end while
	} // end function TransformBytes

private:
	uint32_t hash;

}; // end class FNV1a


#endif // !HLPFNV1A_H
