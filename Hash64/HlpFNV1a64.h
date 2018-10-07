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

	virtual IHash Clone() const
	{
		FNV1a64 HashInstance;

		HashInstance = FNV1a64();
		HashInstance.hash = hash;

		IHash hash = make_shared<FNV1a64>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

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
