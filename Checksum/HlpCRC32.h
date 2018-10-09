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

#ifndef HLPCRC32_H
#define HLPCRC32_H

#include "HlpCRC.h"


class CRC32Polynomials
{
public:
	 static const uint32_t PKZIP = 0x04C11DB7;
	 static const uint32_t Castagnoli = 0x1EDC6F41;

}; // end class CRC32Polynomials


class _CRC32 : public Hash, public IIChecksum, public IIBlockHash, public IIHash32, public IITransformBlock
{
public:
	_CRC32(const uint64_t _poly, const uint64_t _Init,
		const bool _refIn, const bool _refOut, const uint64_t _XorOut,
		const uint64_t _check, const HashLibStringArray &_Names)
		: Hash(4, 1)
	{
		name = __func__;

		CRCAlgorithm = ::move(ICRC(new CRC(32, _poly, _Init, _refIn, _refOut, _XorOut, _check, _Names)));
	} // end constructor

	~_CRC32()
	{} // end destructor

	virtual void Initialize()
	{
		CRCAlgorithm->Initialize();
	} // end function Initialize

	virtual IHashResult TransformFinal()
	{
		return CRCAlgorithm->TransformFinal();
	} // end function TransformFinal

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		CRCAlgorithm->TransformBytes(a_data, a_index, a_length);
	} // end function TransformBytes

private:
	ICRC CRCAlgorithm;

}; // end class CRC32


class _CRC32_PKZIP : public _CRC32
{
public:
	_CRC32_PKZIP()
		: _CRC32(CRC32Polynomials::PKZIP, 0xFFFFFFFF, true, true, 0xFFFFFFFF, 0xCBF43926, HashLibStringArray({ "CRC-32", "CRC-32/ADCCP", "PKZIP" }))
	{} // end constructor
}; // end class _CRC32_PKZIP


class _CRC32_CASTAGNOLI : public _CRC32
{
public:
	_CRC32_CASTAGNOLI()
		: _CRC32(CRC32Polynomials::Castagnoli, 0xFFFFFFFF, true, true, 0xFFFFFFFF, 0xE3069283, HashLibStringArray({"CRC-32C", "CRC-32/ISCSI", "CRC-32/CASTAGNOLI"}))
	{} // end constructor
}; // end class _CRC32_CASTAGNOLI


#endif // !HLPCRC32_H

