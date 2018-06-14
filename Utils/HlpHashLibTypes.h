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
	HashLibException(const char * text)
	: msg_(text)
	{
	    //msg_ = string(text);
	}  // end constructor

	const char* what() const throw ()
	{
	    return msg_.c_str();
	} // end function what

private:
    string msg_;

}; // end class HashLibException

class InvalidOperationHashLibException : public HashLibException
{
public:
	InvalidOperationHashLibException(const char * text)
		: HashLibException(text)
	{}
}; // end class InvalidOperationHashLibException

class IndexOutOfRangeHashLibException : public HashLibException
{
public:
	IndexOutOfRangeHashLibException(const char * text)
		: HashLibException(text)
	{}
}; // end class IndexOutOfRangeHashLibException

class ArgumentHashLibException : public HashLibException
{
public:
	ArgumentHashLibException(const char * text)
		: HashLibException(text)
	{}
}; // end class ArgumentHashLibException

class ArgumentNilHashLibException : HashLibException
{
public:
	ArgumentNilHashLibException(const char * text)
		: HashLibException(text)
	{}
}; // end class ArgumentNilHashLibException

class ArgumentOutOfRangeHashLibException : public HashLibException
{
public:
	ArgumentOutOfRangeHashLibException(const char * text)
		: HashLibException(text)
	{}
}; // end class ArgumentOutOfRangeHashLibException

class NullReferenceHashLibException : public HashLibException
{
public:
	NullReferenceHashLibException(const char * text)
		: HashLibException(text)
	{}
}; // end class NullReferenceHashLibException

class UnsupportedTypeHashLibException : public HashLibException
{
public:
	UnsupportedTypeHashLibException(const char * text)
		: HashLibException(text)
	{}
}; // end class UnsupportedTypeHashLibException


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
/// Represents a dynamic array of array of UInt32.
/// </summary>
typedef vector<HashLibUInt32Array> HashLibMatrixUInt32Array;

/// <summary>
/// Represents a dynamic array of array of UInt64.
/// </summary>
typedef vector<HashLibUInt64Array> HashLibMatrixUInt64Array;

#endif // ! HLPHASHLIBTYPES_H
