#ifndef HLPCRC16_H
#define HLPCRC16_H

#include "HlpCRC.h"


class CRC16Polynomials
{
public:
	static const uint16_t BUYPASS = 0x8005;

}; // end class CRC16Polynomials


class _CRC16 : public Hash, public IIChecksum, public IIBlockHash, public IIHash16, public IITransformBlock
{
public:
	_CRC16(const uint64_t _poly, const uint64_t _Init,
		const bool _refIn, const bool _refOut, const uint64_t _XorOut,
		const uint64_t _check, const HashLibStringArray &_Names)
		: Hash(2, 1)
	{
		name = __func__;

		CRCAlgorithm = ::move(ICRC( new CRC(16, _poly, _Init, _refIn, _refOut, _XorOut, _check, _Names)));
	} // end constructor

	~_CRC16()
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

}; // end class CRC16


class _CRC16_BUYPASS : public _CRC16
{
public:
	_CRC16_BUYPASS()
		: _CRC16(CRC16Polynomials::BUYPASS, 0x0000, false, false, 0x0000, 0xFEE8, HashLibStringArray({ "CRC-16/BUYPASS", "CRC-16/VERIFONE" }))
	{} // end constructor
}; // end class _CRC16_BUYPASS


#endif // !HLPCRC16_H

