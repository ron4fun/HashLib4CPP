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


