// ///////////////////////////////////////////////////////////////// //
// *C++ 11 HashFactory Library                                 
// *Copyright(c) 2018  Mbadiwe Nnaemeka Ronald                 
// *Github Repository <https://github.com/ron4fun>             

// *Distributed under the MIT software license, see the accompanying file LICENSE 
// *or visit http ://www.opensource.org/licenses/mit-license.php.           

// *Acknowledgements:                                  
// ** //
// *Thanks to Ugochukwu Mmaduekwe (https://github.com/Xor-el) for his creative        
// *development of this library in Pascal/Delphi                         

// ////////////////////////////////////////////////////// ///////////////

#ifndef HLPSUPERFAST_H
#define HLPSUPERFAST_H

#include "../Base/HlpMultipleTransformNonBlock.h"


class SuperFast : public MultipleTransformNonBlock, public IIHash32, public IITransformBlock
{
public:
	SuperFast()
		: MultipleTransformNonBlock(4, 4)
	{
		name = __func__;
	} // end constructor

	virtual IHash Clone() const
	{
		SuperFast HashInstance;

		HashInstance = SuperFast();
		
		HashInstance._list = _list;

		IHash hash = make_shared<SuperFast>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

protected:
	virtual IHashResult ComputeAggregatedBytes(const HashLibByteArray &a_data)
	{
		register uint32_t hash, tmp, u1;
		register int32_t Length, currentIndex, i1, i2;
		
		Length = (int32_t)a_data.size();

		if (Length == 0)
			return make_shared<HashResult>(int32_t(0));
		
		hash = uint32_t(Length);
		currentIndex = 0;

		while (Length >= 4)
		{
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			hash = uint16_t(hash + uint32_t(i1 | i2));
			u1 = uint32_t(a_data[currentIndex]);
			currentIndex++;
			tmp = uint32_t((uint8_t(u1) | a_data[currentIndex] << 8) << 11) ^ hash;
			currentIndex++;
			hash = (hash << 16) ^ tmp;
			hash = hash + (hash >> 11);

			Length -= 4;
		} // end while

		switch (Length)
		{
		case 3:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex];
			currentIndex++;
			hash = hash + uint16_t(i1 | i2 << 8);
			hash = hash ^ (hash << 16);
			hash = hash ^ (uint32_t(a_data[currentIndex]) << 18);
			hash = hash + (hash >> 11);
			break;

		case 2:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex];
			hash = hash + uint16_t(i1 | i2 << 8);
			hash = hash ^ (hash << 11);
			hash = hash + (hash >> 17);
			break;

		case 1:
			i1 = a_data[currentIndex];
			hash = hash + uint32_t(i1);
			hash = hash ^ (hash << 10);
			hash = hash + (hash >> 1);
			break;
		} // end switch

		hash = hash ^ (hash << 3);
		hash = hash + (hash >> 5);
		hash = hash ^ (hash << 4);
		hash = hash + (hash >> 17);
		hash = hash ^ (hash << 25);
		hash = hash + (hash >> 6);

		return IHashResult(new HashResult(hash));
	} // end function ComputeAggregatedBytes

}; // end class SuperFast


#endif // !HLPSUPERFAST_H
