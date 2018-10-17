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

#ifndef HLPBLAKE2BLVBUILDER_H
#define HLPBLAKE2BLVBUILDER_H

#include "../../Interfaces/IBlake2BConfigurations/HlpIBlake2BConfig.h"
#include "HlpBlake2BTreeConfig.h"
#include "../../Base/HlpHashSize.h"
#include "../../Base/HlpConverters.h"
#include "../../Utils/HlpHashLibTypes.h"
#include "../../Utils/HlpUtils.h"


class Blake2BIvBuilder
{
public:
	static HashLibUInt64Array ConfigB(const IBlake2BConfig config, const IBlake2BTreeConfig treeConfig)
	{
		bool isSequential;
		HashLibUInt64Array rawConfig;
		IBlake2BTreeConfig LtreeConfig;

		LtreeConfig = treeConfig;
		isSequential = !LtreeConfig;
		if (isSequential)
			LtreeConfig = SequentialTreeConfig;

		rawConfig.resize(8);

		// digest length
		if ((config->GetHashSize() <= 0) || (config->GetHashSize() > 64))
			throw ArgumentOutOfRangeHashLibException(InvalidHashSize);

		rawConfig[0] = rawConfig[0] | uint64_t(uint32_t(config->GetHashSize()));

		// Key length
		if (!config->GetKey().empty())
		{
			if (config->GetKey().size() > 64)
				throw ArgumentOutOfRangeHashLibException(InvalidKeyLength);

			rawConfig[0] = rawConfig[0] | uint64_t(uint32_t(config->GetKey().size())) << 8;
		}

		// FanOut
		rawConfig[0] = rawConfig[0] | (uint32_t(LtreeConfig->GetFanOut()) << 16);

		// Depth
		rawConfig[0] = rawConfig[0] | (uint32_t(LtreeConfig->GetMaxHeight()) << 24);

		// Leaf length
		rawConfig[0] = rawConfig[0] | ((uint64_t(uint32_t(LtreeConfig->GetLeafSize()))) << 32);

		// Inner length
		if ((!isSequential) && ((LtreeConfig->GetIntermediateHashSize() <= 0) ||
			(LtreeConfig->GetIntermediateHashSize() > 64)))
			throw ArgumentOutOfRangeHashLibException("treeConfig.TreeIntermediateHashSize");

		rawConfig[2] = rawConfig[2] | (uint32_t(LtreeConfig->GetIntermediateHashSize()) << 8);

		// Salt
		if (!config->GetSalt().empty())
		{
			if (config->GetSalt().size() != 16)
				throw ArgumentOutOfRangeHashLibException(InvalidSaltLength);

			rawConfig[4] = Converters::ReadBytesAsUInt32LE(&(config->GetSalt())[0], 0);
			rawConfig[5] = Converters::ReadBytesAsUInt32LE(&(config->GetSalt())[0], 8);
		}

		// Personalisation
		if (!config->GetPersonalisation().empty())
		{
			if (config->GetPersonalisation().size() != 16)
				throw ArgumentOutOfRangeHashLibException(InvalidPersonalisationLength);

			rawConfig[6] = Converters::ReadBytesAsUInt32LE(&(config->GetPersonalisation())[0], 0);
			rawConfig[7] = Converters::ReadBytesAsUInt32LE(&(config->GetPersonalisation())[0], 8);
		}

		return rawConfig;
	}

	static void ConfigBSetNode(HashLibUInt64Array &rawConfig, const uint8_t depth, const uint64_t nodeOffset)
	{
		rawConfig[1] = nodeOffset;
		rawConfig[2] = (rawConfig[2] & (~uint64_t(0xFF))) | depth;
	}

private:
	static IBlake2BTreeConfig fillSequentialTreeConfig()
	{
		IBlake2BTreeConfig config = make_shared<Blake2BTreeConfig>();
		config->SetIntermediateHashSize(0);
		config->SetLeafSize(0);
		config->SetFanOut(1);
		config->SetMaxHeight(1);

		return config;
	}

	static IBlake2BTreeConfig SequentialTreeConfig;

	static const char *InvalidHashSize;
	static const char *InvalidKeyLength;
	static const char *InvalidPersonalisationLength;
	static const char *InvalidSaltLength;

}; // end class Blake2BIvBuilder


IBlake2BTreeConfig Blake2BIvBuilder::SequentialTreeConfig = Blake2BIvBuilder::fillSequentialTreeConfig();


const char *Blake2BIvBuilder::InvalidHashSize = "\"HashSize\" Must Be Greater Than 0 And Less Than or Equal To 64";
const char *Blake2BIvBuilder::InvalidKeyLength = "\"Key\" Length Must Not Be Greater Than 64";
const char *Blake2BIvBuilder::InvalidPersonalisationLength = "\"Personalisation\" Length Must Be Equal To 16";
const char *Blake2BIvBuilder::InvalidSaltLength = "\"Salt\" Length Must Be Equal To 16";


#endif // !HLPBLAKE2BLVBUILDER_H