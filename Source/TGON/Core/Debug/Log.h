/**
 * @filename    Log.h
 * @author      ggomdyu
 * @since       04/01/2016
 * @brief       Set of Low level Plaform-agnostic Debug interfaces.
 */

#pragma once
#include "Core/Platform/Config.h"

#include <cstdarg>

namespace tgon
{
namespace core
{

TGON_API void Log(const char* formatStr, ...);

} /* namespace core */
} /* namespace tgon */
