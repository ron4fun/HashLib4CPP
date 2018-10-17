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

#ifndef HLPMULTIPLETRANSFORMNONBLOCK_H
#define HLPMULTIPLETRANSFORMNONBLOCK_H

#include "HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class MultipleTransformNonBlock : public Hash, public IINonBlockHash
{
public:
	MultipleTransformNonBlock(const int32_t a_hash_size, const int32_t a_block_size)
		: Hash(a_hash_size, a_block_size)
	{} // end constructor

	~MultipleTransformNonBlock()
	{} // end destructor

	virtual void Initialize()
	{
		_list.clear();
	} // end fucntion Initialize

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		const HashLibByteArray::const_iterator start = a_data.begin() + a_index;
		const HashLibByteArray::const_iterator end = start + a_length;

		_list.push_back(HashLibByteArray(start, end));
	} // end function TransformBytes

	virtual IHashResult TransformFinal()
	{
		IHashResult result = ComputeAggregatedBytes(Aggregate());

		Initialize();

		return result;
	} // end function TransformFinal

	virtual IHashResult ComputeBytes(const HashLibByteArray &a_data)
	{
		Initialize();
	
		return ComputeAggregatedBytes(a_data);
	} // end function ComputeBytes

protected:
	virtual IHashResult ComputeAggregatedBytes(const HashLibByteArray &a_data) = 0;

private:
	HashLibByteArray Aggregate()
	{
		register uint32_t sum = 0, index = 0;
		
		for (register uint32_t i = 0; i < _list.size(); i++)
		{
			sum = sum + (uint32_t)(_list)[i].size();
		} // end for
		
		HashLibByteArray result = HashLibByteArray(sum);
		
		for (register uint32_t i = 0; i < _list.size(); i++) 
		{
			memmove(&result[index], &(_list)[i][0], (_list)[i].size() * sizeof(uint8_t));
			index = index + (uint32_t)(_list)[i].size();
		} // end for

		return result;
	} // end function Aggregate

protected:
	HashLibMatrixByteArray _list;

}; // end class MultipleTransformNonBlock

#endif // !HLPMULTIPLETRANSFORMNONBLOCK_H


