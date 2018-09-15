/**
 * @file    WELL1024a.h
 * @author  ggomdyu
 * @since   05/05/2017
 * @brief   Fast uniform random number generators.
 * @see     http://www.iro.umontreal.ca/~panneton/WELLRNG.html
 */

#pragma once
#include "Core/Platform/Config.h"

namespace tgon
{

TGON_API void SrandWELL1024a();

/**@brief	Gets random value between 0.0 ~ 1.0 */
TGON_API double WELL1024a();

} /* namespace tgon */
