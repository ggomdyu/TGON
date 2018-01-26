/**
 * @filename    Screen.h
 * @author      ggomdyu
 * @since       08/06/2017
 * @brief       Set of Plaform-agnostic Screen interfaces.
 */

#pragma once
#include "ScreenFwd.h"
#include "Config.h"

#include <vector>

namespace tgon
{
namespace core
{

/* @brief   Returns count of detected monitors. */
TGON_API int32_t GetScreenCount();

/**
 * @brief   Returns current primary screen information.
 * @warning This function assembles many information as far as possible. 
 */
TGON_API Screen GetPrimaryScreen();

/* @brief   Returns all detected screen informations.*/
TGON_API std::vector<Screen> GetAllScreens();

} /* namespace core */
} /* namespace tgon */
