#include "PrecompiledHeader.h"

#include <ctime>

#include "Time.h"

namespace tgon
{

TGON_API int64_t GetUnixTimestamp()
{
    timespec ts;
#ifdef _MSC_VER
    timespec_get(&ts, TIME_UTC);
#else
    clock_gettime(CLOCK_REALTIME, &ts);
#endif
    
    return (ts.tv_sec * 1000000000L + ts.tv_nsec) * 0.000001;
}

} /* namespace tgon */
