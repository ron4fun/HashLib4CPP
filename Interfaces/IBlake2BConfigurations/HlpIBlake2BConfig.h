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

#ifndef HLPIBLAKE2BCONFIG_H
#define HLPIBLAKE2BCONFIG_H

#include "../Utils/HlpHashLibTypes.h"

class IIBlake2BConfig
{
public:
	virtual HashLibByteArray GetPersonalisation() const = 0;
	virtual void SetPersonalisation(const HashLibByteArray &value) = 0;
	virtual HashLibByteArray GetSalt() const = 0;
	virtual void SetSalt(const HashLibByteArray &value) = 0;
	virtual HashLibByteArray GetKey() const = 0;
	virtual void SetKey(const HashLibByteArray &value) = 0;
	virtual int32_t GetHashSize() const = 0;
	virtual void SetHashSize(const int32_t value) = 0;

}; // end class IBlake2BConfig

typedef shared_ptr<IIBlake2BConfig> IBlake2BConfig;

#endif // !HLPIBLAKE2BCONFIG_H