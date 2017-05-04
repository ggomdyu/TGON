#include "PrecompiledHeader.h"
#include "WindowsTime.h"

#ifndef NOMINMAX
#   define NOMINMAX
#endif
#include <Windows.h>

namespace tgon {
namespace time {

std::size_t tgon::time::GetOSExecutionTime()
{
    return GetTickCount();
}

LocalTime tgon::time::GetLocalTime()
{
    SYSTEMTIME prevSysTime;
    ::GetLocalTime(&prevSysTime);
    
    LocalTime sysTime;
    sysTime.month = prevSysTime.wMonth;
    sysTime.day = prevSysTime.wDay;
    sysTime.year = prevSysTime.wYear;
    sysTime.dayOfWeek = static_cast<DayOfWeek>(prevSysTime.wDayOfWeek);
    sysTime.hour = prevSysTime.wHour;
    sysTime.minute = prevSysTime.wMinute;
    sysTime.second = prevSysTime.wSecond;
    
    return sysTime;
}

} /* namespace time */
} /* namespace tgon */