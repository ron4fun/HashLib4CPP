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

#ifndef HLPKDF_H
#define HLPKDF_H

#include "../Interfaces/HlpIKDF.h"


class KDF : public virtual IIKDF
{
public:
	/// <summary>
	/// Returns the pseudo-random bytes for this object.
	/// </summary>
	/// <param name="bc">The number of pseudo-random key bytes to generate.</param>
	/// <returns>A byte array filled with pseudo-random key bytes.</returns>
	/// <exception cref="EArgumentOutOfRangeHashLibException">bc must be greater than zero.</exception>
	/// <exception cref="EArgumentHashLibException">invalid start index or end index of internal buffer.</exception>
	virtual HashLibByteArray GetBytes(const int32_t bc) = 0;

}; // end class KDF


#endif // !HLPKDF_H