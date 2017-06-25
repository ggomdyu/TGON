/**
 * @filename    GenericTime.h
 * @author      ggomdyu
 * @since       05/15/2016
 */

#pragma once
#include "Core/Platform/Config.h"

#include "GenericTimeType.h"

namespace tgon
{
namespace platform
{

[[deprecated("Use the standard sleep_for either")]]
TGON_API void SleepThread(uint32_t millisecond);

TGON_API uint32_t GetOSExecutionTime();
TGON_API uint64_t GetOSExecutionTime64();

TGON_API uint32_t GetProcessExecutionTime();
TGON_API uint64_t GetProcessExecutionTime64();

TGON_API UnixTimeTy GetUnixTime();

/* @return  The DateTime in UTC time */
TGON_API DateTime GetSystemTime();

/* @return  The DateTime in Local time */
TGON_API DateTime GetLocalTime();

} /* namespace platform */
} /* namespace tgon */
