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


#if defined(_MSC_VER)
    //disble vector assert for nullstring converted to byte array
    #define _HAS_ITERATOR_DEBUGGING 0
#endif

#include <stdio.h>
#include <tchar.h>

#include "CryptoTests.h"
#include "ChecksumTests.h"
#include "Hash32Tests.h"
#include "Hash64Tests.h"
#include "Hash128Tests.h"
#include "PBKDF2_HMACTests.h"
#include "NullDigestTest.h"
