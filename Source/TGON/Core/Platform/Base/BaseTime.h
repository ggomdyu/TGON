/**
 * @filename    BaseTime.h
 * @author      ggomdyu
 * @since       05/15/2016
 * @brief       Set of Platform-agnostic Time interface.
 */

#pragma once
#include "Core/Platform/Config.h"

#include "BaseTimeType.h"

namespace tgon
{
namespace platform
{

TGON_API int64_t GetTickCount();

/* @return  The DateTime in UTC time */
TGON_API DateTime GetSystemTime();

/* @return  The DateTime in Local time */
TGON_API DateTime GetLocalTime();

} /* namespace platform */
} /* namespace tgon */
