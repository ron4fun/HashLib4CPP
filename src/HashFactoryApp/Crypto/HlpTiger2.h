#ifndef HLPTIGER2_H
#define HLPTIGER2_H

#include "../Base/HlpHashCryptoNotBuildIn.h"
#include "../Base/HlpHashRounds.h"


class Tiger2 : public BlockHash, public IICryptoNotBuildIn, public IITransformBlock
{
public:
	virtual void Initialize()
	{
		hash.get()[0] = 0x0123456789ABCDEF;
		hash.get()[1] = 0xFEDCBA9876543210;
		hash.get()[2] = 0xF096A5B4C3B2E187;

		BlockHash::Initialize();
	} // end function Initialize

protected:
	Tiger2(const int32_t a_hash_size, const HashRounds &a_rounds)
		: BlockHash(a_hash_size, 64)
	{
		name = __func__;

		rounds = int32_t(a_rounds);
		hash = shared_ptr<uint64_t>(new uint64_t[3], default_delete<uint64_t[]>());
		data = shared_ptr<uint64_t>(new uint64_t[8], default_delete<uint64_t[]>());
	} // end constructor

	~Tiger2()
	{} // end destructor

	virtual void Finish()
	{
		int32_t padindex;

		uint64_t bits = processed_bytes * 8;
		if (buffer->GetPos() < 56)
			padindex = 56 - buffer->GetPos();
		else
			padindex = 120 - buffer->GetPos();

		HashLibByteArray pad = HashLibByteArray(padindex + 8);

		pad[0] = 0x80;

		bits = Converters::le2me_64(bits);

		Converters::ReadUInt64AsBytesLE(bits, pad, padindex);

		padindex = padindex + 8;

		TransformBytes(pad, 0, padindex);

	} // end function Finish

	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(GetHashSize());
		
		Converters::le64_copy(hash.get(), 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult

	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint64_t a, b, c, temp_a;
		register uint32_t _rounds;

		Converters::le64_copy(a_data, a_index, data.get(), 0, 64);

		a = hash.get()[0];
		b = hash.get()[1];
		c = hash.get()[2];

		c = c ^ data.get()[0];
		a = a - (T1[uint8_t(c)] ^ T2[uint8_t(c >> 16)] ^ T3[uint8_t(c >> 32)
		] ^ T4[uint8_t(c >> 48)]);
		b = b + (T4[uint8_t(c >> 8) & 0xFF] ^ T3[uint8_t(c >> 24)
		] ^ T2[uint8_t(c >> 40)] ^ T1[uint8_t(c >> 56)]);
		b = b * 5;

		a = a ^ data.get()[1];
		b = b - (T1[uint8_t(a)] ^ T2[uint8_t(a >> 16)] ^ T3[uint8_t(a >> 32)
		] ^ T4[uint8_t(a >> 48)]);
		c = c + (T4[uint8_t(a >> 8)] ^ T3[uint8_t(a >> 24)] ^ T2[uint8_t(a >> 40)
		] ^ T1[uint8_t(a >> 56)]);
		c = c * 5;

		b = b ^ data.get()[2];
		c = c - (T1[uint8_t(b)] ^ T2[uint8_t(b >> 16)] ^ T3[uint8_t(b >> 32)
		] ^ T4[uint8_t(b >> 48)]);
		a = a + (T4[uint8_t(b >> 8)] ^ T3[uint8_t(b >> 24)] ^ T2[uint8_t(b >> 40)
		] ^ T1[uint8_t(b >> 56)]);
		a = a * 5;

		c = c ^ data.get()[3];
		a = a - (T1[uint8_t(c)] ^ T2[uint8_t(c >> 16)] ^ T3[uint8_t(c >> 32)
		] ^ T4[uint8_t(c >> 48)]);
		b = b + (T4[uint8_t(c >> 8) & 0xFF] ^ T3[uint8_t(c >> 24)
		] ^ T2[uint8_t(c >> 40)] ^ T1[uint8_t(c >> 56)]);
		b = b * 5;

		a = a ^ data.get()[4];
		b = b - (T1[uint8_t(a)] ^ T2[uint8_t(a >> 16)] ^ T3[uint8_t(a >> 32)
		] ^ T4[uint8_t(a >> 48)]);
		c = c + (T4[uint8_t(a >> 8)] ^ T3[uint8_t(a >> 24)] ^ T2[uint8_t(a >> 40)
		] ^ T1[uint8_t(a >> 56)]);
		c = c * 5;

		b = b ^ data.get()[5];
		c = c - (T1[uint8_t(b)] ^ T2[uint8_t(b >> 16)] ^ T3[uint8_t(b >> 32)
		] ^ T4[uint8_t(b >> 48)]);
		a = a + (T4[uint8_t(b >> 8)] ^ T3[uint8_t(b >> 24)] ^ T2[uint8_t(b >> 40)
		] ^ T1[uint8_t(b >> 56)]);
		a = a * 5;

		c = c ^ data.get()[6];
		a = a - (T1[uint8_t(c)] ^ T2[uint8_t(c >> 16)] ^ T3[uint8_t(c >> 32)
		] ^ T4[uint8_t(c >> 48)]);
		b = b + (T4[uint8_t(c >> 8) & 0xFF] ^ T3[uint8_t(c >> 24)
		] ^ T2[uint8_t(c >> 40)] ^ T1[uint8_t(c >> 56)]);
		b = b * 5;

		a = a ^ data.get()[7];
		b = b - (T1[uint8_t(a)] ^ T2[uint8_t(a >> 16)] ^ T3[uint8_t(a >> 32)
		] ^ T4[uint8_t(a >> 48)]);
		c = c + (T4[uint8_t(a >> 8)] ^ T3[uint8_t(a >> 24)] ^ T2[uint8_t(a >> 40)
		] ^ T1[uint8_t(a >> 56)]);
		c = c * 5;

		data.get()[0]  = data.get()[0] - (data.get()[7] ^ C1);
		data.get()[1]  = data.get()[1] ^ data.get()[0];
		data.get()[2]  = data.get()[2] + data.get()[1];
		data.get()[3]  = data.get()[3] - (data.get()[2] ^ (~data.get()[1] << 19));
		data.get()[4]  = data.get()[4] ^ data.get()[3];
		data.get()[5]  = data.get()[5] + data.get()[4];
		data.get()[6]  = data.get()[6] - (data.get()[5] ^ (~data.get()[4] >> 23));
		data.get()[7]  = data.get()[7] ^ data.get()[6];
		data.get()[0]  = data.get()[0] + data.get()[7];
		data.get()[1]  = data.get()[1] - (data.get()[0] ^ (~data.get()[7] << 19));
		data.get()[2]  = data.get()[2] ^ data.get()[1];
		data.get()[3]  = data.get()[3] + data.get()[2];
		data.get()[4]  = data.get()[4] - (data.get()[3] ^ (~data.get()[2] >> 23));
		data.get()[5]  = data.get()[5] ^ data.get()[4];
		data.get()[6]  = data.get()[6] + data.get()[5];
		data.get()[7]  = data.get()[7] - (data.get()[6] ^ C2);

		b = b ^ data.get()[0];
		c = c - (T1[uint8_t(b)] ^ T2[uint8_t(b >> 16)] ^ T3[uint8_t(b >> 32)
		] ^ T4[uint8_t(b >> 48)]);
		a = a + (T4[uint8_t(b >> 8)] ^ T3[uint8_t(b >> 24)] ^ T2[uint8_t(b >> 40)
		] ^ T1[uint8_t(b >> 56)]);
		a = a * 7;

		c = c ^ data.get()[1];
		a = a - (T1[uint8_t(c)] ^ T2[uint8_t(c >> 16)] ^ T3[uint8_t(c >> 32)
		] ^ T4[uint8_t(c >> 48)]);
		b = b + (T4[uint8_t(c >> 8) & 0xFF] ^ T3[uint8_t(c >> 24)
		] ^ T2[uint8_t(c >> 40)] ^ T1[uint8_t(c >> 56)]);
		b = b * 7;

		a = a ^ data.get()[2];
		b = b - (T1[uint8_t(a)] ^ T2[uint8_t(a >> 16)] ^ T3[uint8_t(a >> 32)
		] ^ T4[uint8_t(a >> 48)]);
		c = c + (T4[uint8_t(a >> 8)] ^ T3[uint8_t(a >> 24)] ^ T2[uint8_t(a >> 40)
		] ^ T1[uint8_t(a >> 56)]);
		c = c * 7;

		b = b ^ data.get()[3];
		c = c - (T1[uint8_t(b)] ^ T2[uint8_t(b >> 16)] ^ T3[uint8_t(b >> 32)
		] ^ T4[uint8_t(b >> 48)]);
		a = a + (T4[uint8_t(b >> 8)] ^ T3[uint8_t(b >> 24)] ^ T2[uint8_t(b >> 40)
		] ^ T1[uint8_t(b >> 56)]);
		a = a * 7;

		c = c ^ data.get()[4];
		a = a - (T1[uint8_t(c)] ^ T2[uint8_t(c >> 16)] ^ T3[uint8_t(c >> 32)
		] ^ T4[uint8_t(c >> 48)]);
		b = b + (T4[uint8_t(c >> 8) & 0xFF] ^ T3[uint8_t(c >> 24)
		] ^ T2[uint8_t(c >> 40)] ^ T1[uint8_t(c >> 56)]);
		b = b * 7;

		a = a ^ data.get()[5];
		b = b - (T1[uint8_t(a)] ^ T2[uint8_t(a >> 16)] ^ T3[uint8_t(a >> 32)
		] ^ T4[uint8_t(a >> 48)]);
		c = c + (T4[uint8_t(a >> 8)] ^ T3[uint8_t(a >> 24)] ^ T2[uint8_t(a >> 40)
		] ^ T1[uint8_t(a >> 56)]);
		c = c * 7;

		b = b ^ data.get()[6];
		c = c - (T1[uint8_t(b)] ^ T2[uint8_t(b >> 16)] ^ T3[uint8_t(b >> 32)
		] ^ T4[uint8_t(b >> 48)]);
		a = a + (T4[uint8_t(b >> 8)] ^ T3[uint8_t(b >> 24)] ^ T2[uint8_t(b >> 40)
		] ^ T1[uint8_t(b >> 56)]);
		a = a * 7;

		c = c ^ data.get()[7];
		a = a - (T1[uint8_t(c)] ^ T2[uint8_t(c >> 16)] ^ T3[uint8_t(c >> 32)
		] ^ T4[uint8_t(c >> 48)]);
		b = b + (T4[uint8_t(c >> 8) & 0xFF] ^ T3[uint8_t(c >> 24)
		] ^ T2[uint8_t(c >> 40)] ^ T1[uint8_t(c >> 56)]);
		b = b * 7;

		data.get()[0]  = data.get()[0] - (data.get()[7] ^ C1);
		data.get()[1]  = data.get()[1] ^ data.get()[0];
		data.get()[2]  = data.get()[2] + data.get()[1];
		data.get()[3]  = data.get()[3] - (data.get()[2] ^ (~data.get()[1] << 19));
		data.get()[4]  = data.get()[4] ^ data.get()[3];
		data.get()[5]  = data.get()[5] + data.get()[4];
		data.get()[6]  = data.get()[6] - (data.get()[5] ^ (~data.get()[4] >> 23));
		data.get()[7]  = data.get()[7] ^ data.get()[6];
		data.get()[0]  = data.get()[0] + data.get()[7];
		data.get()[1]  = data.get()[1] - (data.get()[0] ^ (~data.get()[7] << 19));
		data.get()[2]  = data.get()[2] ^ data.get()[1];
		data.get()[3]  = data.get()[3] + data.get()[2];
		data.get()[4]  = data.get()[4] - (data.get()[3] ^ (~data.get()[2] >> 23));
		data.get()[5]  = data.get()[5] ^ data.get()[4];
		data.get()[6]  = data.get()[6] + data.get()[5];
		data.get()[7]  = data.get()[7] - (data.get()[6] ^ C2);

		a = a ^ data.get()[0];
		b = b - (T1[uint8_t(a)] ^ T2[uint8_t(a >> 16)] ^ T3[uint8_t(a >> 32)
		] ^ T4[uint8_t(a >> 48)]);
		c = c + (T4[uint8_t(a >> 8)] ^ T3[uint8_t(a >> 24)] ^ T2[uint8_t(a >> 40)
		] ^ T1[uint8_t(a >> 56)]);
		c = c * 9;

		b = b ^ data.get()[1];
		c = c - (T1[uint8_t(b)] ^ T2[uint8_t(b >> 16)] ^ T3[uint8_t(b >> 32)
		] ^ T4[uint8_t(b >> 48)]);
		a = a + (T4[uint8_t(b >> 8)] ^ T3[uint8_t(b >> 24)] ^ T2[uint8_t(b >> 40)
		] ^ T1[uint8_t(b >> 56)]);
		a = a * 9;

		c = c ^ data.get()[2];
		a = a - (T1[uint8_t(c)] ^ T2[uint8_t(c >> 16)] ^ T3[uint8_t(c >> 32)
		] ^ T4[uint8_t(c >> 48)]);
		b = b + (T4[uint8_t(c >> 8) & 0xFF] ^ T3[uint8_t(c >> 24)
		] ^ T2[uint8_t(c >> 40)] ^ T1[uint8_t(c >> 56)]);
		b = b * 9;

		a = a ^ data.get()[3];
		b = b - (T1[uint8_t(a)] ^ T2[uint8_t(a >> 16)] ^ T3[uint8_t(a >> 32)
		] ^ T4[uint8_t(a >> 48)]);
		c = c + (T4[uint8_t(a >> 8)] ^ T3[uint8_t(a >> 24)] ^ T2[uint8_t(a >> 40)
		] ^ T1[uint8_t(a >> 56)]);
		c = c * 9;

		b = b ^ data.get()[4];
		c = c - (T1[uint8_t(b)] ^ T2[uint8_t(b >> 16)] ^ T3[uint8_t(b >> 32)
		] ^ T4[uint8_t(b >> 48)]);
		a = a + (T4[uint8_t(b >> 8)] ^ T3[uint8_t(b >> 24)] ^ T2[uint8_t(b >> 40)
		] ^ T1[uint8_t(b >> 56)]);
		a = a * 9;

		c = c ^ data.get()[5];
		a = a - (T1[uint8_t(c)] ^ T2[uint8_t(c >> 16)] ^ T3[uint8_t(c >> 32)
		] ^ T4[uint8_t(c >> 48)]);
		b = b + (T4[uint8_t(c >> 8) & 0xFF] ^ T3[uint8_t(c >> 24)
		] ^ T2[uint8_t(c >> 40)] ^ T1[uint8_t(c >> 56)]);
		b = b * 9;

		a = a ^ data.get()[6];
		b = b - (T1[uint8_t(a)] ^ T2[uint8_t(a >> 16)] ^ T3[uint8_t(a >> 32)
		] ^ T4[uint8_t(a >> 48)]);
		c = c + (T4[uint8_t(a >> 8)] ^ T3[uint8_t(a >> 24)] ^ T2[uint8_t(a >> 40)
		] ^ T1[uint8_t(a >> 56)]);
		c = c * 9;

		b = b ^ data.get()[7];
		c = c - (T1[uint8_t(b)] ^ T2[uint8_t(b >> 16)] ^ T3[uint8_t(b >> 32)
		] ^ T4[uint8_t(b >> 48)]);
		a = a + (T4[uint8_t(b >> 8)] ^ T3[uint8_t(b >> 24)] ^ T2[uint8_t(b >> 40)
		] ^ T1[uint8_t(b >> 56)]);
		a = a * 9;

		_rounds = 3;
		while (_rounds < rounds)
		{
			data.get()[0] = data.get()[0] - (data.get()[7] ^ C1);
			data.get()[1] = data.get()[1] ^ data.get()[0];
			data.get()[2] = data.get()[2] + data.get()[1];
			data.get()[3] = data.get()[3] - (data.get()[2] ^ (~data.get()[1] << 19));
			data.get()[4] = data.get()[4] ^ data.get()[3];
			data.get()[5] = data.get()[5] + data.get()[4];
			data.get()[6] = data.get()[6] - (data.get()[5] ^ (~data.get()[4] >> 23));
			data.get()[7] = data.get()[7] ^ data.get()[6];
			data.get()[0] = data.get()[0] + data.get()[7];
			data.get()[1] = data.get()[1] - (data.get()[0] ^ (~data.get()[7] << 19));
			data.get()[2] = data.get()[2] ^ data.get()[1];
			data.get()[3] = data.get()[3] + data.get()[2];
			data.get()[4] = data.get()[4] - (data.get()[3] ^ (~data.get()[2] >> 23));
			data.get()[5] = data.get()[5] ^ data.get()[4];
			data.get()[6] = data.get()[6] + data.get()[5];
			data.get()[7] = data.get()[7] - (data.get()[6] ^ C2);

			c = c ^ data.get()[0];
			a = a - (T1[uint8_t(c)] ^ T2[uint8_t(c >> 16)] ^ T3[uint8_t(c >> 32)
			] ^ T4[uint8_t(c >> 48)]);
			b = b + (T4[uint8_t(c >> 8) & 0xFF] ^ T3[uint8_t(c >> 24)
			] ^ T2[uint8_t(c >> 40)] ^ T1[uint8_t(c >> 56)]);
			b = b * 9;

			a = a ^ data.get()[1];
			b = b - (T1[uint8_t(a)] ^ T2[uint8_t(a >> 16)] ^ T3[uint8_t(a >> 32)
			] ^ T4[uint8_t(a >> 48)]);
			c = c + (T4[uint8_t(a >> 8)] ^ T3[uint8_t(a >> 24)] ^ T2
				[uint8_t(a >> 40)] ^ T1[uint8_t(a >> 56)]);
			c = c * 9;

			b = b ^ data.get()[2];
			c = c - (T1[uint8_t(b)] ^ T2[uint8_t(b >> 16)] ^ T3[uint8_t(b >> 32)
			] ^ T4[uint8_t(b >> 48)]);
			a = a + (T4[uint8_t(b >> 8)] ^ T3[uint8_t(b >> 24)] ^ T2
				[uint8_t(b >> 40)] ^ T1[uint8_t(b >> 56)]);
			a = a * 9;

			c = c ^ data.get()[3];
			a = a - (T1[uint8_t(c)] ^ T2[uint8_t(c >> 16)] ^ T3[uint8_t(c >> 32)
			] ^ T4[uint8_t(c >> 48)]);
			b = b + (T4[uint8_t(c >> 8) & 0xFF] ^ T3[uint8_t(c >> 24)
			] ^ T2[uint8_t(c >> 40)] ^ T1[uint8_t(c >> 56)]);
			b = b * 9;

			a = a ^ data.get()[4];
			b = b - (T1[uint8_t(a)] ^ T2[uint8_t(a >> 16)] ^ T3[uint8_t(a >> 32)
			] ^ T4[uint8_t(a >> 48)]);
			c = c + (T4[uint8_t(a >> 8)] ^ T3[uint8_t(a >> 24)] ^ T2
				[uint8_t(a >> 40)] ^ T1[uint8_t(a >> 56)]);
			c = c * 9;

			b = b ^ data.get()[5];
			c = c - (T1[uint8_t(b)] ^ T2[uint8_t(b >> 16)] ^ T3[uint8_t(b >> 32)
			] ^ T4[uint8_t(b >> 48)]);
			a = a + (T4[uint8_t(b >> 8)] ^ T3[uint8_t(b >> 24)] ^ T2
				[uint8_t(b >> 40)] ^ T1[uint8_t(b >> 56)]);
			a = a * 9;

			c = c ^ data.get()[6];
			a = a - (T1[uint8_t(c)] ^ T2[uint8_t(c >> 16)] ^ T3[uint8_t(c >> 32)
			] ^ T4[uint8_t(c >> 48)]);
			b = b + (T4[uint8_t(c >> 8) & 0xFF] ^ T3[uint8_t(c >> 24)
			] ^ T2[uint8_t(c >> 40)] ^ T1[uint8_t(c >> 56)]);
			b = b * 9;

			a = a ^ data.get()[7];
			b = b - (T1[uint8_t(a)] ^ T2[uint8_t(a >> 16)] ^ T3[uint8_t(a >> 32)
			] ^ T4[uint8_t(a >> 48)]);
			c = c + (T4[uint8_t(a >> 8)] ^ T3[uint8_t(a >> 24)] ^ T2
				[uint8_t(a >> 40)] ^ T1[uint8_t(a >> 56)]);
			c = c * 9;

			temp_a = a;
			a = c;
			c = b;
			b = temp_a;

			_rounds++;
		} // end while

	   hash.get()[0]  = hash.get()[0] ^ a;
	   hash.get()[1]  = b - hash.get()[1];
	   hash.get()[2]  = hash.get()[2] + c;

		memset(data.get(), 0, 8 * sizeof(uint64_t));
	} // end function TransformBlock

public:
	static const char *InvalidTiger2HashSize;

private:
	shared_ptr<uint64_t> hash;
	shared_ptr<uint64_t> data;
	int32_t rounds;

	static const uint64_t C1 = 0xA5A5A5A5A5A5A5A5;
	static const uint64_t C2 = 0x0123456789ABCDEF;

	static const uint64_t T1[256];
	static const uint64_t T2[256];
	static const uint64_t T3[256];
	static const uint64_t T4[256];

}; // end class Tiger2

const char *Tiger2::InvalidTiger2HashSize = "Tiger2 HashSize Must be Either 128 bit(16 byte), 160 bit(20 byte) or 192 bit(24 byte)";

const uint64_t Tiger2::T1[256] = { uint64_t(0x02AAB17CF7E90C5E),
	uint64_t(0xAC424B03E243A8EC), uint64_t(0x72CD5BE30DD5FCD3),
	uint64_t(0x6D019B93F6F97F3A), uint64_t(0xCD9978FFD21F9193),
	uint64_t(0x7573A1C9708029E2), uint64_t(0xB164326B922A83C3),
	uint64_t(0x46883EEE04915870), uint64_t(0xEAACE3057103ECE6),
	uint64_t(0xC54169B808A3535C), uint64_t(0x4CE754918DDEC47C),
	uint64_t(0x0AA2F4DFDC0DF40C), uint64_t(0x10B76F18A74DBEFA),
	uint64_t(0xC6CCB6235AD1AB6A), uint64_t(0x13726121572FE2FF),
	uint64_t(0x1A488C6F199D921E), uint64_t(0x4BC9F9F4DA0007CA),
	uint64_t(0x26F5E6F6E85241C7), uint64_t(0x859079DBEA5947B6),
	uint64_t(0x4F1885C5C99E8C92), uint64_t(0xD78E761EA96F864B),
	uint64_t(0x8E36428C52B5C17D), uint64_t(0x69CF6827373063C1),
	uint64_t(0xB607C93D9BB4C56E), uint64_t(0x7D820E760E76B5EA),
	uint64_t(0x645C9CC6F07FDC42), uint64_t(0xBF38A078243342E0),
	uint64_t(0x5F6B343C9D2E7D04), uint64_t(0xF2C28AEB600B0EC6),
	uint64_t(0x6C0ED85F7254BCAC), uint64_t(0x71592281A4DB4FE5),
	uint64_t(0x1967FA69CE0FED9F), uint64_t(0xFD5293F8B96545DB),
	uint64_t(0xC879E9D7F2A7600B), uint64_t(0x860248920193194E),
	uint64_t(0xA4F9533B2D9CC0B3), uint64_t(0x9053836C15957613),
	uint64_t(0xDB6DCF8AFC357BF1), uint64_t(0x18BEEA7A7A370F57),
	uint64_t(0x037117CA50B99066), uint64_t(0x6AB30A9774424A35),
	uint64_t(0xF4E92F02E325249B), uint64_t(0x7739DB07061CCAE1),
	uint64_t(0xD8F3B49CECA42A05), uint64_t(0xBD56BE3F51382F73),
	uint64_t(0x45FAED5843B0BB28), uint64_t(0x1C813D5C11BF1F83),
	uint64_t(0x8AF0E4B6D75FA169), uint64_t(0x33EE18A487AD9999),
	uint64_t(0x3C26E8EAB1C94410), uint64_t(0xB510102BC0A822F9),
	uint64_t(0x141EEF310CE6123B), uint64_t(0xFC65B90059DDB154),
	uint64_t(0xE0158640C5E0E607), uint64_t(0x884E079826C3A3CF),
	uint64_t(0x930D0D9523C535FD), uint64_t(0x35638D754E9A2B00),
	uint64_t(0x4085FCCF40469DD5), uint64_t(0xC4B17AD28BE23A4C),
	uint64_t(0xCAB2F0FC6A3E6A2E), uint64_t(0x2860971A6B943FCD),
	uint64_t(0x3DDE6EE212E30446), uint64_t(0x6222F32AE01765AE),
	uint64_t(0x5D550BB5478308FE), uint64_t(0xA9EFA98DA0EDA22A),
	uint64_t(0xC351A71686C40DA7), uint64_t(0x1105586D9C867C84),
	uint64_t(0xDCFFEE85FDA22853), uint64_t(0xCCFBD0262C5EEF76),
	uint64_t(0xBAF294CB8990D201), uint64_t(0xE69464F52AFAD975),
	uint64_t(0x94B013AFDF133E14), uint64_t(0x06A7D1A32823C958),
	uint64_t(0x6F95FE5130F61119), uint64_t(0xD92AB34E462C06C0),
	uint64_t(0xED7BDE33887C71D2), uint64_t(0x79746D6E6518393E),
	uint64_t(0x5BA419385D713329), uint64_t(0x7C1BA6B948A97564),
	uint64_t(0x31987C197BFDAC67), uint64_t(0xDE6C23C44B053D02),
	uint64_t(0x581C49FED002D64D), uint64_t(0xDD474D6338261571),
	uint64_t(0xAA4546C3E473D062), uint64_t(0x928FCE349455F860),
	uint64_t(0x48161BBACAAB94D9), uint64_t(0x63912430770E6F68),
	uint64_t(0x6EC8A5E602C6641C), uint64_t(0x87282515337DDD2B),
	uint64_t(0x2CDA6B42034B701B), uint64_t(0xB03D37C181CB096D),
	uint64_t(0xE108438266C71C6F), uint64_t(0x2B3180C7EB51B255),
	uint64_t(0xDF92B82F96C08BBC), uint64_t(0x5C68C8C0A632F3BA),
	uint64_t(0x5504CC861C3D0556), uint64_t(0xABBFA4E55FB26B8F),
	uint64_t(0x41848B0AB3BACEB4), uint64_t(0xB334A273AA445D32),
	uint64_t(0xBCA696F0A85AD881), uint64_t(0x24F6EC65B528D56C),
	uint64_t(0x0CE1512E90F4524A), uint64_t(0x4E9DD79D5506D35A),
	uint64_t(0x258905FAC6CE9779), uint64_t(0x2019295B3E109B33),
	uint64_t(0xF8A9478B73A054CC), uint64_t(0x2924F2F934417EB0),
	uint64_t(0x3993357D536D1BC4), uint64_t(0x38A81AC21DB6FF8B),
	uint64_t(0x47C4FBF17D6016BF), uint64_t(0x1E0FAADD7667E3F5),
	uint64_t(0x7ABCFF62938BEB96), uint64_t(0xA78DAD948FC179C9),
	uint64_t(0x8F1F98B72911E50D), uint64_t(0x61E48EAE27121A91),
	uint64_t(0x4D62F7AD31859808), uint64_t(0xECEBA345EF5CEAEB),
	uint64_t(0xF5CEB25EBC9684CE), uint64_t(0xF633E20CB7F76221),
	uint64_t(0xA32CDF06AB8293E4), uint64_t(0x985A202CA5EE2CA4),
	uint64_t(0xCF0B8447CC8A8FB1), uint64_t(0x9F765244979859A3),
	uint64_t(0xA8D516B1A1240017), uint64_t(0x0BD7BA3EBB5DC726),
	uint64_t(0xE54BCA55B86ADB39), uint64_t(0x1D7A3AFD6C478063),
	uint64_t(0x519EC608E7669EDD), uint64_t(0x0E5715A2D149AA23),
	uint64_t(0x177D4571848FF194), uint64_t(0xEEB55F3241014C22),
	uint64_t(0x0F5E5CA13A6E2EC2), uint64_t(0x8029927B75F5C361),
	uint64_t(0xAD139FABC3D6E436), uint64_t(0x0D5DF1A94CCF402F),
	uint64_t(0x3E8BD948BEA5DFC8), uint64_t(0xA5A0D357BD3FF77E),
	uint64_t(0xA2D12E251F74F645), uint64_t(0x66FD9E525E81A082),
	uint64_t(0x2E0C90CE7F687A49), uint64_t(0xC2E8BCBEBA973BC5),
	uint64_t(0x000001BCE509745F), uint64_t(0x423777BBE6DAB3D6),
	uint64_t(0xD1661C7EAEF06EB5), uint64_t(0xA1781F354DAACFD8),
	uint64_t(0x2D11284A2B16AFFC), uint64_t(0xF1FC4F67FA891D1F),
	uint64_t(0x73ECC25DCB920ADA), uint64_t(0xAE610C22C2A12651),
	uint64_t(0x96E0A810D356B78A), uint64_t(0x5A9A381F2FE7870F),
	uint64_t(0xD5AD62EDE94E5530), uint64_t(0xD225E5E8368D1427),
	uint64_t(0x65977B70C7AF4631), uint64_t(0x99F889B2DE39D74F),
	uint64_t(0x233F30BF54E1D143), uint64_t(0x9A9675D3D9A63C97),
	uint64_t(0x5470554FF334F9A8), uint64_t(0x166ACB744A4F5688),
	uint64_t(0x70C74CAAB2E4AEAD), uint64_t(0xF0D091646F294D12),
	uint64_t(0x57B82A89684031D1), uint64_t(0xEFD95A5A61BE0B6B),
	uint64_t(0x2FBD12E969F2F29A), uint64_t(0x9BD37013FEFF9FE8),
	uint64_t(0x3F9B0404D6085A06), uint64_t(0x4940C1F3166CFE15),
	uint64_t(0x09542C4DCDF3DEFB), uint64_t(0xB4C5218385CD5CE3),
	uint64_t(0xC935B7DC4462A641), uint64_t(0x3417F8A68ED3B63F),
	uint64_t(0xB80959295B215B40), uint64_t(0xF99CDAEF3B8C8572),
	uint64_t(0x018C0614F8FCB95D), uint64_t(0x1B14ACCD1A3ACDF3),
	uint64_t(0x84D471F200BB732D), uint64_t(0xC1A3110E95E8DA16),
	uint64_t(0x430A7220BF1A82B8), uint64_t(0xB77E090D39DF210E),
	uint64_t(0x5EF4BD9F3CD05E9D), uint64_t(0x9D4FF6DA7E57A444),
	uint64_t(0xDA1D60E183D4A5F8), uint64_t(0xB287C38417998E47),
	uint64_t(0xFE3EDC121BB31886), uint64_t(0xC7FE3CCC980CCBEF),
	uint64_t(0xE46FB590189BFD03), uint64_t(0x3732FD469A4C57DC),
	uint64_t(0x7EF700A07CF1AD65), uint64_t(0x59C64468A31D8859),
	uint64_t(0x762FB0B4D45B61F6), uint64_t(0x155BAED099047718),
	uint64_t(0x68755E4C3D50BAA6), uint64_t(0xE9214E7F22D8B4DF),
	uint64_t(0x2ADDBF532EAC95F4), uint64_t(0x32AE3909B4BD0109),
	uint64_t(0x834DF537B08E3450), uint64_t(0xFA209DA84220728D),
	uint64_t(0x9E691D9B9EFE23F7), uint64_t(0x0446D288C4AE8D7F),
	uint64_t(0x7B4CC524E169785B), uint64_t(0x21D87F0135CA1385),
	uint64_t(0xCEBB400F137B8AA5), uint64_t(0x272E2B66580796BE),
	uint64_t(0x3612264125C2B0DE), uint64_t(0x057702BDAD1EFBB2),
	uint64_t(0xD4BABB8EACF84BE9), uint64_t(0x91583139641BC67B),
	uint64_t(0x8BDC2DE08036E024), uint64_t(0x603C8156F49F68ED),
	uint64_t(0xF7D236F7DBEF5111), uint64_t(0x9727C4598AD21E80),
	uint64_t(0xA08A0896670A5FD7), uint64_t(0xCB4A8F4309EBA9CB),
	uint64_t(0x81AF564B0F7036A1), uint64_t(0xC0B99AA778199ABD),
	uint64_t(0x959F1EC83FC8E952), uint64_t(0x8C505077794A81B9),
	uint64_t(0x3ACAAF8F056338F0), uint64_t(0x07B43F50627A6778),
	uint64_t(0x4A44AB49F5ECCC77), uint64_t(0x3BC3D6E4B679EE98),
	uint64_t(0x9CC0D4D1CF14108C), uint64_t(0x4406C00B206BC8A0),
	uint64_t(0x82A18854C8D72D89), uint64_t(0x67E366B35C3C432C),
	uint64_t(0xB923DD61102B37F2), uint64_t(0x56AB2779D884271D),
	uint64_t(0xBE83E1B0FF1525AF), uint64_t(0xFB7C65D4217E49A9),
	uint64_t(0x6BDBE0E76D48E7D4), uint64_t(0x08DF828745D9179E),
	uint64_t(0x22EA6A9ADD53BD34), uint64_t(0xE36E141C5622200A),
	uint64_t(0x7F805D1B8CB750EE), uint64_t(0xAFE5C7A59F58E837),
	uint64_t(0xE27F996A4FB1C23C), uint64_t(0xD3867DFB0775F0D0),
	uint64_t(0xD0E673DE6E88891A), uint64_t(0x123AEB9EAFB86C25),
	uint64_t(0x30F1D5D5C145B895), uint64_t(0xBB434A2DEE7269E7),
	uint64_t(0x78CB67ECF931FA38), uint64_t(0xF33B0372323BBF9C),
	uint64_t(0x52D66336FB279C74), uint64_t(0x505F33AC0AFB4EAA),
	uint64_t(0xE8A5CD99A2CCE187), uint64_t(0x534974801E2D30BB),
	uint64_t(0x8D2D5711D5876D90), uint64_t(0x1F1A412891BC038E),
	uint64_t(0xD6E2E71D82E56648), uint64_t(0x74036C3A497732B7),
	uint64_t(0x89B67ED96361F5AB), uint64_t(0xFFED95D8F1EA02A2),
	uint64_t(0xE72B3BD61464D43D), uint64_t(0xA6300F170BDC4820),
	uint64_t(0xEBC18760ED78A77A) };

const uint64_t Tiger2::T2[256] = { uint64_t(0xE6A6BE5A05A12138),
	uint64_t(0xB5A122A5B4F87C98), uint64_t(0x563C6089140B6990),
	uint64_t(0x4C46CB2E391F5DD5), uint64_t(0xD932ADDBC9B79434),
	uint64_t(0x08EA70E42015AFF5), uint64_t(0xD765A6673E478CF1),
	uint64_t(0xC4FB757EAB278D99), uint64_t(0xDF11C6862D6E0692),
	uint64_t(0xDDEB84F10D7F3B16), uint64_t(0x6F2EF604A665EA04),
	uint64_t(0x4A8E0F0FF0E0DFB3), uint64_t(0xA5EDEEF83DBCBA51),
	uint64_t(0xFC4F0A2A0EA4371E), uint64_t(0xE83E1DA85CB38429),
	uint64_t(0xDC8FF882BA1B1CE2), uint64_t(0xCD45505E8353E80D),
	uint64_t(0x18D19A00D4DB0717), uint64_t(0x34A0CFEDA5F38101),
	uint64_t(0x0BE77E518887CAF2), uint64_t(0x1E341438B3C45136),
	uint64_t(0xE05797F49089CCF9), uint64_t(0xFFD23F9DF2591D14),
	uint64_t(0x543DDA228595C5CD), uint64_t(0x661F81FD99052A33),
	uint64_t(0x8736E641DB0F7B76), uint64_t(0x15227725418E5307),
	uint64_t(0xE25F7F46162EB2FA), uint64_t(0x48A8B2126C13D9FE),
	uint64_t(0xAFDC541792E76EEA), uint64_t(0x03D912BFC6D1898F),
	uint64_t(0x31B1AAFA1B83F51B), uint64_t(0xF1AC2796E42AB7D9),
	uint64_t(0x40A3A7D7FCD2EBAC), uint64_t(0x1056136D0AFBBCC5),
	uint64_t(0x7889E1DD9A6D0C85), uint64_t(0xD33525782A7974AA),
	uint64_t(0xA7E25D09078AC09B), uint64_t(0xBD4138B3EAC6EDD0),
	uint64_t(0x920ABFBE71EB9E70), uint64_t(0xA2A5D0F54FC2625C),
	uint64_t(0xC054E36B0B1290A3), uint64_t(0xF6DD59FF62FE932B),
	uint64_t(0x3537354511A8AC7D), uint64_t(0xCA845E9172FADCD4),
	uint64_t(0x84F82B60329D20DC), uint64_t(0x79C62CE1CD672F18),
	uint64_t(0x8B09A2ADD124642C), uint64_t(0xD0C1E96A19D9E726),
	uint64_t(0x5A786A9B4BA9500C), uint64_t(0x0E020336634C43F3),
	uint64_t(0xC17B474AEB66D822), uint64_t(0x6A731AE3EC9BAAC2),
	uint64_t(0x8226667AE0840258), uint64_t(0x67D4567691CAECA5),
	uint64_t(0x1D94155C4875ADB5), uint64_t(0x6D00FD985B813FDF),
	uint64_t(0x51286EFCB774CD06), uint64_t(0x5E8834471FA744AF),
	uint64_t(0xF72CA0AEE761AE2E), uint64_t(0xBE40E4CDAEE8E09A),
	uint64_t(0xE9970BBB5118F665), uint64_t(0x726E4BEB33DF1964),
	uint64_t(0x703B000729199762), uint64_t(0x4631D816F5EF30A7),
	uint64_t(0xB880B5B51504A6BE), uint64_t(0x641793C37ED84B6C),
	uint64_t(0x7B21ED77F6E97D96), uint64_t(0x776306312EF96B73),
	uint64_t(0xAE528948E86FF3F4), uint64_t(0x53DBD7F286A3F8F8),
	uint64_t(0x16CADCE74CFC1063), uint64_t(0x005C19BDFA52C6DD),
	uint64_t(0x68868F5D64D46AD3), uint64_t(0x3A9D512CCF1E186A),
	uint64_t(0x367E62C2385660AE), uint64_t(0xE359E7EA77DCB1D7),
	uint64_t(0x526C0773749ABE6E), uint64_t(0x735AE5F9D09F734B),
	uint64_t(0x493FC7CC8A558BA8), uint64_t(0xB0B9C1533041AB45),
	uint64_t(0x321958BA470A59BD), uint64_t(0x852DB00B5F46C393),
	uint64_t(0x91209B2BD336B0E5), uint64_t(0x6E604F7D659EF19F),
	uint64_t(0xB99A8AE2782CCB24), uint64_t(0xCCF52AB6C814C4C7),
	uint64_t(0x4727D9AFBE11727B), uint64_t(0x7E950D0C0121B34D),
	uint64_t(0x756F435670AD471F), uint64_t(0xF5ADD442615A6849),
	uint64_t(0x4E87E09980B9957A), uint64_t(0x2ACFA1DF50AEE355),
	uint64_t(0xD898263AFD2FD556), uint64_t(0xC8F4924DD80C8FD6),
	uint64_t(0xCF99CA3D754A173A), uint64_t(0xFE477BACAF91BF3C),
	uint64_t(0xED5371F6D690C12D), uint64_t(0x831A5C285E687094),
	uint64_t(0xC5D3C90A3708A0A4), uint64_t(0x0F7F903717D06580),
	uint64_t(0x19F9BB13B8FDF27F), uint64_t(0xB1BD6F1B4D502843),
	uint64_t(0x1C761BA38FFF4012), uint64_t(0x0D1530C4E2E21F3B),
	uint64_t(0x8943CE69A7372C8A), uint64_t(0xE5184E11FEB5CE66),
	uint64_t(0x618BDB80BD736621), uint64_t(0x7D29BAD68B574D0B),
	uint64_t(0x81BB613E25E6FE5B), uint64_t(0x071C9C10BC07913F),
	uint64_t(0xC7BEEB7909AC2D97), uint64_t(0xC3E58D353BC5D757),
	uint64_t(0xEB017892F38F61E8), uint64_t(0xD4EFFB9C9B1CC21A),
	uint64_t(0x99727D26F494F7AB), uint64_t(0xA3E063A2956B3E03),
	uint64_t(0x9D4A8B9A4AA09C30), uint64_t(0x3F6AB7D500090FB4),
	uint64_t(0x9CC0F2A057268AC0), uint64_t(0x3DEE9D2DEDBF42D1),
	uint64_t(0x330F49C87960A972), uint64_t(0xC6B2720287421B41),
	uint64_t(0x0AC59EC07C00369C), uint64_t(0xEF4EAC49CB353425),
	uint64_t(0xF450244EEF0129D8), uint64_t(0x8ACC46E5CAF4DEB6),
	uint64_t(0x2FFEAB63989263F7), uint64_t(0x8F7CB9FE5D7A4578),
	uint64_t(0x5BD8F7644E634635), uint64_t(0x427A7315BF2DC900),
	uint64_t(0x17D0C4AA2125261C), uint64_t(0x3992486C93518E50),
	uint64_t(0xB4CBFEE0A2D7D4C3), uint64_t(0x7C75D6202C5DDD8D),
	uint64_t(0xDBC295D8E35B6C61), uint64_t(0x60B369D302032B19),
	uint64_t(0xCE42685FDCE44132), uint64_t(0x06F3DDB9DDF65610),
	uint64_t(0x8EA4D21DB5E148F0), uint64_t(0x20B0FCE62FCD496F),
	uint64_t(0x2C1B912358B0EE31), uint64_t(0xB28317B818F5A308),
	uint64_t(0xA89C1E189CA6D2CF), uint64_t(0x0C6B18576AAADBC8),
	uint64_t(0xB65DEAA91299FAE3), uint64_t(0xFB2B794B7F1027E7),
	uint64_t(0x04E4317F443B5BEB), uint64_t(0x4B852D325939D0A6),
	uint64_t(0xD5AE6BEEFB207FFC), uint64_t(0x309682B281C7D374),
	uint64_t(0xBAE309A194C3B475), uint64_t(0x8CC3F97B13B49F05),
	uint64_t(0x98A9422FF8293967), uint64_t(0x244B16B01076FF7C),
	uint64_t(0xF8BF571C663D67EE), uint64_t(0x1F0D6758EEE30DA1),
	uint64_t(0xC9B611D97ADEB9B7), uint64_t(0xB7AFD5887B6C57A2),
	uint64_t(0x6290AE846B984FE1), uint64_t(0x94DF4CDEACC1A5FD),
	uint64_t(0x058A5BD1C5483AFF), uint64_t(0x63166CC142BA3C37),
	uint64_t(0x8DB8526EB2F76F40), uint64_t(0xE10880036F0D6D4E),
	uint64_t(0x9E0523C9971D311D), uint64_t(0x45EC2824CC7CD691),
	uint64_t(0x575B8359E62382C9), uint64_t(0xFA9E400DC4889995),
	uint64_t(0xD1823ECB45721568), uint64_t(0xDAFD983B8206082F),
	uint64_t(0xAA7D29082386A8CB), uint64_t(0x269FCD4403B87588),
	uint64_t(0x1B91F5F728BDD1E0), uint64_t(0xE4669F39040201F6),
	uint64_t(0x7A1D7C218CF04ADE), uint64_t(0x65623C29D79CE5CE),
	uint64_t(0x2368449096C00BB1), uint64_t(0xAB9BF1879DA503BA),
	uint64_t(0xBC23ECB1A458058E), uint64_t(0x9A58DF01BB401ECC),
	uint64_t(0xA070E868A85F143D), uint64_t(0x4FF188307DF2239E),
	uint64_t(0x14D565B41A641183), uint64_t(0xEE13337452701602),
	uint64_t(0x950E3DCF3F285E09), uint64_t(0x59930254B9C80953),
	uint64_t(0x3BF299408930DA6D), uint64_t(0xA955943F53691387),
	uint64_t(0xA15EDECAA9CB8784), uint64_t(0x29142127352BE9A0),
	uint64_t(0x76F0371FFF4E7AFB), uint64_t(0x0239F450274F2228),
	uint64_t(0xBB073AF01D5E868B), uint64_t(0xBFC80571C10E96C1),
	uint64_t(0xD267088568222E23), uint64_t(0x9671A3D48E80B5B0),
	uint64_t(0x55B5D38AE193BB81), uint64_t(0x693AE2D0A18B04B8),
	uint64_t(0x5C48B4ECADD5335F), uint64_t(0xFD743B194916A1CA),
	uint64_t(0x2577018134BE98C4), uint64_t(0xE77987E83C54A4AD),
	uint64_t(0x28E11014DA33E1B9), uint64_t(0x270CC59E226AA213),
	uint64_t(0x71495F756D1A5F60), uint64_t(0x9BE853FB60AFEF77),
	uint64_t(0xADC786A7F7443DBF), uint64_t(0x0904456173B29A82),
	uint64_t(0x58BC7A66C232BD5E), uint64_t(0xF306558C673AC8B2),
	uint64_t(0x41F639C6B6C9772A), uint64_t(0x216DEFE99FDA35DA),
	uint64_t(0x11640CC71C7BE615), uint64_t(0x93C43694565C5527),
	uint64_t(0xEA038E6246777839), uint64_t(0xF9ABF3CE5A3E2469),
	uint64_t(0x741E768D0FD312D2), uint64_t(0x0144B883CED652C6),
	uint64_t(0xC20B5A5BA33F8552), uint64_t(0x1AE69633C3435A9D),
	uint64_t(0x97A28CA4088CFDEC), uint64_t(0x8824A43C1E96F420),
	uint64_t(0x37612FA66EEEA746), uint64_t(0x6B4CB165F9CF0E5A),
	uint64_t(0x43AA1C06A0ABFB4A), uint64_t(0x7F4DC26FF162796B),
	uint64_t(0x6CBACC8E54ED9B0F), uint64_t(0xA6B7FFEFD2BB253E),
	uint64_t(0x2E25BC95B0A29D4F), uint64_t(0x86D6A58BDEF1388C),
	uint64_t(0xDED74AC576B6F054), uint64_t(0x8030BDBC2B45805D),
	uint64_t(0x3C81AF70E94D9289), uint64_t(0x3EFF6DDA9E3100DB),
	uint64_t(0xB38DC39FDFCC8847), uint64_t(0x123885528D17B87E),
	uint64_t(0xF2DA0ED240B1B642), uint64_t(0x44CEFADCD54BF9A9),
	uint64_t(0x1312200E433C7EE6), uint64_t(0x9FFCC84F3A78C748),
	uint64_t(0xF0CD1F72248576BB), uint64_t(0xEC6974053638CFE4),
	uint64_t(0x2BA7B67C0CEC4E4C), uint64_t(0xAC2F4DF3E5CE32ED),
	uint64_t(0xCB33D14326EA4C11), uint64_t(0xA4E9044CC77E58BC),
	uint64_t(0x5F513293D934FCEF), uint64_t(0x5DC9645506E55444),
	uint64_t(0x50DE418F317DE40A), uint64_t(0x388CB31A69DDE259),
	uint64_t(0x2DB4A83455820A86), uint64_t(0x9010A91E84711AE9),
	uint64_t(0x4DF7F0B7B1498371), uint64_t(0xD62A2EABC0977179),
	uint64_t(0x22FAC097AA8D5C0E) };

const uint64_t Tiger2::T3[256] = { uint64_t(0xF49FCC2FF1DAF39B),
	  uint64_t(0x487FD5C66FF29281), uint64_t(0xE8A30667FCDCA83F),
	  uint64_t(0x2C9B4BE3D2FCCE63), uint64_t(0xDA3FF74B93FBBBC2),
	  uint64_t(0x2FA165D2FE70BA66), uint64_t(0xA103E279970E93D4),
	  uint64_t(0xBECDEC77B0E45E71), uint64_t(0xCFB41E723985E497),
	  uint64_t(0xB70AAA025EF75017), uint64_t(0xD42309F03840B8E0),
	  uint64_t(0x8EFC1AD035898579), uint64_t(0x96C6920BE2B2ABC5),
	  uint64_t(0x66AF4163375A9172), uint64_t(0x2174ABDCCA7127FB),
	  uint64_t(0xB33CCEA64A72FF41), uint64_t(0xF04A4933083066A5),
	  uint64_t(0x8D970ACDD7289AF5), uint64_t(0x8F96E8E031C8C25E),
	  uint64_t(0xF3FEC02276875D47), uint64_t(0xEC7BF310056190DD),
	  uint64_t(0xF5ADB0AEBB0F1491), uint64_t(0x9B50F8850FD58892),
	  uint64_t(0x4975488358B74DE8), uint64_t(0xA3354FF691531C61),
	  uint64_t(0x0702BBE481D2C6EE), uint64_t(0x89FB24057DEDED98),
	  uint64_t(0xAC3075138596E902), uint64_t(0x1D2D3580172772ED),
	  uint64_t(0xEB738FC28E6BC30D), uint64_t(0x5854EF8F63044326),
	  uint64_t(0x9E5C52325ADD3BBE), uint64_t(0x90AA53CF325C4623),
	  uint64_t(0xC1D24D51349DD067), uint64_t(0x2051CFEEA69EA624),
	  uint64_t(0x13220F0A862E7E4F), uint64_t(0xCE39399404E04864),
	  uint64_t(0xD9C42CA47086FCB7), uint64_t(0x685AD2238A03E7CC),
	  uint64_t(0x066484B2AB2FF1DB), uint64_t(0xFE9D5D70EFBF79EC),
	  uint64_t(0x5B13B9DD9C481854), uint64_t(0x15F0D475ED1509AD),
	  uint64_t(0x0BEBCD060EC79851), uint64_t(0xD58C6791183AB7F8),
	  uint64_t(0xD1187C5052F3EEE4), uint64_t(0xC95D1192E54E82FF),
	  uint64_t(0x86EEA14CB9AC6CA2), uint64_t(0x3485BEB153677D5D),
	  uint64_t(0xDD191D781F8C492A), uint64_t(0xF60866BAA784EBF9),
	  uint64_t(0x518F643BA2D08C74), uint64_t(0x8852E956E1087C22),
	  uint64_t(0xA768CB8DC410AE8D), uint64_t(0x38047726BFEC8E1A),
	  uint64_t(0xA67738B4CD3B45AA), uint64_t(0xAD16691CEC0DDE19),
	  uint64_t(0xC6D4319380462E07), uint64_t(0xC5A5876D0BA61938),
	  uint64_t(0x16B9FA1FA58FD840), uint64_t(0x188AB1173CA74F18),
	  uint64_t(0xABDA2F98C99C021F), uint64_t(0x3E0580AB134AE816),
	  uint64_t(0x5F3B05B773645ABB), uint64_t(0x2501A2BE5575F2F6),
	  uint64_t(0x1B2F74004E7E8BA9), uint64_t(0x1CD7580371E8D953),
	  uint64_t(0x7F6ED89562764E30), uint64_t(0xB15926FF596F003D),
	  uint64_t(0x9F65293DA8C5D6B9), uint64_t(0x6ECEF04DD690F84C),
	  uint64_t(0x4782275FFF33AF88), uint64_t(0xE41433083F820801),
	  uint64_t(0xFD0DFE409A1AF9B5), uint64_t(0x4325A3342CDB396B),
	  uint64_t(0x8AE77E62B301B252), uint64_t(0xC36F9E9F6655615A),
	  uint64_t(0x85455A2D92D32C09), uint64_t(0xF2C7DEA949477485),
	  uint64_t(0x63CFB4C133A39EBA), uint64_t(0x83B040CC6EBC5462),
	  uint64_t(0x3B9454C8FDB326B0), uint64_t(0x56F56A9E87FFD78C),
	  uint64_t(0x2DC2940D99F42BC6), uint64_t(0x98F7DF096B096E2D),
	  uint64_t(0x19A6E01E3AD852BF), uint64_t(0x42A99CCBDBD4B40B),
	  uint64_t(0xA59998AF45E9C559), uint64_t(0x366295E807D93186),
	  uint64_t(0x6B48181BFAA1F773), uint64_t(0x1FEC57E2157A0A1D),
	  uint64_t(0x4667446AF6201AD5), uint64_t(0xE615EBCACFB0F075),
	  uint64_t(0xB8F31F4F68290778), uint64_t(0x22713ED6CE22D11E),
	  uint64_t(0x3057C1A72EC3C93B), uint64_t(0xCB46ACC37C3F1F2F),
	  uint64_t(0xDBB893FD02AAF50E), uint64_t(0x331FD92E600B9FCF),
	  uint64_t(0xA498F96148EA3AD6), uint64_t(0xA8D8426E8B6A83EA),
	  uint64_t(0xA089B274B7735CDC), uint64_t(0x87F6B3731E524A11),
	  uint64_t(0x118808E5CBC96749), uint64_t(0x9906E4C7B19BD394),
	  uint64_t(0xAFED7F7E9B24A20C), uint64_t(0x6509EADEEB3644A7),
	  uint64_t(0x6C1EF1D3E8EF0EDE), uint64_t(0xB9C97D43E9798FB4),
	  uint64_t(0xA2F2D784740C28A3), uint64_t(0x7B8496476197566F),
	  uint64_t(0x7A5BE3E6B65F069D), uint64_t(0xF96330ED78BE6F10),
	  uint64_t(0xEEE60DE77A076A15), uint64_t(0x2B4BEE4AA08B9BD0),
	  uint64_t(0x6A56A63EC7B8894E), uint64_t(0x02121359BA34FEF4),
	  uint64_t(0x4CBF99F8283703FC), uint64_t(0x398071350CAF30C8),
	  uint64_t(0xD0A77A89F017687A), uint64_t(0xF1C1A9EB9E423569),
	  uint64_t(0x8C7976282DEE8199), uint64_t(0x5D1737A5DD1F7ABD),
	  uint64_t(0x4F53433C09A9FA80), uint64_t(0xFA8B0C53DF7CA1D9),
	  uint64_t(0x3FD9DCBC886CCB77), uint64_t(0xC040917CA91B4720),
	  uint64_t(0x7DD00142F9D1DCDF), uint64_t(0x8476FC1D4F387B58),
	  uint64_t(0x23F8E7C5F3316503), uint64_t(0x032A2244E7E37339),
	  uint64_t(0x5C87A5D750F5A74B), uint64_t(0x082B4CC43698992E),
	  uint64_t(0xDF917BECB858F63C), uint64_t(0x3270B8FC5BF86DDA),
	  uint64_t(0x10AE72BB29B5DD76), uint64_t(0x576AC94E7700362B),
	  uint64_t(0x1AD112DAC61EFB8F), uint64_t(0x691BC30EC5FAA427),
	  uint64_t(0xFF246311CC327143), uint64_t(0x3142368E30E53206),
	  uint64_t(0x71380E31E02CA396), uint64_t(0x958D5C960AAD76F1),
	  uint64_t(0xF8D6F430C16DA536), uint64_t(0xC8FFD13F1BE7E1D2),
	  uint64_t(0x7578AE66004DDBE1), uint64_t(0x05833F01067BE646),
	  uint64_t(0xBB34B5AD3BFE586D), uint64_t(0x095F34C9A12B97F0),
	  uint64_t(0x247AB64525D60CA8), uint64_t(0xDCDBC6F3017477D1),
	  uint64_t(0x4A2E14D4DECAD24D), uint64_t(0xBDB5E6D9BE0A1EEB),
	  uint64_t(0x2A7E70F7794301AB), uint64_t(0xDEF42D8A270540FD),
	  uint64_t(0x01078EC0A34C22C1), uint64_t(0xE5DE511AF4C16387),
	  uint64_t(0x7EBB3A52BD9A330A), uint64_t(0x77697857AA7D6435),
	  uint64_t(0x004E831603AE4C32), uint64_t(0xE7A21020AD78E312),
	  uint64_t(0x9D41A70C6AB420F2), uint64_t(0x28E06C18EA1141E6),
	  uint64_t(0xD2B28CBD984F6B28), uint64_t(0x26B75F6C446E9D83),
	  uint64_t(0xBA47568C4D418D7F), uint64_t(0xD80BADBFE6183D8E),
	  uint64_t(0x0E206D7F5F166044), uint64_t(0xE258A43911CBCA3E),
	  uint64_t(0x723A1746B21DC0BC), uint64_t(0xC7CAA854F5D7CDD3),
	  uint64_t(0x7CAC32883D261D9C), uint64_t(0x7690C26423BA942C),
	  uint64_t(0x17E55524478042B8), uint64_t(0xE0BE477656A2389F),
	  uint64_t(0x4D289B5E67AB2DA0), uint64_t(0x44862B9C8FBBFD31),
	  uint64_t(0xB47CC8049D141365), uint64_t(0x822C1B362B91C793),
	  uint64_t(0x4EB14655FB13DFD8), uint64_t(0x1ECBBA0714E2A97B),
	  uint64_t(0x6143459D5CDE5F14), uint64_t(0x53A8FBF1D5F0AC89),
	  uint64_t(0x97EA04D81C5E5B00), uint64_t(0x622181A8D4FDB3F3),
	  uint64_t(0xE9BCD341572A1208), uint64_t(0x1411258643CCE58A),
	  uint64_t(0x9144C5FEA4C6E0A4), uint64_t(0x0D33D06565CF620F),
	  uint64_t(0x54A48D489F219CA1), uint64_t(0xC43E5EAC6D63C821),
	  uint64_t(0xA9728B3A72770DAF), uint64_t(0xD7934E7B20DF87EF),
	  uint64_t(0xE35503B61A3E86E5), uint64_t(0xCAE321FBC819D504),
	  uint64_t(0x129A50B3AC60BFA6), uint64_t(0xCD5E68EA7E9FB6C3),
	  uint64_t(0xB01C90199483B1C7), uint64_t(0x3DE93CD5C295376C),
	  uint64_t(0xAED52EDF2AB9AD13), uint64_t(0x2E60F512C0A07884),
	  uint64_t(0xBC3D86A3E36210C9), uint64_t(0x35269D9B163951CE),
	  uint64_t(0x0C7D6E2AD0CDB5FA), uint64_t(0x59E86297D87F5733),
	  uint64_t(0x298EF221898DB0E7), uint64_t(0x55000029D1A5AA7E),
	  uint64_t(0x8BC08AE1B5061B45), uint64_t(0xC2C31C2B6C92703A),
	  uint64_t(0x94CC596BAF25EF42), uint64_t(0x0A1D73DB22540456),
	  uint64_t(0x04B6A0F9D9C4179A), uint64_t(0xEFFDAFA2AE3D3C60),
	  uint64_t(0xF7C8075BB49496C4), uint64_t(0x9CC5C7141D1CD4E3),
	  uint64_t(0x78BD1638218E5534), uint64_t(0xB2F11568F850246A),
	  uint64_t(0xEDFABCFA9502BC29), uint64_t(0x796CE5F2DA23051B),
	  uint64_t(0xAAE128B0DC93537C), uint64_t(0x3A493DA0EE4B29AE),
	  uint64_t(0xB5DF6B2C416895D7), uint64_t(0xFCABBD25122D7F37),
	  uint64_t(0x70810B58105DC4B1), uint64_t(0xE10FDD37F7882A90),
	  uint64_t(0x524DCAB5518A3F5C), uint64_t(0x3C9E85878451255B),
	  uint64_t(0x4029828119BD34E2), uint64_t(0x74A05B6F5D3CECCB),
	  uint64_t(0xB610021542E13ECA), uint64_t(0x0FF979D12F59E2AC),
	  uint64_t(0x6037DA27E4F9CC50), uint64_t(0x5E92975A0DF1847D),
	  uint64_t(0xD66DE190D3E623FE), uint64_t(0x5032D6B87B568048),
	  uint64_t(0x9A36B7CE8235216E), uint64_t(0x80272A7A24F64B4A),
	  uint64_t(0x93EFED8B8C6916F7), uint64_t(0x37DDBFF44CCE1555),
	  uint64_t(0x4B95DB5D4B99BD25), uint64_t(0x92D3FDA169812FC0),
	  uint64_t(0xFB1A4A9A90660BB6), uint64_t(0x730C196946A4B9B2),
	  uint64_t(0x81E289AA7F49DA68), uint64_t(0x64669A0F83B1A05F),
	  uint64_t(0x27B3FF7D9644F48B), uint64_t(0xCC6B615C8DB675B3),
	  uint64_t(0x674F20B9BCEBBE95), uint64_t(0x6F31238275655982),
	  uint64_t(0x5AE488713E45CF05), uint64_t(0xBF619F9954C21157),
	  uint64_t(0xEABAC46040A8EAE9), uint64_t(0x454C6FE9F2C0C1CD),
	  uint64_t(0x419CF6496412691C), uint64_t(0xD3DC3BEF265B0F70),
	  uint64_t(0x6D0E60F5C3578A9E) };

const uint64_t Tiger2::T4[256] = { uint64_t(0x5B0E608526323C55),
		uint64_t(0x1A46C1A9FA1B59F5), uint64_t(0xA9E245A17C4C8FFA),
		uint64_t(0x65CA5159DB2955D7), uint64_t(0x05DB0A76CE35AFC2),
		uint64_t(0x81EAC77EA9113D45), uint64_t(0x528EF88AB6AC0A0D),
		uint64_t(0xA09EA253597BE3FF), uint64_t(0x430DDFB3AC48CD56),
		uint64_t(0xC4B3A67AF45CE46F), uint64_t(0x4ECECFD8FBE2D05E),
		uint64_t(0x3EF56F10B39935F0), uint64_t(0x0B22D6829CD619C6),
		uint64_t(0x17FD460A74DF2069), uint64_t(0x6CF8CC8E8510ED40),
		uint64_t(0xD6C824BF3A6ECAA7), uint64_t(0x61243D581A817049),
		uint64_t(0x048BACB6BBC163A2), uint64_t(0xD9A38AC27D44CC32),
		uint64_t(0x7FDDFF5BAAF410AB), uint64_t(0xAD6D495AA804824B),
		uint64_t(0xE1A6A74F2D8C9F94), uint64_t(0xD4F7851235DEE8E3),
		uint64_t(0xFD4B7F886540D893), uint64_t(0x247C20042AA4BFDA),
		uint64_t(0x096EA1C517D1327C), uint64_t(0xD56966B4361A6685),
		uint64_t(0x277DA5C31221057D), uint64_t(0x94D59893A43ACFF7),
		uint64_t(0x64F0C51CCDC02281), uint64_t(0x3D33BCC4FF6189DB),
		uint64_t(0xE005CB184CE66AF1), uint64_t(0xFF5CCD1D1DB99BEA),
		uint64_t(0xB0B854A7FE42980F), uint64_t(0x7BD46A6A718D4B9F),
		uint64_t(0xD10FA8CC22A5FD8C), uint64_t(0xD31484952BE4BD31),
		uint64_t(0xC7FA975FCB243847), uint64_t(0x4886ED1E5846C407),
		uint64_t(0x28CDDB791EB70B04), uint64_t(0xC2B00BE2F573417F),
		uint64_t(0x5C9590452180F877), uint64_t(0x7A6BDDFFF370EB00),
		uint64_t(0xCE509E38D6D9D6A4), uint64_t(0xEBEB0F00647FA702),
		uint64_t(0x1DCC06CF76606F06), uint64_t(0xE4D9F28BA286FF0A),
		uint64_t(0xD85A305DC918C262), uint64_t(0x475B1D8732225F54),
		uint64_t(0x2D4FB51668CCB5FE), uint64_t(0xA679B9D9D72BBA20),
		uint64_t(0x53841C0D912D43A5), uint64_t(0x3B7EAA48BF12A4E8),
		uint64_t(0x781E0E47F22F1DDF), uint64_t(0xEFF20CE60AB50973),
		uint64_t(0x20D261D19DFFB742), uint64_t(0x16A12B03062A2E39),
		uint64_t(0x1960EB2239650495), uint64_t(0x251C16FED50EB8B8),
		uint64_t(0x9AC0C330F826016E), uint64_t(0xED152665953E7671),
		uint64_t(0x02D63194A6369570), uint64_t(0x5074F08394B1C987),
		uint64_t(0x70BA598C90B25CE1), uint64_t(0x794A15810B9742F6),
		uint64_t(0x0D5925E9FCAF8C6C), uint64_t(0x3067716CD868744E),
		uint64_t(0x910AB077E8D7731B), uint64_t(0x6A61BBDB5AC42F61),
		uint64_t(0x93513EFBF0851567), uint64_t(0xF494724B9E83E9D5),
		uint64_t(0xE887E1985C09648D), uint64_t(0x34B1D3C675370CFD),
		uint64_t(0xDC35E433BC0D255D), uint64_t(0xD0AAB84234131BE0),
		uint64_t(0x08042A50B48B7EAF), uint64_t(0x9997C4EE44A3AB35),
		uint64_t(0x829A7B49201799D0), uint64_t(0x263B8307B7C54441),
		uint64_t(0x752F95F4FD6A6CA6), uint64_t(0x927217402C08C6E5),
		uint64_t(0x2A8AB754A795D9EE), uint64_t(0xA442F7552F72943D),
		uint64_t(0x2C31334E19781208), uint64_t(0x4FA98D7CEAEE6291),
		uint64_t(0x55C3862F665DB309), uint64_t(0xBD0610175D53B1F3),
		uint64_t(0x46FE6CB840413F27), uint64_t(0x3FE03792DF0CFA59),
		uint64_t(0xCFE700372EB85E8F), uint64_t(0xA7BE29E7ADBCE118),
		uint64_t(0xE544EE5CDE8431DD), uint64_t(0x8A781B1B41F1873E),
		uint64_t(0xA5C94C78A0D2F0E7), uint64_t(0x39412E2877B60728),
		uint64_t(0xA1265EF3AFC9A62C), uint64_t(0xBCC2770C6A2506C5),
		uint64_t(0x3AB66DD5DCE1CE12), uint64_t(0xE65499D04A675B37),
		uint64_t(0x7D8F523481BFD216), uint64_t(0x0F6F64FCEC15F389),
		uint64_t(0x74EFBE618B5B13C8), uint64_t(0xACDC82B714273E1D),
		uint64_t(0xDD40BFE003199D17), uint64_t(0x37E99257E7E061F8),
		uint64_t(0xFA52626904775AAA), uint64_t(0x8BBBF63A463D56F9),
		uint64_t(0xF0013F1543A26E64), uint64_t(0xA8307E9F879EC898),
		uint64_t(0xCC4C27A4150177CC), uint64_t(0x1B432F2CCA1D3348),
		uint64_t(0xDE1D1F8F9F6FA013), uint64_t(0x606602A047A7DDD6),
		uint64_t(0xD237AB64CC1CB2C7), uint64_t(0x9B938E7225FCD1D3),
		uint64_t(0xEC4E03708E0FF476), uint64_t(0xFEB2FBDA3D03C12D),
		uint64_t(0xAE0BCED2EE43889A), uint64_t(0x22CB8923EBFB4F43),
		uint64_t(0x69360D013CF7396D), uint64_t(0x855E3602D2D4E022),
		uint64_t(0x073805BAD01F784C), uint64_t(0x33E17A133852F546),
		uint64_t(0xDF4874058AC7B638), uint64_t(0xBA92B29C678AA14A),
		uint64_t(0x0CE89FC76CFAADCD), uint64_t(0x5F9D4E0908339E34),
		uint64_t(0xF1AFE9291F5923B9), uint64_t(0x6E3480F60F4A265F),
		uint64_t(0xEEBF3A2AB29B841C), uint64_t(0xE21938A88F91B4AD),
		uint64_t(0x57DFEFF845C6D3C3), uint64_t(0x2F006B0BF62CAAF2),
		uint64_t(0x62F479EF6F75EE78), uint64_t(0x11A55AD41C8916A9),
		uint64_t(0xF229D29084FED453), uint64_t(0x42F1C27B16B000E6),
		uint64_t(0x2B1F76749823C074), uint64_t(0x4B76ECA3C2745360),
		uint64_t(0x8C98F463B91691BD), uint64_t(0x14BCC93CF1ADE66A),
		uint64_t(0x8885213E6D458397), uint64_t(0x8E177DF0274D4711),
		uint64_t(0xB49B73B5503F2951), uint64_t(0x10168168C3F96B6B),
		uint64_t(0x0E3D963B63CAB0AE), uint64_t(0x8DFC4B5655A1DB14),
		uint64_t(0xF789F1356E14DE5C), uint64_t(0x683E68AF4E51DAC1),
		uint64_t(0xC9A84F9D8D4B0FD9), uint64_t(0x3691E03F52A0F9D1),
		uint64_t(0x5ED86E46E1878E80), uint64_t(0x3C711A0E99D07150),
		uint64_t(0x5A0865B20C4E9310), uint64_t(0x56FBFC1FE4F0682E),
		uint64_t(0xEA8D5DE3105EDF9B), uint64_t(0x71ABFDB12379187A),
		uint64_t(0x2EB99DE1BEE77B9C), uint64_t(0x21ECC0EA33CF4523),
		uint64_t(0x59A4D7521805C7A1), uint64_t(0x3896F5EB56AE7C72),
		uint64_t(0xAA638F3DB18F75DC), uint64_t(0x9F39358DABE9808E),
		uint64_t(0xB7DEFA91C00B72AC), uint64_t(0x6B5541FD62492D92),
		uint64_t(0x6DC6DEE8F92E4D5B), uint64_t(0x353F57ABC4BEEA7E),
		uint64_t(0x735769D6DA5690CE), uint64_t(0x0A234AA642391484),
		uint64_t(0xF6F9508028F80D9D), uint64_t(0xB8E319A27AB3F215),
		uint64_t(0x31AD9C1151341A4D), uint64_t(0x773C22A57BEF5805),
		uint64_t(0x45C7561A07968633), uint64_t(0xF913DA9E249DBE36),
		uint64_t(0xDA652D9B78A64C68), uint64_t(0x4C27A97F3BC334EF),
		uint64_t(0x76621220E66B17F4), uint64_t(0x967743899ACD7D0B),
		uint64_t(0xF3EE5BCAE0ED6782), uint64_t(0x409F753600C879FC),
		uint64_t(0x06D09A39B5926DB6), uint64_t(0x6F83AEB0317AC588),
		uint64_t(0x01E6CA4A86381F21), uint64_t(0x66FF3462D19F3025),
		uint64_t(0x72207C24DDFD3BFB), uint64_t(0x4AF6B6D3E2ECE2EB),
		uint64_t(0x9C994DBEC7EA08DE), uint64_t(0x49ACE597B09A8BC4),
		uint64_t(0xB38C4766CF0797BA), uint64_t(0x131B9373C57C2A75),
		uint64_t(0xB1822CCE61931E58), uint64_t(0x9D7555B909BA1C0C),
		uint64_t(0x127FAFDD937D11D2), uint64_t(0x29DA3BADC66D92E4),
		uint64_t(0xA2C1D57154C2ECBC), uint64_t(0x58C5134D82F6FE24),
		uint64_t(0x1C3AE3515B62274F), uint64_t(0xE907C82E01CB8126),
		uint64_t(0xF8ED091913E37FCB), uint64_t(0x3249D8F9C80046C9),
		uint64_t(0x80CF9BEDE388FB63), uint64_t(0x1881539A116CF19E),
		uint64_t(0x5103F3F76BD52457), uint64_t(0x15B7E6F5AE47F7A8),
		uint64_t(0xDBD7C6DED47E9CCF), uint64_t(0x44E55C410228BB1A),
		uint64_t(0xB647D4255EDB4E99), uint64_t(0x5D11882BB8AAFC30),
		uint64_t(0xF5098BBB29D3212A), uint64_t(0x8FB5EA14E90296B3),
		uint64_t(0x677B942157DD025A), uint64_t(0xFB58E7C0A390ACB5),
		uint64_t(0x89D3674C83BD4A01), uint64_t(0x9E2DA4DF4BF3B93B),
		uint64_t(0xFCC41E328CAB4829), uint64_t(0x03F38C96BA582C52),
		uint64_t(0xCAD1BDBD7FD85DB2), uint64_t(0xBBB442C16082AE83),
		uint64_t(0xB95FE86BA5DA9AB0), uint64_t(0xB22E04673771A93F),
		uint64_t(0x845358C9493152D8), uint64_t(0xBE2A488697B4541E),
		uint64_t(0x95A2DC2DD38E6966), uint64_t(0xC02C11AC923C852B),
		uint64_t(0x2388B1990DF2A87B), uint64_t(0x7C8008FA1B4F37BE),
		uint64_t(0x1F70D0C84D54E503), uint64_t(0x5490ADEC7ECE57D4),
		uint64_t(0x002B3C27D9063A3A), uint64_t(0x7EAEA3848030A2BF),
		uint64_t(0xC602326DED2003C0), uint64_t(0x83A7287D69A94086),
		uint64_t(0xC57A5FCB30F57A8A), uint64_t(0xB56844E479EBE779),
		uint64_t(0xA373B40F05DCBCE9), uint64_t(0xD71A786E88570EE2),
		uint64_t(0x879CBACDBDE8F6A0), uint64_t(0x976AD1BCC164A32F),
		uint64_t(0xAB21E25E9666D78B), uint64_t(0x901063AAE5E5C33C),
		uint64_t(0x9818B34448698D90), uint64_t(0xE36487AE3E1E8ABB),
		uint64_t(0xAFBDF931893BDCB4), uint64_t(0x6345A0DC5FBBD519),
		uint64_t(0x8628FE269B9465CA), uint64_t(0x1E5D01603F9C51EC),
		uint64_t(0x4DE44006A15049B7), uint64_t(0xBF6C70E5F776CBB1),
		uint64_t(0x411218F2EF552BED), uint64_t(0xCB0C0708705A36A3),
		uint64_t(0xE74D14754F986044), uint64_t(0xCD56D9430EA8280E),
		uint64_t(0xC12591D7535F5065), uint64_t(0xC83223F1720AEF96),
		uint64_t(0xC3A0396F7363A51F) };


class Tiger2_3_128 : public Tiger2
{
public:
	Tiger2_3_128()
		: Tiger2(16, Rounds3)
	{} // end constructor
}; // end class Tiger2_3_128


class Tiger2_4_128 : public Tiger2
{
public:
	Tiger2_4_128()
		: Tiger2(16, Rounds4)
	{} // end constructor
}; // end class Tiger2_4_128


class Tiger2_5_128 : public Tiger2
{
public:
	Tiger2_5_128()
		: Tiger2(16, Rounds5)
	{} // end constructor
}; // end class Tiger2_5_128


class Tiger2_3_160 : public Tiger2
{
public:
	Tiger2_3_160()
		: Tiger2(20, Rounds3)
	{} // end constructor
}; // end class Tiger2_3_160


class Tiger2_4_160 : public Tiger2
{
public:
	Tiger2_4_160()
		: Tiger2(20, Rounds4)
	{} // end constructor
}; // end class Tiger2_4_160


class Tiger2_5_160 : public Tiger2
{
public:
	Tiger2_5_160()
		: Tiger2(20, Rounds5)
	{} // end constructor
}; // end class Tiger2_5_160


class Tiger2_3_192 : public Tiger2
{
public:
	Tiger2_3_192()
		: Tiger2(24, Rounds3)
	{} // end constructor
}; // end class Tiger2_3_192


class Tiger2_4_192 : public Tiger2
{
public:
	Tiger2_4_192()
		: Tiger2(24, Rounds4)
	{} // end constructor
}; // end class Tiger2_4_192


class Tiger2_5_192 : public Tiger2
{
public:
	Tiger2_5_192()
		: Tiger2(24, Rounds5)
	{} // end constructor
}; // end class Tiger2_5_192


class Tiger2_Base : public Tiger2
{
public:
	Tiger2_Base(const int32_t a_hash_size, const HashRounds &a_rounds)
		: Tiger2(a_hash_size, a_rounds)
	{} // end constructor
}; // end class Tiger_Base

#endif // !HLPTIGER2_H

