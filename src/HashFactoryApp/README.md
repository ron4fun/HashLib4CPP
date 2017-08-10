# HashLib4CPP
HashLib4CPP is a C++ library that provides an easy to use interface for computing hashes and checksums of strings, files, streams, bytearrays and untyped data to mention but a few.
It also supports Incremental Hashing.

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
    SHA3-512,Snefru128, Snefru256, Tiger, Tiger2, WhirlPool.

    HMAC for any of the above.
    
    PBKDF2_HMAC for any of the above.

**Tested Compilers:**
     
    Visual Studio 2015.

    
**Usage Examples.**

    #include "stdafx.h"
    #include "Base\HlpHashFactory.h"

    int main()
    {
        IHash hash = HashFactory::Crypto::CreateMD5();
        IHMAC hmac = HashFactory::HMAC::CreateHMAC(hash);
        hmac->SetKey(Converters::ConvertStringToBytes("password"));

        IHashResult Result1 = hash->ComputeString("Hash");
        IHashResult Result2 = hmac->ComputeString("Hash");
		
        bool check = Result1->CompareTo(Result2);
        
        return 0;
    }

 **Unit Tests:**
To run the unit tests, you should have [boost library](http://www.boost.org/) installed in your workstation.


###License

This "Software" is Licensed Under  **`MIT License (MIT)`** .