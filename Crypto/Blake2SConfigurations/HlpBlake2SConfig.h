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

#ifndef HLPBLAKE2SCONFIG_H
#define HLPBLAKE2SCONFIG_H

#include "../Interfaces/IBlake2SConfigurations/HlpIBlake2SConfig.h"
#include "../Base/HlpHashSize.h"
#include "../Utils/HlpHashLibTypes.h"
#include "../Utils/HlpUtils.h"


class Blake2SConfig : public virtual IIBlake2SConfig
{
public:
	Blake2SConfig(const int32_t a_hash_size = HashSize::HashSize256) 
	{
		ValidateHashSize(a_hash_size);
		hash_size = a_hash_size;
	}

	virtual HashLibByteArray GetPersonalisation() const
	{
		return Personalisation;
	}

	virtual void SetPersonalisation(const HashLibByteArray &value)
	{
		ValidatePersonalisationLength(value);
		Personalisation = value;
	}
	
	virtual HashLibByteArray GetSalt() const
	{
		return Salt;
	}

	virtual void SetSalt(const HashLibByteArray &value)
	{
		ValidateSaltLength(value);
		Salt = value;
	}

	virtual HashLibByteArray GetKey() const
	{
		return Key;
	}

	virtual void SetKey(const HashLibByteArray &value)
	{
		ValidateKeyLength(value);
		Key = value;
	}

	virtual int32_t GetHashSize() const
	{
		return hash_size;
	}

	virtual void SetHashSize(const int32_t value)
	{
		ValidateHashSize(value);
		hash_size = value;
	}

private:
	inline void ValidateHashSize(const int32_t a_hash_size)
	{
		if (!(a_hash_size > 0 && a_hash_size <= 32) || ((a_hash_size * 8) & 7) != 0)
			throw ArgumentHashLibException(Utils::string_format(InvalidHashSize, a_hash_size));
	}

	inline void ValidateKeyLength(const HashLibByteArray &a_Key)
	{
		size_t KeyLength;
		
		if (!a_Key.empty())
		{
			KeyLength = a_Key.size();
			if (KeyLength > 32) 
				throw ArgumentOutOfRangeHashLibException(Utils::string_format(InvalidKeyLength, KeyLength));
		}

	}

	inline void ValidatePersonalisationLength(const HashLibByteArray &a_Personalisation)
	{
		size_t PersonalisationLength;

		if (!a_Personalisation.empty())
		{
			PersonalisationLength = a_Personalisation.size();
			if (PersonalisationLength != 8)
				throw ArgumentOutOfRangeHashLibException(Utils::string_format(InvalidPersonalisationLength, PersonalisationLength));
		}
	}

	inline void ValidateSaltLength(const HashLibByteArray &a_Salt)
	{
		size_t SaltLength;

		if (!a_Salt.empty())
		{
			SaltLength = a_Salt.size();
			if (SaltLength != 8)
				throw ArgumentOutOfRangeHashLibException(Utils::string_format(InvalidSaltLength, SaltLength));
		}
	}

private:
	int32_t hash_size;
	HashLibByteArray Personalisation, Salt, Key;

	static const char *InvalidHashSize;
	static const char *InvalidKeyLength;
	static const char *InvalidPersonalisationLength;
	static const char *InvalidSaltLength;

}; // end class Blake2SConfig


const char *Blake2SConfig::InvalidHashSize = "BLAKE2S HashSize must be restricted to one of the following [1 .. 32], \"%d\"";
const char *Blake2SConfig::InvalidKeyLength = "\"Key\" Length Must Not Be Greater Than 32, \"%d\"";
const char *Blake2SConfig::InvalidPersonalisationLength = "\"Personalisation\" Length Must Be Equal To 8, \"%d\"";
const char *Blake2SConfig::InvalidSaltLength = "\"Salt\" Length Must Be Equal To 8, \"%d\"";


#endif // !HLPBLAKE2SCONFIG_H