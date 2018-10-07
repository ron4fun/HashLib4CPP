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

#ifndef HLPHASH_H
#define HLPHASH_H

#include <typeinfo>
#include "HlpHashResult.h"
#include "../Interfaces/HlpIHash.h"
#include "../Utils/HlpUtils.h"

class Hash : public virtual IIHash
{
protected:
	const char * name;

private:
	static const char *IndexOutOfRange;
	static const char *InvalidBufferSize;
	static const char *UnAssignedStream;
	static const char *FileNotExist;
	static const char *CloneNotYetImplemented;

protected:
	virtual inline int32_t GetBufferSize() const
	{
		return buffer_size;
	} // end function GetBufferSize

	virtual inline void SetBufferSize(const int32_t value)
	{
		if (value > 0)
		{
			buffer_size = value;
		} // end if
		else
		{
			throw ArgumentHashLibException(Hash::InvalidBufferSize);
		} // end else
	} // end function SetBufferSize

	virtual int32_t GetBlockSize() const
	{
		return block_size;
	} // end function GetBlockSize

	virtual int32_t GetHashSize() const
	{
		return hash_size;
	} // end function GetHashSize

public:
	Hash(const int32_t a_hash_size, const int32_t a_block_size)
		: block_size(a_block_size), hash_size(a_hash_size), buffer_size(BUFFER_SIZE)
	{} // end constructor
	
	virtual string GetName() const
	{
		return name;
	} // end function GetName

	virtual IHash Clone() const
	{
		throw NotImplementedHashLibException(Utils::string_format(Hash::CloneNotYetImplemented, GetName()));
	}

	virtual IHashResult ComputeString(const string &a_data)
	{
		return ComputeBytes(Converters::ConvertStringToBytes(a_data));
	} // end function ComputeString

	virtual IHashResult ComputeUntyped(const void *a_data, const int64_t a_length)
	{
		Initialize();
		TransformUntyped(a_data, a_length);
		return TransformFinal();
	} // end function ComputeUntyped

	virtual void TransformUntyped(const void *a_data, const int64_t a_length)
	{
		uint8_t *PtrBuffer, *PtrEnd;
		HashLibByteArray ArrBuffer;
		int32_t LBufferSize;

		PtrBuffer = (uint8_t *)a_data;

		if (buffer_size > a_length) // Sanity Check
			LBufferSize = BUFFER_SIZE;
		else
			LBufferSize = buffer_size;

		if (PtrBuffer)
		{
			ArrBuffer.resize(LBufferSize);
			PtrEnd = (PtrBuffer) + a_length;

			while (PtrBuffer < PtrEnd)
			{
				if ((PtrEnd - PtrBuffer) >= LBufferSize)
				{
					memmove(&ArrBuffer[0], PtrBuffer, LBufferSize);
					TransformBytes(ArrBuffer);
					PtrBuffer += LBufferSize;
				} // end if
				else
				{
					ArrBuffer.resize(PtrEnd - PtrBuffer);
					memmove(&ArrBuffer[0], PtrBuffer, ArrBuffer.size());
					TransformBytes(ArrBuffer);
					break;
				} // end else
			} // end while

		} // end if

	} // end function TransformUntyped

	virtual IHashResult ComputeStream(ifstream &a_stream, const int64_t a_length = -1)
	{
		Initialize();
		TransformStream(a_stream, a_length);
		return TransformFinal();
	} // end function ComputeStream

	virtual IHashResult ComputeFile(const string &a_file_name,
		const int64_t a_from = 0, const int64_t a_length = -1)
	{
		Initialize();
		TransformFile(a_file_name, a_from, a_length);
		return TransformFinal();
	} // end function ComputeFile

	virtual IHashResult ComputeBytes(const HashLibByteArray &a_data)
	{
		Initialize();
		TransformBytes(a_data);
		return TransformFinal();
	} // end function ComputeBytes

	virtual void TransformString(const string &a_data)
	{
		TransformBytes(Converters::ConvertStringToBytes(a_data));
	} // end function TransformString

	virtual void TransformBytes(const HashLibByteArray &a_data)
	{
		TransformBytes(a_data, 0, (int32_t)a_data.size());
	} // end function TransformBytes

	virtual void TransformBytes(const HashLibByteArray &a_data, const int32_t a_index)
	{
		int32_t Length = (int32_t)a_data.size() - a_index;
		TransformBytes(a_data, a_index, Length);
	} // end function TransformBytes

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length) = 0;

	virtual void TransformStream(ifstream &a_stream, const int64_t a_length = -1)
	{
		int32_t readed = 0, LBufferSize;
		uint64_t size, new_size;
		int64_t total;

		total = 0;
		size = GetStreamSize(a_stream);

		if (a_stream)
		{
			if (a_length > -1)
			{
				if (uint64_t(a_stream.tellg() + a_length) > size)
					throw IndexOutOfRangeHashLibException(Hash::IndexOutOfRange);
			} // end if

			if (a_stream.tellg() >= size)
				return;
		} // end if
		else
			throw ArgumentNilHashLibException(Hash::UnAssignedStream);


		if (size > BUFFER_SIZE)
		{
			if (a_length == -1) LBufferSize = BUFFER_SIZE;
			else
			{
				LBufferSize = a_length > BUFFER_SIZE ? BUFFER_SIZE : a_length;
			}
		}
		else
		{
			LBufferSize = a_length == -1 ? size : a_length;
		}	

		HashLibByteArray data = HashLibByteArray(LBufferSize);

		if (LBufferSize == BUFFER_SIZE)
		{
			while (true)
			{
				a_stream.read((char*)&data[0], LBufferSize);

				readed = a_stream.gcount();
				if (readed != BUFFER_SIZE)
				{
					data.resize(readed);

					TransformBytes(data, 0, readed);

					break;
				}
					
				if (readed == 0) break;

				total = total + readed;

				TransformBytes(data, 0, readed);

				if (a_length != -1 && a_length - total <= BUFFER_SIZE)
				{
					new_size = a_length - total;
					data.resize(new_size);

					a_stream.read((char*)&data[0], new_size);

					TransformBytes(data, 0, new_size);
					break;
				}
			
			} // end while
		}
		else
		{
			a_stream.read((char*)&data[0], LBufferSize);

			TransformBytes(data, 0, LBufferSize);
		}		
	} // end function TransformStream

	virtual void TransformFile(const string &a_file_name,
		const int64_t a_from = 0, const int64_t a_length = -1)
	{
		ifstream ReadFile;
		ReadFile.open(a_file_name.c_str(), ios::in | ios::binary);

		if (!ReadFile.is_open())
			throw ArgumentHashLibException(Hash::FileNotExist);

		ReadFile.seekg(a_from, ios::beg);

		TransformStream(ReadFile, a_length);

		ReadFile.close();
	} // end function TransformFile


private:
	static streampos GetStreamSize(ifstream &a_stream)
	{
		streampos pos = a_stream.tellg();

		streampos fsize = pos;
		a_stream.seekg(pos, ios::end);
		fsize = a_stream.tellg() - fsize;

		a_stream.seekg(pos, ios::beg); // return cur to original pos

		return fsize;
	} // end function GetStreamSize
	

protected:
	int32_t buffer_size;
	int32_t block_size;
	int32_t hash_size;

	static const int32_t BUFFER_SIZE = int32_t(64 * 1024); // 64Kb


}; // end class Hash

const char *Hash::IndexOutOfRange = "Current Index Is Out Of Range";
const char *Hash::InvalidBufferSize = "\"BufferSize\" Must Be Greater Than Zero";
const char *Hash::UnAssignedStream = "Input Stream Is Unassigned";
const char *Hash::FileNotExist = "Specified File Not Found";
const char *Hash::CloneNotYetImplemented = "Clone Not Yet Implemented For \"%s\"";

#endif // !HLPHASH_H
