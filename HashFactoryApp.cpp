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

#include "stdafx.h"
#include <iostream>
//#include "Tests\CryptoTests.h"
//#include "Tests\ChecksumTests.h"
//#include "Tests\Hash32Tests.h"
//#include "Tests\Hash64Tests.h"
//#include "Tests\Hash128Tests.h"
//#include "Tests\PBKDF2_HMACTests.h"
#include "Base\HlpHashFactory.h"

int main()
{
	IHash hash = HashFactory::Crypto::CreateMD5();
	IHMAC hmac = HashFactory::HMAC::CreateHMAC(hash);
	hmac->SetKey(Converters::ConvertStringToBytes("password"));

	IHashResult Result1 = hash->ComputeString("Hash");
	IHashResult Result2 = hmac->ComputeString("Hash");
	IHashResult Result3 = hmac->ComputeBytes(Converters::ConvertStringToBytes("Hash"));

	bool check = Result1->CompareTo(Result3);

    return 0;
}


