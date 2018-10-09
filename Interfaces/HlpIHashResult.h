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

#ifndef HLPIHASHRESULT_H
#define HLPIHASHRESULT_H

#include "../Utils/HlpHashLibTypes.h"

class IIHashResult;

typedef shared_ptr<IIHashResult> IHashResult;

class IIHashResult
{
public:
	virtual HashLibByteArray GetBytes() const = 0;
	virtual uint8_t GetUInt8() const = 0;
	virtual uint16_t GetUInt16() const = 0;
	virtual uint32_t GetUInt32() const = 0;
	virtual int32_t GetInt32() const = 0;
	virtual uint64_t GetUInt64() const = 0;
	virtual string ToString(const bool a_group = false) const = 0;
	virtual int32_t GetHashCode() const = 0;
	virtual bool CompareTo(const IHashResult &a_hashResult) const = 0;

}; // end class IHashResult


#endif // !HLPIHASHRESULT_H
