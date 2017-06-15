/**
 * @filename    GenericScreen.h
 * @author      ggomdyu
 * @since       07/05/2016
 */

#pragma once
#include "Core/Platform/Config.h"

#include <cstdint>

namespace tgon
{
namespace platform
{
    
TGON_API int32_t GetMonitorCount();

TGON_API void GetScreenResolution(int32_t* width, int32_t* height);


} /* namespace platform */
} /* namespace tgon */
