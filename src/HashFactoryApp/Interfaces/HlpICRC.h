#ifndef HLPICRC_H
#define HLPICRC_H

#include "HlpIHash.h"

class IICRC : public virtual IIHash
{
public:
	virtual HashLibStringArray GetNames() const = 0;
	virtual int32_t GetWidth() const = 0;
	virtual uint64_t GetPolynomial() const = 0;
	virtual uint64_t GetInit() const = 0;
	virtual bool GetReflectIn() const = 0;
	virtual bool GetReflectOut() const = 0;
	virtual uint64_t GetXOROut() const = 0;
	virtual uint64_t GetCheckValue() const = 0;
	
}; // end class ICRC

typedef shared_ptr<IICRC> ICRC;

#endif // !HLPICRC_H