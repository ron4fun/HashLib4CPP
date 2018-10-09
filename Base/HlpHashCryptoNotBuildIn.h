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

#ifndef HLPHASHCRYPTONOTBUILDIN_H
#define HLPHASHCRYPTONOTBUILDIN_H

#include "HlpHash.h"
#include "HlpHashBuffer.h"
#include "../Interfaces/HlpIHashInfo.h"


class BlockHash : public IIBlockHash, public Hash
{
public:
	BlockHash(const int32_t a_hash_size, const int32_t a_block_size,
		int32_t a_buffer_size = -1)
		: Hash(a_hash_size, a_block_size)
	{
		if (a_buffer_size == -1)
			a_buffer_size = a_block_size;
		
		buffer = make_shared<HashBuffer>(a_buffer_size);
	} // end constructor

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		uint8_t* ptr_a_data = (uint8_t*)(&a_data[0]);

		if (!buffer->GetIsEmpty())
		{
			if (buffer->Feed(ptr_a_data, (int32_t)a_data.size(), a_index, a_length, processed_bytes))
				TransformBuffer();
		} // end if
		
		while (a_length >= buffer->GetLength())
		{
			processed_bytes = processed_bytes + uint64_t(buffer->GetLength());
			TransformBlock(ptr_a_data, buffer->GetLength(), a_index);
			a_index = a_index + buffer->GetLength();
			a_length = a_length - buffer->GetLength();
		} // end while
			
		if (a_length > 0)
			buffer->Feed(ptr_a_data, (int32_t)a_data.size(), a_index, a_length, processed_bytes);

	} // end function TransformBytes

	virtual void Initialize()
	{
		buffer->Initialize();
		processed_bytes = 0;
	} // end function Initialize

	~BlockHash()
	{} // end destructor

	virtual IHashResult TransformFinal()
	{
		Finish();

		HashLibByteArray tempresult = GetResult();
		
		Initialize();
		
		return make_shared<HashResult>(tempresult);
	} // end function TransformFinal

private:
	inline void TransformBuffer()
	{
		TransformBlock(&buffer->GetBytes()[0], buffer->GetLength(), 0);
	} // end function TransformBuffer

	virtual void Finish() = 0;

	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index) = 0;

	virtual HashLibByteArray GetResult() = 0;
	
protected:
	shared_ptr<HashBuffer> buffer;
	uint64_t processed_bytes;

}; // end class BlockHash


#endif // !HLPHASHCRYPTONOTBUILDIN_H
