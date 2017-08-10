#ifndef HLPPANAMA_H
#define HLPPANAMA_H

#include "../Base/HlpHashCryptoNotBuildIn.h"


class Panama : public BlockHash, public IICryptoNotBuildIn, public IITransformBlock
{
public:
	Panama()
		: BlockHash(32, 32)
	{
		name = __func__;

		tap = 0;
		state = shared_ptr<uint32_t>(new uint32_t[17], default_delete<uint32_t[]>());
		theta = shared_ptr<uint32_t>(new uint32_t[17], default_delete<uint32_t[]>());
		gamma = shared_ptr<uint32_t>(new uint32_t[17], default_delete<uint32_t[]>());
		pi = shared_ptr<uint32_t>(new uint32_t[17], default_delete<uint32_t[]>());
		work_buffer = shared_ptr<uint32_t>(new uint32_t[17], default_delete<uint32_t[]>());

		if (initialized != 'I')
		{
			for (register uint32_t i = 0; i < 32; i++)
				(*stages)[i] = HashLibUInt32Array(8);
			initialized = 'I';
		} // end if
	} // end constructor

	~Panama()
	{} // end destructor

	virtual void Initialize()
	{
		memset(state.get(), 0, 17 * sizeof(uint32_t));

		for (register uint32_t i = 0; i < 32; i++)
			memset(&(*stages)[i][0], 0, 8 * sizeof(uint32_t));

		BlockHash::Initialize();
	} // end function Initialize

protected:
	virtual void Finish()
	{
		int32_t tap4, tap16, tap25;

		int32_t padding_size = 32 - (processed_bytes & 31);

		HashLibByteArray pad = HashLibByteArray(padding_size);

		pad[0] = 0x01;
		TransformBytes(pad, 0, padding_size);

		HashLibUInt32Array theta = HashLibUInt32Array(17);

		uint32_t *ptr_theta = &theta[0];

		for (register uint32_t i = 0; i < 32; i++)
		{
			tap4 = (tap + 4) & 0x1F;
			tap16 = (tap + 16) & 0x1F;

			tap = (tap - 1) & 0x1F;
			tap25 = (tap + 25) & 0x1F;

			GPT(ptr_theta);

			(*stages)[tap25][0] = (*stages)[tap25][0] ^ (*stages)[tap][2];
			(*stages)[tap25][1] = (*stages)[tap25][1] ^ (*stages)[tap][3];
			(*stages)[tap25][2] = (*stages)[tap25][2] ^ (*stages)[tap][4];
			(*stages)[tap25][3] = (*stages)[tap25][3] ^ (*stages)[tap][5];
			(*stages)[tap25][4] = (*stages)[tap25][4] ^ (*stages)[tap][6];
			(*stages)[tap25][5] = (*stages)[tap25][5] ^ (*stages)[tap][7];
			(*stages)[tap25][6] = (*stages)[tap25][6] ^ (*stages)[tap][0];
			(*stages)[tap25][7] = (*stages)[tap25][7] ^ (*stages)[tap][1];
			(*stages)[tap][0] = (*stages)[tap][0] ^ state.get()[1];
			(*stages)[tap][1] = (*stages)[tap][1] ^ state.get()[2];
			(*stages)[tap][2] = (*stages)[tap][2] ^ state.get()[3];
			(*stages)[tap][3] = (*stages)[tap][3] ^ state.get()[4];
			(*stages)[tap][4] = (*stages)[tap][4] ^ state.get()[5];
			(*stages)[tap][5] = (*stages)[tap][5] ^ state.get()[6];
			(*stages)[tap][6] = (*stages)[tap][6] ^ state.get()[7];
			(*stages)[tap][7] = (*stages)[tap][7] ^ state.get()[8];

			state.get()[0] = theta[0] ^ 0x01;
			state.get()[1] = theta[1] ^ (*stages)[tap4][0];
			state.get()[2] = theta[2] ^ (*stages)[tap4][1];
			state.get()[3] = theta[3] ^ (*stages)[tap4][2];
			state.get()[4] = theta[4] ^ (*stages)[tap4][3];
			state.get()[5] = theta[5] ^ (*stages)[tap4][4];
			state.get()[6] = theta[6] ^ (*stages)[tap4][5];
			state.get()[7] = theta[7] ^ (*stages)[tap4][6];
			state.get()[8] = theta[8] ^ (*stages)[tap4][7];
			state.get()[9] = theta[9] ^ (*stages)[tap16][0];
			state.get()[10] = theta[10] ^ (*stages)[tap16][1];
			state.get()[11] = theta[11] ^ (*stages)[tap16][2];
			state.get()[12] = theta[12] ^ (*stages)[tap16][3];
			state.get()[13] = theta[13] ^ (*stages)[tap16][4];
			state.get()[14] = theta[14] ^ (*stages)[tap16][5];
			state.get()[15] = theta[15] ^ (*stages)[tap16][6];
			state.get()[16] = theta[16] ^ (*stages)[tap16][7];

		} // end for

	} // end function Finish

	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(8 * sizeof(uint32_t));

		Converters::le32_copy(state.get() + 9, 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult

	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t tap16, tap25;
		
		Converters::le32_copy(a_data, a_index, work_buffer.get(), 0, 32);

		tap16 = (tap + 16) & 0x1F;

		tap = (tap - 1) & 0x1F;
		tap25 = (tap + 25) & 0x1F;

		GPT(theta.get());

		(*stages)[tap25][0] = (*stages)[tap25][0] ^ (*stages)[tap][2];
		(*stages)[tap25][1] = (*stages)[tap25][1] ^ (*stages)[tap][3];
		(*stages)[tap25][2] = (*stages)[tap25][2] ^ (*stages)[tap][4];
		(*stages)[tap25][3] = (*stages)[tap25][3] ^ (*stages)[tap][5];
		(*stages)[tap25][4] = (*stages)[tap25][4] ^ (*stages)[tap][6];
		(*stages)[tap25][5] = (*stages)[tap25][5] ^ (*stages)[tap][7];
		(*stages)[tap25][6] = (*stages)[tap25][6] ^ (*stages)[tap][0];
		(*stages)[tap25][7] = (*stages)[tap25][7] ^ (*stages)[tap][1];
		(*stages)[tap][0] = (*stages)[tap][0] ^ work_buffer.get()[0];
		(*stages)[tap][1] = (*stages)[tap][1] ^ work_buffer.get()[1];
		(*stages)[tap][2] = (*stages)[tap][2] ^ work_buffer.get()[2];
		(*stages)[tap][3] = (*stages)[tap][3] ^ work_buffer.get()[3];
		(*stages)[tap][4] = (*stages)[tap][4] ^ work_buffer.get()[4];
		(*stages)[tap][5] = (*stages)[tap][5] ^ work_buffer.get()[5];
		(*stages)[tap][6] = (*stages)[tap][6] ^ work_buffer.get()[6];
		(*stages)[tap][7] = (*stages)[tap][7] ^ work_buffer.get()[7];

		state.get()[0] = theta.get()[0] ^ 0x01;
		state.get()[1] = theta.get()[1] ^ work_buffer.get()[0];
		state.get()[2] = theta.get()[2] ^ work_buffer.get()[1];
		state.get()[3] = theta.get()[3] ^ work_buffer.get()[2];
		state.get()[4] = theta.get()[4] ^ work_buffer.get()[3];
		state.get()[5] = theta.get()[5] ^ work_buffer.get()[4];
		state.get()[6] = theta.get()[6] ^ work_buffer.get()[5];
		state.get()[7] = theta.get()[7] ^ work_buffer.get()[6];
		state.get()[8] = theta.get()[8] ^ work_buffer.get()[7];
		state.get()[9] = theta.get()[9] ^ (*stages)[tap16][0];
		state.get()[10] = theta.get()[10] ^ (*stages)[tap16][1];
		state.get()[11] = theta.get()[11] ^ (*stages)[tap16][2];
		state.get()[12] = theta.get()[12] ^ (*stages)[tap16][3];
		state.get()[13] = theta.get()[13] ^ (*stages)[tap16][4];
		state.get()[14] = theta.get()[14] ^ (*stages)[tap16][5];
		state.get()[15] = theta.get()[15] ^ (*stages)[tap16][6];
		state.get()[16] = theta.get()[16] ^ (*stages)[tap16][7];

		memset(work_buffer.get(), 0, 8 * sizeof(uint32_t));

	} // end function TransformBlock

private:
	inline void GPT(uint32_t *a_theta)
	{
		gamma.get()[0] = state.get()[0] ^ (state.get()[1] | ~state.get()[2]);
		gamma.get()[1] = state.get()[1] ^ (state.get()[2] | ~state.get()[3]);
		gamma.get()[2] = state.get()[2] ^ (state.get()[3] | ~state.get()[4]);
		gamma.get()[3] = state.get()[3] ^ (state.get()[4] | ~state.get()[5]);
		gamma.get()[4] = state.get()[4] ^ (state.get()[5] | ~state.get()[6]);
		gamma.get()[5] = state.get()[5] ^ (state.get()[6] | ~state.get()[7]);
		gamma.get()[6] = state.get()[6] ^ (state.get()[7] | ~state.get()[8]);
		gamma.get()[7] = state.get()[7] ^ (state.get()[8] | ~state.get()[9]);
		gamma.get()[8] = state.get()[8] ^ (state.get()[9] | ~state.get()[10]);
		gamma.get()[9] = state.get()[9] ^ (state.get()[10] | ~state.get()[11]);
		gamma.get()[10] = state.get()[10] ^ (state.get()[11] | ~state.get()[12]);
		gamma.get()[11] = state.get()[11] ^ (state.get()[12] | ~state.get()[13]);
		gamma.get()[12] = state.get()[12] ^ (state.get()[13] | ~state.get()[14]);
		gamma.get()[13] = state.get()[13] ^ (state.get()[14] | ~state.get()[15]);
		gamma.get()[14] = state.get()[14] ^ (state.get()[15] | ~state.get()[16]);
		gamma.get()[15] = state.get()[15] ^ (state.get()[16] | ~state.get()[0]);
		gamma.get()[16] = state.get()[16] ^ (state.get()[0] | ~state.get()[1]);

		pi.get()[0] = gamma.get()[0];
		pi.get()[1] = Bits::RotateLeft32(gamma.get()[7], 1);
		pi.get()[2] = Bits::RotateLeft32(gamma.get()[14], 3);
		pi.get()[3] = Bits::RotateLeft32(gamma.get()[4], 6);
		pi.get()[4] = Bits::RotateLeft32(gamma.get()[11], 10);
		pi.get()[5] = Bits::RotateLeft32(gamma.get()[1], 15);
		pi.get()[6] = Bits::RotateLeft32(gamma.get()[8], 21);
		pi.get()[7] = Bits::RotateLeft32(gamma.get()[15], 28);
		pi.get()[8] = Bits::RotateLeft32(gamma.get()[5], 4);
		pi.get()[9] = Bits::RotateLeft32(gamma.get()[12], 13);
		pi.get()[10] = Bits::RotateLeft32(gamma.get()[2], 23);
		pi.get()[11] = Bits::RotateLeft32(gamma.get()[9], 2);
		pi.get()[12] = Bits::RotateLeft32(gamma.get()[16], 14);
		pi.get()[13] = Bits::RotateLeft32(gamma.get()[6], 27);
		pi.get()[14] = Bits::RotateLeft32(gamma.get()[13], 9);
		pi.get()[15] = Bits::RotateLeft32(gamma.get()[3], 24);
		pi.get()[16] = Bits::RotateLeft32(gamma.get()[10], 8);

		a_theta[0] = pi.get()[0] ^ pi.get()[1] ^ pi.get()[4];
		a_theta[1] = pi.get()[1] ^ pi.get()[2] ^ pi.get()[5];
		a_theta[2] = pi.get()[2] ^ pi.get()[3] ^ pi.get()[6];
		a_theta[3] = pi.get()[3] ^ pi.get()[4] ^ pi.get()[7];
		a_theta[4] = pi.get()[4] ^ pi.get()[5] ^ pi.get()[8];
		a_theta[5] = pi.get()[5] ^ pi.get()[6] ^ pi.get()[9];
		a_theta[6] = pi.get()[6] ^ pi.get()[7] ^ pi.get()[10];
		a_theta[7] = pi.get()[7] ^ pi.get()[8] ^ pi.get()[11];
		a_theta[8] = pi.get()[8] ^ pi.get()[9] ^ pi.get()[12];
		a_theta[9] = pi.get()[9] ^ pi.get()[10] ^ pi.get()[13];
		a_theta[10] = pi.get()[10] ^ pi.get()[11] ^ pi.get()[14];
		a_theta[11] = pi.get()[11] ^ pi.get()[12] ^ pi.get()[15];
		a_theta[12] = pi.get()[12] ^ pi.get()[13] ^ pi.get()[16];
		a_theta[13] = pi.get()[13] ^ pi.get()[14] ^ pi.get()[0];
		a_theta[14] = pi.get()[14] ^ pi.get()[15] ^ pi.get()[1];
		a_theta[15] = pi.get()[15] ^ pi.get()[16] ^ pi.get()[2];
		a_theta[16] = pi.get()[16] ^ pi.get()[0] ^ pi.get()[3];
	} // end function GPT

private:
	shared_ptr<uint32_t> state, theta, gamma, pi, work_buffer;

	static char initialized;
	static shared_ptr<HashLibMatrixUInt32Array> stages;

	int32_t tap;

}; // end class Panama

char Panama::initialized = 0;
shared_ptr<HashLibMatrixUInt32Array> Panama::stages = make_shared<HashLibMatrixUInt32Array>(32);


#endif // !HLPPANAMA_H

