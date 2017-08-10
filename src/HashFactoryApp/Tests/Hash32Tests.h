#define BOOST_TEST_MODULE Hash32TestCase

#include "TestConstants.h"

// ====================== APTestCase ======================
////////////////////
// AP
///////////////////
BOOST_AUTO_TEST_SUITE(APTestCase)

string ExpectedHashOfEmptyData = "AAAAAAAA";
string ExpectedHashOfDefaultData = "7F14EFED";
string ExpectedHashOfOnetoNine = "C0E86BE5";
string ExpectedHashOfabcde = "7F6A697A";

IHash ap = HashFactory::Hash32::CreateAP();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = ap->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = ap->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = ap->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = ap->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateAP();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = ap->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== BernsteinTestCase ======================
////////////////////
// Bernstein
///////////////////
BOOST_AUTO_TEST_SUITE(BernsteinTestCase)

string ExpectedHashOfEmptyData = "00001505";
string ExpectedHashOfDefaultData = "C4635F48";
string ExpectedHashOfOnetoNine = "35CDBB82";
string ExpectedHashOfabcde = "0F11B894";

IHash bernstein = HashFactory::Hash32::CreateBernstein();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = bernstein->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = bernstein->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = bernstein->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = bernstein->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateBernstein();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = bernstein->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== Bernstein1TestCase ======================
////////////////////
// Bernstein1
///////////////////
BOOST_AUTO_TEST_SUITE(Bernstein1TestCase)

string ExpectedHashOfEmptyData = "00001505";
string ExpectedHashOfDefaultData = "2D122E48";
string ExpectedHashOfOnetoNine = "3BABEA14";
string ExpectedHashOfabcde = "0A1DEB04";

IHash bernstein1 = HashFactory::Hash32::CreateBernstein1();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = bernstein1->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = bernstein1->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = bernstein1->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = bernstein1->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateBernstein1();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = bernstein1->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== BKDRTestCase ======================
////////////////////
// BKDR
///////////////////
BOOST_AUTO_TEST_SUITE(BKDRTestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "29E11B15";
string ExpectedHashOfOnetoNine = "DE43D6D5";
string ExpectedHashOfabcde = "B3EDEA13";

IHash bkdr = HashFactory::Hash32::CreateBKDR();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = bkdr->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = bkdr->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = bkdr->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = bkdr->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateBKDR();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = bkdr->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== DEKTestCase ======================
////////////////////
// DEK
///////////////////
BOOST_AUTO_TEST_SUITE(DEKTestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "8E01E947";
string ExpectedHashOfOnetoNine = "AB4ACBA5";
string ExpectedHashOfabcde = "0C2080E5";

IHash dek = HashFactory::Hash32::CreateDEK();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = dek->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = dek->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = dek->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = dek->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateDEK();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = dek->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== DJBTestCase ======================
////////////////////
// DJB
///////////////////
BOOST_AUTO_TEST_SUITE(DJBTestCase)

string ExpectedHashOfEmptyData = "00001505";
string ExpectedHashOfDefaultData = "C4635F48";
string ExpectedHashOfOnetoNine = "35CDBB82";
string ExpectedHashOfabcde = "0F11B894";

IHash djb = HashFactory::Hash32::CreateDJB();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = djb->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = djb->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = djb->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = djb->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateDJB();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = djb->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== ELFTestCase ======================
////////////////////
// ELF
///////////////////
BOOST_AUTO_TEST_SUITE(ELFTestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "01F5B2CC";
string ExpectedHashOfOnetoNine = "0678AEE9";
string ExpectedHashOfabcde = "006789A5";

IHash elf = HashFactory::Hash32::CreateELF();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = elf->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = elf->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = elf->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = elf->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateELF();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = elf->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== FNVTestCase ======================
////////////////////
// FNV
///////////////////
BOOST_AUTO_TEST_SUITE(FNVTestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "BE611EA3";
string ExpectedHashOfOnetoNine = "D8D70BF1";
string ExpectedHashOfabcde = "B2B39969";

IHash fnv = HashFactory::Hash32::CreateFNV();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = fnv->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = fnv->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = fnv->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = fnv->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateFNV();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = fnv->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== FNV1aTestCase ======================
////////////////////
// FNV1a
///////////////////
BOOST_AUTO_TEST_SUITE(FNV1aTestCase)

string ExpectedHashOfEmptyData = "811C9DC5";
string ExpectedHashOfDefaultData = "1892F1F8";
string ExpectedHashOfOnetoNine = "BB86B11C";
string ExpectedHashOfabcde = "749BCF08";

IHash fnv1a = HashFactory::Hash32::CreateFNV1a();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = fnv1a->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = fnv1a->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = fnv1a->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = fnv1a->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateFNV1a();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = fnv1a->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== Jenkins3TestCase ======================
////////////////////
// Jenkins3
///////////////////
BOOST_AUTO_TEST_SUITE(Jenkins3TestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "F0F69CEF";
string ExpectedHashOfOnetoNine = "845D9A96";
string ExpectedHashOfabcde = "026D72DE";

IHash jenkins3 = HashFactory::Hash32::CreateJenkins3();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = jenkins3->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = jenkins3->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = jenkins3->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = jenkins3->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateJenkins3();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = jenkins3->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== JSTestCase ======================
////////////////////
// JS
///////////////////
BOOST_AUTO_TEST_SUITE(JSTestCase)

string ExpectedHashOfEmptyData = "4E67C6A7";
string ExpectedHashOfDefaultData = "683AFCFE";
string ExpectedHashOfOnetoNine = "90A4224B";
string ExpectedHashOfabcde = "62E8C8B5";

IHash js = HashFactory::Hash32::CreateJS();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = js->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = js->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = js->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = js->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateJS();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = js->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== Murmur2TestCase ======================
////////////////////
// Murmur2
///////////////////
BOOST_AUTO_TEST_SUITE(Murmur2TestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "30512DE6";
string ExpectedHashOfOnetoNine = "DCCB0167";
string ExpectedHashOfabcde = "5F09A8DE";
string ExpectedHashOfDefaultDataWithMaxUInt32AsKey = "B15D52F0";

IHash murmur2 = HashFactory::Hash32::CreateMurmur2();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = murmur2->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = murmur2->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = murmur2->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = murmur2->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateMurmur2();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = murmur2->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKey)
{
	IHashWithKey HashWithKey = HashFactory::Hash32::CreateMurmur2();
	HashWithKey->SetKey(Converters::ReadUInt32AsBytesLE(uint32_t(-1)));

	string ActualString = HashWithKey->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultDataWithMaxUInt32AsKey == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== MurmurHash3_x86_32TestCase ======================
////////////////////
// MurmurHash3_x86_32
///////////////////
BOOST_AUTO_TEST_SUITE(MurmurHash3_x86_32TestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "3D97B9EB";
string ExpectedHashOfRandomString = "A8D02B9A";
string ExpectedHashOfZerotoFour = "19D02170";
string ExpectedHashOfEmptyDataWithOneAsKey = "514E28B7";
string ExpectedHashOfDefaultDataWithMaxUInt32AsKey = "B05606FE";

IHash murmurhash3_x86_32 = HashFactory::Hash32::CreateMurmurHash3_x86_32();

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = murmurhash3_x86_32->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = murmurhash3_x86_32->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = murmurhash3_x86_32->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateMurmurHash3_x86_32();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestRandomString)
{
	string ActualString = murmurhash3_x86_32->ComputeString(RandomStringRecord)->ToString();
	BOOST_CHECK(ExpectedHashOfRandomString == ActualString);
}

BOOST_AUTO_TEST_CASE(TestZerotoFour)
{
	string ActualString = murmurhash3_x86_32->ComputeString(ZerotoFour)->ToString();
	BOOST_CHECK(ExpectedHashOfZerotoFour == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKeyOneEmptyString)
{
	IHashWithKey HashWithKey = HashFactory::Hash32::CreateMurmurHash3_x86_32();
	HashWithKey->SetKey(Converters::ReadUInt32AsBytesLE(uint32_t(1)));

	string ActualString = HashWithKey->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyDataWithOneAsKey == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKeyMaxUInt32DefaultData)
{
	IHashWithKey HashWithKey = HashFactory::Hash32::CreateMurmurHash3_x86_32();
	HashWithKey->SetKey(Converters::ReadUInt32AsBytesLE(uint32_t(-1)));

	string ActualString = HashWithKey->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultDataWithMaxUInt32AsKey == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== OneAtTimeTestCase ======================
////////////////////
// OneAtTime
///////////////////
BOOST_AUTO_TEST_SUITE(OneAtTimeTestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "4E379A4F";
string ExpectedHashOfOnetoNine = "C66B58C5";
string ExpectedHashOfabcde = "B98559FC";

IHash oneattime = HashFactory::Hash32::CreateOneAtTime();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = oneattime->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = oneattime->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = oneattime->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = oneattime->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateOneAtTime();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = oneattime->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== PJWTestCase ======================
////////////////////
// PJW
///////////////////
BOOST_AUTO_TEST_SUITE(PJWTestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "01F5B2CC";
string ExpectedHashOfOnetoNine = "0678AEE9";
string ExpectedHashOfabcde = "006789A5";

IHash pjw = HashFactory::Hash32::CreatePJW();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = pjw->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = pjw->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = pjw->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = pjw->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreatePJW();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = pjw->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== RotatingTestCase ======================
////////////////////
// Rotating
///////////////////
BOOST_AUTO_TEST_SUITE(RotatingTestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "158009D3";
string ExpectedHashOfOnetoNine = "1076548B";
string ExpectedHashOfabcde = "00674525";

IHash rotating = HashFactory::Hash32::CreateRotating();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = rotating->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = rotating->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = rotating->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = rotating->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateRotating();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = rotating->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== RSTestCase ======================
////////////////////
// RS
///////////////////
BOOST_AUTO_TEST_SUITE(RSTestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "9EF98E63";
string ExpectedHashOfOnetoNine = "704952E9";
string ExpectedHashOfabcde = "A4A13F5D";

IHash rs = HashFactory::Hash32::CreateRS();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = rs->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = rs->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = rs->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = rs->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateRS();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = rs->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== SDBMTestCase ======================
////////////////////
// SDBM
///////////////////
BOOST_AUTO_TEST_SUITE(SDBMTestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "3001A5C9";
string ExpectedHashOfOnetoNine = "68A07035";
string ExpectedHashOfabcde = "BD500063";

IHash sdbm = HashFactory::Hash32::CreateSDBM();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = sdbm->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = sdbm->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = sdbm->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = sdbm->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateSDBM();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = sdbm->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== ShiftAndXorTestCase ======================
////////////////////
// ShiftAndXor
///////////////////
BOOST_AUTO_TEST_SUITE(ShiftAndXorTestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "BD0A7DA4";
string ExpectedHashOfOnetoNine = "E164F745";
string ExpectedHashOfabcde = "0731B823";

IHash shiftandxor = HashFactory::Hash32::CreateShiftAndXor();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = shiftandxor->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = shiftandxor->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = shiftandxor->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = shiftandxor->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateShiftAndXor();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = shiftandxor->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== SuperFastTestCase ======================
////////////////////
// SuperFast
///////////////////
BOOST_AUTO_TEST_SUITE(SuperFastTestCase)

string ExpectedHashOfEmptyData = "00000000";
string ExpectedHashOfDefaultData = "F00EB3C0";
string ExpectedHashOfOnetoNine = "9575A2E9";
string ExpectedHashOfabcde = "51ED072E";

IHash superfast = HashFactory::Hash32::CreateSuperFast();

BOOST_AUTO_TEST_CASE(TestBytesabcde)
{
	string ActualString = superfast->ComputeBytes(Bytesabcde)->ToString();
	BOOST_CHECK(ExpectedHashOfabcde == ActualString);
}

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = superfast->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = superfast->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = superfast->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateSuperFast();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestOnetoNine)
{
	string ActualString = superfast->ComputeString(OnetoNine)->ToString();
	BOOST_CHECK(ExpectedHashOfOnetoNine == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()


// ====================== XXHash32TestCase ======================
////////////////////
// XXHash32
///////////////////
BOOST_AUTO_TEST_SUITE(XXHash32TestCase)

string ExpectedHashOfEmptyData = "02CC5D05";
string ExpectedHashOfDefaultData = "6A1C7A99";
string ExpectedHashOfRandomString = "CE8CF448";
string ExpectedHashOfZerotoFour = "8AA3B71C";
string ExpectedHashOfEmptyDataWithOneAsKey = "0B2CB792";
string ExpectedHashOfDefaultDataWithMaxUInt32AsKey = "728C6772";

IHash xxhash32 = HashFactory::Hash32::CreateXXHash32();

BOOST_AUTO_TEST_CASE(TestDefaultData)
{
	string ActualString = xxhash32->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyStream)
{
	ifstream stream("EmptyFile.txt", ios::in | ios::binary);
	string ActualString = xxhash32->ComputeStream(stream)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestEmptyString)
{
	string ActualString = xxhash32->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestIncrementalHash)
{
	IHash hash = HashFactory::Hash32::CreateXXHash32();

	hash->Initialize();
	hash->TransformString(DefaultData.substr(0, 3));
	hash->TransformString(DefaultData.substr(3, 3));
	hash->TransformString(DefaultData.substr(6, 3));
	hash->TransformString(DefaultData.substr(9, 3));
	hash->TransformString(DefaultData.substr(12));

	string ActualString = hash->TransformFinal()->ToString();

	BOOST_CHECK(ExpectedHashOfDefaultData == ActualString);
}

BOOST_AUTO_TEST_CASE(TestRandomString)
{
	string ActualString = xxhash32->ComputeString(RandomStringTobacco)->ToString();
	BOOST_CHECK(ExpectedHashOfRandomString == ActualString);
}

BOOST_AUTO_TEST_CASE(TestZerotoFour)
{
	string ActualString = xxhash32->ComputeString(ZerotoFour)->ToString();
	BOOST_CHECK(ExpectedHashOfZerotoFour == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKeyOneEmptyString)
{
	IHashWithKey HashWithKey = HashFactory::Hash32::CreateXXHash32();
	HashWithKey->SetKey(Converters::ReadUInt32AsBytesLE(uint32_t(1)));

	string ActualString = HashWithKey->ComputeString(EmptyData)->ToString();
	BOOST_CHECK(ExpectedHashOfEmptyDataWithOneAsKey == ActualString);
}

BOOST_AUTO_TEST_CASE(TestWithDifferentKeyMaxUInt32DefaultData)
{
	IHashWithKey HashWithKey = HashFactory::Hash32::CreateXXHash32();
	HashWithKey->SetKey(Converters::ReadUInt32AsBytesLE(uint32_t(-1)));

	string ActualString = HashWithKey->ComputeString(DefaultData)->ToString();
	BOOST_CHECK(ExpectedHashOfDefaultDataWithMaxUInt32AsKey == ActualString);
}

BOOST_AUTO_TEST_SUITE_END()