#ifndef HLPIHASHRESULT_H
#define HLPIHASHRESULT_H

#include "../Utils/HlpHashLibTypes.h"

class IIHashResult
{
public:
	virtual HashLibByteArray GetBytes() const = 0;
	virtual uint8_t GetUInt8() const = 0;
	virtual uint16_t GetUInt16() const = 0;
	virtual uint32_t GetUInt32() const = 0;
	virtual int32_t GetInt32() const = 0;
	virtual uint64_t GetUInt64() const = 0;
	virtual string ToString(const bool a_group = false) const = 0;
	virtual int32_t GetHashCode() const = 0;

}; // end class IHashResult

typedef shared_ptr<IIHashResult> IHashResult;

#endif // !HLPIHASHRESULT_H
