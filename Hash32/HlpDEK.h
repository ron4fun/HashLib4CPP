// ///////////////////////////////////////////////////////////////// //
// *C++ 11 HashLib4CPP Library                                 
// *Copyright(c) 2018  Mbadiwe Nnaemeka Ronald                 
// *Github Repository <https://github.com/ron4fun>             

// *Distributed under the MIT software license, see the accompanying file LICENSE 
// *or visit http ://www.opensource.org/licenses/mit-license.php.           

// *Acknowledgements:                                  
// ** //
// *Thanks to Ugochukwu Mmaduekwe (https://github.com/Xor-el) for his creative        
// *development of this library in Pascal/Delphi                         

// ////////////////////////////////////////////////////// ///////////////

#ifndef HLPDEK_H
#define HLPDEK_H

#include "../Base/HlpMultipleTransformNonBlock.h"


class DEK : public MultipleTransformNonBlock, public IIHash32, public IITransformBlock
{
public:
	DEK()
		: MultipleTransformNonBlock(4, 1)
	{
		name = __func__;
	} // end constructor

	virtual IHash Clone() const
	{
		DEK HashInstance;

		HashInstance = DEK();
	
		HashInstance._list = _list;
		
		IHash hash = make_shared<DEK>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

protected:
	virtual IHashResult ComputeAggregatedBytes(const HashLibByteArray &a_data)
	{
		register uint32_t hash = uint32_t(a_data.size());

		for (register uint32_t i = 0; i < a_data.size(); i++)
			hash = Bits::RotateLeft32(hash, 5) ^ a_data[i];
		
		return IHashResult(new HashResult(hash));
	} // end function ComputeAggregatedBytes

}; // end class DEK


#endif // !HLPDEK_H
