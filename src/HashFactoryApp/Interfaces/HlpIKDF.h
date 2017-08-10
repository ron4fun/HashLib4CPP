#ifndef HLPIKDF_H
#define HLPIKDF_H

#include "../Utils/HlpHashLibTypes.h"


class IIKDF
{
public:
	/// <summary>
	/// Returns the pseudo-random bytes for this object.
	/// </summary>
	/// <param name="bc">The number of pseudo-random key bytes to generate.</param>
	/// <returns>A byte array filled with pseudo-random key bytes.</returns>
	/// <exception cref="EArgumentOutOfRangeHashLibException">bc must be greater than zero.</exception>
	/// <exception cref="EArgumentHashLibException">invalid start index or end index of internal buffer.</exception>
	virtual HashLibByteArray GetBytes(const int32_t bc) = 0;

}; // end class IKDF

typedef shared_ptr<IIKDF> IKDF;

#endif // !HLPIKDF_H