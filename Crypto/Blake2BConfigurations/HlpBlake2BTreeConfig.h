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

#ifndef HLPBLAKE2BTREECONFIG_H
#define HLPBLAKE2BTREECONFIG_H

#include "../Interfaces/IBlake2BConfigurations/HlpIBlake2BTreeConfig.h"
#include "../Base/HlpHashSize.h"
#include "../Utils/HlpHashLibTypes.h"
#include "../Utils/HlpUtils.h"

class Blake2BTreeConfig : public virtual IIBlake2BTreeConfig
{
public:
	Blake2BTreeConfig()
		: IntermediateHashSize(64)
	{}

	static IBlake2BTreeConfig CreateInterleaved(const int32_t parallelism)
	{
		IBlake2BTreeConfig result = make_shared<Blake2BTreeConfig>();
		result->SetFanOut(parallelism);
		result->SetMaxHeight(2);
		result->SetIntermediateHashSize(64);

		return result;
	}

	virtual int32_t GetIntermediateHashSize() const
	{
		return IntermediateHashSize;
	}

	virtual void SetIntermediateHashSize(const int32_t value)
	{
		IntermediateHashSize = value;
	}

	virtual int32_t GetMaxHeight() const
	{
		return MaxHeight;
	}

	virtual void SetMaxHeight(const int32_t value)
	{
		MaxHeight = value;
	}

	virtual int64_t GetLeafSize() const
	{
		return LeafSize;
	}

	virtual void SetLeafSize(const int64_t value)
	{
		LeafSize = value;
	}

	virtual int32_t GetFanOut() const
	{
		return FanOut;
	}

	virtual void SetFanOut(const int32_t value)
	{
		FanOut = value;
	}

private:
	int32_t IntermediateHashSize, MaxHeight, FanOut;
	int64_t LeafSize;

}; // end class Blake2BTreeConfig


#endif // !HLPBLAKE2BTREECONFIG_H