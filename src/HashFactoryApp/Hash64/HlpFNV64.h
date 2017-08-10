#ifndef HLPFNV64_H
#define HLPFNV64_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class FNV64 : public Hash, public IIBlockHash, public IIHash64, public IITransformBlock
{
public:
	FNV64()
		: Hash(8, 1)
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
		register uint32_t i = a_index;

		while (a_length > 0)
		{
			hash = (hash * 1099511628211) ^ a_data[i];
			i++;
			a_length--;
		} // end while
	} // end function TransformBytes

private:
	uint64_t hash;

}; // end class FNV64


#endif // !HLPFNV64_H
