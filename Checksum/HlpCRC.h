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

#ifndef HLPCRC_H
#define HLPCRC_H

#include "../Base/HlpHash.h"
#include "../Interfaces/HlpIHashInfo.h"
#include "../Interfaces/HlpICRC.h"

/// <summary>
/// Enum of all defined and implemented CRC standards.
/// </summary>
enum CRCStandard
{

	/// <summary>
	/// CRC standard named "CRC3_GSM".
	/// </summary>
	CRC3_GSM = 0,

	/// <summary>
	/// CRC standard named "CRC3_ROHC".
	/// </summary>
	CRC3_ROHC,

	/// <summary>
	/// CRC standard named "CRC4_INTERLAKEN".
	/// </summary>
	CRC4_INTERLAKEN,

	/// <summary>
	/// CRC standard named "CRC4_ITU".
	/// </summary>
	CRC4_ITU,

	/// <summary>
	/// CRC standard named "CRC5_EPC".
	/// </summary>
	CRC5_EPC,

	/// <summary>
	/// CRC standard named "CRC5_ITU".
	/// </summary>
	CRC5_ITU,

	/// <summary>
	/// CRC standard named "CRC5_USB".
	/// </summary>
	CRC5_USB,

	/// <summary>
	/// CRC standard named "CRC6_CDMA2000A".
	/// </summary>
	CRC6_CDMA2000A,

	/// <summary>
	/// CRC standard named "CRC6_CDMA2000B".
	/// </summary>
	CRC6_CDMA2000B,

	/// <summary>
	/// CRC standard named "CRC6_DARC".
	/// </summary>
	CRC6_DARC,

	/// <summary>
	/// CRC standard named "CRC6_GSM".
	/// </summary>
	CRC6_GSM,

	/// <summary>
	/// CRC standard named "CRC6_ITU".
	/// </summary>
	CRC6_ITU,

	/// <summary>
	/// CRC standard named "CRC7".
	/// </summary>
	CRC7,

	/// <summary>
	/// CRC standard named "CRC7_ROHC".
	/// </summary>
	CRC7_ROHC,

	/// <summary>
	/// CRC standard named "CRC7_UMTS".
	/// </summary>
	CRC7_UMTS,

	/// <summary>
	/// CRC standard named "CRC8".
	/// </summary>
	CRC8,

	/// <summary>
	/// CRC standard named "CRC8_AUTOSAR".
	/// </summary>
	CRC8_AUTOSAR,

	/// <summary>
	/// CRC standard named "CRC8_BLUETOOTH".
	/// </summary>
	CRC8_BLUETOOTH,

	/// <summary>
	/// CRC standard named "CRC8_CDMA2000".
	/// </summary>
	CRC8_CDMA2000,

	/// <summary>
	/// CRC standard named "CRC8_DARC".
	/// </summary>
	CRC8_DARC,

	/// <summary>
	/// CRC standard named "CRC8_DVBS2".
	/// </summary>
	CRC8_DVBS2,

	/// <summary>
	/// CRC standard named "CRC8_EBU".
	/// </summary>
	CRC8_EBU,

	/// <summary>
	/// CRC standard named "CRC8_GSMA".
	/// </summary>
	CRC8_GSMA,

	/// <summary>
	/// CRC standard named "CRC8_GSMB".
	/// </summary>
	CRC8_GSMB,

	/// <summary>
	/// CRC standard named "CRC8_ICODE".
	/// </summary>
	CRC8_ICODE,

	/// <summary>
	/// CRC standard named "CRC8_ITU".
	/// </summary>
	CRC8_ITU,

	/// <summary>
	/// CRC standard named "CRC8_LTE".
	/// </summary>
	CRC8_LTE,

	/// <summary>
	/// CRC standard named "CRC8_MAXIM".
	/// </summary>
	CRC8_MAXIM,

	/// <summary>
	/// CRC standard named "CRC8_OPENSAFETY".
	/// </summary>
	CRC8_OPENSAFETY,

	/// <summary>
	/// CRC standard named "CRC8_ROHC".
	/// </summary>
	CRC8_ROHC,

	/// <summary>
	/// CRC standard named "CRC8_SAEJ1850".
	/// </summary>
	CRC8_SAEJ1850,

	/// <summary>
	/// CRC standard named "CRC8_WCDMA".
	/// </summary>
	CRC8_WCDMA,

	/// <summary>
	/// CRC standard named "CRC10".
	/// </summary>
	CRC10,

	/// <summary>
	/// CRC standard named "CRC10_CDMA2000".
	/// </summary>
	CRC10_CDMA2000,

	/// <summary>
	/// CRC standard named "CRC10_GSM".
	/// </summary>
	CRC10_GSM,

	/// <summary>
	/// CRC standard named "CRC11".
	/// </summary>
	CRC11,

	/// <summary>
	/// CRC standard named "CRC11_UMTS".
	/// </summary>
	CRC11_UMTS,

	/// <summary>
	/// CRC standard named "CRC12_CDMA2000".
	/// </summary>
	CRC12_CDMA2000,

	/// <summary>
	/// CRC standard named "CRC12_DECT".
	/// </summary>
	CRC12_DECT,

	/// <summary>
	/// CRC standard named "CRC12_GSM".
	/// </summary>
	CRC12_GSM,

	/// <summary>
	/// CRC standard named "CRC12_UMTS".
	/// </summary>
	CRC12_UMTS,

	/// <summary>
	/// CRC standard named "CRC13_BBC".
	/// </summary>
	CRC13_BBC,

	/// <summary>
	/// CRC standard named "CRC14_DARC".
	/// </summary>
	CRC14_DARC,

	/// <summary>
	/// CRC standard named "CRC14_GSM".
	/// </summary>
	CRC14_GSM,

	/// <summary>
	/// CRC standard named "CRC15".
	/// </summary>
	CRC15,

	/// <summary>
	/// CRC standard named "CRC15_MPT1327".
	/// </summary>
	CRC15_MPT1327,

	/// <summary>
	/// CRC standard named "ARC".
	/// </summary>
	ARC,

	/// <summary>
	/// CRC standard named "CRC16_AUGCCITT".
	/// </summary>
	CRC16_AUGCCITT,

	/// <summary>
	/// CRC standard named "CRC16_BUYPASS".
	/// </summary>
	CRC16_BUYPASS,

	/// <summary>
	/// CRC standard named "CRC16_CCITTFALSE".
	/// </summary>
	CRC16_CCITTFALSE,

	/// <summary>
	/// CRC standard named "CRC16_CDMA2000".
	/// </summary>
	CRC16_CDMA2000,

	/// <summary>
	/// CRC standard named "CRC16_CMS".
	/// </summary>
	CRC16_CMS,

	/// <summary>
	/// CRC standard named "CRC16_DDS110".
	/// </summary>
	CRC16_DDS110,

	/// <summary>
	/// CRC standard named "CRC16_DECTR".
	/// </summary>
	CRC16_DECTR,

	/// <summary>
	/// CRC standard named "CRC16_DECTX".
	/// </summary>
	CRC16_DECTX,

	/// <summary>
	/// CRC standard named "CRC16_DNP".
	/// </summary>
	CRC16_DNP,

	/// <summary>
	/// CRC standard named "CRC16_EN13757".
	/// </summary>
	CRC16_EN13757,

	/// <summary>
	/// CRC standard named "CRC16_GENIBUS".
	/// </summary>
	CRC16_GENIBUS,

	/// <summary>
	/// CRC standard named "CRC16_GSM".
	/// </summary>
	CRC16_GSM,

	/// <summary>
	/// CRC standard named "CRC16_LJ1200".
	/// </summary>
	CRC16_LJ1200,

	/// <summary>
	/// CRC standard named "CRC16_MAXIM".
	/// </summary>
	CRC16_MAXIM,

	/// <summary>
	/// CRC standard named "CRC16_MCRF4XX".
	/// </summary>
	CRC16_MCRF4XX,

	/// <summary>
	/// CRC standard named "CRC16_OPENSAFETYA".
	/// </summary>
	CRC16_OPENSAFETYA,

	/// <summary>
	/// CRC standard named "CRC16_OPENSAFETYB".
	/// </summary>
	CRC16_OPENSAFETYB,

	/// <summary>
	/// CRC standard named "CRC16_PROFIBUS".
	/// </summary>
	CRC16_PROFIBUS,

	/// <summary>
	/// CRC standard named "CRC16_RIELLO".
	/// </summary>
	CRC16_RIELLO,

	/// <summary>
	/// CRC standard named "CRC16_T10DIF".
	/// </summary>
	CRC16_T10DIF,

	/// <summary>
	/// CRC standard named "CRC16_TELEDISK".
	/// </summary>
	CRC16_TELEDISK,

	/// <summary>
	/// CRC standard named "CRC16_TMS37157".
	/// </summary>
	CRC16_TMS37157,

	/// <summary>
	/// CRC standard named "CRC16_USB".
	/// </summary>
	CRC16_USB,

	/// <summary>
	/// CRC standard named "CRCA".
	/// </summary>
	CRCA,

	/// <summary>
	/// CRC standard named "KERMIT".
	/// </summary>
	KERMIT,

	/// <summary>
	/// CRC standard named "MODBUS".
	/// </summary>
	MODBUS,

	/// <summary>
	/// CRC standard named "X25".
	/// </summary>
	X25,

	/// <summary>
	/// CRC standard named "XMODEM".
	/// </summary>
	XMODEM,

	/// <summary>
	/// CRC standard named "CRC17_CANFD".
	/// </summary>
	CRC17_CANFD,

	/// <summary>
	/// CRC standard named "CRC21_CANFD".
	/// </summary>
	CRC21_CANFD,

	/// <summary>
	/// CRC standard named "CRC24".
	/// </summary>
	CRC24,

	/// <summary>
	/// CRC standard named "CRC24_BLE".
	/// </summary>
	CRC24_BLE,

	/// <summary>
	/// CRC standard named "CRC24_FLEXRAYA".
	/// </summary>
	CRC24_FLEXRAYA,

	/// <summary>
	/// CRC standard named "CRC24_FLEXRAYB".
	/// </summary>
	CRC24_FLEXRAYB,

	/// <summary>
	/// CRC standard named "CRC24_INTERLAKEN".
	/// </summary>
	CRC24_INTERLAKEN,

	/// <summary>
	/// CRC standard named "CRC24_LTEA".
	/// </summary>
	CRC24_LTEA,

	/// <summary>
	/// CRC standard named "CRC24_LTEB".
	/// </summary>
	CRC24_LTEB,

	/// <summary>
	/// CRC standard named "CRC30_CDMA".
	/// </summary>
	CRC30_CDMA,

	/// <summary>
	/// CRC standard named "CRC31_PHILIPS".
	/// </summary>
	CRC31_PHILIPS,

	/// <summary>
	/// CRC standard named "CRC32".
	/// </summary>
	CRC32,

	/// <summary>
	/// CRC standard named "CRC32_AUTOSAR".
	/// </summary>
	CRC32_AUTOSAR,

	/// <summary>
	/// CRC standard named "CRC32_BZIP2".
	/// </summary>
	CRC32_BZIP2,

	/// <summary>
	/// CRC standard named "CRC32C".
	/// </summary>
	CRC32C,

	/// <summary>
	/// CRC standard named "CRC32D".
	/// </summary>
	CRC32D,

	/// <summary>
	/// CRC standard named "CRC32_MPEG2".
	/// </summary>
	CRC32_MPEG2,

	/// <summary>
	/// CRC standard named "CRC32_POSIX".
	/// </summary>
	CRC32_POSIX,

	/// <summary>
	/// CRC standard named "CRC32Q".
	/// </summary>
	CRC32Q,

	/// <summary>
	/// CRC standard named "JAMCRC".
	/// </summary>
	JAMCRC,

	/// <summary>
	/// CRC standard named "XFER".
	/// </summary>
	XFER,

	/// <summary>
	/// CRC standard named "CRC40_GSM".
	/// </summary>
	CRC40_GSM,

	/// <summary>
	/// CRC standard named "CRC64".
	/// </summary>
	CRC64,

	/// <summary>
	/// CRC standard named "CRC64_GOISO".
	/// </summary>
	CRC64_GOISO,

	/// <summary>
	/// CRC standard named "CRC64_WE".
	/// </summary>
	CRC64_WE,

	/// <summary>
	/// CRC standard named "CRC64_XZ".
	/// </summary>
	CRC64_XZ
}; // end enum

class CRC : public Hash, public IIChecksum, public IICRC, public IITransformBlock
{
public:
	CRC(const int32_t _Width, const uint64_t _poly, const uint64_t _Init,
		const bool _refIn, const bool _refOut, const uint64_t _XorOut,
		const uint64_t _check, const HashLibStringArray &_Names)
		: Hash(0, 0) // Ok, Nothing serious..
	{
		name = __func__;

		IsTableGenerated = false;

		if (_Width >= 0 && _Width <= 7)
		{
			hash_size = 1;
			block_size = 1;
		} // end if
		else if (_Width >= 8 && _Width <= 16)
		{
			hash_size = 2;
			block_size = 1;
		} // end else if
		else if (_Width >= 17 && _Width <= 39)
		{
			hash_size = 4;
			block_size = 1;
		} // end else if
		else
		{
			hash_size = 8;
			block_size = 1;
		} // end else

		Names = _Names;
		Width = _Width;
		Polynomial = _poly;
		Init = _Init;
		ReflectIn = _refIn;
		ReflectOut = _refOut;
		XorOut = _XorOut;
		CheckValue = _check;

	} // end constructor

	~CRC()
	{
		//	delete CRCTable;
	} // end destructor

	virtual void Initialize()
	{
		// initialize some bitmasks
		CRCMask = (((uint64_t(1) << (Width - 1)) - 1) << 1) | 1;
		CRCHighBitMask = uint64_t(1) << (Width - 1);
		hash = Init;

		if (Width > Delta) // then use table
		{
			if (! IsTableGenerated)
				GenerateTable();

			if (ReflectIn)
				hash = Reflect(hash, Width);
		} // end if
	} // end function Initialize

	virtual IHashResult TransformFinal()
	{
		register uint64_t LUInt64;
		register uint32_t LUInt32;
		register uint16_t LUInt16;
		register uint8_t LUInt8;
				
		if (Width > Delta)
		{
			if (ReflectIn ^ ReflectOut)
				hash = Reflect(hash, Width);
		} // end if
		else
		{
			if (ReflectOut)
				hash = Reflect(hash, Width);
		} // end else

		hash = hash ^ XorOut;
		hash = hash & CRCMask;

		if (Width == 21) // special case
		{
			LUInt32 = (uint32_t)hash;

			IHashResult result(new HashResult(LUInt32));

			Initialize();

			return result;
		} // end if

		int64_t value = Width >> 3;
		
		if (value == 0)
		{
			LUInt8 = (uint8_t)hash;
			Initialize();
			return IHashResult(new HashResult(LUInt8));
		} // end result
		else if (value == 1 || value == 2)
		{
			LUInt16 = (uint16_t)hash;
			Initialize();
			return IHashResult(new HashResult(LUInt16));
		} // end else if
		else if (value == 3 || value == 4)
		{
			LUInt32 = (uint32_t)hash;
			Initialize();
			return IHashResult(new HashResult(LUInt32));
		} // end else if
		
		LUInt64 = hash;
		Initialize();
		return IHashResult(new HashResult(LUInt64));
	} // end function TransformFinal

	virtual void TransformBytes(const HashLibByteArray &a_data, int32_t a_index, int32_t a_length)
	{
		// table driven CRC reportedly only works for 8, 16, 24, 32 bits
		// HOWEVER, it seems to work for everything > 7 bits, so use it
		// accordingly

		int32_t i = a_index;

		uint8_t *ptr_a_data = (uint8_t *)&a_data[0];

		if (Width > Delta)
			CalculateCRCbyTable(ptr_a_data, a_length, i);
		else
			CalculateCRCdirect(ptr_a_data, a_length, i);
		
	} // end function TransformBytes

	static ICRC CreateCRCObject(const CRCStandard &a_value)
	{
		switch (a_value)
		{
		case CRC3_GSM:
			return ICRC(new CRC(3, 0x3, 0x0, false, false, 0x7, 0x4, HashLibStringArray({ "CRC-3/GSM" })));

		case CRC3_ROHC:
			return ICRC(new CRC(3, 0x3, 0x7, true, true, 0x0, 0x6, HashLibStringArray({ "CRC-3/ROHC" })));

		case CRC4_INTERLAKEN:
			return ICRC(new CRC(4, 0x3, 0xF, false, false, 0xF, 0xB, HashLibStringArray({ "CRC-4/INTERLAKEN" })));

		case CRC4_ITU:
			return ICRC(new CRC(4, 0x3, 0x0, true, true, 0x0, 0x7, HashLibStringArray({ "CRC-4/ITU" })));

		case CRC5_EPC:
			return ICRC(new CRC(5, 0x9, 0x9, false, false, 0x00, 0x00, HashLibStringArray({ "CRC-5/EPC" })));

		case CRC5_ITU:
			return ICRC(new CRC(5, 0x15, 0x00, true, true, 0x00, 0x07, HashLibStringArray({ "CRC-5/ITU" })));

		case CRC5_USB:
			return ICRC(new CRC(5, 0x05, 0x1F, true, true, 0x1F, 0x19, HashLibStringArray({ "CRC-5/USB" })));

		case CRC6_CDMA2000A:
			return ICRC(new CRC(6, 0x27, 0x3F, false, false, 0x00, 0x0D, HashLibStringArray({ "CRC-6/CDMA2000-A" })));

		case CRC6_CDMA2000B:
			return ICRC(new CRC(6, 0x07, 0x3F, false, false, 0x00, 0x3B, HashLibStringArray({ "CRC-6/CDMA2000-B" })));

		case CRC6_DARC:
			return ICRC(new CRC(6, 0x19, 0x00, true, true, 0x00, 0x26, HashLibStringArray({ "CRC-6/DARC" })));

		case CRC6_GSM:
			return ICRC(new CRC(6, 0x2F, 0x00, false, false, 0x3F, 0x13, HashLibStringArray({ "CRC-6/GSM" })));
			
		case CRC6_ITU:
			return ICRC(new CRC(6, 0x03, 0x00, true, true, 0x00, 0x06, HashLibStringArray({ "CRC-6/ITU" })));

		case CRC7:
			return ICRC(new CRC(7, 0x09, 0x00, false, false, 0x00, 0x75,	HashLibStringArray({"CRC-7"})));
			
		case CRC7_ROHC:
			return ICRC(new CRC(7, 0x4F, 0x7F, true, true, 0x00, 0x53, HashLibStringArray({"CRC-7/ROHC"})));
			
		case CRC7_UMTS:
			return ICRC(new CRC(7, 0x45, 0x00, false, false, 0x00, 0x61, HashLibStringArray({"CRC-7/UMTS"})));
			
		case CRC8:
			return ICRC(new CRC(8, 0x07, 0x00, false, false, 0x00, 0xF4, HashLibStringArray({"CRC-8"})));
			
		case CRC8_AUTOSAR:
			return ICRC(new CRC(8, 0x2F, 0xFF, false, false, 0xFF, 0xDF, HashLibStringArray({"CRC-8/AUTOSAR"})));
			
		case CRC8_BLUETOOTH:
			return ICRC(new CRC(8, 0xA7, 0x00, true, true, 0x00, 0x26, HashLibStringArray({"CRC-8/BLUETOOTH"})));
			
		case CRC8_CDMA2000:
			return ICRC(new CRC(8, 0x9B, 0xFF, false, false, 0x00, 0xDA, HashLibStringArray({"CRC-8/CDMA2000"})));
			
		case CRC8_DARC:
			return ICRC(new CRC(8, 0x39, 0x00, true, true, 0x00, 0x15, HashLibStringArray({"CRC-8/DARC"})));
			
		case CRC8_DVBS2:
			return ICRC(new CRC(8, 0xD5, 0x00, false, false, 0x00, 0xBC, HashLibStringArray({"CRC-8/DVB-S2"})));
			
		case CRC8_EBU:
			return ICRC(new CRC(8, 0x1D, 0xFF, true, true, 0x00, 0x97, HashLibStringArray({"CRC-8/EBU", "CRC-8/AES"})));
			
		case CRC8_GSMA:
			return ICRC(new CRC(8, 0x1D, 0x00, false, false, 0x00, 0x37, HashLibStringArray({"CRC-8/GSM-A"})));
			
		case CRC8_GSMB:
			return ICRC(new CRC(8, 0x49, 0x00, false, false, 0xFF, 0x94, HashLibStringArray({"CRC-8/GSM-B"})));
			
		case CRC8_ICODE:
			return ICRC(new CRC(8, 0x1D, 0xFD, false, false, 0x00, 0x7E, HashLibStringArray({"CRC-8/I-CODE"})));
			
		case CRC8_ITU:
			return ICRC(new CRC(8, 0x07, 0x00, false, false, 0x55, 0xA1, HashLibStringArray({"CRC-8/ITU"})));
			
		case CRC8_LTE:
			return ICRC(new CRC(8, 0x9B, 0x00, false, false, 0x00, 0xEA, HashLibStringArray({"CRC-8/LTE"})));
			
		case CRC8_MAXIM:
			return ICRC(new CRC(8, 0x31, 0x00, true, true, 0x00, 0xA1, HashLibStringArray({"CRC-8/MAXIM", "DOW-CRC"})));
			
		case CRC8_OPENSAFETY:
			return ICRC(new CRC(8, 0x2F, 0x00, false, false, 0x00, 0x3E, HashLibStringArray({"CRC-8/OPENSAFETY"})));
			
		case CRC8_ROHC:
			return ICRC(new CRC(8, 0x07, 0xFF, true, true, 0x00, 0xD0, HashLibStringArray({"CRC-8/ROHC"})));
			
		case CRC8_SAEJ1850:
			return ICRC(new CRC(8, 0x1D, 0xFF, false, false, 0xFF, 0x4B, HashLibStringArray({"CRC-8/SAE-J1850"})));
			
		case CRC8_WCDMA:
			return ICRC(new CRC(8, 0x9B, 0x00, true, true, 0x00, 0x25, HashLibStringArray({"CRC-8/WCDMA"})));
			
		case CRC10:
			return ICRC(new CRC(10, 0x233, 0x000, false, false, 0x000, 0x199, HashLibStringArray({"CRC-10"})));
			
		case CRC10_CDMA2000:
			return ICRC(new CRC(10, 0x3D9, 0x3FF, false, false, 0x000, 0x233, HashLibStringArray({"CRC-10/CDMA2000"})));
			
		case CRC10_GSM:
			return ICRC(new CRC(10, 0x175, 0x000, false, false, 0x3FF, 0x12A, HashLibStringArray({"CRC-10/GSM"})));
			
		case CRC11:
			return ICRC(new CRC(11, 0x385, 0x01A, false, false, 0x000, 0x5A3, HashLibStringArray({"CRC-11"})));
			
		case CRC11_UMTS:
			return ICRC(new CRC(11, 0x307, 0x000, false, false, 0x000, 0x061, HashLibStringArray({"CRC-11/UMTS"})));
			
		case CRC12_CDMA2000:
			return ICRC(new CRC(12, 0xF13, 0xFFF, false, false, 0x000, 0xD4D, HashLibStringArray({"CRC-12/CDMA2000"})));
			
		case CRC12_DECT:
			return ICRC(new CRC(12, 0x80F, 0x000, false, false, 0x000, 0xF5B, HashLibStringArray({"CRC-12/DECT", "X-CRC-12"})));
			
		case CRC12_GSM:
			return ICRC(new CRC(12, 0xD31, 0x000, false, false, 0xFFF, 0xB34, HashLibStringArray({"CRC-12/GSM"})));
			
		case CRC12_UMTS:
			return ICRC(new CRC(12, 0x80F, 0x000, false, true, 0x000, 0xDAF,	HashLibStringArray({"CRC-12/UMTS", "CRC-12/3GPP"})));
			
		case CRC13_BBC:
			return ICRC(new CRC(13, 0x1CF5, 0x0000, false, false, 0x0000, 0x04FA, HashLibStringArray({"CRC-13/BBC"})));
			
		case CRC14_DARC:
			return ICRC(new CRC(14, 0x0805, 0x0000, true, true, 0x0000, 0x082D, HashLibStringArray({"CRC-14/DARC"})));
			
		case CRC14_GSM:
			return ICRC(new CRC(14, 0x202D, 0x0000, false, false, 0x3FFF, 0x30AE, HashLibStringArray({"CRC-14/GSM"})));
			
		case CRC15:
			return ICRC(new CRC(15, 0x4599, 0x0000, false, false, 0x0000, 0x059E, HashLibStringArray({"CRC-15"})));
			
		case CRC15_MPT1327:
			return ICRC(new CRC(15, 0x6815, 0x0000, false, false, 0x0001, 0x2566, HashLibStringArray({"CRC-15/MPT1327"})));
			
		case ARC:
			return ICRC(new CRC(16, 0x8005, 0x0000, true, true, 0x0000, 0xBB3D, HashLibStringArray({"CRC-16", "ARC", "CRC-IBM", "CRC-16/ARC", "CRC-16/LHA"})));
			
		case CRC16_AUGCCITT:
			return ICRC(new CRC(16, 0x1021, 0x1D0F, false, false, 0x0000, 0xE5CC, HashLibStringArray({"CRC-16/AUG-CCITT", "CRC-16/SPI-FUJITSU"})));
			
		case CRC16_BUYPASS:
			return ICRC(new CRC(16, 0x8005, 0x0000, false, false, 0x0000, 0xFEE8, HashLibStringArray({"CRC-16/BUYPASS", "CRC-16/VERIFONE"})));
			
		case CRC16_CCITTFALSE:
			return ICRC(new CRC(16, 0x1021, 0xFFFF, false, false, 0x0000, 0x29B1, HashLibStringArray({"CRC-16/CCITT-FALSE"})));
			
		case CRC16_CDMA2000:
			return ICRC(new CRC(16, 0xC867, 0xFFFF, false, false, 0x0000, 0x4C06, HashLibStringArray({"CRC-16/CDMA2000"})));
			
		case CRC16_CMS:
			return ICRC(new CRC(16, 0x8005, 0xFFFF, false, false, 0x0000, 0xAEE7, HashLibStringArray({"CRC-16/CMS"})));
			
		case CRC16_DDS110:
			return ICRC(new CRC(16, 0x8005, 0x800D, false, false, 0x0000, 0x9ECF, HashLibStringArray({"CRC-16/DDS-110"})));
			
		case CRC16_DECTR:
			return ICRC(new CRC(16, 0x0589, 0x0000, false, false, 0x0001, 0x007E, HashLibStringArray({"CRC-16/DECT-R", "R-CRC-16"})));
			
		case CRC16_DECTX:
			return ICRC(new CRC(16, 0x0589, 0x0000, false, false, 0x0000, 0x007F, HashLibStringArray({"CRC-16/DECT-X", "X-CRC-16"})));
			
		case CRC16_DNP:
			return ICRC(new CRC(16, 0x3D65, 0x0000, true, true, 0xFFFF, 0xEA82, HashLibStringArray({"CRC-16/DNP"})));
			
		case CRC16_EN13757:
			return ICRC(new CRC(16, 0x3D65, 0x0000, false, false, 0xFFFF, 0xC2B7, HashLibStringArray({"CRC-16/EN13757"})));
			
		case CRC16_GENIBUS:
			return ICRC(new CRC(16, 0x1021, 0xFFFF, false, false, 0xFFFF, 0xD64E, HashLibStringArray({"CRC-16/GENIBUS", "CRC-16/EPC", "CRC-16/I-CODE", "CRC-16/DARC"})));
			
		case CRC16_GSM:
			return ICRC(new CRC(16, 0x1021, 0x0000, false, false, 0xFFFF, 0xCE3C, HashLibStringArray({"CRC-16/GSM"})));
			
		case CRC16_LJ1200:
			return ICRC(new CRC(16, 0x6F63, 0x0000, false, false, 0x0000, 0xBDF4, HashLibStringArray({"CRC-16/LJ1200"})));
			
		case CRC16_MAXIM:
			return ICRC(new CRC(16, 0x8005, 0x0000, true, true, 0xFFFF, 0x44C2, HashLibStringArray({"CRC-16/MAXIM"})));
			
		case CRC16_MCRF4XX:
			return ICRC(new CRC(16, 0x1021, 0xFFFF, true, true, 0x0000, 0x6F91, HashLibStringArray({"CRC-16/MCRF4XX"})));
			
		case CRC16_OPENSAFETYA:
			return ICRC(new CRC(16, 0x5935, 0x0000, false, false, 0x0000, 0x5D38, HashLibStringArray({"CRC-16/OPENSAFETY-A"})));
			
		case CRC16_OPENSAFETYB:
			return ICRC(new CRC(16, 0x755B, 0x0000, false, false, 0x0000, 0x20FE, HashLibStringArray({"CRC-16/OPENSAFETY-B"})));
			
		case CRC16_PROFIBUS:
			return ICRC(new CRC(16, 0x1DCF, 0xFFFF, false, false, 0xFFFF, 0xA819, HashLibStringArray({"CRC-16/PROFIBUS", "CRC-16/IEC-61158-2"})));
			
		case CRC16_RIELLO:
			return ICRC(new CRC(16, 0x1021, 0xB2AA, true, true, 0x0000, 0x63D0, HashLibStringArray({"CRC-16/RIELLO"})));
			
		case CRC16_T10DIF:
			return ICRC(new CRC(16, 0x8BB7, 0x0000, false, false, 0x0000, 0xD0DB, HashLibStringArray({"CRC-16/T10-DIF"})));
			
		case CRC16_TELEDISK:
			return ICRC(new CRC(16, 0xA097, 0x0000, false, false, 0x0000, 0x0FB3, HashLibStringArray({"CRC-16/TELEDISK"})));
			
		case CRC16_TMS37157:
			return ICRC(new CRC(16, 0x1021, 0x89EC, true, true, 0x0000, 0x26B1, HashLibStringArray({"CRC-16/TMS37157"})));
			
		case CRC16_USB:
			return ICRC(new CRC(16, 0x8005, 0xFFFF, true, true, 0xFFFF, 0xB4C8, HashLibStringArray({"CRC-16/USB"})));
			
		case CRCA:
			return ICRC(new CRC(16, 0x1021, 0xC6C6, true, true, 0x0000, 0xBF05, HashLibStringArray({"CRC-A"})));
			
		case KERMIT:
			return ICRC(new CRC(16, 0x1021, 0x0000, true, true, 0x0000, 0x2189, HashLibStringArray({"KERMIT", "CRC-16/CCITT", "CRC-16/CCITT-TRUE", "CRC-CCITT"})));
			
		case MODBUS:
			return ICRC(new CRC(16, 0x8005, 0xFFFF, true, true, 0x0000, 0x4B37, HashLibStringArray({"MODBUS"})));
			
		case X25:
			return ICRC(new CRC(16, 0x1021, 0xFFFF, true, true, 0xFFFF, 0x906E, HashLibStringArray({"X-25", "CRC-16/IBM-SDLC", "CRC-16/ISO-HDLC", "CRC-B"})));
			
		case XMODEM:
			return ICRC(new CRC(16, 0x1021, 0x0000, false, false, 0x0000, 0x31C3, HashLibStringArray({"XMODEM", "ZMODEM", "CRC-16/ACORN"})));
			
		case CRC17_CANFD:
			return ICRC(new CRC(17, 0x1685B, 0x00000, false, false, 0x00000, 0x04F03, HashLibStringArray({"CRC-17/CAN-FD"})));
			
		case CRC21_CANFD:
			return ICRC(new CRC(21, 0x102899, 0x00000, false, false, 0x00000, 0x0ED841, HashLibStringArray({"CRC-21/CAN-FD"})));
			
		case CRC24:
			return ICRC(new CRC(24, 0x864CFB, 0xB704CE, false, false, 0x000000, 0x21CF02, HashLibStringArray({"CRC-24", "CRC-24/OPENPGP"})));
			
		case CRC24_BLE:
			return ICRC(new CRC(24, 0x00065B, 0x555555, true, true, 0x000000, 0xC25A56, HashLibStringArray({"CRC-24/BLE"})));
			
		case CRC24_FLEXRAYA:
			return ICRC(new CRC(24, 0x5D6DCB, 0xFEDCBA, false, false, 0x000000, 0x7979BD, HashLibStringArray({"CRC-24/FLEXRAY-A"})));
			
		case CRC24_FLEXRAYB:
			return ICRC(new CRC(24, 0x5D6DCB, 0xABCDEF, false, false, 0x000000, 0x1F23B8, HashLibStringArray({"CRC-24/FLEXRAY-B"})));
			
		case CRC24_INTERLAKEN:
			return ICRC(new CRC(24, 0x328B63, 0xFFFFFF, false, false, 0xFFFFFF, 0xB4F3E6, HashLibStringArray({"CRC-24/INTERLAKEN"})));
			
		case CRC24_LTEA:
			return ICRC(new CRC(24, 0x864CFB, 0x000000, false, false, 0x000000, 0xCDE703, HashLibStringArray({"CRC-24/LTE-A"})));
			
		case CRC24_LTEB:
			return ICRC(new CRC(24, 0x800063, 0x000000, false, false, 0x000000, 0x23EF52, HashLibStringArray({"CRC-24/LTE-B"})));
			
		case CRC30_CDMA:
			return ICRC(new CRC(30, 0x2030B9C7, 0x3FFFFFFF, false, false, 0x3FFFFFFF, 0x04C34ABF, HashLibStringArray({"CRC-30/CDMA"})));
			
		case CRC31_PHILIPS:
			return ICRC(new CRC(31, 0x04C11DB7, 0x7FFFFFFF, false, false, 0x7FFFFFFF, 0x0CE9E46C, HashLibStringArray({"CRC-31/PHILLIPS"})));
			
		case CRC32:
			return ICRC(new CRC(32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF, 0xCBF43926, HashLibStringArray({"CRC-32", "CRC-32/ADCCP", "PKZIP"})));
			
		case CRC32_AUTOSAR:
			return ICRC(new CRC(32, 0xF4ACFB13, 0xFFFFFFFF, true, true, 0xFFFFFFFF, 0x1697D06A, HashLibStringArray({"CRC-32/AUTOSAR"})));
			
		case CRC32_BZIP2:
			return ICRC(new CRC(32, 0x04C11DB7, 0xFFFFFFFF, false, false, 0xFFFFFFFF, 0xFC891918, HashLibStringArray({"CRC-32/BZIP2", "CRC-32/AAL5",	"CRC-32/DECT-B", "B-CRC-32"})));
			
		case CRC32C:
			return ICRC(new CRC(32, 0x1EDC6F41, 0xFFFFFFFF, true, true, 0xFFFFFFFF, 0xE3069283, HashLibStringArray({"CRC-32C", "CRC-32/ISCSI", "CRC-32/CASTAGNOLI", "CRC-32/INTERLAKEN"})));
			
		case CRC32D:
			return ICRC(new CRC(32, 0xA833982B, 0xFFFFFFFF, true, true, 0xFFFFFFFF, 0x87315576, HashLibStringArray({"CRC-32D"})));
			
		case CRC32_MPEG2:
			return ICRC(new CRC(32, 0x04C11DB7, 0xFFFFFFFF, false, false, 0x00000000, 0x0376E6E7, HashLibStringArray({"CRC-32/MPEG-2"})));
			
		case CRC32_POSIX:
			return ICRC(new CRC(32, 0x04C11DB7, 0xFFFFFFFF, false, false, 0x00000000, 0x0376E6E7, HashLibStringArray({"CRC-32/POSIX", "CKSUM"})));
			
		case CRC32Q:
			return ICRC(new CRC(32, 0x814141AB, 0x00000000, false, false, 0x00000000, 0x3010BF7F, HashLibStringArray({"CRC-32Q"})));
			
		case JAMCRC:
			return ICRC(new CRC(32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0x00000000, 0x340BC6D9, HashLibStringArray({"JAMCRC"})));
			
		case XFER:
			return ICRC(new CRC(32, 0x000000AF, 0x00000000, false, false, 0x00000000, 0xBD0BE338, HashLibStringArray({"XFER"})));
			
		case CRC40_GSM:
			return ICRC(new CRC(40, 0x0004820009, 0x0000000000, false, false, 0xFFFFFFFFFF, 0xD4164FC646, HashLibStringArray({"CRC-40/GSM"})));
			
		case CRC64:
			return ICRC(new CRC(64, 0x42F0E1EBA9EA3693, 0x0000000000000000, false, false, 0x0000000000000000, 0x6C40DF5F0B497347, HashLibStringArray({"CRC-64", "CRC-64/ECMA-182"})));
			
		case CRC64_GOISO:
			return ICRC(new CRC(64, 0x000000000000001B, 0xFFFFFFFFFFFFFFFF, true, true, 0xFFFFFFFFFFFFFFFF, 0xB90956C775A41001, HashLibStringArray({"CRC-64/GO-ISO"})));
			
		case CRC64_WE:
			return ICRC(new CRC(64, 0x42F0E1EBA9EA3693, uint64_t(0xFFFFFFFFFFFFFFFF), false, false, uint64_t(0xFFFFFFFFFFFFFFFF), 0x62EC59E3F1A4F00A, HashLibStringArray({"CRC-64/WE"})));																																																																																																																																																																																																		
		
		case CRC64_XZ:
			return ICRC(new CRC(64, 0x42F0E1EBA9EA3693, uint64_t(0xFFFFFFFFFFFFFFFF), true, true, uint64_t(0xFFFFFFFFFFFFFFFF), uint64_t(0x995DC9BBDF1939FA), HashLibStringArray({ "CRC-64/XZ", "CRC-64/GO-ECMA" })));
		
		} // end switch

		throw ArgumentHashLibException("Invalid CRCStandard object.");
	} // end function CreateCRCObject

private:
	inline void SetNames(const HashLibStringArray &value)
	{
		Names = value;
	} // end function SetNames

	inline void SetWidth(const int32_t value)
	{
		Width = value;
	} // end function SetWidth

	inline void SetPolynomial(const uint64_t value)
	{
		Polynomial = value;
	} // end function SetPolynomial

	inline void SetInit(const uint64_t value)
	{
		Init = value;
	} // end function SetInit

	inline void SetReflectIn(const bool value)
	{
		ReflectIn = value;
	} // end function SetReflectIn

	inline void SetReflectOut(const bool value)
	{
		ReflectOut = value;
	} // end function SetReflectOut

	inline void SetXOROut(const uint64_t value)
	{
		XorOut = value;
	} // end function SetXOROut

	inline void SetCheckValue(const uint64_t value)
	{
		CheckValue = value;
	} // end function SetCheckValue

public:
	inline virtual HashLibStringArray GetNames() const
	{
		return Names;
	} // end function GetNames

	inline virtual int32_t GetWidth() const
	{
		return Width;
	} // end function GetWidth

	inline virtual uint64_t GetPolynomial() const
	{
		return Polynomial;
	} // end function GetPolynomial

	inline virtual uint64_t GetInit() const
	{
		return Init;
	} // end function GetInit

	inline virtual bool GetReflectIn() const
	{
		return ReflectIn;
	} // end function GetReflectIn

	inline virtual bool GetReflectOut() const
	{
		return ReflectOut;
	} // end function GetReflectOut 

	inline virtual uint64_t GetXOROut() const
	{
		return XorOut;
	} // end function GetXOROut

	inline virtual uint64_t GetCheckValue() const
	{
		return CheckValue;
	} // end function GetCheckValue

private:
	void GenerateTable()
	{
		register uint64_t bit, crc;
		register uint32_t i = 0, j = 0;
		
		CRCTable = make_shared<HashLibUInt64Array>(256);
		ptr_Fm_CRCTable = &(*CRCTable)[0];

		while (i < 256)
		{
			crc = i;
			if (ReflectIn)
				crc = Reflect(crc, 8);

			crc = crc << (Width - 8);
			j = 0;
			while (j < 8)
			{
				bit = crc & CRCHighBitMask;
				crc = crc << 1;
				if (bit != 0)
					crc = (crc ^ Polynomial);			
				j++;
			} // end while

			if (ReflectIn)
				crc = Reflect(crc, Width);

			crc = crc & CRCMask;
			ptr_Fm_CRCTable[i] = crc;
			i++;
		} // end while

		IsTableGenerated = true;
	} // end function GenerateTable

	// tables work only for 8, 16, 24, 32 bit CRC
	void CalculateCRCbyTable(const uint8_t * a_data, const int32_t a_data_length, const int32_t a_index)
	{
		int32_t Length, i;
		uint64_t tmp;
		
		Length = a_data_length;
		i = a_index;
		tmp = hash;

		if (ReflectIn)
		{
			while (Length > 0)
			{
				tmp = (tmp >> 8) ^ ptr_Fm_CRCTable[uint8_t(tmp ^ a_data[i])];
				i++;
				Length--;
			} // end while
		} // end if
		else
		{
			while (Length > 0)
			{
				tmp = (tmp << 8) ^ ptr_Fm_CRCTable
				[uint8_t((tmp >>(Width - 8)) ^ a_data[i])];
				 i++;
				 Length--;
			} // end while
		} // end else

		hash = tmp;
	} // end function CalculateCRCbyTable

	// fast bit by bit algorithm without augmented zero bytes.
	// does not use lookup table, suited for polynomial orders between 1...32.
	void CalculateCRCdirect(const uint8_t *a_data, const int32_t a_data_length, const int32_t a_index)
	{
		int32_t Length, i;
		register uint64_t c, bit, j;
		
		Length = a_data_length;
		i = a_index;

		while (Length > 0)
		{
			c = a_data[i];
			if (ReflectIn)
				c = Reflect(c, 8);

			j = 0x80;
			while (j > 0)
			{
				bit = hash & CRCHighBitMask;
				hash = hash << 1;
				if ((c & j) > 0)
					bit = bit ^ CRCHighBitMask;
				if (bit > 0)
					hash = hash ^ Polynomial;
				j = j >> 1;
			} // end while

			i++;
			Length--;
		} // end while

	} // end function CalculateCRCdirect

	// reflects the lower 'width' bits of 'value'
	static uint64_t Reflect(const uint64_t a_value, const int32_t a_width)
	{
		register uint64_t j, i, result = 0;
		
		j = 1;
		i = uint64_t(1) << (a_width - 1);
		while (i != 0)
		{
			if ((a_value & i) != 0)
				result = result | j;
			
			j = j << 1;
			i = i >> 1;
		} // end while

		return result;
	} // end function Reflect

protected:
	virtual int32_t GetBlockSize() const
	{
		return block_size;
	} // end function GetBlockSize

	virtual int32_t GetHashSize() const
	{
		return hash_size;
	} // end function GetHashSize

private:
	int32_t block_size;
	int32_t hash_size;

	HashLibStringArray Names;
	int32_t Width;
	uint64_t Polynomial, Init, XorOut, CheckValue, CRCMask, CRCHighBitMask, hash;
	bool ReflectIn, ReflectOut;
	bool IsTableGenerated;

	shared_ptr<HashLibUInt64Array> CRCTable;
	uint64_t *ptr_Fm_CRCTable;

	static const int32_t Delta = 7;

}; // end class CRC


#endif // !HLPCRC_H

