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

#ifndef HLPCRC64_H
#define HLPCRC64_H

#include "HlpCRC.h"


class CRC64Polynomials
{
public:
	static const uint64_t ECMA_182 = 0x42F0E1EBA9EA3693;

}; // end class CRC64Polynomials


class _CRC64 : public Hash, public IIChecksum, public IIBlockHash, public IIHash64, public IITransformBlock
{
public:
	_CRC64(const uint64_t _poly, const uint64_t _Init,
		const bool _refIn, const bool _refOut, const uint64_t _XorOut,
		const uint64_t _check, const HashLibStringArray &_Names)
		: Hash(8, 1)
	{
		name = __func__;

		CRCAlgorithm = ::move(ICRC(new CRC(64, _poly, _Init, _refIn, _refOut, _XorOut, _check, _Names)));
	} // end constructor

	~_CRC64()
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

}; // end class CRC64


class _CRC64_ECMA : public _CRC64
{
public:
	_CRC64_ECMA()
		: _CRC64(CRC64Polynomials::ECMA_182, 0x0000000000000000, false, false, 0x0000000000000000, 0x6C40DF5F0B497347, HashLibStringArray({"CRC-64/ECMA"}))
	{} // end constructor
}; // end class _CRC64_ECMA


#endif // !HLPCRC64_H

