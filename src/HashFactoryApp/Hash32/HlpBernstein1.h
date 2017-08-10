#ifndef HLPBERNSTEIN1_H
#define HLPBERNSTEIN1_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class Bernstein1 : public Hash, public IIBlockHash, public IIHash32, public IITransformBlock
{
public:
	Bernstein1()
		: Hash(4, 1)
	{
		name = __func__;
	} // end constructor

	virtual void Initialize()
	{
		hash = 5381;
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
			hash = (hash * 33) ^ a_data[i];
			i++;
			a_length--;
		} // end while
	} // end function TransformBytes

private:
	uint32_t hash = 5381;

}; // end class Bernstein1


#endif // !HLPBERNSTEIN1_H
