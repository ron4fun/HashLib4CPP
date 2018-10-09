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

#define BOOST_TEST_MODULE ChecksumTestCase

#include "TestConstants.h"

// ====================== Adler32TestCase ======================
////////////////////
// Adler32
///////////////////
BOOST_AUTO_TEST_SUITE(Adler32TestCase)

string ExpectedHashOfEmptyData = "00000001";
string ExpectedHashOfDefaultData = "25D40524";
string ExpectedHashOfOnetoNine = "091E01DE";
string ExpectedHashOfabcde = "05C801F0";

IHash adler = HashLib4CPP::Checksum::CreateAdler32();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = adler->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = adler->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = adler->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = adler->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashLib4CPP::Checksum::CreateAdler32();
		
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
	string ActualString = adler->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== CRCTestCase ======================
////////////////////
// CRC
///////////////////
BOOST_AUTO_TEST_SUITE(CRCTestCase)

BOOST_AUTO_TEST_CASE(TestCheckValue)
{
	for (register uint32_t i = 0; i <= 100; i++)
	{
		ICRC crc = HashLib4CPP::Checksum::CreateCRC(CRCStandard(i));

		string ExpectedString = lstrip(IntToHex(crc->GetCheckValue()), '0');
		
		string ActualString = lstrip(crc->ComputeString(OnetoNine)->ToString(), '0');

		BOOST_CHECK(ExpectedString == ActualString);
	} // end for
}

BOOST_AUTO_TEST_CASE(TestCheckValueWithIncrementalHash)
{
	for (register uint32_t i = 0; i <= 100; i++)
	{
		ICRC crc = HashLib4CPP::Checksum::CreateCRC(CRCStandard(i));
		
		crc->Initialize();

		string ExpectedString = lstrip(IntToHex(crc->GetCheckValue()), '0');

		crc->TransformString(OnetoNine.substr(0, 3));
		crc->TransformString(OnetoNine.substr(3, 3));
		crc->TransformString(OnetoNine.substr(6));

		IHashResult res = crc->TransformFinal();

		string ActualString = lstrip(res->ToString(), '0');
		
		BOOST_CHECK(ExpectedString == ActualString);
	} // end for
}

BOOST_AUTO_TEST_SUITE_END()

