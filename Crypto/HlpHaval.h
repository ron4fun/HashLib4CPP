// ///////////////////////////////////////////////////////////////// //
// *C++ 11 HashFactory Library                                 
// *Copyright(c) 2018  Mbadiwe Nnaemeka Ronald                 
// *Github Repository <https://github.com/ron4fun>             

// *Distributed under the MIT software license, see the accompanying file LICENSE 
// *or visit http ://www.opensource.org/licenses/mit-license.php.           

// *Acknowledgements:                                  
// ** //
// *Thanks to Ugochukwu Mmaduekwe (https://github.com/Xor-el) for his creative        
// *development of this library in Pascal/Delphi                         

// ////////////////////////////////////////////////////// ///////////////

#ifndef HLPHAVAL_H
#define HLPHAVAL_H

#include "../Base/HlpHashCryptoNotBuildIn.h"
#include "../Base/HlpHashSize.h"
#include "../Base/HlpHashRounds.h"
#include "../Utils/HlpUtils.h"


class Haval : public BlockHash, public IICryptoNotBuildIn, public IITransformBlock
{
public:
	virtual void Initialize()
	{
		hash.get()[0] = 0x243F6A88;
		hash.get()[1] = 0x85A308D3;
		hash.get()[2] = 0x13198A2E;
		hash.get()[3] = 0x03707344;
		hash.get()[4] = 0xA4093822;
		hash.get()[5] = 0x299F31D0;
		hash.get()[6] = 0x082EFA98;
		hash.get()[7] = 0xEC4E6C89;

		BlockHash::Initialize();
	} // end function Initialize

	virtual string GetName() const
	{
		return Utils::string_format("%s_%u_%u",
			name, rounds, _HashSize * 8);
	}

protected:
	Haval(const HashRounds &a_rounds, const HashSize &a_hash_size)
		: BlockHash(int32_t(a_hash_size), 128)
	{
		name = __func__;

		_HashSize = GetHashSize();

		rounds = int32_t(a_rounds);
		hash = shared_ptr<uint32_t>(new uint32_t[8], default_delete<uint32_t[]>());
		temp = shared_ptr<uint32_t>(new uint32_t[32], default_delete<uint32_t[]>());
	} // end constructor

	~Haval()
	{} // end destructor

	virtual void Finish()
	{
		int32_t padindex;

		uint64_t bits = processed_bytes * 8;
		if (buffer->GetPos() < 118)
			padindex = 118 - buffer->GetPos();
		else
			padindex = 246 - buffer->GetPos();
		
		HashLibByteArray pad = HashLibByteArray(padindex + 10);

		pad[0] = uint8_t(0x01);

		pad[padindex] = uint8_t((rounds << 3) | (HAVAL_VERSION & 0x07));
		padindex++;
		pad[padindex] = uint8_t(_HashSize << 1);
		padindex++;

		bits = Converters::le2me_64(bits);

		Converters::ReadUInt64AsBytesLE(bits, pad, padindex);

		padindex = padindex + 8;

		TransformBytes(pad, 0, padindex);

	} // end function Finish

	virtual HashLibByteArray GetResult()
	{
		TailorDigestBits();

		HashLibByteArray result = HashLibByteArray((_HashSize >> 2) * sizeof(uint32_t));

		Converters::le32_copy(hash.get(), 0, &result[0], 0, (int32_t)result.size());

		return result;
	} // end function GetResult

protected:
	int32_t rounds, _HashSize;
	shared_ptr<uint32_t> hash, temp;

private:
	static const int32_t HAVAL_VERSION = 1;

	inline void TailorDigestBits()
	{
		register uint32_t t;
		
		if (_HashSize == 16)
		{
			t = (hash.get()[7] & 0x000000FF) | (hash.get()[6] & 0xFF000000) |
				(hash.get()[5] & 0x00FF0000) | (hash.get()[4] & 0x0000FF00);
				hash.get()[0] = hash.get()[0] + Bits::RotateRight32(t, 8);
			t = (hash.get()[7] & 0x0000FF00) | (hash.get()[6] & 0x000000FF) |
				(hash.get()[5] & 0xFF000000) | (hash.get()[4] & 0x00FF0000);
				hash.get()[1] = hash.get()[1] + Bits::RotateRight32(t, 16);
			t = (hash.get()[7] & 0x00FF0000) | (hash.get()[6] & 0x0000FF00) |
				(hash.get()[5] & 0x000000FF) | (hash.get()[4] & 0xFF000000);
				hash.get()[2] = hash.get()[2] + Bits::RotateRight32(t, 24);
			t = (hash.get()[7] & 0xFF000000) | (hash.get()[6] & 0x00FF0000) |
				(hash.get()[5] & 0x0000FF00) | (hash.get()[4] & 0x000000FF);
			hash.get()[3] = hash.get()[3] + t;
		} // end if

		else if (_HashSize == 20)
		{
			t = uint32_t(hash.get()[7] & 0x3F) | uint32_t(hash.get()[6] & (0x7F << 25))
				| uint32_t(hash.get()[5] & (0x3F << 19));
			hash.get()[0] = hash.get()[0] + Bits::RotateRight32(t, 19);
			t = uint32_t(hash.get()[7] & (0x3F << 6)) | uint32_t(hash.get()[6] & 0x3F) |
				uint32_t(hash.get()[5] & (0x7F << 25));
			hash.get()[1] = hash.get()[1] + Bits::RotateRight32(t, 25);
			t = (hash.get()[7] & (0x7F << 12)) | (hash.get()[6] & (0x3F << 6)) |
				(hash.get()[5] & 0x3F);
			hash.get()[2] = hash.get()[2] + t;
			t = (hash.get()[7] & (0x3F << 19)) | (hash.get()[6] & (0x7F << 12)) |
				(hash.get()[5] & (0x3F << 6));
			hash.get()[3] = hash.get()[3] + (t >> 6);
			t = (hash.get()[7] & (uint32_t(0x7F) << 25)) |
				uint32_t(hash.get()[6] & (0x3F << 19)) |
				uint32_t(hash.get()[5] & (0x7F << 12));
			hash.get()[4] = hash.get()[4] + (t >> 12);
		} // end else if

		else if (_HashSize == 24)
		{
			t = uint32_t(hash.get()[7] & 0x1F) | uint32_t(hash.get()[6] & (0x3F << 26));
			hash.get()[0] = hash.get()[0] + Bits::RotateRight32(t, 26);
			t = (hash.get()[7] & (0x1F << 5)) | (hash.get()[6] & 0x1F);
			hash.get()[1] = hash.get()[1] + t;
			t = (hash.get()[7] & (0x3F << 10)) | (hash.get()[6] & (0x1F << 5));
			hash.get()[2] = hash.get()[2] + (t >> 5);
			t = (hash.get()[7] & (0x1F << 16)) | (hash.get()[6] & (0x3F << 10));
			hash.get()[3] = hash.get()[3] + (t >> 10);
			t = (hash.get()[7] & (0x1F << 21)) | (hash.get()[6] & (0x1F << 16));
			hash.get()[4] = hash.get()[4] + (t >> 16);
			t = uint32_t(hash.get()[7] & (0x3F << 26)) |
				uint32_t(hash.get()[6] & (0x1F << 21));
			hash.get()[5] = hash.get()[5] + (t >> 21);
		} // end else if

		else if (_HashSize == 28)
		{
			hash.get()[0] = hash.get()[0] + ((hash.get()[7] >> 27) & 0x1F);
			hash.get()[1] = hash.get()[1] + ((hash.get()[7] >> 22) & 0x1F);
			hash.get()[2] = hash.get()[2] + ((hash.get()[7] >> 18) & 0x0F);
			hash.get()[3] = hash.get()[3] + ((hash.get()[7] >> 13) & 0x1F);
			hash.get()[4] = hash.get()[4] + ((hash.get()[7] >> 9) & 0x0F);
			hash.get()[5] = hash.get()[5] + ((hash.get()[7] >> 4) & 0x1F);
			hash.get()[6] = hash.get()[6] + (hash.get()[7] & 0x0F);
		} // end else if

	} // end function TailorDigestBits

public:
	static const char *InvalidHavalRound;
	static const char *InvalidHavalHashSize;

}; // end class Haval

const char *Haval::InvalidHavalRound = "Haval Round Must be 3, 4 | 5";
const char *Haval::InvalidHavalHashSize = "Haval HashSize Must be Either 128 bit(16 byte), 160 bit(20 byte), 192 bit(24 byte), 224 bit(28 byte) | 256 bit(32 byte)";


class Haval3 : public Haval
{
public:
	Haval3(const HashSize &a_hash_size)
		: Haval(Rounds3, a_hash_size)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval3 HashInstance = Haval3(HashSize(_HashSize));
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval3>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

protected:
	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t a, b, c, d, e, f, g, h, t;

		Converters::le32_copy(a_data, a_index, temp.get(), 0, 128);

		a = hash.get()[0];
		b = hash.get()[1];
		c = hash.get()[2];
		d = hash.get()[3];
		e = hash.get()[4];
		f = hash.get()[5];
		g = hash.get()[6];
		h = hash.get()[7];

		t = c & (e ^ d) ^ g & a ^ f & b ^ e;
		h = temp.get()[0] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(h, 11);

		t = b & (d ^ c) ^ f & h ^ e & a ^ d;
		g = temp.get()[1] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(g, 11);

		t = a & (c ^ b) ^ e & g ^ d & h ^ c;
		f = temp.get()[2] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(f, 11);

		t = h & (b ^ a) ^ d & f ^ c & g ^ b;
		e = temp.get()[3] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(e, 11);

		t = g & (a ^ h) ^ c & e ^ b & f ^ a;
		d = temp.get()[4] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(d, 11);

		t = f & (h ^ g) ^ b & d ^ a & e ^ h;
		c = temp.get()[5] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(c, 11);

		t = e & (g ^ f) ^ a & c ^ h & d ^ g;
		b = temp.get()[6] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(b, 11);

		t = d & (f ^ e) ^ h & b ^ g & c ^ f;
		a = temp.get()[7] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(a, 11);

		t = c & (e ^ d) ^ g & a ^ f & b ^ e;
		h = temp.get()[8] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(h, 11);

		t = b & (d ^ c) ^ f & h ^ e & a ^ d;
		g = temp.get()[9] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(g, 11);

		t = a & (c ^ b) ^ e & g ^ d & h ^ c;
		f = temp.get()[10] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(f, 11);

		t = h & (b ^ a) ^ d & f ^ c & g ^ b;
		e = temp.get()[11] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(e, 11);

		t = g & (a ^ h) ^ c & e ^ b & f ^ a;
		d = temp.get()[12] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(d, 11);

		t = f & (h ^ g) ^ b & d ^ a & e ^ h;
		c = temp.get()[13] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(c, 11);

		t = e & (g ^ f) ^ a & c ^ h & d ^ g;
		b = temp.get()[14] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(b, 11);

		t = d & (f ^ e) ^ h & b ^ g & c ^ f;
		a = temp.get()[15] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(a, 11);

		t = c & (e ^ d) ^ g & a ^ f & b ^ e;
		h = temp.get()[16] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(h, 11);

		t = b & (d ^ c) ^ f & h ^ e & a ^ d;
		g = temp.get()[17] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(g, 11);

		t = a & (c ^ b) ^ e & g ^ d & h ^ c;
		f = temp.get()[18] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(f, 11);

		t = h & (b ^ a) ^ d & f ^ c & g ^ b;
		e = temp.get()[19] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(e, 11);

		t = g & (a ^ h) ^ c & e ^ b & f ^ a;
		d = temp.get()[20] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(d, 11);

		t = f & (h ^ g) ^ b & d ^ a & e ^ h;
		c = temp.get()[21] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(c, 11);

		t = e & (g ^ f) ^ a & c ^ h & d ^ g;
		b = temp.get()[22] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(b, 11);

		t = d & (f ^ e) ^ h & b ^ g & c ^ f;
		a = temp.get()[23] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(a, 11);

		t = c & (e ^ d) ^ g & a ^ f & b ^ e;
		h = temp.get()[24] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(h, 11);

		t = b & (d ^ c) ^ f & h ^ e & a ^ d;
		g = temp.get()[25] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(g, 11);

		t = a & (c ^ b) ^ e & g ^ d & h ^ c;
		f = temp.get()[26] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(f, 11);

		t = h & (b ^ a) ^ d & f ^ c & g ^ b;
		e = temp.get()[27] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(e, 11);

		t = g & (a ^ h) ^ c & e ^ b & f ^ a;
		d = temp.get()[28] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(d, 11);

		t = f & (h ^ g) ^ b & d ^ a & e ^ h;
		c = temp.get()[29] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(c, 11);

		t = e & (g ^ f) ^ a & c ^ h & d ^ g;
		b = temp.get()[30] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(b, 11);

		t = d & (f ^ e) ^ h & b ^ g & c ^ f;
		a = temp.get()[31] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(a, 11);

		t = f & (d & ~a ^ b & c ^ e ^ g) ^ b & (d ^ c)
			^ a & c ^ g;
		h = temp.get()[5] + 0x452821E6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = e & (c & ~h ^ a & b ^ d ^ f) ^ a & (c ^ b)
			^ h & b ^ f;
		g = temp.get()[14] + 0x38D01377 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = d & (b & ~g ^ h & a ^ c ^ e) ^ h & (b ^ a)
			^ g & a ^ e;
		f = temp.get()[26] + 0xBE5466CF + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = c & (a & ~f ^ g & h ^ b ^ d) ^ g & (a ^ h)
			^ f & h ^ d;
		e = temp.get()[18] + 0x34E90C6C + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = b & (h & ~e ^ f & g ^ a ^ c) ^ f & (h ^ g)
			^ e & g ^ c;
		d = temp.get()[11] + 0xC0AC29B7 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = a & (g & ~d ^ e & f ^ h ^ b) ^ e & (g ^ f)
			^ d & f ^ b;
		c = temp.get()[28] + 0xC97C50DD + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = h & (f & ~c ^ d & e ^ g ^ a) ^ d & (f ^ e)
			^ c & e ^ a;
		b = temp.get()[7] + 0x3F84D5B5 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = g & (e & ~b ^ c & d ^ f ^ h) ^ c & (e ^ d)
			^ b & d ^ h;
		a = temp.get()[16] + 0xB5470917 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = f & (d & ~a ^ b & c ^ e ^ g) ^ b & (d ^ c)
			^ a & c ^ g;
		h = temp.get()[0] + 0x9216D5D9 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = e & (c & ~h ^ a & b ^ d ^ f) ^ a & (c ^ b)
			^ h & b ^ f;
		g = temp.get()[23] + 0x8979FB1B + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = d & (b & ~g ^ h & a ^ c ^ e) ^ h & (b ^ a)
			^ g & a ^ e;
		f = temp.get()[20] + 0xD1310BA6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = c & (a & ~f ^ g & h ^ b ^ d) ^ g & (a ^ h)
			^ f & h ^ d;
		e = temp.get()[22] + 0x98DFB5AC + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = b & (h & ~e ^ f & g ^ a ^ c) ^ f & (h ^ g)
			^ e & g ^ c;
		d = temp.get()[1] + 0x2FFD72DB + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = a & (g & ~d ^ e & f ^ h ^ b) ^ e & (g ^ f)
			^ d & f ^ b;
		c = temp.get()[10] + 0xD01ADFB7 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = h & (f & ~c ^ d & e ^ g ^ a) ^ d & (f ^ e)
			^ c & e ^ a;
		b = temp.get()[4] + 0xB8E1AFED + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = g & (e & ~b ^ c & d ^ f ^ h) ^ c & (e ^ d)
			^ b & d ^ h;
		a = temp.get()[8] + 0x6A267E96 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = f & (d & ~a ^ b & c ^ e ^ g) ^ b & (d ^ c)
			^ a & c ^ g;
		h = temp.get()[30] + 0xBA7C9045 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = e & (c & ~h ^ a & b ^ d ^ f) ^ a & (c ^ b)
			^ h & b ^ f;
		g = temp.get()[3] + 0xF12C7F99 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = d & (b & ~g ^ h & a ^ c ^ e) ^ h & (b ^ a)
			^ g & a ^ e;
		f = temp.get()[21] + 0x24A19947 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = c & (a & ~f ^ g & h ^ b ^ d) ^ g & (a ^ h)
			^ f & h ^ d;
		e = temp.get()[9] + 0xB3916CF7 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = b & (h & ~e ^ f & g ^ a ^ c) ^ f & (h ^ g)
			^ e & g ^ c;
		d = temp.get()[17] + 0x0801F2E2 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = a & (g & ~d ^ e & f ^ h ^ b) ^ e & (g ^ f)
			^ d & f ^ b;
		c = temp.get()[24] + 0x858EFC16 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = h & (f & ~c ^ d & e ^ g ^ a) ^ d & (f ^ e)
			^ c & e ^ a;
		b = temp.get()[29] + 0x636920D8 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = g & (e & ~b ^ c & d ^ f ^ h) ^ c & (e ^ d)
			^ b & d ^ h;
		a = temp.get()[6] + 0x71574E69 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = f & (d & ~a ^ b & c ^ e ^ g) ^ b & (d ^ c)
			^ a & c ^ g;
		h = temp.get()[19] + 0xA458FEA3 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = e & (c & ~h ^ a & b ^ d ^ f) ^ a & (c ^ b)
			^ h & b ^ f;
		g = temp.get()[12] + 0xF4933D7E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = d & (b & ~g ^ h & a ^ c ^ e) ^ h & (b ^ a)
			^ g & a ^ e;
		f = temp.get()[15] + 0x0D95748F + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = c & (a & ~f ^ g & h ^ b ^ d) ^ g & (a ^ h)
			^ f & h ^ d;
		e = temp.get()[13] + 0x728EB658 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = b & (h & ~e ^ f & g ^ a ^ c) ^ f & (h ^ g)
			^ e & g ^ c;
		d = temp.get()[2] + 0x718BCD58 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = a & (g & ~d ^ e & f ^ h ^ b) ^ e & (g ^ f)
			^ d & f ^ b;
		c = temp.get()[25] + 0x82154AEE + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = h & (f & ~c ^ d & e ^ g ^ a) ^ d & (f ^ e)
			^ c & e ^ a;
		b = temp.get()[31] + 0x7B54A41D + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = g & (e & ~b ^ c & d ^ f ^ h) ^ c & (e ^ d)
			^ b & d ^ h;
		a = temp.get()[27] + 0xC25A59B5 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = d & (f & e ^ g ^ a) ^ f & c ^ e & b ^ a;
		h = temp.get()[19] + 0x9C30D539 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = c & (e & d ^ f ^ h) ^ e & b ^ d & a ^ h;
		g = temp.get()[9] + 0x2AF26013 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = b & (d & c ^ e ^ g) ^ d & a ^ c & h ^ g;
		f = temp.get()[4] + 0xC5D1B023 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = a & (c & b ^ d ^ f) ^ c & h ^ b & g ^ f;
		e = temp.get()[20] + 0x286085F0 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = h & (b & a ^ c ^ e) ^ b & g ^ a & f ^ e;
		d = temp.get()[28] + 0xCA417918 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = g & (a & h ^ b ^ d) ^ a & f ^ h & e ^ d;
		c = temp.get()[17] + 0xB8DB38EF + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = f & (h & g ^ a ^ c) ^ h & e ^ g & d ^ c;
		b = temp.get()[8] + 0x8E79DCB0 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = e & (g & f ^ h ^ b) ^ g & d ^ f & c ^ b;
		a = temp.get()[22] + 0x603A180E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = d & (f & e ^ g ^ a) ^ f & c ^ e & b ^ a;
		h = temp.get()[29] + 0x6C9E0E8B + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = c & (e & d ^ f ^ h) ^ e & b ^ d & a ^ h;
		g = temp.get()[14] + 0xB01E8A3E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = b & (d & c ^ e ^ g) ^ d & a ^ c & h ^ g;
		f = temp.get()[25] + 0xD71577C1 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = a & (c & b ^ d ^ f) ^ c & h ^ b & g ^ f;
		e = temp.get()[12] + 0xBD314B27 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = h & (b & a ^ c ^ e) ^ b & g ^ a & f ^ e;
		d = temp.get()[24] + 0x78AF2FDA + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = g & (a & h ^ b ^ d) ^ a & f ^ h & e ^ d;
		c = temp.get()[30] + 0x55605C60 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = f & (h & g ^ a ^ c) ^ h & e ^ g & d ^ c;
		b = temp.get()[16] + 0xE65525F3 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = e & (g & f ^ h ^ b) ^ g & d ^ f & c ^ b;
		a = temp.get()[26] + 0xAA55AB94 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = d & (f & e ^ g ^ a) ^ f & c ^ e & b ^ a;
		h = temp.get()[31] + 0x57489862 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = c & (e & d ^ f ^ h) ^ e & b ^ d & a ^ h;
		g = temp.get()[15] + 0x63E81440 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = b & (d & c ^ e ^ g) ^ d & a ^ c & h ^ g;
		f = temp.get()[7] + 0x55CA396A + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = a & (c & b ^ d ^ f) ^ c & h ^ b & g ^ f;
		e = temp.get()[3] + 0x2AAB10B6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = h & (b & a ^ c ^ e) ^ b & g ^ a & f ^ e;
		d = temp.get()[1] + 0xB4CC5C34 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = g & (a & h ^ b ^ d) ^ a & f ^ h & e ^ d;
		c = temp.get()[0] + 0x1141E8CE + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = f & (h & g ^ a ^ c) ^ h & e ^ g & d ^ c;
		b = temp.get()[18] + 0xA15486AF + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = e & (g & f ^ h ^ b) ^ g & d ^ f & c ^ b;
		a = temp.get()[27] + 0x7C72E993 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = d & (f & e ^ g ^ a) ^ f & c ^ e & b ^ a;
		h = temp.get()[13] + 0xB3EE1411 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = c & (e & d ^ f ^ h) ^ e & b ^ d & a ^ h;
		g = temp.get()[6] + 0x636FBC2A + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = b & (d & c ^ e ^ g) ^ d & a ^ c & h ^ g;
		f = temp.get()[21] + 0x2BA9C55D + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = a & (c & b ^ d ^ f) ^ c & h ^ b & g ^ f;
		e = temp.get()[10] + 0x741831F6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = h & (b & a ^ c ^ e) ^ b & g ^ a & f ^ e;
		d = temp.get()[23] + 0xCE5C3E16 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = g & (a & h ^ b ^ d) ^ a & f ^ h & e ^ d;
		c = temp.get()[11] + 0x9B87931E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = f & (h & g ^ a ^ c) ^ h & e ^ g & d ^ c;
		b = temp.get()[5] + 0xAFD6BA33 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = e & (g & f ^ h ^ b) ^ g & d ^ f & c ^ b;
		a = temp.get()[2] + 0x6C24CF5C + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		hash.get()[0]  = hash.get()[0] + a;
		hash.get()[1]  = hash.get()[1] + b;
		hash.get()[2]  = hash.get()[2] + c;
		hash.get()[3]  = hash.get()[3] + d;
		hash.get()[4]  = hash.get()[4] + e;
		hash.get()[5]  = hash.get()[5] + f;
		hash.get()[6]  = hash.get()[6] + g;
		hash.get()[7]  = hash.get()[7] + h;

		memset(temp.get(), 0, 32 * sizeof(uint32_t));
	} // end function TransformBlock

}; // end class Haval3
	

class Haval4 : public Haval
{
public:
	Haval4(const HashSize &a_hash_size)
		: Haval(Rounds4, a_hash_size)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval4 HashInstance = Haval4(HashSize(_HashSize));
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval4>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

protected:
	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t a, b, c, d, e, f, g, h, t;

		Converters::le32_copy(a_data, a_index, temp.get(), 0, 128);

		a = hash.get()[0];
		b = hash.get()[1];
		c = hash.get()[2];
		d = hash.get()[3];
		e = hash.get()[4];
		f = hash.get()[5];
		g = hash.get()[6];
		h = hash.get()[7];

		t = d & (a ^ b) ^ f & g ^ e & c ^ a;
		h = temp.get()[0] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(h, 11);

		t = c & (h ^ a) ^ e & f ^ d & b ^ h;
		g = temp.get()[1] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(g, 11);

		t = b & (g ^ h) ^ d & e ^ c & a ^ g;
		f = temp.get()[2] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(f, 11);

		t = a & (f ^ g) ^ c & d ^ b & h ^ f;
		e = temp.get()[3] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(e, 11);

		t = h & (e ^ f) ^ b & c ^ a & g ^ e;
		d = temp.get()[4] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(d, 11);

		t = g & (d ^ e) ^ a & b ^ h & f ^ d;
		c = temp.get()[5] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(c, 11);

		t = f & (c ^ d) ^ h & a ^ g & e ^ c;
		b = temp.get()[6] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(b, 11);

		t = e & (b ^ c) ^ g & h ^ f & d ^ b;
		a = temp.get()[7] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(a, 11);

		t = d & (a ^ b) ^ f & g ^ e & c ^ a;
		h = temp.get()[8] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(h, 11);

		t = c & (h ^ a) ^ e & f ^ d & b ^ h;
		g = temp.get()[9] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(g, 11);

		t = b & (g ^ h) ^ d & e ^ c & a ^ g;
		f = temp.get()[10] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(f, 11);

		t = a & (f ^ g) ^ c & d ^ b & h ^ f;
		e = temp.get()[11] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(e, 11);

		t = h & (e ^ f) ^ b & c ^ a & g ^ e;
		d = temp.get()[12] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(d, 11);

		t = g & (d ^ e) ^ a & b ^ h & f ^ d;
		c = temp.get()[13] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(c, 11);

		t = f & (c ^ d) ^ h & a ^ g & e ^ c;
		b = temp.get()[14] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(b, 11);

		t = e & (b ^ c) ^ g & h ^ f & d ^ b;
		a = temp.get()[15] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(a, 11);

		t = d & (a ^ b) ^ f & g ^ e & c ^ a;
		h = temp.get()[16] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(h, 11);

		t = c & (h ^ a) ^ e & f ^ d & b ^ h;
		g = temp.get()[17] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(g, 11);

		t = b & (g ^ h) ^ d & e ^ c & a ^ g;
		f = temp.get()[18] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(f, 11);

		t = a & (f ^ g) ^ c & d ^ b & h ^ f;
		e = temp.get()[19] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(e, 11);

		t = h & (e ^ f) ^ b & c ^ a & g ^ e;
		d = temp.get()[20] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(d, 11);

		t = g & (d ^ e) ^ a & b ^ h & f ^ d;
		c = temp.get()[21] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(c, 11);

		t = f & (c ^ d) ^ h & a ^ g & e ^ c;
		b = temp.get()[22] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(b, 11);

		t = e & (b ^ c) ^ g & h ^ f & d ^ b;
		a = temp.get()[23] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(a, 11);

		t = d & (a ^ b) ^ f & g ^ e & c ^ a;
		h = temp.get()[24] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(h, 11);

		t = c & (h ^ a) ^ e & f ^ d & b ^ h;
		g = temp.get()[25] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(g, 11);

		t = b & (g ^ h) ^ d & e ^ c & a ^ g;
		f = temp.get()[26] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(f, 11);

		t = a & (f ^ g) ^ c & d ^ b & h ^ f;
		e = temp.get()[27] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(e, 11);

		t = h & (e ^ f) ^ b & c ^ a & g ^ e;
		d = temp.get()[28] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(d, 11);

		t = g & (d ^ e) ^ a & b ^ h & f ^ d;
		c = temp.get()[29] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(c, 11);

		t = f & (c ^ d) ^ h & a ^ g & e ^ c;
		b = temp.get()[30] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(b, 11);

		t = e & (b ^ c) ^ g & h ^ f & d ^ b;
		a = temp.get()[31] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(a, 11);

		t = b & (g & ~a ^ c & f ^ d ^ e) ^ c & (g ^ f)
			^ a & f ^ e;
		h = temp.get()[5] + 0x452821E6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = a & (f & ~h ^ b & e ^ c ^ d) ^ b & (f ^ e)
			^ h & e ^ d;
		g = temp.get()[14] + 0x38D01377 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = h & (e & ~g ^ a & d ^ b ^ c) ^ a & (e ^ d)
			^ g & d ^ c;
		f = temp.get()[26] + 0xBE5466CF + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = g & (d & ~f ^ h & c ^ a ^ b) ^ h & (d ^ c)
			^ f & c ^ b;
		e = temp.get()[18] + 0x34E90C6C + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = f & (c & ~e ^ g & b ^ h ^ a) ^ g & (c ^ b)
			^ e & b ^ a;
		d = temp.get()[11] + 0xC0AC29B7 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = e & (b & ~d ^ f & a ^ g ^ h) ^ f & (b ^ a)
			^ d & a ^ h;
		c = temp.get()[28] + 0xC97C50DD + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = d & (a & ~c ^ e & h ^ f ^ g) ^ e & (a ^ h)
			^ c & h ^ g;
		b = temp.get()[7] + 0x3F84D5B5 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = c & (h & ~b ^ d & g ^ e ^ f) ^ d & (h ^ g)
			^ b & g ^ f;
		a = temp.get()[16] + 0xB5470917 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = b & (g & ~a ^ c & f ^ d ^ e) ^ c & (g ^ f)
			^ a & f ^ e;
		h = temp.get()[0] + 0x9216D5D9 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = a & (f & ~h ^ b & e ^ c ^ d) ^ b & (f ^ e)
			^ h & e ^ d;
		g = temp.get()[23] + 0x8979FB1B + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = h & (e & ~g ^ a & d ^ b ^ c) ^ a & (e ^ d)
			^ g & d ^ c;
		f = temp.get()[20] + 0xD1310BA6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = g & (d & ~f ^ h & c ^ a ^ b) ^ h & (d ^ c)
			^ f & c ^ b;
		e = temp.get()[22] + 0x98DFB5AC + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = f & (c & ~e ^ g & b ^ h ^ a) ^ g & (c ^ b)
			^ e & b ^ a;
		d = temp.get()[1] + 0x2FFD72DB + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = e & (b & ~d ^ f & a ^ g ^ h) ^ f & (b ^ a)
			^ d & a ^ h;
		c = temp.get()[10] + 0xD01ADFB7 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = d & (a & ~c ^ e & h ^ f ^ g) ^ e & (a ^ h)
			^ c & h ^ g;
		b = temp.get()[4] + 0xB8E1AFED + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = c & (h & ~b ^ d & g ^ e ^ f) ^ d & (h ^ g)
			^ b & g ^ f;
		a = temp.get()[8] + 0x6A267E96 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = b & (g & ~a ^ c & f ^ d ^ e) ^ c & (g ^ f)
			^ a & f ^ e;
		h = temp.get()[30] + 0xBA7C9045 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = a & (f & ~h ^ b & e ^ c ^ d) ^ b & (f ^ e)
			^ h & e ^ d;
		g = temp.get()[3] + 0xF12C7F99 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = h & (e & ~g ^ a & d ^ b ^ c) ^ a & (e ^ d)
			^ g & d ^ c;
		f = temp.get()[21] + 0x24A19947 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = g & (d & ~f ^ h & c ^ a ^ b) ^ h & (d ^ c)
			^ f & c ^ b;
		e = temp.get()[9] + 0xB3916CF7 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = f & (c & ~e ^ g & b ^ h ^ a) ^ g & (c ^ b)
			^ e & b ^ a;
		d = temp.get()[17] + 0x0801F2E2 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = e & (b & ~d ^ f & a ^ g ^ h) ^ f & (b ^ a)
			^ d & a ^ h;
		c = temp.get()[24] + 0x858EFC16 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = d & (a & ~c ^ e & h ^ f ^ g) ^ e & (a ^ h)
			^ c & h ^ g;
		b = temp.get()[29] + 0x636920D8 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = c & (h & ~b ^ d & g ^ e ^ f) ^ d & (h ^ g)
			^ b & g ^ f;
		a = temp.get()[6] + 0x71574E69 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = b & (g & ~a ^ c & f ^ d ^ e) ^ c & (g ^ f)
			^ a & f ^ e;
		h = temp.get()[19] + 0xA458FEA3 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = a & (f & ~h ^ b & e ^ c ^ d) ^ b & (f ^ e)
			^ h & e ^ d;
		g = temp.get()[12] + 0xF4933D7E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = h & (e & ~g ^ a & d ^ b ^ c) ^ a & (e ^ d)
			^ g & d ^ c;
		f = temp.get()[15] + 0x0D95748F + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = g & (d & ~f ^ h & c ^ a ^ b) ^ h & (d ^ c)
			^ f & c ^ b;
		e = temp.get()[13] + 0x728EB658 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = f & (c & ~e ^ g & b ^ h ^ a) ^ g & (c ^ b)
			^ e & b ^ a;
		d = temp.get()[2] + 0x718BCD58 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = e & (b & ~d ^ f & a ^ g ^ h) ^ f & (b ^ a)
			^ d & a ^ h;
		c = temp.get()[25] + 0x82154AEE + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = d & (a & ~c ^ e & h ^ f ^ g) ^ e & (a ^ h)
			^ c & h ^ g;
		b = temp.get()[31] + 0x7B54A41D + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = c & (h & ~b ^ d & g ^ e ^ f) ^ d & (h ^ g)
			^ b & g ^ f;
		a = temp.get()[27] + 0xC25A59B5 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = g & (c & a ^ b ^ f) ^ c & d ^ a & e ^ f;
		h = temp.get()[19] + 0x9C30D539 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = f & (b & h ^ a ^ e) ^ b & c ^ h & d ^ e;
		g = temp.get()[9] + 0x2AF26013 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = e & (a & g ^ h ^ d) ^ a & b ^ g & c ^ d;
		f = temp.get()[4] + 0xC5D1B023 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = d & (h & f ^ g ^ c) ^ h & a ^ f & b ^ c;
		e = temp.get()[20] + 0x286085F0 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = c & (g & e ^ f ^ b) ^ g & h ^ e & a ^ b;
		d = temp.get()[28] + 0xCA417918 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = b & (f & d ^ e ^ a) ^ f & g ^ d & h ^ a;
		c = temp.get()[17] + 0xB8DB38EF + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = a & (e & c ^ d ^ h) ^ e & f ^ c & g ^ h;
		b = temp.get()[8] + 0x8E79DCB0 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = h & (d & b ^ c ^ g) ^ d & e ^ b & f ^ g;
		a = temp.get()[22] + 0x603A180E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = g & (c & a ^ b ^ f) ^ c & d ^ a & e ^ f;
		h = temp.get()[29] + 0x6C9E0E8B + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = f & (b & h ^ a ^ e) ^ b & c ^ h & d ^ e;
		g = temp.get()[14] + 0xB01E8A3E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = e & (a & g ^ h ^ d) ^ a & b ^ g & c ^ d;
		f = temp.get()[25] + 0xD71577C1 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = d & (h & f ^ g ^ c) ^ h & a ^ f & b ^ c;
		e = temp.get()[12] + 0xBD314B27 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = c & (g & e ^ f ^ b) ^ g & h ^ e & a ^ b;
		d = temp.get()[24] + 0x78AF2FDA + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = b & (f & d ^ e ^ a) ^ f & g ^ d & h ^ a;
		c = temp.get()[30] + 0x55605C60 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = a & (e & c ^ d ^ h) ^ e & f ^ c & g ^ h;
		b = temp.get()[16] + 0xE65525F3 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = h & (d & b ^ c ^ g) ^ d & e ^ b & f ^ g;
		a = temp.get()[26] + 0xAA55AB94 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = g & (c & a ^ b ^ f) ^ c & d ^ a & e ^ f;
		h = temp.get()[31] + 0x57489862 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = f & (b & h ^ a ^ e) ^ b & c ^ h & d ^ e;
		g = temp.get()[15] + 0x63E81440 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = e & (a & g ^ h ^ d) ^ a & b ^ g & c ^ d;
		f = temp.get()[7] + 0x55CA396A + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = d & (h & f ^ g ^ c) ^ h & a ^ f & b ^ c;
		e = temp.get()[3] + 0x2AAB10B6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = c & (g & e ^ f ^ b) ^ g & h ^ e & a ^ b;
		d = temp.get()[1] + 0xB4CC5C34 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = b & (f & d ^ e ^ a) ^ f & g ^ d & h ^ a;
		c = temp.get()[0] + 0x1141E8CE + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = a & (e & c ^ d ^ h) ^ e & f ^ c & g ^ h;
		b = temp.get()[18] + 0xA15486AF + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = h & (d & b ^ c ^ g) ^ d & e ^ b & f ^ g;
		a = temp.get()[27] + 0x7C72E993 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = g & (c & a ^ b ^ f) ^ c & d ^ a & e ^ f;
		h = temp.get()[13] + 0xB3EE1411 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = f & (b & h ^ a ^ e) ^ b & c ^ h & d ^ e;
		g = temp.get()[6] + 0x636FBC2A + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = e & (a & g ^ h ^ d) ^ a & b ^ g & c ^ d;
		f = temp.get()[21] + 0x2BA9C55D + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = d & (h & f ^ g ^ c) ^ h & a ^ f & b ^ c;
		e = temp.get()[10] + 0x741831F6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = c & (g & e ^ f ^ b) ^ g & h ^ e & a ^ b;
		d = temp.get()[23] + 0xCE5C3E16 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = b & (f & d ^ e ^ a) ^ f & g ^ d & h ^ a;
		c = temp.get()[11] + 0x9B87931E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = a & (e & c ^ d ^ h) ^ e & f ^ c & g ^ h;
		b = temp.get()[5] + 0xAFD6BA33 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = h & (d & b ^ c ^ g) ^ d & e ^ b & f ^ g;
		a = temp.get()[2] + 0x6C24CF5C + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = a & (e & ~c ^ f & ~g ^ b ^ g ^ d) ^ f &
			(b & c ^ e ^ g) ^ c & g ^ d;
		h = temp.get()[24] + 0x7A325381 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = h & (d & ~b ^ e & ~f ^ a ^ f ^ c) ^ e &
			(a & b ^ d ^ f) ^ b & f ^ c;
		g = temp.get()[4] + 0x28958677 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = g & (c & ~a ^ d & ~e ^ h ^ e ^ b) ^ d &
			(h & a ^ c ^ e) ^ a & e ^ b;
		f = temp.get()[0] + 0x3B8F4898 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = f & (b & ~h ^ c & ~d ^ g ^ d ^ a) ^ c &
			(g & h ^ b ^ d) ^ h & d ^ a;
		e = temp.get()[14] + 0x6B4BB9AF + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = e & (a & ~g ^ b & ~c ^ f ^ c ^ h) ^ b &
			(f & g ^ a ^ c) ^ g & c ^ h;
		d = temp.get()[2] + 0xC4BFE81B + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = d & (h & ~f ^ a & ~b ^ e ^ b ^ g) ^ a &
			(e & f ^ h ^ b) ^ f & b ^ g;
		c = temp.get()[7] + 0x66282193 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = c & (g & ~e ^ h & ~a ^ d ^ a ^ f) ^ h &
			(d & e ^ g ^ a) ^ e & a ^ f;
		b = temp.get()[28] + 0x61D809CC + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = b & (f & ~d ^ g & ~h ^ c ^ h ^ e) ^ g &
			(c & d ^ f ^ h) ^ d & h ^ e;
		a = temp.get()[23] + 0xFB21A991 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = a & (e & ~c ^ f & ~g ^ b ^ g ^ d) ^ f &
			(b & c ^ e ^ g) ^ c & g ^ d;
		h = temp.get()[26] + 0x487CAC60 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = h & (d & ~b ^ e & ~f ^ a ^ f ^ c) ^ e &
			(a & b ^ d ^ f) ^ b & f ^ c;
		g = temp.get()[6] + 0x5DEC8032 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = g & (c & ~a ^ d & ~e ^ h ^ e ^ b) ^ d &
			(h & a ^ c ^ e) ^ a & e ^ b;
		f = temp.get()[30] + 0xEF845D5D + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = f & (b & ~h ^ c & ~d ^ g ^ d ^ a) ^ c &
			(g & h ^ b ^ d) ^ h & d ^ a;
		e = temp.get()[20] + 0xE98575B1 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = e & (a & ~g ^ b & ~c ^ f ^ c ^ h) ^ b &
			(f & g ^ a ^ c) ^ g & c ^ h;
		d = temp.get()[18] + 0xDC262302 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = d & (h & ~f ^ a & ~b ^ e ^ b ^ g) ^ a &
			(e & f ^ h ^ b) ^ f & b ^ g;
		c = temp.get()[25] + 0xEB651B88 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = c & (g & ~e ^ h & ~a ^ d ^ a ^ f) ^ h &
			(d & e ^ g ^ a) ^ e & a ^ f;
		b = temp.get()[19] + 0x23893E81 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = b & (f & ~d ^ g & ~h ^ c ^ h ^ e) ^ g &
			(c & d ^ f ^ h) ^ d & h ^ e;
		a = temp.get()[3] + 0xD396ACC5 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = a & (e & ~c ^ f & ~g ^ b ^ g ^ d) ^ f &
			(b & c ^ e ^ g) ^ c & g ^ d;
		h = temp.get()[22] + 0x0F6D6FF3 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = h & (d & ~b ^ e & ~f ^ a ^ f ^ c) ^ e &
			(a & b ^ d ^ f) ^ b & f ^ c;
		g = temp.get()[11] + 0x83F44239 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = g & (c & ~a ^ d & ~e ^ h ^ e ^ b) ^ d &
			(h & a ^ c ^ e) ^ a & e ^ b;
		f = temp.get()[31] + 0x2E0B4482 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = f & (b & ~h ^ c & ~d ^ g ^ d ^ a) ^ c &
			(g & h ^ b ^ d) ^ h & d ^ a;
		e = temp.get()[21] + 0xA4842004 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = e & (a & ~g ^ b & ~c ^ f ^ c ^ h) ^ b &
			(f & g ^ a ^ c) ^ g & c ^ h;
		d = temp.get()[8] + 0x69C8F04A + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = d & (h & ~f ^ a & ~b ^ e ^ b ^ g) ^ a &
			(e & f ^ h ^ b) ^ f & b ^ g;
		c = temp.get()[27] + 0x9E1F9B5E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = c & (g & ~e ^ h & ~a ^ d ^ a ^ f) ^ h &
			(d & e ^ g ^ a) ^ e & a ^ f;
		b = temp.get()[12] + 0x21C66842 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = b & (f & ~d ^ g & ~h ^ c ^ h ^ e) ^ g &
			(c & d ^ f ^ h) ^ d & h ^ e;
		a = temp.get()[9] + 0xF6E96C9A + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = a & (e & ~c ^ f & ~g ^ b ^ g ^ d) ^ f &
			(b & c ^ e ^ g) ^ c & g ^ d;
		h = temp.get()[1] + 0x670C9C61 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = h & (d & ~b ^ e & ~f ^ a ^ f ^ c) ^ e &
			(a & b ^ d ^ f) ^ b & f ^ c;
		g = temp.get()[29] + 0xABD388F0 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = g & (c & ~a ^ d & ~e ^ h ^ e ^ b) ^ d &
			(h & a ^ c ^ e) ^ a & e ^ b;
		f = temp.get()[5] + 0x6A51A0D2 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = f & (b & ~h ^ c & ~d ^ g ^ d ^ a) ^ c &
			(g & h ^ b ^ d) ^ h & d ^ a;
		e = temp.get()[15] + 0xD8542F68 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = e & (a & ~g ^ b & ~c ^ f ^ c ^ h) ^ b &
			(f & g ^ a ^ c) ^ g & c ^ h;
		d = temp.get()[17] + 0x960FA728 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = d & (h & ~f ^ a & ~b ^ e ^ b ^ g) ^ a &
			(e & f ^ h ^ b) ^ f & b ^ g;
		c = temp.get()[10] + 0xAB5133A3 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = c & (g & ~e ^ h & ~a ^ d ^ a ^ f) ^ h &
			(d & e ^ g ^ a) ^ e & a ^ f;
		b = temp.get()[16] + 0x6EEF0B6C + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = b & (f & ~d ^ g & ~h ^ c ^ h ^ e) ^ g &
			(c & d ^ f ^ h) ^ d & h ^ e;
		a = temp.get()[13] + 0x137A3BE4 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		hash.get()[0]  = hash.get()[0] + a;
		hash.get()[1]  = hash.get()[1] + b;
		hash.get()[2]  = hash.get()[2] + c;
		hash.get()[3]  = hash.get()[3] + d;
		hash.get()[4]  = hash.get()[4] + e;
		hash.get()[5]  = hash.get()[5] + f;
		hash.get()[6]  = hash.get()[6] + g;
		hash.get()[7]  = hash.get()[7] + h;

		memset(temp.get(), 0, 32 * sizeof(uint32_t));
	} // end function TransformBlock

}; // end class Haval4


class Haval5 : public Haval
{
public:
	Haval5(const HashSize &a_hash_size)
		: Haval(Rounds5, a_hash_size)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval5 HashInstance = Haval5(HashSize(_HashSize));
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval5>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

protected:
	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t a, b, c, d, e, f, g, h, t;

		Converters::le32_copy(a_data, a_index, temp.get(), 0, 128);

		a = hash.get()[0];
		b = hash.get()[1];
		c = hash.get()[2];
		d = hash.get()[3];
		e = hash.get()[4];
		f = hash.get()[5];
		g = hash.get()[6];
		h = hash.get()[7];

		t = c & (g ^ b) ^ f & e ^ a & d ^ g;
		h = temp.get()[0] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(h, 11);
		t = b & (f ^ a) ^ e & d ^ h & c ^ f;
		g = temp.get()[1] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(g, 11);

		t = a & (e ^ h) ^ d & c ^ g & b ^ e;
		f = temp.get()[2] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(f, 11);

		t = h & (d ^ g) ^ c & b ^ f & a ^ d;
		e = temp.get()[3] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(e, 11);

		t = g & (c ^ f) ^ b & a ^ e & h ^ c;
		d = temp.get()[4] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(d, 11);

		t = f & (b ^ e) ^ a & h ^ d & g ^ b;
		c = temp.get()[5] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(c, 11);

		t = e & (a ^ d) ^ h & g ^ c & f ^ a;
		b = temp.get()[6] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(b, 11);

		t = d & (h ^ c) ^ g & f ^ b & e ^ h;
		a = temp.get()[7] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(a, 11);

		t = c & (g ^ b) ^ f & e ^ a & d ^ g;
		h = temp.get()[8] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(h, 11);

		t = b & (f ^ a) ^ e & d ^ h & c ^ f;
		g = temp.get()[9] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(g, 11);

		t = a & (e ^ h) ^ d & c ^ g & b ^ e;
		f = temp.get()[10] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(f, 11);

		t = h & (d ^ g) ^ c & b ^ f & a ^ d;
		e = temp.get()[11] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(e, 11);

		t = g & (c ^ f) ^ b & a ^ e & h ^ c;
		d = temp.get()[12] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(d, 11);

		t = f & (b ^ e) ^ a & h ^ d & g ^ b;
		c = temp.get()[13] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(c, 11);

		t = e & (a ^ d) ^ h & g ^ c & f ^ a;
		b = temp.get()[14] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(b, 11);

		t = d & (h ^ c) ^ g & f ^ b & e ^ h;
		a = temp.get()[15] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(a, 11);

		t = c & (g ^ b) ^ f & e ^ a & d ^ g;
		h = temp.get()[16] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(h, 11);

		t = b & (f ^ a) ^ e & d ^ h & c ^ f;
		g = temp.get()[17] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(g, 11);

		t = a & (e ^ h) ^ d & c ^ g & b ^ e;
		f = temp.get()[18] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(f, 11);

		t = h & (d ^ g) ^ c & b ^ f & a ^ d;
		e = temp.get()[19] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(e, 11);

		t = g & (c ^ f) ^ b & a ^ e & h ^ c;
		d = temp.get()[20] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(d, 11);

		t = f & (b ^ e) ^ a & h ^ d & g ^ b;
		c = temp.get()[21] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(c, 11);

		t = e & (a ^ d) ^ h & g ^ c & f ^ a;
		b = temp.get()[22] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(b, 11);

		t = d & (h ^ c) ^ g & f ^ b & e ^ h;
		a = temp.get()[23] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(a, 11);

		t = c & (g ^ b) ^ f & e ^ a & d ^ g;
		h = temp.get()[24] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(h, 11);

		t = b & (f ^ a) ^ e & d ^ h & c ^ f;
		g = temp.get()[25] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(g, 11);

		t = a & (e ^ h) ^ d & c ^ g & b ^ e;
		f = temp.get()[26] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(f, 11);

		t = h & (d ^ g) ^ c & b ^ f & a ^ d;
		e = temp.get()[27] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(e, 11);

		t = g & (c ^ f) ^ b & a ^ e & h ^ c;
		d = temp.get()[28] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(d, 11);

		t = f & (b ^ e) ^ a & h ^ d & g ^ b;
		c = temp.get()[29] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(c, 11);

		t = e & (a ^ d) ^ h & g ^ c & f ^ a;
		b = temp.get()[30] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(b, 11);

		t = d & (h ^ c) ^ g & f ^ b & e ^ h;
		a = temp.get()[31] + Bits::RotateRight32(t, 7) + Bits::RotateRight32(a, 11);

		t = d & (e & ~a ^ b & c ^ g ^ f) ^ b & (e ^ c)
			^ a & c ^ f;
		h = temp.get()[5] + 0x452821E6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = c & (d & ~h ^ a & b ^ f ^ e) ^ a & (d ^ b)
			^ h & b ^ e;
		g = temp.get()[14] + 0x38D01377 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = b & (c & ~g ^ h & a ^ e ^ d) ^ h & (c ^ a)
			^ g & a ^ d;
		f = temp.get()[26] + 0xBE5466CF + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = a & (b & ~f ^ g & h ^ d ^ c) ^ g & (b ^ h)
			^ f & h ^ c;
		e = temp.get()[18] + 0x34E90C6C + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = h & (a & ~e ^ f & g ^ c ^ b) ^ f & (a ^ g)
			^ e & g ^ b;
		d = temp.get()[11] + 0xC0AC29B7 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = g & (h & ~d ^ e & f ^ b ^ a) ^ e & (h ^ f)
			^ d & f ^ a;
		c = temp.get()[28] + 0xC97C50DD + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = f & (g & ~c ^ d & e ^ a ^ h) ^ d & (g ^ e)
			^ c & e ^ h;
		b = temp.get()[7] + 0x3F84D5B5 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = e & (f & ~b ^ c & d ^ h ^ g) ^ c & (f ^ d)
			^ b & d ^ g;
		a = temp.get()[16] + 0xB5470917 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = d & (e & ~a ^ b & c ^ g ^ f) ^ b & (e ^ c)
			^ a & c ^ f;
		h = temp.get()[0] + 0x9216D5D9 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = c & (d & ~h ^ a & b ^ f ^ e) ^ a & (d ^ b)
			^ h & b ^ e;
		g = temp.get()[23] + 0x8979FB1B + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = b & (c & ~g ^ h & a ^ e ^ d) ^ h & (c ^ a)
			^ g & a ^ d;
		f = temp.get()[20] + 0xD1310BA6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = a & (b & ~f ^ g & h ^ d ^ c) ^ g & (b ^ h)
			^ f & h ^ c;
		e = temp.get()[22] + 0x98DFB5AC + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = h & (a & ~e ^ f & g ^ c ^ b) ^ f & (a ^ g)
			^ e & g ^ b;
		d = temp.get()[1] + 0x2FFD72DB + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = g & (h & ~d ^ e & f ^ b ^ a) ^ e & (h ^ f)
			^ d & f ^ a;
		c = temp.get()[10] + 0xD01ADFB7 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = f & (g & ~c ^ d & e ^ a ^ h) ^ d & (g ^ e)
			^ c & e ^ h;
		b = temp.get()[4] + 0xB8E1AFED + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = e & (f & ~b ^ c & d ^ h ^ g) ^ c & (f ^ d)
			^ b & d ^ g;
		a = temp.get()[8] + 0x6A267E96 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = d & (e & ~a ^ b & c ^ g ^ f) ^ b & (e ^ c)
			^ a & c ^ f;
		h = temp.get()[30] + 0xBA7C9045 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = c & (d & ~h ^ a & b ^ f ^ e) ^ a & (d ^ b)
			^ h & b ^ e;
		g = temp.get()[3] + 0xF12C7F99 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = b & (c & ~g ^ h & a ^ e ^ d) ^ h & (c ^ a)
			^ g & a ^ d;
		f = temp.get()[21] + 0x24A19947 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = a & (b & ~f ^ g & h ^ d ^ c) ^ g & (b ^ h)
			^ f & h ^ c;
		e = temp.get()[9] + 0xB3916CF7 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = h & (a & ~e ^ f & g ^ c ^ b) ^ f & (a ^ g)
			^ e & g ^ b;
		d = temp.get()[17] + 0x0801F2E2 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = g & (h & ~d ^ e & f ^ b ^ a) ^ e & (h ^ f)
			^ d & f ^ a;
		c = temp.get()[24] + 0x858EFC16 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = f & (g & ~c ^ d & e ^ a ^ h) ^ d & (g ^ e)
			^ c & e ^ h;
		b = temp.get()[29] + 0x636920D8 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = e & (f & ~b ^ c & d ^ h ^ g) ^ c & (f ^ d)
			^ b & d ^ g;
		a = temp.get()[6] + 0x71574E69 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = d & (e & ~a ^ b & c ^ g ^ f) ^ b & (e ^ c)
			^ a & c ^ f;
		h = temp.get()[19] + 0xA458FEA3 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = c & (d & ~h ^ a & b ^ f ^ e) ^ a & (d ^ b)
			^ h & b ^ e;
		g = temp.get()[12] + 0xF4933D7E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = b & (c & ~g ^ h & a ^ e ^ d) ^ h & (c ^ a)
			^ g & a ^ d;
		f = temp.get()[15] + 0x0D95748F + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = a & (b & ~f ^ g & h ^ d ^ c) ^ g & (b ^ h)
			^ f & h ^ c;
		e = temp.get()[13] + 0x728EB658 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = h & (a & ~e ^ f & g ^ c ^ b) ^ f & (a ^ g)
			^ e & g ^ b;
		d = temp.get()[2] + 0x718BCD58 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = g & (h & ~d ^ e & f ^ b ^ a) ^ e & (h ^ f)
			^ d & f ^ a;
		c = temp.get()[25] + 0x82154AEE + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = f & (g & ~c ^ d & e ^ a ^ h) ^ d & (g ^ e)
			^ c & e ^ h;
		b = temp.get()[31] + 0x7B54A41D + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = e & (f & ~b ^ c & d ^ h ^ g) ^ c & (f ^ d)
			^ b & d ^ g;
		a = temp.get()[27] + 0xC25A59B5 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = e & (b & d ^ c ^ f) ^ b & a ^ d & g ^ f;
		h = temp.get()[19] + 0x9C30D539 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = d & (a & c ^ b ^ e) ^ a & h ^ c & f ^ e;
		g = temp.get()[9] + 0x2AF26013 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = c & (h & b ^ a ^ d) ^ h & g ^ b & e ^ d;
		f = temp.get()[4] + 0xC5D1B023 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = b & (g & a ^ h ^ c) ^ g & f ^ a & d ^ c;
		e = temp.get()[20] + 0x286085F0 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = a & (f & h ^ g ^ b) ^ f & e ^ h & c ^ b;
		d = temp.get()[28] + 0xCA417918 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = h & (e & g ^ f ^ a) ^ e & d ^ g & b ^ a;
		c = temp.get()[17] + 0xB8DB38EF + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = g & (d & f ^ e ^ h) ^ d & c ^ f & a ^ h;
		b = temp.get()[8] + 0x8E79DCB0 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = f & (c & e ^ d ^ g) ^ c & b ^ e & h ^ g;
		a = temp.get()[22] + 0x603A180E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = e & (b & d ^ c ^ f) ^ b & a ^ d & g ^ f;
		h = temp.get()[29] + 0x6C9E0E8B + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = d & (a & c ^ b ^ e) ^ a & h ^ c & f ^ e;
		g = temp.get()[14] + 0xB01E8A3E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = c & (h & b ^ a ^ d) ^ h & g ^ b & e ^ d;
		f = temp.get()[25] + 0xD71577C1 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = b & (g & a ^ h ^ c) ^ g & f ^ a & d ^ c;
		e = temp.get()[12] + 0xBD314B27 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = a & (f & h ^ g ^ b) ^ f & e ^ h & c ^ b;
		d = temp.get()[24] + 0x78AF2FDA + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = h & (e & g ^ f ^ a) ^ e & d ^ g & b ^ a;
		c = temp.get()[30] + 0x55605C60 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = g & (d & f ^ e ^ h) ^ d & c ^ f & a ^ h;
		b = temp.get()[16] + 0xE65525F3 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = f & (c & e ^ d ^ g) ^ c & b ^ e & h ^ g;
		a = temp.get()[26] + 0xAA55AB94 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = e & (b & d ^ c ^ f) ^ b & a ^ d & g ^ f;
		h = temp.get()[31] + 0x57489862 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = d & (a & c ^ b ^ e) ^ a & h ^ c & f ^ e;
		g = temp.get()[15] + 0x63E81440 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = c & (h & b ^ a ^ d) ^ h & g ^ b & e ^ d;
		f = temp.get()[7] + 0x55CA396A + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = b & (g & a ^ h ^ c) ^ g & f ^ a & d ^ c;
		e = temp.get()[3] + 0x2AAB10B6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = a & (f & h ^ g ^ b) ^ f & e ^ h & c ^ b;
		d = temp.get()[1] + 0xB4CC5C34 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = h & (e & g ^ f ^ a) ^ e & d ^ g & b ^ a;
		c = temp.get()[0] + 0x1141E8CE + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = g & (d & f ^ e ^ h) ^ d & c ^ f & a ^ h;
		b = temp.get()[18] + 0xA15486AF + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = f & (c & e ^ d ^ g) ^ c & b ^ e & h ^ g;
		a = temp.get()[27] + 0x7C72E993 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = e & (b & d ^ c ^ f) ^ b & a ^ d & g ^ f;
		h = temp.get()[13] + 0xB3EE1411 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = d & (a & c ^ b ^ e) ^ a & h ^ c & f ^ e;
		g = temp.get()[6] + 0x636FBC2A + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = c & (h & b ^ a ^ d) ^ h & g ^ b & e ^ d;
		f = temp.get()[21] + 0x2BA9C55D + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = b & (g & a ^ h ^ c) ^ g & f ^ a & d ^ c;
		e = temp.get()[10] + 0x741831F6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = a & (f & h ^ g ^ b) ^ f & e ^ h & c ^ b;
		d = temp.get()[23] + 0xCE5C3E16 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = h & (e & g ^ f ^ a) ^ e & d ^ g & b ^ a;
		c = temp.get()[11] + 0x9B87931E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = g & (d & f ^ e ^ h) ^ d & c ^ f & a ^ h;
		b = temp.get()[5] + 0xAFD6BA33 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = f & (c & e ^ d ^ g) ^ c & b ^ e & h ^ g;
		a = temp.get()[2] + 0x6C24CF5C + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = d & (f & ~a ^ c & ~b ^ e ^ b ^ g) ^ c &
			(e & a ^ f ^ b) ^ a & b ^ g;
		h = temp.get()[24] + 0x7A325381 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = c & (e & ~h ^ b & ~a ^ d ^ a ^ f) ^ b &
			(d & h ^ e ^ a) ^ h & a ^ f;
		g = temp.get()[4] + 0x28958677 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = b & (d & ~g ^ a & ~h ^ c ^ h ^ e) ^ a &
			(c & g ^ d ^ h) ^ g & h ^ e;
		f = temp.get()[0] + 0x3B8F4898 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = a & (c & ~f ^ h & ~g ^ b ^ g ^ d) ^ h &
			(b & f ^ c ^ g) ^ f & g ^ d;
		e = temp.get()[14] + 0x6B4BB9AF + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = h & (b & ~e ^ g & ~f ^ a ^ f ^ c) ^ g &
			(a & e ^ b ^ f) ^ e & f ^ c;
		d = temp.get()[2] + 0xC4BFE81B + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = g & (a & ~d ^ f & ~e ^ h ^ e ^ b) ^ f &
			(h & d ^ a ^ e) ^ d & e ^ b;
		c = temp.get()[7] + 0x66282193 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = f & (h & ~c ^ e & ~d ^ g ^ d ^ a) ^ e &
			(g & c ^ h ^ d) ^ c & d ^ a;
		b = temp.get()[28] + 0x61D809CC + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = e & (g & ~b ^ d & ~c ^ f ^ c ^ h) ^ d &
			(f & b ^ g ^ c) ^ b & c ^ h;
		a = temp.get()[23] + 0xFB21A991 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = d & (f & ~a ^ c & ~b ^ e ^ b ^ g) ^ c &
			(e & a ^ f ^ b) ^ a & b ^ g;
		h = temp.get()[26] + 0x487CAC60 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = c & (e & ~h ^ b & ~a ^ d ^ a ^ f) ^ b &
			(d & h ^ e ^ a) ^ h & a ^ f;
		g = temp.get()[6] + 0x5DEC8032 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = b & (d & ~g ^ a & ~h ^ c ^ h ^ e) ^ a &
			(c & g ^ d ^ h) ^ g & h ^ e;
		f = temp.get()[30] + 0xEF845D5D + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = a & (c & ~f ^ h & ~g ^ b ^ g ^ d) ^ h &
			(b & f ^ c ^ g) ^ f & g ^ d;
		e = temp.get()[20] + 0xE98575B1 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = h & (b & ~e ^ g & ~f ^ a ^ f ^ c) ^ g &
			(a & e ^ b ^ f) ^ e & f ^ c;
		d = temp.get()[18] + 0xDC262302 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = g & (a & ~d ^ f & ~e ^ h ^ e ^ b) ^ f &
			(h & d ^ a ^ e) ^ d & e ^ b;
		c = temp.get()[25] + 0xEB651B88 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = f & (h & ~c ^ e & ~d ^ g ^ d ^ a) ^ e &
			(g & c ^ h ^ d) ^ c & d ^ a;
		b = temp.get()[19] + 0x23893E81 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = e & (g & ~b ^ d & ~c ^ f ^ c ^ h) ^ d &
			(f & b ^ g ^ c) ^ b & c ^ h;
		a = temp.get()[3] + 0xD396ACC5 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = d & (f & ~a ^ c & ~b ^ e ^ b ^ g) ^ c &
			(e & a ^ f ^ b) ^ a & b ^ g;
		h = temp.get()[22] + 0x0F6D6FF3 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = c & (e & ~h ^ b & ~a ^ d ^ a ^ f) ^ b &
			(d & h ^ e ^ a) ^ h & a ^ f;
		g = temp.get()[11] + 0x83F44239 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = b & (d & ~g ^ a & ~h ^ c ^ h ^ e) ^ a &
			(c & g ^ d ^ h) ^ g & h ^ e;
		f = temp.get()[31] + 0x2E0B4482 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = a & (c & ~f ^ h & ~g ^ b ^ g ^ d) ^ h &
			(b & f ^ c ^ g) ^ f & g ^ d;
		e = temp.get()[21] + 0xA4842004 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = h & (b & ~e ^ g & ~f ^ a ^ f ^ c) ^ g &
			(a & e ^ b ^ f) ^ e & f ^ c;
		d = temp.get()[8] + 0x69C8F04A + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = g & (a & ~d ^ f & ~e ^ h ^ e ^ b) ^ f &
			(h & d ^ a ^ e) ^ d & e ^ b;
		c = temp.get()[27] + 0x9E1F9B5E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = f & (h & ~c ^ e & ~d ^ g ^ d ^ a) ^ e &
			(g & c ^ h ^ d) ^ c & d ^ a;
		b = temp.get()[12] + 0x21C66842 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = e & (g & ~b ^ d & ~c ^ f ^ c ^ h) ^ d &
			(f & b ^ g ^ c) ^ b & c ^ h;
		a = temp.get()[9] + 0xF6E96C9A + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = d & (f & ~a ^ c & ~b ^ e ^ b ^ g) ^ c &
			(e & a ^ f ^ b) ^ a & b ^ g;
		h = temp.get()[1] + 0x670C9C61 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = c & (e & ~h ^ b & ~a ^ d ^ a ^ f) ^ b &
			(d & h ^ e ^ a) ^ h & a ^ f;
		g = temp.get()[29] + 0xABD388F0 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = b & (d & ~g ^ a & ~h ^ c ^ h ^ e) ^ a &
			(c & g ^ d ^ h) ^ g & h ^ e;
		f = temp.get()[5] + 0x6A51A0D2 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = a & (c & ~f ^ h & ~g ^ b ^ g ^ d) ^ h &
			(b & f ^ c ^ g) ^ f & g ^ d;
		e = temp.get()[15] + 0xD8542F68 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = h & (b & ~e ^ g & ~f ^ a ^ f ^ c) ^ g &
			(a & e ^ b ^ f) ^ e & f ^ c;
		d = temp.get()[17] + 0x960FA728 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = g & (a & ~d ^ f & ~e ^ h ^ e ^ b) ^ f &
			(h & d ^ a ^ e) ^ d & e ^ b;
		c = temp.get()[10] + 0xAB5133A3 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = f & (h & ~c ^ e & ~d ^ g ^ d ^ a) ^ e &
			(g & c ^ h ^ d) ^ c & d ^ a;
		b = temp.get()[16] + 0x6EEF0B6C + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = e & (g & ~b ^ d & ~c ^ f ^ c ^ h) ^ d &
			(f & b ^ g ^ c) ^ b & c ^ h;
		a = temp.get()[13] + 0x137A3BE4 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = b & (d & e & g ^ ~f) ^ d & a ^ e & f ^ g & c;
		h = temp.get()[27] + 0xBA3BF050 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = a & (c & d & f ^ ~e) ^ c & h ^ d & e ^ f & b;
		g = temp.get()[3] + 0x7EFB2A98 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = h & (b & c & e ^ ~d) ^ b & g ^ c & d ^ e & a;
		f = temp.get()[21] + 0xA1F1651D + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = g & (a & b & d ^ ~c) ^ a & f ^ b & c ^ d & h;
		e = temp.get()[26] + 0x39AF0176 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = f & (h & a & c ^ ~b) ^ h & e ^ a & b ^ c & g;
		d = temp.get()[17] + 0x66CA593E + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = e & (g & h & b ^ ~a) ^ g & d ^ h & a ^ b & f;
		c = temp.get()[11] + 0x82430E88 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = d & (f & g & a ^ ~h) ^ f & c ^ g & h ^ a & e;
		b = temp.get()[20] + 0x8CEE8619 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = c & (e & f & h ^ ~g) ^ e & b ^ f & g ^ h & d;
		a = temp.get()[29] + 0x456F9FB4 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = b & (d & e & g ^ ~f) ^ d & a ^ e & f ^ g & c;
		h = temp.get()[19] + 0x7D84A5C3 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = a & (c & d & f ^ ~e) ^ c & h ^ d & e ^ f & b;
		g = temp.get()[0] + 0x3B8B5EBE + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = h & (b & c & e ^ ~d) ^ b & g ^ c & d ^ e & a;
		f = temp.get()[12] + 0xE06F75D8 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = g & (a & b & d ^ ~c) ^ a & f ^ b & c ^ d & h;
		e = temp.get()[7] + 0x85C12073 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = f & (h & a & c ^ ~b) ^ h & e ^ a & b ^ c & g;
		d = temp.get()[13] + 0x401A449F + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = e & (g & h & b ^ ~a) ^ g & d ^ h & a ^ b & f;
		c = temp.get()[8] + 0x56C16AA6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = d & (f & g & a ^ ~h) ^ f & c ^ g & h ^ a & e;
		b = temp.get()[31] + 0x4ED3AA62 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = c & (e & f & h ^ ~g) ^ e & b ^ f & g ^ h & d;
		a = temp.get()[10] + 0x363F7706 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = b & (d & e & g ^ ~f) ^ d & a ^ e & f ^ g & c;
		h = temp.get()[5] + 0x1BFEDF72 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = a & (c & d & f ^ ~e) ^ c & h ^ d & e ^ f & b;
		g = temp.get()[9] + 0x429B023D + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = h & (b & c & e ^ ~d) ^ b & g ^ c & d ^ e & a;
		f = temp.get()[14] + 0x37D0D724 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = g & (a & b & d ^ ~c) ^ a & f ^ b & c ^ d & h;
		e = temp.get()[30] + 0xD00A1248 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = f & (h & a & c ^ ~b) ^ h & e ^ a & b ^ c & g;
		d = temp.get()[18] + 0xDB0FEAD3 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = e & (g & h & b ^ ~a) ^ g & d ^ h & a ^ b & f;
		c = temp.get()[6] + 0x49F1C09B + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = d & (f & g & a ^ ~h) ^ f & c ^ g & h ^ a & e;
		b = temp.get()[28] + 0x075372C9 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = c & (e & f & h ^ ~g) ^ e & b ^ f & g ^ h & d;
		a = temp.get()[24] + 0x80991B7B + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		t = b & (d & e & g ^ ~f) ^ d & a ^ e & f ^ g & c;
		h = temp.get()[2] + 0x25D479D8 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(h, 11);

		t = a & (c & d & f ^ ~e) ^ c & h ^ d & e ^ f & b;
		g = temp.get()[23] + 0xF6E8DEF7 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(g, 11);

		t = h & (b & c & e ^ ~d) ^ b & g ^ c & d ^ e & a;
		f = temp.get()[16] + 0xE3FE501A + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(f, 11);

		t = g & (a & b & d ^ ~c) ^ a & f ^ b & c ^ d & h;
		e = temp.get()[22] + 0xB6794C3B + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(e, 11);

		t = f & (h & a & c ^ ~b) ^ h & e ^ a & b ^ c & g;
		d = temp.get()[4] + 0x976CE0BD + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(d, 11);

		t = e & (g & h & b ^ ~a) ^ g & d ^ h & a ^ b & f;
		c = temp.get()[1] + 0x04C006BA + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(c, 11);

		t = d & (f & g & a ^ ~h) ^ f & c ^ g & h ^ a & e;
		b = temp.get()[25] + 0xC1A94FB6 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(b, 11);

		t = c & (e & f & h ^ ~g) ^ e & b ^ f & g ^ h & d;
		a = temp.get()[15] + 0x409F60C4 + Bits::RotateRight32(t, 7) +
			Bits::RotateRight32(a, 11);

		hash.get()[0]  = hash.get()[0] + a;
		hash.get()[1]  = hash.get()[1] + b;
		hash.get()[2]  = hash.get()[2] + c;
		hash.get()[3]  = hash.get()[3] + d;
		hash.get()[4]  = hash.get()[4] + e;
		hash.get()[5]  = hash.get()[5] + f;
		hash.get()[6]  = hash.get()[6] + g;
		hash.get()[7]  = hash.get()[7] + h;

		memset(temp.get(), 0, 32 * sizeof(uint32_t));
	} // end function TransformBlock

}; // end class Haval5


class Haval_3_128 : public Haval3
{
public:
	Haval_3_128()
		: Haval3(HashSize128)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_3_128 HashInstance;

		HashInstance = Haval_3_128();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_3_128>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_3_128


class Haval_4_128 : public Haval4
{
public:
	Haval_4_128()
		: Haval4(HashSize128)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_4_128 HashInstance;

		HashInstance = Haval_4_128();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_4_128>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_4_128


class Haval_5_128 : public Haval5
{
public:
	Haval_5_128()
		: Haval5(HashSize128)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_5_128 HashInstance;

		HashInstance = Haval_5_128();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_5_128>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_5_128


class Haval_3_160 : public Haval3
{
public:
	Haval_3_160()
		: Haval3(HashSize160)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_3_160 HashInstance;

		HashInstance = Haval_3_160();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_3_160>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_3_160


class Haval_4_160 : public Haval4
{
public:
	Haval_4_160()
		: Haval4(HashSize160)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_4_160 HashInstance;

		HashInstance = Haval_4_160();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_4_160>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_4_160


class Haval_5_160 : public Haval5
{
public:
	Haval_5_160()
		: Haval5(HashSize160)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_5_160 HashInstance;

		HashInstance = Haval_5_160();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_5_160>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_5_160


class Haval_3_192 : public Haval3
{
public:
	Haval_3_192()
		: Haval3(HashSize192)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_3_192 HashInstance;

		HashInstance = Haval_3_192();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_3_192>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_3_192


class Haval_4_192 : public Haval4
{
public:
	Haval_4_192()
		: Haval4(HashSize192)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_4_192 HashInstance;

		HashInstance = Haval_4_192();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_4_192>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_4_192


class Haval_5_192 : public Haval5
{
public:
	Haval_5_192()
		: Haval5(HashSize192)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_5_192 HashInstance;

		HashInstance = Haval_5_192();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_5_192>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_5_192


class Haval_3_224 : public Haval3
{
public:
	Haval_3_224()
		: Haval3(HashSize224)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_3_224 HashInstance;

		HashInstance = Haval_3_224();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_3_224>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_3_224


class Haval_4_224 : public Haval4
{
public:
	Haval_4_224()
		: Haval4(HashSize224)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_4_224 HashInstance;

		HashInstance = Haval_4_224();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_4_224>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_4_224


class Haval_5_224 : public Haval5
{
public:
	Haval_5_224()
		: Haval5(HashSize224)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_5_224 HashInstance;

		HashInstance = Haval_5_224();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_5_224>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_5_224


class Haval_3_256 : public Haval3
{
public:
	Haval_3_256()
		: Haval3(HashSize256)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_3_256 HashInstance;

		HashInstance = Haval_3_256();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_3_256>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_3_256


class Haval_4_256 : public Haval4
{
public:
	Haval_4_256()
		: Haval4(HashSize256)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_4_256 HashInstance;

		HashInstance = Haval_4_256();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_4_256>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_4_256


class Haval_5_256 : public Haval5
{
public:
	Haval_5_256()
		: Haval5(HashSize256)
	{} // end constructor

	virtual IHash Clone() const
	{
		Haval_5_256 HashInstance;

		HashInstance = Haval_5_256();
		HashInstance.rounds = rounds;
		HashInstance._HashSize = _HashSize;
		HashInstance.hash = hash;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<Haval_5_256>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

}; // end class Haval_5_256



#endif // !HLPHAVAL_H

