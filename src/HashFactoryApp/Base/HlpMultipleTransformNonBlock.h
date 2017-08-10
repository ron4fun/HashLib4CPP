#ifndef HLPMULTIPLETRANSFORMNONBLOCK_H
#define HLPMULTIPLETRANSFORMNONBLOCK_H

#include "HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class MultipleTransformNonBlock : public Hash, public IINonBlockHash
{
public:
	MultipleTransformNonBlock(const int32_t a_hash_size, const int32_t a_block_size)
		: Hash(a_hash_size, a_block_size)
	{
		_list = make_shared<vector<HashLibByteArray>>();
	} // end constructor

	~MultipleTransformNonBlock()
	{} // end destructor

	virtual void Initialize()
	{
		_list->clear();
	} // end fucntion Initialize

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		_list->push_back(a_data);
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
		
		for (register uint32_t i = 0; i < _list->size(); i++)
		{
			sum = sum + (uint32_t)(*_list)[i].size();
		} // end for
		
		HashLibByteArray result = HashLibByteArray(sum);
		
		for (register uint32_t i = 0; i < _list->size(); i++) 
		{
			memmove(&result[index], &(*_list)[i][0], (*_list)[i].size() * sizeof(uint8_t));
			index = index + (uint32_t)(*_list)[i].size();
		} // end for

		return result;
	} // end function Aggregate

private:
	shared_ptr<vector<HashLibByteArray>> _list;

}; // end class MultipleTransformNonBlock

#endif // !HLPMULTIPLETRANSFORMNONBLOCK_H


