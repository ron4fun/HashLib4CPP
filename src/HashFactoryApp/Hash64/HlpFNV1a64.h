#ifndef HLPFNV1A64_H
#define HLPFNV1A64_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class FNV1a64 : public Hash, public IIBlockHash, public IIHash64, public IITransformBlock
{
public:
	FNV1a64()
		: Hash(8, 1)
	{
		name = __func__;
	} // end constructor

	virtual void Initialize()
	{
		hash = 14695981039346656037;
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
			hash = (hash ^ a_data[i]) * 1099511628211;
			i++;
			a_length--;
		} // end while
	} // end function TransformBytes

private:
	uint64_t hash;

}; // end class FNV1a64


#endif // !HLPFNV1A64_H
