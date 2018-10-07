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

#ifndef HLPHMACNOTBUILDINADAPTER_H
#define HLPHMACNOTBUILDINADAPTER_H

#include <sstream>
#include "HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"


class HMACNotBuildInAdapter : public Hash, public virtual IIHMAC, public IIHMACNotBuildIn, 
	public virtual IIWithKey, public virtual IICrypto, public IICryptoNotBuildIn
{
public:
	HMACNotBuildInAdapter(IHash a_underlyingHash)
		: Hash(a_underlyingHash->GetHashSize(), a_underlyingHash->GetBlockSize())
	{
		name = __func__;

		hash = ::move(a_underlyingHash);
		blocksize = hash->GetBlockSize();
		key = make_shared<HashLibByteArray>(0);
		ipad = make_shared<HashLibByteArray>(blocksize);
		opad = make_shared<HashLibByteArray>(blocksize);
	} // end constructor

	~HMACNotBuildInAdapter()
	{} // end destructor

	virtual IHMAC CloneHMAC() const
	{
		HMACNotBuildInAdapter hmac = HMACNotBuildInAdapter(hash->Clone());
		hmac.blocksize = blocksize;
		hmac.opad = opad;
		hmac.ipad = ipad;
		hmac.key = key;

		return make_shared<HMACNotBuildInAdapter>(hmac);
	}

	virtual void Initialize()
	{
		hash->Initialize();
		UpdatePads();
		hash->TransformBytes(*ipad);
	} // end function Initialize

	virtual IHashResult TransformFinal()
	{
		IHashResult result = hash->TransformFinal();
		hash->TransformBytes(*opad);
		hash->TransformBytes(result->GetBytes());
		result = hash->TransformFinal();
		Initialize();

		return result;
	} // end function TransformFinal

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		hash->TransformBytes(a_data, a_index, a_length);
	} // end function TransformBytes

protected:
	virtual string GetName() const
	{
		stringstream ss;
		ss << name << "(" << hash->GetName() << ")";

		return ss.str();
	} // end function GetName

	virtual HashLibByteArray GetKey() const
	{
		return *key;
	} // end function GetKey

	virtual NullableInteger GetKeyLength() const
	{
		return NullableInteger();
	} // end function GetKeyLength

	virtual void SetKey(const HashLibByteArray &value)
	{
		if (value.empty())
			key->clear();
		else
			*key = value;
	} // end function SetKey

	void UpdatePads()
	{
		HashLibByteArray LKey;
		register int32_t Idx;

		if (key->size() > blocksize)
		{
			LKey = hash->ComputeBytes(*key)->GetBytes();
		} // end if
		else
		{
			LKey = *key;
		} // end else

		
		memset(&(*ipad)[0], 0x36, blocksize * sizeof(uint8_t));
		memset(&(*opad)[0], 0x5C, blocksize * sizeof(uint8_t));

		Idx = 0;
		while ((Idx < int32_t(LKey.size())) && (Idx < blocksize))
		{
			(*ipad)[Idx] = (*ipad)[Idx] ^ LKey[Idx];
			(*opad)[Idx] = (*opad)[Idx] ^ LKey[Idx];
			Idx++;
		} // end while
	} // end function UpdatePads

private:
	IHash hash;
	shared_ptr<HashLibByteArray> opad, ipad, key;
	int32_t blocksize;

}; // end class HMACNotBuildInAdapter


#endif // !HLPHMACNOTBUILDINADAPTER_H