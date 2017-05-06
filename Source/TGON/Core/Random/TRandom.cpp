#include "PrecompiledHeader.h"
#include "TRandom.h"

#include "WELLRNG.h"

namespace tgon {
namespace random {

TGON_API int Range(int min, int max)
{
	// TODO: �ڵ尡 �ణ �̻���
    return (int)std::round(Range((float)min, (float)max));
}

TGON_API float Range(float min, float max)
{
    return min + (WELLRNG512a() * (max - min));
}

} /* namespace random */
} /* namespace tgon */