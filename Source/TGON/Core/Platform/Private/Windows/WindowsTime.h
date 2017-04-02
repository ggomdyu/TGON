/**
 * filename WindowsTime.h
 * author   ggomdyu
 * since    05/15/2016
 */

#pragma once
#include "../Generic/GenericTime.h"

#include <Windows.h>

namespace tgon
{

class TGON_API WindowsTime :
	public GenericTime<WindowsTime>
{
/**
 * @section Public methods
 */
public:
	/* @return  Execution time of OS as millisecond */
	static std::size_t GetBootTime();
	
	/* @return  current system time */
	static LocalTime GetLocalTime();

/**
 * @section Ctor/Dtor
 */ 
public:
	WindowsTime() = delete;
	~WindowsTime() = delete;
};

using TTime = WindowsTime;

} /* namespace tgon */