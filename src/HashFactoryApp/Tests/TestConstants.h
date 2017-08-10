#ifndef TESTCONSTANTS_H
#define TESTCONSTANTS_H

#include <boost/test/included/unit_test.hpp>
#include "../Utils/HlpHashLibTypes.h"
#include "../Base/HlpConverters.h"
#include "../Base/HlpHashFactory.h"

string EmptyData = "";
string DefaultData = "HashLib4Pascal";
string ShortMessage = "A short message";
string ZerotoFour = "01234";
string OnetoNine = "123456789";
string RandomStringRecord = "I will not buy this record, it is scratched.";
string RandomStringTobacco = "I will not buy this tobacconist's, it is scratched.";
HashLibByteArray Bytesabcde = HashLibByteArray({ 0x61, 0x62, 0x63, 0x64, 0x65 });
string HexStringAsKey = "000102030405060708090A0B0C0D0E0F";
string HMACLongStringKey = "I need an Angel";
string HMACShortStringKey = "Hash";

string StringOfChar(const char value, const uint32_t count)
{
	string temp;
	for (register uint32_t i = 0; i < count; i++)
		temp += value;
	return temp;
} // end function StringOfChar

string IntToHex(const uint64_t value)
{
	stringstream ss;
	ss << hex << value;
	return Converters::toUpper(ss.str());
} // end function IntToHex

string lstrip(const string &str, const char value)
{
	register uint32_t s_pos = 0;
	for (register uint32_t i = 0; i < str.length(); i++, s_pos++)
	{
		if (str[i] != value) break;
	}// end if
	
	return str.substr(s_pos);
} // end lstrip

#endif // !TESTCONSTANTS_H

