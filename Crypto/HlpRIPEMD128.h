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

#ifndef HLPRIPEMD128_H
#define HLPRIPEMD128_H

#include "HlpMDBase.h"


class RIPEMD128 : public MDBase, public IITransformBlock
{
public:
	RIPEMD128()
		: MDBase(4, 16)
	{
		name = __func__;

		data = shared_ptr<uint32_t>(new uint32_t[16], default_delete<uint32_t[]>());
	} // end constructor

	~RIPEMD128()
	{} // end destructor


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
		aa = a;
		bb = b;
		cc = c;
		dd = d;

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

		a = a + (data.get()[7] + C2 + ((b & c) | (~b & d)));
		a = Bits::RotateLeft32(a, 7);
		d = d + (data.get()[4] + C2 + ((a & b) | (~a & c)));
		d = Bits::RotateLeft32(d, 6);
		c = c + (data.get()[13] + C2 + ((d & a) | (~d & b)));
		c = Bits::RotateLeft32(c, 8);
		b = b + (data.get()[1] + C2 + ((c & d) | (~c & a)));
		b = Bits::RotateLeft32(b, 13);
		a = a + (data.get()[10] + C2 + ((b & c) | (~b & d)));
		a = Bits::RotateLeft32(a, 11);
		d = d + (data.get()[6] + C2 + ((a & b) | (~a & c)));
		d = Bits::RotateLeft32(d, 9);
		c = c + (data.get()[15] + C2 + ((d & a) | (~d & b)));
		c = Bits::RotateLeft32(c, 7);
		b = b + (data.get()[3] + C2 + ((c & d) | (~c & a)));
		b = Bits::RotateLeft32(b, 15);
		a = a + (data.get()[12] + C2 + ((b & c) | (~b & d)));
		a = Bits::RotateLeft32(a, 7);
		d = d + (data.get()[0] + C2 + ((a & b) | (~a & c)));
		d = Bits::RotateLeft32(d, 12);
		c = c + (data.get()[9] + C2 + ((d & a) | (~d & b)));
		c = Bits::RotateLeft32(c, 15);
		b = b + (data.get()[5] + C2 + ((c & d) | (~c & a)));
		b = Bits::RotateLeft32(b, 9);
		a = a + (data.get()[2] + C2 + ((b & c) | (~b & d)));
		a = Bits::RotateLeft32(a, 11);
		d = d + (data.get()[14] + C2 + ((a & b) | (~a & c)));
		d = Bits::RotateLeft32(d, 7);
		c = c + (data.get()[11] + C2 + ((d & a) | (~d & b)));
		c = Bits::RotateLeft32(c, 13);
		b = b + (data.get()[8] + C2 + ((c & d) | (~c & a)));
		b = Bits::RotateLeft32(b, 12);

		a = a + (data.get()[3] + C4 + ((b | ~c) ^ d));
		a = Bits::RotateLeft32(a, 11);
		d = d + (data.get()[10] + C4 + ((a | ~b) ^ c));
		d = Bits::RotateLeft32(d, 13);
		c = c + (data.get()[14] + C4 + ((d | ~a) ^ b));
		c = Bits::RotateLeft32(c, 6);
		b = b + (data.get()[4] + C4 + ((c | ~d) ^ a));
		b = Bits::RotateLeft32(b, 7);
		a = a + (data.get()[9] + C4 + ((b | ~c) ^ d));
		a = Bits::RotateLeft32(a, 14);
		d = d + (data.get()[15] + C4 + ((a | ~b) ^ c));
		d = Bits::RotateLeft32(d, 9);
		c = c + (data.get()[8] + C4 + ((d | ~a) ^ b));
		c = Bits::RotateLeft32(c, 13);
		b = b + (data.get()[1] + C4 + ((c | ~d) ^ a));
		b = Bits::RotateLeft32(b, 15);
		a = a + (data.get()[2] + C4 + ((b | ~c) ^ d));
		a = Bits::RotateLeft32(a, 14);
		d = d + (data.get()[7] + C4 + ((a | ~b) ^ c));
		d = Bits::RotateLeft32(d, 8);
		c = c + (data.get()[0] + C4 + ((d | ~a) ^ b));
		c = Bits::RotateLeft32(c, 13);
		b = b + (data.get()[6] + C4 + ((c | ~d) ^ a));
		b = Bits::RotateLeft32(b, 6);
		a = a + (data.get()[13] + C4 + ((b | ~c) ^ d));
		a = Bits::RotateLeft32(a, 5);
		d = d + (data.get()[11] + C4 + ((a | ~b) ^ c));
		d = Bits::RotateLeft32(d, 12);
		c = c + (data.get()[5] + C4 + ((d | ~a) ^ b));
		c = Bits::RotateLeft32(c, 7);
		b = b + (data.get()[12] + C4 + ((c | ~d) ^ a));
		b = Bits::RotateLeft32(b, 5);

		a = a + (data.get()[1] + C6 + ((b & d) | (c & ~d)));
		a = Bits::RotateLeft32(a, 11);
		d = d + (data.get()[9] + C6 + ((a & c) | (b & ~c)));
		d = Bits::RotateLeft32(d, 12);
		c = c + (data.get()[11] + C6 + ((d & b) | (a & ~b)));
		c = Bits::RotateLeft32(c, 14);
		b = b + (data.get()[10] + C6 + ((c & a) | (d & ~a)));
		b = Bits::RotateLeft32(b, 15);
		a = a + (data.get()[0] + C6 + ((b & d) | (c & ~d)));
		a = Bits::RotateLeft32(a, 14);
		d = d + (data.get()[8] + C6 + ((a & c) | (b & ~c)));
		d = Bits::RotateLeft32(d, 15);
		c = c + (data.get()[12] + C6 + ((d & b) | (a & ~b)));
		c = Bits::RotateLeft32(c, 9);
		b = b + (data.get()[4] + C6 + ((c & a) | (d & ~a)));
		b = Bits::RotateLeft32(b, 8);
		a = a + (data.get()[13] + C6 + ((b & d) | (c & ~d)));
		a = Bits::RotateLeft32(a, 9);
		d = d + (data.get()[3] + C6 + ((a & c) | (b & ~c)));
		d = Bits::RotateLeft32(d, 14);
		c = c + (data.get()[7] + C6 + ((d & b) | (a & ~b)));
		c = Bits::RotateLeft32(c, 5);
		b = b + (data.get()[15] + C6 + ((c & a) | (d & ~a)));
		b = Bits::RotateLeft32(b, 6);
		a = a + (data.get()[14] + C6 + ((b & d) | (c & ~d)));
		a = Bits::RotateLeft32(a, 8);
		d = d + (data.get()[5] + C6 + ((a & c) | (b & ~c)));
		d = Bits::RotateLeft32(d, 6);
		c = c + (data.get()[6] + C6 + ((d & b) | (a & ~b)));
		c = Bits::RotateLeft32(c, 5);
		b = b + (data.get()[2] + C6 + ((c & a) | (d & ~a)));
		b = Bits::RotateLeft32(b, 12);

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

		aa = aa + (data.get()[6] + C3 + ((bb | ~cc) ^ dd));
		aa = Bits::RotateLeft32(aa, 9);
		dd = dd + (data.get()[11] + C3 + ((aa | ~bb) ^ cc));
		dd = Bits::RotateLeft32(dd, 13);
		cc = cc + (data.get()[3] + C3 + ((dd | ~aa) ^ bb));
		cc = Bits::RotateLeft32(cc, 15);
		bb = bb + (data.get()[7] + C3 + ((cc | ~dd) ^ aa));
		bb = Bits::RotateLeft32(bb, 7);
		aa = aa + (data.get()[0] + C3 + ((bb | ~cc) ^ dd));
		aa = Bits::RotateLeft32(aa, 12);
		dd = dd + (data.get()[13] + C3 + ((aa | ~bb) ^ cc));
		dd = Bits::RotateLeft32(dd, 8);
		cc = cc + (data.get()[5] + C3 + ((dd | ~aa) ^ bb));
		cc = Bits::RotateLeft32(cc, 9);
		bb = bb + (data.get()[10] + C3 + ((cc | ~dd) ^ aa));
		bb = Bits::RotateLeft32(bb, 11);
		aa = aa + (data.get()[14] + C3 + ((bb | ~cc) ^ dd));
		aa = Bits::RotateLeft32(aa, 7);
		dd = dd + (data.get()[15] + C3 + ((aa | ~bb) ^ cc));
		dd = Bits::RotateLeft32(dd, 7);
		cc = cc + (data.get()[8] + C3 + ((dd | ~aa) ^ bb));
		cc = Bits::RotateLeft32(cc, 12);
		bb = bb + (data.get()[12] + C3 + ((cc | ~dd) ^ aa));
		bb = Bits::RotateLeft32(bb, 7);
		aa = aa + (data.get()[4] + C3 + ((bb | ~cc) ^ dd));
		aa = Bits::RotateLeft32(aa, 6);
		dd = dd + (data.get()[9] + C3 + ((aa | ~bb) ^ cc));
		dd = Bits::RotateLeft32(dd, 15);
		cc = cc + (data.get()[1] + C3 + ((dd | ~aa) ^ bb));
		cc = Bits::RotateLeft32(cc, 13);
		bb = bb + (data.get()[2] + C3 + ((cc | ~dd) ^ aa));
		bb = Bits::RotateLeft32(bb, 11);

		aa = aa + (data.get()[15] + C5 + ((bb & cc) | (~bb & dd)));
		aa = Bits::RotateLeft32(aa, 9);
		dd = dd + (data.get()[5] + C5 + ((aa & bb) | (~aa & cc)));
		dd = Bits::RotateLeft32(dd, 7);
		cc = cc + (data.get()[1] + C5 + ((dd & aa) | (~dd & bb)));
		cc = Bits::RotateLeft32(cc, 15);
		bb = bb + (data.get()[3] + C5 + ((cc & dd) | (~cc & aa)));
		bb = Bits::RotateLeft32(bb, 11);
		aa = aa + (data.get()[7] + C5 + ((bb & cc) | (~bb & dd)));
		aa = Bits::RotateLeft32(aa, 8);
		dd = dd + (data.get()[14] + C5 + ((aa & bb) | (~aa & cc)));
		dd = Bits::RotateLeft32(dd, 6);
		cc = cc + (data.get()[6] + C5 + ((dd & aa) | (~dd & bb)));
		cc = Bits::RotateLeft32(cc, 6);
		bb = bb + (data.get()[9] + C5 + ((cc & dd) | (~cc & aa)));
		bb = Bits::RotateLeft32(bb, 14);
		aa = aa + (data.get()[11] + C5 + ((bb & cc) | (~bb & dd)));
		aa = Bits::RotateLeft32(aa, 12);
		dd = dd + (data.get()[8] + C5 + ((aa & bb) | (~aa & cc)));
		dd = Bits::RotateLeft32(dd, 13);
		cc = cc + (data.get()[12] + C5 + ((dd & aa) | (~dd & bb)));
		cc = Bits::RotateLeft32(cc, 5);
		bb = bb + (data.get()[2] + C5 + ((cc & dd) | (~cc & aa)));
		bb = Bits::RotateLeft32(bb, 14);
		aa = aa + (data.get()[10] + C5 + ((bb & cc) | (~bb & dd)));
		aa = Bits::RotateLeft32(aa, 13);
		dd = dd + (data.get()[0] + C5 + ((aa & bb) | (~aa & cc)));
		dd = Bits::RotateLeft32(dd, 13);
		cc = cc + (data.get()[4] + C5 + ((dd & aa) | (~dd & bb)));
		cc = Bits::RotateLeft32(cc, 7);
		bb = bb + (data.get()[13] + C5 + ((cc & dd) | (~cc & aa)));
		bb = Bits::RotateLeft32(bb, 5);

		aa = aa + (data.get()[8] + (bb ^ cc ^ dd));
		aa = Bits::RotateLeft32(aa, 15);
		dd = dd + (data.get()[6] + (aa ^ bb ^ cc));
		dd = Bits::RotateLeft32(dd, 5);
		cc = cc + (data.get()[4] + (dd ^ aa ^ bb));
		cc = Bits::RotateLeft32(cc, 8);
		bb = bb + (data.get()[1] + (cc ^ dd ^ aa));
		bb = Bits::RotateLeft32(bb, 11);
		aa = aa + (data.get()[3] + (bb ^ cc ^ dd));
		aa = Bits::RotateLeft32(aa, 14);
		dd = dd + (data.get()[11] + (aa ^ bb ^ cc));
		dd = Bits::RotateLeft32(dd, 14);
		cc = cc + (data.get()[15] + (dd ^ aa ^ bb));
		cc = Bits::RotateLeft32(cc, 6);
		bb = bb + (data.get()[0] + (cc ^ dd ^ aa));
		bb = Bits::RotateLeft32(bb, 14);
		aa = aa + (data.get()[5] + (bb ^ cc ^ dd));
		aa = Bits::RotateLeft32(aa, 6);
		dd = dd + (data.get()[12] + (aa ^ bb ^ cc));
		dd = Bits::RotateLeft32(dd, 9);
		cc = cc + (data.get()[2] + (dd ^ aa ^ bb));
		cc = Bits::RotateLeft32(cc, 12);
		bb = bb + (data.get()[13] + (cc ^ dd ^ aa));
		bb = Bits::RotateLeft32(bb, 9);
		aa = aa + (data.get()[9] + (bb ^ cc ^ dd));
		aa = Bits::RotateLeft32(aa, 12);
		dd = dd + (data.get()[7] + (aa ^ bb ^ cc));
		dd = Bits::RotateLeft32(dd, 5);
		cc = cc + (data.get()[10] + (dd ^ aa ^ bb));
		cc = Bits::RotateLeft32(cc, 15);
		bb = bb + (data.get()[14] + (cc ^ dd ^ aa));
		bb = Bits::RotateLeft32(bb, 8);

		dd = dd + c + (*state)[1];
		(*state)[1]  = (*state)[2] + d + aa;
		(*state)[2]  = (*state)[3] + a + bb;
		(*state)[3]  = (*state)[0] + b + cc;
		(*state)[0]  = dd;

		memset(&data.get()[0], 0, 16 * sizeof(uint32_t));

	} // end function 

private:
	shared_ptr<uint32_t> data;

}; // end class RIPEMD128


#endif //!HLPRIPEMD128_H