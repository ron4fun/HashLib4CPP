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
		state.resize(17);
		theta.resize(17);
		gamma.resize(17);
		pi.resize(17);
		work_buffer.resize(17);

		stages.resize(32);
		for (register uint32_t i = 0; i < 32; i++)
			stages[i] = HashLibUInt32Array(8);

	} // end constructor

	virtual IHash Clone() const
	{
		Panama HashInstance;

		HashInstance = Panama();
		HashInstance.state = state;
		HashInstance.theta = theta;
		HashInstance.gamma = gamma;
		HashInstance.pi = pi;

		HashInstance.stages = stages;

		HashInstance.tap = tap;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Panama>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		memset(&state[0], 0, 17 * sizeof(uint32_t));

		for (register uint32_t i = 0; i < 32; i++)
			memset(&stages[i][0], 0, 8 * sizeof(uint32_t));

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

			stages[tap25][0] = stages[tap25][0] ^ stages[tap][2];
			stages[tap25][1] = stages[tap25][1] ^ stages[tap][3];
			stages[tap25][2] = stages[tap25][2] ^ stages[tap][4];
			stages[tap25][3] = stages[tap25][3] ^ stages[tap][5];
			stages[tap25][4] = stages[tap25][4] ^ stages[tap][6];
			stages[tap25][5] = stages[tap25][5] ^ stages[tap][7];
			stages[tap25][6] = stages[tap25][6] ^ stages[tap][0];
			stages[tap25][7] = stages[tap25][7] ^ stages[tap][1];
			stages[tap][0] = stages[tap][0] ^ state[1];
			stages[tap][1] = stages[tap][1] ^ state[2];
			stages[tap][2] = stages[tap][2] ^ state[3];
			stages[tap][3] = stages[tap][3] ^ state[4];
			stages[tap][4] = stages[tap][4] ^ state[5];
			stages[tap][5] = stages[tap][5] ^ state[6];
			stages[tap][6] = stages[tap][6] ^ state[7];
			stages[tap][7] = stages[tap][7] ^ state[8];

			state[0] = theta[0] ^ 0x01;
			state[1] = theta[1] ^ stages[tap4][0];
			state[2] = theta[2] ^ stages[tap4][1];
			state[3] = theta[3] ^ stages[tap4][2];
			state[4] = theta[4] ^ stages[tap4][3];
			state[5] = theta[5] ^ stages[tap4][4];
			state[6] = theta[6] ^ stages[tap4][5];
			state[7] = theta[7] ^ stages[tap4][6];
			state[8] = theta[8] ^ stages[tap4][7];
			state[9] = theta[9] ^ stages[tap16][0];
			state[10] = theta[10] ^ stages[tap16][1];
			state[11] = theta[11] ^ stages[tap16][2];
			state[12] = theta[12] ^ stages[tap16][3];
			state[13] = theta[13] ^ stages[tap16][4];
			state[14] = theta[14] ^ stages[tap16][5];
			state[15] = theta[15] ^ stages[tap16][6];
			state[16] = theta[16] ^ stages[tap16][7];

		} // end for

	} // end function Finish

	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(8 * sizeof(uint32_t));

		Converters::le32_copy(&state[0] + 9, 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult

	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t tap16, tap25;
		
		Converters::le32_copy(a_data, a_index, &work_buffer[0], 0, 32);

		tap16 = (tap + 16) & 0x1F;

		tap = (tap - 1) & 0x1F;
		tap25 = (tap + 25) & 0x1F;

		GPT(&theta[0]);

		stages[tap25][0] = stages[tap25][0] ^ stages[tap][2];
		stages[tap25][1] = stages[tap25][1] ^ stages[tap][3];
		stages[tap25][2] = stages[tap25][2] ^ stages[tap][4];
		stages[tap25][3] = stages[tap25][3] ^ stages[tap][5];
		stages[tap25][4] = stages[tap25][4] ^ stages[tap][6];
		stages[tap25][5] = stages[tap25][5] ^ stages[tap][7];
		stages[tap25][6] = stages[tap25][6] ^ stages[tap][0];
		stages[tap25][7] = stages[tap25][7] ^ stages[tap][1];
		stages[tap][0] = stages[tap][0] ^ work_buffer[0];
		stages[tap][1] = stages[tap][1] ^ work_buffer[1];
		stages[tap][2] = stages[tap][2] ^ work_buffer[2];
		stages[tap][3] = stages[tap][3] ^ work_buffer[3];
		stages[tap][4] = stages[tap][4] ^ work_buffer[4];
		stages[tap][5] = stages[tap][5] ^ work_buffer[5];
		stages[tap][6] = stages[tap][6] ^ work_buffer[6];
		stages[tap][7] = stages[tap][7] ^ work_buffer[7];

		state[0] = theta[0] ^ 0x01;
		state[1] = theta[1] ^ work_buffer[0];
		state[2] = theta[2] ^ work_buffer[1];
		state[3] = theta[3] ^ work_buffer[2];
		state[4] = theta[4] ^ work_buffer[3];
		state[5] = theta[5] ^ work_buffer[4];
		state[6] = theta[6] ^ work_buffer[5];
		state[7] = theta[7] ^ work_buffer[6];
		state[8] = theta[8] ^ work_buffer[7];
		state[9] = theta[9] ^ stages[tap16][0];
		state[10] = theta[10] ^ stages[tap16][1];
		state[11] = theta[11] ^ stages[tap16][2];
		state[12] = theta[12] ^ stages[tap16][3];
		state[13] = theta[13] ^ stages[tap16][4];
		state[14] = theta[14] ^ stages[tap16][5];
		state[15] = theta[15] ^ stages[tap16][6];
		state[16] = theta[16] ^ stages[tap16][7];

		memset(&work_buffer[0], 0, 8 * sizeof(uint32_t));

	} // end function TransformBlock

private:
	inline void GPT(uint32_t *a_theta)
	{
		gamma[0] = state[0] ^ (state[1] | ~state[2]);
		gamma[1] = state[1] ^ (state[2] | ~state[3]);
		gamma[2] = state[2] ^ (state[3] | ~state[4]);
		gamma[3] = state[3] ^ (state[4] | ~state[5]);
		gamma[4] = state[4] ^ (state[5] | ~state[6]);
		gamma[5] = state[5] ^ (state[6] | ~state[7]);
		gamma[6] = state[6] ^ (state[7] | ~state[8]);
		gamma[7] = state[7] ^ (state[8] | ~state[9]);
		gamma[8] = state[8] ^ (state[9] | ~state[10]);
		gamma[9] = state[9] ^ (state[10] | ~state[11]);
		gamma[10] = state[10] ^ (state[11] | ~state[12]);
		gamma[11] = state[11] ^ (state[12] | ~state[13]);
		gamma[12] = state[12] ^ (state[13] | ~state[14]);
		gamma[13] = state[13] ^ (state[14] | ~state[15]);
		gamma[14] = state[14] ^ (state[15] | ~state[16]);
		gamma[15] = state[15] ^ (state[16] | ~state[0]);
		gamma[16] = state[16] ^ (state[0] | ~state[1]);

		pi[0] = gamma[0];
		pi[1] = Bits::RotateLeft32(gamma[7], 1);
		pi[2] = Bits::RotateLeft32(gamma[14], 3);
		pi[3] = Bits::RotateLeft32(gamma[4], 6);
		pi[4] = Bits::RotateLeft32(gamma[11], 10);
		pi[5] = Bits::RotateLeft32(gamma[1], 15);
		pi[6] = Bits::RotateLeft32(gamma[8], 21);
		pi[7] = Bits::RotateLeft32(gamma[15], 28);
		pi[8] = Bits::RotateLeft32(gamma[5], 4);
		pi[9] = Bits::RotateLeft32(gamma[12], 13);
		pi[10] = Bits::RotateLeft32(gamma[2], 23);
		pi[11] = Bits::RotateLeft32(gamma[9], 2);
		pi[12] = Bits::RotateLeft32(gamma[16], 14);
		pi[13] = Bits::RotateLeft32(gamma[6], 27);
		pi[14] = Bits::RotateLeft32(gamma[13], 9);
		pi[15] = Bits::RotateLeft32(gamma[3], 24);
		pi[16] = Bits::RotateLeft32(gamma[10], 8);

		a_theta[0] = pi[0] ^ pi[1] ^ pi[4];
		a_theta[1] = pi[1] ^ pi[2] ^ pi[5];
		a_theta[2] = pi[2] ^ pi[3] ^ pi[6];
		a_theta[3] = pi[3] ^ pi[4] ^ pi[7];
		a_theta[4] = pi[4] ^ pi[5] ^ pi[8];
		a_theta[5] = pi[5] ^ pi[6] ^ pi[9];
		a_theta[6] = pi[6] ^ pi[7] ^ pi[10];
		a_theta[7] = pi[7] ^ pi[8] ^ pi[11];
		a_theta[8] = pi[8] ^ pi[9] ^ pi[12];
		a_theta[9] = pi[9] ^ pi[10] ^ pi[13];
		a_theta[10] = pi[10] ^ pi[11] ^ pi[14];
		a_theta[11] = pi[11] ^ pi[12] ^ pi[15];
		a_theta[12] = pi[12] ^ pi[13] ^ pi[16];
		a_theta[13] = pi[13] ^ pi[14] ^ pi[0];
		a_theta[14] = pi[14] ^ pi[15] ^ pi[1];
		a_theta[15] = pi[15] ^ pi[16] ^ pi[2];
		a_theta[16] = pi[16] ^ pi[0] ^ pi[3];
	} // end function GPT

private:
	HashLibUInt32Array state, theta, gamma, pi, work_buffer;

	HashLibMatrixUInt32Array stages;

	int32_t tap;

}; // end class Panama


#endif // !HLPPANAMA_H

