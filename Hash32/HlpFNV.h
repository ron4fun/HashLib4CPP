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

#ifndef HLPFNV_H
#define HLPFNV_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class FNV : public Hash, public IIBlockHash, public IIHash32, public IITransformBlock
{
public:
	FNV()
		: Hash(4, 1)
	{
		name = __func__;
	} // end constructor

	virtual IHash Clone() const
	{
		FNV HashInstance;

		HashInstance = FNV();
		HashInstance.hash = hash;

		IHash hash = make_shared<FNV>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

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
			hash = (hash * 16777619) ^ a_data[i];
			i++;
			a_length--;
		} // end while
	} // end function TransformBytes

private:
	uint32_t hash;

}; // end class FNV


#endif // !HLPFNV_H
