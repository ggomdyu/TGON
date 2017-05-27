/**
 * @filename    WELLRNG.h
 * @author      ggomdyu
 * @since       05/05/2017
 * @desc        Random number generate algorithm that faster than the Mersenne Twister above 40%
 * @see         http://www.iro.umontreal.ca/~panneton/WELLRNG.html
 */

#pragma once
#include "Core/Platform/TConfig.h"

namespace tgon {
namespace random {

/* @return  Return random value between 0.0 ~ 1.0 */
TGON_API double WELLRNG1024a();

} /* namespace random */
} /* namespace tgon */