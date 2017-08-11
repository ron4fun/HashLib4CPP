#ifndef HLPGOST_H
#define HLPGOST_H

#include "../Base/HlpHashCryptoNotBuildIn.h"


class Gost : public BlockHash, public IICryptoNotBuildIn, public IITransformBlock
{
public:
	Gost()
		: BlockHash(32, 32)
	{
		name = __func__;

		state = shared_ptr<uint32_t>(new uint32_t[8], default_delete<uint32_t[]>());
		hash = shared_ptr<uint32_t>(new uint32_t[8], default_delete<uint32_t[]>());
		data = shared_ptr<uint32_t>(new uint32_t[8], default_delete<uint32_t[]>());
		m = shared_ptr<uint32_t>(new uint32_t[8], default_delete<uint32_t[]>());
		s = shared_ptr<uint32_t>(new uint32_t[8], default_delete<uint32_t[]>());

	
		if (initialized != 'I')
		{
			register uint32_t ax, bx, cx, dx;

			HashLibMatrixUInt32Array sbox = HashLibMatrixUInt32Array({ HashLibUInt32Array({ 4, 10, 9,
				2, 13, 8, 0, 14, 6, 11, 1, 12, 7, 15, 5, 3 }), HashLibUInt32Array({ 14,
					11, 4, 12, 6, 13, 15, 10, 2, 3, 8, 1, 0, 7, 5, 9 }),
				HashLibUInt32Array({ 5, 8, 1, 13, 10, 3, 4, 2, 14, 15, 12, 7, 6, 0, 9,
					11 }), HashLibUInt32Array({ 7, 13, 10, 1, 0, 8, 9, 15, 14, 4, 6, 12, 11,
						2, 5, 3 }), HashLibUInt32Array({ 6, 12, 7, 1, 5, 15, 13, 8, 4, 10, 9,
							14, 0, 3, 11, 2 }), HashLibUInt32Array({ 4, 11, 10, 0, 7, 2, 1, 13, 3,
								6, 8, 5, 9, 12, 15, 14 }), HashLibUInt32Array({ 13, 11, 4, 1, 3, 15, 5,
									9, 0, 10, 14, 7, 6, 8, 2, 12 }), HashLibUInt32Array({ 1, 15, 13, 0, 5,
										7, 10, 4, 9, 2, 3, 14, 6, 11, 8, 12 }) });

			register uint32_t i = 0;

			for (register uint32_t a = 0; a < 16; a++)
			{
				ax = sbox[1][a] << 15;
				bx = sbox[3][a] << 23;
				cx = sbox[5][a];
				cx = Bits::RotateRight32(cx, 1);
				dx = sbox[7][a] << 7;

				for (register uint32_t b = 0; b < 16; b++)
				{
					Gost::sbox1.get()[i] = ax | (sbox[0][b] << 11);
					Gost::sbox2.get()[i] = bx | (sbox[2][b] << 19);
					Gost::sbox3.get()[i] = cx | (sbox[4][b] << 27);
					Gost::sbox4.get()[i] = dx | (sbox[6][b] << 3);
					i++;
				} // end for
			} // end for
			
			initialized = 'I';
		} // end if
	} // end constructor

	~Gost()
	{} // end destructor

	virtual void Initialize()
	{
		memset(&state.get()[0], 0, 8 * sizeof(uint32_t));
		memset(&hash.get()[0], 0, 8 * sizeof(uint32_t));

		BlockHash::Initialize();
	} // end function Initialize

private:
	inline void Compress(uint32_t *a_m)
	{
		register uint32_t u0, u1, u2, u3, u4, u5, u6, u7, v0, v1, v2, v3, v4, v5, v6, v7, w0, w1, w2,
			w3, w4, w5, w6, w7, key0, key1, key2, key3, key4, key5, key6, key7, r, l, t;

		u0  = hash.get()[0];
		u1 = hash.get()[1];
		u2 = hash.get()[2];
		u3 = hash.get()[3];
		u4 = hash.get()[4];
		u5 = hash.get()[5];
		u6 = hash.get()[6];
		u7 = hash.get()[7];

		v0 = a_m[0];
		v1 = a_m[1];
		v2 = a_m[2];
		v3 = a_m[3];
		v4 = a_m[4];
		v5 = a_m[5];
		v6 = a_m[6];
		v7 = a_m[7];

		register uint32_t i = 0;

		while (i < 8)
		{
			w0 = u0 ^ v0;
			w1 = u1 ^ v1;
			w2 = u2 ^ v2;
			w3 = u3 ^ v3;
			w4 = u4 ^ v4;
			w5 = u5 ^ v5;
			w6 = u6 ^ v6;
			w7 = u7 ^ v7;

			key0 = uint32_t(uint8_t(w0)) | (uint32_t(uint8_t(w2)) << 8) |
				(uint32_t(uint8_t(w4)) << 16) | (uint32_t(uint8_t(w6)) << 24);
			key1 = uint32_t(uint8_t(w0 >> 8)) | (w2 & 0x0000FF00) |
				((w4 & 0x0000FF00) << 8) | ((w6 & 0x0000FF00) << 16);
			key2 = uint32_t(uint8_t(w0 >> 16)) | ((w2 & 0x00FF0000) >> 8) |
				(w4 & 0x00FF0000) | ((w6 & 0x00FF0000) << 8);
			key3 = (w0 >> 24) | ((w2 & 0xFF000000) >> 16) |
				((w4 & 0xFF000000) >> 8) | (w6 & 0xFF000000);
			key4 = uint32_t(uint8_t(w1)) | ((w3 & 0x000000FF) << 8) |
				((w5 & 0x000000FF) << 16) | ((w7 & 0x000000FF) << 24);
			key5 = uint32_t(uint8_t(w1 >> 8)) | (w3 & 0x0000FF00) |
				((w5 & 0x0000FF00) << 8) | ((w7 & 0x0000FF00) << 16);
			key6 = uint32_t(uint8_t(w1 >> 16)) | ((w3 & 0x00FF0000) >> 8) |
				(w5 & 0x00FF0000) | ((w7 & 0x00FF0000) << 8);
			key7 = (w1 >> 24) | ((w3 & 0xFF000000) >> 16) |
				((w5 & 0xFF000000) >> 8) | (w7 & 0xFF000000);

			r = hash.get()[i];
			l = hash.get()[i + 1];

			t = key0 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key1 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key2 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key3 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key4 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key5 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key6 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key7 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key0 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key1 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key2 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key3 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key4 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key5 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key6 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key7 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key0 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key1 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key2 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key3 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key4 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key5 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key6 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key7 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key7 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key6 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key5 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key4 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key3 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key2 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key1 + r;
			l = l ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);
			t = key0 + l;
			r = r ^ (sbox1.get()[uint8_t(t)] ^ sbox2.get()[uint8_t(t >> 8)] ^ sbox3.get()
				[uint8_t(t >> 16)] ^ sbox4.get()[t >> 24]);

			t = r;
			r = l;
			l = t;
				
			s.get()[i] = r;
			s.get()[i + 1] = l;

			if (i == 6)
				break;

			l = u0 ^ u2;
			r = u1 ^ u3;
			u0 = u2;
			u1 = u3;
			u2 = u4;
			u3 = u5;
			u4 = u6;
			u5 = u7;
			u6 = l;
			u7 = r;

			if (i == 2)
			{
				u0 = u0 ^ 0xFF00FF00;
				u1 = u1 ^ 0xFF00FF00;
				u2 = u2 ^ 0x00FF00FF;
				u3 = u3 ^ 0x00FF00FF;
				u4 = u4 ^ 0x00FFFF00;
				u5 = u5 ^ 0xFF0000FF;
				u6 = u6 ^ 0x000000FF;
				u7 = u7 ^ 0xFF00FFFF;
			} // end if

			l = v0;
			r = v2;
			v0 = v4;
			v2 = v6;
			v4 = l ^ r;
			v6 = v0 ^ r;
			l = v1;
			r = v3;
			v1 = v5;
			v3 = v7;
			v5 = l ^ r;
			v7 = v1 ^ r;

			i += 2;
		} // end while

		u0 = a_m[0] ^ s.get()[6];
		u1 = a_m[1] ^ s.get()[7];
		u2 = a_m[2] ^ (s.get()[0] << 16) ^ (s.get()[0] >> 16) ^ (s.get()[0] & 0xFFFF)
			^ (s.get()[1] & 0xFFFF) ^ (s.get()[1] >> 16) ^ (s.get()[2] << 16)
			^ s.get()[6] ^ (s.get()[6] << 16) ^ (s.get()[7] & 0xFFFF0000) ^ (s.get()[7] >> 16);
		u3 = a_m[3] ^ (s.get()[0] & 0xFFFF) ^ (s.get()[0] << 16) ^ (s.get()[1] & 0xFFFF)
			^ (s.get()[1] << 16) ^ (s.get()[1] >> 16) ^ (s.get()[2] << 16) ^ (s.get()[2] >> 16)
			^ (s.get()[3] << 16) ^ s.get()[6] ^ (s.get()[6] << 16) ^ (s.get()[6] >> 16)
			^ (s.get()[7] & 0xFFFF) ^ (s.get()[7] << 16) ^ (s.get()[7] >> 16);
		u4 = a_m[4] ^ (s.get()[0] & 0xFFFF0000) ^ (s.get()[0] << 16) ^ (s.get()[0] >> 16)
			^ (s.get()[1] & 0xFFFF0000) ^ (s.get()[1] >> 16) ^ (s.get()[2] << 16)
			^ (s.get()[2] >> 16) ^ (s.get()[3] << 16) ^ (s.get()[3] >> 16) ^ (s.get()[4] << 16)
			^ (s.get()[6] << 16) ^ (s.get()[6] >> 16) ^ (s.get()[7] & 0xFFFF) ^ (s.get()[7] << 16)
			^ (s.get()[7] >> 16);
		u5 = a_m[5] ^ (s.get()[0] << 16) ^ (s.get()[0] >> 16) ^ (s.get()[0] & 0xFFFF0000)
			^ (s.get()[1] & 0xFFFF) ^ s.get()[2] ^ (s.get()[2] >> 16) ^ (s.get()[3] << 16)
			^ (s.get()[3] >> 16) ^ (s.get()[4] << 16) ^ (s.get()[4] >> 16) ^ (s.get()[5] << 16)
			^ (s.get()[6] << 16) ^ (s.get()[6] >> 16) ^ (s.get()[7] & 0xFFFF0000)
			^ (s.get()[7] << 16) ^ (s.get()[7] >> 16);
		u6 = a_m[6] ^ s.get()[0] ^ (s.get()[1] >> 16) ^ (s.get()[2] << 16)
			^ s.get()[3] ^ (s.get()[3] >> 16) ^ (s.get()[4] << 16) ^ (s.get()[4] >> 16)
			^ (s.get()[5] << 16) ^ (s.get()[5] >> 16) ^ s.get()[6] ^ (s.get()[6] << 16)
			^ (s.get()[6] >> 16) ^ (s.get()[7] << 16);
		u7 = a_m[7] ^ (s.get()[0] & 0xFFFF0000) ^ (s.get()[0] << 16) ^ (s.get()[1] & 0xFFFF)
			^ (s.get()[1] << 16) ^ (s.get()[2] >> 16) ^ (s.get()[3] << 16)
			^ s.get()[4] ^ (s.get()[4] >> 16) ^ (s.get()[5] << 16) ^ (s.get()[5] >> 16)
			^ (s.get()[6] >> 16) ^ (s.get()[7] & 0xFFFF) ^ (s.get()[7] << 16) ^ (s.get()[7] >> 16);

		v0 = hash.get()[0] ^ (u1 << 16) ^ (u0 >> 16);
		v1 = hash.get()[1] ^ (u2 << 16) ^ (u1 >> 16);
		v2 = hash.get()[2] ^ (u3 << 16) ^ (u2 >> 16);
		v3 = hash.get()[3] ^ (u4 << 16) ^ (u3 >> 16);
		v4 = hash.get()[4] ^ (u5 << 16) ^ (u4 >> 16);
		v5 = hash.get()[5] ^ (u6 << 16) ^ (u5 >> 16);
		v6 = hash.get()[6] ^ (u7 << 16) ^ (u6 >> 16);
		v7 = hash.get()[7] ^ (u0 & 0xFFFF0000) ^ (u0 << 16) ^ (u7 >> 16)
			^ (u1 & 0xFFFF0000) ^ (u1 << 16) ^ (u6 << 16)
			^ (u7 & 0xFFFF0000);

		hash.get()[0]  = (v0 & 0xFFFF0000) ^ (v0 << 16) ^ (v0 >> 16)
			^ (v1 >> 16) ^ (v1 & 0xFFFF0000) ^ (v2 << 16) ^ (v3 >> 16)
			^ (v4 << 16) ^ (v5 >> 16) ^ v5 ^ (v6 >> 16) ^ (v7 << 16)
			^ (v7 >> 16) ^ (v7 & 0xFFFF);
		hash.get()[1]  = (v0 << 16) ^ (v0 >> 16) ^ (v0 & 0xFFFF0000)
			^ (v1 & 0xFFFF) ^ v2 ^ (v2 >> 16) ^ (v3 << 16) ^ (v4 >> 16)
			^ (v5 << 16) ^ (v6 << 16) ^ v6 ^ (v7 & 0xFFFF0000)
			^ (v7 >> 16);
		hash.get()[2]  = (v0 & 0xFFFF) ^ (v0 << 16) ^ (v1 << 16) ^ (v1 >> 16)
			^ (v1 & 0xFFFF0000) ^ (v2 << 16) ^ (v3 >> 16)
			^ v3 ^ (v4 << 16) ^ (v5 >> 16) ^ v6 ^ (v6 >> 16)
			^ (v7 & 0xFFFF) ^ (v7 << 16) ^ (v7 >> 16);
		hash.get()[3]  = (v0 << 16) ^ (v0 >> 16) ^ (v0 & 0xFFFF0000)
			^ (v1 & 0xFFFF0000) ^ (v1 >> 16) ^ (v2 << 16) ^ (v2 >> 16)
			^ v2 ^ (v3 << 16) ^ (v4 >> 16) ^ v4 ^ (v5 << 16)
			^ (v6 << 16) ^ (v7 & 0xFFFF) ^ (v7 >> 16);
		hash.get()[4]  = (v0 >> 16) ^ (v1 << 16) ^ v1 ^ (v2 >> 16)
			^ v2 ^ (v3 << 16) ^ (v3 >> 16) ^ v3 ^ (v4 << 16)
			^ (v5 >> 16) ^ v5 ^ (v6 << 16) ^ (v6 >> 16) ^ (v7 << 16);
		hash.get()[5]  = (v0 << 16) ^ (v0 & 0xFFFF0000) ^ (v1 << 16)
			^ (v1 >> 16) ^ (v1 & 0xFFFF0000) ^ (v2 << 16)
			^ v2 ^ (v3 >> 16) ^ v3 ^ (v4 << 16) ^ (v4 >> 16)
			^ v4 ^ (v5 << 16) ^ (v6 << 16) ^ (v6 >> 16)
			^ v6 ^ (v7 << 16) ^ (v7 >> 16) ^ (v7 & 0xFFFF0000);
		hash.get()[6]  = v0 ^ v2 ^ (v2 >> 16) ^ v3 ^ (v3 << 16)
			^ v4 ^ (v4 >> 16) ^ (v5 << 16) ^ (v5 >> 16)
			^ v5 ^ (v6 << 16) ^ (v6 >> 16) ^ v6 ^ (v7 << 16) ^ v7;
		hash.get()[7]  = v0 ^ (v0 >> 16) ^ (v1 << 16) ^ (v1 >> 16)
			^ (v2 << 16) ^ (v3 >> 16) ^ v3 ^ (v4 << 16)
			^ v4 ^ (v5 >> 16) ^ v5 ^ (v6 << 16) ^ (v6 >> 16)
			^ (v7 << 16) ^ v7;

	} // end function Compress

protected:
	virtual void Finish()
	{
		uint64_t bits = processed_bytes * 8;

		if (buffer->GetPos() > 0)
		{
			HashLibByteArray pad = HashLibByteArray(32 - buffer->GetPos());
			TransformBytes(pad, 0, 32 - buffer->GetPos());
		} // end if

		HashLibUInt32Array length = HashLibUInt32Array(8);
		length[0] = bits;
		length[1] = bits >> 32;

		Compress(&length[0]);

		Compress(&state.get()[0]);

	} // end function Finish

	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(8 * sizeof(uint32_t));

		Converters::le32_copy((uint32_t*)(&hash.get()[0]), 0, (uint8_t*)&result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult

	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t c, a, b;

		c = 0;

		Converters::le32_copy(a_data, a_index, data.get(), 0, 32);

		for (register uint32_t i = 0; i < 8; i++)
		{
			a = data.get()[i];
			m.get()[i] = a;
			b = state.get()[i];
			c = a + c + state.get()[i];
			state.get()[i] = c;

			if ((c < a) || (c < b))
				c = 1;
			else
				c = 0;

		} // end for
			
		Compress(&m.get()[0]);

		memset(m.get(), 0, 8 * sizeof(uint32_t));
		memset(data.get(), 0, 8 * sizeof(uint32_t));

	} // end function TransformBlock


protected:
	shared_ptr<uint32_t> state;
	shared_ptr<uint32_t> hash;
	shared_ptr<uint32_t> data;
	shared_ptr<uint32_t> m;
	shared_ptr<uint32_t> s;
	
	static char initialized;
	static shared_ptr<uint32_t> sbox1;
	static shared_ptr<uint32_t> sbox2;
	static shared_ptr<uint32_t> sbox3;
	static shared_ptr<uint32_t> sbox4;
}; // end class Gost

char Gost::initialized = 0;
shared_ptr<uint32_t> Gost::sbox1 = shared_ptr<uint32_t>(new uint32_t[256], default_delete<uint32_t[]>());
shared_ptr<uint32_t> Gost::sbox2 = shared_ptr<uint32_t>(new uint32_t[256], default_delete<uint32_t[]>());
shared_ptr<uint32_t> Gost::sbox3 = shared_ptr<uint32_t>(new uint32_t[256], default_delete<uint32_t[]>());
shared_ptr<uint32_t> Gost::sbox4 = shared_ptr<uint32_t>(new uint32_t[256], default_delete<uint32_t[]>());


#endif //!HLPGOST_H