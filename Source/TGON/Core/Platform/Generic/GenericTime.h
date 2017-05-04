#pragma once
#include "GenericTimeType.h"

namespace tgon {
namespace time {

/**
 * @brief                   Make the caller thread to sleep for a given millisecond time.
 * @param   milliSecond     Sleep time
 */
[[deprecated("Use the standard sleep_for either")]]
void Sleep(std::size_t milliSecond);

/* @return  Execution time of OS as millisecond */
std::size_t GetOSExecutionTime();
    
/* @return  Execution time of process as millisecond */
std::size_t GetProcessExecutionTime();

LocalTime GetLocalTime();

} /* namespace time */
} /* namespace tgon */