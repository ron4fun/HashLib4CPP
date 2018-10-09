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

#ifndef HLPCONVERTERS_H
#define HLPCONVERTERS_H

#include <algorithm>
#include <iterator>
#include "../Utils/HlpBits.h"
#include "../Utils/HlpBitConverter.h"


class Converters
{
public:
	inline static void toUpper(uint8_t *value, const uint32_t length)
	{
		for (register uint32_t i = 0; i < length; i++)
		{
			value[i] = toupper(value[i]);
		} // end for

	} // end function toUpper

	inline static string toUpper(const string &value)
	{
		string temp;
		for (register uint32_t i = 0; i < value.length(); i++)
		{
			temp += toupper(value[i]);
		} // end for
		return temp;
	} // end function toUpper

	static void swap_copy_str_to_u32(const void *src, const int32_t src_index,
		void *dest, int32_t dest_index, const int32_t length)
	{
		uint32_t *lsrc, *ldest, *lend;
		uint8_t *lbsrc;
		int32_t	lLength;
		
		// if all pointers and length are 32-bits aligned
		if (((int32_t((uint8_t *)(dest)-(uint8_t *)(0)) | ((uint8_t *)(src)-(uint8_t *)(0)) | src_index |
			dest_index | length) & 3) == 0)
		{
			// copy memory as 32-bit words
			lsrc = (uint32_t *)((uint8_t *)(src) + src_index);
			lend = (uint32_t *)(((uint8_t *)(src) + src_index) + length);
			ldest = (uint32_t *)((uint8_t *)(dest) + dest_index);
			while (lsrc < lend)
			{
				*ldest = Bits::ReverseBytesUInt32(*lsrc);
				ldest += 1;
				lsrc += 1;
			} // end while
		} // end if
		
		else
		{
			lbsrc = ((uint8_t *)(src) + src_index);

			lLength = length + dest_index;
			while (dest_index < lLength)
			{
				((uint8_t *)dest)[dest_index ^ 3] = *lbsrc;

				lbsrc += 1;
				dest_index += 1;
			} // end while
		} // end else

	} // end function swap_copy_str_to_u32
	
	static void swap_copy_str_to_u64(const void *src, const int32_t src_index,
		void *dest, int32_t dest_index, const int32_t length)
	{
		uint64_t *lsrc, *ldest, *lend;
		uint8_t *lbsrc;
		int32_t	lLength;

		// if all pointers and length are 64-bits aligned
		if (((int32_t((uint8_t *)(dest)-(uint8_t *)(0)) | ((uint8_t *)(src)-(uint8_t *)(0)) | src_index |
			dest_index | length) & 7) == 0)
		{
			// copy aligned memory block as 64-bit integers
			lsrc = (uint64_t *)((uint8_t *)(src) + src_index);
			lend = (uint64_t *)(((uint8_t *)(src) + src_index) + length);
			ldest = (uint64_t *)((uint8_t *)(dest) + dest_index);
			while (lsrc < lend)
			{
				*ldest = Bits::ReverseBytesUInt64(*lsrc);
				ldest += 1;
				lsrc += 1;
			} // end while
		} // end if
		else
		{
			lbsrc = ((uint8_t *)(src) + src_index);

			lLength = length + dest_index;
			while (dest_index < lLength)
			{
				((uint8_t *)dest)[dest_index ^ 7] = *lbsrc;

				lbsrc += 1;
				dest_index += 1;
			} // end while				
		} // end else		
	} // end function swap_copy_str_to_u64
	
	inline static uint32_t be2me_32(const uint32_t x)
	{
		if (BitConverter::GetIsLittleEndian())
		{
			return Bits::ReverseBytesUInt32(x);
		} // end if
		
		return x;
	} // end function be2me_32
	
	inline static uint64_t be2me_64(const uint64_t x)
	{
		if (BitConverter::GetIsLittleEndian())
		{
			return Bits::ReverseBytesUInt64(x);
		} // end if
		
		return x;
	} // end function be2me_64
	
	inline static void be32_copy(const void *src, const int32_t src_index,
		void *dest, const int32_t dest_index, const int32_t length)
	{
		if (BitConverter::GetIsLittleEndian())
		{
			Converters::swap_copy_str_to_u32(src, src_index, dest, dest_index, length);
		} // end if	
		else
		{
			memmove(((uint8_t *)(dest) + dest_index), ((uint8_t *)(src) + src_index), length);
		} // end else
	} // end function be32_copy
	
	inline static void be64_copy(const void *src, const int32_t src_index,
		void *dest, const int32_t dest_index, const int32_t length)
	{
		if (BitConverter::GetIsLittleEndian())
		{
			Converters::swap_copy_str_to_u64(src, src_index, dest, dest_index, length);
		} // end if	
		else
		{
			memmove(((uint8_t *)(dest)+dest_index), ((uint8_t *)(src)+src_index), length);
		} // end else
	} // end function be64_copy
	
	inline static uint32_t le2me_32(const uint32_t x)
	{
		if (!BitConverter::GetIsLittleEndian())
		{
			return Bits::ReverseBytesUInt32(x);
		} // end if
		
		return x;
	} // end function le2me_32
	
	inline static uint64_t le2me_64(const uint64_t x)
	{
		if (!BitConverter::GetIsLittleEndian())
		{
			return Bits::ReverseBytesUInt64(x);
		} // end if
		
		return x;
	} // end function le2me_64
	
	inline static void le32_copy(const void *src, const int32_t src_index,
		void *dest, const int32_t dest_index, const int32_t length)
	{
		if (BitConverter::GetIsLittleEndian())
		{
			memmove(((uint8_t *)(dest)+dest_index), ((uint8_t *)(src)+src_index), length);
		} // end if
		else
		{
			Converters::swap_copy_str_to_u32(src, src_index, dest, dest_index, length);
		} // end else
	} // end function le32_copy
	
	inline static void le64_copy(const void *src, const int32_t src_index,
		void *dest, const int32_t dest_index, const int32_t length)
	{
		if (BitConverter::GetIsLittleEndian())
		{
			memmove(((uint8_t *)(dest)+dest_index), ((uint8_t *)(src)+src_index), length);
		} // end if
		else
		{
			Converters::swap_copy_str_to_u64(src, src_index, dest, dest_index, length);
		} // end else
	} // end function le64_copy
	
	inline static uint32_t ReadBytesAsUInt32LE(const uint8_t *a_in, const int32_t a_index)
	{
		uint32_t result = *(uint32_t *)(a_in + a_index);
		return Converters::le2me_32(result);
	} // end function ReadBytesAsUInt32LE
	
	inline static uint64_t ReadBytesAsUInt64LE(const uint8_t *a_in, const int32_t a_index)
	{
		uint64_t result = *(uint64_t *)(a_in + a_index);
		return Converters::le2me_64(result);
	} // end function ReadBytesAsUInt64LE

	inline static HashLibByteArray ReadUInt32AsBytesLE(const uint32_t a_in)
	{
		HashLibByteArray arr = HashLibByteArray(4);
		arr[0] = uint8_t(a_in);
		arr[1] = uint8_t(a_in >> 8);
		arr[2] = uint8_t(a_in >> 16);
		arr[3] = uint8_t(a_in >> 24);

		return arr;
	} // end function ReadUInt32AsBytesLE

	inline static HashLibByteArray ReadUInt64AsBytesLE(const uint64_t a_in)
	{
		HashLibByteArray arr = HashLibByteArray(8);
		arr[0] = uint8_t(a_in);
		arr[1] = uint8_t(a_in >> 8);
		arr[2] = uint8_t(a_in >> 16);
		arr[3] = uint8_t(a_in >> 24);
		arr[4] = uint8_t(a_in >> 32);
		arr[5] = uint8_t(a_in >> 40);
		arr[6] = uint8_t(a_in >> 48);
		arr[7] = uint8_t(a_in >> 56);

		return arr;
	} // end function ReadUInt64AsBytesLE

	inline static void ReadUInt64AsBytesLE(const uint64_t a_in, HashLibByteArray &a_out, const int32_t a_index)
	{
		a_out[a_index] = (uint8_t)a_in;
		a_out[a_index + 1] = (uint8_t)(a_in >> 8);
		a_out[a_index + 2] = (uint8_t)(a_in >> 16);
		a_out[a_index + 3] = (uint8_t)(a_in >> 24);
		a_out[a_index + 4] = (uint8_t)(a_in >> 32);
		a_out[a_index + 5] = (uint8_t)(a_in >> 40);
		a_out[a_index + 6] = (uint8_t)(a_in >> 48);
		a_out[a_index + 7] = (uint8_t)(a_in >> 56);
	} // end function ReadUInt64AsBytesLE

	inline static void ReadUInt64AsBytesBE(const uint64_t a_in, HashLibByteArray &a_out, const int32_t a_index)
	{
		a_out[a_index] = (uint8_t)(a_in >> 56);
		a_out[a_index + 1] = (uint8_t)(a_in >> 48);
		a_out[a_index + 2] = (uint8_t)(a_in >> 40);
		a_out[a_index + 3] = (uint8_t)(a_in >> 32);
		a_out[a_index + 4] = (uint8_t)(a_in >> 24);
		a_out[a_index + 5] = (uint8_t)(a_in >> 16);
		a_out[a_index + 6] = (uint8_t)(a_in >> 8);
		a_out[a_index + 7] = (uint8_t)a_in;
	} // end function ReadUInt64AsBytesBE

	static string ConvertBytesToHexString(const HashLibByteArray &a_in, const bool a_group)
	{
		return ConvertBytesToHexString(&a_in[0], a_in.size(), a_group);
	} // end function ConvertBytesToHexString

	static string ConvertBytesToHexString(const uint8_t *a_in, const uint32_t size, const bool a_group)
	{
		string hex = BitConverter::ToString(a_in, 0, size);
		transform(hex.begin(), hex.end(), hex.begin(), ::toupper);

		if (size == 1)
		{
			return hex;
		} // end if
		
		if (size == 2)
		{
			string result;
			remove_copy(hex.begin(), hex.end(), back_inserter(result), '-');

			return result;
		} // end if
	
		if (a_group)
		{
			string workstring = BitConverter::ToString(a_in, 0, size);
			transform(workstring.begin(), workstring.end(), workstring.begin(), ::toupper);

			HashLibStringArray arr = Converters::SplitString(workstring, '-');
			hex.clear();
			uint32_t I = 0;

			while (I < (arr.size() >> 2))
			{
				if (I != 0)
				{
					hex = hex + '-';
				} // end if
					
				hex = hex + (arr[I * 4] + arr[I * 4 + 1] + arr[I * 4 + 2] + arr[I * 4 + 3]);

				I += 1;
			} // end while

			return hex;
		} // end if
		
		string result;
		remove_copy(hex.begin(), hex.end(), back_inserter(result), '-');
		
		return result;
	} // end function ConvertBytesToHexString

	static inline HashLibByteArray ConvertHexStringToBytes(const string &_a_in)
	{
		string a_in = _a_in;

		remove(a_in.begin(), a_in.end(), '-');
		//replace(a_in.begin(), a_in.end(), '-', (char)0);
		HashLibByteArray result(a_in.size() >> 1);
		
		for (register uint32_t i = 0, j=0; i < a_in.length(); i += 2, j += 1)
		{
			string byteStr = a_in.substr(i, 2);
			result[j] = (char)strtol(byteStr.c_str(), 0, 16);
		} // end for

		return result;
	} // end function ConvertHexStringToBytes

	static inline HashLibByteArray ConvertStringToBytes(const string &a_in)
	{
		HashLibByteArray arr(a_in.length());
		for (register uint32_t i = 0; i < a_in.length(); i += 1)
		{
			arr[i] = uint8_t(a_in[i]);
		} // end for

		return arr;
	} // end function ConvertStringToBytes
	
	static HashLibStringArray SplitString(const string &S, const char Delimiter)
	{
		int32_t PosStart, PosDel, SplitPoints, I, Len;
		HashLibStringArray result;

		if (!S.empty())
		{
			SplitPoints = 0;
			for (register uint32_t i = 0; i < S.length(); i += 1)
			{ 
				if (Delimiter == S[i])
					SplitPoints += 1;
			} // end for
			
			result.resize(SplitPoints + 1);
			
			I = 0;
			Len = 1;
			PosStart = 0;
			PosDel = (int32_t)S.find(Delimiter, 0);
			while (PosDel != string::npos)
			{
				result[I] = S.substr(PosStart, PosDel - PosStart);
				PosStart = PosDel + Len;
				PosDel = (int32_t)S.find(Delimiter, PosStart);
				I += 1;
			} // end while

			result[I] = S.substr(PosStart, S.length());
		} // end if
		
		return result;
	} // end function SplitString


}; // end class Converters


#endif // !HLPCONVERTERS_H
