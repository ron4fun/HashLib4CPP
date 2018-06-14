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

#define BOOST_TEST_MODULE Hash64TestCase

#include "TestConstants.h"


// ====================== FNV64TestCase ======================
////////////////////
// FNV64
///////////////////
BOOST_AUTO_TEST_SUITE(FNV64TestCase)

string ExpectedHashOfEmptyData = "0000000000000000";
string ExpectedHashOfDefaultData = "061A6856F5925B83";
string ExpectedHashOfOnetoNine = "B8FB573C21FE68F1";
string ExpectedHashOfabcde = "77018B280326F529";

IHash fnv = HashFactory::Hash64::CreateFNV();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = fnv->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = fnv->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = fnv->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = fnv->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash64::CreateFNV();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = fnv->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== FNV1a64TestCase ======================
////////////////////
// FNV1a64
///////////////////
BOOST_AUTO_TEST_SUITE(FNV1a64TestCase)

string ExpectedHashOfEmptyData = "CBF29CE484222325";
string ExpectedHashOfDefaultData = "5997E22BF92B0598";
string ExpectedHashOfOnetoNine = "06D5573923C6CDFC";
string ExpectedHashOfabcde = "6348C52D762364A8";

IHash fnv1a = HashFactory::Hash64::CreateFNV1a();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = fnv1a->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = fnv1a->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = fnv1a->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = fnv1a->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash64::CreateFNV1a();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = fnv1a->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== Murmur2_64TestCase ======================
////////////////////
// Murmur2_64
///////////////////
BOOST_AUTO_TEST_SUITE(Murmur2_64TestCase)

string ExpectedHashOfEmptyData = "0000000000000000";
string ExpectedHashOfDefaultData = "F78F3AF068158F5A";
string ExpectedHashOfOnetoNine = "F22BE622518FAF39";
string ExpectedHashOfabcde = "AF7BA284707E90C2";
string ExpectedHashOfDefaultDataWithMaxUInt32AsKey = "49F2E215E924B552";

IHash murmur2 = HashFactory::Hash64::CreateMurmur2();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = murmur2->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = murmur2->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = murmur2->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = murmur2->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash64::CreateMurmur2();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = murmur2->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKey)
{
	IHashWithKey HashWithKey = HashFactory::Hash64::CreateMurmur2();
	HashWithKey->SetKey(Converters::ReadUInt32AsBytesLE(uint32_t(-1)));

	string ActualString = HashWithKey->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultDataWithMaxUInt32AsKey == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== SipHash2_4TestCase ======================
////////////////////
// SipHash2_4
///////////////////
BOOST_AUTO_TEST_SUITE(SipHash2_4TestCase)

string ExpectedHashOfEmptyData = "726FDB47DD0E0E31";
string ExpectedHashOfDefaultData = "AA43C4288619D24E";
string ExpectedHashOfOnetoNine = "CA60FC96020EFEFD";
string ExpectedHashOfabcde = "A74563E1EA79B873";
string ExpectedHashOfShortMessage = "AE43DFAED1AB1C00";

IHash siphash2_4 = HashFactory::Hash64::CreateSipHash2_4();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = siphash2_4->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = siphash2_4->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = siphash2_4->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = siphash2_4->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash64::CreateSipHash2_4();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = siphash2_4->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_CASE(TestShortMessage)
{
	string ActualString = siphash2_4->ComputeString(ShortMessage)->ToString();
	BOOST_CHECK(ExpectedHashOfShortMessage == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithOutsideKey)
{
	IHashWithKey HashWithKey = HashFactory::Hash64::CreateSipHash2_4();
	HashWithKey->SetKey(Converters::ConvertHexStringToBytes(HexStringAsKey));

	string ActualString = HashWithKey->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== XXHash64TestCase ======================
////////////////////
// XXHash64
///////////////////
BOOST_AUTO_TEST_SUITE(XXHash64TestCase)

string ExpectedHashOfEmptyData = "EF46DB3751D8E999";
string ExpectedHashOfDefaultData = "0F1FADEDD0B77861";
string ExpectedHashOfRandomString = "C9C17BCD07584404";
string ExpectedHashOfZerotoFour = "34CB4C2EE6166F65";
string ExpectedHashOfEmptyDataWithOneAsKey = "D5AFBA1336A3BE4B";
string ExpectedHashOfDefaultDataWithMaxUInt64AsKey = "68DCC1056096A94F";

IHash xxhash64 = HashFactory::Hash64::CreateXXHash64();

BOOST_AUTO_TEST_CASE(TestRandomString)
{
	string ActualString = xxhash64->ComputeString(RandomStringTobacco)->ToString();
	BOOST_CHECK(ExpectedHashOfRandomString == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = xxhash64->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = xxhash64->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = xxhash64->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash64::CreateXXHash64();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestZerotoFour)
{
	string ActualString = xxhash64->ComputeString(ZerotoFour)->ToString();
	BOOST_CHECK(ExpectedHashOfZerotoFour == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKeyMaxUInt64DefaultData)
{
	IHashWithKey HashWithKey = HashFactory::Hash64::CreateXXHash64();
	HashWithKey->SetKey(Converters::ReadUInt64AsBytesLE(uint64_t(-1)));

	string ActualString = HashWithKey->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultDataWithMaxUInt64AsKey == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKeyOneEmptyString)
{
	IHashWithKey HashWithKey = HashFactory::Hash64::CreateXXHash64();
	HashWithKey->SetKey(Converters::ReadUInt64AsBytesLE(uint64_t(1)));

	string ActualString = HashWithKey->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyDataWithOneAsKey == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()