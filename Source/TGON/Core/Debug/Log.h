/**
 * @filename    Log.h
 * @author      ggomdyu
 * @since       04/01/2016
 * @brief       Set of Low level Plaform-agnostic Debug interfaces.
 */

#pragma once
#include <cstdarg>

#include "Core/Platform/Config.h"

namespace tgon
{

TGON_API void Log(const char* formatStr, ...);

} /* namespace tgon */