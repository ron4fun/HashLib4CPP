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

#ifndef HLPIHASHINFO_H
#define HLPIHASHINFO_H

#include "HlpIHash.h"
#include "HlpIKDF.h"
#include "../Nullable/HlpNullable.h"

class IITransformBlock
{}; // end class ITransformBlock

typedef shared_ptr<IITransformBlock> ITransformBlock;

class IIBlockHash : public virtual IIHash
{}; // end class IBlockHash

typedef shared_ptr<IIBlockHash> IBlockHash;

class IINonBlockHash
{}; // end class INonBlockHash

typedef shared_ptr<IINonBlockHash> INonBlockHash;

class IIChecksum
{}; // end class IChecksum

typedef shared_ptr<IIChecksum> IChecksum;

class IICrypto : public IIBlockHash
{}; // end class ICrypto

typedef shared_ptr<IICrypto> ICrypto;

class IICryptoNotBuildIn : public virtual IICrypto
{}; // end class ICryptoNotBuildIn

typedef shared_ptr<IICryptoNotBuildIn> ICryptoNotBuildIn;

class IIWithKey : public virtual IIHash
{
public:
	virtual HashLibByteArray GetKey() const = 0;
	virtual void SetKey(const HashLibByteArray &value) = 0;
	virtual NullableInteger GetKeyLength() const = 0;

}; // end class IWithKey

typedef shared_ptr<IIWithKey> IWithKey;

class IIPBKDF2_HMAC : public virtual IIKDF
{}; // end class IPBKDF2_HMAC

typedef shared_ptr<IIPBKDF2_HMAC> IPBKDF2_HMAC;

class IIPBKDF2_HMACNotBuildIn : public IIPBKDF2_HMAC
{}; // end class IPBKDF2_HMACNotBuildIn

typedef shared_ptr<IIPBKDF2_HMACNotBuildIn> IPBKDF2_HMACNotBuildIn;

class IIHMAC;

typedef shared_ptr<IIHMAC> IHMAC;

class IIHMAC : public virtual IIWithKey
{
public:
	virtual IHMAC CloneHMAC() const = 0;

}; // end class IHMAC

class IIHMACNotBuildIn : public virtual IIHMAC
{}; // end class IHMACNotBuildIn

typedef shared_ptr<IIHMACNotBuildIn> IHMACNotBuildIn;

class IIHash16 : public virtual IIHash
{}; // end class IHash16

typedef shared_ptr<IIHash16> IHash16;

class IIHash32 : public virtual IIHash
{}; // end class IHash32

typedef shared_ptr<IIHash32> IHash32;

class IIHash64 : public virtual IIHash
{}; // end class IHash64

typedef shared_ptr<IIHash64> IHash64;

class IIHash128 : public virtual IIHash
{}; // end class IHash128

typedef shared_ptr<IIHash128> IHash128;

class IIHashWithKey : public IIWithKey
{}; // end class IHashWithKey

typedef shared_ptr<IIHashWithKey> IHashWithKey;

#endif // !HLPIHASHINFO_H
