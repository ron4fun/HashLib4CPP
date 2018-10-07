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

#ifndef HLPHASHFACTORY_H
#define HLPHASHFACTORY_H

#include "HlpHashRounds.h"
#include "HlpHashSize.h"
#include "../Interfaces/HlpIHash.h"
#include "../Interfaces/HlpIHashInfo.h"
#include "../Utils/HlpHashLibTypes.h"
// Checksum Units //
#include "../Checksum/HlpAdler32.h"
#include "../Checksum/HlpCRC32.h"
#include "../Checksum/HlpCRC64.h"
#include "../Checksum/HlpCRC.h"
#include "../Checksum/HlpCRC16.h"

// Hash32 Units //
#include "../Hash32/HlpAP.h"
#include "../Hash32/HlpBernstein.h"
#include "../Hash32/HlpBernstein1.h"
#include "../Hash32/HlpBKDR.h"
#include "../Hash32/HlpDEK.h"
#include "../Hash32/HlpDJB.h"
#include "../Hash32/HlpELF.h"
#include "../Hash32/HlpFNV.h"
#include "../Hash32/HlpFNV1a.h"
#include "../Hash32/HlpJenkins3.h"
#include "../Hash32/HlpJS.h"
#include "../Hash32/HlpMurmur2.h"
#include "../Hash32/HlpMurmurHash3_x86_32.h"
#include "../Hash32/HlpOneAtTime.h"
#include "../Hash32/HlpPJW.h"
#include "../Hash32/HlpRotating.h"
#include "../Hash32/HlpRS.h"
#include "../Hash32/HlpSDBM.h"
#include "../Hash32/HlpShiftAndXor.h"
#include "../Hash32/HlpSuperFast.h"
#include "../Hash32/HlpXXHash32.h"
// Hash64 Units //
#include "../Hash64/HlpFNV64.h"
#include "../Hash64/HlpFNV1a64.h"
#include "../Hash64/HlpMurmur2_64.h"
#include "../Hash64/HlpSipHash.h"
#include "../Hash64/HlpXXHash64.h"
// Hash128 Units //
#include "../Hash128/HlpMurmurHash3_x86_128.h"
#include "../Hash128/HlpMurmurHash3_x64_128.h"
// Crypto Units
#include "../Crypto/HlpBlake2B.h"
#include "../Crypto/HlpBlake2S.h"
#include "../Crypto/HlpTiger.h"
#include "../Crypto/HlpTiger2.h"
#include "../Crypto/HlpMD2.h"
#include "../Crypto/HlpMD4.h"
#include "../Crypto/HlpMD5.h"
#include "../Crypto/HlpSHA0.h"
#include "../Crypto/HlpSHA1.h"
#include "../Crypto/HlpSHA2_224.h"
#include "../Crypto/HlpSHA2_256.h"
#include "../Crypto/HlpSHA2_384.h"
#include "../Crypto/HlpSHA2_512.h"
#include "../Crypto/HlpSHA2_512_224.h"
#include "../Crypto/HlpSHA2_512_256.h"
#include "../Crypto/HlpGrindahl256.h"
#include "../Crypto/HlpGrindahl512.h"
#include "../Crypto/HlpPanama.h"
#include "../Crypto/HlpWhirlPool.h"
#include "../Crypto/HlpRadioGatun32.h"
#include "../Crypto/HlpRadioGatun64.h"
#include "../Crypto/HlpSnefru.h"
#include "../Crypto/HlpHaval.h"
#include "../Crypto/HlpGost.h"
#include "../Crypto/HlpGOST3411_2012.h"
#include "../Crypto/HlpHAS160.h"
#include "../Crypto/HlpRIPEMD.h"
#include "../Crypto/HlpRIPEMD128.h"
#include "../Crypto/HlpRIPEMD160.h"
#include "../Crypto/HlpRIPEMD256.h"
#include "../Crypto/HlpRIPEMD320.h"
#include "../Crypto/HlpSHA3.h"
// HMAC Unit
#include "HlpHMACNotBuildInAdapter.h"
// PBKDF2_HMAC Unit
#include "../KDF/HlpPBKDF2_HMACNotBuildInAdapter.h"
// NullDigest
#include "../NullDigest/HlpNullDigest.h"


namespace HashFactory
{
	// ====================== Checksum ====================== 
	namespace Checksum
	{
		static ICRC CreateCRC(const int32_t _Width, const int64_t _poly, const int64_t _Init,
			const bool _refIn, const bool _refOut, const int64_t _XorOut, const int64_t _check,
			const HashLibStringArray &_Names)
		{
			return make_shared<CRC>(_Width, _poly, _Init, _refIn, _refOut, _XorOut, _check, _Names);
		} // end function CreateCRC

		static ICRC CreateCRC(const CRCStandard &_value)
		{
			return CRC::CreateCRCObject(_value);
		} // end function CreateCRC

		static IHash CreateCRC16(const int64_t _poly, const int64_t _Init,
			const bool _refIn, const bool _refOut, const int64_t _XorOut, const int64_t _check,
			const HashLibStringArray &_Names)
		{
			return make_shared<_CRC16>(_poly, _Init, _refIn, _refOut, _XorOut, _check, _Names);
		} // end function CreateCRC16

		static IHash CreateCRC32(const int64_t _poly, const int64_t _Init,
			const bool _refIn, const bool _refOut, const int64_t _XorOut, const int64_t _check,
			const HashLibStringArray &_Names)
		{
			return make_shared<_CRC32>(_poly, _Init, _refIn, _refOut, _XorOut, _check, _Names);
		} // end function CreateCRC32

		static IHash CreateCRC64(const int64_t _poly, const int64_t _Init,
			const bool _refIn, const bool _refOut, const int64_t _XorOut, const int64_t _check,
			const HashLibStringArray &_Names)
		{
			return make_shared<_CRC64>(_poly, _Init, _refIn, _refOut, _XorOut, _check, _Names);
		} // end function CreateCRC64

		/// <summary>
		/// BUYPASS, polynomial = 0x8005
		/// </summary>
		/// <returns></returns>
		static IHash CreateCRC16_BUYPASS()
		{
			return make_shared<_CRC16_BUYPASS>();
		} // end function CreateCRC16_BUYPASS

		/// <summary>
		/// PKZIP, polynomial = 0x04C11DB7
		/// </summary>
		/// <returns></returns>
		static IHash CreateCRC32_PKZIP()
		{
			return make_shared<_CRC32_PKZIP>();
		} // end function CreateCRC32_PKZIP

		/// <summary>
		/// Castagnoli, polynomial = 0x1EDC6F41
		/// </summary>
		/// <returns></returns>
		static IHash CreateCRC32_CASTAGNOLI()
		{
			return make_shared<_CRC32_CASTAGNOLI>();
		} // end function CreateCRC32_CASTAGNOLI

		/// <summary>
		/// ECMA-182, polynomial = 0x42F0E1EBA9EA3693
		/// </summary>
		/// <returns></returns>
		static IHash CreateCRC64_ECMA()
		{
			return make_shared<_CRC64_ECMA>();
		} // end function CreateCRC64_ECMA

		static IHash CreateAdler32()
		{
			return make_shared<Adler32>();
		} // end function CreateAdler32

	} // end namespace Checksum

	// ====================== Hash32 ======================
	namespace Hash32
	{
		static IHash CreateAP()
		{
			return make_shared<AP>();
		} // end function CreateAP

		static IHash CreateBernstein()
		{
			return make_shared<Bernstein>();
		} // end function CreateBernstein

		static IHash CreateBernstein1()
		{
			return make_shared<Bernstein1>();
		} // end function CreateBernstein1

		static IHash CreateBKDR()
		{
			return make_shared<BKDR>();
		} // end function CreateBKDR

		static IHash CreateDEK()
		{
			return make_shared<DEK>();
		} // end function CreateDEK

		static IHash CreateDJB()
		{
			return make_shared<DJB>();
		} // end function CreateDJB

		static IHash CreateELF()
		{
			return make_shared<ELF>();
		} // end function CreateELF

		static IHash CreateFNV()
		{
			return make_shared<FNV>();
		} // end function CreateFNV

		static IHash CreateFNV1a()
		{
			return make_shared<FNV1a>();
		} // end function CreateFNV1a

		static IHash CreateJenkins3()
		{
			return make_shared<Jenkins3>();
		} // end function CreateJenkins3

		static IHash CreateJS()
		{
			return make_shared<JS>();
		} // end function CreateJS

		static IHashWithKey CreateMurmur2()
		{
			return make_shared<Murmur2>();
		} // end function CreateMurmur2

		static IHashWithKey CreateMurmurHash3_x86_32()
		{
			return make_shared<MurmurHash3_x86_32>();
		} // end function CreateMurmurHash3_x86_32

		static IHash CreateOneAtTime()
		{
			return make_shared<OneAtTime>();
		} // end function CreateOneAtTime

		static IHash CreatePJW()
		{
			return  make_shared<PJW>();
		} // end function CreatePJW

		static IHash CreateRotating()
		{
			return  make_shared<Rotating>();
		} // end function CreateRotating

		static IHash CreateRS()
		{
			return  make_shared<RS>();
		} // end function CreateRS

		static IHash CreateSDBM()
		{
			return  make_shared<SDBM>();
		} // end function CreateSDBM

		static IHash CreateShiftAndXor()
		{
			return  make_shared<ShiftAndXor>();
		} // end function CreateShiftAndXor

		static IHash CreateSuperFast()
		{
			return  make_shared<SuperFast>();
		} // end function CreateSuperFast

		static IHashWithKey CreateXXHash32()
		{
			return  make_shared<XXHash32>();
		} // end function CreateXXHash32

	} // end namespace Hash32

	// ====================== Hash64 ====================== 
	namespace Hash64
	{
		static IHash CreateFNV()
		{
			return  make_shared<FNV64>();
		} // end function CreateFNV

		static IHash CreateFNV1a()
		{
			return  make_shared<FNV1a64>();
		} // end function CreateFNV1a

		static IHashWithKey CreateMurmur2()
		{
			return  make_shared<Murmur2_64>();
		} // end function CreateMurmur2

		static IHashWithKey CreateSipHash2_4()
		{
			return  make_shared<SipHash2_4>();
		} // end function CreateSipHash2_4

		static IHashWithKey CreateXXHash64()
		{
			return  make_shared<XXHash64>();
		} // end function CreateXXHash64

	} // end namespace Hash64

	// ====================== Hash128 ======================
	namespace Hash128
	{
		static IHashWithKey CreateMurmurHash3_x86_128()
		{
			return  make_shared<MurmurHash3_x86_128>();
		} // end function CreateMurmurHash3_x86_128

		static IHashWithKey CreateMurmurHash3_x64_128()
		{
			return  make_shared<MurmurHash3_x64_128>();
		} // end function 

	} // end namespace Hash128

	// ====================== Crypto ======================
	namespace Crypto
	{
		/// <summary>
		///
		/// </summary>
		/// <param name="a_hash_size">16, 20 or 24 bytes. </param>
		/// <param name="a_rounds">no of rounds (standard rounds are 3, 4 and 5)</param>
		/// <returns></returns>
		static IHash CreateTiger(const int32_t a_hash_size, const HashRounds &a_rounds)
		{
			if ((a_hash_size != 16) && (a_hash_size != 20) && (a_hash_size != 24))
				throw ArgumentHashLibException(Tiger::InvalidTigerHashSize);

			return  make_shared<Tiger_Base>(a_hash_size, a_rounds);
		} // end function CreateTiger

		static IHash CreateTiger_3_128()
		{
			return  make_shared<Tiger_3_128>();
		} // end function CreateTiger_3_128

		static IHash CreateTiger_3_160()
		{
			return  make_shared<Tiger_3_160>();
		} // end function CreateTiger_3_160

		static IHash CreateTiger_3_192()
		{
			return  make_shared<Tiger_3_192>();
		} // end function CreateTiger_3_192

		static IHash CreateTiger_4_128()
		{
			return  make_shared<Tiger_4_128>();
		} // end function CreateTiger_4_128

		static IHash CreateTiger_4_160()
		{
			return  make_shared<Tiger_4_160>();
		} // end function CreateTiger_4_160

		static IHash CreateTiger_4_192()
		{
			return  make_shared<Tiger_4_192>();
		} // end function CreateTiger_4_192

		static IHash CreateTiger_5_128()
		{
			return make_shared<Tiger_5_128>();
		} // end function CreateTiger_5_128

		static IHash CreateTiger_5_160()
		{
			return  make_shared<Tiger_5_160>();
		} // end function CreateTiger_5_160

		static IHash CreateTiger_5_192()
		{
			return  make_shared<Tiger_5_192>();
		} // end function CreateTiger_5_192

		/// <summary>
		///
		/// </summary>
		/// <param name="a_hash_size">16, 20 or 24 bytes. </param>
		/// <param name="a_rounds">no of rounds (standard rounds are 3, 4 and 5)</param>
		/// <returns></returns>
		static IHash CreateTiger2(const int32_t a_hash_size, const HashRounds &a_rounds)
		{
			if ((a_hash_size != 16) && (a_hash_size != 20) && (a_hash_size != 24))
				throw ArgumentHashLibException(Tiger2::InvalidTiger2HashSize);

			return  make_shared<Tiger2_Base>(a_hash_size, a_rounds);
		} // end function CreateTiger2

		static IHash CreateTiger2_3_128()
		{
			return  make_shared<Tiger2_3_128>();
		} // end function CreateTiger2_3_128

		static IHash CreateTiger2_3_160()
		{
			return  make_shared<Tiger2_3_160>();
		} // end function CreateTiger2_3_160

		static IHash CreateTiger2_3_192()
		{
			return  make_shared<Tiger2_3_192>();
		} // end function CreateTiger2_3_192

		static IHash CreateTiger2_4_128()
		{
			return  make_shared<Tiger2_4_128>();
		} // end function CreateTiger2_4_128

		static IHash CreateTiger2_4_160()
		{
			return  make_shared<Tiger2_4_160>();
		} // end function CreateTiger2_4_160

		static IHash CreateTiger2_4_192()
		{
			return  make_shared<Tiger2_4_192>();
		} // end function CreateTiger2_4_192

		static IHash CreateTiger2_5_128()
		{
			return  make_shared<Tiger2_5_128>();
		} // end function CreateTiger2_5_128

		static IHash CreateTiger2_5_160()
		{
			return  make_shared<Tiger2_5_160>();
		} // end function CreateTiger2_5_160

		static IHash CreateTiger2_5_192()
		{
			return  make_shared<Tiger2_5_192>();
		} // end function CreateTiger2_5_192

		static IHash CreateMD2()
		{
			return  make_shared<MD2>();
		} // end function CreateMD2

		static IHash CreateMD4()
		{
			return  make_shared<MD4>();
		} // end function CreateMD4

		static IHash CreateMD5()
		{
			return make_shared<MD5>();
		} // end function CreateMD5

		static IHash CreateSHA0()
		{
			return  make_shared<SHA0>();
		} // end function CreateSHA0

		static IHash CreateSHA1()
		{
			return  make_shared<SHA1>();
		} // end function CreateSHA1

		static IHash CreateSHA2_224()
		{
			return  make_shared<SHA2_224>();
		} // end function CreateSHA2_224

		static IHash CreateSHA2_256()
		{
			return  make_shared<SHA2_256>();
		} // end function CreateSHA2_256

		static IHash CreateSHA2_384()
		{
			return  make_shared<SHA2_384>();
		} // end function CreateSHA2_384

		static IHash CreateSHA2_512()
		{
			return  make_shared<SHA2_512>();
		} // end function CreateSHA2_512

		static IHash CreateSHA2_512_224()
		{
			return make_shared<SHA2_512_224>();
		} // end function CreateSHA2_512_224

		static IHash CreateSHA2_512_256()
		{
			return  make_shared<SHA2_512_256>();
		} // end function CreateSHA2_512_256

		static IHash CreateGrindahl256()
		{
			return  make_shared<Grindahl256>();
		} // end function CreateGrindahl256

		static IHash CreateGrindahl512()
		{
			return  make_shared<Grindahl512>();
		} // end function CreateGrindahl512

		static IHash CreatePanama()
		{
			return  make_shared<Panama>();
		} // end function CreatePanama

		static IHash CreateWhirlPool()
		{
			return  make_shared<WhirlPool>();
		} // end function CreateWhirlPool

		static IHash CreateRadioGatun32()
		{
			return  make_shared<RadioGatun32>();
		} // end function CreateRadioGatun32

		static IHash CreateRadioGatun64()
		{
			return  make_shared<RadioGatun64>();
		} // end function CreateRadioGatun64

		/// <summary>
		///
		/// </summary>
		/// <param name="a_security_level">any Integer value greater than 0. Standard is 8. </param>
		/// <param name="a_hash_size">128bit, 256bit</param>
		/// <returns></returns>
		static IHash CreateSnefru(const int32_t a_security_level, const HashSize &a_hash_size)
		{
			if (a_security_level < int32_t(1))
				throw ArgumentHashLibException(Snefru::InvalidSnefruLevel);

			if ((a_hash_size == HashSize128) || (a_hash_size == HashSize256))
				return  make_shared<Snefru>(a_security_level, a_hash_size);
			else
				throw ArgumentHashLibException(Snefru::InvalidSnefruHashSize);
		} // end function CreateSnefru

		static IHash CreateSnefru_8_128()
		{
			return CreateSnefru(8, HashSize128);
		} // end function CreateSnefru_8_128

		static IHash CreateSnefru_8_256()
		{
			return CreateSnefru(8, HashSize256);
		} // end function CreateSnefru_8_256


		static IHash CreateHaval_3_128()
		{
			return  make_shared<Haval_3_128>();
		} // end function CreateHaval_3_128

		static IHash CreateHaval_4_128()
		{
			return  make_shared<Haval_4_128>();
		} // end function CreateHaval_4_128

		static IHash CreateHaval_5_128()
		{
			return  make_shared<Haval_5_128>();
		} // end function CreateHaval_5_128

		static IHash CreateHaval_3_160()
		{
			return  make_shared<Haval_3_160>();
		} // end function CreateHaval_3_160

		static IHash CreateHaval_4_160()
		{
			return  make_shared<Haval_4_160>();
		} // end function CreateHaval_4_160

		static IHash CreateHaval_5_160()
		{
			return  make_shared<Haval_5_160>();
		} // end function CreateHaval_5_160

		static IHash CreateHaval_3_192()
		{
			return  make_shared<Haval_3_192>();
		} // end function CreateHaval_3_192

		static IHash CreateHaval_4_192()
		{
			return  make_shared<Haval_4_192>();
		} // end function CreateHaval_4_192

		static IHash CreateHaval_5_192()
		{
			return  make_shared<Haval_5_192>();
		} // end function CreateHaval_5_192

		static IHash CreateHaval_3_224()
		{
			return  make_shared<Haval_3_224>();
		} // end function CreateHaval_3_224

		static IHash CreateHaval_4_224()
		{
			return  make_shared<Haval_4_224>();
		} // end function CreateHaval_4_224

		static IHash CreateHaval_5_224()
		{
			return  make_shared<Haval_5_224>();
		} // end function CreateHaval_5_224

		static IHash CreateHaval_3_256()
		{
			return  make_shared<Haval_3_256>();
		} // end function CreateHaval_3_256

		static IHash CreateHaval_4_256()
		{
			return  make_shared<Haval_4_256>();
		} // end function CreateHaval_4_256

		static IHash CreateHaval_5_256()
		{
			return  make_shared<Haval_5_256>();
		} // end function CreateHaval_5_256

		/// <summary>
		///
		/// </summary>
		/// <param name="a_rounds">3, 4, 5</param>
		/// <param name="a_hash_size">128, 160, 192, 224, 256</param>
		/// <returns></returns>
		static IHash CreateHaval(const HashRounds &a_rounds, const HashSize &a_hash_size)
		{
			switch (a_rounds)
			{
			case Rounds3:
				switch (a_hash_size)
				{
				case HashSize128:
					return CreateHaval_3_128();
				case HashSize160:
					return CreateHaval_3_160();
				case HashSize192:
					return CreateHaval_3_192();
				case HashSize224:
					return CreateHaval_3_224();
				case HashSize256:
					return CreateHaval_3_256();
				default:
					throw ArgumentHashLibException(Haval::InvalidHavalHashSize);
				} // end switch

			case Rounds4:
				switch (a_hash_size)
				{
				case HashSize128:
					return CreateHaval_4_128();
				case HashSize160:
					return CreateHaval_4_160();
				case HashSize192:
					return CreateHaval_4_192();
				case HashSize224:
					return CreateHaval_4_224();
				case HashSize256:
					return CreateHaval_4_256();
				default:
					throw ArgumentHashLibException(Haval::InvalidHavalHashSize);
				} // end switch

			case Rounds5:
				switch (a_hash_size)
				{
				case HashSize128:
					return CreateHaval_5_128();
				case HashSize160:
					return CreateHaval_5_160();
				case HashSize192:
					return CreateHaval_5_192();
				case HashSize224:
					return CreateHaval_5_224();
				case HashSize256:
					return CreateHaval_5_256();
				default:
					throw ArgumentHashLibException(Haval::InvalidHavalHashSize);
				} // end switch

			default:
				throw ArgumentHashLibException(Haval::InvalidHavalRound);
			} // end switch
		} // end function Haval

		static IHash CreateGost()
		{
			return  make_shared<Gost>();
		} // end function CreateGost

		static IHash CreateGOST3411_2012_256()
		{
			return  make_shared<GOST3411_2012_256>();
		} // end function CreateGOST3411_2012_256

		static IHash CreateGOST3411_2012_512()
		{
			return  make_shared<GOST3411_2012_512>();
		} // end function CreateGOST3411_2012_512
		
		static IHash CreateHAS160()
		{
			return  make_shared<HAS160>();
		} // end function CreateHAS160

		static IHash CreateRIPEMD()
		{
			return  make_shared<RIPEMD>();
		} // end function CreateRIPEMD

		static IHash CreateRIPEMD128()
		{
			return  make_shared<RIPEMD128>();
		} // end function CreateRIPEMD128
		
		static IHash CreateRIPEMD160()
		{
			return  make_shared<RIPEMD160>();
		} // end function CreateRIPEMD160

		static IHash CreateRIPEMD256()
		{
			return  make_shared<RIPEMD256>();
		} // end function CreateRIPEMD256

		static IHash CreateRIPEMD320()
		{
			return  make_shared<RIPEMD320>();
		} // end function CreateRIPEMD320
		
		static IHash CreateSHA3_224()
		{
			return  make_shared<SHA3_224>();
		} // end function CreateSHA3_224

		static IHash CreateSHA3_256()
		{
			return  make_shared<SHA3_256>();
		} // end function CreateSHA3_256

		static IHash CreateSHA3_384()
		{
			return  make_shared<SHA3_384>();
		} // end function CreateSHA3_384

		static IHash CreateSHA3_512()
		{
			return  make_shared<SHA3_512>();
		} // end function CreateSHA3_512

		static IHash CreateKeccak_224()
		{
			return  make_shared<Keccak_224>();
		} // end function CreateKeccak_224

		static IHash CreateKeccak_256()
		{
			return  make_shared<Keccak_256>();
		} // end function CreateKeccak_256

		static IHash CreateKeccak_384()
		{
			return  make_shared<Keccak_384>();
		} // end function CreateKeccak_384

		static IHash CreateKeccak_512()
		{
			return  make_shared<Keccak_512>();
		} // end function CreateKeccak_512

		static IHash CreateBlake2B(const IBlake2BConfig config = nullptr)
		{
			if (config == nullptr) return make_shared<Blake2B>();
			return make_shared<Blake2B>(config);
		}

		static IHash CreateBlake2B_160()
		{
			IBlake2BConfig config = make_shared<Blake2BConfig>(HashSize::HashSize160);
			return HashFactory::Crypto::CreateBlake2B(config);
		}

		static IHash CreateBlake2B_256()
		{
			IBlake2BConfig config = make_shared<Blake2BConfig>(HashSize::HashSize256);
			return HashFactory::Crypto::CreateBlake2B(config);
		}

		static IHash CreateBlake2B_384()
		{
			IBlake2BConfig config = make_shared<Blake2BConfig>(HashSize::HashSize384);
			return HashFactory::Crypto::CreateBlake2B(config);
		}

		static IHash CreateBlake2B_512()
		{
			IBlake2BConfig config = make_shared<Blake2BConfig>(HashSize::HashSize512);
			return HashFactory::Crypto::CreateBlake2B(config);
		}

		static IHash CreateBlake2S(const IBlake2SConfig config = nullptr)
		{
			if (config == nullptr) return make_shared<Blake2S>();
			return make_shared<Blake2S>(config);
		}

		static IHash CreateBlake2S_128()
		{
			IBlake2SConfig config = make_shared<Blake2SConfig>(HashSize::HashSize128);
			return HashFactory::Crypto::CreateBlake2S(config);
		}

		static IHash CreateBlake2S_160()
		{
			IBlake2SConfig config = make_shared<Blake2SConfig>(HashSize::HashSize160);
			return HashFactory::Crypto::CreateBlake2S(config);
		}

		static IHash CreateBlake2S_224()
		{
			IBlake2SConfig config = make_shared<Blake2SConfig>(HashSize::HashSize224);
			return HashFactory::Crypto::CreateBlake2S(config);
		}

		static IHash CreateBlake2S_256()
		{
			IBlake2SConfig config = make_shared<Blake2SConfig>(HashSize::HashSize256);
			return HashFactory::Crypto::CreateBlake2S(config);
		}

	} // end namespace Crypto

	// ====================== HMAC ======================
	namespace HMAC
	{
		static IHMAC CreateHMAC(IHash &a_hash)
		{
			return make_shared<HMACNotBuildInAdapter>(a_hash);
		} // end function CreateHMAC
	} // end namespace HMAC

	// ====================== PBKDF2_HMAC ======================
	namespace PBKDF2_HMAC
	{
		/// <summary>
		/// Initializes a new interface instance of the TPBKDF2_HMAC class using a password, a salt, a number of iterations and an Instance of an "IHash" to be used as an "IHMAC" hashing implementation to derive the key.
		/// </summary>
		/// <param name="a_hash">The name of the "IHash" implementation to be transformed to an "IHMAC" Instance so it can be used to derive the key.</param>
		/// <param name="password">The password to derive the key for.</param>
		/// <param name="salt">The salt to use to derive the key.</param>
		/// <param name="iterations">The number of iterations to use to derive the key.</param>
		/// <exception cref="ArgumentNilHashLibException">The password, salt or algorithm is Nil.</exception>
		/// <exception cref="ArgumentHashLibException">The iteration is less than 1.</exception>
		static IPBKDF2_HMAC CreatePBKDF2_HMAC(IHash a_hash, const HashLibByteArray &a_password,
			const HashLibByteArray &a_salt, const uint32_t a_iterations)
		{
			if (!a_hash)
				throw ArgumentNilHashLibException(PBKDF2_HMACNotBuildInAdapter::UninitializedInstance);

			if (a_password.empty())
				throw ArgumentNilHashLibException(PBKDF2_HMACNotBuildInAdapter::EmptyPassword);

			if (a_salt.empty())
				throw ArgumentNilHashLibException(PBKDF2_HMACNotBuildInAdapter::EmptySalt);

			if (a_iterations < 1)
				throw ArgumentHashLibException(PBKDF2_HMACNotBuildInAdapter::IterationtooSmall);

			return make_shared<PBKDF2_HMACNotBuildInAdapter>(a_hash, a_password, a_salt, a_iterations);
		} // end function CreatePBKDF2_HMAC
	} // end namespace PBKDF2_HMAC

	// ====================== NullDigest ======================
	namespace NullDigestFactory
	{
		IHash CreateNullDigest()
		{
			return make_shared<NullDigest>();
		}

	}

} // end namespace HashFactory


#endif // !HLPHASHFACTORY_H