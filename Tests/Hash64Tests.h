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

IHash fnv = HashLib4CPP::Hash64::CreateFNV();

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
	IHash hash = HashLib4CPP::Hash64::CreateFNV();

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

BOOST_AUTO_TEST_CASE(TestHashCloneIsCorrect)
{
	IHash hash = HashLib4CPP::Hash64::CreateFNV();

	HashCloneIsCorrectTestHelper(hash);
}

BOOST_AUTO_TEST_CASE(TestHashCloneIsUnique)
{
	IHash hash = HashLib4CPP::Hash64::CreateFNV();

	HashCloneIsUnique(hash);
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

IHash fnv1a = HashLib4CPP::Hash64::CreateFNV1a();

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
	IHash hash = HashLib4CPP::Hash64::CreateFNV1a();

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

BOOST_AUTO_TEST_CASE(TestHashCloneIsCorrect)
{
	IHash hash = HashLib4CPP::Hash64::CreateFNV1a();

	HashCloneIsCorrectTestHelper(hash);
}

BOOST_AUTO_TEST_CASE(TestHashCloneIsUnique)
{
	IHash hash = HashLib4CPP::Hash64::CreateFNV1a();

	HashCloneIsUnique(hash);
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

IHash murmur2 = HashLib4CPP::Hash64::CreateMurmur2();

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
	IHash hash = HashLib4CPP::Hash64::CreateMurmur2();

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
	IHashWithKey HashWithKey = HashLib4CPP::Hash64::CreateMurmur2();
	HashWithKey->SetKey(Converters::ReadUInt32AsBytesLE(uint32_t(-1)));

	string ActualString = HashWithKey->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultDataWithMaxUInt32AsKey == ActualString);
}

BOOST_AUTO_TEST_CASE(TestHashCloneIsCorrect)
{
	IHash hash = HashLib4CPP::Hash64::CreateMurmur2();

	HashCloneIsCorrectTestHelper(hash);
}

BOOST_AUTO_TEST_CASE(TestHashCloneIsUnique)
{
	IHash hash = HashLib4CPP::Hash64::CreateMurmur2();

	HashCloneIsUnique(hash);
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

IHash siphash2_4 = HashLib4CPP::Hash64::CreateSipHash2_4();

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
	IHash hash = HashLib4CPP::Hash64::CreateSipHash2_4();
	string SipHashData = "HashLib4Pascal012345678";
	string SipHashExpectedResult = "17D7F70CD2C5EBBC";
	int i;

	int c_chunkSize[] = { 1,     //Test many chunk of < sizeof(int)
		2, // Test many chunk of < sizeof(int)
		3, // Test many chunk of < sizeof(int)
		4, // Test many chunk of = sizeof(int)
		5, // Test many chunk of > sizeof(int)
		6, // Test many chunk of > sizeof(int)
		7, // Test many chunk of > sizeof(int)
		8, // Test many chunk of > 2*sizeof(int)
		9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
		28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
		46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
		64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81,
		82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
		100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
		115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
		130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
		145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
		160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174,
		175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189,
		190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204,
		205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
		220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234,
		235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249,
		250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260 
	}; 

	for (int x = 0; x < sizeof(c_chunkSize) / sizeof(int); x++)
	{
		int size = c_chunkSize[x];
		hash->Initialize();
		for (i = size; i < SipHashData.length(); i += size)
			hash->TransformString(SipHashData.substr(i - size, size));
		hash->TransformString(SipHashData.substr(i - size));

		string ActualString = hash->TransformFinal()->ToString();
		BOOST_CHECK(SipHashExpectedResult == ActualString);
	}
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
	IHashWithKey HashWithKey = HashLib4CPP::Hash64::CreateSipHash2_4();
	HashWithKey->SetKey(Converters::ConvertHexStringToBytes(HexStringAsKey));

	string ActualString = HashWithKey->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestAnotherChunkedDataIncrementalHash)
{
	register size_t x, size, i;
	string temp;

	for (x = 0; x < (sizeof(chunkSize) / sizeof(int32_t)); x++)
	{
		size = chunkSize[x];
		siphash2_4->Initialize();
		i = size;
		while (i < ChunkedData.size())
		{
			temp = ChunkedData.substr((i - size), size);
			siphash2_4->TransformString(temp);

			i += size;
		}

		temp = ChunkedData.substr((i - size), ChunkedData.size() - ((i - size)));
		siphash2_4->TransformString(temp);

		string ActualString = siphash2_4->TransformFinal()->ToString();
		string ExpectedString = HashLib4CPP::Hash64::CreateSipHash2_4()
			->ComputeString(ChunkedData)->ToString();

		BOOST_CHECK(ExpectedString == ActualString, Utils::string_format("Expected %s but got %s.", ExpectedString, ActualString));
	}

}

BOOST_AUTO_TEST_CASE(TestHashCloneIsCorrect)
{
	IHash hash = HashLib4CPP::Hash64::CreateSipHash2_4();

	HashCloneIsCorrectTestHelper(hash);
}

BOOST_AUTO_TEST_CASE(TestHashCloneIsUnique)
{
	IHash hash = HashLib4CPP::Hash64::CreateSipHash2_4();

	HashCloneIsUnique(hash);
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

IHash xxhash64 = HashLib4CPP::Hash64::CreateXXHash64();

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
	IHash hash = HashLib4CPP::Hash64::CreateXXHash64();

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
	IHashWithKey HashWithKey = HashLib4CPP::Hash64::CreateXXHash64();
	HashWithKey->SetKey(Converters::ReadUInt64AsBytesLE(uint64_t(-1)));

	string ActualString = HashWithKey->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultDataWithMaxUInt64AsKey == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKeyOneEmptyString)
{
	IHashWithKey HashWithKey = HashLib4CPP::Hash64::CreateXXHash64();
	HashWithKey->SetKey(Converters::ReadUInt64AsBytesLE(uint64_t(1)));

	string ActualString = HashWithKey->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyDataWithOneAsKey == ActualString);
}

BOOST_AUTO_TEST_CASE(TestHashCloneIsCorrect)
{
	IHash hash = HashLib4CPP::Hash64::CreateXXHash64();

	HashCloneIsCorrectTestHelper(hash);
}

BOOST_AUTO_TEST_CASE(TestHashCloneIsUnique)
{
	IHash hash = HashLib4CPP::Hash64::CreateXXHash64();

	HashCloneIsUnique(hash);
}

BOOST_AUTO_TEST_SUITE_END()