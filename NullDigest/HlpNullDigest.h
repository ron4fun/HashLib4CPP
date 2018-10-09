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

#ifndef HLPNULLDIGEST_H
#define HLPNULLDIGEST_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"

#include <sstream>
using namespace std;

class NullDigest : public Hash, public IITransformBlock
{
public:
	NullDigest()
		: Hash(-1,-1) // Dummy State
	{
		name = __func__;

		Out = make_shared<stringstream>();
	} // end constructor

	virtual IHash Clone() const
	{
		NullDigest HashInstance = NullDigest();
		*HashInstance.Out << Out->str();
	
		IHash hash = make_shared<NullDigest>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		Out->str(string()); // Reset stream
		hash_size = 0;
		block_size = 0;
	} // end function Initialize

	virtual IHashResult TransformFinal()
	{
		HashLibByteArray res;
		
		streampos size = GetStreamSize(*Out);
		
		res.resize(size);
		Out->read((char *)&res[0], size);

		IHashResult result(new HashResult(res));

		Initialize();

		return result;
	} // end function TransformFinal

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		const HashLibByteArray::const_iterator start = a_data.begin() + a_index;
		const HashLibByteArray::const_iterator end = start + a_length;

		*Out << string(start, end);
		hash_size = int32_t(GetStreamSize(*Out));
	} // end function TransformBytes

private:
	static streampos GetStreamSize(stringstream &a_stream)
	{
		streampos pos = a_stream.tellg();

		streampos fsize = pos;
		a_stream.seekg(pos, ios::end);
		fsize = a_stream.tellg() - fsize;

		a_stream.seekg(pos, ios::beg); // return cur to original pos

		return fsize;
	} // end function GetStreamSize

private:
	shared_ptr<stringstream> Out;

}; // end class NullDigest


#endif // !HLPNULLDIGEST_H
