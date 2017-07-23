/**
 * @filename    GenericTime.h
 * @author      ggomdyu
 * @since       05/15/2016
 * @desc        Set of Platform agnostic interface.
 */

#pragma once
#include "Core/Platform/Config.h"

#include "GenericTimeType.h"

namespace tgon
{
namespace platform
{

TGON_API uint32_t GetOSExecutionTime();
    
TGON_API uint32_t GetProcessExecutionTime();

TGON_API time_t GetUnixTime();

/* @return  The DateTime in UTC time */
TGON_API DateTime GetSystemTime();

/* @return  The DateTime in Local time */
TGON_API DateTime GetLocalTime();

} /* namespace platform */
} /* namespace tgon */
