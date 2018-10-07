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

#ifndef HLPHASHLIBTYPES_H
#define HLPHASHLIBTYPES_H

#include <memory>
#include <utility>
#include <stdexcept>
#include <vector>
#include <string>
using namespace std;

class HashLibException //: public runtime_error
{
public:
	HashLibException(const string &text)
		:msg_(text)
	{}  // end constructor

	const char * what() const throw ()
	{
		return msg_.c_str();
	} // end function what

private:
    string msg_;

}; // end class HashLibException

class InvalidOperationHashLibException : public HashLibException
{
public:
	InvalidOperationHashLibException(const string &text)
		: HashLibException(text)
	{}
}; // end class InvalidOperationHashLibException

class IndexOutOfRangeHashLibException : public HashLibException
{
public:
	IndexOutOfRangeHashLibException(const string &text)
		: HashLibException(text)
	{}
}; // end class IndexOutOfRangeHashLibException

class ArgumentInvalidHashLibException : public HashLibException
{
public:
	ArgumentInvalidHashLibException(const string &text)
		: HashLibException(text)
	{}
}; // end class ArgumentInvalidHashLibException

class ArgumentHashLibException : public HashLibException
{
public:
	ArgumentHashLibException(const string &text)
		: HashLibException(text)
	{}
}; // end class ArgumentHashLibException

class ArgumentNilHashLibException : HashLibException
{
public:
	ArgumentNilHashLibException(const string &text)
		: HashLibException(text)
	{}
}; // end class ArgumentNilHashLibException

class ArgumentOutOfRangeHashLibException : public HashLibException
{
public:
	ArgumentOutOfRangeHashLibException(const string &text)
		: HashLibException(text)
	{}
}; // end class ArgumentOutOfRangeHashLibException

class NullReferenceHashLibException : public HashLibException
{
public:
	NullReferenceHashLibException(const string &text)
		: HashLibException(text)
	{}
}; // end class NullReferenceHashLibException

class UnsupportedTypeHashLibException : public HashLibException
{
public:
	UnsupportedTypeHashLibException(const string &text)
		: HashLibException(text)
	{}
}; // end class UnsupportedTypeHashLibException

class NotImplementedHashLibException : public HashLibException
{
public:
	NotImplementedHashLibException(const string &text)
		: HashLibException(text)
	{}
}; // end class NotImplementedHashLibException

/// <summary>
/// Represents a dynamic array of Byte.
/// </summary>
typedef vector<uint8_t> HashLibByteArray;

/// <summary>
/// Represents a dynamic array of UInt32.
/// </summary>
typedef vector<uint32_t> HashLibUInt32Array;

/// <summary>
/// Represents a dynamic array of UInt64.
/// </summary>
typedef vector<uint64_t> HashLibUInt64Array;

/// <summary>
/// Represents a dynamic array of String.
/// </summary>
typedef vector<string> HashLibStringArray;

/// <summary>
/// Represents a dynamic array of Char.
/// </summary>
typedef vector<char> HashLibCharArray;

/// <summary>
/// Represents a dynamic array of array of UInt8.
/// </summary>
typedef vector<HashLibByteArray> HashLibMatrixByteArray;

/// <summary>
/// Represents a dynamic array of array of UInt32.
/// </summary>
typedef vector<HashLibUInt32Array> HashLibMatrixUInt32Array;

/// <summary>
/// Represents a dynamic array of array of UInt64.
/// </summary>
typedef vector<HashLibUInt64Array> HashLibMatrixUInt64Array;

#endif // ! HLPHASHLIBTYPES_H
