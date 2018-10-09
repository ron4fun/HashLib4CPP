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

	virtual IHash Clone() const
	{
		RS HashInstance;

		HashInstance = RS();
		HashInstance.hash = hash;
		HashInstance.a = a;

		IHash hash = make_shared<RS>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

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
