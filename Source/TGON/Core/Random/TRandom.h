/**
 * @filename    TRandom.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include "Core/Platform/TConfig.h"

namespace tgon {
namespace random {

/* @return	Return random value between min ~ max as int */
TGON_API int Range(int min, int max);

/* @return	Return random value between min ~ max as float */
TGON_API float Range(float min, float max);

} /* namespace random */
} /* namespace tgon */