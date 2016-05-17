#include "PrecompiledHeader.h"
#include "WindowsTime.h"

const uint32_t tgon::WindowsTime::ms_oldTime = GetTickCount( );

tgon::TSystemTime tgon::WindowsTime::GetLocalTime( )
{
#ifdef TGON_PLATFORM_WINDOWS
	SYSTEMTIME prevSysTime;
	::GetLocalTime( &prevSysTime );

	TSystemTime sysTime;
	sysTime.month = prevSysTime.wMonth;
	sysTime.day = prevSysTime.wDay;
	sysTime.year = prevSysTime.wYear;
	sysTime.dayOfWeek = prevSysTime.wDayOfWeek;
	sysTime.hour = prevSysTime.wHour;
	sysTime.minute = prevSysTime.wMinute;
	sysTime.second = prevSysTime.wSecond;

	return sysTime;
#else

#endif
}