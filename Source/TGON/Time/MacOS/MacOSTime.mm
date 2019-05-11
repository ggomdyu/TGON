#include "PrecompiledHeader.h"

#include <mach/mach_time.h>

#include "../Time.h"

namespace tgon
{

TGON_API int64_t GetTickCount()
{
    return mach_absolute_time() * 0.000001f;
}

} /* namespace tgon */
