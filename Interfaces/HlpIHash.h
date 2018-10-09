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

#ifndef HLPIHASH_H
#define HLPIHASH_H

#include <fstream>
#include "HlpIHashResult.h"
#include "../Utils/HlpHashLibTypes.h"

class IIHash;

typedef shared_ptr<IIHash> IHash;


class IIHash
{
public:
	virtual string GetName() const = 0;
	virtual int32_t GetBlockSize() const = 0;
	virtual int32_t GetHashSize() const = 0;
	virtual int32_t GetBufferSize() const = 0;
	virtual void SetBufferSize(const int32_t value) = 0;

	virtual IHash Clone() const = 0;

	virtual IHashResult ComputeString(const string &a_data) = 0;
	virtual IHashResult ComputeBytes(const HashLibByteArray &a_data) = 0;
	virtual IHashResult ComputeUntyped(const void *a_data, const int64_t a_length) = 0;
	virtual IHashResult ComputeStream(ifstream &a_stream, const int64_t a_length = -1) = 0;
	virtual IHashResult ComputeFile(const string &a_file_name,
		const int64_t a_from = 0, const int64_t a_length = -1) = 0;

	virtual void Initialize() = 0;

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length) = 0;
	virtual void TransformBytes(const HashLibByteArray &a_data, const int32_t a_index) = 0;
	virtual void TransformBytes(const HashLibByteArray &a_data) = 0;
	
	virtual void TransformUntyped(const void *a_data, const int64_t a_length) = 0;

	virtual IHashResult TransformFinal() = 0;

	virtual void TransformString(const string &a_data) = 0;
	virtual void TransformStream(ifstream &a_stream, const int64_t a_length = -1) = 0;
	virtual void TransformFile(const string &a_file_name,
		const int64_t a_from = 0, const int64_t a_length = -1) = 0;

}; // end class IHash

#endif // !HLPIHASH
