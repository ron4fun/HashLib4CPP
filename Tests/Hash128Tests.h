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

#define BOOST_TEST_MODULE Hash128TestCase

#include "TestConstants.h"


// ====================== MurmurHash3_x64_128TestCase ======================
////////////////////
// MurmurHash3_x64_128
///////////////////
BOOST_AUTO_TEST_SUITE(MurmurHash3_x64_128TestCase)

string ExpectedHashOfEmptyData = "00000000000000000000000000000000";
string ExpectedHashOfDefaultData = "705BD3C954B94BE056F06B68662E6364";
string ExpectedHashOfRandomString = "D30654ABBD8227E367D73523F0079673";
string ExpectedHashOfZerotoFour = "0F04E459497F3FC1ECCC6223A28DD613";
string ExpectedHashOfEmptyDataWithOneAsKey = "4610ABE56EFF5CB551622DAA78F83583";
string ExpectedHashOfDefaultDataWithMaxUInt32AsKey = "ADFD14988FB1F8582A1B67C1BBACC218";

IHash murmurhash3_x64_128 = HashFactory::Hash128::CreateMurmurHash3_x64_128();

BOOST_AUTO_TEST_CASE(TestRandomString)
{
	string ActualString = murmurhash3_x64_128->ComputeString(RandomStringTobacco)->ToString();
	BOOST_CHECK(ExpectedHashOfRandomString == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = murmurhash3_x64_128->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = murmurhash3_x64_128->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = murmurhash3_x64_128->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash128::CreateMurmurHash3_x64_128();

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
	string ActualString = murmurhash3_x64_128->ComputeString(ZerotoFour)->ToString();
	BOOST_CHECK(ExpectedHashOfZerotoFour == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKeyMaxUInt32DefaultData)
{
	IHashWithKey HashWithKey = HashFactory::Hash128::CreateMurmurHash3_x64_128();
	HashWithKey->SetKey(Converters::ReadUInt32AsBytesLE(uint32_t(-1)));

	string ActualString = HashWithKey->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultDataWithMaxUInt32AsKey == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKeyOneEmptyString)
{
	IHashWithKey HashWithKey = HashFactory::Hash128::CreateMurmurHash3_x64_128();
	HashWithKey->SetKey(Converters::ReadUInt32AsBytesLE(uint32_t(1)));

	string ActualString = HashWithKey->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyDataWithOneAsKey == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== MurmurHash3_x86_128TestCase ======================
////////////////////
// MurmurHash3_x86_128
///////////////////
BOOST_AUTO_TEST_SUITE(MurmurHash3_x86_128TestCase)

string ExpectedHashOfEmptyData = "00000000000000000000000000000000";
string ExpectedHashOfDefaultData = "B35E1058738E067BF637B17075F14B8B";
string ExpectedHashOfRandomString = "9B5B7BA2EF3F7866889ADEAF00F3F98E";
string ExpectedHashOfZerotoFour = "35C5B3EE7B3B211600AE108800AE1088";
string ExpectedHashOfEmptyDataWithOneAsKey = "88C4ADEC54D201B954D201B954D201B9";
string ExpectedHashOfDefaultDataWithMaxUInt32AsKey = "55315FA9E8129C7390C080B8FDB1C972";

IHash murmurhash3_x86_128 = HashFactory::Hash128::CreateMurmurHash3_x86_128();

BOOST_AUTO_TEST_CASE(TestRandomString)
{
	string ActualString = murmurhash3_x86_128->ComputeString(RandomStringTobacco)->ToString();
	BOOST_CHECK(ExpectedHashOfRandomString == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = murmurhash3_x86_128->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = murmurhash3_x86_128->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = murmurhash3_x86_128->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash128::CreateMurmurHash3_x86_128();

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
	string ActualString = murmurhash3_x86_128->ComputeString(ZerotoFour)->ToString();
	BOOST_CHECK(ExpectedHashOfZerotoFour == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKeyMaxUInt32DefaultData)
{
	IHashWithKey HashWithKey = HashFactory::Hash128::CreateMurmurHash3_x86_128();
	HashWithKey->SetKey(Converters::ReadUInt32AsBytesLE(uint32_t(-1)));

	string ActualString = HashWithKey->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultDataWithMaxUInt32AsKey == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKeyOneEmptyString)
{
	IHashWithKey HashWithKey = HashFactory::Hash128::CreateMurmurHash3_x86_128();
	HashWithKey->SetKey(Converters::ReadUInt32AsBytesLE(uint32_t(1)));

	string ActualString = HashWithKey->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyDataWithOneAsKey == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()
