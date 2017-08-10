#ifndef HLPJENKINS3_H
#define HLPJENKINS3_H

#include "../Base/HlpMultipleTransformNonBlock.h"


class Jenkins3 : public MultipleTransformNonBlock, public IIHash32, public IITransformBlock
{
public:
	Jenkins3()
		: MultipleTransformNonBlock(4, 12)
	{
		name = __func__;
	} // end constructor

protected:
	virtual IHashResult ComputeAggregatedBytes(const HashLibByteArray &a_data)
	{
		register int32_t length, currentIndex, i1, i2, i3, i4;
		register uint32_t a, b, c;
		
		length = (int32_t)a_data.size();
		if (length == 0)
			return IHashResult(new HashResult(uint32_t(0)));
		
		a = 0xDEADBEEF + uint32_t(length);
		b = a;
		c = b;
		currentIndex = 0;
		while (length > 12)
		{
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			a = a + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			b = b + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			c = c + uint32_t(i1 | i2 | i3 | i4);

			a = a - c;
			a = a ^ Bits::RotateLeft32(c, 4);
			c = c + b;
			b = b - a;
			b = b ^ Bits::RotateLeft32(a, 6);
			a = a + c;
			c = c - b;
			c = c ^ Bits::RotateLeft32(b, 8);
			b = b + a;
			a = a - c;
			a = a ^ Bits::RotateLeft32(c, 16);
			c = c + b;
			b = b - a;
			b = b ^ Bits::RotateLeft32(a, 19);
			a = a + c;
			c = c - b;
			c = c ^ Bits::RotateLeft32(b, 4);
			b = b + a;

			length -= 12;
		} // end while

		switch (length)
		{
		case 12:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			a = a + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			b = b + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;

			c = c + uint32_t(i1 | i2 | i3 | i4);
			break;

		case 11:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			a = a + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			b = b + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;

			c = c + uint32_t(i1 | i2 | i3);
			break;

		case 10:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			a = a + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			b = b + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;

			c = c + uint32_t(i1 | i2);
			break;

		case 9:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			a = a + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			b = b + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];

			c = c + uint32_t(i1);
			break;

		case 8:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			a = a + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;

			b = b + uint32_t(i1 | i2 | i3 | i4);
			break;

		case 7:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			a = a + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;

			b = b + uint32_t(i1 | i2 | i3);
			break;

		case 6:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			a = a + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;

			b = b + uint32_t(i1 | i2);
			break;

		case 5:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;
			currentIndex++;

			a = a + uint32_t(i1 | i2 | i3 | i4);

			i1 = a_data[currentIndex];

			b = b + uint32_t(i1);
			break;

		case 4:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;
			currentIndex++;
			i4 = a_data[currentIndex] << 24;

			a = a + uint32_t(i1 | i2 | i3 | i4);
			break;

		case 3:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;
			currentIndex++;
			i3 = a_data[currentIndex] << 16;

			a = a + uint32_t(i1 | i2 | i3);
			break;

		case 2:
			i1 = a_data[currentIndex];
			currentIndex++;
			i2 = a_data[currentIndex] << 8;

			a = a + uint32_t(i1 | i2);
			break;

		case 1:
			i1 = a_data[currentIndex];

			a = a + uint32_t(i1);
		} // end switch

		c = c ^ b;
		c = c - Bits::RotateLeft32(b, 14);
		a = a ^ c;
		a = a - Bits::RotateLeft32(c, 11);
		b = b ^ a;
		b = b - Bits::RotateLeft32(a, 25);
		c = c ^ b;
		c = c - Bits::RotateLeft32(b, 16);
		a = a ^ c;
		a = a - Bits::RotateLeft32(c, 4);
		b = b ^ a;
		b = b - Bits::RotateLeft32(a, 14);
		c = c ^ b;
		c = c - Bits::RotateLeft32(b, 24);

		return IHashResult(new HashResult(c));
	} // end function ComputeAggregatedBytes

}; // end class Jenkins3


#endif // !HLPJENKINS3_H
