/**
 * @filename    BaseScreen.h
 * @author      ggomdyu
 * @since       08/06/2017
 * @brief       Set of Plaform-agnostic Screen interface.
 */

#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

#include "Core/Platform/Config.h"

#include "BaseScreenType.h"

namespace tgon
{
namespace platform
{

/* @brief   Return main screen currently. */
Screen GetMainScreen();

/* @brief   Return all connected screen. */
std::vector<Screen> GetAllScreen();

} /* namespace platform */
} /* namespace tgon */
