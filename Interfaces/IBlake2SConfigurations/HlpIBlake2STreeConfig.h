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

#ifndef HLPIBLAKE2STREECONFIG_H
#define HLPIBLAKE2STREECONFIG_H

#include "../Utils/HlpHashLibTypes.h"

class IIBlake2STreeConfig
{
public:
	virtual int32_t GetIntermediateHashSize() const = 0;
	virtual void SetIntermediateHashSize(const int32_t value) = 0;
	virtual int32_t GetMaxHeight() const = 0;
	virtual void SetMaxHeight(const int32_t value) = 0;
	virtual int64_t GetLeafSize() const = 0;
	virtual void SetLeafSize(const int64_t value) = 0;
	virtual int32_t GetFanOut() const = 0;
	virtual void SetFanOut(const int32_t value) = 0;
	
}; // end class IBlake2STreeConfig

typedef shared_ptr<IIBlake2STreeConfig> IBlake2STreeConfig;

#endif // !HLPIBLAKE2STREECONFIG_H