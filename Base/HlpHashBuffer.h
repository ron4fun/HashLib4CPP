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

#ifndef HLPHASHBUFFER_H
#define HLPHASHBUFFER_H

#include <sstream>
#include "../Utils/HlpHashLibTypes.h"


class HashBuffer
{
public:
	HashBuffer(const int32_t a_length)
	{
		data.resize(a_length);
		Initialize();
	} // end constructor

	~HashBuffer()
	{} // end destructor

	HashBuffer Clone() const
	{
		HashBuffer result = HashBuffer(0);
		result.data = data;
		result.pos = pos;

		return result;
	}

	bool Feed(const uint8_t *a_data, const int32_t a_length_a_data, const int32_t a_length)
	{
		int32_t Length;

		if (a_length_a_data == 0)
		{
			return false;
		} // end if
		
		if (a_length == 0)
		{
			return false;
		} // end if
		
		Length = data.size() - pos;
		if (Length > a_length)
		{
			Length = a_length;
		} // end if
		
		memmove(&data[pos], &a_data[0], Length * sizeof(uint8_t));

		pos = pos + Length;

		return GetIsFull();
	} // end function Feed
	
	bool Feed(const uint8_t *a_data, const int32_t a_length_a_data,
		int32_t &a_start_index, int32_t &a_length, uint64_t &a_processed_bytes)
	{
		int32_t Length;

		if (a_length_a_data == 0)
		{
			return false;
		} // end if
		
		if (a_length == 0)
		{
			return false;
		} // end if
		
		Length = data.size() - pos;
		if (Length > a_length)
		{
			Length = a_length;
		} // end if

		memmove(&data[pos], &a_data[a_start_index], Length * sizeof(uint8_t));
		
		pos = pos + Length;
		a_start_index = a_start_index + Length;
		a_length = a_length - Length;
		a_processed_bytes = a_processed_bytes + uint64_t(Length);

		return GetIsFull();
	} // end function Feed
	
	inline HashLibByteArray GetBytes()
	{
		pos = 0;
		return data;
	} // end function GetBytes
	
	inline HashLibByteArray GetBytesZeroPadded()
	{
		memset(&data[pos], 0, (data.size() - pos) * sizeof(uint8_t));
		pos = 0;
		return data;
	} // end function GetBytesZeroPadded
	
	bool GetIsEmpty() const
	{
		return pos == 0;
	} // end function GetIsEmpty
	
	bool GetIsFull() const
	{
		return pos == data.size();
	} // end function GetIsFull
	
	int32_t GetLength() const
	{
		return data.size();
	} // end function GetLength
	
	int32_t GetPos() const
	{
		return pos;
	} // end function GetPos
	
	void Initialize()
	{
		pos = 0;
		memset(&data[0], 0, data.size() * sizeof(uint8_t));
	} // end function Initialize
	
	string ToString() const
	{
		stringstream ss;
		ss << "HashBuffer, Length: " << GetLength();
		ss << ", Pos: " << GetPos() << ", IsEmpty: " << GetIsEmpty();
		
		return ss.str();
	} // end function ToString
	

private:
	HashLibByteArray data;
	int32_t pos;

}; // end class HashBuffer


#endif // !HLPHASHBUFFER_H