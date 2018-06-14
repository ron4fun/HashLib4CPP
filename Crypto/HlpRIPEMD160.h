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

#ifndef HLPRIPEMD160_H
#define HLPRIPEMD160_H

#include "HlpMDBase.h"


class RIPEMD160 : public MDBase, public IITransformBlock
{
public:
	RIPEMD160()
		: MDBase(5, 20)
	{
		name = __func__;

		data = shared_ptr<uint32_t>(new uint32_t[16], default_delete<uint32_t[]>());
	} // end constructor

	~RIPEMD160()
	{} // end destructor

	virtual void Initialize()
	{
		(*state)[4] = 0xC3D2E1F0;

		MDBase::Initialize();
	} // end function Initialize

protected:
	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t a, b, c, d, e, aa, bb, cc, dd, ee;

		Converters::le32_copy(a_data, a_index, &data.get()[0], 0, 64);

		a = (*state)[0];
		b = (*state)[1];
		c = (*state)[2];
		d = (*state)[3];
		e = (*state)[4];
		aa = a;
		bb = b;
		cc = c;
		dd = d;
		ee = e;

		a = a + (data.get()[0] + (b ^ c ^ d));
		a = Bits::RotateLeft32(a, 11) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[1] + (a ^ b ^ c));
		e = Bits::RotateLeft32(e, 14) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[2] + (e ^ a ^ b));
		d = Bits::RotateLeft32(d, 15) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[3] + (d ^ e ^ a));
		c = Bits::RotateLeft32(c, 12) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[4] + (c ^ d ^ e));
		b = Bits::RotateLeft32(b, 5) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[5] + (b ^ c ^ d));
		a = Bits::RotateLeft32(a, 8) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[6] + (a ^ b ^ c));
		e = Bits::RotateLeft32(e, 7) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[7] + (e ^ a ^ b));
		d = Bits::RotateLeft32(d, 9) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[8] + (d ^ e ^ a));
		c = Bits::RotateLeft32(c, 11) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[9] + (c ^ d ^ e));
		b = Bits::RotateLeft32(b, 13) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[10] + (b ^ c ^ d));
		a = Bits::RotateLeft32(a, 14) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[11] + (a ^ b ^ c));
		e = Bits::RotateLeft32(e, 15) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[12] + (e ^ a ^ b));
		d = Bits::RotateLeft32(d, 6) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[13] + (d ^ e ^ a));
		c = Bits::RotateLeft32(c, 7) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[14] + (c ^ d ^ e));
		b = Bits::RotateLeft32(b, 9) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[15] + (b ^ c ^ d));
		a = Bits::RotateLeft32(a, 8) + e;
		c = Bits::RotateLeft32(c, 10);

		aa = aa + (data.get()[5] + C1 + (bb ^ (cc | ~dd)));
		aa = Bits::RotateLeft32(aa, 8) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[14] + C1 + (aa ^ (bb | ~cc)));
		ee = Bits::RotateLeft32(ee, 9) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[7] + C1 + (ee ^ (aa | ~bb)));
		dd = Bits::RotateLeft32(dd, 9) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[0] + C1 + (dd ^ (ee | ~aa)));
		cc = Bits::RotateLeft32(cc, 11) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[9] + C1 + (cc ^ (dd | ~ee)));
		bb = Bits::RotateLeft32(bb, 13) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[2] + C1 + (bb ^ (cc | ~dd)));
		aa = Bits::RotateLeft32(aa, 15) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[11] + C1 + (aa ^ (bb | ~cc)));
		ee = Bits::RotateLeft32(ee, 15) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[4] + C1 + (ee ^ (aa | ~bb)));
		dd = Bits::RotateLeft32(dd, 5) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[13] + C1 + (dd ^ (ee | ~aa)));
		cc = Bits::RotateLeft32(cc, 7) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[6] + C1 + (cc ^ (dd | ~ee)));
		bb = Bits::RotateLeft32(bb, 7) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[15] + C1 + (bb ^ (cc | ~dd)));
		aa = Bits::RotateLeft32(aa, 8) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[8] + C1 + (aa ^ (bb | ~cc)));
		ee = Bits::RotateLeft32(ee, 11) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[1] + C1 + (ee ^ (aa | ~bb)));
		dd = Bits::RotateLeft32(dd, 14) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[10] + C1 + (dd ^ (ee | ~aa)));
		cc = Bits::RotateLeft32(cc, 14) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[3] + C1 + (cc ^ (dd | ~ee)));
		bb = Bits::RotateLeft32(bb, 12) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[12] + C1 + (bb ^ (cc | ~dd)));
		aa = Bits::RotateLeft32(aa, 6) + ee;
		cc = Bits::RotateLeft32(cc, 10);

		e = e + (data.get()[7] + C2 + ((a & b) | (~a & c)));
		e = Bits::RotateLeft32(e, 7) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[4] + C2 + ((e & a) | (~e & b)));
		d = Bits::RotateLeft32(d, 6) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[13] + C2 + ((d & e) | (~d & a)));
		c = Bits::RotateLeft32(c, 8) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[1] + C2 + ((c & d) | (~c & e)));
		b = Bits::RotateLeft32(b, 13) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[10] + C2 + ((b & c) | (~b & d)));
		a = Bits::RotateLeft32(a, 11) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[6] + C2 + ((a & b) | (~a & c)));
		e = Bits::RotateLeft32(e, 9) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[15] + C2 + ((e & a) | (~e & b)));
		d = Bits::RotateLeft32(d, 7) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[3] + C2 + ((d & e) | (~d & a)));
		c = Bits::RotateLeft32(c, 15) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[12] + C2 + ((c & d) | (~c & e)));
		b = Bits::RotateLeft32(b, 7) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[0] + C2 + ((b & c) | (~b & d)));
		a = Bits::RotateLeft32(a, 12) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[9] + C2 + ((a & b) | (~a & c)));
		e = Bits::RotateLeft32(e, 15) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[5] + C2 + ((e & a) | (~e & b)));
		d = Bits::RotateLeft32(d, 9) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[2] + C2 + ((d & e) | (~d & a)));
		c = Bits::RotateLeft32(c, 11) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[14] + C2 + ((c & d) | (~c & e)));
		b = Bits::RotateLeft32(b, 7) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[11] + C2 + ((b & c) | (~b & d)));
		a = Bits::RotateLeft32(a, 13) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[8] + C2 + ((a & b) | (~a & c)));
		e = Bits::RotateLeft32(e, 12) + d;
		b = Bits::RotateLeft32(b, 10);

		ee = ee + (data.get()[6] + C3 + ((aa & cc) | (bb & ~cc)));
		ee = Bits::RotateLeft32(ee, 9) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[11] + C3 + ((ee & bb) | (aa & ~bb)));
		dd = Bits::RotateLeft32(dd, 13) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[3] + C3 + ((dd & aa) | (ee & ~aa)));
		cc = Bits::RotateLeft32(cc, 15) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[7] + C3 + ((cc & ee) | (dd & ~ee)));
		bb = Bits::RotateLeft32(bb, 7) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[0] + C3 + ((bb & dd) | (cc & ~dd)));
		aa = Bits::RotateLeft32(aa, 12) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[13] + C3 + ((aa & cc) | (bb & ~cc)));
		ee = Bits::RotateLeft32(ee, 8) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[5] + C3 + ((ee & bb) | (aa & ~bb)));
		dd = Bits::RotateLeft32(dd, 9) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[10] + C3 + ((dd & aa) | (ee & ~aa)));
		cc = Bits::RotateLeft32(cc, 11) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[14] + C3 + ((cc & ee) | (dd & ~ee)));
		bb = Bits::RotateLeft32(bb, 7) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[15] + C3 + ((bb & dd) | (cc & ~dd)));
		aa = Bits::RotateLeft32(aa, 7) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[8] + C3 + ((aa & cc) | (bb & ~cc)));
		ee = Bits::RotateLeft32(ee, 12) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[12] + C3 + ((ee & bb) | (aa & ~bb)));
		dd = Bits::RotateLeft32(dd, 7) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[4] + C3 + ((dd & aa) | (ee & ~aa)));
		cc = Bits::RotateLeft32(cc, 6) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[9] + C3 + ((cc & ee) | (dd & ~ee)));
		bb = Bits::RotateLeft32(bb, 15) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[1] + C3 + ((bb & dd) | (cc & ~dd)));
		aa = Bits::RotateLeft32(aa, 13) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[2] + C3 + ((aa & cc) | (bb & ~cc)));
		ee = Bits::RotateLeft32(ee, 11) + dd;
		bb = Bits::RotateLeft32(bb, 10);

		d = d + (data.get()[3] + C4 + ((e | ~a) ^ b));
		d = Bits::RotateLeft32(d, 11) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[10] + C4 + ((d | ~e) ^ a));
		c = Bits::RotateLeft32(c, 13) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[14] + C4 + ((c | ~d) ^ e));
		b = Bits::RotateLeft32(b, 6) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[4] + C4 + ((b | ~c) ^ d));
		a = Bits::RotateLeft32(a, 7) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[9] + C4 + ((a | ~b) ^ c));
		e = Bits::RotateLeft32(e, 14) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[15] + C4 + ((e | ~a) ^ b));
		d = Bits::RotateLeft32(d, 9) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[8] + C4 + ((d | ~e) ^ a));
		c = Bits::RotateLeft32(c, 13) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[1] + C4 + ((c | ~d) ^ e));
		b = Bits::RotateLeft32(b, 15) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[2] + C4 + ((b | ~c) ^ d));
		a = Bits::RotateLeft32(a, 14) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[7] + C4 + ((a | ~b) ^ c));
		e = Bits::RotateLeft32(e, 8) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[0] + C4 + ((e | ~a) ^ b));
		d = Bits::RotateLeft32(d, 13) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[6] + C4 + ((d | ~e) ^ a));
		c = Bits::RotateLeft32(c, 6) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[13] + C4 + ((c | ~d) ^ e));
		b = Bits::RotateLeft32(b, 5) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[11] + C4 + ((b | ~c) ^ d));
		a = Bits::RotateLeft32(a, 12) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[5] + C4 + ((a | ~b) ^ c));
		e = Bits::RotateLeft32(e, 7) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[12] + C4 + ((e | ~a) ^ b));
		d = Bits::RotateLeft32(d, 5) + c;
		a = Bits::RotateLeft32(a, 10);

		dd = dd + (data.get()[15] + C5 + ((ee | ~aa) ^ bb));
		dd = Bits::RotateLeft32(dd, 9) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[5] + C5 + ((dd | ~ee) ^ aa));
		cc = Bits::RotateLeft32(cc, 7) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[1] + C5 + ((cc | ~dd) ^ ee));
		bb = Bits::RotateLeft32(bb, 15) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[3] + C5 + ((bb | ~cc) ^ dd));
		aa = Bits::RotateLeft32(aa, 11) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[7] + C5 + ((aa | ~bb) ^ cc));
		ee = Bits::RotateLeft32(ee, 8) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[14] + C5 + ((ee | ~aa) ^ bb));
		dd = Bits::RotateLeft32(dd, 6) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[6] + C5 + ((dd | ~ee) ^ aa));
		cc = Bits::RotateLeft32(cc, 6) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[9] + C5 + ((cc | ~dd) ^ ee));
		bb = Bits::RotateLeft32(bb, 14) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[11] + C5 + ((bb | ~cc) ^ dd));
		aa = Bits::RotateLeft32(aa, 12) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[8] + C5 + ((aa | ~bb) ^ cc));
		ee = Bits::RotateLeft32(ee, 13) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[12] + C5 + ((ee | ~aa) ^ bb));
		dd = Bits::RotateLeft32(dd, 5) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[2] + C5 + ((dd | ~ee) ^ aa));
		cc = Bits::RotateLeft32(cc, 14) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[10] + C5 + ((cc | ~dd) ^ ee));
		bb = Bits::RotateLeft32(bb, 13) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[0] + C5 + ((bb | ~cc) ^ dd));
		aa = Bits::RotateLeft32(aa, 13) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[4] + C5 + ((aa | ~bb) ^ cc));
		ee = Bits::RotateLeft32(ee, 7) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[13] + C5 + ((ee | ~aa) ^ bb));
		dd = Bits::RotateLeft32(dd, 5) + cc;
		aa = Bits::RotateLeft32(aa, 10);

		c = c + (data.get()[1] + C6 + ((d & a) | (e & ~a)));
		c = Bits::RotateLeft32(c, 11) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[9] + C6 + ((c & e) | (d & ~e)));
		b = Bits::RotateLeft32(b, 12) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[11] + C6 + ((b & d) | (c & ~d)));
		a = Bits::RotateLeft32(a, 14) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[10] + C6 + ((a & c) | (b & ~c)));
		e = Bits::RotateLeft32(e, 15) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[0] + C6 + ((e & b) | (a & ~b)));
		d = Bits::RotateLeft32(d, 14) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[8] + C6 + ((d & a) | (e & ~a)));
		c = Bits::RotateLeft32(c, 15) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[12] + C6 + ((c & e) | (d & ~e)));
		b = Bits::RotateLeft32(b, 9) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[4] + C6 + ((b & d) | (c & ~d)));
		a = Bits::RotateLeft32(a, 8) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[13] + C6 + ((a & c) | (b & ~c)));
		e = Bits::RotateLeft32(e, 9) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[3] + C6 + ((e & b) | (a & ~b)));
		d = Bits::RotateLeft32(d, 14) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[7] + C6 + ((d & a) | (e & ~a)));
		c = Bits::RotateLeft32(c, 5) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[15] + C6 + ((c & e) | (d & ~e)));
		b = Bits::RotateLeft32(b, 6) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[14] + C6 + ((b & d) | (c & ~d)));
		a = Bits::RotateLeft32(a, 8) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[5] + C6 + ((a & c) | (b & ~c)));
		e = Bits::RotateLeft32(e, 6) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[6] + C6 + ((e & b) | (a & ~b)));
		d = Bits::RotateLeft32(d, 5) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[2] + C6 + ((d & a) | (e & ~a)));
		c = Bits::RotateLeft32(c, 12) + b;
		e = Bits::RotateLeft32(e, 10);

		cc = cc + (data.get()[8] + C7 + ((dd & ee) | (~dd & aa)));
		cc = Bits::RotateLeft32(cc, 15) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[6] + C7 + ((cc & dd) | (~cc & ee)));
		bb = Bits::RotateLeft32(bb, 5) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[4] + C7 + ((bb & cc) | (~bb & dd)));
		aa = Bits::RotateLeft32(aa, 8) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[1] + C7 + ((aa & bb) | (~aa & cc)));
		ee = Bits::RotateLeft32(ee, 11) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[3] + C7 + ((ee & aa) | (~ee & bb)));
		dd = Bits::RotateLeft32(dd, 14) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[11] + C7 + ((dd & ee) | (~dd & aa)));
		cc = Bits::RotateLeft32(cc, 14) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[15] + C7 + ((cc & dd) | (~cc & ee)));
		bb = Bits::RotateLeft32(bb, 6) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[0] + C7 + ((bb & cc) | (~bb & dd)));
		aa = Bits::RotateLeft32(aa, 14) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[5] + C7 + ((aa & bb) | (~aa & cc)));
		ee = Bits::RotateLeft32(ee, 6) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[12] + C7 + ((ee & aa) | (~ee & bb)));
		dd = Bits::RotateLeft32(dd, 9) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[2] + C7 + ((dd & ee) | (~dd & aa)));
		cc = Bits::RotateLeft32(cc, 12) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[13] + C7 + ((cc & dd) | (~cc & ee)));
		bb = Bits::RotateLeft32(bb, 9) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[9] + C7 + ((bb & cc) | (~bb & dd)));
		aa = Bits::RotateLeft32(aa, 12) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[7] + C7 + ((aa & bb) | (~aa & cc)));
		ee = Bits::RotateLeft32(ee, 5) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[10] + C7 + ((ee & aa) | (~ee & bb)));
		dd = Bits::RotateLeft32(dd, 15) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[14] + C7 + ((dd & ee) | (~dd & aa)));
		cc = Bits::RotateLeft32(cc, 8) + bb;
		ee = Bits::RotateLeft32(ee, 10);

		b = b + (data.get()[4] + C8 + (c ^ (d | ~e)));
		b = Bits::RotateLeft32(b, 9) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[0] + C8 + (b ^ (c | ~d)));
		a = Bits::RotateLeft32(a, 15) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[5] + C8 + (a ^ (b | ~c)));
		e = Bits::RotateLeft32(e, 5) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[9] + C8 + (e ^ (a | ~b)));
		d = Bits::RotateLeft32(d, 11) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[7] + C8 + (d ^ (e | ~a)));
		c = Bits::RotateLeft32(c, 6) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[12] + C8 + (c ^ (d | ~e)));
		b = Bits::RotateLeft32(b, 8) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[2] + C8 + (b ^ (c | ~d)));
		a = Bits::RotateLeft32(a, 13) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[10] + C8 + (a ^ (b | ~c)));
		e = Bits::RotateLeft32(e, 12) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[14] + C8 + (e ^ (a | ~b)));
		d = Bits::RotateLeft32(d, 5) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[1] + C8 + (d ^ (e | ~a)));
		c = Bits::RotateLeft32(c, 12) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[3] + C8 + (c ^ (d | ~e)));
		b = Bits::RotateLeft32(b, 13) + a;
		d = Bits::RotateLeft32(d, 10);
		a = a + (data.get()[8] + C8 + (b ^ (c | ~d)));
		a = Bits::RotateLeft32(a, 14) + e;
		c = Bits::RotateLeft32(c, 10);
		e = e + (data.get()[11] + C8 + (a ^ (b | ~c)));
		e = Bits::RotateLeft32(e, 11) + d;
		b = Bits::RotateLeft32(b, 10);
		d = d + (data.get()[6] + C8 + (e ^ (a | ~b)));
		d = Bits::RotateLeft32(d, 8) + c;
		a = Bits::RotateLeft32(a, 10);
		c = c + (data.get()[15] + C8 + (d ^ (e | ~a)));
		c = Bits::RotateLeft32(c, 5) + b;
		e = Bits::RotateLeft32(e, 10);
		b = b + (data.get()[13] + C8 + (c ^ (d | ~e)));
		b = Bits::RotateLeft32(b, 6) + a;
		d = Bits::RotateLeft32(d, 10);

		bb = bb + (data.get()[12] + (cc ^ dd ^ ee));
		bb = Bits::RotateLeft32(bb, 8) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[15] + (bb ^ cc ^ dd));
		aa = Bits::RotateLeft32(aa, 5) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[10] + (aa ^ bb ^ cc));
		ee = Bits::RotateLeft32(ee, 12) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[4] + (ee ^ aa ^ bb));
		dd = Bits::RotateLeft32(dd, 9) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[1] + (dd ^ ee ^ aa));
		cc = Bits::RotateLeft32(cc, 12) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[5] + (cc ^ dd ^ ee));
		bb = Bits::RotateLeft32(bb, 5) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[8] + (bb ^ cc ^ dd));
		aa = Bits::RotateLeft32(aa, 14) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[7] + (aa ^ bb ^ cc));
		ee = Bits::RotateLeft32(ee, 6) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[6] + (ee ^ aa ^ bb));
		dd = Bits::RotateLeft32(dd, 8) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[2] + (dd ^ ee ^ aa));
		cc = Bits::RotateLeft32(cc, 13) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[13] + (cc ^ dd ^ ee));
		bb = Bits::RotateLeft32(bb, 6) + aa;
		dd = Bits::RotateLeft32(dd, 10);
		aa = aa + (data.get()[14] + (bb ^ cc ^ dd));
		aa = Bits::RotateLeft32(aa, 5) + ee;
		cc = Bits::RotateLeft32(cc, 10);
		ee = ee + (data.get()[0] + (aa ^ bb ^ cc));
		ee = Bits::RotateLeft32(ee, 15) + dd;
		bb = Bits::RotateLeft32(bb, 10);
		dd = dd + (data.get()[3] + (ee ^ aa ^ bb));
		dd = Bits::RotateLeft32(dd, 13) + cc;
		aa = Bits::RotateLeft32(aa, 10);
		cc = cc + (data.get()[9] + (dd ^ ee ^ aa));
		cc = Bits::RotateLeft32(cc, 11) + bb;
		ee = Bits::RotateLeft32(ee, 10);
		bb = bb + (data.get()[11] + (cc ^ dd ^ ee));
		bb = Bits::RotateLeft32(bb, 11) + aa;
		dd = Bits::RotateLeft32(dd, 10);

		dd = dd + c + (*state)[1];
		(*state)[1]  = (*state)[2] + d + ee;
		(*state)[2]  = (*state)[3] + e + aa;
		(*state)[3]  = (*state)[4] + a + bb;
		(*state)[4]  = (*state)[0] + b + cc;
		(*state)[0]  = dd;
		
		memset(&data.get()[0], 0, 16 * sizeof(uint32_t));

	} // end function 

private:
	shared_ptr<uint32_t> data;

}; // end class RIPEMD160


#endif //!HLPRIPEMD160_H