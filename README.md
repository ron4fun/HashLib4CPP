# HashLib4CPP [![License](http://img.shields.io/badge/license-MIT-green.svg)](https://github.com/ron4fun/HashLib4CPP/blob/master/LICENSE)
HashLib4CPP is a C++11 library that provides an easy to use interface for computing hashes and checksums of strings, files, streams, bytearrays and untyped data to mention but a few.
It also supports **Incremental Hashing**, **Cloning** and **NullDigest**.

**Supported Algorithms:**

    Non-Cryptographic 32-bits Hash Algorithms: AP, BKDR, Bernstein, Bernstein1, DEK, DJB, 
    ELF, FNV, FNV1a, JS, Jenkins3, Murmur2, MurmurHash3_x86_32, OneAtTime, PJW, RS, 
    Rotating, SDBM, ShiftAndXor, SuperFast, XXHash32.

    Non-Cryptographic 64-bits Algorithms: FNV, FNV1a, Murmur2_64, SipHash2_4, XXHash64.

    Non-Cryptographic 128-bits Algorithms: MurmurHash3_x86_128, MurmurHash3_x64_128. 

    Checksum Algorithms: Adler32, All CRC Variants from CRC3 to CRC64. 

    Cryptographic Algorithms: GOST, Grindahl, HAS160, Haval, MD2, MD4, MD5, Panama, 
    RadioGatun, RIPEMD, RIPEMD128, RIPEMD160, RIPEMD256, RIPEMD320, SHA0, SHA1, SHA2-224,
    SHA2-256, SHA2-384, SHA2-512, SHA2-512-224, SHA2-512-256, SHA3-224, SHA3-256, SHA3-384, 
    SHA3-512, Keccak-224, Keccak-256, Keccak-384, Keccak-512, Snefru128, Snefru256, Tiger,
	Tiger2, WhirlPool, Blake2B, Blake2S, Streebog (GOST3411_2012_256, GOST3411_2012_512).

    HMAC for any of the above.
    
    PBKDF2_HMAC for any of the above.

**Tested Enviroments:**
     
    Visual Studio 2015.
    Visual Studio 2017.

    
**Usage Examples.**

    #include "HashLib4CPP.h"

    int main()
    {
        IHash hash = HashLib4CPP::Crypto::CreateMD5();
			
        IHash clone = hash->Clone();

        IHMAC hmac = HashLib4CPP::HMAC::CreateHMAC(hash);
        hmac->SetKey(Converters::ConvertStringToBytes("password"));

        IHashResult Result1 = hash->ComputeString("Hash");
        IHashResult Result2 = hmac->ComputeString("Hash");
		
        bool check = Result1->CompareTo(Result2);
        
        return 0;
    }

 **Unit Tests:**
To run the unit tests, you should have [boost library](http://www.boost.org/) installed in your workstation.
For VisualStudio, set environment variable BOOST_ROOT to your boost root folder (where the bjam binary is)

###License

This "Software" is Licensed Under  **`MIT License (MIT)`** .

#### Tip Jar
* :dollar: **Bitcoin**: `1Mcci95WffSJnV6PsYG7KD1af1gDfUvLe6`


Conclusion
--------------------------------------------------

   Special thanks to [Xor-el](https://github.com/xor-el) for making this library available in the first place.
