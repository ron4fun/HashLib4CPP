#ifndef HLPELF_H
#define HLPELF_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class ELF : public Hash, public IIBlockHash, public IIHash32, public IITransformBlock
{
public:
	ELF()
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
		register uint32_t g, i = a_index;

		while (a_length > 0)
		{
			hash = (hash << 4) + a_data[i];
			g = hash & 0xF0000000;

			if (g != 0)
				hash = hash ^ (g >> 24);

			hash = hash & (~g);
			i++;
			a_length--;
		} // end while
	} // end function TransformBytes

private:
	uint32_t hash;

}; // end class ELF


#endif // !HLPELF_H
