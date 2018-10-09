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

#ifndef HLPBLAKE2S_H
#define HLPBLAKE2S_H

#include "Blake2SConfigurations\HlpBlake2SConfig.h"
#include "Blake2SConfigurations\HlpBlake2STreeConfig.h"
#include "Blake2SConfigurations\HlpBlake2SIvBuilder.h"
#include "../Interfaces/HlpIHashInfo.h"
#include "../Base/HlpHashSize.h"
#include "../Base/HlpHash.h"
#include "../Base/HlpConverters.h"
#include "../Base/HlpHashBuffer.h"
#include "../Base/HlpHashResult.h"
#include "../Utils/HlpBitConverter.h"
#include "../Utils/HlpHashLibTypes.h"
#include "../Utils/HlpUtils.h"


class Blake2S : public Hash, public IICryptoNotBuildIn, public IITransformBlock
{
public:
	Blake2S(const IBlake2SConfig config = DefaultConfig, const IBlake2STreeConfig treeConfig = nullptr)
		: Hash(0, 0)
	{
		IBlake2SConfig Lconfig;
		
		name = __func__;

		Lconfig = config;
		BlockSize = BlockSizeInBytes;
				
		rawConfig = Blake2SIvBuilder::ConfigS(Lconfig, treeConfig);
		if ((!Lconfig->GetKey().empty()) && (Lconfig->GetKey().size() != 0))
		{
			Key = Lconfig->GetKey();
			Key.resize(BlockSize);
		}

		FHashSize = Lconfig->GetHashSize();

		state.resize(8);
		m.resize(16);

		// Set the Inherited Hash variables
		hash_size = FHashSize;
		block_size = BlockSize;
	}

	virtual IHash Clone() const
	{
		Blake2S HashInstance = Blake2S(make_shared<Blake2SConfig>(FHashSize));
		HashInstance.m = m;
		HashInstance.rawConfig = rawConfig;
		HashInstance.state = state;
		HashInstance.Key = Key;
		HashInstance.buf = buf;
		
		HashInstance.bufferFilled = bufferFilled;
		HashInstance.counter0 = counter0;
		HashInstance.counter1 = counter1;
		HashInstance.finalizationFlag0 = finalizationFlag0;
		HashInstance.finalizationFlag1 = finalizationFlag1;

		IHash hash = make_shared<Blake2S>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

	virtual void Initialize()
	{
		register size_t i;
		
		if (rawConfig.empty()) 
			throw ArgumentNilHashLibException("config");

		if (rawConfig.size() != 8)
			throw ArgumentHashLibException(InvalidConfigLength);

		state[0] = IV0;
		state[1] = IV1;
		state[2] = IV2;
		state[3] = IV3;
		state[4] = IV4;
		state[5] = IV5;
		state[6] = IV6;
		state[7] = IV7;

		counter0 = 0;
		counter1 = 0;
		finalizationFlag0 = 0;
		finalizationFlag1 = 0;

		bufferFilled = 0;

		buf.resize(BlockSizeInBytes);

		memset(&buf[0], 0, buf.size() * sizeof(uint8_t));

		memset(&m[0], uint32_t(0), sizeof(m));
		
		for (i = 0; i < 8; i++) state[i] = state[i] ^ rawConfig[i];

		if (!Key.empty())
			TransformBytes(Key, 0, Key.size());
	}

	virtual void TransformBytes(const HashLibByteArray &a_data, const int32_t _a_index, const int32_t _a_data_length)
	{
		register size_t offset, bufferRemaining;
		int32_t a_index = _a_index, a_data_length = _a_data_length;

		offset = a_index;
		bufferRemaining = BlockSizeInBytes - bufferFilled;

		if ((bufferFilled > 0) && (a_data_length > bufferRemaining))
		{
			memmove(&buf[bufferFilled], &a_data[offset], bufferRemaining);
			counter0 = counter0 + uint32_t(BlockSizeInBytes);
			if (counter0 == 0)
				counter1++;
			
			Compress(&buf[0], 0);
			offset = offset + bufferRemaining;
			a_data_length = a_data_length - bufferRemaining;
			bufferFilled = 0;
		}

		while (a_data_length > BlockSizeInBytes)
		{
			counter0 = counter0 + uint32_t(BlockSizeInBytes);
			if (counter0 == 0)
				counter1++;
			
			Compress(&a_data[0], offset);
			offset = offset + BlockSizeInBytes;
			a_data_length = a_data_length - BlockSizeInBytes;
		}
		
		if (a_data_length > 0)
		{
			memmove(&buf[bufferFilled], &a_data[offset], a_data_length);
			bufferFilled = bufferFilled + a_data_length;
		}

	}

	virtual IHashResult TransformFinal()
	{
		HashLibByteArray tempRes;
		
		Finish();

		tempRes.resize(FHashSize);

		Converters::le32_copy(&state[0], 0, &tempRes[0], 0, tempRes.size());

		IHashResult result = make_shared<HashResult>(tempRes);

		Initialize();

		return result;
	}

protected:
	virtual string GetName() const
	{
		return Utils::string_format("%s_%u", name, FHashSize * 8);
	}	

private:
	void Compress(const uint8_t *block, const int32_t start)
	{
		register uint32_t m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, v0, v1,
			v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15;

		Converters::le32_copy(block, start, &m[0], 0, BlockSize);

		m0 = m[0];
		m1 = m[1];
		m2 = m[2];
		m3 = m[3];
		m4 = m[4];
		m5 = m[5];
		m6 = m[6];
		m7 = m[7];
		m8 = m[8];
		m9 = m[9];
		m10 = m[10];
		m11 = m[11];
		m12 = m[12];
		m13 = m[13];
		m14 = m[14];
		m15 = m[15];

		v0 = state[0];
		v1 = state[1];
		v2 = state[2];
		v3 = state[3];
		v4 = state[4];
		v5 = state[5];
		v6 = state[6];
		v7 = state[7];

		v8 = IV0;
		v9 = IV1;
		v10 = IV2;
		v11 = IV3;
		v12 = IV4 ^ counter0;
		v13 = IV5 ^ counter1;
		v14 = IV6 ^ finalizationFlag0;
		v15 = IV7 ^ finalizationFlag1;

		// Rounds
		// *
		// Round 1.
		v0 = v0 + m0;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 12);
		v1 = v1 + m2;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 12);
		v2 = v2 + m4;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 12);
		v3 = v3 + m6;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 12);
		v2 = v2 + m5;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 8);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 7);
		v3 = v3 + m7;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 8);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 7);
		v1 = v1 + m3;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 8);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 7);
		v0 = v0 + m1;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 8);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 7);
		v0 = v0 + m8;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 12);
		v1 = v1 + m10;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 12);
		v2 = v2 + m12;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 12);
		v3 = v3 + m14;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 12);
		v2 = v2 + m13;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 8);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 7);
		v3 = v3 + m15;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 8);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 7);
		v1 = v1 + m11;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 8);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 7);
		v0 = v0 + m9;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 8);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 7);

		// Round 2.
		v0 = v0 + m14;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 12);
		v1 = v1 + m4;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 12);
		v2 = v2 + m9;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 12);
		v3 = v3 + m13;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 12);
		v2 = v2 + m15;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 8);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 7);
		v3 = v3 + m6;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 8);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 7);
		v1 = v1 + m8;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 8);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 7);
		v0 = v0 + m10;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 8);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 7);
		v0 = v0 + m1;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 12);
		v1 = v1 + m0;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 12);
		v2 = v2 + m11;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 12);
		v3 = v3 + m5;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 12);
		v2 = v2 + m7;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 8);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 7);
		v3 = v3 + m3;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 8);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 7);
		v1 = v1 + m2;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 8);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 7);
		v0 = v0 + m12;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 8);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 7);

		// Round 3.
		v0 = v0 + m11;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 12);
		v1 = v1 + m12;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 12);
		v2 = v2 + m5;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 12);
		v3 = v3 + m15;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 12);
		v2 = v2 + m2;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 8);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 7);
		v3 = v3 + m13;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 8);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 7);
		v1 = v1 + m0;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 8);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 7);
		v0 = v0 + m8;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 8);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 7);
		v0 = v0 + m10;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 12);
		v1 = v1 + m3;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 12);
		v2 = v2 + m7;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 12);
		v3 = v3 + m9;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 12);
		v2 = v2 + m1;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 8);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 7);
		v3 = v3 + m4;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 8);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 7);
		v1 = v1 + m6;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 8);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 7);
		v0 = v0 + m14;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 8);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 7);

		// Round 4.
		v0 = v0 + m7;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 12);
		v1 = v1 + m3;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 12);
		v2 = v2 + m13;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 12);
		v3 = v3 + m11;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 12);
		v2 = v2 + m12;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 8);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 7);
		v3 = v3 + m14;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 8);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 7);
		v1 = v1 + m1;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 8);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 7);
		v0 = v0 + m9;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 8);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 7);
		v0 = v0 + m2;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 12);
		v1 = v1 + m5;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 12);
		v2 = v2 + m4;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 12);
		v3 = v3 + m15;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 12);
		v2 = v2 + m0;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 8);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 7);
		v3 = v3 + m8;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 8);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 7);
		v1 = v1 + m10;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 8);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 7);
		v0 = v0 + m6;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 8);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 7);

		// Round 5.
		v0 = v0 + m9;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 12);
		v1 = v1 + m5;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 12);
		v2 = v2 + m2;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 12);
		v3 = v3 + m10;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 12);
		v2 = v2 + m4;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 8);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 7);
		v3 = v3 + m15;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 8);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 7);
		v1 = v1 + m7;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 8);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 7);
		v0 = v0 + m0;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 8);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 7);
		v0 = v0 + m14;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 12);
		v1 = v1 + m11;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 12);
		v2 = v2 + m6;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 12);
		v3 = v3 + m3;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 12);
		v2 = v2 + m8;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 8);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 7);
		v3 = v3 + m13;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 8);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 7);
		v1 = v1 + m12;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 8);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 7);
		v0 = v0 + m1;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 8);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 7);

		// Round 6.
		v0 = v0 + m2;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 12);
		v1 = v1 + m6;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 12);
		v2 = v2 + m0;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 12);
		v3 = v3 + m8;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 12);
		v2 = v2 + m11;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 8);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 7);
		v3 = v3 + m3;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 8);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 7);
		v1 = v1 + m10;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 8);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 7);
		v0 = v0 + m12;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 8);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 7);
		v0 = v0 + m4;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 12);
		v1 = v1 + m7;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 12);
		v2 = v2 + m15;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 12);
		v3 = v3 + m1;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 12);
		v2 = v2 + m14;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 8);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 7);
		v3 = v3 + m9;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 8);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 7);
		v1 = v1 + m5;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 8);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 7);
		v0 = v0 + m13;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 8);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 7);

		// Round 7.
		v0 = v0 + m12;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 12);
		v1 = v1 + m1;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 12);
		v2 = v2 + m14;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 12);
		v3 = v3 + m4;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 12);
		v2 = v2 + m13;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 8);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 7);
		v3 = v3 + m10;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 8);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 7);
		v1 = v1 + m15;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 8);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 7);
		v0 = v0 + m5;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 8);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 7);
		v0 = v0 + m0;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 12);
		v1 = v1 + m6;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 12);
		v2 = v2 + m9;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 12);
		v3 = v3 + m8;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 12);
		v2 = v2 + m2;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 8);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 7);
		v3 = v3 + m11;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 8);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 7);
		v1 = v1 + m3;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 8);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 7);
		v0 = v0 + m7;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 8);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 7);

		// Round 8.
		v0 = v0 + m13;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 12);
		v1 = v1 + m7;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 12);
		v2 = v2 + m12;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 12);
		v3 = v3 + m3;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 12);
		v2 = v2 + m1;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 8);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 7);
		v3 = v3 + m9;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 8);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 7);
		v1 = v1 + m14;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 8);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 7);
		v0 = v0 + m11;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 8);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 7);
		v0 = v0 + m5;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 12);
		v1 = v1 + m15;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 12);
		v2 = v2 + m8;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 12);
		v3 = v3 + m2;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 12);
		v2 = v2 + m6;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 8);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 7);
		v3 = v3 + m10;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 8);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 7);
		v1 = v1 + m4;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 8);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 7);
		v0 = v0 + m0;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 8);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 7);

		// Round 9.
		v0 = v0 + m6;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 12);
		v1 = v1 + m14;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 12);
		v2 = v2 + m11;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 12);
		v3 = v3 + m0;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 12);
		v2 = v2 + m3;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 8);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 7);
		v3 = v3 + m8;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 8);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 7);
		v1 = v1 + m9;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 8);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 7);
		v0 = v0 + m15;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 8);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 7);
		v0 = v0 + m12;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 12);
		v1 = v1 + m13;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 12);
		v2 = v2 + m1;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 12);
		v3 = v3 + m10;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 12);
		v2 = v2 + m4;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 8);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 7);
		v3 = v3 + m5;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 8);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 7);
		v1 = v1 + m7;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 8);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 7);
		v0 = v0 + m2;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 8);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 7);

		// Round 10.
		v0 = v0 + m10;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 12);
		v1 = v1 + m8;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 12);
		v2 = v2 + m7;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 12);
		v3 = v3 + m1;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 12);
		v2 = v2 + m6;
		v2 = v2 + v6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight32(v14, 8);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight32(v6, 7);
		v3 = v3 + m5;
		v3 = v3 + v7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight32(v15, 8);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight32(v7, 7);
		v1 = v1 + m4;
		v1 = v1 + v5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight32(v13, 8);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight32(v5, 7);
		v0 = v0 + m2;
		v0 = v0 + v4;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight32(v12, 8);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight32(v4, 7);
		v0 = v0 + m15;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 12);
		v1 = v1 + m9;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 12);
		v2 = v2 + m3;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 12);
		v3 = v3 + m13;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 12);
		v2 = v2 + m12;
		v2 = v2 + v7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight32(v13, 8);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight32(v7, 7);
		v3 = v3 + m0;
		v3 = v3 + v4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight32(v14, 8);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight32(v4, 7);
		v1 = v1 + m14;
		v1 = v1 + v6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight32(v12, 8);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight32(v6, 7);
		v0 = v0 + m11;
		v0 = v0 + v5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight32(v15, 8);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight32(v5, 7);
		// */
		// Finalization

		state[0]  = state[0] ^ (v0 ^ v8);
		state[1]  = state[1] ^ (v1 ^ v9);
		state[2]  = state[2] ^ (v2 ^ v10);
		state[3]  = state[3] ^ (v3 ^ v11);
		state[4]  = state[4] ^ (v4 ^ v12);
		state[5]  = state[5] ^ (v5 ^ v13);
		state[6]  = state[6] ^ (v6 ^ v14);
		state[7]  = state[7] ^ (v7 ^ v15);

	}

	inline void Finish()
	{
		// Last compression

		counter0 = counter0 + uint32_t(bufferFilled);

		finalizationFlag0 = UINT32_MAX;

		memset(&buf[bufferFilled], 0, buf.size() - bufferFilled);

		Compress(&buf[0], 0);
	}

private:
	HashLibUInt32Array m, rawConfig, state;
	HashLibByteArray Key, buf;
	int32_t bufferFilled, FHashSize, BlockSize;
	uint32_t counter0, counter1, finalizationFlag0, finalizationFlag1;
	
private:
	static IBlake2SConfig fillDefaultConfig()
	{
		return make_shared<Blake2SConfig>();
	}

	static const int32_t BlockSizeInBytes = int32_t(64);

	static const uint32_t IV0 = uint32_t(0x66A09E667);
	static const uint32_t IV1 = uint32_t(0xBB67AE85);
	static const uint32_t IV2 = uint32_t(0x3C6EF372);
	static const uint32_t IV3 = uint32_t(0xA54FF53A);
	static const uint32_t IV4 = uint32_t(0x510E527F);
	static const uint32_t IV5 = uint32_t(0x9B05688C);
	static const uint32_t IV6 = uint32_t(0x1F83D9AB);
	static const uint32_t IV7 = uint32_t(0x5BE0CD19);

	static const char *InvalidConfigLength;

	static IBlake2SConfig DefaultConfig;

}; // end class Blake2S


IBlake2SConfig Blake2S::DefaultConfig = Blake2S::fillDefaultConfig();

const char *Blake2S::InvalidConfigLength = "Config Length Must Be 8 Words";


#endif // !HLPBLAKE2S_H