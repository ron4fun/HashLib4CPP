#ifndef HLPRIPEMD256_H
#define HLPRIPEMD256_H

#include "HlpMDBase.h"


class RIPEMD256 : public MDBase, public IITransformBlock
{
public:
	RIPEMD256()
		: MDBase(8, 32)
	{
		name = __func__;

		data = shared_ptr<uint32_t>(new uint32_t[16], default_delete<uint32_t[]>());
	} // end constructor

	~RIPEMD256()
	{} // end destructor

	virtual void Initialize()
	{
		(*state)[4] = 0x76543210;
		(*state)[5] = 0xFEDCBA98;
		(*state)[6] = 0x89ABCDEF;
		(*state)[7] = 0x01234567;

		MDBase::Initialize();
	} // end function Initialize

protected:
	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t a, b, c, d, aa, bb, cc, dd;

		Converters::le32_copy(a_data, a_index, &data.get()[0], 0, 64);

		a = (*state)[0];
		b = (*state)[1];
		c = (*state)[2];
		d = (*state)[3];
		aa = (*state)[4];
		bb = (*state)[5];
		cc = (*state)[6];
		dd = (*state)[7];

		a = a + (data.get()[0] + (b ^ c ^ d));
		a = Bits::RotateLeft32(a, 11);
		d = d + (data.get()[1] + (a ^ b ^ c));
		d = Bits::RotateLeft32(d, 14);
		c = c + (data.get()[2] + (d ^ a ^ b));
		c = Bits::RotateLeft32(c, 15);
		b = b + (data.get()[3] + (c ^ d ^ a));
		b = Bits::RotateLeft32(b, 12);
		a = a + (data.get()[4] + (b ^ c ^ d));
		a = Bits::RotateLeft32(a, 5);
		d = d + (data.get()[5] + (a ^ b ^ c));
		d = Bits::RotateLeft32(d, 8);
		c = c + (data.get()[6] + (d ^ a ^ b));
		c = Bits::RotateLeft32(c, 7);
		b = b + (data.get()[7] + (c ^ d ^ a));
		b = Bits::RotateLeft32(b, 9);
		a = a + (data.get()[8] + (b ^ c ^ d));
		a = Bits::RotateLeft32(a, 11);
		d = d + (data.get()[9] + (a ^ b ^ c));
		d = Bits::RotateLeft32(d, 13);
		c = c + (data.get()[10] + (d ^ a ^ b));
		c = Bits::RotateLeft32(c, 14);
		b = b + (data.get()[11] + (c ^ d ^ a));
		b = Bits::RotateLeft32(b, 15);
		a = a + (data.get()[12] + (b ^ c ^ d));
		a = Bits::RotateLeft32(a, 6);
		d = d + (data.get()[13] + (a ^ b ^ c));
		d = Bits::RotateLeft32(d, 7);
		c = c + (data.get()[14] + (d ^ a ^ b));
		c = Bits::RotateLeft32(c, 9);
		b = b + (data.get()[15] + (c ^ d ^ a));
		b = Bits::RotateLeft32(b, 8);

		aa = aa + (data.get()[5] + C1 + ((bb & dd) | (cc & ~dd)));
		aa = Bits::RotateLeft32(aa, 8);
		dd = dd + (data.get()[14] + C1 + ((aa & cc) | (bb & ~cc)));
		dd = Bits::RotateLeft32(dd, 9);
		cc = cc + (data.get()[7] + C1 + ((dd & bb) | (aa & ~bb)));
		cc = Bits::RotateLeft32(cc, 9);
		bb = bb + (data.get()[0] + C1 + ((cc & aa) | (dd & ~aa)));
		bb = Bits::RotateLeft32(bb, 11);
		aa = aa + (data.get()[9] + C1 + ((bb & dd) | (cc & ~dd)));
		aa = Bits::RotateLeft32(aa, 13);
		dd = dd + (data.get()[2] + C1 + ((aa & cc) | (bb & ~cc)));
		dd = Bits::RotateLeft32(dd, 15);
		cc = cc + (data.get()[11] + C1 + ((dd & bb) | (aa & ~bb)));
		cc = Bits::RotateLeft32(cc, 15);
		bb = bb + (data.get()[4] + C1 + ((cc & aa) | (dd & ~aa)));
		bb = Bits::RotateLeft32(bb, 5);
		aa = aa + (data.get()[13] + C1 + ((bb & dd) | (cc & ~dd)));
		aa = Bits::RotateLeft32(aa, 7);
		dd = dd + (data.get()[6] + C1 + ((aa & cc) | (bb & ~cc)));
		dd = Bits::RotateLeft32(dd, 7);
		cc = cc + (data.get()[15] + C1 + ((dd & bb) | (aa & ~bb)));
		cc = Bits::RotateLeft32(cc, 8);
		bb = bb + (data.get()[8] + C1 + ((cc & aa) | (dd & ~aa)));
		bb = Bits::RotateLeft32(bb, 11);
		aa = aa + (data.get()[1] + C1 + ((bb & dd) | (cc & ~dd)));
		aa = Bits::RotateLeft32(aa, 14);
		dd = dd + (data.get()[10] + C1 + ((aa & cc) | (bb & ~cc)));
		dd = Bits::RotateLeft32(dd, 14);
		cc = cc + (data.get()[3] + C1 + ((dd & bb) | (aa & ~bb)));
		cc = Bits::RotateLeft32(cc, 12);
		bb = bb + (data.get()[12] + C1 + ((cc & aa) | (dd & ~aa)));
		bb = Bits::RotateLeft32(bb, 6);

		aa = aa + (data.get()[7] + C2 + ((b & c) | (~b & d)));
		aa = Bits::RotateLeft32(aa, 7);
		d = d + (data.get()[4] + C2 + ((aa & b) | (~aa & c)));
		d = Bits::RotateLeft32(d, 6);
		c = c + (data.get()[13] + C2 + ((d & aa) | (~d & b)));
		c = Bits::RotateLeft32(c, 8);
		b = b + (data.get()[1] + C2 + ((c & d) | (~c & aa)));
		b = Bits::RotateLeft32(b, 13);
		aa = aa + (data.get()[10] + C2 + ((b & c) | (~b & d)));
		aa = Bits::RotateLeft32(aa, 11);
		d = d + (data.get()[6] + C2 + ((aa & b) | (~aa & c)));
		d = Bits::RotateLeft32(d, 9);
		c = c + (data.get()[15] + C2 + ((d & aa) | (~d & b)));
		c = Bits::RotateLeft32(c, 7);
		b = b + (data.get()[3] + C2 + ((c & d) | (~c & aa)));
		b = Bits::RotateLeft32(b, 15);
		aa = aa + (data.get()[12] + C2 + ((b & c) | (~b & d)));
		aa = Bits::RotateLeft32(aa, 7);
		d = d + (data.get()[0] + C2 + ((aa & b) | (~aa & c)));
		d = Bits::RotateLeft32(d, 12);
		c = c + (data.get()[9] + C2 + ((d & aa) | (~d & b)));
		c = Bits::RotateLeft32(c, 15);
		b = b + (data.get()[5] + C2 + ((c & d) | (~c & aa)));
		b = Bits::RotateLeft32(b, 9);
		aa = aa + (data.get()[2] + C2 + ((b & c) | (~b & d)));
		aa = Bits::RotateLeft32(aa, 11);
		d = d + (data.get()[14] + C2 + ((aa & b) | (~aa & c)));
		d = Bits::RotateLeft32(d, 7);
		c = c + (data.get()[11] + C2 + ((d & aa) | (~d & b)));
		c = Bits::RotateLeft32(c, 13);
		b = b + (data.get()[8] + C2 + ((c & d) | (~c & aa)));
		b = Bits::RotateLeft32(b, 12);

		a = a + (data.get()[6] + C3 + ((bb | ~cc) ^ dd));
		a = Bits::RotateLeft32(a, 9);
		dd = dd + (data.get()[11] + C3 + ((a | ~bb) ^ cc));
		dd = Bits::RotateLeft32(dd, 13);
		cc = cc + (data.get()[3] + C3 + ((dd | ~a) ^ bb));
		cc = Bits::RotateLeft32(cc, 15);
		bb = bb + (data.get()[7] + C3 + ((cc | ~dd) ^ a));
		bb = Bits::RotateLeft32(bb, 7);
		a = a + (data.get()[0] + C3 + ((bb | ~cc) ^ dd));
		a = Bits::RotateLeft32(a, 12);
		dd = dd + (data.get()[13] + C3 + ((a | ~bb) ^ cc));
		dd = Bits::RotateLeft32(dd, 8);
		cc = cc + (data.get()[5] + C3 + ((dd | ~a) ^ bb));
		cc = Bits::RotateLeft32(cc, 9);
		bb = bb + (data.get()[10] + C3 + ((cc | ~dd) ^ a));
		bb = Bits::RotateLeft32(bb, 11);
		a = a + (data.get()[14] + C3 + ((bb | ~cc) ^ dd));
		a = Bits::RotateLeft32(a, 7);
		dd = dd + (data.get()[15] + C3 + ((a | ~bb) ^ cc));
		dd = Bits::RotateLeft32(dd, 7);
		cc = cc + (data.get()[8] + C3 + ((dd | ~a) ^ bb));
		cc = Bits::RotateLeft32(cc, 12);
		bb = bb + (data.get()[12] + C3 + ((cc | ~dd) ^ a));
		bb = Bits::RotateLeft32(bb, 7);
		a = a + (data.get()[4] + C3 + ((bb | ~cc) ^ dd));
		a = Bits::RotateLeft32(a, 6);
		dd = dd + (data.get()[9] + C3 + ((a | ~bb) ^ cc));
		dd = Bits::RotateLeft32(dd, 15);
		cc = cc + (data.get()[1] + C3 + ((dd | ~a) ^ bb));
		cc = Bits::RotateLeft32(cc, 13);
		bb = bb + (data.get()[2] + C3 + ((cc | ~dd) ^ a));
		bb = Bits::RotateLeft32(bb, 11);

		aa = aa + (data.get()[3] + C4 + ((bb | ~c) ^ d));
		aa = Bits::RotateLeft32(aa, 11);
		d = d + (data.get()[10] + C4 + ((aa | ~bb) ^ c));
		d = Bits::RotateLeft32(d, 13);
		c = c + (data.get()[14] + C4 + ((d | ~aa) ^ bb));
		c = Bits::RotateLeft32(c, 6);
		bb = bb + (data.get()[4] + C4 + ((c | ~d) ^ aa));
		bb = Bits::RotateLeft32(bb, 7);
		aa = aa + (data.get()[9] + C4 + ((bb | ~c) ^ d));
		aa = Bits::RotateLeft32(aa, 14);
		d = d + (data.get()[15] + C4 + ((aa | ~bb) ^ c));
		d = Bits::RotateLeft32(d, 9);
		c = c + (data.get()[8] + C4 + ((d | ~aa) ^ bb));
		c = Bits::RotateLeft32(c, 13);
		bb = bb + (data.get()[1] + C4 + ((c | ~d) ^ aa));
		bb = Bits::RotateLeft32(bb, 15);
		aa = aa + (data.get()[2] + C4 + ((bb | ~c) ^ d));
		aa = Bits::RotateLeft32(aa, 14);
		d = d + (data.get()[7] + C4 + ((aa | ~bb) ^ c));
		d = Bits::RotateLeft32(d, 8);
		c = c + (data.get()[0] + C4 + ((d | ~aa) ^ bb));
		c = Bits::RotateLeft32(c, 13);
		bb = bb + (data.get()[6] + C4 + ((c | ~d) ^ aa));
		bb = Bits::RotateLeft32(bb, 6);
		aa = aa + (data.get()[13] + C4 + ((bb | ~c) ^ d));
		aa = Bits::RotateLeft32(aa, 5);
		d = d + (data.get()[11] + C4 + ((aa | ~bb) ^ c));
		d = Bits::RotateLeft32(d, 12);
		c = c + (data.get()[5] + C4 + ((d | ~aa) ^ bb));
		c = Bits::RotateLeft32(c, 7);
		bb = bb + (data.get()[12] + C4 + ((c | ~d) ^ aa));
		bb = Bits::RotateLeft32(bb, 5);

		a = a + (data.get()[15] + C5 + ((b & cc) | (~b & dd)));
		a = Bits::RotateLeft32(a, 9);
		dd = dd + (data.get()[5] + C5 + ((a & b) | (~a & cc)));
		dd = Bits::RotateLeft32(dd, 7);
		cc = cc + (data.get()[1] + C5 + ((dd & a) | (~dd & b)));
		cc = Bits::RotateLeft32(cc, 15);
		b = b + (data.get()[3] + C5 + ((cc & dd) | (~cc & a)));
		b = Bits::RotateLeft32(b, 11);
		a = a + (data.get()[7] + C5 + ((b & cc) | (~b & dd)));
		a = Bits::RotateLeft32(a, 8);
		dd = dd + (data.get()[14] + C5 + ((a & b) | (~a & cc)));
		dd = Bits::RotateLeft32(dd, 6);
		cc = cc + (data.get()[6] + C5 + ((dd & a) | (~dd & b)));
		cc = Bits::RotateLeft32(cc, 6);
		b = b + (data.get()[9] + C5 + ((cc & dd) | (~cc & a)));
		b = Bits::RotateLeft32(b, 14);
		a = a + (data.get()[11] + C5 + ((b & cc) | (~b & dd)));
		a = Bits::RotateLeft32(a, 12);
		dd = dd + (data.get()[8] + C5 + ((a & b) | (~a & cc)));
		dd = Bits::RotateLeft32(dd, 13);
		cc = cc + (data.get()[12] + C5 + ((dd & a) | (~dd & b)));
		cc = Bits::RotateLeft32(cc, 5);
		b = b + (data.get()[2] + C5 + ((cc & dd) | (~cc & a)));
		b = Bits::RotateLeft32(b, 14);
		a = a + (data.get()[10] + C5 + ((b & cc) | (~b & dd)));
		a = Bits::RotateLeft32(a, 13);
		dd = dd + (data.get()[0] + C5 + ((a & b) | (~a & cc)));
		dd = Bits::RotateLeft32(dd, 13);
		cc = cc + (data.get()[4] + C5 + ((dd & a) | (~dd & b)));
		cc = Bits::RotateLeft32(cc, 7);
		b = b + (data.get()[13] + C5 + ((cc & dd) | (~cc & a)));
		b = Bits::RotateLeft32(b, 5);

		aa = aa + (data.get()[1] + C6 + ((bb & d) | (cc & ~d)));
		aa = Bits::RotateLeft32(aa, 11);
		d = d + (data.get()[9] + C6 + ((aa & cc) | (bb & ~cc)));
		d = Bits::RotateLeft32(d, 12);
		cc = cc + (data.get()[11] + C6 + ((d & bb) | (aa & ~bb)));
		cc = Bits::RotateLeft32(cc, 14);
		bb = bb + (data.get()[10] + C6 + ((cc & aa) | (d & ~aa)));
		bb = Bits::RotateLeft32(bb, 15);
		aa = aa + (data.get()[0] + C6 + ((bb & d) | (cc & ~d)));
		aa = Bits::RotateLeft32(aa, 14);
		d = d + (data.get()[8] + C6 + ((aa & cc) | (bb & ~cc)));
		d = Bits::RotateLeft32(d, 15);
		cc = cc + (data.get()[12] + C6 + ((d & bb) | (aa & ~bb)));
		cc = Bits::RotateLeft32(cc, 9);
		bb = bb + (data.get()[4] + C6 + ((cc & aa) | (d & ~aa)));
		bb = Bits::RotateLeft32(bb, 8);
		aa = aa + (data.get()[13] + C6 + ((bb & d) | (cc & ~d)));
		aa = Bits::RotateLeft32(aa, 9);
		d = d + (data.get()[3] + C6 + ((aa & cc) | (bb & ~cc)));
		d = Bits::RotateLeft32(d, 14);
		cc = cc + (data.get()[7] + C6 + ((d & bb) | (aa & ~bb)));
		cc = Bits::RotateLeft32(cc, 5);
		bb = bb + (data.get()[15] + C6 + ((cc & aa) | (d & ~aa)));
		bb = Bits::RotateLeft32(bb, 6);
		aa = aa + (data.get()[14] + C6 + ((bb & d) | (cc & ~d)));
		aa = Bits::RotateLeft32(aa, 8);
		d = d + (data.get()[5] + C6 + ((aa & cc) | (bb & ~cc)));
		d = Bits::RotateLeft32(d, 6);
		cc = cc + (data.get()[6] + C6 + ((d & bb) | (aa & ~bb)));
		cc = Bits::RotateLeft32(cc, 5);
		bb = bb + (data.get()[2] + C6 + ((cc & aa) | (d & ~aa)));
		bb = Bits::RotateLeft32(bb, 12);

		a = a + (data.get()[8] + (b ^ c ^ dd));
		a = Bits::RotateLeft32(a, 15);
		dd = dd + (data.get()[6] + (a ^ b ^ c));
		dd = Bits::RotateLeft32(dd, 5);
		c = c + (data.get()[4] + (dd ^ a ^ b));
		c = Bits::RotateLeft32(c, 8);
		b = b + (data.get()[1] + (c ^ dd ^ a));
		b = Bits::RotateLeft32(b, 11);
		a = a + (data.get()[3] + (b ^ c ^ dd));
		a = Bits::RotateLeft32(a, 14);
		dd = dd + (data.get()[11] + (a ^ b ^ c));
		dd = Bits::RotateLeft32(dd, 14);
		c = c + (data.get()[15] + (dd ^ a ^ b));
		c = Bits::RotateLeft32(c, 6);
		b = b + (data.get()[0] + (c ^ dd ^ a));
		b = Bits::RotateLeft32(b, 14);
		a = a + (data.get()[5] + (b ^ c ^ dd));
		a = Bits::RotateLeft32(a, 6);
		dd = dd + (data.get()[12] + (a ^ b ^ c));
		dd = Bits::RotateLeft32(dd, 9);
		c = c + (data.get()[2] + (dd ^ a ^ b));
		c = Bits::RotateLeft32(c, 12);
		b = b + (data.get()[13] + (c ^ dd ^ a));
		b = Bits::RotateLeft32(b, 9);
		a = a + (data.get()[9] + (b ^ c ^ dd));
		a = Bits::RotateLeft32(a, 12);
		dd = dd + (data.get()[7] + (a ^ b ^ c));
		dd = Bits::RotateLeft32(dd, 5);
		c = c + (data.get()[10] + (dd ^ a ^ b));
		c = Bits::RotateLeft32(c, 15);
		b = b + (data.get()[14] + (c ^ dd ^ a));
		b = Bits::RotateLeft32(b, 8);

		(*state)[0]  = (*state)[0] + aa;
		(*state)[1]  = (*state)[1] + bb;
		(*state)[2]  = (*state)[2] + cc;
		(*state)[3]  = (*state)[3] + dd;
		(*state)[4]  = (*state)[4] + a;
		(*state)[5]  = (*state)[5] + b;
		(*state)[6]  = (*state)[6] + c;
		(*state)[7]  = (*state)[7] + d;

		memset(&data.get()[0], 0, 16 * sizeof(uint32_t));

	} // end function 

private:
	shared_ptr<uint32_t> data;

}; // end class RIPEMD256


#endif //!HLPRIPEMD256_H