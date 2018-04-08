/**
 * @filename    Time.h
 * @author      ggomdyu
 * @since       05/15/2016
 * @brief       Set of Platform-agnostic Time interfaces.
 */

#pragma once
#include <cstdint>

#include "Config.h"

namespace tgon
{

/* @brief   Returns OS excution elapsed time. */
TGON_API int64_t GetTickCount();

/* @brief   Returns current time information in UTC time. */
TGON_API struct DateTime GetSystemTime();

/* @brief   Returns current time information in Local time. */
TGON_API struct DateTime GetLocalTime();

} /* namespace tgon */