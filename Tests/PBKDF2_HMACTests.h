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

#define BOOST_TEST_MODULE PBKDF2_HMACTestCase

#include "TestConstants.h"


// ====================== PBKDF2_HMACSHA1TestCase ======================
////////////////////
// PBKDF2_HMACSHA1 
///////////////////
BOOST_AUTO_TEST_SUITE(PBKDF2_HMACSHA1TestCase)

string ExpectedString = "BFDE6BE94DF7E11DD409BCE20A0255EC327CB936FFE93643";
HashLibByteArray Password = { 0x70, 0x61, 0x73, 0x73, 0x77, 0x6F, 0x72, 0x64 };
HashLibByteArray Salt = { 0x78, 0x57, 0x8E, 0x5A, 0x5D, 0x63, 0xCB, 0x06 };
IHash hash = HashFactory::Crypto::CreateSHA1();

BOOST_AUTO_TEST_CASE(TestOne)
{
	IPBKDF2_HMAC PBKDF2 = HashFactory::PBKDF2_HMAC::CreatePBKDF2_HMAC(hash, Password, Salt, 2048);
	HashLibByteArray Key = PBKDF2->GetBytes(24);

	string ActualString = Converters::ConvertBytesToHexString(Key, false);
	BOOST_CHECK(ExpectedString == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== PBKDF2_HMACSHA2_256TestCase ======================
////////////////////
// PBKDF2_HMACSHA2_256 
///////////////////
BOOST_AUTO_TEST_SUITE(PBKDF2_HMACSHA2_256TestCase)

string ExpectedString = "0394A2EDE332C9A13EB82E9B24631604C31DF978B4E2F0FBD2C549944F9D79A5";
HashLibByteArray Password = Converters::ConvertStringToBytes("password");
HashLibByteArray Salt = Converters::ConvertStringToBytes("salt");
IHash hash = HashFactory::Crypto::CreateSHA2_256();

BOOST_AUTO_TEST_CASE(TestOne)
{
	HashLibByteArray Key = HashFactory::PBKDF2_HMAC::CreatePBKDF2_HMAC(hash, Password, Salt, 100000)->GetBytes(32);
	
	string ActualString = Converters::ConvertBytesToHexString(Key, false);
	BOOST_CHECK(ExpectedString == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()
