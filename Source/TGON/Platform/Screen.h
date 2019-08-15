/**
 * @file    Screen.h
 * @author  ggomdyu
 * @since   08/06/2017
 * @brief   Set of Plaform-agnostic Screen interfaces.
 */

#pragma once
#include <vector>

#include "Config.h"
#include "ScreenType.h"

namespace tgon
{

/**@brief   Returns count of detected monitors. */
TGON_API int32_t GetScreenCount();

/**@brief   Returns current primary screen information.  */
TGON_API Screen GetPrimaryScreen();

/**@brief   Returns all detected screen informations.*/
TGON_API std::vector<Screen> GetAllScreens();

}
