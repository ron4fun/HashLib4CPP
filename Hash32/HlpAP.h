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

#ifndef HLPAP_H
#define HLPAP_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class AP : public Hash, public IIBlockHash, public IIHash32, public IITransformBlock
{
public:
	AP()
		: Hash(4, 1)
	{
		name = __func__;
	} // end constructor

	virtual IHash Clone() const
	{
		AP HashInstance;

		HashInstance = AP();
		HashInstance.hash = hash;
		HashInstance.index = index;

		IHash hash = make_shared<AP>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		hash = 0xAAAAAAAA;
		index = 0;
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
			if ((index & 1) == 0)
				hash = hash ^ ((hash << 7) ^ a_data[i] * (hash >> 3));
			else
				hash = hash ^ (~((hash << 11) ^ a_data[i] ^ (hash >> 5)));

			index++;
			i++;
			a_length--;
		} // end while
	} // end function TransformBytes

private:
	uint32_t hash = 0xAAAAAAAA;
	int32_t index = 0;

}; // end class AP


#endif // !HLPAP_H

