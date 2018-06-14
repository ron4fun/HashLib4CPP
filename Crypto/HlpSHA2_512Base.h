#ifndef HLPSHA2_512BASE_H
#define HLPSHA2_512BASE_H

#include "../Base/HlpHashCryptoNotBuildIn.h"


class SHA2_512Base : public BlockHash, public IICryptoNotBuildIn, public IITransformBlock
{
protected:
	SHA2_512Base(const int32_t a_hash_size)
		: BlockHash(a_hash_size, 128)
	{
		state = shared_ptr<uint64_t>(new uint64_t[8], default_delete<uint64_t[]>());
		data = shared_ptr<uint64_t>(new uint64_t[80], default_delete<uint64_t[]>());
	} // end constructor

	~SHA2_512Base()
	{} // end destructor

	virtual void Finish()
	{
		register uint64_t lowBits, hiBits;
		register int32_t padindex;
	    
		lowBits = processed_bytes << 3;
		hiBits = processed_bytes >> 61;

		if (buffer->GetPos() < 112)
			padindex = 111 - buffer->GetPos();
		else
			padindex = 239 - buffer->GetPos();

		padindex++;
		HashLibByteArray pad = HashLibByteArray(padindex + 16);

		pad[0] = 0x80;

		hiBits = Converters::be2me_64(hiBits);

		Converters::ReadUInt64AsBytesLE(hiBits, pad, padindex);

		padindex = padindex + 8;

		lowBits = Converters::be2me_64(lowBits);

		Converters::ReadUInt64AsBytesLE(lowBits, pad, padindex);

		padindex = padindex + 8;

		TransformBytes(pad, 0, padindex);

	} // end function Finish

	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint64_t T0, T1, a, b, c, d, e, f, g, h;
		
		Converters::be64_copy(a_data, a_index, data.get(), 0, 128);

		// Step 1

		T0 = data.get()[16 - 15];
		T1 = data.get()[16 - 2];
		data.get()[16]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[16 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[0];
		T0 = data.get()[17 - 15];
		T1 = data.get()[17 - 2];
		data.get()[17]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[17 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[17 - 16];
		T0 = data.get()[18 - 15];
		T1 = data.get()[18 - 2];
		data.get()[18]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[18 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[18 - 16];
		T0 = data.get()[19 - 15];
		T1 = data.get()[19 - 2];
		data.get()[19]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[19 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[19 - 16];
		T0 = data.get()[20 - 15];
		T1 = data.get()[20 - 2];
		data.get()[20]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[20 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[20 - 16];
		T0 = data.get()[21 - 15];
		T1 = data.get()[21 - 2];
		data.get()[21]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[21 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[21 - 16];
		T0 = data.get()[22 - 15];
		T1 = data.get()[22 - 2];
		data.get()[22]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[22 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[22 - 16];
		T0 = data.get()[23 - 15];
		T1 = data.get()[23 - 2];
		data.get()[23]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[23 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[23 - 16];
		T0 = data.get()[24 - 15];
		T1 = data.get()[24 - 2];
		data.get()[24]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[24 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[24 - 16];
		T0 = data.get()[25 - 15];
		T1 = data.get()[25 - 2];
		data.get()[25]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[25 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[25 - 16];
		T0 = data.get()[26 - 15];
		T1 = data.get()[26 - 2];
		data.get()[26]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[26 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[26 - 16];
		T0 = data.get()[27 - 15];
		T1 = data.get()[27 - 2];
		data.get()[27]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[27 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[27 - 16];
		T0 = data.get()[28 - 15];
		T1 = data.get()[28 - 2];
		data.get()[28]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[28 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[28 - 16];
		T0 = data.get()[29 - 15];
		T1 = data.get()[29 - 2];
		data.get()[29]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[29 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[29 - 16];
		T0 = data.get()[30 - 15];
		T1 = data.get()[30 - 2];
		data.get()[30]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[30 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[30 - 16];
		T0 = data.get()[31 - 15];
		T1 = data.get()[31 - 2];
		data.get()[31]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[31 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[31 - 16];
		T0 = data.get()[32 - 15];
		T1 = data.get()[32 - 2];
		data.get()[32]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[32 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[32 - 16];
		T0 = data.get()[33 - 15];
		T1 = data.get()[33 - 2];
		data.get()[33]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[33 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[33 - 16];
		T0 = data.get()[34 - 15];
		T1 = data.get()[34 - 2];
		data.get()[34]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[34 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[34 - 16];
		T0 = data.get()[35 - 15];
		T1 = data.get()[35 - 2];
		data.get()[35]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[35 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[35 - 16];
		T0 = data.get()[36 - 15];
		T1 = data.get()[36 - 2];
		data.get()[36]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[36 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[36 - 16];
		T0 = data.get()[37 - 15];
		T1 = data.get()[37 - 2];
		data.get()[37]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[37 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[37 - 16];
		T0 = data.get()[38 - 15];
		T1 = data.get()[38 - 2];
		data.get()[38]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[38 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[38 - 16];
		T0 = data.get()[39 - 15];
		T1 = data.get()[39 - 2];
		data.get()[39]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[39 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[39 - 16];
		T0 = data.get()[40 - 15];
		T1 = data.get()[40 - 2];
		data.get()[40]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[40 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[40 - 16];
		T0 = data.get()[41 - 15];
		T1 = data.get()[41 - 2];
		data.get()[41]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[41 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[41 - 16];
		T0 = data.get()[42 - 15];
		T1 = data.get()[42 - 2];
		data.get()[42]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[42 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[42 - 16];
		T0 = data.get()[43 - 15];
		T1 = data.get()[43 - 2];
		data.get()[43]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[43 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[43 - 16];
		T0 = data.get()[44 - 15];
		T1 = data.get()[44 - 2];
		data.get()[44]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[44 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[44 - 16];
		T0 = data.get()[45 - 15];
		T1 = data.get()[45 - 2];
		data.get()[45]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[45 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[45 - 16];
		T0 = data.get()[46 - 15];
		T1 = data.get()[46 - 2];
		data.get()[46]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[46 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[46 - 16];
		T0 = data.get()[47 - 15];
		T1 = data.get()[47 - 2];
		data.get()[47]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[47 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[47 - 16];
		T0 = data.get()[48 - 15];
		T1 = data.get()[48 - 2];
		data.get()[48]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[48 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[48 - 16];
		T0 = data.get()[49 - 15];
		T1 = data.get()[49 - 2];
		data.get()[49]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[49 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[49 - 16];
		T0 = data.get()[50 - 15];
		T1 = data.get()[50 - 2];
		data.get()[50]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[50 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[50 - 16];
		T0 = data.get()[51 - 15];
		T1 = data.get()[51 - 2];
		data.get()[51]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[51 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[51 - 16];
		T0 = data.get()[52 - 15];
		T1 = data.get()[52 - 2];
		data.get()[52]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[52 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[52 - 16];
		T0 = data.get()[53 - 15];
		T1 = data.get()[53 - 2];
		data.get()[53]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[53 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[53 - 16];
		T0 = data.get()[54 - 15];
		T1 = data.get()[54 - 2];
		data.get()[54]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[54 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[54 - 16];
		T0 = data.get()[55 - 15];
		T1 = data.get()[55 - 2];
		data.get()[55]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[55 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[55 - 16];
		T0 = data.get()[56 - 15];
		T1 = data.get()[56 - 2];
		data.get()[56]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[56 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[56 - 16];
		T0 = data.get()[57 - 15];
		T1 = data.get()[57 - 2];
		data.get()[57]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[57 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[57 - 16];
		T0 = data.get()[58 - 15];
		T1 = data.get()[58 - 2];
		data.get()[58]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[58 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[58 - 16];
		T0 = data.get()[59 - 15];
		T1 = data.get()[59 - 2];
		data.get()[59]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[59 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[59 - 16];
		T0 = data.get()[60 - 15];
		T1 = data.get()[60 - 2];
		data.get()[60]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[60 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[60 - 16];
		T0 = data.get()[61 - 15];
		T1 = data.get()[61 - 2];
		data.get()[61]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[61 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[61 - 16];
		T0 = data.get()[62 - 15];
		T1 = data.get()[62 - 2];
		data.get()[62]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[62 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[62 - 16];
		T0 = data.get()[63 - 15];
		T1 = data.get()[63 - 2];
		data.get()[63]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[63 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[63 - 16];
		T0 = data.get()[64 - 15];
		T1 = data.get()[64 - 2];
		data.get()[64]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[64 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[64 - 16];
		T0 = data.get()[65 - 15];
		T1 = data.get()[65 - 2];
		data.get()[65]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[65 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[65 - 16];
		T0 = data.get()[66 - 15];
		T1 = data.get()[66 - 2];
		data.get()[66]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[66 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[66 - 16];
		T0 = data.get()[67 - 15];
		T1 = data.get()[67 - 2];
		data.get()[67]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[67 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[67 - 16];
		T0 = data.get()[68 - 15];
		T1 = data.get()[68 - 2];
		data.get()[68]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[68 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[68 - 16];
		T0 = data.get()[69 - 15];
		T1 = data.get()[69 - 2];
		data.get()[69]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[69 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[69 - 16];
		T0 = data.get()[70 - 15];
		T1 = data.get()[70 - 2];
		data.get()[70]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[70 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[70 - 16];
		T0 = data.get()[71 - 15];
		T1 = data.get()[71 - 2];
		data.get()[71]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[71 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[71 - 16];
		T0 = data.get()[72 - 15];
		T1 = data.get()[72 - 2];
		data.get()[72]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[72 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[72 - 16];
		T0 = data.get()[73 - 15];
		T1 = data.get()[73 - 2];
		data.get()[73]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[73 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[73 - 16];
		T0 = data.get()[74 - 15];
		T1 = data.get()[74 - 2];
		data.get()[74]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[74 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[74 - 16];
		T0 = data.get()[75 - 15];
		T1 = data.get()[75 - 2];
		data.get()[75]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[75 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[75 - 16];
		T0 = data.get()[76 - 15];
		T1 = data.get()[76 - 2];
		data.get()[76]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[76 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[76 - 16];
		T0 = data.get()[77 - 15];
		T1 = data.get()[77 - 2];
		data.get()[77]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[77 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[77 - 16];
		T0 = data.get()[78 - 15];
		T1 = data.get()[78 - 2];
		data.get()[78]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[78 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[78 - 16];
		T0 = data.get()[79 - 15];
		T1 = data.get()[79 - 2];
		data.get()[79]  = ((Bits::RotateLeft64(T1, 45)) ^ (Bits::RotateLeft64(T1, 3))
			^ (T1 >> 6)) + data.get()[79 - 7] +
			((Bits::RotateLeft64(T0, 63)) ^ (Bits::RotateLeft64(T0, 56))
				^ (T0 >> 7)) + data.get()[79 - 16];

		a = state.get()[0];
		b = state.get()[1];
		c = state.get()[2];
		d = state.get()[3];
		e = state.get()[4];
		f = state.get()[5];
		g = state.get()[6];
		h = state.get()[7];

		// Step 2

		// R0
		h = h + (0x428A2F98D728AE22 + data.get()[0] + ((Bits::RotateLeft64(e, 50))
			^ (Bits::RotateLeft64(e, 46)) ^ (Bits::RotateLeft64(e, 23))) +
			((e & f) ^ (~e & g)));

		d = d + h;
		h = h + (((Bits::RotateLeft64(a, 36)) ^ (Bits::RotateLeft64(a, 30))
			^ (Bits::RotateLeft64(a, 25))) + ((a & b) ^ (a & c) ^ (b & c)));

		g = g + (0x7137449123EF65CD + data.get()[1] + ((Bits::RotateLeft64(d, 50))
			^ (Bits::RotateLeft64(d, 46)) ^ (Bits::RotateLeft64(d, 23))) +
			((d & e) ^ (~d & f)));

		c = c + g;
		g = g + (((Bits::RotateLeft64(h, 36)) ^ (Bits::RotateLeft64(h, 30))
			^ (Bits::RotateLeft64(h, 25))) + ((h & a) ^ (h & b) ^ (a & b)));

		f = f + (0xB5C0FBCFEC4D3B2F + data.get()[2] + ((Bits::RotateLeft64(c, 50))
			^ (Bits::RotateLeft64(c, 46)) ^ (Bits::RotateLeft64(c, 23))) +
			((c & d) ^ (~c & e)));

		b = b + f;
		f = f + (((Bits::RotateLeft64(g, 36)) ^ (Bits::RotateLeft64(g, 30))
			^ (Bits::RotateLeft64(g, 25))) + ((g & h) ^ (g & a) ^ (h & a)));

		e = e + (0xE9B5DBA58189DBBC + data.get()[3] + ((Bits::RotateLeft64(b, 50))
			^ (Bits::RotateLeft64(b, 46)) ^ (Bits::RotateLeft64(b, 23))) +
			((b & c) ^ (~b & d)));

		a = a + e;
		e = e + (((Bits::RotateLeft64(f, 36)) ^ (Bits::RotateLeft64(f, 30))
			^ (Bits::RotateLeft64(f, 25))) + ((f & g) ^ (f & h) ^ (g & h)));

		d = d + (0x3956C25BF348B538 + data.get()[4] + ((Bits::RotateLeft64(a, 50))
			^ (Bits::RotateLeft64(a, 46)) ^ (Bits::RotateLeft64(a, 23))) +
			((a & b) ^ (~a & c)));

		h = h + d;
		d = d + (((Bits::RotateLeft64(e, 36)) ^ (Bits::RotateLeft64(e, 30))
			^ (Bits::RotateLeft64(e, 25))) + ((e & f) ^ (e & g) ^ (f & g)));

		c = c + (0x59F111F1B605D019 + data.get()[5] + ((Bits::RotateLeft64(h, 50))
			^ (Bits::RotateLeft64(h, 46)) ^ (Bits::RotateLeft64(h, 23))) +
			((h & a) ^ (~h & b)));

		g = g + c;
		c = c + (((Bits::RotateLeft64(d, 36)) ^ (Bits::RotateLeft64(d, 30))
			^ (Bits::RotateLeft64(d, 25))) + ((d & e) ^ (d & f) ^ (e & f)));

		b = b + (0x923F82A4AF194F9B + data.get()[6] + ((Bits::RotateLeft64(g, 50))
			^ (Bits::RotateLeft64(g, 46)) ^ (Bits::RotateLeft64(g, 23))) +
			((g & h) ^ (~g & a)));

		f = f + b;
		b = b + (((Bits::RotateLeft64(c, 36)) ^ (Bits::RotateLeft64(c, 30))
			^ (Bits::RotateLeft64(c, 25))) + ((c & d) ^ (c & e) ^ (d & e)));

		a = a + (0xAB1C5ED5DA6D8118 + data.get()[7] + ((Bits::RotateLeft64(f, 50))
			^ (Bits::RotateLeft64(f, 46)) ^ (Bits::RotateLeft64(f, 23))) +
			((f & g) ^ (~f & h)));

		e = e + a;
		a = a + (((Bits::RotateLeft64(b, 36)) ^ (Bits::RotateLeft64(b, 30))
			^ (Bits::RotateLeft64(b, 25))) + ((b & c) ^ (b & d) ^ (c & d)));

		   // R1
		h = h + (0xD807AA98A3030242 + data.get()[8] + ((Bits::RotateLeft64(e, 50))
			^ (Bits::RotateLeft64(e, 46)) ^ (Bits::RotateLeft64(e, 23))) +
			((e & f) ^ (~e & g)));

		d = d + h;
		h = h + (((Bits::RotateLeft64(a, 36)) ^ (Bits::RotateLeft64(a, 30))
			^ (Bits::RotateLeft64(a, 25))) + ((a & b) ^ (a & c) ^ (b & c)));

		g = g + (0x12835B0145706FBE + data.get()[9] + ((Bits::RotateLeft64(d, 50))
			^ (Bits::RotateLeft64(d, 46)) ^ (Bits::RotateLeft64(d, 23))) +
			((d & e) ^ (~d & f)));

		c = c + g;
		g = g + (((Bits::RotateLeft64(h, 36)) ^ (Bits::RotateLeft64(h, 30))
			^ (Bits::RotateLeft64(h, 25))) + ((h & a) ^ (h & b) ^ (a & b)));

		f = f + (0x243185BE4EE4B28C + data.get()[10] + ((Bits::RotateLeft64(c, 50))
			^ (Bits::RotateLeft64(c, 46)) ^ (Bits::RotateLeft64(c, 23))) +
			((c & d) ^ (~c & e)));

		b = b + f;
		f = f + (((Bits::RotateLeft64(g, 36)) ^ (Bits::RotateLeft64(g, 30))
			^ (Bits::RotateLeft64(g, 25))) + ((g & h) ^ (g & a) ^ (h & a)));

		e = e + (0x550C7DC3D5FFB4E2 + data.get()[11] + ((Bits::RotateLeft64(b, 50))
			^ (Bits::RotateLeft64(b, 46)) ^ (Bits::RotateLeft64(b, 23))) +
			((b & c) ^ (~b & d)));

		a = a + e;
		e = e + (((Bits::RotateLeft64(f, 36)) ^ (Bits::RotateLeft64(f, 30))
			^ (Bits::RotateLeft64(f, 25))) + ((f & g) ^ (f & h) ^ (g & h)));

		d = d + (0x72BE5D74F27B896F + data.get()[12] + ((Bits::RotateLeft64(a, 50))
			^ (Bits::RotateLeft64(a, 46)) ^ (Bits::RotateLeft64(a, 23))) +
			((a & b) ^ (~a & c)));

		h = h + d;
		d = d + (((Bits::RotateLeft64(e, 36)) ^ (Bits::RotateLeft64(e, 30))
			^ (Bits::RotateLeft64(e, 25))) + ((e & f) ^ (e & g) ^ (f & g)));

		c = c + (0x80DEB1FE3B1696B1 + data.get()[13] + ((Bits::RotateLeft64(h, 50))
			^ (Bits::RotateLeft64(h, 46)) ^ (Bits::RotateLeft64(h, 23))) +
			((h & a) ^ (~h & b)));

		g = g + c;
		c = c + (((Bits::RotateLeft64(d, 36)) ^ (Bits::RotateLeft64(d, 30))
			^ (Bits::RotateLeft64(d, 25))) + ((d & e) ^ (d & f) ^ (e & f)));

		b = b + (0x9BDC06A725C71235 + data.get()[14] + ((Bits::RotateLeft64(g, 50))
			^ (Bits::RotateLeft64(g, 46)) ^ (Bits::RotateLeft64(g, 23))) +
			((g & h) ^ (~g & a)));

		f = f + b;
		b = b + (((Bits::RotateLeft64(c, 36)) ^ (Bits::RotateLeft64(c, 30))
			^ (Bits::RotateLeft64(c, 25))) + ((c & d) ^ (c & e) ^ (d & e)));

		a = a + (0xC19BF174CF692694 + data.get()[15] + ((Bits::RotateLeft64(f, 50))
			^ (Bits::RotateLeft64(f, 46)) ^ (Bits::RotateLeft64(f, 23))) +
			((f & g) ^ (~f & h)));

		e = e + a;
		a = a + (((Bits::RotateLeft64(b, 36)) ^ (Bits::RotateLeft64(b, 30))
			^ (Bits::RotateLeft64(b, 25))) + ((b & c) ^ (b & d) ^ (c & d)));

		   // R2

		h = h + (0xE49B69C19EF14AD2 + data.get()[16] + ((Bits::RotateLeft64(e, 50))
			^ (Bits::RotateLeft64(e, 46)) ^ (Bits::RotateLeft64(e, 23))) +
			((e & f) ^ (~e & g)));

		d = d + h;
		h = h + (((Bits::RotateLeft64(a, 36)) ^ (Bits::RotateLeft64(a, 30))
			^ (Bits::RotateLeft64(a, 25))) + ((a & b) ^ (a & c) ^ (b & c)));

		g = g + (0xEFBE4786384F25E3 + data.get()[17] + ((Bits::RotateLeft64(d, 50))
			^ (Bits::RotateLeft64(d, 46)) ^ (Bits::RotateLeft64(d, 23))) +
			((d & e) ^ (~d & f)));

		c = c + g;
		g = g + (((Bits::RotateLeft64(h, 36)) ^ (Bits::RotateLeft64(h, 30))
			^ (Bits::RotateLeft64(h, 25))) + ((h & a) ^ (h & b) ^ (a & b)));

		f = f + (0x0FC19DC68B8CD5B5 + data.get()[18] + ((Bits::RotateLeft64(c, 50))
			^ (Bits::RotateLeft64(c, 46)) ^ (Bits::RotateLeft64(c, 23))) +
			((c & d) ^ (~c & e)));

		b = b + f;
		f = f + (((Bits::RotateLeft64(g, 36)) ^ (Bits::RotateLeft64(g, 30))
			^ (Bits::RotateLeft64(g, 25))) + ((g & h) ^ (g & a) ^ (h & a)));

		e = e + (0x240CA1CC77AC9C65 + data.get()[19] + ((Bits::RotateLeft64(b, 50))
			^ (Bits::RotateLeft64(b, 46)) ^ (Bits::RotateLeft64(b, 23))) +
			((b & c) ^ (~b & d)));

		a = a + e;
		e = e + (((Bits::RotateLeft64(f, 36)) ^ (Bits::RotateLeft64(f, 30))
			^ (Bits::RotateLeft64(f, 25))) + ((f & g) ^ (f & h) ^ (g & h)));

		d = d + (0x2DE92C6F592B0275 + data.get()[20] + ((Bits::RotateLeft64(a, 50))
			^ (Bits::RotateLeft64(a, 46)) ^ (Bits::RotateLeft64(a, 23))) +
			((a & b) ^ (~a & c)));

		h = h + d;
		d = d + (((Bits::RotateLeft64(e, 36)) ^ (Bits::RotateLeft64(e, 30))
			^ (Bits::RotateLeft64(e, 25))) + ((e & f) ^ (e & g) ^ (f & g)));

		c = c + (0x4A7484AA6EA6E483 + data.get()[21] + ((Bits::RotateLeft64(h, 50))
			^ (Bits::RotateLeft64(h, 46)) ^ (Bits::RotateLeft64(h, 23))) +
			((h & a) ^ (~h & b)));

		g = g + c;
		c = c + (((Bits::RotateLeft64(d, 36)) ^ (Bits::RotateLeft64(d, 30))
			^ (Bits::RotateLeft64(d, 25))) + ((d & e) ^ (d & f) ^ (e & f)));

		b = b + (0x5CB0A9DCBD41FBD4 + data.get()[22] + ((Bits::RotateLeft64(g, 50))
			^ (Bits::RotateLeft64(g, 46)) ^ (Bits::RotateLeft64(g, 23))) +
			((g & h) ^ (~g & a)));

		f = f + b;
		b = b + (((Bits::RotateLeft64(c, 36)) ^ (Bits::RotateLeft64(c, 30))
			^ (Bits::RotateLeft64(c, 25))) + ((c & d) ^ (c & e) ^ (d & e)));

		a = a + (0x76F988DA831153B5 + data.get()[23] + ((Bits::RotateLeft64(f, 50))
			^ (Bits::RotateLeft64(f, 46)) ^ (Bits::RotateLeft64(f, 23))) +
			((f & g) ^ (~f & h)));

		e = e + a;
		a = a + (((Bits::RotateLeft64(b, 36)) ^ (Bits::RotateLeft64(b, 30))
			^ (Bits::RotateLeft64(b, 25))) + ((b & c) ^ (b & d) ^ (c & d)));

		   // R3

		h = h + (0x983E5152EE66DFAB + data.get()[24] + ((Bits::RotateLeft64(e, 50))
			^ (Bits::RotateLeft64(e, 46)) ^ (Bits::RotateLeft64(e, 23))) +
			((e & f) ^ (~e & g)));

		d = d + h;
		h = h + (((Bits::RotateLeft64(a, 36)) ^ (Bits::RotateLeft64(a, 30))
			^ (Bits::RotateLeft64(a, 25))) + ((a & b) ^ (a & c) ^ (b & c)));

		g = g + (0xA831C66D2DB43210 + data.get()[25] + ((Bits::RotateLeft64(d, 50))
			^ (Bits::RotateLeft64(d, 46)) ^ (Bits::RotateLeft64(d, 23))) +
			((d & e) ^ (~d & f)));

		c = c + g;
		g = g + (((Bits::RotateLeft64(h, 36)) ^ (Bits::RotateLeft64(h, 30))
			^ (Bits::RotateLeft64(h, 25))) + ((h & a) ^ (h & b) ^ (a & b)));

		f = f + (0xB00327C898FB213F + data.get()[26] + ((Bits::RotateLeft64(c, 50))
			^ (Bits::RotateLeft64(c, 46)) ^ (Bits::RotateLeft64(c, 23))) +
			((c & d) ^ (~c & e)));

		b = b + f;
		f = f + (((Bits::RotateLeft64(g, 36)) ^ (Bits::RotateLeft64(g, 30))
			^ (Bits::RotateLeft64(g, 25))) + ((g & h) ^ (g & a) ^ (h & a)));

		e = e + (0xBF597FC7BEEF0EE4 + data.get()[27] + ((Bits::RotateLeft64(b, 50))
			^ (Bits::RotateLeft64(b, 46)) ^ (Bits::RotateLeft64(b, 23))) +
			((b & c) ^ (~b & d)));

		a = a + e;
		e = e + (((Bits::RotateLeft64(f, 36)) ^ (Bits::RotateLeft64(f, 30))
			^ (Bits::RotateLeft64(f, 25))) + ((f & g) ^ (f & h) ^ (g & h)));

		d = d + (0xC6E00BF33DA88FC2 + data.get()[28] + ((Bits::RotateLeft64(a, 50))
			^ (Bits::RotateLeft64(a, 46)) ^ (Bits::RotateLeft64(a, 23))) +
			((a & b) ^ (~a & c)));

		h = h + d;
		d = d + (((Bits::RotateLeft64(e, 36)) ^ (Bits::RotateLeft64(e, 30))
			^ (Bits::RotateLeft64(e, 25))) + ((e & f) ^ (e & g) ^ (f & g)));

		c = c + (0xD5A79147930AA725 + data.get()[29] + ((Bits::RotateLeft64(h, 50))
			^ (Bits::RotateLeft64(h, 46)) ^ (Bits::RotateLeft64(h, 23))) +
			((h & a) ^ (~h & b)));

		g = g + c;
		c = c + (((Bits::RotateLeft64(d, 36)) ^ (Bits::RotateLeft64(d, 30))
			^ (Bits::RotateLeft64(d, 25))) + ((d & e) ^ (d & f) ^ (e & f)));

		b = b + (0x06CA6351E003826F + data.get()[30] + ((Bits::RotateLeft64(g, 50))
			^ (Bits::RotateLeft64(g, 46)) ^ (Bits::RotateLeft64(g, 23))) +
			((g & h) ^ (~g & a)));

		f = f + b;
		b = b + (((Bits::RotateLeft64(c, 36)) ^ (Bits::RotateLeft64(c, 30))
			^ (Bits::RotateLeft64(c, 25))) + ((c & d) ^ (c & e) ^ (d & e)));

		a = a + (0x142929670A0E6E70 + data.get()[31] + ((Bits::RotateLeft64(f, 50))
			^ (Bits::RotateLeft64(f, 46)) ^ (Bits::RotateLeft64(f, 23))) +
			((f & g) ^ (~f & h)));

		e = e + a;
		a = a + (((Bits::RotateLeft64(b, 36)) ^ (Bits::RotateLeft64(b, 30))
			^ (Bits::RotateLeft64(b, 25))) + ((b & c) ^ (b & d) ^ (c & d)));

		   // R4

		h = h + (0x27B70A8546D22FFC + data.get()[32] + ((Bits::RotateLeft64(e, 50))
			^ (Bits::RotateLeft64(e, 46)) ^ (Bits::RotateLeft64(e, 23))) +
			((e & f) ^ (~e & g)));

		d = d + h;
		h = h + (((Bits::RotateLeft64(a, 36)) ^ (Bits::RotateLeft64(a, 30))
			^ (Bits::RotateLeft64(a, 25))) + ((a & b) ^ (a & c) ^ (b & c)));

		g = g + (0x2E1B21385C26C926 + data.get()[33] + ((Bits::RotateLeft64(d, 50))
			^ (Bits::RotateLeft64(d, 46)) ^ (Bits::RotateLeft64(d, 23))) +
			((d & e) ^ (~d & f)));

		c = c + g;
		g = g + (((Bits::RotateLeft64(h, 36)) ^ (Bits::RotateLeft64(h, 30))
			^ (Bits::RotateLeft64(h, 25))) + ((h & a) ^ (h & b) ^ (a & b)));

		f = f + (0x4D2C6DFC5AC42AED + data.get()[34] + ((Bits::RotateLeft64(c, 50))
			^ (Bits::RotateLeft64(c, 46)) ^ (Bits::RotateLeft64(c, 23))) +
			((c & d) ^ (~c & e)));

		b = b + f;
		f = f + (((Bits::RotateLeft64(g, 36)) ^ (Bits::RotateLeft64(g, 30))
			^ (Bits::RotateLeft64(g, 25))) + ((g & h) ^ (g & a) ^ (h & a)));

		e = e + (0x53380D139D95B3DF + data.get()[35] + ((Bits::RotateLeft64(b, 50))
			^ (Bits::RotateLeft64(b, 46)) ^ (Bits::RotateLeft64(b, 23))) +
			((b & c) ^ (~b & d)));

		a = a + e;
		e = e + (((Bits::RotateLeft64(f, 36)) ^ (Bits::RotateLeft64(f, 30))
			^ (Bits::RotateLeft64(f, 25))) + ((f & g) ^ (f & h) ^ (g & h)));

		d = d + (0x650A73548BAF63DE + data.get()[36] + ((Bits::RotateLeft64(a, 50))
			^ (Bits::RotateLeft64(a, 46)) ^ (Bits::RotateLeft64(a, 23))) +
			((a & b) ^ (~a & c)));

		h = h + d;
		d = d + (((Bits::RotateLeft64(e, 36)) ^ (Bits::RotateLeft64(e, 30))
			^ (Bits::RotateLeft64(e, 25))) + ((e & f) ^ (e & g) ^ (f & g)));

		c = c + (0x766A0ABB3C77B2A8 + data.get()[37] + ((Bits::RotateLeft64(h, 50))
			^ (Bits::RotateLeft64(h, 46)) ^ (Bits::RotateLeft64(h, 23))) +
			((h & a) ^ (~h & b)));

		g = g + c;
		c = c + (((Bits::RotateLeft64(d, 36)) ^ (Bits::RotateLeft64(d, 30))
			^ (Bits::RotateLeft64(d, 25))) + ((d & e) ^ (d & f) ^ (e & f)));

		b = b + (0x81C2C92E47EDAEE6 + data.get()[38] + ((Bits::RotateLeft64(g, 50))
			^ (Bits::RotateLeft64(g, 46)) ^ (Bits::RotateLeft64(g, 23))) +
			((g & h) ^ (~g & a)));

		f = f + b;
		b = b + (((Bits::RotateLeft64(c, 36)) ^ (Bits::RotateLeft64(c, 30))
			^ (Bits::RotateLeft64(c, 25))) + ((c & d) ^ (c & e) ^ (d & e)));

		a = a + (0x92722C851482353B + data.get()[39] + ((Bits::RotateLeft64(f, 50))
			^ (Bits::RotateLeft64(f, 46)) ^ (Bits::RotateLeft64(f, 23))) +
			((f & g) ^ (~f & h)));

		e = e + a;
		a = a + (((Bits::RotateLeft64(b, 36)) ^ (Bits::RotateLeft64(b, 30))
			^ (Bits::RotateLeft64(b, 25))) + ((b & c) ^ (b & d) ^ (c & d)));

		   // R5

		h = h + (0xA2BFE8A14CF10364 + data.get()[40] + ((Bits::RotateLeft64(e, 50))
			^ (Bits::RotateLeft64(e, 46)) ^ (Bits::RotateLeft64(e, 23))) +
			((e & f) ^ (~e & g)));

		d = d + h;
		h = h + (((Bits::RotateLeft64(a, 36)) ^ (Bits::RotateLeft64(a, 30))
			^ (Bits::RotateLeft64(a, 25))) + ((a & b) ^ (a & c) ^ (b & c)));

		g = g + (0xA81A664BBC423001 + data.get()[41] + ((Bits::RotateLeft64(d, 50))
			^ (Bits::RotateLeft64(d, 46)) ^ (Bits::RotateLeft64(d, 23))) +
			((d & e) ^ (~d & f)));

		c = c + g;
		g = g + (((Bits::RotateLeft64(h, 36)) ^ (Bits::RotateLeft64(h, 30))
			^ (Bits::RotateLeft64(h, 25))) + ((h & a) ^ (h & b) ^ (a & b)));

		f = f + (0xC24B8B70D0F89791 + data.get()[42] + ((Bits::RotateLeft64(c, 50))
			^ (Bits::RotateLeft64(c, 46)) ^ (Bits::RotateLeft64(c, 23))) +
			((c & d) ^ (~c & e)));

		b = b + f;
		f = f + (((Bits::RotateLeft64(g, 36)) ^ (Bits::RotateLeft64(g, 30))
			^ (Bits::RotateLeft64(g, 25))) + ((g & h) ^ (g & a) ^ (h & a)));

		e = e + (0xC76C51A30654BE30 + data.get()[43] + ((Bits::RotateLeft64(b, 50))
			^ (Bits::RotateLeft64(b, 46)) ^ (Bits::RotateLeft64(b, 23))) +
			((b & c) ^ (~b & d)));

		a = a + e;
		e = e + (((Bits::RotateLeft64(f, 36)) ^ (Bits::RotateLeft64(f, 30))
			^ (Bits::RotateLeft64(f, 25))) + ((f & g) ^ (f & h) ^ (g & h)));

		d = d + (0xD192E819D6EF5218 + data.get()[44] + ((Bits::RotateLeft64(a, 50))
			^ (Bits::RotateLeft64(a, 46)) ^ (Bits::RotateLeft64(a, 23))) +
			((a & b) ^ (~a & c)));

		h = h + d;
		d = d + (((Bits::RotateLeft64(e, 36)) ^ (Bits::RotateLeft64(e, 30))
			^ (Bits::RotateLeft64(e, 25))) + ((e & f) ^ (e & g) ^ (f & g)));

		c = c + (0xD69906245565A910 + data.get()[45] + ((Bits::RotateLeft64(h, 50))
			^ (Bits::RotateLeft64(h, 46)) ^ (Bits::RotateLeft64(h, 23))) +
			((h & a) ^ (~h & b)));

		g = g + c;
		c = c + (((Bits::RotateLeft64(d, 36)) ^ (Bits::RotateLeft64(d, 30))
			^ (Bits::RotateLeft64(d, 25))) + ((d & e) ^ (d & f) ^ (e & f)));

		b = b + (0xF40E35855771202A + data.get()[46] + ((Bits::RotateLeft64(g, 50))
			^ (Bits::RotateLeft64(g, 46)) ^ (Bits::RotateLeft64(g, 23))) +
			((g & h) ^ (~g & a)));

		f = f + b;
		b = b + (((Bits::RotateLeft64(c, 36)) ^ (Bits::RotateLeft64(c, 30))
			^ (Bits::RotateLeft64(c, 25))) + ((c & d) ^ (c & e) ^ (d & e)));

		a = a + (0x106AA07032BBD1B8 + data.get()[47] + ((Bits::RotateLeft64(f, 50))
			^ (Bits::RotateLeft64(f, 46)) ^ (Bits::RotateLeft64(f, 23))) +
			((f & g) ^ (~f & h)));

		e = e + a;
		a = a + (((Bits::RotateLeft64(b, 36)) ^ (Bits::RotateLeft64(b, 30))
			^ (Bits::RotateLeft64(b, 25))) + ((b & c) ^ (b & d) ^ (c & d)));

		   // R6

		h = h + (0x19A4C116B8D2D0C8 + data.get()[48] + ((Bits::RotateLeft64(e, 50))
			^ (Bits::RotateLeft64(e, 46)) ^ (Bits::RotateLeft64(e, 23))) +
			((e & f) ^ (~e & g)));

		d = d + h;
		h = h + (((Bits::RotateLeft64(a, 36)) ^ (Bits::RotateLeft64(a, 30))
			^ (Bits::RotateLeft64(a, 25))) + ((a & b) ^ (a & c) ^ (b & c)));

		g = g + (0x1E376C085141AB53 + data.get()[49] + ((Bits::RotateLeft64(d, 50))
			^ (Bits::RotateLeft64(d, 46)) ^ (Bits::RotateLeft64(d, 23))) +
			((d & e) ^ (~d & f)));

		c = c + g;
		g = g + (((Bits::RotateLeft64(h, 36)) ^ (Bits::RotateLeft64(h, 30))
			^ (Bits::RotateLeft64(h, 25))) + ((h & a) ^ (h & b) ^ (a & b)));

		f = f + (0x2748774CDF8EEB99 + data.get()[50] + ((Bits::RotateLeft64(c, 50))
			^ (Bits::RotateLeft64(c, 46)) ^ (Bits::RotateLeft64(c, 23))) +
			((c & d) ^ (~c & e)));

		b = b + f;
		f = f + (((Bits::RotateLeft64(g, 36)) ^ (Bits::RotateLeft64(g, 30))
			^ (Bits::RotateLeft64(g, 25))) + ((g & h) ^ (g & a) ^ (h & a)));

		e = e + (0x34B0BCB5E19B48A8 + data.get()[51] + ((Bits::RotateLeft64(b, 50))
			^ (Bits::RotateLeft64(b, 46)) ^ (Bits::RotateLeft64(b, 23))) +
			((b & c) ^ (~b & d)));

		a = a + e;
		e = e + (((Bits::RotateLeft64(f, 36)) ^ (Bits::RotateLeft64(f, 30))
			^ (Bits::RotateLeft64(f, 25))) + ((f & g) ^ (f & h) ^ (g & h)));

		d = d + (0x391C0CB3C5C95A63 + data.get()[52] + ((Bits::RotateLeft64(a, 50))
			^ (Bits::RotateLeft64(a, 46)) ^ (Bits::RotateLeft64(a, 23))) +
			((a & b) ^ (~a & c)));

		h = h + d;
		d = d + (((Bits::RotateLeft64(e, 36)) ^ (Bits::RotateLeft64(e, 30))
			^ (Bits::RotateLeft64(e, 25))) + ((e & f) ^ (e & g) ^ (f & g)));

		c = c + (0x4ED8AA4AE3418ACB + data.get()[53] + ((Bits::RotateLeft64(h, 50))
			^ (Bits::RotateLeft64(h, 46)) ^ (Bits::RotateLeft64(h, 23))) +
			((h & a) ^ (~h & b)));

		g = g + c;
		c = c + (((Bits::RotateLeft64(d, 36)) ^ (Bits::RotateLeft64(d, 30))
			^ (Bits::RotateLeft64(d, 25))) + ((d & e) ^ (d & f) ^ (e & f)));

		b = b + (0x5B9CCA4F7763E373 + data.get()[54] + ((Bits::RotateLeft64(g, 50))
			^ (Bits::RotateLeft64(g, 46)) ^ (Bits::RotateLeft64(g, 23))) +
			((g & h) ^ (~g & a)));

		f = f + b;
		b = b + (((Bits::RotateLeft64(c, 36)) ^ (Bits::RotateLeft64(c, 30))
			^ (Bits::RotateLeft64(c, 25))) + ((c & d) ^ (c & e) ^ (d & e)));

		a = a + (0x682E6FF3D6B2B8A3 + data.get()[55] + ((Bits::RotateLeft64(f, 50))
			^ (Bits::RotateLeft64(f, 46)) ^ (Bits::RotateLeft64(f, 23))) +
			((f & g) ^ (~f & h)));

		e = e + a;
		a = a + (((Bits::RotateLeft64(b, 36)) ^ (Bits::RotateLeft64(b, 30))
			^ (Bits::RotateLeft64(b, 25))) + ((b & c) ^ (b & d) ^ (c & d)));

		   // R7

		h = h + (0x748F82EE5DEFB2FC + data.get()[56] + ((Bits::RotateLeft64(e, 50))
			^ (Bits::RotateLeft64(e, 46)) ^ (Bits::RotateLeft64(e, 23))) +
			((e & f) ^ (~e & g)));

		d = d + h;
		h = h + (((Bits::RotateLeft64(a, 36)) ^ (Bits::RotateLeft64(a, 30))
			^ (Bits::RotateLeft64(a, 25))) + ((a & b) ^ (a & c) ^ (b & c)));

		g = g + (0x78A5636F43172F60 + data.get()[57] + ((Bits::RotateLeft64(d, 50))
			^ (Bits::RotateLeft64(d, 46)) ^ (Bits::RotateLeft64(d, 23))) +
			((d & e) ^ (~d & f)));

		c = c + g;
		g = g + (((Bits::RotateLeft64(h, 36)) ^ (Bits::RotateLeft64(h, 30))
			^ (Bits::RotateLeft64(h, 25))) + ((h & a) ^ (h & b) ^ (a & b)));

		f = f + (0x84C87814A1F0AB72 + data.get()[58] + ((Bits::RotateLeft64(c, 50))
			^ (Bits::RotateLeft64(c, 46)) ^ (Bits::RotateLeft64(c, 23))) +
			((c & d) ^ (~c & e)));

		b = b + f;
		f = f + (((Bits::RotateLeft64(g, 36)) ^ (Bits::RotateLeft64(g, 30))
			^ (Bits::RotateLeft64(g, 25))) + ((g & h) ^ (g & a) ^ (h & a)));

		e = e + (0x8CC702081A6439EC + data.get()[59] + ((Bits::RotateLeft64(b, 50))
			^ (Bits::RotateLeft64(b, 46)) ^ (Bits::RotateLeft64(b, 23))) +
			((b & c) ^ (~b & d)));

		a = a + e;
		e = e + (((Bits::RotateLeft64(f, 36)) ^ (Bits::RotateLeft64(f, 30))
			^ (Bits::RotateLeft64(f, 25))) + ((f & g) ^ (f & h) ^ (g & h)));

		d = d + (0x90BEFFFA23631E28 + data.get()[60] + ((Bits::RotateLeft64(a, 50))
			^ (Bits::RotateLeft64(a, 46)) ^ (Bits::RotateLeft64(a, 23))) +
			((a & b) ^ (~a & c)));

		h = h + d;
		d = d + (((Bits::RotateLeft64(e, 36)) ^ (Bits::RotateLeft64(e, 30))
			^ (Bits::RotateLeft64(e, 25))) + ((e & f) ^ (e & g) ^ (f & g)));

		c = c + (0xA4506CEBDE82BDE9 + data.get()[61] + ((Bits::RotateLeft64(h, 50))
			^ (Bits::RotateLeft64(h, 46)) ^ (Bits::RotateLeft64(h, 23))) +
			((h & a) ^ (~h & b)));

		g = g + c;
		c = c + (((Bits::RotateLeft64(d, 36)) ^ (Bits::RotateLeft64(d, 30))
			^ (Bits::RotateLeft64(d, 25))) + ((d & e) ^ (d & f) ^ (e & f)));

		b = b + (0xBEF9A3F7B2C67915 + data.get()[62] + ((Bits::RotateLeft64(g, 50))
			^ (Bits::RotateLeft64(g, 46)) ^ (Bits::RotateLeft64(g, 23))) +
			((g & h) ^ (~g & a)));

		f = f + b;
		b = b + (((Bits::RotateLeft64(c, 36)) ^ (Bits::RotateLeft64(c, 30))
			^ (Bits::RotateLeft64(c, 25))) + ((c & d) ^ (c & e) ^ (d & e)));

		a = a + (0xC67178F2E372532B + data.get()[63] + ((Bits::RotateLeft64(f, 50))
			^ (Bits::RotateLeft64(f, 46)) ^ (Bits::RotateLeft64(f, 23))) +
			((f & g) ^ (~f & h)));

		e = e + a;
		a = a + (((Bits::RotateLeft64(b, 36)) ^ (Bits::RotateLeft64(b, 30))
			^ (Bits::RotateLeft64(b, 25))) + ((b & c) ^ (b & d) ^ (c & d)));

		   // R8

		h = h + (0xCA273ECEEA26619C + data.get()[64] + ((Bits::RotateLeft64(e, 50))
			^ (Bits::RotateLeft64(e, 46)) ^ (Bits::RotateLeft64(e, 23))) +
			((e & f) ^ (~e & g)));

		d = d + h;
		h = h + (((Bits::RotateLeft64(a, 36)) ^ (Bits::RotateLeft64(a, 30))
			^ (Bits::RotateLeft64(a, 25))) + ((a & b) ^ (a & c) ^ (b & c)));

		g = g + (0xD186B8C721C0C207 + data.get()[65] + ((Bits::RotateLeft64(d, 50))
			^ (Bits::RotateLeft64(d, 46)) ^ (Bits::RotateLeft64(d, 23))) +
			((d & e) ^ (~d & f)));

		c = c + g;
		g = g + (((Bits::RotateLeft64(h, 36)) ^ (Bits::RotateLeft64(h, 30))
			^ (Bits::RotateLeft64(h, 25))) + ((h & a) ^ (h & b) ^ (a & b)));

		f = f + (0xEADA7DD6CDE0EB1E + data.get()[66] + ((Bits::RotateLeft64(c, 50))
			^ (Bits::RotateLeft64(c, 46)) ^ (Bits::RotateLeft64(c, 23))) +
			((c & d) ^ (~c & e)));

		b = b + f;
		f = f + (((Bits::RotateLeft64(g, 36)) ^ (Bits::RotateLeft64(g, 30))
			^ (Bits::RotateLeft64(g, 25))) + ((g & h) ^ (g & a) ^ (h & a)));

		e = e + (0xF57D4F7FEE6ED178 + data.get()[67] + ((Bits::RotateLeft64(b, 50))
			^ (Bits::RotateLeft64(b, 46)) ^ (Bits::RotateLeft64(b, 23))) +
			((b & c) ^ (~b & d)));

		a = a + e;
		e = e + (((Bits::RotateLeft64(f, 36)) ^ (Bits::RotateLeft64(f, 30))
			^ (Bits::RotateLeft64(f, 25))) + ((f & g) ^ (f & h) ^ (g & h)));

		d = d + (0x06F067AA72176FBA + data.get()[68] + ((Bits::RotateLeft64(a, 50))
			^ (Bits::RotateLeft64(a, 46)) ^ (Bits::RotateLeft64(a, 23))) +
			((a & b) ^ (~a & c)));

		h = h + d;
		d = d + (((Bits::RotateLeft64(e, 36)) ^ (Bits::RotateLeft64(e, 30))
			^ (Bits::RotateLeft64(e, 25))) + ((e & f) ^ (e & g) ^ (f & g)));

		c = c + (0x0A637DC5A2C898A6 + data.get()[69] + ((Bits::RotateLeft64(h, 50))
			^ (Bits::RotateLeft64(h, 46)) ^ (Bits::RotateLeft64(h, 23))) +
			((h & a) ^ (~h & b)));

		g = g + c;
		c = c + (((Bits::RotateLeft64(d, 36)) ^ (Bits::RotateLeft64(d, 30))
			^ (Bits::RotateLeft64(d, 25))) + ((d & e) ^ (d & f) ^ (e & f)));

		b = b + (0x113F9804BEF90DAE + data.get()[70] + ((Bits::RotateLeft64(g, 50))
			^ (Bits::RotateLeft64(g, 46)) ^ (Bits::RotateLeft64(g, 23))) +
			((g & h) ^ (~g & a)));

		f = f + b;
		b = b + (((Bits::RotateLeft64(c, 36)) ^ (Bits::RotateLeft64(c, 30))
			^ (Bits::RotateLeft64(c, 25))) + ((c & d) ^ (c & e) ^ (d & e)));

		a = a + (0x1B710B35131C471B + data.get()[71] + ((Bits::RotateLeft64(f, 50))
			^ (Bits::RotateLeft64(f, 46)) ^ (Bits::RotateLeft64(f, 23))) +
			((f & g) ^ (~f & h)));

		e = e + a;
		a = a + (((Bits::RotateLeft64(b, 36)) ^ (Bits::RotateLeft64(b, 30))
			^ (Bits::RotateLeft64(b, 25))) + ((b & c) ^ (b & d) ^ (c & d)));

		   // R9

		h = h + (0x28DB77F523047D84 + data.get()[72] + ((Bits::RotateLeft64(e, 50))
			^ (Bits::RotateLeft64(e, 46)) ^ (Bits::RotateLeft64(e, 23))) +
			((e & f) ^ (~e & g)));

		d = d + h;
		h = h + (((Bits::RotateLeft64(a, 36)) ^ (Bits::RotateLeft64(a, 30))
			^ (Bits::RotateLeft64(a, 25))) + ((a & b) ^ (a & c) ^ (b & c)));

		g = g + (0x32CAAB7B40C72493 + data.get()[73] + ((Bits::RotateLeft64(d, 50))
			^ (Bits::RotateLeft64(d, 46)) ^ (Bits::RotateLeft64(d, 23))) +
			((d & e) ^ (~d & f)));

		c = c + g;
		g = g + (((Bits::RotateLeft64(h, 36)) ^ (Bits::RotateLeft64(h, 30))
			^ (Bits::RotateLeft64(h, 25))) + ((h & a) ^ (h & b) ^ (a & b)));

		f = f + (0x3C9EBE0A15C9BEBC + data.get()[74] + ((Bits::RotateLeft64(c, 50))
			^ (Bits::RotateLeft64(c, 46)) ^ (Bits::RotateLeft64(c, 23))) +
			((c & d) ^ (~c & e)));

		b = b + f;
		f = f + (((Bits::RotateLeft64(g, 36)) ^ (Bits::RotateLeft64(g, 30))
			^ (Bits::RotateLeft64(g, 25))) + ((g & h) ^ (g & a) ^ (h & a)));

		e = e + (0x431D67C49C100D4C + data.get()[75] + ((Bits::RotateLeft64(b, 50))
			^ (Bits::RotateLeft64(b, 46)) ^ (Bits::RotateLeft64(b, 23))) +
			((b & c) ^ (~b & d)));

		a = a + e;
		e = e + (((Bits::RotateLeft64(f, 36)) ^ (Bits::RotateLeft64(f, 30))
			^ (Bits::RotateLeft64(f, 25))) + ((f & g) ^ (f & h) ^ (g & h)));

		d = d + (0x4CC5D4BECB3E42B6 + data.get()[76] + ((Bits::RotateLeft64(a, 50))
			^ (Bits::RotateLeft64(a, 46)) ^ (Bits::RotateLeft64(a, 23))) +
			((a & b) ^ (~a & c)));

		h = h + d;
		d = d + (((Bits::RotateLeft64(e, 36)) ^ (Bits::RotateLeft64(e, 30))
			^ (Bits::RotateLeft64(e, 25))) + ((e & f) ^ (e & g) ^ (f & g)));

		c = c + (0x597F299CFC657E2A + data.get()[77] + ((Bits::RotateLeft64(h, 50))
			^ (Bits::RotateLeft64(h, 46)) ^ (Bits::RotateLeft64(h, 23))) +
			((h & a) ^ (~h & b)));

		g = g + c;
		c = c + (((Bits::RotateLeft64(d, 36)) ^ (Bits::RotateLeft64(d, 30))
			^ (Bits::RotateLeft64(d, 25))) + ((d & e) ^ (d & f) ^ (e & f)));

		b = b + (0x5FCB6FAB3AD6FAEC + data.get()[78] + ((Bits::RotateLeft64(g, 50))
			^ (Bits::RotateLeft64(g, 46)) ^ (Bits::RotateLeft64(g, 23))) +
			((g & h) ^ (~g & a)));

		f = f + b;
		b = b + (((Bits::RotateLeft64(c, 36)) ^ (Bits::RotateLeft64(c, 30))
			^ (Bits::RotateLeft64(c, 25))) + ((c & d) ^ (c & e) ^ (d & e)));

		a = a + (0x6C44198C4A475817 + data.get()[79] + ((Bits::RotateLeft64(f, 50))
			^ (Bits::RotateLeft64(f, 46)) ^ (Bits::RotateLeft64(f, 23))) +
			((f & g) ^ (~f & h)));

		e = e + a;
		a = a + (((Bits::RotateLeft64(b, 36)) ^ (Bits::RotateLeft64(b, 30))
			^ (Bits::RotateLeft64(b, 25))) + ((b & c) ^ (b & d) ^ (c & d)));

		state.get()[0]  = state.get()[0] + a;
		state.get()[1]  = state.get()[1] + b;
		state.get()[2]  = state.get()[2] + c;
		state.get()[3]  = state.get()[3] + d;
		state.get()[4]  = state.get()[4] + e;
		state.get()[5]  = state.get()[5] + f;
		state.get()[6]  = state.get()[6] + g;
		state.get()[7]  = state.get()[7] + h;

		memset(data.get(), 0, sizeof(data.get()));
	} // end function TransformBlock

protected:
	shared_ptr<uint64_t> state;
	shared_ptr<uint64_t> data;

}; // end class SHA2_512Base


#endif //!HLPSHA2_512BASE_H