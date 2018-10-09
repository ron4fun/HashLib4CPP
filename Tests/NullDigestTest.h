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

#define BOOST_TEST_MODULE NullDigestFactoryTestCase

#include "TestConstants.h"


// ====================== NullDigestTestCase ======================
////////////////////
// NullDigest
///////////////////
BOOST_AUTO_TEST_SUITE(NullDigestTestCase)

IHash nullDigest = HashLib4CPP::NullDigestFactory::CreateNullDigest();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	HashLibByteArray BytesABCDE, Result;
	
	BytesABCDE = Converters::ConvertStringToBytes("abcde");
	BOOST_CHECK(-1 == nullDigest->GetBlockSize());
	BOOST_CHECK(-1 == nullDigest->GetHashSize());

	nullDigest->Initialize();

	BOOST_CHECK(0 == nullDigest->GetBlockSize());
	BOOST_CHECK(0 == nullDigest->GetHashSize());

	nullDigest->TransformBytes(BytesABCDE);

	BOOST_CHECK(0 == nullDigest->GetBlockSize());
	BOOST_CHECK(BytesABCDE.size() == nullDigest->GetHashSize());

	Result = nullDigest->TransformFinal()->GetBytes();

	BOOST_CHECK(0 == nullDigest->GetBlockSize());
	BOOST_CHECK(0 == nullDigest->GetHashSize());

	BOOST_CHECK(BytesABCDE == Result);
}

BOOST_AUTO_TEST_CASE(TestEmptyBytes)
{
	HashLibByteArray BytesEmpty, Result;
	
	nullDigest = HashLib4CPP::NullDigestFactory::CreateNullDigest();

	BytesEmpty = Converters::ConvertStringToBytes("");
	BOOST_CHECK(-1 == nullDigest->GetBlockSize());
	BOOST_CHECK(-1 == nullDigest->GetHashSize());

	nullDigest->Initialize();

	BOOST_CHECK(0 == nullDigest->GetBlockSize());
	BOOST_CHECK(0 == nullDigest->GetHashSize());

	nullDigest->TransformBytes(BytesEmpty);

	BOOST_CHECK(0 == nullDigest->GetBlockSize());
	BOOST_CHECK(BytesEmpty.size() == nullDigest->GetHashSize());

	Result = nullDigest->TransformFinal()->GetBytes();

	BOOST_CHECK(0 == nullDigest->GetBlockSize());
	BOOST_CHECK(0 == nullDigest->GetHashSize());

	BOOST_CHECK(BytesEmpty == Result);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	HashLibByteArray BytesZeroToNine, Result;
	HashLibByteArray::const_iterator start, end;

	nullDigest = HashLib4CPP::NullDigestFactory::CreateNullDigest();

	BytesZeroToNine = Converters::ConvertStringToBytes("0123456789");
	BOOST_CHECK(-1 == nullDigest->GetBlockSize());
	BOOST_CHECK(-1 == nullDigest->GetHashSize());

	nullDigest->Initialize();

	BOOST_CHECK(0 == nullDigest->GetBlockSize());
	BOOST_CHECK(0 == nullDigest->GetHashSize());

	start = BytesZeroToNine.begin();
	end = start + 4;

	nullDigest->TransformBytes(HashLibByteArray(start, end));

	BOOST_CHECK(0 == nullDigest->GetBlockSize());
	BOOST_CHECK(4 == nullDigest->GetHashSize());

	start = BytesZeroToNine.begin() + 4;
	end = start + 6;

	nullDigest->TransformBytes(HashLibByteArray(start, end));

	BOOST_CHECK(0 == nullDigest->GetBlockSize());
	BOOST_CHECK(10 == nullDigest->GetHashSize());

	Result = nullDigest->TransformFinal()->GetBytes();

	BOOST_CHECK(0 == nullDigest->GetBlockSize());
	BOOST_CHECK(0 == nullDigest->GetHashSize());

	BOOST_CHECK(BytesZeroToNine == Result);
}

BOOST_AUTO_TEST_CASE(TestHashCloneIsCorrect)
{
	nullDigest = HashLib4CPP::NullDigestFactory::CreateNullDigest();

	HashCloneIsCorrectTestHelper(nullDigest);
}

BOOST_AUTO_TEST_CASE(TestHashCloneIsUnique)
{
	nullDigest = HashLib4CPP::NullDigestFactory::CreateNullDigest();

	HashCloneIsUnique(nullDigest);
}

BOOST_AUTO_TEST_SUITE_END()