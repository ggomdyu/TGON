#include "PrecompiledHeader.h"
#include "WindowsTime.h"

#include <Windows.h>


tgon::TSystemTime tgon::WindowsTime::GetLocalTime( )
{
	SYSTEMTIME prevSysTime;
	::GetLocalTime( &prevSysTime );

	TSystemTime sysTime;
	sysTime.month = prevSysTime.wMonth;
	sysTime.day = prevSysTime.wDay;
	sysTime.year = prevSysTime.wYear;
	sysTime.dayOfWeek = static_cast<TDayOfWeek>( prevSysTime.wDayOfWeek );
	sysTime.hour = prevSysTime.wHour;
	sysTime.minute = prevSysTime.wMinute;
	sysTime.second = prevSysTime.wSecond;

	return sysTime;
}