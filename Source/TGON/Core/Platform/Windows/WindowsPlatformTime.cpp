#include "PrecompiledHeader.h"
#include "WindowsPlatformTime.h"


namespace tgon
{


LocalTime WindowsPlatformTime::GetLocalTime( )
{
	SYSTEMTIME prevSysTime;
	::GetLocalTime( &prevSysTime );

	LocalTime sysTime;
	sysTime.month = prevSysTime.wMonth;
	sysTime.day = prevSysTime.wDay;
	sysTime.year = prevSysTime.wYear;
	sysTime.dayOfWeek = static_cast<DayOfWeek>( prevSysTime.wDayOfWeek );
	sysTime.hour = prevSysTime.wHour;
	sysTime.minute = prevSysTime.wMinute;
	sysTime.second = prevSysTime.wSecond;

	return sysTime;
}


} /*namespace tgon*/