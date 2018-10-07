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

    string MurMur3Data = "HashLib4Pascal012345678HashLib4Pascal012345678HashLib4Pascal012345678HashLib4Pascal012345678";
    string MurMur3ExpectedResult = "380BB6EFADE13DFBA82A58BE1BBC60E9";
    int i;

    int c_chunkSize[] = { 1,         //Test many chunk of < sizeof(int128)
                         2,          //Test many chunk of < sizeof(int128)
                         29,         //Test many chunk of < sizeof(int128)
                         30,         //Test many chunk of = sizeof(int128)
                         31,         //Test many chunk of > sizeof(int128)
                         32,         //Test many chunk of > sizeof(int128)
                         33,         //Test many chunk of > sizeof(int128)
                         34,         //Test many chunk of > sizeof(int128)
                         29 * 2,     //Test many chunk of < sizeof(int128)*2
                         30 * 2,     //Test many chunk of = sizeof(int128)*2
                         31 * 2,     //Test many chunk of > sizeof(int128)*2
                         32 * 2,     //Test many chunk of > sizeof(int128)*2
                         33 * 2,     //Test many chunk of > sizeof(int128)*2
                         34 * 2 };   //Test many chunk of > sizeof(int128)*2
    
    for(int x = 0; x < sizeof(c_chunkSize)/sizeof(int); x++)
    {         
        int size = c_chunkSize[x];
	    hash->Initialize();
        for(i=size; i < MurMur3Data.length(); i += size)
	        hash->TransformString(MurMur3Data.substr(i-size, size));
	    hash->TransformString(MurMur3Data.substr(i-size));

        string ActualString = hash->TransformFinal()->ToString();
	    BOOST_CHECK(MurMur3ExpectedResult == ActualString);
    }

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

BOOST_AUTO_TEST_CASE(TestAnotherChunkedDataIncrementalHash)
{
	register size_t x, size, i;
	string temp;

	for (x = 0; x < (sizeof(chunkSize) / sizeof(int32_t)); x++)
	{
		size = chunkSize[x];
		murmurhash3_x64_128->Initialize();
		i = size;
		while (i < ChunkedData.size())
		{
			temp = ChunkedData.substr((i - size), size);
			murmurhash3_x64_128->TransformString(temp);

			i += size;
		}

		temp = ChunkedData.substr((i - size), ChunkedData.size() - ((i - size)));
		murmurhash3_x64_128->TransformString(temp);

		string ActualString = murmurhash3_x64_128->TransformFinal()->ToString();
		string ExpectedString = HashFactory::Hash128::CreateMurmurHash3_x64_128()
			->ComputeString(ChunkedData)->ToString();

		BOOST_CHECK(ExpectedString == ActualString, Utils::string_format("Expected %s but got %s.", ExpectedString, ActualString));
	}

}

BOOST_AUTO_TEST_CASE(TestIndexChunkedDataIncrementalHash)
{
	register size_t Count, i;
	HashLibByteArray temp, ChunkedDataBytes;

	ChunkedDataBytes = Converters::ConvertStringToBytes(ChunkedData);
	for (i = 0; i < ChunkedDataBytes.size(); i++)
	{
		Count = ChunkedDataBytes.size() - i;

		const HashLibByteArray::const_iterator start = ChunkedDataBytes.begin() + i;
		const HashLibByteArray::const_iterator end = ChunkedDataBytes.end();

		temp = HashLibByteArray(start, end);
		murmurhash3_x64_128->Initialize();

		murmurhash3_x64_128->TransformBytes(ChunkedDataBytes, i, Count);

		string ActualString = murmurhash3_x64_128->TransformFinal()->ToString();
		string ExpectedString = HashFactory::Hash128::CreateMurmurHash3_x64_128()
												->ComputeBytes(temp)->ToString();
		
		BOOST_CHECK(ExpectedString == ActualString, Utils::string_format("Expected %s but got %s.", ExpectedString, ActualString));
	}

}

BOOST_AUTO_TEST_CASE(TestHashCloneIsCorrect)
{
	IHash hash = HashFactory::Hash128::CreateMurmurHash3_x64_128();

	HashCloneIsCorrectTestHelper(hash);
}

BOOST_AUTO_TEST_CASE(TestHashCloneIsUnique)
{
	IHash hash = HashFactory::Hash128::CreateMurmurHash3_x64_128();

	HashCloneIsUnique(hash);
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

    string MurMur3Data = "HashLib4Pascal012345678HashLib4Pascal012345678HashLib4Pascal012345678HashLib4Pascal012345678";
    string MurMur3ExpectedResult = "CE383F71F9B801A4C03634DAB47ACC7A";
    int i;

    int c_chunkSize[] = { 1,         //Test many chunk of < sizeof(int128)
                         2,          //Test many chunk of < sizeof(int128)
                         29,         //Test many chunk of < sizeof(int128)
                         30,         //Test many chunk of = sizeof(int128)
                         31,         //Test many chunk of > sizeof(int128)
                         32,         //Test many chunk of > sizeof(int128)
                         33,         //Test many chunk of > sizeof(int128)
                         34,         //Test many chunk of > sizeof(int128)
                         29 * 2,     //Test many chunk of < sizeof(int128)*2
                         30 * 2,     //Test many chunk of = sizeof(int128)*2
                         31 * 2,     //Test many chunk of > sizeof(int128)*2
                         32 * 2,     //Test many chunk of > sizeof(int128)*2
                         33 * 2,     //Test many chunk of > sizeof(int128)*2
                         34 * 2 };   //Test many chunk of > sizeof(int128)*2
    
    for(int x = 0; x < sizeof(c_chunkSize)/sizeof(int); x++)
    {         
        int size = c_chunkSize[x];
	    hash->Initialize();
        for(i=size; i < MurMur3Data.length(); i += size)
	        hash->TransformString(MurMur3Data.substr(i-size, size));
	    hash->TransformString(MurMur3Data.substr(i-size));

        string ActualString = hash->TransformFinal()->ToString();
	    BOOST_CHECK(MurMur3ExpectedResult == ActualString);
    }
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

BOOST_AUTO_TEST_CASE(TestAnotherChunkedDataIncrementalHash)
{
	register size_t x, size, i;
	string temp;

	for (x = 0; x < (sizeof(chunkSize) / sizeof(int32_t)); x++)
	{
		size = chunkSize[x];
		murmurhash3_x86_128->Initialize();
		i = size;
		while (i < ChunkedData.size())
		{
			temp = ChunkedData.substr((i - size), size);
			murmurhash3_x86_128->TransformString(temp);

			i += size;
		}

		temp = ChunkedData.substr((i - size), ChunkedData.size() - ((i - size)));
		murmurhash3_x86_128->TransformString(temp);

		string ActualString = murmurhash3_x86_128->TransformFinal()->ToString();
		string ExpectedString = HashFactory::Hash128::CreateMurmurHash3_x86_128()
			->ComputeString(ChunkedData)->ToString();

		BOOST_CHECK(ExpectedString == ActualString, Utils::string_format("Expected %s but got %s.", ExpectedString, ActualString));
	}

}

BOOST_AUTO_TEST_CASE(TestIndexChunkedDataIncrementalHash)
{
	register size_t Count, i;
	HashLibByteArray temp, ChunkedDataBytes;

	ChunkedDataBytes = Converters::ConvertStringToBytes(ChunkedData);
	for (i = 0; i < ChunkedDataBytes.size(); i++)
	{
		Count = ChunkedDataBytes.size() - i;

		const HashLibByteArray::const_iterator start = ChunkedDataBytes.begin() + i;
		const HashLibByteArray::const_iterator end = ChunkedDataBytes.end();

		temp = HashLibByteArray(start, end);
		murmurhash3_x86_128->Initialize();

		murmurhash3_x86_128->TransformBytes(ChunkedDataBytes, i, Count);

		string ActualString = murmurhash3_x86_128->TransformFinal()->ToString();
		string ExpectedString = HashFactory::Hash128::CreateMurmurHash3_x86_128()
			->ComputeBytes(temp)->ToString();

		BOOST_CHECK(ExpectedString == ActualString, Utils::string_format("Expected %s but got %s.", ExpectedString, ActualString));
	}

}

BOOST_AUTO_TEST_CASE(TestHashCloneIsCorrect)
{
	IHash hash = HashFactory::Hash128::CreateMurmurHash3_x86_128();

	HashCloneIsCorrectTestHelper(hash);
}

BOOST_AUTO_TEST_CASE(TestHashCloneIsUnique)
{
	IHash hash = HashFactory::Hash128::CreateMurmurHash3_x86_128();

	HashCloneIsUnique(hash);
}

BOOST_AUTO_TEST_SUITE_END()
