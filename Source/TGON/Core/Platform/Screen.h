/**
 * @filename    Screen.h
 * @author      ggomdyu
 * @since       08/06/2017
 * @brief       Set of Plaform-agnostic Screen interface.
 */

#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

#include "Core/Platform/Config.h"

#include "ScreenType.h"

namespace tgon
{
namespace platform
{

/**
 * @brief   Return primary screen currently.
 * @warning This function assembles many information as far as possible. 
 */
TGON_API Screen GetPrimaryScreen();

/**
 * @brief   Return all detected screen.
 * @warning This function assembles many information as far as possible.
 */
TGON_API std::vector<Screen> GetAllScreen();

} /* namespace platform */
} /* namespace tgon */
