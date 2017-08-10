#ifndef HLPRS_H
#define HLPRS_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class RS : public Hash, public IIBlockHash, public IIHash32, public IITransformBlock
{
public:
	RS()
		: Hash(4, 1)
	{
		name = __func__;
	} // end constructor

	virtual void Initialize()
	{
		hash = 0;
		a = 63689;
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
			hash = (hash * a) + a_data[i];
			a = a * B;
			i++;
			a_length--;
		} // end while
	} // end function TransformBytes

private:
	uint32_t a, hash;

	static const uint32_t B = uint32_t(378551);

}; // end class RS


#endif // !HLPRS_H
