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

#ifndef HLPRIPEMD_H
#define HLPRIPEMD_H

#include "HlpMDBase.h"


class RIPEMD : public MDBase, public IITransformBlock
{
public:
	RIPEMD()
		: MDBase(4, 16)
	{
		name = __func__;

		data.resize(16);
	} // end constructor

	virtual IHash Clone() const
	{
		RIPEMD HashInstance;

		HashInstance = RIPEMD();
		HashInstance.state = state;
		HashInstance.buffer = make_shared<HashBuffer>(buffer->Clone());
		HashInstance.processed_bytes = processed_bytes;

		IHash hash = make_shared<RIPEMD>(HashInstance);
		hash->SetBufferSize(GetBufferSize());

		return hash;
	}

private:
	static inline uint32_t P1(const uint32_t a, const uint32_t b, const uint32_t c)
	{
		return (a & b) | (~a & c);
	} // end function P1

	static inline uint32_t P2(const uint32_t a, const uint32_t b, const uint32_t c)
	{
		return (a & b) | (a & c) | (b & c);
	} // end function P2

	static inline uint32_t P3(const uint32_t a, const uint32_t b, const uint32_t c)
	{
		return a ^ b ^ c;
	} // end function P3

protected:
	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t a, b, c, d, aa, bb, cc, dd;

		Converters::le32_copy(a_data, a_index, &data[0], 0, 64);

		a = state[0];
		b = state[1];
		c = state[2];
		d = state[3];
		aa = a;
		bb = b;
		cc = c;
		dd = d;

		a = Bits::RotateLeft32(P1(b, c, d) + a + data[0], 11);
		d = Bits::RotateLeft32(P1(a, b, c) + d + data[1], 14);
		c = Bits::RotateLeft32(P1(d, a, b) + c + data[2], 15);
		b = Bits::RotateLeft32(P1(c, d, a) + b + data[3], 12);
		a = Bits::RotateLeft32(P1(b, c, d) + a + data[4], 5);
		d = Bits::RotateLeft32(P1(a, b, c) + d + data[5], 8);
		c = Bits::RotateLeft32(P1(d, a, b) + c + data[6], 7);
		b = Bits::RotateLeft32(P1(c, d, a) + b + data[7], 9);
		a = Bits::RotateLeft32(P1(b, c, d) + a + data[8], 11);
		d = Bits::RotateLeft32(P1(a, b, c) + d + data[9], 13);
		c = Bits::RotateLeft32(P1(d, a, b) + c + data[10], 14);
		b = Bits::RotateLeft32(P1(c, d, a) + b + data[11], 15);
		a = Bits::RotateLeft32(P1(b, c, d) + a + data[12], 6);
		d = Bits::RotateLeft32(P1(a, b, c) + d + data[13], 7);
		c = Bits::RotateLeft32(P1(d, a, b) + c + data[14], 9);
		b = Bits::RotateLeft32(P1(c, d, a) + b + data[15], 8);

		a = Bits::RotateLeft32(P2(b, c, d) + a + data[7] + C2, 7);
		d = Bits::RotateLeft32(P2(a, b, c) + d + data[4] + C2, 6);
		c = Bits::RotateLeft32(P2(d, a, b) + c + data[13] + C2, 8);
		b = Bits::RotateLeft32(P2(c, d, a) + b + data[1] + C2, 13);
		a = Bits::RotateLeft32(P2(b, c, d) + a + data[10] + C2, 11);
		d = Bits::RotateLeft32(P2(a, b, c) + d + data[6] + C2, 9);
		c = Bits::RotateLeft32(P2(d, a, b) + c + data[15] + C2, 7);
		b = Bits::RotateLeft32(P2(c, d, a) + b + data[3] + C2, 15);
		a = Bits::RotateLeft32(P2(b, c, d) + a + data[12] + C2, 7);
		d = Bits::RotateLeft32(P2(a, b, c) + d + data[0] + C2, 12);
		c = Bits::RotateLeft32(P2(d, a, b) + c + data[9] + C2, 15);
		b = Bits::RotateLeft32(P2(c, d, a) + b + data[5] + C2, 9);
		a = Bits::RotateLeft32(P2(b, c, d) + a + data[14] + C2, 7);
		d = Bits::RotateLeft32(P2(a, b, c) + d + data[2] + C2, 11);
		c = Bits::RotateLeft32(P2(d, a, b) + c + data[11] + C2, 13);
		b = Bits::RotateLeft32(P2(c, d, a) + b + data[8] + C2, 12);

		a = Bits::RotateLeft32(P3(b, c, d) + a + data[3] + C4, 11);
		d = Bits::RotateLeft32(P3(a, b, c) + d + data[10] + C4, 13);
		c = Bits::RotateLeft32(P3(d, a, b) + c + data[2] + C4, 14);
		b = Bits::RotateLeft32(P3(c, d, a) + b + data[4] + C4, 7);
		a = Bits::RotateLeft32(P3(b, c, d) + a + data[9] + C4, 14);
		d = Bits::RotateLeft32(P3(a, b, c) + d + data[15] + C4, 9);
		c = Bits::RotateLeft32(P3(d, a, b) + c + data[8] + C4, 13);
		b = Bits::RotateLeft32(P3(c, d, a) + b + data[1] + C4, 15);
		a = Bits::RotateLeft32(P3(b, c, d) + a + data[14] + C4, 6);
		d = Bits::RotateLeft32(P3(a, b, c) + d + data[7] + C4, 8);
		c = Bits::RotateLeft32(P3(d, a, b) + c + data[0] + C4, 13);
		b = Bits::RotateLeft32(P3(c, d, a) + b + data[6] + C4, 6);
		a = Bits::RotateLeft32(P3(b, c, d) + a + data[11] + C4, 12);
		d = Bits::RotateLeft32(P3(a, b, c) + d + data[13] + C4, 5);
		c = Bits::RotateLeft32(P3(d, a, b) + c + data[5] + C4, 7);
		b = Bits::RotateLeft32(P3(c, d, a) + b + data[12] + C4, 5);

		aa = Bits::RotateLeft32(P1(bb, cc, dd) + aa + data[0] + C1, 11);
		dd = Bits::RotateLeft32(P1(aa, bb, cc) + dd + data[1] + C1, 14);
		cc = Bits::RotateLeft32(P1(dd, aa, bb) + cc + data[2] + C1, 15);
		bb = Bits::RotateLeft32(P1(cc, dd, aa) + bb + data[3] + C1, 12);
		aa = Bits::RotateLeft32(P1(bb, cc, dd) + aa + data[4] + C1, 5);
		dd = Bits::RotateLeft32(P1(aa, bb, cc) + dd + data[5] + C1, 8);
		cc = Bits::RotateLeft32(P1(dd, aa, bb) + cc + data[6] + C1, 7);
		bb = Bits::RotateLeft32(P1(cc, dd, aa) + bb + data[7] + C1, 9);
		aa = Bits::RotateLeft32(P1(bb, cc, dd) + aa + data[8] + C1, 11);
		dd = Bits::RotateLeft32(P1(aa, bb, cc) + dd + data[9] + C1, 13);
		cc = Bits::RotateLeft32(P1(dd, aa, bb) + cc + data[10] + C1, 14);
		bb = Bits::RotateLeft32(P1(cc, dd, aa) + bb + data[11] + C1, 15);
		aa = Bits::RotateLeft32(P1(bb, cc, dd) + aa + data[12] + C1, 6);
		dd = Bits::RotateLeft32(P1(aa, bb, cc) + dd + data[13] + C1, 7);
		cc = Bits::RotateLeft32(P1(dd, aa, bb) + cc + data[14] + C1, 9);
		bb = Bits::RotateLeft32(P1(cc, dd, aa) + bb + data[15] + C1, 8);

		aa = Bits::RotateLeft32(P2(bb, cc, dd) + aa + data[7], 7);
		dd = Bits::RotateLeft32(P2(aa, bb, cc) + dd + data[4], 6);
		cc = Bits::RotateLeft32(P2(dd, aa, bb) + cc + data[13], 8);
		bb = Bits::RotateLeft32(P2(cc, dd, aa) + bb + data[1], 13);
		aa = Bits::RotateLeft32(P2(bb, cc, dd) + aa + data[10], 11);
		dd = Bits::RotateLeft32(P2(aa, bb, cc) + dd + data[6], 9);
		cc = Bits::RotateLeft32(P2(dd, aa, bb) + cc + data[15], 7);
		bb = Bits::RotateLeft32(P2(cc, dd, aa) + bb + data[3], 15);
		aa = Bits::RotateLeft32(P2(bb, cc, dd) + aa + data[12], 7);
		dd = Bits::RotateLeft32(P2(aa, bb, cc) + dd + data[0], 12);
		cc = Bits::RotateLeft32(P2(dd, aa, bb) + cc + data[9], 15);
		bb = Bits::RotateLeft32(P2(cc, dd, aa) + bb + data[5], 9);
		aa = Bits::RotateLeft32(P2(bb, cc, dd) + aa + data[14], 7);
		dd = Bits::RotateLeft32(P2(aa, bb, cc) + dd + data[2], 11);
		cc = Bits::RotateLeft32(P2(dd, aa, bb) + cc + data[11], 13);
		bb = Bits::RotateLeft32(P2(cc, dd, aa) + bb + data[8], 12);

		aa = Bits::RotateLeft32(P3(bb, cc, dd) + aa + data[3] + C3, 11);
		dd = Bits::RotateLeft32(P3(aa, bb, cc) + dd + data[10] + C3, 13);
		cc = Bits::RotateLeft32(P3(dd, aa, bb) + cc + data[2] + C3, 14);
		bb = Bits::RotateLeft32(P3(cc, dd, aa) + bb + data[4] + C3, 7);
		aa = Bits::RotateLeft32(P3(bb, cc, dd) + aa + data[9] + C3, 14);
		dd = Bits::RotateLeft32(P3(aa, bb, cc) + dd + data[15] + C3, 9);
		cc = Bits::RotateLeft32(P3(dd, aa, bb) + cc + data[8] + C3, 13);
		bb = Bits::RotateLeft32(P3(cc, dd, aa) + bb + data[1] + C3, 15);
		aa = Bits::RotateLeft32(P3(bb, cc, dd) + aa + data[14] + C3, 6);
		dd = Bits::RotateLeft32(P3(aa, bb, cc) + dd + data[7] + C3, 8);
		cc = Bits::RotateLeft32(P3(dd, aa, bb) + cc + data[0] + C3, 13);
		bb = Bits::RotateLeft32(P3(cc, dd, aa) + bb + data[6] + C3, 6);
		aa = Bits::RotateLeft32(P3(bb, cc, dd) + aa + data[11] + C3, 12);
		dd = Bits::RotateLeft32(P3(aa, bb, cc) + dd + data[13] + C3, 5);
		cc = Bits::RotateLeft32(P3(dd, aa, bb) + cc + data[5] + C3, 7);
		bb = Bits::RotateLeft32(P3(cc, dd, aa) + bb + data[12] + C3, 5);

		cc = cc + state[0] + b;
		state[0]  = state[1] + c + dd;
		state[1]  = state[2] + d + aa;
		state[2]  = state[3] + a + bb;
		state[3]  = cc;

		memset(&data[0], 0, 16 * sizeof(uint32_t));

} // end function 

private:
	HashLibUInt32Array data;

}; // end class 


#endif //!HLPRIPEMD_H