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

#ifndef HLPICRC_H
#define HLPICRC_H

#include "HlpIHash.h"

class IICRC : public virtual IIHash
{
public:
	virtual HashLibStringArray GetNames() const = 0;
	virtual int32_t GetWidth() const = 0;
	virtual uint64_t GetPolynomial() const = 0;
	virtual uint64_t GetInit() const = 0;
	virtual bool GetReflectIn() const = 0;
	virtual bool GetReflectOut() const = 0;
	virtual uint64_t GetXOROut() const = 0;
	virtual uint64_t GetCheckValue() const = 0;
	
}; // end class ICRC

typedef shared_ptr<IICRC> ICRC;

#endif // !HLPICRC_H