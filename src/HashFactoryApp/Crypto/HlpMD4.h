#ifndef HLPMD4_H
#define HLPMD4_H

#include "HlpMDBase.h"


class MD4 : public MDBase, public IITransformBlock
{
public:
	MD4()
		: MDBase(4, 16)
	{
		name = __func__;

		data = shared_ptr<uint32_t>(new uint32_t[16], default_delete<uint32_t[]>());
	} // end constructor

	~MD4()
	{
		//delete[] data;
	} // end destructor

protected:
	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t a, b, c, d;

		Converters::le32_copy(a_data, a_index, &data.get()[0], 0, 64);

		a = (*state)[0];
		b = (*state)[1];
		c = (*state)[2];
		d = (*state)[3];

		a = a + (data.get()[0] + ((b & c) | ((~b) & d)));
		a = Bits::RotateLeft32(a, 3);
		d = d + (data.get()[1] + ((a & b) | ((~a) & c)));
		d = Bits::RotateLeft32(d, 7);
		c = c + (data.get()[2] + ((d & a) | ((~d) & b)));
		c = Bits::RotateLeft32(c, 11);
		b = b + (data.get()[3] + ((c & d) | ((~c) & a)));
		b = Bits::RotateLeft32(b, 19);
		a = a + (data.get()[4] + ((b & c) | ((~b) & d)));
		a = Bits::RotateLeft32(a, 3);
		d = d + (data.get()[5] + ((a & b) | ((~a) & c)));
		d = Bits::RotateLeft32(d, 7);
		c = c + (data.get()[6] + ((d & a) | ((~d) & b)));
		c = Bits::RotateLeft32(c, 11);
		b = b + (data.get()[7] + ((c & d) | ((~c) & a)));
		b = Bits::RotateLeft32(b, 19);
		a = a + (data.get()[8] + ((b & c) | ((~b) & d)));
		a = Bits::RotateLeft32(a, 3);
		d = d + (data.get()[9] + ((a & b) | ((~a) & c)));
		d = Bits::RotateLeft32(d, 7);
		c = c + (data.get()[10] + ((d & a) | ((~d) & b)));
		c = Bits::RotateLeft32(c, 11);
		b = b + (data.get()[11] + ((c & d) | ((~c) & a)));
		b = Bits::RotateLeft32(b, 19);
		a = a + (data.get()[12] + ((b & c) | ((~b) & d)));
		a = Bits::RotateLeft32(a, 3);
		d = d + (data.get()[13] + ((a & b) | ((~a) & c)));
		d = Bits::RotateLeft32(d, 7);
		c = c + (data.get()[14] + ((d & a) | ((~d) & b)));
		c = Bits::RotateLeft32(c, 11);
		b = b + (data.get()[15] + ((c & d) | ((~c) & a)));
		b = Bits::RotateLeft32(b, 19);

		a = a + (data.get()[0] + C2 + ((b & (c | d)) | (c & d)));
		a = Bits::RotateLeft32(a, 3);
		d = d + (data.get()[4] + C2 + ((a & (b | c)) | (b & c)));
		d = Bits::RotateLeft32(d, 5);
		c = c + (data.get()[8] + C2 + ((d & (a | b)) | (a & b)));
		c = Bits::RotateLeft32(c, 9);
		b = b + (data.get()[12] + C2 + ((c & (d | a)) | (d & a)));
		b = Bits::RotateLeft32(b, 13);
		a = a + (data.get()[1] + C2 + ((b & (c | d)) | (c & d)));
		a = Bits::RotateLeft32(a, 3);
		d = d + (data.get()[5] + C2 + ((a & (b | c)) | (b & c)));
		d = Bits::RotateLeft32(d, 5);
		c = c + (data.get()[9] + C2 + ((d & (a | b)) | (a & b)));
		c = Bits::RotateLeft32(c, 9);
		b = b + (data.get()[13] + C2 + ((c & (d | a)) | (d & a)));
		b = Bits::RotateLeft32(b, 13);
		a = a + (data.get()[2] + C2 + ((b & (c | d)) | (c & d)));
		a = Bits::RotateLeft32(a, 3);
		d = d + (data.get()[6] + C2 + ((a & (b | c)) | (b & c)));
		d = Bits::RotateLeft32(d, 5);
		c = c + (data.get()[10] + C2 + ((d & (a | b)) | (a & b)));
		c = Bits::RotateLeft32(c, 9);
		b = b + (data.get()[14] + C2 + ((c & (d | a)) | (d & a)));
		b = Bits::RotateLeft32(b, 13);
		a = a + (data.get()[3] + C2 + ((b & (c | d)) | (c & d)));
		a = Bits::RotateLeft32(a, 3);
		d = d + (data.get()[7] + C2 + ((a & (b | c)) | (b & c)));
		d = Bits::RotateLeft32(d, 5);
		c = c + (data.get()[11] + C2 + ((d & (a | b)) | (a & b)));
		c = Bits::RotateLeft32(c, 9);
		b = b + (data.get()[15] + C2 + ((c & (d | a)) | (d & a)));
		b = Bits::RotateLeft32(b, 13);

		a = a + (data.get()[0] + C4 + (b ^ c ^ d));
		a = Bits::RotateLeft32(a, 3);
		d = d + (data.get()[8] + C4 + (a ^ b ^ c));
		d = Bits::RotateLeft32(d, 9);
		c = c + (data.get()[4] + C4 + (d ^ a ^ b));
		c = Bits::RotateLeft32(c, 11);
		b = b + (data.get()[12] + C4 + (c ^ d ^ a));
		b = Bits::RotateLeft32(b, 15);
		a = a + (data.get()[2] + C4 + (b ^ c ^ d));
		a = Bits::RotateLeft32(a, 3);
		d = d + (data.get()[10] + C4 + (a ^ b ^ c));
		d = Bits::RotateLeft32(d, 9);
		c = c + (data.get()[6] + C4 + (d ^ a ^ b));
		c = Bits::RotateLeft32(c, 11);
		b = b + (data.get()[14] + C4 + (c ^ d ^ a));
		b = Bits::RotateLeft32(b, 15);
		a = a + (data.get()[1] + C4 + (b ^ c ^ d));
		a = Bits::RotateLeft32(a, 3);
		d = d + (data.get()[9] + C4 + (a ^ b ^ c));
		d = Bits::RotateLeft32(d, 9);
		c = c + (data.get()[5] + C4 + (d ^ a ^ b));
		c = Bits::RotateLeft32(c, 11);
		b = b + (data.get()[13] + C4 + (c ^ d ^ a));
		b = Bits::RotateLeft32(b, 15);
		a = a + (data.get()[3] + C4 + (b ^ c ^ d));
		a = Bits::RotateLeft32(a, 3);
		d = d + (data.get()[11] + C4 + (a ^ b ^ c));
		d = Bits::RotateLeft32(d, 9);
		c = c + (data.get()[7] + C4 + (d ^ a ^ b));
		c = Bits::RotateLeft32(c, 11);
		b = b + (data.get()[15] + C4 + (c ^ d ^ a));
		b = Bits::RotateLeft32(b, 15);

		(*state)[0]  = (*state)[0] + a;
		(*state)[1]  = (*state)[1] + b;
		(*state)[2]  = (*state)[2] + c;
		(*state)[3]  = (*state)[3] + d;

		memset(&data.get()[0], 0, 16 * sizeof(uint32_t));
	} // end function TransformBlock


private:
	shared_ptr<uint32_t> data;

}; // end class MD4


#endif // !HLPMD4_H