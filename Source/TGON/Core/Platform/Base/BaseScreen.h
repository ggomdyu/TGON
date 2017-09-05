/**
 * @filename    BaseScreen.h
 * @author      ggomdyu
 * @since       08/06/2017
 * @brief       Set of Plaform-agnostic Screen interface.
 */

#pragma once
#include <cstddef>
#include <cstdint>

#include "Core/Platform/Config.h"

namespace tgon
{
namespace platform
{

TGON_API int32_t GetMonitorCount();

TGON_API void GetScreenResolution(int32_t* width, int32_t* height);

TGON_API float GetScaleFactor();

} /* namespace platform */
} /* namespace tgon */
