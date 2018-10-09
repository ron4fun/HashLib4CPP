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

#ifndef HLPBLAKE2B_H
#define HLPBLAKE2B_H

#include "Blake2BConfigurations\HlpBlake2BConfig.h"
#include "Blake2BConfigurations\HlpBlake2BTreeConfig.h"
#include "Blake2BConfigurations\HlpBlake2BIvBuilder.h"
#include "../Interfaces/HlpIHashInfo.h"
#include "../Base/HlpHashSize.h"
#include "../Base/HlpHash.h"
#include "../Base/HlpConverters.h"
#include "../Base/HlpHashBuffer.h"
#include "../Base/HlpHashResult.h"
#include "../Utils/HlpBitConverter.h"
#include "../Utils/HlpHashLibTypes.h"
#include "../Utils/HlpUtils.h"


class Blake2B : public Hash, public IICryptoNotBuildIn, public IITransformBlock
{
public:
	Blake2B(const IBlake2BConfig config = DefaultConfig, const IBlake2BTreeConfig treeConfig = nullptr)
		: Hash(0, 0)
	{
		IBlake2BConfig Lconfig;

		name = __func__;

		Lconfig = config;
		BlockSize = BlockSizeInBytes;

		rawConfig = Blake2BIvBuilder::ConfigB(Lconfig, treeConfig);
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
		Blake2B HashInstance = Blake2B(make_shared<Blake2BConfig>(FHashSize));
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

		IHash hash = make_shared<Blake2B>(HashInstance);
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

		memset(&m[0], uint64_t(0), sizeof(m));
		
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
			counter0 = counter0 + BlockSizeInBytes;
			if (counter0 == 0)
				counter1++;

			Compress(&buf[0], 0);
			offset = offset + bufferRemaining;
			a_data_length = a_data_length - bufferRemaining;
			bufferFilled = 0;
		}

		while (a_data_length > BlockSizeInBytes)
		{
			counter0 = counter0 + BlockSizeInBytes;
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

		Converters::le64_copy(&state[0], 0, &tempRes[0], 0, tempRes.size());

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
		register uint64_t m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, v0, v1,
			v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15;

		Converters::le64_copy(block, start, &m[0], 0, BlockSize);

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

		// ##### Round(0)
		// G(0, 0, v0, v4, v8, v12)
		v0 = v0 + v4 + m0;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 32);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 24);
		v0 = v0 + v4 + m1;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 63);

		// G(0, 1, v1, v5, v9, v13)
		v1 = v1 + v5 + m2;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 32);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 24);
		v1 = v1 + v5 + m3;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 63);

		// G(0, 2, v2, v6, v10, v14)
		v2 = v2 + v6 + m4;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 32);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 24);
		v2 = v2 + v6 + m5;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 63);

		// G(0, 3, v3, v7, v11, v15)
		v3 = v3 + v7 + m6;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 32);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 24);
		v3 = v3 + v7 + m7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 63);

		// G(0, 4, v0, v5, v10, v15)
		v0 = v0 + v5 + m8;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 32);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 24);
		v0 = v0 + v5 + m9;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 63);

		// G(0, 5, v1, v6, v11, v12)
		v1 = v1 + v6 + m10;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 32);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 24);
		v1 = v1 + v6 + m11;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 63);

		// G(0, 6, v2, v7, v8, v13)
		v2 = v2 + v7 + m12;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 32);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 24);
		v2 = v2 + v7 + m13;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 63);

		// G(0, 7, v3, v4, v9, v14)
		v3 = v3 + v4 + m14;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 32);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 24);
		v3 = v3 + v4 + m15;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 63);

		// ##### Round(1)
		// G(1, 0, v0, v4, v8, v12)
		v0 = v0 + v4 + m14;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 32);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 24);
		v0 = v0 + v4 + m10;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 63);

		// G(1, 1, v1, v5, v9, v13)
		v1 = v1 + v5 + m4;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 32);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 24);
		v1 = v1 + v5 + m8;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 63);

		// G(1, 2, v2, v6, v10, v14)
		v2 = v2 + v6 + m9;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 32);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 24);
		v2 = v2 + v6 + m15;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 63);

		// G(1, 3, v3, v7, v11, v15)
		v3 = v3 + v7 + m13;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 32);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 24);
		v3 = v3 + v7 + m6;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 63);

		// G(1, 4, v0, v5, v10, v15)
		v0 = v0 + v5 + m1;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 32);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 24);
		v0 = v0 + v5 + m12;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 63);

		// G(1, 5, v1, v6, v11, v12)
		v1 = v1 + v6 + m0;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 32);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 24);
		v1 = v1 + v6 + m2;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 63);

		// G(1, 6, v2, v7, v8, v13)
		v2 = v2 + v7 + m11;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 32);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 24);
		v2 = v2 + v7 + m7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 63);

		// G(1, 7, v3, v4, v9, v14)
		v3 = v3 + v4 + m5;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 32);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 24);
		v3 = v3 + v4 + m3;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 63);

		// ##### Round(2)
		// G(2, 0, v0, v4, v8, v12)
		v0 = v0 + v4 + m11;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 32);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 24);
		v0 = v0 + v4 + m8;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 63);

		// G(2, 1, v1, v5, v9, v13)
		v1 = v1 + v5 + m12;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 32);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 24);
		v1 = v1 + v5 + m0;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 63);

		// G(2, 2, v2, v6, v10, v14)
		v2 = v2 + v6 + m5;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 32);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 24);
		v2 = v2 + v6 + m2;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 63);

		// G(2, 3, v3, v7, v11, v15)
		v3 = v3 + v7 + m15;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 32);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 24);
		v3 = v3 + v7 + m13;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 63);

		// G(2, 4, v0, v5, v10, v15)
		v0 = v0 + v5 + m10;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 32);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 24);
		v0 = v0 + v5 + m14;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 63);

		// G(2, 5, v1, v6, v11, v12)
		v1 = v1 + v6 + m3;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 32);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 24);
		v1 = v1 + v6 + m6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 63);

		// G(2, 6, v2, v7, v8, v13)
		v2 = v2 + v7 + m7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 32);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 24);
		v2 = v2 + v7 + m1;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 63);

		// G(2, 7, v3, v4, v9, v14)
		v3 = v3 + v4 + m9;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 32);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 24);
		v3 = v3 + v4 + m4;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 63);

		// ##### Round(3)
		// G(3, 0, v0, v4, v8, v12)
		v0 = v0 + v4 + m7;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 32);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 24);
		v0 = v0 + v4 + m9;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 63);

		// G(3, 1, v1, v5, v9, v13)
		v1 = v1 + v5 + m3;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 32);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 24);
		v1 = v1 + v5 + m1;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 63);

		// G(3, 2, v2, v6, v10, v14)
		v2 = v2 + v6 + m13;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 32);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 24);
		v2 = v2 + v6 + m12;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 63);

		// G(3, 3, v3, v7, v11, v15)
		v3 = v3 + v7 + m11;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 32);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 24);
		v3 = v3 + v7 + m14;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 63);

		// G(3, 4, v0, v5, v10, v15)
		v0 = v0 + v5 + m2;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 32);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 24);
		v0 = v0 + v5 + m6;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 63);

		// G(3, 5, v1, v6, v11, v12)
		v1 = v1 + v6 + m5;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 32);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 24);
		v1 = v1 + v6 + m10;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 63);

		// G(3, 6, v2, v7, v8, v13)
		v2 = v2 + v7 + m4;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 32);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 24);
		v2 = v2 + v7 + m0;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 63);

		// G(3, 7, v3, v4, v9, v14)
		v3 = v3 + v4 + m15;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 32);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 24);
		v3 = v3 + v4 + m8;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 63);

		// ##### Round(4)
		// G(4, 0, v0, v4, v8, v12)
		v0 = v0 + v4 + m9;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 32);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 24);
		v0 = v0 + v4 + m0;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 63);

		// G(4, 1, v1, v5, v9, v13)
		v1 = v1 + v5 + m5;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 32);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 24);
		v1 = v1 + v5 + m7;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 63);

		// G(4, 2, v2, v6, v10, v14)
		v2 = v2 + v6 + m2;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 32);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 24);
		v2 = v2 + v6 + m4;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 63);

		// G(4, 3, v3, v7, v11, v15)
		v3 = v3 + v7 + m10;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 32);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 24);
		v3 = v3 + v7 + m15;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 63);

		// G(4, 4, v0, v5, v10, v15)
		v0 = v0 + v5 + m14;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 32);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 24);
		v0 = v0 + v5 + m1;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 63);

		// G(4, 5, v1, v6, v11, v12)
		v1 = v1 + v6 + m11;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 32);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 24);
		v1 = v1 + v6 + m12;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 63);

		// G(4, 6, v2, v7, v8, v13)
		v2 = v2 + v7 + m6;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 32);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 24);
		v2 = v2 + v7 + m8;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 63);

		// G(4, 7, v3, v4, v9, v14)
		v3 = v3 + v4 + m3;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 32);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 24);
		v3 = v3 + v4 + m13;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 63);

		// ##### Round(5)
		// G(5, 0, v0, v4, v8, v12)
		v0 = v0 + v4 + m2;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 32);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 24);
		v0 = v0 + v4 + m12;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 63);

		// G(5, 1, v1, v5, v9, v13)
		v1 = v1 + v5 + m6;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 32);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 24);
		v1 = v1 + v5 + m10;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 63);

		// G(5, 2, v2, v6, v10, v14)
		v2 = v2 + v6 + m0;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 32);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 24);
		v2 = v2 + v6 + m11;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 63);

		// G(5, 3, v3, v7, v11, v15)
		v3 = v3 + v7 + m8;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 32);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 24);
		v3 = v3 + v7 + m3;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 63);

		// G(5, 4, v0, v5, v10, v15)
		v0 = v0 + v5 + m4;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 32);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 24);
		v0 = v0 + v5 + m13;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 63);

		// G(5, 5, v1, v6, v11, v12)
		v1 = v1 + v6 + m7;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 32);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 24);
		v1 = v1 + v6 + m5;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 63);

		// G(5, 6, v2, v7, v8, v13)
		v2 = v2 + v7 + m15;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 32);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 24);
		v2 = v2 + v7 + m14;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 63);

		// G(5, 7, v3, v4, v9, v14)
		v3 = v3 + v4 + m1;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 32);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 24);
		v3 = v3 + v4 + m9;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 63);

		// ##### Round(6)
		// G(6, 0, v0, v4, v8, v12)
		v0 = v0 + v4 + m12;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 32);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 24);
		v0 = v0 + v4 + m5;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 63);

		// G(6, 1, v1, v5, v9, v13)
		v1 = v1 + v5 + m1;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 32);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 24);
		v1 = v1 + v5 + m15;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 63);

		// G(6, 2, v2, v6, v10, v14)
		v2 = v2 + v6 + m14;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 32);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 24);
		v2 = v2 + v6 + m13;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 63);

		// G(6, 3, v3, v7, v11, v15)
		v3 = v3 + v7 + m4;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 32);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 24);
		v3 = v3 + v7 + m10;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 63);

		// G(6, 4, v0, v5, v10, v15)
		v0 = v0 + v5 + m0;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 32);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 24);
		v0 = v0 + v5 + m7;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 63);

		// G(6, 5, v1, v6, v11, v12)
		v1 = v1 + v6 + m6;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 32);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 24);
		v1 = v1 + v6 + m3;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 63);

		// G(6, 6, v2, v7, v8, v13)
		v2 = v2 + v7 + m9;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 32);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 24);
		v2 = v2 + v7 + m2;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 63);

		// G(6, 7, v3, v4, v9, v14)
		v3 = v3 + v4 + m8;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 32);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 24);
		v3 = v3 + v4 + m11;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 63);

		// ##### Round(7)
		// G(7, 0, v0, v4, v8, v12)
		v0 = v0 + v4 + m13;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 32);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 24);
		v0 = v0 + v4 + m11;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 63);

		// G(7, 1, v1, v5, v9, v13)
		v1 = v1 + v5 + m7;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 32);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 24);
		v1 = v1 + v5 + m14;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 63);

		// G(7, 2, v2, v6, v10, v14)
		v2 = v2 + v6 + m12;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 32);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 24);
		v2 = v2 + v6 + m1;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 63);

		// G(7, 3, v3, v7, v11, v15)
		v3 = v3 + v7 + m3;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 32);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 24);
		v3 = v3 + v7 + m9;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 63);

		// G(7, 4, v0, v5, v10, v15)
		v0 = v0 + v5 + m5;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 32);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 24);
		v0 = v0 + v5 + m0;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 63);

		// G(7, 5, v1, v6, v11, v12)
		v1 = v1 + v6 + m15;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 32);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 24);
		v1 = v1 + v6 + m4;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 63);

		// G(7, 6, v2, v7, v8, v13)
		v2 = v2 + v7 + m8;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 32);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 24);
		v2 = v2 + v7 + m6;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 63);

		// G(7, 7, v3, v4, v9, v14)
		v3 = v3 + v4 + m2;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 32);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 24);
		v3 = v3 + v4 + m10;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 63);

		// ##### Round(8)
		// G(8, 0, v0, v4, v8, v12)
		v0 = v0 + v4 + m6;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 32);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 24);
		v0 = v0 + v4 + m15;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 63);

		// G(8, 1, v1, v5, v9, v13)
		v1 = v1 + v5 + m14;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 32);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 24);
		v1 = v1 + v5 + m9;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 63);

		// G(8, 2, v2, v6, v10, v14)
		v2 = v2 + v6 + m11;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 32);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 24);
		v2 = v2 + v6 + m3;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 63);

		// G(8, 3, v3, v7, v11, v15)
		v3 = v3 + v7 + m0;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 32);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 24);
		v3 = v3 + v7 + m8;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 63);

		// G(8, 4, v0, v5, v10, v15)
		v0 = v0 + v5 + m12;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 32);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 24);
		v0 = v0 + v5 + m2;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 63);

		// G(8, 5, v1, v6, v11, v12)
		v1 = v1 + v6 + m13;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 32);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 24);
		v1 = v1 + v6 + m7;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 63);

		// G(8, 6, v2, v7, v8, v13)
		v2 = v2 + v7 + m1;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 32);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 24);
		v2 = v2 + v7 + m4;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 63);

		// G(8, 7, v3, v4, v9, v14)
		v3 = v3 + v4 + m10;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 32);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 24);
		v3 = v3 + v4 + m5;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 63);

		// ##### Round(9)
		// G(9, 0, v0, v4, v8, v12)
		v0 = v0 + v4 + m10;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 32);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 24);
		v0 = v0 + v4 + m2;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 63);

		// G(9, 1, v1, v5, v9, v13)
		v1 = v1 + v5 + m8;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 32);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 24);
		v1 = v1 + v5 + m4;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 63);

		// G(9, 2, v2, v6, v10, v14)
		v2 = v2 + v6 + m7;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 32);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 24);
		v2 = v2 + v6 + m6;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 63);

		// G(9, 3, v3, v7, v11, v15)
		v3 = v3 + v7 + m1;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 32);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 24);
		v3 = v3 + v7 + m5;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 63);

		// G(9, 4, v0, v5, v10, v15)
		v0 = v0 + v5 + m15;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 32);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 24);
		v0 = v0 + v5 + m11;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 63);

		// G(9, 5, v1, v6, v11, v12)
		v1 = v1 + v6 + m9;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 32);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 24);
		v1 = v1 + v6 + m14;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 63);

		// G(9, 6, v2, v7, v8, v13)
		v2 = v2 + v7 + m3;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 32);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 24);
		v2 = v2 + v7 + m12;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 63);

		// G(9, 7, v3, v4, v9, v14)
		v3 = v3 + v4 + m13;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 32);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 24);
		v3 = v3 + v4 + m0;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 63);

		// ##### Round(10)
		// G(10, 0, v0, v4, v8, v12)
		v0 = v0 + v4 + m0;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 32);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 24);
		v0 = v0 + v4 + m1;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 63);

		// G(10, 1, v1, v5, v9, v13)
		v1 = v1 + v5 + m2;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 32);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 24);
		v1 = v1 + v5 + m3;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 63);

		// G(10, 2, v2, v6, v10, v14)
		v2 = v2 + v6 + m4;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 32);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 24);
		v2 = v2 + v6 + m5;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 63);

		// G(10, 3, v3, v7, v11, v15)
		v3 = v3 + v7 + m6;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 32);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 24);
		v3 = v3 + v7 + m7;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 63);

		// G(10, 4, v0, v5, v10, v15)
		v0 = v0 + v5 + m8;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 32);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 24);
		v0 = v0 + v5 + m9;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 63);

		// G(10, 5, v1, v6, v11, v12)
		v1 = v1 + v6 + m10;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 32);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 24);
		v1 = v1 + v6 + m11;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 63);

		// G(10, 6, v2, v7, v8, v13)
		v2 = v2 + v7 + m12;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 32);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 24);
		v2 = v2 + v7 + m13;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 63);

		// G(10, 7, v3, v4, v9, v14)
		v3 = v3 + v4 + m14;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 32);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 24);
		v3 = v3 + v4 + m15;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 63);

		// ##### Round(11)
		// G(11, 0, v0, v4, v8, v12)
		v0 = v0 + v4 + m14;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 32);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 24);
		v0 = v0 + v4 + m10;
		v12 = v12 ^ v0;
		v12 = Bits::RotateRight64(v12, 16);
		v8 = v8 + v12;
		v4 = v4 ^ v8;
		v4 = Bits::RotateRight64(v4, 63);

		// G(11, 1, v1, v5, v9, v13)
		v1 = v1 + v5 + m4;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 32);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 24);
		v1 = v1 + v5 + m8;
		v13 = v13 ^ v1;
		v13 = Bits::RotateRight64(v13, 16);
		v9 = v9 + v13;
		v5 = v5 ^ v9;
		v5 = Bits::RotateRight64(v5, 63);

		// G(11, 2, v2, v6, v10, v14)
		v2 = v2 + v6 + m9;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 32);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 24);
		v2 = v2 + v6 + m15;
		v14 = v14 ^ v2;
		v14 = Bits::RotateRight64(v14, 16);
		v10 = v10 + v14;
		v6 = v6 ^ v10;
		v6 = Bits::RotateRight64(v6, 63);

		// G(11, 3, v3, v7, v11, v15)
		v3 = v3 + v7 + m13;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 32);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 24);
		v3 = v3 + v7 + m6;
		v15 = v15 ^ v3;
		v15 = Bits::RotateRight64(v15, 16);
		v11 = v11 + v15;
		v7 = v7 ^ v11;
		v7 = Bits::RotateRight64(v7, 63);

		// G(11, 4, v0, v5, v10, v15)
		v0 = v0 + v5 + m1;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 32);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 24);
		v0 = v0 + v5 + m12;
		v15 = v15 ^ v0;
		v15 = Bits::RotateRight64(v15, 16);
		v10 = v10 + v15;
		v5 = v5 ^ v10;
		v5 = Bits::RotateRight64(v5, 63);

		// G(11, 5, v1, v6, v11, v12)
		v1 = v1 + v6 + m0;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 32);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 24);
		v1 = v1 + v6 + m2;
		v12 = v12 ^ v1;
		v12 = Bits::RotateRight64(v12, 16);
		v11 = v11 + v12;
		v6 = v6 ^ v11;
		v6 = Bits::RotateRight64(v6, 63);

		// G(11, 6, v2, v7, v8, v13)
		v2 = v2 + v7 + m11;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 32);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 24);
		v2 = v2 + v7 + m7;
		v13 = v13 ^ v2;
		v13 = Bits::RotateRight64(v13, 16);
		v8 = v8 + v13;
		v7 = v7 ^ v8;
		v7 = Bits::RotateRight64(v7, 63);

		// G(11, 7, v3, v4, v9, v14)
		v3 = v3 + v4 + m5;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 32);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 24);
		v3 = v3 + v4 + m3;
		v14 = v14 ^ v3;
		v14 = Bits::RotateRight64(v14, 16);
		v9 = v9 + v14;
		v4 = v4 ^ v9;
		v4 = Bits::RotateRight64(v4, 63);

		// Finalization
		state[0] = state[0] ^ (v0 ^ v8);
		state[1] = state[1] ^ (v1 ^ v9);
		state[2] = state[2] ^ (v2 ^ v10);
		state[3] = state[3] ^ (v3 ^ v11);
		state[4] = state[4] ^ (v4 ^ v12);
		state[5] = state[5] ^ (v5 ^ v13);
		state[6] = state[6] ^ (v6 ^ v14);
		state[7] = state[7] ^ (v7 ^ v15);

	}

	inline void Finish()
	{
		// Last compression

		counter0 = counter0 + uint64_t(bufferFilled);

		finalizationFlag0 = UINT64_MAX;

		memset(&buf[bufferFilled], 0, buf.size() - bufferFilled);

		Compress(&buf[0], 0);
	}

private:
	HashLibUInt64Array m, rawConfig, state;
	HashLibByteArray Key, buf;
	int32_t bufferFilled, FHashSize, BlockSize;
	uint64_t counter0, counter1, finalizationFlag0, finalizationFlag1;

private:
	static IBlake2BConfig fillDefaultConfig()
	{
		return make_shared<Blake2BConfig>();
	}

	static const int32_t BlockSizeInBytes = int32_t(128);

	static const uint64_t IV0 = uint64_t(0x6A09E667F3BCC908);
	static const uint64_t IV1 = uint64_t(0xBB67AE8584CAA73B);
	static const uint64_t IV2 = uint64_t(0x3C6EF372FE94F82B);
	static const uint64_t IV3 = uint64_t(0xA54FF53A5F1D36F1);
	static const uint64_t IV4 = uint64_t(0x510E527FADE682D1);
	static const uint64_t IV5 = uint64_t(0x9B05688C2B3E6C1F);
	static const uint64_t IV6 = uint64_t(0x1F83D9ABFB41BD6B);
	static const uint64_t IV7 = uint64_t(0x5BE0CD19137E2179);

	static const char *InvalidConfigLength;

	static IBlake2BConfig DefaultConfig;

}; // end class Blake2B


IBlake2BConfig Blake2B::DefaultConfig = Blake2B::fillDefaultConfig();

const char *Blake2B::InvalidConfigLength = "Config Length Must Be 8 Words";


#endif // !HLPBLAKE2B_H