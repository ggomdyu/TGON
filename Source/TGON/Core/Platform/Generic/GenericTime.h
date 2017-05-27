/**
 * @filename    GenericTime.h
 * @author      ggomdyu
 * @since       05/15/2016
 */

#pragma once
#include "Core/Platform/TConfig.h"
#include "GenericTimeType.h"

namespace tgon {
namespace platform {

/**
 * @brief                   Sleep caller thread for a given millisecond time.
 * @param [in] milliSecond  Sleep time
 */
[[deprecated("Use the standard sleep_for either")]]
TGON_API void Sleep(uint32_t milliSecond);

/* @return  Execution time of OS as millisecond */
TGON_API uint32_t GetOSExecutionTime();
TGON_API uint64_t GetOSExecutionTime64();

/* @return  Execution time of process as millisecond */
TGON_API uint32_t GetProcessExecutionTime();
TGON_API uint64_t GetProcessExecutionTime64();

/* @return  Execution time of OS as millisecond */
TGON_API UnixTimeTy GetUnixTime();

/* @return  The DateTime in UTC time */
TGON_API DateTime GetSystemTime();

/* @return  The DateTime in Local time */
TGON_API DateTime GetLocalTime();

} /* namespace platform */
} /* namespace tgon */