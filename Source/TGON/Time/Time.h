/**
 * @file    Time.h
 * @author  ggomdyu
 * @since   05/15/2016
 * @brief   Set of Platform-agnostic Time interfaces.
 */

#pragma once
#include <cstdint>

#include "Platform/Config.h"

namespace tgon
{

/**@brief   Gets the milliseconds that have elapsed since the system was started. */
TGON_API int64_t GetTickCount();

} /* namespace tgon */
