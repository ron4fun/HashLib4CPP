#ifndef HLPSDBM_H
#define HLPSDBM_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class SDBM : public Hash, public IIBlockHash, public IIHash32, public IITransformBlock
{
public:
	SDBM()
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
		register uint32_t i = a_index;

		while (a_length > 0)
		{
			hash = a_data[i] + int64_t(hash << 6) + int64_t(hash << 16)	- hash;
			i++;
			a_length--;
		} // end while
	} // end function TransformBytes

private:
	uint32_t hash;

}; // end class SDBM


#endif // !HLPSDBM_H
