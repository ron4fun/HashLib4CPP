#ifndef HLPONEATTIME_H
#define HLPONEATTIME_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class OneAtTime : public Hash, public IIBlockHash, public IIHash32, public IITransformBlock
{
public:
	OneAtTime()
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
		hash = hash + (hash << 3);
		hash = hash ^ (hash >> 11);
		hash = hash + (hash << 15);

		IHashResult result(new HashResult(hash));

		Initialize();

		return result;
	} // end function TransformFinal

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		register uint32_t i = a_index;

		while (a_length > 0)
		{
			hash = hash + a_data[i];
			hash = hash + (hash << 10);
			hash = hash ^ (hash >> 6);
			i++;
			a_length--;
		} // end while
	} // end function TransformBytes

private:
	uint32_t hash;

}; // end class OneAtTime


#endif // !HLPONEATTIME_H
