#ifndef HLPBITCONVERTER_H
#define HLPBITCONVERTER_H

#include "HlpHashLibTypes.h"


class BitConverter
{
public:
	BitConverter()
	{
		int32_t IntValue = 1;
		int * PIIntValueAddress = &IntValue;
		uint8_t *PBIntValueAddress = (uint8_t *)PIIntValueAddress;
		uint8_t ByteValue = *PBIntValueAddress;
		
		IsLittleEndian = (ByteValue == 1) ? true : false;
	} // end constructor

	inline static bool GetIsLittleEndian()
	{
		return IsLittleEndian;
	} // end function GetIsLittleEndian

	inline static char GetHexValue(const int32_t i)
	{
		if (i < 10)
		{
			return i + '0';
		} // end if
		
		return (i - 10) + 'A';
	} // end function GetHexValue

	inline static HashLibByteArray GetBytes(const int16_t value)
	{
		HashLibByteArray result = HashLibByteArray(sizeof(value));
		*(int16_t *)(&(result[0])) = value;

		return result;
	} // end function GetBytes

	inline static HashLibByteArray GetBytes(const int32_t value)
	{
		HashLibByteArray result = HashLibByteArray(sizeof(value));
		*(int32_t *)(&(result[0])) = value;

		return result;
	} // end function GetBytes

	inline static HashLibByteArray GetBytes(const float value)
	{
		HashLibByteArray result = HashLibByteArray(sizeof(value));
		*(float *)(&(result[0])) = value;

		return result;
	} // end function GetBytes

	inline static HashLibByteArray GetBytes(const double value)
	{
		HashLibByteArray result = HashLibByteArray(sizeof(value));
		*(double *)(&(result[0])) = value;

		return result;
	} // end function GetBytes

	inline static HashLibByteArray GetBytes(const bool value)
	{
		HashLibByteArray result = HashLibByteArray(sizeof(value));
		*(bool *)(&(result[0])) = value;

		return result;
	} // end function GetBytes

	inline static HashLibByteArray GetBytes(const char value)
	{
		HashLibByteArray result = HashLibByteArray(sizeof(value));
		*(char *)(&(result[0])) = value;

		return result;
	} // end function GetBytes

	inline static HashLibByteArray GetBytes(const uint8_t value)
	{
		HashLibByteArray result = HashLibByteArray(sizeof(value));
		*(uint8_t *)(&(result[0])) = value;

		return result;
	} // end function GetBytes

	inline static HashLibByteArray GetBytes(const uint16_t value)
	{
		HashLibByteArray result = HashLibByteArray(sizeof(value));
		*(uint16_t *)(&(result[0])) = value;

		return result;
	} // end function GetBytes

	inline static HashLibByteArray GetBytes(const uint32_t value)
	{
		HashLibByteArray result = HashLibByteArray(sizeof(value));
		*(uint32_t *)(&(result[0])) = value;

		return result;
	} // end function GetBytes

	inline static HashLibByteArray GetBytes(const int64_t value)
	{
		HashLibByteArray result = HashLibByteArray(sizeof(value));
		*(int64_t *)(&(result[0])) = value;

		return result;
	} // end function GetBytes

	inline static HashLibByteArray GetBytes(const uint64_t value)
	{
		HashLibByteArray result = HashLibByteArray(sizeof(value));
		*(uint64_t *)(&(result[0])) = value;

		return result;
	} // end function GetBytes

	inline static bool ToBoolean(const HashLibByteArray &value, const int32_t StartIndex)
	{
		return *(bool *)(&value[StartIndex]);
	} // end function ToBoolean

	inline static char ToChar(const HashLibByteArray &value, const int32_t StartIndex)
	{
		if (IsLittleEndian)
		{
			return  (value[StartIndex] | (value[StartIndex + 1] << 8));
		} // end if

		return ((value[StartIndex] << 8) | value[StartIndex + 1]);
	} // end function ToChar

	inline static double ToDouble(const HashLibByteArray &value, const int32_t StartIndex)
	{
		int32_t i1, i2;
		int64_t val;

		if (IsLittleEndian)
		{
			i1 = value[StartIndex] | (value[StartIndex + 1] << 8) |
				(value[StartIndex + 2] << 16) | (value[StartIndex + 3] << 24);
			i2 = (value[StartIndex + 4]) | (value[StartIndex + 5] << 8) |
				(value[StartIndex + 6] << 16) | (value[StartIndex + 7] << 24);
			val = uint32_t(i1) | (int64_t(i2) << 32);
			return *(double *)(&val);
		}

		i1 = (value[StartIndex] << 24) | (value[StartIndex + 1] << 16) |
		(value[StartIndex + 2] << 8) | (value[StartIndex + 3]);
		i2 = (value[StartIndex + 4] << 24) | (value[StartIndex + 5] << 16) |
		(value[StartIndex + 6] << 8) | (value[StartIndex + 7]);
		val = uint32_t(i2) | (int64_t(i1) << 32);
		return *(double *)(&val);
	} // end function ToDouble

	inline static int16_t ToInt16(const HashLibByteArray &value, const int32_t StartIndex)
	{
		if (IsLittleEndian)
		{
			return (value[StartIndex] | (value[StartIndex + 1] << 8));
		} // end if

		return ((value[StartIndex] << 8) | value[StartIndex + 1]);
	} // end function ToInt16

	inline static int32_t ToInt32(const HashLibByteArray &value, const int32_t StartIndex)
	{
		if (IsLittleEndian)
		{
			return value[StartIndex] | (value[StartIndex + 1] << 8) |
				(value[StartIndex + 2] << 16) | (value[StartIndex + 3] << 24);
		} // end if

		return (value[StartIndex] << 24) | (value[StartIndex + 1] << 16) |
			(value[StartIndex + 2] << 8) | (value[StartIndex + 3]);
	} // end function ToInt32
	
	inline static int64_t ToInt64(const HashLibByteArray &value, const int32_t StartIndex)
	{
		int32_t i1, i2;

		if (IsLittleEndian)
		{
			i1 = value[StartIndex] | (value[StartIndex + 1] << 8) |
			(value[StartIndex + 2] << 16) | (value[StartIndex + 3] << 24);
			i2 = (value[StartIndex + 4]) | (value[StartIndex + 5] << 8) |
			(value[StartIndex + 6] << 16) | (value[StartIndex + 7] << 24);
			return uint32_t(i1) | (int64_t(i2) << 32);
		} // end if
		
		i1 = (value[StartIndex] << 24) | (value[StartIndex + 1] << 16) |
			(value[StartIndex + 2] << 8) | (value[StartIndex + 3]);
		i2 = (value[StartIndex + 4] << 24) | (value[StartIndex + 5] << 16) |
		(value[StartIndex + 6] << 8) | (value[StartIndex + 7]);
		return uint32_t(i2) | (int64_t(i1) << 32);
	} // end function ToInt64
	
	inline static float ToFloat(const HashLibByteArray &value, const int32_t StartIndex)
	{
		int32_t val;

		if (IsLittleEndian)
		{
			val = (value[StartIndex] | (value[StartIndex + 1] << 8) |
			(value[StartIndex + 2] << 16) | (value[StartIndex + 3] << 24));
			return *(float *)(&val);
		} // end if
	
		val = (value[StartIndex] << 24) | (value[StartIndex + 1] << 16) |
		(value[StartIndex + 2] << 8) | (value[StartIndex + 3]);
		return *(float *)(&val);
	} // end function ToFloat
	
	inline static string ToString(const HashLibByteArray &value)
	{
		return BitConverter::ToString(value, 0);
	} // end function ToString
	
	inline static string ToString(const HashLibByteArray &value, const int32_t StartIndex)
	{
		return BitConverter::ToString((uint8_t *)&value[0], StartIndex, (int32_t)value.size() - StartIndex);
	} // end function ToString

	inline static string ToString(const uint8_t *value, const int32_t StartIndex, const int32_t Length)
	{
		string result;

		int32_t chArrayLength = Length * 3;

		char* chArray = new char[chArrayLength];

		int32_t Idx = 0;
		int32_t Index = StartIndex;
		while (Idx < chArrayLength)
		{
			uint8_t b = value[Index];
			Index += 1;

			chArray[Idx] = BitConverter::GetHexValue(b >> 4);
			chArray[Idx + 1] = BitConverter::GetHexValue(b & 15);
			chArray[Idx + 2] = '-';

			Idx += 3;
		} // end while
		
		result = string((char *)&chArray[0], chArrayLength - 1);

		delete[] chArray;

		return result;
	} // end function ToString

	inline static uint8_t ToUInt8(const HashLibByteArray &value, const int32_t StartIndex)
	{
		return *(uint8_t *)(&value[StartIndex]);
	} // end function ToUInt8

	inline static uint16_t ToUInt16(const HashLibByteArray &value, const int32_t StartIndex)
	{
		if (IsLittleEndian)
		{
			return (value[StartIndex] | (value[StartIndex + 1] << 8));
		} // end if
		
		return ((value[StartIndex] << 8) | value[StartIndex + 1]);
	} // end function ToUInt16

	inline static uint32_t ToUInt32(const HashLibByteArray &value, const int32_t StartIndex)
	{
		if (IsLittleEndian)
		{
			return (value[StartIndex] | (value[StartIndex + 1] << 8) |
				(value[StartIndex + 2] << 16) | (value[StartIndex + 3] << 24));
		} // end if
		
		return ((value[StartIndex] << 24) |
				(value[StartIndex + 1] << 16) | (value[StartIndex + 2] << 8) |
				(value[StartIndex + 3]));
	} // end function ToUInt32

	inline static uint32_t ToUInt32(const uint8_t *value, const int32_t StartIndex)
	{
		if (IsLittleEndian)
		{
			return (value[StartIndex] | (value[StartIndex + 1] << 8) |
				(value[StartIndex + 2] << 16) | (value[StartIndex + 3] << 24));
		} // end if
		
		return ((value[StartIndex] << 24) |
				(value[StartIndex + 1] << 16) | (value[StartIndex + 2] << 8) |
				(value[StartIndex + 3]));
	} // end function ToUInt32

	inline static uint64_t ToUInt64(const HashLibByteArray &value, const int32_t StartIndex)
	{
		int32_t i1, i2;
		
		if (IsLittleEndian)
		{
			i1 = value[StartIndex] | (value[StartIndex + 1] << 8) |
			(value[StartIndex + 2] << 16) | (value[StartIndex + 3] << 24);
			i2 = (value[StartIndex + 4]) | (value[StartIndex + 5] << 8) |
			(value[StartIndex + 6] << 16) | (value[StartIndex + 7] << 24);
			return uint64_t(uint32_t(i1) | (int64_t(i2) << 32));
		} // end if
		
		i1= (value[StartIndex] << 24) | (value[StartIndex + 1] << 16) |
			(value[StartIndex + 2] << 8) | (value[StartIndex + 3]);
		i2 = (value[StartIndex + 4] << 24) | (value[StartIndex + 5] << 16) |
			(value[StartIndex + 6] << 8) | (value[StartIndex + 7]);
		return uint64_t(uint32_t(i2) | (int64_t(i1) << 32));
	} // end function ToUInt64
	
	inline static uint64_t ToUInt64(const uint8_t *value, const int32_t StartIndex)
	{
		int32_t i1, i2;
		
		if (IsLittleEndian)
		{
			i1 = value[StartIndex] | (value[StartIndex + 1] << 8) |
			(value[StartIndex + 2] << 16) | (value[StartIndex + 3] << 24);
			i2 = (value[StartIndex + 4]) | (value[StartIndex + 5] << 8) |
			(value[StartIndex + 6] << 16) | (value[StartIndex + 7] << 24);
			return uint64_t(uint32_t(i1) | (int64_t(i2) << 32));
		} // end if
			
		i1 = (value[StartIndex] << 24) | (value[StartIndex + 1] << 16) |
			(value[StartIndex + 2] << 8) | (value[StartIndex + 3]);
		i2 = (value[StartIndex + 4] << 24) | (value[StartIndex + 5] << 16) |
			(value[StartIndex + 6] << 8) | (value[StartIndex + 7]);
		return uint64_t(uint32_t(i2) | (int64_t(i1) << 32));
	} // end function ToUInt64
	
private:
	inline static bool staticConstructor()
	{
		int32_t IntValue = 1;
		int * PIIntValueAddress = &IntValue;
		uint8_t *PBIntValueAddress = (uint8_t *)PIIntValueAddress;
		uint8_t ByteValue = *PBIntValueAddress;

		return (ByteValue == 1) ? true : false;
	} // end function staticConstructor

	static bool IsLittleEndian;

}; // end class BitConverter

bool BitConverter::IsLittleEndian = BitConverter::staticConstructor();

#endif // !HLPBITCONVERTER_H