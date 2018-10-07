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

#ifndef HLPBLAKE2SLVBUILDER_H
#define HLPBLAKE2SLVBUILDER_H

#include "../Interfaces/IBlake2SConfigurations/HlpIBlake2SConfig.h"
#include "Blake2SConfigurations\HlpBlake2STreeConfig.h"
#include "../Base/HlpHashSize.h"
#include "../Base/HlpConverters.h"
#include "../Utils/HlpHashLibTypes.h"
#include "../Utils/HlpUtils.h"


class Blake2SIvBuilder
{
public:
	static HashLibUInt32Array ConfigS(const IBlake2SConfig config, const IBlake2STreeConfig treeConfig)
	{
		bool isSequential;
		HashLibUInt32Array rawConfig;
		IBlake2STreeConfig LtreeConfig;
		
		LtreeConfig = treeConfig;
		isSequential = !LtreeConfig;
		if (isSequential) 
			LtreeConfig = SequentialTreeConfig;
		
		rawConfig.resize(8);

		// digest length
		if ((config->GetHashSize() <= 0) || (config->GetHashSize() > 32)) 
			throw ArgumentOutOfRangeHashLibException(InvalidHashSize);
		
		rawConfig[0] = rawConfig[0] | (uint32_t(config->GetHashSize()));

		// Key length
		if (!config->GetKey().empty())
		{
			if (config->GetKey().size() > 32) 
				throw ArgumentOutOfRangeHashLibException(InvalidKeyLength);

			rawConfig[0] = rawConfig[0] | uint32_t(config->GetKey().size()) << 8;
		}
		
		// FanOut
		rawConfig[0] = rawConfig[0] | (uint32_t(LtreeConfig->GetFanOut()) << 16);

		// Depth
		rawConfig[0] = rawConfig[0] | (uint32_t(LtreeConfig->GetMaxHeight()) << 24);

		// Leaf length
		rawConfig[0] = rawConfig[0] | ((uint64_t(uint32_t(LtreeConfig->GetLeafSize()))) << 32);

		// Inner length
		if ((! isSequential) && ((LtreeConfig->GetIntermediateHashSize() <= 0) ||
			(LtreeConfig->GetIntermediateHashSize() > 32))) 
			throw ArgumentOutOfRangeHashLibException("treeConfig.TreeIntermediateHashSize");
		
		rawConfig[2] = rawConfig[2] | (uint32_t(LtreeConfig->GetIntermediateHashSize()) << 8);

		// Salt
		if (!config->GetSalt().empty())
		{
			if (config->GetSalt().size() != 8)
				throw ArgumentOutOfRangeHashLibException(InvalidSaltLength);

			rawConfig[4] = Converters::ReadBytesAsUInt32LE(&(config->GetSalt())[0], 0);
			rawConfig[5] = Converters::ReadBytesAsUInt32LE(&(config->GetSalt())[0], 4);
		}

		// Personalisation
		if (!config->GetPersonalisation().empty())
		{
			if (config->GetPersonalisation().size() != 8)
				throw ArgumentOutOfRangeHashLibException(InvalidPersonalisationLength);
			
			rawConfig[6] = Converters::ReadBytesAsUInt32LE(&(config->GetPersonalisation())[0], 0);
			rawConfig[7] = Converters::ReadBytesAsUInt32LE(&(config->GetPersonalisation())[0], 4);
		}
			
		return rawConfig;
	}

private:
	static IBlake2STreeConfig fillSequentialTreeConfig()
	{
		IBlake2STreeConfig config = make_shared<Blake2STreeConfig>();
		config->SetIntermediateHashSize(0);
		config->SetLeafSize(0);
		config->SetFanOut(1);
		config->SetMaxHeight(1);

		return config;
	}

	static IBlake2STreeConfig SequentialTreeConfig;

	static const char *InvalidHashSize;
	static const char *InvalidKeyLength;
	static const char *InvalidPersonalisationLength;
	static const char *InvalidSaltLength;

}; // end class Blake2SIvBuilder


IBlake2STreeConfig Blake2SIvBuilder::SequentialTreeConfig = Blake2SIvBuilder::fillSequentialTreeConfig();


const char *Blake2SIvBuilder::InvalidHashSize = "\"HashSize\" Must Be Greater Than 0 And Less Than or Equal To 32";
const char *Blake2SIvBuilder::InvalidKeyLength = "\"Key\" Length Must Not Be Greater Than 32";
const char *Blake2SIvBuilder::InvalidPersonalisationLength = "\"Personalisation\" Length Must Be Equal To 8";
const char *Blake2SIvBuilder::InvalidSaltLength = "\"Salt\" Length Must Be Equal To 8";


#endif // !HLPBLAKE2SLVBUILDER_H