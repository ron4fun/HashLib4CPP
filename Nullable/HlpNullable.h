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

#ifndef HLPNULLABLE_H
#define HLPNULLABLE_H

#include <typeinfo>
#include "../Utils/HlpHashLibTypes.h"


template <typename T>
class Nullable
{
public:
	Nullable() 
	{} // end constructor

	Nullable(const T aValue)
	{
		SetValue(aValue);
	} // end constructor

	Nullable(const T aValue, const T aDefault)
	{
		SetValue(aValue);
		SetDefault(aDefault);
	} // end constructor

	inline void ClearValue()
	{
		InitValue = "";
	} // end function ClearValue

	inline void SetDefault(const T aDefault)
	{
		Default = aDefault;
		InitDefault = "I";
		if (GetIsNull())
			Value = aDefault;
	} // end function SetDefault

	explicit operator T() const
	{
		return Value;
	} // end operator T()

	operator Nullable<T>() const
	{
		return *this;
	} // end operator Nullable<T>()

	Nullable<T> operator+(const Nullable<T> &aValue)
	{
		Nullable<T> result = Nullable<T>();

		if (GetIsNull() || aValue.GetIsNull())
		{
			result.ClearValue();
			return result;
		} // end if		
		else
		{
			if (typeid(T) == typeid(int32_t))
				return result.SetValue(NewAddInt(GetValue(), aValue.GetValue()));
			if (typeid(T) == typeid(float))
				return result.SetValue(AddFloat(GetValue(), aValue.GetValue()));
			if (typeid(T) == typeid(string))
				return result.SetValue(AddString(GetValue(), aValue.GetValue()));
			if (typeid(T) == typeid(int64_t))
				return result.SetValue(AddInt64(GetValue(), aValue.GetValue()));
		}
		throw UnsupportedTypeHashLibException(UnsupportedType);
	} // end function operator+

	inline T GetValue()
	{
		CheckType();
		CheckValue();
		return Value;
	} // end function GetValue

private:
	static T CastBack(const Nullable<T> &aValue)
	{
		return T(aValue);
	} // end function CastBack

	static T AddFloat(const Nullable<T> &aFloat, const Nullable<T> &bFloat)
	{
		double _Value = double(aFloat) + double(bFloat);
		return CastBack(_Value);
	} // end function AddFloat

	static T AddString(const Nullable<T> &aString, const Nullable<T> &bString)
	{
		string _Value = string(aString) + string(bString);
		return CastBack(_Value);
	} // end function AddString

	static T AddInt64(const Nullable<T> &aInt64, const Nullable<T> &bInt64)
	{
		int64_t _Value = int64_t(aInt64) + int64_t(bInt64);
		return CastBack(_Value);
	} // end function AddInt64

	static T NewAddInt(const Nullable<T> &aInt, const Nullable<T> &bInt)
	{
		int32_t _Value = int32_t(aInt) + int32_t(bInt);
		return CastBack(_Value);
	} // end function NewAddInt

	inline void SetValue(const T aValue)
	{
		InitValue = "I";
		Value = aValue;
	} // end function SetValue

	inline void CheckValue()
	{
		if (GetIsNull()) 
		{
			if (GetHasDefault())
				Value = Default;
			else
				throw NullReferenceHashLibException(GetNullValue);
		} // end if
	} // end function CheckValue

	inline void CheckType() const
	{
		if (typeid(T) == typeid(int));
		else if (typeid(T) == typeid(int8_t));
		else if (typeid(T) == typeid(int16_t));
		else if (typeid(T) == typeid(int32_t));
		else if (typeid(T) == typeid(int64_t));
		else if (typeid(T) == typeid(uint8_t));
		else if (typeid(T) == typeid(uint16_t));
		else if (typeid(T) == typeid(uint32_t));
		else if (typeid(T) == typeid(uint64_t));
		else if (typeid(T) == typeid(float));
		else if (typeid(T) == typeid(double));
		else if (typeid(T) == typeid(string));
		else throw UnsupportedTypeHashLibException(UnsupportedType);
	} // end function CheckType
	
	inline bool GetIsNull() const
	{
		return InitValue != "I";
	} // end function GetIsNull

	inline bool GetHasValue() const
	{
		return !GetIsNull();
	} // end function GetHasValue

	inline bool GetHasDefault() const
	{
		return InitDefault == "I";
	} // end function GetHasDefault

private:
	T Value;
	string InitValue;
	T Default;
	string InitDefault;

	//static const char *CannotAssignPointerToNullable;
	static const char *UnsupportedType;
	static const char *GetNullValue;
}; // end class Nullable

//template <typename T>
//const char *Nullable<T>::CannotAssignPointerToNullable = "Cannot assign non-null pointer to nullable type.";
template <typename T>
const char *Nullable<T>::UnsupportedType = "Unsupported Type: Only supports Integers, Int64, Floats and Strings.";
template <typename T>
const char *Nullable<T>::GetNullValue = "Attempted to get a null value.";



/// <summary>
/// Represents a Nullable Integer.
/// </summary>
typedef Nullable<int32_t> NullableInteger;


#endif // !HLPNULLABLE_H

