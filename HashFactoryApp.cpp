
#if defined(_MSC_VER)
    //disble vector assert for nullstring converted to byte array
    #define _HAS_ITERATOR_DEBUGGING 0
#endif

#include <stdio.h>
#include <tchar.h>

using namespace std;

#include "CryptoTests.h"
#include "ChecksumTests.h"
#include "Hash32Tests.h"
#include "Hash64Tests.h"
#include "Hash128Tests.h"
#include "PBKDF2_HMACTests.h"

