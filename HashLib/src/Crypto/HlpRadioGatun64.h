#ifndef HLPRADIOGATUN64_H
#define HLPRADIOGATUN64_H

#include "../Base/HlpHashCryptoNotBuildIn.h"


class RadioGatun64 : public BlockHash, public IICryptoNotBuildIn, public IITransformBlock
{
public:
	RadioGatun64()
		: BlockHash(32, 24)
	{
		name = __func__;

		mill = shared_ptr<uint64_t>(new uint64_t[19], default_delete<uint64_t[]>());
		a = shared_ptr<uint64_t>(new uint64_t[19], default_delete<uint64_t[]>());
		data = shared_ptr<uint64_t>(new uint64_t[3], default_delete<uint64_t[]>());

		belt = make_shared<HashLibMatrixUInt64Array>(13);

		for (register uint32_t i = 0; i < 13; i++)
			(*belt)[i] = HashLibUInt64Array(3);

	} // end constructor

	~RadioGatun64()
	{} // end destructor

	virtual void Initialize()
	{
		memset(mill.get(), 0, 19 * sizeof(uint64_t));

		for (register uint32_t i = 0; i < 13; i++)
			memset(&(*belt)[i][0], 0, 3 * sizeof(uint64_t));

		BlockHash::Initialize();
	} // end function Initialize

protected:
	virtual void Finish()
	{
		int32_t padding_size = 24 - (processed_bytes % 24);

		HashLibByteArray pad = HashLibByteArray(padding_size);

		pad[0] = 0x01;

		TransformBytes(pad, 0, padding_size);

		for (register uint32_t i = 0; i < 16; i++)
			RoundFunction();

	} // end function Finish

	virtual HashLibByteArray GetResult()
	{
		HashLibUInt64Array tempRes = HashLibUInt64Array(4);

		HashLibByteArray result = HashLibByteArray(4 * sizeof(uint64_t));

		for (register uint32_t i = 0; i < 2; i++)
		{
			RoundFunction();
			memmove(&tempRes[i * 2], &mill.get()[1], 2 * sizeof(uint64_t));
		} // end for

		Converters::le64_copy(&tempRes[0], 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult

	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		Converters::le64_copy(a_data, a_index, data.get(), 0, 24);

		register uint32_t i = 0;
		while (i < 3)
		{
			mill.get()[i + 16] = mill.get()[i + 16] ^ data.get()[i];
			(*belt)[0][i] = (*belt)[0][i] ^ data.get()[i];
			i++;
		} // end while

		RoundFunction();

		memset(data.get(), 0, 3 * sizeof(uint64_t));
	} // end function TransformBlock

private:
	inline void RoundFunction()
	{
		HashLibUInt64Array q = (*belt)[12];

		register uint32_t i = 12;
		while (i > 0)
		{
			(*belt)[i] = (*belt)[i - 1];
			i--;
		} // end while

		(*belt)[0] = q;

		i = 0;
		while (i < 12)
		{
			(*belt)[i + 1][i % 3] = (*belt)[i + 1][i % 3] ^ mill.get()[i + 1];
			i++;
		} // end while

		i = 0;
		while (i < 19)
		{
			a.get()[i] = mill.get()[i] ^ (mill.get()[(i + 1) % 19] | ~mill.get()[(i + 2) % 19]);
			i++;
		} // end while

		i = 0;
		while (i < 19)
		{
			mill.get()[i] = Bits::RotateRight64(a.get()[(7 * i) % 19], (i * (i + 1)) >> 1);
			i++;
		} // end while

		i = 0;
		while (i < 19)
		{
			a.get()[i] = mill.get()[i] ^ mill.get()[(i + 1) % 19] ^ mill.get()[(i + 4) % 19];
			i++;
		} // end while

		a.get()[0] = a.get()[0] ^ 1;

		i = 0;
		while (i < 19)
		{
			mill.get()[i] = a.get()[i];
			i++;
		} // end while

		i = 0;
		while (i < 3)
		{
			mill.get()[i + 13] = mill.get()[i + 13] ^ q[i];
			i++;
		} // end while
	} // end function RoundFunction

private:
	shared_ptr<uint64_t> mill, data, a;

	shared_ptr<HashLibMatrixUInt64Array> belt;

}; // end class RadioGatun64


#endif // !HLPRADIOGATUN64_H

