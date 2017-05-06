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
 * @brief                   Make the caller thread to sleep for a given millisecond time.
 * @param [in] milliSecond  Sleep time
 */
[[deprecated("Use the standard sleep_for either")]]
TGON_API void Sleep(std::size_t milliSecond);

/* @return  Execution time of OS as millisecond */
TGON_API std::size_t GetOSExecutionTime();
    
/* @return  Execution time of process as millisecond */
TGON_API std::size_t GetProcessExecutionTime();

TGON_API LocalTime GetLocalTime();

} /* namespace platform */
} /* namespace tgon */