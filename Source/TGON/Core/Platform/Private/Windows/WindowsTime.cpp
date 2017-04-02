#include "PrecompiledHeader.h"
#include "WindowsTime.h"

namespace tgon
{

LocalTime WindowsTime::GetLocalTime()
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

std::size_t WindowsTime::GetBootTime()
{
	return GetTickCount();
}

} /* namespace tgon */