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

#ifndef HLPADLER32_H
#define HLPADLER32_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class Adler32 : public Hash, public IIChecksum, public IIBlockHash, public IIHash32, public IITransformBlock
{
public:
	Adler32()
		: Hash(4, 1)
	{
		name = __func__;
	} // end constructor
	
	virtual IHash Clone() const
	{
		Adler32 HashInstance;

		HashInstance = Adler32();
		HashInstance.a = a;
		HashInstance.b = b;

		IHash hash = make_shared<Adler32>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		a = 1;
		b = 0;
	} // end function Initialize

	virtual IHashResult TransformFinal()
	{
		IHashResult result( new HashResult(int32_t((b << 16) | a)));

		Initialize();

		return result;
	} // end function TransformFinal

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		register int32_t n;

		// lifted from PngEncoder Adler32.cs

		while (a_length > 0)
		{
			// We can defer the modulo operation:
			// a maximally grows from 65521 to 65521 + 255 * 3800
			// b maximally grows by3800 * median(a) = 2090079800 < 2^31
			n = 3800;
			if (n > a_length)
				n  = a_length;
			
			a_length = a_length - n;

			while ((n - 1) >= 0)
			{
				a = (a + a_data[a_index]);
				b = (b + a);
				a_index++;
				n--;
			} // end while

			a = a % MOD_ADLER;
			b = b % MOD_ADLER;
		} // end while

	} // end function TransformBlock

private:
	uint32_t a = 1, b = 0;

	static const uint32_t MOD_ADLER = 65521;

}; // end class Adler32


#endif // !HLPADLER32_H

